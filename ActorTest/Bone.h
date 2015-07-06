#include "../Math/Line.h"

namespace Crystal {
	namespace Actor {

template<typename T>
class Bone
{
public:
	Bone() = default;

	Bone(const Math::Vector3d<T>& start, const Math::Vector3d<T>& end) :
		start(start),
		end(end)
	{
	}

	Math::Line3d<T> getLine() const {
		return Math::Line3d<T>(start, end);
	}

	/*
	Math::Vector3dVector<float> getPosition(const float param) const {
	return getLine().getPosition(param);
	}
	*/

	void move(const Math::Vector3d<float>& v) {
		start += v;
		end += v;
	}

	void moveEnd(const Math::Vector3d<float>& v) {
		end += v;
	}

private:
	Math::Vector3d<T> start;
	Math::Vector3d<T> end;
};

	}
}