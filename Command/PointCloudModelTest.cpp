#include "gtest/gtest.h"

#include "PointCloudModel.h"

using namespace Crystal::Graphics;
using namespace Crystal::Model;

TEST(PointCloudObjectTest, Test)
{
	using T = float;
	PointCloudSPtr<T> pointCloud = std::make_shared < PointCloud<T> >();
	PointCloudObject<T> object(pointCloud, 10);
	EXPECT_EQ(10, object.getId());
	EXPECT_EQ(Object::Type::PointCloud, object.getType());
}