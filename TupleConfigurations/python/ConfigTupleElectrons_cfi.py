import FWCore.ParameterSet.Config as cms

###################################
# configuration file to determine
# what mini-AOD skimmedElectrons are retained
# in TupleElectron collection
# will define :
# thinCuts = minimum skim requirements on electrons (anything failing these will be thrown away)
# vetoCuts = minimum requirement to be a veto electron
# signal_eleTauCuts = minimum requirement to be a signal ele + Tau_h final state electron
# signal_eleMuCuts = minimum requirement to be a signal ele + muon final state electron
###################################

ele_thinCuts = cms.PSet(minPt = cms.double(10.0))
ele_vetoCuts = cms.PSet(minPt = cms.double(10.0))
ele_signal_eleTauCuts = cms.PSet(minPt = cms.double(10.0))
ele_signal_eleMuCuts = cms.PSet(minPt = cms.double(10.0))