#include "Voxel.h"

using namespace Crystal::Math;

std::vector< Voxel* > Voxel::createChildren()
{
	if (!children.empty()) {
		return std::vector< Voxel* >();
	}

	const float minx = box.getMinX();
	const float miny = box.getMinY();
	const float minz = box.getMinZ();

	const float midx = minx + box.getLength().getX() * 0.5f;
	const float midy = minx + box.getLength().getY() * 0.5f;
	const float midz = miny + box.getLength().getZ() * 0.5f;

	const float maxx = box.getMaxX();
	const float maxy = box.getMaxY();
	const float maxz = box.getMaxZ();

	this->children = std::vector < Voxel* > {
		new Voxel(Box(Vector3d(minx, miny, minz), Vector3d(midx, midy, midz)), this),
		new Voxel(Box(Vector3d(midx, miny, minz), Vector3d(maxx, midy, midz)), this),
		new Voxel(Box(Vector3d(midx, midy, minz), Vector3d(maxx, midy, midz)), this),
		new Voxel(Box(Vector3d(minx, midy, midz), Vector3d(maxx, midy, midz)), this),
		nullptr,
		nullptr,
		nullptr,
		nullptr
	};

	return children;
}