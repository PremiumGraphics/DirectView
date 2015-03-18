#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

namespace Crystal {
	namespace CG {

class Model {
public:
	Model() :
		builder(new Graphics::PolygonBuilder())
	{}

	Graphics::PolygonBuilderSPtr getPolygonBuilder() const  { return builder; }

	Graphics::MaterialSPtrList getMaterials() { return builder->getMaterialBuilder()->getMaterials(); }

	Graphics::FaceSPtrVector getFaces() const { return builder->getFaces(); }

	Graphics::PolygonSPtrList getPolygons() const { return builder->getPolygons(); }

private:
	const Graphics::PolygonBuilderSPtr builder;

};

	}
}

#endif