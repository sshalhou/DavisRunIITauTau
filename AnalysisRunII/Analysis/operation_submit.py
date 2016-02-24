#!/usr/local/bin/python
import subprocess
import os
import sys, getopt

def getOptions(argv):
  useCondor = 0
  tTree = ""
  inFile = ""
  operationList = []
  outputDir = ""
  try:
    opts, args = getopt.getopt(argv,"hct:i:o:d:",["tTree=","iFile=","opList=","outDir="])
  except getopt.GetoptError:
    print 'Usage: python operation_submit.py -c (to use condor) -i [TTree in FlatTuple] -i [input FlatTuple root file or txt file with list of root files] -o [operations to perform] -d [output path]'
    sys.exit(2)
  for opt, arg in opts:
    if opt == '-h':
      print 'Usage: python operation_submit.py -c (to use condor) -t [TTree in FlatTuple] -i [input FlatTuple root file or txt file with list of root files] -o [operations to perform] -d [output path]'
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
        line = '  T->Add("' + List[2] + '");' + '\n'
      elif '.txt' in List[2]:
        addFileString = ""
        fileTxt = open(os.getcwd() + '/' + List[2])
        for line in fileTxt:
          addFileString += '  T->Add' + line + '\n'
        fileTxt.close()
        line = addFileString
    analysisDriverFileUse.write(line)
  analysisDriverFileUse.close()
  analysisDriverFileTmp.close()

def editCondorConfig(List):
  condorConfigFileTmp = open(os.getcwd() + '/run_condor.txt.tmp')
  condorConfigFileUse = open(os.getcwd() + '/run_condor.txt', 'w')
  for line in condorConfigFileTmp:
    if 'Place Directory' in line:
      line = 'Initialdir = ' + List[4] + '\n'
    condorConfigFileUse.write(line)
  condorConfigFileUse.close()
  condorConfigFileTmp.close()

allParams = getOptions(sys.argv[1:])
print allParams
editAnalysisDriver(allParams)
editCondorConfig(allParams)

#if not os.path.isdir(allParams[4]) == "":
#  subprocess.call('mkdir ' + allParams[4], shell = True)
subprocess.call('make clean', shell = True)
subprocess.call('make dict', shell = True)
subprocess.call('make', shell = True)
if allParams[0] == 1:
  if os.path.isdir(allParams[4]) == 0:
    subprocess.call('mkdir ' + allParams[4], shell = True)
  subprocess.call('condor_submit run_condor.txt', shell = True)
else:
  subprocess.call('./run_analysis', shell = True)
