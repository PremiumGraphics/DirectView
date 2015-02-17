#include "VTKPoints.h"

using namespace Crystal::IO;

void VTKPoints::read( std::istream& stream )
{
	std::string str = Helper::read<std::string>(stream);
	assert( str == "POINTS" );

	size_t numPoints = Helper::read<int>(stream);
		
	str = Helper::read<std::string>(stream);
	type = VTKType( str );

	for( size_t i = 0; i < numPoints; ++i ) {
		points.push_back( Helper::readVector( stream ) );
	}
}

void VTKPoints::write( std::ostream& stream, const VTKPoints& data ) const
{
	stream << "POINTS " << data.getPoints().size() << " ";
	stream << data.getType().toString() << std::endl;

	for( const Math::Vector3d& v : data.getPoints() ) {
		stream << v.getX() << " " << v.getY() << " " << v.getZ() << std::endl;
	}
}

bool VTKPoints::equals( const VTKPoints& rhs )
{
	const bool b = ( this->type == rhs.type ) &&
		( this->points.size() == rhs.points.size() );

	if( !b ) {
		return false;
	}

	for( size_t i = 0; i < points.size(); ++i ) {
		if( points[i] != rhs.points[i] ) {
			return false;
		}
	}

	return true;
}