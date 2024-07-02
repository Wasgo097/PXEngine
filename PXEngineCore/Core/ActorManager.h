#pragma once
#include "Objects/Actor.h"
#include "Settings/ActorManagerSettings.h"
#include <memory>
class ActorManager
{
public:
	ActorManager(ActorManagerSettings actorManagerSettings);
	void RegistrNewActor(const std::shared_ptr<Actor>& newActor);
protected:
	ActorManagerSettings _actorManagerSettings;
};

