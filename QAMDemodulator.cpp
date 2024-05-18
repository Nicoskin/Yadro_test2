#include "QAMDemodulator.h"
#include <cmath>

QAMDemodulator::QAMDemodulator(QAMType type) : qamType(type) {
    initialize();
}

void QAMDemodulator::initialize() {
    switch (qamType) {
        case QPSK:
            bitsPerSymbol = 2;
            break;
        case QAM16:
            bitsPerSymbol = 4;
            break;
        case QAM64:
            bitsPerSymbol = 6;
            break;
    }
}

std::vector<int> QAMDemodulator::demodulate(const std::vector<std::complex<double>>& symbols) {
    std::vector<int> bits;
    int M = 1 << bitsPerSymbol;

    for (const auto& symbol : symbols) {
        int I = std::round((symbol.real() + M - 1) / 2);
        int Q = std::round((symbol.imag() + M - 1) / 2);
        for (int j = bitsPerSymbol / 2 - 1; j >= 0; --j) {
            bits.push_back((I >> j) & 1);
            bits.push_back((Q >> j) & 1);
        }
    }

    return bits;
}
