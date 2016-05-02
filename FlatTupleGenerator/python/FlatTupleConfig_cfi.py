# master config file for FlatTupleGenerator 
# define PSets for various settings and selection cuts
# -- S. Shalhout June 18, 2015

import FWCore.ParameterSet.Config as cms
from DavisRunIITauTau.TupleConfigurations.and_string_concatonator import and_string_concatonator

##########################################
# set up SVMass  @ FlatTuple level	     #
##########################################
# The computation at FlatTuple level contains 
# options for recoil corrections and systematics
# when using MVA MET. In addition you can run SVFit using
# PFMET and/or puppiMET
# warning : each additional true slows down the code!
# warning : any SVFit computed at Ntuple level will be replaced
#     by the flatTuple value (if recomputed)
##########################################

SVMASS_LOG_M_FlatTuple = 0.0
SVMASS_VERBOSE_FlatTuple = True

############################################
# SVFit + different METs				   #	
############################################


USE_MVAMET_FOR_SVFit_AT_FlatTuple = True  				# this is the default choice (recoil corrected MVA MET)
USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple = True
USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple = True
USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple = True
USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple = True
USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple = True
USE_PFMET_FOR_SVFit_AT_FlatTuple = True  			
USE_PUPPIMET_FOR_SVFit_AT_FlatTuple = True  			

print '******************************************'
print '********* SV FIT SETTINGS @ FLATTUPLE ****'
print '******************************************'

count_SVFit = 0

if USE_MVAMET_FOR_SVFit_AT_FlatTuple is True:
	count_SVFit += 1
if USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple is True:
	count_SVFit += 1
if USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple is True:
	count_SVFit += 1
if USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple is True:
	count_SVFit += 1
if USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple is True:
	count_SVFit += 1
if USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple is True:
	count_SVFit += 1
if USE_PFMET_FOR_SVFit_AT_FlatTuple is True:
	count_SVFit += 1
if USE_PUPPIMET_FOR_SVFit_AT_FlatTuple is True:
	count_SVFit += 1


print '**************************************************'
if count_SVFit == 0:
	print 'WARNING : SVFit calls are off at FlatTuple level, will take any values from Ntuple as they are'
	print '**************************************************'

if count_SVFit > 0:
	print 'will (re-)compute SVmass (@ FLATTUPLE level) with log_m term = ', SVMASS_LOG_M_FlatTuple
	print '*** this will cause FLATUPLE to ignore (& replace) any SVmass values read from NTUPLE level ***'	
	print '**************************************************'
	print "Run SVFit with MVAMET ........ ", USE_MVAMET_FOR_SVFit_AT_FlatTuple
	print "Run SVFit with MVAMET_uncorrected ........ ", USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple
	print "Run SVFit with MVAMET_responseUP ........ ", USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple
	print "Run SVFit with MVAMET_responseDOWN ........ ", USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple
	print "Run SVFit with MVAMET_resolutionUP ........ ", USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple
	print "Run SVFit with MVAMET_resolutionDOWN ........ ", USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple
	print "Run SVFit with PFMET ........ ", USE_PFMET_FOR_SVFit_AT_FlatTuple
	print "Run SVFit with PUPPIMET ........ ", USE_PUPPIMET_FOR_SVFit_AT_FlatTuple
	print '**************************************************'

if count_SVFit > 1:
	print 'WARNING : YOU HAVE ASKED FOR ', count_SVFit, ' DIFFERENT SVFit Calls at FlatTuple level, this will slow down the code'
	print '**************************************************'





print '******************************************'
print '******************************************'



svMassAtFlatTupleConfig = cms.PSet(
	USE_MVAMET_FOR_SVFit_AT_FlatTuple_ = cms.bool(USE_MVAMET_FOR_SVFit_AT_FlatTuple),
	USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple_ = cms.bool(USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple),
	USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple_ = cms.bool(USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple),
	USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple_ = cms.bool(USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple),
	USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple_ = cms.bool(USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple),
	USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple_ = cms.bool(USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple),
	USE_PFMET_FOR_SVFit_AT_FlatTuple_ = cms.bool(USE_PFMET_FOR_SVFit_AT_FlatTuple),
	USE_PUPPIMET_FOR_SVFit_AT_FlatTuple_ = cms.bool(USE_PUPPIMET_FOR_SVFit_AT_FlatTuple),
	flatTuple_svMassVerbose = cms.bool(SVMASS_VERBOSE_FlatTuple),
	flatTuple_logMterm = cms.double(SVMASS_LOG_M_FlatTuple)
	)




# individual object cuts used to build the PSets 
# each line appended will be concatenated (using &&) into a single cut string

# electron in EleTau final state :
ele_EleTau = []
ele_EleTau.append("pt>23")
ele_EleTau.append("abs(eta)<2.1")
ele_EleTau.append("abs(dxy)<0.045")
ele_EleTau.append("abs(dz)<0.2")
ele_EleTau.append("passFail_electronMVA80==1.0")
ele_EleTau.append("passConversionVeto==1.0")
ele_EleTau.append("numberOfMissingInnerHits<=1")
#ele_EleTau.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.1")


# electron in EleMuon final state :
ele_EleMuon = []
ele_EleMuon.append("pt>13")
ele_EleMuon.append("abs(eta)<2.5")
ele_EleMuon.append("abs(dxy)<0.045")
ele_EleMuon.append("abs(dz)<0.2")
ele_EleMuon.append("passFail_electronMVA80==1.0")
ele_EleMuon.append("passConversionVeto==1.0")
ele_EleMuon.append("numberOfMissingInnerHits<=1")

#ele_EleMuon.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.15")


# muon in MuonTau final state :
muon_MuonTau = []
muon_MuonTau.append("pt>18")
muon_MuonTau.append("abs(eta)<2.1")
muon_MuonTau.append("abs(dxy)<0.045")
muon_MuonTau.append("abs(dz)<0.2")
muon_MuonTau.append("passesMediumMuonId==1.0")
#muon_MuonTau.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.1")


# muon in EleMuon final state :
muon_EleMuon = []
muon_EleMuon.append("pt>10")
muon_EleMuon.append("abs(eta)<2.4")
muon_EleMuon.append("abs(dxy)<0.045")
muon_EleMuon.append("abs(dz)<0.2")
muon_EleMuon.append("passesMediumMuonId==1.0")
#muon_EleMuon.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.15")




# tau in MuonTau final state :
tau_MuonTau = []
tau_MuonTau.append("pt>20")
tau_MuonTau.append("abs(eta)<2.3")
tau_MuonTau.append("tauID('decayModeFindingNewDMs') > 0.5")                                        
tau_MuonTau.append("abs(dz)<0.2")
#tau_MuonTau.append("abs(dzTauVertex)==0.0")
tau_MuonTau.append("abs(charge)==1.0")


# tau in TauTau final state :
tau_TauTau = []
tau_TauTau.append("pt>45")
tau_TauTau.append("abs(eta)<2.1")
tau_TauTau.append("tauID('decayModeFindingNewDMs') > 0.5")                                        
tau_TauTau.append("abs(dz)<0.2")
#tau_TauTau.append("abs(dzTauVertex)==0.0")
tau_TauTau.append("abs(charge)==1.0")


# tau in EleTau final state :
tau_EleTau = []
tau_EleTau.append("pt>20")
tau_EleTau.append("abs(eta)<2.3")
tau_EleTau.append("tauID('decayModeFindingNewDMs') > 0.5")                                        
tau_EleTau.append("abs(dz)<0.2")
#tau_EleTau.append("abs(dzTauVertex)==0.0")
tau_EleTau.append("abs(charge)==1.0")




cut_ele_EleTau = cms.string(and_string_concatonator(ele_EleTau))
cut_ele_EleMuon = cms.string(and_string_concatonator(ele_EleMuon))
cut_muon_MuonTau = cms.string(and_string_concatonator(muon_MuonTau))
cut_muon_EleMuon = cms.string(and_string_concatonator(muon_EleMuon))
cut_tau_TauTau = cms.string(and_string_concatonator(tau_TauTau))
cut_tau_EleTau = cms.string(and_string_concatonator(tau_EleTau))
cut_tau_MuonTau = cms.string(and_string_concatonator(tau_MuonTau))




#################################################################
# trigger cuts for Spring 15 MC mini aod v2  - HLT (_v) VERSION MATTERS!!!  #
#################################################################

emuTriggerCutSpring15MCminiAODv2 = "((isLeg1GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') &&\
	isLeg2GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') && leg2.pt>24) ||\
   (isLeg1GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*') &&\
	isLeg2GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*') && leg1.pt>24))"

tautauTriggerCutSpring15MCminiAODv2 = "(isLeg1GoodForHLTPath('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v*') \
	&& isLeg2GoodForHLTPath('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v*'))"

etauTriggerCutSpring15MCminiAODv2 = "(isLeg1GoodForHLTPath('HLT_Ele22_eta2p1_WP75_Gsf_v*') && leg1MaxPtTriggerObjMatch > 23)"

mtauTriggerCutSpring15MCminiAODv2 = "(isLeg1GoodForHLTPath('HLT_IsoMu17_eta2p1_v*') && leg1MaxPtTriggerObjMatch > 18)"





#################################################################
# trigger cuts for Spring 15 MC  - HLT (_v) VERSION MATTERS!!!  #
#################################################################

emuTriggerCutSpring15 = "((isLeg1GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1') &&\
	isLeg2GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1') && leg2.pt>24) ||\
   (isLeg1GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1') &&\
	isLeg2GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1') && leg1.pt>24))"

tautauTriggerCutSpring15 = "(isLeg1GoodForHLTPath('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v1') \
	&& isLeg2GoodForHLTPath('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v1'))"

etauTriggerCutSpring15 = "(isLeg1GoodForHLTPath('HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20_v1')\
	 && isLeg2GoodForHLTPath('HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20_v1')) \
	|| ((isLeg1GoodForHLTPath('HLT_Ele32_eta2p1_WP75_Gsf_v1') && leg1.pt>33))"

mtauTriggerCutSpring15 = "(isLeg1GoodForHLTPath('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1') \
	&& isLeg2GoodForHLTPath('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1'))\
	|| ((isLeg1GoodForHLTPath('HLT_IsoMu24_eta2p1_v1') && leg1.pt>25))"




#################################################################
# trigger cuts for Run2015C Data  - HLT (_v) VERSION MATTERS!!! #
# special note :  this is the same for Run2015B Data sine
# it has identical path names to C (some filters differ though!)
#################################################################

emuTriggerCutRun2015C = "((isLeg1GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2') &&\
	isLeg2GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2') && leg2.pt>24) ||\
   (isLeg1GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2') &&\
	isLeg2GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2') && leg1.pt>24))"

tautauTriggerCutRun2015C = "(isLeg1GoodForHLTPath('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v2') \
	&& isLeg2GoodForHLTPath('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v2'))"



etauTriggerCutRun2015C = "(isLeg1GoodForHLTPath('HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v1')\
	 && isLeg2GoodForHLTPath('HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v1')) \
	|| ((isLeg1GoodForHLTPath('HLT_Ele32_eta2p1_WPTight_Gsf_v1') && leg1.pt>33))"

mtauTriggerCutRun2015C = "(isLeg1GoodForHLTPath('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v2') \
	&& isLeg2GoodForHLTPath('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v2'))\
	|| ((isLeg1GoodForHLTPath('HLT_IsoMu24_eta2p1_v2') && leg1.pt>25))"


#################################################################
# trigger cuts for Run2015D Data  - HLT (_v) VERSION MATTERS!!! #
# special note :  this is the same for Run2015B Data since
# it has identical path names to D (some filters differ though!)
#################################################################

emuTriggerCutRun2015D = "((isLeg1GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') &&\
	isLeg2GoodForHLTPath('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') && leg2.pt>24) ||\
   (isLeg1GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*') &&\
	isLeg2GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*') && leg1.pt>24))"

tautauTriggerCutRun2015D = "(isLeg1GoodForHLTPath('HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*') \
	&& isLeg2GoodForHLTPath('HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*'))"



etauTriggerCutRun2015D = "(isLeg1GoodForHLTPath('HLT_Ele23_WPLoose_Gsf_v*'))"


mtauTriggerCutRun2015D = "(isLeg1GoodForHLTPath('HLT_IsoMu18_v*'))"




#################################################################
# trigger cuts for Fall 15 MC  - HLT !!!  #
#################################################################

emuTriggerCutFall15MCminiAOD = "((isLeg1GoodForHLTPath('HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') &&\
	isLeg2GoodForHLTPath('HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') && leg2.pt>18) ||\
    (isLeg1GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*') &&\
	isLeg2GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*') && leg1.pt>18))"


tautauTriggerCutFall15MCminiAOD = "(isLeg1GoodForHLTPath('HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*')\
	&& isLeg2GoodForHLTPath('HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*')\
	&& PairPassesDoubleTauIsoTau28MatchCut)"

etauTriggerCutFall15MCminiAOD = "(isLeg1GoodForHLTPath('HLT_Ele23_WPLoose_Gsf_v*'))"

mtauTriggerCutFall15MCminiAOD = "(isLeg1GoodForHLTPath('HLT_IsoMu18_v*'))"




################################
# concatenate trigger cuts     #
################################
# always include isRealData checks to 
# avoid the data condition 
# triggering the mc condition
# in cases where DATA & MC HLT conditions
# are the same, but MC has extra pt or isoTau match cuts
################################

emuTriggerCut = cms.string(" ( !isRealData && "+emuTriggerCutFall15MCminiAOD+" ) || ( "+emuTriggerCutRun2015D + " && isRealData )" )
tautauTriggerCut = cms.string(" ( !isRealData && "+tautauTriggerCutFall15MCminiAOD+" ) || ( "+tautauTriggerCutRun2015D+ " && isRealData )")
etauTriggerCut = cms.string(" ( !isRealData && "+etauTriggerCutFall15MCminiAOD+" ) || ( "+etauTriggerCutRun2015D+ " && isRealData )")
mtauTriggerCut  = cms.string(" ( !isRealData && "+mtauTriggerCutFall15MCminiAOD+" ) || ( "+mtauTriggerCutRun2015D+ " && isRealData )")


# emuTriggerCut = cms.string(emuTriggerCutFall15MCminiAOD+" || "+emuTriggerCutRun2015D)
# tautauTriggerCut = cms.string(tautauTriggerCutFall15MCminiAOD+" || "+tautauTriggerCutRun2015D)
# etauTriggerCut = cms.string(etauTriggerCutFall15MCminiAOD+" || "+etauTriggerCutRun2015D)
# mtauTriggerCut  = cms.string(mtauTriggerCutFall15MCminiAOD+" || "+mtauTriggerCutRun2015D)



# emuTriggerCut = cms.string(emuTriggerCutSpring15MCminiAODv2+" || "+emuTriggerCutRun2015D)
# tautauTriggerCut = cms.string(tautauTriggerCutSpring15MCminiAODv2+" || "+tautauTriggerCutRun2015D)
# etauTriggerCut = cms.string(etauTriggerCutSpring15MCminiAODv2+" || "+etauTriggerCutRun2015D)
# mtauTriggerCut  = cms.string(mtauTriggerCutSpring15MCminiAODv2+" || "+mtauTriggerCutRun2015D)



# emuTriggerCut = cms.string("1==1")
# tautauTriggerCut = cms.string("1==1")
# etauTriggerCut = cms.string("1==1")
# mtauTriggerCut  = cms.string("1==1")


print "*********************************************************"
print "FlatTuple trigger cuts set to : "
print "*********************************************************"
print " emuTriggerCut = ", emuTriggerCut
print "-----------------------------------------------------------"
print " tautauTriggerCut = ", tautauTriggerCut
print "-----------------------------------------------------------"
print " etauTriggerCut = ", etauTriggerCut
print "-----------------------------------------------------------"
print " mtauTriggerCut = ", mtauTriggerCut
print "*********************************************************"
print " should make code so that you don't need to manually adjust this "

# VPSet containing selections for different final states, if PSet is not
# provided for a given final state the 
# the events will omitted


# main cut vector PSet :
theCuts = cms.VPSet(

		cms.PSet(   candidatePairType = cms.string("EleTau"),
					electronID = cut_ele_EleTau,
					tauID = cut_tau_EleTau,
					minDR = cms.double(0.5),
					trigger = etauTriggerCut
				),
		cms.PSet(   candidatePairType = cms.string("EleMuon"),
					electronID = cut_ele_EleMuon,
					muonID = cut_muon_EleMuon,
					minDR = cms.double(0.3),
					trigger = emuTriggerCut

				),
		cms.PSet(   candidatePairType = cms.string("MuonTau"),
					muonID = cut_muon_MuonTau,
					tauID = cut_tau_MuonTau,
					minDR = cms.double(0.5),
					trigger = mtauTriggerCut

				),
		cms.PSet(   candidatePairType = cms.string("TauTau"),
					tauID = cut_tau_TauTau,
					minDR = cms.double(0.5),
					trigger = tautauTriggerCut

				)
	)


minimalCuts = cms.VPSet(

		cms.PSet(   candidatePairType = cms.string("EleTau"),
					minDR = cms.double(0.5),
					trigger = etauTriggerCut
				),
		cms.PSet(   candidatePairType = cms.string("EleMuon"),
					minDR = cms.double(0.3),
					trigger = emuTriggerCut

				),
		cms.PSet(   candidatePairType = cms.string("MuonTau"),
					minDR = cms.double(0.5),
					trigger = mtauTriggerCut

				),
		cms.PSet(   candidatePairType = cms.string("TauTau"),
					minDR = cms.double(0.5),
					trigger = tautauTriggerCut

				)
	)

		

# config for basic settings 
generalConfig = cms.PSet(

			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(True),
			keepSS = cms.bool(True),			
			# how to rank pairs within this selection
			rankByPtSum = cms.bool(False),
			rankByIsolation = cms.bool(True), # checks leg1 isolation, then pt in case of tie
			electronIsolationForRank = cms.string("DeltaBetaCorrectedRelIso"),
			muonIsolationForRank = cms.string("DeltaBetaCorrectedRelIso"),
			tauIDisolationForRank = cms.string("byCombinedIsolationDeltaBetaCorrRaw3Hits"),

			# isolations to keep as the leg1_relativeIsolation and 
			# leg2_relativeIsolation branches 

			electronIsolationForRelIsoBranch = cms.string("DeltaBetaCorrectedRelIso"),
			muonIsolationForRelIsoBranch= cms.string("DeltaBetaCorrectedRelIso"),
			tauIsolationForRelIsoBranch = cms.string("byCombinedIsolationDeltaBetaCorrRaw3Hits"),

			# isolations to keep as the veto_relativeIsolation  
			# branches 

			vetoElectronIsolationForRelIsoBranch = cms.string("DeltaBetaCorrectedRelIso"),
			vetoMuonIsolationForRelIsoBranch= cms.string("DeltaBetaCorrectedRelIso"),

			# check isLeg1GoodForHLTPath_Labels, isLeg2GoodForHLTPath_Labels
			# for the following trigger paths (only a summary, need more functions to access new triggers)
			# not requested in FlatTupleConfif_cfi.py summary variables
			# note : the hardcoded THE_MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 
			# be sure to include the _v1, _v2 etc. version suffix as v* 
			# also make sure none are repeats 


			triggerSummaryChecks = cms.vstring(
				"HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
				"HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*",
				"HLT_IsoMu18_v*",
				"HLT_Ele23_WPLoose_Gsf_v*",
				"HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*"				
				),



			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded THE_MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(
				"againstElectronLooseMVA5",
				"againstElectronMediumMVA5",
				"againstElectronTightMVA5",
				"againstElectronVLooseMVA5",
				"againstElectronVTightMVA5",
				"againstMuonLoose3",
				"againstMuonTight3",
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"byIsolationMVA3newDMwLTraw",
				#"byIsolationMVA3newDMwoLTraw",
				"byIsolationMVA3oldDMwLTraw",
				#"byIsolationMVA3oldDMwoLTraw",
				"byLooseCombinedIsolationDeltaBetaCorr3Hits",
				"byLoosePileupWeightedIsolation3Hits",
				"byMediumCombinedIsolationDeltaBetaCorr3Hits",
				"byMediumPileupWeightedIsolation3Hits",
				"byPileupWeightedIsolationRaw3Hits",
				"byTightCombinedIsolationDeltaBetaCorr3Hits",
				"byTightPileupWeightedIsolation3Hits",
				"chargedIsoPtSum",
				"decayModeFindingNewDMs",
				#"decayModeFindingOldDMs",
				"footprintCorrection",
				"neutralIsoPtSum",
				"neutralIsoPtSumWeight",
				"photonPtSumOutsideSignalCone",
				"puCorrPtSum"),

			###################
			# jet & bjet ID cut strings
			jetLeptonDRmin = cms.double(0.5),
			# note PU jet ID is not to be applied yet
			#jetIDcut = cms.string("pt>20 && abs(eta) < 4.7 && PU_jetIdPassed && PF_jetIdPassed"),
			#BjetIDcut = cms.string("pt>20 && abs(eta) < 2.4 && PU_jetIdPassed && PF_jetIdPassed && defaultBtagAlgorithm_isPassed")
			jetIDcut = cms.string("pt>20 && abs(eta) < 4.7  && PF_jetIdPassed"),
			BjetIDcut = cms.string("pt>20 && abs(eta) < 2.4 && PF_jetIdPassed && defaultBtagAlgorithm_RawScore > 0.8") # medium w.p.

					)


