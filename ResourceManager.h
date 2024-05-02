#pragma once

#include "Shader.h"
#include "StaticModel.h"
#include "SkeletalModel.h"

#include <unordered_map>


class ResourceManager
{
public:
	static void loadShader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile);
	static std::shared_ptr<Shader> getLoadedShader(const std::string& name);

	static void loadStaticModel(const std::string& name, const std::string& filePath);
	static std::shared_ptr<StaticModel> getStaticModel(const std::string& name);

	static void loadSkeletealModel(const std::string& name, const std::string& filePath);
	static std::shared_ptr<SkeletalModel> getSkeletalModel(const std::string& name);
private:
	static std::unordered_map<std::string, std::shared_ptr<Shader>> mLoadedShaders;
	static std::unordered_map<std::string, std::shared_ptr<StaticModel>> mLoadedStaticModels;
	static std::unordered_map<std::string, std::shared_ptr<SkeletalModel>> mLoadedSkeletalModels;
};

