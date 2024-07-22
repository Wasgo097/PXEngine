#include "ColliderComponent.h"
#include "../Actor.h"
ColliderComponent::ColliderComponent(Actor* parent, const ActorSettings& actorSettings) :ActorComponent{ parent }, _collider(actorSettings.colliderSize)
{
	sf::Vector2f origin = _collider.getSize();
	origin.x /= 2.0f;
	_collider.setOrigin(origin);
	_collider.setPosition(actorSettings.position);
}

void ColliderComponent::Move(const sf::Vector2f& velocity)
{
	_collider.move(velocity);
}

const sf::RectangleShape& ColliderComponent::GetCollider() const
{
	return _collider;
}

sf::RectangleShape& ColliderComponent::GetCollider()
{
	return _collider;
}

bool ColliderComponent::Collide(const ColliderComponent& other, sf::FloatRect& outRect) const
{
	return _collider.getGlobalBounds().intersects(other._collider.getGlobalBounds(), outRect);
}