# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "actionlib;angles;roscpp;urdf;control_toolbox;controller_interface;hardware_interface;realtime_tools;control_msgs;trajectory_msgs;kdl_parser;ddynamic_reconfigure".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-ldirect_dynamic_controller".split(';') if "-ldirect_dynamic_controller" != "" else []
PROJECT_NAME = "direct_dynamic_controller"
PROJECT_SPACE_DIR = "/home/adrii/talos_public_ws/install"
PROJECT_VERSION = "2.0.0"
