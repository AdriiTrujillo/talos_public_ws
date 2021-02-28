#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Float64.h>

int main(int argc, char **argv){

    ros::init(argc, argv, "look_to_arcuo_node");
    ros::NodeHandle n;

    ros::Publisher head_publisher = n.advertise<std_msgs::Float64>("/astronaut_head_pan_controller/command", 1000);

    std_msgs::Float64 head_move;
    head_move.data = -0.5;

    while(ros::ok){
        head_publisher.publish(head_move);
        ros::spinOnce();
    }

    return 0;
}