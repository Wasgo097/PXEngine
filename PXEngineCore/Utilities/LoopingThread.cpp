#include "LoopingThread.h"

LoopingThread::~LoopingThread()
{
	Terminate();
	Wait();
}

void LoopingThread::Wait()
{
	if (!_thr)
		return;
	if (_thr->joinable())
		_thr->join();
}

void LoopingThread::Start()
{
	_thr = std::make_unique<std::thread>(&LoopingThread::Runner, this);
}

void LoopingThread::Terminate()
{
	_thrFlag = false;
}

void LoopingThread::Runner()
{
	while (!_thrFlag)
		Run();
}