#!/usr/local/bin/python                                                                                                                                               
import subprocess
import os
import sys
import math
import time

topDirName = raw_input("Please enter full path to production output top directory: ")

storageDirNames = topDirName.split("/")
if storageDirNames[len(storageDirNames) - 1] == '':
   storageDirName = storageDirNames[len(storageDirNames) - 2] + '_errorFileList'
else:
   storageDirName = storageDirNames[len(storageDirNames) - 1] + '_errorFileList'
cmd = 'find ' + topDirName + ' -name runErrors.stderr -ls'
outfile = open(storageDirName + '.txt','a+')
process = subprocess.Popen(cmd.split(), shell=False, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
outfile.write(process.communicate()[0])
outfile.close()

errCheck = 0

readfile = open(storageDirName + '.txt')
for line in readfile:
   if line.split()[6] != '0':
      tmpStr = line.split()[10]
      errCheck += 1
      print 'Run errors in: ' + tmpStr.split('/')[6] + ' ' + tmpStr.split('/')[7] + ' ' + tmpStr.split('/')[8] + ' ' + tmpStr.split('/')[9]

if errCheck == 0:
   print 'No production errors'

readfile.close()
os.remove(storageDirName + '.txt')
