#include "Box.h"

void Box::DebugDraw(LineRenderer* lines)
{
	GameNode::DebugDraw(lines);

	Vec2 localCorners[4];

	localCorners[0] = { -m_halfWidth, m_halfHeight };
	localCorners[1] = { m_halfWidth, m_halfHeight };
	localCorners[2] = { m_halfWidth, -m_halfHeight };
	localCorners[3] = { -m_halfWidth, -m_halfHeight };

	lines->SetColour(m_colour);

	Vec2 globalPos = GetGlobalPos();
	for (int i = 0; i < std::size(localCorners); i++)
	{
		// this is a little weird...
		lines->AddPointToLine(localCorners[i] + globalPos);
	}
	lines->FinishLineLoop();
}

float Box::GetWidth()
{
	return m_halfWidth * 2;
}

float Box::GetHalfWidth()
{
	return m_halfWidth;
}

float Box::GetHeight()
{
	return m_halfHeight * 2;
}

float Box::GetHalfHeight()
{
	return m_halfHeight;
}
