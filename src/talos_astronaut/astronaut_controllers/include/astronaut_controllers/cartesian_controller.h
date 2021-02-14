#ifndef CARTESIAN_CONTROLLER_H_INCLUDED
#define CARTESIAN_CONTROLLER_H_INCLUDED

#include <ros/ros.h>
#include <vector>
#include <string>

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

#include <astronaut_controllers/target_frame.h>

namespace controller_ns{

    class cartesian_controller_class : public controller_interface::Controller<hardware_interface::EffortJointInterface> {
        
        public:

            bool init(hardware_interface::EffortJointInterface* hw, ros::NodeHandle& nh);
            void update(const ros::Time &time, const ros::Duration &period);
            void starting(const ros::Time &time);
            void stopping(const ros::Time &time);
            void writeJointCommand(KDL::JntArray joint_command);

        private:
            
            ros::Subscriber target_frame_subscr_;
            void targetFrameCallback(const astronaut_controllers::target_frame& target_frame);

            std::vector<hardware_interface::JointHandle>      _joint_handles;
            std::vector<std::string>                          _joint_names;

            KDL::Chain _robot_chain;
            KDL::Tree _robot_tree;

            // KDL Solvers performing the actual computations
            int ik_status;
            boost::scoped_ptr<KDL::ChainFkSolverPos>    _jnt_to_pose_solver;
            boost::scoped_ptr<KDL::ChainJntToJacSolver> _jnt_to_jac_solver;

            //Variables
            KDL::JntArray _jnt_pos, _jnt_effort;
            KDL::Jacobian _jacobian;
            KDL::Frame _reference_pose;
            KDL::Frame target_frame_;
    };

}; //namespace

//Project
#include <astronaut_controllers/cartesian_controller.hpp>

#endif


