###########################################
#Author: Janki Bhimani
#Sample run command: python MakeDict.py ../data/6mysql nvme0n1 /FreqSeqRecCoh/
###########################################

from collections import Counter
import re

import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import sys
import matplotlib.ticker as ticker
import plotly.plotly as py
import os
from itertools import chain


a0=[]
a1=[]
a2=[]
a3=[]
a4=[]
a5=[]
a6=[]
a7=[]
a8=[]
a9=[]
a12=[]
a13=[]
p1=[]
p2=[]
p3=[]
p4=[]
b1=[]
b1f=[]
Totlbainsec=[]
d ={}
d1={}
i=0
FRE=0
SEQ=0
prev=0
Tottime=0
beta=0
l = [0]*16
incom1=sys.argv[1]
incom2=sys.argv[2]
if not os.path.exists(sys.argv[1]+sys.argv[3]):
	os.mkdir(sys.argv[1]+sys.argv[3], 777 )
if not os.path.exists(sys.argv[1]+sys.argv[3]+sys.argv[2]):
	os.mkdir(sys.argv[1]+sys.argv[3]+sys.argv[2], 777 )
infile=open(sys.argv[1]+'/blktrace_'+sys.argv[2]+'.log')
infile1=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/streams_'+sys.argv[2]+'.log','wr+')
outfile=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/write_blktrace_'+sys.argv[2]+'.log','wr+')
freqfile=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/write_freq_blktrace_'+sys.argv[2]+'.log','wr+')
points=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/write_points_blktrace_'+sys.argv[2]+'.log','wr+')
kmeansin=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/kmeans_input_'+sys.argv[2]+'.log','wr+')
pointsstream=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/points_stream_'+sys.argv[2]+'.log','wr+')
file1=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/file1.log','w')
file2=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/file2.log','w')
file3=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/file3.log','w')
file4=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/file4.log','w')
dictionary=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/dictionary.log','w')
for line in infile:
	line_words=(line.split(',') )
	a0.append(line_words[0])
	a1.append(int(line_words[1]))
	a2.append(int(line_words[2]))
	if line_words[0] == 'W' or line_words[0] == 'WS' or line_words[0] == 'WSM':
		a3.append(int(line_words[1])) #LBA
		a4.append(int(line_words[2])) #size
		a5.append(int(line_words[3])) #Time
		Tottime=int(line_words[3])
		#print int(line_words[1])
		if int(line_words[1]) in l:
			SEQ=1
			a12.append(int(line_words[1]))
		else:
			SEQ=0
		prev = int(line_words[1]) + int(line_words[2])
		l.append(prev)                         # add 'x' to right side of list
		l = l[-16:]
		outfile.writelines( str(line_words[1]) + ',' + str(line_words[2]) + ',' + str(line_words[3]))
		p2.append(int(SEQ))
		#points.writelines( str(SEQ) +'\n' )
		prev = int(line_words[1]) + int(line_words[2])
"""
xv = np.array(a5)
yv = np.array(a3)
fig = plt.figure(figsize=(100,50))

plt.figure(1)
plt.plot(xv,yv,'.')
plt.savefig("RUN1-4containers/plot1.png")

"""
TottimeCount=Counter(a5)
#Tottime1= TottimeCount.items()
#print Tottime1
#print len(list(TottimeCount))
beta=sum(TottimeCount.values())/len(list(TottimeCount)) #average number of LBAs accessed in 1sec
#print sum(TottimeCount.values())
#print len(a5)
print beta #average number of LBAs accessed in one second
print sum(TottimeCount.values())

for item in TottimeCount:
	if TottimeCount[item] <= beta: #if # unique LBAs accessed in that sec is less than beta
		Totlbainsec.append(int(item))
#print TottimeCount.values()
#print Totlbainsec
for (k1,v1) in zip(a5,a3):
	if k1 in Totlbainsec:
		d1.setdefault(k1, [])
		if not v1 in d1[k1]:
			d1[k1].append(v1)
#print d1[0]

test=[]
test1=[]
d3={}
p=0
q=Tottime/10 # max length of queue is 10% of total time elements
r=2 # atleast 2 LBAs should match in 2 different time elelments
print 'len_d1'
print len(d1)
for z in range((Tottime/q)+1):
	for x in xrange(p,p+q,1):
		if x <= Tottime:
			#print x
			if x in d1:
#				print x
				for y in xrange(p,p+q,1):
					if y in d1:
						if (x!=y):
							#print x,y
#							print list(set(d1[x]).intersection(d1[y]))
							if len(list(set(d1[x]).intersection(d1[y]))) > r:
								test.append(list(set(d1[x]).intersection(d1[y])))
	p=p+q
map(test1.extend, test)
#print test
#print len(list(test))
#print len(list(test1))
Testcount=Counter(test1)
print len(list(Testcount))
#print Testcount
for item in Testcount.items():
	#print item[0]
	d3[item[0]]=item[0]


for (k,v) in zip(a3,a5):
	d.setdefault(k, [])
	if not v in d[k]:
		d[k].append(v)
	file1.writelines( str(v) + ',' + str(k) + '\n' )
#print (d)

counts = Counter(a3)
counts1= counts.items()
freqfile.writelines( str(counts) + '\n')
total=sum(counts.values())
unique=list(counts)
print ('Tottime/2')
print(Tottime/2)
print str('unique')
print len(unique)
#print len(list(counts1))

print str('total')
print total
ratio=float(len(unique))/float(total)
print ratio


#print counts1

for word in counts1:
        a8.append(word[0])
	if word[1] == 1:
		i=i+1
		FRE = 0
	else:
		a6.append(int(word[0]))
		FRE = 1
	p1.append(int(FRE))

	#print d[word[0]][-1]
	#print d[word[0]]
	if d[word[0]][-1] <= Tottime/2: #to get last ellement of the array (all the time at which LBA id=s accessed) in the array(different LBAs)
		p3.append(int(0))
	else:
		p3.append(int(1))

	if word[0] in d3:
		p4.append(int(1))
		#print word[0]
	else:
		p4.append(int(0))

print i
for item in zip(p1,p2,p3,p4):
	points.writelines( str(item) + '\n' )
points.close()

for i in a6:
        a7.append(d[i])

for i in range(len(a6)):        
	file3.writelines( str(a7[i]) + ',' + str(a6[i])+ '\n' )


for i in a12:
	a13.append(d[i])
	
for i in range(len(a12)):
	file2.writelines( str(a13[i]) + ',' + str(a12[i]) + '\n' )

points=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/write_points_blktrace_'+sys.argv[2]+'.log','r')
print str(sys.argv[3])
for word in points:
        #kmeansin.writelines(str(word[1])+','+str(word[4])+'\n') #freq+seq
        #kmeansin.writelines(str(word[1]) + '\n') #freq
        #kmeansin.writelines(str(word[4]) + '\n') #seq
        if str(sys.argv[3]) == '/Freq/':
        	kmeansin.writelines(str(word[1])+'\n') #freq
        elif str(sys.argv[3]) == '/Seq/':
        	kmeansin.writelines(str(word[4])+'\n') #seq
        elif str(sys.argv[3]) == '/Rec/':
        	kmeansin.writelines(str(word[7])+'\n') #rec
        elif str(sys.argv[3]) == '/Coh/':
        	kmeansin.writelines(str(word[10])+'\n') #coh
        elif str(sys.argv[3]) == '/FreqSeq/':
			kmeansin.writelines(str(word[1])+','+str(word[4])+'\n') #freq+seq
        elif str(sys.argv[3]) == '/FreqRec/':
			kmeansin.writelines(str(word[1])+','+str(word[7])+'\n') #freq+rec
        elif str(sys.argv[3]) == '/FreqCoh/':
			kmeansin.writelines(str(word[1])+','+str(word[10])+'\n') #freq+coh
        elif str(sys.argv[3]) == '/SeqRec/':
			kmeansin.writelines(str(word[4])+','+str(word[7])+'\n') #freq+seq+rec+coh
        elif str(sys.argv[3]) == '/SeqCoh/':
			kmeansin.writelines(str(word[4])+','+str(word[10])+'\n') #freq+seq+rec+coh
        elif str(sys.argv[3]) == '/RecCoh/':
			kmeansin.writelines(str(word[7])+','+str(word[10])+'\n') #freq+seq+rec+coh
        elif str(sys.argv[3]) == '/FreqSeqRec/':
			kmeansin.writelines(str(word[1])+','+str(word[4])+','+str(word[7])+'\n') #freq+seq+rec+coh
        elif str(sys.argv[3]) == '/FreqRecCoh/':
			kmeansin.writelines(str(word[1])+','+str(word[7])+','+str(word[10])+'\n') #freq+seq+rec+coh
        elif str(sys.argv[3]) == '/FreqSeqCoh/':
			kmeansin.writelines(str(word[1])+','+str(word[4])+','+str(word[10])+'\n') #freq+seq+rec+coh
        elif str(sys.argv[3]) == '/SeqRecCoh/':
			kmeansin.writelines(str(word[4])+','+str(word[7])+','+str(word[10])+'\n') #freq+seq+rec+coh
        elif str(sys.argv[3]) == '/FreqSeqRecCoh/':
			kmeansin.writelines(str(word[1])+','+str(word[4])+','+str(word[7])+','+str(word[10])+'\n') #freq+seq+rec+coh

kmeansin.close()

kmeansin=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/kmeans_input_'+sys.argv[2]+'.log','r')

cmdstring = "/home/j.bhimani/Downloads/blkexp/kmean_omp "+sys.argv[1]+sys.argv[3]+sys.argv[2]+"/kmeans_input_"+sys.argv[2]+".log "+sys.argv[1]+sys.argv[3]+sys.argv[2]+"/streams_"+sys.argv[2]+".log 5 10 %s" % (str(len(unique)))
os.system(cmdstring)


for line in infile1:
        line=(line.split(',') )
        a9.append(int(line[0]))

zipped = zip(a8,a9)
sortzipped= sorted(zipped, key= lambda x: x[0])
for item in sortzipped:
        pointsstream.writelines( str(item) + '\n' )

pointsstream.close()
pointsstream=open(sys.argv[1]+sys.argv[3]+sys.argv[2]+'/points_stream_'+sys.argv[2]+'.log','r')
for line in pointsstream:
	word=(re.split(r'[,( )]+',line))
#	print 'word'
	dictionary.writelines(str(word[1])+','+str(word[2]) +'\n')




a10 = [[] for i in range(16)]
a11 = [[] for i in range(16)]

for j in range(16):
	for i in range( len(unique)):
        	if(int(a9[i]) == j):
			a10[j].append(int(a8[i]))
			a11[j].append(d[int(a8[i])])
for j in range(16):
	for i in range(len(a10[j])):
		file4.writelines(str(j) + ',' + str(a11[j][i]) + ',' + str(a10[j][i]) + '\n')

#for j in range(16):
#	for i in a10:
#		file4.writelines( str(j) + ',' + str(a11[j][i]+ ',' + str(a10[j][i])+ '\n' )
