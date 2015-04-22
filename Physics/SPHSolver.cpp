#include "SPHSolver.h"

#include "NeighborSearcher.h"

#include "Coordinator.h"

#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

void SPHSolver::solve(const PhysicsObjectVector& objects, const float effectLength )
{
	const ParticleSPtrVector& particles = getParticles( objects );

	if( particles.empty() ) {
		return;
	}

	for( const ParticleSPtr& particle : particles ) {
		particle->init();
	}

	const ParticlePairVector& pairs = NeighborSearcher::createPairs( particles, effectLength );
		
	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( pairs.size() ); ++i ) {
		const float distance = pairs[i].getDistance();
		pairs[i].particle1->addDensity( getPoly6Kernel( distance, effectLength ) * pairs[i].particle2->getMass() );
	}
	
	for( int i = 0; i < static_cast<int>( particles.size() ); ++i ) {
		particles[i]->addDensity( getPoly6Kernel( 0.0, effectLength ) * particles[i]->getMass() );
	}

	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( pairs.size() ); ++i ) {
		const float pressure = pairs[i].getPressure();
		const Vector3d distanceVector = pairs[i].getDistanceVector();
		pairs[i].particle1->addForce( getSpikyKernelGradient( distanceVector, effectLength ) * pressure * pairs[i].particle2->getVolume() );

		const float viscosityCoe = pairs[i].getViscosityCoe();
		const Vector3d velocityDiff = pairs[i].getVelocityDiff();
		const float distance = pairs[i].getDistance();
		pairs[i].particle1->addForce( viscosityCoe * velocityDiff * getViscosityKernelLaplacian( distance, effectLength ) * pairs[i].particle2->getVolume() );
	}

	for( PhysicsObject* object : objects ) {
		object->coordinate();
	}
}

ParticleSPtrVector SPHSolver::getParticles( const PhysicsObjectVector& objects )
{
	ParticleSPtrVector ordered;
	for( const PhysicsObject* object : objects ) {
		const ParticleSPtrVector& particles = object->getParticles();
		ordered.insert( ordered.end(), particles.begin(), particles.end() );
	}
	return ordered;
}

float SPHSolver::getPoly6Kernel( const float distance, const float effectLength )
{
	const float poly6Constant = 315.0f / (64.0f * Tolerances::getPI() * pow( effectLength, 9 ) );
	return poly6Constant * pow( effectLength * effectLength - distance * distance, 3 );
}

Vector3d SPHSolver::getPoly6KernelGradient( const Vector3d& distanceVector, const float effectLength )
{
	const float distance = distanceVector.getLength();
	const float poly6ConstantGradient = 945.0f / ( 32.0f * Tolerances::getPI() * pow( effectLength, 9 ) );
	const float factor = poly6ConstantGradient * pow( effectLength * effectLength - distance * distance, 2 );
	return distanceVector * factor;
}

float SPHSolver::getPoly6KernelLaplacian(const float distance, const float effectLength )
{
	const float poly6ConstantLaplacian = 945.0f / ( 32.0f * Tolerances::getPI() * pow(effectLength, 9 ) );
	return poly6ConstantLaplacian * ( effectLength * effectLength - distance * distance ) 
		* ( 42.0f * distance * distance - 18.0f * effectLength * effectLength );
}

Vector3d SPHSolver::getSpikyKernelGradient(const Vector3d &distanceVector, const float effectLength )
{
	const float constant = 45.0f / ( Tolerances::getPI() * pow(effectLength, 6 ) );
	const float distance = distanceVector.getLength();
	return distanceVector * constant * pow ( effectLength - distance, 2 ) / distance;
}

float SPHSolver::getViscosityKernelLaplacian(const float distance, const float effectLength )
{
	const float constant = 45.0f / ( Tolerances::getPI() * pow(effectLength, 6) );
	return (effectLength - distance ) * constant;
}
