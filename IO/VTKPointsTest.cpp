#include "gtest/gtest.h"

#include "VTKPoints.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST( VTKPointsTest, Test )
{
	std::stringstream stream;
	stream
		<< "POINTS"	<< std::endl
		<< "3 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl;
	VTKPoints points;
	points.read( stream );

	EXPECT_EQ( "float", points.getType().toString() );

	EXPECT_EQ( 3, points.getPoints().size() );
	EXPECT_EQ( Vector3d( 0.0, 0.0, 0.0 ), points.getPoints().front() );
	EXPECT_EQ( Vector3d( 1.0, 1.0, 0.0 ), points.getPoints().back() );
}
