#pragma once
#include "ActorComponent.h"
#include "Settings/ActorSettings.h"
#include <SFML/Graphics/RectangleShape.hpp>
class ColliderComponent :public ActorComponent
{
public:
	ColliderComponent(Actor* parent, const ActorSettings& actorSettings);
	void Move(const sf::Vector2f& velocity);
	const sf::RectangleShape& GetCollider()const;
	sf::RectangleShape& GetCollider();
	bool Collide(const ColliderComponent& other, sf::FloatRect& outRect)const;
protected:
	sf::RectangleShape _collider;
};