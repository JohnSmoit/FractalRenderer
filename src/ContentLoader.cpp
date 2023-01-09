#include "ContentLoader.h"
#include "Timer.h"
#include "Material.h"
#include "AssetLibrary.h"
#include "types.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <exception>
#include <glew.h>
#include <glfw3.h>

namespace fs = std::filesystem;

const std::string shader_dir = "C:\\Users\\jusmo\\Develop\\Games\\FractalGodComplex\\Assets\\Shaders\\";
Timer ContentLoader::timer = Timer();

struct ShaderSourceData 
{
public:
	std::string shaderSources[2];

	const char* get_vertex_source() const
	{
		return shaderSources[0].c_str();
	}
	const char* get_fragment_source() const
	{
		return shaderSources[1].c_str();
	}

	bool has_vertex_shader() const
	{
		return !shaderSources[0].empty();
	}

	bool has_fragment_shader() const
	{
		return !shaderSources[1].empty();
	}
};
/// <summary>
/// finds the file and reads the source into a string (later to be converted to c-strings).
/// </summary>
/// <param name="filePath"></param>
/// <returns></returns>
std::string ReadSourceFromFile(const fs::path& filePath) 
{
	std::string sourceCode;
	std::ifstream sourceReader;

	sourceReader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		sourceReader.open(filePath.string());

		std::stringstream stream;

		stream << sourceReader.rdbuf();
		sourceReader.close();
		sourceCode = stream.str();
	}
	catch (std::ifstream::failure fail) 
	{
		std::cout << "failed to load source for reason: \n" << fail.what() << std::endl;
	}

	return sourceCode;
}

void CreatePrograms(const std::map<std::string, ShaderSourceData>& shaderSources) 
{
	for (auto iter = shaderSources.begin(); iter != shaderSources.end(); iter++) 
	{
		try 
		{
			const ShaderSourceData& value = iter->second;

			if (!value.has_fragment_shader() || !value.has_vertex_shader())
			{
				std::cout << "cannot load shader known by the name of " << iter->first << " because either the vertex source or the fragment source is missing!" << std::endl;
				continue;
			}

			const char* vSource = value.get_vertex_source();
			const char* fSource = value.get_fragment_source();

			Material* newMat = new Material(fSource, vSource);

			AssetLibrary<Material>::Add(newMat, iter->first); //note that adding to asset libraries takes ownership.
		}
		catch (std::exception ex) 
		{
			std::cout << "failed to create shader program: \n" << ex.what() << std::endl;
		}
	}
}

void ContentLoader::load_all_shaders() 
{
	timer.Start();
	try {
		std::string filePath = std::string(shader_dir);

		const fs::path path{ filePath };

		std::map<std::string, ShaderSourceData> shaderSources;

		//iterate through each file in the given directory
		for (const auto& entry : fs::recursive_directory_iterator(path))
		{
			const auto& path2 = entry.path();
			const auto fileName = path2.filename().string();

			if (entry.is_directory()) 
			{
				std::cout << "found dir: " << fileName << std::endl;
			}
			else if (entry.is_regular_file()) 
			{
				std::cout << "found file: " << fileName << std::endl;
				if (path2.has_extension())
				{
					const auto extension = path2.extension().string();

					int32 shaderType = -1;
					if (extension == ".fs") 
					{
						std::cout << "found fragment shader source: " << fileName << std::endl;
						shaderType = 1;
					}
					else if (extension == ".vs") 
					{
						std::cout << "found vertex shader source: " << fileName << std::endl;
						shaderType = 0;
					}

					if (shaderType != -1) 
					{
						if (!shaderSources.count(path2.stem().string())) 
						{
							ShaderSourceData dat;
							dat.shaderSources[shaderType] = ReadSourceFromFile(path2);
							shaderSources.emplace(path2.stem().string(), dat);
						}
						else 
						{
							ShaderSourceData& dat = shaderSources.at(path2.stem().string());
							dat.shaderSources[shaderType] = ReadSourceFromFile(path2);
						}
					}
				}
			}
			else 
			{
				std::cout << "dunno what this is: " << fileName << std::endl;
			}
		}

		if (!shaderSources.empty()) 
		{
			CreatePrograms(shaderSources);
		}
	}
	catch (std::exception ex) 
	{
		std::cout << "OOPS: " << ex.what() << std::endl;
	}
	timer.Stop();
}
TimeSpan ContentLoader::getLoadingTime() 
{
	return timer.GetElapsedTime();
}
