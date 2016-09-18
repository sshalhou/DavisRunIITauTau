
# -*- coding: utf-8 -*-
#!/usr/local/bin/python
import subprocess
import os
import sys
import math
import time

filesPerJob = 5
topDirName = "/eos/uscms/store/user/gfunk/SeptProduction_76X_Prelim_Abrev_1/"

subprocess.call('make clean', shell = True)
subprocess.call('make', shell = True)

storageDirNames = topDirName.split("/")
if storageDirNames[len(storageDirNames) - 1] == '':
   storageDirName = storageDirNames[len(storageDirNames) - 2] + '_fileLists'
else:
   storageDirName = storageDirNames[len(storageDirNames) - 1] + '_fileLists'
subprocess.call('mkdir ' + storageDirName, shell = True)

bkgDirLists = [
            ["SingleElectron",["/store/user/shalhout/SingleElectron/trigFilter_fall15_76Xsmall/160711_191213/0000/"],"DATA"],
            ["SingleMuon",["/store/user/shalhout/SingleMuon/trigFilter_fall15_76Xsmall/160711_191253/0000/"],"DATA"]
            ]


def makeList(char):
  for i in range(1,len(char.split(','))):
    print 'ls /eos/uscms' + char.split(',')[i] + ' > ./tempList' + str(i) + '.txt.tmp'
    subprocess.call('ls /eos/uscms' + char.split(',')[i] + ' > ./tempList' + str(i) + '.txt.tmp' , shell = True)
    currFileTmp = open('tempList' + str(i) + '.txt.tmp','r')
    currFileOut = open('tempList' + str(i) + '.txt','w')
    for line in currFileTmp:
      if 'root' in line:
        line = 'root://cmsxrootd.fnal.gov/' + char.split(',')[i] + line
        currFileOut.write(line)
    currFileTmp.close()
    currFileOut.close()
    os.remove('tempList' + str(i) + '.txt.tmp')
  tempFileList = ""
  for i in range(1,len(char.split(','))):
    tempFileList += "tempList" + str(i) + ".txt "
  subprocess.call('cat ' + tempFileList + '> ' + "FullListTemp.txt" , shell = True)
  subprocess.call('rm ' + tempFileList, shell = True)
  longFileList = open('FullListTemp.txt','r')
  fileListsFinal = open(char.split(',')[0] + "_GROUP0" + ".txt",'w')
  lineIndex = 0
  fileIndex = 0
  for line in longFileList:
    fileListsFinal.write(line)
    lineIndex += 1
    if lineIndex > (filesPerJob - 1):
      fileListsFinal.close()
      lineIndex = 0
      fileIndex +=1
      fileListsFinal = open(char.split(',')[0] + "_GROUP" + str(fileIndex) + ".txt",'w')
  fileListsFinal.close()
  longFileList.close()
  os.remove('FullListTemp.txt')
  return fileIndex


print "Sync Tree Operation Submissions: "

for i in range (0,len(bkgDirLists)):
  fullDirName = topDirName + bkgDirLists[i][2] + '/' + bkgDirLists[i][0] + '/'
  fileListName = bkgDirLists[i][0] + "_FlatTuple_LIST"
  inChar = fileListName
  for j in range (0,len(bkgDirLists[i][1])):
    inChar += "," + str(bkgDirLists[i][1][j])
  numberOfLists = makeList(inChar) + 1
  for j in range(0,numberOfLists):
    fullDirName = topDirName + bkgDirLists[i][2] + '/' + bkgDirLists[i][0] + '/CondorJob' + str(j) + '/'
    fileListName = bkgDirLists[i][0] + "_FlatTuple_LIST_GROUP" + str(j)
    print "_____________________________________________New Submit_____________________________________________" + '\n'
    print "python operation_submit.py -c -t \"BASELINE/FlatTuple\" -i " + str(fileListName) + ".txt" + " -o generateH2TauSyncTree -d " + str(fullDirName) + '\n'
    subprocess.call("python operation_submit.py -c -t \"BASELINE/FlatTuple\" -i " + str(fileListName) + ".txt" + " -o generateH2TauSyncTree -d " + str(fullDirName) + '\n', shell = True)

time.sleep(1)
print 'Issue command after all jobs are running: mv *FlatTuple_LIST_GROUP* ' + storageDirName + ' '
#subprocess.call('mv *FlatTuple_LIST_GROUP* ' + storageDirName, shell = True)
