#include "Circle.h"

void Circle::DebugDraw(LineRenderer* lines)
{
	GameNode::DebugDraw(lines);

	lines->SetColour(m_colour);
	lines->DrawCircle(GetGlobalPos(), m_radius);
}
