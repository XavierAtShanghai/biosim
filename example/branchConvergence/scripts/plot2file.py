#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
from numpy import *


h = array( [0.1, 0.1, 0.1, 0.1] )
E = array( [0.4, 0.4, 0.4, 0.4] ) * 1e6 
A_ref = array( [4, 2, 2, 4] )
R_ref = sqrt(A_ref / pi) 
beta=4.0/3.0 * E * h / sqrt(pi)/(R_ref ** 2)
L=array( [400, 200, 200, 400] )     # length of the vessels,
rho = 1.050e-3
beta_cm=beta/100.0 
c_ref = sqrt(0.5* beta_cm / rho * sqrt(A_ref))

print(c_ref)
Z = rho * c_ref / A_ref   # characteristic impedence
invZ = 1.0 / Z
sum_invZ=sum(invZ[0:3] )
Refl = (invZ[0] - invZ[1] - invZ[2]) / sum_invZ   # reflectio coefficient
Tr=2 * invZ[0] / sum_invZ      # transmiss
Tr2= 2* 2 * invZ[1] / sum_invZ

histP=genfromtxt('../data/histP.csv',delimiter=',')
peak=max( histP[histP[:,0] < 0.8,1] )
ref = ones( (len(histP[:,0]), 1 )) * Refl
trs1 = ones( (len(histP[:,0]), 1 )) * Tr
trs2 = ones( (len(histP[:,0]), 1 )) * Tr2 * Tr
print([Refl,Tr,Tr2])

num_sample=201
pos_plt=(num_sample+1)/2
plt.plot(histP[:,0],histP[:,1+pos_plt]/peak,'--',histP[:,0],histP[:,1+num_sample+pos_plt]/peak,'-.',histP[:,0],histP[:,3*num_sample+pos_plt]/peak,':',histP[:,0],ref,histP[:,0],trs1,histP[:,0],trs2)
plt.xlabel('time(s)')
plt.ylabel('pressure')
#plt.grid(True)
plt.legend(['artery-1','artery-2','artery-3'],loc = 'lower left') 
plt.autoscale(axis='x',tight=True)
#plt.savefig('../figures/refelction.png')
desti='/home/wang/paper_HPC/figures/refelction.png'
plt.savefig(desti)
print("figure was writen as"+desti) 
