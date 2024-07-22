#pragma once
#include "Core/EngineBase.h"
class TestEngine :public EngineBase
{
public:
	TestEngine(ArgumentParser&& parser);
protected:


	// Inherited via EngineBase
	std::unique_ptr<WorldBase> InitWorld() override;

};