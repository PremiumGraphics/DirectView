#ifndef __CRYSTAL_GRAPHICS_BUFFER_H__
#define __CRYSTAL_GRAPHICS_BUFFER_H__

#include "../Graphics/Surface.h"

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
	void add(const Surface<T>& surface, const int type, const int id, const int isSelected) {
		for (const auto& e : surface.getEdges()) {
			addPosition(e->getStartPosition(), type, id, isSelected);
			addPosition(e->getEndPosition(), type, id, isSelected);
		}
		//positions.add( surface.)
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