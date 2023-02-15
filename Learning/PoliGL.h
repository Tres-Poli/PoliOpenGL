#pragma once

#include <string.h>
#include <GL/gl3w.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Poli
{
	class PoliGL
	{
	protected:
		struct WindowProps
		{
			char title[64];
			int width;
			int height;
			int minor_version;
			int major_version;
		} props;

		GLFWwindow* window;
		GLuint rendering_program;
		GLuint vao;

	public:
		PoliGL()
		{

		}

		virtual ~PoliGL()
		{

		}

		void Init(const char* title, int width, int height, int minor_version, int major_version);
		void Shutdown();
		bool IsRunning();
		void SetResizeCallback(GLFWwindowsizefun callback);

		virtual void CompileShaders()
		{

		}

		virtual void Startup()
		{

		}

		virtual void Render(double time)
		{

		}

		virtual void OnResize(int w, int h)
		{

		}
	};
}
