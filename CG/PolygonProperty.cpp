#include "stdafx.h"
#include "PolygonProperty.h"
#include "Converter.h"

#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;

PolygonProperty::PolygonProperty(wxWindow* parent, const wxSize& size, const MaterialList& materials) :
	wxPropertyGrid
		(
		parent,
		-1,
		wxDefaultPosition,
		size,
		wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
		),
		materials( materials )
{
	Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( PolygonProperty::OnChanged ) );
	Connect( wxEVT_PG_DOUBLE_CLICK, wxPropertyGridEventHandler( PolygonProperty::OnDoubleClick ) );
}

void PolygonProperty::build( const PolygonGroup& group )
{
	this->group = group;

	Graphics::Polygon* polygon = group.getPolygon();

	Clear();
	Append( new wxStringProperty("Name", wxPG_LABEL, polygon->name ) );
	Append( new wxIntProperty("Faces", wxPG_LABEL, polygon->faces.size() ) );
	Append( new wxIntProperty("Vertices", wxPG_LABEL, polygon->getPositions().size() ) );

	Graphics::Material* m = group.getMaterial();

	wxArrayString materialNames;
	materialNames.Add( wxEmptyString );
	for( Material* m : materials ) {
		materialNames.Add( m->getName() );
	}

	wxEnumProperty* materialProp = new wxEnumProperty( wxT("Material"), wxPG_LABEL, materialNames );
	Append( materialProp );
	if (m != nullptr) {
		materialProp->SetValueFromString(m->getName());
	}
}

void PolygonProperty::OnDoubleClick( wxPropertyGridEvent& event )
{
    wxPGProperty* property = event.GetProperty();
	wxMessageBox( property->GetLabel() );
    /*wxStatusBar* sb = GetStatusBar();
    if ( property ) {
        wxString text(wxT("Double-clicked: "));
        text += property->GetLabel();
        text += wxT(", name=");
        text += propGridManager->GetPropertyName( property );
        sb->SetStatusText( text );
    }
    else {
        sb->SetStatusText( wxEmptyString );
    }*/


	//wxTreeCtrl* tree = new wxTreeCtrl( this, wxNewId() );
	//tree->Appen
}

void PolygonProperty::OnChanged( wxPropertyGridEvent& event )
{
    wxPGProperty* property = event.GetProperty();
	const wxString& name = property->GetName();

	if( name == "Material" ) {
		const std::string &str = property->GetValueAsString().ToStdString();
		for (Material* m : materials) {
			if (m->getName() == str) {
				group.setMaterial(m);
			}
		}
	}
}