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

events = Events ("/uscms_data/d3/shalhout/RunIIWorking/CMSSW_7_2_3_patch1/src/NtupleFile.root")
handle = Handle ("std::vector<NtupleEvent>")
label = ("NtupleEvent","NtupleEvent","Ntuple")



for event in events:
	event.getByLabel (label, handle)
	pairs = handle.product()
	for p in pairs:
		leg0 = p.leg0()
		for i in range(0,len(leg0.relativeIsol_Labels())):
			print 'event type = ', p.CandidateEventType(), leg0.relativeIsol_Labels()[i]," = ", leg0.relativeIsol_Values()[i]





events2 = Events ("/uscms_data/d3/shalhout/RunIIWorking/CMSSW_7_2_3_patch1/src/NtupleFile.root")
handle2 = Handle ("std::vector<NtuplePairIndependentInfo>")
label2 = ("pairIndep","NtupleEventPairIndep","Ntuple")


for event2 in events2:
    # use getByLabel, just like in cmsRun
    event2.getByLabel (label2, handle2)
    # get the product
    pairIndep = handle2.product()   
    for pI in pairIndep:
    	for gP in pI.genParticles():
    		print 'gen particle id, status, pt = ', gP.gen_pdgId(), gP.gen_status(), gP.gen_p4().pt(),
    		print 'mother(s) [pdgId, status] = ',
    		for m in range(0, len(gP.mothers_pdgId())):
    			print '[', gP.mothers_pdgId()[m],',',gP.mothers_status()[m],']'
    		print 'daughters(s) [pdgId, status] = ',
    		for d in range(0, len(gP.daughters_pdgId())):
    			print '[', gP.daughters_pdgId()[d],',',gP.daughters_status()[d],']'



