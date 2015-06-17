#ifndef __CRYSTAL_COMMAND_VOLUME_MODEL_H__
#define __CRYSTAL_COMMAND_VOLUME_MODEL_H__

#include "../Math/Volume.h"
#include "MainConfig.h"

#include "Object.h"

#include <memory>

namespace Crystal{
	namespace Model {


template<typename T>
class VolumeObject final : public Object
{
public:
	VolumeObject(const unsigned int id, const Math::Volume3dSPtr<T>& ss) :
		Object( id ),
		ss( ss )
	{}

	~VolumeObject(){}

	Type getType() const { return Type::VOLUME; }


	Math::Volume3dSPtr<T> getSpace() const { return ss; }

private:
	Math::Volume3dSPtr<T> ss;
};

template<typename T>
using VolumeObjectSPtr = std::shared_ptr < VolumeObject<T> > ;

template<typename T>
using VolumeObjectSPtrList = std::list < VolumeObjectSPtr<T> > ;


template<typename T>
class VolumeModel final : public ModelBase
{
public:
	VolumeModel()
	{}

	~VolumeModel(){};

	void clear() {
		ModelBase::clear();
		spaces.clear();
	}

	VolumeObjectSPtr<T> create(const GridConfig<T>& config)
	{
		Math::Grid3d<T> grid(config.getResx(), config.getResy(), config.getResz());
		Math::Volume3dSPtr<T> ss(new Math::Volume3d<T>(config.getSpace(), grid));
		//ss->add( Math::Metaball<float>( Math::Vector3d<float>(0.5, 0.5, 0.5), 0.5) );
		return add(ss);
	}

	VolumeObjectSPtrList<T> getSpaces() const { return spaces; }

	VolumeObjectSPtr<T> find(const unsigned int id) {
		for (const auto& s: spaces) {
			if (s->getId() == id) {
				return s;
			}
		}
		return nullptr;
	}

	void remove(const unsigned int id) override {
		const auto& s = find(id);
		if (s == nullptr) {
			return;
		}
		spaces.remove(s);
	}


private:
	VolumeObjectSPtrList<T> spaces;

	VolumeObjectSPtr<T> add(const Math::Volume3dSPtr<T>& ss) {
		spaces.push_back( std::make_shared< VolumeObject<float> >( getNextId(), ss) );
		return spaces.back();
	}


};

template<typename T>
using VolumeModelSPtr = std::shared_ptr < VolumeModel<T> > ;

	}
}

#endif