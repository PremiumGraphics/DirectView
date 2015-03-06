#include "DisplayList.h"

#include "Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

DisplayList::DisplayList(Face* f)
{
	this->vertices = toArray( f->getPositions() );
	this->normals = toArray( f->getNormals() );
	this->texCoords = toArray( f->getTexCoords() );

	this->ids.push_back( f->getVertexIds() );
}


DisplayList::DisplayList(Polygon* polygon)
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
}

void DisplayList::add(Face* f)
{
	const std::vector<float>& vs = toArray(f->getPositions());
	vertices.insert(vertices.end(), vs.begin(), vs.end() );

	const std::vector<float>& ns = toArray(f->getNormals());
	normals.insert(normals.end(), ns.begin(), ns.end());

	const std::vector<float> ts = toArray(f->getTexCoords());
	texCoords.insert(texCoords.end(), ts.begin(), ts.end());

	const std::vector<unsigned int> ids_ = f->getVertexIds();
	this->ids.push_back( ids_ );

	vertexIds.insert(vertexIds.end(), ids_.begin(), ids_.end());

	for (size_t i = 0; i < f->getPositions().size(); ++i) {
		faceIds.push_back(f->getId());
	}
}

void DisplayList::add(Polygon* p)
{
	for (Face* f : p->getFaces()) {
		add(f);
	}
}
