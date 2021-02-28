#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Float64.h>

int main(int argc, char **argv){

    ros::init(argc, argv, "look_to_arcuo_node");
    ros::NodeHandle n;

    ros::Publisher head_pan_publisher = n.advertise<std_msgs::Float64>("/astronaut_head_pan_controller/command", 1000);
    ros::Publisher head_tilt_publisher = n.advertise<std_msgs::Float64>("/astronaut_head_tilt_controller/command", 1000);

    std_msgs::Float64 head_pan_move;
    std_msgs::Float64 head_tilt_move;
    head_pan_move.data = -0.4;
    head_tilt_move.data = -0.1;


    while(ros::ok){
        head_pan_publisher.publish(head_pan_move);
        head_tilt_publisher.publish(head_tilt_move);
        ros::spinOnce();
    }

    return 0;
}