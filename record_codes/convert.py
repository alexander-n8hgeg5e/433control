#/usr/bin/env python3
# coding: utf-8
deltas={}
codes={}

def append_check_delta(delta):
    if str(delta) in deltas.keys():
        return delta
    retval=None
    poplist=[]
    addlist=[]
    for k in deltas.keys():
        d=int(k)
        if delta*0.9<d<=delta*1.1:
            if not delta in deltas[k]:
                deltas[k].append(delta)
            retval=d
            if len(deltas[k])>0:
                avg=round(sum(deltas[k])/len(deltas[k]))
                if not delta*0.95 < avg <= delta*1.05:
                    addlist.append({str(avg):deltas[k]})
                    poplist.append(k)
                    retval=avg
    for p in poplist:
        deltas.pop(p)
    for a in addlist:
        deltas.update(a)
    if retval is None:
        deltas.update({str(delta):[]})
        retval=delta
    if retval is None:
        raise Exception("error")
    return retval

for i in a:
    code=[]
    with open(i) as f:
        data=f.read()
    spdata=data.split(" ")
    for d in spdata:
        try:
            delta=int(d.strip())
            code.append(append_check_delta(delta))
        except ValueError:
            pass
                
    codes.update({i:code})

for k,v in codes.items():
    remote,button,action=k.split("_")[1:]
    remote=remote[2:]
    with open('../codes/433/remote'+remote+"_btn"+button+"_"+action,'wt') as f:
        # remove first element
        code=[str(k) for k in codes[k]]
        f.write("2288 "+" ".join(code[:55]))
        
