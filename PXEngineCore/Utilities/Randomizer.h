#pragma once
#include <random>
class Randomizer {
public:
	Randomizer();
	int Random(int min, int max);
	double Random(double min, double max);
private:
	std::random_device _device;
	std::default_random_engine _engine;
};