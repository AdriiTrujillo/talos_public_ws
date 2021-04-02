cmake_minimum_required(VERSION 3.0)
project(PinocchioDudas)

find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)
find_package(pinocchio REQUIRED)

add_definitions("-DBOOST_MPL_LIMIT_LIST_SIZE=30")

include_directories(
  ${EIGEN3_INCLUDE_DIRS}
  ${pinocchio_INCLUDE_DIRS}
)

add_executable(pinocchio_jacobiana pinocchio_jacobiana.cc)
target_link_libraries(pinocchio_jacobiana ${pinocchio_LIBRARIES} ${boost_LIBRARIES})
