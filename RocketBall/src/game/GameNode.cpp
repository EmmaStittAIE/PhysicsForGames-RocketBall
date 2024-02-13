#include "GameNode.h"

#include <sstream>

void GameNode::DebugDraw(LineRenderer* lines)
{
	lines->SetColour({ 1, 1, 1 });

	lines->DrawCross(m_localPosition, 0.1);

	// hadn't heard of this before, seems useful
	std::stringstream posString;

	posString << "Pos: (" << m_localPosition.x << ", " << m_localPosition.y << ")";
	lines->RenderString(posString.str(), m_localPosition, 0.4);
}

Vec2 GameNode::GetGlobalPos()
{
	if (m_parent != nullptr)
	{
		return m_localPosition + m_parent->GetGlobalPos();
	}

	return m_localPosition;
}

void GameNode::SetGlobalPos(Vec2 pos)
{
	Vec2 parentPos = { 0,0 };

	if (m_parent != nullptr)
	{
		Vec2 parentPos =  m_parent->GetGlobalPos();
	}

	m_localPosition = pos - parentPos;
}

Vec2 GameNode::GetLocalPos()
{
	return m_localPosition;
}

void GameNode::SetLocalPos(Vec2 pos)
{
	m_localPosition = pos;
}

void GameNode::MovePos(Vec2 distance)
{
	m_localPosition += distance;
}

GameNode::~GameNode()
{
	for (int i = 0; i < m_children.size(); i++)
	{
		delete(m_children[i]);
	}
}
