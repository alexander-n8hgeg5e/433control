#!/usr/bin/env python3
from math import inf
from argparse import ArgumentParser
from math import floor
from sys import stderr,stdout
ap=ArgumentParser()
ap.add_argument(dest="file",help="file with logic data one sample per byte and 1MS/s.  (like from pulseview if you click export raw logic data). 100kSamples at 1MS/s are optimal for my remote" )
ap.add_argument("-l","--limit",help="shorten the length to this number",type=int,default=56)
args=ap.parse_args()

def _gen_classes(data,classes=[]):
    for v in data1:
        found=False
        for c in classes:
            if c - distance <= v <= c + distance:
                found=True
        if not found:
            classes.append(v)
    return classes

def adj_classes(data,classes):
    classes1=[]
    for c in classes:
        values=[]
        for v in data1:
            if c - distance <= v <= c + distance:
                values.append(v)
    
        avg = sum(values)/len(values)
        classes1.append(avg)
    return classes1

from math import nan
def print_classes(*c,prec=1,file=stdout):
    ll=[len(i) for i in c]
    m=max(ll)
    for i in range(m):
        a=[]
        for cc in c:
            a.append(cc[i] if len(cc) > i else nan)
        print(" ".join(["{:"+str(8+prec)+"."+str(prec)+"f}"]*len(c)).format(*a),file=file)

def diff(c0,c1):
    return sum(c0) - sum(c1)

def compress_classes(c,distance):
    c.sort()
    newc=[]
    skip=False
    lc=len(c)
    for i in range(1,len(c)):
        if skip:
            if i+1 == lc:
                newc.append(c[i])
            else:
                skip=False
                continue
        if c[i] - c[i-1] <= distance:
            newc.append(( c[i] + c[i-1] ) / 2)
            skip=True
        else:
            newc.append(c[i-1])
            if i+1 == len(c):
                newc.append(c[i])
    return newc

def gen_classes(vals,distance):
    d = vals
    c = _gen_classes(d)
    c.sort()
    cc = [c]
    minlen_c = len(c)
    c = adj_classes(d,c)
    c.sort()
    cc.append(c)
    c = _gen_classes(d,classes=c)
    
    while cc[-1] != c:
        c = adj_classes(d,c)
        c.sort()
        cc.append(c)
        c = _gen_classes(d,classes=c)
    
    while diff(cc[-1],c) > 0.001:
        c.sort()
        cc.append(c)
        c=compress_classes(c,distance)

    return c

def val2cls(val,classes,distance):
    for c in classes:
        if c - distance <= val <= c+distance:
            return c
    return None

def find_longest_repeating_seq(l):
    """
    finds longest repeating seq and returns 2 start positions and len
    """
    data2=l
    m=2
    for i in range(floor(len(data2)/2)):
        seq = data2[i:i+m]
        for j in range(len(data2[i+m:])):
            if seq == data2[i+m+j:i+m+j+m]:
               #print("{} x={:<5n} y={:<5n}".format(m,i,i+m+j))
               x=i
               y=i+m+j
               m+=1
               break
    m-=1
    return x,y,m

def  remove_repeating_stuff(d):
    ###
    ### remove repeating stuff
    ###
    m=inf
    print("len data = {}".format(len(d)))
    while m > 10:
        print("m={}  len data={}".format(m, len(d)))
        x,y,m=find_longest_repeating_seq(d)
        d=d[:y]+d[y+m:]
    return d

MEGA_SAMPLE_RATE=8

with open(args.file,'rb') as f: 
     data0=f.read()                

y=0
data1=[]                          
for i in range(1,len(data0)):    
    if data0[i-1] != data0[i]:      
        data1.append(int((i-y)/MEGA_SAMPLE_RATE))
        y=i

# raw print
print(f"raw start: {data1[:10]} ... ",file=stderr)

# fix long first value
#m=max(data1[1:])
#data1[0]=min(m,data1[0])
#print(data1[:5],file=stderr)
#print(data1[-5:],file=stderr)
#print("len data = {}".format(len(data1)),file=stderr)


## clean values
#avg = sum(data1)/len(data1)
#distance = 0.05 * avg
#print("distance = {}".format(distance),file=stderr)
#classes = gen_classes(data1,distance)
#classes=[int(round(i,0)) for i in classes]
#print_classes(classes,file=stderr)
#data2=[val2cls(v,classes,distance) for v in data1 ]

# invert
data2 = [3000] + data1    
print(f"inverted start: {data2[:10]} ... ",file=stderr)

data2=data2[:args.limit]
print("sum-time={}".format(sum(data2)),file=stderr)
print(" ".join([str(i) for i in data2]),end="")










