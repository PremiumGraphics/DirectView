#include "../Math/Line.h"

#include "Joint.h"
#include <list>


namespace Crystal {
	namespace Actor {

template<typename T>
class Bone
{
public:
	Bone() = default;

	Bone(const JointSPtr<T>& start, const JointSPtr<T>& end) :
		start(start),
		end(end)
	{
	}

	Math::Line3d<T> getLine() const {
		return Math::Line3d<T>(start->getPosition(), end->getPosition());
	}

	/*
	Math::Vector3dVector<float> getPosition(const float param) const {
	return getLine().getPosition(param);
	}
	*/

	void move(const Math::Vector3d<float>& v) {
		start->move(v);
		end->move(v);
	}

	void moveStart(const Math::Vector3d<T>& v) {
		start->move(v);
	}

	void moveEnd(const Math::Vector3d<float>& v) {
		end->move(v);
	}

private:
	JointSPtr<T> start;
	JointSPtr<T> end;
};
	}
}