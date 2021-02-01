
#include <pluginlib/class_list_macros.h>
#include <astronaut_controllers/cartesian_controller.h>

namespace position_controller {

typedef controller_ns::cartesian_controller_class PositionController;

};

PLUGINLIB_EXPORT_CLASS(position_controller::PositionController, controller_interface::ControllerBase);

