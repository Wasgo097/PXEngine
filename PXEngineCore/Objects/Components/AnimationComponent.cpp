#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(Actor* parent, sf::Sprite& animatedSprite, const AnimationSettings& animationSettings) :ActorComponent(parent), _animatedSprite{ animatedSprite }, _animationSettings{ animationSettings }, _elapsed{ .0 }, _row{ -1 }
{
	_frameOnTexture.width = _animationSettings.rectSize.x;
	_frameOnTexture.height = _animationSettings.rectSize.y;
}

void AnimationComponent::SetRow(int row)
{
	if (_row != row)
	{
		_row = row;
		_viewOnTexture.x = 0;
		_elapsed = .0;
	}
}

void AnimationComponent::SetRowAndSetTexture(int row)
{
	SetRow(row);
	_viewOnTexture.y = _row;
	_viewOnTexture.x = 0;
	_frameOnTexture.left = _viewOnTexture.x * _animationSettings.rectSize.x;
	_frameOnTexture.top = _viewOnTexture.y * _animationSettings.rectSize.y;
	_animatedSprite.setTextureRect(_frameOnTexture);
}

void AnimationComponent::Update(double delta)
{
	_viewOnTexture.y = _row;
	_elapsed += delta;
	if (_elapsed >= _animationSettings.switchTime)
	{
		_elapsed -= _animationSettings.switchTime;
		_viewOnTexture.x++;
		if (_viewOnTexture.x >= _animationSettings.framesCount.at(_viewOnTexture.y))
			_viewOnTexture.x = 0;
	}
	_frameOnTexture.left = _viewOnTexture.x * _animationSettings.rectSize.x;
	_frameOnTexture.top = _viewOnTexture.y * _animationSettings.rectSize.y;
	_animatedSprite.setTextureRect(_frameOnTexture);
}