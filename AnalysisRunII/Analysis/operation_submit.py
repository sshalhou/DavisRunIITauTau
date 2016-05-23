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
  print len(operationList)
  return [useCondor,tTree , inFile, operationList, outputDir]

def editAnalysisDriver(List):
  txtFileList = ""
  analysisDriverFileTmp = open(os.getcwd() + '/src/analysisDriver.cc.tmp')
  analysisDriverFileUse = open(os.getcwd() + '/src/analysisDriver.cc','w')
  for line in analysisDriverFileTmp:
    if 'Add operations here' in line:
      opComlist = ''
      for i in range (0 ,len(List[3])):
        opComlist += '   operations_map["' + List[3][i] + '"] = 1;' + '\n'
      line = opComlist
    if 'Add TTree here' in line:
      line = '  TChain * T = new TChain("' + List[1] + '");' + '\n'
    if 'Add root files here' in line:
      if '.root' in List[2]:
        if List[0] == 1:
            inFileTitle = List[2].rsplit('/',1)[1]
        else:
            inFileTitle = List[2]
        line = '  T->Add("' + inFileTitle + '");' + '\n'
      elif '.txt' in List[2]:
        addFileString = ""
        fileTxt = open(os.getcwd() + '/' + List[2])
        for line in fileTxt:
          txtFileList += str(line) + ","
          if List[0] == 1:
            inFileTitle = line.rsplit('/',1)[1]
          else:
            inFileTitle = line
          inFileTitle = inFileTitle.replace("\n","")
          addFileString += '  T->Add("' + inFileTitle + '");' + '\n'
        fileTxt.close()
        line = addFileString
    analysisDriverFileUse.write(line)
  analysisDriverFileUse.close()
  analysisDriverFileTmp.close()
  txtFileList = txtFileList.replace("\n","")
  return txtFileList

def editCondorConfig(List,execTitle):
  condorConfigFileTmp = open(os.getcwd() + '/run_condor.txt.tmp')
  condorConfigFileUse = open(os.getcwd() + '/run_condor.txt', 'w')
  for line in condorConfigFileTmp:
    if 'Place Directory' in line:
      line = 'Initialdir = ' + List[4] + '\n'
    if 'Place Input' in line:
      if '.root' in List[2]:
        line = 'transfer_input_files = ' + List[2] + ',/uscms/home/gfunk/public/pDistPlots.root,/uscms/home/gfunk/public/dRvP_singleSample2.root' + '\n'
      else:
        line = 'transfer_input_files = ' + txtFileListFinal + '/uscms/home/gfunk/public/pDistPlots.root,/uscms/home/gfunk/public/dRvP_singleSample2.root' + '\n'
    if 'Place Executable' in line:
      line = 'Executable = ' + execTitle + '\n'
    condorConfigFileUse.write(line)
  condorConfigFileUse.close()
  condorConfigFileTmp.close()

allParams = getOptions(sys.argv[1:])
print allParams[2]
if '.root' in allParams[2]:
  runTitle = 'fileRun'
else:
  runTitle = 'RUN_ANALYSIS_' + allParams[2].split('.')[0]
txtFileListFinal = editAnalysisDriver(allParams)
editCondorConfig(allParams,runTitle)

subprocess.call('make clean', shell = True)
subprocess.call('make dict', shell = True)
subprocess.call('make', shell = True)
time.sleep(1)
if allParams[0] == 1:
  subprocess.call('mv run_analysis ' + runTitle,shell = True)
  if os.path.isdir(allParams[4]) == 0:
    subprocess.call('mkdir -p ' + allParams[4], shell = True)
  subprocess.call('condor_submit run_condor.txt', shell = True)
else:
  subprocess.call('./run_analysis', shell = True)
