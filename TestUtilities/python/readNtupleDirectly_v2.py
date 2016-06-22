import time
import sys
import os
import math
from array import array

FILE = "/uscms_data/d3/shalhout/RunIIWorking/UpdateEId/CMSSW_7_4_7/src/NtupleFile.root"


# import ROOT in batch mode                                                                                                                                                                                                                  
import sys                                                                                                                                                                                                                                   
oldargv = sys.argv[:]                                                                                                                                                                                                                        
sys.argv = [ '-b-' ]                                                                                                                                                                                                                         
import ROOT                                                                                                                                                                                                                                                                    
ROOT.gROOT.SetBatch(True)                                                                                                                                                                                                                                                      
sys.argv = oldargv                                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                               
# load FWLite C++ libraries                                                                                                                                                                                                                                                    
ROOT.gSystem.Load("libFWCoreFWLite.so");                                                                                                                                                                                                                                       
ROOT.gSystem.Load("libDataFormatsFWLite.so");                                                                                                                                                                                                                                  
ROOT.AutoLibraryLoader.enable()   


#import ROOT
#import sys
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
doExample5 = False
doExample6 = False
doExample7 = True

####################################
# EX-1 : print candidateType & isolations

if doExample1 :
    events = Events (FILE)
    handle = Handle ("std::vector<NtupleEvent>")
    label = "NtupleEvent:NtupleEvent:Ntuple"



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
    label2 = "pairIndep:NtupleEventPairIndep:Ntuple"


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
    label3 = "pairIndep:NtupleEventPairIndep:Ntuple"

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
                print 'pass/fail = ', jet.defaultBtagAlgorithmMediumWP_isPassed()

    # write to file
    outFileEx3.cd()
    UncorrectedSF.Write()
    outFileEx3.Close()    


####################################
# EX-4 : print HLT accepted paths and preScales, rhos, and relativeIsols, tauIDs

if doExample4 :

    events4 = Events (FILE)
    handle4 = Handle ("std::vector<NtupleEvent>")
    label4 = "NtupleEvent:NtupleEvent:Ntuple"



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
    label5 = "NtupleEvent:NtupleEvent:Ntuple"

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




####################################
# EX-6 : study HLT  for e+mu channel

if doExample6 :
    
    events6 = Events (FILE)
    handle6 = Handle ("std::vector<NtupleEvent>")
    label6 = "NtupleEvent:NtupleEvent:Ntuple"

    print '********************************************************'    
    print ' searching for ele+muon events in FILE ', FILE    
    print '********************************************************'    

 

    for event6 in events6:
        event6.getByLabel (label6, handle6)
        pairs = handle6.product()
        for p in pairs:
            leg1 = p.leg1()
            leg2 = p.leg2()
            type = p.CandidateEventType()
            if type == 2:
                print '--> found e+mu event with pTs of ', leg1.pt(), 'and', leg2.pt()
                print 'for HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoV_v1 have isGOOD == ',
                print p.isLeg1GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1'), 'and',
                print p.isLeg2GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1')
                print 'for HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1 have isGOOD == ',
                print p.isLeg1GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1'), 'and',
                print p.isLeg2GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1')

                print 'all good leg1 paths : \n',
                for path in p.isLeg1GoodForHLTPath_Labels():
                    print '-------> ',path
                print 'all good leg2 paths : \n',
                for path in p.isLeg2GoodForHLTPath_Labels():
                    print '-------> ',path



####################################
# EX-7 : study HLT  for e+mu channel

if doExample7 :
    
    events7 = Events (FILE)
    handle7 = Handle ("std::vector<NtupleEvent>")
    label7 = "NtupleEvent:NtupleEvent:DavisNtuple"

    print '********************************************************'    
    print ' HLT info object and filter dump for file ', FILE    
    print '********************************************************'    

    muf1 = 'hltL3crIsoL1sMu16erTauJet20erL1f0L2f10QL3f17QL3trkIsoFiltered0p09'
    muf2 = 'hltOverlapFilterIsoMu17LooseIsoPFTau20'

    tf1 = 'hltPFTau20TrackLooseIsoAgainstMuon'
    tf2 = 'hltOverlapFilterIsoMu17LooseIsoPFTau20'

    singleMuf1 = 'hltL3crIsoL1sMu20Eta2p1L1f0L2f10QL3f24QL3trkIsoFiltered0p09'


    for event7 in events7:
        event7.getByLabel (label7, handle7)
        pairs = handle7.product()
        for p in pairs:
            leg1 = p.leg1()
            leg2 = p.leg2()
            objs1 = p.leg1_trigMatches()
            objs2 = p.leg2_trigMatches()
            type = p.CandidateEventType()
            if type == 5:
                print '==================================================================== '
                print ' found mu+Tau pair with reco pTs of ', leg1.pt(), 'and', leg2.pt()
                print ' found mu+Tau pair with reco dxy of ', leg1.dxy(), 'and', leg2.dxy()
                print ' found mu+Tau pair with reco dz of ', leg1.dz(), 'and', leg2.dz()
                print ' found mu+Tau pair with reco dxy of ', leg1.charge(), 'and', leg2.charge()
		print ' muon medium ID for leg 1 = ', leg1.passesMediumMuonId()

                print '==================================================================== '
                print '     at event level HLT path HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1 is ', leg1.HLTpath('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1')   
                print '     at event level HLT path HLT_IsoMu24_eta2p1_v1 is ', leg1.HLTpath('HLT_IsoMu24_eta2p1_v1')   
                print '         now considering only the single muon trigger check trig-objects & filters on the muon leg : '
                print '         the only filter required on the muon leg of isoMu24 is ', singleMuf1
                print '         reco muon (leg1) is matched to ', objs1.size(), 'trigger objects'
                for t1 in objs1 :
                    print '         ->  trig obj with pt, eta, type = ', t1.p4().pt(), t1.p4().eta(), t1.triggerObjectTypes()[0], 'double mu fil 1=', t1.HLTFilter(muf1), 'double mu fil 2=', t1.HLTFilter(muf2), 
                    print ' single mu fil= ', t1.HLTFilter(singleMuf1)

                print '         reco tau (leg2) is matched to ', objs2.size(), 'trigger objects'
                for t2 in objs2 :
                   print '         --->  trig obj with pt, eta, type = ', t2.p4().pt(), t2.p4().eta(), t2.triggerObjectTypes()[0], 'fil 1=', t2.HLTFilter(tf1), 'fil 2=', t2.HLTFilter(tf2)

                    # if(t2.HLTFilter(tf1) == 1.0):
                    #     print tf1, '         --->  trig obj with pt, type = ', t2.p4().pt(), t2.triggerObjectTypes()[0], 'pass/fail filter ', 'is ', t2.HLTFilter(tf1), '<---- GOOD TRIG OBJECT AND FILTER'
                    # elif(t2.HLTFilter(tf2) == 1.0):
                    #     print tf2, '         --->  trig obj with pt, type = ', t2.p4().pt(), t2.triggerObjectTypes()[0], 'pass/fail filter ', 'is ', t2.HLTFilter(tf2), '<---- GOOD TRIG OBJECT AND FILTER'                        
                    # else:
                    #     print '         --->  trig obj with pt, type = ', t2.p4().pt(), t2.triggerObjectTypes()[0], 'pass/fail filter ', 'is ', t2.HLTFilter(tf1), t2.HLTFilter(tf2)

                print '   is leg1 and leg2 good for HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1 : leg1 = ', p.isLeg1GoodForHLTPath('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1'),' leg2 = ',p.isLeg2GoodForHLTPath('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1')
                print '   is leg1 good for HLT_IsoMu24_eta2p1_v1 ', p.isLeg1GoodForHLTPath('HLT_IsoMu24_eta2p1_v1')
                #print '   reco leg 1 is matched to ', objs1.size(), 'trigger objects'
                # for t1 in objs1 :
                #     print 'mathched trigger object with pt, type = ', t1.p4().pt(), t1.triggerObjectTypes()[0]
                #     fil1 = t1.HLTFilter_labels()
                #     print 'has good filters : ',
                #     for fil in fil1:
                #         print fil,

                # print '   reco leg 2 is matched to ', objs2.size(), 'trigger objects'
                # for t2 in objs2 :
                #     print t2.p4().pt()



                # print 'for HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoV_v1 have isGOOD == ',
                # print p.isLeg1GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1'), 'and',
                # print p.isLeg2GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1')
                # print 'for HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1 have isGOOD == ',
                # print p.isLeg1GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1'), 'and',
                # print p.isLeg2GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1')

                # print 'all good leg1 paths : \n',
                # for path in p.isLeg1GoodForHLTPath_Labels():
                #     print '-------> ',path
                # print 'all good leg2 paths : \n',
                # for path in p.isLeg2GoodForHLTPath_Labels():
                #     print '-------> ',path



