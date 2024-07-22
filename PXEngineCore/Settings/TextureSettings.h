#pragma once
#include "json.hpp"
struct TextureSettings
{
	TextureSettings(const std::string& texturePath = "", bool smooth = false, bool repeatable = false, float scale = 1.0f) :texturePath{ texturePath }, smooth{ smooth }, repeatable{ repeatable }, scale{ scale } {}

	bool operator==(const TextureSettings& obj)const
	{
		return texturePath == obj.texturePath && smooth == obj.smooth && repeatable == obj.repeatable;
	}

	std::string texturePath;
	bool smooth;
	bool repeatable;
	float scale;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TextureSettings, texturePath, smooth, repeatable, scale);