#include "gtest/gtest.h"

#include "VTKAttribute.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST( VTKAttributeTest, TestMinMax )
{
	VTKAttributes attributes;
	attributes.setValues({ 0.0, 50.0, 100.0 });
	EXPECT_EQ( 0.0, attributes.getMin() );
	EXPECT_EQ( 100.0, attributes.getMax() );
}

TEST( VTKAttributes, TestToDimensionalArray )
{
	VTKAttributes attributes;
	attributes.setValues( { 0.0, 50.0, 100.0, 200.0 } );

	const std::vector< std::vector<float> >& arrays1 = attributes.toDimensionalArrays( 1 );
	EXPECT_EQ( arrays1.size(), 4 );
	
	const std::vector< std::vector<float> >& arrays2 = attributes.toDimensionalArrays( 2 );
	EXPECT_EQ( arrays2.size(), 2 );
}

TEST( VTKAttributes, TestTo3dVectorsBy2Dim )
{
	VTKAttributes attributes;
	attributes.setValues({ 0.0, 100.0, 200.0, 300.0, 400.0, 500.0 });
	attributes.setDim( 2 );

	const std::vector< Vector3d >& vectors = attributes.toVector3ds();
	EXPECT_EQ( vectors.size(), 3 );
}


TEST( VTKAttributes, TestTo3dVectorsBy3Dim )
{
	VTKAttributes attributes;
	attributes.setValues({ 0.0, 100.0, 200.0, 300.0, 400.0, 500.0 });
	attributes.setDim( 3 );

	const std::vector< Vector3d >& vectors = attributes.toVector3ds();
	EXPECT_EQ( vectors.size(), 2 );
	EXPECT_EQ( Vector3d(   0.0, 100.0, 200.0 ), vectors.front() );
	EXPECT_EQ( Vector3d( 300.0, 400.0, 500.0 ), vectors.back() );
}

TEST( VTKAttributes, TestTo3dVectorsBy4Dim )
{
	VTKAttributes attributes;
	attributes.setValues({ 0.0, 100.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0 } );
	attributes.setDim( 4 );

	const std::vector< Vector3d >& vectors = attributes.toVector3ds();
	EXPECT_EQ( vectors.size(), 2 );
	EXPECT_EQ( Vector3d( 0.0, 100.0, 200.0 ), vectors.front() );
	EXPECT_EQ( Vector3d( 400.0, 500.0, 600.0 ), vectors.back() );
}
