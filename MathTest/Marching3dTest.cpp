#include "gtest/gtest.h"

#include "../Math/Marching3d.h"

using namespace Crystal::Math;

TEST(Marching3dTest, Test)
{
	Marching3d<float> m;
	const auto table = m.getTriTable();
	EXPECT_EQ( 16, table.size());
	EXPECT_EQ(0, table[0].size());
	EXPECT_EQ(1, table[1].size());
	EXPECT_EQ(2, table[2].size());
	EXPECT_EQ(2, table[3].size());
	EXPECT_EQ(3, table[4].size());
	EXPECT_EQ(2, table[5].size());
	EXPECT_EQ(4, table[6].size());
	EXPECT_EQ(4, table[7].size());
	EXPECT_EQ(4, table[8].size());
	EXPECT_EQ(4, table[9].size());
	EXPECT_EQ(2, table[10].size());
	EXPECT_EQ(3, table[11].size());
	EXPECT_EQ(3, table[12].size());
	EXPECT_EQ(4, table[13].size());
	EXPECT_EQ(4, table[14].size());

	EXPECT_EQ(Vector3d_<float>::UnitXYZ(), table[1].front().getNormal());
	EXPECT_EQ(Vector3d_<float>::UnitYZ(), table[2].front().getNormal());
	EXPECT_EQ(Vector3d_<float>::UnitYZ(), table[2].back().getNormal());
	EXPECT_EQ(Vector3d_<float>::UnitXYZ(), table[3].front().getNormal());
	EXPECT_EQ(Vector3d_<float>(-1, -1, 1).getNormalized(), table[3].back().getNormal() );

	EXPECT_EQ(Vector3d_<float>::UnitY(), table[5][0].getNormal());
	EXPECT_EQ(Vector3d_<float>::UnitY(), table[5][1].getNormal());

	EXPECT_EQ(Vector3d_<float>(1, -1, 1).getNormalized(), table[6][0].getNormal() );

	EXPECT_EQ(Vector3d_<float>::UnitXYZ(), table[10][0].getNormal());
	EXPECT_EQ(-1.0 *Vector3d_<float>::UnitXYZ(), table[10][1].getNormal());

	EXPECT_EQ(Vector3d_<float>(1.0, -1.0, 1.0).getNormalized(), table[12][0].getNormal());

	EXPECT_EQ(Vector3d_<float>::UnitXZ(), table[13][0].getNormal());
	EXPECT_EQ(Vector3d_<float>::UnitXZ(), table[13][1].getNormal());
	EXPECT_EQ(-1.0 * Vector3d_<float>::UnitXZ(), table[13][2].getNormal());
	EXPECT_EQ(-1.0 * Vector3d_<float>::UnitXZ(), table[13][3].getNormal());


}