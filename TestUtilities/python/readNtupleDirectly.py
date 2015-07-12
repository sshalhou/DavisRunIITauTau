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
from ROOT import TH1F, TFile, TH2F
options = VarParsing ('python')
options.parseArguments()

######################
# choose which to run :

doExample1 = False
doExample2 = False
doExample3 = False
doExample4 = False
doExample5 = True

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



####################################
# EX-5 : print HLT filter info

if doExample5 :

    WILDCARDpathsToCheck = []
    WILDCARDpathsToCheck.append('HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v*') # path
    WILDCARDpathsToCheck.append('HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v*') # path
    WILDCARDpathsToCheck.append('HLT_Ele22_eta2p1_WP85_Gsf_LooseIsoPFTau20_v*') # path
    WILDCARDpathsToCheck.append('HLT_Ele27_eta2p1_WP85_Gsf_v*') # path
    WILDCARDpathsToCheck.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v*') # path
    WILDCARDpathsToCheck.append('HLT_IsoMu24_eta2p1_IterTrk02_v*') # path
    WILDCARDpathsToCheck.append('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v*') # path
    WILDCARDpathsToCheck.append('HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120_v*') # path




    events5 = Events (FILE)
    handle5 = Handle ("std::vector<NtupleEvent>")
    label5 = ("NtupleEvent","NtupleEvent","Ntuple")

    print '********************************************************'    
    print 'printing triggers from ConfigTupleTriggers_cfi with at least one leg passing all requirements : '    
    print '********************************************************'    

    # set up a file to hold the histogram
    outFileEx5 = TFile("outFileEx5.root","RECREATE")


    # set up a TH1F histogram and invoke the proper error setup - Sumw2
    triggerInfo = TH2F("TriggerLegSummary","Various Triggers for diTau Events with >=1 good leg;leg1 isGood;leg2 isGood",2,0,1.0001,2,0,1.0001)
    triggerInfo.Sumw2()

    for event5 in events5:
        event5.getByLabel (label5, handle5)
        pairs = handle5.product()
        for p in pairs:
            leg1 = p.leg1()
            leg2 = p.leg2()

            type1 = ''
            type2 = ''

            if leg1.leptonType()==1:
                type1 = 'ELECTRON' 
            elif leg1.leptonType()==2:
                type1 = 'MUON' 
            elif leg1.leptonType()==3:
                type1 = 'TAU' 

            if leg2.leptonType()==1:
                type2 = 'ELECTRON' 
            elif leg2.leptonType()==2:
                type2 = 'MUON' 
            elif leg2.leptonType()==3:
                type2 = 'TAU' 


            for apath in WILDCARDpathsToCheck:
                plotValue1 = 0.0 
                plotValue2 = 0.0   
                if p.isLeg1GoodForHLTPath(apath)==1.0 and p.isLeg2GoodForHLTPath(apath)==1.0 :
                    print 'for path ', apath , type1,'+',type2,
                    print ' pass all HLT accept+ trigger matching + filters for this trigger '
                    plotValue1 = 1.0
                    plotValue2 = 1.0

                elif p.isLeg1GoodForHLTPath(apath)==1.0 and p.isLeg2GoodForHLTPath(apath)==0.0 :
                    print 'for path ', apath , type1,'+',type2,
                    print ' only leg1 passes all HLT accept+ trigger matching + filters for this trigger '
                    plotValue1 = 1.0
                    plotValue2 = 0.0

                elif p.isLeg1GoodForHLTPath(apath)==0.0 and p.isLeg2GoodForHLTPath(apath)==1.0 :
                    print 'for path ', apath , type1,'+',type2,
                    print ' only leg2 passes all HLT accept+ trigger matching + filters for this trigger '
                    plotValue1 = 0.0
                    plotValue2 = 1.0

                #if type1=='TAU' and type2=='TAU' :
                if (plotValue1+plotValue2)!=0 :
                    triggerInfo.Fill(plotValue1,plotValue2)

    # write to file
    outFileEx5.cd()
    triggerInfo.Write()
    outFileEx5.Close()    

                # elif p.isLeg1GoodForHLTPath(apath)==0.0 and p.isLeg2GoodForHLTPath(apath)==0.0 :
                #     print 'for path ', apath , type1,'+',type2,
                #     print ' both fail '




            # print type, 'L3 PATHS = [',
            # for l3 in leg1.pathSummary_isL3():
            #     print l3, ',',
            # print '] Filters = [',    
            # for filter in leg1.pathSummary_filterListPassed():
            #     print filter, ',',
            # print '], L1 accepted filters = [',
            # for filter in leg1.L1acceptedFilters():
            #     print filter, ',',                
            # print '], L3 accepted filters = [',    
            # for filter in leg1.L3acceptedFilters():
            #     print filter, ',', 
            # print ']'

            # if leg2.leptonType()==0:
            #     type = '----- ELECTRON ----' 
            # if leg2.leptonType()==1:
            #     type = '----- MUON ----' 
            # if leg2.leptonType()==2:
            #     type = '----- TAU ----' 


            # print type, 'L3 PATHS = [',
            # for l3 in leg2.pathSummary_isL3():
            #     print l3, ',',
            # print '] Filters = [',    
            # for filter in leg2.pathSummary_filterListPassed():
            #     print filter, ',',
            # print '], L1 accepted filters = [',
            # for filter in leg2.L1acceptedFilters():
            #     print filter, ',',                
            # print '], L3 accepted filters = [',    
            # for filter in leg2.L3acceptedFilters():
            #     print filter, ',', 
            # print ']'

