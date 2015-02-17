#ifndef __CRYSTAL_IO_VTK_CONNECTION_H__
#define __CRYSTAL_IO_VTK_CONNECTION_H__

#include <vector>

namespace Crystal {
	namespace IO {

typedef std::vector< unsigned int > VertexIndices;

typedef std::vector< unsigned int > Connection;

typedef std::vector< Connection > ConnectionVector;


namespace {

Connection build(const std::vector< unsigned int >& is, const VertexIndices& indices)
{
	Connection c;
	for (const unsigned int i : is) {
		c.push_back( indices[i] );
	}
	return c;
}

}

	}
}

#endif