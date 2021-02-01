
#ifndef DIRECT_DYNAMIC_CONTROLLER_JOINT_TRAJECTORY_MSG_UTILS_H
#define DIRECT_DYNAMIC_CONTROLLER_JOINT_TRAJECTORY_MSG_UTILS_H

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include <ros/console.h>
#include <ros/time.h>
#include <trajectory_msgs/JointTrajectory.h>

#include <trajectory_interface/trajectory_interface.h>

namespace direct_dynamic_controller
{
namespace internal
{

class IsBeforePoint
{
public:
  IsBeforePoint(const ros::Time& msg_start_time) : msg_start_time_(msg_start_time) {}

  bool operator()(const ros::Time& time, const trajectory_msgs::JointTrajectoryPoint& point)
  {
    const ros::Time point_start_time = msg_start_time_ + point.time_from_start;
    return time < point_start_time;
  }

private:
  ros::Time msg_start_time_;
};

/**
 * \param msg Trajectory message.
 * \param time Trajectory start time, if unspecified in message.
 * \return Start time specified in message. If unspecified (set to zero) return \p time.
 */
inline ros::Time startTime(const trajectory_msgs::JointTrajectory& msg,
                           const ros::Time&                        time)
{
  return msg.header.stamp.isZero() ? time : msg.header.stamp;
}

} // namespace

/**
 * \param point Trajectory point message.
 * \param joint_dim Expected dimension of the position, velocity and acceleration fields.
 * \return True if sizes of the position, velocity and acceleration fields are consistent. An empty field means that
 * it's unspecified, so in this particular case its dimension must not coincide with \p joint_dim.
 */
inline bool isValid(const trajectory_msgs::JointTrajectoryPoint& point, const unsigned int joint_dim)
{
  if (!point.positions.empty()     && point.positions.size()     != joint_dim) {return false;}
  if (!point.velocities.empty()    && point.velocities.size()    != joint_dim) {return false;}
  if (!point.accelerations.empty() && point.accelerations.size() != joint_dim) {return false;}
  return true;
}

/**
 * \param msg Trajectory message.
 * \return True if sizes of input message are consistent (joint names, position, velocity, acceleration).
 */
inline bool isValid(const trajectory_msgs::JointTrajectory& msg)
{
  const std::vector<std::string>::size_type joint_dim = msg.joint_names.size();

  typedef std::vector<trajectory_msgs::JointTrajectoryPoint>::const_iterator PointConstIterator;

  for (PointConstIterator it = msg.points.begin(); it != msg.points.end(); ++it)
  {
    const std::iterator_traits<PointConstIterator>::difference_type index = std::distance(msg.points.begin(), it);

    if(!isValid(*it, joint_dim))
    {
      ROS_ERROR_STREAM("Invalid trajectory point at index: " << index <<
                       ". Size mismatch in joint names, position, velocity or acceleration data.");
      return false;
    }
  }
  return true;
}

/**
 * \param msg Trajectory message.
 * \return True if each trajectory waypoint is reached at a later time than its predecessor.
 */
inline bool isTimeStrictlyIncreasing(const trajectory_msgs::JointTrajectory& msg)
{
  if (msg.points.size() < 2) {return true;}

  typedef std::vector<trajectory_msgs::JointTrajectoryPoint>::const_iterator PointConstIterator;

  PointConstIterator it = msg.points.begin();
  PointConstIterator end_it = --msg.points.end();
  while (it != end_it)
  {
    const ros::Duration& t1 = it->time_from_start;
    const ros::Duration& t2 = (++it)->time_from_start;
    if (t1 >= t2) {return false;}
  }
  return true;
}

/**
 * \brief Find an iterator to the trajectory point with the greatest start time < \p time.
 *
 * \param msg Trajectory message.
 * \param time Time to search for in the range.
 *
 * \return Iterator to the trajectory point with the greatest start time < \p time.
 * If all points occur at a time greater than \p time, then \p the points sequence end is returned.
 *
 * \pre The points in \p msg have monotonically increasing times.
 *
 * \note On average, this method has logarithmic time complexity when used on containers with \b random-access iterators.
 * On \b non-random-access iterators, iterator advances incur an additional linear time cost.
 */
inline std::vector<trajectory_msgs::JointTrajectoryPoint>::const_iterator
findPoint(const trajectory_msgs::JointTrajectory& msg,
          const ros::Time&                        time)
{
  // Message trajectory start time
  // If message time is == 0.0, the trajectory should start at the current time
  const ros::Time msg_start_time = internal::startTime(msg, time);
  internal::IsBeforePoint isBeforePoint(msg_start_time);

  typedef std::vector<trajectory_msgs::JointTrajectoryPoint>::const_iterator ConstIterator;
  const ConstIterator first = msg.points.begin();
  const ConstIterator last  = msg.points.end();

  return (first == last || isBeforePoint(time, *first))
         ? last // Optimization when time preceeds all segments, or when an empty range is passed
         : --std::upper_bound(first, last, time, isBeforePoint); // Notice decrement operator
}

} // namespace

#endif // header guard
