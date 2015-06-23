#ifndef __CRYSTAL_COMMAND_VOLUME_MODEL_H__
#define __CRYSTAL_COMMAND_VOLUME_MODEL_H__

#include "../Math/Volume.h"

#include "Object.h"

#include <memory>

namespace Crystal{
	namespace Model {

template<typename T>
class VolumeConfig {
public:
	VolumeConfig() {
		setDefault();
	}

	VolumeConfig(const unsigned int resx, const unsigned int resy, const unsigned int resz, const Math::Space3d<T>& space) :
		resx(resx),
		resy(resy),
		resz(resz),
		space(space)
	{}

	unsigned int getResx() const { return resx; }

	unsigned int getResy() const { return resy; }

	unsigned int getResz() const { return resz; }

	Math::Space3d<T> getSpace() const { return space; }

	void setDefault() {
		resx = 20;
		resy = 20;
		resz = 20;
		space = Math::Space3d<T>(Math::Vector3d<T>(-1, -1, -1), Math::Vector3d<T>(2, 2, 2));
	}

private:
	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
	Math::Space3d<T> space;
};


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

	virtual void move(const Math::Vector3d<float>& vector) override
	{
		ss->move(vector);
	};

	virtual void rotate(const Math::Vector3d<float>& center, const Math::Vector3d<float>& angle) override
	{
		;
	};

	virtual void scale(const Math::Vector3d<float>& s) override
	{
		ss->scale(s);
	}

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

	VolumeObjectSPtr<T> create()
	{
		Math::Grid3d<T> grid(config.getResx(), config.getResy(), config.getResz());
		Math::Volume3dSPtr<T> ss(new Math::Volume3d<T>(config.getSpace(), grid));
		//ss->add( Math::Metaball<float>( Math::Vector3d<float>(0.5, 0.5, 0.5), 0.5) );
		return add(ss);
	}

	VolumeObjectSPtrList<T> getSpaces() const { return spaces; }

	VolumeConfig<T> getConfig() const { return config; }

	void setConfig(const VolumeConfig<T>& config) { this->config = config; }


private:
	VolumeObjectSPtrList<T> spaces;

	VolumeObjectSPtr<T> add(const Math::Volume3dSPtr<T>& ss) {
		spaces.push_back( std::make_shared< VolumeObject<float> >( getNextId(), ss) );
		return spaces.back();
	}

	VolumeConfig<T> config;

};

template<typename T>
using VolumeModelSPtr = std::shared_ptr < VolumeModel<T> > ;

	}
}

#endif