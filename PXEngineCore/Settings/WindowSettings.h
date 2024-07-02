#pragma once
#include "BasicSFMLTypesToJson.h"
#include "json.hpp"
#include <compare>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <string>
struct WindowSettingsBase
{
	WindowSettingsBase(sf::VideoMode mode = sf::VideoMode(), int displayStyle = sf::Style::Fullscreen, bool vsync = true) :videoMode{ mode }, displayStyle{ displayStyle }, vsync{ vsync } {}

	bool operator ==(const WindowSettingsBase& obj)const
	{
		return (videoMode == obj.videoMode) &&
			(displayStyle == obj.displayStyle) &&
			(vsync == obj.vsync);
	}

	sf::VideoMode videoMode;
	int displayStyle;
	bool vsync;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WindowSettingsBase, videoMode, displayStyle, vsync);
struct WindowSettings :public WindowSettingsBase
{
	WindowSettings(sf::VideoMode mode = sf::VideoMode(), int displayStyle = sf::Style::Fullscreen, bool vsync = false, const std::string& windowName = "Window") : WindowSettingsBase(mode, displayStyle, vsync), windowName{ windowName } {}

	bool operator ==(const WindowSettings& obj)const
	{
		return (videoMode == obj.videoMode) &&
			(displayStyle == obj.displayStyle) &&
			(vsync == obj.vsync) &&
			(windowName == obj.windowName);
	}

	std::string windowName;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WindowSettings, videoMode, displayStyle, vsync, windowName);