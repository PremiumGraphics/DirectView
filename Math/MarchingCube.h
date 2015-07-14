#ifndef __CRYSTAL_MATH_MARCHING_CUBE_H__
#define __CRYSTAL_MATH_MARCHING_CUBE_H__


#include "Triangle.h"
#include "Vector.h"
#include "Space.h"
#include "../Util/UnCopyable.h"
#include "MarchingCubeTable.h"
#include <bitset>
#include <vector>
#include <array>
#include "Bitmap.h"
#include "BitSpace.h"
#include "Volume.h"

namespace Crystal {
	namespace Math {

template<typename GeomType = float, typename ValueType = float>
class MarchingCube final : UnCopyable
{
public:
	MarchingCube() = default;

	~MarchingCube() = default;

	Vector3d<GeomType> interpolate(const ValueType isolevel, const Vector3d<GeomType>& p1, const Vector3d<GeomType>& p2, const ValueType valp1, const ValueType valp2) const {
		const auto mu = (isolevel - valp1) / (valp2 - valp1);
		/*
		const auto x = p1.getX() + mu * (p2.getX() - p1.getX());
		const auto y = p1.getY() + mu * (p2.getY() - p1.getY());
		const auto z = p1.getZ() + mu * (p2.getZ() - p1.getZ());

		return Vector3d< T > ( x, y, z );
		*/
		return p1 + mu *(p2 - p1);
	}


	/*
	std::vector<Triangle<T> > build(const Bitmap3d<8>& bmp, const Space3d& space) {
		for (size_t i = 0; i < bmp.size(); ++i) {
			for (size_t j = 0; j > bmp[i].size(); ++j) {
				const b bmp[i]
			}
		}
	}
	*/

	TriangleVector<GeomType> march(const Volume3d<GeomType>& ss, const ValueType isolevel) const
	{
		TriangleVector<GeomType> triangles;
		const auto& cells = ss.toBoundaryCells(isolevel);
		for (const auto& c : cells) {
			const auto& ts = build(c.getSpace(), c.getValues(), isolevel);
			triangles.insert(triangles.end(), ts.begin(), ts.end());
		}
		return std::move(triangles);
	}


	TriangleVector<GeomType> build(const Space3d<GeomType>& s, const std::array< ValueType, 8 >& val, const ValueType isolevel) const
	{
		TriangleVector<GeomType> triangles;
		const std::array< Vector3d<GeomType>, 8 >& vs = s.toArray();
		const int cubeindex = getCubeIndex( val, isolevel );
		const auto& vertices = getPositions(cubeindex, vs, val, isolevel);
		return std::move( build(cubeindex, vertices) );
	}

	TriangleVector<GeomType> march(const BitSpace3d<GeomType>& bs)
	{
		TriangleVector<GeomType> triangles;
		const std::vector< BitCell3d<GeomType> >& cells = bs.toCells();
		for (const auto c : cells) {
			const auto ts = build(c.getSpace(), c.getValues());
			triangles.insert(triangles.end(), ts.begin(), ts.end());
		}
		return triangles;
	}

	TriangleVector<GeomType> build(const Space3d<GeomType>& s, const std::bitset< 8 >& bit ) const
	{
		const std::array< Vector3d<GeomType>, 8 >& vs = s.toArray();
		const int& cubeindex = bit.to_ulong();//getCubeIndex(val, isolevel);
		const auto& vertices = getPositions( cubeindex, vs );
		return std::move( build(cubeindex, vertices) );
	}

private:
	MarchingCubeTable table;

	TriangleVector<GeomType> build(const int cubeindex, const std::array<Vector3d<GeomType>, 12>& vertices) const {
		TriangleVector<GeomType> triangles;
		const auto& triTable = table.getTriangleTable();
		for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
			const auto& v1 = vertices[triTable[cubeindex][i]];
			const auto& v2 = vertices[triTable[cubeindex][i + 1]];
			const auto& v3 = vertices[triTable[cubeindex][i + 2]];
			const Triangle<GeomType> t(v1, v2, v3);
			triangles.emplace_back(t);
		}
		return std::move(triangles);
	}

	Vector3d<GeomType> getCenter(const Vector3d<GeomType>& p1, const Vector3d<GeomType>& p2) const {
		return p1 * 0.5 + p2 * 0.5;
	}


	int getCubeIndex(const std::array< ValueType, 8 >& val, const ValueType isolevel) const {
		std::bitset<8> bit;
		if (val[0] < isolevel) { bit.set(0); }
		if (val[1] < isolevel) { bit.set(1); }
		if (val[2] < isolevel) { bit.set(2); }
		if (val[3] < isolevel) { bit.set(3); }
		if (val[4] < isolevel) { bit.set(4); }
		if (val[5] < isolevel) { bit.set(5); }
		if (val[6] < isolevel) { bit.set(6); }
		if (val[7] < isolevel) { bit.set(7); }
		return static_cast<int>( bit.to_ulong() );
	}

	std::array< Vector3d<GeomType>, 12 > getPositions(const int cubeindex, const std::array< Vector3d<ValueType>, 8 > p) const {
		std::array< Vector3d<GeomType>, 12 > vertices;
		const auto& edgeTable = table.getEdgeTable();
//		if (edgeTable[cubeindex] & 1) {
		if (edgeTable[cubeindex][0] ) {
			vertices[0] = getCenter(p[0], p[1]);
		}
		//if (edgeTable[cubeindex] & 2) {
		if (edgeTable[cubeindex][1] ) {
			vertices[1] = getCenter(p[1], p[2]);
		}
		if (edgeTable[cubeindex][2] ) {
			vertices[2] = getCenter(p[2], p[3]);
		}
		if (edgeTable[cubeindex][3] ) {
			vertices[3] = getCenter(p[3], p[0]);
		}
		if (edgeTable[cubeindex][4] ) {
			vertices[4] = getCenter(p[4], p[5]);
		}
		if (edgeTable[cubeindex][5] ) {
			vertices[5] = getCenter(p[5], p[6]);
		}
		if (edgeTable[cubeindex][6]) {
			vertices[6] = getCenter(p[6], p[7]);
		}
		if (edgeTable[cubeindex][7] ) {
			vertices[7] = getCenter(p[7], p[4]);
		}
		if (edgeTable[cubeindex][8] ) {
			vertices[8] = getCenter(p[0], p[4]);
		}
		if (edgeTable[cubeindex][9] ) {
			vertices[9] = getCenter(p[1], p[5]);
		}
		if (edgeTable[cubeindex][10] ) {
			vertices[10] = getCenter(p[2], p[6]);
		}
		if (edgeTable[cubeindex][11] ) {
			vertices[11] = getCenter(p[3], p[7]);
		}
		return vertices;
	}


	std::array< Vector3d<GeomType>, 12 > getPositions(const int cubeindex, const std::array< Vector3d<GeomType>, 8 > p, const std::array< ValueType, 8 >& val, const ValueType isolevel) const {
		std::array< Vector3d<GeomType>, 12 > vertices;
		const auto& edgeTable = table.getEdgeTable();
		if (edgeTable[cubeindex][0]) {
			vertices[0] = interpolate(isolevel, p[0], p[1], val[0], val[1]);
		}
		if (edgeTable[cubeindex][1]) {
			vertices[1] = interpolate(isolevel, p[1], p[2], val[1], val[2]);
		}
		if (edgeTable[cubeindex][2]) {
			vertices[2] = interpolate(isolevel, p[2], p[3], val[2], val[3]);
		}
		if (edgeTable[cubeindex][3]) {
			vertices[3] = interpolate(isolevel, p[3], p[0], val[3], val[0]);
		}
		if (edgeTable[cubeindex][4]) {
			vertices[4] = interpolate(isolevel, p[4], p[5], val[4], val[5]);
		}
		if (edgeTable[cubeindex][5]) {
			vertices[5] = interpolate(isolevel, p[5], p[6], val[5], val[6]);
		}
		if (edgeTable[cubeindex][6]) {
			vertices[6] = interpolate(isolevel, p[6], p[7], val[6], val[7]);
		}
		if (edgeTable[cubeindex][7]) {
			vertices[7] = interpolate(isolevel, p[7], p[4], val[7], val[4]);
		}
		if (edgeTable[cubeindex][8]) {
			vertices[8] = interpolate(isolevel, p[0], p[4], val[0], val[4]);
		}
		if (edgeTable[cubeindex][9]) {
			vertices[9] = interpolate(isolevel, p[1], p[5], val[1], val[5]);
		}
		if (edgeTable[cubeindex][10]) {
			vertices[10] = interpolate(isolevel, p[2], p[6], val[2], val[6]);
		}
		if (edgeTable[cubeindex][11]) {
			vertices[11] = interpolate(isolevel, p[3], p[7], val[3], val[7]);
		}
		return vertices;
	}


public:
	void buildTable() {
		table.buildEdgeTable();
		table.buildTriangleTable();

	}

};
	}
}

#endif