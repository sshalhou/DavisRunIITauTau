# master config file for FlatTupleGenerator 
# define PSets for various settings and selection cuts
# -- S. Shalhout June 18, 2015

import FWCore.ParameterSet.Config as cms
from DavisRunIITauTau.TupleConfigurations.and_string_concatonator import and_string_concatonator

###################################################
# do we want a smaller version of the FlatTuple ?
###################################################

SmallTree_ = True

if SmallTree_ is True :
	print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	print " SmallTree_ option is Active... "
	print "     -- FlatTuple size reduction of ~50%  "
	print "     -- eliminates inputs to electron/muon/tau ID and MVAs "
	print "     -- eliminates bTag SF and Eff (but keep tag pass/fail) "
	print "     -- eliminates genMothers and genDaughters (but not genParticles) "
	print "     -- still allows for full analysis (excluding more detailed side studies) "
	print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"


###################################################
# do we want to build low DR FlatTuples as well?  #
###################################################

BUILD_LOWDR = False


#########################################################
# do we want to apply post-sync/baseline iso and anti-e/anti-mu ?
# cuts on the hadronically decaying tau legs?
#########################################################

APPLY_POST_SYNC_TAU_CUTS = True # default true unless you want to check sync 

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
# each True invokes SVFit (Mass and MT)    #
# using the correponding MET               #
############################################


USE_MVAMET_FOR_SVFit_AT_FlatTuple = True  				# this is the default choice (recoil corrected MVA MET)
USE_MVAMET_uncorrected_FOR_SVFit_AT_FlatTuple = False
USE_MVAMET_responseUP_FOR_SVFit_AT_FlatTuple = False
USE_MVAMET_responseDOWN_FOR_SVFit_AT_FlatTuple = False
USE_MVAMET_resolutionUP_FOR_SVFit_AT_FlatTuple = False
USE_MVAMET_resolutionDOWN_FOR_SVFit_AT_FlatTuple = False
USE_PFMET_FOR_SVFit_AT_FlatTuple = False  			
USE_PUPPIMET_FOR_SVFit_AT_FlatTuple = False  			

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

# electron in EleMuon final state :
ele_EleMuon = []
ele_EleMuon.append("pt>13")
ele_EleMuon.append("abs(eta)<2.5")
ele_EleMuon.append("abs(dxy)<0.045")
ele_EleMuon.append("abs(dz)<0.2")
ele_EleMuon.append("passFail_electronMVA80==1.0")
ele_EleMuon.append("numberOfMissingInnerHits<=1")
ele_EleMuon.append("passConversionVeto==1.0")

# muon in EleMuon final state :
muon_EleMuon = []
muon_EleMuon.append("pt>10")
muon_EleMuon.append("abs(eta)<2.4")
muon_EleMuon.append("abs(dxy)<0.045")
muon_EleMuon.append("abs(dz)<0.2")
muon_EleMuon.append("passesMediumMuonId==1.0")

# muon in MuonTau final state :
muon_MuonTau = []
muon_MuonTau.append("pt>19")
muon_MuonTau.append("abs(eta)<2.1")
muon_MuonTau.append("abs(dxy)<0.045")
muon_MuonTau.append("abs(dz)<0.2")
muon_MuonTau.append("passesMediumMuonId==1.0")


# tau in MuonTau final state :
tau_MuonTau = []
tau_MuonTau.append("pt>20")
tau_MuonTau.append("abs(eta)<2.3")
tau_MuonTau.append("tauID('decayModeFinding') > 0.5")                                        
tau_MuonTau.append("abs(dz)<0.2")
tau_MuonTau.append("abs(charge)==1.0")

# electron in EleTau final state :
ele_EleTau = []
ele_EleTau.append("pt>24")
ele_EleTau.append("abs(eta)<2.1")
ele_EleTau.append("abs(dxy)<0.045")
ele_EleTau.append("abs(dz)<0.2")
ele_EleTau.append("passFail_electronMVA80==1.0")
ele_EleTau.append("passConversionVeto==1.0")
ele_EleTau.append("numberOfMissingInnerHits<=1")

# tau in EleTau final state :
tau_EleTau = []
tau_EleTau.append("pt>20")
tau_EleTau.append("abs(eta)<2.3")
tau_EleTau.append("tauID('decayModeFinding') > 0.5")                                        
tau_EleTau.append("abs(dz)<0.2")
tau_EleTau.append("abs(charge)==1.0")

# tau in TauTau final state :
tau_TauTau = []
tau_TauTau.append("pt>40")
tau_TauTau.append("abs(eta)<2.1")
tau_TauTau.append("tauID('decayModeFinding') > 0.5")                                        
tau_TauTau.append("abs(dz)<0.2")
tau_TauTau.append("abs(charge)==1.0")

#######################################
# --- cut sets for Z->ee and Z->mumu  #
# these are approx. cuts since don't  #
# have firm guide from H2TauTau       #
#######################################

# electron in EleEle final state :
ele_EleEle = []
ele_EleEle.append("pt>10")
ele_EleEle.append("abs(eta)<2.5")
ele_EleEle.append("abs(dxy)<0.045")
ele_EleEle.append("abs(dz)<0.2")
ele_EleEle.append("passFail_electronMVA80==1.0")
ele_EleEle.append("numberOfMissingInnerHits<=1")
ele_EleEle.append("passConversionVeto==1.0")

# muon in MuonMuon final state :
muon_MuonMuon = []
muon_MuonMuon.append("pt>10")
muon_MuonMuon.append("abs(eta)<2.1")
muon_MuonMuon.append("abs(dxy)<0.045")
muon_MuonMuon.append("abs(dz)<0.2")
muon_MuonMuon.append("isGlobalMuon==1.0")
muon_MuonMuon.append("passesMediumMuonId==1.0")


#############################################
# for veto cuts we include isolation here   #
# since the code in flatTuple only uses these
# to set veto flags (all veto leptons are retained even those that fail,
# meaning the cuts and flags can always be re-evaluated when generating
# the sync tree )


# electron cuts for third lepton veto :
ele_ThirdLeptonVeto = []
ele_ThirdLeptonVeto.append("pt>10")
ele_ThirdLeptonVeto.append("abs(eta)<2.5")
ele_ThirdLeptonVeto.append("abs(dxy)<0.045")
ele_ThirdLeptonVeto.append("abs(dz)<0.2")
ele_ThirdLeptonVeto.append("passFail_electronMVA90==1.0")
ele_ThirdLeptonVeto.append("passConversionVeto==1.0")
ele_ThirdLeptonVeto.append("numberOfMissingInnerHits<=1")
ele_ThirdLeptonVeto.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.3")

# electron cuts for DiElectron veto :
ele_DiElectron = []
ele_DiElectron.append("pt>15")
ele_DiElectron.append("abs(eta)<2.5")
ele_DiElectron.append("passFail_electronCutBasedID==1.0")
ele_DiElectron.append("abs(dz)<0.2")
ele_DiElectron.append("abs(dxy)<0.045")
ele_DiElectron.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.3")

# muon cuts for third lepton veto :
muon_ThirdLeptonVeto = []
muon_ThirdLeptonVeto.append("pt>10")
muon_ThirdLeptonVeto.append("abs(eta)<2.4")
muon_ThirdLeptonVeto.append("abs(dxy)<0.045")
muon_ThirdLeptonVeto.append("abs(dz)<0.2")
muon_ThirdLeptonVeto.append("passesMediumMuonId==1.0")
muon_ThirdLeptonVeto.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.3")

# muon cuts for DiMuon veto :
muon_DiMuonVeto = []
muon_DiMuonVeto.append("pt>15")
muon_DiMuonVeto.append("abs(eta)<2.4")
muon_DiMuonVeto.append("(isGlobalMuon==1.0 && isTightMuon==1.0 && isTrackerMuon==1.0)")
muon_DiMuonVeto.append("abs(dxy)<0.045")
muon_DiMuonVeto.append("abs(dz)<0.2")
muon_DiMuonVeto.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.3")



##################################
# concatenate the cut strings    #

cut_ele_EleTau = cms.string(and_string_concatonator(ele_EleTau))
cut_ele_EleMuon = cms.string(and_string_concatonator(ele_EleMuon))
cut_muon_MuonTau = cms.string(and_string_concatonator(muon_MuonTau))
cut_muon_EleMuon = cms.string(and_string_concatonator(muon_EleMuon))
cut_tau_TauTau = cms.string(and_string_concatonator(tau_TauTau))
cut_tau_EleTau = cms.string(and_string_concatonator(tau_EleTau))
cut_tau_MuonTau = cms.string(and_string_concatonator(tau_MuonTau))
cut_ele_ThirdLeptonVeto = cms.string(and_string_concatonator(ele_ThirdLeptonVeto))
cut_ele_DiElectron = cms.string(and_string_concatonator(ele_DiElectron))
cut_muon_ThirdLeptonVeto = cms.string(and_string_concatonator(muon_ThirdLeptonVeto))
cut_muon_DiMuonVeto =  cms.string(and_string_concatonator(muon_DiMuonVeto))
cut_ele_EleEle = cms.string(and_string_concatonator(ele_EleEle))
cut_muon_MuonMuon = cms.string(and_string_concatonator(muon_MuonMuon))


#################################
# post-sync baseline tau ID cuts
# these need to be loose enough for all channels + QCD and W anti-iso 
# background methods


post_sync_tauIso_ = cms.string('1==1')
post_sync_EleTau_tauMVACuts_ = cms.string('1==1')
post_sync_MuonTau_tauMVACuts_ = cms.string('1==1')
post_sync_TauTau_tauMVACuts_ = cms.string('1==1')

##################################################################
# turn them into real cuts if APPLY_POST_SYNC_TAU_CUTS

if APPLY_POST_SYNC_TAU_CUTS is True :
	post_sync_tauIso_ = cms.string('(tauID("byTightIsolationMVArun2v1DBoldDMwLT") > 0.5 || tauID("byVTightIsolationMVArun2v1DBoldDMwLT") > 0.5 || tauID("byLooseIsolationMVArun2v1DBoldDMwLT") > 0.5 || tauID("byMediumIsolationMVArun2v1DBoldDMwLT") > 0.5 || tauID("byVLooseIsolationMVArun2v1DBoldDMwLT") > 0.5 || tauID("byVVTightIsolationMVArun2v1DBoldDMwLT") > 0.5)')
	post_sync_EleTau_tauMVACuts_ = cms.string("(tauID('againstElectronTightMVA6')> 0.5 && tauID('againstMuonLoose3')>0.5)")
	post_sync_MuonTau_tauMVACuts_ = cms.string("(tauID('againstElectronVLooseMVA6')> 0.5 && tauID('againstMuonTight3')>0.5)")
	post_sync_TauTau_tauMVACuts_ = cms.string("(tauID('againstElectronVLooseMVA6')> 0.5 && tauID('againstMuonLoose3')>0.5)")


	print '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
	print '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
	print '++ WARNING -- applying post sync/baseline tau iso and mva cuts'
	print '++ sync ntuples will not compare well to other groups !!! '
	print '++ make sure these cuts are loose enough for all analysis cuts + bkg methods'
	print '++ change in FlatTupleConfig_cfi.py ...'
	print '++', post_sync_tauIso_
	print '+++++++++++'
	print '++ in channel EleTau will require tau leg to pass', post_sync_EleTau_tauMVACuts_
	print '++ in channel MuonTau will require tau leg to pass', post_sync_MuonTau_tauMVACuts_
	print '++ in channel TauTau will require tau legs to pass', post_sync_TauTau_tauMVACuts_
	print '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
	print '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'




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

emuTriggerCutRun2015D = "((isLeg1GoodForHLTPath('HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') &&\
	isLeg2GoodForHLTPath('HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') && leg2.pt>18) ||\
    (isLeg1GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*') &&\
	isLeg2GoodForHLTPath('HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*') && leg1.pt>18))"

tautauTriggerCutRun2015D = "(isLeg1GoodForHLTPath('HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*') \
	&& isLeg2GoodForHLTPath('HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*'))"



etauTriggerCutRun2015D = "(isLeg1GoodForHLTPath('HLT_Ele23_WPLoose_Gsf_v*'))"


mtauTriggerCutRun2015D = "(isLeg1GoodForHLTPath('HLT_IsoMu18_v*'))"

# for Z->ee and Z->mumu let either leg1 or leg2 pass the single e (or mu) trigger  

ZEETriggerCutRun2015D = "((isLeg1GoodForHLTPath('HLT_Ele23_WPLoose_Gsf_v*')) || (isLeg2GoodForHLTPath('HLT_Ele23_WPLoose_Gsf_v*')))"

ZMuMuTriggerCutRun2015D = "((isLeg1GoodForHLTPath('HLT_IsoMu18_v*')) || (isLeg1GoodForHLTPath('HLT_IsoMu18_v*')))"



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

# for Z->ee and Z->mumu let either leg1 or leg2 pass the single e (or mu) trigger  

ZEETriggerCutFall15MCminiAOD = "((isLeg1GoodForHLTPath('HLT_Ele23_WPLoose_Gsf_v*')) || (isLeg2GoodForHLTPath('HLT_Ele23_WPLoose_Gsf_v*')))"

ZMuMuTriggerCutFall15MCminiAOD = "((isLeg1GoodForHLTPath('HLT_IsoMu18_v*')) || (isLeg1GoodForHLTPath('HLT_IsoMu18_v*')))"



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

# ok since 2015 we use single e and single mu triggers from muTau, eTau, ee and muMu
eeTriggerCut = cms.string(" ( !isRealData && "+ZEETriggerCutFall15MCminiAOD+" ) || ( "+ZEETriggerCutRun2015D+ " && isRealData )")
mmTriggerCut  = cms.string(" ( !isRealData && "+ZMuMuTriggerCutFall15MCminiAOD+" ) || ( "+ZMuMuTriggerCutRun2015D+ " && isRealData )")



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
print "-----------------------------------------------------------"
print " mmTriggerCut = ", mmTriggerCut
print "-----------------------------------------------------------"
print " eeTriggerCut = ", eeTriggerCut
print "*********************************************************"



# VPSet containing selections for different final states, if PSet is not
# provided for a given final state the 
# the events will omitted



# main cut vector PSet :
defaultCuts = cms.VPSet(

		cms.PSet(   candidatePairType = cms.string("MuonMuon"),
					muonID = cut_muon_MuonMuon,
					minDR = cms.double(0.5),
					maxDR = cms.double(999.0),
					trigger = mmTriggerCut

				),


		cms.PSet(   candidatePairType = cms.string("EleEle"),
					electronID = cut_ele_EleEle,
					minDR = cms.double(0.5),
					maxDR = cms.double(999.0),
					trigger = eeTriggerCut

				),


		cms.PSet(   candidatePairType = cms.string("EleMuon"),
					electronID = cut_ele_EleMuon,
					muonID = cut_muon_EleMuon,
					minDR = cms.double(0.3),
					maxDR = cms.double(999.0),
					trigger = emuTriggerCut

				),

		cms.PSet(   candidatePairType = cms.string("MuonTau"),
					muonID = cut_muon_MuonTau,
					tauID = cut_tau_MuonTau,
					minDR = cms.double(0.5),
					maxDR = cms.double(999.0),
					trigger = mtauTriggerCut

				),


		cms.PSet(   candidatePairType = cms.string("EleTau"),
					electronID = cut_ele_EleTau,
					tauID = cut_tau_EleTau,
					minDR = cms.double(0.5),
					maxDR = cms.double(999.0),
					trigger = etauTriggerCut
				),


		cms.PSet(   candidatePairType = cms.string("TauTau"),
					tauID = cut_tau_TauTau,
					minDR = cms.double(0.5),
					maxDR = cms.double(999.0),
					trigger = tautauTriggerCut
				)
	)



lowDeltaRCuts = cms.VPSet(


		cms.PSet(   candidatePairType = cms.string("MuonMuon"),
					muonID = cut_muon_MuonMuon,
					minDR = cms.double(0.),
					maxDR = cms.double(0.4999),
					trigger = mmTriggerCut

				),


		cms.PSet(   candidatePairType = cms.string("EleEle"),
					electronID = cut_ele_EleEle,
					minDR = cms.double(0.),
					maxDR = cms.double(0.4999),
					trigger = eeTriggerCut

				),


		cms.PSet(   candidatePairType = cms.string("EleMuon"),
					electronID = cut_ele_EleMuon,
					muonID = cut_muon_EleMuon,
					minDR = cms.double(0.),
					maxDR = cms.double(0.2999),
					trigger = emuTriggerCut

				),

		cms.PSet(   candidatePairType = cms.string("MuonTau"),
					muonID = cut_muon_MuonTau,
					tauID = cut_tau_MuonTau,
					minDR = cms.double(0.),
					maxDR = cms.double(0.4999),
					trigger = mtauTriggerCut

				),


		cms.PSet(   candidatePairType = cms.string("EleTau"),
					electronID = cut_ele_EleTau,
					tauID = cut_tau_EleTau,
					minDR = cms.double(0.),
					maxDR = cms.double(0.4999),
					trigger = etauTriggerCut
				),


		cms.PSet(   candidatePairType = cms.string("TauTau"),
					tauID = cut_tau_TauTau,
					minDR = cms.double(0.),
					maxDR = cms.double(0.4999),
					trigger = tautauTriggerCut
				)
	)

############################################################
# check isLeg1GoodForHLTPath_Labels, isLeg2GoodForHLTPath_Labels
# for the following trigger paths (only a summary, need more functions to access new triggers)
# not requested in FlatTupleConfif_cfi.py summary variables
# note : the hardcoded THE_MAX variable in FlatTupleGenerator.cc limits the 
# number of these that we can keep 
# be sure to include the _v1, _v2 etc. version suffix as v* 
# also make sure none are repeats 


triggerSummaryChecks_ = cms.vstring(
	"HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*",
	"HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*",
	"HLT_IsoMu18_v*",
	"HLT_Ele23_WPLoose_Gsf_v*",
	"HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*"				
	)
############################################################

from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import BUILD_EFFICIENCY_TREE as BuildEffTree_
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import BUILD_ELECTRON_ELECTRON as BuildEleEle_
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import BUILD_ELECTRON_MUON as BuildEleMuon_
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import BUILD_ELECTRON_TAU as BuildEleTau_
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import BUILD_MUON_MUON as BuildMuonMuon_
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import BUILD_MUON_TAU as BuildMuonTau_
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import BUILD_TAU_TAU as BuildTauTau_






# config for basic settings 
generalConfig = cms.PSet(

			keepOnlyBestRankedPair = cms.bool(True), # for debugging set to False (best pair will have pairRank = 0), default should be True
			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(True),
			keepSS = cms.bool(True),			
			# how to rank pairs within this selection
			rankByPtSum = cms.bool(False),
			rankByIsolation = cms.bool(True), # checks leg1 isolation, then pt in case of tie
			
			####################################
			# new options for a FlatTuple 
			# size reduction of ~50% 
			# when True :
			# -- eliminates inputs to electron/muon/tau ID and MVAs
			# -- eliminates genMothers and genDaughters (but not genParticles)
			# -- still allows for full analysis (excluding more detailed side studies)

			SmallTree = cms.bool(SmallTree_),
			BuildEffTree = cms.bool(BuildEffTree_), # if false no effLep info will be in FlatTuple
			
			#######################################
			# pair types to keep or reject (set in ConfigNtupleContent_cfi.py)
			BuildEleEle = cms.bool(BuildEleEle_),
			BuildEleMuon = cms.bool(BuildEleMuon_),
			BuildEleTau = cms.bool(BuildEleTau_),
			BuildMuonMuon = cms.bool(BuildMuonMuon_),
			BuildMuonTau = cms.bool(BuildMuonTau_),
			BuildTauTau = cms.bool(BuildTauTau_),			

		
			#######################################
			# in 76X have a new complication :
			# for DeltaBeta (ex: byCombinedIsolationDeltaBetaCorrRaw3Hits)  smaller value = more isolated
			# for MVA iso (ex: byIsolationMVArun2v1DBnewDMwLTraw) bigger value = more isolated
			# so now the pair rank algorithm accepts the args x_isSmallerValueMoreIsolated 
			# which should tell how to handle the particular isolation used for ranking


			electronIsolationForRank = cms.string("DeltaBetaCorrectedRelIso"),
			electron_isSmallerValueMoreIsolated = cms.bool(True),

			muonIsolationForRank = cms.string("DeltaBetaCorrectedRelIso"),
			muon_isSmallerValueMoreIsolated = cms.bool(True),
			
			tauIDisolationForRank = cms.string("byIsolationMVArun2v1DBoldDMwLTraw"),
			tau_isSmallerValueMoreIsolated = cms.bool(False),

			# isolations to keep as the leg1_relativeIsolation and 
			# leg2_relativeIsolation branches 

			electronIsolationForRelIsoBranch = cms.string("DeltaBetaCorrectedRelIso"),
			muonIsolationForRelIsoBranch= cms.string("DeltaBetaCorrectedRelIso"),

			# in 76X and up these differ by channel
			tauIsolationForRelIsoBranch = cms.string("byTightIsolationMVArun2v1DBoldDMwLT"), # default for effLeptons
			tauIsolationForRelIsoBranch_forEleTau = cms.string("byTightIsolationMVArun2v1DBoldDMwLT"),
			tauIsolationForRelIsoBranch_forMuTau = cms.string("byTightIsolationMVArun2v1DBoldDMwLT"),
			tauIsolationForRelIsoBranch_forTauTau = cms.string("byVTightIsolationMVArun2v1DBoldDMwLT"),


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


			triggerSummaryChecks = triggerSummaryChecks_,



			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded THE_MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(				
				"byIsolationMVArun2v1DBoldDMwLTraw",
				"byTightIsolationMVArun2v1DBoldDMwLT",
				"byVTightIsolationMVArun2v1DBoldDMwLT",
				"byLooseIsolationMVArun2v1DBoldDMwLT",
				"byMediumIsolationMVArun2v1DBoldDMwLT",
				"byVLooseIsolationMVArun2v1DBoldDMwLT",
				"byVVTightIsolationMVArun2v1DBoldDMwLT",

				"againstElectronVLooseMVA6",
				"againstMuonTight3",
				"againstElectronTightMVA6",
				"againstMuonLoose3",
				"decayModeFinding",


				#"againstElectronLooseMVA6",	
				#"againstElectronMediumMVA6",
				#"againstElectronVTightMVA6",
				"byIsolationMVA3oldDMwLTraw",
				#"chargedIsoPtSum",
				#"neutralIsoPtSum",
				#"puCorrPtSum",
				#"againstElectronTightMVA5",
				#"againstElectronVLooseMVA5",
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"byIsolationMVArun2v1DBnewDMwLTraw",
				#"byTightIsolationMVArun2v1DBnewDMwLT",
				#"byVTightIsolationMVArun2v1DBnewDMwLT",
				#"byLooseIsolationMVArun2v1DBnewDMwLT",
				#"byMediumIsolationMVArun2v1DBnewDMwLT",
				#"byVLooseIsolationMVArun2v1DBnewDMwLT",
				#"byVVTightIsolationMVArun2v1DBnewDMwLT",
				#"byIsolationMVA3newDMwLTraw",
				"decayModeFindingNewDMs"
# bad				"decayModeFindingOldDMs"
					),




			#############################################
			# 3rd lepton veto and di-lepton rejection   #
			
			thirdEleVeto = cut_ele_ThirdLeptonVeto, 
			thirdMuonVeto =	cut_muon_ThirdLeptonVeto,
			legThirdLeptonMinDR = cms.double(0.01), # make sure leg1 or leg2 don't cause the veto 

			diEleVeto =	cut_ele_DiElectron, 
			diMuonVeto = cut_muon_DiMuonVeto,
			diLeptonMinDR = cms.double(0.15), # make sure that a single veto lepton does not trigger the di-lepton flag 


			#####################
			# b-tag configuration 

			BtagSF_File = cms.string("DavisRunIITauTau/RunTimeDataInput/data/BTAGSF/CSVv2_ichep.csv"),
			# note for 80X it seems only a single file is available
			looseBtagEff_file = cms.string("DavisRunIITauTau/RunTimeDataInput/data/BTAGEFF/tagging_efficiencies_ichep2016.root"),
			mediumBtagEff_file = cms.string("DavisRunIITauTau/RunTimeDataInput/data/BTAGEFF/tagging_efficiencies_ichep2016.root"),
			tightBtagEff_file = cms.string("DavisRunIITauTau/RunTimeDataInput/data/BTAGEFF/tagging_efficiencies_ichep2016.root"), 
			LooseBtagWPcut = cms.double(0.460),
			MediumBtagWPcut = cms.double(0.800),
			TightBtagWPcut = cms.double(0.935),


			###################
			# jet cut strings
			jetLeptonDRmin = cms.double(0.5),

			# note PU jet ID is not to be applied yet
			# you *MUST* make sure this jetIDcut is inclusive of any b-tag selection you
			# wish to apply later 
			jetIDcut = cms.string("pt>20 && abs(eta) < 4.7  && PF_jetIdPassed")

					)


