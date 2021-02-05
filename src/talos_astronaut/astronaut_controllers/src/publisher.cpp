#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

int main(int argc, char **argv){

    ros::init(argc, argv, "Publisher");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<geometry_msgs::PoseStamped>("my_cartesian_motion_controller/target_frame", 1000);
    
    geometry_msgs::PoseStamped target_frame;
    ros::Rate loop_rate(10);
    target_frame.header.frame_id = "wrist_right_ft_tool_link";
    target_frame.pose.position.x = 0.5;
    target_frame.pose.position.y = -0.2;
    target_frame.pose.position.z = -0.2;
    target_frame.pose.orientation.x = 0.0;
    target_frame.pose.orientation.y = 0.0;
    target_frame.pose.orientation.z = 0.0;
    target_frame.pose.orientation.w = 1.0;

    while (ros::ok()){

        pub.publish(target_frame);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;

}