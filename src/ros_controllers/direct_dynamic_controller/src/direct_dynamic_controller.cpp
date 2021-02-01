// Pluginlib
#include <pluginlib/class_list_macros.h>

// Project
#include <trajectory_interface/quintic_spline_segment.h>
#include <direct_dynamic_controller/direct_dynamic_controller.h>

namespace effort_controllers
{
  /**
   * \brief Joint trajectory controller that represents trajectory segments as <b>quintic splines</b> and sends
   * commands to an \b effort interface, taking into account the robotic arm dynamics at each time step.
   */
  typedef direct_dynamic_controller::DirectDynamicController<trajectory_interface::QuinticSplineSegment<double>,
                                                                 hardware_interface::EffortJointInterface>
          DirectDynamicController;
}

PLUGINLIB_EXPORT_CLASS(effort_controllers::DirectDynamicController,   controller_interface::ControllerBase)

