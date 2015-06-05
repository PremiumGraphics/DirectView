#include "gtest/gtest.h"

#include "../CG/Model.h"

using namespace Crystal::Math;
using namespace Crystal::CG;

TEST(ModelTest, Test)
{
	Model model;
	BitSpace3dSPtr<float> bs = std::make_shared<BitSpace3d<float> >( Bitmap3d(1,1,1) );
	model.addBitSpace(bs);
}