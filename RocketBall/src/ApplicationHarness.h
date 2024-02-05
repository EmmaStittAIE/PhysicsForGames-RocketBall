#pragma once
#include "Graphics.h"
#include "Maths.h"
#include "LineRenderer.h"
#include "ShaderProgram.h"
#include "Application.h"




class ApplicationHarness
{
	Application* app = nullptr;
	float cameraHeight = 10.0f;
	Vec2 cameraCentre = { 0.0f, 0.0f };
	GLFWwindow* window = nullptr;

	ShaderProgram simpleShader;
	float aspectRatio = 16.0f / 9.0f;

	LineRenderer grid;

	const float cameraSpeed = 0.8f;

	const int gridLimits = 10;

	glm::mat4 GetCameraTransform() const;


protected:
	LineRenderer lines;
	const int fixedFramerate = 60;

public:
	ApplicationHarness(Application* appInit);
	~ApplicationHarness();

	ApplicationHarness(const ApplicationHarness& other) = delete;
	ApplicationHarness& operator=(const ApplicationHarness& other) = delete;


	void Run();

	void Update(float delta);
	void Render();

	bool IsRunning() const;

	//1 for left, 2 for right, 3 for middle. Other button codes will get sent for other buttons but I'm not sure how they'd map to a particular mouse.
	virtual void OnMouseClick(int mouseButton);
	virtual void OnMouseRelease(int mouseButton);

	void Zoom(float zoomFactor);
};
