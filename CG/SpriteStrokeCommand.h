#ifndef __CRYSTAL_UI_SPRITE_STROKE_COMMAND_H__
#define __CRYSTAL_UI_SPRITE_STROKE_COMMAND_H__

#include "MouseCommand.h"
#include "DisplayList.h"
#include "../Math/Volume.h"

namespace Crystal {
	namespace UI {

class SpriteStrokeCommand : public MouseOperationCommand
{
public:

	SpriteStrokeCommand(Graphics::Camera<float>& camera, Math::Vector3d<float>& cursor, Math::Volume3dSPtr<float>& volume) :
		MouseOperationCommand(camera),
		cursor(cursor),
		volume(volume)
		//	_doRealTimeBake(false)
	{
		_doRealTimeBakeParticle = false;
		//_doRealTimePreview = false;

	}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual void onLeftDoubleClicked() override { attribute.charge *= -1.0f; }

	//virtual bool doRealTimeBake() override { return _doRealTimeBake; }

	DisplayList getDisplayList() {
		DisplayList list;
		list.add(toParticle(cursor));
		return list;
	}




	virtual void doPost(){
		if (_doRealTimeBakeParticle) {
			bake();
		}
	};

private:
	Math::Vector3d<float>& cursor;
	bool _doRealTimeBakeParticle;
	Math::Volume3dSPtr<float>& volume;
	Math::Particle3d<float>::Attribute attribute;

	//bool _doRealTimeBake;

	Math::Particle3d<float> toParticle(const Math::Vector3d<float>& pos) const {
		return Math::Particle3d<float>(pos, attribute);
	}


	void bake();

};

	}
}

#endif