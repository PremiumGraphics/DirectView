#include "VTKObject.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

VTKObject::~VTKObject()
{
	for( ColorRGBAMap<float>* map : colorMaps ) {
		delete map;
	}
	colorMaps.clear();
	for( VTKCell* c : cells ) {
		delete c;
	}
	cells.clear();
	for( VTKAttributes* attr : nodeAttributes ) {
		delete attr;
	}
	nodeAttributes.clear();
	for( VTKAttributes* attr: cellAttributes ) {
		delete attr;
	}
	cellAttributes.clear();
}

Box VTKObject::getBoundingBox() const
{
	Box box;
	float minx = FLT_MAX;
	float miny = FLT_MAX;
	float minz = FLT_MAX;

	float maxx = -FLT_MAX;
	float maxy = -FLT_MAX;
	float maxz = -FLT_MAX;

	for( const Math::Vector3d& v: vertices ) {
		minx = std::min<float>( minx, v.getX() );
		miny = std::min<float>( miny, v.getY() );
		minz = std::min<float>( minz, v.getZ() );

		maxx = std::max<float>( maxx, v.getX() );
		maxy = std::max<float>( maxy, v.getY() );
		maxz = std::max<float>( maxz, v.getZ() );
	}

	Math::Vector3d minv( minx, miny, minz );
	Math::Vector3d maxv( maxx, maxy, maxz );

	return Math::Box( minv, maxv );
}

#include "../Graphics/ColorHSV.h"
#include "../Graphics/ColorConverter.h"

ColorRGBAMap<float>* VTKObject::createDefaultColorMap()
{
	Graphics::ColorRGBAMap<float>* map = new Graphics::ColorRGBAMap<float>( 0.0, 1.0, 360 );
	map->setName( "default" );
	for( int i = 0; i < 360; ++i ) {
		Graphics::ColorHSV hsv( i, 1.0, 1.0 );
		const ColorRGB<float>& color = ColorConverter::toRGB( hsv );
		ColorRGBA<float> colora( color.getRed(), color.getGreen(), color.getBlue(), 1.0 );
		map->setColor( i, colora );
	}
	colorMaps.push_back( map );
	return map;
	//colorMaps.push_back( map );
}

VectorVector VTKObject::getCellCenters() const
{
	VectorVector centers;
	for( VTKCell* cell : cells ) {
		Vector3d center;
		const ConnectionVector& connections = cell->getConnections();
		for( const Connection& c : connections ) {
			for( unsigned int i : c ) {
				center += vertices[i].getScaled( 1.0 / c.size() );
			}
		}
		centers.push_back( center );
	}
	return centers;
}
