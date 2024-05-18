#ifndef QAMMODULATOR_H
#define QAMMODULATOR_H

#include <vector>
#include <complex>
#include "QAMTypes.h"

class QAMModulator {
public:
    QAMModulator(QAMType type);
    std::vector<std::complex<double>> modulate(const std::vector<int>& bits);

private:
    QAMType qamType;
    int bitsPerSymbol;
    void initialize();
};

#endif // QAMMODULATOR_H
