#ifndef __CRYSTAL_SHADER_WIREFRAME_RENDERER_H__
#define __CRYSTAL_SHADER_WIREFRAME_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "../Math/Volume.h"
#include "../Math/Line.h"
#include "../Util/UnCopyable.h"
#include "../Graphics/Brush.h"

#include "RendererBase.h"

namespace Crystal {
	namespace Shader {

class WireframeRenderer final : public RendererBase
{
public:

	WireframeRenderer() = default;

	~WireframeRenderer() = default;

	void add(const Graphics::BlendBrush<float>& b) override;

	void add(const Math::Volume3d<float>& volume) override;

	void add(const Graphics::Surface<float>& surface) override;

	void render(const int width, const int height, const Graphics::Camera<float>& camera) override;

	void build() override;

private:

	ShaderObject shader;

public:
	void clear() {
		positions.clear();
	}


public:
	void add(const Math::Line3d<float>& line) {
		add(line.getStart());
		add(line.getEnd());
	}

private:
	void add(const Math::Vector3d<float>& position) {
		const auto& poss = position.toArray3();
		positions.insert(positions.end(), std::begin(poss), std::end(poss));
	}


private:
	std::vector<float> positions;

public:
	void add(const Math::Box<float>& box);

};

	}
}

#endif