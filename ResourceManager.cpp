#include "ResourceManager.h"

std::unordered_map<std::string, std::shared_ptr<Shader>> ResourceManager::mLoadedShaders;

void ResourceManager::loadShader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile)
{
	if(mLoadedShaders.find(name) != mLoadedShaders.end())
	{
		std::cout << "Shader " << name << " already loaded!" << std::endl;
		return;
	}
	mLoadedShaders[name] = std::make_shared<Shader>();
	mLoadedShaders[name]->loadShader(vertexFile.c_str(), fragmentFile.c_str());
}

std::shared_ptr<Shader> ResourceManager::getLoadedShader(const std::string& name)
{
	if (mLoadedShaders.find(name) == mLoadedShaders.end())
	{
		std::cout << "Shader " << name << " not loaded yet!" << std::endl;
		return nullptr;
	}
	return mLoadedShaders[name];
}

