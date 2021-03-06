#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

#include "Resource.h"
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

class ResourceShader : public Resource
{
	friend class ComponentMaterial;

public:
	ResourceShader(const uint64& uid);
	~ResourceShader();

	void ParseAndCreateShader();

	bool LoadInMemory() override;
	bool FreeMemory() override;

	void Bind() const;
	void Unbind() const;

	void SetUniform1f(const std::string& name, const float& value);
	void SetUniform4f(const std::string& name, const float& v0, const float& v1, const float& v2, const float& v3);
	void SetUniformMat4f(const std::string& name, const math::float4x4& matrix);

private:
	SHADER_PROGRAM_SOURCE ParseShader(const std::string& path);
	uint CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);
	uint CompileShader(const uint& shader_type, const std::string& shader_source);

	int GetUniformLocation(const std::string& name) const;

	// TODO: Shader uniform cache
	// TODO: glVertexAttribPointer, etc...

protected:
	uint renderer_id;
};

#endif /* __SHADER_H__ */