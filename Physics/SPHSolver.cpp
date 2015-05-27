#include "SPHSolver.h"

#include "PhysicsParticleFindAlgo.h"

#include "Coordinator.h"

#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

void SPHSolver<float>::solve(const PhysicsObjectSPtrVector& objects, const float effectLength )
{
	const PhysicsParticleSPtrVector& particles = getParticles( objects );

	if( particles.empty() ) {
		return;
	}

	for( const PhysicsParticleSPtr& particle : particles ) {
		particle->init();
	}

	PhysicsParticleFindAlgo algo;
	algo.createPairs(particles, effectLength);
	const ParticlePairVector& pairs = algo.getPairs();
		
	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( pairs.size() ); ++i ) {
		const float distance = pairs[i].getDistance();
		pairs[i].getParticle1()->addDensity( getPoly6Kernel( distance, effectLength ) * pairs[i].getParticle2()->getMass() );
	}
	
	for( int i = 0; i < static_cast<int>( particles.size() ); ++i ) {
		particles[i]->addDensity( getPoly6Kernel( 0.0, effectLength ) * particles[i]->getMass() );
	}

	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( pairs.size() ); ++i ) {
		const float pressure = pairs[i].getPressure();
		const Vector3d<float> distanceVector = pairs[i].getDistanceVector();
		pairs[i].getParticle1()->addForce( getSpikyKernelGradient( distanceVector, effectLength ) * pressure * pairs[i].getParticle2()->getVolume() );

		const float viscosityCoe = pairs[i].getViscosityCoe();
		const Vector3d<float> velocityDiff = pairs[i].getVelocityDiff();
		const float distance = pairs[i].getDistance();
		pairs[i].getParticle2()->addForce( viscosityCoe * velocityDiff * getViscosityKernelLaplacian( distance, effectLength ) * pairs[i].getParticle2()->getVolume() );
	}

	for( const auto& object : objects ) {
		object->coordinate();
	}
}


Vector3d<float> SPHSolver<float>::getPoly6KernelGradient( const Vector3d<float>& distanceVector, const float effectLength )
{
	const auto distance = distanceVector.getLength();
	const auto poly6ConstantGradient = 945.0f / ( 32.0f * Tolerancef::getPI() * pow( effectLength, 9 ) );
	const auto factor = poly6ConstantGradient * pow( effectLength * effectLength - distance * distance, 2 );
	return distanceVector * factor;
}


