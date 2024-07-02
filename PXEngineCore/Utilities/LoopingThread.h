#pragma once
#include <atomic>
#include <memory>
#include <thread>
class LoopingThread
{
public:
	virtual void Run() = 0;
	void Wait();
	void Start();
	void Terminate();
	virtual ~LoopingThread() = default;
private:
	void Runner();
protected:
	std::atomic_bool _thrFlag{ true };
	std::unique_ptr<std::thread> _thr;
};