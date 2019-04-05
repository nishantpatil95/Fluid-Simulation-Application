#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
class Shader
{
public:
	static GLuint program;
	const char * vertexShaderCode =
		"uniform mat4 MVP;\n"
		"attribute vec3 vCol;\n"
		"attribute vec2 vPos;\n"
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
		"    color = vCol;\n"
		"}\n";
	const char * fragmentShaderCode =
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = vec4(color, 1.0);\n"
		"}\n";
	Shader()
	{
		GLuint vid = glCreateShader(GL_VERTEX_SHADER);
		GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vid, 1, &vertexShaderCode, 0);
		glCompileShader(vid);
		int result;
		glGetShaderiv(vid, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			cout << "FAILED" << endl;
			int length;
			glGetShaderiv(vid, GL_INFO_LOG_LENGTH, &length);
			char *msg = (char *)alloca(length * sizeof(char));
			glGetShaderInfoLog(vid, length, &length, msg);
			LOG("COMPILE ERROR::%s", msg);
			glDeleteShader(vid);
		}
		glShaderSource(fid, 1, &fragmentShaderCode, 0);
		glCompileShader(fid);

		glGetShaderiv(fid, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			cout << "FAILED" << endl;
			int length;
			glGetShaderiv(fid, GL_INFO_LOG_LENGTH, &length);
			char *msg = (char *)alloca(length * sizeof(char));
			glGetShaderInfoLog(fid, length, &length, msg);
			LOG("COMPILE ERROR::%s", msg);
			glDeleteShader(fid);

		}
		program = glCreateProgram();
		LOG("program::%d", program)
			glAttachShader(program, vid);
		glAttachShader(program, fid);
		glLinkProgram(program);

		glUseProgram(program);
	}
};