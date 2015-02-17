#include "stdafx.h"

#include "LightProperty.h"

#include "../Graphics/Light.h"

using namespace Crystal::Graphics;
using namespace Crystal::CG;

LightProperty::LightProperty( wxWindow* parent, const wxSize& size ) :
	wxPropertyGrid
		(
		parent,
		-1,
		wxDefaultPosition,
		size,
		wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
		)
{
	Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( LightProperty::OnChange ) );
}

#include "Converter.h"

void LightProperty::setValue( Light* light )
{
	this->light = light;
	Clear();
	Append( new wxStringProperty("Name", wxPG_LABEL, light->name) );
	//Append( new wxIntProperty( "ID", wxPG_LABEL, light->getId() ) );

	Append( new wxFloatProperty( "PosX", wxPG_LABEL, light->pos.getX() ) );
	Append( new wxFloatProperty( "PosY", wxPG_LABEL, light->pos.getY() ) );
	Append( new wxFloatProperty( "PosZ", wxPG_LABEL, light->pos.getZ() ) );

	Append( new wxColourProperty(wxT("Diffuse"), wxPG_LABEL, Converter::toWxColor(light->getDiffuse() ) ) );
	Append( new wxColourProperty(wxT("Ambient"), wxPG_LABEL, Converter::toWxColor( light->getAmbient() ) ) );
	Append( new wxColourProperty(wxT("Specular"), wxPG_LABEL, Converter::toWxColor(light->getSpecular() ) ) );
}

void LightProperty::OnChange( wxPropertyGridEvent& event )
{
    wxPGProperty* property = event.GetProperty();
    const wxString& name = property->GetName();
	const wxAny& value = property->GetValue();

    if ( value.IsNull() ) {
        return;
	}

	if( name == "PosX") {
		const float x = wxANY_AS( value, float );
		light->pos.setX( x );
	}
	else if( name == "PosY") {
		const float y = wxANY_AS( value, float );
		light->pos.setY( y );
	}
	else if( name == "PosZ") {
		const float z = wxANY_AS( value, float );
		light->pos.setZ( z );
	}

	if ( name == wxT("Diffuse") ) {
		wxColour c = wxANY_AS( value, wxColour );
		const Graphics::ColorRGB<float>& color = Converter::toColorRGB( c );
		light->setDiffuse( color );
	}
	else if( name == wxT("Ambient") ) {
		wxColour c = wxANY_AS( value, wxColour );
		const Graphics::ColorRGB<float>& color = Converter::toColorRGB( c );
		light->setAmbient( color );
	}
	else if( name == wxT("Specular") ) {
		wxColour c = wxANY_AS( value, wxColour );
		const Graphics::ColorRGB<float>& color = Converter::toColorRGB( c );
		light->setSpecular( color );
	}
}