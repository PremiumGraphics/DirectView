#ifndef __CRYSTAL_IO_AVS_UCD_CONVERTER_H__
#define __CRYSTAL_IO_AVS_UCD_CONVERTER_H__

#include "AVSCell.h"
#include "VTKCell.h"

namespace Crystal {
	namespace IO {

class AVSCell;
class VTKCell;
class VTKObject;
class AVSUCDFile;

class AVSUCDConverter {
public:
	static VTKObject* toVTKObject(const int id, const AVSUCDFile& file);

	static VTKCell* toVTKCell( AVSCell* cell );

	static VTKCellType toVTKCellType( const AVSCell::Type& src );
};

	}
}

#endif

#ifndef __CRYSTAL_IO_VTK_CONVERTER_H__
#define __CRYSTAL_IO_VTK_CONVERTER_H__

#include "VTKFile.h"

namespace Crystal {
	namespace IO {

class VTKConverter {
public:
	static VTKObject* toVTKObject( const VTKFile& file, const int id );

	static VTKAttributeVector toVTKAttributes( const VTKAttributePart_& attr );

	static std::list< Graphics::ColorRGBAMap<float>* > toColorMaps(const VTKAttributePart_& attr);

	static VTKFile toVTKFile( VTKObject* object );

};
	}
}

#endif

#ifndef __CRYSTAL_IO_VTK_OBJECT_FACTORY_H__
#define __CRYSTAL_IO_VTK_OBJECT_FACTORY_H__

#include "VTKFile.h"
#include "AVSUCDFile.h"
#include "VTKObject.h"

#include "../Graphics/ColorRGBAMap.h"

#include "AVSFLDFile.h"

#include <list>

namespace Crystal {
	namespace IO {

class AVSFLDConverter {
public:
	static VTKObject* toVTKObject(const int id, const AVSFLDFile& file);
};


class VTKObjectFactory {
public:
	VTKObjectFactory() :
		nextId( 0 )
	{
		//createDefaultColorMap();
	}

	~VTKObjectFactory() {
		clear();
	}

	VTKObject* createDiffuse();

	VTKObject* create(const VTKFile& file);

	VTKObject* create(const AVSUCDFile& file);

	VTKObject* create(const AVSFLDFile& file);

	void remove( VTKObject* object ) {
		objects.remove( object );
		delete object;
	}

	void clear() {
		for( VTKObject* object : objects ) {
			delete object;
		}
		objects.clear();
	}

	std::list< VTKObject* > getObjects() const { return objects; }

	//void applyMinMaxToColorMap();

	std::list< VTKObject* > getSelectedObjects() {
		std::list<VTKObject*> selected;
		for( VTKObject* object : objects ) {
			if( object->isSelected() ) {
				selected.push_back( object );
			}
		}
		return selected;
	}


private:
	int nextId;
	std::list< VTKObject* > objects;
};
	}
}

#endif