#ifndef __CRYSTAL_GRAPHICS_BONE_H__
#define __CRYSTAL_GRAPHICS_BONE_H__

#include "../Math/Vector.h"
#include "../Math/Line.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Bone
{
public:
	Bone(const Math::Vector3d<T>& start, const Math::Vector3d<T>& end) :
		start( start ),
		end( end )
	{
	}

	Math::Line3d<T> getLine() const {
		return Math::Line3d<T>(start, end);
	}

	Math::Vector3dVector<T> getPosition(const T param) const {
		return getLine().getPosition(param);
	}

private:
	Math::Vector3d<T> start;
	Math::Vector3d<T> end;
};
	}
}

#endif