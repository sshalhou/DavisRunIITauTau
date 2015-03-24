import FWCore.ParameterSet.Config as cms

###################################
# configuration file to determine
# what mini-AOD skimmedTaus are retained
# in TupleTau collection
# will define :
# thinCuts = minimum skim requirements on taus (anything failing these will be thrown away)
# vetoCuts = minimum requirement to be a veto Tau
# signal_eleTauCuts = minimum requirement to be a signal ele + Tau_h final state Tau
# signal_muTauCuts = minimum requirement to be a signal muon + Tau_h final state Tau
###################################


tau_Cuts = cms.PSet(
	######### thin cuts ##############
	THIN_minPt = cms.double(10.0),
	######### veto cuts ##############
	VETO_minPt = cms.double(10.0),
	######### eleTau signal cuts ##############
	SIGeleTau_minPt = cms.double(10.0),
	######### eleMu signal cuts ##############
	SIGmuTau_minPt = cms.double(10.0)
)

