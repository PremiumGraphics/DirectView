#ifndef __CRYSTAL_UI_SPRITE_STROKE_COMMAND_H__
#define __CRYSTAL_UI_SPRITE_STROKE_COMMAND_H__

#include "../UI/MouseCommand.h"
#include "DisplayList.h"
#include "../Math/Volume.h"
#include "../Graphics/Brush.h"

namespace Crystal {
	namespace UI {

class SpriteStrokeCommand : public MouseOperationCommand
{
public:

	SpriteStrokeCommand(Graphics::Camera<float>& camera ) :
		MouseOperationCommand(camera)
		//	_doRealTimeBake(false)
	{
		_doRealTimeBake = false;
		//_doRealTimePreview = false;

	}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	//virtual void onLeftDoubleClicked() override { density *= -1.0f; }

	//virtual bool doRealTimeBake() override { return _doRealTimeBake; }

	virtual bool doSurfaceConstruction() const override { return _doSurfaceConstruct; }

	virtual bool doBakeParticlesToVolume() const override { return _doRealTimeBake; }

	//virtual bool doRealTimeBake() const override { return}

	DisplayList getDisplayList() const override {
		DisplayList list;
		list.add(toParticle(brush.getPosition()));
		return list;
	}

	/*
	void setCharge(const float c) { this->density = c; }

	float getCharge() const { return density; }
	*/

	std::vector< Math::Particle3d<float> > getParticles() const override{
		return{ toParticle(brush.getPosition()) };
	}

private:
	Graphics::Brush3d<float> brush;
	//Math::Particle3d<float>::Attribute attribute;

	bool _doRealTimeBake;
	bool _doSurfaceConstruct;

	Math::Particle3d<float> toParticle(const Math::Vector3d<float>& pos) const {
		return Math::Particle3d<float>(pos, brush.getSize().getX(), brush.getDensity() );
	}

};

	}
}

#endif