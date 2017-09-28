#! /usr/bin/python
from numpy import *
import os
import matplotlib.pyplot as plt

L = 350
nu = 1e-2         #kinematic  viscocity of the blood  cm/s
Kr = 40 * nu * pi

h = 2e-1         # thickness of the vessel;
E = 3.0 / 4.0 * 1.7e4           # elatisity modulus;
rho = 1.050e-3 
R0 = 1.470
A_ref = pi * R0 ** 2
beta=4.0/3.0*E*h/sqrt(pi)/R0**2
beta_cm=beta/100    #in kg/(s*cm^2)
c_ref = sqrt(0.5* beta_cm / rho * sqrt(A_ref))

t_final = 4 
dt=4e-5
timeSteps = int(t_final/dt)
tt = linspace(0,t_final,timeSteps)

num_smpl_pts=1001
xx=linspace(0,350,num_smpl_pts)
anly = exp(-0.5 * Kr / A_ref *(xx/c_ref))

'''
with open("temp_anly.csv",'w') as fh:
	for i in range(len(xx)):
		print("%f\t%f"%(xx[i],anly[i]),file=fh)
'''

num_sample=50
folder="../data"
filePath=folder+"/histQ.csv"
'''
with open(filePath,'r') as fh:
	num_data=0
	for line in fh:
		num_data+=1
	num_end=num_data-1
	fh.seek(0)
	num_line=0
	samples=[int(num_end*i/(num_sample-1) ) for i in range(num_sample) ]

tem=genfromtxt(filePath,delimiter=",")
record=array([ tem[s,:] for s in samples ])

print(len(record[0]))
with open("temp_flux.csv",'w') as fh:
	for i in range(len(record[0][1:])):
		print("%f\t"%xx[i],end="", file=fh)
		for re in record:
			print("%f\t"%re[i+1], end="",file=fh)
		print(file=fh)

'''

bg='''
gnuplot <<_EOF
set terminal gif
dataFile="temp_flux.csv"
analyFile="temp_anly.csv"
#set title "speedUp with openMP" 
unset key
set xlabel "distance (cm)"
set ylabel "flux"
set style data lines
set arrow from graph 0.7,0.9 to graph 0.6,0.85 head filled
set label "analytical damping" at graph 0.7,0.9 offset 0,0.5
'''
os.system("rm ../figures/anim/*.gif")
for i in range(num_sample):
	st=""
	st+="set output \"../figures/anim/attenu_%02d.gif\" \n"%i 
	
	st+="plot [][0:1] dataFile u 1:%d, analyFile u 1:2 \n"%(i+2)
	st+="set o\n"
	st+="_EOF\n"
	cmd=bg+st
	print(cmd)
	os.system(cmd)
mkAnim="convert -delay 20 -loop 0 ../figures/anim/*.gif ../attenuation.gif"
os.system(mkAnim)
