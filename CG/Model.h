#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Polygon.h"

namespace Crystal {
	namespace CG {

class Model {
public:
	Model() :
		lightBuilder(new Graphics::LightBuilder()),
		camera( std::make_shared< Graphics::Camera<float> >() )
	{
		camera->setNear(1.0f);
	}

	void clear()
	{
	}


	Graphics::LightBuilderSPtr getLightBuilder() const { return lightBuilder; }

	Graphics::CameraSPtr<float> getCamera() { return camera; }

	Graphics::LightSPtrList getLights() { return lightBuilder->getLights(); }

private:
	Graphics::PolygonSPtrVector polygons;

	Graphics::CameraSPtr<float> camera;
	Graphics::LightBuilderSPtr lightBuilder;
};

	}
}

#endif