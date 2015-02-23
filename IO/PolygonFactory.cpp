#include "PolygonFactory.h"

#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

PolygonGroupList PolygonFactory::create(const OBJFile& file)
{
	PolygonGroupList polygons;
	for (const OBJGroup& g : file.getGroups()) {
		Polygon* polygon = new Polygon();
		polygon->setPositions( g.getPositions() );
		polygon->setNormals( g.getNormals() );
		polygon->setTexCoords( g.getTexCoords() );

		std::vector< Face > faces;
		for (const OBJFace& f : g.getFaces()) {
			Face face;
			face.setVertexIds( f.getVertexIndices() );
			face.setNormalIds( f.getNormalIndices() );
			face.setTexIds( f.getTexIndices() );
			faces.push_back(face);
		}
		polygon->setFaces(faces);
		polygons.push_back(polygon);
	}
	return polygons;
}

PolygonGroupList PolygonFactory::create(const STLFile& file)
{
	Polygon* polygon = new Polygon();
	//polygon.positions = file.
	const STLCellVector& cells = file.getCells();
	std::vector< Vector3d > normals;
	std::vector< Vector3d > positions;
	std::vector< Face > faces;

	unsigned int normalId = 0;
	unsigned int vertexId = 0;
	for (const STLCell& c : cells) {
		normals.push_back( c.getNormal() );
		const std::vector< Vector3d >& pos = c.getPositions();
		positions.insert(positions.end(), pos.begin(), pos.end());
		Face face;
		face.setNormalIds( { normalId, normalId, normalId } );
		face.setVertexIds( { vertexId, vertexId+1, vertexId+2 } );
		normalId += 1;
		vertexId += 3;
		faces.push_back(face);
	}

	polygon->setFaces(faces);
	polygon->setNormals( normals );
	polygon->setPositions( positions );
	return PolygonGroupList({ polygon } );
}