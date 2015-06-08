#ifndef __CRYSTAL_CGS_SPACE_FACTORY__
#define __CRYSTAL_CGS_SPACE_FACTORY__

#include "../Math/ScalarSpace.h"
#include "../Math/BitSpace.h"
#include <memory>
#include <map>
#include <list>


namespace Crystal {
	namespace CGS {

template<typename T>
using ScalarSpace3dSPtr = std::shared_ptr < Math::ScalarSpace3d<T> >;

template<typename T>
using ScalarSpace3dSPtrList = std::list < ScalarSpace3dSPtr<T> >;

template<typename T>
using BitSpace3dSPtr = std::shared_ptr < Math::BitSpace3d<T> >;

template<typename T>
using BitSpace3dSPtrList = std::list < BitSpace3dSPtr<T> >;

template<typename T>
using BitSpaceIdMap = std::map< BitSpace3dSPtr<T>, unsigned int >;

template<typename T>
using ScalarSpaceIdMap = std::map < ScalarSpace3dSPtr<T>, unsigned int > ;

class SpaceFactory
{
public:
	SpaceFactory() :
		nextId(0)
	{}

	void clear() {
		bitSpaces.clear();
		scalarSpaces.clear();
		nextId = 0;
	}

	void addBitSpace(const BitSpace3dSPtr<float>& bs) {
		bitSpaces.push_back(bs);
		bitIdMap[bs] = nextId++;
	}

	BitSpace3dSPtrList<float> getBitSpaces() const { return bitSpaces; }

	void addScalarSpace(const ScalarSpace3dSPtr<float>& ss) {
		scalarSpaces.push_back(ss);
		scalarIdMap[ss] = nextId++;
	}

	ScalarSpace3dSPtrList<float> getScalarSpaces() const { return scalarSpaces; }

	BitSpace3dSPtr<float> createBox(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		Math::Space3d<float> space(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));

		Math::Bitmap3d bmp(resx, resy, resz);
		BitSpace3dSPtr<float> bs(new Math::BitSpace3d<float>(space, bmp));
		bs->setBox();
		addBitSpace(bs);
		return bs;
	}


	unsigned int getId(const BitSpace3dSPtr<float>& bs) { return bitIdMap[bs]; }

	unsigned int getId(const ScalarSpace3dSPtr<float>& ss) { return scalarIdMap[ss]; }

private:
	BitSpace3dSPtrList<float> bitSpaces;
	ScalarSpace3dSPtrList<float> scalarSpaces;
	BitSpaceIdMap<float> bitIdMap;
	ScalarSpaceIdMap<float> scalarIdMap;
	unsigned int nextId;
};

	}
}

#endif