#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"

#include <memory>

#include <map>

namespace Crystal {
	namespace CG {

		/*
struct Face {
	std::vector<unsigned int> vertexIds;
	std::vector<unsigned int> normalIds;
};

struct Position {
	std::vector<Crystal::Math::Vector3d> vertices;
};
*/

class Polygon {
};

class Model {
public:
	Model();

	~Model();

	void clear();

	std::list<Graphics::Light> getLights() const { return lights; }

	Graphics::Camera<float>* getCamera() const { return camera.get(); }

	std::list<Graphics::Material> getMaterials() const { return materials; }

	std::list<Polygon> getPolygons() const { return polygons; }

private:
	const std::unique_ptr< Graphics::Camera<float> > camera;
	std::list<Graphics::Light> lights;
	std::list<Graphics::Material> materials;
	std::list<Polygon> polygons;

	wxDECLARE_NO_COPY_CLASS( Model );
};

	}
}

#endif