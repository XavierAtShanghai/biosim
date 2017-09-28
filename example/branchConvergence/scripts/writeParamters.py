#! /usr/bin/python3
#units  cm kg s
from numpy import *
import sys
sys.path.append("/home/wang/bloodflow/py_lib")
from network_def import *
import pickle
Conect = array([1, 2, 3])  #connetivity of the network
Entree = 1
Sorties = array( [3], ) 
  
Rt = array( [0.0] )
 
h = array( [0.1, 0.1, 0.1, 0.1] )
E = array( [0.4, 0.4, 0.4, 0.4] ) * 1e6 
A_ref = array( [4, 2, 2, 4] )
R_ref = sqrt(A_ref / pi) 
beta=4.0/3.0 * E * h / sqrt(pi)/(R_ref ** 2)
L=array( [400, 200, 200, 400] )     # length of the vessels,
rho = 1.050e-3
beta_cm=beta/100.0 #pas/cm = kg/(s*m*cm)-> kg/(s*cm^2)
c_ref = sqrt(0.5* beta_cm / rho * sqrt(A_ref))
Z = rho * c_ref / A_ref   # characteristic impedence
invZ = 1.0 / Z
Refl = (invZ[0] - invZ[1] - invZ[2]) / sum(invZ[:3])   # reflectio coefficient
Tr=2 * invZ[0] / sum(invZ[:3])      # transmiss
Tr2= 2* 2 * invZ[1] / sum(invZ[:3])
print("Tr2 is %f" %Tr2)

print(Refl)
print(Tr)  
L_ref = L / c_ref

N= array([400,200, 200,400]) * 4 
phi=000.0  #5000,
C_v=2.0 / 3.0 * sqrt(pi) * phi * h / sqrt(A_ref) / rho  
NbrArt=len(L)


pickleName='converg_arts.pkl'

with open(pickleName,'rb') as fh:
	arts=pickle.load(fh)


for i in range(NbrArt):
	arts[i].L=L[i]
	arts[i].A_ref=A_ref[i]
	arts[i].h=h[i]
	arts[i].E=E[i]
	arts[i].beta=beta[i]
	arts[i].C_v=0
	arts[i].fric=0
	arts[i].N=N[i]
	arts[i].outPut=[0]
	for t in range(1,201):
		arts[i].outPut.append(int(t*0.005*N[i])-1)


arts[0].daughterArts=[arts[1],arts[2]]
arts[1].daughterArts=[arts[3]]
arts[2].daughterArts=[arts[3]]
arts[3].reFlec=0

conjs=[conjunc(i) for i in range(NbrArt)]
arts[0].headPt=conjs[0]
arts[0].tailPt=conjs[1]

arts[1].headPt=conjs[1]
arts[1].tailPt=conjs[2]

arts[2].headPt=conjs[1]
arts[2].tailPt=conjs[2]

arts[3].headPt=conjs[2]
arts[3].tailPt=conjs[3]

pulse = 0.8 
t_final = pulse * 3 
dt=4e-5
timeSteps = int(t_final/dt)
tt=linspace(0,t_final,timeSteps)
Q_c=1 #500,   ml/s
Q_Input = Q_c * maximum( sin(2*pi/0.8*tt), 0)
Q_Input [tt >0.8] = 0

tS=timeSetup()
tS.t_final=t_final
tS.dt=dt
tS.t_start=0
tS.t_final=t_final
tS.tt=tt
tS.inFlow_Q=Q_Input

net1=network(ARTS=arts,CONS=conjs)
net1.tS=tS
net1.writeParam("../param")


