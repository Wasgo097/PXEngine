#pragma once
class WorldBase;
class WorldBaseComponent
{
public:
	WorldBaseComponent(WorldBase* parent);
	virtual ~WorldBaseComponent() = default;
	virtual void InitComponent() {}
	virtual void EndComponent() {}
	void Update(double delta) {};
protected:
	WorldBase* _parent;
};