#include "ResourceManager.h"

std::unordered_map<std::string, std::shared_ptr<Shader>> ResourceManager::mLoadedShaders;
std::unordered_map<std::string, std::shared_ptr<StaticModel>> ResourceManager::mLoadedStaticModels;

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

void ResourceManager::loadStaticModel(const std::string& name, const std::string& filePath)
{
	if (mLoadedStaticModels.find(name) != mLoadedStaticModels.end())
	{
		std::cout << "Static model " << name << " already loaded!" << std::endl;
		return;
	}
	mLoadedStaticModels[name] = std::make_shared<StaticModel>();
	mLoadedStaticModels[name]->loadModel(filePath);
}

std::shared_ptr<StaticModel> ResourceManager::getStaticModel(const std::string& name)
{
	if (mLoadedStaticModels.find(name) == mLoadedStaticModels.end())
	{
		std::cout << "Static model " << name << " not loaded yet!" << std::endl;
		return nullptr;
	}
	return mLoadedStaticModels[name];
}

