#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

Vector3dVector Face::getTexCoords() const
{
	Vector3dVector texCoords;
	for (const HalfEdgeSPtr& e : edges) {
		texCoords.push_back(e->getStart()->getNormal());
		if (e == edges.back() && isOpen()) {
			texCoords.push_back(e->getEnd()->getNormal());
		}
	}
	return texCoords;

}

Vector3d Face::getCenter() const
{
	Vector3d center;
	const float size = static_cast<float>(getVertices().size());
	for (VertexSPtr v : getVertices()) {
		center += v->getPosition() / size;
	}
	return center;
}
