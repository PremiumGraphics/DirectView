#include "gtest/gtest.h"

#include "AVSCell.h"

#include <memory>

using namespace Crystal::IO;

TEST( AVSCellTest, TestToType )
{
	EXPECT_EQ( AVSCell::Point,	AVSCell::toAVSType( "point"	) );
	EXPECT_EQ( AVSCell::Line,	AVSCell::toAVSType( "line"	) );
	EXPECT_EQ( AVSCell::Tri,	AVSCell::toAVSType( "tri"	) );
	EXPECT_EQ( AVSCell::Quad,	AVSCell::toAVSType( "quad"	) );
	EXPECT_EQ( AVSCell::Tet,	AVSCell::toAVSType( "tet"	) );
	EXPECT_EQ( AVSCell::Pyr,	AVSCell::toAVSType( "pyr"	) );
	EXPECT_EQ( AVSCell::Prism,	AVSCell::toAVSType( "prism" ) );
	EXPECT_EQ( AVSCell::Hex,	AVSCell::toAVSType( "hex"	) );
}

TEST( AVSCellTest, TestPoint )
{
	const VertexIndices indices{ 100 };
	std::unique_ptr< AVSCell > cell( AVSCell::create( AVSCell::Type::Point, indices ) );
	EXPECT_EQ( AVSCell::Type::Point, cell->getType() );
	EXPECT_EQ( 1, cell->getConnections().size() );

	const ConnectionVector expected{ { 100 } };
	EXPECT_EQ( expected, cell->getConnections() );
}

TEST( AVSCellTest, TestLine )
{
	const VertexIndices indices{ 100, 200 };
	std::unique_ptr< AVSCell > cell( AVSCell::create( AVSCell::Type::Line, indices ) );
	EXPECT_EQ( AVSCell::Type::Line, cell->getType() );

	const ConnectionVector expected{
		Connection{ 100, 200 }
	};
	EXPECT_EQ( expected, cell->getConnections() );
}

TEST( AVSCellTest, TestTri )
{
	const VertexIndices indices{ 100, 200, 300 };
	std::unique_ptr< AVSCell > cell( AVSCell::create( AVSCell::Type::Tri, indices ) );
	EXPECT_EQ( AVSCell::Type::Tri, cell->getType() );

	const ConnectionVector expected{ Connection{ 100, 200, 300, 100 } };
	EXPECT_EQ( expected, cell->getConnections() );
}

TEST(AVSCellTest, TestQuad)
{
	const VertexIndices indices = { 100, 200, 300, 400 };
	std::unique_ptr< AVSCell > cell(AVSCell::create(AVSCell::Type::Quad, indices));
	EXPECT_EQ(AVSCell::Type::Quad, cell->getType());

	const ConnectionVector& actual = cell->getConnections();
	const ConnectionVector expected{ { 100, 200, 300, 400, 100 } };
	EXPECT_EQ( expected, actual );
}

TEST( AVSCellTest, TestTet )
{
	const VertexIndices indices = { 100, 200, 300, 400 };
	std::unique_ptr< AVSCell > cell( AVSCell::create( AVSCell::Type::Tet, indices ) );
	EXPECT_EQ( AVSCell::Type::Tet, cell->getType() );
	EXPECT_EQ( 4, cell->getConnections().size() );
	//const Connection& expected = build( 100, 200, 300, 100, indices );
	//EXPECT_EQ( expected, cell->getConnections().front() );
}

TEST( AVSCellTest, TestPrism )
{
	const VertexIndices indices{ 100, 200, 300, 400, 500, 600 };

	std::unique_ptr< AVSCell > cell( AVSCell::create( AVSCell::Type::Prism, indices ) );
	EXPECT_EQ( AVSCell::Type::Prism, cell->getType() );
}

TEST( AVSCellTest, TestHex )
{
	const VertexIndices indices = { 100, 200, 300, 400, 500, 600, 700, 800 };

	std::unique_ptr< AVSCell > cell( AVSCell::create( AVSCell::Type::Hex, indices ) );
	EXPECT_EQ( AVSCell::Type::Hex, cell->getType() );
	EXPECT_EQ( 6, cell->getConnections().size() );
}