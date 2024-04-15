#include "ResourceManager.h"

std::map<std::string, std::shared_ptr<Shader>> ResourceManager::mLoadedShaders;

void ResourceManager::loadShader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile)
{
	mLoadedShaders[name] = std::make_shared<Shader>();
	mLoadedShaders[name]->loadShader(vertexFile.c_str(), fragmentFile.c_str());
}

std::shared_ptr<Shader> ResourceManager::getLoadedShader(const std::string& name)
{
	return mLoadedShaders[name];
}
