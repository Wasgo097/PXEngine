#include "Actor.h"

Actor::Actor(WorldBase* parent, ActorSettings actorSettings, TextureSettings textureSettings) :_parent{ parent }, _actorSettings{ std::move(actorSettings) }, _textureSettings{ std::move(textureSettings) }
{
}

std::string Actor::ToString() const
{
	return "Actor";
}

void Actor::Init()
{
	CreateActorComponents();
	for (const auto& component : _actorComponents)
		component->InitComponent();
}

void Actor::OnDelete()
{
	for (const auto& component : _actorComponents)
		component->EndComponent();
}

void Actor::Update(double delta)
{
	for (const auto& component : _actorComponents)
		component->Update(delta);
}

void Actor::Move(const sf::Vector2f& velocity)
{

}

void Actor::ConstPush(const sf::Vector2f& const_velocity)
{

}

void Actor::Draw(sf::RenderWindow& window)
{

}

void Actor::Destroy() { _destroy = true; }
bool Actor::ToDestroy() const { return _destroy; }
