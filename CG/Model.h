#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Polygon.h"

#include "../Math/BitSpace.h"
#include "../Math/ScalarSpace.h"
#include "../Math/MarchingCube.h"

#include <memory>

namespace Crystal {
	namespace CG {

template<typename T>
using ScalarSpace3dSPtr = std::shared_ptr < Math::ScalarSpace3d<T> > ;

template<typename T>
using ScalarSpace3dSPtrList = std::list < ScalarSpace3dSPtr<T> > ;

template<typename T>
using BitSpace3dSPtr = std::shared_ptr < Math::BitSpace3d<T> > ;

template<typename T>
using BitSpace3dSPtrList = std::list < BitSpace3dSPtr<T> > ;

class Model {
public:
	Model() :
		lightBuilder( std::make_shared< Graphics::LightBuilder>()),
		camera( std::make_shared< Graphics::Camera<float> >() )
	{
		mc.buildTable();
	}

	void clear()
	{
		bitSpaces.clear();
		polygons.clear();
	}

	void addBitSpace(const BitSpace3dSPtr<float>& bs) { bitSpaces.push_back(bs); }

	BitSpace3dSPtrList<float> getBitSpaces() const { return bitSpaces; }

	void addScalarSpace(const ScalarSpace3dSPtr<float>& ss) { scalarSpaces.push_back(ss); }

	ScalarSpace3dSPtrList<float> getScalarSpaces() const { return scalarSpaces; }

	Graphics::LightBuilderSPtr getLightBuilder() const { return lightBuilder; }

	Graphics::CameraSPtr<float> getCamera() { return camera; }

	Graphics::LightSPtrList getLights() { return lightBuilder->getLights(); }

	void toPolygon();

	Graphics::PolygonSPtrVector getPolygons() const { return polygons; }

private:
	Graphics::PolygonSPtrVector polygons;
	std::vector< Math::Vector3d<float > > gridCenters;
	BitSpace3dSPtrList<float> bitSpaces;
	ScalarSpace3dSPtrList<float> scalarSpaces;
	Math::MarchingCube<float> mc;

	Graphics::CameraSPtr<float> camera;
	Graphics::LightBuilderSPtr lightBuilder;
};

	}
}

#endif