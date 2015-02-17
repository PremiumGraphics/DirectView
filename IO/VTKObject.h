#ifndef __CRYSTAL_IO_VTK_OBJECT_H__
#define __CRYSTAL_IO_VTK_OBJECT_H__

#include "../Math/Box.h"
#include "../Graphics/ColorRGBAMap.h"

#include "VTKAttribute.h"
#include "VTKCell.h"

#include <list>
#include <algorithm>

namespace Crystal {
	namespace IO {



class VTKObject {
public:

	VTKObject( const int id ) :
	id( id ),
	selected( true )
	{}

	~VTKObject();

	unsigned int getId() const { return id; }

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

	void addNodeAttribute( VTKAttributes* attribute ) { this->nodeAttributes.push_back( attribute ); }

	void setNodeAttribute( const VTKAttributeVector& attributes ) { this->nodeAttributes = attributes; }

	VTKAttributeVector getNodeAttributes() const { return nodeAttributes; }

	void addCellAttribute( VTKAttributes* attribute ) { this->cellAttributes.push_back( attribute ); } 

	void setCellAttribute( const VTKAttributeVector& attributes ) { this->cellAttributes = attributes; }

	VTKAttributeVector getCellAttributes() const { return cellAttributes; }

	void addColorMap( Graphics::ColorRGBAMap<float>* map ) { colorMaps.push_back( map ); }

	void removeColorMap( Graphics::ColorRGBAMap<float>* map ) { colorMaps.remove( map ); }

	std::list< Graphics::ColorRGBAMap<float>* > getColorMaps() const { return colorMaps; }

	Graphics::ColorRGBAMap<float>* getColorMap( const std::string& name ) {
		for( Graphics::ColorRGBAMap<float>* map : colorMaps ) {
			if( map->getName() == name ) {
				return map;
			}
		}
		return nullptr;
	}

	void addCell( VTKCell* cell ) { this->cells.push_back( cell ); }

	std::vector< VTKCell* > getCells() const { return cells; }

	void setVertices( const Math::VectorVector& vs ) { this->vertices = vs; }

	Math::VectorVector getVertices() const { return vertices; }

	Math::VectorVector getCellCenters() const;

	Math::Box getBoundingBox() const;

	bool isSelected() const { return selected; }

	void setIsSelected(const bool b) { this->selected = b; }

	Graphics::ColorRGBAMap<float>* createDefaultColorMap();

	void setConnections( const ConnectionVector& connections ) { this->connections = connections; }

	ConnectionVector getConnections() const { return connections; }

private:
	const unsigned int id;
	bool selected;
	std::string name;
	Graphics::ColorRGBAMap<float> map;
	std::vector< VTKCell* > cells;
	Math::VectorVector vertices;
	VTKAttributeVector nodeAttributes;
	VTKAttributeVector cellAttributes;
	std::list< Graphics::ColorRGBAMap<float>* > colorMaps;

	ConnectionVector connections;

};

	}
}

#endif