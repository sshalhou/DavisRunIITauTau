import FWCore.ParameterSet.Config as cms

###################################
# configuration file to determine
# what mini-AOD offlineSlimmedPrimaryVertices are retained
# in TupleOfllineVertices collection
 ###################################

vtx_Cuts = cms.string("isValid & ndof >= 4 & z > -24 & z < +24 & position.Rho < 2.")