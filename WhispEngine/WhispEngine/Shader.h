#ifndef __SHADER_H__
#define __SHADER_H__

#include <iostream>

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
	static SHADER_PROGRAM_SOURCE ParseShader(const std::string& path);
	static uint CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);
	static uint CompileShader(const uint& shader_type, const std::string& shader_source);
};

#endif /* __SHADER_H__ */