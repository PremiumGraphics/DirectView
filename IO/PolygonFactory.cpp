#include "PolygonFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

Polygon* PolygonFactory::create(const OBJFile& file)
{
	std::list<Polygon*> polygons;
	for (const OBJGroup& g : file.getGroups()) {
		Polygon* polygon = new Polygon();
		polygon->positions = g.getPositions();
		polygon->normals = g.getNormals();
		polygon->texCoords = g.getTexCoords();

		for (const OBJFace& f : g.getFaces()) {
			Face face;
			face.vertexIds = f.getVertexIndices();
			face.normalIds = f.getNormalIndices();
			face.texIds = f.getTexIndices();
			polygon->faces.push_back(face);
		}
		polygons.push_back(polygon);
	}
	return polygons.front();
}

Polygon* PolygonFactory::create(const STLFile& file)
{
	Polygon* polygon = new Polygon();
	//polygon.positions = file.
	const STLCellVector& cells = file.getCells();
	std::vector< Vector3d > normals;
	std::vector< Vector3d > positions;

	unsigned int normalId = 0;
	unsigned int vertexId = 0;
	for (const STLCell& c : cells) {
		normals.push_back( c.getNormal() );
		const std::vector< Vector3d >& pos = c.getPositions();
		positions.insert(positions.end(), pos.begin(), pos.end());
		Face face;
		face.normalIds.push_back( normalId );
		face.vertexIds = std::vector < unsigned int > { vertexId, vertexId+1, vertexId+2 };
		normalId += 1;
		vertexId += 3;
		polygon->faces.push_back(face);
	}

	polygon->normals = normals;
	polygon->positions = positions;
	return polygon;
}