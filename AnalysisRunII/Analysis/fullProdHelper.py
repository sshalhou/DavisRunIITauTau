#!/usr/local/bin/python                                                                                                                                               
import subprocess
import os
import sys
import math
import time

topDirName = "/eos/uscms/store/user/gfunk/MayProduction_Trial_1/"

subprocess.call('make clean', shell = True)
subprocess.call('make', shell = True)
storageDirNames = topDirName.split("/")
if storageDirNames[len(storageDirNames) - 1] == '':
   storageDirName = storageDirNames[len(storageDirNames) - 2] + '_fileLists'
else:
   storageDirName = storageDirNames[len(storageDirNames) - 1] + '_fileLists'
subprocess.call('mkdir ' + storageDirName, shell = True)

bkgDirLists = [
            ["DoubleEG_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/DoubleEG/ExoWkshopTry3NoMVAMET/151105_161345/0000/","/eos/uscms/store/user/shalhout/DoubleEG/ExoWkshopTry3NoMVAMET/151105_161421/0000/"],"DATA"],
            ["MuonEG_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/MuonEG/ExoWkshopTry3NoMVAMET/151105_161501/0000/","/eos/uscms/store/user/shalhout/MuonEG/ExoWkshopTry3NoMVAMET/151105_161534/0000/"],"DATA"],
            ["SingleElectron_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/SingleElectron/ExoWkshopTry3NoMVAMET/151105_161251/0000/","/eos/uscms/store/user/shalhout/SingleElectron/ExoWkshopTry3NoMVAMET/151105_161217/0000/"],"DATA"],
            ["SingleMuon_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/SingleMuon/ExoWkshopTry3NoMVAMET/151105_161059/0000/","/eos/uscms/store/user/shalhout/SingleMuon/ExoWkshopTry3NoMVAMET/151105_161132/0000/"],"DATA"],
            ["Tau_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/Tau/ExoWkshopTry3NoMVAMET/151105_161614/0000/","/eos/uscms/store/user/shalhout/Tau/ExoWkshopTry3NoMVAMET/151105_161650/0000/"],"DATA"],
            ["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ExoWkshopTry3NoMVAMET/151105_160744/0000/","/eos/uscms/store/user/shalhout/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ExoWkshopTry3NoMVAMET/151105_160744/0001/"],"DY"],
            ["SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/ExoWkshopTry3NoMVAMET/151105_154541/0000/"],"SusyGGH160"],
            ["TT_TuneCUETP8M1_13TeV-powheg-pythia8_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/TT_TuneCUETP8M1_13TeV-powheg-pythia8/ExoWkshopTry3NoMVAMET/151105_160818/0000/","/eos/uscms/store/user/shalhout/TT_TuneCUETP8M1_13TeV-powheg-pythia8/ExoWkshopTry3NoMVAMET/151105_160818/0001/","/eos/uscms/store/user/shalhout/TT_TuneCUETP8M1_13TeV-powheg-pythia8/ExoWkshopTry3NoMVAMET/151105_160818/0002/","/eos/uscms/store/user/shalhout/TT_TuneCUETP8M1_13TeV-powheg-pythia8/ExoWkshopTry3NoMVAMET/151105_160818/0003/"],"TTbar"],
            ["WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ExoWkshopTry3NoMVAMET/151105_160650/0000/"],"WJets"],
            ["WW_TuneCUETP8M1_13TeV-pythia8_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/WW_TuneCUETP8M1_13TeV-pythia8/ExoWkshopTry3NoMVAMET/151105_160535/0000/"],"WW"],
            ["WZ_TuneCUETP8M1_13TeV-pythia8_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/WZ_TuneCUETP8M1_13TeV-pythia8/ExoWkshopTry3NoMVAMET/151105_160612/0000/"],"WZ"],
            ["ZHToTauTau_M125_13TeV_powheg_pythia8_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/ZHToTauTau_M125_13TeV_powheg_pythia8/ExoWkshopTry3NoMVAMET/151105_160908/0000/"],"ZH"],
            ["ZZ_TuneCUETP8M1_13TeV-pythia8_ExoWkshopTry3NoMVAMET",["/eos/uscms/store/user/shalhout/ZZ_TuneCUETP8M1_13TeV-pythia8/ExoWkshopTry3NoMVAMET/151105_160458/0000/"],"ZZ"]
            ]

def makeList(char):
  for i in range(1,len(char.split(','))):
    subprocess.call('ls ' + char.split(',')[i] + ' > ./tempList' + str(i) + '.txt.tmp' , shell = True)
    currFileTmp = open('tempList' + str(i) + '.txt.tmp','r')
    currFileOut = open('tempList' + str(i) + '.txt','w')
    for line in currFileTmp:
      if 'root' in line:
        line = char.split(',')[i] + line
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
    if lineIndex > 20:
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
    time.sleep(1)
    subprocess.call("python operation_submit.py -c -t \"BASELINE/FlatTuple\" -i " + str(fileListName) + ".txt" + " -o generateH2TauSyncTree -d " + str(fullDirName) + '\n', shell = True)
    subprocess.call('mv ' + fileListName + '.txt' + ' ' + storageDirName, shell = True)

time.sleep(5)
subprocess.call('rm *c_*', shell = True)
