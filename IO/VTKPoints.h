#ifndef __CRYSTAL_IO_VTK_POINTS_H__
#define __CRYSTAL_IO_VTK_POINTS_H__

#include <istream>
#include <cassert>
#include <string>

#include "../Math/Vector3d.h"
#include "Helper.h"
#include "VTKType.h"

namespace Crystal {
	namespace IO {

struct VTKPoints {
	VTKPoints() :
		type( VTKType::FLOAT )
	{}

	void read( std::istream& stream );

	void write( std::ostream& stream, const VTKPoints& data ) const;

	std::vector< Math::Vector3d > getPoints() const { return points; }

	size_t size() const { return points.size(); }

	void setPoints( const std::vector< Math::Vector3d >& points ) { this->points = points; }
	
	VTKType getType() const { return type; }

	void setType( const VTKType& t ) { type = t; }

	bool equals( const VTKPoints& rhs );

	bool operator==( const VTKPoints& rhs ) {
		return equals( rhs );
	}

private:
	VTKType type;
	std::vector< Math::Vector3d > points;

};

	}
}

#endif