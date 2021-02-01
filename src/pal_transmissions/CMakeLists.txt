cmake_minimum_required(VERSION 2.8.3)
project(pal_transmissions)

# Load catkin and all dependencies required for this package
find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  hardware_interface
  pluginlib
  roscpp
  transmission_interface
)

# Include a custom cmake file for TinyXML
find_package(TinyXML REQUIRED)

# Declare a catkin package
catkin_package(
  LIBRARIES
  INCLUDE_DIRS
    include
  DEPENDS
    pluginlib
    roscpp
    TinyXML
    transmission_interface
)

###########
## Build ##
###########

include_directories(include ${catkin_INCLUDE_DIRS} ${TinyXML_INCLUDE_DIRS})

add_library(${PROJECT_NAME}_loader_plugins src/head_transmission_loader.cpp
                                           src/half_differential_transmission_loader.cpp)
target_link_libraries(${PROJECT_NAME}_loader_plugins ${catkin_LIBRARIES} ${TinyXML_LIBRARIES})

#############
## Install ##
#############

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(TARGETS ${PROJECT_NAME}_loader_plugins
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(FILES ros_control_plugins.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

#############
## Testing ##
#############

if(CATKIN_ENABLE_TESTING)
  find_package(resource_retriever)
  include_directories(${resource_retriever_INCLUDE_DIRS})

  catkin_add_gtest(head_transmission_test test/head_transmission_test.cpp)

  catkin_add_gtest(head_transmission_loader_test test/head_transmission_loader_test.cpp)
  target_link_libraries(head_transmission_loader_test ${catkin_LIBRARIES}
                                                           ${resource_retriever_LIBRARIES})

  add_dependencies(head_transmission_loader_test ${PROJECT_NAME}_loader_plugins)
endif()
