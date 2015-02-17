#ifndef __CRYSTAL_IO_AVS_CELL_H__
#define __CRYSTAL_IO_AVS_CELL_H__

#include <string>
#include <vector>
#include <cassert>

#include "VTKConnection.h"

#include <cassert>


namespace Crystal {
	namespace IO {


class AVSCell
{
public:
	enum Type {
		None,
		Point,
		Line,
		Tri,
		Quad,
		Tet,
		Pyr,
		Prism,
		Hex,
		Line2,
		Tri2,
		Quad2,
		Tet2,
		Pyr2,
		Prism2,
		Hex2,
	};

	
	static Type toAVSType(const std::string& str);

	AVSCell()
	{}

	virtual ~AVSCell(){};

	static AVSCell* create( const Type& type, const VertexIndices& indices );
	
	int getId() const { return id; }

	virtual Type getType() const = 0;

	ConnectionVector getConnections() const { return connections; }

	void setIndices( const std::vector< unsigned int >& indices ) { this->indices = indices; }

	std::vector< unsigned int > getIndices() const { return indices; }


private:
	int id;

protected:
	std::vector< unsigned int > indices;
	ConnectionVector connections;
};


typedef std::vector< AVSCell* > AVSCellVector;

class AVSPoint : public AVSCell
{
public:
	AVSPoint(const VertexIndices& indices)
	{
		assert( indices.size() == 1 );
		connections.push_back(build(std::vector < unsigned int > {0}, indices));
		this->indices = indices;
	}


	virtual Type getType() const{ return Type::Point; }
};

class AVSLine : public AVSCell
{
public:
	AVSLine(const VertexIndices& indices)
	{
		assert( indices.size() == 2 );
		connections.push_back(build(std::vector < unsigned int > {0, 1 }, indices));
		this->indices = indices;
	};

	virtual Type getType() const{ return Type::Line; }
};

class AVSTri : public AVSCell
{
public:
	AVSTri(const VertexIndices& indices)
	{
		assert( indices.size() == 3 );
		connections.push_back(build(std::vector < unsigned int > { 0, 1, 2, 0 }, indices));
		//connections.push_back( VTKConnection( 1, 2, 3, 1 ) );
		this->indices = indices;

	};

	virtual Type getType() const{ return Type::Tri; }
};

class AVSQuad : public AVSCell
{
public:
	AVSQuad(const VertexIndices& indices)
	{
		assert( indices.size() == 4 );
		connections.push_back( build( std::vector < unsigned int > {0, 1, 2, 3, 0 }, indices));
		this->indices = indices;
	}

	virtual Type getType() const{ return Type::Quad; }
};

class AVSTet : public AVSCell
{
public:
	AVSTet(const VertexIndices& indices)
	{
		assert( indices.size() == 4 );
		connections.push_back( build( std::vector < unsigned int > { 0, 1, 2, 0 }, indices));
		connections.push_back( build( std::vector < unsigned int > { 0, 2, 3, 0 }, indices));
		connections.push_back( build( std::vector < unsigned int > { 0, 3, 1, 0 }, indices));
		connections.push_back( build( std::vector < unsigned int > { 2, 1, 3, 2 }, indices));
		//connections.push_back( VTKConnection( 3, 2, 4, 3 ) );
		this->indices = indices;

	}

	virtual Type getType() const{ return Type::Tet; }
};

class AVSPyr: public AVSCell
{
public:
	AVSPyr(const VertexIndices& indices)
	{
		assert( indices.size() == 5 );
		/*
		connections.push_back( VTKConnection( 1, 2, 5, 1 ) );
		connections.push_back( VTKConnection( 1, 5, 4, 1 ) );
		connections.push_back( VTKConnection( 1, 4, 3, 1 ) );
		connections.push_back( VTKConnection( 1, 3, 2, 1 ) );
		connections.push_back( VTKConnection( 2, 3, 4, 5, 2 ) );
		*/
		connections.push_back( build( std::vector < unsigned int > { 0, 1, 4, 0 }, indices));
		connections.push_back( build( std::vector < unsigned int > { 0, 4, 3, 0 }, indices));
		connections.push_back( build( std::vector < unsigned int > { 0, 3, 2, 0 }, indices));
		connections.push_back( build( std::vector < unsigned int > { 0, 2, 1, 0 }, indices));
		connections.push_back( build( std::vector < unsigned int > { 1, 2, 3, 4, 1 }, indices));
				this->indices = indices;

	}

	virtual Type getType() const{ return Type::Pyr; }
};

class AVSPrism : public AVSCell
{
public:
	AVSPrism(const VertexIndices& indices)
	{
		assert( indices.size() == 6 );
		connections.push_back( build( std::vector < unsigned int > {0, 1, 4, 3, 0 }, indices));
		connections.push_back( build( std::vector < unsigned int > {4, 1, 2, 5, 4 }, indices));
		connections.push_back( build( std::vector < unsigned int > {5, 2, 0, 3, 5}, indices));
		connections.push_back( build( std::vector < unsigned int > {5, 3, 4, 5 }, indices));
		connections.push_back( build( std::vector < unsigned int > {2, 0, 1, 2 }, indices));
		this->indices = indices;
	}

	virtual Type getType() const{ return Type::Prism; }
};

class AVSHex : public AVSCell
{
public:
	AVSHex(const VertexIndices& indices)
	{
		assert( indices.size() == 8 );
		/*
		connections.push_back( VTKConnection( 1, 2, 3, 4, 1 ) );
		connections.push_back( VTKConnection( 5, 6, 7, 8, 5 ) );
		connections.push_back( VTKConnection( 1, 2, 6, 5, 1 ) );
		connections.push_back( VTKConnection( 6, 2, 3, 7, 6 ) );
		connections.push_back( VTKConnection( 7, 3, 4, 8, 7 ) );
		connections.push_back( VTKConnection( 8, 4, 1, 5, 8 ) );
		*/
		connections.push_back( build( std::vector < unsigned int > { 0, 1, 2, 3, 0 }, indices));
		connections.push_back( build( std::vector < unsigned int > {4, 5, 6, 7, 4 }, indices));
		connections.push_back( build( std::vector < unsigned int > {0, 1, 5, 4, 0}, indices));
		connections.push_back( build( std::vector < unsigned int > { 5, 1, 2, 6, 5}, indices));
		connections.push_back( build( std::vector < unsigned int > {6, 2, 3, 7, 6}, indices));
		connections.push_back( build( std::vector < unsigned int > {7, 3, 0, 4, 7}, indices));
		this->indices = indices;

	}

	virtual Type getType() const{ return Type::Hex; }
};

	}
}

#endif