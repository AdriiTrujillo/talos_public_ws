#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include "astronaut_controllers/target_frame.h"

#include <vector>
#include <string>
#include <bits/stdc++.h>

astronaut_controllers::target_frame target_frame;
std_msgs::Float64 head_move;
bool ready = false;

std::vector<float> removeDupWord(std::string str) {

    // Used to split string around spaces.
    std::istringstream ss(str);
 
    std::string word;
    std::vector<float> positions;

    while (ss >> word){
        positions.push_back(std::stof(word));
    }

    return positions;

}

void qr_callback(const std_msgs::String::ConstPtr& data){

    std::vector<float> positions;
    positions = removeDupWord(data->data.c_str());
    
    target_frame.x = positions[0];

    target_frame.y = positions[1];

    target_frame.z = positions[2];

    target_frame.roll = positions[3];

    target_frame.pitch = positions[4];

    target_frame.yaw = positions[5];

    head_move.data = 0.0;
    
    ready = true;
    
}

int main(int argc, char **argv){

    ros::init(argc, argv, "send_position_node");
    ros::NodeHandle n;

    ros::Publisher head_publisher = n.advertise<std_msgs::Float64>("/astronaut_head_pan_controller/command", 1000);
    ros::Publisher arm_publisher = n.advertise<astronaut_controllers::target_frame>("/cartesian_target_frame", 1000);
    ros::Subscriber qr_subscriber = n.subscribe("/qr_codes", 1000, qr_callback);

    head_move.data = -0.5;

    while(ros::ok){
        if(ready) arm_publisher.publish(target_frame);
        head_publisher.publish(head_move);
        ros::spinOnce();
    }

    return 0;
}
