#ifndef __CRYSTAL_COMMAND_RENDERING_COMMAND_H__
#define __CRYSTAL_COMMAND_RENDERING_COMMAND_H__

#include <memory>

#include "../Graphics/Polygon.h"
#include "../Math/ScalarSpace.h"

namespace Crystal{
	namespace Command {

template<typename T>
class WireFrameRenderingBuffer {
public:
	WireFrameRenderingBuffer()
	{

	}

	void clear() {
		positions.clear();
		colors.clear();
	}


	void build(const Graphics::PolygonSPtrList<T>& polygons) {
		// positions;
		const auto cs = Graphics::ColorRGBA<T>::Blue().toArray3();
		for (const auto& p : polygons) {
			for (const auto& e : p->getEdges()) {
				const auto& start = e->getStartPosition().toArray();
				positions.insert(positions.end(), start.begin(), start.end());
				colors.insert(colors.end(), cs.begin(), cs.end());
				const auto& end = e->getEndPosition().toArray();
				positions.insert(positions.end(), end.begin(), end.end());
				colors.insert(colors.end(), cs.begin(), cs.end());

			}
			//colors.insert(colors.end(), cs.begin(), cs.end());
		}
	}

	std::vector< T > getPositions() const { return positions; }

	std::vector< T > getColors() const { return colors; }

private:
	std::vector< T > positions;
	std::vector< T > colors;

};

template<typename T>
using WireFrameRenderingBufferSPtr = std::shared_ptr < WireFrameRenderingBuffer<T> > ;

template<typename T>
class PointRenderingBuffer
{
public:

	PointRenderingBuffer()
	{}

	void clear() {
		ids.clear();
		points.clear();
	}


	void build(const Math::ScalarSpace3d<T>& ss, const unsigned int id) {
		const auto center = ss.getCenter();
		const auto cs = ss.getCenter().toArray();
		points.insert(points.end(), cs.begin(), cs.end());
		ids.push_back(id);
	}


	std::vector<T> getPoints() const { return points; }

	std::vector<int> getIds() const { return ids; }

private:
	std::vector< T > points;
	std::vector< int > ids;
};

template<typename T>
using PointRenderingBufferSPtr = std::shared_ptr < PointRenderingBuffer<T> > ;

template<typename T>
class NormalRenderingBuffer
{
public:
	NormalRenderingBuffer() = default;

	void clear() {
		positions.clear();
		normals.clear();
	}

	void build(const Graphics::PolygonSPtrList<T>& polygons) {
		for (const auto& p : polygons) {
			for (const auto& v : p->getVertices()) {
				const auto& ps = v->toPositionArray();
				positions.insert(positions.end(), ps.begin(), ps.end());
				const auto& ns = v->toNormalArray();
				normals.insert(normals.end(), ns.begin(), ns.end());

			}
		}
	}


	std::vector< T > getPositions() const { return positions; }

	std::vector< T > getNormals() const { return normals; }

private:
	std::vector< T > positions;
	std::vector< T > normals;

};

template<typename T>
using NormalRenderingBufferSPtr = std::shared_ptr < NormalRenderingBuffer<T> > ;

template<typename T>
class RenderingBuffer final : private UnCopyable
{
public:
	RenderingBuffer() :
		wfRenderingCommand(std::make_shared<WireFrameRenderingBuffer<T> >()),
		pointRenderingCommand(std::make_shared<PointRenderingBuffer<T> >()),
		normalRenderingCommand(std::make_shared<NormalRenderingBuffer<T> >())
	{}

	~RenderingBuffer() = default;

	WireFrameRenderingBufferSPtr<T> getWireframeCommand() const { return wfRenderingCommand; }

	PointRenderingBufferSPtr<T> getPointRenderingCommand() const { return pointRenderingCommand; }
	
	NormalRenderingBufferSPtr<T> getNormalRenderingCommand() const { return  normalRenderingCommand; }

	void clear() {
		wfRenderingCommand->clear();
		pointRenderingCommand->clear();
		normalRenderingCommand->clear();
	}

private:
	WireFrameRenderingBufferSPtr<T> wfRenderingCommand;
	PointRenderingBufferSPtr<T> pointRenderingCommand;
	NormalRenderingBufferSPtr<T> normalRenderingCommand;
};

template<typename T>
using RenderingBufferSPtr = std::shared_ptr < RenderingBuffer<T> >;

	}
}

#endif