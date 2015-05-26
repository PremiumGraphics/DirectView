#include "gtest/gtest.h"

#include "../Math/Space.h"

using namespace Crystal::Math;

template < typename T >
using Space1d = Space < T, 1 > ;

template < typename T >
using Space2d = Space < T, 2 >;


TEST(SpaceTest, TestGetStart)
{
	using T = float;
	EXPECT_EQ(Position1d<T>({ 0 }), Space1d<T>().getStart());
	EXPECT_EQ(Position1d<T>({ 1 }), Space1d<T>(Position1d<T>({ 1 })).getStart());

	EXPECT_EQ(Position2d<T>({ 0, 0 }), Space2d<T>().getStart());
}

TEST(SpaceTest, TestGetEnd)
{
	EXPECT_EQ(Position1d<float>({ 0 }), Space1d<float>().getEnd());
}

TEST(SpaceTest, TestEquals)
{
	using T = float;
	EXPECT_EQ(Space1d<T>(), Space1d<T>());
	EXPECT_NE(Space1d<T>(), Space1d<T>(Position1d<T>({ 1 })));

}