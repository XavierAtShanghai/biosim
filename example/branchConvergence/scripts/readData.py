#!/usr/bin/python3
import numpy as np
from sys import stderr
import sys
sys.path.append("/home/wang/bloodflow/py_lib")
from network_def import *
import pickle

dat1=linspace(0,400,200)
line0=[ [i,0] for i in dat1 ]
line3=[ [i+600,0] for i in dat1 ]

angle=linspace(pi,0,200)
R=100
line1=[[ 500+R*cos(i),R*sin(i) ] for i in angle ]
line2=[[ 500+R*cos(i),-R*sin(i) ] for i in angle ]


arts=[]
NbrArts=4
for ID in range(NbrArts):
	art=artery(ID)
	arts.append(art)	
arts[0].pos=line0
arts[1].pos=line1
arts[2].pos=line2
arts[3].pos=line3


#with open("converge_arts.csv",'w') as fh:
#	for art in arts:
#		for pt in art.pos:
#			print("%f\t%f\t%f"%(pt[0],pt[1],0),file=fh)
#		print('\n', file=fh)

with open("converg_arts.pkl",'wb') as fh:
	pickle.dump(arts,fh)
