#pragma once
#include "Component.h"
#include <string>

class ComponentMaterial :
	public Component
{
public:
	ComponentMaterial(GameObject* parent);
	~ComponentMaterial();

public:

	const bool		HasTexture() const;
	const uint		GetIDTexture() const;

	const bool		HasShader() const;
	const uint		GetIDShader() const;

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
	bool select_shader = false;

public:
	uint64 uid = 0u;

	uint64 s_uid = 0u;
};

