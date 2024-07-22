#include "TestEngine.h"

TestEngine::TestEngine(ArgumentParser&& parser) :EngineBase(std::move(parser))
{
}

std::unique_ptr<WorldBase> TestEngine::InitWorld()
{
	return std::unique_ptr<WorldBase>();
}
