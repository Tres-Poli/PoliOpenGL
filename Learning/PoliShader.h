#pragma once

#include <GL/gl3w.h>

namespace Poli
{
	class PoliShader
	{
	public:
		static GLuint LoadShader(GLenum shader_type, const char* file_path);
	};
}