import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d

def f(x, y):
    return np.exp(-(x**2+y**2))

xmin=-20.0
xmax=20.0
ymin=-20.0
ymax=20.0

nx=32
ny=32
dx=(xmax-xmin)/(nx-1)
dy=(ymax-ymin)/(ny-1)

s=np.zeros((nx,ny))
xa=np.zeros(nx)
ya=np.zeros(ny)
for i in range(nx):
    for j in range(ny):
        s[i][j]=f(xmin+i*dx,ymin+j*dy)
        ya[i]=ymin+j*dy
    xa[i]=xmin+i*dx
nft=np.fft.fft2(s, norm='ortho')

kxa=np.fft.fftfreq(nft.shape[0], d=dx)
kya=np.fft.fftfreq(nft.shape[1], d=dy)
kxa=1*2*np.pi*kxa
kya=1*2*np.pi*kya

fact=np.exp(-1j*kxa*xmin)*np.exp(-1j*kya*ymin)
aft=dx*dy*np.sqrt(nx/(2.0*np.pi))*np.sqrt(ny/(2.0*np.pi))*fact*nft

X,Y=np.meshgrid(kxa, kya)
Z=np.abs(aft)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(X, Y, Z)
plt.show()

