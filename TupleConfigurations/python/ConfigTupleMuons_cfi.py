import FWCore.ParameterSet.Config as cms

###################################
# configuration file to determine
# what mini-AOD skimmedMuons are retained
# in TupleMuon collection
# will define :
# thinCuts = minimum skim requirements on muons (anything failing these will be thrown away)
# vetoCuts = minimum requirement to be a veto muon
# signal_muTauCuts = minimum requirement to be a signal mu + Tau_h final state muon
# signal_muMuCuts = minimum requirement to be a signal mu + muon final state muon
###################################


mu_Cuts = cms.PSet(
	######### thin cuts ##############
	THIN_minPt = cms.double(10.0),
	######### veto cuts ##############
	VETO_minPt = cms.double(10.0),
	######### muTau signal cuts ##############
	SIGmuTau_minPt = cms.double(10.0),
	######### muMu signal cuts ##############
	SIGeleMu_minPt = cms.double(10.0)
)

