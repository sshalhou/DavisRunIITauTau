####################################################################################################
# config file containing all trigger setup info for HLT pats at the event level
# and also for lepton-trigObject matching

import FWCore.ParameterSet.Config as cms
from doubleHyphen_string_concatonator import doubleHyphen_string_concatonator

####################################################################################################
# User Provided Arguments for Trigger Setup : 
####################################################################################################
#	- trigger object match max DR
#
#	- trigger object match types: cms.vint32(+81, +82)
#
#  			see :  https://github.com/cms-sw/cmssw/blob/CMSSW_7_2_X/DataFormats/HLTReco/interface/TriggerTypeDefs.h
#
#   - specific path and filters to summarize (vstring with components sep. by --): 
#
#	    vstring('PATHNAME1--FILTER REQ. AND/OR--FILTER_1--FILTER_2--FILTER_N',
#		  	     PATHNAME2--FILTER REQ. AND/OR--FILTER_1--FILTER_2--FILTER_N')
#
#       Note : HLT_SOMETHING_v* version wildcards are supported, but in that case be careful of changing
#		       filter requirements
#								
###############
# *** NOTES ***
###############
# 
# [1a] ALL HLT paths that were accepted for the event are embedded 
#      during creation of CustomPat{e,mu,tau} Collections --> these are UserFloat("HLT_XYZ_v1")
#      note : cuts version wildcards not supported at this stage - yet	
#
# [1b] ALL HLT paths that were accepted for the event are kept in NtupleEvent's 
#	   NtupleLeptons (i.e. leg1() and leg2(); see HLTpath function in NtupleLepton.h) 
#      note : version wildcards (_v*) are supported in the HLTpath function
# 
# [2] ALL TriggerObjects matched to leg1 and leg2 meeting DR and object match type requirments are stored in 
#     NtupleEvent as a vector of NtupleTrigObject (i.e. leg1_trigMatches and leg2_trigMatches)
#
# [3a] Each NtupleTrigObject retains isL3, isLF, & isBoth
#     (see https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATTrigger#TriggerObjectStandAlone)   
#     evaluated for each accepted HLT path
#
# [3b] Each NtupleTrigObject has a list of all Filters the object satisfies (from any HLT path, not just accepted ones)  
#
# [4] Summary Variables : For ease of checking HLT paths, trigger matching & filters, NtupleEvent now contains 
#     the following built in functions :
#
#						isLeg1GoodForHLTPath('HLT_WHATEVER')
#                       isLeg2GoodForHLTPath('HLT_WHATEVER')
#
#    these return 1.0 if  'specific path and filters to summarize' are satisfied by the given leg
#
####################################################################################################

####################################################################################################
# Configuration :
####################################################################################################

# DR match between lepton at reco and the triggerObject

electronTriggerMatch_DR = cms.double(0.3)
muonTriggerMatch_DR = cms.double(0.3)
tauTriggerMatch_DR = cms.double(0.5)

# allowed types for triggerObject matching

electronTriggerMatch_Types = cms.vint32(+81, +82)
muonTriggerMatch_Types = cms.vint32(+83)
tauTriggerMatch_Types = cms.vint32(-86,+84)


########################
# user should modify the append statements below to change lepton trigger settings
# strings will be (--) concatenated to form one string 

# master list to hold all paths & filters, will be converted to vsrting

electron_masterList_ = []
muon_masterList_ = []
tau_masterList_ = []


# specific path strings to be concatenated and then grouped into one vstring object
# don't forget to append to masterList_ 

#========================================================
#---------------------------------
elist1_ = []
elist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1') # path
elist1_.append('AND') # AND or OR of the following filters
elist1_.append('hltMu23Ele12GsfTrackIsoLegEle12GsfCaloIdTrackIdIsoMediumWPFilter') # filter
electron_masterList_.append(elist1_)

#---------------------------------
elist2_ = []
elist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1') # path
elist2_.append('AND') # AND or OR of the following filters
elist2_.append('hltMu8Ele23GsfTrackIsoLegEle23GsfCaloIdTrackIdIsoMediumWPFilter') # filter
electron_masterList_.append(elist2_)


#---------------------------------
elist3_ = []
elist3_.append('HLT_Ele22_eta2p1_WP85_Gsf_LooseIsoPFTau20_v1') # path
elist3_.append('AND') # AND or OR of the following filters
elist3_.append('hltOverlapFilterIsoEle22WP85GsfLooseIsoPFTau20') # filter
electron_masterList_.append(elist3_)

#---------------------------------
elist4_ = []
elist4_.append('HLT_Ele27_eta2p1_WP85_Gsf_v1') # path
elist4_.append('AND') # AND or OR of the following filters
elist4_.append('hltEle27WP85GsfTrackIsoFilter') # filter
electron_masterList_.append(elist4_)

#========================================================
#---------------------------------
mlist1_ = []
mlist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1') # path
mlist1_.append('AND') # AND or OR of the following filters
mlist1_.append('hltL1Mu12EG7L3IsoMuFiltered23') # filter
muon_masterList_.append(mlist1_)

#---------------------------------
mlist2_ = []
mlist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1') # path
mlist2_.append('AND') # AND or OR of the following filters
mlist2_.append('hltL1sL1Mu5EG20ORL1Mu5IsoEG18L3IsoFiltered8') # filter
muon_masterList_.append(mlist2_)


#---------------------------------
mlist3_ = []
mlist3_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v*') # path

#mlist3_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1') # path
mlist3_.append('AND') # AND or OR of the following filters
mlist3_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
muon_masterList_.append(mlist3_)

#---------------------------------
mlist4_ = []
mlist4_.append('HLT_IsoMu24_eta2p1_IterTrk02_v1') # path
mlist4_.append('AND') # AND or OR of the following filters
mlist4_.append('hltL3crIsoL1sMu20Eta2p1L1f0L2f20QL3f24QL3crIsoRhoFiltered0p15IterTrk02') # filter
muon_masterList_.append(mlist4_)

#========================================================
#---------------------------------
tlist1_ = []
tlist1_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v*') # path
#tlist1_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1') # path
tlist1_.append('AND') # AND or OR of the following filters
tlist1_.append('hltL1sMu16erTauJet20er') # filter
tlist1_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
tau_masterList_.append(tlist1_)



#---------------------------------
tlist2_ = []
tlist2_.append('HLT_Ele22_eta2p1_WP85_Gsf_LooseIsoPFTau20_v1') # path
tlist2_.append('AND') # AND or OR of the following filters
tlist2_.append('hltL1sL1IsoEG20erTauJet20er') # filter
tlist2_.append('hltOverlapFilterIsoEle22WP85GsfLooseIsoPFTau20') # filter
tau_masterList_.append(tlist2_)

#---------------------------------
tlist3_ = []
tlist3_.append('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v1') # path
tlist3_.append('AND') # AND or OR of the following filters
tlist3_.append('hltL1sDoubleTauJet36erORDoubleTauJet68er') # AND or OR of the following filters
tlist3_.append('hltDoubleL2IsoTau35eta2p1') # filter
tlist3_.append('hltDoublePFTau40TrackPt1MediumIsolationDz02Reg') # filter
tau_masterList_.append(tlist3_)


#---------------------------------
tlist4_ = []
tlist4_.append('HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120_v1') # path
tlist4_.append('AND') # AND or OR of the following filters
tlist4_.append('hltSingleL2Tau35eta2p1') # AND or OR of the following filters
tlist4_.append('hltPFTau50TrackPt30LooseAbsOrRelIso') # filter
tau_masterList_.append(tlist4_)



####################################################################################################
# form the actual vsrting to be passed  -- electrons

electronTriggerPathsAndFilters = cms.vstring()

for alist in electron_masterList_:
	electronTriggerPathsAndFilters.append(doubleHyphen_string_concatonator(alist))

####################################################################################################
# form the actual vsrting to be passed  -- muons

muonTriggerPathsAndFilters = cms.vstring()

for alist in muon_masterList_:
	muonTriggerPathsAndFilters.append(doubleHyphen_string_concatonator(alist))

####################################################################################################
# form the actual vsrting to be passed  -- taus

tauTriggerPathsAndFilters = cms.vstring()

for alist in tau_masterList_:
	tauTriggerPathsAndFilters.append(doubleHyphen_string_concatonator(alist))



####################################################################################################
####################################################################################################
####################################################################################################




