#ifndef CARTESIAN_CONTROLLER_HPP_INCLUDED
#define CARTESIAN_CONTROLLER_HPP_INCLUDED

// PROJECT
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

    if (!kdl_parser::treeFromUrdfModel(robot_model,robot_tree_))
    {

        const std::string error = ""
        "Failed to parse KDL tree from urdf model";
        ROS_ERROR_STREAM(error);
        throw std::runtime_error(error);
    }

    if (!robot_tree_.getChain(base_link,end_effector_link,robot_chain_)){

        const std::string error = ""
        "Failed to parse robot chain from urdf model. "
        "Are you sure that both your 'base_link' and 'end_effector_link' exist?";
        ROS_ERROR_STREAM(error);
        throw std::runtime_error(error);
    }
    // Chain built ----------------------------------------------------------------

    // Get Joints specific names and its handles ----------------------------------
    if (!nh.getParam("joints",joint_names_)){
        const std::string error = ""
        "Failed to load " + nh.getNamespace() + "/joints" + " from parameter server";
        ROS_ERROR_STREAM(error);
        throw std::runtime_error(error);
    }

    for (size_t i = 0; i < joint_names_.size(); ++i)
    {
        joint_handles_.push_back(hw->getHandle(joint_names_[i]));
    }
    // Joints Configured -----------------------------------------------------------

    // Initialize solvers ----------------------------------------------------------
    KDL::Chain kdl_chain;
    // To remove two joints of the torso but the base_link is still in the 0,0,0
    for(size_t i = 0; i < robot_chain_.getNrOfSegments(); i++){
        if(i != 1 && i != 2) kdl_chain.addSegment(robot_chain_.getSegment(i));
    }

    // kdl_chain.addChain(robot_chain_);
    jnt_to_pose_solver_.reset(new KDL::ChainFkSolverPos_recursive(kdl_chain));
    jnt_to_jac_solver_.reset(new KDL::ChainJntToJacSolver(kdl_chain));
    // -----------------------------------------------------------------------------

    // Resizes the joint state vectors in non-realtime -----------------------------
    jnt_pos_.resize(kdl_chain.getNrOfJoints());
    jnt_effort_.resize(kdl_chain.getNrOfJoints());
    jacobian_.resize(kdl_chain.getNrOfJoints());

    // Set the desired pose --------------------------------------------------------
    // El punto KDL::Rotation::RPY(0,0,3.14), KDL::Vector(0.5, -0.2, 0.2) funciona
    // El punto KDL::Rotation::RPY(0,0,3.14), KDL::Vector(0.5, -0.2, -0.2) funciona
    // target_frame_ = KDL::Frame(KDL::Rotation::RPY(0,0,3.14), KDL::Vector(0.4, -0.1, 0.2));
    // -----------------------------------------------------------------------------

    // ROS_INFO("Cadena cinematica incializada correctamente ...");
    // ROS_INFO("Handles Size: %i", joint_handles_.size());
    // ROS_INFO("Names Size: %i", joint_names_.size());
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
    Gazebo_models_subscr_ = nh.subscribe("/gazebo/model_states", 3, &cartesian_controller_class::transformationsCallback, this);

    return true;

}

void cartesian_controller_class::update(const ros::Time &time, const ros::Duration &period){

    //Get initial joints position
    for(unsigned int i = 0; i < joint_handles_.size(); i++){
        jnt_pos_(i) = joint_handles_[i].getPosition();
    }

    KDL::Frame current_pose;
    ik_status = jnt_to_pose_solver_->JntToCart(jnt_pos_,current_pose);
    if (ik_status == -1) 
        ROS_ERROR_STREAM("No se ha podido calcular la cinematica directa ... ");

    // Descomentar para imprimir por pantalla la posición del extremo

    // ROS_INFO("Antes de entrar");
    // ROS_INFO("x : %f",current_pose.p.x());
    // ROS_INFO("y : %f",current_pose.p.y());
    // ROS_INFO("z : %f",current_pose.p.z());

    calculate_transformations(current_pose);

    // ROS_INFO("Despues de salir");
    // ROS_INFO("x : %f",current_pose.p.x());
    // ROS_INFO("y : %f",current_pose.p.y());
    // ROS_INFO("z : %f",current_pose.p.z());
    // Target frame is already with ISS reference
    
    // get the pose error
    KDL::Twist error;

    error = KDL::diff(current_pose, target_frame_);

    jnt_to_jac_solver_->JntToJac(jnt_pos_, jacobian_);

    // jnt_effort_ = Jac^transpose * cart_wrench
    for (unsigned int i = 0; i < jnt_pos_.rows(); i++)
    {
        jnt_effort_(i) = 0;
        for (unsigned int j=0; j<6; j++){
            jnt_effort_(i) += (jacobian_(j,i) * 125 * error(j));
        }
    }

    writeJointCommand(jnt_effort_);

}

void cartesian_controller_class::writeJointCommand(KDL::JntArray joint_command){

    for(size_t i = 0; i < joint_handles_.size(); i++){
        joint_handles_[i].setCommand(joint_command(i));
    }
    
}

void cartesian_controller_class::starting(const ros::Time &time) {
    
    //Get initial joints position
    for(unsigned int i = 0; i < joint_handles_.size(); i++){
        jnt_pos_(i) = joint_handles_[i].getPosition();
    }

    KDL::Frame current_pose;
    ik_status = jnt_to_pose_solver_->JntToCart(jnt_pos_,current_pose);
    if (ik_status == -1) 
        ROS_ERROR_STREAM("No se ha podido calcular la cinematica directa ... ");

    // ROS_INFO("Antes de entrar");
    // ROS_INFO("x : %f",current_pose.p.x());
    // ROS_INFO("y : %f",current_pose.p.y());
    // ROS_INFO("z : %f",current_pose.p.z());

    calculate_transformations(current_pose);

    // ROS_INFO("Despues de salir");
    // ROS_INFO("x : %f",current_pose.p.x());
    // ROS_INFO("y : %f",current_pose.p.y());
    // ROS_INFO("z : %f",current_pose.p.z());

    target_frame_ = current_pose;

    // ROS_INFO("Target Frame");
    // ROS_INFO("x : %f",target_frame_.p.x());
    // ROS_INFO("y : %f",target_frame_.p.y());
    // ROS_INFO("z : %f",target_frame_.p.z());

}

void cartesian_controller_class::stopping(const ros::Time &time) {}

void cartesian_controller_class::calculate_transformations(KDL::Frame &current_pose) {

    // To obtain Talos position with ISS reference
    KDL::Frame iss_2_Talos = world_2_ISS_.Inverse() * world_2_Talos_;

    // To obtain current_frame with ISS reference
    current_pose = iss_2_Talos * current_pose;

}

void cartesian_controller_class::targetFrameCallback(const astronaut_controllers::target_frame& target_frame){

    // The desired point is movig with the ISS
    float x = world_2_ISS_.p.x() + target_frame.x;
    float y = world_2_ISS_.p.y() + target_frame.y;
    float z = world_2_ISS_.p.z() + target_frame.z;
    double roll, pitch, yaw;
    world_2_ISS_.M.GetRPY(roll, pitch, yaw);
    roll += target_frame.roll;
    pitch += target_frame.pitch;
    yaw += target_frame.yaw + M_PI;

    target_frame_ = KDL::Frame(KDL::Rotation::RPY(roll, pitch, yaw), KDL::Vector(x, y, z));
}

void cartesian_controller_class::transformationsCallback(const gazebo_msgs::ModelStates& data){
    
    float x, y, z, q_x, q_y, q_z, q_w;

    for (size_t i = 0; i < data.name.size(); i++){

        x = data.pose[i].position.x;
        y = data.pose[i].position.y;
        z = data.pose[i].position.z;
        q_x = data.pose[i].orientation.x;
        q_y = data.pose[i].orientation.y;
        q_z = data.pose[i].orientation.z;
        q_w = data.pose[i].orientation.w;

        if(data.name[i] == "talos"){
            world_2_Talos_ = KDL::Frame(KDL::Rotation::Quaternion(q_x, q_y, q_z, q_w), KDL::Vector(x, y, z));
        }

        if(data.name[i] == "International Space Station"){
            world_2_ISS_ = KDL::Frame(KDL::Rotation::Quaternion(q_x, q_y, q_z, q_w), KDL::Vector(x, y, z));
        }

    }

} 
    
}; // namespace


#endif