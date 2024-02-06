#include "GameNode.h"

#include <sstream>

void GameNode::DebugDraw(LineRenderer* lines)
{
#if _DEBUG
	lines->DrawCross(position, 0.1);

	// Hadn't heard of this before, seems useful
	std::stringstream posString;

	posString << "Pos: (" << position.x << ", " << position.y << ")";
	lines->RenderString(posString.str(), position, 0.4);
#endif
}
