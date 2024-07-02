#include "ActorManager.h"

ActorManager::ActorManager(ActorManagerSettings actorManagerSettings) :_actorManagerSettings{ std::move(actorManagerSettings) }
{
}

void ActorManager::RegistrNewActor(const std::shared_ptr<Actor>& newActor)
{
}
