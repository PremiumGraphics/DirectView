#include <stdafx.h>

#include "VTKPropertyGrid.h"

#include "View.h"

#include "../Graphics/ColorRGBAMap.h"
#include "../Math/Box.h"
#include "../IO/VTKObject.h"

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::App;

VTKPropertyGrid::VTKPropertyGrid( wxWindow* parent, View* view, const wxPoint position, const wxSize& size ) :
	wxPropertyGrid
		(
		parent,
		-1,
		position,
		size,
		wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
		),
	object( nullptr ),
	attr( nullptr ),
	view( view )
	
{
	Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( VTKPropertyGrid::OnChange ) );
}

void VTKPropertyGrid::build(Crystal::IO::VTKObject* object)
{
	Clear();
	Append( new wxIntProperty("���_��", wxPG_LABEL, object->getVertices().size() ) );
	Append( new wxIntProperty("�Z����", wxPG_LABEL, object->getCells().size() ) );
	const Box& box = object->getBoundingBox();
	Append( new wxFloatProperty("�ŏ�X", wxPG_LABEL, box.getMinX() ) );
	Append( new wxFloatProperty("�ő�X", wxPG_LABEL, box.getMaxX() ) );
	Append( new wxFloatProperty("�ŏ�Y", wxPG_LABEL, box.getMinY() ) );
	Append( new wxFloatProperty("�ő�Y", wxPG_LABEL, box.getMaxY() ) );
	Append( new wxFloatProperty("�ŏ�Z", wxPG_LABEL, box.getMinZ() ) );
	Append( new wxFloatProperty("�ő�Z", wxPG_LABEL, box.getMaxZ() ) );
}

void VTKPropertyGrid::build(VTKAttributes* attribute, VTKObject* object)
{
	this->object = object;
	this->attr = attribute;

	Clear();
	Append( new wxStringProperty("�ϐ���", wxPG_LABEL, attribute->getName() ) ); 
	Append( new wxIntProperty("����", wxPG_LABEL, attribute->getDim() ) );
	Append( new wxStringProperty("�^", wxPG_LABEL, attribute->getType() ) );
	Append( new wxIntProperty("�v�f��", wxPG_LABEL, attribute->getValues().size() ) );
	Append( new wxFloatProperty("�ŏ��l", wxPG_LABEL, attribute->getMin() ) );
	Append( new wxFloatProperty("�ő�l", wxPG_LABEL, attribute->getMax() ) );


	wxArrayString strs;
	for( Crystal::Graphics::ColorRGBAMap<float>* map : object->getColorMaps() ) {
		strs.Add( map->getName() );
	}

	prop = new wxEnumProperty( "�J���[�}�b�v", wxPG_LABEL, strs );
	const std::string& str = attribute->getLookupTableName();
	if( !str.empty() ) {
		prop->SetValueFromString( str );
	}
	else {
		prop->SetValue( wxEmptyString );
	}
	Append( prop );	
}

void VTKPropertyGrid::OnChange(wxPropertyGridEvent& event)
{
    wxPGProperty* property = event.GetProperty();
    const wxString& name = property->GetName();
	const wxAny& value = property->GetValue();

    if ( value.IsNull() ) {
        return;
	}

	assert( object != nullptr );
	assert( attr != nullptr );
	assert( prop != nullptr );

	if( name == "�J���[�}�b�v") {
		const wxString& str = prop->GetValueAsString();//wxANY_AS( value, wxString );
		//wxMessageBox("TODO");
		attr->setLookupTableName( str.ToStdString() );
		view->setRenderingBlocks();
		view->Refresh();
		//attribut
	}
}