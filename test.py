import FWCore.ParameterSet.Config as cms
process = cms.Process("Ntuple")

###################################
# preliminaries 
###################################

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.myProducerLabel = cms.EDProducer('Ntuple')


###################################
# input - remove for crab running
###################################

myfilelist = cms.untracked.vstring()
myfilelist.extend(['file:/uscms_data/d3/shalhout/Phys14signal_miniAOD.root'])
process.source = cms.Source("PoolSource",fileNames=myfilelist)


###################################
# vertex filtering 
#     - filter+clone vertex collection
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigTupleOfflineVertices_cfi import vertexFilter

process.filteredVertices = cms.EDFilter(
    "VertexSelector",
    src = cms.InputTag('offlineSlimmedPrimaryVertices'),
    cut = vertexFilter,
    filter = cms.bool(True) # drop events without good quality veritces
)



###################################
# perform custom parameter embedding
# in slimmed collections
#    - e.g. dz, relIso, mva outputs
# in the case of taus also handle
# the Energy scale variation
###################################

process.customSlimmedElectrons = cms.EDProducer('CustomPatElectronProducer' ,
							electronSrc =cms.InputTag('slimmedElectrons::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::Ntuple'),
							NAME=cms.string("customSlimmedElectrons")
							                 )

process.customSlimmedMuons = cms.EDProducer('CustomPatMuonProducer' ,
							muonSrc =cms.InputTag('slimmedMuons::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::Ntuple'),
							NAME=cms.string("customSlimmedMuons")
							                 )

process.customSlimmedTaus = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTaus::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::Ntuple'),
							NAME=cms.string("customSlimmedTaus")
							                 )



###################################
# apply lepton filters onto 
# custom slimmed lepton collections
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigTupleElectrons_cfi import electronFilter
from DavisRunIITauTau.TupleConfigurations.ConfigTupleMuons_cfi import muonFilter
from DavisRunIITauTau.TupleConfigurations.ConfigTupleTaus_cfi import tauFilter



process.filteredCustomElectrons = cms.EDFilter("PATElectronRefSelector",
	src = cms.InputTag('customSlimmedElectrons:customSlimmedElectrons:Ntuple'),
	cut = electronFilter
	)

process.filteredCustomMuons = cms.EDFilter("PATMuonRefSelector",
	src = cms.InputTag('customSlimmedMuons:customSlimmedMuons:Ntuple'),
	cut = muonFilter
	)

process.filteredCustomTausEsNominal = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTaus:customSlimmedTausTauEsNominal:Ntuple'),
	cut = tauFilter
	)


process.filteredCustomTausEsUp = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTaus:customSlimmedTausTauEsUp:Ntuple'),
	cut = tauFilter
	)

process.filteredCustomTausEsDown = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTaus:customSlimmedTausTauEsDown:Ntuple'),
	cut = tauFilter
	)


###################################
# double lepton requirement
# should go here
###################################


process.requireCandidateHiggsPair = cms.EDFilter("HiggsCandidateCountFilter",
  electronSource = cms.InputTag("filteredCustomElectrons::Ntuple"),
  muonSource     = cms.InputTag("filteredCustomMuons::Ntuple"),
  tauSource      = cms.InputTag("filteredCustomTausEsDown::Ntuple"), # always count with down ES shift
  countElectronTaus = cms.bool(True),
  countMuonTaus     = cms.bool(True),
  countElectronMuons    = cms.bool(False), # for now we won't keep eMu pairs
  countTauTaus    = cms.bool(False), # for now we won't keep Tau_h Tau_h pairs
  filter = cms.bool(True)
)


###################################
# create TupleLepton collections
###################################


process.TupleElectronsNominal = cms.EDProducer('TupleElectronProducer' ,
							electronSrc =cms.InputTag('filteredCustomElectrons::Ntuple'),
							NAME=cms.string("TupleElectronsNominal")
							                 )


process.TupleMuonsNominal = cms.EDProducer('TupleMuonProducer' ,
							muonSrc =cms.InputTag('filteredCustomMuons::Ntuple'),
							NAME=cms.string("TupleMuonsNominal")
							                 )

process.TupleTausNominal = cms.EDProducer('TupleTauProducer' ,
							tauSrc =cms.InputTag('filteredCustomTausEsNominal::Ntuple'),
							NAME=cms.string("TupleTausNominal")
												)

process.TupleTausUp = cms.EDProducer('TupleTauProducer' ,
							tauSrc =cms.InputTag('filteredCustomTausEsUp::Ntuple'),
							NAME=cms.string("TupleTausNominal")
												)

process.TupleTausDown = cms.EDProducer('TupleTauProducer' ,
							tauSrc =cms.InputTag('filteredCustomTausEsDown::Ntuple'),
							NAME=cms.string("TupleTausNominal")
												)





###################################
# output config
###################################

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

process.p *= process.filteredVertices

process.p *= process.customSlimmedElectrons
process.p *= process.customSlimmedMuons
process.p *= process.customSlimmedTaus

process.p *= process.filteredCustomElectrons
process.p *= process.filteredCustomMuons
process.p *= process.filteredCustomTausEsNominal
process.p *= process.filteredCustomTausEsUp
process.p *= process.filteredCustomTausEsDown


process.p *= process.requireCandidateHiggsPair

process.p *= process.TupleElectronsNominal
process.p *= process.TupleMuonsNominal
process.p *= process.TupleTausNominal
process.p *= process.TupleTausUp
process.p *= process.TupleTausDown


process.e = cms.EndPath(process.out)


#################################
# keep everything produced by Tuple-Code
#################################
#process.out.outputCommands +=['drop *_*_*_*']
process.out.outputCommands +=['keep TupleUserSpecifiedDatas_UserSpecifiedData_TupleUserSpecifiedData_PAT']
process.out.outputCommands +=['keep *_*_*_*']






