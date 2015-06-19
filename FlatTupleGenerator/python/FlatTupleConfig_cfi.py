# master config file for FlatTupleGenerator 
# define PSets for various settings and selection cuts
# -- S. Shalhout June 18, 2015

import FWCore.ParameterSet.Config as cms
from DavisRunIITauTau.TupleConfigurations.and_string_concatonator import and_string_concatonator


# individual object cuts used to build the PSets 
# each line appended will be concatenated (using &&) into a single cut string

# electron in EleTau final state :
ele_EleTau = []
ele_EleTau.append("pt>23")
ele_EleTau.append("abs(eta)<2.1")
ele_EleTau.append("abs(dxy)<0.045")
ele_EleTau.append("abs(dz)<0.2")
ele_EleTau.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.1")
ele_EleTau.append("passFail_electronMVA==1.0")


# electron in EleMuon final state :
ele_EleMuon = []
ele_EleMuon.append("pt>20")
ele_EleMuon.append("abs(eta)<2.5")
ele_EleMuon.append("abs(dxy)<0.045")
ele_EleMuon.append("abs(dz)<0.2")
ele_EleMuon.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.15")
ele_EleMuon.append("passFail_electronMVA==1.0")


# muon in MuonTau final state :
muon_MuonTau = []
muon_MuonTau.append("pt>18")
muon_MuonTau.append("abs(eta)<2.1")
muon_MuonTau.append("abs(dxy)<0.045")
muon_MuonTau.append("abs(dz)<0.2")
muon_MuonTau.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.1")
muon_MuonTau.append("passesMediumMuonId==1.0")


# muon in EleMuon final state :
muon_EleMuon = []
muon_EleMuon.append("pt>10")
muon_EleMuon.append("abs(eta)<2.5")
muon_EleMuon.append("abs(dxy)<0.045")
muon_EleMuon.append("abs(dz)<0.2")
muon_EleMuon.append("relativeIsol('DeltaBetaCorrectedRelIso')<0.15")
muon_EleMuon.append("passesMediumMuonId==1.0")


# tau in TauTau final state :
tau_TauTau = []
tau_TauTau.append("abs(dz)==0.0")
tau_TauTau.append("tauID('byCombinedIsolationDeltaBetaCorrRaw3Hits')<1.0")
tau_TauTau.append("pt>45")
tau_TauTau.append("abs(eta)<2.1")
tau_TauTau.append("(tauID('decayModeFinding')>0.5 ||  tauID('decayModeFindingNewDMs') > 0.5)")                                        
tau_TauTau.append("tauID('againstElectronVLooseMVA5')>0.5")
tau_TauTau.append("tauID('againstMuonLoose3')>0.5")


# tau in EleTau final state :
tau_EleTau = []
tau_EleTau.append("abs(dz)==0.0")
tau_EleTau.append("tauID('byCombinedIsolationDeltaBetaCorrRaw3Hits')<1.0")
tau_EleTau.append("pt>20")
tau_EleTau.append("abs(eta)<2.3")
tau_EleTau.append("(tauID('decayModeFinding')>0.5 ||  tauID('decayModeFindingNewDMs') > 0.5)")                                        
tau_EleTau.append("tauID('againstElectronTightMVA5')>0.5")
tau_EleTau.append("tauID('againstMuonLoose3')>0.5")

# tau in MuonTau final state :
tau_MuonTau = []
tau_MuonTau.append("abs(dz)==0.0")
tau_MuonTau.append("tauID('byCombinedIsolationDeltaBetaCorrRaw3Hits')<1.0")
tau_MuonTau.append("pt>20")
tau_MuonTau.append("abs(eta)<2.3")
tau_MuonTau.append("(tauID('decayModeFinding')>0.5 ||  tauID('decayModeFindingNewDMs') > 0.5)")                                        
tau_MuonTau.append("tauID('againstElectronVLooseMVA5')>0.5")
tau_MuonTau.append("tauID('againstMuonTight3')>0.5")



cut_ele_EleTau = cms.string(and_string_concatonator(ele_EleTau))
cut_ele_EleMuon = cms.string(and_string_concatonator(ele_EleMuon))
cut_muon_MuonTau = cms.string(and_string_concatonator(muon_MuonTau))
cut_muon_EleMuon = cms.string(and_string_concatonator(muon_EleMuon))
cut_tau_TauTau = cms.string(and_string_concatonator(tau_TauTau))
cut_tau_EleTau = cms.string(and_string_concatonator(tau_EleTau))
cut_tau_MuonTau = cms.string(and_string_concatonator(tau_MuonTau))




# VPSet containing selections for different final states, if no PSet is not
# provided for a given final state the 
# the events will omitted

# main cut vector PSet :
theCuts = cms.VPSet(

		cms.PSet(   candidatePairType = cms.string("EleTau"),
					electronID = cut_ele_EleTau,
					tauID = cut_tau_EleTau
				),
		cms.PSet(   candidatePairType = cms.string("EleMuon"),
					electronID = cut_ele_EleMuon,
					muonID = cut_muon_EleMuon
				),
		cms.PSet(   candidatePairType = cms.string("MuonTau"),
					muonID = cut_muon_MuonTau,
					tauID = cut_tau_MuonTau
				),
		cms.PSet(   candidatePairType = cms.string("TauTau"),
					tauID = cut_tau_TauTau

				)
	)


		

# config for basic settings 
generalConfig = cms.PSet(

			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(True),
			keepSS = cms.bool(True),
			keepTauEsNominal = cms.bool(True),
			keepTauEsUp = cms.bool(False),
			keepTauEsDown = cms.bool(False),

			# how to rank pairs within this selection
			rankByPtSum = cms.bool(True),
			rankByIsolation = cms.bool(False),
			electronIsolationForRank = cms.string("DeltaBetaCorrectedRelIso"),
			muonIsolationForRank = cms.string("DeltaBetaCorrectedRelIso"),
			tauIDisolationForRank = cms.string("byCombinedIsolationDeltaBetaCorrRaw3Hits"),

			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"decayModeFindingNewDMs",
				"againstMuonLoose3",
				"againstElectronVLooseMVA5",
				"againstMuonLoose3",
				"againstElectronMediumMVA5")

					)


