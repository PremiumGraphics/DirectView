#include "gtest/gtest.h"

#include "../Math/Space2d.h"

using namespace Crystal::Math;

template<class T>
class Space2dTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Space2dTest, TestTypes);

TYPED_TEST(Space2dTest, TestGetSize)
{
	using T = TypeParam;
	EXPECT_EQ(Vector2d<T>({ 1.0f, 1.0f }), Space1x1<T>().getSizes());
	EXPECT_EQ(Vector2d<T>({ 1.0f, 1.0f }), Space1x1<T>().getSizes());

}

TYPED_TEST(Space2dTest, TestEquals)
{
	using T = TypeParam;

	EXPECT_EQ( Space1x1<T>(), Space1x1<T>());
	EXPECT_NE( Space1x1<T>( Quad<T>( Position2d<T>(1.0f, 1.0f) )), Space1x1<T>() );
}

TYPED_TEST(Space2dTest, TestGetResX)
{
	using T = TypeParam;

	EXPECT_EQ(2, Space2x2<T>().getResX());
	EXPECT_EQ(4, Space4x2<T>().getResX());

//	EXPECT_EQ(20, s.getResY());
}

TYPED_TEST(Space2dTest, TestGetStart)
{
	using T = TypeParam;

	EXPECT_EQ( Position2d<T>(0.0f, 0.0f), Space2x2<T>().getStart());
	EXPECT_EQ( Position2d<T>(1.0f, 2.0f), Space2x2<T>( Quad<T>( Position2d<T>(1.0f, 2.0f )) ).getStart() );
}

TYPED_TEST(Space2dTest, TestGetEnd)
{
	using T = TypeParam;

	EXPECT_EQ( Position2d<T>(1.0f, 1.0f), Space2x2<T>().getEnd());
	EXPECT_EQ( Position2d<T>(2.0f, 3.0f), Space2x2<T>( Quad<T>( Position2d<T>(1.0f, 2.0f) ) ).getEnd() );
}

/*
TEST(Space2dTest, TestMove)
{
	Space2x2 s(Vector2d<float>(1.0f, 2.0f));
	 //s.move(Vector2d<float>(10.0f, 10.0f));

}
*/

/*
TEST(Space2dTest, TestGetBoundingQuad)
{
	const Space2d<2, 2> s(Vector2d<float>(1.0f, 2.0f) );
	const Quad expected( Vector2d<float>(11.0f, 22.0f), Position2d<float>(1.0f, 2.0f) );
	const auto& actual = s.getBoundingQuad();
	EXPECT_EQ(expected, actual);
}
*/

TYPED_TEST(Space2dTest, TestToBoundaryPositions)
{
	using T = TypeParam;

	EXPECT_TRUE(Space2x2<T>( Quad<T>(), Bitmap2x2() ).toBoundaryPositions().empty());

	/*
	{
		const auto actual = Space2x2().toBoundaryPositions(Bitmap2x2("0001"));
		const Position2dVector < float > expected{
			Position2d<float>(0.5, 0.0),
			Position2d<float>(0.0, 0.5)
		};
		EXPECT_EQ(expected, actual);
	}
	*/
}

TYPED_TEST(Space2dTest, TestToQuads)
{
	using T = TypeParam;

	EXPECT_TRUE( Space2x2<T>( Quad<T>(), Bitmap2x2() ).toDividedQuads().empty() );

	/*
	{
		Bitmap2d<2, 2> bmp;
		bmp.set(0, 0);
		Space2d<2, 2> space( Bitmap2x2() );
		const std::vector<Quad<float> >& quads = space.toQuads(bmp);
		EXPECT_EQ(1, quads.size());
		EXPECT_EQ(Position2d<float>(0.5f, 0.5f), quads.front().getCenter());
	}
	*/
}

TYPED_TEST(Space2dTest, TestHasIntersection)
{
	using T = TypeParam;

	EXPECT_TRUE( Space2x2<T>().hasIntersection(Space2x2<T>() ) );
}

/*
TEST(Space3dTest, TestGetHashedIndex)
{
Space3d space(1, 1, 1);

const std::vector<int>& actual = space.getHashedIndex(Vector3d(1.5f, 0.0f, 0.0f));
const std::vector<int> expected{ 1, 0, 0 };
EXPECT_EQ(expected, actual);
}
*/