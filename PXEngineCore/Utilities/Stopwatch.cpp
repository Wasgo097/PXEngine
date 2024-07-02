#include "Stopwatch.h"

void Stopwatch::reset() 
{
    _timePoint = std::chrono::high_resolution_clock::now();
}

unsigned long Stopwatch::elapsedMilliseconds() const 
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _timePoint).count();
}

double Stopwatch::elapsedSeconds() const 
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - _timePoint).count();
}