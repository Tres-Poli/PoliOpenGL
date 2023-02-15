#include "PoliGL.h"

using namespace Poli;

void PoliGL::Init(const char* title, int width, int height, int minor_version, int major_version)
{
	strcpy_s(props.title, title);
	props.width = width;
	props.height = height;
	props.minor_version = minor_version;
	props.major_version = major_version;

	glfwInit();

	window = glfwCreateWindow(props.width, props.height, "window", NULL, NULL);
	glfwMakeContextCurrent(window);

	gl3wInit();

	Startup();
}

void PoliGL::SetResizeCallback(GLFWwindowsizefun callback)
{
	glfwSetWindowSizeCallback(window, callback);
}

void PoliGL::Shutdown()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(rendering_program);

	glfwDestroyWindow(window);
	glfwTerminate();
}

bool PoliGL::IsRunning()
{
	return !glfwWindowShouldClose(window);
}