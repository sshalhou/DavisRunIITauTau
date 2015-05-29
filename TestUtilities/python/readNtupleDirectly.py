import time
import sys
import os
import math
from array import array



import ROOT
import sys
from DataFormats.FWLite import Events, Handle

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('python')
options.parseArguments()

events = Events ("NtupleFile.root")

handle = Handle ("std::vector<NtupleEvent>")

label = ("NtupleEvent","","Ntuple")


for event in events:
    # use getByLabel, just like in cmsRun
    event.getByLabel (label, handle)
    # get the product
    pairs = handle.product()
    for i in range(0, pairs.size()):
    	print pairs[i].CandidateEventType()
    	for ii in range(0, pairs[i].leg0().relativeIsol_Labels().size()):
	    	print pairs[i].leg0().relativeIsol_Labels()[ii], '=', pairs[i].leg0().relativeIsol_Values()[ii]



