#include "GameNode.h"

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
	if (child->m_parent != nullptr)
	{
		child->m_parent->RemoveChild(child);
	}

	m_children.push_back(child);

	child->m_parent = this;
}

void GameNode::RemoveChild(GameNode* child)
{
	child->m_parent = nullptr;

	for (int i = 0; i < m_children.size(); i++)
	{
		if (m_children[i] == child)
		{
			m_children.erase(m_children.begin() + i);
			return;
		}
	}
}

GameNode::~GameNode()
{
	for (int i = 0; i < m_children.size(); i++)
	{
		delete(m_children[i]);
	}
}
