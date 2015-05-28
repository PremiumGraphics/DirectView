#ifndef __CRYSTAL_PHYSICS_PARTICLE_H__
#define __CRYSTAL_PHYSICS_PARTICLE_H__

#include <list>
#include <vector>
#include <memory>

#include "../Math/Vector.h"

#include "../Util/UnCopyable.h"

namespace Crystal{
	namespace Physics{
		class Coordinator;

template<typename T>
class Particle final : private UnCopyable
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
	
	Particle()
	{
	}

	Particle( const Math::Vector3d<T>& center ) :
		center( center )
	{}

	Particle(const Constant& constant, const Math::Vector3d<T>& center) :
	constant( constant ),
	center( center )
	{
	}

	float getDensityRatio() const {
		return density / constant.getRestDensity();
	}

	float getPressure() const {
		return constant.pressureCoe * (std::pow(getDensityRatio(), 1) - 1.0f);
	}

	float getMass() const {
		return constant.getRestDensity() * std::pow(constant.getDiameter(), 3);
	}

	float getVolume() const {
		return getMass() / density;
	}

	float getRestVolume() const {
		return getMass() / getRestDensity();
	}

	void addForce(const Math::Vector3d<T>& force) { this->force += force; }

	void setForce( const Math::Vector3d<T>& force ) { this->force = force; }

	Math::Vector3d<T> getForce() const { return force; }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	float getRestDensity() const { return constant.getRestDensity(); }

	void init() {
		density = 0.0;
		force = Math::Vector3d<T>( 0.0f, 0.0f, 0.0f);
	}

	void addCenter( const Math::Vector3d<T>& center ) { this->center += center; }

	void setCenter( const Math::Vector3d<T>& center ) { this->center = center; } 

	Math::Vector3d<T> getCenter() const { return center; }

	Math::Vector3d<T> getAccelaration() { return force / density; }

	Math::Vector3d<T> getVelocity() const { return velocity; }

	void setVelocity( const Math::Vector3d<T>& velocity ) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3d<T>& velocity) { this->velocity += velocity; }

	float getViscosityCoe() const { return constant.viscosityCoe; }

private:
	const Constant constant;

public:
	void setGridID( const float effectLength ) {
		const Math::Vector3d<T>& point = center;
		int gridX = static_cast<int>( point.getX() / effectLength );
		int gridY = static_cast<int>( point.getY() / effectLength );
		int gridZ = static_cast<int>( point.getZ() / effectLength );
		gridID = getID( gridX, gridY, gridZ );
	}

	int getGridID() const { return gridID; }

	static bool compare(const std::shared_ptr<Particle>& lhs, const std::shared_ptr<Particle>& rhs){
		return lhs->getGridID() < rhs->getGridID();
	}


private:
	int getID( int idX, int idY, int idZ ) const {
		return (idZ << 20) + (idY << 10) + idX;
	}

	float density;
	Math::Vector3d<T> force;
	Math::Vector3d<T> velocity;
	Math::Vector3d<T> center;
	int gridID;
};

using ParticleSPtr = std::shared_ptr < Particle<float> > ;

using ParticleSPtrList = std::list < ParticleSPtr > ;

using ParticleSPtrVector = std::vector < ParticleSPtr > ;

//typedef std::pair<Particle*, Particle*> ParticlePair;


	}
}

#endif