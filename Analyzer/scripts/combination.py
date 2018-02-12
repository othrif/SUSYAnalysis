from math import sqrt
from datetime import datetime

fakesInputSR = r'''
    Rpc2L0bH & $ 0.83 \pm  0.56 \pm  0.73$  &  $01.00 \pm 00.96 \pm 00.81$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.41 \pm  0.20 \pm  0.35$  \\
    Rpc2L0bS & $ 1.52 \pm  0.60 \pm  0.77$  &  $01.68 \pm 01.02 \pm 01.26$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 1.75 \pm  0.24 \pm  0.88$  \\
    Rpc2L1bH & $ 3.46 \pm  1.56 \pm  2.46$  &  $02.07 \pm 00.63 \pm 01.56$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 2.48 \pm  0.37 \pm  1.83$  \\
    Rpc2L1bS & $ 2.65 \pm  1.21 \pm  1.89$  &  $02.33 \pm 01.17 \pm 02.10$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 2.90 \pm  0.69 \pm  1.41$  \\
    Rpc2L2bH & $-0.11 \pm  0.11 \pm  0.15$  &  $0.001 \pm 0.001 \pm 0.001$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.15 \pm  0.15 \pm  0.00$  \\
    Rpc2L2bS & $ 1.27 \pm  1.03 \pm  1.25$  &  $00.41 \pm 00.33 \pm 00.45$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.88 \pm  0.19 \pm  0.62$  \\
 Rpc2Lsoft1b & $ 4.71 \pm  1.39 \pm  3.12$  &  $02.48 \pm 01.32 \pm 01.86$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 3.78 \pm  0.71 \pm  2.35$  \\
 Rpc2Lsoft2b & $ 1.87 \pm  1.15 \pm  1.75$  &  $01.66 \pm 00.66 \pm 01.28$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 3.42 \pm  0.14 \pm  3.23$  \\
    Rpc3L0bH & $-0.00 \pm  0.11 \pm  0.12$  &  $00.00 \pm 00.00 \pm 00.00$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.15 \pm  0.15 \pm  0.00$  \\
    Rpc3L0bS & $ 2.23 \pm  1.44 \pm  2.25$  &  $00.21 \pm 00.15 \pm 00.16$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.45 \pm  0.20 \pm  0.44$  \\
    Rpc3L1bH & $ 0.58 \pm  0.43 \pm  0.50$  &  $00.42 \pm 00.29 \pm 00.32$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.85 \pm  0.21 \pm  0.48$  \\
    Rpc3L1bS & $ 4.89 \pm  1.78 \pm  3.01$  &  $03.55 \pm 01.80 \pm 02.76$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 3.35 \pm  0.61 \pm  1.73$  \\
   Rpc3LSS1b & $-0.09 \pm  1.16 \pm  1.79$  &  $00.90 \pm 00.14 \pm 00.69$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.48 \pm  0.24 \pm  0.59$  \\
     Rpv2L0b & $ 0.14 \pm  0.22 \pm  0.23$  &  $01.02 \pm 00.96 \pm 00.76$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.22 \pm  0.15 \pm  0.25$  \\
    Rpv2L1bH & $-0.06 \pm  0.03 \pm  0.10$  &  $00.60 \pm 00.35 \pm 00.48$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.15 \pm  0.15 \pm  0.00$  \\
    Rpv2L1bM & $ 1.66 \pm  1.97 \pm  1.24$  &  $01.20 \pm 00.69 \pm 00.95$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 1.32 \pm  0.67 \pm  1.22$  \\
    Rpv2L1bS & $16.04 \pm  3.88 \pm 13.06$  &  $04.46 \pm 01.67 \pm 03.45$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 7.67 \pm  1.83 \pm  6.72$  \\
    Rpv2L2bH & $-0.03 \pm  0.02 \pm  0.09$  &  $00.001 \pm 00.001 \pm 00.001$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.15 \pm  0.15 \pm  0.00$  \\
    Rpv2L2bS & $ 9.44 \pm  3.16 \pm  6.93$  &  $07.24 \pm 02.36 \pm 05.43$  &  $01.23 \pm 01.23 \pm 01.23$    &  $ 0.88 \pm  0.68 \pm  0.82$  \\
'''

fakesInputVR =  r'''    
               & VR-$t\bar t W$ & VR-$t\bar t Z$ & VR-$WZ$4j & VR-$WZ$5j & VR-$W^\pm W^{\pm}$  \\\hline	   
Fakes DD       & $23 \pm 5 \pm 21$      & $30 \pm 4 \pm 17$   & $52 \pm 6 \pm 27$   & $21 \pm 3 \pm 11$  & $14 \pm 3 \pm 10$ \\
Fakes MC       & $14 \pm 4 \pm 10$      & $18 \pm 3 \pm 13 $  & $46 \pm 5  \pm 34$  & $16 \pm 2 \pm 12$  & $13 \pm 2 \pm 10$ \\\hline
'''

def combine(yDD, yMC):
    w = (yMC[1]**2)/(yDD[1]**2 + yMC[1]**2)
    y = w*yDD[0] + (1-w)*yMC[0]
    dy_stat = sqrt((w*yDD[1])**2 + ((1-w)*yMC[1])**2)
    dy_syst = w*yDD[2] + (1-w)*yMC[2]
    if y<0.15:
        dy = sqrt(dy_stat**2 + dy_syst**2)
        if y+dy>0.3:
            y = 0.5*(y+dy)
            dy_stat = y
            dy_syst = 0
        else:   
            y = 0.15
            dy_stat = 0.15
            dy_syst = 0
    return (y,dy_stat,dy_syst)


fakeYields = {}
chargeFlipYields = {}

vrNames = []
vrYieldsDD = []
vrYieldsMC = []
tokenLengths = []
updated_VR_table = fakesInputVR 
if fakesInputVR[-1]!='\n': updated_VR_table += '\n'
updated_VR_table += 'Combined       & '
for line in fakesInputVR.split('\n'):
    if len(line)<10: continue
    tokens = line.replace('\\\\','').replace('\\hline','').split('&')
    if 'Fakes' in tokens[0]:
        if 'DD' in tokens[0]:
            vrYields = vrYieldsDD
            tokenLengths = [len(s) for s in tokens[1:]]
        elif 'MC' in tokens[0]: vrYields = vrYieldsMC
        else: raise BaseException('Invalid format')
        for i in range(1,len(tokens)):
            vrYields.append(tuple([float(s.strip()) for s in tokens[i].replace('$','').strip().split('\pm')]))
    else:
        for i in range(1,len(tokens)):
            n = tokens[i].strip()
            if n=='VR-$t\\bar t W$': n='VRttW'
            elif n=='VR-$t\\bar t Z$': n='VRttZ'
            elif n=='VR-$WZ$4j': n='VRWZ4J'
            elif n=='VR-$WZ$5j': n='VRWZ5J'
            elif n=='VR-$W^\\pm W^{\\pm}$': n='VRWW'
            else: raise BaseException('Unknown VR name %s'%(n))
            vrNames.append(n)
if len(vrNames)==len(vrYieldsDD) and len(vrYieldsDD)==len(vrYieldsMC):
    for i,n in enumerate(vrNames):
        y = combine(vrYieldsDD[i],vrYieldsMC[i])
        fakeYields[n] = y
        s = '$%.0f \\pm %.0f \\pm %.0f$'%y
        updated_VR_table += s
        if i<len(vrNames)-1: updated_VR_table += ' '*(tokenLengths[i]-len(s)-2) + ' & '
    updated_VR_table += ' \\\\\hline'
else: raise BaseException('Error: VR parsing failed')

output = {}
updated_SR_table = ''
withinStats = []
for line in fakesInputSR.split('\n'):
    if len(line)<10: continue
    tokens = line.split('&')
    name = tokens[0].strip()
    x = 11 - len(name)
    name = ' '*x + name
    mxm = [float(s.strip()) for s in tokens[1].replace('$','').strip().split('\\pm')]
    mxm.append(sqrt(mxm[1]**2 + mxm[2]**2))
    mct = [float(s.strip()) for s in tokens[2].replace('$','').strip().split('\\pm')]
    mct.append(sqrt(mct[1]**2 + mct[2]**2))
    args = [name,mxm[0],mxm[3],mct[0],mct[3]]
    # check if the estimates are within statistical fluctuations
    if abs(mxm[0] - mct[0]) < sqrt(mxm[1]*mxm[1] + mct[1]*mct[1]): withinStats.append(tokens[0])
    # weighted average
    print  mxm[3],mct[3]
    if( (mxm[3]**2 + mct[3]**2) == 0 ): w = 0.001
    else:w = mct[3]*mct[3]/(mxm[3]**2 + mct[3]**2)
    y = w*mxm[0] + (1-w)*mct[0]
    dy = sqrt((w*mxm[3])**2 + ((1-w)*mct[3])**2)
    args.append(y)
    args.append(dy)
    # stats-weighted average, correlated systematics
    if( (mxm[1]*mxm[1]+mct[1]*mct[1]) == 0 ): w = 0.001
    else: w = mct[1]*mct[1]/(mxm[1]*mxm[1]+mct[1]*mct[1])
    y = w*mxm[0] + (1-w)*mct[0]
    dy = sqrt((w*mxm[1])**2 + ((1-w)*mct[1])**2 + (w*mxm[2] + (1-w)*mct[2])**2)
    args.append(y)
    args.append(dy)
    # arithmetic mean
    y = 0.5*(mxm[0] + mct[0])
    dy = 0.5*abs(mxm[0] - mct[0])
    args.append(y)
    args.append(dy)
    # print
    output[tokens[0]] = '%s: mxm=%.2f +- %.2f;  mct=%.2f +- %.2f;  A=%.2f +- %.2f;  B=%.2f +- %.2f;  C=%.2f +- %.2f'%tuple(args)
    
    # combined estimate
    c = combine(mxm,mct)
    comb = '  &  $%5.2f \\pm %5.2f \\pm %5.2f$  \\\\'%c
    fakeYields[name] = c
    updated_SR_table += '&'.join(tokens[0:4]) + comb + '\n'
    
print '\nA = weighted average\nB = stats-weighted average, correlated systs\nC = mean +- half-difference'

print '\nSRs for which estimates are within statistical fluctuations:'   
for n,s in output.iteritems(): 
   if n in withinStats: print s
   
print '\nOther SRs:'   
for n,s in output.iteritems(): 
   if n not in withinStats: print s
   
# Formatted SR table for the supporting note
print '\nUpdated SR table:'
print updated_SR_table

# Formatted VR table for the supporting note
print '\nUpdated VR table:'
print updated_VR_table

chargeFlipInputSR = r'''
    Rpc2L0bH & $ 0.01 \pm  0.00 \pm  0.00$ & $ 00.00 \pm 00.00 \pm 00.00 $ \\
    Rpc2L0bS & $ 0.05 \pm  0.01 \pm  0.01$ & $ 00.02 \pm 00.02 \pm 00.00 $ \\
    Rpc2L1bH & $ 0.25 \pm  0.03 \pm  0.04$ & $ 00.21 \pm 00.32 \pm 00.16 $ \\
    Rpc2L1bS & $ 0.25 \pm  0.02 \pm  0.04$ & $ 00.35 \pm 00.37 \pm 00.26 $ \\
    Rpc2L2bH & $ 0.02 \pm  0.01 \pm  0.00$ & $ 00.00 \pm 00.00 \pm 00.00 $ \\
    Rpc2L2bS & $ 0.10 \pm  0.01 \pm  0.02$ & $ 00.00 \pm 00.00 \pm 00.00 $ \\
 Rpc2Lsoft1b & $ 0.08 \pm  0.01 \pm  0.02$ & $ 00.00 \pm 00.00 \pm 00.00 $ \\
 Rpc2Lsoft2b & $ 0.08 \pm  0.01 \pm  0.02$ & $ 00.00 \pm 00.00 \pm 00.00 $ \\
   Rpc3LSS1b & $ 0.39 \pm  0.03 \pm  0.07$ & $ 00.81 \pm 00.53 \pm 00.34 $ \\
     Rpv2L0b & $ 0.03 \pm  0.02 \pm  0.00$ & $ 00.22 \pm 00.06 \pm 00.09 $ \\
    Rpv2L1bH & $ 0.02 \pm  0.01 \pm  0.00$ & $ 00.02 \pm 00.01 \pm 00.01 $ \\
    Rpv2L1bM & $ 0.10 \pm  0.01 \pm  0.02$ & $ 00.10 \pm 00.06 \pm 00.04 $ \\
    Rpv2L1bS & $ 0.74 \pm  0.04 \pm  0.11$ & $ 01.30 \pm 00.66 \pm 00.54 $ \\
    Rpv2L2bH & $ 0.03 \pm  0.01 \pm  0.01$ & $ 00.00 \pm 00.00 \pm 00.00 $ \\
    Rpv2L2bS & $ 0.46 \pm  0.03 \pm  0.07$ & $ 01.55 \pm 01.07 \pm 01.25 $ \\
'''
for line in chargeFlipInputSR.split('\n'):
    if len(line)<10: continue
    tokens = line.split('&')
    name = tokens[0].strip()
    chargeFlipYields[name] = tuple([float(s.strip()) for s in tokens[1].replace('$','').strip().split('\\pm')])
chargeFlipYields['VRttW'] = (3.6, 0.1, 0.5)
chargeFlipYields['VRWW'] = (1.8, 0.1, 0.2)
chargeFlipYields['Rpc3L0bH'] = (0.,0.,0.)
chargeFlipYields['Rpc3L0bS'] = (0.,0.,0.)
chargeFlipYields['Rpc3L1bH'] = (0.,0.,0.)
chargeFlipYields['Rpc3L1bS'] = (0.,0.,0.)
chargeFlipYields['VRttZ'] = (0.,0.,0.)
chargeFlipYields['VRWZ4j'] = (0.,0.,0.)
chargeFlipYields['VRWZ5j'] = (0.,0.,0.)

# Python file for HistFitter
with open('datadriven_bkg_winter2017.py', 'w') as f:
    d = datetime.now()
    f.write('# 2015+2016 data-driven background yields (36 fb-1)\n# %02d/%02d/%d - %02d:%02d\n'%(d.day,d.month,d.year,d.hour,d.minute))
    dictName = ('fakeCounts','fakeStatErr','fakeSystErr','mischCount','mischStatErr','mischSystErr')
    for i in range(0,6):
        f.write('\n%s = {\n'%(dictName[i]))
        yields = fakeYields if i<3 else chargeFlipYields
        for r,y in yields.iteritems():
            f.write("\t\t'"+r.strip()+"': ([%.2f],'cuts',0.5),\n"%(y[i%3]))
        f.write('}\n')
