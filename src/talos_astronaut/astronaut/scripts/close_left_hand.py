#!/usr/bin/env python

import rospy
import math
import time

from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

def jointTrajectoryCommand():

    while rospy.get_rostime().to_sec() == 0.0:
        time.sleep(0.1)

    rospy.loginfo("Waiting for hand joints ... ")
    pub = rospy.Publisher('/left_hand_controller/command', JointTrajectory, queue_size=10)
    rate = rospy.Rate(10) # 10hz
    jt = JointTrajectory()
    jt.header.stamp = rospy.Time.now()
    jt.joint_names = ["hand_left_thumb_joint", "hand_left_index_joint", "hand_left_mrl_joint"]
    p = JointTrajectoryPoint()
    p.positions = [6.2, 6.8, 9.2]
    p.velocities = [0.0, 0.0, 0.0]
    p.accelerations = [0.0, 0.0, 0.0]
    p.effort = []
    p.time_from_start = rospy.Duration(2.5)
    jt.points.append(p)

    rospy.loginfo("closing ... ")
    while not rospy.is_shutdown():
        pub.publish(jt)
        rate.sleep()

if __name__ == "__main__":

    # Initialize the node
    rospy.init_node('Close_left_hand')

    try:
        jointTrajectoryCommand()

    except rospy.ROSInterruptException:
        pass