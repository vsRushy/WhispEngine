#include <string>
#include <fstream>
#include <sstream>
#include "glew-2.1.0/include/GL/glew.h"

#include "Shader.h"

SHADER_PROGRAM_SOURCE WhispShader::ParseShader(const std::string& path)
{
	std::ifstream stream(path);

	std::string line;
	std::stringstream ss[2]; // one for each shader type
	
	SHADER_TYPE shader_type = SHADER_TYPE::UNKNOWN;
	
	while (getline(stream, line))
	{
		if (line.find("shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				shader_type = SHADER_TYPE::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				shader_type = SHADER_TYPE::FRAGMENT;
			}
		}
		else
		{
			ss[(int)shader_type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

uint WhispShader::CreateShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	uint program = glCreateProgram();

	uint vertex_s = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	uint fragment_s = CompileShader(GL_FRAGMENT_SHADER, vertex_shader);

	glAttachShader(program, vertex_s);
	glAttachShader(program, fragment_s);

	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, vertex_s);
	glDetachShader(program, fragment_s);

	glDeleteShader(vertex_s);
	glDeleteShader(fragment_s);

	return program;
}

uint WhispShader::CompileShader(const uint& shader_type, const std::string& shader_source)
{
	uint shader_id = glCreateShader(shader_type);

	const char* source = shader_source.c_str();
	glShaderSource(shader_id, 1, &source, nullptr);
	glCompileShader(shader_id);
	
	int result;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader_id, length, &length, message);

		std::string type_string;
		switch (shader_type)
		{
		case GL_VERTEX_SHADER:
		{
			type_string = "vertex";
		}
		break;
		case GL_FRAGMENT_SHADER:
		{
			type_string = "fragment";
		}
		break;
		default:
			break;
		}

		LOG("ERROR: Can't compile %s shader...", type_string);
		LOG(message);

		glDeleteShader(shader_id);
		
		return 0;
	}

	return shader_id;
}
