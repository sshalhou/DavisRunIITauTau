import time
import sys
import os
from ROOT import gROOT,TChain, TLorentzVector, TSelector, TTree, TF1, TH1F, TCanvas, gStyle, TFile
import math
import glob


def listFlatTrees(path):
    flatRootTrees = []
    for name in os.listdir(path):
        if os.path.isfile(os.path.join(path, name)):
        	if os.path.join(path, name).endswith('.root'):
	            flatRootTrees.append(os.path.join(path, name))
    return flatRootTrees 



#####################
# for local tests
testList = []
for path in glob.glob('/eos/uscms/store/user/shalhout/VBF_HToTauTau_M-125_13TeV-powheg-pythia6/DUMMY_NAME/150716_142817/0000'):
	testList += listFlatTrees(path)





