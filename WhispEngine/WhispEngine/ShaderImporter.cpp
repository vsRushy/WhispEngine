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

	ResourceShader* shad = (ResourceShader*)App->resources->CreateResource(Resource::Type::SHADER, meta);
	App->file_system->GenerateMetaFile(shad_path.c_str(), shad->GetUID());

	shad->SetFile(shad_path.c_str());
	shad->SetResourcePath(std::string(SHADER_L_FOLDER + std::to_string(shad->GetUID()) + ".shader").c_str());
	shad->ParseAndCreateShader();
}
