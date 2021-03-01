#!/usr/bin/env python

import rospy
import math
import time

from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

def jointTrajectoryCommand():

    while rospy.get_rostime().to_sec() == 0.0:
        time.sleep(0.1)

    rospy.loginfo("Waiting for hand joints ... ")
    pub = rospy.Publisher('/right_hand_controller/command', JointTrajectory, queue_size=10)
    rate = rospy.Rate(10) # 10hz
    jt = JointTrajectory()
    jt.header.stamp = rospy.Time.now()
    jt.joint_names = ["hand_right_thumb_joint", "hand_right_index_joint", "hand_right_mrl_joint"]
    p = JointTrajectoryPoint()
    # p.positions = [6.2, 6.8, 9.2]
    p.positions = [1.70, 1.70, 2.0]
    p.velocities = [0.0, 0.0, 0.0]
    p.accelerations = [0.0, 0.0, 0.0]
    p.effort = [0.33, 0.33, 0.33]
    p.time_from_start = rospy.Duration(2.5)
    jt.points.append(p)

    rospy.loginfo("closing ... ")
    while not rospy.is_shutdown():
        pub.publish(jt)
        rate.sleep()

if __name__ == "__main__":

    # Initialize the node
    rospy.init_node('Close_right_hand')

    try:
        jointTrajectoryCommand()

    except rospy.ROSInterruptException:
        pass