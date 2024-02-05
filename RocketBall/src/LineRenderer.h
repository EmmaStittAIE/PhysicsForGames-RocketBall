#pragma once

#include "Maths.h"
#include <vector>
#include "Graphics.h"


class LineRenderer
{
	std::vector<Vec2> positions;
	std::vector<Vec3> colours;
	bool initialised = false;

	Vec3 currentColour = { 1.0f,1.0f,1.0f };

	Vec2 firstPos;
	Vec2 lastPos;
	Vec3 firstColour;
	Vec3 lastColour;
	bool lineActive = false;

	GLuint positionBufferID;
	GLuint colourBufferID;


public:
	LineRenderer();
	~LineRenderer();
	LineRenderer(const LineRenderer&) = delete;
	LineRenderer(const LineRenderer&&) = delete;
	const LineRenderer& operator=(const LineRenderer&) = delete;
	const LineRenderer& operator=(LineRenderer&&) = delete;

	void Initialise();

	void SetColour(Vec3 colour);

	void DrawLineSegment(Vec2 start, Vec2 end);
	void DrawLineSegment(Vec2 start, Vec2 end, Vec3 colour);

	void FinishLineStrip();
	void FinishLineLoop();

	void AddPointToLine(Vec2 point);
	void AddPointToLine(Vec2 point, Vec3 colour);

	void DrawCross(Vec2 centre, float size);
	void DrawCross(Vec2 centre, float size, Vec3 colour);

	void DrawCircle(Vec2 centre, float size, int segmentCount = 64);
	void DrawCircle(Vec2 centre, float size, Vec3 colour, int segmentCount = 64);

	void UpdateFrame();

	void Clear();
	void Compile();
	void Draw();
};