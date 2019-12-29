#include <fstream>

#include "ComponentMaterial.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "Application.h"
#include "MaterialImporter.h"
#include "ResourceTexture.h"
#include "ResourceShader.h"
#include "ModuleImport.h"
#include "ModuleInput.h"
#include "ModuleObjectManager.h"
#include "ModuleResources.h"
#include "Resource.h"
#include "TextEditor.h"
#include "FileSystem.h"

ComponentMaterial::ComponentMaterial(GameObject* parent) : Component(parent, ComponentType::MATERIAL)
{
	text_editor.SetLanguageDefinition(lang);

	// Always apply the default shader. Don't change the name of the file!!!
	uint64 id_s = App->resources->Find("Assets\\Shaders\\shader_default.shader");
	res_shader = (ResourceShader*)App->resources->Get(id_s);

	fileToEdit = res_shader->file;
}


ComponentMaterial::~ComponentMaterial()
{
	App->resources->FreeMemory(uid);
	App->resources->FreeMemory(s_uid);
}

const bool ComponentMaterial::HasTexture() const
{
	return uid != 0u;
}

const uint ComponentMaterial::GetIDTexture() const
{
	ResourceTexture *res = (ResourceTexture*)App->resources->Get(uid);
	if (res != nullptr)
		return res->buffer_id;

	return 0u;
}

const bool ComponentMaterial::HasShader() const
{
	return s_uid != 0u;
}

const uint ComponentMaterial::GetIDShader() const
{
	ResourceShader* res = (ResourceShader*)App->resources->Get(s_uid);
	if (res != nullptr)
		return res->renderer_id;

	return 0u;
}

void ComponentMaterial::ShowShaderTextEditor()
{
	auto cpos = text_editor.GetCursorPosition();
	ImGui::SetNextWindowPosCenter(ImGuiCond_FirstUseEver);
	ImGui::Begin("Text Editor", &show_shader_text_editor, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
	ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				auto textToSave = text_editor.GetText();
				
				// Save text assets folder
				App->file_system->SaveTextFile(textToSave.c_str(), fileToEdit.c_str());
			
				// Save text library folder
				App->file_system->SaveTextFile(textToSave.c_str(), res_shader->resource_path.c_str());
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			bool ro = text_editor.IsReadOnly();
			if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
				text_editor.SetReadOnly(ro);
			ImGui::Separator();

			if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && text_editor.CanUndo()))
				text_editor.Undo();
			if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && text_editor.CanRedo()))
				text_editor.Redo();

			ImGui::Separator();

			if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, text_editor.HasSelection()))
				text_editor.Copy();
			if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && text_editor.HasSelection()))
				text_editor.Cut();
			if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && text_editor.HasSelection()))
				text_editor.Delete();
			if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
				text_editor.Paste();

			ImGui::Separator();

			if (ImGui::MenuItem("Select all", nullptr, nullptr))
				text_editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(text_editor.GetTotalLines(), 0));

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Dark palette"))
				text_editor.SetPalette(TextEditor::GetDarkPalette());
			if (ImGui::MenuItem("Light palette"))
				text_editor.SetPalette(TextEditor::GetLightPalette());
			if (ImGui::MenuItem("Retro blue palette"))
				text_editor.SetPalette(TextEditor::GetRetroBluePalette());
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, text_editor.GetTotalLines(),
		text_editor.IsOverwrite() ? "Ovr" : "Ins",
		text_editor.CanUndo() ? "*" : " ",
		text_editor.GetLanguageDefinition().mName.c_str(), fileToEdit.c_str());

	text_editor.Render("TextEditor");

	ImGui::End();
}

void ComponentMaterial::OnInspector()
{
	ActiveImGui();
	ImGui::SameLine();
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen)) {

		ImGui::ColorEdit4("Face Color", face_color);
		ImGui::ColorEdit4("Wireframe Color", wire_color);

		if (uid != 0u) {
			ResourceTexture * texture = (ResourceTexture*)App->resources->Get(uid);
			if (texture != nullptr)
				ImGui::Text("%s", texture->GetFile());
			if (ImGui::Button("Change Texture")) {
				select_tex = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Deselect Texture")) {
				App->resources->FreeMemory(uid);
				uid = 0;
				texture = nullptr;
			}

			if (texture != nullptr) {
				ImGui::Text("(%d, %d)", texture->width, texture->height);
				ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), "References: %u", texture->GetReferences());
				ImGui::Image((ImTextureID)texture->buffer_id, ImVec2(128.f, 128.f));
			}
		}
		else {
			if (ImGui::Button("Select Texture")) {
				select_tex = true;
			}
		}
		if (select_tex) {
			float width = 20;
			float height = 20.f;
			if (ImGui::Begin("Select Texture", &select_tex)) {
				std::vector<ResourceTexture*> textures;
				App->resources->GetTextures(textures);
				for (auto i = textures.begin(); i != textures.end(); ++i) {
					if ((*i)->IsLoadedInMemory()) {
						ImGui::ImageButton((ImTextureID)(*i)->buffer_id, ImVec2(width, height));
						ImGui::SameLine();
					}
					ImGui::Text((*i)->GetFile());
				}

				ImGui::End();
			}

		}

		ImGui::Separator();

		ImGui::Text("Current shader: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), res_shader->file.c_str());
		if (ImGui::Button("Select Shader"))
		{
			select_shader = true;
		}

		ImGui::SameLine();
		if (ImGui::Button("Edit shader"))
		{
			{
				std::ifstream t(fileToEdit.c_str());
				if (t.good())
				{
					std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
					text_editor.SetText(str);
				}
			}

			show_shader_text_editor = true;
		}

		if (ImGui::Button("Compile shader"))
		{
			res_shader->ParseAndCreateShader();
		}

		if (select_shader)
		{
			//ImGui::SetNextWindowPosCenter(ImGuiCond_::ImGuiCond_Always);
			if (ImGui::Begin("Select Shader", &select_shader))
			{
				if (ImGui::Button("Close"))
				{
					select_shader = false;
				}

				std::vector<ResourceShader*> shaders;
				App->resources->GetShaders(shaders);
				for (auto i = shaders.begin(); i != shaders.end(); ++i) {
					/*if ((*i)->IsLoadedInMemory()) {
						ImGui::ImageButton((ImTextureID)(*i)->renderer_id, ImVec2(width, height));
						ImGui::SameLine();
					}*/
					if (ImGui::Button((*i)->GetFile()))
					{
						uint64 id_s = App->resources->Find((*i)->GetFile());
						res_shader = (ResourceShader*)App->resources->Get(id_s);

						fileToEdit = res_shader->file;
					}
				}

				ImGui::End();
			}
		}

		if (show_shader_text_editor)
		{
			ShowShaderTextEditor();
		}
	}
}

void ComponentMaterial::Save(nlohmann::json & node)
{
	node["Resource"] = uid;
	App->json->AddColor4("face color", face_color, node);
	App->json->AddColor4("wire color", wire_color, node);
}

void ComponentMaterial::Load(const nlohmann::json & node)
{
	uid = (uint64)node.value("Resource", (uint64)0u);
	App->resources->LoadToMemory(uid);

	App->json->GetColor4("face color", node, face_color);

	App->json->GetColor4("wire color", node, wire_color);
}

void ComponentMaterial::SetFaceColor(const float & r, const float & g, const float & b, const float & a)
{
	face_color[0] = r;
	face_color[1] = g;
	face_color[2] = b;
	face_color[3] = a;
}

void ComponentMaterial::SetFaceColor(const float * c)
{
	memcpy(face_color, c, sizeof(float) * 4);
}

void ComponentMaterial::SetWireColor(const float & r, const float & g, const float & b, const float & a)
{
	wire_color[0] = r;
	wire_color[1] = g;
	wire_color[2] = b;
	wire_color[3] = a;
}

void ComponentMaterial::SetWireColor(const float * c)
{
	memcpy(wire_color, c, sizeof(float) * 4);
}

const float * ComponentMaterial::GetFaceColor() const
{
	return &face_color[0];
}

const float * ComponentMaterial::GetWireColor() const
{
	return &wire_color[0];
}
