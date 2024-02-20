#include <sstream>

#include "TransformNode.h"

void TransformNode::DebugDraw(LineRenderer* lines)
{
	Vec2 globalPos = GetGlobalPos();

	lines->SetColour(m_debugColour);

	lines->DrawCross(globalPos, 0.1);

	std::stringstream posString;

	posString << "Pos: (" << globalPos.x << ", " << globalPos.y << ")";
	lines->RenderString(posString.str(), globalPos, 0.4);
}

Vec2 TransformNode::GetGlobalPos()
{
	TransformNode* parentTransform = dynamic_cast<TransformNode*>(m_parent);
	if (parentTransform != nullptr)
	{
		return m_localPosition + parentTransform->GetGlobalPos();
	}

	return m_localPosition;
}

void TransformNode::SetGlobalPos(Vec2 pos)
{
	Vec2 parentPos = { 0,0 };

	TransformNode* parentTransform = dynamic_cast<TransformNode*>(m_parent);
	if (parentTransform != nullptr)
	{
		Vec2 parentPos = parentTransform->GetGlobalPos();
	}

	m_localPosition = pos - parentPos;
}

Vec2 TransformNode::GetLocalPos()
{
	return m_localPosition;
}

void TransformNode::SetLocalPos(Vec2 pos)
{
	m_localPosition = pos;
}

void TransformNode::MovePos(Vec2 distance)
{
	m_localPosition += distance;
}