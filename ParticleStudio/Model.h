#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/PolygonBuilder.h"
#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Polygon.h"

#include "../Physics/ParticleBuilder.h"

namespace Crystal {
	namespace CG {

class Model {
public:
	Model() :
		pBuilder( 0.1f)
	{
		camera.setNear(1.0f);
	}

	void clear()
	{
		builder.clear();
	}

	Graphics::PolygonBuilder& getPolygonBuilder() { return builder; }

	Graphics::PolygonSPtrList getPolygons() const { return builder.getPolygons(); }

	Graphics::VertexSPtrVector getVertices() const { return builder.getVertices(); }

	Graphics::Camera<float>* getCamera() { return &camera; }

	Physics::ParticleBuilder& getParticleBuilder() { return pBuilder; }

private:
	Graphics::PolygonBuilder builder;
	Graphics::Camera<float> camera;
	Physics::ParticleBuilder pBuilder;
};

	}
}

#endif