#include "ApplicationHarness.h"
#include "GLFWCallbacks.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

glm::mat4 ApplicationHarness::GetCameraTransform() const
{
	return glm::ortho(
		-aspectRatio * cameraHeight / 2.0f + cameraCentre.x, 
		aspectRatio * cameraHeight / 2.0f + cameraCentre.x,
		-cameraHeight / 2.0f + cameraCentre.y,
		cameraHeight / 2.0f + cameraCentre.y,
		-1.0f, 1.0f);
}

ApplicationHarness::ApplicationHarness(Application* appInit) : app(appInit)
{
	if (!glfwInit())
	{
		return;
	}
	if (app == nullptr)
	{
		return;
	}


	//Can choose resolution here.
	window = glfwCreateWindow(1280, 720, "Physics Testbed", nullptr, nullptr);

	//This is the somewhat hacky oldschool way of making callbacks work without everything having to be global. Look
	//at the way the function callbacks work to get an idea of what's going on.
	glfwSetWindowUserPointer(window, (void*)this);	

	//These functions will be able to reference the testbed object via the user pointer.
	glfwSetWindowSizeCallback(window, WindowResizeCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, MouseWheelCallback);

	if (!window)
	{
		//If the window failed to create for some reason, abandon ship.
		glfwTerminate();
		return;
	}

	//We have to tell glfw to use the OpenGL context from the window.
	glfwMakeContextCurrent(window);

	//This is where GLAD gets set up. After this point we can use openGL functions.
	if (!gladLoadGL())
	{
		return;
	}
	glfwSwapInterval(1);


	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	simpleShader = ShaderProgram("Simple.vsd", "Simple.fsd");
	simpleShader.UseShader();

	lines.Initialise();
	app->lines = &lines;

	glClearColor(0, 0, 0, 1);

	glLineWidth(3.0f);

	grid.Initialise();
	for (float i = (float)-gridLimits; i <= (float)gridLimits; i++)
	{
		Vec3 colour = (i == 0) ? Vec3(0.8f, 0.8f, 0.8f) : Vec3(0.3f, 0.3f, 0.3f);
		grid.DrawLineSegment({ i, -gridLimits }, { i, gridLimits }, colour);
		grid.DrawLineSegment({ -gridLimits, i }, { gridLimits, i }, colour);
	}
	grid.DrawLineSegment({ 0,0 }, { 1, 0 }, { 1, 0, 0 });
	grid.DrawLineSegment({ 0,0 }, { 0, 1 }, { 0, 1, 0 });
	grid.Compile();
}

ApplicationHarness::~ApplicationHarness()
{
	delete app;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void ApplicationHarness::Run()
{
	double fixedDelta = 1.0 / fixedFramerate;
	double currentTime = glfwGetTime();
	double accumulator = 0.0;

	while (IsRunning())
	{

		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= fixedDelta)
		{
			Update((float)fixedDelta);
			accumulator -= fixedDelta;
		}

		if (IsRunning())
		{
			Render();
		}
	}
}

void ApplicationHarness::Update(float delta)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	aspectRatio = width / (float)height;

	glm::mat4 deprojection = glm::inverse(GetCameraTransform());
	double cursorX, cursorY;
	glfwGetCursorPos(window, &cursorX, &cursorY);
	cursorX = (cursorX / width) * 2.0 - 1.0;
	cursorY = -((cursorY / height) * 2.0 - 1.0);

	glm::vec4 mousePosNDC(float(cursorX), float(cursorY), 0, 1);

	glm::vec4 mousePosWorld = deprojection * mousePosNDC;

	app->cursorPos.x = mousePosWorld.x;
	app->cursorPos.y = mousePosWorld.y;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		cameraCentre.x -= cameraSpeed * delta * cameraHeight;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		cameraCentre.x += cameraSpeed * delta * cameraHeight;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		cameraCentre.y += cameraSpeed * delta * cameraHeight;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		cameraCentre.y -= cameraSpeed * delta * cameraHeight;
	}

	app->leftMouseDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	app->rightMouseDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

	lines.Clear();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	app->Update(delta);

	lines.Compile();

	ImGui::Render();
}

void ApplicationHarness::Render()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glm::mat4 orthoMat = GetCameraTransform();
	simpleShader.SetUniform("vpMatrix", orthoMat);
	grid.Draw();
	lines.Draw();

	if (ImGui::GetDrawData())	//Render tends to get called once or twice before Update gets called, so we need to make sure this info exists.
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool ApplicationHarness::IsRunning() const
{
	return !glfwWindowShouldClose(window);
}

void ApplicationHarness::OnMouseClick(int mouseButton)
{
	if (mouseButton == 0)
	{
		app->OnLeftClick();
	}
	else if (mouseButton == 1)
	{
		app->OnRightClick();
	}
}

void ApplicationHarness::OnMouseRelease(int mouseButton)
{
	if (mouseButton == 0)
	{
		app->OnLeftRelease();
	}
	else if (mouseButton == 1)
	{
		app->OnRightRelease();
	}
}


void ApplicationHarness::Zoom(float zoomFactor)
{
	cameraHeight /= zoomFactor;
}
