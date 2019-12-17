#include "ShaderImporter.h"
#include "Application.h"
#include "ModuleObjectManager.h"

#include "ModuleResources.h"
#include "ResourceShader.h"

#include "glew-2.1.0/include/GL/glew.h"

ShaderImporter::ShaderImporter()
{

}

ShaderImporter::~ShaderImporter()
{

}

uint64 ShaderImporter::Import(const char* path, const uint64& force_uid)
{
	uint64 meta = force_uid;
	if (meta == 0u)
		meta = App->random->RandomGUID();

	std::string file = App->file_system->GetFileFromPath(path);
	std::string shad_path(path);

	if (App->file_system->IsInSubDirectory(ASSETS_FOLDER, file.c_str(), &shad_path))
	{
		if (App->file_system->Exists((shad_path + ".meta").c_str()))
		{
			if (App->file_system->IsMetaVaild((shad_path + ".meta").c_str()))
			{
				meta = App->file_system->GetUIDFromMeta((shad_path + ".meta").c_str());
				Resource* res = App->resources->CreateResource(Resource::Type::SHADER, meta);
				res->SetFile(shad_path.c_str());
				res->SetResourcePath((SHADER_L_FOLDER + std::to_string(meta) + ".shader").c_str());
				// TODO: load resource

				return res->GetUID();
			}
			else
			{
				LOG("Meta %s not vaild, recreating...", path);
				meta = App->file_system->GetUIDFromMeta((shad_path + ".meta").c_str());
			}
		}
	}
	else
	{
		LOG("File not found in Assets folder, trying to find file in fbx folder...")
			shad_path.assign(std::string(SHADER_A_FOLDER) + file);
		if (!CopyFile(path, shad_path.data(), FALSE)) {
			wchar_t buf[256];
			FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
			LOG("Failed to copy texture in Assets folder, Error: %s", buf);
			return 0U;
		}
	}

	ResourceShader* shad = (ResourceShader*)App->resources->CreateResource(Resource::Type::SHADER, meta);
	App->file_system->GenerateMetaFile(shad_path.c_str(), shad->GetUID());

	shad->SetFile(shad_path.c_str());
	shad->SetResourcePath(std::string(SHADER_L_FOLDER + std::to_string(mat->GetUID()) + ".shader").c_str());
}
