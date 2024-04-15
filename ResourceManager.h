#pragma once

#include "Shader.h"

#include <map>

class ResourceManager
{
public:
	static void loadShader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile);
	static std::shared_ptr<Shader> getLoadedShader(const std::string& name);

	static void loadStaticModel(const std::string& name, const std::string& fileName);
	static void getLoadedStaticModel(const std::string& name);
private:
	static std::map<std::string, std::shared_ptr<Shader>> mLoadedShaders;
	static std::map<std::string, std::shared_ptr<Shader>> mLoadedStaticModels;
};

