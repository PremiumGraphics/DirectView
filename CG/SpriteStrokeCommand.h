#ifndef __CRYSTAL_UI_SPRITE_STROKE_COMMAND_H__
#define __CRYSTAL_UI_SPRITE_STROKE_COMMAND_H__

#include "MouseCommand.h"

namespace Crystal {
	namespace UI {

class SpriteStrokeCommand : public MouseOperationCommand
{
public:

	SpriteStrokeCommand(Graphics::Camera<float>& camera, Math::Vector3d<float>& cursor) :
		MouseOperationCommand(camera),
		cursor(cursor)//,
		//	_doRealTimeBake(false)
	{
		_doRealTimeBakeParticle = true;

	}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	//virtual bool doRealTimeBake() override { return _doRealTimeBake; }

private:
	Math::Vector3d<float>& cursor;
	//bool _doRealTimeBake;
};

	}
}

#endif