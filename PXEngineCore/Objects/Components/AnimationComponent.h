#pragma once
#include "ActorComponent.h"
#include "Settings/AnimationSettings.h"
#include <SFML/Graphics/Sprite.hpp>
class AnimationComponent :public ActorComponent
{
public:
	AnimationComponent(Actor* parent, sf::Sprite& animatedSprite, const AnimationSettings& animationSettings);
	void Update(double delta)override;
protected:
	void SetRow(int row);
	void SetRowAndSetTexture(int row);
	sf::Sprite& _animatedSprite;
	AnimationSettings _animationSettings;
	sf::IntRect _frameOnTexture;
	sf::Vector2u _viewOnTexture;
	double _elapsed;
	int _row;
};