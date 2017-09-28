#!/usr/bin/python3
from numpy import *
dat1=linspace(0,400,200)
line1=[ (i,0) for i in dat1 ]
line4=[ (i+600,0) for i in dat1 ]

angle=linspace(2*pi,0,200)
print(angle) 
R=100
line2=[( 500+R*cos(i),R*sin(i) ) for i in angle ]
line3=[( 500+R*cos(i),-R*sin(i) ) for i in angle ]

with open("lines.csv","w") as fh:
	for line in (line1,line2, line3, line4):
		for pt in line:
			print("%f\t%f"%(pt[0],pt[1]),file=fh)
		print('\n',file=fh)


