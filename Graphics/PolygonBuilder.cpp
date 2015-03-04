#include "PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void PolygonBuilder::buildQuad()
{
	positions = {
		new Vertex( Vector3d(0.0, 1.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 0 ),
		new Vertex( Vector3d(0.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 1 ),
		new Vertex( Vector3d(1.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 2 ),
		new Vertex( Vector3d(1.0, 1.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 3 )
	};

	normals = {
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	};

	faces = { Face({ 0, 1, 2, 3 }, { 0, 1, 2, 3 }) };
}

void PolygonBuilder::buildBox()
{
	positions = {
		new Vertex( Vector3d(0.0, 1.0, 1.0), 0 ),
		new Vertex( Vector3d(0.0, 0.0, 1.0), 1 ),
  		new Vertex( Vector3d(1.0, 0.0, 1.0), 2 ),
		new Vertex( Vector3d(1.0, 1.0, 1.0), 3 ),
		new Vertex( Vector3d(0.0, 1.0, 0.0), 4 ),
		new Vertex( Vector3d(0.0, 0.0, 0.0), 5 ),
		new Vertex( Vector3d(1.0, 0.0, 0.0), 6 ),
		new Vertex( Vector3d(1.0, 1.0, 0.0), 7 )
	};

	normals = {
		Vector3d( 0.0, 0.0, 1.0),
		Vector3d( 0.0, 0.0,-1.0),
		Vector3d( 1.0, 0.0, 0.0),
		Vector3d(-1.0, 0.0, 0.0),
		Vector3d( 0.0,-1.0, 0.0),
		Vector3d( 0.0, 1.0, 0.0)
	};

	faces = {
		Face({ 0, 1, 2, 3 }, { 0, 0, 0, 0 }),
		Face({ 4, 5, 6, 7 }, { 1, 1, 1, 1 }),
		Face({ 0, 1, 5, 4 }, { 2, 2, 2, 2 }),
		Face({ 2, 3, 7, 6 }, { 3, 3, 3, 3 }),
		Face({ 3, 0, 4, 7 }, { 4, 4, 4, 4 }),
		Face({ 5, 1, 2, 6 }, { 5, 5, 5, 5 })
	};
}

void PolygonBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	std::vector<unsigned int> vertexIds;
	std::vector<unsigned int> normalIds;

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		positions.push_back( new Vertex( radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f), i ) );
		vertexIds.push_back(i);
		normalIds.push_back(0);
	}
	normals.push_back(Vector3d(0.0, 0.0, 1.0));
	Face f(vertexIds,normalIds);
	faces.push_back(f);
}

void PolygonBuilder::buildCircleByAngle(const float radius, const float divideAngle)
{
	buildCircleByNumber(radius, 360.0f / divideAngle);
}

void PolygonBuilder::buildCylinder(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	normals = {
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, -1.0),
	};

	std::vector<unsigned int> vertexIds0;
	std::vector<unsigned int> normalIds0;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		positions.push_back( new Vertex( Vector3d(std::sin(rad), std::cos(rad), 0.0f), i ));
		vertexIds0.push_back(i);
		normalIds0.push_back(0);
	}
	faces.push_back( Face( vertexIds0, normalIds0 ) );

	std::vector<unsigned int> vertexIds1;
	std::vector<unsigned int> normalIds1;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		positions.push_back( new Vertex( Vector3d(std::sin(rad), std::cos(rad), 1.0f), divideNumber + i ));
		vertexIds1.push_back( divideNumber + i);
		normalIds1.push_back(1);
	}
	faces.push_back( Face( vertexIds1, normalIds1) );

	for (unsigned int i = 0; i < divideNumber-1; ++i) {
		const unsigned int v0 = vertexIds0[i];
		const unsigned int v1 = vertexIds0[i+1];
		const unsigned int v2 = vertexIds1[i+1];
		const unsigned int v3 = vertexIds1[i];
		normals.push_back(Vector3d(0.0, 0.0, 0.0));
		faces.push_back(Face({ v0, v1, v2, v3 }));
	}

	{
		const unsigned int v0 = vertexIds0.back();
		const unsigned int v1 = vertexIds0.front();
		const unsigned int v2 = vertexIds1.front();
		const unsigned int v3 = vertexIds1.back();
		normals.push_back(Vector3d(0.0, 0.0, 0.0));
		faces.push_back(Face({ v0, v1, v2, v3 }));
	}

}

void PolygonBuilder::buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber)
{
	for (unsigned int i = 0; i < uDivideNumber; ++i) {
		std::vector<unsigned int> vertexIds;
		std::vector<unsigned int> normalIds;
		for (unsigned int k = 0; k < vDivideNumber; ++k) {
			const float vAngle = 180.0f / vDivideNumber * k;
			const float vRadius = vAngle * Tolerances::getPI() / 180.0f;

			const float uAngle = 360.0f / uDivideNumber * i;
			const float rad = uAngle *Tolerances::getPI() / 180.0f;
			positions.push_back( new Vertex( Vector3d(std::sin(rad), std::cos(rad), 0.0f) * vRadius, i ) );
			normals.push_back(Vector3d(std::sin(rad), std::cos(rad), 0.0f));
			vertexIds.push_back(i);
			normalIds.push_back(i);
		}
	}
	//f.setVertexIds(vertexIds);
	//f.setNormalIds(normalIds);
}

void PolygonBuilder::buildCone(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);
	std::vector<unsigned int> vertexIds;
	std::vector<unsigned int> normalIds;

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		positions.push_back( new Vertex(  Vector3d(std::sin(rad), std::cos(rad), 0.0f), i ));
		vertexIds.push_back(i);
		normalIds.push_back(0);
	}

	normals.push_back(Vector3d(0.0, 0.0, 1.0));
	Face f(vertexIds, normalIds);
	faces.push_back(f);

	positions.push_back( new Vertex( Vector3d(0.0, 0.0, 1.0f), divideNumber ));

	for (unsigned int i = 0; i < divideNumber-1; ++i) {
		const unsigned int v0 = i;
		const unsigned int v1 = i + 1;
		const unsigned int v2 = divideNumber;
		Face f;
		f.setVertexIds({ v0, v1, v2 });
		faces.push_back(f);
	}

	{
		const unsigned int v0 = divideNumber-1;
		const unsigned int v1 = 0;
		const unsigned int v2 = divideNumber;
		Face f;
		f.setVertexIds({ v0, v1, v2 });
		faces.push_back(f);
	}
}