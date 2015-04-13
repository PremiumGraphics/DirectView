#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/PolygonBuilder.h"
#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"

namespace Crystal {
	namespace CG {

class Model {
public:
	Model() :
		lightBuilder(new Graphics::LightBuilder())
	{
		camera.setNear(1.0f);
	}

	void clear()
	{
		builder.clear();
	}

	Graphics::PolygonBuilder& getPolygonBuilder() { return builder; }

	Graphics::LightBuilderSPtr getLightBuilder() const { return lightBuilder; }

	Graphics::MaterialSPtrList getMaterials() { return builder.getMaterialBuilder()->getMaterials(); }

	Graphics::FaceSPtrVector getFaces() const { return builder.getFaces(); }

	Graphics::PolygonSPtrList getPolygons() const { return builder.getPolygons(); }

	Graphics::VertexSPtrVector getVertices() const { return builder.getVertices(); }

	Graphics::VertexSPtrVector getSelectedVertices() const { return selectedVertex; }

	Graphics::FaceSPtrVector getSelectedFaces() const { return selectedFace; }

	void setSelectedVertex(const unsigned int id);

	void setSelectedFace(const unsigned int id);

	Graphics::Camera<float>* getCamera() { return &camera; }

	Graphics::LightSPtrList getLights() { return lightBuilder->getLights(); }


private:
	Graphics::PolygonBuilder builder;
	Graphics::VertexSPtrVector selectedVertex;
	Graphics::FaceSPtrVector selectedFace;

	Graphics::Camera<float> camera;
	Graphics::LightBuilderSPtr lightBuilder;

};

	}
}

#endif