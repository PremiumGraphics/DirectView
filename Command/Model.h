#ifndef __CRYSTAL_COMMAND_MODEL_H__
#define __CRYSTAL_COMMAND_MODEL_H__

#include "../Graphics/Camera.h"

#include "ScalarSpaceModel.h"
#include "PolygonModel.h"
#include "LightModel.h"
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
		light(std::make_shared< LightModel<T> >()),
		camera(std::make_shared< Graphics::Camera<T> >()),
		scalarSpace(std::make_shared< ScalarSpaceModel<T> >()),
		polygon(std::make_shared< PolygonModel<T> >()),
		metaball(std::make_shared< MetaballObjectModel<T> >()),
		renderingBuffer(std::make_shared< RenderingBuffer<T> >())
	{
	}

	void clear()
	{
		scalarSpace->clear();
		polygon->clear();
		metaball->clear();
		renderingBuffer->clear();
	}

	void add(const MetaballObject<T>& metaball)
	{
		auto ss = scalarSpace->getSpaces().front();
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

	void translate(const Math::Vector3d<T>& v) {
		;
	}

	void rotate(const Math::Vector3d<T>& v) {
		;
	}

	void scale(const Math::Vector3d<T>& s) {
		;
	}

	void setRendering() {
		const auto& buffer = getRenderingBuffer();
		buffer->add( getPolygonFactory()->getPolygons());
		buffer->add( getScalarSpaceFactory()->getSpaces());
		buffer->add( getMetaballFactory()->getBalls());
	}

	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	LightModelSPtr<T> getLightFactory() const { return light; }

	ScalarSpaceModelSPtr<T> getScalarSpaceFactory() const { return scalarSpace; }

	PolygonModelSPtr<T> getPolygonFactory() const { return polygon; }

	//PolygonFactorySPtr<float> getDrawableFactory() const { return supportFactory; }

	MetaballModelSPtr<T> getMetaballFactory() const { return metaball; }

	RenderingBufferSPtr<T> getRenderingBuffer() const { return renderingBuffer; }


	Object* find(const int id) {
		if (scalarSpace == nullptr) {
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
	LightModelSPtr<T> light;
	ScalarSpaceModelSPtr<T> scalarSpace;
	PolygonModelSPtr<T> polygon;
	MetaballModelSPtr<T> metaball;
	RenderingBufferSPtr<T> renderingBuffer;
};

template<typename T>
using ModelSPtr = std::shared_ptr < Model<T> > ;
	}
}

#endif