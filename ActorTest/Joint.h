#ifndef __CRYSTAL_ACTOR_JOINT_H__
#define __CRYSTAL_ACTOR_JOINT_H__

#include "../Math/Vector.h"
#include <list>
#include <memory>

namespace Crystal{
	namespace Actor{

template<typename T>
class Joint {
public:
	Joint() = default;

	~Joint() = default;

	explicit Joint(const Math::Vector3d<T>& position) :
		position(position)
	{}

	Math::Vector3d<T> getPosition() const { return position; }

	void move(const Math::Vector3d<T>& v) {
		position += v;
	}

private:
	Math::Vector3d<T> position;
};

template<typename T>
using JointSPtr = std::shared_ptr < Joint<T> > ;


template<typename T>
using JointList = std::list < Joint<T> > ;
	}
}

#endif