#include "LineRenderer.h"
#include <iostream>

void LineRenderer::Initialise()
{
	glGenBuffers(1, &positionBufferID);
	glGenBuffers(1, &colourBufferID);
	initialised = true;
}

void LineRenderer::SetColour(Vec3 colour)
{
	currentColour = colour;
}

void LineRenderer::DrawLineSegment(Vec2 start, Vec2 end)
{
	DrawLineSegment(start, end, currentColour);
}

void LineRenderer::DrawLineSegment(Vec2 start, Vec2 end, Vec3 colour)
{
	positions.push_back(start);
	positions.push_back(end);
	colours.push_back(colour);
	colours.push_back(colour);
}

void LineRenderer::FinishLineStrip()
{
	if (lineActive)
	{
		lineActive = false;
	}
}

void LineRenderer::FinishLineLoop()
{
	if (lineActive)
	{
		positions.push_back(lastPos);
		positions.push_back(firstPos);
		colours.push_back(lastColour);
		colours.push_back(firstColour);
		lineActive = false;
	}
}

void LineRenderer::AddPointToLine(Vec2 point)
{
	AddPointToLine(point, currentColour);
}

void LineRenderer::AddPointToLine(Vec2 point, Vec3 colour)
{
	if (lineActive)
	{
		positions.push_back(lastPos);
		positions.push_back(point);
		colours.push_back(lastColour);
		colours.push_back(colour);
		lastPos = point;
		lastColour = colour;
	}
	else
	{
		lineActive = true;
		lastPos = point;
		firstPos = point;
		lastColour = colour;
		firstColour = colour;
	}
}

void LineRenderer::DrawCross(Vec2 centre, float size)
{
	DrawCross(centre, size, currentColour);
}

void LineRenderer::DrawCross(Vec2 centre, float size, Vec3 colour)
{
	positions.push_back({ centre.x - size, centre.y - size });
	positions.push_back({ centre.x + size, centre.y + size });
	positions.push_back({ centre.x + size, centre.y - size });
	positions.push_back({ centre.x - size, centre.y + size });
	colours.push_back(colour);
	colours.push_back(colour);
	colours.push_back(colour);
	colours.push_back(colour);
}

void LineRenderer::DrawCircle(Vec2 centre, float size, int segmentCount)
{
	DrawCircle(centre, size, currentColour, segmentCount);
}

void LineRenderer::DrawCircle(Vec2 centre, float size, Vec3 colour, int segmentCount)
{
	float cosAngle = cos(2 * 3.14159f / segmentCount);
	float sinAngle = sin(2 * 3.14159f / segmentCount);

	glm::mat2 rotMat = { {cosAngle, -sinAngle},{sinAngle, cosAngle} };

	Vec2 plotPoint(0, size);

	for (int i = 0; i <= segmentCount; i++)
	{
		positions.push_back(centre + plotPoint);
		plotPoint = rotMat * plotPoint;
		positions.push_back(centre + plotPoint);
		colours.push_back(colour);
		colours.push_back(colour);
	}
}

void LineRenderer::UpdateFrame()
{
	if (positions.size() != colours.size())
	{
		std::cout << "ERROR: Somehow, position and colour buffer are different sizes in the line renderer. This should never happen." << std::endl;
		return;
	}
	if (positions.size() > 0)
	{
		Compile();
		Draw();
	}
	Clear();	//It's possible to have done a single point, in which case there's nothing to draw but we do have to set 'lineActive' to false.
}

void LineRenderer::Clear()
{
	lineActive = false;
	positions.clear();
	colours.clear();
}

void LineRenderer::Compile()
{
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * positions.size(), positions.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * colours.size(), colours.data(), GL_DYNAMIC_DRAW);

}

void LineRenderer::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), 0);

	glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_LINES, 0, (GLsizei)positions.size());

}

LineRenderer::LineRenderer()
{
	//Do nothing here - initialise separately to avoid calling GL functions before it's set up.
}

LineRenderer::~LineRenderer()
{
	if (initialised)
	{
		glDeleteBuffers(1, &positionBufferID);
		glDeleteBuffers(1, &colourBufferID);
	}
}
