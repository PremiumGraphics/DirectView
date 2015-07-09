#ifndef __CRYSTAL_UI_HISTORY_H__
#define __CRYSTAL_UI_HISTORY_H__

#include "../Math/Volume.h"
#include "../Graphics/Brush.h"

#include <queue>

namespace Crystal {
	namespace UI {

template<typename T>
class HistoryCommand
{
public:
	HistoryCommand(const Math::Volume3dSPtr<float>& volume) :
		volume(volume)
	{}

	~HistoryCommand() = default;

	void add(const Graphics::Brush3d<float>& b) { brushes.push_back(b); }

	void undo();

	void redo();

private:
	std::deque < Graphics::Brush3d<float> > brushes;
	Math::Volume3dSPtr volume;
};

	}
}

#endif