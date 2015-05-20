#include "gtest/gtest.h"

#include "../Math/DynamicBitmap.h"

using namespace Crystal::Math;


TEST(DyanmicsBitmapTest, TestConstructByBitmap1ds)
{
	DynamicBitmap<2> bmp;
	{
		std::bitset<32> bits;
		std::vector < std::bitset<32 > >  bitv{ bits };
		DynamicBitmap<1> bmp(bitv);
		EXPECT_EQ(1, bmp.getSize());
	}
}