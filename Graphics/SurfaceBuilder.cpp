#include "SurfaceBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

Polygon* SurfaceBuilder::build(const ParticleObject& object)
{
	const Box& bb = object.getBoundingBox();
	const float length = object.getParticles().front()->getDiameter();
	float y = bb.getMaxY() - length * 0.5f;
	for ( ParticleBase* p : object.getParticles()) {
		const Vector3d v = p->getPosition();
	}
	return nullptr;
}

Vector3dVector SurfaceBuilder::findEdges(const ImageRGBA<float>& image)
{
	Vector3dVector edges;
	const float threshold = 0.5f;
	for (int y = 0; y < image.getHeight(); ++y) {
		//int count = 0;
		for (int x = 0; x < image.getWidth(); ++x) {
			const ColorRGBA<float>& color = image.getColor(x, y);
			if (color.getAlpha() > threshold) {
				edges.push_back( Vector3d(x, y, 0.0) );
				continue;
			}
		}
	}
	return edges;
}
