import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("ber_results.txt", header=None, names=["Modulation", "SNR", "BER"])

modulations = {0: "QPSK", 1: "QAM16", 2: "QAM64"}
colors = {0: 'r', 1: 'g', 2: 'b'}

plt.figure(figsize=(10, 6))

for mod_type, mod_name in modulations.items():
    mod_data = data[data["Modulation"] == mod_type]
    plt.plot(mod_data["SNR"], mod_data["BER"], marker='o', color=colors[mod_type], label=mod_name)

plt.xlabel('SNR (dB)')
plt.ylabel('Bit Error Rate (BER)')
plt.yscale('log')
plt.title('BER vs. SNR for QPSK, QAM16, and QAM64')
plt.legend()
plt.grid(True)
plt.show()
