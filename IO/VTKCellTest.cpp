#include "gtest/gtest.h"

#include "VTKCell.h"

#include <memory>

using namespace Crystal::IO;

TEST( VTKCellTest, TestVertex )
{
	const VertexIndices indices = { 10 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 1, indices ) );
	EXPECT_EQ( VTKCellType::VERTEX, cell->getType() );

	const ConnectionVector& connected = cell->getConnections();
	EXPECT_EQ( 1, connected.size() );
	EXPECT_EQ( 10, connected.front()[0] );
}

TEST( VTKCellTest, TestPolyVertex )
{
	const VertexIndices indices = { 10, 20 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 2, indices ) );
	EXPECT_EQ( VTKCellType::POLY_VERTEX, cell->getType() );

	const ConnectionVector& actual = cell->getConnections();
	const ConnectionVector expected{ { 10, 20 } };
	EXPECT_EQ( expected, actual );
}

TEST( VTKCellTest, TestLine )
{
	const VertexIndices indices = { 10, 20 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 3, indices ) );
	EXPECT_EQ( VTKCellType::LINE, cell->getType() );

	const ConnectionVector expected = { { 10, 20 } };
	const ConnectionVector& actual = cell->getConnections();
	EXPECT_EQ( expected, actual );
}

TEST( VTKCellTest, TestCreatePolyLine )
{
	const VertexIndices indices = { 10, 20 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 4,indices ) );
	EXPECT_EQ( cell->getType(), VTKCellType::POLY_LINE );

	const ConnectionVector& connected = cell->getConnections();
	EXPECT_EQ( 1, connected.size() );
	EXPECT_EQ( 2, connected.front().size() );
	EXPECT_EQ( 10, connected.front()[0] );
	EXPECT_EQ( 20, connected.front()[1] );
}

TEST( VTKCellTest, TestTriangle )
{
	const VertexIndices indices = { 10, 20, 30 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 5, indices ) );
	EXPECT_EQ( VTKCellType::TRIANGLE, cell->getType() );

	const ConnectionVector expected = { { 10, 20, 30, 10 } };
	const ConnectionVector& actual = cell->getConnections();
	EXPECT_EQ( expected, actual );
}


TEST( VTKCellTest, TestTriangleStrip )
{
	const VertexIndices indices = { 10, 20, 30, 40 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 6, indices ) );
	EXPECT_EQ( VTKCellType::TRIANGLE_STRIP, cell->getType() );

	const ConnectionVector& connected = cell->getConnections();
	EXPECT_EQ( 2, connected.size() );

	//const Connection expected = build( 10, 30, 20, 10, indices );
	EXPECT_EQ( 10, connected.front()[0] );

}

TEST( VTKCellTest, TestCreatePolygon )
{
	const VertexIndices indices = { 10, 20, 30 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 7, indices ) );
	EXPECT_EQ( VTKCellType::POLYGON, cell->getType() );

	const ConnectionVector& actual = cell->getConnections();
	const ConnectionVector& expected{ { 10, 20, 30, 10 } };
	EXPECT_EQ( expected, actual );
}

TEST( VTKCellTest, TestPixel )
{
	const VertexIndices indices = { 100, 110, 120, 130 };

	std::unique_ptr< VTKCell > cell( VTKCell::create( 8, indices ) );
	EXPECT_EQ( VTKCellType::PIXEL, cell->getType() );

	const ConnectionVector& connected = cell->getConnections();
	EXPECT_EQ( 1, connected.size() );

	const VertexIndices expected = { 100, 110, 130, 120, 100 };
	EXPECT_EQ( expected, connected.front() );
}

TEST( VTKCellTest, TestQuad )
{
	const VertexIndices indices = { 0, 1, 2, 3 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 9, indices ) );
	EXPECT_EQ( VTKCellType::QUAD, cell->getType() );
	const ConnectionVector& connected = cell->getConnections();
	EXPECT_EQ( 1, connected.size() );
}

TEST( VTKCellTest, TestTetra )
{
	const VertexIndices indices = { 0, 1, 2, 3 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 10, indices ) );
	EXPECT_EQ( VTKCellType::TETRA, cell->getType() );
}

TEST( VTKCellTest, TestVoxel )
{
	const VertexIndices indices = { 0, 1, 2, 3, 4, 5, 6, 7 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 11, indices ) );
	EXPECT_EQ( VTKCellType::VOXEL, cell->getType() );
}

TEST( VTKCellTest, TestHexahedron )
{
	const VertexIndices indices = { 0, 1, 2, 3, 4, 5, 6, 7 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 12, indices ) );
	EXPECT_EQ( VTKCellType::HEXAHEDRON, cell->getType() );
}

TEST( VTKCellTest, TestWedge )
{
	const VertexIndices indices = { 0, 1, 2, 3, 4, 5 };
	std::unique_ptr< VTKCell > cell( VTKCell::create( 13, indices ) );
	EXPECT_EQ( VTKCellType::WEDGE, cell->getType() );
}

TEST(VTKCellTest, TestPyramid)
{
	const VertexIndices indices = { 100, 110, 120, 130, 140 };
	std::unique_ptr< VTKCell > cell(VTKCell::create(14, indices));
	EXPECT_EQ(VTKCellType::PYRAMID, cell->getType());
}