#include "gtest/gtest.h"
 
#include "../Graphics/Camera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST( CameraTest, ContructTest )
{
	Camera<float> c;
	EXPECT_TRUE( c.getNear() == 0.01f );// == Color::Black() );
}

TEST( CameraTest, MoveTest )
{
	Camera<float> c;
	c.move( Vector3d<T>( 1.0f, 0.0f, 0.0f ) );
	EXPECT_EQ( c.getPos(), Vector3d<T>( 1.0f, 0.0f, 0.0f ) );
}

TEST( CameraTest, PerspectiveTest )
{
	Camera<float> c;
	const Matrix4d<float>& m = c.getPerspectiveMatrix();
	{
		const float expected = 2.0 / ( c.getRight() - c.getLeft() );
		EXPECT_EQ( expected, m.getX00() );
		EXPECT_EQ( 0.0, m.getX01() );
		EXPECT_EQ( 0.0, m.getX02() );
		EXPECT_EQ( 0.0, m.getX03() );
	}

	{
		const float expected = 2.0 / ( c.getTop() - c.getBottom() );
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