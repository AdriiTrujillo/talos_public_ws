# TALOS ASTRONAUT PROJECT
*Author: Adrián Trujillo López*  
*Contact: adrii.trujillo@gmail.com*

## Description

This is my final degree project for the Alicante University's robotics engineering degree. In this project I carry out the design, simlation and control of 
a humanoid robotic atronaut. To do this project I started working from the TALOS robot from [PAL Robotics' Company](https://pal-robotics.com/). That is the
reason why almost everything on this project is from the public repository of the TALOS Robot, only the next folders are made by me:

* src/talos_astronaut/astronaut
* src/talos_astronaut/astronaut_controllers
* src/talos_astronaut/Gazebo_Models

Said that, I will start explaining that I implemented different cartesian controllers in the folder `astronaut_controllers` which can move the arm to a
known point to grasp a handle from the ISS. However, I also implemented a version of those controllers to work at any situation in general. The controllers
that works to gras a handle from the ISS also auses an Aruco Marker to localize its own base and adjust the trajectory to the final destination even if the
robot's base is moving because of arms' movement inertia.

## Compile the project

I will recommend to look at PAL's Robotics [instructions](http://wiki.ros.org/Robots/TALOS/Tutorials/Installation/Simulation) to install all the requiered dependencies for 
each ROS Version.In addition to PAL Robotics dependencies this project also uses KDL, Pinocchio and Eigen libraries. Once that all the dependencies are installed and the 
environment variables are setted the next step will be to compile my packages in first place:

```
1º --> catkin build astronaut_controllers
2º --> catkin build astronaut
3º --> catkin build aruco_ros
4º --> catkin build hey5_description
```
Then the rest of the project can be compiled by typing:

```
catkin build -DCATKIN_ENABLE_TESTING=0
```

## Run

Before running any example it would be necessary to copy the Gazebo models in de folder `Gazebo_Models` to your own system.
Then If you want to see the funcionality of this project you can run the next simulation:

```
roslaunch astronaut astronaut.launch
```
