#ifndef __CRYSTAL_COMMAND_RENDERING_COMMAND_H__
#define __CRYSTAL_COMMAND_RENDERING_COMMAND_H__

#include "../Graphics/Polygon.h"
#include "../Math/ScalarSpace.h"

namespace Crystal{
	namespace Command {


class WireFrameRenderingCommand {
public:
	WireFrameRenderingCommand()
	{

	}

	void clear() {
		positions.clear();
		colors.clear();
	}


	void build(const Graphics::PolygonSPtrList<float>& polygons) {
		// positions;
		const auto cs = Graphics::ColorRGBA<float>::Blue().toArray3();
		for (const auto& p : polygons) {
			for (const auto& e : p->getEdges()) {
				const auto& start = e->getStartPosition().toArray();
				positions.insert(positions.end(), start.begin(), start.end());
				colors.insert(colors.end(), cs.begin(), cs.end());
				const auto& end = e->getEndPosition().toArray();
				positions.insert(positions.end(), end.begin(), end.end());
				colors.insert(colors.end(), cs.begin(), cs.end());

			}
			//colors.insert(colors.end(), cs.begin(), cs.end());
		}
	}

	std::vector< float > getPositions() const { return positions; }

	std::vector< float > getColors() const { return colors; }

private:
	std::vector< float > positions;
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

class NormalRenderingCommand
{
public:
	NormalRenderingCommand() = default;


	void clear() {
		positions.clear();
		normals.clear();
	}

	void build(const Graphics::PolygonSPtrList<float>& polygons) {
		for (const auto& p : polygons) {
			for (const auto& v : p->getVertices()) {
				const auto& ps = v->toPositionArray();
				positions.insert(positions.end(), ps.begin(), ps.end());
				const auto& ns = v->toNormalArray();
				normals.insert(normals.end(), ns.begin(), ns.end());

			}
		}
	}


	std::vector< float > getPositions() const { return positions; }

	std::vector< float > getNormals() const { return normals; }

private:
	std::vector< float > positions;
	std::vector< float > normals;

};

	}
}

#endif