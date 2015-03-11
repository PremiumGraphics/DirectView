#include "PolygonFactory.h"

#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

PolygonSPtrList PolygonFactory::create(const OBJFile& file)
{
	PolygonSPtrList polygons;
	for (const OBJGroup& g : file.getGroups()) {
		PolygonSPtr polygon( new Polygon(0) );
		//polygon->setPositions( g.getPositions() );
		//polygon->setNormals( g.getNormals() );
		//polygon->setTexCoords( g.getTexCoords() );

		FaceVector faces;
		for (const OBJFace& f : g.getFaces()) {
			std::shared_ptr<Face> face(  new Face(0) );
			//face->setVertexIds( f.getVertexIndices() );
			//face->setNormalIds( f.getNormalIndices() );
			//face.setTexIds( f.getTexIndices() );
			faces.push_back(face);
		}
		polygon->setFaces(faces);
		polygons.push_back(polygon);
	}
	return polygons;
}

PolygonSPtrList PolygonFactory::create(const STLFile& file)
{
	PolygonSPtr polygon( new Polygon(0) );
	//polygon.positions = file.
	const STLCellVector& cells = file.getCells();
	std::vector< Vector3d > normals;
	FaceVector faces;

	unsigned int normalId = 0;
	unsigned int vertexId = 0;
	for (const STLCell& c : cells) {
		std::shared_ptr<Face> face(new Face(0));
		normals.push_back( c.getNormal() );
		const std::vector< Vector3d >& pos = c.getPositions();
		const VertexVector& vv = vBuilder.buildVerticesFromPositions(pos);
		const HalfEdgeSPtrList& edges = eBuilder.buildClosedFromVertices(vv);
		const FaceSPtr& f = fBuilder.build(edges);
		//face->setNormalIds( { normalId, normalId, normalId } );
		//face->setVertexIds( { vertexId, vertexId+1, vertexId+2 } );
		normalId += 1;
		vertexId += 3;
		faces.push_back(face);
	}

	polygon->setFaces(faces);
	//polygon->setNormals( normals );
	//polygon->setPositions( positions );
	return PolygonSPtrList({ polygon } );
}