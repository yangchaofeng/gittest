#!/usr/bin/python

import os,sys,time,datetime

print 'Hello Python'

for i in range(len(sys.argv)):
	print  'argv[',i,']=',sys.argv[i]

pass 

curpath=sys.path[0]
inputfilename=curpath+'/'+sys.argv[1]
inputfile=open(inputfilename,'r+')
temp0file=open(curpath+'/'+'init_code_temp0.txt','wb')

command_num=0

lines = inputfile.readlines()
for aline in lines:
	if aline.split():#delete blank line
		aline=aline.strip()
		aline=aline.upper()#Convert to upper
		if aline.startswith('DCS'):#if begin with 'DCS'
			if command_num != 0:
				temp0file.write('\r\n')
			temp0file.write(aline.replace(";","").split(' ')[0].split('#')[0])
			command_num +=1
		elif aline.startswith('GEN'):
                        if command_num != 0:
                                temp0file.write('\r\n')			
			temp0file.write(aline.replace(";","").split(' ')[0].split('#')[0])
			command_num +=1
		elif aline.startswith('CMD'):
			temp0file.write(aline.replace(";","").split(' ')[0].split('#')[0])
		elif aline.startswith('DATA'):
			temp0file.write(aline.replace(";","").split(' ')[0].split('#')[0])
		else:
			print 'invalid parameter'
inputfile.close()
temp0file.close()


inputfile=open(curpath+'/'+'init_code_temp0.txt','r+')
mtkfile=open(curpath+'/'+'mtk_init_code.txt','wb')

lines = inputfile.readlines()
for aline in lines:
	cmd_num = aline.find("DATA",1,-1)

	aline = aline[:cmd_num]+'DATA_NUM_BEGIN('+oct(aline.count('DATA'))+'DATA_NUM_END)'+aline[cmd_num:]
	aline = aline.replace(")DATA(",",")
	aline = aline.replace("DCS","")
	aline = aline.replace("GEN","")
	aline = aline.replace("CMD(","{")
	aline = aline.replace(")DATA_NUM_BEGIN(",",")
	aline = aline.replace("DATA_NUM_END,",",{")
	aline = aline.replace(")","}},")
	
	mtkfile.write(aline)
inputfile.close()
mtkfile.close()

