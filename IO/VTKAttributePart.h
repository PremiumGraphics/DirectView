#ifndef __CRYSTAL_IO_VTK_ATTRIBUTE_PART_H__
#define __CRYSTAL_IO_VTK_ATTRIBUTE_PART_H__

#include "../Math/Matrix3d.h"
#include "VTKType.h"
#include "VTKObject.h"
#include "Helper.h"

namespace Crystal {
	namespace IO {


struct VTKScalars {
	VTKScalars() :
		type( VTKType::FLOAT )
	{}

	void read(std::istream& stream, const int howMany );

	void write(std::ostream& stream ) const;

	VTKAttributes* toVTKAttributes() const;

	void setValues( const std::vector<float>& values ) { this->values = values; }

	std::vector< float > getValues() const { return values; }

	void setType( const VTKType& t ) { this->type = t; }

	VTKType getType() const { return type; }

	void setLookupTableName( const std::string& lookupTableName ) { this->lookupTableName = lookupTableName; }

	std::string getLookupTableName() const { return lookupTableName; }

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

private:
	std::vector< float > values;
	
	VTKType type;
	std::string name;
	std::string lookupTableName;
};

typedef std::vector< VTKScalars > VTKScalarsVector;

class VTKColorScalars {
public:

	void read( std::istream& stream, const int howMany ) {
		std::string str = Helper::read<std::string>(stream);
		assert( str == "COLOR_SCALARS");

		name = Helper::read<std::string>(stream);
		valuesNumber = Helper::read<int>(stream);
		
		for( int i = 0; i < howMany; ++i ) {
			std::vector< float > values( valuesNumber );
			for( int j = 0; j < valuesNumber; ++j ) {
				const float c = Helper::read<float>(stream);
				values[j] = c;
			}
		}
	}

	void write( std::ostream& stream ) const {

	}

	std::string getName() const { return name; }

private:
	std::string name;
	int valuesNumber;
};

typedef std::vector< VTKColorScalars > VTKColorScalarsVector;

struct VTKLookupTable {
	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

	void setColors( const std::vector< Graphics::ColorRGBA<float> >& colors ) { this->colors = colors; }

	std::vector< Graphics::ColorRGBA<float> > getColors() const { return colors; }

	void read( std::istream& stream );

	void write( std::ostream& stream ) const;

	Graphics::ColorRGBAMap<float>* toColorMap() const {
		Graphics::ColorRGBAMap<float>* map = new Graphics::ColorRGBAMap<float>( colors );
		map->setName( name );
		return map;
	}

private:
	std::string name;
	std::vector< Graphics::ColorRGBA<float> > colors;

};

typedef std::vector< VTKLookupTable > VTKLookupTableVector;

struct VTKVectors
{
	VTKVectors() : type( VTKType::FLOAT )
	{}

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

	void setValues( const std::vector< Math::Vector3d >& vs ) { values = vs; }

	std::vector< Math::Vector3d > getValues() const { return values; }

	VTKAttributes* toVTKAttributes() const;

	void setType( const VTKType& t ) { this->type = t; }

	VTKType getType() const { return type; }

	void read( std::istream& stream, const int howMany );

	void write( std::ostream& stream ) const;

private:
	std::string name;

	VTKType type;
	
	std::vector< Math::Vector3d > values;
};

typedef std::vector< VTKVectors > VTKVectorsVector;

struct VTKNormals {
public:
	void read( std::istream& stream, const int howMany );

	void write( std::ostream& stream ) const;

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

	void setValues( const std::vector< Math::Vector3d >& values ) { this->values = values; }

	std::vector< Math::Vector3d > getValues() const { return values; }

	VTKAttributes* toVTKAttributes() const;

	void setType( const VTKType& t ) { this->type = t; }

	VTKType getType() const { return type; }

private:
	std::string name;

	VTKType type;

	std::vector< Math::Vector3d > values;
};

typedef std::vector< VTKNormals > VTKNormalsVector;

struct VTKTexCoords
{
public:
	void read( std::istream& stream, const int howMany );

	void write( std::ostream& stream ) const;

	bool isValid() const {
		return (1 <= dim) && (3 <= dim);
	}

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

	VTKType getType() const { return type; }

	void setType( const VTKType& t ) { this->type = t; }

	void setDim( const int dim ) { this->dim = dim; }

	int getDim() const { return dim; }

	void setCoords( const std::vector< Math::Vector3d >& coords ) { this->coords = coords; }

	std::vector< Math::Vector3d > getValues() const { return coords; }

	VTKAttributes* toVTKAttributes() const {
		VTKAttributes* attr = new VTKAttributes();
		attr->setDim( 3 );
		attr->setName( name );
		std::vector< float > vs;
		for( const Math::Vector3d& v : coords ) {
			const std::vector< float >& ar = v.toArray();
			vs.insert( vs.end(), ar.begin(), ar.end() );
		}
		attr->setValues( vs );
		return attr;
	}

private:
	std::string name;
	int dim;
	VTKType type;
	std::vector< Math::Vector3d > coords;
};

typedef std::vector< VTKTexCoords > VTKTexCoordsVector;

struct VTKTensors
{
public:
	void read( std::istream& stream, const int howMany );

	void write( std::ostream& stream) const;

	std::string getName() const { return name; }

	std::vector< Math::Matrix3d<float> > getTensors() const { return tensors; }

private:
	std::vector< Math::Matrix3d<float> > tensors;

	std::string name;
};

typedef std::vector< VTKTensors > VTKTensorsVector;

struct VTKField {
	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

	void setNumComponents( const int n ) { this->numComponents = n; }

	int getNumComponents() const { return numComponents; }

	void setNumTuples( const int n ) { this->numTuples = n; }

	int getNumTuples() const { return numTuples; }

	void setValues( const std::vector<float>& values ) { this->values = values; }

	std::vector< float > getValues() const { return values; }

	void read(std::istream& stream);

	void write(std::ostream& stream) const;

	VTKAttributes* toVTKAttributes() const;

	static std::vector<VTKField> readFields(std::istream& stream);

private:
	std::string name;
	int numComponents;
	int numTuples;
	std::vector< float > values;
};

typedef std::vector< VTKField > VTKFieldVector;


struct VTKAttributePart_ {
	void setScalars( const VTKScalarsVector& scalars ) { this->scalars = scalars; }

	VTKScalarsVector getScalars() const { return scalars; }

	void setColorScalars( const VTKColorScalarsVector& cs ) { this->colorScalars = cs; }

	VTKColorScalarsVector getColorScalars() const { return colorScalars; }

	void setVectors( const VTKVectorsVector& vectors ) { this->vectors = vectors; }

	VTKVectorsVector getVectors() const { return vectors; }

	VTKNormalsVector getNormals() const { return normals; }

	VTKTexCoordsVector getTexCoords() const { return texCoords; }

	VTKTensorsVector getTensors() const { return tensors; }

	VTKLookupTableVector getLookupTables() const { return tables; }

	VTKFieldVector getFields() const { return fields; }

	void read( std::istream& stream );

	void write( std::ostream& stream ) const;

	void setSize( const int howMany ) { this->howMany = howMany; }

	size_t size() const {
		return howMany;
	}

	bool isEmpty() const { 
		return
			scalars.empty() &&
			colorScalars.empty() &&
			vectors.empty() &&
			normals.empty() &&
			texCoords.empty() &&
			tensors.empty() &&
			tables.empty() &&
			fields.empty();
	}

private:
	VTKScalarsVector scalars;
	VTKColorScalarsVector colorScalars;
	VTKVectorsVector vectors;
	VTKNormalsVector normals;
	VTKTexCoordsVector texCoords;
	VTKTensorsVector tensors;
	VTKLookupTableVector tables;
	VTKFieldVector fields;

	size_t howMany;
};

class VTKAttributePart
{
public:
	void read( std::istream& stream );

	void write( std::ostream& stream ) const;

	VTKAttributePart_ getCellAttribute() const { return cellAttribute; }

	void setCellAttribute( const VTKAttributePart_& attr ) { this->cellAttribute = attr; }

	VTKAttributePart_ getPointAttribute() const { return pointAttribute; }

	void setPointAttribute( const VTKAttributePart_& attr ) { this->pointAttribute = attr; }

private:
	VTKAttributePart_ cellAttribute;
	VTKAttributePart_ pointAttribute;
};




	}
}
#endif