#include "QAMModulator.h"
#include "GaussianNoise.h"
#include "QAMDemodulator.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

double calculateBER(const std::vector<int>& transmittedBits, const std::vector<int>& receivedBits) {
    int errorCount = 0;
    for (size_t i = 0; i < transmittedBits.size(); ++i) {
        if (transmittedBits[i] != receivedBits[i]) {
            ++errorCount;
        }
    }
    return static_cast<double>(errorCount) / transmittedBits.size();
}

void simulateQAM(QAMType qamType, const std::vector<int>& bits, const std::vector<double>& snrValues, std::ofstream& outFile) {
    QAMModulator modulator(qamType);
    QAMDemodulator demodulator(qamType);

    std::vector<std::complex<double>> modulatedSymbols = modulator.modulate(bits);

    for (double snr : snrValues) {
        double noiseVariance = pow(10, -snr / 10.0);
        GaussianNoise noise(noiseVariance);
        std::vector<std::complex<double>> noisySymbols = modulatedSymbols;
        noise.addNoise(noisySymbols);

        std::vector<int> receivedBits = demodulator.demodulate(noisySymbols);

        double ber = calculateBER(bits, receivedBits);
        outFile << qamType << "," << snr << "," << ber << std::endl;
        std::cout << "Modulation: " << qamType << ", SNR: " << snr << ", BER: " << ber << std::endl;
    }
}

int main() {
    std::vector<int> bits(1000000);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int& bit : bits) {
        bit = dis(gen);
    }

    std::vector<double> snrValues = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
    std::ofstream outFile("ber_results.txt");

    simulateQAM(QPSK, bits, snrValues, outFile);
    simulateQAM(QAM16, bits, snrValues, outFile);
    simulateQAM(QAM64, bits, snrValues, outFile);

    outFile.close();
    return 0;
}
