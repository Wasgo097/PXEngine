#pragma once
class Actor;
class ActorComponent
{
public:
	ActorComponent(Actor* parent);
	virtual ~ActorComponent() = default;
	virtual void InitComponent() {}
	virtual void EndComponent() {}
	virtual void Update(double delta) {};
protected:
	Actor* _parent;
};