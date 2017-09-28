#! /usr/bin/python3
#units  cm kg s (pas for E, beta pas/cm, beta kg/(s*cm^2) )
from numpy import *
import sys
sys.path.append("/home/wang/bloodflow/py_lib")
from network_def import *

Conect = array([])
Entree = 1
Sorties = array( [1,] ) 
  
Rt = array( [0.0,] )

R_ref = array( [1.470,] )
  
h = array( [0.2,] )
  
E = array( [3.0/4.0*1.7*0.1,] ) * 1e5 
  
A_ref=pi*R_ref**2
 
beta=4.0/3.0*E*h/sqrt(pi)/R_ref**2

L=array( [350,] )     # length of the vessels,
 
rho = 1.050e-3 

beta_cm=beta/100    #in kg/(s*cm^2)
c_ref = sqrt(0.5* beta_cm / rho * sqrt(A_ref))
print(c_ref)
L_ref = L / c_ref
N= array([4*800,]) #2 * floor(L_ref/min(L_ref))
phi=000.0  #5000,
C_v=2.0 / 3.0 * sqrt(pi) * phi * h / sqrt(A_ref) / rho
  
NbrArt=len(L)


arts=[artery(0)]
for i in [0]:
	arts[i].L=L[i]
	arts[i].ave_dia=R_ref[i]*2
	arts[i].A_ref=pi*R_ref[i]**2
	arts[i].h=h[i]
	arts[i].E=E[i]
	arts[i].beta=beta[i]
	arts[i].C_v=C_v[i]
	arts[i].fric=40	
	arts[i].R_ref=R_ref[i]
	arts[i].N=N[i]
	
	arts[i].outPut=[0]
	for t in range(1,1000+1):
		arts[i].outPut.append(int(t*0.001*N[i])-1)

conjs=[conjunc(0),conjunc(1)]
arts[0].reFlec=0;
arts[0].headPt=conjs[0]			
arts[0].tailPt=conjs[1]			

net1=network(ARTS=arts,CONS=conjs)

t_final = 4 
dt=4e-5
timeSteps = int(t_final/dt)
tt=linspace(0,t_final,timeSteps)
Q_c=1 
Q_Input = Q_c * maximum( sin(2*pi/0.8*tt), 0)
Q_Input[(tt > 0.8)] = 0


tS=timeSetup()
tS.t_final=t_final
tS.dt=dt
tS.t_start=0
tS.t_final=t_final
tS.tt=tt
tS.inFlow_Q=Q_Input


net1=network(ARTS=arts,CONS=conjs)
#net1.plot_fig_nwt()
net1.tS=tS
net1.writeParam('../parameters')


