#include "WorldBase.h"

WorldBase::WorldBase(EngineBase* parent, ActorManagerSettings actorManagerSettings) :_parent{ parent }, _actorManager{ this, std::move(actorManagerSettings) }
{
}

void WorldBase::InitWorld()
{
	CreateWorldBaseComponents();
	InitCallbacks();
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
	_actorManager.Draw(window);
}

void WorldBase::Update(double delta)
{
	for (const auto& component : _worldBaseComponents)
		component->Update(delta);
	_actorManager.Update(delta);
}

void WorldBase::OnActorDelete()
{
	if (_onActorDelete)
		_onActorDelete();
}