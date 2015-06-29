#include "gtest/gtest.h"
 
#include "../Graphics/Camera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST( CameraTest, TestGetConstruct )
{
	Camera<T> c;
	EXPECT_EQ(c.getNear(), 1.0f );// == Color::Black() );
	EXPECT_EQ(c.getFar(), 10.0f);
	EXPECT_EQ(Vector3d<T>(0, 0, 0), c.getPos());
}

TEST( CameraTest, TestMove )
{
	Camera<float> c;
	c.move(Vector3d<T>(1.0f, 0.0f, 0.0f));

	EXPECT_EQ(Vector3d<T>(1.0f, 0.0f, 0.0f), c.getPos() );
}

TEST(CameraTest, TestGetRotationMatrix)
{
	{
		Camera<float> c;
		const auto& expected = Matrix3d<float>::Identity();
		const auto& actual = c.getRotationMatrix();
		EXPECT_EQ(expected, actual);
	}
	{
		Camera<float> c;
		c.setAngle(Vector3d<float>(Tolerance<float>::getHalfPI(), 0.0, 0.0));
		const auto& actual = c.getRotationMatrix();
	}
}


TEST( CameraTest, TestGetPerspectiveMatrix )
{
	const Camera<float> c;
	const Matrix4d<float>& m = c.getPerspectiveMatrix();
	{
		const T expected = T(2) / ( c.getRight() - c.getLeft() );
		EXPECT_EQ( expected, m.getX00() );
		EXPECT_EQ( 0.0, m.getX01() );
		EXPECT_EQ( 0.0, m.getX02() );
		EXPECT_EQ( 0.0, m.getX03() );
	}

	{
		const T expected = T(2) / ( c.getTop() - c.getBottom() );
		EXPECT_EQ( 0.0, m.getX10() );
		EXPECT_EQ( expected, m.getX11() );
		EXPECT_EQ( 0.0, m.getX12() );
		EXPECT_EQ( 0.0, m.getX13() );
	}

	/*
	{
		EXPECT_EQ(  0.0, m.getX30() );
		EXPECT_EQ(  0.0, m.getX31() );
		//EXPECT_EQ( -1.0, m.getX32() );
		//EXPECT_EQ(  0.0, m.getX33() );
	}
	*/
}