#pragma once
#include "json.hpp"
#include <compare>
struct ActorManagerSettings
{
	ActorManagerSettings(int gcDelay = 5, float deadZoneX = 2000, float deadZoneY = 2000) : gcDelay{ gcDelay }, deadZoneX{ deadZoneX }, deadZoneY{ deadZoneY } {};

	auto operator<=>(const ActorManagerSettings&)const = default;

	int gcDelay;
	float deadZoneX;
	float deadZoneY;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActorManagerSettings, gcDelay, deadZoneX, deadZoneY);