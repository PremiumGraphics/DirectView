#ifndef __CRYSTAL_APP_COLOR_MAP_CANVAS_H__
#define __CRYSTAL_APP_COLOR_MAP_CANVAS_H__

#include "../Graphics/ColorRGBAMap.h"

namespace Crystal {
	namespace App {

class ColorMapCanvas : public wxScrolledWindow
{
public:
    ColorMapCanvas(wxWindow *parent, const wxPoint& pos, const wxSize& size, Graphics::ColorRGBAMap<float>* colorMap );

protected:
    virtual void OnDraw(wxDC& dc);

private:
	Graphics::ColorRGBAMap<float>* colorMap;
};

	}
}

#endif