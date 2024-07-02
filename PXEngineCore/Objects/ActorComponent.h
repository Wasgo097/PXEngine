#pragma once
class ActorComponent
{
public:
	virtual ~ActorComponent() = default;
	virtual void InitComponent() {}
	virtual void EndComponent() {}
	void Update(double delta);
};

