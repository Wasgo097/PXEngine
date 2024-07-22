#include "Actor.h"

Actor::Actor(WorldBase* parent, ActorSettings actorSettings, TextureSettings textureSettings) :_parent{ parent }, _actorSettings{ std::move(actorSettings) },
_textureSettings{ std::move(textureSettings) }
{
	if (!_textureSettings.texturePath.empty())
	{
		_texture = std::make_unique<sf::Texture>();
		if (_texture->loadFromFile(_textureSettings.texturePath))
		{
			_texture->setSmooth(_textureSettings.smooth);
			_texture->setRepeated(_textureSettings.repeatable);
			_sprite = std::make_unique<sf::Sprite>();
			_sprite->setTexture(*_texture);
			_sprite->setScale({ _textureSettings.scale,_textureSettings.scale });
			const auto& textureSize = _texture->getSize();
			sf::Vector2f origin(static_cast<float>(textureSize.x), static_cast<float>(textureSize.y));
			origin.x /= 2.0f;
			_sprite->setOrigin(origin);
			_sprite->setPosition(actorSettings.position);
		}
		else
		{
			_texture.reset();
			throw std::invalid_argument("Cant load actor texture: " + _textureSettings.texturePath + " in " + ToString());
		}
	}
	_velocity = _actorSettings.initVelocity;
	if (_velocity != sf::Vector2f())
		_pushed = true;
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
	if (_actorSettings.type == ActorType::Dynamic && _velocity != sf::Vector2f())
		ChangePosition(_velocity * static_cast<float>(delta));
}

void Actor::Move(const sf::Vector2f& velocity)
{
	_velocity = velocity;
}

void Actor::ConstPush(const sf::Vector2f& cVelocity)
{
	_velocity = cVelocity;
	_pushed = true;
}

void Actor::Draw(sf::RenderWindow& window)
{
	if (_sprite)
		window.draw(*_sprite);
	if (_actorSettings.drawableCollisionBox and CanCollide())
	{
		window.draw(GetColliderComponent().lock()->GetCollider());
		/*sf::CircleShape circle(1.0);
		circle.setPosition(GetColliderComponent().lock()->GetCollider().getPosition());
		circle.setFillColor(sf::Color::Black);
		window.draw(circle);*/
	}
}

void Actor::Destroy() { _destroy = true; }
bool Actor::ToDestroy() const { return _destroy; }

sf::Vector2f Actor::GetPosition() const
{
	if (_sprite)
		return _sprite->getPosition();
	else if (CanCollide())
		GetColliderComponent().lock()->GetCollider().getPosition();
	return  {};
}

bool Actor::CanCollide() const
{
	return _actorSettings.collision != CollisionType::None;
}

std::weak_ptr<ColliderComponent> Actor::GetColliderComponent() const
{
	return GetActorComponent<ColliderComponent>();
}

void Actor::CreateActorComponents()
{
	if (CanCollide())
		_actorComponents.emplace_back(std::make_shared<ColliderComponent>(this, _actorSettings));
}

void Actor::ChangePosition(sf::Vector2f velocity)
{
	if (!_sprite)
		return;
	_sprite->move(velocity);
	if (CanCollide())
		GetColliderComponent().lock()->Move(velocity);
	if (!_pushed)
		_velocity = sf::Vector2f();
}