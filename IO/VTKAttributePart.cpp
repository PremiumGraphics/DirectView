#include "VTKAttributePart.h"

#include "Helper.h"


using namespace Crystal::Math;
using namespace Crystal::IO;

void VTKAttributePart::read(std::istream& stream) {
	std::string str = Helper::read<std::string>(stream);
	while( str == "CELL_DATA" || str == "POINT_DATA") {
		if( str == "CELL_DATA" ) {
			cellAttribute.read( stream );
			str = Helper::read<std::string>(stream);
			continue;
		}
		if( str == "POINT_DATA" ) {
			pointAttribute.read( stream );
			str = Helper::read<std::string>(stream);
			continue;
		}
	}
}

void VTKAttributePart::write( std::ostream& stream ) const
{
	if( !cellAttribute.isEmpty() ) {
		stream << "CELL_DATA " << cellAttribute.size() << std::endl;
		cellAttribute.write( stream );
	}
	if( !pointAttribute.isEmpty() ) {
		stream << "POINT_DATA " << pointAttribute.size() << std::endl;
		pointAttribute.write( stream );
	}
}

void VTKAttributePart_::read( std::istream& stream )
{
	const int howMany = Helper::read<int>(stream);
	std::string str = Helper::readNextString(stream);

	while( true ) {
		if( str == "SCALARS" ) {
			VTKScalars s;
			s.read(stream, howMany );
			scalars.push_back( s );
			str = Helper::readNextString(stream);
			continue;
		}
		else if( str == "COLOR_SCALARS" ) {
			VTKColorScalars cs;
			cs.read( stream, howMany );
			cs.read( stream, howMany );
			colorScalars.push_back( cs );
			str = Helper::readNextString(stream);
			continue;
		}
		else if( str == "LOOKUP_TABLE" ) {
			VTKLookupTable table;
			table.read( stream );
			tables.push_back( table );
			str = Helper::readNextString(stream);
			continue;
		}
		else if( str == "VECTORS" ) {
			VTKVectors v;
			v.read( stream, howMany );
			vectors.push_back( v );
			str = Helper::readNextString(stream);
			continue;
		}
		else if( str == "NORMALS" ) {
			VTKNormals n;
			n.read( stream, howMany );
			normals.push_back( n );
			str = Helper::readNextString(stream);
			continue;
		}
		else if( str == "TEXTURE_COORDINATES" ) {
			VTKTexCoords t;
			t.read( stream, howMany );
			texCoords.push_back( t );
			str = Helper::readNextString(stream);
			continue;
		}
		else if( str == "TENSORS" ) {
			VTKTensors t;
			t.read( stream, howMany );
			tensors.push_back( t );
			str = Helper::readNextString(stream);
			continue;
		}
		else if( str == "FIELD" ) {
			str = Helper::read<std::string>(stream);
			const std::string& dataName = Helper::read<std::string>(stream);
			const int numArrays = Helper::read<int>(stream);

			for( int i = 0; i < numArrays; ++i ) {
				VTKField field;
				field.read( stream );
				fields.push_back( field );
			}
			str = Helper::readNextString(stream);
			continue;
		}
		else {
			return;
		}
	}
}

void VTKAttributePart_::write( std::ostream& stream ) const
{
	for( const VTKScalars& s : scalars ) {
		s.write(stream);
	}
	for( const VTKColorScalars& s : colorScalars ) {
		s.write(stream);
	}
	for( const VTKLookupTable& t : tables ) {
		t.write(stream);
	}
	for( const VTKVectors& v : vectors ) {
		v.write(stream);
	}
	for( const VTKNormals& n : normals ) {
		n.write(stream);
	}
	for( const VTKTexCoords& t : texCoords ) {
		t.write(stream);
	}
	for( const VTKTensors& t : tensors ) {
		t.write(stream);
	}
	for( const VTKField& f : fields ) {
		f.write(stream);
	}
}


void VTKScalars::read( std::istream& stream, const int howMany ) {
	std::string str;
	str = Helper::read<std::string>(stream);
	assert( str == "SCALARS");

	name = Helper::read<std::string>(stream);
	str = Helper::read<std::string>(stream);
	type = VTKType( str );

	str = Helper::read<std::string>(stream);
	if( str == "LOOKUP_TABLE" ) {
		lookupTableName = Helper::read<std::string>(stream);
		for( int i = 0; i < howMany; ++i ) {
			values.push_back( Helper::read<float>(stream) );
		}
		return;
	}
	else {
		int i = ::atoi(str.c_str());
	}

	str = Helper::read<std::string>(stream);
	if( str == "LOOKUP_TABLE" ) {
		lookupTableName = Helper::read<std::string>(stream);
		for( int i = 0; i < howMany; ++i ) {
			values.push_back( Helper::read<float>(stream) );
		}
	}
}

void VTKScalars::write( std::ostream& stream ) const
{
	stream << "SCALARS " << name << " " << type.toString() << std::endl;
	stream << "LOOKUP_TABLE " << lookupTableName << std::endl;

	for( float v : values ) {
		stream << v << std::endl;
	}
	return;
}


VTKAttributes* VTKScalars::toVTKAttributes() const
{
	VTKAttributes* attr = new VTKAttributes;
	attr->setDim( 1 );
	attr->setName( name );
	attr->setType( type.toString() );
	attr->setValues( values );
	attr->setLookupTableName( lookupTableName );
	return attr;
}


void VTKLookupTable::read( std::istream& stream ) {
	std::string str = Helper::read<std::string>(stream);
	assert( str == "LOOKUP_TABLE" );
	name = Helper::read<std::string>(stream);
	int howMany = Helper::read<int>(stream);
	for( int i = 0; i < howMany; ++i ) {
		const float red = Helper::read<float>(stream);
		const float green = Helper::read<float>(stream);
		const float blue = Helper::read<float>(stream);
		const float alpha = Helper::read<float>(stream);
		Graphics::ColorRGBA<float> color( red, green, blue, alpha );
		colors.push_back( color );
	}
}

void VTKLookupTable::write( std::ostream& stream ) const
{
	stream << "LOOKUP_TABLE " << name << " " << colors.size() << std::endl;
	for( const Graphics::ColorRGBA<float>& c : colors ) {
		stream << c.getRed() << " " << c.getGreen() << " " << c.getBlue() << " " << c.getAlpha() << std::endl;
	}
}

void VTKVectors::read( std::istream& stream, const int howMany )
{
	std::string str;
	str = Helper::read<std::string>(stream);
	assert( str == "VECTORS");

	name = Helper::read<std::string>(stream);
	str = Helper::read<std::string>(stream);
	type = VTKType( str );
	for( int i = 0; i < howMany; ++i ) {
		const Math::Vector3d& normal = Helper::readVector(stream);
		values.push_back( normal );
	}
}

void VTKVectors::write( std::ostream& stream ) const
{
	stream << "VECTORS " << name << " " << type.toString() << std::endl;
	for( Vector3d v : values ) {
		stream << v.getX() << " " << v.getY() << " " << v.getZ() << std::endl;
	}
}

VTKAttributes* VTKVectors::toVTKAttributes() const
{
	VTKAttributes* attr = new VTKAttributes();
	attr->setDim( 3 );
	attr->setName( name );
	std::vector< float > vs;
	for( const Vector3d& v : values ) {
		const std::vector< float >& ar = v.toArray();
		vs.insert( vs.end(), ar.begin(), ar.end() );
	}
	attr->setValues( vs );
	return attr;
}

void VTKNormals::read( std::istream& stream, const int howMany )
{
	std::string str;
	str = Helper::read<std::string>(stream);
	assert( str == "NORMALS");
	name = Helper::read<std::string>(stream);
	type = Helper::read<std::string>(stream);
	for( int i = 0; i < howMany; ++i ) {
		const Math::Vector3d& normal = Helper::readVector(stream);
		values.push_back( normal );
	}
}

void VTKNormals::write( std::ostream& stream ) const
{
	stream << "NORMALS " << name << " " << type.toString() << std::endl;
	for( const Vector3d& v : values ) {
		stream << v.getX() << " " << v.getY() << " " << v.getZ() << std::endl;
	}
}

VTKAttributes* VTKNormals::toVTKAttributes() const
{
	VTKAttributes* attr = new VTKAttributes();
	attr->setDim( 3 );
	attr->setName( name );
	std::vector< float > vs;
	for( const Vector3d& v : values ) {
		const std::vector< float >& ar = v.toArray();
		vs.insert( vs.end(), ar.begin(), ar.end() );
	}
	attr->setValues( vs );
	return attr;
}

void VTKTexCoords::read( std::istream& stream, const int howMany )
{
	std::string str = Helper::read<std::string>(stream);
	assert( str == "TEXTURE_COORDINATES" );

	name = Helper::read<std::string>(stream);
	dim = Helper::read<int>(stream);
	type = Helper::read<std::string>(stream);
	for( int i = 0; i < howMany; ++i ) {
		const Math::Vector3d& coord = Helper::readVector(stream);
		coords.push_back( coord );
	}

	assert( isValid() );
}

void VTKTexCoords::write( std::ostream& stream ) const
{
	assert( isValid() );

	stream << "TEXTURE_COORDINATES " << name << " " << dim << " " << type.toString() << std::endl;
	for( const Vector3d& c : coords ) {
		stream << c.getX() << " " << c.getY() << " " << c.getZ() << std::endl;
	}
}

void VTKTensors::read( std::istream& stream, const int howMany )
{	
	std::string str = Helper::read<std::string>(stream);
	assert( str == "TENSORS" );
	name = Helper::read<std::string>(stream);
	const std::string& dataType = Helper::read<std::string>(stream);
	for( int i = 0; i < howMany; ++i ) {
		const Math::Vector3d& v0 = Helper::readVector(stream);
		const Math::Vector3d& v1 = Helper::readVector(stream);
		const Math::Vector3d& v2 = Helper::readVector(stream);
		Math::Matrix3d<float> m(
			v0.getX(), v0.getY(), v0.getZ(),
			v1.getX(), v1.getY(), v1.getZ(),
			v2.getX(), v2.getY(), v2.getZ()
			);
		tensors.push_back( m );
	}
}

void VTKTensors::write( std::ostream& stream ) const
{
	stream << "TENSORS ";
}

void VTKField::read(std::istream& stream)
{
	name = Helper::read<std::string>(stream);
	numComponents = Helper::read<int>(stream);
	numTuples = Helper::read<int>(stream);
	const std::string& dataType = Helper::read<std::string>(stream);
	for( int j = 0; j < numTuples; ++ j ) {
		for( int k = 0; k < numComponents; ++k ) {
			const float v = Helper::read<float>(stream);
			values.push_back( v );
		}
	}
}

void VTKField::write(std::ostream& stream) const
{
}

VTKAttributes* VTKField::toVTKAttributes() const
{
	VTKAttributes* attr = new VTKAttributes();
	attr->setName( name );
	attr->setDim( numComponents );
	attr->setValues( values );
	return attr;
}

std::vector<VTKField> VTKField::readFields(std::istream& stream)
{
	std::vector<VTKField> fields;
	std::string str = Helper::read<std::string>( stream );
	assert( str == "FIELD" );
	str = Helper::read<std::string>( stream );
	assert( str == "FieldData" );
	const size_t howMany = Helper::read<int>(stream);

	for( size_t i = 0; i < howMany; ++i ) {
		VTKField field;
		field.read( stream );
		fields.push_back( field );
	}
	return fields;
}