#ifndef __CRYSTAL_COMMAND_RENDERING_BUFFER_H__
#define __CRYSTAL_COMMAND_RENDERING_BUFFER_H__

#include <memory>

#include "../Graphics/Surface.h"

#include "VolumeModel.h"
#include "SurfaceModel.h"
#include "MetaballModel.h"

namespace Crystal{
	namespace Command {

template<typename T>
class PointRenderingBuffer
{
public:

	PointRenderingBuffer()
	{}

	void clear() {
		ids.clear();
		types.clear();
		points.clear();
	}


	void build(const Math::Volume3d<T>& ss, const unsigned int id) {
		const auto center = ss.getCenter();
		const auto cs = ss.getCenter().toArray();
		points.insert(points.end(), cs.begin(), cs.end());
		types.push_back(0);
		ids.push_back(id);
	}

	void build(const MetaballObject<T>& ball) {
		const auto center = ball.getMetaball()->getCenter();
		const auto cs = center.toArray();
		points.insert(points.end(), cs.begin(), cs.end());
		types.push_back(1);
		ids.push_back(ball.getId());
	}

	std::vector<T> getPoints() const { return points; }

	std::vector<int> getTypes() const { return types; }

	std::vector<int> getIds() const { return ids; }

private:
	std::vector< T > points;
	std::vector< int > types;
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

	void build(const SurfaceObjectSPtrList<T>& polygons) {
		for (const auto& pp : polygons) {
			const auto& p = pp->getPolygon();
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
		pointRenderingCommand(std::make_shared<PointRenderingBuffer<T> >()),
		normalRenderingCommand(std::make_shared<NormalRenderingBuffer<T> >())
	{}

	~RenderingBuffer() = default;

	void add(const SurfaceObjectSPtrList<T>& polygons) {
		clear();
		wfRenderingCommand->build(polygons);
		normalRenderingCommand->build(polygons);
	}

	void add(const VolumeObjectSPtrList<T>& sss) {
		for (const auto& ss : sss) {
			pointRenderingCommand->build(*ss->getSpace(), ss->getId());
		}
	}

	void add(const MetaballObjectSPtrList<T>& balls) {
		for (const auto& b : balls) {
			pointRenderingCommand->build(*b);
		}
	}


	PointRenderingBufferSPtr<T> getPointRenderingCommand() const { return pointRenderingCommand; }
	
	NormalRenderingBufferSPtr<T> getNormalRenderingCommand() const { return  normalRenderingCommand; }

	void clear() {
		pointRenderingCommand->clear();
		normalRenderingCommand->clear();
	}

private:
	PointRenderingBufferSPtr<T> pointRenderingCommand;
	NormalRenderingBufferSPtr<T> normalRenderingCommand;
};

template<typename T>
using RenderingBufferSPtr = std::shared_ptr < RenderingBuffer<T> >;

	}
}

#endif