#include "DisplayList.h"

#include "Polygon.h"
#include "Material.h"
#include "ColorRGB.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

DisplayList::DisplayList(Face* f, const ColorRGBA<float>& color)
{
	add(f, color);
}


DisplayList::DisplayList(Polygon* polygon)
{
	add(polygon);
}

DisplayList::DisplayList(const Vector3dVector<float>& poss)
{
	vertices = Math::Vector3d<float>::toArray(poss);
}


DisplayList::DisplayList(const Vector3dVector<float>& poss, const Vector3dVector<float>& norms)
{
	vertices = Math::Vector3d<float>::toArray(poss);
	normals = Math::Vector3d<float>::toArray(norms);
}

DisplayList::DisplayList(const Vector3dVector<float>& poss, const Vector3dVector<float>& norms, const Vector3dVector<float>& texs)
{
	vertices = Math::Vector3d<float>::toArray(poss);
	normals = Math::Vector3d<float>::toArray(norms);
	texCoords = Math::Vector3d<float>::toArray(texs);
}


void DisplayList::clear()
{
	vertices.clear();
	normals.clear();
	texCoords.clear();
	colors.clear();

	ids.clear();
	vertexIds.clear();
	faceIds.clear();
	polygonIds.clear();
	materialIds.clear();
}

/*
void DisplayList::add(Vertex* v)
{
	v->getPosition()
}
*/

void DisplayList::add(Face* f, const ColorRGBA<float>& color)
{
	const std::vector<float>& vs = Vector3d<float>::toArray( getPositions( *f ));
	vertices.insert(vertices.end(), vs.begin(), vs.end() );

	const std::vector<float>& ns = Vector3d<float>::toArray( getNormals( *f ) );
	normals.insert(normals.end(), ns.begin(), ns.end());

	const std::vector<float>& ts = Vector3d<float>::toArray(f->getTexCoords());
	texCoords.insert(texCoords.end(), ts.begin(), ts.end());

	std::vector<unsigned int> vids;
	for (const VertexSPtr& v : f->getVertices()) {
		vids.push_back( v->getId() );
	}

	vertexIds.insert(vertexIds.end(), vids.begin(), vids.end());
	ids.push_back(vids);

	const Vector3dVector<float> positions = getPositions(*f);
	for (size_t i = 0; i < positions.size(); ++i) {
		faceIds.push_back(f->getId());
	}

	for (size_t i = 0; i < positions.size(); ++i) {
		const std::vector<float>& cs = color.toArray3();
		colors.insert( colors.end(), cs.begin(), cs.end() );
	}
}

void DisplayList::add(Polygon* p)
{
	for (std::shared_ptr<Face> f : p->getFaces()) {
		add(f.get(), p->getMaterial()->getAmbient());
	}
	for (size_t i = 0; i < p->getVertices().size(); ++i) {
		polygonIds.push_back(p->getId());
		materialIds.push_back(p->getMaterial()->getId());
	}
}


Vector3dVector<float> DisplayList::getPositions(const Face& f) const
{
	Vector3dVector<float> positions;
	const HalfEdgeSPtrList& edges = f.getEdges();
	for (const HalfEdgeSPtr& e : edges) {
		positions.push_back(e->getStartPosition());
		if (e == edges.back() && f.isOpen()) {
			positions.push_back(e->getEndPosition());
		}
	}
	return positions;
}


Vector3dVector<float> DisplayList::getNormals(const Face& f) const
{
	Vector3dVector<float> normals;
	const HalfEdgeSPtrList& edges = f.getEdges();
	for (const HalfEdgeSPtr& e : edges) {
		normals.push_back(e->getStart()->getNormal());
		if (e == edges.back() && f.isOpen()) {
			normals.push_back(e->getEnd()->getNormal());
		}
	}
	return normals;
}