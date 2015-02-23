#include "VTKObjectFactory.h"

#include "AVSUCDFile.h"

#include "VTKObject.h"
#include "VTKCell.h"


using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

VTKObject* VTKConverter::toVTKObject( const VTKFile& file, int id )
{
	const std::vector< Vector3d >& points = file.getGeometryPart().getPoints().getPoints();
	Vector3dVector vertices = points;

	std::vector< VTKCell* > cs;
	for( const VTKCell_& c : file.getGeometryPart().getCells() ) {
		const std::vector<unsigned int>& indices = c.getIndices();
		cs.push_back( VTKCell::create( c.getType(), indices ) );
	}

	VTKObject* object = new VTKObject( id );

	object->setVertices( points );

	ConnectionVector connections;
	for( VTKCell* c : cs ) {
		object->addCell( c );
		const ConnectionVector& cs = c->getConnections();
		connections.insert( connections.end(), cs.begin(), cs.end() );
	}
	object->setConnections( connections );

	/*for( VTKCell* c : cs ) {
		delete c;
	}
	cs.clear();*/

	object->setName( file.getHeaderPart().getTitle() );
	object->setNodeAttribute( VTKConverter::toVTKAttributes( file.getAttributePart().getPointAttribute() ) );
	object->setCellAttribute( VTKConverter::toVTKAttributes( file.getAttributePart().getCellAttribute() ) );
	object->createDefaultColorMap();

	std::list< ColorRGBAMap<float >* > maps = VTKConverter::toColorMaps( file.getAttributePart().getPointAttribute() );
	std::list< ColorRGBAMap<float >* > cellColorMaps = VTKConverter::toColorMaps( file.getAttributePart().getCellAttribute() );

	for( ColorRGBAMap<float>* m : maps ) {
		object->addColorMap( m );
	}

	for( ColorRGBAMap<float>* m : cellColorMaps ) {
		object->addColorMap( m );
	}

	return object;

}

VTKAttributeVector VTKConverter::toVTKAttributes(const VTKAttributePart_& attr) {
	VTKAttributeVector attributes;
	const std::vector<VTKScalars>& scalars = attr.getScalars();
	const std::vector<VTKVectors>& vectors = attr.getVectors();
	const std::vector<VTKNormals>& normals = attr.getNormals();
	const std::vector<VTKTexCoords>& texCoords = attr.getTexCoords();
	const std::vector<VTKTensors>& tensors = attr.getTensors();
	const VTKFieldVector& fields = attr.getFields();
	for( const VTKScalars& s : scalars ) {
		attributes.push_back( s.toVTKAttributes() );
	}
	for( const VTKVectors& v : vectors ) {
		attributes.push_back( v.toVTKAttributes() );
	}
	for( const VTKNormals& n : normals ) {
		attributes.push_back( n.toVTKAttributes() );
	}
	for( const VTKTexCoords& t : texCoords ) {
		attributes.push_back( t.toVTKAttributes() );
	}
	for( const VTKField& field : fields ) {
		attributes.push_back( field.toVTKAttributes() );
	}
	/*
	if( !tensors.getTensors().empty() ) {
		const VTKAttributes& attr = tensors.to
	}
	*/

	return attributes;
};


std::list< ColorRGBAMap<float>* > VTKConverter::toColorMaps(const VTKAttributePart_& attr)
{
	std::list< ColorRGBAMap<float>* > maps;
	for( const VTKLookupTable& table:  attr.getLookupTables() ) {
		maps.push_back( table.toColorMap() );
	}
	return maps;
}

VTKFile VTKConverter::toVTKFile( VTKObject* object )
{
	VTKFile file;
//	object->getVertices();
//	file.setGeometryPart( );
	return file;
}

VTKObject* AVSUCDConverter::toVTKObject(const int id, const AVSUCDFile& file)
{
	VTKObject* object = new VTKObject( id );

	Vector3dVector vertices = file.getGeom().getNode().getPositions();

	object->setVertices( vertices );

	for( const AVSComponent& component : file.getComponent().getNodeComponents() ) {
		const VTKAttributeVector& attributes = component.toVTKAttributes();
		object->setNodeAttribute( attributes );
	}

	for( const AVSComponent& component : file.getComponent().getElementComponents() ) {
		const VTKAttributeVector& attributes = component.toVTKAttributes();
		object->setCellAttribute( attributes );
	}

	ConnectionVector connections;
	for( const AVSElement_& elem : file.getGeom().getElement().getCells() ) {
		AVSCell* cell = elem.toCell();
		object->addCell( toVTKCell( cell ) );
		const ConnectionVector& cs = cell->getConnections();
		connections.insert( connections.end(), cs.begin(), cs.end() );
		delete cell;
	}
	object->setConnections( connections );

	object->setName( file.getHeader().getComment() );

	object->createDefaultColorMap();

	return object;
}

VTKCell* AVSUCDConverter::toVTKCell( AVSCell* cell )
{
	const VTKCellType& type = toVTKCellType( cell->getType() );
	//ConnectionVector indices = cell->getConnections();
/*	for( unsigned int& i : indices ) {
		i--;
	}
	*/
	return VTKCell::create( type, cell->getIndices() );
}


VTKCellType AVSUCDConverter::toVTKCellType( const AVSCell::Type& src )
{
	switch( src ) {
	case AVSCell::Type::Point :
		return VTKCellType::VERTEX;
	case AVSCell::Type::Line :
		return VTKCellType::LINE;
	case AVSCell::Type::Tri:
		return VTKCellType::TRIANGLE;
	case AVSCell::Type::Quad:
		return VTKCellType::QUAD;
	case AVSCell::Type::Tet:
		return VTKCellType::TETRA;
	case AVSCell::Type::Pyr :
		return VTKCellType::PYRAMID;
	case AVSCell::Type::Prism :
		return VTKCellType::WEDGE;
	case AVSCell::Type::Hex :
		return VTKCellType::HEXAHEDRON;
	default:
		assert( false );
		return VTKCellType::NONE;
	}
}

VTKObject* AVSFLDConverter::toVTKObject(const int id, const AVSFLDFile& file)
{
	VTKObject* object = new VTKObject( id );
	object->setName( "" );

	const std::vector< Vector3d >& positions = file.toPositions();
	object->setVertices( positions );

	VTKAttributeVector attrs;
	VTKAttributes* attr = new VTKAttributes();
	attr->setName( "TestName" );
	attr->setUnit( "TestUnit" );
	attr->setLookupTableName( "default" );
	attr->setDim( file.getVecLength() );
	attr->setValues( file.toScalarValues() );
	attrs.push_back( attr );

	object->setNodeAttribute( attrs );
	object->createDefaultColorMap();

	return object;
}

VTKObject* VTKObjectFactory::createDiffuse()
{
	VTKFile file;
	file.setDiffuseData();
	return create( file );
}

VTKObject* VTKObjectFactory::create( const VTKFile& file )
{
	VTKObject* object = VTKConverter::toVTKObject( file, nextId++ );
	objects.push_back( object );
	return object;
}


VTKObject* VTKObjectFactory::create(const AVSUCDFile& file)
{
	VTKObject* object = AVSUCDConverter::toVTKObject( nextId++, file );
	objects.push_back( object );
	return object;
}

VTKObject* VTKObjectFactory::create(const AVSFLDFile& file)
{
	VTKObject* object = AVSFLDConverter::toVTKObject( nextId++, file );
	objects.push_back( object );
	return object;
}
