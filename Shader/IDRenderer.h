#ifndef __CRYSTAL_SHADER_ID_RENDERER_H__
#define __CRYSTAL_SHADER_ID_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Buffer.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class IDRenderer final : private UnCopyable
{
public:

	IDRenderer() = default;

	~IDRenderer() = default;

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::PointBuffer<float>& buffer);

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::LineBuffer<float>& buffer);

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::TriangleBuffer<float>& buffer);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint type;
		GLuint id;
		GLuint isSelected;
	};

	Location getLocations();


	void down();


	/*
	std::vector<float> positions;
	std::vector<int> types;
	std::vector<int> ids;
	std::vector<int> isSelecteds;
	*/
	Graphics::ShaderObject shader;
};

	}
}

#endif