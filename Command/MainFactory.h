#ifndef __CRYSTAL_COMMAND_MODEL_H__
#define __CRYSTAL_COMMAND_MODEL_H__

#include "../Graphics/Camera.h"

#include "ScalarSpaceFactory.h"
#include "PolygonFactory.h"
#include "LightFactory.h"
#include "MetaballModel.h"
#include "RenderingBuffer.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Command {

template<typename T>
class Model {
public:
	Model() :
		lightFactory(std::make_shared< LightModel<T> >()),
		camera(std::make_shared< Graphics::Camera<T> >()),
		ssFactory(std::make_shared< ScalarSpaceFactory<T> >()),
		polygonFactory(std::make_shared< PolygonFactory<T> >()),
		metaballFactory(std::make_shared< MetaballObjectModel<T> >()),
		renderingBuffer(std::make_shared< RenderingBuffer<T> >())
	{
	}

	void clear()
	{
		ssFactory->clear();
		polygonFactory->clear();
		metaballFactory->clear();
		renderingBuffer->clear();
	}

	void add(const MetaballObject<T>& metaball)
	{
		auto ss = ssFactory->getSpaces().front();
		ss->getSpace()->add(*metaball.getMetaball());
	}

	void add(const GridConfig<T>& config)
	{
		const auto ss = getScalarSpaceFactory()->create(config);
		getPolygonFactory()->create(*(ss->getSpace()));
		getPolygonFactory()->createBoundingBox(*ss->getSpace());
		getPolygonFactory()->createGridCells(*ss->getSpace());
	}

	void polygonize()
	{
		for (const auto& s : getScalarSpaceFactory()->getSpaces()) {
			getPolygonFactory()->create(*s->getSpace());
		}
	}

	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	LightFactorySPtr<T> getLightFactory() const { return lightFactory; }

	ScalarSpaceFactorySPtr<T> getScalarSpaceFactory() const { return ssFactory; }

	PolygonFactorySPtr<T> getPolygonFactory() const { return polygonFactory; }

	//PolygonFactorySPtr<float> getDrawableFactory() const { return supportFactory; }

	MetaballModelSPtr<T> getMetaballFactory() const { return metaballFactory; }

	RenderingBufferSPtr<T> getRenderingBuffer() const { return renderingBuffer; }


	Object* find(const int id) {
		if (ssFactory == nullptr) {
			return nullptr;
		}
		/*
		const auto ptr = ssFactory->find(id);
		if (ptr != nullptr) {
			return ptr->get();
		}
		*/
		return nullptr;
		//const auto ptr2 = ballFactory->find()
	}

private:
	Graphics::CameraSPtr<T> camera;
	LightFactorySPtr<T> lightFactory;
	ScalarSpaceFactorySPtr<T> ssFactory;
	PolygonFactorySPtr<T> polygonFactory;
	MetaballModelSPtr<T> metaballFactory;
	RenderingBufferSPtr<T> renderingBuffer;
};

template<typename T>
using ModelSPtr = std::shared_ptr < Model<T> > ;
	}
}

#endif