#ifndef GAUSSIANNOISE_H
#define GAUSSIANNOISE_H

#include <vector>
#include <complex>
#include <random>

class GaussianNoise {
public:
    GaussianNoise(double variance);
    void addNoise(std::vector<std::complex<double>>& symbols);

private:
    double variance;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
};

#endif // GAUSSIANNOISE_H
