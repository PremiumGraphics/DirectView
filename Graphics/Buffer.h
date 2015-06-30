#ifndef __CRYSTAL_GRAPHICS_BUFFER_H__
#define __CRYSTAL_GRAPHICS_BUFFER_H__

#include "../Graphics/Surface.h"
#include "../Math/Volume.h"
#include "../Math/Line.h"
#include "../Math/Range.h"


#include <vector>

namespace Crystal {
	namespace Graphics {



template<typename T>
class LineBuffer final
{
public:
	void clear() {
		positions.clear();
		normals.clear();
	}


	void add(const Math::Volume3d<T>& volume ) {
		const Math::Box<T> v(volume.getStart(), volume.getEnd());
		add(v);
	}

	void add(const Math::Box<T>& box ) {
		const auto minx = box.getMinX();
		const auto miny = box.getMinY();
		const auto minz = box.getMinZ();
		const auto maxx = box.getMaxX();
		const auto maxy = box.getMaxY();
		const auto maxz = box.getMaxZ();

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
			add(l);
		}

	}

	void add(const Surface<T>& surface ) {
		for (const auto& e : surface.getEdges()) {
			addPosition(e->getStartPosition(), e->getStartVertex()->getNormal() );
			addPosition(e->getEndPosition(), e->getEndVertex()->getNormal() );
		}
		//positions.add( surface.)
	}

	void add(const Math::Line3d<T>& line ) {
		addPosition(line.getStart(), Math::Vector3d<T>::Zero() );
		addPosition(line.getEnd(), Math::Vector3d<T>::Zero() );
	}

	void addPosition(const Math::Vector3d<T>& position, const Math::Vector3d<T>& normal) {
		const auto& poss = position.toArray3();
		positions.insert(positions.end(), std::begin( poss), std::end(poss));
		const auto& norms = normal.toArray3();
		normals.insert(normals.end(), std::begin(poss), std::end( poss));
	}


	std::vector<T> getPositions() const { return positions; }

	std::vector<T> getNormals() const { return normals; }

private:
	std::vector<T> positions;
	std::vector<T> normals;

};

template<typename T>
class TriangleBuffer final
{
public:
	void clear() {
		positions.clear();
		normals.clear();
	}

	void add(const Surface<T>& surface) {
		for (const auto& v : surface.getVertices()) {
			const auto& pos = v->getPosition();
			const auto& norms = v->getNormal();
			addPosition(pos, norms );
		}
		//positions.add( surface.)
	}

	void addPosition(const Math::Vector3d<T>& position, const Math::Vector3d<T>& normal) {
		const auto& poss = position.toArray3();
		positions.insert(positions.end(), std::begin(poss), std::end(poss));
		const auto& norms = normal.toArray3();
		normals.insert(normals.end(), std::begin(poss), std::end(poss));
	}



	std::vector<T> getPositions() const { return positions; }

	std::vector<T> getNormals() const { return normals; }

private:
	std::vector<T> positions;
	std::vector<T> normals;

};


template<typename T>
class VolumeBuffer final
{
public:
	VolumeBuffer() :
	range( 0.0, 1.0)
	{
	}

	void add(const Math::Volume3d<T>& volume) {
		const auto& ps = volume.toCenterPositions();
		const auto& vs = volume.getValues();
		assert(ps.size() == vs.size());
		for (size_t i = 0; i < ps.size(); ++i) {
			const auto& pss = ps[i].toArray();
			positions.insert(positions.end(), pss.begin(), pss.end());
			values.emplace_back( vs[i] );
		}
		//positions.add( surface.)
	}

	std::vector<T> getPositions() const { return positions; }

	std::vector<T> getValues() const { return values; }

	void clear() {
		positions.clear();
		values.clear();
	}

private:
	std::vector<T> positions;
	std::vector<T> values;
	Math::Range<T> range;
};

	}
}

#endif