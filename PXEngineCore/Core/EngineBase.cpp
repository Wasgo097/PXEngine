#include "EngineBase.h"
#include "Settings/SettingsSerializer.h"
EngineBase::EngineBase(ArgumentParser&& parser) :_parser{ std::move(parser) }
{
	SettingsSerializer serializer("cfg\\");
	if (auto engineSettings = serializer.CreateSettings<EngineBaseSettings>("engineSettingsBase.json"))
	{
		_engineSettings = *engineSettings;
		if (auto windowSettings = serializer.CreateSettings<WindowSettings>(_engineSettings.windowSettingsPath))
			_windowSettings = *windowSettings;
		_window = std::make_unique<sf::RenderWindow>(_windowSettings.videoMode, _windowSettings.windowName, _windowSettings.displayStyle);
		_window->setVerticalSyncEnabled(_windowSettings.vsync);
	}
}

EngineBase::~EngineBase()
{
	Close();
}

int EngineBase::Run()
{
	InitEngine();
	bool run{ _window->isOpen() && !_worlds.empty() };
	while (run)
	{
		ServiceInput();
		Update();
		Render();
		ManageWorlds();
		run = _window->isOpen() && !_worlds.empty();
	}
	return 0;
}

void EngineBase::PushNewWorld(std::unique_ptr<WorldBase>&& newWorld)
{
	if (newWorld)
		_worlds.push(std::move(newWorld));
}

void EngineBase::Close()
{
	if (_window->isOpen())
		_window->close();
}

void EngineBase::Render()
{
	if (!_window->isOpen())
		return;
	_window->setView(_view);
	_window->clear();
	_worlds.front()->Draw(*_window);
	_window->display();
}

void EngineBase::Update()
{
	_worlds.front()->Update(_engineStopWatch.elapsedSeconds());
	_engineStopWatch.reset();
}

void EngineBase::ServiceInput()
{
	sf::Event action;
	while (_window->pollEvent(action))
	{
		if (action.type == sf::Event::Closed)
		{
			_worlds.front()->EndWorld();
			Close();
		}
	}
}

void EngineBase::InitEngine()
{
	PushNewWorld(InitWorld());
	_worlds.front()->InitWorld();
}

void EngineBase::ManageWorlds()
{
	if (_worlds.front()->Quit())
	{
		_worlds.front()->EndWorld();
		_worlds.pop();
		if (!_worlds.empty())
			_worlds.front()->InitWorld();
		else
			Close();
	}
}