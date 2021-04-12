#ifndef ARUCO_TRAJECTORY_CARTESIAN_CONTROLLER_HPP_INCLUDED
#define ARUCO_TRAJECTORY_CARTESIAN_CONTROLLER_HPP_INCLUDED

// PROJECT
#include <astronaut_controllers/aruco_trajectory_cartesian_controller.h>
#include <astronaut_controllers/plot_msg.h>

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
    jnt_vel_.resize(kdl_chain.getNrOfJoints());
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
    control_error_pub_ = nh.advertise<astronaut_controllers::plot_msg>("/control_error", 1000);
    velocity_error_pub_ = nh.advertise<astronaut_controllers::plot_msg>("/velocity_error", 1000);
    joint_value_pub_ = nh.advertise<astronaut_controllers::plot_msg>("/joint_value", 1000);

    return true;

}

void aruco_trajectory_cartesian_controller_class::update(const ros::Time &time, const ros::Duration &period){

    //Get initial joints position
    for(unsigned int i = 0; i < joint_handles_.size(); i++){
        jnt_pos_(i) = joint_handles_[i].getPosition();
    }

    //Get initial joints velocity
    for(unsigned int i = 0; i < joint_handles_.size(); i++){
        jnt_vel_(i) = joint_handles_[i].getVelocity();
    }

    KDL::Frame current_pose;
    fk_status = jnt_to_pose_solver_->JntToCart(jnt_pos_,current_pose);
    // ROS_INFO("fk_status: %i", fk_status);
    if (fk_status < 0) 
        ROS_ERROR_STREAM("No se ha podido calcular la cinematica directa ... ");

    // calculate_transformations(current_pose);
// -------------------------------------------------------------------------------------------    
    // Descomentar para imprimir por pantalla la posición del extremo
    // ROS_INFO("Current: ");
    // ROS_INFO("x : %f",current_pose.p.x());
    // ROS_INFO("y : %f",current_pose.p.y());
    // ROS_INFO("z : %f",current_pose.p.z());
// ------------------------------------------------------------------------------------------- 
    KDL::Twist desired_vel;

    if(start_trajectory_){
        //Get the actual time
        actual_time_ = ros::Time::now() - begin_time_; // That's start in sec 0
        now_ = actual_time_.toSec();
        target_frame_ = trajectory_->Pos(now_);
        desired_vel = trajectory_->Vel(now_);
        vel_i_ = global_velPof_->Vel(now_);
        acc_i_ = global_velPof_->Acc(now_);
        start_frame_ = current_pose; //Update de start frame to start the folowing trajectory
    }

    // get the each pose control error
    KDL::Twist control_error;
    // get the error with respect final frame
    KDL::Twist final_error;

    // Target frame is the next nearest pose
    control_error = KDL::diff(current_pose, target_frame_);

    //_____________________________________________
    astronaut_controllers::plot_msg plot_error;
    plot_error.x_err = control_error(0);
    plot_error.y_err = control_error(1);
    plot_error.z_err = control_error(2);
    plot_error.roll_err = control_error(3);
    plot_error.pitch_err = control_error(4);
    plot_error.yaw_err = control_error(5);
    //_____________________________________________

    // Calculate the error of the final pose in the trajectory
    final_error = KDL::diff(current_pose, final_frame_);
    //check if the tool has arrive to the desired point
    goal_reached.data = compareTolerance(final_error);

    jnt_to_jac_solver_->JntToJac(jnt_pos_, jacobian_);

    // get actual cartesian velocities
    KDL::Twist cart_vel = KDL::Twist::Zero(); // Initiliz it to zeros
    for(unsigned int i = 0; i < 6 ; i++){
        for (unsigned int j=0; j<jnt_vel_.rows(); j++){
            cart_vel(i) += jacobian_(i,j) * jnt_vel_(j);
        }
    }

    KDL::Twist velocity_error;
    velocity_error = KDL::diff(cart_vel, desired_vel);
    //_____________________________________________
    astronaut_controllers::plot_msg plot_vel_error;
    plot_vel_error.x_err = velocity_error(0);
    plot_vel_error.y_err = velocity_error(1);
    plot_vel_error.z_err = velocity_error(2);
    plot_vel_error.roll_err = velocity_error(3);
    plot_vel_error.pitch_err = velocity_error(4);
    plot_vel_error.yaw_err = velocity_error(5);
    //_____________________________________________

    // jnt_effort_ = Jac^transpose * cart_wrench
    for (unsigned int i = 0; i < jnt_pos_.rows(); i++)
    {
        jnt_effort_(i) = 0;
        for (unsigned int j=0; j<6; j++){
            jnt_effort_(i) += (jacobian_(j,i) * (kp_ * control_error(j) + kv_*velocity_error(j)));
        }
    }

    //_____________________________________________
    astronaut_controllers::plot_msg joint_value;
    joint_value.x_err = jnt_effort_(0);
    joint_value.y_err = jnt_effort_(1);
    joint_value.z_err = jnt_effort_(2);
    joint_value.roll_err = jnt_effort_(3);
    joint_value.pitch_err = jnt_effort_(4);
    joint_value.yaw_err = jnt_effort_(5);
    //_____________________________________________

    writeJointCommand(jnt_effort_);
    tolerance_publisher_.publish(goal_reached);
    control_error_pub_.publish(plot_error);
    velocity_error_pub_.publish(plot_vel_error);
    joint_value_pub_.publish(joint_value);


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
    
    // Some initializtions __________________________________________________________________________________________
    kp_ = 20.0;
    kv_ = 10.0; // 50 not working vibrations // 10 better but worse than with only kp
    goal_reached.data = false;
    diff_frame_ = false;
    // Transformation from the aruco marker to the target point
    aruco_2_target_ = KDL::Frame(KDL::Rotation::RPY(1.555, 0.1558, -3.008), KDL::Vector(-0.491, 0.310, -0.090)); // HEY-5 Point
    // aruco_2_target_ = KDL::Frame(KDL::Rotation::RPY(1.498, 0.254, 3.101), KDL::Vector(-0.441, 0.301, -0.135)); // GRIPPERS Point

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
    // ______________________________________________________________________________________________________________

    //Get initial joints position ___________________________________________________________________________________ 
    for(unsigned int i = 0; i < joint_handles_.size(); i++){
        jnt_pos_(i) = joint_handles_[i].getPosition();
    }

    KDL::Frame current_pose;
    fk_status = jnt_to_pose_solver_->JntToCart(jnt_pos_,current_pose);
    if (fk_status == -1) 
        ROS_ERROR_STREAM("No se ha podido calcular la cinematica directa ... ");

    // Send current pose to the end effector to not to move
    target_frame_ = current_pose;
    // ______________________________________________________________________________________________________________
    // Save the first cartesian positión to detect when a differente one has arrived ________________________________
    local_frame_ = current_pose;
    start_frame_ = current_pose;
    // ______________________________________________________________________________________________________________
}

void aruco_trajectory_cartesian_controller_class::stopping(const ros::Time &time) {}

bool aruco_trajectory_cartesian_controller_class::compareTolerance(KDL::Twist error){

    if(diff_frame_){ // To not check when it has just started
        // std::cout << " ------- " << std::endl;
        // std::cout << "x_err: " << fabs(error(0)) << std::endl;
        // std::cout << "y_err: " << fabs(error(1)) << std::endl;
        // std::cout << "z_err: " << fabs(error(2)) << std::endl;
        // std::cout << "roll_err: " << fabs(error(3)) << std::endl;  
        // std::cout << "pitch_err: " << fabs(error(4)) << std::endl;
        // std::cout << "yaw_err: " << fabs(error(5)) << std::endl;
        // std::cout << " ------- " << std::endl;
        if(fabs(error(0)) < tolerance_ and fabs(error(1)) < tolerance_ and fabs(error(2)) < tolerance_ and fabs(error(3)) < tolerance_ and fabs(error(4)) < tolerance_ and fabs(error(5)) < tolerance_){
            // std::cout << "GOAL REACHED" << std::endl;
            return true; // Point reached
        }
    }
    // Not reached yet
    // std::cout << "GOAL NOT REACHED YET" << std::endl;
    return false;
}

bool aruco_trajectory_cartesian_controller_class::diffTargetFrame(KDL::Frame target_frame){

    if(target_frame != local_frame_){
            return true; // A different frame has arrived!!
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
        target_frame_ = talos_2_aruco_ * aruco_2_target_; // Transformation from base link to position using aruco reference.

        if (diffTargetFrame(target_frame_) and not finish_trajectory_) {
            diff_frame_ = true;
            final_frame_ = target_frame_;

            if(take_start_distance_){
                start_distance_ = distanceBetweenFrames(start_frame_, final_frame_);
            }

            double frame_distance = distanceBetweenFrames(start_frame_, final_frame_);
            // The time is escalated having the reference of the first distance
            duration_time_ = (frame_distance * ref_time_)/start_distance_;

            // Save starting time for the trajectory
            begin_time_ = ros::Time::now();

            // If a direfent frame is recalculated it won't do a 9 sec trajectory
            // It use the velocity and acceleration of the previous trajectory to start the next one
            trajectory_ = trajectoryPlanner(start_frame_, final_frame_,vel_i_, acc_i_, duration_time_);
            local_frame_ = target_frame_;
            start_trajectory_ = true;
            take_start_distance_ = false;
            kp_ = 300.0; // When moving it uses this constant
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
    global_velPof_->SetProfileDuration(0, vel_i, acc_i, path->PathLength(), 0, 0.0,  duration); // To get the velocity and accelration of the previous trajectory
    KDL::Trajectory* traject = new KDL::Trajectory_Segment(path, velprof);

    return traject;

}

double aruco_trajectory_cartesian_controller_class::distanceBetweenFrames(const KDL::Frame start, const KDL::Frame ending){

    double angle_distance;
    double module_distance;
    double distance;

    KDL::Frame R = ending.Inverse()*start;
    angle_distance = acos((trace(R)-1)/2); // Distance beetwen start matrix rotation and end matrix rotation

    double x_s = start.p.x();
    double y_s = start.p.y();
    double z_s = start.p.z();
    double x_e = ending.p.x();
    double y_e = ending.p.y();
    double z_e = ending.p.z();
    
    // Distance beetwen start position and ending position
    module_distance = sqrt(pow(x_s - x_e, 2) + pow(y_s - y_e, 2) + pow(z_s - z_e, 2)); 

    // Calculate the mean of this two
    distance = (angle_distance + module_distance)/2;

    return distance;

}

// Obtain the trace of the matrix rotation instade a KDL::Frame
double aruco_trajectory_cartesian_controller_class::trace(const KDL::Frame frame){

    double trace;
    
    trace = frame(0,0) + frame(1,1) + frame(2,2);
    
    return trace;

}
    
}; // namespace


#endif