#ifndef __CRYSTAL_SHADER_ID_RENDERER_H__
#define __CRYSTAL_SHADER_ID_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class IDRenderer final : private UnCopyable
{
public:
	enum class Mode{
		POINTS,
		LINES,
		TRIANGLES,
	};

	IDRenderer() = default;

	~IDRenderer() = default;

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Mode mode);

	void build();

	void add(const Math::Vector3d<float>& v, const unsigned int type, const unsigned int id, const unsigned int isSelected) {
		const auto& cs = v.toArray();
		positions.insert(positions.end(), cs.begin(), cs.end());
		types.push_back(type);
		ids.push_back(id);
		isSelecteds.push_back(isSelected);
	}

	void clear() {
		positions.clear();
		types.clear();
		ids.clear();
		isSelecteds.clear();
	}

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


	std::vector<float> positions;
	std::vector<int> types;
	std::vector<int> ids;
	std::vector<int> isSelecteds;

	Graphics::ShaderObject shader;
};

	}
}

#endif