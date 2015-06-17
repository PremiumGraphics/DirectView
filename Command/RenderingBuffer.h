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
		normalRenderingCommand(std::make_shared<NormalRenderingBuffer<T> >())
	{}

	~RenderingBuffer() = default;

	void add(const SurfaceObjectSPtrList<T>& polygons) {
		clear();
		normalRenderingCommand->build(polygons);
	}
	
	NormalRenderingBufferSPtr<T> getNormalRenderingCommand() const { return  normalRenderingCommand; }

	void clear() {
		normalRenderingCommand->clear();
	}

private:
	NormalRenderingBufferSPtr<T> normalRenderingCommand;
};

template<typename T>
using RenderingBufferSPtr = std::shared_ptr < RenderingBuffer<T> >;

	}
}

#endif