import numpy as np
import matplotlib.pyplot as plt

file=open('noise.txt','r')

data=np.loadtxt('noise.txt', dtype=float)
fig1 = plt.subplots()
plt.plot(data, 'r', label='The noise')
plt.legend()
plt.grid(True)

dft=np.fft.fft(data)
karr=np.fft.fftfreq(data.size, d=1)

karr=karr[np.argsort(karr)]
sdft=dft[np.argsort(karr)]

fig2 = plt.subplots()
plt.plot(sdft, 'g', label='The DFT of the noise')
plt.legend()
plt.grid(True)

spectra=abs(sdft)*abs(sdft)/(data.size)

fig3 = plt.subplots()
plt.plot(spectra, 'y', label='Spectra')
plt.legend()
plt.grid(True)

bin=10
fig4 = plt.subplots()
plt.hist(spectra,bin, facecolor='m',label='binned power spectrum')
plt.legend()
plt.grid(True)
plt.show()
