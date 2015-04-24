#include "NeighborSearcher.h"

#include "../Math/Vector3d.h"

#include <algorithm>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace Crystal::Math;
using namespace Crystal::Physics;

ParticlePairVector search1(const PhysicsParticleSPtrVector& particles, PhysicsParticleSPtrVector::const_iterator startIter, PhysicsParticleSPtrVector::const_iterator endIter, const float effectLengthSquared){
	ParticlePairVector pairs;
	for( PhysicsParticleSPtrVector::const_iterator xIter = startIter; xIter != endIter; ++xIter ) {
		const int gridID = (*xIter)->getGridID();
		const Vector3d& centerX = (*xIter)->getCenter();
		PhysicsParticleSPtrVector::const_iterator yIter = xIter;
		++yIter;// ignore itself.
		while( yIter != particles.end() && ( (*yIter)->getGridID() <= gridID + 1) ) {
			const Vector3d& centerY = (*yIter)->getCenter();
			if( centerX.getDistanceSquared( centerY ) < effectLengthSquared ) {
				pairs.push_back( PhysicsParticlePair( (*xIter), (*yIter) ) );
				pairs.push_back( PhysicsParticlePair( (*yIter), (*xIter) ) );
			}
			++yIter;
		}
	}
	return pairs;
}

ParticlePairVector search2(const PhysicsParticleSPtrVector& particles, PhysicsParticleSPtrVector::const_iterator startIter, PhysicsParticleSPtrVector::const_iterator endIter, const float effectLengthSquared)
{
	ParticlePairVector pairs;

	std::vector<PhysicsParticleSPtrVector::const_iterator> yIter(4, startIter);
	std::vector<int> offsetIds;
	offsetIds.push_back(1023);
	offsetIds.push_back(1047551);
	offsetIds.push_back(1048575);
	offsetIds.push_back(1049599);

	for (PhysicsParticleSPtrVector::const_iterator xIter = startIter; xIter != endIter; ++xIter) {
		for( size_t i = 0; i < 4; ++i ) {
			const int baseID = (*xIter)->getGridID() + offsetIds[i];
			while( yIter[i] != particles.end() && ( (*yIter[i])->getGridID() < baseID ) ) {
				++yIter[i];
			}
			
			const Vector3d& centerX = (*xIter)->getCenter();
			PhysicsParticleSPtrVector::const_iterator zIter = yIter[i];
			while( zIter != particles.end() && ( (*zIter)->getGridID() <= baseID + 2) ) {
				const Vector3d& centerZ = (*zIter)->getCenter();
				if( centerX.getDistanceSquared( centerZ ) < effectLengthSquared ) {
					pairs.push_back( PhysicsParticlePair( (*xIter), (*zIter) ) );
					pairs.push_back( PhysicsParticlePair( (*zIter), (*xIter) ) );
				}
				++zIter;
			}
		}
	}
	
	return pairs;
}

ParticlePairVector NeighborSearcher::createPairs(PhysicsParticleSPtrVector particles, const float effectLength)
{
	if( particles.empty() ) {
		return ParticlePairVector();
	}

	for( const PhysicsParticleSPtr& particle : particles ) {
		particle->setGridID( effectLength );
	}
	
	std::sort( particles.begin(), particles.end(), &PhysicsParticle::compare );

	// optimization for quad core.
	const int threads = 8;

	std::vector<ParticlePairVector> eachPairs( threads );

	std::vector<PhysicsParticleSPtrVector::const_iterator> iters;
	for( int i = 0; i < threads; ++i ) {
		iters.push_back( particles.begin() + i * particles.size() / threads );
	}
	iters.push_back( particles.end() );

	#pragma omp parallel for
	for( int i = 0; i < threads; ++i ) {
		eachPairs[i] = ::search1( particles, iters[i], iters[i+1], effectLength * effectLength );
	}

	ParticlePairVector pairs;
	for( size_t i = 0; i < eachPairs.size(); ++i ) {
		pairs.insert( pairs.end(), eachPairs[i].begin(), eachPairs[i].end() );
	}

	#pragma omp parallel for
	for( int i = 0; i < threads; ++i ) {
		eachPairs[i] = search2( particles, iters[i], iters[i+1], effectLength * effectLength );
	}

	for( size_t i = 0; i < eachPairs.size(); ++i ) {
		pairs.insert( pairs.end(), eachPairs[i].begin(), eachPairs[i].end() );
	}

	return pairs;
}