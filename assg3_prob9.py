import numpy as np
import matplotlib.pyplot as pt

def f(x):
 if abs(x)<=1.0:
  return(1.0)
 else:
  return(0.0)
def g(x):
 if abs(x)<=1.0:
  return(1.0)
 else:
  return(0.0)
 
n=int(2**7)
x_min=-1.5
x_max=4.5
dx=(x_max-x_min)/(n-1)

x=np.linspace(x_min,x_max,n) 
X1=[]
X2=[]

for i in x:
 X1+=[f(i)] 
 X2+=[g(i)]
Y1=np.hstack((X1,np.zeros(n)))
Y2=np.hstack((X2,np.zeros(n)))

K1=np.fft.fft(Y1,norm="ortho")
K2=np.fft.fft(Y2,norm="ortho")

K=K1*K2
Y=np.fft.ifft(K,norm="ortho")

Y=Y*dx*np.sqrt(2*n)
x_prime=np.linspace(2*x_min,x_min+x_max,n) 

pt.plot([-3,-1,-1,1,1,3],[0,0,1,1,0,0],'g--',label="box function")
pt.plot(x_prime,Y[:n],'rx',label="numerical convolution")
pt.xlabel("x")
pt.ylabel("y")
pt.legend()
pt.show()
