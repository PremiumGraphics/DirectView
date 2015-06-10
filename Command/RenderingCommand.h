#ifndef __CRYSTAL_COMMAND_RENDERING_COMMAND_H__
#define __CRYSTAL_COMMAND_RENDERING_COMMAND_H__

#include "../Graphics/Polygon.h"
#include "../Math/ScalarSpace.h"

namespace Crystal{
	namespace Command {


class RenderingCommand {
public:
	RenderingCommand()
	{

	}

	void clear() {
		positions.clear();
		normals.clear();
		texCoords.clear();
		colors.clear();
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



	std::vector< float > getPositions() const { return positions; }

	std::vector< float > getNormals() const { return normals; }

	std::vector< float > getTexCoords() const { return texCoords; }

	std::vector< float > getColors() const { return colors; }

private:
	std::vector< float > positions;
	std::vector< float > normals;
	std::vector< float > texCoords;
	std::vector< float > colors;

};

class PointRenderingCommand
{
public:

	PointRenderingCommand() :
		pointSize(10)
	{}

	void clear() {
		ids.clear();
		points.clear();
	}


	void build(const Math::ScalarSpace3d<float>& ss, const unsigned int id) {
		const auto center = ss.getCenter();
		const auto cs = ss.getCenter().toArray();
		points.insert(points.end(), cs.begin(), cs.end());
		ids.push_back(id);
	}



	float getPointSize() const { return pointSize; }

	std::vector<float> getPoints() const { return points; }

	std::vector<int> getIds() const { return ids; }

private:
	float pointSize;
	std::vector< float > points;
	std::vector< int > ids;

};

	}
}

#endif