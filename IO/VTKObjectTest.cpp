#include "gtest/gtest.h"
#include "VTKObject.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

TEST( VTKObjectTest, TestContruct )
{
	VTKObject object(0);
	EXPECT_EQ( 0, object.getId() );
}

TEST( VTKObjectTest, TestColorMap )
{
	VTKObject object(0);
	ColorRGBAMap<float>* colorMap = new ColorRGBAMap<float>();
	colorMap->setName( "default" );
	object.addColorMap( colorMap );
	ColorRGBAMap<float>* actual = object.getColorMap( "default" );
	EXPECT_EQ( colorMap, actual );
}

TEST( VTKObjectTest, TestBoundingBox )
{
	VTKObject object(0);
	Vector3dVector vertices;
	vertices.push_back( Vector3d( -1.0, -10.0, -100.0 ) );
	vertices.push_back( Vector3d(  1.0,  10.0,  100.0 ) );
	object.setVertices( vertices );
	EXPECT_EQ( object.getBoundingBox(), Box( Vector3d( -1.0, -10.0, -100.0 ), Vector3d( 1.0, 10.0, 100.0 ) ) );
}