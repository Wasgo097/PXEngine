#include "Randomizer.h"

Randomizer::Randomizer() : _device(), _engine(_device()) {}

int Randomizer::Random(int min, int max) {
	if (max < min)
		std::swap(min, max);
	std::uniform_int_distribution<int> uniDist(min, max);
	return uniDist(_engine);
}

double Randomizer::Random(double min, double max) {
	if (max < min)
		std::swap(min, max);
	std::uniform_real_distribution<double> uniDist(min, max);
	return uniDist(_engine);
}
