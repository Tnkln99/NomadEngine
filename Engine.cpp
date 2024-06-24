#include "Engine.h"

#include <utility>
#include "Locator.h"
#include "Timer.h"
#include "ResourceManager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"

Engine::Engine(std::shared_ptr<Scene> scene)
{
	mWindow = std::make_shared<Window>("Nomad", 900, 900);
	Locator::getRendererService().registerWindow(mWindow);
	Locator::getRendererService().loadDefaultShaders();

	mCurrentScene = std::move(scene);
	mCurrentScene->init();
}

void Engine::changeScene(std::shared_ptr<Scene> scene)
{
	mCurrentScene = std::move(scene);
	mCurrentScene->init();
}

void Engine::run()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	mWindow->setUpImgui();
	ImGui_ImplOpenGL3_Init("#version 430 core");

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	Locator::getRendererService().changeRenderMode(WIREFRAME);
	mCurrentScene->beginPlay();
	Timer::start();
	while (!mWindow->shouldCloseWindow())
	{
		mWindow->clear();
		Timer::update();

		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Infos");
		ImGui::Text("Application average (%.1f FPS)", Timer::getFps());
		ImGui::End();

		mCurrentScene->update(Timer::getDeltaTime());

		Locator::getRendererService().render();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGui::UpdatePlatformWindows();

		mWindow->swapBuffers();
		mWindow->pollEvents();
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	mWindow->terminate();
}
