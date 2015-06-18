#ifndef __CRYSTAL_GRAPHICS_BUFFER_H__
#define __CRYSTAL_GRAPHICS_BUFFER_H__

#include "../Graphics/Surface.h"
#include "../Math/Volume.h"
#include "../Math/Line.h"

#include <vector>

namespace Crystal {
	namespace Graphics {

template<typename T>
class BufferBase
{
public:

	virtual ~BufferBase() = default;

	void addPosition(const Math::Vector3d<T>& position, const int type, const int id, const int isSelected) {
		const auto& poss = position.toArray();
		positions.insert(positions.end(), poss.begin(), poss.end());
		types.push_back(type);
		ids.push_back(id);
		isSelecteds.push_back(isSelected);
	}

	std::vector<T> getPositions() const { return positions; }

	std::vector<int> getTypes() const { return types; }

	std::vector<int> getIds() const { return ids; }

	std::vector<int> getIsSelecteds() const { return isSelecteds; }

	void clear() {
		positions.clear();
		types.clear();
		ids.clear();
		isSelecteds.clear();
	}

	bool isEmpty() const {
		return positions.empty();
	}

private:
	std::vector<T> positions;
	std::vector<int> types;
	std::vector<int> ids;
	std::vector<int> isSelecteds;
};

template<typename T>
class PointBuffer : public BufferBase<T>
{
public:
	void add(const Surface<T>& surface, const int type, const int id, const int isSelected) {
		for (const auto& v : surface.getVertices()) {
			const auto pos = v->getPosition();
			addPosition( pos, type, id, isSelected);
		}
		//positions.add( surface.)
	}
};

template<typename T>
class LineBuffer : public BufferBase < T >
{
public:
	void add(const Math::Volume3d<T>& volume, const int type, const int id, const int isSelected) {
		const auto minx = volume.getStart().getX();
		const auto miny = volume.getStart().getY();
		const auto minz = volume.getStart().getZ();
		const auto maxx = volume.getEnd().getX();
		const auto maxy = volume.getEnd().getY();
		const auto maxz = volume.getEnd().getZ();
	
		const Math::Vector3dVector<T> vs = {
			Math::Vector3d<T>(minx, miny, minz),
			Math::Vector3d<T>(maxx, miny, minz),
			Math::Vector3d<T>(maxx, maxy, minz),
			Math::Vector3d<T>(minx, maxy, minz),
			Math::Vector3d<T>(minx, miny, maxz),
			Math::Vector3d<T>(maxx, miny, maxz),
			Math::Vector3d<T>(maxx, maxy, maxz),
			Math::Vector3d<T>(minx, maxy, maxz)
		};

		const Math::Line3dVector<T> lines{
			Math::Line3d<T>(vs[0], vs[1]),
			Math::Line3d<T>(vs[1], vs[2]),
			Math::Line3d<T>(vs[2], vs[3]),
			Math::Line3d<T>(vs[3], vs[0]),
			Math::Line3d<T>(vs[4], vs[5]),
			Math::Line3d<T>(vs[5], vs[6]),
			Math::Line3d<T>(vs[6], vs[7]),
			Math::Line3d<T>(vs[7], vs[4]),
			Math::Line3d<T>(vs[0], vs[4]),
			Math::Line3d<T>(vs[1], vs[5]),
			Math::Line3d<T>(vs[2], vs[6]),
			Math::Line3d<T>(vs[3], vs[7])
		};

		for (const auto& l : lines) {
			add(l, type, id, isSelected);
		}
	}


	void add(const Surface<T>& surface, const int type, const int id, const int isSelected) {
		for (const auto& e : surface.getEdges()) {
			addPosition(e->getStartPosition(), type, id, isSelected);
			addPosition(e->getEndPosition(), type, id, isSelected);
		}
		//positions.add( surface.)
	}

	void add(const Math::Line3d<T>& line, const int type, const int id, const int isSelected) {
		addPosition(line.getStart(), type, id, isSelected);
		addPosition(line.getEnd(), type, id, isSelected);
	}
};

template<typename T>
class TriangleBuffer : public BufferBase < T >
{
public:
	void add(const Surface<T>& surface, const int type, const int id, const int isSelected) {
		for (const auto& v : surface.getVertices()) {
			const auto pos = v->getPosition();
			addPosition(pos, type, id, isSelected);
		}
		//positions.add( surface.)
	}

};
	}
}

#endif