#include "stdafx.h"

#include "MaterialProperty.h"

#include "../Graphics/Material.h"

#include <wx/propgrid/advprops.h>

using namespace Crystal::Graphics;
using namespace Crystal::CG;

MaterialProperty::MaterialProperty( wxWindow* parent, const wxSize& size ) :
	wxPropertyGrid
		(
		parent,
		-1,
		wxDefaultPosition,
		size,
		wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
		)
{
	Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( MaterialProperty::OnChange ) );
	Connect( wxEVT_PG_DOUBLE_CLICK, wxPropertyGridEventHandler( MaterialProperty::OnDoubleClick ) );
}

#include "Converter.h"

void MaterialProperty::setValue( Material* m )
{
	this->m = m;
	Clear();
	Append( new wxStringProperty("Name", wxPG_LABEL, m->getName()) );
	//Append( new wxIntProperty( "ID", wxPG_LABEL, m->getId() ) );
	Append( new wxColourProperty( wxT("Diffuse"), wxPG_LABEL, Converter::toWxColor(m->getDiffuse() ) ) );
	Append( new wxColourProperty( wxT("Ambient"), wxPG_LABEL, Converter::toWxColor(m->getAmbient() ) ) );
	Append( new wxColourProperty( wxT("Specular"), wxPG_LABEL, Converter::toWxColor(m->getSpecular() ) ) );
	Append( new wxFloatProperty( wxT("Shininess"), wxPG_LABEL, m->getShininess() ) );

	const Texture& texture = m->getTexture();
	Append( new wxStringProperty( wxT("AmbientTexture"), wxPG_LABEL, texture.ambient ) );
	Append( new wxStringProperty( wxT("DiffuseTexture"), wxPG_LABEL, texture.diffuse) );
	Append( new wxStringProperty( wxT("SpecularTexture"), wxPG_LABEL, texture.shininess) );
	Append( new wxStringProperty(wxT("BumpMap"), wxPG_LABEL, texture.bump) );
	/*
    wxBitmap myTestBitmap(60, 15, 32);
    wxMemoryDC mdc;
    mdc.SelectObject(myTestBitmap);
    mdc.Clear();
    mdc.SetPen(*wxBLACK);
    mdc.DrawLine(0, 0, 60, 15);
    mdc.SelectObject(wxNullBitmap);
	SetPropertyImage( wxT("AmbientTexture"), myTestBitmap );
	
	SetPropertyImage( "AmbientTexture", wxBitmap( 24, 24 ) ); //m->texture.getAmbientBitmap() );

	//Append(new wxStringProperty( wxT("DiffuseTexture"), wxPG_LABEL, m->texture.getDiffuseFileName() ) );
	//SetPropertyImage( "DiffuseTexture", m->texture.getDiffuseBitmap() );

	//Append(new wxStringProperty( wxT("SpecularTexture"), wxPG_LABEL, m->texture.getSpecularFileName() ) );
	//SetPropertyImage( "SpecularTexture", m->texture.getSpecularFileName );

	//Append(new wxStringProperty( "BumpMap", wxPG_LABEL, wxEmptyString ) );
	//SetPropertyImage( "BumpMap", m->texture.bump );
	*/
}

void MaterialProperty::OnChange( wxPropertyGridEvent& event )
{
    wxPGProperty* property = event.GetProperty();
    const wxString& name = property->GetName();
	const wxAny& value = property->GetValue();

    if ( value.IsNull() ) {
        return;
	}

	if ( name == wxT("Diffuse") ) {
		wxColour c = wxANY_AS( value, wxColour );
		const Graphics::ColorRGBA<float>& color = Converter::toColorRGBA( c );
		m->setDiffuse( color );
	}
	else if( name == wxT("Ambient") ) {
		wxColour c = wxANY_AS( value, wxColour );
		const Graphics::ColorRGBA<float>& color = Converter::toColorRGBA( c );
		m->setAmbient( color );
	}
	else if( name == "Specular" ) {
		wxColour c = wxANY_AS( value, wxColour );
		const Graphics::ColorRGBA<float>& color = Converter::toColorRGBA( c );
		m->setSpecular( color );
	}
	else if( name == "Shininess" ) {
		m->setShininess( wxANY_AS( value, float ) );
	}
}

wxString MaterialProperty::getImageFile()
{
	const wxString filename = wxFileSelector
		(
		wxT("Open Image"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		wxT("BMP files (*.bmp)|*.bmp|")
		wxT("PNG files (*.png)|*.png|")
		wxT("JPEG files (*.jpg)|*.jpg"),
		wxFD_OPEN,
		this
		);

	if (filename.IsEmpty()) {
		return wxEmptyString;
	}

	wxImage image;
	image.LoadFile(filename);

	if (!image.IsOk()) {
		wxMessageBox(wxT("Invalid Image"));
		return wxEmptyString;
	}
	return filename;
}

void MaterialProperty::OnDoubleClick( wxPropertyGridEvent& event )
{
    wxPGProperty* property = event.GetProperty();
    const wxString& name = property->GetName();
	const wxAny& value = property->GetValue();

    if ( value.IsNull() ) {
        return;
	}

	Texture texture = m->getTexture();
	if( name == "AmbientTexture") {
		const wxString& filename = getImageFile();
		if (filename.IsEmpty()) {
			return;
		}
		texture.ambient = filename.ToStdString();
	}
	else if( name == "DiffuseTexture") {
		const wxString& filename = getImageFile();
		if (filename.IsEmpty()) {
			return;
		}
		texture.diffuse = filename.ToStdString();
	}
	else if (name == "SpecularTexture") {
		const wxString& filename = getImageFile();
		if (filename.IsEmpty()) {
			return;
		}
		texture.shininess = filename.ToStdString();
	}
	else if (name == "BumpMap") {
		const wxString& filename = getImageFile();
		if (filename.IsEmpty()) {
			return;
		}
		texture.bump = filename.ToStdString();
	}
	m->setTexture(texture);
	setValue(m);
}