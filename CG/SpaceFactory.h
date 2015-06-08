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
using BitSpace3dSPtr = std::shared_ptr < Math::BitSpace3d<T> >;

template<typename T>
using BitSpace3dSPtrList = std::list < BitSpace3dSPtr<T> >;

template<typename T>
using BitSpaceIdMap = std::map< BitSpace3dSPtr<T>, unsigned int >;

template<typename T>
using IdBitSpacemap = std::map < unsigned int, BitSpace3dSPtr<T> > ;

template<typename T>
using ScalarSpaceIdMap = std::map < Math::ScalarSpace3dSPtr<T>, unsigned int > ;

template<typename T>
using IdScalarSpaceMap = std::map < unsigned int, Math::ScalarSpace3dSPtr<T> > ;

class BitSpaceFactory
{
public:
	BitSpaceFactory() :
		nextId(0)
	{}

	void clear() {
		bitSpaces.clear();
		nextId = 0;
	}


	BitSpace3dSPtrList<float> getBitSpaces() const { return bitSpaces; }


	BitSpace3dSPtr<float> createBox(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		Math::Space3d<float> space(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));

		Math::Bitmap3d bmp(resx, resy, resz);
		BitSpace3dSPtr<float> bs(new Math::BitSpace3d<float>(space, bmp));
		bs->setBox();
		addBitSpace(bs);
		return bs;
	}

	BitSpace3dSPtr<float> createSphere(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		Math::Space3d<float> space(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));

		Math::Bitmap3d bmp(20, 20, 20);
		BitSpace3dSPtr<float> bs(new Math::BitSpace3d<float>(space, bmp));
		bs->setSphere();
		addBitSpace(bs);
		return bs;
	}

	BitSpace3dSPtr<float> createCylinder(const unsigned int resx, const unsigned int resy, const unsigned int resz) {
		Math::Space3d<float> space(Math::Vector3d<float>(0, 0, 0), Math::Vector3d<float>(1, 1, 1));
		Math::Bitmap3d bmp(20, 20, 20);
		BitSpace3dSPtr<float> bs(new Math::BitSpace3d<float>(space, bmp));
		bs->setBox();
		bs->not();
		addBitSpace(bs);

		return bs;
	}


	unsigned int getId(const BitSpace3dSPtr<float>& bs) { return bitIdMap[bs]; }



private:
	BitSpace3dSPtrList<float> bitSpaces;
	BitSpaceIdMap<float> bitIdMap;
	IdBitSpacemap<float> idBitMap;
	unsigned int nextId;

	void addBitSpace(const BitSpace3dSPtr<float>& bs) {
		bitSpaces.push_back(bs);
		bitIdMap[bs] = nextId;
		idBitMap[nextId] = bs;
		nextId++;
	}


};

class ScalarSpaceFactory
{
public:
	ScalarSpaceFactory() :
		nextId(0)
	{}

	void clear() {
		scalarSpaces.clear();
		nextId = 0;
	}

	void addScalarSpace(const Math::ScalarSpace3dSPtr<float>& ss) {
		scalarSpaces.push_back(ss);
		scalarIdMap[ss] = nextId;
		idScalarMap[nextId] = ss;
		nextId++;
	}

	unsigned int getId(const Math::ScalarSpace3dSPtr<float>& ss) { return scalarIdMap[ss]; }

	Math::ScalarSpace3dSPtr<float> getScalarSpace(const unsigned int id) { return idScalarMap[id]; }

	Math::ScalarSpace3dSPtrList<float> getScalarSpaces() const { return scalarSpaces; }


private:
	Math::ScalarSpace3dSPtrList<float> scalarSpaces;
	ScalarSpaceIdMap<float> scalarIdMap;
	IdScalarSpaceMap<float> idScalarMap;
	unsigned int nextId;

};

	}
}

#endif