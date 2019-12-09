#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

#include "Globals.h"

struct SHADER_PROGRAM_SOURCE
{
	std::string vertex_source;
	std::string fragment_source;
};

enum class SHADER_TYPE
{
	UNKNOWN = -1,
	VERTEX,
	FRAGMENT
};

class WhispShader
{
public:
	WhispShader(const std::string& path);
	~WhispShader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	SHADER_PROGRAM_SOURCE ParseShader(const std::string& path);
	uint CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);
	uint CompileShader(const uint& shader_type, const std::string& shader_source);

	int GetUniformLocation(const std::string& name) const;

	// TODO: Shader uniform cache
	// TODO: glVertexAttribPointer, etc...

private:
	std::string file_path;
	uint renderer_id;
};

#endif /* __SHADER_H__ */