#pragma once
#include <chrono>
class Stopwatch {
public:
	Stopwatch() = default;

	void start();
	void reset();

	unsigned long elapsedMilliseconds() const;
	double elapsedSeconds() const;

private:
	std::chrono::high_resolution_clock::time_point _timePoint;
};