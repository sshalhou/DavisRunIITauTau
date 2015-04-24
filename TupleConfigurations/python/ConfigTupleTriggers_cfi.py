####################################################################################################
# config file containing all trigger selection summaries and vetos for electrons, muons, and taus
#

import FWCore.ParameterSet.Config as cms
from doubleHyphen_string_concatonator import doubleHyphen_string_concatonator

####################################################################################################
# trigger Setup : 
#
#	- trigger object match max DR
#
#	- trigger object match types: cms.vint32(+81, +82)
#
#  			see :  https://github.com/cms-sw/cmssw/blob/CMSSW_7_2_X/DataFormats/HLTReco/interface/TriggerTypeDefs.h
#
#   - specific path and filters to summarize (vstring with components sep. by --): 
#
#	    vstring('SummaryVarName1--PATHNAME1--FILTER REQ. AND/OR--FILTER_1--FILTER_2--FILTER_N',
#		  	     SummaryVarName2--PATHNAME2--FILTER REQ. AND/OR--FILTER_1--FILTER_2--FILTER_N')
#								
#  by default full info is stored for each reco lepton matched to one of the allowed trigger types
#  the summary vstring just simplifies access
#  to decode the value attached to each element of the vstring use :
#
#    -- finalValue :
#   			if(isBoth) finalValue+= 1000.0;
#   			if(isL3) finalValue+= 100.0;
#   			if(isLF) finalValue+= 10.0;
#   			if(FilterListPassed) finalValue+= 1.0;
#				(so 1111.0 passes everything, 0.0 would fail all, etc.)
#
####################################################################################################


# DR match between lepton at reco and the triggerObject

electronTriggerMatch_DR = cms.double(0.5)
muonTriggerMatch_DR = cms.double(0.5)
tauTriggerMatch_DR = cms.double(0.5)

# allowed types for triggerObject matching

electronTriggerMatch_Types = cms.vint32(+81, +82)
muonTriggerMatch_Types = cms.vint32(+83)
tauTriggerMatch_Types = cms.vint32(+84)


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
elist1_.append('trigObjectPathSummary_eleMu_Mu23_Ele12') # summary variable name 
elist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1') # path
elist1_.append('AND') # AND or OR of the following filters
elist1_.append('hltMu23Ele12GsfTrackIsoLegEle12GsfCaloIdTrackIdIsoMediumWPFilter') # filter
electron_masterList_.append(elist1_)

#---------------------------------
elist2_ = []
elist2_.append('trigObjectPathSummary_eleMu_Mu8_Ele23') # summary variable name 
elist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1') # path
elist2_.append('AND') # AND or OR of the following filters
elist2_.append('hltMu8Ele23GsfTrackIsoLegEle23GsfCaloIdTrackIdIsoMediumWPFilter') # filter
electron_masterList_.append(elist2_)


#---------------------------------
elist3_ = []
elist3_.append('trigObjectPathSummary_eleTau_Ele22_Tau20') #  summary variable name 
elist3_.append('HLT_Ele22_eta2p1_WP85_Gsf_LooseIsoPFTau20_v1') # path
elist3_.append('AND') # AND or OR of the following filters
elist3_.append('hltOverlapFilterIsoEle22WP85GsfLooseIsoPFTau20') # filter
electron_masterList_.append(elist3_)

#---------------------------------
elist4_ = []
elist4_.append('trigObjectPathSummary_eleTau_Ele27') #  summary variable name 
elist4_.append('HLT_Ele27_eta2p1_WP85_Gsf_v1') # path
elist4_.append('AND') # AND or OR of the following filters
elist4_.append('hltEle27WP85GsfTrackIsoFilter') # filter
electron_masterList_.append(elist4_)

#========================================================
#---------------------------------
mlist1_ = []
mlist1_.append('trigObjectPathSummary_eleMu_Mu23_Ele12') # summary variable name 
mlist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_Gsf_CaloId_TrackId_Iso_MediumWP_v1') # path
mlist1_.append('AND') # AND or OR of the following filters
mlist1_.append('hltL1Mu12EG7L3IsoMuFiltered23') # filter
muon_masterList_.append(mlist1_)

#---------------------------------
mlist2_ = []
mlist2_.append('trigObjectPathSummary_eleMu_Mu8_Ele23') # summary variable name 
mlist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_Gsf_CaloId_TrackId_Iso_MediumWP_v1') # path
mlist2_.append('AND') # AND or OR of the following filters
mlist2_.append('hltL1sL1Mu5EG20ORL1Mu5IsoEG18L3IsoFiltered8') # filter
muon_masterList_.append(mlist2_)


#---------------------------------
mlist3_ = []
mlist3_.append('trigObjectPathSummary_IsoMu17_Tau20') # summary variable name 
mlist3_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1') # path
mlist3_.append('AND') # AND or OR of the following filters
mlist3_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
muon_masterList_.append(mlist3_)

#---------------------------------
mlist4_ = []
mlist4_.append('trigObjectPathSummary_IsoMu24') # summary variable name 
mlist4_.append('HLT_IsoMu24_eta2p1_IterTrk02_v1') # path
mlist4_.append('AND') # AND or OR of the following filters
mlist4_.append('hltL3crIsoL1sMu20Eta2p1L1f0L2f20QL3f24QL3crIsoRhoFiltered0p15IterTrk02') # filter
muon_masterList_.append(mlist4_)

#========================================================
#---------------------------------
tlist1_ = []
tlist1_.append('trigObjectPathSummary_IsoMu17_Tau20') # summary variable name 
tlist1_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1') # path
tlist1_.append('OR') # AND or OR of the following filters
tlist1_.append('hltL1sMu16erTauJet20er') # filter
tlist1_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
tau_masterList_.append(tlist1_)



#---------------------------------
tlist2_ = []
tlist2_.append('trigObjectPathSummary_eleTau_Ele22_Tau20') #  summary variable name 
tlist2_.append('HLT_Ele22_eta2p1_WP85_Gsf_LooseIsoPFTau20_v1') # path
tlist2_.append('OR') # AND or OR of the following filters
tlist2_.append('hltL1sL1IsoEG20erTauJet20er') # filter
tlist2_.append('hltOverlapFilterIsoEle22WP85GsfLooseIsoPFTau20') # filter
tau_masterList_.append(tlist2_)

#---------------------------------
tlist3_ = []
tlist3_.append('trigObjectPathSummary_DoubleMediumIsoPFTau40') #  summary variable name 
tlist3_.append('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v1') # path
tlist3_.append('OR') # AND or OR of the following filters
tlist3_.append('hltL1sDoubleTauJet36erORDoubleTauJet68er') # AND or OR of the following filters
tlist3_.append('hltDoubleL2IsoTau35eta2p1') # filter
tlist3_.append('hltDoublePFTau40TrackPt1MediumIsolationDz02Reg') # filter
tau_masterList_.append(tlist3_)


#---------------------------------
tlist4_ = []
tlist4_.append('trigObjectPathSummary_LooseIsoPFTau50') #  summary variable name 
tlist4_.append('HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120_v1') # path
tlist4_.append('OR') # AND or OR of the following filters
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




