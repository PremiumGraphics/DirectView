#include "stdafx.h"
#include "PolygonProperty.h"
#include "Converter.h"

#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;

PolygonProperty::PolygonProperty( wxWindow* parent, const wxSize& size ) :
	wxPropertyGrid
		(
		parent,
		-1,
		wxDefaultPosition,
		size,
		wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
		)
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
	Append( new wxIntProperty("Vertices", wxPG_LABEL, polygon->positions.size() ) );

	Graphics::Material* m = group.getMaterial();
	if (m == nullptr) {
		return;
	}

	Append(new wxStringProperty("MaterialName", wxPG_LABEL, m->getName()));
	Append(new wxColourProperty(wxT("Diffuse"), wxPG_LABEL, Converter::toWxColor(m->getDiffuse())));
	Append(new wxColourProperty(wxT("Ambient"), wxPG_LABEL, Converter::toWxColor(m->getAmbient())));
	Append(new wxColourProperty(wxT("Specular"), wxPG_LABEL, Converter::toWxColor(m->getSpecular())));
	Append(new wxFloatProperty(wxT("Shininess"), wxPG_LABEL, m->getShininess()));

	const Texture& texture = m->getTexture();
	Append(new wxStringProperty(wxT("AmbientTexture"), wxPG_LABEL, texture.ambient));
	Append(new wxStringProperty(wxT("DiffuseTexture"), wxPG_LABEL, texture.diffuse));
	Append(new wxStringProperty(wxT("SpecularTexture"), wxPG_LABEL, texture.shininess));
	Append(new wxStringProperty(wxT("BumpMap"), wxPG_LABEL, texture.bump));

//	Append( new wxMultiChoiceProperty( "Materials",

	/*
	wxArrayString materialNames;
	materialNames.Add( wxEmptyString );
	const MaterialList& ms = materials->getMaterials();
	for( Material* m : ms ) {
		materialNames.Add( m->name );
	}

	wxEnumProperty* materialProp = new wxEnumProperty( wxT("Material"), wxPG_LABEL, materialNames );
	Append( materialProp );
	materialProp->SetValueFromString( polygon->material->name );

	const Vector3d& worldPosition = polygon->getCenter();
	Append( new wxFloatProperty("CenterX", wxPG_LABEL, worldPosition.getX() ) );
	Append( new wxFloatProperty("CenterY", wxPG_LABEL, worldPosition.getY() ) );
	Append( new wxFloatProperty("CenterZ", wxPG_LABEL, worldPosition.getZ() ) );

	const Vector3d& length = polygon->getBoundingBox().getLength();
	Append( new wxFloatProperty("SizeX", wxPG_LABEL, length.getX() ) );
	Append( new wxFloatProperty("SizeY", wxPG_LABEL, length.getY() ) );
	Append( new wxFloatProperty("SizeZ", wxPG_LABEL, length.getZ() ) );

	const Vector3d& angle = polygon->getAngle();
	Append( new wxFloatProperty("AngleX", wxPG_LABEL, angle.getX() ) );
	Append( new wxFloatProperty("AngleY", wxPG_LABEL, angle.getY() ) );
	Append( new wxFloatProperty("AngleZ", wxPG_LABEL, angle.getZ() ) );
	*/
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
	/*
    wxPGProperty* property = event.GetProperty();
	const wxString& name = property->GetName();

	if( name == "Material" ) {
		const wxString& str = property->GetValueAsString();
		Material* m = materials->find( str.ToStdString() );
		polygon->material = m;
	}
	else if( name == "CenterX" ) {
		Vector3d pos = polygon->getCenter();
		const float x = property->GetValue().GetDouble();
		pos.setX( x );
		polygon->setCenter( pos );
	}
	else if( name == "CenterY" ) {
		Vector3d pos = polygon->getCenter();
		const float y = property->GetValue().GetDouble();
		pos.setY( y );
		polygon->setCenter( pos );
	}
	else if( name == "CenterZ" ) {
		Vector3d pos = polygon->getCenter();
		const float z = property->GetValue().GetDouble();
		pos.setZ( z );
		polygon->setCenter( pos );
	}
	else if( name == "AngleX" ) {
		Vector3d angle = polygon->getAngle();
		const float x = property->GetValue().GetDouble();
		angle.setX( x );
		polygon->setAngle( angle );
	}
	else if( name == "AngleY" ) {
		Vector3d angle = polygon->getAngle();
		const float y = property->GetValue().GetDouble();
		angle.setY( y );
		polygon->setAngle( angle );
	}
	else if( name == "AngleZ" ) {
		Vector3d angle = polygon->getAngle();
		const float z = property->GetValue().GetDouble();
		angle.setZ( z );
		polygon->setAngle( angle );
	}
	*/
}