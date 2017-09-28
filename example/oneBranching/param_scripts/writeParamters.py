#! /usr/bin/python
#units  m kg s
from numpy import *
Conect = array([1, 2, 3])  #connetivity of the network
Entree = 1
Sorties = array( [2, 3] ) 
  
Rt = array( [0.0, 0.0] )
 
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
print(Refl)
print(Tr)  
L_ref = L / c_ref
N= array([400,200, 200]) * 4 
phi=000.0  #5000,
C_v=2.0 / 3.0 * sqrt(pi) * phi * h / sqrt(A_ref) / rho  
NbrArt=len(L)

folder = '../param'
fileName = folder +'/systemic_network.csv'
fileHandle = open(fileName,'w')

fileHandle.write("{0},{1},{2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}\n".format('number','<R0>(cm)',  '<A0> (cm^2)', '<Thickness> (cm)',  '<Length>(cm)', '<N>(mesh points)', '<E>(10^6 Pa)', 
    '<beta>(10^6 Pa/cm)', '<Cv>(10^4 cm^2/s)', '<fric>', '<solver>', '<order>') )
for iter in range(NbrArt): 
	fileHandle.write("{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11}\n".format(iter-1, 1e2*R_ref[iter],  1e4*A_ref[iter], 1e2*h[iter],  1e2*L[iter], N[iter],
	 E[iter]*1e-6, beta[iter]*1e-8, C_v[iter], 0, 'FV', 2 ) )
fileHandle.close()


#the number of node starts from 0 

DAG=zeros((NbrArt,2),int)
DAG[0,:]= [0, 1]
numArt = 1
if Conect.ndim ==  1 & len(Conect) > 0:
	DAG[numArt,:] = [Conect[0], Conect[1] ]
	numArt = numArt + 1
	if ( Conect[2] > 0 ):               #if the are two arteries at the conj, it should be Conect(itr, 3) = -1
		DAG[numArt,:] = [Conect[0], Conect[2] ]
		numArt = numArt + 1
elif Conec.ndim == 2:
	for itr in range( len( Conect[:,0]) ):
		DAG[numArt,:] = [Conect[itr,0], Conect[itr,1] ]
		numArt = numArt + 1
		if ( Conect[itr,2] > 0 ):               #if the are two arteries at the conj, it should be Conect(itr, 3) = -1
			DAG[numArt,:] = [Conect[itr,0], Conect[itr,2] ]
			numArt = numArt + 1
DAG = DAG[ argsort(DAG[:,1] ), : ]    # to make row number of the record corresponds to the artery number
fileDAG=folder+'/DAG.csv'
fileHandle = open( fileDAG, 'w')
for itr in range(NbrArt):
	fileHandle.write("{0},{1} \n".format( DAG[itr,0], DAG[itr,1] ))
fileHandle.close()
 
# write leavesReflect file

fileName = folder+'/leavesReflect.csv'

fileHandle = open( fileName, 'w')
for itr in range( len(Sorties) ):
	fileHandle.write("{0},{1} \n".format( Sorties[itr], Rt[itr]) )
fileHandle.close()
 
# write leavesReflect file

fileName=folder+'/leavesReflect.csv'
fileHandle = open (fileName, 'w')
for itr in range( len( Sorties) ):
	fileHandle.write("{0},{1} \n".format(Sorties[itr], Rt[itr] ) )
fileHandle.close()
 
inputFile=folder + '/output.csv'
fileHandle = open(inputFile, 'w')
fileHandle.write("{0},{1} \n".format('#<numArtery>', '<numMeshPoint>'))
for itr in range( len(N) ):
	fileHandle.write("{0},{1} \n".format( itr, int(0.5*N[itr] )) )
fileHandle.close()

pulse = 0.8 
t_final = pulse * 2 
dt=4e-5
timeSteps = int(t_final/dt)
tt=linspace(0,t_final,timeSteps)
Q_c=1 #500,   ml/s
Q_Input = Q_c * maximum( sin(2*pi/0.8*tt), 0)
Q_Input [tt >0.8] = 0

fileName = folder+'/timeSetup.csv'
fileHandle = open(fileName,'w')
fileHandle.write("{0},{1},{2},{3},{4},{5} \n".format('<t_final>(s)', '<t_step> (s)', '<record_start>','<record_end>', '<slover>(FV=1MC=2)', '<order>(for FV)') )
fileHandle.write("{0},{1},{2},{3},{4},{5} \n".format(t_final, dt, 0, t_final, 1, 2) )
fileHandle.close() 

inputFile=folder + '/input.csv'
fileHandle = open(inputFile, 'w')
fileHandle.write("{0},{1}\n".format('#<time>', '<Q_Input>(cm^/s)'))
for itr in range(timeSteps):
	fileHandle.write("{0},{1}\n".format(tt[itr], Q_Input[itr]) )
fileHandle.close()
