#pragma once
#include "Component.h"
#include <string>

struct Texture
{
	Texture(const uint &id, const char* path, const int& width, const int& height, const uint64_t& file_uid);

	uint id = 0u;
	uint64_t uid = 0u;
	std::string name;
	std::string path;

	bool visible_on_inspector = true;

	int width = -1;
	int height = -1;
};

class ComponentMaterial :
	public Component
{
public:
	ComponentMaterial(GameObject* parent);
	~ComponentMaterial();

public:

	void			SetTexture(Texture *texture);
	const bool		HasTexture() const;
	const uint		GetIDTexture() const;

	void OnInspector();

	void Save(nlohmann::json &node) override;
	void Load(const nlohmann::json &node) override;

	void			SetFaceColor(const float &r, const float &g, const float &b, const float &a);
	void			SetFaceColor(const float* c);
	void			SetWireColor(const float &r, const float &g, const float &b, const float &a);
	void			SetWireColor(const float* c);
	const float*	GetFaceColor() const;
	const float*	GetWireColor() const;

private:
	float face_color[4]{ 1.f, 1.f, 1.f, 1.f };
	float wire_color[4]{ 0.f, 0.f, 0.f, 0.f };

	bool select_tex = false;

	uint64 uid = 0u;
};

