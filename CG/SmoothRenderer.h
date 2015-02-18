#ifndef __CRYSTAL_APP_POLYGON_RENDERER_H__
#define __CRYSTAL_APP_POLYGON_RENDERER_H__

#include <map>
#include <vector>

#include "../Graphics/ShaderObject.h"


namespace Crystal {
	namespace Math {
		class Vector3d;
	}
	namespace CG {

class SmoothRenderer {
public:

	SmoothRenderer();

	~SmoothRenderer();

	void build();

	void render( const int width, const int height );

private:
	Graphics::ShaderObject shader;
};

	}
}

#endif