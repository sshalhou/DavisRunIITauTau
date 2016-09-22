import time
import sys
import os
from ROOT import gROOT,TChain, TLorentzVector, TSelector, TTree, TF1, TH1F, TCanvas, gStyle, TFile
import math
import glob
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('--DIR', type=str, nargs=1, required=True, 
                   help='ex: --DIR /store/user/shalhout/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/trigFilter_fall15_76Xsmall')

parser.add_argument('--TTree', type=str, nargs=1, required=True, 
                   help='ex: --TTree Cumulative/CumulativeTuple')


args = parser.parse_args(sys.argv[1:])

dir_ = args.DIR[0]

if dir_.startswith("/eos/uscms"):
	dir_ = dir_[len("/eos/uscms"):]



print "chaining root files in ", dir_, "...."


def splitList(list, mergeCount):
    for l in range(0, len(list), mergeCount):
        yield list[l:l+mergeCount]

#####################################
# search and find all subdirectories -- this assumes the usual CRAB job output dir structure 
#####################################

ALL_ROOT_FILES = []

dirListtRaw = os.popen("eos root://cmseos.fnal.gov ls "+dir_).read()
dirListt = dirListtRaw.split("\n")
print "Found the following JOB ID sub-directories "
print dirListt


for name in dirListt:
	if name == '':
		continue
	print "... checking subdir .... ", name
	subDir = dir_ + "/" + name

	SUBdirListtRaw = os.popen("eos root://cmseos.fnal.gov ls "+subDir).read()
	SUBdirListt = SUBdirListtRaw.split("\n")
	SUBdirListt.remove("")
	print "******* sub-directory ", name , " has ", len(SUBdirListt), " sub-directories : "
	print SUBdirListt

	for i in range(0, len(SUBdirListt)):
		a_path = dir_+"/"+name+"/"+SUBdirListt[i]
		TEMP_ALL_FILES = ((os.popen("eos root://cmseos.fnal.gov ls "+a_path).read()).split("\n"))
		TEMP_ALL_FILES.remove("")
		#print TEMP_ALL_FILES

		TEMP_ROOT_FILES = []
		for z in range(0, len(TEMP_ALL_FILES)):
			testForRoot = TEMP_ALL_FILES[z]
			if testForRoot.endswith('.root') is True:
				TEMP_ROOT_FILES.append(testForRoot)

		#print TEMP_ROOT_FILES
		print " found ", len(TEMP_ROOT_FILES) ," root files in ", a_path

		for r in range(0, len(TEMP_ROOT_FILES)):
			a_root_file = "root://cmsxrootd.fnal.gov/"+a_path + "/" + TEMP_ROOT_FILES[r]
			ALL_ROOT_FILES.append(a_root_file)
			#print a_root_file

print "***** FOUND ", len(ALL_ROOT_FILES), " root files in total ******* "			

total = 0

for split_list in splitList(ALL_ROOT_FILES, 5000):
	#print "checking 1st ", len(split_list), " files ..."
	check = TChain(args.TTree[0])	
	for ll in range(0, len(split_list)):	
		check.Add(split_list[ll])
		total += check.GetEntries()
		if(ll%100 == 0):
			print "counted ", total, " event so far ..."
		check.Reset()	
		#print check.GetEntries(), " should be zero "

# check = TChain(args.TTree[0])	
# for ll in range(0, len(ALL_ROOT_FILES)):
# 	check.Add(ALL_ROOT_FILES[ll])

# print " counting events, this may take a while ..."

# total = check.GetEntries()

print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
print "++> In ", args.DIR[0]
print "++> Found ", len(ALL_ROOT_FILES), " ROOT files with ", total, " events in TTree ", args.TTree[0]
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"



