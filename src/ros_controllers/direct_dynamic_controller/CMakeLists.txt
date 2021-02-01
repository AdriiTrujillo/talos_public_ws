cmake_minimum_required(VERSION 2.8.3)
project(direct_dynamic_controller)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

# Load catkin and all dependencies required for this package
find_package(catkin
  REQUIRED COMPONENTS
    actionlib
    angles
    cmake_modules
    roscpp
    urdf
    control_toolbox
    controller_interface
    hardware_interface
    realtime_tools
    control_msgs
    trajectory_msgs
    kdl_parser
    ddynamic_reconfigure
)

find_package(orocos_kdl REQUIRED)

# Declare catkin package
catkin_package(
  CATKIN_DEPENDS
  actionlib
  angles
  roscpp
  urdf
  control_toolbox
  controller_interface
  hardware_interface
  realtime_tools
  control_msgs
  trajectory_msgs
  kdl_parser
  ddynamic_reconfigure
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
)

include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${USE_OROCOS_INCLUDE_DIRS} ${orocos_kdl_INCLUDE_DIRS})

add_library(${PROJECT_NAME} src/direct_dynamic_controller.cpp
                            include/direct_dynamic_controller/hardware_interface_adapter.h
                            include/direct_dynamic_controller/init_joint_trajectory.h
                            include/direct_dynamic_controller/direct_dynamic_controller.h
                            include/direct_dynamic_controller/direct_dynamic_controller_impl.h
                            include/direct_dynamic_controller/joint_trajectory_msg_utils.h
                            include/direct_dynamic_controller/joint_trajectory_segment.h
                            include/direct_dynamic_controller/tolerances.h
                            include/trajectory_interface/trajectory_interface.h
                            include/trajectory_interface/quintic_spline_segment.h
                            include/trajectory_interface/pos_vel_acc_state.h)

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

# Install
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(DIRECTORY include/trajectory_interface/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/trajectory_interface/)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

foreach(dir config launch)
    install(DIRECTORY ${dir}/
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)

install(FILES ros_control_plugins.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

# TODO: Install test resource files as well?
