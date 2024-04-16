#pragma once

#include "Shader.h"

#include <unordered_map>

class ResourceManager
{
public:
	static void loadShader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile);
	static std::shared_ptr<Shader> getLoadedShader(const std::string& name);
private:
	static std::unordered_map<std::string, std::shared_ptr<Shader>> mLoadedShaders;
};
