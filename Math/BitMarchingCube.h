#ifndef __CRYSTAL_MATH_BIT_MARCHING_CUBE_H__
#define __CRYSTAL_MATH_BIT_MARCHING_CUBE_H__

#include "BitSpace.h"
#include "Triangle.h"
#include "MarchingCubeTable.h"

namespace Crystal {
	namespace Math {

template<typename GeomType>
class BitMarchingCube
{
public:
	BitMarchingCube() {
		table.buildEdgeTable();
		table.buildTriangleTable();
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

	TriangleVector<GeomType> build(const Space3d<GeomType>& s, const std::bitset< 8 >& bit) const
	{
		const std::array< Vector3d<GeomType>, 8 >& vs = s.toArray();
		const int& cubeindex = bit.to_ulong();//getCubeIndex(val, isolevel);
		const auto& vertices = getPositions(cubeindex, vs);
		return std::move(build(cubeindex, vertices));
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


	std::array< Vector3d<GeomType>, 12 > getPositions(const int cubeindex, const std::array< Vector3d<GeomType>, 8 > p) const {
		std::array< Vector3d<GeomType>, 12 > vertices;
		const auto& edgeTable = table.getEdgeTable();
		//		if (edgeTable[cubeindex] & 1) {
		if (edgeTable[cubeindex][0]) {
			vertices[0] = getCenter(p[0], p[1]);
		}
		//if (edgeTable[cubeindex] & 2) {
		if (edgeTable[cubeindex][1]) {
			vertices[1] = getCenter(p[1], p[2]);
		}
		if (edgeTable[cubeindex][2]) {
			vertices[2] = getCenter(p[2], p[3]);
		}
		if (edgeTable[cubeindex][3]) {
			vertices[3] = getCenter(p[3], p[0]);
		}
		if (edgeTable[cubeindex][4]) {
			vertices[4] = getCenter(p[4], p[5]);
		}
		if (edgeTable[cubeindex][5]) {
			vertices[5] = getCenter(p[5], p[6]);
		}
		if (edgeTable[cubeindex][6]) {
			vertices[6] = getCenter(p[6], p[7]);
		}
		if (edgeTable[cubeindex][7]) {
			vertices[7] = getCenter(p[7], p[4]);
		}
		if (edgeTable[cubeindex][8]) {
			vertices[8] = getCenter(p[0], p[4]);
		}
		if (edgeTable[cubeindex][9]) {
			vertices[9] = getCenter(p[1], p[5]);
		}
		if (edgeTable[cubeindex][10]) {
			vertices[10] = getCenter(p[2], p[6]);
		}
		if (edgeTable[cubeindex][11]) {
			vertices[11] = getCenter(p[3], p[7]);
		}
		return vertices;
	}


	Vector3d<GeomType> getCenter(const Vector3d<GeomType>& p1, const Vector3d<GeomType>& p2) const {
		return p1 * 0.5 + p2 * 0.5;
	}

};
	}
}

#endif