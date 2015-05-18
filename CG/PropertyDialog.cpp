#include "stdafx.h"
#include "PropertyDialog.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;

/*
VertexPropertyDialog::VertexPropertyDialog(wxWindow* parent, const VertexSPtr& vertex) :
wxDialog(parent, wxID_ANY, "VertexProperty", wxDefaultPosition, wxSize(500, 500)),
vertex( vertex )
{
	const wxSize size(50, 25);

	new wxStaticText(this, wxID_ANY, "ID", wxPoint(0, 0));
	wxSpinCtrl* id = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 0));
	id->SetValue(vertex->getId());

	new wxStaticText(this, wxID_ANY, "Position", wxPoint(0, 100));

	positionX = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100), size);
	positionY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 100), size);
	positionZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 100), size);

	setPosition(vertex->getPosition());

	new wxStaticText(this, wxID_ANY, "Normal", wxPoint(0, 200));

	normalX = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200), size);
	normalY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 200), size);
	normalZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 200), size);

	setNormal(vertex->getNormal());

	new wxStaticText(this, wxID_ANY, "TexCoord", wxPoint(0, 300));
	texCoordX = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 300), size);
	texCoordY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 300), size);
	texCoordZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 300), size);

	setTexCoord(vertex->getTexCoord());

	wxButton* okButton = new wxButton(this, wxID_OK, "OK", wxPoint(400, 100) );
	wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(400, 200));
}

void VertexPropertyDialog::OnOk(wxCommandEvent& e)
{
	vertex->setPosition( getPosition() );
	vertex->setNormal( getNormal() );
	vertex->setTexCoord( getTexCoord());
	//positionX->GetValue();
}

Vector3d VertexPropertyDialog::getPosition() const
{
	return Vector3d(positionX->GetValue(), positionY->GetValue(), positionZ->GetValue());
}

Vector3d VertexPropertyDialog::getNormal() const
{
	return Vector3d(normalX->GetValue(), normalY->GetValue(), normalZ->GetValue());
}

Vector3d VertexPropertyDialog::getTexCoord() const
{
	return Vector3d(texCoordX->GetValue(), texCoordY->GetValue(), texCoordZ->GetValue());
}

void VertexPropertyDialog::OnNormalizeNormal(wxCommandEvent& e)
{
	const Vector3d& normal = getNormal();
	setNormal(normal.getNormalized());
}

void VertexPropertyDialog::setPosition(const Vector3d& pos)
{
	positionX->SetValue(pos.getX());
	positionY->SetValue(pos.getY());
	positionZ->SetValue(pos.getZ());
}

void VertexPropertyDialog::setNormal(const Vector3d& norm)
{
	normalX->SetValue(norm.getX());
	normalY->SetValue(norm.getY());
	normalZ->SetValue(norm.getZ());
}

void VertexPropertyDialog::setTexCoord(const Vector3d& texCoord)
{
	texCoordX->SetValue(texCoord.getX());
	texCoordY->SetValue(texCoord.getY());
	texCoordZ->SetValue(texCoord.getZ());
}
*/

FacePropertyDialog::FacePropertyDialog(wxWindow* parent, const Face& f) :
wxDialog(parent, wxID_ANY, "FaceProperty", wxDefaultPosition, wxSize(500, 500))
{
	const wxSize size(50, 25);

	new wxStaticText(this, wxID_ANY, "ID", wxPoint(0, 0));
	wxSpinCtrl* id = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 0));
	id->SetValue(f.getId());
}

EdgePropertyDialog::EdgePropertyDialog(wxWindow* parent, HalfEdge& edge) :
wxDialog(parent, wxID_ANY, "EdgeProperty", wxDefaultPosition, wxSize(500, 500)),
edge(edge)
{
	const wxSize size(50, 25);

	new wxStaticText(this, wxID_ANY, "ID", wxPoint(0, 0));
	wxSpinCtrl* id = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 0));
	id->SetValue(edge.getId());

	startId = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 100), size);

	endId = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 200), size);
}

PolygonPropertyDialog::PolygonPropertyDialog(wxWindow* parent, Crystal::Graphics::Polygon& polygon) :
wxDialog(parent, wxID_ANY, "PolygonProperty", wxDefaultPosition, wxSize( 500, 500)),
polygon( polygon)
{
	const wxSize size(50, 25);

	new wxStaticText(this, wxID_ANY, "ID", wxPoint(0, 0));
	wxSpinCtrl* id = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 0));
	id->SetValue( polygon.getId());
}

LightProperty::LightProperty(wxWindow* parent, const wxSize& size) :
wxPropertyGrid
(
parent,
-1,
wxDefaultPosition,
size,
wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
)
{
	Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(LightProperty::OnChange));
}

#include "Converter.h"

void LightProperty::setValue(LightSPtr light)
{
	this->light = light;
	Clear();
	Append(new wxStringProperty("Name", wxPG_LABEL, light->name));
	//Append( new wxIntProperty( "ID", wxPG_LABEL, light->getId() ) );

	const Vector3d& pos = light->getPos();
	Append(new wxFloatProperty("PosX", wxPG_LABEL, pos.getX()));
	Append(new wxFloatProperty("PosY", wxPG_LABEL, pos.getY()));
	Append(new wxFloatProperty("PosZ", wxPG_LABEL, pos.getZ()));

	Append(new wxColourProperty(wxT("Diffuse"), wxPG_LABEL, Converter::toWxColor(light->getDiffuse())));
	//Append(new wxColourProperty(wxT("Ambient"), wxPG_LABEL, Converter::toWxColor(light->getAmbient())));
	Append(new wxColourProperty(wxT("Specular"), wxPG_LABEL, Converter::toWxColor(light->getSpecular())));
}

void LightProperty::OnChange(wxPropertyGridEvent& event)
{
	wxPGProperty* property = event.GetProperty();
	const wxString& name = property->GetName();
	const wxAny& value = property->GetValue();

	if (value.IsNull()) {
		return;
	}

	Math::Vector3d pos = light->getPos();
	if (name == "PosX") {
		const float x = wxANY_AS(value, float);
		pos.setX(x);
	}
	else if (name == "PosY") {
		const float y = wxANY_AS(value, float);
		pos.setY(y);
	}
	else if (name == "PosZ") {
		const float z = wxANY_AS(value, float);
		pos.setZ(z);
	}
	light->setPos(pos);

	if (name == wxT("Diffuse")) {
		wxColour c = wxANY_AS(value, wxColour);
		const Graphics::ColorRGB<float>& color = Converter::toColorRGB(c);
		light->setDiffuse(color);
	}/*
	else if (name == wxT("Ambient")) {
		wxColour c = wxANY_AS(value, wxColour);
		const Graphics::ColorRGB<float>& color = Converter::toColorRGB(c);
		light->setAmbient(color);
	}
	*/
	else if (name == wxT("Specular")) {
		wxColour c = wxANY_AS(value, wxColour);
		const Graphics::ColorRGB<float>& color = Converter::toColorRGB(c);
		light->setSpecular(color);
	}
}


MaterialProperty::MaterialProperty(wxWindow* parent, const wxSize& size) :
wxPropertyGrid
(
parent,
-1,
wxDefaultPosition,
size,
wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
)
{
	Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(MaterialProperty::OnChange));
	Connect(wxEVT_PG_DOUBLE_CLICK, wxPropertyGridEventHandler(MaterialProperty::OnDoubleClick));
}

#include "Converter.h"

void MaterialProperty::setValue(Material* m)
{
	this->m = m;
	Clear();
	Append(new wxStringProperty("Name", wxPG_LABEL, m->getName()));
	//Append( new wxIntProperty( "ID", wxPG_LABEL, m->getId() ) );
	Append(new wxColourProperty(wxT("Diffuse"), wxPG_LABEL, Converter::toWxColor(m->getDiffuse())));
	Append(new wxColourProperty(wxT("Ambient"), wxPG_LABEL, Converter::toWxColor(m->getAmbient())));
	Append(new wxColourProperty(wxT("Specular"), wxPG_LABEL, Converter::toWxColor(m->getSpecular())));
	Append(new wxFloatProperty(wxT("Shininess"), wxPG_LABEL, m->getShininess()));

	const Texture& texture = m->getTexture();
	Append(new wxStringProperty(wxT("AmbientTexture"), wxPG_LABEL, texture.ambient));
	Append(new wxStringProperty(wxT("DiffuseTexture"), wxPG_LABEL, texture.diffuse));
	Append(new wxStringProperty(wxT("SpecularTexture"), wxPG_LABEL, texture.shininess));
	Append(new wxStringProperty(wxT("BumpMap"), wxPG_LABEL, texture.bump));
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

void MaterialProperty::OnChange(wxPropertyGridEvent& event)
{
	wxPGProperty* property = event.GetProperty();
	const wxString& name = property->GetName();
	const wxAny& value = property->GetValue();

	if (value.IsNull()) {
		return;
	}

	if (name == wxT("Diffuse")) {
		wxColour c = wxANY_AS(value, wxColour);
		const Graphics::ColorRGBA<float>& color = Converter::toColorRGBA(c);
		m->setDiffuse(color);
	}
	else if (name == wxT("Ambient")) {
		wxColour c = wxANY_AS(value, wxColour);
		const Graphics::ColorRGBA<float>& color = Converter::toColorRGBA(c);
		m->setAmbient(color);
	}
	else if (name == "Specular") {
		wxColour c = wxANY_AS(value, wxColour);
		const Graphics::ColorRGBA<float>& color = Converter::toColorRGBA(c);
		m->setSpecular(color);
	}
	else if (name == "Shininess") {
		m->setShininess(wxANY_AS(value, float));
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

void MaterialProperty::OnDoubleClick(wxPropertyGridEvent& event)
{
	wxPGProperty* property = event.GetProperty();
	const wxString& name = property->GetName();
	const wxAny& value = property->GetValue();

	if (value.IsNull()) {
		return;
	}

	Texture texture = m->getTexture();
	if (name == "AmbientTexture") {
		const wxString& filename = getImageFile();
		if (filename.IsEmpty()) {
			return;
		}
		texture.ambient = filename.ToStdString();
	}
	else if (name == "DiffuseTexture") {
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


PolygonProperty::PolygonProperty(wxWindow* parent, const wxSize& size, const std::list<Material*>& materials) :
wxPropertyGrid
(
parent,
-1,
wxDefaultPosition,
size,
wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
),
materials(materials)
{
	Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(PolygonProperty::OnChanged));
	Connect(wxEVT_PG_DOUBLE_CLICK, wxPropertyGridEventHandler(PolygonProperty::OnDoubleClick));
}

void PolygonProperty::build(Crystal::Graphics::Polygon* polygon)
{
	this->polygon = polygon;

	Clear();
	Append(new wxStringProperty("Name", wxPG_LABEL, polygon->getName()) );

	Append(new wxIntProperty("Faces", wxPG_LABEL, polygon->getFaces().size()));
	Append(new wxIntProperty("Vertices", wxPG_LABEL, polygon->getVertices().size()));
	Append(new wxIntProperty("ID", wxPG_LABEL, polygon->getId()));
	Append(new wxFloatProperty("CenterX", wxPG_LABEL, polygon->getCenter().getX()));
	Append(new wxFloatProperty("CenterY", wxPG_LABEL, polygon->getCenter().getY()));
	Append(new wxFloatProperty("CenterZ", wxPG_LABEL, polygon->getCenter().getZ()));

	Material* m = polygon->getMaterial();

	wxArrayString materialNames;
	materialNames.Add(wxEmptyString);
	for (const Material* m : materials) {
		materialNames.Add(m->getName());
	}

	wxEnumProperty* materialProp = new wxEnumProperty(wxT("Material"), wxPG_LABEL, materialNames);
	Append(materialProp);
	if (m != nullptr) {
		materialProp->SetValueFromString(m->getName());
	}
}

void PolygonProperty::OnDoubleClick(wxPropertyGridEvent& event)
{
	wxPGProperty* property = event.GetProperty();
	wxMessageBox(property->GetLabel());
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

void PolygonProperty::OnChanged(wxPropertyGridEvent& event)
{
	wxPGProperty* property = event.GetProperty();
	const wxString& name = property->GetName();

	/*
	//Vector3d center = polygon->getCenter();
	if (name == "Material") {
		const std::string &str = property->GetValueAsString().ToStdString();
		for (Material* m : materials) {
			if (m->getName() == str) {
				polygon->setMaterial(m);
			}
		}
	}
	/*
	else if (name == "CenterX") {
		const float x = property->GetValue().GetDouble();
		center.setX(x);
	}
	else if (name == "CenterY") {
		const float y = property->GetValue().GetDouble();
		center.setY(y);
	}
	else if (name == "CenterZ") {
		const float z = property->GetValue().GetDouble();
		center.setZ(z);
	}
	polygon->setCenter(center);
	*/
}