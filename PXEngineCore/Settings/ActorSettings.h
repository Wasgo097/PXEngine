#pragma once
#include "json.hpp"
#include "BasicSFMLTypesToJson.h"
enum class CollisionType {
	None,
	Overlap,
	Collision
};
enum class ActorType {
	Static,
	Dynamic
};
NLOHMANN_JSON_SERIALIZE_ENUM(CollisionType, {
	{CollisionType::None, "None"},
	{CollisionType::Overlap, "Overlap"},
	{CollisionType::Collision, "Collision"}
	});
NLOHMANN_JSON_SERIALIZE_ENUM(ActorType, {
{ActorType::Static, "Static"},
{ActorType::Dynamic, "Dynamic"}
	});
struct ActorSettings
{
	ActorSettings(CollisionType collision = CollisionType::None, ActorType type = ActorType::Static, sf::Vector2f position = sf::Vector2f(), sf::Vector2f colliderSize = sf::Vector2f(), sf::Vector2f initVelocity = sf::Vector2f(), bool drawableCollisionBox = false) :
		collision{ collision }, type{ type }, position{ position }, colliderSize{ colliderSize }, initVelocity{ initVelocity }, drawableCollisionBox{ drawableCollisionBox } {}

	bool operator ==(const ActorSettings& obj)const {
		return (collision == obj.collision) &&
			(type == obj.type) &&
			(position == obj.position) &&
			(colliderSize == obj.colliderSize) &&
			(initVelocity == obj.initVelocity) &&
			(drawableCollisionBox == obj.drawableCollisionBox);
	}

	CollisionType collision;
	ActorType type;
	sf::Vector2f position;
	sf::Vector2f colliderSize;
	sf::Vector2f initVelocity;
	bool drawableCollisionBox;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActorSettings, collision, type, position, colliderSize, initVelocity, drawableCollisionBox);