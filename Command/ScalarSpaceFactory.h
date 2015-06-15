#ifndef __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__
#define __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__

#include "../Math/ScalarSpace.h"
#include "MainConfig.h"

#include "Object.h"
#include "Factory.h"

#include <memory>

namespace Crystal{
	namespace Command {


template<typename T>
class ScalarSpaceId final : public Object
{
public:
	ScalarSpaceId(const unsigned int id, const Math::ScalarSpace3dSPtr<T>& ss) :
		Object( id ),
		ss( ss )
	{}

	~ScalarSpaceId(){}

	Math::ScalarSpace3dSPtr<T> getScalarSpace() const { return ss; }

private:
	Math::ScalarSpace3dSPtr<T> ss;
};

template<typename T>
using ScalarSpaceIdList = std::list < ScalarSpaceId<T> > ;


template<typename T>
class ScalarSpaceFactory final : public FactoryBase
{
public:
	ScalarSpaceFactory()
	{}
	
	~ScalarSpaceFactory(){};

	void clear() {
		FactoryBase::clear();
		spaces.clear();
	}

	ScalarSpaceId<T> create(const GridConfig<T>& config)
	{
		Math::Grid3d<T> grid( config.getResx(), config.getResy(), config.getResz());
		Math::ScalarSpace3dSPtr<T> ss(new Math::ScalarSpace3d<T>( config.getSpace(), grid));
		//ss->add( Math::Metaball<float>( Math::Vector3d<float>(0.5, 0.5, 0.5), 0.5) );
		return add(ss);
	}

	ScalarSpaceIdList<T> getSpaces() const { return spaces; }

	Math::ScalarSpace3dSPtr<T> find(const unsigned int id) {
		for (const auto& s: spaces) {
			if (s.getId() == id) {
				return s.getScalarSpace();
			}
		}
		return nullptr;
	}


private:
	ScalarSpaceIdList<T> spaces;

	ScalarSpaceId<T> add(const Math::ScalarSpace3dSPtr<T>& ss) {
		spaces.push_back( ScalarSpaceId<float>( getNextId(), ss) );
		return spaces.back();
	}


};

template<typename T>
using ScalarSpaceFactorySPtr = std::shared_ptr < ScalarSpaceFactory<T> > ;

	}
}

#endif