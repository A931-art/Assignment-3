import numpy as np
import matplotlib.pyplot as plt

def DFT(function_array):
    N = len(function_array)
    Fourier_array = []
    for m in range(N):
        f = 0
        for n in range(N):
            f += function_array[n] * np.exp(- 2j *np.pi * m * n / N)
        Fourier_array.append(f / (np.sqrt(N)))
    return Fourier_array

x_min = -10.0 
x_max = 10.0
number_of_points = 256 
delta = (x_max-x_min)/(number_of_points-1)
function_array = np.zeros(number_of_points)
x_arr = np.zeros(number_of_points)
for i in range(number_of_points):
        function_array[i] = 1
        x_arr[i] = x_min+i*delta
nft =  DFT(function_array)
karr =2*np.pi* np.fft.fftfreq(number_of_points, d=delta)
fact = np.exp(-1j * karr * x_min)
aft = delta * np.sqrt(number_of_points/(2.0*np.pi)) * fact * nft 

fig1=plt.subplots()
#plt.subplot(2,2,1)
plt.plot(x_arr,function_array,'r',label='The constant function')
plt.xlabel('x',fontsize=16)
plt.ylabel('f(x)',fontsize=16)
plt.grid(True)

fig2=plt.subplots()
#plt.subplot(2,2,2)
plt.plot(karr,aft,'g', label='The fourier transform of the constant function')
plt.xlabel('k',fontsize=16)
plt.ylabel('g(k)',fontsize=16)
plt.grid(True)
plt.show()
