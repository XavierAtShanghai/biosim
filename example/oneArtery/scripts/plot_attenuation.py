#! /usr/bin/python
import numpy as np
import matplotlib.pyplot as plt

L = 350
nu = 1e-2         #kinematic  viscocity of the blood  cm/s
Kr = 40 * nu * np.pi

h = 2e-1         # thickness of the vessel;
E = 3.0 / 4.0 * 1.7e4           # elatisity modulus;
rho = 0.1050
R0 = 1.470
A_ref = np.pi * R0 ** 2

t_final = 4 
dt=4e-5
timeSteps = int(t_final/dt)
tt = np.linspace(0,t_final,timeSteps)
anly = np.exp(-0.5 * Kr / A_ref *(tt-0.2))
histQ = np.genfromtxt('../data/histQ.csv',delimiter=',')

plt.plot(histQ[:,0],histQ[:,1], histQ[:,0], histQ[:,2],histQ[:,0],histQ[:,3],histQ[:,0],histQ[:,4],histQ[:,0],histQ[:,5],tt, anly)     
plt.xlabel('time(s)');
plt.ylabel('Flux');
plt.savefig("../figures/attenuation.png")
