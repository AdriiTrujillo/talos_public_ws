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

#include <limits>
#include <string>
#include <boost/foreach.hpp>
#include <gtest/gtest.h>
#include <pluginlib/class_loader.h>
#include <pal_transmissions/head_transmission.h>
#include <transmission_interface/transmission_loader.h>
#include "read_file.h"
#include "loader_utils.h"

using namespace transmission_interface;
using namespace pal_transmissions;
typedef TransmissionLoader::TransmissionPtr TransmissionPtr;


TEST(HeadTransmissionLoaderTest, fullSpec)
{
  // Parse transmission info
  std::vector<TransmissionInfo> infos = parseUrdf("test/urdf/head_transmission_loader_full.urdf");
  ASSERT_EQ(1, infos.size());

  // Transmission loader
  TransmissionPluginLoader loader;
  boost::shared_ptr<TransmissionLoader> transmission_loader = loader.create(infos.front().type_);
  ASSERT_TRUE(0 != transmission_loader);

  TransmissionPtr transmission;
  const TransmissionInfo& info = infos.front();
  transmission = transmission_loader->load(info);
  ASSERT_TRUE(0 != transmission);

  // Validate transmission
  HeadTransmission* tran = dynamic_cast<HeadTransmission*>(transmission.get());
  ASSERT_TRUE(0 != tran);

  const std::vector<double>& actuator_reduction = tran->getActuatorReduction();
  EXPECT_EQ(2.0, actuator_reduction[0]);
  EXPECT_EQ(4.0, actuator_reduction[1]);

  const std::vector<double>& joint_offset = tran->getJointOffset();
  EXPECT_EQ( 1.0, joint_offset[0]);
  EXPECT_EQ(-1.0, joint_offset[1]);

  const double max_d = std::numeric_limits<double>::max();
  const double min_d = -max_d;
  const std::vector<HeadTransmission::Limits>& limits_vec = tran->getLimitsVector();
  ASSERT_EQ(7, limits_vec.size());

  EXPECT_EQ( -3.0, limits_vec[0].key);
  EXPECT_EQ(min_d, limits_vec[0].min);
  EXPECT_EQ(  0.0, limits_vec[0].max);

  EXPECT_EQ( -2.0, limits_vec[1].key);
  EXPECT_EQ(  0.0, limits_vec[1].min);
  EXPECT_EQ(  0.0, limits_vec[1].max);

  EXPECT_EQ( -1.0, limits_vec[2].key);
  EXPECT_EQ( -1.0, limits_vec[2].min);
  EXPECT_EQ(  1.0, limits_vec[2].max);

  EXPECT_EQ(  1.0, limits_vec[3].key);
  EXPECT_EQ( -2.0, limits_vec[3].min);
  EXPECT_EQ(  2.0, limits_vec[3].max);

  EXPECT_EQ(  2.0, limits_vec[4].key);
  EXPECT_EQ(  0.0, limits_vec[4].min);
  EXPECT_EQ(  0.0, limits_vec[4].max);

  EXPECT_EQ(  3.0, limits_vec[5].key);
  EXPECT_EQ(  0.0, limits_vec[5].min);
  EXPECT_EQ(max_d, limits_vec[5].max);

  EXPECT_EQ(  4.0, limits_vec[6].key);
  EXPECT_EQ(min_d, limits_vec[6].min);
  EXPECT_EQ(max_d, limits_vec[6].max);
}

TEST(HeadTransmissionLoaderTest, minimalSpec)
{
  // Parse transmission info
  std::vector<TransmissionInfo> infos = parseUrdf("test/urdf/head_transmission_loader_minimal.urdf");
  ASSERT_EQ(1, infos.size());

  // Transmission loader
  TransmissionPluginLoader loader;
  boost::shared_ptr<TransmissionLoader> transmission_loader = loader.create(infos.front().type_);
  ASSERT_TRUE(0 != transmission_loader);

  TransmissionPtr transmission;
  const TransmissionInfo& info = infos.front();
  transmission = transmission_loader->load(info);
  ASSERT_TRUE(0 != transmission);

  // Validate transmission
  HeadTransmission* tran = dynamic_cast<HeadTransmission*>(transmission.get());
  ASSERT_TRUE(0 != tran);
  const std::vector<double>& actuator_reduction = tran->getActuatorReduction();
  EXPECT_EQ(2.0, actuator_reduction[0]);
  EXPECT_EQ(4.0, actuator_reduction[1]);

  const std::vector<double>& joint_offset = tran->getJointOffset();
  EXPECT_EQ(0.0, joint_offset[0]);
  EXPECT_EQ(0.0, joint_offset[1]);

  EXPECT_TRUE(tran->getLimitsVector().empty());
}

TEST(HeadTransmissionLoaderTest, flippedSpec)
{
  // Parse transmission info
  std::vector<TransmissionInfo> infos = parseUrdf("test/urdf/head_transmission_loader_full_flipped.urdf");
  ASSERT_EQ(1, infos.size());

  // Transmission loader
  TransmissionPluginLoader loader;
  boost::shared_ptr<TransmissionLoader> transmission_loader = loader.create(infos.front().type_);
  ASSERT_TRUE(0 != transmission_loader);

  TransmissionPtr transmission;
  const TransmissionInfo& info = infos.front();
  transmission = transmission_loader->load(info);
  ASSERT_TRUE(0 != transmission);

  // Validate transmission
  HeadTransmission* tran = dynamic_cast<HeadTransmission*>(transmission.get());
  ASSERT_TRUE(0 != tran);
  const std::vector<double>& actuator_reduction = tran->getActuatorReduction();
  EXPECT_EQ(2.0, actuator_reduction[0]);
  EXPECT_EQ(4.0, actuator_reduction[1]);

  const std::vector<double>& joint_offset = tran->getJointOffset();
  EXPECT_EQ( 1.0, joint_offset[0]);
  EXPECT_EQ(-1.0, joint_offset[1]);

  EXPECT_EQ(7, tran->getLimitsVector().size());
}

TEST(HeadTransmissionLoaderTest, invalidSpec)
{
  // Parse transmission info
  std::vector<TransmissionInfo> infos = parseUrdf("test/urdf/head_transmission_loader_invalid.urdf");
  ASSERT_EQ(16, infos.size());

  // Transmission loader
  TransmissionPluginLoader loader;
  boost::shared_ptr<TransmissionLoader> transmission_loader = loader.create(infos.front().type_);
  ASSERT_TRUE(0 != transmission_loader);

  BOOST_FOREACH(const TransmissionInfo& info, infos)
  {
    TransmissionPtr transmission;
    transmission = transmission_loader->load(info);
    ASSERT_TRUE(0 == transmission);
  }
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
