
#include <pluginlib/class_list_macros.h>
#include <astronaut_controllers/aruco_cartesian_controller.h>
#include <astronaut_controllers/aruco_trajectory_cartesian_controller.h>
#include <astronaut_controllers/cartesian_controller_gazebo_ref.h>

namespace position_controller {

typedef controller_ns::aruco_cartesian_controller_class ArucoController;

typedef controller_ns::gazebo_cartesian_controller_class GazeboController;

typedef controller_ns::aruco_trajectory_cartesian_controller_class ArucoTrajectoryController;

};

PLUGINLIB_EXPORT_CLASS(position_controller::ArucoController, controller_interface::ControllerBase);
PLUGINLIB_EXPORT_CLASS(position_controller::GazeboController, controller_interface::ControllerBase);
PLUGINLIB_EXPORT_CLASS(position_controller::ArucoTrajectoryController, controller_interface::ControllerBase);

