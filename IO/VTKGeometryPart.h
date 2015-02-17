#ifndef __CRYSTAL_IO_VTK_GEOMETRY_PART_H__
#define __CRYSTAL_IO_VTK_GEOMETRY_PART_H__

#include "VTKPoints.h"
#include "VTKCell.h"

namespace Crystal {
	namespace IO {

struct VTKGeometryBase {
	virtual std::vector< VTKCell_ > getCells() const { return cells; }

	void setCells( const std::vector<VTKCell_>& cells ) { this->cells = cells; }

	VTKPoints getPositions() const { return positions; }

	virtual void write( std::ostream& stream ) const{};

	virtual	void read(std::istream& stream ){};

protected:
	VTKPoints positions;
	std::vector< VTKCell_ > cells;
};

class VTKGeometryPart {
public:
	enum Type {
		STRUCTURED_POINTS,
		STRUCTURED_GRID,
		RECTILINEAR_GRID,
		POLYDATA,
		UNSTRUCTURED_GRID,
		FIELD,
	};

	VTKGeometryPart() :geom( nullptr ) {
	}

	void setGeometry( VTKGeometryBase* geom ) {
		this->geom = geom;
		this->cells = geom->getCells();
		this->points = geom->getPositions();
	}
	
	void read(std::istream& stream );

	void write( std::ostream& stream ) const;

	std::vector< VTKCell_ > getCells() const { return cells; }

	VTKPoints getPoints() const { return points; }

private:
	Type type;
	std::vector< VTKCell_ > cells;
	VTKPoints points;
	VTKGeometryBase* geom;

};


struct VTKStructuredPoints : public VTKGeometryBase
{
	Math::Vector3d getOrigin() const { return origin; }

	void setOrigin( const Math::Vector3d& origin ) { this->origin = origin; }

	Math::Vector3d getAspect() const { return aspect; }

	void setAspect( const Math::Vector3d& aspect ) { this->aspect = aspect; }

	int getDimX() const { return dimX; }

	int getDimY() const { return dimY; }

	int getDimZ() const { return dimZ; }

	void toPoints();

	void setDimensions( const int x, const int y, const int z ) {
		dimX = x;
		dimY = y;
		dimZ = z;
	}

	bool operator==( const VTKStructuredPoints& rhs ) const {
		return
			origin == rhs.origin &&
			aspect == rhs.aspect &&
			dimX == rhs.dimX &&
			dimY == rhs.dimY &&
			dimZ == rhs.dimZ;
	}

	void read( std::istream& s );

	void write( std::ostream& s ) const;

private:
	
	int dimX;
	int dimY;
	int dimZ;
	Math::Vector3d origin;
	Math::Vector3d aspect;
};

struct VTKStructuredGrid : public VTKGeometryBase
{
	int getDimX() const { return dimX; }

	int getDimY() const { return dimY; }

	int getDimZ() const { return dimZ; }

	void setDimensions( const int x, const int y, const int z ) {
		dimX = x;
		dimY = y;
		dimZ = z;
	}

	void setPositions( const std::vector< Math::Vector3d >& positions ) { this->positions.setPoints( positions ); }

	void read(std::istream& stream );

	void write(std::ostream& stream ) const;

	VTKType getType() const { return type; }

	void setType( const VTKType& t ) { this->type = t; }

private:
	int dimX;
	int dimY;
	int dimZ;
	VTKType type;
};

class VTKUnstructuredGrid : public VTKGeometryBase
{
public:
	std::vector< int > types;

	void read( std::istream& s );

	void write( std::ostream& s ) const;

	void setPositions( const std::vector< Math::Vector3d >& positions ) { this->positions.setPoints( positions ); }

	void setType( const VTKType& type ) { this->positions.setType( type ); }

private:
	std::vector< VTKCell_ > readCells(std::istream& stream, const VTKCellType& type);

	void writeCells(std::ostream& stream) const;
};


struct VTKRectlinearGrid : public VTKGeometryBase
{
	void read( std::istream& stream );

	void write( std::ostream& s ) const;

	int getDimX() const { return dimX; }

	int getDimY() const { return dimY; }

	int getDimZ() const { return dimZ; }

	void setDimensions( const int x, const int y, const int z ) {
		this->dimX = x;
		this->dimY = y;
		this->dimZ = z;
		assert( isValid() );
	}

	void setXCoords( const std::vector< float >& coords ) { this->xCoords = coords; }

	void setYCoords( const std::vector< float >& coords ) { this->yCoords = coords; }

	void setZCoords( const std::vector< float >& coords ) { this->zCoords = coords; }

	bool isValid() const { 
		return dimX >= 1 && dimY >= 1 && dimZ >= 1;
	}

	void setTypes( const VTKType& x, const VTKType& y, const VTKType& z ) {
		this->xType = x;
		this->yType = y;
		this->zType = z;
	}

	VTKType getTypeX() const { return xType; }

	VTKType getTypeY() const { return yType; }

	VTKType getTypeZ() const { return zType; }

	std::vector< float > getXCoords() const { return xCoords; }

	std::vector< float > getYCoords() const { return yCoords; }

	std::vector< float > getZCoords() const { return zCoords; }

private:

	int dimX;
	int dimY;
	int dimZ;
	std::vector< float > xCoords;
	std::vector< float > yCoords;
	std::vector< float > zCoords;
	VTKType xType;
	VTKType yType;
	VTKType zType;

};

class VTKPolygonalData : public VTKGeometryBase
{
public:
	void setPositions( const VTKPoints& points ) { this->positions = points; }

	void read(std::istream& stream);

	void write(std::ostream& stream) const;

private:

	std::vector< VTKCell_ > readCells(std::istream& stream, const VTKCellType& type);

	void writeCells( std::ostream& stream ) const;

};

	}

}

#endif