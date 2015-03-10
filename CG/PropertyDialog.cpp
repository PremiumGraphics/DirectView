#include "stdafx.h"
#include "PropertyDialog.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;

VertexPropertyDialog::VertexPropertyDialog(wxWindow* parent, Vertex& vertex) :
wxDialog(parent, wxID_ANY, "VertexProperty", wxDefaultPosition, wxSize(500, 500)),
vertex( vertex )
{
	const wxSize size(50, 25);

	new wxStaticText(this, wxID_ANY, "ID", wxPoint(0, 0));
	wxSpinCtrl* id = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 0));
	id->SetValue(vertex.getId());

	new wxStaticText(this, wxID_ANY, "Position", wxPoint(0, 100));

	positionX = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 100), size);
	positionY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 100), size);
	positionZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 100), size);

	setPosition(vertex.getPosition());

	new wxStaticText(this, wxID_ANY, "Normal", wxPoint(0, 200));

	normalX = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 200), size);
	normalY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 200), size);
	normalZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 200), size);

	setNormal(vertex.getNormal());

	new wxStaticText(this, wxID_ANY, "TexCoord", wxPoint(0, 300));
	texCoordX = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 300), size);
	texCoordY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 300), size);
	texCoordZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 300), size);

	setTexCoord(vertex.getTexCoord());

	wxButton* okButton = new wxButton(this, wxID_OK, "OK", wxPoint(400, 100) );
	wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(400, 200));
}

void VertexPropertyDialog::OnOk(wxCommandEvent& e)
{
	vertex.setPosition( getPosition() );
	vertex.setNormal( getNormal() );
	vertex.setTexCoord( getTexCoord());
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