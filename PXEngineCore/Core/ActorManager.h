#pragma once
#include "Objects/Actor.h"
#include "Settings/ActorManagerSettings.h"
#include "Utilities/LoopingThread.h"
#include "Utilities/ThreadingResource.h"
#include <memory>
class WorldBase;
class ActorManager :public LoopingThread
{
public:
	ActorManager(WorldBase* parent,ActorManagerSettings actorManagerSettings);
	void RegistrNewActor(const std::shared_ptr<Actor>& newActor);
	void Draw(sf::RenderWindow& window);
	void Update(double delta);
	void Run() override;
protected:
	bool PositionOnDeadzone(const sf::Vector2f& position)const;
	ActorManagerSettings _actorManagerSettings;
	WorldBase* _parent;
	ThreadingResourceShared<std::vector<std::shared_ptr<Actor>>> _actors;
};