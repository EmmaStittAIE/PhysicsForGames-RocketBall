#include "GameNode.h"

#include <sstream>

void GameNode::DebugDraw(LineRenderer* lines)
{
#if _DEBUG
	lines->DrawCross(m_localPosition, 0.1);

	// hadn't heard of this before, seems useful
	std::stringstream posString;

	posString << "Pos: (" << m_localPosition.x << ", " << m_localPosition.y << ")";
	lines->RenderString(posString.str(), m_localPosition, 0.4);
#endif
}

Vec2 GameNode::GetGlobalPos()
{
	if (m_parent != nullptr)
	{
		return m_localPosition + m_parent->GetGlobalPos();
	}

	return m_localPosition;
}

GameNode::~GameNode()
{
	for (int i = 0; i < m_children.size(); i++)
	{
		delete(m_children[i]);
	}
}
