#ifndef __CRYSTAL_APP_VTK_PROPERTY_GRID_H__
#define __CRYSTAL_APP_VTK_PROPERTY_GRID_H__

#include "../IO/VTKObject.h"
#include "../IO/VTKObjectFactory.h"

namespace Crystal {
	namespace App {
		class View;
class VTKPropertyGrid : public wxPropertyGrid
{
public:
	VTKPropertyGrid( wxWindow* parent, View* view, const wxPoint position, const wxSize& size );

	void build(IO::VTKObject* object);

	void build(IO::VTKAttributes* attribute, IO::VTKObject* object );

private:
	void OnChange( wxPropertyGridEvent& e );

	IO::VTKObject* object;
	IO::VTKAttributes* attr;

	wxEnumProperty* prop;
	View* view;
};
	}
}

#endif
