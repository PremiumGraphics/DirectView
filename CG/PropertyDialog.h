#ifndef __CRYSTAL_APP_PROPERTY_DIALOG_H__
#define __CRYSTAL_APP_PROPERTY_DIALOG_H__

#include <stdafx.h>

#include "../Graphics/Vertex.h"
#include "../Graphics/Face.h"
#include "../Graphics/Polygon.h"

namespace Crystal{
	namespace CG{

class VertexPropertyDialog : public wxDialog {
public:
	VertexPropertyDialog(wxWindow* parent, Graphics::Vertex& vertex);

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

	Graphics::Vertex& vertex;
};

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

	}
}

#endif