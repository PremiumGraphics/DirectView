#ifndef __CRYSTAL_APP_PROPERTY_DIALOG_H__
#define __CRYSTAL_APP_PROPERTY_DIALOG_H__

#include "stdafx.h"

#include "../Graphics/Vertex.h"
#include "../Graphics/Face.h"
#include "../Graphics/Polygon.h"
#include "../Graphics/Light.h"


namespace Crystal{
	namespace CG{

		/*
class VertexPropertyDialog : public wxDialog {
public:
	VertexPropertyDialog(wxWindow* parent, const Graphics::VertexSPtr& vertex);

	void OnOk(wxCommandEvent& e);

	void OnNormalizeNormal(wxCommandEvent& e);

private:
	void setPosition(const Math::Vector3d& pos);

	void setNormal(const Math::Vector3d& norm);

	void setTexCoord(const Math::Vector3d& texCoord);

	Math::Vector3d getPosition() const;

	Math::Vector3d getNormal() const;

	Math::Vector3d getTexCoord() const;

	wxSpinCtrlDouble* positionX;
	wxSpinCtrlDouble* positionY;
	wxSpinCtrlDouble* positionZ;

	wxSpinCtrlDouble* normalX;
	wxSpinCtrlDouble* normalY;
	wxSpinCtrlDouble* normalZ;

	wxSpinCtrlDouble* texCoordX;
	wxSpinCtrlDouble* texCoordY;
	wxSpinCtrlDouble* texCoordZ;

	Graphics::VertexSPtr vertex;
};
*/

class FacePropertyDialog : public wxDialog {
public:
	FacePropertyDialog(wxWindow* parent, const Graphics::Face& f);
};

class EdgePropertyDialog : public wxDialog
{
public:
	EdgePropertyDialog(wxWindow* parent, Graphics::HalfEdge& edge);

private:
	Graphics::HalfEdge& edge;

	wxSpinCtrl* startId;

	wxSpinCtrl* endId;
};

class PolygonPropertyDialog : public wxDialog
{
public:
	PolygonPropertyDialog(wxWindow* parent, Graphics::Polygon& polygon);

private:
	Graphics::Polygon& polygon;

	wxSpinCtrl* vertices;
	wxSpinCtrl* edges;
	wxSpinCtrl* faces;
};

class LightProperty : public wxPropertyGrid {
public:
	LightProperty(wxWindow* parent, const wxSize& size);

	void setValue(Graphics::LightSPtr light);

private:
	Graphics::LightSPtr light;

	void OnChange(wxPropertyGridEvent& event);
};

class MaterialProperty : public wxPropertyGrid {
public:
	MaterialProperty(wxWindow* parent, const wxSize& size);

	void setValue(Graphics::Material* material);

	void OnChange(wxPropertyGridEvent& event);

	void OnDoubleClick(wxPropertyGridEvent& event);

private:
	Graphics::Material* m;
	//wxColourProperty* diffuse;

	wxString getImageFile();

};

class PolygonProperty : public wxPropertyGrid {
public:
	PolygonProperty(wxWindow* parent, const wxSize& size, const std::list<Graphics::Material*>& materials);

	void build(Graphics::Polygon* polygon);

	void OnDoubleClick(wxPropertyGridEvent& event);

	void OnChanged(wxPropertyGridEvent& event);

private:
	Graphics::Polygon* polygon;
	const std::list<Graphics::Material*>& materials;
};

}
}

#endif