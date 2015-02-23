#include "gtest/gtest.h"

#include "VTKObjectFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

TEST( VTKConverterTest, TestToVTKAttributes )
{
	std::stringstream stream;
	stream
		//<< "POINT_DATA << std::endl
		<< "4" << std::endl
		<< "SCALARS name char 1" << std::endl
		<< "LOOKUP_TABLE default" << std::endl
		<< "1.0 2.0 3.0 4.0" << std::endl;

	VTKAttributePart_ attr;
	attr.read( stream );

	const VTKAttributeVector& attrs = VTKConverter::toVTKAttributes( attr );
	EXPECT_EQ( 1, attrs.size() );

	VTKAttributes* actual = attrs.front();
	EXPECT_EQ( "name", actual->getName() );
	EXPECT_EQ( "", actual->getUnit() );
	EXPECT_EQ( "char", actual->getType() );
	EXPECT_EQ( 4, actual->getValues().size() );

	for( VTKAttributes* attr: attrs ) {
		delete attr;
	}
}


TEST( AVSUCDConverterTest, TestToVTKType )
{
	EXPECT_EQ( VTKCellType::VERTEX,		AVSUCDConverter::toVTKCellType( AVSCell::Type::Point ) );
	EXPECT_EQ( VTKCellType::LINE,		AVSUCDConverter::toVTKCellType( AVSCell::Type::Line ) );
	EXPECT_EQ( VTKCellType::TRIANGLE,	AVSUCDConverter::toVTKCellType( AVSCell::Type::Tri ) );
	EXPECT_EQ( VTKCellType::QUAD,		AVSUCDConverter::toVTKCellType( AVSCell::Type::Quad ) );
	EXPECT_EQ( VTKCellType::TETRA,		AVSUCDConverter::toVTKCellType( AVSCell::Type::Tet ) );
	EXPECT_EQ( VTKCellType::WEDGE,		AVSUCDConverter::toVTKCellType( AVSCell::Type::Prism ) );
	EXPECT_EQ( VTKCellType::PYRAMID,	AVSUCDConverter::toVTKCellType( AVSCell::Type::Pyr ) );
}

TEST( AVSUCDConverterTest, TestToVTKCell )
{
	VertexIndices indices;
	indices.push_back( 0 );
	AVSCell* acell = AVSCell::create( AVSCell::Type::Point, indices );
	VTKCell* vcell = AVSUCDConverter::toVTKCell( acell );
	delete acell;
	delete vcell;
}

TEST( AVSUCDConverterTest, TestCreateAVSUCDScalar )
{
	std::stringstream stream;
	stream
		<< "1" << std::endl
		<< "data" << std::endl
		<< "step1" << std::endl
		<< "4 1" << std::endl
		<< "1 0.0 0.0 0.0" << std::endl
		<< "2 1.0 0.0 0.0" << std::endl
		<< "3 2.0 0.0 0.0" << std::endl
		<< "4 3.0 0.0 0.0" << std::endl
		<< "1 1 quad 1 2 3 4" << std::endl
		<< "0 1" << std::endl
		<< "1 1" << std::endl
		<< "scalar," << std::endl
		<< "1 0.1" << std::endl;

	AVSUCDFile file;
	file.read( stream );

	VTKObject* object = AVSUCDConverter::toVTKObject( 0, file );
	EXPECT_EQ( 0, object->getId() );

	EXPECT_EQ( 4, object->getVertices().size() );
	EXPECT_EQ( Vector3d( 0.0, 0.0, 0.0 ), object->getVertices().front() );
	EXPECT_EQ( Vector3d( 3.0, 0.0, 0.0 ), object->getVertices().back() );

	EXPECT_EQ( 1, object->getCells().size() );

	EXPECT_TRUE( object->getNodeAttributes().empty() );
	EXPECT_EQ( 1, object->getCellAttributes().size() );
	delete object;
}

TEST( AVSUCDConverterTest, TestCreateAVSUCDVector )
{
	std::stringstream stream;
	stream
		<< "1" << std::endl
		<< "data" << std::endl
		<< "step1" << std::endl
		<< "4 1" << std::endl
		<< "1 0.0 0.0 0.0" << std::endl
		<< "2 1.0 0.0 0.0" << std::endl
		<< "3 0.0 1.0 0.0" << std::endl
		<< "4 1.0 1.0 0.0" << std::endl
		<< "1 1 quad 1 2 4 3" << std::endl
		<< "3 0" << std::endl
		<< "1 3" << std::endl
		<< "velocity," << std::endl
		<< "1 0.0 -0.5 0.0" << std::endl
		<< "2 0.5 -0.5 0.0" << std::endl
		<< "3 0.5 0.0 0.0" << std::endl
		<< "4 0.25 0.5 0.0" << std::endl;

	AVSUCDFile file;
	file.read( stream );

	VTKObject* object = AVSUCDConverter::toVTKObject( 0, file );
	EXPECT_EQ( 0, object->getId() );
	EXPECT_EQ( 4, object->getVertices().size() );
	EXPECT_EQ( 1, object->getNodeAttributes().size() );
	//EXPECT_TRUE( object->getCellAttributes().empty() );
	delete object;
}

TEST( AVSUCDConverterTest, TestCreateLegacy )
{
	std::stringstream stream;
	stream
		<< "5 2 3 3 1" << std::endl
		<< "1 0.0 0.0 1.0" << std::endl
		<< "2 1.0 0.0 0.0" << std::endl
		<< "3 0.0 0.0 -1.0" << std::endl
		<< "4 0.0 0.0 0.0" << std::endl
		<< "5 0.0 1.0 0.0" << std::endl
		<< "1 1 tet 2 4 3 5" << std::endl
		<< "2 1 tet 2 5 1 4" << std::endl
		<< "3 1 1 1" << std::endl
		<< "stress x,lb" << std::endl
		<< "stress y,lb" << std::endl
		<< "stress z,lb" << std::endl
		<< "1 1.0 0.1 1.1" << std::endl
		<< "2 2.0 0.2 2.2" << std::endl
		<< "3 3.0 0.3 3.3" << std::endl
		<< "4 4.0 0.4 4.4" << std::endl
		<< "5 5.0 0.5 5.5" << std::endl
		<< "3 1 1 1" << std::endl
		<< "temp1, K" << std::endl
		<< "temp2, K" << std::endl
		<< "temp3, K" << std::endl
		<< "1 10.0 20.0 30.0" << std::endl
		<< "2 40.0 50.0 60.0" << std::endl
		<< "1 1" << std::endl
		<< "mises, X" << std::endl
		<< "1 500" << std::endl;

	AVSUCDFile file;
	file.readLegacy( stream );

	VTKObject* object = AVSUCDConverter::toVTKObject( 0, file );

	EXPECT_EQ( 0, object->getId() );

	EXPECT_EQ( 5, object->getVertices().size() );
	EXPECT_EQ( 2, object->getCells().size() );

	EXPECT_EQ( 3, object->getNodeAttributes().size() );
	EXPECT_EQ( 3, object->getCellAttributes().size() );
	delete object;
}

TEST( AVSFLDConverterTest, TestCreate )
{
	std::stringstream stream;
	stream
		<< "#AVS" << std::endl
		<< "ndim = 2" << std::endl
		<< "dim1 = 2" << std::endl
		<< "dim2 = 2" << std::endl
		<< "nspace = 2" << std::endl
		<< "veclen = 2" << std::endl
		<< "data = float" << std::endl
		<< "field = irregular" << std::endl;

	AVSFLDDataFile geom;
	geom.setValues({ 0.0, 1.0, 2.0, 3.0 } );

	AVSFLDDataFile geom2;
	geom2.setValues({ 10.0, 11.0, 12.0, 13.0 });

	const std::vector< AVSFLDDataFile > geoms{ geom, geom2 };

	AVSFLDFile file;
	file.setGeoFiles( geoms );
	file.read(stream);
	VTKObject* object = AVSFLDConverter::toVTKObject( 0, file );
	const Vector3dVector& positions = object->getVertices();
 	EXPECT_EQ( 4, positions.size() );

	const Vector3dVector expected = {
		Vector3d(0.0f, 10.0f, 0.0f),
		Vector3d(1.0f, 11.0f, 0.0f),
		Vector3d(2.0f, 12.0f, 0.0f),
		Vector3d(3.0f, 13.0f, 0.0f)
	};
	EXPECT_EQ( expected, positions );
}

TEST( VTKObjectFactoryTest, TestCreateVTKFilePolyData )
{
	std::stringstream stream;
		stream
			<< "# vtk DataFile Version 2.0" << std::endl
			<< "Cube example" << std::endl
			<< "ASCII" << std::endl
			<< "DATASET POLYDATA" << std::endl
			<< "POINTS 8 float" << std::endl
			<< "0.0 0.0 0.0" << std::endl
			<< "1.0 0.0 0.0" << std::endl
			<< "1.0 1.0 0.0" << std::endl
			<< "0.0 1.0 0.0" << std::endl
			<< "0.0 0.0 1.0" << std::endl
			<< "1.0 0.0 1.0" << std::endl
			<< "1.0 1.0 1.0" << std::endl
			<< "0.0 1.0 1.0" << std::endl
			<< "POLYGONS 6 30" << std::endl
			<< "4 0 1 2 3" << std::endl
			<< "4 4 5 6 7" << std::endl
			<< "4 0 1 5 4" << std::endl
			<< "4 2 3 7 6" << std::endl
			<< "4 0 4 7 3" << std::endl
			<< "4 1 2 6 5" << std::endl
			<< "CELL_DATA 6" << std::endl
			<< "SCALARS cell_scalars int 1" << std::endl
			<< "LOOKUP_TABLE default" << std::endl
			<< "0" << std::endl
			<< "1" << std::endl
			<< "2" << std::endl
			<< "3" << std::endl
			<< "4" << std::endl
			<< "5" << std::endl
			<< "NORMALS cell_normals float" << std::endl
			<< "0 0 -1" << std::endl
			<< "0 0 1" << std::endl
			<< "0 -1 0" << std::endl
			<< "0 1 0" << std::endl
			<< "-1 0 0" << std::endl
			<< "1 0 0" << std::endl
			<< "FIELD FieldData 2" << std::endl
			<< "cellIds 1 6 int" << std::endl
			<< "0 1 2 3 4 5" << std::endl
			<< "faceAttributes 2 6 float" << std::endl
			<< "0.0 1.0 1.0 2.0 2.0 3.0 3.0 4.0 4.0 5.0 5.0 6.0" << std::endl
			<< "POINT_DATA 8" << std::endl
			<< "SCALARS sample_scalars float 1" << std::endl
			<< "LOOKUP_TABLE my_table" << std::endl
			<< "0.0" << std::endl
			<< "1.0" << std::endl
			<< "2.0" << std::endl
			<< "3.0" << std::endl
			<< "4.0" << std::endl
			<< "5.0" << std::endl
			<< "6.0" << std::endl
			<< "7.0" << std::endl
			<< "LOOKUP_TABLE my_table 8" << std::endl
			<< "0.0 0.0 0.0 1.0" << std::endl
			<< "1.0 0.0 0.0 1.0" << std::endl
			<< "0.0 1.0 0.0 1.0" << std::endl
			<< "1.0 1.0 0.0 1.0" << std::endl
			<< "0.0 0.0 1.0 1.0" << std::endl
			<< "1.0 0.0 1.0 1.0" << std::endl
			<< "0.0 1.0 1.0 1.0" << std::endl
			<< "1.0 1.0 1.0 1.0" << std::endl;

	VTKFile file;
	file.read( stream );

	VTKObjectFactory factory;
	VTKObject* object = factory.create( file );
	EXPECT_EQ( "Cube example", object->getName() );

	EXPECT_EQ( 6, object->getCells().size() ); 

	const VTKAttributeVector& attributes = object->getCellAttributes(); 
	EXPECT_EQ( 4, attributes.size() );
	EXPECT_EQ( "cell_scalars", attributes.front()->getName() );
	EXPECT_EQ( "cell_normals", attributes[1]->getName() );
	EXPECT_EQ( "cellIds", attributes[2]->getName() );
	EXPECT_EQ( "faceAttributes", attributes[3]->getName() );

	EXPECT_EQ( 1, object->getNodeAttributes().size() );

	const std::list< ColorRGBAMap<float>* >& colorMaps = object->getColorMaps();
	EXPECT_EQ( 2, colorMaps.size() );
	EXPECT_EQ( "default", colorMaps.front()->getName() );
	EXPECT_EQ( "my_table", colorMaps.back()->getName() );
}

TEST( VTKObjectFactoryTest, TestCreateVTKFileStructuedPoints )
{
	std::stringstream stream;
	stream
		<< "# vtk DataFile Version 2.0" << std::endl
		<< "Volume example" << std::endl
		<< "ASCII" << std::endl
		<< "DATASET STRUCTURED_POINTS" << std::endl
		<< "DIMENSIONS 2 2 2" << std::endl
		<< "ASPECT_RATIO 1 1 1" << std::endl
		<< "ORIGIN 0 0 0" << std::endl
		<< "POINT_DATA 8" << std::endl
		<< "SCALARS volume_scalars char 1" << std::endl
		<< "LOOKUP_TABLE default" << std::endl
		<< "1 2 3 4 5 6 7 8" << std::endl;

	VTKFile file;
	const bool isOpen = file.read( stream );

	VTKObjectFactory factory;
	VTKObject* object = factory.create( file );
	EXPECT_EQ( 0, object->getId() );
	EXPECT_EQ( "Volume example", object->getName() );
	EXPECT_EQ( 8, object->getVertices().size() );
	//EXPECT_TRUE( object->getCegetFaces().empty() );

	EXPECT_EQ( 1, object->getNodeAttributes().size() );
	VTKAttributes* attr = object->getNodeAttributes().front();
	EXPECT_EQ( "volume_scalars", attr->getName() );
	EXPECT_EQ( 8, attr->getValues().size() );
	//EXPECT_EQ( 1, attr.getDim() );

	const std::list< ColorRGBAMap<float>* >& colorMaps = object->getColorMaps();
	EXPECT_EQ( 1, colorMaps.size() );
	EXPECT_EQ( "default", colorMaps.front()->getName() );

	ColorRGBAMap<float>* map = object->getColorMap( "default" );
	EXPECT_FALSE( map == nullptr );
}


static std::stringstream getUnstructuredGrid() {
	std::stringstream stream;
	stream
		<< "# vtk DataFile Version 2.0" << std::endl
		<< "Unstructured Grid Example" << std::endl
		<< "ASCII" << std::endl
		<< "DATASET UNSTRUCTURED_GRID" << std::endl
		<< "POINTS 27 float" << std::endl
		<< "0 0 0 1 0 0 2 0 0 0 1 0 1 1 0 2 1 0" << std::endl
		<< "0 0 1 1 0 1 2 0 1 0 1 1 1 1 1 2 1 1" << std::endl
		<< "0 1 2 1 1 2 2 1 2 0 1 3 1 1 3 2 1 3" << std::endl
		<< "0 1 4 1 1 4 2 1 4 0 1 5 1 1 5 2 1 5" << std::endl
		<< "0 1 6 1 1 6 2 1 6" << std::endl
		<< "CELLS 11 60" << std::endl
		<< "8 0 1 4 3 6 7 10 9" << std::endl
		<< "8 1 2 5 4 7 8 11 10" << std::endl
		<< "4 6 10 9 12" << std::endl
		<< "4 5 11 10 14" << std::endl
		<< "6 15 16 17 14 13 12" << std::endl
		<< "6 18 15 19 16 20 17" << std::endl
		<< "4 22 23 20 19" << std::endl
		<< "3 21 22 18" << std::endl
		<< "3 22 19 18" << std::endl
		<< "2 26 25" << std::endl
		<< "1 24" << std::endl
		<< "CELL_TYPES 11" << std::endl
		<< "12 12 10 10 7 6 9" << std::endl
		<< "5" << std::endl
		<< "5" << std::endl
		<< "3" << std::endl
		<< "1" << std::endl
		<< "POINT_DATA 27" << std::endl
		<< "SCALARS scalars float 1" << std::endl
		<< "LOOKUP_TABLE default" << std::endl
		<< "0.0 1.0 2.0 3.0 4.0 5.0" << std::endl
		<< "6.0 7.0 8.0 9.0 10.0 11.0" << std::endl
		<< "12.0 13.0 14.0 15.0 16.0 17.0" << std::endl
		<< "18.0 19.0 20.0 21.0 22.0 23.0" << std::endl
		<< "24.0 25.0 26.0" << std::endl
		<< "VECTORS vectors float" << std::endl
		<< "1 0 0 1 1 0 0 2 0 1 0 0 1 1 0 0 2 0" << std::endl
		<< "1 0 0 1 1 0 0 2 0 1 0 0 1 1 0 0 2 0" << std::endl
		<< "0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1" << std::endl
		<< "0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1" << std::endl
		<< "0 0 1 0 0 1 0 0 1" << std::endl;
	return stream;
}

TEST( VTKObjectFactoryTest, TestCreateVTKFileUnstructuedGrid )
{
	std::stringstream stream = ::getUnstructuredGrid();

	VTKFile file;
	file.read( stream );

	VTKObjectFactory factory;
	VTKObject* object = factory.create( file );

	EXPECT_EQ( 27, object->getVertices().size() );
	EXPECT_EQ( 11, object->getCells().size() );

	EXPECT_TRUE( object->getCellAttributes().empty() );
	EXPECT_EQ( 2, object->getNodeAttributes().size() );
}

TEST( VTKObjectFactoryTest, TestCreateAVSUCDScalar )
{
	std::stringstream stream;
	stream
		<< "1" << std::endl
		<< "data" << std::endl
		<< "step1" << std::endl
		<< "8 3" << std::endl
		<< "1   0.   0.   0." << std::endl
		<< "2   1.   0.   0." << std::endl
		<< "3   2.   0.   0." << std::endl
		<< "4   3.   0.   0." << std::endl
		<< "5   0.   1.   0." << std::endl
		<< "6   1.   1.   0." << std::endl
		<< "7   2.   1.   0." << std::endl
		<< "8   3.   1.   0." << std::endl
		<< "1   1 quad 1 2 6 5" << std::endl
		<< "2   1 quad 2 3 7 6" << std::endl
		<< "3   1 quad 3 4 8 7" << std::endl
		<< "0   1" << std::endl
		<< "1   1" << std::endl
		<< "scalar," << std::endl
		<< "1 0.1" << std::endl
		<< "2 0.4" << std::endl
		<< "3 0.3" << std::endl;

	AVSUCDFile file;
	file.read( stream );

	VTKObjectFactory factory;
	VTKObject* object = factory.create( file );
	EXPECT_EQ( 0, object->getId() );

	EXPECT_EQ( 8, object->getVertices().size() );
	EXPECT_EQ( Vector3d( 0.0, 0.0, 0.0 ), object->getVertices().front() );
	EXPECT_EQ( Vector3d( 3.0, 1.0, 0.0 ), object->getVertices().back() );
	EXPECT_TRUE( object->getNodeAttributes().empty() );
	EXPECT_EQ( 1, object->getCellAttributes().size() );
}

TEST( VTKObjectFactoryTest, TestCreateAVSUCDVector )
{
	std::stringstream stream;
		stream
			<< "1" << std::endl
			<< "data" << std::endl
			<< "step1" << std::endl
			<< "4 1" << std::endl
			<< "1 0.0 0.0 0." << std::endl
			<< "2 1.0 0.0 0." << std::endl
			<< "3 0.0 1.0 0." << std::endl
			<< "4 1.0 1.0 0." << std::endl
			<< "1 1 quad 1 2 4 3" << std::endl
			<< "3 0		" << std::endl
			<< "1 3" << std::endl
			<< "Vector-component," << std::endl
			<< "1 0.0 -0.5 0.0" << std::endl
			<< "2 0.5 -0.5 0.0" << std::endl
			<< "3 0.5 0.0 0.0" << std::endl
			<< "4 0.25 0.5 0.0" << std::endl;

	AVSUCDFile file;
	file.read( stream );

	VTKObjectFactory factory;
	VTKObject* object = factory.create( file );
	EXPECT_EQ( 0, object->getId() );
	EXPECT_EQ( 4, object->getVertices().size() );
	EXPECT_EQ( 1, object->getNodeAttributes().size() );
	//EXPECT_TRUE( object->getCellAttributes().empty() );
}

TEST( VTKObjectFactoryTest, TestCreateDiffuse )
{
	VTKObjectFactory factory;
	VTKObject* object = factory.createDiffuse();
	EXPECT_EQ( 10*10, object->getVertices().size() );
}