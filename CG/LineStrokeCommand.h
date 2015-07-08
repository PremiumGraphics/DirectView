#ifndef __CRYSTAL_UI_LINE_STROKE_COMMAND_H__
#define __CRYSTAL_UI_LINE_STROKE_COMMAND_H__

#include "MouseCommand.h"
#include "../Math/Volume.h"
#include "DisplayList.h"

namespace Crystal {
	namespace UI {

class LineStrokeCommand : public MouseOperationCommand
{
public:
	LineStrokeCommand(Graphics::Camera<float>& camera, Math::Vector3d<float>& cursor, Math::Volume3d<float>& volume);

	virtual void onDraggingLeft(const Math::Vector3d<float>& v) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual void onRightButtonDown() override;

	virtual void onRightButtonUp() override;

	virtual void doPost() override;

	DisplayList getDispayList() const {
		DisplayList list;
		list.add(getLine());
		return list;
	}


private:
	Math::Vector3d<float> startPosition;
	Math::Vector3d<float> endPosition;
	Math::Vector3d<float>& cursor;
	Math::Volume3d<float>& volume;

	Math::Line3d<float> getLine() const { return Math::Line3d<float>(startPosition, endPosition); }

	Math::Particle3d<float> toParticle(const Math::Vector3d<float>& pos) const {
		return Math::Particle3d<float>(pos, attr);
	}

	Math::Particle3d<float>::Attribute attr;

	bool doRealTimeBake;
};

	}
}

#endif