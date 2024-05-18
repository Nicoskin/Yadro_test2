#include "QAMModulator.h"
#include <cmath>

QAMModulator::QAMModulator(QAMType type) : qamType(type) {
    initialize();
}

void QAMModulator::initialize() {
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

std::vector<std::complex<double>> QAMModulator::modulate(const std::vector<int>& bits) {
    std::vector<std::complex<double>> symbols;
    int M = 1 << bitsPerSymbol;
    int k = 0;

    for (size_t i = 0; i < bits.size(); i += bitsPerSymbol) {
        int I = 0, Q = 0;
        for (int j = 0; j < bitsPerSymbol / 2; ++j) {
            I = (I << 1) | bits[i + j];
            Q = (Q << 1) | bits[i + j + bitsPerSymbol / 2];
        }
        I = 2 * I - M + 1;
        Q = 2 * Q - M + 1;
        symbols.emplace_back(I, Q);
    }

    return symbols;
}
