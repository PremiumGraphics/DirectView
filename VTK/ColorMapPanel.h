#ifndef __CRYSTAL_APP_COLOR_MAP_PANEL_H__
#define __CRYSTAL_APP_COLOR_MAP_PANEL_H__


#include <vector>

#include "../Graphics/ColorRGBAMap.h"

#include "ColorMapCanvas.h"

namespace Crystal {
	namespace App {

class ColorMapPanel : public wxDialog {
public:
	ColorMapPanel( wxWindow* parent, const wxPoint& position, Graphics::ColorRGBAMap<float>* colorMap );

private:
    void OnPaint( wxPaintEvent& WXUNUSED(event) );

	ColorMapCanvas *m_canvas;
	Graphics::ColorRGBAMap<float>* colorMap;

	wxImage toImage( const int width, const int height ) const;

	void OnSave( wxCommandEvent& e );

	void OnLoad( wxCommandEvent& e );

};

	}
}

#endif