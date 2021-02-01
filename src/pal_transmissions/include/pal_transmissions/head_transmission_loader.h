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

#ifndef TRANSMISSIONS_HEAD__TRANSMISSION_LOADER_H
#define TRANSMISSIONS_HEAD__TRANSMISSION_LOADER_H

// C++ standard
#include <string>

// ros_control
#include <transmission_interface/transmission_loader.h>

// Current package
#include <pal_transmissions/head_transmission.h>

namespace pal_transmissions
{

/**
 * \brief Class for loading a simple transmission instance from configuration data.
 */
class HeadTransmissionLoader : public transmission_interface::TransmissionLoader
{
public:
  typedef transmission_interface::TransmissionLoader::TransmissionPtr TransmissionPtr;
  typedef transmission_interface::TransmissionInfo TransmissionInfo;

  TransmissionPtr load(const TransmissionInfo& transmission_info);

private:
  typedef std::vector<HeadTransmission::Limits> LimitsVec;

  static bool getActuatorConfig(const TransmissionInfo& transmission_info,
                                std::vector<double>&    actuator_reduction);

  static bool getJointConfig(const TransmissionInfo& transmission_info,
                             std::vector<double>&    joint_offset,
                             LimitsVec&              limits_vec);

  static ParseStatus parseJointValue(const TiXmlElement& joint_el,
                                     const std::string&  value_name,
                                     const std::string&  joint_name,
                                     const std::string&  transmission_name,
                                     double&             value);

  static ParseStatus parseLimits(const TiXmlElement& joint_el,
                                 const std::string&  joint_name,
                                 const std::string&  transmission_name,
                                 LimitsVec&          limits_vec);
};

} // namespace

#endif // header guard
