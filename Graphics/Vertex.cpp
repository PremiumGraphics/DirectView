#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

VertexSPtr VertexBuilder::build(const Vector3d& position)
{
	VertexSPtr v = VertexSPtr(new Vertex(position, nextId++));
	vertices.push_back(v);
	return v;
}

VertexSPtr VertexBuilder::build(const Vector3d& position, const Vector3d& normal)
{
	VertexSPtr v = VertexSPtr(new Vertex(position, normal, nextId++));
	vertices.push_back(v);
	return v;
}

VertexSPtr VertexBuilder::build(const Vector3d& position, const Vector3d& normal, const Vector3d& texCoord)
{
	VertexSPtr v = VertexSPtr(new Vertex(position, normal, texCoord, nextId++));
	vertices.push_back(v);
	return v;
}

VertexSPtrVector VertexBuilder::buildVerticesFromPositions(const Vector3dVector& positions)
{
	VertexSPtrVector vv;
	for (const Math::Vector3d& position : positions) {
		VertexSPtr v(new Vertex(position, nextId++));
		vv.push_back(v);
	}
	vertices.insert(vertices.end(), vv.begin(), vv.end());
	return vv;
}

VertexSPtrVector VertexBuilder::buildVerticesFromPositionsAndNormals(const Vector3dVector& positions, const Vector3dVector& normals)
{
	assert(positions.size() == normals.size());
	VertexSPtrVector vv;
	for (size_t i = 0; i < positions.size(); ++i) {
		VertexSPtr v(new Vertex(positions[i], normals[i], nextId++));
		vv.push_back(v);
	}
	vertices.insert(vertices.end(), vv.begin(), vv.end());
	return vv;
}

VertexSPtrVector VertexBuilder::buildVerticesFromPositionsNormalsTexCoords(const Vector3dVector& positions, const Vector3dVector& normals, const Vector3dVector& texCoords)
{
	assert(positions.size() == normals.size());
	assert(normals.size() == texCoords.size());
	VertexSPtrVector vv;
	for (size_t i = 0; i < positions.size(); ++i) {
		VertexSPtr v( new Vertex(positions[i], normals[i], texCoords[i], i) );
		vv.push_back(v);
	}
	vertices.insert(vertices.end(), vv.begin(), vv.end());
	return vv;
}
