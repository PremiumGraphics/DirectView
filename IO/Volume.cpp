#include "Volume.h"

#include "../Math/Vector3d.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

//  Orignal source code is developed by https://code.google.com/p/kvs/.
std::vector< float > Volume::createHydrogenVolume()
{
    const float kr1 = 32.0f / dimX;
    const float kr2 = 32.0f / dimY;
    const float kr3 = 32.0f / dimZ;
    const float kd = 6.0;

	std::vector< float > values;

    for( int z = 0; z < dimZ; ++z ) {
        const float dz = kr3 * ( z - ( dimZ / 2.0f ) );
        for( int y = 0; y < dimY; ++y ) {
			const float dy = kr2 * ( y - ( dimY / 2.0f ) );
			for ( int x = 0; x < dimX; ++x ) {
                const float dx = kr1 * ( x - ( dimX / 2.0f ));
                const float r = std::sqrt( dx * dx + dy * dy + dz * dz );
                const float cos_theta = dz / r;
                const float phi = kd * ( r*r ) * std::exp( -r/2 ) * ( 3*cos_theta*cos_theta-1 );

                float c = phi * phi;
                if ( c > 255.0 ) {
					c = 255.0;
				}

				values.push_back( c );
            }
        }
    }

    return values;
}


//  Orignal source code is developed by https://code.google.com/p/kvs/.
std::vector< Vector3d<float> > Volume::createTornadoVolume( const float time )
{
    const double dx = 1.0f / ( dimX - 1.0f );
    const double dy = 1.0f / ( dimY - 1.0f );
    const double dz = 1.0f / ( dimZ - 1.0f );

	std::vector< Vector3d<float> > vectors;
    for( int k = 0; k < dimZ; k++ ) {
        /* map z to 0->1
         * For each z-slice, determine the spiral circle.
         * (xc,yc) determine the center of the circle.
         * The radius also changes at each z-slice.
         * r is the center radius, r2 is for damping
         */
        const double z  = k * dz;
        const double xc = 0.5 + 0.1 * std::sin( 0.04 * time + 10.0 * z );
        const double yc = 0.5 + 0.1 * std::cos( 0.03 * time + 3.0 * z );
        const double r  = 0.1 + 0.4 * z * z + 0.1 * z * std::sin( 8.0 * z );
        const double r2 = 0.2 + 0.1 * z;

        for( int j = 0; j < dimY; j++ ) {
            const double y = j * dy;
            for( int i = 0; i < dimX; i++ ) {
                const double x = i * dx;

                double temp  = std::sqrt( (y-yc) * (y-yc) + (x-xc) * (x-xc) );
                double scale = std::fabs( r - temp );

                /*  I do not like this next line. It produces a discontinuity
                 *  in the magnitude. Fi it later.
                 */
                scale = ( scale > r2 ) ? ( 0.8 - scale ) : 1.0;

                double z0 = 0.1 * ( 0.1 - temp * z );
                if ( z0 < 0.0 )  z0 = 0.0;

                temp = std::sqrt( temp * temp + z0 * z0 );

                const double epsiron = 0.00000000001;
                scale = ( r + r2 - temp ) * scale / ( temp + epsiron );
                scale = scale / ( 1 + z );

                const double v[3] = {
                    scale *  ( y - yc ) + 0.1 * ( x - xc ),
                    scale * -( x - xc ) + 0.1 * ( y - yc ),
                    scale * z0
                };

				Vector3d<float> vector( v[0], v[1], v[2] );
				vectors.push_back( vector );
            }
        }
    }
	return vectors;
}
