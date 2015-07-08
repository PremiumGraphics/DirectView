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
	LineStrokeCommand(Graphics::Camera<float>& camera, Math::Vector3d<float>& cursor);

	virtual void onDraggingLeft(const Math::Vector3d<float>& v) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual void onRightButtonDown() override;

	virtual void onRightButtonUp() override;

	DisplayList getDisplayList() const override {
		DisplayList list;
		list.add(toParticle(cursor));
		list.add(getLine());
		return list;
	}

	virtual bool doBakeParticlesToVolume() const override { return doRealTimeBake; }


	virtual std::vector<Math::Particle3d<float> > getParticles() const override;


private:
	Math::Vector3d<float> startPosition;
	Math::Vector3d<float> endPosition;
	Math::Vector3d<float>& cursor;

	Math::Line3d<float> getLine() const { return Math::Line3d<float>(startPosition, endPosition); }

	Math::Particle3d<float> toParticle(const Math::Vector3d<float>& pos) const {
		return Math::Particle3d<float>(pos, radius, density);
	}

	float radius;
	float density;

	bool doRealTimeBake;
};

	}
}

#endif