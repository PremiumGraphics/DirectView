#ifndef __CRYSTAL_IO_VTK_ATTRIBUTE_H__
#define __CRYSTAL_IO_VTK_ATTRIBUTE_H__

#include <vector>
#include <algorithm>

#include "../Graphics/ColorRGBAMap.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {
class VTKAttributes {
public:
	VTKAttributes() :
		selected( false )
	{}

	void setDim( int dim ) { this->dim = dim; }

	int getDim() const { return dim; }

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

	void setUnit( const std::string& unit ) { this->unit = unit; }

	std::string getUnit() const { return unit; }

	void setType( const std::string& type ) { this->type = type; }

	std::string getType() const { return type; }

	float getMin() const { return *std::min_element( values.begin(), values.end() ); }

	float getMax() const { return *std::max_element( values.begin(), values.end() ); }

	void add( const float v ) { this->values.push_back( v ); }

	void add( const std::vector<float>& v ) { this->values.insert( values.end(), v.begin(), v.end() ); }

	void setValues( const std::vector<float>& values ) { this->values = values; }

	std::vector<float> getValues() const { return values; }

	std::vector< std::vector<float> > toDimensionalArrays( const int dim ) const {
		std::vector< std::vector< float > > arrays;
		int index =0;
		for( unsigned i = 0; i < values.size() / dim; ++i ) {
			std::vector< float > ar;
			for( int j = 0; j < dim; ++j ) {
				ar.push_back( values[index++] );
			}
			arrays.push_back( ar );
		}
		return arrays;
	}

	std::vector< Math::Vector3d > toVector3ds() const {
		assert( dim >= 0 );
		std::vector< Math::Vector3d > vectors;
		for( size_t index = 0; index < values.size(); ) {
			float x = 0.0;
			float y = 0.0;
			float z = 0.0;
			if( dim >= 1 ) {
				x = values[index];
			}
			if( dim >= 2 ) {
				y = values[index+1];
			}
			if( dim >= 3 ) {
				z = values[index+2];
			}
			/*
			if( dim <= 3 ) {
				index += 3;
			}
			else { */
				index += dim;
			//}
			vectors.push_back( Math::Vector3d( x, y, z ) );
		}
		return vectors;
	}

	void setLookupTableName( const std::string& name ) { this->tableName = name; }

	std::string getLookupTableName() const { return tableName; }

	bool isSelected() const { return selected; }

	void setSelected( const bool b ) { this->selected = b; }

private:
	bool selected;
	int dim;
	std::string name;
	std::string unit;
	std::string type;
	std::vector< float > values;
	std::string tableName;
};

typedef std::vector< VTKAttributes* > VTKAttributeVector;
	}
}

#endif