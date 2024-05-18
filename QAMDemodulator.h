#ifndef QAMDEMODULATOR_H
#define QAMDEMODULATOR_H

#include <vector>
#include <complex>
#include "QAMTypes.h"

class QAMDemodulator {
public:
    QAMDemodulator(QAMType type);
    std::vector<int> demodulate(const std::vector<std::complex<double>>& symbols);

private:
    QAMType qamType;
    int bitsPerSymbol;
    void initialize();
};

#endif // QAMDEMODULATOR_H
