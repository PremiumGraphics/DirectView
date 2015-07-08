#ifndef __CRYSTAL_UI_BONE_STROKE_COMMAND_H__
#define __CRYSTAL_UI_BONE_STROKE_COMMAND_H__

#include "MouseCommand.h"
#include "../Math/Volume.h"
#include "DisplayList.h"

namespace Crystal {
	namespace UI {

class BoneStrokeCommand final : public MouseOperationCommand
{
public:
	BoneStrokeCommand(Graphics::Camera<float>& camera, Math::Vector3d<float>& cursor, Math::Volume3d<float>& volume);

	~BoneStrokeCommand() = default;

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual void onLeftButtonDown() override;

	virtual void onLeftButtonUp() override;

	virtual void doPost() override;

	Math::Line3d<float> getLine() const { return Math::Line3d<float>(startPosition, endPosition); }

private:
	Math::Vector3d<float> startPosition;
	Math::Vector3d<float> endPosition;
	Math::Vector3d<float>& cursor;
	Math::Volume3d<float>& volume;


	Math::Particle3d<float> toParticle(const Math::Vector3d<float>& pos) const {
		return Math::Particle3d<float>(pos, particleAttribute);
	}

	Math::Particle3d<float>::Attribute particleAttribute;

	bool doRealTimeBake;
};

	}
}

#endif