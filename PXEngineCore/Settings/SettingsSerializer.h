#pragma once
#include "ActorManagerSettings.h"
#include "EngineBaseSettings.h"
#include "json.hpp"
#include "WindowSettings.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
using namespace nlohmann;
class SettingsSerializer
{
public:
	SettingsSerializer(const std::string& root) :_root{ root } {}

	template<class T>
	static std::optional<T> CreateSettingsStatic(const std::string& path)
	{
		T result;
		try
		{
			std::ifstream stream(path);
			json jobj;
			stream >> jobj;
			result = jobj;
			stream.close();
		}
		catch (std::exception& exception)
		{
			std::cerr << "Error in SettingsSerializer<" << typeid(T).name() << ">::CreateSettingsStatic. \n" << exception.what();
			return std::optional<T>();
		}
		return result;
	}

	template<class T>
	std::optional<T> CreateSettings(const std::string& path)
	{
		return CreateSettingsStatic<T>(_root + path);
	}

	template<class T>
	static void CreateSettingsJsonFileStatic(const std::string& path, const T& settings = T())
	{
		try
		{
			std::ofstream stream(path);
			json jobj = settings;
			stream << jobj.dump(4);
			stream.close();
		}
		catch (std::exception& exception)
		{
			std::cerr << "Error in SettingsSerializer<" << typeid(T).name() << ">::CreateSettingsJsonFileStatic. \n" << exception.what();
		}
	}

	template<class T>
	void CreateSettingsJsonFile(const std::string& path, const T& settings = T())
	{
		CreateSettingsJsonFileStatic(_root + path, settings);
	}
protected:
	std::string _root;
};