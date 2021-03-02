
#include <pluginlib/class_list_macros.h>
#include <astronaut_controllers/aruco_cartesian_controller.h>

namespace position_controller {

typedef controller_ns::aruco_cartesian_controller_class ArucoController;

};

PLUGINLIB_EXPORT_CLASS(position_controller::ArucoController, controller_interface::ControllerBase);

