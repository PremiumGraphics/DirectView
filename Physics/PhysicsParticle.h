#ifndef __CRYSTAL_PHYSICS_PARTICLE_H__
#define __CRYSTAL_PHYSICS_PARTICLE_H__

#include <list>
#include <vector>
#include <memory>

#include "../Math/Vector3d.h"

#include "../Util/UnCopyable.h"

namespace Crystal{
	namespace Physics{
		class Coordinator;
		
class PhysicsParticle final : private UnCopyable
{
public:
	
	struct Constant
	{
		float pressureCoe;
		float viscosityCoe;

		void setDiameter(const float d) { this->diameter = d; }

		float getDiameter() const { return diameter; }

		float getRestDensity() const { return restDensity; }

		float getVolume() const { return std::pow(diameter, 3); }

		Constant() :
			pressureCoe( 1.0f ),
			viscosityCoe( 0.0 ),
			restDensity( 1.0f ),
			diameter( 1.0f )
		{}

	private:
		float diameter;
		float restDensity;
	};
	
	PhysicsParticle()
	{
	}

	PhysicsParticle( const Math::Vector3d& center ) :
		center( center )
	{}

	PhysicsParticle(const Constant& constant, const Math::Vector3d& center) :
	constant( constant ),
	center( center )
	{
	}

	float getDensityRatio() const;

	float getPressure() const;

	float getMass() const;

	float getVolume() const {
		return getMass() / density;
	}

	float getRestVolume() const {
		return getMass() / getRestDensity();
	}

	void addForce(const Math::Vector3d& force) { this->force += force; }

	void setForce( const Math::Vector3d& force ) { this->force = force; }

	Math::Vector3d getForce() const { return force; }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	float getRestDensity() const { return constant.getRestDensity(); }

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

	static bool compare(const std::shared_ptr<PhysicsParticle>& lhs, const std::shared_ptr<PhysicsParticle>& rhs){
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

using PhysicsParticleSPtr = std::shared_ptr < PhysicsParticle > ;

using PhysicsParticleSPtrList = std::list < PhysicsParticleSPtr > ;

using PhysicsParticleSPtrVector = std::vector < PhysicsParticleSPtr > ;

//typedef std::pair<Particle*, Particle*> ParticlePair;


	}
}

#endif