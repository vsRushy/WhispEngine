#include <iostream>
#include <fstream>
#include <sstream>

#include "glew-2.1.0/include/GL/glew.h"

#include "ResourceShader.h"

ResourceShader::ResourceShader(const uint64& uid) : Resource(uid, Resource::Type::SHADER)
{

}

/*ResourceShader::ResourceShader(const std::string& path)
	: file_path(path), renderer_id(NULL)
{
	SHADER_PROGRAM_SOURCE source = ParseShader(path);
	renderer_id = CreateShader(source.vertex_source, source.fragment_source);
}*/

ResourceShader::~ResourceShader()
{
	if (references > 0u)
		FreeMemory();
	references = 0u;

	glDeleteProgram(renderer_id);
}

bool ResourceShader::LoadInMemory()
{
	return true;
}

bool ResourceShader::FreeMemory()
{
	return true;
}

void ResourceShader::Bind() const
{
	glUseProgram(renderer_id);
}

void ResourceShader::Unbind() const
{
	glUseProgram(NULL);
}

void ResourceShader::SetUniform1f(const std::string& name, const float& value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void ResourceShader::SetUniform4f(const std::string& name, const float& v0, const float& v1, const float& v2, const float& v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

SHADER_PROGRAM_SOURCE ResourceShader::ParseShader(const std::string& path)
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

uint ResourceShader::CreateShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	uint program = glCreateProgram();

	uint vertex_s = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	uint fragment_s = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

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

uint ResourceShader::CompileShader(const uint& shader_type, const std::string& shader_source)
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
			type_string = "WE_NULL";
			break;
		}

		LOG("ERROR: Can't compile %s shader...", type_string.c_str());
		LOG(message);

		glDeleteShader(shader_id);

		return 0;
	}

	return shader_id;
}

int ResourceShader::GetUniformLocation(const std::string& name) const
{
	int location = glGetUniformLocation(renderer_id, name.c_str());
	if (location == -1)
	{
		LOG("WARNING: Uniform %s doesn't exist...", name.c_str());
	}

	return location;
}
