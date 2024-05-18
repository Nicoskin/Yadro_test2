#include "GaussianNoise.h"

GaussianNoise::GaussianNoise(double var) : variance(var), distribution(0.0, sqrt(variance)) {}

void GaussianNoise::addNoise(std::vector<std::complex<double>>& symbols) {
    for (auto& symbol : symbols) {
        double noiseI = distribution(generator);
        double noiseQ = distribution(generator);
        symbol += std::complex<double>(noiseI, noiseQ);
    }
}
