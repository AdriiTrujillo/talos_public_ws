#ifndef CARTESIAN_CONTROLLER_HPP_INCLUDED
#define CARTESIAN_CONTROLLER_HPP_INCLUDED

//Project
#include <astronaut_controllers/cartesian_controller.h>

// KDL
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/jntarray.hpp>

// URDF
#include <urdf/model.h>

namespace controller_ns{

bool cartesian_controller_class::init(hardware_interface::EffortJointInterface* hw, ros::NodeHandle& nh){

    std::string robot_description;
    std::string base_link;
    std::string end_effector_link;
    urdf::Model robot_model;

    // Get specific configuration of the robot -------------------------------
    if (!nh.getParam("/robot_description",robot_description)){

        ROS_ERROR("Failed to load '/robot_description' from parameter server");
        return false;
    }
    if (!nh.getParam("base_link",base_link)){
        
        ROS_ERROR_STREAM("Failed to load " << nh.getNamespace() + "/base_link" << " from parameter server");
        return false;
    }
    if (!nh.getParam("end_effector_link",end_effector_link)){
    
        ROS_ERROR_STREAM("Failed to load " << nh.getNamespace() + "/end_effector_link" << " from parameter server");
        return false;
    }
    // Robot configuration done ----------------------------------------------


    // Build the kinematic chain ---------------------------------------------
    if (!robot_model.initString(robot_description))
    {

        ROS_ERROR("Failed to parse urdf model from 'robot_description'");
        return false;
    }

    if (!kdl_parser::treeFromUrdfModel(robot_model,_robot_tree))
    {

        const std::string error = ""
        "Failed to parse KDL tree from urdf model";
        ROS_ERROR_STREAM(error);
        throw std::runtime_error(error);
    }

    if (!_robot_tree.getChain(base_link,end_effector_link,_robot_chain)){

        const std::string error = ""
        "Failed to parse robot chain from urdf model. "
        "Are you sure that both your 'base_link' and 'end_effector_link' exist?";
        ROS_ERROR_STREAM(error);
        throw std::runtime_error(error);
    }
    // Chain built ----------------------------------------------------------------

    // Get Joints specific names and its handles ----------------------------------
    if (!nh.getParam("joints",_joint_names)){
        const std::string error = ""
        "Failed to load " + nh.getNamespace() + "/joints" + " from parameter server";
        ROS_ERROR_STREAM(error);
        throw std::runtime_error(error);
    }

    for (size_t i = 0; i < _joint_names.size(); ++i)
    {
        _joint_handles.push_back(hw->getHandle(_joint_names[i]));
    }
    // Joints Configured -----------------------------------------------------------

    // Initialize solvers ----------------------------------------------------------
    KDL::Chain kdl_chain;
    // To remove two joints of the torso but the base_link is still in the 0,0,0
    for(size_t i = 0; i < _robot_chain.getNrOfSegments(); i++){
        if(i != 1 && i != 2) kdl_chain.addSegment(_robot_chain.getSegment(i));
    }

    // kdl_chain.addChain(_robot_chain);
    _jnt_to_pose_solver.reset(new KDL::ChainFkSolverPos_recursive(kdl_chain));
    _jnt_to_jac_solver.reset(new KDL::ChainJntToJacSolver(kdl_chain));
    // -----------------------------------------------------------------------------

    // Resizes the joint state vectors in non-realtime -----------------------------
    _jnt_pos.resize(kdl_chain.getNrOfJoints());
    _jnt_effort.resize(kdl_chain.getNrOfJoints());
    _jacobian.resize(kdl_chain.getNrOfJoints());

    // Set the desired pose --------------------------------------------------------
    // El punto KDL::Rotation::RPY(0,0,3.14), KDL::Vector(0.5, -0.2, 0.2) funciona
    // El punto KDL::Rotation::RPY(0,0,3.14), KDL::Vector(0.5, -0.2, -0.2) funciona
    // target_frame_ = KDL::Frame(KDL::Rotation::RPY(0,0,3.14), KDL::Vector(0.4, -0.1, 0.2));
    // -----------------------------------------------------------------------------

    // ROS_INFO("Cadena cinematica incializada correctamente ...");
    // ROS_INFO("Handles Size: %i", _joint_handles.size());
    // ROS_INFO("Names Size: %i", _joint_names.size());
    // ROS_INFO("Number of Segments: %i", kdl_chain.getNrOfSegments());
    // ROS_INFO("Number of Joints: %i", kdl_chain.getNrOfJoints());

    // ROS_INFO("Number of Segments: %i", kdl_chain.getNrOfSegments());
    // ROS_INFO("Number of Joints: %i", kdl_chain.getNrOfJoints());
    // ROS_INFO("Cadena cinemática creada: ");
    // for(int i = 0; i < kdl_chain.getNrOfSegments(); i++){
    //     std::cout << "Segment : " << i << " --> " << kdl_chain.getSegment(i).getName() << std::endl;
    //     std::cout << "Segments' Joint name : " << kdl_chain.getSegment(i).getJoint().getName() << std::endl;
    //     std::cout << "Segments' Joint Type : " << kdl_chain.getSegment(i).getJoint().getTypeName() << std::endl;
    //     std::cout << " ------------------------- " << std::endl;
    // }

    target_frame_subscr_ = nh.subscribe("/cartesian_target_frame", 3, &cartesian_controller_class::targetFrameCallback, this);

    return true;

}

void cartesian_controller_class::update(const ros::Time &time, const ros::Duration &period){

    //Get initial joints position
    for(unsigned int i = 0; i < _joint_handles.size(); i++){
        _jnt_pos(i) = _joint_handles[i].getPosition();
    }

    KDL::Frame current_pose;
    ik_status = _jnt_to_pose_solver->JntToCart(_jnt_pos,current_pose);
    if (ik_status == -1) 
        ROS_ERROR_STREAM("No se ha podido calcular la cinematica directa ... ");

    // Descomentar para imprimir por pantalla la posición del extremo
    // ROS_INFO("x : %f",current_pose.p.x());
    // ROS_INFO("y : %f",current_pose.p.y());
    // ROS_INFO("z : %f",current_pose.p.z());
    
    // get the pose error
    KDL::Twist error;

    error = KDL::diff(current_pose, target_frame_);

    _jnt_to_jac_solver->JntToJac(_jnt_pos, _jacobian);

    // _jnt_effort = Jac^transpose * cart_wrench
    for (unsigned int i = 0; i < _jnt_pos.rows(); i++)
    {
        _jnt_effort(i) = 0;
        for (unsigned int j=0; j<6; j++){
            _jnt_effort(i) += (_jacobian(j,i) * 125.0 * error(j));
        }
    }

    writeJointCommand(_jnt_effort);

}

void cartesian_controller_class::writeJointCommand(KDL::JntArray joint_command){

    for(size_t i = 0; i < _joint_handles.size(); i++){
        _joint_handles[i].setCommand(joint_command(i));
    }
    
}

void cartesian_controller_class::starting(const ros::Time &time) {
    
    //Get initial joints position
    for(unsigned int i = 0; i < _joint_handles.size(); i++){
        _jnt_pos(i) = _joint_handles[i].getPosition();
    }

    KDL::Frame current_pose;
    ik_status = _jnt_to_pose_solver->JntToCart(_jnt_pos,current_pose);
    if (ik_status == -1) 
        ROS_ERROR_STREAM("No se ha podido calcular la cinematica directa ... ");


    target_frame_ = current_pose;

}

void cartesian_controller_class::stopping(const ros::Time &time) {}

void cartesian_controller_class::targetFrameCallback(const astronaut_controllers::target_frame& target_frame){
                                                                                                        //0.4, -0.1, 0.2
    target_frame_ = KDL::Frame(KDL::Rotation::RPY(target_frame.roll,target_frame.pitch,target_frame.yaw + M_PI), KDL::Vector(target_frame.x, target_frame.y, target_frame.z));

}
    
}; // namespace


#endif