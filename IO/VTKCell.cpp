#include "VTKCell.h"

#include <cassert>

using namespace Crystal::IO;

VTKCell* VTKCell::create( const int id, const VertexIndices& indices )
{
	switch( id ) {
	case VTKCellType::VERTEX :
		{
			return new VTKVertex( indices );
		}
	case VTKCellType::POLY_VERTEX :
		{
			return new VTKPolyVertex( indices );
		}
	case VTKCellType::LINE :
		{
			return new VTKLine( indices );
		}
	case VTKCellType::POLY_LINE :
		{
			return new VTKPolyLine( indices );
		}
	case VTKCellType::TRIANGLE :
		{
			return new VTKTriangle( indices );
		}
	case VTKCellType::TRIANGLE_STRIP :
		{
			return new VTKTriangleStrip( indices );
		}
	case VTKCellType::POLYGON :
		{
			return new VTKPolygon( indices );
		}
	case VTKCellType::PIXEL:
		{
			return new VTKPixel( indices );
		}
	case VTKCellType::QUAD:
		{
			return new VTKQuad( indices );
		}
	case VTKCellType::TETRA:
		{
			return new VTKTetra( indices );
		}
	case VTKCellType::VOXEL:
		{
			return new VTKVoxel( indices );
		}
	case VTKCellType::HEXAHEDRON :
		{
			return new VTKHexahedron( indices );
		}
	case VTKCellType::WEDGE :
		{
			return new VTKWedge( indices );
		}
	case VTKCellType::PYRAMID :
		{
			return new VTKPyramid( indices );
		}
	default:
		{
			assert( false );
			return nullptr;
		}
	}
}

VTKVertex::VTKVertex( const VertexIndices& indices )
{
	assert( indices.size() == 1 );
	Connection c;
	c.push_back( indices[0] );
	connections.push_back( c );
}


VTKPolyVertex::VTKPolyVertex( const VertexIndices& indices )
{
	assert( !indices.empty() );

	Connection cone;
	for( size_t i = 0; i < indices.size(); ++i ) {
		cone.push_back( indices[i] );
	}
	connections.push_back( cone );

}


VTKLine::VTKLine(const VertexIndices& indices)
{
	assert(indices.size() == 2);

	Connection c = build(std::vector < unsigned int > { 0, 1 }, indices);
	connections.push_back( c );
}

VTKPolyLine::VTKPolyLine( const VertexIndices& indices )
{
	Connection connection;
	for( size_t i = 0; i < indices.size(); ++i ) {
		connection.push_back( indices[i] );
	}
	connections.push_back( connection );
}

VTKTriangle::VTKTriangle(const VertexIndices& indices)
{
	const Connection c = build(std::vector < unsigned int > { 0, 1, 2, 0 }, indices);
	connections.push_back( c );
}

VTKTriangleStrip::VTKTriangleStrip( const VertexIndices& indices )
{
	for( size_t i = 0; i < indices.size() -3; i+=3 ) {
		const Connection c1 = build( { i+0, i+2, i+1, i+0 }, indices );
		connections.push_back( c1 );
		//connections.push_back( VTKConnection( i+0, i+2, i+1, i+0 ) );
		const Connection c2 = build({ i+1, i+2, i+3, i+1 }, indices );
		connections.push_back( c2 );
		//connections.push_back( VTKConnection( i+1, i+2, i+3, i+1 ) );
	}
}

VTKPolygon::VTKPolygon( const VertexIndices& indices )
{
	assert( indices.size() >= 3 );

	Connection connection;
	for( size_t i = 0; i < indices.size(); ++i ) {
		connection.push_back( indices[i] );
	}
	connection.push_back( indices[0] );
	connections.push_back( connection );
}

VTKPixel::VTKPixel( const VertexIndices& indices )
{
	assert( indices.size() == 4 );
	connections.push_back( build(std::vector < unsigned int > {0, 1, 3, 2, 0 }, indices) );
}


VTKQuad::VTKQuad( const VertexIndices& indices )
{
	assert( indices.size() == 4 );
	connections.push_back( build(std::vector < unsigned int > { 0, 1, 2, 3, 0 }, indices) );
}

VTKTetra::VTKTetra( const VertexIndices& indices )
{
	assert( indices.size() == 4 );

	connections.push_back( build( std::vector < unsigned int > { 3, 0, 1, 3 }, indices) );
	connections.push_back( build( std::vector < unsigned int > { 0, 1, 2, 0 }, indices) );
	connections.push_back( build( std::vector < unsigned int > { 3, 1, 2, 3 }, indices) );
	connections.push_back( build( std::vector < unsigned int > { 3, 2, 0, 3 }, indices) );
}

VTKVoxel::VTKVoxel( const VertexIndices& indices )
{
	assert( indices.size() == 8 );

	connections.push_back( build( std::vector < unsigned int > { 4, 0, 1, 5, 4}, indices) );
	connections.push_back( build( std::vector < unsigned int > { 5, 1, 3, 7, 5}, indices) );
	connections.push_back( build( std::vector < unsigned int > { 7, 3, 2, 6, 7}, indices) );
	connections.push_back( build( std::vector < unsigned int > { 6, 2, 0, 4, 6}, indices) );
	connections.push_back( build( std::vector < unsigned int > { 6, 4, 5, 7, 6}, indices) );
	connections.push_back( build( std::vector < unsigned int > { 0, 1, 2, 3, 0}, indices) );
}

VTKHexahedron::VTKHexahedron( const VertexIndices& indices )
{
	assert( indices.size() == 8 );

	connections.push_back( build(std::vector < unsigned int > { 0, 1, 5, 4, 0}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 0, 1, 2, 3, 0}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 5, 1, 2, 6, 5}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 6, 2, 3, 7, 6}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 7, 3, 0, 4, 7}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 7, 4, 5, 6, 7}, indices) );
}


VTKWedge::VTKWedge( const VertexIndices& indices )
{
	assert( indices.size() == 6 );

	connections.push_back( build(std::vector < unsigned int > { 0, 1, 2, 0}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 3, 4, 5, 3}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 5, 3, 0, 2, 5}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 2, 1, 4, 5, 2}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 0, 1, 4, 3, 0}, indices) );
}

VTKPyramid::VTKPyramid( const VertexIndices& indices )
{
	assert( indices.size() == 5 );

	connections.push_back( build(std::vector < unsigned int > { 0, 1, 2, 3, 0 }, indices) );
	connections.push_back( build(std::vector < unsigned int > { 4, 0, 1, 4}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 4, 1, 2, 4}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 4, 2, 3, 4}, indices) );
	connections.push_back( build(std::vector < unsigned int > { 4, 3, 0, 4}, indices) );
}
