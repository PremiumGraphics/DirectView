#ifndef __CRYSTAL_UI_LINE_STROKE_COMMAND_H__
#define __CRYSTAL_UI_LINE_STROKE_COMMAND_H__

#include "MouseCommand.h"

namespace Crystal {
	namespace UI {

class LineStrokeCommand : public MouseOperationCommand
{
public:
	LineStrokeCommand(Graphics::Camera<float>& camera, Math::Vector3d<float>& cursor) :
		MouseOperationCommand(camera),
		cursor(cursor)
	{}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual void onRightButtonDown() override;

	virtual void onLeftButtonDown() override;

	virtual void onLeftButtonUp() override;

	Math::Line3d<float> getLine() const { return Math::Line3d<float>(startPosition, endPosition); }

private:
	Math::Vector3d<float> startPosition;
	Math::Vector3d<float> endPosition;
	Math::Vector3d<float>& cursor;
};

	}
}

#endif