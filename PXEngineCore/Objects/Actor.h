#pragma once
#include "Components/ActorComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/ColliderComponent.h"
#include "Settings/ActorSettings.h"
#include "Settings/TextureSettings.h"
#include <list>
#include <memory>
#include <optional>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
class WorldBase;
class Actor
{
public:
	Actor(WorldBase* parent = nullptr, ActorSettings actorSettings = ActorSettings(), TextureSettings textureSettings = TextureSettings());
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;
	Actor(Actor&&) = delete;
	Actor& operator=(Actor&&) = delete;
	virtual ~Actor() = default;
	virtual std::string ToString()const;
	virtual void Init();
	virtual void OnSpawn() {}
	virtual void OnDelete();
	virtual void OnOverlap(const Actor* other, sf::Vector2f difference) {}
	virtual void OnCollide(const Actor* other, sf::Vector2f difference) {}
	virtual void Update(double delta);
	virtual void Move(const sf::Vector2f& velocity);
	virtual void ConstPush(const sf::Vector2f& cVelocity);
	virtual void Draw(sf::RenderWindow& window);
	void Destroy();
	bool ToDestroy() const;
	sf::Vector2f GetPosition()const;
	bool CanCollide()const;
protected:
	template<typename T>
		requires std::derived_from<T, ActorComponent>
	std::weak_ptr<T> GetActorComponent()const
	{
		for (const auto& component : _actorComponents)
			if (auto castedComponent = std::dynamic_pointer_cast<T>(component))
				return castedComponent;
		return {};
	}
	std::weak_ptr<ColliderComponent> GetColliderComponent()const;
	WorldBase* _parent;
	ActorSettings _actorSettings;
	TextureSettings _textureSettings;
	std::unique_ptr<sf::Texture> _texture;
	std::unique_ptr<sf::Sprite> _sprite;
	sf::Vector2f _velocity;
	bool _pushed{ false };
private:
	virtual void CreateActorComponents();
	void ChangePosition(sf::Vector2f velocity);
	std::list<std::shared_ptr<ActorComponent>> _actorComponents;
	bool _destroy{ false };
};