#include "gtest/gtest.h"

#include "VolumeModel.h"

using namespace Crystal::Math;
using namespace Crystal::Model;

TEST(VolumeModelTest, TestCreate)
{
	VolumeModel<float> model;
	const VolumeConfig<float> config(5, 5, 5, Space3d<float>( Vector3d<float>(0,0,0), Vector3d<float>(1,1,1) ) );
	model.setConfig(config);
	const auto& ss = model.create();
	EXPECT_EQ(0, ss->getId());
}