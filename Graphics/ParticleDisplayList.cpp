#include "ParticleDisplayList.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void ParticleDisplayList::add(const ParticleObject& object)
{
	const std::vector< float >& ps = object.toPositionArray();
	positions.insert(positions.end(), ps.begin(), ps.end() );

	const std::vector< ColorRGB<float> >& cs = toColors(object);
	for (const ColorRGB<float>& c : cs) {
		std::vector< float > cc = c.toArray3();
		colors.insert(colors.end(), cc.begin(), cc.end());
	}
}

void ParticleDisplayList::add(const ParticleObject& object, const ColorRGB<float>& color)
{
	const std::vector< float >& ps = object.toPositionArray();
	positions.insert(positions.end(), ps.begin(), ps.end());

	const std::vector< ColorRGB<float> >& cs = toColors(object);
	for (const ParticleBaseSPtr& p : object.getParticles()) {
		std::vector< float > cc = color.toArray3();
		colors.insert(colors.end(), cc.begin(), cc.end());
	}
}


ColorRGB<float> ParticleDisplayList::toColor(const ParticleBase& particle)
{
	const float r = particle.getId() / 1024.0f;
	const float g = particle.getId() / 2048.0f;
	const float b = 0.0f;
	return ColorRGB<float>(r, g, b);
}

std::vector< ColorRGB<float> > ParticleDisplayList::toColors(const ParticleObject& object)
{
	std::vector< ColorRGB<float> > colors;
	for (const ParticleBaseSPtr& p : object.getParticles()) {
		ColorRGB<float>& cs = toColor(*p);
		cs.setBlue(object.getId() / 512.0f);
		colors.push_back( cs );
	}
	return colors;
}
