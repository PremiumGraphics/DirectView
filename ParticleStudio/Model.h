#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/PolygonBuilder.h"
#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Polygon.h"

namespace Crystal {
	namespace CG {

class Model {
public:
	Model()
	{
		camera.setNear(1.0f);
	}

	void clear()
	{
		builder.clear();
	}

	Graphics::PolygonBuilder& getPolygonBuilder() { return builder; }

	std::list< Graphics::Material* > getMaterials() { return builder.getMaterialBuilder().getMaterials(); }

	Graphics::FaceSPtrVector getFaces() const { return builder.getFaces(); }

	Graphics::PolygonSPtrList getPolygons() const { return builder.getPolygons(); }

	Graphics::VertexSPtrVector getVertices() const { return builder.getVertices(); }

	Graphics::VertexSPtrVector getSelectedVertices() const { return selectedVertex; }

	Graphics::FaceSPtrVector getSelectedFaces() const { return selectedFace; }

	void setSelectedVertex(const unsigned int id);

	void setSelectedFace(const unsigned int id);

	Graphics::Camera<float>* getCamera() { return &camera; }

private:
	Graphics::PolygonBuilder builder;
	Graphics::VertexSPtrVector selectedVertex;
	Graphics::FaceSPtrVector selectedFace;

	Graphics::Camera<float> camera;
};

	}
}

#endif