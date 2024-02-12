#include "GameNode.h"

#include <sstream>

void GameNode::DebugDraw(LineRenderer* lines)
{
#if _DEBUG
	lines->DrawCross(m_position, 0.1);

	// hadn't heard of this before, seems useful
	std::stringstream posString;

	posString << "Pos: (" << m_position.x << ", " << m_position.y << ")";
	lines->RenderString(posString.str(), m_position, 0.4);
#endif
}

GameNode::~GameNode()
{
	delete(m_parent);
}
