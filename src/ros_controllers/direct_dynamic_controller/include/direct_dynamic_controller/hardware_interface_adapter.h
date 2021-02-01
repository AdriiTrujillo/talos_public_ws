
#ifndef DIRECT_DYNAMIC_CONTROLLER_HARDWARE_INTERFACE_ADAPTER_H
#define DIRECT_DYNAMIC_CONTROLLER_HARDWARE_INTERFACE_ADAPTER_H

// C++ Standard headers
#include <cassert>
#include <string>
#include <vector>
#include <iostream>

// Boost headers
#include <boost/shared_ptr.hpp>

// ROS headers
#include "ros/ros.h"
#include <ros/node_handle.h>
#include <ros/time.h>
#include "std_msgs/Float64MultiArray.h"
#include <ddynamic_reconfigure/ddynamic_reconfigure.h>

// ROS Control headers
#include <control_toolbox/pid.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/posvel_command_interface.h>
#include <hardware_interface/posvelacc_command_interface.h>

// Eigen
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions> // For getting sqrt of a matrix
#include <Eigen/Geometry>

// KDL includes
#include <kdl_parser/kdl_parser.hpp>
#include <urdf/model.h>
#include <kdl/chaindynparam.hpp>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames.hpp>
#include <kdl/framevel.hpp>
#include <kdl/jacobian.hpp>
#include <kdl/chainjnttojacsolver.hpp>
#include <kdl/jntarray.hpp>
#include <kdl/jntarrayvel.hpp>
#include <kdl/jntarrayacc.hpp>


template <class HardwareInterface, class State>
class HardwareInterfaceAdapter
{
public:
  bool init(std::vector<typename HardwareInterface::ResourceHandleType>& /*joint_handles*/, ros::NodeHandle& /*controller_nh*/)
  {
    return false;
  }

  void starting(const ros::Time& /*time*/) {}
  void stopping(const ros::Time& /*time*/) {}

  void updateCommand(const ros::Time&     /*time*/,
                     const ros::Duration& /*period*/,
                     const State&         /*desired_state*/,
                     const State&         /*state_error*/) {}
};

/**
 * \brief Adapter for an effort-controlled hardware interface. Maps position and velocity errors to effort commands
 * through diferent strategies, which can be chosen at the YAML config file. These are:
 *  - Feedforward
 *  - PD_Feedforward
 *  - PD+
 *  - Computed_torque
 *  - Cartesian_CT
 *  - Optimal
 */
template <class State>
class HardwareInterfaceAdapter<hardware_interface::EffortJointInterface, State>
{
public:
  HardwareInterfaceAdapter() : joint_handles_ptr_(0) {}

  bool init(std::vector<hardware_interface::JointHandle>& joint_handles, ros::NodeHandle& controller_nh)
  {
    // Store pointer to joint handles
    joint_handles_ptr_ = &joint_handles;
    controller_nh_ptr_ = &controller_nh;

    // Get joint names from parameter server
    if (!controller_nh_ptr_->getParam("joints", joint_names_)){
      ROS_ERROR("Could not load joint names from parameter server");
    }

    // Get link names from parameter server
    if (!controller_nh_ptr_->getParam("links", link_names_)){
      ROS_ERROR("Could not load link names from parameter server");
    }
    


    // Obtain proportional and derivative gains stated  at the YAML config file
    std::vector<double> kp_default, kv_default = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    if (!controller_nh_ptr_->getParam("Kp", kp_default)){
      ROS_ERROR("Could not load proportional gain. Default value Kp=500");
    }

    if (!controller_nh_ptr_->getParam("Kv", kv_default)){
      ROS_ERROR("Could not load derivative gain. Default value Kv=50");
    }

    if (!controller_nh_ptr_->getParam("lambda", lambda_value)){
      ROS_ERROR("Could not load lambda. Default value Kv=50");
    }

    // Obtain required controller type. Default: PD_Gravity_Compensation
    if (!controller_nh_ptr_->getParam("controller_type", controller_type)){
      ROS_ERROR("Could not load controller type. Default: PD+");
    }
    /*
    // Obtain inertia,damping and stiffness values
    double Md_default, Dd_default, Kd_default = 0.0;
    if (!controller_nh_ptr_->getParam("Md", Md_default)){
      ROS_ERROR("Could not load proportional gain. Default value Md=0");
    }
    if (!controller_nh_ptr_->getParam("Dd", Dd_default)){
      ROS_ERROR("Could not load derivative gain. Default value Dd=0");
    }
    if (!controller_nh_ptr_->getParam("Kd", Kd_default)){
      ROS_ERROR("Could not load derivative gain. Default value Kd=0");
    }
    */

    // Obtain required controller type. Default: PD_Gravity_Compensation
    if (!controller_nh_ptr_->getParam("controller_type", controller_type)){
      ROS_ERROR("Could not load controller type. Default: PD+");
    }    

    // Friction gain control
    double F_default = 0.0;

    // Init ddynamic_reconfigure to tune gains and set default values
    ddr.reset(new ddynamic_reconfigure::DDynamicReconfigure(controller_nh));

    // If it is a Cartesian controller, change matrix gain to a cartesian one
    if(controller_type.compare("Cartesian_CT") == 0 or controller_type.compare("Optimal") == 0)
    {
      // Resize gain matrixs
      Kp.resize(6,6);
      Kp = Eigen::MatrixXd::Zero(6,6);
      Kv.resize(6,6);
      Kv = Eigen::MatrixXd::Zero(6,6);

      for(int i = 0; i < 6; i++)
      {
        Kp_vec[i] = kp_default[i];
        Kv_vec[i] = kv_default[i];
        ddr->RegisterVariable(&Kp_vec[i], controller_nh_ptr_->getNamespace() + "/Kp/" + std::to_string(i), 0, 6000);
        ddr->RegisterVariable(&Kv_vec[i], controller_nh_ptr_->getNamespace() + "/Kv/" + std::to_string(i), 0, 600);
      }
    }
    /*else if(controller_type.compare("Optimal_Force")==0)
    {
      // Resize matrix's inertia, damping, stiffness
      Md.resize(6,6);
      Md = Eigen::MatrixXd::Zero(6,6);
      Dd.resize(6,6);
      Dd = Eigen::MatrixXd::Zero(6,6);
      Kd.resize(6,6);
      Kd = Eigen::MatrixXd::Zero(6,6);

      for(int i = 0; i < 6; i++)
      {      
        Md_vec[i] = Md_default;
        Dd_vec[i] = Dd_default;
        Kd_vec[i] = Kd_default;
        ddr->RegisterVariable(&Md_vec[i], controller_nh_ptr_->getNamespace() + "/Md/" + std::to_string(i), 0, 600);
        ddr->RegisterVariable(&Dd_vec[i], controller_nh_ptr_->getNamespace() + "/Dd/" + std::to_string(i), 0, 600);
        ddr->RegisterVariable(&Kd_vec[i], controller_nh_ptr_->getNamespace() + "/Kd/" + std::to_string(i), 0, 600);
      }
    }*/
    else
    {
      for(int i=0; i<joint_handles_ptr_->size();i++)
      {
        Kp_vec[i] = kp_default[i];
        Kv_vec[i] = kv_default[i];
        F_vec[i] = F_default;
        ddr->RegisterVariable(&Kp_vec[i], controller_nh_ptr_->getNamespace() + "/Kp/" + joint_names_[i], 0, 6000);
        ddr->RegisterVariable(&Kv_vec[i], controller_nh_ptr_->getNamespace() + "/Kv/" + joint_names_[i], 0, 600);
        ddr->RegisterVariable(&F_vec[i], controller_nh_ptr_->getNamespace() + "/Friction/" + joint_names_[i], -10, 10);
      }
    }

    // Initializa dynamic reconfigure
    ddr->publishServicesTopics();

    // Obtain motor parameters from parameter server
    // Read the actuator parameters from param server
    for(int i = 0; i < joint_handles_ptr_->size(); i++)
    {
      if (!controller_nh_ptr_->getParam("/motor_params/" + joint_names_[i] + "/motor_torque_constant", motor_torque_constant[i]))
      {
        ROS_ERROR_STREAM("Could not find motor torque constant for joint " << joint_names_[i]);
        return false;
      }
      if (!controller_nh_ptr_->getParam("/motor_params/" + joint_names_[i] + "/reduction_ratio", reduction_ratio[i]))
      {
        ROS_ERROR_STREAM("Could not find reduction ratio for joint " << joint_names_[i]);
        return false;
      }
    }

    // Obtain KDL Tree
    urdf::Model talos_model;
    std::string paramName = "/robot_description";
    if (!talos_model.initParam(paramName)){
      ROS_ERROR("Failed to parse urdf robot model");
      return false;
    }

    if (!kdl_parser::treeFromUrdfModel(talos_model, talos_kdl)){
      ROS_ERROR("Failed to construct kdl tree");
      return false;
    }

    // Obtain kinematic chain corresponding to TALOS arm
    talos_kdl.getChain(link_names_[0],link_names_[1],chain);

    // Create publishers
    error_pub = controller_nh_ptr_->advertise<std_msgs::Float64MultiArray>("position_error",1000);
    torque_pub = controller_nh_ptr_->advertise<std_msgs::Float64MultiArray>("torques",1000);

    for(unsigned int i=0;i<joint_handles_ptr_->size();i++){
      xi1(i)=0;
      xi2(i)=0;
    }

    return true;
  }

  void starting(const ros::Time& /*time*/)
  {
    if (!joint_handles_ptr_) {return;}

    //Zero effort commands
    for (unsigned int i = 0; i < joint_handles_ptr_->size(); ++i)
    {
      (*joint_handles_ptr_)[i].setCommand(0.0);
    }
  }

  void stopping(const ros::Time& /*time*/) {
    //Zero effort commands
    for (unsigned int i = 0; i < joint_handles_ptr_->size(); ++i)
    {
      (*joint_handles_ptr_)[i].setCommand(0.0);
    }
  }

  void updateCommand(const ros::Time&     /*time*/,
                     const ros::Duration& period,
                     const State&         desired_state,
                     const State&         state_error)
  {
    const unsigned int n_joints = joint_handles_ptr_->size();

    // Preconditions
    if (!joint_handles_ptr_) {return;}
    assert(n_joints == state_error.position.size());
    assert(n_joints == state_error.velocity.size());

    //Obtain current position and velocities, desired state and state errors and store it at KDL::JntArray variables
    for(unsigned int i=0;i<n_joints;i++){
      current.q(i) = (*joint_handles_ptr_)[i].getPosition();
      current.qdot(i) = (*joint_handles_ptr_)[i].getVelocity();
      current_torque[i] = (*joint_handles_ptr_)[i].getEffort();

      desired.q(i) = desired_state.position[i];
      desired.qdot(i) = desired_state.velocity[i];
      desired.qdotdot(i) = desired_state.acceleration[i];   

      error.q(i) = state_error.position[i];
      error.qdot(i) = state_error.velocity[i];
    }    
    if(controller_type.compare("Cartesian_CT") == 0 or controller_type.compare("Optimal") == 0){
      for(unsigned int i=0;i<6;i++){
        Kp(i,i) = Kp_vec[i];
        Kv(i,i) = Kv_vec[i];
        F(i,i) = F_vec[i];
        
        //Md(i,i) = Md_vec[i];
        //Dd(i,i) = Dd_vec[i];
        //Kd(i,i) = Kd_vec[i];
      }
    }
    else
    {
      for(unsigned int i=0;i<n_joints;i++){
        Kp(i,i) = Kp_vec[i];
        Kv(i,i) = Kv_vec[i];
        F(i,i) = F_vec[i];
        lambda(i,i) = lambda_value;

        //Md(i,i) = Md_vec[i];
        //Dd(i,i) = Dd_vec[i];
        //Kd(i,i) = Kd_vec[i];
      }
    }


    // KDL object for calculate dynamic parameters
    KDL::ChainDynParam dynamics = KDL::ChainDynParam(chain, KDL::Vector(0.0,0.0,-9.81));
    
    /* ----------  CONTROLLER SELECTION ---------------- */

    if(controller_type.compare("Feedforward")==0)
    {
      dynamics.JntToGravity(desired.q,G);
      dynamics.JntToCoriolis(desired.q,desired.qdot,C);
      dynamics.JntToMass(desired.q,M);

      // Obtain torque needed for each joint
      tau.data = M.data*desired.qdotdot.data + C.data + G.data - F * current.qdot.data;
      
      for (unsigned int i = 0; i < n_joints; ++i)
      {
        // Effort command sending
        const double command = tau(i)/(motor_torque_constant[i] * reduction_ratio[i]);
        if(!std::isnan(command))
          (*joint_handles_ptr_)[i].setCommand(command);
      }
    }
    else if(controller_type.compare("PD_Feedforward")==0)
    {
      dynamics.JntToGravity(desired.q,G);
      dynamics.JntToCoriolis(desired.q,desired.qdot,C);
      dynamics.JntToMass(desired.q,M);

      // Obtain torque needed for each joint
      tau.data = Kp*error.q.data + Kv*error.qdot.data + M.data*desired.qdotdot.data + C.data + G.data - F * current.qdot.data;
      for (unsigned int i = 0; i < n_joints; ++i)
      {
        // Effort command sending
        const double command = tau(i)/(motor_torque_constant[i] * reduction_ratio[i]);
        if(!std::isnan(command))
          (*joint_handles_ptr_)[i].setCommand(command);
      }
    }
    else if(controller_type.compare("PD+")==0)
    {
      dynamics.JntToGravity(current.q,G);
      dynamics.JntToCoriolis(current.q,current.qdot,C);
      dynamics.JntToMass(current.q,M);

      // Obtain torque needed for each joint
      tau.data = Kp * error.q.data +  Kv * error.qdot.data + M.data*desired.qdotdot.data + C.data + G.data - F * current.qdot.data;
      
      for (unsigned int i = 0; i < n_joints; ++i)
      {
        // Effort command sending
        const double command = tau(i)/(motor_torque_constant[i] * reduction_ratio[i]);
        if(!std::isnan(command))
          (*joint_handles_ptr_)[i].setCommand(command);
      }
    }
    else if(controller_type.compare("Computed_torque")==0)
    {
      dynamics.JntToGravity(current.q,G);
      dynamics.JntToCoriolis(current.q,current.qdot,C);
      dynamics.JntToMass(current.q,M);
      

      tau.data = M.data*(desired.qdotdot.data + Kp*error.q.data + Kv*error.qdot.data) + C.data + G.data - F * current.qdot.data;
      for (unsigned int i = 0; i < n_joints; ++i)
      {
        // Effort command sending
        const double command = tau(i)/(motor_torque_constant[i] * reduction_ratio[i]);
        if(!std::isnan(command))
          (*joint_handles_ptr_)[i].setCommand(command);
      }

    }
/*
    else if(controller_type.compare("Computed_torque+")==0)
    {
      dynamics.JntToGravity(current.q,G);
      dynamics.JntToCoriolis(current.q,current.qdot,C);
      dynamics.JntToMass(current.q,M);

      xi1 = - lambda*xi1 + Kp*error.q.data + Kv*error.qdot.data;
      xi2 = - lambda*xi2 + lambda*error.qdot.data;
      v.data = -xi1 - xi2 - error.qdot.data;

      dynamics.JntToCoriolis(current.q,v,Cv);
      std::cout << Cv.data << std::endl;

      tau.data = M.data*(desired.qdotdot.data + Kp*error.q.data + Kv*error.qdot.data) + C.data - Cv.data + G.data - F * current.qdot.data;

      for (unsigned int i = 0; i < n_joints; ++i)
      {
        // Effort command sending
        const double command = tau(i)/(motor_torque_constant[i] * reduction_ratio[i]);
        if(!std::isnan(command))
          (*joint_handles_ptr_)[i].setCommand(command);
      }

    }
*/
    else if(controller_type.compare("Cartesian_CT")==0)
    {
      dynamics.JntToGravity(current.q,G);
      dynamics.JntToCoriolis(current.q,current.qdot,C);
      dynamics.JntToMass(current.q,M);

      // Add extra gains
      for(int i = n_joints; i < 6; i++)
      {
        Kp(i,i) = Kp_vec[i];
        Kv(i,i) = Kv_vec[i];
      }

      // KDL object for computing forward kinematics and obtain end-effector position, velocity and acceleration
      KDL::ChainFkSolverPos_recursive fk_solver = KDL::ChainFkSolverPos_recursive(chain);

      // Compute forward kinematics for current and desired states
      fk_solver.JntToCart(current.q, current_cart);
      fk_solver.JntToCart(desired.q, desired_cart);

      // Compute jacobians
      // KDL object for obtaining jacobian matrix
      KDL::ChainJntToJacSolver jacob_solver = KDL::ChainJntToJacSolver(chain);
      J_prev = J;
      Jdes_prev = Jdes;
      jacob_solver.JntToJac(current.q,J);
      jacob_solver.JntToJac(desired.q,Jdes);

      // Obtain J derivative and pseudoinverse
      Jdot.data = J.data - J_prev.data; // J difference between time steps
      Jdesdot.data = Jdes.data - Jdes_prev.data; // J difference between time steps
    
      J_pinv = J.data.transpose() * (J.data * J.data.transpose()).inverse(); // Compute pseudo-inverse as J+ = Jt*(J*Jt)^-1

      //std::cout << "Jacob_pinv" << std::endl;
      //std::cout << J_pinv << std::endl;

      // Compute velocity
      current_vel = J.data * current.qdot.data;
      desired_vel = Jdes.data * desired.qdot.data;
      desired_acc = Jdesdot.data * desired.qdot.data + Jdes.data * desired.qdotdot.data;


      /* -------- COMPUTE CARTESIAN ERROR -------------*/

      // Position error
      error_cart.p = desired_cart.p - current_cart.p;

      // Orientation error
      double w, x, y, z, wd, xd, yd, zd = 0.0;
      // Desired orientation
      desired_cart.M.GetQuaternion(xd, yd, zd, wd);
      Eigen::Quaterniond desired_orientation = Eigen::Quaterniond(wd, xd, yd, zd);
      // Current orientation
      current_cart.M.GetQuaternion(x, y, z, w);
      Eigen::Quaterniond current_orientation = Eigen::Quaterniond(w, x, y, z);
      // Orientation error
      Eigen::Quaterniond error_orientation = desired_orientation * (current_orientation.inverse());
      error_orientation.normalize();
      
      // Store position error in an Eigen::Vector
      pos_error(0) = error_cart.p.x();
      pos_error(1) = error_cart.p.y();
      pos_error(2) = error_cart.p.z();
      pos_error(3) = error_orientation.x() * error_orientation.w();
      pos_error(4) = error_orientation.y() * error_orientation.w();
      pos_error(5) = error_orientation.z() * error_orientation.w();

      // Velocity error
      vel_error = desired_vel - current_vel;

      // EFFORT COMMAND CALCULUS
      tau.data = M.data * J_pinv * (desired_acc + Kp * pos_error + Kv * vel_error - Jdot.data * current.qdot.data) + C.data + G.data - F * current.qdot.data;

      // Send each effort command to robot joints
      for (unsigned int i = 0; i < n_joints; ++i)
      {
        // Effort command sending
        const double command = tau(i)/(motor_torque_constant[i] * reduction_ratio[i]);
        if(!std::isnan(command))
          (*joint_handles_ptr_)[i].setCommand(command);
      }

      // PUBLISH ERROR AND TORQUE FOR CARTESIAN CONTROLLER
      std_msgs::Float64MultiArray error_msg, torque_msg;
      error_msg.data.resize(3);
      torque_msg.data.resize(4);

      for(int i=0;i<7;i++)
      {
        if(i<3)
          error_msg.data[i] = error_cart.p.data[i];

        torque_msg.data[i] = current_torque[i] * (motor_torque_constant[i] * reduction_ratio[i]);
      }

      error_pub.publish(error_msg);
      torque_pub.publish(torque_msg);

      ros::spinOnce();   

      return;   

    }
    else if(controller_type.compare("Optimal")==0)
    {
      dynamics.JntToGravity(current.q,G);
      dynamics.JntToCoriolis(current.q,current.qdot,C);
      dynamics.JntToMass(current.q,M);

      // Add extra gains
      for(int i = n_joints; i < 6; i++)
      {
        Kp(i,i) = Kp_vec[i];
        Kv(i,i) = Kv_vec[i];
      }

      // KDL object for computing forward kinematics and obtain end-effector position, velocity and acceleration
      KDL::ChainFkSolverPos_recursive fk_solver = KDL::ChainFkSolverPos_recursive(chain);

      // Compute forward kinematics for current and desired states
      fk_solver.JntToCart(current.q, current_cart);
      fk_solver.JntToCart(desired.q, desired_cart);

      // Compute jacobiansº
      KDL::ChainJntToJacSolver jacob_solver = KDL::ChainJntToJacSolver(chain);
      J_prev = J;
      jacob_solver.JntToJac(current.q,J);

      // Obtain J derivative and pseudoinverse
      Jdot.data = J.data - J_prev.data; // J difference between time steps
      J_pinv = J.data.transpose();// * (J.data * J.data.transpose()).inverse(); // Compute pseudo-inverse as J+ = Jt*(J*Jt)^-1

      // Compute velocity
      current_vel = J.data * current.qdot.data;
      desired_vel = J.data * desired.qdot.data;
      desired_acc = Jdot.data * desired.qdot.data + J.data * desired.qdotdot.data;

      /* -------- COMPUTE CARTESIAN ERROR -------------*/

      // Position error
      error_cart.p = desired_cart.p - current_cart.p;

      // Orientation error
      double w, x, y, z, wd, xd, yd, zd = 0.0;
      // Desired orientation
      desired_cart.M.GetQuaternion(xd, yd, zd, wd);
      Eigen::Quaterniond desired_orientation = Eigen::Quaterniond(wd, xd, yd, zd);
      // Current orientation
      current_cart.M.GetQuaternion(x, y, z, w);
      Eigen::Quaterniond current_orientation = Eigen::Quaterniond(w, x, y, z);
      // Orientation error
      Eigen::Quaterniond error_orientation = desired_orientation * (current_orientation.inverse());
      error_orientation.normalize();
     
      // Store position error in an Eigen::Vector
      pos_error(0) = error_cart.p.x();
      pos_error(1) = error_cart.p.y();
      pos_error(2) = error_cart.p.z();
      pos_error(3) = error_orientation.x() * error_orientation.w();
      pos_error(4) = error_orientation.y() * error_orientation.w();
      pos_error(5) = error_orientation.z() * error_orientation.w();

      // Velocity error
      vel_error = desired_vel - current_vel;
      
      // Optimal controller terms
      Eigen::VectorXd D = - C.data - G.data;
      Eigen::MatrixXd A = J.data;
      Eigen::VectorXd b = desired_acc + Kv*vel_error + Kp*pos_error - Jdot.data * current.qdot.data;
      Eigen::MatrixXd M_inv = M.data.inverse();
      
      // WEIGHT MATRIX:  This is the key term in optimal control. The optimal controller effect will depend on this value
      //Eigen::MatrixXd W = Eigen::MatrixXd::Identity(7,7);
      Eigen::MatrixXd W = M_inv;
      //Eigen::MatrixXd W = (M.data * M.data).inverse();
      /*Eigen::MatrixXd W = Eigen::MatrixXd::Zero(7,7);
      W.diagonal() << 1.0, 3.0, 0.5, 1.0, 1.0, 1.0, 1.0;//0.025, 0.025, 0.0455, 0.0455, 0.333, 0.2, 0.2;

      W = W * M_inv;*/

      Eigen::MatrixXd W_inv_sqrt = W.sqrt().inverse();

      // Control law
      tau.data = W_inv_sqrt * (A * M_inv * W_inv_sqrt).transpose() * (b - (A * M_inv * D));
      for (unsigned int i = 0; i < 4; ++i)
      {
        // Effort command sending
        const double command = tau(i)/(motor_torque_constant[i] * reduction_ratio[i]);
        if(!std::isnan(command))
          (*joint_handles_ptr_)[i].setCommand(command);
      }

      // PUBLISH ERROR AND TORQUE FOR CARTESIAN CONTROLLER
      std_msgs::Float64MultiArray error_msg, torque_msg;
      error_msg.data.resize(3);
      torque_msg.data.resize(4);

      for(int i=0;i<4;i++)
      {
        if(i<3)
          error_msg.data[i] = error_cart.p.data[i];

        torque_msg.data[i] = current_torque[i] * (motor_torque_constant[i] * reduction_ratio[i]);
      }

      error_pub.publish(error_msg);
      torque_pub.publish(torque_msg);

      ros::spinOnce();   

      return;
    }
    /*
    else if(controller_type.compare("Optimal_Force")==0)
    {
      dynamics.JntToGravity(current.q,G);
      dynamics.JntToCoriolis(current.q,current.qdot,C);
      dynamics.JntToMass(current.q,M);
      ROS_ERROR("start controller");
      // Add extra gains
      for(int i = n_joints; i < 6; i++)
      {
        Md(i,i) = Md_vec[i];
        Dd(i,i) = Dd_vec[i];
        Kd(i,i) = Kd_vec[i];
      }

      // KDL object for computing forward kinematics and obtain end-effector position, velocity and acceleration
      KDL::ChainFkSolverPos_recursive fk_solver = KDL::ChainFkSolverPos_recursive(chain);

      // Compute forward kinematics for current and desired states
      fk_solver.JntToCart(current.q, current_cart);
      fk_solver.JntToCart(desired.q, desired_cart);

      // Compute jacobians
      // KDL object for obtaining jacobian matrix
      KDL::ChainJntToJacSolver jacob_solver = KDL::ChainJntToJacSolver(chain);
      J_prev = J;
      jacob_solver.JntToJac(current.q,J);

      // Obtain J derivative and pseudoinverse
      Jdot.data = J.data - J_prev.data; // J difference between time steps
      // ROS_ERROR("J_TRANS_PINV start");
      // J_trans_pinv = (J.data.transpose() * J.data.transpose().transpose()).inverse() * J.data.transpose().transpose();  * J.data; Compute transpose pseudo-inverse Jt+ = (Jt*Jtt)⁻1 * Jtt
      // ROS_ERROR("J_TRANS_PINV done");
      // Compute velocity
      current_vel = J.data * current.qdot.data;
      desired_vel = J.data * desired.qdot.data;
      desired_acc = Jdot.data * desired.qdot.data + J.data * desired.qdotdot.data;


      // -------- COMPUTE CARTESIAN ERROR -------------//

      // Position error
      error_cart.p = desired_cart.p - current_cart.p;

      // Orientation error
      double w, x, y, z, wd, xd, yd, zd = 0.0;
      // Desired orientation
      desired_cart.M.GetQuaternion(xd, yd, zd, wd);
      Eigen::Quaterniond desired_orientation = Eigen::Quaterniond(wd, xd, yd, zd);
      // Current orientation
      current_cart.M.GetQuaternion(x, y, z, w);
      Eigen::Quaterniond current_orientation = Eigen::Quaterniond(w, x, y, z);
      // Orientation error
      Eigen::Quaterniond error_orientation = desired_orientation * (current_orientation.inverse());
      error_orientation.normalize();
      
      // Store position error in an Eigen::Vector
      pos_error(0) = error_cart.p.x();
      pos_error(1) = error_cart.p.y();
      pos_error(2) = error_cart.p.z();
      pos_error(3) = error_orientation.x() * error_orientation.w();
      pos_error(4) = error_orientation.y() * error_orientation.w();
      pos_error(5) = error_orientation.z() * error_orientation.w();

      // Velocity error
      vel_error = desired_vel - current_vel;

      //External Torque

      Fc = current_torque - M.data*desired.qdotdot.data + C.data + G.data - F * current.qdot.data; //TODO tipo de variables
      ROS_ERROR("FC done");
      std::cout << "Fc: " << Fc << std::endl;
      std::cout << "Md*desired_acc: " << Md*desired_acc << std::endl;
      std::cout << "Dd*vel_error: " << Dd*vel_error << std::endl;
      std::cout << "Kd*pos_error: " << Kd*pos_error << std::endl;
      std::cout << "current.qdot.data: " << Md*Jdot.data * current.qdot.data << std::endl;

      // Optimal controller terms
      Eigen::VectorXd D = - C.data - G.data;
      Eigen::MatrixXd A = Md * J.data;
      Eigen::VectorXd b = Fc - Md*desired_acc + Dd*vel_error + Kd*pos_error - Md*Jdot.data * current.qdot.data;
      Eigen::MatrixXd M_inv = M.data.inverse();
      
      // WEIGHT MATRIX:  This is the key term in optimal control. The optimal controller effect will depend on this value
      //Eigen::MatrixXd W = Eigen::MatrixXd::Identity(7,7);
      Eigen::MatrixXd W = M_inv;
      //Eigen::MatrixXd W = (M.data * M.data).inverse();
      //Eigen::MatrixXd W = Eigen::MatrixXd::Zero(7,7);
      //W.diagonal() << 1.0, 3.0, 0.5, 1.0, 1.0, 1.0, 1.0;0.025, 0.025, 0.0455, 0.0455, 0.333, 0.2, 0.2;
      //W = W * M_inv;

      Eigen::MatrixXd W_inv_sqrt = W.sqrt().inverse();

      // Control law
      tau.data = W_inv_sqrt * (A * M_inv * W_inv_sqrt).transpose() * (b - (A * M_inv * D)) - F * current.qdot.data;

      for (unsigned int i = 0; i < 4; ++i)
      {
        // Effort command sending
        const double command = tau(i)/(motor_torque_constant[i] * reduction_ratio[i]);
        if(!std::isnan(command))
          (*joint_handles_ptr_)[i].setCommand(command);
      }
      
      // PUBLISH ERROR AND TORQUE FOR CARTESIAN CONTROLLER
      std_msgs::Float64MultiArray error_msg, torque_msg;
      error_msg.data.resize(3);
      torque_msg.data.resize(4);

      for(int i=0;i<4;i++)
      {
        if(i<3)
          error_msg.data[i] = error_cart.p.data[i];

        torque_msg.data[i] = current_torque[i] * (motor_torque_constant[i] * reduction_ratio[i]);
      }

      error_pub.publish(error_msg);
      torque_pub.publish(torque_msg);

      ros::spinOnce();   

      return;
    }*/
    else
      ROS_ERROR("Invalid controller type for effort_controllers/DirectDynamicController");

    // PUBLISH ERROR AND TORQUE FOR JOINT CONTROLLERS
    std_msgs::Float64MultiArray error_msg, torque_msg;
    error_msg.data.resize(JOINTS);
    torque_msg.data.resize(JOINTS);

    for(int i=0;i<JOINTS;i++)
    {
      error_msg.data[i] = error.q(i);
      torque_msg.data[i] = current_torque[i] * (motor_torque_constant[i] * reduction_ratio[i]);
    }

    error_pub.publish(error_msg);
    torque_pub.publish(torque_msg);

    ros::spinOnce();     
  }

private:
  // ROS Control variables
  std::vector<hardware_interface::JointHandle>* joint_handles_ptr_;
  ros::NodeHandle* controller_nh_ptr_;
  ros::NodeHandle n;
  std::vector<std::string> joint_names_;
  std::vector<std::string> link_names_;
  std::string controller_type="PD+";
  ros::Publisher error_pub;
  ros::Publisher torque_pub;

  static const int JOINTS = 7;

  //Gains - to be updated via rosparam and ddynamic_reconfigure
  ddynamic_reconfigure::DDynamicReconfigurePtr ddr;
  double Kp_vec[JOINTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double Kv_vec[JOINTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Eigen::MatrixXd Kp = Eigen::MatrixXd::Zero(JOINTS,JOINTS);
  Eigen::MatrixXd Kv = Eigen::MatrixXd::Zero(JOINTS,JOINTS);

  //Gains for de optimal force control
  double Md_vec[JOINTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double Dd_vec[JOINTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double Kd_vec[JOINTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Eigen::MatrixXd Md = Eigen::MatrixXd::Zero(JOINTS,JOINTS);
  Eigen::MatrixXd Dd = Eigen::MatrixXd::Zero(JOINTS,JOINTS);
  Eigen::MatrixXd Kd = Eigen::MatrixXd::Zero(JOINTS,JOINTS);
  Eigen::VectorXd Fc = Eigen::VectorXd::Zero(JOINTS);

  // Friction compensation
  double F_vec[JOINTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Eigen::MatrixXd F = Eigen::MatrixXd::Zero(JOINTS, JOINTS);

  // Motor parameters
  double motor_torque_constant[JOINTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double reduction_ratio[JOINTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  // KDL parameters obtained from robot URDF file
  KDL::Tree talos_kdl;
  KDL::Chain chain;

  // Current state
  KDL::JntArrayAcc current = KDL::JntArrayAcc(JOINTS);
  KDL::Frame current_cart = KDL::Frame();
  Eigen::VectorXd current_vel = Eigen::VectorXd::Zero(6);
  Eigen::VectorXd current_torque = Eigen::VectorXd::Zero(JOINTS); 

  // Error
  KDL::JntArrayAcc error = KDL::JntArrayAcc(JOINTS);
  KDL::Frame error_cart = KDL::Frame();
  Eigen::VectorXd pos_error = Eigen::VectorXd::Zero(6); 
  Eigen::VectorXd vel_error = Eigen::VectorXd::Zero(6);

  //xi
  Eigen::VectorXd xi1 = Eigen::VectorXd::Zero(JOINTS); 
  Eigen::VectorXd xi2 = Eigen::VectorXd::Zero(JOINTS);
  KDL::JntArray v = KDL::JntArray(JOINTS);
  Eigen::MatrixXd lambda = Eigen::MatrixXd::Zero(JOINTS,JOINTS);
  double lambda_value = 0.0;
  
  // Desired state
  KDL::JntArrayAcc desired = KDL::JntArrayAcc(JOINTS);
  KDL::Frame desired_cart = KDL::Frame();
  Eigen::VectorXd desired_vel = Eigen::VectorXd::Zero(6); 
  Eigen::VectorXd desired_acc = Eigen::VectorXd::Zero(6);

  // Jacobian
  KDL::Jacobian J = KDL::Jacobian(JOINTS);
  KDL::Jacobian Jdes = KDL::Jacobian(JOINTS);
  KDL::Jacobian J_prev = KDL::Jacobian(JOINTS);
  KDL::Jacobian Jdes_prev = KDL::Jacobian(JOINTS);
  KDL::Jacobian Jdot = KDL::Jacobian(JOINTS);
  KDL::Jacobian Jdesdot = KDL::Jacobian(JOINTS);
  Eigen::MatrixXd J_pinv = Eigen::MatrixXd::Zero(JOINTS,6);
  //Eigen::MatrixXd J_trans_pinv = Eigen::MatrixXd::Zero(6,JOINTS);


  // KDL-obtained dynamic params
  KDL::JntSpaceInertiaMatrix M = KDL::JntSpaceInertiaMatrix(JOINTS);
  KDL::JntArray C = KDL::JntArray(JOINTS);
  KDL::JntArray Cv = KDL::JntArray(JOINTS);
  KDL::JntArray G = KDL::JntArray(JOINTS);

  // Calculated torque
  KDL::JntArray tau = KDL::JntArray(JOINTS);
};

#endif
