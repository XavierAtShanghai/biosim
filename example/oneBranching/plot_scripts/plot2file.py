#!/usr/bin/python
import matplotlib.pyplot as plt
import numpy as np
from numpy import *

h = array( [0.1, 0.1, 0.1] )*1e-2 
E = array( [0.4, 0.4, 0.4] ) * 1e6 
A_ref = array( [4, 1.5, 1.5] )*1e-4
R_ref = sqrt(A_ref / pi) 
beta=4.0/3.0 * E * h / sqrt(pi)/(R_ref ** 2)
L=array( [400, 200, 200] )*1e-2     # length of the vessels,
rho = 1.050e3 
c_ref = sqrt(0.5* beta / rho * sqrt(A_ref))
Z = rho * c_ref / A_ref   # characteristic impedence
invZ = 1.0 / Z
Refl = (invZ[0] - invZ[1] - invZ[2]) / sum(invZ)   # reflectio coefficient
Tr=2 * invZ[0] / sum(invZ)      # transmiss

histP=genfromtxt('../data/histP.csv',delimiter=',')
peak=max( histP[histP[:,0] < 0.8,1] )
ref = ones( (len(histP[:,0]), 1 )) * Refl
trs = ones( (len(histP[:,0]), 1 )) * Tr 
plt.plot(histP[:,0],histP[:,1]/peak,histP[:,0],histP[:,2]/peak,histP[:,0],ref,histP[:,0],trs)
plt.xlabel('time(s)')
plt.ylabel('pressure (kPa)')
plt.grid(True)
plt.legend(['parent','daughter'],loc = 'upper left')
plt.savefig('../figures/refelction.png')
print("pgn file written in ../figures/")
