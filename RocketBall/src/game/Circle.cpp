#include "Circle.h"

void Circle::DebugDraw(LineRenderer* lines)
{
	lines->DrawCircle(GetGlobalPos(), m_radius);
}
