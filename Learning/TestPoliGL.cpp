#include "PoliGL.h"
#include "PoliShader.h"
#include "vmath.h"

class TestPoliGL : public Poli::PoliGL
{
private:
	GLuint buffer;

public:
	TestPoliGL()
	{

	}

	~TestPoliGL()
	{

	}

	struct vertex
	{
		// Position
		float x;
		float y;
		float z;

		// Color
		float r;
		float g;
		float b;
	};

	GLint mv_location;
	GLint proj_location;

	vmath::mat4 proj_matrix;

	void Startup() override
	{
		rendering_program = glCreateProgram();

		glPointSize(10);

		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLfloat vertex_positions[]
		{
			-1.0f,-1.0f,-1.0f, // triangle 1 : begin
			-1.0f,-1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, // triangle 1 : end

			1.0f, 1.0f,-1.0f, // triangle 2 : begin
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f, // triangle 2 : end

			1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,

			1.0f, 1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,

			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,

			1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,

			-1.0f, 1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f,-1.0f,

			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,

			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f,-1.0f, 1.0f
		};

		for (int i = 0; i < 108; i++)
		{
			vertex_positions[i] *= 0.1f;
		}

		proj_matrix = vmath::perspective(50.0f,
			(float)props.width / props.height,
			0.1f,
			1000.0f);

		glCreateBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(vertex_positions),
					 vertex_positions,
					 GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);

		CompileShaders();

		mv_location = glGetUniformLocation(rendering_program, "mv_matrix");
		proj_location = glGetUniformLocation(rendering_program, "proj_matrix");
	}

	void CompileShaders() override
	{
		GLuint vs = Poli::PoliShader::LoadShader(GL_VERTEX_SHADER, "vertex_shader.vert");
		glAttachShader(rendering_program, vs);
		GLuint fs = Poli::PoliShader::LoadShader(GL_FRAGMENT_SHADER, "fragment_shader.frag");
		glAttachShader(rendering_program, fs);

		glLinkProgram(rendering_program);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	void Render(double time) override
	{
		static const GLfloat bgColor[] =
		{
			0.0f, 0.5f, 0.0f, 1.0f
		};

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearBufferfv(GL_COLOR, 0, bgColor);
		glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);

		glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);

		for (int i = 0; i < 24; ++i)
		{
			float f = (float)i + (float)time * 0.3f;
			vmath::mat4 mv_matrix =
				vmath::translate(0.0f, 0.0f, -10.0f) *
				vmath::translate(sinf(2.1f * f) * 0.5f,
					cosf(1.7f * f) * 0.5f,
					sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) *
				vmath::rotate((float)time * 45.0f, 0.0f, 1.0f, 0.0f) *
				vmath::rotate((float)time * 81.0f, 1.0f, 0.0f, 0.0f);

			glUseProgram(rendering_program);
			glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
	}

	void OnResize(int w, int h) override
	{
		proj_matrix = vmath::perspective(100.0f,
			(float)w / h,
			0.1f,
			1000.0f);
	}
};