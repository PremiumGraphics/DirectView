#include "DisplayList.h"

#include "Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

DisplayList::DisplayList(Face* f)
{
	this->vertices = toArray( getPositions( *f) );
	this->normals = toArray( f->getNormals() );
	this->texCoords = toArray( f->getTexCoords() );

	this->ids.push_back( getVertexIds( *f ) );
}


DisplayList::DisplayList(const PolygonSPtr& polygon)
{
	add(polygon);
}

void DisplayList::clear()
{
	vertices.clear();
	normals.clear();
	texCoords.clear();
	ids.clear();
	vertexIds.clear();
	faceIds.clear();
	polygonIds.clear();
}

void DisplayList::add(Face* f)
{
	const std::vector<float>& vs = toArray( getPositions( *f ));
	vertices.insert(vertices.end(), vs.begin(), vs.end() );

	const std::vector<float>& ns = toArray(f->getNormals());
	normals.insert(normals.end(), ns.begin(), ns.end());

	const std::vector<float> ts = toArray(f->getTexCoords());
	texCoords.insert(texCoords.end(), ts.begin(), ts.end());

	const std::vector<unsigned int> ids_ = getVertexIds(*f);
	this->ids.push_back( ids_ );

	vertexIds.insert(vertexIds.end(), ids_.begin(), ids_.end());

	const Vector3dVector positions = getPositions(*f);
	for (size_t i = 0; i < positions.size(); ++i) {
		faceIds.push_back(f->getId());
	}
}

void DisplayList::add(const PolygonSPtr& p)
{
	for (std::shared_ptr<Face> f : p->getFaces()) {
		add(f.get());
	}
	for (size_t i = 0; i < p->getVertices().size(); ++i) {
		polygonIds.push_back(p->getId());
	}
}

/*
void DisplayList::addHighlight(Vertex* v)
{
	;
}

void DisplayList::addHighlight(Face* f)
{
	;
}
*/

std::vector<unsigned int> DisplayList::getVertexIds(const Face& f) const {
	std::vector<unsigned int> ids;
	for (const HalfEdgeSPtr& edge : f.getEdges() ) {
		ids.push_back(edge->getStart()->getId());
	}
	return ids;
}

Vector3dVector DisplayList::getPositions(const Face& f) const
{
	Vector3dVector positions;
	const HalfEdgeList& edges = f.getEdges();
	for (const HalfEdgeSPtr& e : edges) {
		positions.push_back(e->getStartPosition());
		if (e == edges.back() && f.isOpen()) {
			positions.push_back(e->getEndPosition());
		}
	}
	return positions;
}

