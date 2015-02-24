#include "RigidCoordinator.h"

#include "../Math/Matrix3d.h"

#include "../Math/Tolerances.h"
#include "../Math/Vector3d.h"
#include "../Math/Quaternion.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Vector3d getCenter(const ParticleVector& particles){
	if( particles.empty() ) {
		return Vector3d( 0.0, 0.0, 0.0);
	}
	Vector3d center( 0.0, 0.0, 0.0);
	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		center += (*iter)->getCenter();
	}
	return center /= static_cast<float>(particles.size());
}

Vector3d getAverageVelosity(const ParticleVector& particles)
{
	Vector3d averageVelosity( 0.0, 0.0, 0.0 );
	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		averageVelosity += (*iter)->getVelocity();// variable.velocity;
	}
	return averageVelosity / static_cast<float>(particles.size());
}

float getWeight(const ParticleVector& particles)
{
	float weight = 0.0;
	for( Particle* particle : particles ) {
		weight += particle->getMass();
	}
	return weight;
}

#include <iostream>

void RigidCoordinator::coordinate(const ParticleVector& particles, const float proceedTime)
{
	const Math::Vector3d& objectCenter = getCenter( particles );
	const Math::Vector3d& velocityAverage = getAverageVelosity( particles );

	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		(*iter)->setVelocity( velocityAverage );
	}

	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		(*iter)->addCenter( -1.0 * objectCenter );
	}

	//std::cout << getCenter( particles ).x << std::endl;
	//std::cout << getCenter( particles ).y << std::endl;
	//std::cout << getCenter( particles ).z << std::endl;

	//assert( getCenter( particles ) == Math::Vector3d( 0.0, 0.0, 0.0 ) );

	Math::Vector3d inertiaMoment( 0.0, 0.0, 0.0 );
	Math::Vector3d torque( 0.0, 0.0, 0.0 );
	
	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		Particle* particle = (*iter);
		const Math::Vector3d& center = particle->getCenter();
		
		Math::Vector3d particleMoment( pow( center.getY(), 2) + pow( center.getZ(), 2),
			pow( center.getZ(), 2 ) + pow( center.getX(), 2),
			pow( center.getX(), 2 ) + pow( center.getY(), 2) );
		inertiaMoment += (particleMoment) * particle->getMass();

		const Math::Vector3d diffVector( Math::Vector3d( 0.0, 0.0, 0.0), particle->getCenter() );
		const Math::Vector3d& particleTorque = diffVector.getOuterProduct( particle->getForce() * particle->getVolume() );
		torque += particleTorque;
	}

	getAngleVelosity( inertiaMoment , torque, proceedTime );

	if( Math::Tolerances::isEqualStrictly( angleVelosity.getLength() ) ) {
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			(*iter)->addCenter( objectCenter );
		}
		convertToFluidForce( particles);
		return;
	}
	const float rotateAngle = angleVelosity.getLength() * proceedTime;
	if( rotateAngle < 1.0e-5 ) {
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			(*iter)->addCenter( objectCenter );
		}
		convertToFluidForce( particles);
		return;
	}

	Math::Quaternion quaternion( angleVelosity.getNormalized(), rotateAngle );
	const Math::Matrix3d<float>& rotateMatrix = quaternion.toMatrix();
/*	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		(*iter)->variable.center.rotate( rotateMatrix );
	}

	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		(*iter)->variable.center += objectCenter;
	} */
	convertToFluidForce( particles );
}

void RigidCoordinator::convertToFluidForce(const ParticleVector& particles)
{	
	Math::Vector3d totalForce( 0.0, 0.0, 0.0 );
	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		totalForce += (*iter)->getForce() * (*iter)->getVolume();
	}

	const float weight =  getWeight( particles );
	for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
		(*iter)->setForce( totalForce / weight * (*iter)->getDensity() );
	}
}

float getAngleAccelerationX( float x1,float x2,float x3, const Vector3d& I, const Vector3d& N)
{
	return ( N.getX() + ( I.getY() - I.getZ() ) * x2 * x3 ) / I.getX() - 10.0f * x1;
}

float getAngleAccelerationY( float x1,float x2,float x3, const Vector3d& I, const Vector3d& N)
{
	return ( N.getY() + ( I.getZ() - I.getX() ) * x3 * x1 ) / I.getY() - 10.0f * x2;
}

float getAngleAccelerationZ( float x1, float x2, float x3, const Vector3d& I, const Vector3d& N)
{
	return ( N.getZ() + ( I.getX() - I.getY() ) * x1 * x2 ) / I.getZ() - 10.0f * x3;
}

void RigidCoordinator::getAngleVelosity( const Vector3d& I, const Vector3d& N, const float proceedTime )
{
	float x1,x2,x3;
	const int innerSteps = 10;
	float h = proceedTime / innerSteps;
	
	x1 = angleVelosity.getX();
	x2 = angleVelosity.getY();
	x3 = angleVelosity.getZ();

	for( int i = 0; i < innerSteps; i++ ){
		const float k11 = h * getAngleAccelerationX( x1, x2, x3, I, N);
		const float k21 = h * getAngleAccelerationY( x1, x2, x3, I, N);
		const float k31 = h * getAngleAccelerationZ( x1, x2, x3, I, N);
		const float k12 = h * getAngleAccelerationX( x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f, I, N );
		const float k22 = h * getAngleAccelerationY( x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f, I, N );
		const float k32 = h * getAngleAccelerationZ( x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f, I, N );
		const float k13 = h * getAngleAccelerationX( x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f, I, N );
		const float k23 = h * getAngleAccelerationY( x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f, I, N );
		const float k33 = h * getAngleAccelerationZ( x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f, I, N );
		const float k14 = h * getAngleAccelerationX( x1 + k13, x2 + k23, x3 + k33, I, N );
		const float k24 = h * getAngleAccelerationY( x1 + k13, x2 + k23, x3 + k33, I, N );
		const float k34 = h * getAngleAccelerationZ( x1 + k13, x2 + k23, x3 + k33, I, N );

		const float dx1 = ( k11 + 2.0f * k12 + 2.0f * k13 + k14 ) / 6.0f;
		const float dx2 = ( k21 + 2.0f * k22 + 2.0f * k23 + k24 ) / 6.0f;
		const float dx3 = ( k31 + 2.0f * k32 + 2.0f * k33 + k34 ) / 6.0f;

		x1 += dx1;
		x2 += dx2;
		x3 += dx3;
	}

	//angleVelosity.x = x1;
	//angleVelosity.y = x2;
	//angleVelosity.z = x3;
	angleVelosity = Vector3d( x1, x2, x3 );
}