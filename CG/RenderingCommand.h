#ifndef __CRYSTAL_CGS_RENDERING_COMMAND_H__
#define __CRYSTAL_CGS_RENDERING_COMMAND_H__

#include "../Graphics/Polygon.h"
#include "../Math/ScalarSpace.h"

namespace Crystal{
	namespace Command {


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
			const auto ps = p->toPositionArray();
			const auto ns = p->toNormalArray();
			const auto cs =  p->toColorArray();

			positions.insert(positions.end(), ps.begin(), ps.end());
			normals.insert(normals.end(), ns.begin(), ns.end());
			colors.insert(colors.end(), cs.begin(), cs.end());
		}
	}

	void build(const Math::ScalarSpace3d<float>& ss, const unsigned int id) {
		const auto center = ss.getCenter();
		const auto cs = ss.getCenter().toArray();
		points.insert(points.end(), cs.begin(), cs.end());
		ids.push_back(id);
	}

	float getPointSize() const { return pointSize; }

	std::vector< float > normals;
	std::vector< float > texCoords;
	std::vector< float > colors;
	std::vector< int > ids;

	std::vector< float > points;

	std::vector< float > getPositions() const { return positions; }

private:
	float pointSize;
	std::vector< float > positions;

};

	}
}

#endif