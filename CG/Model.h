#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

namespace Crystal {
	namespace CG {

class Model {
public:
	Model() :
		builder(new Graphics::PolygonBuilder()),
		lightBuilder(new Graphics::LightBuilder())
	{
		camera.setNear(1.0f);
	}

	Graphics::PolygonBuilderSPtr getPolygonBuilder() const  { return builder; }

	Graphics::LightBuilderSPtr getLightBuilder() const { return lightBuilder; }

	Graphics::MaterialSPtrList getMaterials() { return builder->getMaterialBuilder()->getMaterials(); }

	Graphics::FaceSPtrVector getFaces() const { return builder->getFaces(); }

	Graphics::PolygonSPtrList getPolygons() const { return builder->getPolygons(); }

	Graphics::VertexSPtrVector getVertices() const { return builder->getVertices(); }

	Graphics::VertexSPtrVector getSelectedVertices() const { return selectedVertex; }

	Graphics::FaceSPtrVector getSelectedFaces() const { return selectedFace; }

	void setSelectedVertex(const Graphics::VertexSPtr& v) {
		this->selectedVertex.clear();
		this->selectedVertex.push_back(v);
	}

	void setSelectedFace(const Graphics::FaceSPtr& f) {
		this->selectedFace.clear();
		this->selectedFace.push_back(f);
	}


	void setSelectedVertex(const unsigned int id)
	{
		if (id >= 0 && id < getVertices().size()) {
			const Graphics::VertexSPtr& v = getVertices()[id];
		}
	}

	void setSelectedFace(const unsigned int id)
	{
		if (id >= 0 && id < getFaces().size()) {
			std::shared_ptr< Graphics::Face > f = getFaces()[id];
		}
	}

	Graphics::Camera<float>* getCamera() { return &camera; }

	Graphics::LightSPtrList getLights() { return lightBuilder->getLights(); }


private:
	const Graphics::PolygonBuilderSPtr builder;
	Graphics::VertexSPtrVector selectedVertex;
	Graphics::FaceSPtrVector selectedFace;

	Graphics::Camera<float> camera;
	Graphics::LightBuilderSPtr lightBuilder;

};

	}
}

#endif