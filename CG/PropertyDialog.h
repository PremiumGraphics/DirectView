#ifndef __CRYSTAL_APP_PROPERTY_DIALOG_H__
#define __CRYSTAL_APP_PROPERTY_DIALOG_H__

#include <stdafx.h>

#include "../Graphics/Vertex.h"

namespace Crystal{
	namespace CG{

		class VertexPropertyDialog : public wxDialog {
		public:
			VertexPropertyDialog(wxWindow* parent, const Graphics::Vertex& vertex) :
				wxDialog(parent, wxID_ANY, "VertexProperty", wxDefaultPosition, wxSize(300, 300))
			{
				wxSize size(50, 25);

				new wxStaticText(this, wxID_ANY, "ID", wxPoint(0, 0));
				wxSpinCtrl* id = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 0));
				id->SetValue(vertex.getId());

				new wxStaticText(this, wxID_ANY, "Position", wxPoint(0, 100));

				wxSpinCtrlDouble* positionX = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100), size);
				positionX->SetValue(vertex.getPosition().getX());

				wxSpinCtrlDouble* positionY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 100), size);
				positionY->SetValue(vertex.getPosition().getY());

				wxSpinCtrlDouble* positionZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 100), size);
				positionZ->SetValue(vertex.getPosition().getY());

				new wxStaticText(this, wxID_ANY, "Normal", wxPoint(0, 200));

				wxSpinCtrlDouble* normalX = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200), size);
				normalX->SetValue(vertex.getPosition().getX());

				wxSpinCtrlDouble* normalY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 200), size);
				normalY->SetValue(vertex.getPosition().getY());

				wxSpinCtrlDouble* normalZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 200), size);
				normalZ->SetValue(vertex.getPosition().getZ());


			}

		private:

		};

		class FacePropertyDialog : public wxDialog {
		public:
			FacePropertyDialog(wxWindow* parent, const Graphics::Face& f) :
				wxDialog(parent, wxID_ANY, "FaceProperty", wxDefaultPosition, wxSize(300, 300))
			{
				wxSize size(50, 25);

				new wxStaticText(this, wxID_ANY, "ID", wxPoint(0, 0));
				wxSpinCtrl* id = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 0));
				id->SetValue(f.getId());
			}
		};

	}
}

#endif