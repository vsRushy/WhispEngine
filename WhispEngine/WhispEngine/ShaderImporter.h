#ifndef __SHADER_IMPORTER_H__
#define __SHADER_IMPORTER_H__

#include "Importer.h"
#include "Globals.h"

class ShaderImporter : public Importer
{
public:
	ShaderImporter();
	~ShaderImporter();

	uint64 Import(const char* path, const uint64& force_uid = 0u);
};

#endif /* __SHADER_IMPORTER_H__ */