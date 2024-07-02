#pragma once
#include "json.hpp"
#include <string>
struct EngineBaseSettings
{
	EngineBaseSettings(const std::string& windowSettings = "windowsettings.json", const std::string& musicSettings = "musicsettings.json", const std::string& worldSettings = "worldbasesettings.json") :
		windowSettingsPath{ windowSettings }, musicSettingsPath{ musicSettings }, worldSettingsPath{ worldSettings } {}

	auto operator<=>(const EngineBaseSettings&)const = default;

	std::string windowSettingsPath;
	std::string musicSettingsPath;
	std::string worldSettingsPath;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EngineBaseSettings, windowSettingsPath, musicSettingsPath, worldSettingsPath);