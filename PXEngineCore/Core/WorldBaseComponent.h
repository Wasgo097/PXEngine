#pragma once
class WorldBaseComponent
{
public:
	virtual ~WorldBaseComponent() = default;
	virtual void InitComponent() {}
	virtual void EndComponent() {}
	void Update(double delta);
};

