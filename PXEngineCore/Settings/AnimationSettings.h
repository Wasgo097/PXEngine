#pragma once
#include "BasicSFMLTypesToJson.h"
#include "json.hpp"
#include <map>
#include <SFML/System/Vector2.hpp>
enum class Direction {
	None,
	Left,
	Up,
	Right,
	Down,
	LeftIdle,
	UpIdle,
	RightIdle,
	DownIdle
};
NLOHMANN_JSON_SERIALIZE_ENUM(Direction, {
{Direction::None, "None"},
{Direction::Left, "Left"},
{Direction::Up, "Up"},
{Direction::Right, "Right"},
{Direction::LeftIdle, "LeftIdle"},
{Direction::UpIdle, "UpIdle"},
{Direction::RightIdle, "RightIdle"},
{Direction::DownIdle, "DownIdle"}
	});
struct AnimationSettings
{
	//framescount key is a rows(y), value is a  columns (x), all columns and rows which will be used in animation; switchtime - switch between aniamtion 
	//rectsize - size of one frame on texture image
	AnimationSettings(sf::Vector2u rectSize, double switchTime = .0, const std::map<int, int>& framesCount = std::map<int, int>(), const std::map<Direction, int>& dirToRow = std::map<Direction, int>()) :rectSize{ rectSize }, 
		switchTime{ switchTime }, framesCount{ framesCount }, dirToRow{ dirToRow } {}

	bool operator ==(const AnimationSettings& obj)const
	{
		return (rectSize == obj.rectSize) &&
			(switchTime == obj.switchTime) &&
			(framesCount == obj.framesCount) &&
			(dirToRow == obj.dirToRow);
	}

	sf::Vector2u rectSize;
	double switchTime;
	//k - row number  v - count of columns
	std::map<int, int> framesCount;
	//k - direction v-row number
	std::map<Direction, int> dirToRow;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationSettings, rectSize, switchTime, framesCount, dirToRow);