#include "stdafx.h"
#include "PropertyDialog.h"

using namespace Crystal::CG;
using namespace Crystal::Graphics;

VertexPropertyDialog::VertexPropertyDialog(wxWindow* parent, const Vertex& vertex) :
wxDialog(parent, wxID_ANY, "VertexProperty", wxDefaultPosition, wxSize(500, 500))
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
	normalX->SetValue(vertex.getNormal().getX());

	wxSpinCtrlDouble* normalY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 200), size);
	normalY->SetValue(vertex.getNormal().getY());

	wxSpinCtrlDouble* normalZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 200), size);
	normalZ->SetValue(vertex.getNormal().getZ());

	new wxStaticText(this, wxID_ANY, "TexCoord", wxPoint(0, 300));
	wxSpinCtrlDouble* texCoordX = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(100, 300), size);
	texCoordX->SetValue( vertex.getTexCoord().getX());

	wxSpinCtrlDouble* texCoordY = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(200, 300), size);
	texCoordY->SetValue(vertex.getTexCoord().getY());

	wxSpinCtrlDouble* texCoordZ = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxPoint(300, 300), size);
	texCoordZ->SetValue(vertex.getTexCoord().getZ());
}
