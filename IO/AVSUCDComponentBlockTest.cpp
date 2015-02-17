#include "gtest/gtest.h"
#include "AVSUCDFile.h"

#include <istream>

using namespace Crystal::IO;

TEST( AVSNameUnitTest, TestRead )
{
	std::stringstream stream;
	stream<< "stress, lb/in**2" << std::endl;
	AVSNameUnit actual;
	actual.read( stream );

	const AVSNameUnit expected("stress", " lb/in**2");
	EXPECT_EQ( expected, actual );
}

TEST( AVSNameUnitTest, Test )
{
	std::stringstream stream;
	stream << "temperature,K" << std::endl;

	AVSNameUnit nUnit;
	nUnit.read( stream );

	const AVSNameUnit expected("temperature", "K");
	EXPECT_EQ( expected, nUnit );
}

TEST( AVSNameUnitTest, TestReadSpace )
{
	std::stringstream stream;
	stream << "stress sx,lb" << std::endl;
	AVSNameUnit nUnit;
	nUnit.read( stream );

	const AVSNameUnit expected("stress sx","lb");
	EXPECT_EQ( expected, nUnit );
}

TEST( AVSIndexedValueTest, TestScalar )
{
	std::stringstream stream;
	stream << "1 0.1" << std::endl;
	const std::vector<int> lengths = { 1 };

	AVSIndexedValue iValue;
	iValue.read( stream, lengths );
	EXPECT_EQ( 1, iValue.getIndex() );

	AVSIndexedValue expected;
	expected.setIndex( 1 );
	const std::vector< float > values = { 0.1f };
	expected.setValues( values );

	EXPECT_EQ( expected, iValue );
}

TEST( AVSIndexedValueTest, TestVector )
{
	std::stringstream stream;
	stream << "1 0.0 -0.5 0.0" << std::endl;
	
	AVSIndexedValue actual;
	actual.read(stream, { 3 });

	AVSIndexedValue expected;
	expected.setIndex(1);
	const std::vector< float > values = { 0.0f, -0.5f, 0.0f };
	expected.setValues( values );

	EXPECT_EQ( expected, actual );
}

TEST( AVSIndexedValueTest, TestScalarAndVector )
{
	std::stringstream stream;
	stream
		<< "1 10.0 0.0 -0.5 0.0" << std::endl;
	
	const std::vector<int> lengths{ 1, 3 };

	AVSIndexedValue iValue;
	iValue.read( stream, lengths );
	EXPECT_EQ( 1, iValue.getIndex() );

	const std::vector< std::vector<float> >& vs = iValue.toVectors( lengths );
	EXPECT_EQ( 2, vs.size() );
	EXPECT_EQ( 1, vs.front().size() );
	EXPECT_EQ( 10.0, vs.front().front() );
	EXPECT_EQ( 3, vs.back().size() );
}

TEST( AVSUCDFileTest, TestComponent )
{
	std::stringstream stream;
	stream
		<< "1" << std::endl
		<< "scalar," << std::endl
		<< "1 1.0" << std::endl
		<< "2 2.0" << std::endl
		<< "3 3.0" << std::endl;

	AVSComponent component;
	component.read(stream, 1, 3);

	EXPECT_EQ(std::vector < int > {1}, component.getVectorLengths());

	AVSIndexedValue i0(1, std::vector < float > { 1.0 });
	AVSIndexedValue i1(2, std::vector < float > { 2.0 });
	AVSIndexedValue i2(3, std::vector < float > { 3.0 });
	std::vector< AVSIndexedValue > expected = { i0, i1, i2 };
	EXPECT_EQ( expected, component.getIndexedValues() );
}

TEST( AVSUCDFileTest, TestReadWithSpaces )
{
	std::stringstream stream;
	stream
		<< "3 " << std::endl
		<< "vect, cm " << std::endl
		<< "1 1.000000 1.000000 0.000000 " << std::endl;

	AVSComponent component;
	component.read( stream, 1, 1 );

	EXPECT_EQ( 1, component.getNameUnits().size() );
	EXPECT_EQ( "vect", component.getNameUnits().front().getName() );
}

TEST( AVSUCDFileTest, TestToUVTKAttributes )
{
	std::stringstream stream;
	stream
		<< "1" << std::endl
		<< "scalar," << std::endl
		<< "1 0.1" << std::endl
		<< "2 0.4" << std::endl
		<< "3 0.3" << std::endl;

	AVSComponent component;
	component.read(stream, 1, 3);

	const VTKAttributeVector& attributes = component.toVTKAttributes();
	EXPECT_EQ( 1, attributes.size() );
	EXPECT_EQ( "scalar", attributes.front()->getName() );
	EXPECT_EQ( 3, attributes.front()->getValues().size() );

	for( VTKAttributes* attr : attributes ) {
		delete attr;
	}
}

TEST( AVSUCDFileTest, TestMultiComponents )
{
	std::stringstream stream;
	stream
		<< "1  1" << std::endl
		<< "scalar," << std::endl
		<< "scalar," << std::endl
		<< "1 0.1 1.1" << std::endl
		<< "2 0.4 1.4" << std::endl
		<< "3 0.3 1.3" << std::endl;

	AVSComponent component;
	component.read(stream, 2, 3);

	const std::vector<int> vectorLengths = { 1, 1 };

	EXPECT_EQ( vectorLengths, component.getVectorLengths() );

	EXPECT_EQ( 3, component.getIndexedValues().size() );
	EXPECT_FLOAT_EQ( 0.1f, component.getIndexedValues().front().getValues().front() );
	EXPECT_EQ( 2, component.getIndexedValues().front().getValues().size() );
}

TEST( AVSUCDFileTest, TestToVTKAttributes )
{
	std::stringstream stream;
	stream
		<< "1  1" << std::endl
		<< "scalar," << std::endl
		<< "scalar," << std::endl
		<< "1 0.1 1.1" << std::endl
		<< "2 0.4 1.4" << std::endl
		<< "3 0.3 1.3" << std::endl;

	AVSComponent component;
	component.read(stream, 2, 3);

	EXPECT_EQ( 2, component.getVectorLengths().size() );
	EXPECT_EQ( 1, component.getVectorLengths().front() );
	EXPECT_EQ( 1, component.getVectorLengths().back() );

	EXPECT_EQ( 3, component.getIndexedValues().size() );
	EXPECT_FLOAT_EQ( 0.1f, component.getIndexedValues().front().getValues().front() );
	EXPECT_EQ( 2, component.getIndexedValues().front().getValues().size() );

	const VTKAttributeVector& attrs = component.toVTKAttributes();

	EXPECT_EQ( 2, attrs.size() );
	EXPECT_EQ( "scalar", attrs.front()->getName() );
	EXPECT_EQ( 3, attrs.front()->getValues().size() );
	EXPECT_FLOAT_EQ( 0.1f, attrs.front()->getValues().front() );

	
	for( VTKAttributes* attr : attrs ) {
		delete attr;
	}
}

TEST( AVSUCDComponentBlockTest, TestReadScalar )
{
	std::stringstream stream;
	stream
		<< "0 1" << std::endl
		<< "1 1" << std::endl
		<< "scalar," << std::endl
		<< "1 0.1" << std::endl
		<< "2 0.4" << std::endl
		<< "3 0.3" << std::endl;

	AVSUCDComponentBlock block;
	block.read( stream, 3, 0 );

	EXPECT_EQ( 0, block.getNodeComponents().size() );
	EXPECT_EQ( 1, block.getElementComponents().size() );
}

TEST( AVSUCDComponentBlockTest, TestReadVector )
{
	std::stringstream stream;
	stream
		<< "3 0" << std::endl
		<< "1 3" << std::endl
		<< "vector," << std::endl
		<< "1 0.0 -0.5 0.0" << std::endl
		<< "2 0.5 -0.5 0.0" << std::endl
		<< "3 0.5 0.0 0.0" << std::endl
		<< "4 0.25 0.5 0.0" << std::endl;

	AVSUCDComponentBlock block;
	block.read( stream, 4, 0 );

	EXPECT_EQ( 1, block.getNodeComponents().size() );
	EXPECT_EQ( 0, block.getElementComponents().size() );
}