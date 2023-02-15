#include "iostream"
#include "TestPoliGL.cpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

Poli::PoliGL* currentGL;

void WindowResizeCallback(GLFWwindow* window, int w, int h)
{
	currentGL->OnResize(w, h);
}

void main()
{
	/*currentGL = new TestPoliGL();
	currentGL->Init("Test window", 1920, 1080, 0, 4);
	currentGL->SetResizeCallback(WindowResizeCallback);

	while (currentGL->IsRunning())
	{
		currentGL->Render(glfwGetTime());

		glfwPollEvents();
	}

	currentGL->Shutdown();
	delete (currentGL);*/

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "window", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	gl3wInit();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	static bool show_scene = false;
	static bool show_scene_notation = false;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Scene notation", &show_scene_notation);
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_scene_notation = false;
		ImGui::End();

		GLuint textureID;
		glGenTextures(1, &textureID);

		ImGui::Begin("Scene", &show_scene);
		if (ImGui::BeginChild("GameRender"))
		{
			ImGui::Image(reinterpret_cast<ImTextureID>(textureID), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::EndChild();
		}
		ImGui::End();

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}