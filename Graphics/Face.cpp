#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

Vector3dVector<float> Face::getTexCoords() const
{
	Vector3dVector<float> texCoords;
	for (const HalfEdgeSPtr& e : edges) {
		texCoords.push_back(e->getStart()->getNormal());
		if (e == edges.back() && isOpen()) {
			texCoords.push_back(e->getEnd()->getNormal());
		}
	}
	return texCoords;

}

Vector3d<float> Face::getCenter() const
{
	Vector3d<float> center;
	const float size = static_cast<float>(getVertices().size());
	for (VertexSPtr v : getVertices()) {
		center += v->getPosition() / size;
	}
	return center;
}
