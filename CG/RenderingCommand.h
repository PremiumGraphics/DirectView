#ifndef __CRYSTAL_CGS_RENDERING_COMMAND_H__
#define __CRYSTAL_CGS_RENDERING_COMMAND_H__

#include "../Graphics/Polygon.h"

namespace Crystal{
	namespace CGS {


struct RenderingCommand {
	RenderingCommand() : pointSize(10)
	{

	}

	void clear() {
		positions.clear();
		normals.clear();
		texCoords.clear();
		colors.clear();
		ids.clear();
		points.clear();
	}


	void build(const Graphics::PolygonSPtrList& polygons) {
		for (const auto& p : polygons) {
			positions = p->toPositionArray();
			normals = p->toNormalArray();
			colors = p->toColorArray();
		}
	}

	float pointSize;

	std::vector< float > positions;
	std::vector< float > normals;
	std::vector< float > texCoords;
	std::vector< float > colors;
	std::vector< int > ids;

	std::vector< float > points;

};

	}
}

#endif