#include "PoliShader.h"
#include <cstdio>

GLuint Poli::PoliShader::LoadShader(GLenum shader_type, const char* file_path)
{
	FILE* file;
	size_t filesize;
	char* data;

	fopen_s(&file, file_path, "r");
	fseek(file, 0, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0, SEEK_SET);

	data = new char[filesize + 1];
	memset(data, 0, sizeof(char) * filesize);

	fread(data, 1, filesize, file);
	fclose(file);

	data[filesize] = '\0';

	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &data, NULL);
	glCompileShader(shader);

	delete[] data;

	return shader;
}
