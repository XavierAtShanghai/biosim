#!/usr/bin/python3
import numpy as np
import pickle
import sys
sys.path.append("/home/wang/bloodflow/py_lib")
from network_def import *

pickleName='converg_arts.pkl'
folder="../data"
fig_data="../data/fig_data.csv"

with open(pickleName,'rb') as fh:
	arts=pickle.load(fh)

num_sample=40
filePath=folder+"/histP.csv"
with open(filePath,'r') as fh:
	num_data=0
	for line in fh:
		num_data+=1
	num_end=num_data-1
	fh.seek(0)
	num_line=0
	samples=[int(num_end*i/(num_sample-1) ) for i in range(num_sample) ]

tem=np.genfromtxt(filePath,delimiter=",")
record=np.array([tem[s,:] for s in samples])
#Pasc2mmHG=0.007500617
#record=record*Pasc2mmHG

print(record)
print("number of samples=%d"%len(record))
for art in arts:
	for re in record:
		art.histP.append(list(re[art.ID*201+1 : 201*(art.ID+1)+1]))
	art.fill_middle_data_P()

with open(fig_data,'w') as fh:
	for art in arts:
		n=len(art.pos)
		for i in range(n):
			st="{0:8f}\t{1:8f}".format(art.pos[i][0],art.pos[i][1])
			for hP in art.histP[i]:
				st+="\t{0:010.8f}".format(hP)
			print(st,file=fh)
		print("\n",file=fh)
