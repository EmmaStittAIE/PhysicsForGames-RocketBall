#include "GameNode.h"
#include "TransformNode.h"

GameNode* GameNode::GetParent()
{
	return m_parent;
}

const std::vector<GameNode*>* GameNode::GetChildren()
{
	return &m_children;
}

void GameNode::AddChild(GameNode* child)
{
	// Only used for TransformNodes, but I'm not sure how else to do this
	Vec2 childGlobalPos(0, 0);

	TransformNode* childTransform = dynamic_cast<TransformNode*>(child);
	if (childTransform != nullptr)
	{
		childGlobalPos = childTransform->GetGlobalPos();
	}

	if (child->m_parent != nullptr)
	{
		child->m_parent->RemoveChild(child);
	}

	m_children.push_back(child);

	child->m_parent = this;

	if (childTransform != nullptr)
	{
		childTransform->SetGlobalPos(childGlobalPos);
	}
}

void GameNode::RemoveChild(GameNode* child)
{
	// Only used for TransformNodes, but I'm not sure how else to do this
	Vec2 childGlobalPos(0, 0);

	TransformNode* childTransform = dynamic_cast<TransformNode*>(child);
	if (childTransform != nullptr)
	{
		childGlobalPos = childTransform->GetGlobalPos();
	}

	child->m_parent = nullptr;

	for (int i = 0; i < m_children.size(); i++)
	{
		if (m_children[i] == child)
		{
			m_children.erase(m_children.begin() + i);
			return;
		}
	}

	if (childTransform != nullptr)
	{
		childTransform->SetGlobalPos(childGlobalPos);
	}
}

void GameNode::SetDebugColour(Vec3 debugColour)
{
	m_debugColour = debugColour / 255.0f;
}

GameNode::~GameNode()
{
	for (int i = 0; i < m_children.size(); i++)
	{
		delete(m_children[i]);
	}
}
