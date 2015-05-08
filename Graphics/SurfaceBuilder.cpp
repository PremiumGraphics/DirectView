#include "SurfaceBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;
using namespace Crystal::Graphics;

Polygon* SurfaceBuilder::build(const ParticleObject& object)
{
	const Box& bb = object.getBoundingBox();
	const float length = object.getParticles().front()->getDiameter();
	float y = bb.getMaxY() - length * 0.5f;
	for ( ParticleBaseSPtr p : object.getParticles()) {
		const Vector3d v = p->getPosition();
	}
	return nullptr;
}

Vector3dVector SurfaceBuilder::findEdges(const ImageRGBA<float>& image)
{
	Vector3dVector edges;
	const auto threshold = 0.5f;
	for (auto y = 0; y < image.getHeight(); ++y) {
		//int count = 0;
		for (auto x = 0; x < image.getWidth(); ++x) {
			const auto& color = image.getColor(x, y);
			if (color.getAlpha() > threshold) {
				edges.push_back( Vector3d(x * 1.0f, y * 1.0f, 0.0f) );
				continue;
			}
		}
	}
	return edges;
}
