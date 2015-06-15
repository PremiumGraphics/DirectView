#ifndef __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__
#define __CRYSTAL_COMMAND_SCALAR_SPACE_FACTORY_H__

#include "../Math/ScalarSpace.h"
#include "MainConfig.h"

#include <map>
#include <memory>

namespace Crystal{
	namespace Command {

template<typename T>
class ObjectIdBase {
public:
	ObjectIdBase (const unsigned int id) :
		id( id )
	{}

	virtual ~ObjectIdBase(){}

	unsigned int getId() const { return id; }

private:
	unsigned int id;
};

template<typename T>
class ScalarSpaceId final : public ObjectIdBase<T>
{
public:
	ScalarSpaceId(const unsigned int id, const Math::ScalarSpace3dSPtr<T>& ss) :
		ObjectIdBase( id ),
		ss( ss )
	{}

	~ScalarSpaceId(){}

	Math::ScalarSpace3dSPtr<T> getScalarSpace() const { return ss; }

private:
	Math::ScalarSpace3dSPtr<T> ss;
};

template<typename T>
using ScalarSpaceIdList = std::list < ScalarSpaceId<T> > ;

class FactoryBase {
public:
	FactoryBase() :
		nextId(0)
	{}

	virtual ~FactoryBase(){};

	void clear() {
		nextId = 0;
	}

	unsigned int getNextId() { return nextId++; }

private:
	unsigned int nextId;
};

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