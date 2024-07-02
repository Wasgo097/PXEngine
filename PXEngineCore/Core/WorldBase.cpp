#include "WorldBase.h"

WorldBase::WorldBase(EngineBase* parent, ActorManagerSettings actorManagerSettings) :_parent{ parent }, _actorManager{std::move(actorManagerSettings)}
{
}

void WorldBase::InitWorld()
{
	CreateWorldBaseComponents();
	for (const auto& component : _worldBaseComponents)
		component->InitComponent();
}

void WorldBase::EndWorld()
{
	for (const auto& component : _worldBaseComponents)
		component->EndComponent();
}

void WorldBase::Draw(sf::RenderWindow& window)
{
}

void WorldBase::Update(double delta)
{
	for (const auto& component : _worldBaseComponents)
		component->Update(delta);
}

bool WorldBase::Quit()
{
	return false;
}
