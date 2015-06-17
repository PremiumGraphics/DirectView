#ifndef __CRYSTAL_SHADER_WIRE_FRAME_RENDERER_H__
#define __CRYSTAL_SHADER_WIRE_FRAME_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Surface.h"

namespace Crystal {
	namespace Shader {

class WireFrameRenderer {
public:

	WireFrameRenderer()
	{};

	~WireFrameRenderer();

	void render(const int width, const int height, const Graphics::Camera<float>& camera );

	void build();

	void clear() {
		positions.clear();
		colors.clear();
	}

	void add(const Graphics::Surface<float>& s) {
		// positions;
		const auto cs = Graphics::ColorRGBA<float>::Blue().toArray3();
		for (const auto& e : s.getEdges()) {
			const auto& start = e->getStartPosition().toArray();
			positions.insert(positions.end(), start.begin(), start.end());
			colors.insert(colors.end(), cs.begin(), cs.end());
			const auto& end = e->getEndPosition().toArray();
			positions.insert(positions.end(), end.begin(), end.end());
			colors.insert(colors.end(), cs.begin(), cs.end());
		}
			//colors.insert(colors.end(), cs.begin(), cs.end());
	}

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint color;
	};

	Location getLocations();

	Graphics::ShaderObject shader;

	std::vector< float > positions;
	std::vector< float > colors;

};

class SurfaceRenderer {
public:
	SurfaceRenderer()
	{};

	virtual ~SurfaceRenderer();

	virtual void render(const int width, const int height, const Graphics::Camera<float>& camera );

	void build();

	std::vector< float > positions;
	std::vector< float > colors;


private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint color;
	};

	Location getLocations();

	Graphics::ShaderObject shader;
};

	}
}

#endif