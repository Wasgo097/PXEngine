#include "ActorManager.h"

#include <algorithm>
#include <functional>
#include "WorldBase.h"
ActorManager::ActorManager(WorldBase* parent, ActorManagerSettings actorManagerSettings) :_parent{ parent }, _actorManagerSettings{ std::move(actorManagerSettings) }
{
}

void ActorManager::RegistrNewActor(const std::shared_ptr<Actor>& newActor)
{
	std::lock_guard lock(*_actors.mtx);
	_actors.rsc->push_back(newActor);
	newActor->Init();
}

void ActorManager::Draw(sf::RenderWindow& window)
{
	static std::function<bool(const std::shared_ptr<const Actor>&, const std::shared_ptr<const Actor>&)> actors_comparator =
		[](const std::shared_ptr<const Actor>& first, const std::shared_ptr<const Actor>& second) {
		auto firstPos = first->GetPosition();
		auto secondPos = second->GetPosition();
		return static_cast<int>(firstPos.y) < static_cast<int>(secondPos.y);
		return true;
		};
	std::lock_guard lock(*_actors.mtx);
	for (auto& actor : *_actors.rsc)
		actor->Draw(window);
}

void ActorManager::Update(double delta)
{
	std::lock_guard lock(*_actors.mtx);
	for (auto& actor : *_actors.rsc)
		actor->Update(delta);
}

void ActorManager::Run()
{
	std::lock_guard lock(*_actors.mtx);
	auto it = std::partition(_actors.rsc->begin(), _actors.rsc->end(), [this](const std::shared_ptr<Actor>& actor) {
		bool toDestroy = actor->ToDestroy() || PositionOnDeadzone(actor->GetPosition());
		if (toDestroy)
			actor->OnDelete();
		return toDestroy; });
	if (_actors.rsc->begin() != it)
	{
		_actors.rsc->erase(_actors.rsc->begin(), it);
		_parent->OnActorDelete();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(_actorManagerSettings.gcDelay));
}

bool ActorManager::PositionOnDeadzone(const sf::Vector2f& position) const {
	return position.x < -std::abs(_actorManagerSettings.deadZoneX) or position.x > std::abs(_actorManagerSettings.deadZoneX)
		or position.y < -std::abs(_actorManagerSettings.deadZoneY) or position.y > std::abs(_actorManagerSettings.deadZoneY);
}