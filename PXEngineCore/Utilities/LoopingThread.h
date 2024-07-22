#pragma once
#include <atomic>
#include <memory>
#include <thread>
class LoopingThread
{
public:
	virtual ~LoopingThread();
	virtual void Run() = 0;
	void Wait();
	void Start();
	void Terminate();
private:
	void Runner();
protected:
	std::atomic_bool _thrFlag{ true };
	std::unique_ptr<std::thread> _thr;
};