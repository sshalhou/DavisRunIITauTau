import time
import sys
import os
from ROOT import gROOT,TChain, TLorentzVector, TSelector, TTree, TF1, TH1F, TCanvas, gStyle, TFile
import math
import glob
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('--DIR', type=str, nargs=1, required=True, 
                   help='ex: --DIR /eos/uscms/store/user/shalhout/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/trigFilter_fall15_76Xsmall')

parser.add_argument('--TTree', type=str, nargs=1, required=True, 
                   help='ex: --TTree Cumulative/CumulativeTuple')


args = parser.parse_args(sys.argv[1:])

dir_ = args.DIR[0]

print "chaining root files in ", dir_, "...."

ROOT_FILES = []
for name in os.listdir(dir_):
	print "... checking subdir .... ", name
	subDir = dir_ + "/" + name
	for subSubDir in os.listdir(subDir):
		print "... ... checking sub-subdir .... ", subSubDir
		for file in os.listdir(subDir+"/"+subSubDir):
			if file.endswith('.root'):
				check = TChain(args.TTree[0])	
				check.Add(subDir+"/"+subSubDir+"/"+file)
				ROOT_FILES.append(subDir+"/"+subSubDir+"/"+file)
				
print "found ", len(ROOT_FILES), " root files"
print "chaining files together and counting entries ..."
print "this can take a while for large samples ...."

chain = TChain(args.TTree[0])

for file in ROOT_FILES:
	chain.Add(file)

total = chain.GetEntries()

print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
print "++ In ", args.DIR[0]
print "++ Found ", len(ROOT_FILES), " ROOT files with ", total, " events in TTree ", args.TTree[0]
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"


