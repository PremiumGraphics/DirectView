#include "gtest/gtest.h"
 
#include "AVSUCDFile.h"
#include "VTKObject.h"

using namespace Crystal::Math;
using namespace Crystal::IO;


TEST( AVSCycleTypeTest, TestToType )
{
	EXPECT_EQ( AVSCycleType::DATA,		AVSCycleType::toType( "data" ) );
	EXPECT_EQ( AVSCycleType::GEOM,		AVSCycleType::toType( "geom" ) );
	EXPECT_EQ( AVSCycleType::DATA_GEOM, AVSCycleType::toType( "data_geom") );
}

TEST( AVSCycleTypeTest, TestToStr )
{
	EXPECT_EQ( "data",		AVSCycleType::toStr( AVSCycleType::DATA ) );
	EXPECT_EQ( "geom",		AVSCycleType::toStr( AVSCycleType::GEOM ) );
	EXPECT_EQ( "data_geom", AVSCycleType::toStr( AVSCycleType::DATA_GEOM ) );
}

TEST( AVSUCDHeaderBlockTest, TestReadNoComments )
{
	std::stringstream stream;
	stream
		<< "1" << std::endl
		<< "data_geom" << std::endl;
	AVSUCDHeaderBlock header;
	header.read( stream );

	EXPECT_EQ( "" , header.getComment() );
	EXPECT_EQ( 1, header.getTotalSteps() );
	EXPECT_EQ( AVSCycleType::DATA_GEOM, header.getCycleType() );
}

TEST( AVSUCDHeaderBlockTest, TestWrite )
{
	std::ostringstream stream;
	AVSUCDHeaderBlock header;
	header.setComment( "" );
	header.setTotalSteps( 1 );
	header.setCycleType( AVSCycleType::DATA );
	header.write( stream );

	const std::string& actual = stream.str();
	std::stringstream expected;
	expected << "" << std::endl
		<< "1"	<< std::endl
		<< "data" << std::endl;

	EXPECT_EQ( expected.str(), actual );
}


TEST( AVSUCDHeaderBlockTest, TestReadAComment )
{
	std::stringstream stream;
	stream
		<< "# Comment" << std::endl
		<< 1 << std::endl
		<< "data_geom" << std::endl;
	AVSUCDHeaderBlock header;
	header.read( stream );

	EXPECT_EQ("# Comment" , header.getComment() );
	EXPECT_EQ( 1, header.getTotalSteps() );
	EXPECT_EQ( AVSCycleType::DATA_GEOM, header.getCycleType() );
}

TEST( AVSUCDHeaderBlockTest, TestReadComments )
{
	std::stringstream stream;
	stream
		<< "# Comment1" << std::endl
		<< "# Comment2" << std::endl
		<< 1 << std::endl
		<< "data_geom" << std::endl;
	AVSUCDHeaderBlock header;
	header.read( stream );

	EXPECT_EQ("# Comment1# Comment2" , header.getComment() );
	EXPECT_EQ( 1, header.getTotalSteps() );
	EXPECT_EQ( AVSCycleType::DATA_GEOM, header.getCycleType() );
}


TEST(AVSUCDElementTest, TestPoint)
{
	std::stringstream stream;
	stream
		<< "1 1 pt 1" << std::endl;

	AVSUCDElement element;
	element.read(stream, 1);
	EXPECT_EQ(1, element.getCells().size());
	const std::vector<unsigned int> expected{ 0 };
	EXPECT_EQ( expected, element.getCells().front().getIndices() );
}

TEST(AVSUCDElementTest, TestLine)
{
	std::stringstream stream;
	stream
		<< "1 1 line 1 2" << std::endl;

	AVSUCDElement element;
	element.read(stream, 1);
	EXPECT_EQ(1, element.getCells().size());
	const std::vector<unsigned int> expected{ 0, 1 };
	EXPECT_EQ( expected, element.getCells().front().getIndices() );
}

TEST(AVSElementTest, TestTriangle)
{
	std::stringstream stream;
	stream
		<< "1   1 tri 1 2 3" << std::endl;

	AVSUCDElement element;
	element.read(stream, 1);
	EXPECT_EQ(1, element.getCells().size());
	const std::vector<unsigned int> expected{ 0, 1, 2 };
	EXPECT_EQ( expected, element.getCells().front().getIndices() );
}

TEST(AVSElementTest, TestPyramid)
{
	std::stringstream stream;
	stream << "1   1 pyr 1 2 3 4 5" << std::endl;

	AVSUCDElement element;
	element.read(stream, 1);
	EXPECT_EQ(1, element.getCells().size());
	const std::vector<unsigned int> expected{ 0, 1, 2, 3, 4 };
	EXPECT_EQ( expected, element.getCells().front().getIndices() );
}

TEST(AVSElementTest, TestPrism)
{
	std::stringstream stream;
	stream << "1   1 prism 1 2 3 4 5" << std::endl;

	AVSUCDElement element;
	element.read(stream, 1);
	EXPECT_EQ(1, element.getCells().size());
	const std::vector<unsigned int> expected{ 0, 1, 2, 3, 4 };
	EXPECT_EQ( expected, element.getCells().front().getIndices() );
}

TEST(AVSElementTest, TestHex)
{
	std::stringstream stream;
	stream << "1   1 hex 1 2 3 4 5 6 7 8" << std::endl;

	AVSUCDElement element;
	element.read(stream, 1);
	EXPECT_EQ(1, element.getCells().size());
	const std::vector<unsigned int> expected{ 0, 1, 2, 3, 4, 5, 6, 7 };
	EXPECT_EQ( expected, element.getCells().front().getIndices() );
}

TEST(AVSElementTest, TestQuad)
{
	std::stringstream stream;
	stream
		<< "1   1 quad 1 2 6 5" << std::endl
		<< "2   1 quad 2 3 7 6" << std::endl
		<< "3   1 quad 3 4 8 7" << std::endl;

	AVSUCDElement element;
	element.read(stream, 3);
	EXPECT_EQ(3, element.getCells().size());
}

TEST( AVSUCDNodeTest, TestRead )
{
	std::stringstream stream;
	stream << "1 0.0 0.0 0.0" << std::endl;
	stream << "2 1.0 0.0 0.0" << std::endl;
	AVSUCDNode node;
	node.read(stream, 2);

	const std::vector<AVSUCDNodePair>& actual = node.getPairs();
	const std::vector<AVSUCDNodePair> expected = {
		AVSUCDNodePair(1, Vector3d(0.0, 0.0, 0.0)),
		AVSUCDNodePair(2, Vector3d(1.0, 0.0, 0.0))
	};
	EXPECT_EQ( expected, actual );
}


TEST( AVSUCDNodeTest, TestWrite )
{
	const std::vector< AVSUCDNodePair > pairs = {
		AVSUCDNodePair(1, Vector3d(0.0f, 0.0f, 0.0f))
	};
	
	std::ostringstream stream;

	AVSUCDNode node;
	node.setPairs( pairs );
	node.write( stream );

	const std::string expected = "1 0 0 0\n";
	const std::string& actual = stream.str();
	EXPECT_EQ( expected, actual );
}

TEST( AVSUCDFileTest, TestScalar )
{

	std::stringstream stream;
	stream
		<< "1" << std::endl
		<< "data" << std::endl
		<< "step1" << std::endl
		<< "2 1" << std::endl
		<< "1 0.0 0.0 0.0" << std::endl
		<< "2 1.0 0.0 0.0" << std::endl
		<< "1 1 line 1 2" << std::endl
		<< "0 1" << std::endl
		<< "1 1" << std::endl
		<< "scalar," << std::endl
		<< "1 0.1" << std::endl;

	AVSUCDFile file;
	file.read( stream );

	const AVSUCDGeomBlock& geom = file.getGeom();

	const std::vector< Vector3d >& vertices = geom.getNode().getPositions();

	const std::vector< Vector3d > expected{
		Vector3d(0.0f, 0.0f, 0.0f),
		Vector3d(1.0f, 0.0f, 0.0f)
	};

	EXPECT_EQ( expected, vertices );

	const std::vector<AVSElement_>& cells = geom.getElement().getCells();
	EXPECT_EQ( 1, cells.size() );
	EXPECT_EQ( 2, cells[0].getIndices().size() );
	EXPECT_EQ( 1, file.getComponent().getElementComponents().size() );

	const AVSUCDComponentBlock& component = file.getComponent();

	const AVSComponentVector& elementComponents = component.getElementComponents();

	const AVSComponentVector& nodeComponents = component.getNodeComponents();

	EXPECT_TRUE( nodeComponents.empty() );

	{
		const AVSComponentVector& components = elementComponents;
		const AVSComponent& component = components.front();
		EXPECT_EQ( "scalar", component.getNameUnits().front().getName() );
		//EXPECT_EQ( "", component.getUnit() );
		EXPECT_EQ( 1, component.getIndexedValues().size() );
	}
}

TEST( AVSUCDFileTest, TestVector )
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
		<< "vector," << std::endl
		<< "1 0.0 -0.5 0.0" << std::endl
		<< "2 0.5 -0.5 0.0" << std::endl
		<< "3 0.5 0.0 0.0" << std::endl
		<< "4 0.25 0.5 0.0" << std::endl;

	AVSUCDFile file;
	file.read( stream );

	const std::vector< Vector3d >& vertices = file.getGeom().getNode().getPositions();
	EXPECT_EQ( 4, vertices.size() );

	const AVSComponentVector& components = file.getComponent().getNodeComponents();
	const AVSComponent& component = components.front();
	EXPECT_EQ( "vector", component.getNameUnits().front().getName() );
	//EXPECT_EQ( "", component.getUnit() );
	EXPECT_EQ( 4, component.getIndexedValues().size() );
}

TEST( AVSUCDFileTest, TestLegacy )
{
	std::stringstream stream;
	stream
		<< "# Comment" << std::endl
		<< "5 1 1 0 0" << std::endl
		<< "1 0.5 0.5 1.0" << std::endl
		<< "2 0.0 1.0 0.0" << std::endl
		<< "3 0.0 0.0 0.0" << std::endl
		<< "4 1.0 0.0 0.0" << std::endl
		<< "5 1.0 1.0 0.0" << std::endl
		<< "1 1 pyr 1 2 3 4 5" << std::endl
		<< "1 1" << std::endl
		<< "stress, lb/in**2" << std::endl
		<< "1 10.0" << std::endl
		<< "2 20.0" << std::endl 
		<< "3 30.0" << std::endl
		<< "4 40.0" << std::endl
		<< "5 50.0" << std::endl;

	AVSUCDFile file;
	file.readLegacy( stream );

	const AVSUCDGeomBlock& geom = file.getGeom();
	const std::vector< Vector3d >& vertices = geom.getNode().getPositions();
	EXPECT_EQ( 5, vertices.size() );
	EXPECT_EQ( 1, geom.getElement().getCells().size() );

	const AVSComponentVector& components = file.getComponent().getNodeComponents();
	const AVSComponent& component = components.front();
	EXPECT_EQ( "stress", component.getNameUnits().front().getName() );

	EXPECT_EQ( 5, component.getIndexedValues().size() );
	EXPECT_EQ( 1, component.getIndexedValues().front().getValues().size() );
	EXPECT_EQ( 1, component.getIndexedValues().front().getIndex() );
	EXPECT_FLOAT_EQ( 10.0f, component.getIndexedValues().front().getValues().front() );

}

std::stringstream getSampleUCD() {
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
		<< "stress sx,lb" << std::endl
		<< "stress sy,lb" << std::endl
		<< "stress sz,lb" << std::endl
		<< "1 0.1 1.0 1.1" << std::endl
		<< "2 0.2 2.0 2.2" << std::endl 
		<< "3 0.3 3.0 3.3" << std::endl
		<< "4 0.4 4.0 4.4" << std::endl
		<< "5 0.5 5.0 5.5" << std::endl
		<< "3 1 1 1" << std::endl
		<< "temp1, F" << std::endl
		<< "temp2, F" << std::endl
		<< "temp3, F" << std::endl
		<< "1 10.0 20.0 30.0" << std::endl
		<< "2 40.0 50.0 60.0" << std::endl
		<< "1 1" << std::endl
		<< "mises, X" << std::endl
		<< "1 200" << std::endl;
	return stream;
}

TEST( AVSUCDFileTest, TestLegacyMulti )
{
	AVSUCDFile file;
	file.readLegacy( getSampleUCD() );	
	const AVSComponentVector& nodeComponents = file.getComponent().getNodeComponents();
	EXPECT_EQ( 1, nodeComponents.size() );
	EXPECT_EQ( 5, nodeComponents.front().getIndexedValues().size() );
	EXPECT_FLOAT_EQ( 0.1f, nodeComponents.front().getIndexedValues()[0].getValues().front() ); 

	const AVSComponentVector& elementComponents = file.getComponent().getElementComponents();
	EXPECT_EQ( 1, elementComponents.size() );
	//EXPECT_EQ( 2, elementComponents.front().getIndexedValues().size() );

	{
		const AVSNameUnitVector& nameUnits = elementComponents.front().getNameUnits();
		const AVSNameUnitVector expected
		{
			AVSNameUnit("temp1", " F"),
			AVSNameUnit("temp2", " F"),
			AVSNameUnit("temp3", " F")
		};
		EXPECT_EQ( expected, nameUnits );
	}
	const AVSIndexedValueVector& iValues = elementComponents.front().getIndexedValues();
	EXPECT_EQ( 2, iValues.size() );
	EXPECT_EQ( 1, iValues.front().getIndex() );
	{
		const std::vector< float >& values = iValues.front().getValues();
		const std::vector< float > expected{ 10.0, 20.0, 30.0 };
		EXPECT_EQ( expected, values );
	}
}