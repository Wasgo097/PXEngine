#pragma once
#include "ActorManager.h"
#include "Settings/ActorManagerSettings.h"
#include "WorldBaseComponent.h"
#include <concepts>
#include "Settings/ActorSettings.h"
#include "Settings/TextureSettings.h"
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
class EngineBase;
class WorldBase
{
public:
	WorldBase(EngineBase* parent = nullptr, ActorManagerSettings actorManagerSettings = ActorManagerSettings());
	WorldBase(const WorldBase&) = delete;
	WorldBase& operator=(const WorldBase&) = delete;
	WorldBase(WorldBase&&) = delete;;
	WorldBase& operator=(WorldBase&&) = delete;
	virtual ~WorldBase() = default;
	virtual void InitWorld();
	virtual void EndWorld();
	void Draw(sf::RenderWindow& window);
	void Update(double delta);
	virtual bool Quit() = 0;
	template<typename TypeToCreate, typename ...Argv>
		requires std::derived_from<TypeToCreate, Actor>
	std::weak_ptr<TypeToCreate> SpawnActor(const ActorSettings& actorSettings, const TextureSettings& textureSettings, Argv && ...argv) 
	{
		std::shared_ptr<TypeToCreate> result{ std::make_shared<TypeToCreate>(this, actorSettings, textureSettings, std::forward<Argv>(argv)...) };
		_actorManager.RegistrNewActor(result);
		result->OnSpawn();
		if (_onActorSpawn)
			_onActorSpawn(result);
		return result;
	}
	void OnActorDelete();
protected:
	template<typename T>
		requires std::derived_from<T, WorldBaseComponent>
	std::weak_ptr<T> GetWorldBaseComponent()const
	{
		for (const auto& component : _worldBaseComponents)
			if (auto castedComponent = std::dynamic_pointer_cast<T>(component))
				return castedComponent;
		return {};
	}
	EngineBase* _parent;
private:
	virtual void CreateWorldBaseComponents() = 0;
	virtual void InitCallbacks() = 0;
	std::function<void(const std::weak_ptr<Actor>&)> _onActorSpawn;
	std::function<void()> _onActorDelete;
	std::list<std::shared_ptr<WorldBaseComponent>> _worldBaseComponents;
	ActorManager _actorManager;
};