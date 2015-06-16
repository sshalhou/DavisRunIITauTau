import time
import sys
import os
import math
from array import array

FILE = "/uscms_data/d3/shalhout/RunIIWorking/CMSSW_7_2_3_patch1/src/NtupleFile.root"

import ROOT
import sys
from DataFormats.FWLite import Events, Handle

from FWCore.ParameterSet.VarParsing import VarParsing
from ROOT import TH1F, TFile
options = VarParsing ('python')
options.parseArguments()

######################
# choose which to run :

doExample1 = False
doExample2 = False
doExample3 = False
doExample4 = True

####################################
# EX-1 : print candidateType & isolations

if doExample1 :
    events = Events (FILE)
    handle = Handle ("std::vector<NtupleEvent>")
    label = ("NtupleEvent","NtupleEvent","Ntuple")



    for event in events:
    	event.getByLabel (label, handle)
    	pairs = handle.product()
    	for p in pairs:
    		leg1 = p.leg1()
    		for i in range(0,len(leg1.relativeIsol_Labels())):
    			print 'event type = ', p.CandidateEventType(), leg1.relativeIsol_Labels()[i]," = ", leg1.relativeIsol_Values()[i]



##############################################
# EX-2 : print genPartilce types, pt, status

if doExample2 :

    events2 = Events (FILE)
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


#########################################################################
# EX-3 : print & histogram jet energy correction SF for "Uncorrected"
#        and check the default b-tag raw output and post-sf boolean

if doExample3 :

    events3 = Events (FILE)
    handle3 = Handle ("std::vector<NtuplePairIndependentInfo>")
    label3 = ("pairIndep","NtupleEventPairIndep","Ntuple")

    # set up a file to hold the histogram
    outFileEx3 = TFile("outFileEx3.root","RECREATE")


    # set up a TH1F histogram and invoke the proper error setup - Sumw2
    UncorrectedSF = TH1F("UncorrectedSF","Uncorrected Jet Energy SF:Events/Bin:SF",100,0,2)
    UncorrectedSF.Sumw2()

    for event3 in events3:
        # use getByLabel, just like in cmsRun
        event3.getByLabel (label3, handle3)
        # get the product
        pairIndep3 = handle3.product()   
        for pI in pairIndep3:
            for jet in pI.jets():
                value = jet.JEC("Uncorrected")
                print 'jet uncorrected SF = ', value,
                UncorrectedSF.Fill(value)
                print jet.defaultBtagAlgorithm_Name(), 'raw score = ', jet.defaultBtagAlgorithm_RawScore(), 
                print 'pass/fail = ', jet.defaultBtagAlgorithm_isPassed()

    # write to file
    outFileEx3.cd()
    UncorrectedSF.Write()
    outFileEx3.Close()    


####################################
# EX-4 : print HLT accepted paths and preScales, rhos, and relativeIsols, tauIDs

if doExample4 :

    events4 = Events (FILE)
    handle4 = Handle ("std::vector<NtupleEvent>")
    label4 = ("NtupleEvent","NtupleEvent","Ntuple")



    for event4 in events4:
        event4.getByLabel (label4, handle4)
        pairs = handle4.product()
        for p in pairs:
            leg1 = p.leg1()
            print '**********************************************', leg1.leptonType()
            print '------------- accepted HLT paths and preScales ----------------------'
            for pathName in leg1.HLTAcceptedPath_Labels():
                print '[', pathName, " , ", leg1.HLTpath(pathName), ']' 
            print     
            print '------------- known Rho labels and values ----------------------'
            for rhoName in leg1.rho_Labels():
                print '[', rhoName, " , ", leg1.rho(rhoName), ']' 
            print     
            print '------------- known RelIso labels and values ----------------------'
            for isoName in leg1.relativeIsol_Labels():
                print '[', isoName, " , ", leg1.relativeIsol(isoName), ']' 
            print     
            print '------------- known tauID labels and values ----------------------'
            for idName in leg1.tauID_Labels():
                print '[', idName, " , ", leg1.tauID(idName), ']' 
            print   

