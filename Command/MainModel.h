#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Shader/IDRenderer.h"
#include "../Shader/NormalRenderer.h"
#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"

#include "VolumeModel.h"
#include "SurfaceModel.h"
#include "LightModel.h"
#include "MetaballModel.h"
#include "RenderingModel.h"
#include "SurfaceConstructCommand.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Model {

enum UIMode
{
	CAMERA_TRANSLATE,
	SELECTED_TRANSLATE,
	SELECTED_ROTATE,
	SELECTED_SCALE,
};


template<typename T>
class MainModel final : private UnCopyable
{
public:
	MainModel() :
		camera(std::make_shared< Graphics::Camera<T> >()),
		volume(std::make_shared< VolumeModel<T> >())
	{
		uiMode = CAMERA_TRANSLATE;
	}

	void clear()
	{
		volume->clear();
		surface.clear();
		metaball.clear();
	}

	/*
	void add(const GridConfig<T>& config)
	{
		const auto ss = getVolumeModel()->create(config);
		getSurfaceModel()->create(*(ss->getSpace()));
	}
	*/

	void toVolume() {
		for (const auto& s : volume->getSpaces()) {
			s->getSpace()->setValue(0);
		}
		for (const auto& b : metaball.getBalls()) {
			for (const auto& s : volume->getSpaces()) {
				const auto& m = b->getMetaball();
				s->getSpace()->add(*(m));
			}
		}
	}

	void createMetaball() {
		metaball.create();
		buildSurface();
	}

	void buildSurface()
	{
		//getSurface()->clear();
		surface.clear();
		toVolume();
		for (const auto& s : getVolume()->getSpaces()) {
			//getSurface()->create(*s->getSpace());
			const auto ss = surfaceConstructCommand.create(*s->getSpace());
			surface.add(ss);
		}
	}

	void instanciateSurface() {
		surface.instanciate();
	}

	void rotate(const Math::Vector3d<T>& v) {
		;
	}


	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	VolumeModelSPtr<T> getVolume() const { return volume; }

	//SurfaceModelSPtr<T> getSurface() const { return surface; }


	void changeSelected(const Object::Type& type, const unsigned int id) {
		if (type == Object::Type::Metaball) {
			const auto selected = metaball.find(id);
			if (selected != nullptr) {
				selected->changeSelected();
			}
		}
		else if (type == Object::Type::VOLUME) {
			const auto selected = volume->find(id);
			if (selected != nullptr) {
				selected->changeSelected();
			}
		}
		else if (type == Object::Type::Polygon) {
			const auto selected = surface.find(id);
			if (selected != nullptr) {
				selected->changeSelected();
			}
		}
	}


	void move(const Math::Vector3d<T>& vector) {
		metaball.move(vector);
		volume->move(vector);
		surface.move(vector);
	}

	void deleteSelected() {
		metaball.deleteSelected();
		volume->deleteSelected();
		surface.deleteSelected();
	}

	void clearSelected() {
		metaball.clearSelected();
		volume->clearSelected();
		//surface->clearSelected();
	}

	void scale(const Math::Vector3d<T>& s) {
		volume->scale(s);

		//surface->scale(s);
	}

	MetaballConfig<T> getMetaballConfig() const {
		return metaball.getConfig();
	}

	void setMetaballConfig(const MetaballConfig<T>& config) {
		metaball.setConfig(config);
	}

	void setRendering()
	{
		//normalRenderer.clear();
		surfaceView.clear();
		volumeView.clear();
		metaballView.clear();

		surfaceView.set(surface);
		volumeView.set(volume);
		metaballView.set(metaball);
	}

	//Graphics::PointBuffer getPointBuffer() { }

	void move(const Math::Vector3d<T>& pos, const Math::Vector3d<T>& angle) {
		if (getUIMode() == CAMERA_TRANSLATE) {
			getCamera()->move(pos);
			getCamera()->addAngle(angle);
		}
		else if (getUIMode() == SELECTED_TRANSLATE) {
			move(pos);
			buildSurface();
			setRendering();
			//ssTransformCmd->move(pos);
		}
		else if (getUIMode() == SELECTED_ROTATE) {
			rotate(angle);
			setRendering();
		}
		else if (getUIMode() == SELECTED_SCALE) {
			scale(Vector3d<float>(1, 1, 1) + pos*0.01f);
			setRendering();
		}
		else {
			assert(false);
		}
	}

	Graphics::PointBuffer<T> getPointBuffer() const {
		auto p1 = metaballView.getPointBuffer();
		return p1;
	}

	Graphics::LineBuffer<T> getLineBuffer() const {
		auto l1 = volumeView.getLineBuffer();
		const auto& l2 = surfaceView.getLineBuffer();
		l1.add(l2);
		return l1;
	}

	Graphics::TriangleBuffer<T> getTriangleBuffer() const {
		return surfaceView.getTriangleBuffer();
	}

	UIMode getUIMode() const { return uiMode; }

	void setUIMode(const UIMode m) { this->uiMode = m; }

	RenderingConfig<T> getRenderingConfig() const { return rendering.getConfig(); }

	void setRenderingConfig(const RenderingConfig<T>& config) { rendering.setConfig(config); }

	void render(const int width, const int height) {

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glPointSize( rendering.getConfig().pointSize);

		const auto& points = getPointBuffer();
		const auto& lines = getLineBuffer();
		const auto& triangles = getTriangleBuffer();

		if (rendering.getMode() == RenderingCommand<float>::Mode::WIRE_FRAME) {
			glLineWidth(rendering.getConfig().lineWidth);
			wireframeRenderer.render(width, height, *camera, getLineBuffer());

//			glPointSize( this->getPointSize());
			wireframeRenderer.render(width, height, *camera, getPointBuffer());
		}
		else if (rendering.getMode() == RenderingCommand<float>::Mode::SURFACE) {
			wireframeRenderer.render(width, height, *camera, getTriangleBuffer());
			//surfaceRenderer.render(width, height, c );
		}
		else {
			assert(false);
		}
	}

	void buildRenderer() {
		normalRenderer.build();
		wireframeRenderer.build();
	}

private:
	Graphics::CameraSPtr<T> camera;
	LightModel<T> light;
	VolumeModelSPtr<T> volume;
	SurfaceModel<T> surface;
	MetaballModel<T> metaball;
	RenderingCommand<T> rendering;
	SurfaceConstructCommand<T> surfaceConstructCommand;
	SurfaceView<T> surfaceView;
	VolumeView<T> volumeView;
	MetaballView<T> metaballView;

	Graphics::NormalRenderer normalRenderer;
	Shader::WireframeRenderer wireframeRenderer;


	UIMode uiMode;

};

template<typename T>
using MainModelSPtr = std::shared_ptr < MainModel<T> > ;
	}
}

#endif