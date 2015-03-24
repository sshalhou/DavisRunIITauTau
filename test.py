import FWCore.ParameterSet.Config as cms
process = cms.Process("Ntuple")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )


###################
# settings

SampleName_='SUSYGluGluToHToTauTau_M-120_8TeV-pythia6-tauola/AODSIM/PU_S10_START53_V7A-v1/AODSIM'
PhysicsProcess_='ggA0tautau[SUSY_120_8TeV]'
MASS_=120.0
isNonTopEmbeddedSample_ = False
isTopEmbeddedSample_ = False
runOnMC_ = True # true for MC, and all topTopBar and Ztautau embedded samples
branchingFraction_ = 999.99
crossSection_ = 999.99
numberEvents_ = 999
WillRunSVFit_ = True




myfilelist = cms.untracked.vstring()
myfilelist.extend(['file:/uscms_data/d3/shalhout/Phys14signal_miniAOD.root'])


process.source = cms.Source("PoolSource",fileNames=myfilelist)

process.myProducerLabel = cms.EDProducer('Ntuple')



###################################
# create a new Tuple primary vertex collection
# drop events without at least one good vtx
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigTupleOfflineVertices_cfi import vtx_Cuts

process.TupleOfllineVertices = cms.EDFilter(
    "VertexSelector",
    src = cms.InputTag('offlineSlimmedPrimaryVertices'),
    cut = vtx_Cuts,
    filter = cms.bool(True)
)


###################################
# create a new Tuple electron collection
# based on customSlimmedElectrons which has
# user defined variables and selections applied
###################################


from DavisRunIITauTau.TupleConfigurations.ConfigTupleElectrons_cfi import ele_Cuts

process.customSlimmedElectrons = cms.EDProducer('CustomPatElectronProducer' ,
							electronSrc =cms.InputTag('slimmedElectrons'),
							cutSrc = ele_Cuts, 
							vertexSrc =cms.InputTag('TupleOfllineVertices'),
							NAME=cms.string("customSlimmedElectrons")
							                 )


process.TupleElectronsNominal = cms.EDProducer('TupleElectronProducer' ,
							electronSrc =cms.InputTag('customSlimmedElectrons:customSlimmedElectrons:Ntuple'),
							NAME=cms.string("TupleElectronsNominal")
							                 )


###################################
# create a new Tuple muon collection
# based on customSlimmedMuons which has
# user defined variables and selections applied
###################################


from DavisRunIITauTau.TupleConfigurations.ConfigTupleMuons_cfi import mu_Cuts

process.customSlimmedMuons = cms.EDProducer('CustomPatMuonProducer' ,
							muonSrc =cms.InputTag('slimmedMuons'),
							cutSrc = mu_Cuts, 
							vertexSrc =cms.InputTag('TupleOfllineVertices'),
							NAME=cms.string("customSlimmedMuons")
							                 )




process.out = cms.OutputModule("PoolOutputModule",
			fileName = cms.untracked.string('NtupleFile.root'),
			SelectEvents = cms.untracked.PSet(
			                SelectEvents = cms.vstring('p')
			                ),
			outputCommands = cms.untracked.vstring('drop *')
)








#################################
# keep everything produced by Ntuple
#################################
process.out.outputCommands +=['keep *_*_*_Ntuple']


process.p = cms.Path(process.myProducerLabel)
#process.p *= process.UserSpecifiedData
process.p *= process.TupleOfllineVertices
process.p *= process.customSlimmedElectrons

process.p *= process.TupleElectronsNominal
process.p *= process.customSlimmedMuons
process.e = cms.EndPath(process.out)


#################################
# keep everything produced by Tuple-Code
#################################
#process.out.outputCommands +=['drop *_*_*_*']
process.out.outputCommands +=['keep TupleUserSpecifiedDatas_UserSpecifiedData_TupleUserSpecifiedData_PAT']
process.out.outputCommands +=['keep *_*_*_*']






