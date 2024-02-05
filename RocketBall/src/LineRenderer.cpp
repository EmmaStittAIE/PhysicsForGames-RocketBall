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

std::vector<Vec2> LineRenderer::GetGlyph(char character)
{

	switch (character)
	{
	case 'a':
	case 'A':
		return { {0.2f, 0.2f}, {0.5f, 1.6f}, {0.5f, 1.6f}, {0.8f, 0.2f} , {0.3f, 0.8f}, {0.7f, 0.8f} };
	case 'b':
	case 'B':
		return { {0.2f, 0.2f}, {0.2f, 1.6f}, {0.2f, 1.6f}, {0.6f, 1.6f}, {0.8f, 1.3f}, {0.6f, 1.6f}, {0.8f, 1.3f}, {0.6f, 1.0f}, {0.6, 1.0f}, {0.2f, 1.0f}, {0.6f, 1.0f}, {0.9f, 0.6f}, {0.9f, 0.6f}, {0.7f, 0.2f}, {0.7f, 0.2f}, {0.2f, 0.2f} };
	case 'c':
	case 'C':
		return { {0.8f, 1.4f}, {0.6f, 1.6f}, {0.3f, 1.6f}, {0.1f, 1.3f}, {0.1f, 1.3f}, {0.1f, 0.5f}, {0.1f, 0.5f}, {0.3f, 0.2f}, {0.6f, 0.2f}, {0.8f, 0.4f}, {0.3f, 0.2f}, {0.6f, 0.2f}, {0.3f, 1.6f}, {0.6f, 1.6f} };
	case 'd':
	case 'D':
		return { {0.2f, 1.6f}, {0.5f, 1.6f}, {0.8f, 1.3f}, {0.5f, 1.6f}, {0.8f, 1.3f}, {0.8f, 0.5f}, {0.8f, 0.5f}, {0.5f, 0.2f}, {0.5f, 0.2f}, {0.2f, 0.2f}, {0.2f, 0.2f}, {0.2f, 1.6f} };
	case 'e':
	case 'E':
		return { {0.8f, 1.6f}, {0.2f, 1.6f}, {0.2f, 1.6f}, {0.2f, 0.2f}, {0.2f, 0.2f}, {0.8f, 0.2f}, {0.7f, 0.9f}, {0.2f, 0.9f} };
	case 'f':
	case 'F':
		return { {0.8f, 1.6f}, {0.2f, 1.6f}, {0.2f, 1.6f}, {0.2f, 0.2f}, {0.7f, 0.9f}, {0.2f, 0.9f} };
	case 'g':
	case 'G':
		return { {0.8f, 1.3f}, {0.6f, 1.5f}, {0.6f, 1.5f}, {0.3f, 1.5f}, {0.3f, 1.5f}, {0.1f, 1.1f}, {0.1f, 1.1f}, {0.1f, 0.6f}, {0.1f, 0.6f}, {0.2f, 0.3f}, {0.2f, 0.3f}, {0.5f, 0.2f}, {0.8f, 0.5f}, {0.5f, 0.2f}, {0.8f, 0.2f}, {0.8f, 0.5f}, {0.5f, 0.5f}, {0.8f, 0.5f} };
	case 'h':
	case 'H':
		return { {0.2f, 1.5f}, {0.2f, 0.2f}, {0.8f, 1.5f}, {0.8f, 0.2f}, {0.2f, 0.9f}, {0.8f, 0.9f} };
	case 'i':
	case 'I':
		return { {0.5f, 1.5f}, {0.5f, 0.2f}, {0.4f, 1.5f}, {0.6f, 1.5f}, {0.4f, 0.2f}, {0.6f, 0.2f} };
	case 'j':
	case 'J':
		return { {0.7f, 1.5f}, {0.8f, 0.5f}, {0.4f, 1.5f}, {0.8f, 1.5f}, {0.6f, 0.2f}, {0.3f, 0.2f}, {0.2f, 0.5f}, {0.3f, 0.2f}, {0.8f, 0.5f}, {0.6f, 0.2f} };
	case 'k':
	case 'K':
		return { {0.2f, 1.5f}, {0.2f, 0.2f}, {0.8f, 1.4f}, {0.2f, 0.8f}, {0.8f, 0.2f}, {0.3f, 0.9f} };
	case 'l':
	case 'L':
		return { {0.2f, 1.5f}, {0.2f, 0.2f}, {0.8f, 0.2f}, {0.2f, 0.2f} };
	case 'm':
	case 'M':
		return { {0.2f, 1.4f}, {0.2f, 0.2f}, {0.8f, 1.4f}, {0.8f, 0.2f}, {0.5f, 0.8f}, {0.8f, 1.4f}, {0.2f, 1.4f}, {0.5f, 0.8f} };
	case 'n':
	case 'N':
		return { {0.2f, 1.4f}, {0.2f, 0.2f}, {0.8f, 0.2f}, {0.8f, 1.4f}, {0.2f, 1.4f}, {0.8f, 0.2f} };
	case 'o':
	case 'O':
		return { {0.5f, 1.5f}, {0.2f, 1.2f}, {0.8f, 1.2f}, {0.5f, 1.5f}, {0.5f, 0.1f}, {0.8f, 0.4f}, {0.2f, 0.4f}, {0.5f, 0.1f}, {0.2f, 0.4f}, {0.2f, 1.2f}, {0.8f, 0.4f}, {0.8f, 1.2f} };
	case 'p':
	case 'P':
		return { {0.2f, 1.6f}, {0.6f, 1.6f}, {0.8f, 1.3f}, {0.6f, 1.6f}, {0.6f, 0.9f}, {0.8f, 1.3f}, {0.2f, 0.9f}, {0.6f, 0.9f}, {0.2f, 1.6f}, {0.2f, 0.2f} };
	case 'q':
	case 'Q':
		return { {0.5f, 1.6f}, {0.1f, 1.2f}, {0.1f, 0.5f}, {0.4f, 0.2f}, {0.9f, 0.5f}, {0.9f, 1.2f}, {0.5f, 1.6f}, {0.9f, 1.2f}, {0.1f, 1.2f}, {0.1f, 0.5f}, {0.4f, 0.2f}, {0.9f, 0.5f}, {0.5f, 0.5f}, {0.8f, 0.2f} };
	case 'r':
	case 'R':
		return { {0.2f, 1.6f}, {0.7f, 1.6f}, {0.9f, 1.2f}, {0.7f, 0.9f}, {0.2f, 0.9f}, {0.7f, 0.9f}, {0.7f, 1.6f}, {0.9f, 1.2f}, {0.4f, 0.9f}, {0.8f, 0.2f}, {0.2f, 0.2f}, {0.2f, 1.6f} };
	case 's':
	case 'S':
		return { {0.9f, 1.3f}, {0.7f, 1.6f}, {0.3f, 1.6f}, {0.1f, 1.3f}, {0.2f, 0.9f}, {0.8f, 0.7f}, {0.9f, 0.3f}, {0.5f, 0.1f}, {0.1f, 0.3f}, {0.5f, 0.1f}, {0.8f, 0.7f}, {0.9f, 0.3f}, {0.7f, 1.6f}, {0.3f, 1.6f}, {0.1f, 1.3f}, {0.2f, 0.9f} };
	case 't':
	case 'T':
		return { {0.1f, 1.5f}, {0.9f, 1.5f}, {0.5f, 1.5f}, {0.5f, 0.2f} };
	case 'u':
	case 'U':
		return { {0.8f, 1.5f}, {0.8f, 0.6f}, {0.4f, 0.2f}, {0.2f, 0.6f}, {0.2f, 1.5f}, {0.2f, 0.6f}, {0.8f, 0.6f}, {0.6f, 0.2f}, {0.4f, 0.2f}, {0.6f, 0.2f} };
	case 'v':
	case 'V':
		return { {0.9f, 1.5f}, {0.5f, 0.2f}, {0.5f, 0.2f}, {0.1f, 1.5f} };
	case 'w':
	case 'W':
		return { {0.9f, 1.5f}, {0.8f, 0.2f}, {0.2f, 0.2f}, {0.1f, 1.5f}, {0.5f, 0.8f}, {0.8f, 0.2f}, {0.5f, 0.8f}, {0.2f, 0.2f} };
	case 'x':
	case 'X':
		return { {0.8f, 0.2f}, {0.2f, 1.5f}, {0.2f, 0.2f}, {0.8f, 1.5f} };
	case 'y':
	case 'Y':
		return { {0.2f, 1.5f}, {0.5f, 0.9f}, {0.8f, 1.5f}, {0.5f, 0.9f}, {0.5f, 0.2f}, {0.5f, 0.9f} };
	case 'z':
	case 'Z':
		return { {0.2f, 1.5f}, {0.8f, 1.5f}, {0.8f, 0.2f}, {0.2f, 0.2f}, {0.8f, 1.5f}, {0.2f, 0.2f} };
	case '1':
		return { {0.3f, 1.3f}, {0.5f, 1.4f}, {0.5f, 1.4f}, {0.5f, 0.2f}, {0.3f, 0.2f}, {0.7f, 0.2f} };
	case '2':
		return { {0.2f, 1.3f}, {0.4f, 1.5f}, {0.6f, 0.8f}, {0.7f, 1.3f}, {0.2f, 0.3f}, {0.6f, 0.8f}, {0.8f, 0.3f}, {0.2f, 0.3f}, {0.4f, 1.5f}, {0.7f, 1.3f} };
	case '3':
		return { {0.2f, 1.3f}, {0.5f, 1.5f}, {0.4f, 0.9f}, {0.8f, 1.2f}, {0.5f, 1.5f}, {0.8f, 1.2f}, {0.7f, 0.7f}, {0.4f, 0.9f}, {0.8f, 0.4f}, {0.7f, 0.7f}, {0.2f, 0.3f}, {0.4f, 0.2f}, {0.8f, 0.4f}, {0.4f, 0.2f} };
	case '4':
		return { {0.6f, 1.5f}, {0.2f, 0.8f}, {0.8f, 0.8f}, {0.2f, 0.8f}, {0.6f, 0.9f}, {0.5f, 0.2f} };
	case '5':
		return { {0.8f, 1.4f}, {0.2f, 1.4f}, {0.2f, 0.9f}, {0.6f, 0.8f}, {0.8f, 0.5f}, {0.6f, 0.2f}, {0.6f, 0.8f}, {0.8f, 0.5f}, {0.2f, 1.4f}, {0.2f, 0.9f}, {0.1f, 0.3f}, {0.6f, 0.2f} };
	case '6':
		return { {0.7f, 1.5f}, {0.3f, 1.2f}, {0.2f, 0.8f}, {0.2f, 0.4f}, {0.5f, 0.2f}, {0.8f, 0.4f}, {0.9f, 0.7f}, {0.6f, 0.9f}, {0.8f, 0.4f}, {0.9f, 0.7f}, {0.2f, 0.4f}, {0.5f, 0.2f}, {0.3f, 1.2f}, {0.2f, 0.8f}, {0.2f, 0.8f}, {0.6f, 0.9f} };
	case '7':
		return { {0.2f, 1.4f}, {0.8f, 1.4f}, {0.5f, 0.8f}, {0.4f, 0.2f}, {0.5f, 0.8f}, {0.8f, 1.4f} };
	case '8':
		return { {0.5f, 1.5f}, {0.3f, 1.3f}, {0.3f, 1.f}, {0.8f, 0.6f}, {0.8f, 0.3f}, {0.5f, 0.1f}, {0.2f, 0.3f}, {0.5f, 0.1f}, {0.2f, 0.6f}, {0.2f, 0.3f}, {0.8f, 0.6f}, {0.8f, 0.3f}, {0.7f, 1.3f}, {0.7f, 1.f}, {0.2f, 0.6f}, {0.7f, 1.f}, {0.5f, 1.5f}, {0.7f, 1.3f}, {0.3f, 1.3f}, {0.3f, 1.f} };
	case '9':
		return { {0.2f, 1.3f}, {0.4f, 1.5f}, {0.7f, 1.5f}, {0.8f, 1.1f}, {0.7f, 0.6f}, {0.2f, 0.2f}, {0.2f, 1.f}, {0.5f, 0.9f}, {0.8f, 1.1f}, {0.5f, 0.9f}, {0.8f, 1.1f}, {0.7f, 0.6f}, {0.2f, 1.3f}, {0.2f, 1.f}, {0.4f, 1.5f}, {0.7f, 1.5f} };
	case '0':
		return { {0.5f, 1.5f}, {0.2f, 1.1f}, {0.2f, 0.5f}, {0.5f, 0.2f}, {0.8f, 0.5f}, {0.8f, 1.1f}, {0.5f, 1.5f}, {0.8f, 1.1f}, {0.2f, 1.1f}, {0.2f, 0.5f}, {0.8f, 0.5f}, {0.5f, 0.2f}, {0.2f, 0.2f}, {0.8f, 1.5f} };
	case '!':
		return { {0.5f, 1.5f}, {0.5f, 0.6f}, {0.4f, 0.3f}, {0.6f, 0.1f}, {0.6f, 0.3f}, {0.4f, 0.1f} };
	case '"':
		return { {0.4f, 1.4f}, {0.4f, 1.2f}, {0.6f, 1.4f}, {0.6f, 1.2f} };
	case '#':
		return { {0.3f, 1.3f}, {0.3f, 0.6f}, {0.7f, 1.3f}, {0.7f, 0.6f}, {0.1f, 1.1f}, {0.9f, 1.1f}, {0.1f, 0.8f}, {0.9f, 0.8f} };
	case '$':
		return { {0.5f, 1.5f}, {0.8f, 1.3f}, {0.2f, 1.2f}, {0.2f, 0.9f}, {0.8f, 0.7f}, {0.8f, 0.4f}, {0.5f, 0.2f}, {0.2f, 0.4f}, {0.5f, 0.2f}, {0.8f, 0.4f}, {0.2f, 0.9f}, {0.8f, 0.7f}, {0.5f, 1.5f}, {0.2f, 1.2f}, {0.4f, 1.5f}, {0.4f, 0.2f}, {0.6f, 1.5f}, {0.6f, 0.2f} };
	case '%':
		return { {0.8f, 1.4f}, {0.2f, 0.3f}, {0.3f, 1.1f}, {0.2f, 1.0f}, {0.3f, 0.9f}, {0.4f, 1.0f}, {0.2f, 1.0f}, {0.3f, 0.9f}, {0.3f, 1.1f}, {0.4f, 1.0f}, {0.6f, 0.7f}, {0.7f, 0.8f}, {0.7f, 0.6f}, {0.8f, 0.7f}, {0.6f, 0.7f}, {0.7f, 0.6f}, {0.7f, 0.8f}, {0.8f, 0.7f} };
	case '&':
		return { {0.5f, 1.5f}, {0.2f, 1.3f}, {0.2f, 1.f}, {0.6f, 0.7f}, {0.9f, 0.5f}, {0.4f, 0.2f}, {0.2f, 0.4f}, {0.4f, 0.2f}, {0.2f, 0.6f}, {0.2f, 0.4f}, {0.6f, 0.7f}, {0.8f, 0.2f}, {0.2f, 0.6f}, {0.7f, 1.f}, {0.5f, 1.5f}, {0.7f, 1.3f}, {0.2f, 1.3f}, {0.2f, 1.f} };
	case '\'':
		return { {0.5f, 1.4f}, {0.5f, 1.2f} };
	case '(':
		return { {0.5f, 1.5f}, {0.2f, 1.1f}, {0.2f, 0.6f}, {0.5f, 0.2f}, {0.2f, 1.1f}, {0.2f, 0.6f} };
	case ')':
		return { {0.5f, 1.5f}, {0.8f, 1.1f}, {0.8f, 0.6f}, {0.5f, 0.2f}, {0.8f, 1.1f}, {0.8f, 0.6f} };
	case '*':
		return { {0.4f, 1.4f}, {0.6f, 1.0f}, {0.6f, 1.4f}, {0.4f, 1.0f}, {0.3f, 1.2f}, {0.7f, 1.2f} };
	case '+':
		return { {0.5f, 1.1f}, {0.5f, 0.5f}, {0.2f, 0.8f}, {0.8f, 0.8f} };
	case ',':
		return { {0.6f, 0.4f}, {0.4f, 0.2f} };
	case '-':
		return { {0.2f, 0.9f}, {0.8f, 0.9f} };
	case '.':
		return { {0.4f, 0.3f}, {0.6f, 0.3f}, {0.5f, 0.4f}, {0.5f, 0.2f} };
	case '/':
		return { {0.8f, 1.4f}, {0.2f, 0.2f} };
	case ':':
		return { {0.6f, 1.3f}, {0.5f, 1.2f}, {0.4f, 1.3f}, {0.5f, 1.4f}, {0.5f, 1.4f}, {0.6f, 1.3f}, {0.4f, 1.3f}, {0.5f, 1.2f}, {0.5f, 0.5f}, {0.4f, 0.4f}, {0.5f, 0.3f}, {0.6f, 0.4f}, {0.5f, 0.5f}, {0.6f, 0.4f}, {0.4f, 0.4f}, {0.5f, 0.3f} };
	case ';':
		return { {0.6f, 1.3f}, {0.5f, 1.2f}, {0.4f, 1.3f}, {0.5f, 1.4f}, {0.5f, 1.4f}, {0.6f, 1.3f}, {0.4f, 1.3f}, {0.5f, 1.2f}, {0.6f, 0.5f}, {0.4f, 0.2f} };
	case '<':
		return { {0.8f, 1.2f}, {0.1f, 0.9f}, {0.8f, 0.6f}, {0.1f, 0.9f} };
	case '=':
		return { {0.8f, 1.2f}, {0.2f, 1.2f}, {0.8f, 0.6f}, {0.2f, 0.6f} };
	case '>':
		return { {0.9f, 0.9f}, {0.2f, 1.2f}, {0.9f, 0.9f}, {0.2f, 0.6f} };
	case '?':
		return { {0.1f, 1.2f}, {0.3f, 1.5f}, {0.7f, 1.5f}, {0.9f, 1.3f}, {0.3f, 1.5f}, {0.7f, 1.5f}, {0.8f, 1.0f}, {0.9f, 1.3f}, {0.5f, 0.8f}, {0.8f, 1.0f}, {0.5f, 0.5f}, {0.5f, 0.8f}, {0.5f, 0.3f}, {0.4f, 0.2f}, {0.6f, 0.2f}, {0.5f, 0.1f}, {0.6f, 0.2f}, {0.5f, 0.3f}, {0.4f, 0.2f}, {0.5f, 0.1f} };
	case '@':
		return { {0.8f, 1.0f}, {0.5f, 1.2f}, {0.3f, 1.0f}, {0.3f, 0.6f}, {0.5f, 0.5f}, {0.8f, 0.7f}, {0.7f, 1.5f}, {0.8f, 0.7f}, {0.5f, 1.2f}, {0.3f, 1.0f}, {0.5f, 0.5f}, {0.3f, 0.6f}, {0.4f, 1.5f}, {0.7f, 1.5f}, {0.1f, 1.1f}, {0.4f, 1.5f}, {0.1f, 0.5f}, {0.1f, 1.1f}, {0.4f, 0.2f}, {0.8f, 0.3f}, {0.1f, 0.5f}, {0.4f, 0.2f} };
	case '[':
		return { {0.5f, 1.5f}, {0.2f, 1.5f}, {0.2f, 0.2f}, {0.5f, 0.2f}, {0.2f, 0.2f}, {0.2f, 1.5f} };
	case ']':
		return { {0.5f, 1.5f}, {0.8f, 1.5f}, {0.8f, 0.2f}, {0.5f, 0.2f}, {0.8f, 0.2f}, {0.8f, 1.5f} };
	case '\\':
		return { {0.2f, 1.5f}, {0.8f, 0.2f} };
	case '^':
		return { {0.5f, 1.5f}, {0.3f, 1.2f}, {0.7f, 1.2f}, {0.5f, 1.5f} };
	case '_':
		return { {0.2f, 0.2f}, {0.8f, 0.2f} };
	case '`':
		return { {0.4f, 1.4f}, {0.6f, 1.2f} };
	case '{':
		return { {0.5f, 0.2f}, {0.3f, 0.3f}, {0.2f, 0.9f}, {0.3f, 0.7f}, {0.3f, 0.7f}, {0.3f, 0.3f}, {0.3f, 1.0f}, {0.3f, 1.3f}, {0.3f, 1.3f}, {0.5f, 1.4f}, {0.3f, 1.0f}, {0.2f, 0.8f} };
	case '}':
		return { {0.5f, 0.2f}, {0.7f, 0.3f}, {0.8f, 0.9f}, {0.7f, 0.7f}, {0.7f, 0.7f}, {0.7f, 0.3f}, {0.7f, 1.0f}, {0.7f, 1.3f}, {0.7f, 1.3f}, {0.5f, 1.4f}, {0.7f, 1.0f}, {0.8f, 0.8f} };
	case '|':
		return { {0.5f, 0.2f}, {0.5f, 1.4f} };
	case '~':
		return { {0.1f, 0.9f}, {0.3f, 1.1f}, {0.7f, 0.9f}, {0.9f, 1.1f}, {0.3f, 1.1f}, {0.7f, 0.9f} };
	}

}

float LineRenderer::RenderString(std::string text, Vec2 pos, float size)
{
	Vec2 currentPos = pos;
	for (int i = 0; i < text.size(); i++)
	{
		currentPos.x += RenderChar(text[i], currentPos, size);
	}
	return currentPos.x - pos.x;
}

float LineRenderer::RenderChar(char character, Vec2 pos, float size)
{
	std::vector<Vec2> points = GetGlyph(character);
	if (points.size() > 0)
	{
		for (int i = 0; i + 1 < points.size(); i += 2)
		{
			DrawLineSegment(points[i] * size + pos, points[i + 1] * size + pos);
		}
		return size;
	}
	else
	{
		if (character == ' ') return size;
		else return 0.0f;
	}
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
