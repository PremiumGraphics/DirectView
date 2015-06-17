#ifndef __CRYSTAL_GRAPHICS_POINT_CLOUD_H__
#define __CRYSTAL_GRAPHICS_POINT_CLOUD_H__

#include <memory>

#include "../Math/Vector.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class PointCloud final
{
public:
	PointCloud() = default;

	~PointCloud() = default;

	void add(const Math::Vector3d<T>& p) {
		positions.push_back(p);
	}

	void move(const Math::Vector3d<T>& v) {
		for (Math::Vector3d<T>& p : points) {
			p += v;
		}
	}

	void cash() {
		positions.clear();
		colors.clear();

		for (const auto& p : points) {
			const auto ps = p.toArray();
			positions.insert(positions.end(), ps.begin(), ps.end());

		}
	}

	std::vector<T> getPositions() const { return positions; }

	std::vector<T> getColors() const { return colors; }

private:
	Math::Vector3dVector<T> points;

	std::vector<T> positions;
	std::vector<T> colors;
};

template<typename T>
using PointCloudSPtr = std::shared_ptr < PointCloud<T> > ;
	}
}

#endif