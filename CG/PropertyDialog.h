#ifndef __CRYSTAL_APP_PROPERTY_DIALOG_H__
#define __CRYSTAL_APP_PROPERTY_DIALOG_H__

#include <stdafx.h>

#include "../Graphics/Vertex.h"
#include "../Graphics/Face.h"

namespace Crystal{
	namespace CG{

		class VertexPropertyDialog : public wxDialog {
		public:
			VertexPropertyDialog(wxWindow* parent, const Graphics::Vertex& vertex);
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