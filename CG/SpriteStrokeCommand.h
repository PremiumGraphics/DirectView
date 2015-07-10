#ifndef __CRYSTAL_UI_SPRITE_STROKE_COMMAND_H__
#define __CRYSTAL_UI_SPRITE_STROKE_COMMAND_H__

#include "../UI/MouseCommand.h"
#include "../Graphics/DisplayList.h"
#include "../Math/Volume.h"
#include "../Graphics/Brush.h"

namespace Crystal {
	namespace UI {

class SpriteStrokeCommand : public MouseOperationCommand
{
public:
	SpriteStrokeCommand(Graphics::Camera<float>& camera ) :
		MouseOperationCommand(camera)
	{
		brush = std::make_shared< Graphics::BlendBrush<float> >();
		_doRealTimeBake = false;
		//_doRealTimePreview = false;

	}

	void setBrush(const Graphics::BrushSPtr<float>& b) { this->brush = b; }

	~SpriteStrokeCommand() = default;

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual void onWheel(const float delta) override;

	virtual bool doSurfaceConstruction() const override { return _doSurfaceConstruct; }

	virtual bool doBakeParticlesToVolume() const override { return _doRealTimeBake; }

	//virtual bool doRealTimeBake() const override { return}

	Graphics::DisplayList getDisplayList() const override;

	Graphics::BrushSPtrVector<float> getBrushes() const override{ return{ brush }; }

private:
	Graphics::BrushSPtr<float> brush;

	bool _doRealTimeBake;
	bool _doSurfaceConstruct;
};

	}
}

#endif