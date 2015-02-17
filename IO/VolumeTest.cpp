#include "gtest/gtest.h"

#include "Volume.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST( VolumeTest, TestCreateHydrogen )
{
	Volume volume( 10, 10, 10 );
	const std::vector< float >& values = volume.createHydrogenVolume();
}

TEST( VolumeTest, TestCreateTornado )
{
	Volume volume( 10, 10, 10 );
	const std::vector< Vector3d >& vectors = volume.createTornadoVolume( 0.1f );
	EXPECT_EQ( 10 * 10 * 10, vectors.size() );
}