#ifndef ARUCO_TRAJECTORY_CARTESIAN_CONTROLLER_HPP_INCLUDED
#define ARUCO_TRAJECTORY_CARTESIAN_CONTROLLER_HPP_INCLUDED

// PROJECT
#include <astronaut_controllers/aruco_trajectory_cartesian_controller.h>

// KDL
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/jntarray.hpp>

// URDF
#include <urdf/model.h>

namespace controller_ns{

bool aruco_trajectory_cartesian_controller_class::init(hardware_interface::EffortJointInterface* hw, ros::NodeHandle& nh){

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
    if (!nh.getParam("goal_tolerance",tolerance_)){
    
        ROS_ERROR_STREAM("Failed to load " << nh.getNamespace() + "/goal_tolerance" << " from parameter server");
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

    aruco_subscr_ = nh.subscribe("/aruco_single/pose", 10000, &aruco_trajectory_cartesian_controller_class::transformationCallback, this);
    tolerance_publisher_ = nh.advertise<std_msgs::Bool>("/goal_tolerance", 1000);

    return true;

}

void aruco_trajectory_cartesian_controller_class::update(const ros::Time &time, const ros::Duration &period){

    //Get initial joints position
    for(unsigned int i = 0; i < joint_handles_.size(); i++){
        jnt_pos_(i) = joint_handles_[i].getPosition();
    }

    KDL::Frame current_pose;
    fk_status = jnt_to_pose_solver_->JntToCart(jnt_pos_,current_pose);
    if (fk_status == -1) 
        ROS_ERROR_STREAM("No se ha podido calcular la cinematica directa ... ");

    // calculate_transformations(current_pose);
// -------------------------------------------------------------------------------------------    
    // Descomentar para imprimir por pantalla la posición del extremo
    // ROS_INFO("Current: ");
    // ROS_INFO("x : %f",current_pose.p.x());
    // ROS_INFO("y : %f",current_pose.p.y());
    // ROS_INFO("z : %f",current_pose.p.z());
// ------------------------------------------------------------------------------------------- 
    
    if(start_trajectory_){
        //Get the actual time
        actual_time_ = ros::Time::now() - begin_time_; // That's 0 sec
        now_ = actual_time_.toSec();
        // std::cout << "NOW Time: " << now << std::endl;
        target_frame_ = trajectory_->Pos(now_);
        vel_i_ = global_velPof_->Vel(now_);
        acc_i_ = global_velPof_->Acc(now_);
        // std::cout << "NOW Vel: " << vel_i << std::endl;
        // std::cout << "NOW Acc: " << acc_i << std::endl;
        // std::cout << "Target Frame:" << std::endl;
        // std::cout << "X: " << target_frame_.p.x() << std::endl;
        // std::cout << "Y: " << target_frame_.p.y() << std::endl;
        // std::cout << "Z: " << target_frame_.p.z() << std::endl;
        // std::cout << "Current Frame:" << std::endl;
        // std::cout << "X: " << current_pose.p.x() << std::endl;
        // std::cout << "Y: " << current_pose.p.y() << std::endl;
        // std::cout << "Z: " << current_pose.p.z() << std::endl;
        start_frame_ = current_pose;
    }

    // get the pose error
    KDL::Twist control_error;
    KDL::Twist final_error;

    // Target frame is already with ISS reference
    control_error = KDL::diff(current_pose, target_frame_);
    // std::cout << "Error: " << control_error << std::endl;
    final_error = KDL::diff(current_pose, final_frame_);
    //check if the tool has arrive to the desired point
    goal_reached.data = compareTolerance(final_error);

    jnt_to_jac_solver_->JntToJac(jnt_pos_, jacobian_);

    // jnt_effort_ = Jac^transpose * cart_wrench
    for (unsigned int i = 0; i < jnt_pos_.rows(); i++)
    {
        jnt_effort_(i) = 0;
        for (unsigned int j=0; j<6; j++){
            jnt_effort_(i) += (jacobian_(j,i) * kp_ * control_error(j));
        }
    }

    writeJointCommand(jnt_effort_);
    tolerance_publisher_.publish(goal_reached);

    // If it arrives to the desired point it has to stop there
    if(goal_reached.data and start_trajectory_){
        target_frame_ = current_pose;
        start_frame_ = current_pose;
        start_trajectory_ = false;
        finish_trajectory_ = true;
        kp_ = 20.0;
    }

}

void aruco_trajectory_cartesian_controller_class::writeJointCommand(KDL::JntArray joint_command){
    // Send joint position to joints
    for(size_t i = 0; i < joint_handles_.size(); i++){
        joint_handles_[i].setCommand(joint_command(i));
    }
}

void aruco_trajectory_cartesian_controller_class::starting(const ros::Time &time) {
    
    //Some initializtions
    kp_ = 20.0;
    goal_reached.data = false;
    diff_frame_ = false;
    // Transformation from the aruco marker to the target point
    aruco_2_target_ = KDL::Frame(KDL::Rotation::RPY(1.555, 0.1558, -3.008), KDL::Vector(-0.491, 0.310, -0.090));
    // Trjectory inicializations
    start_trajectory_ = false;
    finish_trajectory_ = false;
    take_start_distance_ = true;
    ref_time_ = ros::Duration(9.0).toSec(); //9 sec trajectory
    duration_time_ = 0.0; 
    now_ = 0.0;
    vel_i_ = 0.0;
    acc_i_ = 0.0;
    global_velPof_ = new KDL::VelocityProfile_Spline();

    //Get initial joints position 
    for(unsigned int i = 0; i < joint_handles_.size(); i++){
        jnt_pos_(i) = joint_handles_[i].getPosition();
    }

    KDL::Frame current_pose;
    fk_status = jnt_to_pose_solver_->JntToCart(jnt_pos_,current_pose);
    if (fk_status == -1) 
        ROS_ERROR_STREAM("No se ha podido calcular la cinematica directa ... ");

    // Send current pose to the end effector to not to move
    target_frame_ = current_pose;
    // Save first cartesian positión to detect when a differente one has arrived
    local_frame_ = current_pose;
    start_frame_ = current_pose;
}

void aruco_trajectory_cartesian_controller_class::stopping(const ros::Time &time) {}

bool aruco_trajectory_cartesian_controller_class::compareTolerance(KDL::Twist error){

    // Point reached
    if(diff_frame_){ // To not check when it has just started
        if(fabs(error(0)) < tolerance_ and fabs(error(1)) < tolerance_ and fabs(error(2)) < tolerance_){
            return true;
        }
    }
    // Not reached yet
    return false;
}

bool aruco_trajectory_cartesian_controller_class::diffTargetFrame(KDL::Frame target_frame){

    if(target_frame != local_frame_){
            return true; // A different frame has arrived
    }
    return false;
}

void aruco_trajectory_cartesian_controller_class::transformationCallback(const geometry_msgs::PoseStamped& data){
    
    float x, y, z, q_x, q_y, q_z, q_w;

    x = data.pose.position.x;
    y = data.pose.position.y;
    z = data.pose.position.z;
    q_x = data.pose.orientation.x;
    q_y = data.pose.orientation.y;
    q_z = data.pose.orientation.z;
    q_w = data.pose.orientation.w;

    if(data.header.frame_id == "base_link"){

        talos_2_aruco_ = KDL::Frame(KDL::Rotation::Quaternion(q_x, q_y, q_z, q_w), KDL::Vector(x, y, z));
        target_frame_ = talos_2_aruco_ * aruco_2_target_;

        if (diffTargetFrame(target_frame_) and not finish_trajectory_) {
            diff_frame_ = true;
            final_frame_ = target_frame_;

            if(take_start_distance_){
                start_distance_ = distanceBetweenFrames(start_frame_, final_frame_);
            }

            double frame_distance = distanceBetweenFrames(start_frame_, final_frame_);
            duration_time_ = (frame_distance * ref_time_)/start_distance_;

            // Save starting time for the trajectory
            begin_time_ = ros::Time::now();
            // If a direfent frame is recalculated it won't do a 7 sec trajectory
            // if((duration_time_ - now) > 0.0) duration_time_ = duration_time_ - now;
            // std::cout << "NOW Vel: " << vel_i_ << std::endl;
            // std::cout << "NOW Acc: " << acc_i_ << std::endl;
            // std::cout << "START DISTANCE between frames : " << start_distance_ << std::endl;
            // std::cout << "DISTANCE between frames : " << frame_distance << std::endl;
            // std::cout << "DURATION time recalculated : " << duration_time_ << std::endl;

            // std::cout << "Start Frame:" << std::endl;
            // std::cout << "X: " << start_frame_.p.x() << std::endl;
            // std::cout << "Y: " << start_frame_.p.y() << std::endl;
            // std::cout << "Z: " << start_frame_.p.z() << std::endl;
            // std::cout << "Final Frame:" << std::endl;
            // std::cout << "X: " << final_frame_.p.x() << std::endl;
            // std::cout << "Y: " << final_frame_.p.y() << std::endl;
            // std::cout << "Z: " << final_frame_.p.z() << std::endl;

            trajectory_ = trajectoryPlanner(start_frame_, final_frame_,vel_i_, acc_i_, duration_time_);
            local_frame_ = target_frame_;
            start_trajectory_ = true;
            take_start_distance_ = false;
            kp_ = 75.0;
        }
    }

}

// Create a cartesian trajectory with a quintic spline interpolation 
KDL::Trajectory* aruco_trajectory_cartesian_controller_class::trajectoryPlanner(const KDL::Frame start, const KDL::Frame ending, double vel_i, double acc_i, double duration){

    // Geometrical path
    KDL::Path_RoundedComposite* path = new KDL::Path_RoundedComposite(0.2,0.01,new KDL::RotationalInterpolation_SingleAxis()); 
    path->Add(start); 
    path->Add(ending);
    path->Finish();

    KDL::VelocityProfile_Spline* velprof = new KDL::VelocityProfile_Spline();
    //(start_pos, start_vel, start_acc, end_pos, end_vel, end_acc, Duration)
    velprof->SetProfileDuration(0, vel_i, acc_i, path->PathLength(), 0, 0.0,  duration);
    global_velPof_->SetProfileDuration(0, vel_i, acc_i, path->PathLength(), 0, 0.0,  duration);
    KDL::Trajectory* traject = new KDL::Trajectory_Segment(path, velprof);

    return traject;

}

double aruco_trajectory_cartesian_controller_class::distanceBetweenFrames(const KDL::Frame start, const KDL::Frame ending){

    double angle_distance;
    double module_distance;
    double distance;

    KDL::Frame R = ending.Inverse()*start;
    angle_distance = acos((trace(R)-1)/2);

    double x_s = start.p.x();
    double y_s = start.p.y();
    double z_s = start.p.z();
    double x_e = ending.p.x();
    double y_e = ending.p.y();
    double z_e = ending.p.z();

    module_distance = sqrt(pow(x_s - x_e, 2) + pow(y_s - y_e, 2) + pow(z_s - z_e, 2));

    distance = (angle_distance + module_distance)/2;

    return distance;

}

double aruco_trajectory_cartesian_controller_class::trace(const KDL::Frame frame){

    double trace;
    
    trace = frame(0,0) + frame(1,1) + frame(2,2);
    
    return trace;

}
    
}; // namespace


#endif