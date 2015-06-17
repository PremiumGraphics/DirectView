#ifndef __CRYSTAL_COMMAND_POINT_CLOUD_MODEL__
#define __CRYSTAL_COMMAND_POINT_CLOUD_MODEL__

#include <list>

#include "Object.h"

#include "../Graphics/PointCloud.h"

namespace Crystal {
	namespace Command {

template<typename T>
class PointCloudObject final : public Object
{
public:
	PointCloudObject(const Graphics::PointCloudSPtr<T>& pointCloud, const unsigned int id) :
		Object(id),
		pointCloud(pointCloud)
	{}

	Graphics::PointCloudSPtr<T> getPointCloud() const { return pointCloud; }

	Type getType() const { return Type::PointCloud; }

	virtual void move(const Math::Vector3d<T>& vector) override
	{
		pointCloud->move(vector);
	}

private:
	Graphics::PointCloudSPtr<T> pointCloud;
};

template<typename T>
using PointCloudObjectSPtr = std::shared_ptr < PointCloudObject<T> > ;

template<typename T>
using PointCloudObjectSPtrList = std::list < PointCloudObjectSPtr<T> > ;

/*
template<typename T>
class PointCloudModel final : public ModelBase
{
public:
	PointCloudModel() = default;

	~PointCloudModel() = default;

	void clear() {
		ModelBase::clear();
		objects.clear();
	}

	PointCloudObjectSPtr create() {
		return Point
	}

private:
	PointCloudObjectSPtrList<T> objects;

	PointCloudObjectSPtr<T> add(const Graphics::PointCloudSPtr<T>& pointCloud) {
		objects.push_back(std::make_shared< PointCloudObject<float> >(getNextId(), pointCloud));
		return spaces.back();
	}

};
*/
	}
}



#endif