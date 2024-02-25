#include <sstream>

#include "TransformNode.h"

void TransformNode::DebugDraw(LineRenderer* lines, Vec2 cameraPos, Vec2 cameraHalfExtents)
{
	Vec2 globalPos = GetGlobalPos();

	Vec2 clampedPoint = glm::clamp(globalPos, cameraPos - cameraHalfExtents, cameraPos + cameraHalfExtents);

	// If we are within the bounds of the camera
	// Might need some touching up later, as the text disappears instantly despite still being shown
	if (clampedPoint == globalPos)
	{
		lines->SetColour(m_debugColour);

		lines->DrawCross(globalPos, 0.1);

		std::stringstream posString;

		posString << "Pos: (" << globalPos.x << ", " << globalPos.y << ")";
		lines->RenderString(posString.str(), globalPos, 0.4);
	}
}

Vec2 TransformNode::GetGlobalPos()
{
	// Loop through all parents, accumulating their local positions, until we reach the top, then break out
	// Because a parent might not be a TransformNode, we don't want to stop checking when we hit it
	// and ignore any potential TransformNodes above it
	Vec2 globalPos = m_localPosition;

	GameNode* currentParent = m_parent;
	while (1)
	{
		if (currentParent == nullptr) { break; }

		TransformNode* parentTransform = dynamic_cast<TransformNode*>(currentParent);
		if (parentTransform != nullptr)
		{
			globalPos += parentTransform->GetLocalPos();
		}

		currentParent = currentParent->GetParent();
	}

	return globalPos;
}

void TransformNode::SetGlobalPos(Vec2 pos)
{
	Vec2 parentGlobalPos(0, 0);

	GameNode* currentParent = m_parent;
	while (1)
	{
		if (currentParent == nullptr) { break; }

		TransformNode* parentTransform = dynamic_cast<TransformNode*>(currentParent);
		if (parentTransform != nullptr)
		{
			parentGlobalPos += parentTransform->GetLocalPos();
		}

		currentParent = currentParent->GetParent();
	}

	m_localPosition = pos - parentGlobalPos;
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