#ifndef __CRYSTAL_PHYSICS_PARTICLE_H__
#define __CRYSTAL_PHYSICS_PARTICLE_H__

#include <list>
#include <vector>

#include "../Math/Vector3d.h"

namespace Crystal{
	namespace Physics{
		class Coordinator;

class ParticleBase {
public:
	ParticleBase(const float diameter, const Math::Vector3d& position) :
		diameter( diameter )
	{}

	Math::Vector3d getPosition() const { return position; }

	float getVolume() const { return diameter * diameter * diameter; }

private:
	float diameter;
	Math::Vector3d position;
};
		
class Particle 
{
public:
	
	struct Constant
	{
		float pressureCoe;
		float viscosityCoe;
		float restDensity;
		float diameter;
	};
	
	Particle::Particle(const Constant& constant, const Math::Vector3d& center) :
	constant( constant ),
	center( center )
	{
	}

	float getDensityRatio() const {
		return density / constant.restDensity;
	}

	float getPressure() const {
		return constant.pressureCoe * ( std::pow( getDensityRatio(), 1 ) - 1.0f );
	}

	float getMass() const {
		return constant.restDensity * std::pow( constant.diameter, 3 );
	}

	float getVolume() const {
		return getMass() / density;
	}

	void addForce(const Math::Vector3d& force) { this->force += force; }

	void setForce( const Math::Vector3d& force ) { this->force = force; }

	Math::Vector3d getForce() const { return force; }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	void init() {
		density = 0.0;
		force = Math::Vector3d( 0.0f, 0.0f, 0.0f);
	}

	void addCenter( const Math::Vector3d& center ) { this->center += center; }

	void setCenter( const Math::Vector3d& center ) { this->center = center; } 

	Math::Vector3d getCenter() const { return center; }

	Math::Vector3d getAccelaration() { return force / density; }

	Math::Vector3d getVelocity() const { return velocity; }

	void setVelocity( const Math::Vector3d& velocity ) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3d& velocity) { this->velocity += velocity; }

	float getViscosityCoe() const { return constant.viscosityCoe; }

private:
	const Constant constant;

public:
	void setGridID( const float effectLength ) {
		const Math::Vector3d& point = center;
		int gridX = static_cast<int>( point.getX() / effectLength );
		int gridY = static_cast<int>( point.getY() / effectLength );
		int gridZ = static_cast<int>( point.getZ() / effectLength );
		gridID = getID( gridX, gridY, gridZ );
	}

	int getGridID() const { return gridID; }

	static bool compare( Particle* lhs, Particle* rhs ){
		return lhs->getGridID() < rhs->getGridID();
	}


private:
	int getID( int idX, int idY, int idZ ) const {
		return (idZ << 20) + (idY << 10) + idX;
	}

	float density;
	Math::Vector3d force;
	Math::Vector3d velocity;
	Math::Vector3d center;
	int gridID;
};

typedef std::vector<Particle*> ParticleVector;

typedef std::list<Particle*> ParticleList;

//typedef std::pair<Particle*, Particle*> ParticlePair;

struct ParticlePair{
	ParticlePair( Particle* particle1, Particle* particle2 ) :
		particle1( particle1 ), particle2( particle2 )
	{
	}
	Particle* particle1;
	Particle* particle2;

	Math::Vector3d getDistanceVector() const {
		return Math::Vector3d( particle1->getCenter() - particle2->getCenter() );
	}

	float getDistance() const {
		return getDistanceVector().getLength();
	}

	float getPressure() const {
		return ( particle1->getPressure() + particle2->getPressure() ) * 0.5f;
	}

	float getViscosityCoe() const {
		return ( particle1->getViscosityCoe() + particle2->getViscosityCoe() ) * 0.5f;
	}

	Math::Vector3d getVelocityDiff() const {
		return Math::Vector3d( particle1->getVelocity(), particle2->getVelocity() );
	}
};

typedef std::vector<ParticlePair> ParticlePairVector; 

	}
}

#endif