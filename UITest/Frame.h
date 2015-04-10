#ifndef __CRYSTAL_CG_FRAME_H__
#define __CRYSTAL_CG_FRAME_H__

#include "../Graphics/Camera.h"
#include "../Graphics/Light.h"

#include "../UI/ModelingDialog.h"

#include "../UI/PropertyDialog.h"

#include "../UI/PolygonTree.h"

#include <memory>


#ifndef __CRYSTAL_MODELING_MODEL_H__
#define __CRYSTAL_MODELING_MODEL_H__

#include "../Graphics/PolygonBuilder.h"
#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Modeling {

		class Model {
		public:
			Model() :
				builder(new Graphics::PolygonBuilder())
			{
				camera.setNear(1.0f);
			}

			void clear()
			{
				builder->clear();
			}

			Graphics::PolygonBuilderSPtr getPolygonBuilder() const  { return builder; }

			Graphics::FaceSPtrVector getFaces() const { return builder->getFaces(); }

			Graphics::PolygonSPtrList getPolygons() const { return builder->getPolygons(); }

			Graphics::VertexSPtrVector getVertices() const { return builder->getVertices(); }

			Graphics::VertexSPtrVector getSelectedVertices() const { return selectedVertex; }

			Graphics::FaceSPtrVector getSelectedFaces() const { return selectedFace; }

			void setSelectedVertex(const unsigned int id);

			void setSelectedFace(const unsigned int id);

			Graphics::Camera<float>* getCamera() { return &camera; }



		private:
			const Graphics::PolygonBuilderSPtr builder;
			Graphics::VertexSPtrVector selectedVertex;
			Graphics::FaceSPtrVector selectedFace;

			Graphics::Camera<float> camera;

		};

	}
}

#endif

namespace Crystal {
	namespace Modeling {
		class View;
		class Model;
		class MaterialTree;
		class LightTree;

		class MaterialProperty;
		class LightProperty;

		class Frame;
		class Model;



class Widgets {
public:
	Widgets() {}

	void build(Frame* parent, Model& model);

	void refresh() {
		polygonTree->build();
	}

	UI::PolygonTree* getPolygonTree() const { return polygonTree; }


	UI::PolygonProperty* getPolygonProperty() const { return polygonProperty; }

private:
	UI::PolygonTree* polygonTree;
	MaterialTree* materialTree;

	UI::PolygonProperty* polygonProperty;
};


class Frame : public wxFrame//wxMDIParentFrame
{
public:
	Frame();

	~Frame();

	Model& getModel() { return model; }

private:


	void OnCameraTranslate( wxRibbonButtonBarEvent& );

	void OnPolygonTranslate( wxRibbonButtonBarEvent& );

	void OnPolygonRotate( wxRibbonButtonBarEvent& );

	//void OnPick(wxRibbonButtonBarEvent&);


	void OnGLConfig( wxRibbonButtonBarEvent& e );

	void OnLocale( wxCommandEvent& );

	void OnPolygonScale( wxRibbonButtonBarEvent& e);

	void OnCameraFit( wxRibbonButtonBarEvent& e );

	void OnCapture( wxRibbonButtonBarEvent& e );


	void clear();

private:

	Widgets w;

	UI::ModelingDialogs modelings;

	View* view;
	Model model;

	wxLocale locale;

	wxDECLARE_NO_COPY_CLASS( Frame );

};


	}
}

#endif
