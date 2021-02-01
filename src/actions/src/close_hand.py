#!/usr/bin/env python

import rospy
import actionlib
from control_msgs.msg import FollowJointTrajectoryAction, FollowJointTrajectoryGoal
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from sensor_msgs.msg import JointState

first_move = [-2.37, 0.0, 0.0]
final_move = [-6.2, -6.8, -9.2]

if __name__ == "__main__":

  rospy.init_node("close_hand")
  joint_names = ["hand_right_thumb_joint", "hand_right_index_joint", "hand_right_mrl_joint"]
  rospy.loginfo("Waiting for hand controllers ...")
  client = actionlib.SimpleActionClient("right_arm_controller/follow_joint_trajectory", FollowJointTrajectoryAction)
  client.wait_for_server()
  rospy.loginfo("...connected.")

  rospy.wait_for_message("joint_states", JointState)

  trajectory = JointTrajectory()
  trajectory.joint_names = joint_names
  trajectory.points.append(JointTrajectoryPoint())
  trajectory.points[0].positions = first_move
  trajectory.points[0].velocities = [0.0 for i in joint_names]
  trajectory.points[0].accelerations = [0.0 for i in joint_names]
  trajectory.points[0].time_from_start = rospy.Duration(0.1)

  rospy.loginfo("Preparing to close...")
  goal = FollowJointTrajectoryGoal()
  goal.trajectory = trajectory
  goal.goal_time_tolerance = rospy.Duration(0.0)

  client.send_goal(goal)
  client.wait_for_result(rospy.Duration(3.0))
  rospy.loginfo("Prepared")

  closing_trajectory = JointTrajectory()
  closing_trajectory.joint_names = joint_names
  closing_trajectory.points.append(JointTrajectoryPoint())
  closing_trajectory.points[0].positions = first_move
  closing_trajectory.points[0].velocities = [0.0 for i in joint_names]
  closing_trajectory.points[0].accelerations = [0.0 for i in joint_names]
  closing_trajectory.points[0].time_from_start = rospy.Duration(2.5)

  rospy.loginfo("Closing...")
  goal = FollowJointTrajectoryGoal()
  goal.trajectory = trajectory
  goal.goal_time_tolerance = rospy.Duration(0.0)

  client.send_goal(goal)
  client.wait_for_result(rospy.Duration(3.0))
  rospy.loginfo("Closed")

