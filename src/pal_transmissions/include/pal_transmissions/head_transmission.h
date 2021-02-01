///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2015, PAL Robotics S.L.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of PAL Robotics S.L. nor the names of its
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

/// \author Adolfo Rodriguez Tsouroukdissian

#ifndef TRANSMISSIONS_HEAD__TRANSMISSION
#define TRANSMISSIONS_HEAD__TRANSMISSION

#include <algorithm>
#include <cassert>
#include <limits>
#include <string>
#include <vector>

#include <transmission_interface/transmission.h>
#include <transmission_interface/transmission_interface_exception.h>

using transmission_interface::ActuatorData;
using transmission_interface::JointData;
using transmission_interface::Transmission;
using transmission_interface::TransmissionInterfaceException;

namespace pal_transmissions
{

/**
 * \brief Implementation of the REEM / REEM-C head tramsission.
 *
 */
class HeadTransmission : public Transmission
{
public:
  /**
   * Stores minimum and maximum values for a variable associated to a key.
   */
  struct Limits
  {
    Limits()
      : min(-std::numeric_limits<double>::max()),
        max( std::numeric_limits<double>::max()) {}

    Limits(double key_val, double min_val, double max_val)
      : key(key_val), min(min_val), max(max_val) {}

    bool operator<(const Limits& other) const {return key < other.key;}

    double key;
    double min;
    double max;
  };

  /**
   * \param reduction Reduction ratio.
   * \param joint_offset Joint position offset used in the position mappings.
   * \param limits Specification of how one joint position limit changes as a function of another joint's position
   * \pre Nonzero reduction values.
   * \pre limits is sorted by increasing \c Limits.key values.
   */
  HeadTransmission(const std::vector<double>& reduction,
                       const std::vector<double>& joint_offset = std::vector<double>(2, 0.0),
                       const std::vector<Limits>& limits = std::vector<Limits>());

  /**
   * \brief Transform \e effort variables from actuator to joint space.
   * \param[in]  act_data Actuator-space variables.
   * \param[out] jnt_data Joint-space variables.
   * \pre Actuator and joint effort vectors must have size 2 and point to valid data.
   *  To call this method it is not required that all other data vectors contain valid data, and can even remain empty.
   */
  void actuatorToJointEffort(const ActuatorData& act_data,
                                   JointData&    jnt_data);

  /**
   * \brief Transform \e velocity variables from actuator to joint space.
   * \param[in]  act_data Actuator-space variables.
   * \param[out] jnt_data Joint-space variables.
   * \pre Actuator and joint velocity vectors must have size 2 and point to valid data.
   *  To call this method it is not required that all other data vectors contain valid data, and can even remain empty.
   */
  void actuatorToJointVelocity(const ActuatorData& act_data,
                                     JointData&    jnt_data);

  /**
   * \brief Transform \e position variables from actuator to joint space.
   * \param[in]  act_data Actuator-space variables.
   * \param[out] jnt_data Joint-space variables.
   * \pre Actuator and joint position vectors must have size 2 and point to valid data.
   *  To call this method it is not required that all other data vectors contain valid data, and can even remain empty.
   */
  void actuatorToJointPosition(const ActuatorData& act_data,
                                     JointData&    jnt_data);

  /**
   * \brief Transform \e effort variables from joint to actuator space.
   * \param[in]  jnt_data Joint-space variables.
   * \param[out] act_data Actuator-space variables.
   * \pre Actuator and joint effort vectors must have size 2 and point to valid data.
   *  To call this method it is not required that all other data vectors contain valid data, and can even remain empty.
   */
  void jointToActuatorEffort(const JointData&    jnt_data,
                                   ActuatorData& act_data);

  /**
   * \brief Transform \e velocity variables from joint to actuator space.
   * \param[in]  jnt_data Joint-space variables.
   * \param[out] act_data Actuator-space variables.
   * \pre Actuator and joint velocity vectors must have size 2 and point to valid data.
   *  To call this method it is not required that all other data vectors contain valid data, and can even remain empty.
   */
  void jointToActuatorVelocity(const JointData&    jnt_data,
                                     ActuatorData& act_data);

  /**
   * \brief Transform \e position variables from joint to actuator space.
   * \param[in]  jnt_data Joint-space variables.
   * \param[out] act_data Actuator-space variables.
   * \pre Actuator and joint position vectors must have size 2 and point to valid data.
   *  To call this method it is not required that all other data vectors contain valid data, and can even remain empty.
   */
  void jointToActuatorPosition(const JointData&    jnt_data,
                                     ActuatorData& act_data);

  virtual bool hasActuatorToJointAbsolutePosition(){
    return false;
  }

  virtual bool hasActuatorToJointTorqueSensor(){
    return false;
  }

  std::size_t numActuators() const {return 2;}
  std::size_t numJoints()    const {return 2;}

  const std::vector<double>& getActuatorReduction()   const {return reduction_;}
  const std::vector<double>& getJointOffset()         const {return jnt_offset_;}
  const std::vector<Limits>& getLimitsVector()        const {return limits_vec_;}

private:
  std::vector<double> reduction_;
  std::vector<double> jnt_offset_;
  std::vector<Limits> limits_vec_;

  /** \return Value of \b j2 that satisfies joint position limits corresponding to \b j1. */
  double enforceLimits(const double j1, const double j2) const;
  Limits getLimits(const double val) const;
  static double interpolate(const double x1, const double y1,
                            const double x2, const double y2,
                            const double x);
};

inline HeadTransmission::HeadTransmission(const std::vector<double>& reduction,
                                                  const std::vector<double>& joint_offset,
                                                  const std::vector<Limits>& limits)
  : Transmission(),
    reduction_(reduction),
    jnt_offset_(joint_offset),
    limits_vec_(limits)
{
  if (numJoints() != reduction_.size() ||
      numJoints() != reduction_.size() ||
      numJoints() != jnt_offset_.size())
  {
    throw TransmissionInterfaceException("Reduction and offset vectors of a head transmission must have size 2.");
  }

  if (0.0 == reduction_[0] ||
      0.0 == reduction_[1]
  )
  {
    throw TransmissionInterfaceException("Transmission reduction ratios cannot be zero.");
  }
}

inline void HeadTransmission::actuatorToJointEffort(const ActuatorData& act_data,
                                                              JointData&    jnt_data)
{
  assert(numActuators() == act_data.effort.size() && numJoints() == jnt_data.effort.size());
  assert(act_data.effort[0] && act_data.effort[1] && jnt_data.effort[0] && jnt_data.effort[1]);

  *jnt_data.effort[0] = *act_data.effort[0] * reduction_[0];
  *jnt_data.effort[1] = *act_data.effort[1] * reduction_[1];
}

inline void HeadTransmission::actuatorToJointVelocity(const ActuatorData& act_data,
                                                                JointData&    jnt_data)
{
  assert(numActuators() == act_data.velocity.size() && numJoints() == jnt_data.velocity.size());
  assert(act_data.velocity[0] && act_data.velocity[1] && jnt_data.velocity[0] && jnt_data.velocity[1]);

  *jnt_data.velocity[0] = *act_data.velocity[0] / reduction_[0];
  *jnt_data.velocity[1] = *act_data.velocity[1] / reduction_[1];
}

inline void HeadTransmission::actuatorToJointPosition(const ActuatorData& act_data,
                                                                JointData&    jnt_data)
{
  assert(numActuators() == act_data.position.size() && numJoints() == jnt_data.position.size());
  assert(act_data.position[0] && act_data.position[1] && jnt_data.position[0] && jnt_data.position[1]);

  *jnt_data.position[0] = *act_data.position[0] / reduction_[0] + jnt_offset_[0];
  *jnt_data.position[1] = *act_data.position[1] / reduction_[1] + jnt_offset_[1];
}

inline void HeadTransmission::jointToActuatorEffort(const JointData&    jnt_data,
                                                              ActuatorData& act_data)
{
  assert(numActuators() == act_data.effort.size() && numJoints() == jnt_data.effort.size());
  assert(act_data.effort[0] && act_data.effort[1] && jnt_data.effort[0] && jnt_data.effort[1]);

  *act_data.effort[0] = *jnt_data.effort[0] / reduction_[0];
  *act_data.effort[1] = *jnt_data.effort[1] / reduction_[1];
}

inline void HeadTransmission::jointToActuatorVelocity(const JointData&    jnt_data,
                                                                ActuatorData& act_data)
{
  assert(numActuators() == act_data.velocity.size() && numJoints() == jnt_data.velocity.size());
  assert(act_data.velocity[0] && act_data.velocity[1] && jnt_data.velocity[0] && jnt_data.velocity[1]);

  *act_data.velocity[1] = *jnt_data.velocity[1] * reduction_[1];
}

inline void HeadTransmission::jointToActuatorPosition(const JointData&    jnt_data,
                                                                ActuatorData& act_data)
{
  assert(numActuators() == act_data.position.size() && numJoints() == jnt_data.position.size());
  assert(act_data.position[0] && act_data.position[1] && jnt_data.position[0] && jnt_data.position[1]);

  const double clamped_j2 = enforceLimits(*jnt_data.position[0], *jnt_data.position[1]);

  *act_data.position[0] = (*jnt_data.position[0] - jnt_offset_[0]) * reduction_[0];
  *act_data.position[1] = (clamped_j2            - jnt_offset_[1]) * reduction_[1];
}

inline double HeadTransmission::enforceLimits(const double j1, const double j2) const
{
  Limits lim = getLimits(j1);
  return std::max(std::min(j2, lim.max), lim.min); // clamp
}

inline HeadTransmission::Limits HeadTransmission::getLimits(const double val) const
{
  Limits ret;
  ret.key = val;

  if (limits_vec_.empty())
  {
    ret.min = -std::numeric_limits<double>::max();
    ret.max =  std::numeric_limits<double>::max();
    return ret;
  }

  typedef std::vector<Limits>::const_iterator Iterator;
  Iterator it2 = std::upper_bound(limits_vec_.begin(), limits_vec_.end(), ret);
  if (it2 == limits_vec_.begin())
  {
    // Take first
    ret.min = it2->min;
    ret.max = it2->max;
  }
  else if (it2 == limits_vec_.end())
  {
    // Take last
    --it2;
    ret.min = it2->min;
    ret.max = it2->max;
  }
  else
  {
    // General case
    Iterator it1 = it2;
    --it1;
    ret.min = interpolate(it1->key, it1->min,
                          it2->key, it2->min,
                          val);
    ret.max = interpolate(it1->key, it1->max,
                          it2->key, it2->max,
                          val);
  }

  return ret;
}

inline double HeadTransmission::interpolate(const double x1, const double y1,
                                                const double x2, const double y2,
                                                const double x)
{
  return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}

} // namespace

#endif // header guard
