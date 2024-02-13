#pragma once

#include <vector>

#include "Application.h"

class GameNode;
class Shape;

class RocketBall : public Application
{
private:
	std::vector<GameNode*> m_gameNodes;
	std::vector<Shape*> m_shapes;

	Shape* m_shapeOnMouse = nullptr;
	Shape* m_shapeToFling = nullptr;

	float m_flingMultiplier = 5;

public:
	RocketBall();

	void Update(float delta) override;

	void OnLeftClick() override;
	void OnLeftRelease() override;
	void OnRightClick() override;
	void OnRightRelease() override;

	~RocketBall();
};