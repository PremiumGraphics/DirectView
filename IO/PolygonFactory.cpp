#include "PolygonFactory.h"

#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

PolygonSPtrList PolygonFactory::create(const OBJFile& file)
{
	PolygonSPtrList polygons;
	for (const OBJGroup& g : file.getGroups()) {
		PolygonSPtr polygon = pBuilder->build();
		//polygon->setPositions( g.getPositions() );
		//polygon->setNormals( g.getNormals() );
		//polygon->setTexCoords( g.getTexCoords() );
		const VertexSPtrVector& vv = vBuilder->buildVerticesFromPositions(g.getPositions());

		FaceSPtrVector faces;
		for (const OBJFace& f : g.getFaces()) {

			VertexSPtrVector vvv;
			for (unsigned int i : f.getVertexIndices()) {
				vvv.push_back(vv[i]);
			}
			const HalfEdgeSPtrList& edges = eBuilder->buildClosedFromVertices(vvv);
			FaceSPtr f = fBuilder->build(edges);

			//face->setVertexIds( f.getVertexIndices() );
			//face->setNormalIds( f.getNormalIndices() );
			//face.setTexIds( f.getTexIndices() );
			faces.push_back(f);
		}
		polygon->setVertices(vv);
		polygon->setFaces(faces);
		polygons.push_back(polygon);
	}
	return polygons;
}

PolygonSPtrList PolygonFactory::create(const STLFile& file)
{
	PolygonSPtr polygon = pBuilder->build();
	const STLCellVector& cells = file.getCells();
	FaceSPtrVector faces;

	for (const STLCell& c : cells) {
		const Vector3dVector& pos = c.getPositions();
		const Vector3dVector normals(3, c.getNormal());
		const VertexSPtrVector& vv = vBuilder->buildVerticesFromPositionsAndNormals(pos, normals);
		const HalfEdgeSPtrList& edges = eBuilder->buildClosedFromVertices(vv);
		const FaceSPtr& face = fBuilder->build(edges);
		faces.push_back(face);
		polygon->addVertices(vv);
	}

	polygon->setFaces(faces);
	return PolygonSPtrList({ polygon } );
}