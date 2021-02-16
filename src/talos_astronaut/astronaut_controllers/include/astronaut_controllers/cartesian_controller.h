#ifndef CARTESIAN_CONTROLLER_H_INCLUDED
#define CARTESIAN_CONTROLLER_H_INCLUDED

#include <ros/ros.h>
#include <vector>
#include <string>
#include <math.h>

#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>

#include <boost/scoped_ptr.hpp>
#include <kdl/chain.hpp>
#include <kdl/tree.hpp>
#include <kdl/chainjnttojacsolver.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames.hpp>
#include <kdl/jacobian.hpp>
#include <kdl/jntarray.hpp>
#include <kdl/segment.hpp>
#include <kdl/joint.hpp>

// GAZEBO MSGS
#include <gazebo_msgs/ModelStates.h>


#include <astronaut_controllers/target_frame.h>

namespace controller_ns{

    class cartesian_controller_class : public controller_interface::Controller<hardware_interface::EffortJointInterface> {
        
        public:

            bool init(hardware_interface::EffortJointInterface* hw, ros::NodeHandle& nh);
            void update(const ros::Time &time, const ros::Duration &period);
            void starting(const ros::Time &time);
            void stopping(const ros::Time &time);
            void writeJointCommand(KDL::JntArray joint_command);
            void calculate_transformations(KDL::Frame &current_pose);

        private:
            
            ros::Subscriber target_frame_subscr_;
            void targetFrameCallback(const astronaut_controllers::target_frame& target_frame);

            ros::Subscriber Gazebo_models_subscr_;
            void transformationsCallback(const gazebo_msgs::ModelStates& data);

            std::vector<hardware_interface::JointHandle>      joint_handles_;
            std::vector<std::string>                          joint_names_;

            KDL::Chain robot_chain_;
            KDL::Tree robot_tree_;

            // KDL Solvers performing the actual computations
            int ik_status;
            boost::scoped_ptr<KDL::ChainFkSolverPos>    jnt_to_pose_solver_;
            boost::scoped_ptr<KDL::ChainJntToJacSolver> jnt_to_jac_solver_;

            //Variables
            KDL::JntArray jnt_pos_, jnt_effort_;
            KDL::Jacobian jacobian_;
            KDL::Frame target_frame_;
            KDL::Frame world_2_Talos_;
            KDL::Frame world_2_ISS_;

    };

}; //namespace

//Project
#include <astronaut_controllers/cartesian_controller.hpp>

#endif


