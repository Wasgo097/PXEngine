#pragma once
#include "Settings/EngineBaseSettings.h"
#include "Settings/WindowSettings.h"
#include "Utilities/ArgumentParser.h"
#include "Utilities/Stopwatch.h"
#include "WorldBase.h"
#include <memory>
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>
class EngineBase
{
public:
	EngineBase(ArgumentParser&& parser);
	EngineBase(const EngineBase&) = delete;
	EngineBase& operator=(const EngineBase&) = delete;
	EngineBase(EngineBase&&) = delete;;
	EngineBase& operator=(EngineBase&&) = delete;
	virtual ~EngineBase();
	int Run();
	void PushNewWorld(std::unique_ptr<WorldBase>&& newWorld);
private:
	void ServiceInput();
	void Update();
	void Render();
	void ManageWorlds();
	void Close();
	virtual void InitEngine();
	virtual std::unique_ptr<WorldBase> InitWorld() = 0;
protected:
	ArgumentParser _parser;
	Stopwatch _engineStopWatch;
	EngineBaseSettings _engineSettings;
	WindowSettings _windowSettings;
	std::queue<std::unique_ptr<WorldBase>> _worlds;
	std::unique_ptr<sf::RenderWindow> _window;
	sf::View _view;
};