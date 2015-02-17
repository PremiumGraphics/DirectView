#ifndef __CRYSTAL_IO_VTK_CELL_H__
#define __CRYSTAL_IO_VTK_CELL_H__

#include <vector>
#include <cassert>

#include "VTKConnection.h"

namespace Crystal {
	namespace IO {

enum VTKCellType {
	NONE = 0,
	VERTEX = 1,
	POLY_VERTEX = 2,
	LINE = 3,
	POLY_LINE = 4,
	TRIANGLE = 5,
	TRIANGLE_STRIP = 6,
	POLYGON = 7,
	PIXEL = 8,
	QUAD = 9,
	TETRA = 10,
	VOXEL = 11,
	HEXAHEDRON = 12,
	WEDGE = 13,
	PYRAMID = 14,
	QUADRATIC_EDGE = 21,
	QUADRATIC_TRIANGLE = 22,
	QUADRATIC_QUAD = 23,
	QUADRATIC_TETRA = 24,
	QUADRATIC_HEXAHEDRON = 25,
};

class VTKCell_ {
public:


	VTKCell_()
	{}

	void setType( const VTKCellType& t ) { this->type = t; }

	VTKCellType getType() const { return type; }

	void setIndices( const std::vector< unsigned int >& indices ) { this->indices = indices; }

	std::vector< unsigned int > getIndices() const { return indices; }

private:
	VTKCellType type;
	std::vector< unsigned int > indices;

};


class VTKCell {
public:

	VTKCell()
	{}

	virtual ~VTKCell()
	{
	}

	static VTKCell* VTKCell::create( const int id, const VertexIndices& vs );

	virtual VTKCellType getType() const = 0;

	ConnectionVector getConnections() const { return connections; }

protected:
	ConnectionVector connections;
};

class VTKVertex : public VTKCell {
public:
	VTKVertex( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::VERTEX; }

};

class VTKPolyVertex : public VTKCell {
public:
	VTKPolyVertex( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::POLY_VERTEX; }
};

class VTKLine : public VTKCell {
public:
	VTKLine( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::LINE; }
};

class VTKPolyLine : public VTKCell {
public:
	VTKPolyLine( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::POLY_LINE; }

};

class VTKTriangle : public VTKCell {
public:
	VTKTriangle( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::TRIANGLE; }
};

class VTKTriangleStrip : public VTKCell {
public:
	VTKTriangleStrip( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::TRIANGLE_STRIP; }

};

class VTKPolygon : public VTKCell {
public:
	VTKPolygon( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::POLYGON; }
};

class VTKPixel : public VTKCell {
public:
	VTKPixel( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::PIXEL; }
};

class VTKQuad : public VTKCell {
public:
	VTKQuad( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::QUAD; }

};

class VTKTetra : public VTKCell {
public:
	VTKTetra( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::TETRA; }
};

class VTKVoxel : public VTKCell {
public:
	VTKVoxel( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::VOXEL; }
};

class VTKHexahedron : public VTKCell {
public:
	VTKHexahedron( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::HEXAHEDRON; }
};

class VTKWedge : public VTKCell {
public:
	VTKWedge( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::WEDGE; }
};

class VTKPyramid : public VTKCell {
public:
	VTKPyramid( const VertexIndices& indices );

	VTKCellType getType() const { return VTKCellType::PYRAMID; }
};


	}
}

#endif