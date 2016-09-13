#!/usr/local/bin/python
import subprocess
import os
import sys, getopt
import textwrap
import time

execTitle = ""

def getOptions(argv):
  useCondor = 0
  tTree = ""
  inFile = ""
  operationList = []
  outputDir = ""
  try:
    opts, args = getopt.getopt(argv,"hct:i:o:d:",["tTree=","iFile=","opList=","outDir="])
  except getopt.GetoptError:
    print 'Usage: python operation_submit.py -c (to use condor) -i [TTree in FlatTuple] -i [input name and path to FlatTuple root file or txt file with list of root files] -o [operations to perform] -d [output path]'
    sys.exit(2)
  for opt, arg in opts:
    if opt == '-h':
      print 'Usage: python operation_submit.py -c (to use condor) -t [TTree in FlatTuple] -i [input name and path to FlatTuple root file or txt file with list of root files] -o [operations to perform] -d [output path]'
      sys.exit()
    elif opt == '-c':
      useCondor = 1
    elif opt in ("-t", "--tTree"):
      tTree = arg
    elif opt in ("-i", "--iFile"):
      inFile = arg
    elif opt in ("-o", "--opList"):
      operationList = arg.split()
    elif opt in ("-d", "--outDir"):
      outputDir = arg
  return [useCondor,tTree , inFile, operationList, outputDir]

def parseCommands(List):
  inFileTitle = ""
  txtFileList = ""
  if List[0] ==1:
    if '.txt' in List[2]:
        fileTxt = open(os.getcwd() + '/' + List[2])
        cFileList = open(os.getcwd() + '/' + 'c_' + List[2], 'w+')
        for line in fileTxt:
          txtFileList += str(line) + ","
          line = line.rsplit('/',1)[1]
          cFileList.write(line)
        cFileList.close()
        fileTxt.close()
        txtFileList += os.getcwd() + '/c_' + List[2]
    elif '.root' in List[2]:
        inFileTitle = List[2].rsplit('/',1)[1]
        txtFileList = List[2]
  txtFileList = txtFileList.replace("\n","")
  txtBlock = [txtFileList,inFileTitle]
  return txtBlock

def editCondorConfig(List):
  condorConfigFileTmp = open(os.getcwd() + '/run_condor.txt.tmp')
  condorConfigFileUse = open(os.getcwd() + '/run_condor.txt', 'w')
  for line in condorConfigFileTmp:
    if 'Place Arguments' in line:
      if '.root' in List[2]:
        line = 'arguments = ' + List[1] + ' ' + List[2].rsplit('/',1)[1] + ' ' + List[3][0] + '\n'
      else:
        line = 'arguments = ' + List[1] + ' c_' + List[2] + ' ' + List[3][0] + '\n'
    if 'Place Directory' in line:
      line = 'Initialdir = ' + List[4] + '\n'
    if 'Place Input' in line:
      if '.root' in List[2]:
        line = 'transfer_input_files = ' + List[2] + ',' + os.getcwd() + '/supportFiles/pDistPlots.root' + ',' + os.getcwd() + '/ZReweight/zpt_weights.root'+ ',' + os.getcwd() + '/HTT-utilities/QCDModelingEMu/data/QCD_weight_emu.root'+ ',' + os.getcwd() + '/HTT-utilities/QCDModelingEMu/data/QCD_weight_emu_nodzeta.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_IdIso0p1_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_SingleMu_eff.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_IdIso0p15_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_IdIso0p1_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_SingleEle_eff.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_IdIso0p15_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_Mu8_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_Mu17_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_Ele17_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_Ele12_fall15.root' + ',' + os.getcwd() + '/SUSYHiggsPtReweight/Reweight.root' + '\n'
      else:
        line = 'transfer_input_files = ' + txtFileBlockFinal[0] + ',' + os.getcwd() + '/supportFiles/pDistPlots.root' + ',' + os.getcwd() + '/ZReweight/zpt_weights.root'+ ',' + os.getcwd() + '/HTT-utilities/QCDModelingEMu/data/QCD_weight_emu.root'+ ',' + os.getcwd() + '/HTT-utilities/QCDModelingEMu/data/QCD_weight_emu_nodzeta.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_IdIso0p1_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_SingleMu_eff.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_IdIso0p15_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_IdIso0p1_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_SingleEle_eff.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_IdIso0p15_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_Mu8_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Muon/Muon_Mu17_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_Ele17_fall15.root' + ',' + os.getcwd() + '/HTT-utilities/LepEffInterface/data/Electron/Electron_Ele12_fall15.root' + ',' + os.getcwd() + '/SUSYHiggsPtReweight/Reweight.root' + '\n'
    condorConfigFileUse.write(line)
  condorConfigFileUse.close()
  condorConfigFileTmp.close()

allParams = getOptions(sys.argv[1:])
print allParams
txtFileBlockFinal = parseCommands(allParams)
print "txtFileBlockFinal: " + str(txtFileBlockFinal)
editCondorConfig(allParams)

if allParams[0] == 1:
  if os.path.isdir(allParams[4]) == 0:
    subprocess.call('mkdir -p ' + allParams[4], shell = True)
  subprocess.call('condor_submit run_condor.txt', shell = True)
else:
  subprocess.call('./run_analysis ' + allParams[1] + ' ' + allParams[2] + ' ' + allParams[3][0], shell = True)