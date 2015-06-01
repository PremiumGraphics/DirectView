#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Polygon.h"

#include "../Math/BitSpace.h"

namespace Crystal {
	namespace CG {

class Model {
public:
	Model() :
		lightBuilder( std::make_shared< Graphics::LightBuilder>()),
		camera( std::make_shared< Graphics::Camera<float> >() )
	{
	}

	void clear()
	{
		bitSpaces.clear();
	}

	void addBitSpace(const Math::BitSpace3d<float>& bs) { bitSpaces.push_back(bs); }

	std::list< Math::BitSpace3d<float> > getBitSpaces() const { return bitSpaces; }

	Graphics::LightBuilderSPtr getLightBuilder() const { return lightBuilder; }

	Graphics::CameraSPtr<float> getCamera() { return camera; }

	Graphics::LightSPtrList getLights() { return lightBuilder->getLights(); }

private:
	Graphics::PolygonSPtrVector polygons;
	std::list< Math::BitSpace3d<float> > bitSpaces;

	Graphics::CameraSPtr<float> camera;
	Graphics::LightBuilderSPtr lightBuilder;
};

	}
}

#endif