import FWCore.ParameterSet.Config as cms
process = cms.Process("Ntuple")




###################################
# preliminaries 
###################################


process.myProducerLabel = cms.EDProducer('Ntuple')

# import of standard configurations
process.load("FWCore.MessageService.MessageLogger_cfi")

# mva MET --start
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff import *
from JetMETCorrections.Configuration.DefaultJEC_cff import *

# process.load('Configuration.StandardSequences.Services_cff')
# process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
# process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
# from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
# process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
# process.load("RecoJets.JetProducers.ak4PFJets_cfi")
# process.ak4PFJets.doAreaFastjet = cms.bool(True) 
# process.ak4PFJets.src = cms.InputTag("packedPFCandidates")
# from JetMETCorrections.Configuration.DefaultJEC_cff import ak4PFJetsL1FastL2L3
# process.load("RecoMET.METPUSubtraction.mvaPFMET_cff")
# #process.pfMVAMEt.srcLeptons = cms.VInputTag("slimmedElectrons")
# process.pfMVAMEt.srcPFCandidates = cms.InputTag("packedPFCandidates")
# process.pfMVAMEt.srcVertices = cms.InputTag("offlineSlimmedPrimaryVertices")
# process.puJetIdForPFMVAMEt.jec =  cms.string('AK4PF')
# #process.puJetIdForPFMVAMEt.jets = cms.InputTag("ak4PFJets")
# process.puJetIdForPFMVAMEt.vertexes = cms.InputTag("offlineSlimmedPrimaryVertices")
# process.puJetIdForPFMVAMEt.rho = cms.InputTag("fixedGridRhoFastjetAll")

# mva MET -- end

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


from DavisRunIITauTau.TupleConfigurations.ConfigTupleTriggers_cfi import (electronTriggerPathsAndFilters,
electronTriggerMatch_DR, electronTriggerMatch_Types)

process.customSlimmedElectrons = cms.EDProducer('CustomPatElectronProducer' ,
							electronSrc =cms.InputTag('slimmedElectrons::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::Ntuple'),
							NAME=cms.string("customSlimmedElectrons"),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							triggerMatchDRSrc = electronTriggerMatch_DR,
							triggerMatchTypesSrc = electronTriggerMatch_Types,
							triggerMatchPathsAndFiltersSrc = electronTriggerPathsAndFilters
							                 )

from DavisRunIITauTau.TupleConfigurations.ConfigTupleTriggers_cfi import (muonTriggerPathsAndFilters,
muonTriggerMatch_DR, muonTriggerMatch_Types)

process.customSlimmedMuons = cms.EDProducer('CustomPatMuonProducer' ,
							muonSrc =cms.InputTag('slimmedMuons::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::Ntuple'),
							NAME=cms.string("customSlimmedMuons"),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							triggerMatchDRSrc = muonTriggerMatch_DR,
							triggerMatchTypesSrc = muonTriggerMatch_Types,
							triggerMatchPathsAndFiltersSrc = muonTriggerPathsAndFilters
							                 )

from DavisRunIITauTau.TupleConfigurations.ConfigTupleTriggers_cfi import (tauTriggerPathsAndFilters,
tauTriggerMatch_DR, tauTriggerMatch_Types)

process.customSlimmedTaus = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTaus::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::Ntuple'),
							NAME=cms.string("customSlimmedTaus"),
							TauEsCorrection=cms.double(1.01),
							TauEsUpSystematic=cms.double(1.03),
							TauEsDownSystematic=cms.double(0.97),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							triggerMatchDRSrc = tauTriggerMatch_DR,
							triggerMatchTypesSrc = tauTriggerMatch_Types,
							triggerMatchPathsAndFiltersSrc = tauTriggerPathsAndFilters
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

###############################
# test -- start
################################

from DavisRunIITauTau.PythonHelperClasses.pairContainer_cff import PairWiseMetHelper


mvaMEThelper = PairWiseMetHelper(process)
#mvaMEThelper.initializeMVAmet()



###############################
# test -- end
################################

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

# test -- pair producer

process.TupleEventPair = cms.EDProducer('TupleCandidateEventProducer' ,
							tauSrc =cms.InputTag("singleTauEsNominal0","singleTauEsNominal0","Ntuple"),
							electronSrc =cms.InputTag("singleElectron0","singleElectron0","Ntuple"),
							muonSrc =cms.InputTag(''),
							NAME=cms.string("TuplePair")
												)



# end test -- pair producer



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
# keep everything produced by Tuple-Code
#################################
#process.out.outputCommands +=['drop *_*_*_*']
#process.out.outputCommands +=['keep *_*_*_*']

process.out.outputCommands +=['keep TupleUserSpecifiedDatas_UserSpecifiedData_TupleUserSpecifiedData_PAT']




#################################
# keep everything produced by Ntuple
#################################
process.out.outputCommands +=['keep *_*_*_Ntuple']


###################################
# asked to keep trigger info 

process.out.outputCommands +=['keep *_l1extraParticles_*_*']



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

# test - start
mvaMEThelper.initializeMVAmet(process.p)
mvaMEThelper.runSingleLeptonProducers(process.p)
mvaMEThelper.runPairWiseMets(process.p)
# test - end

process.p *=process.TupleEventPair

process.e = cms.EndPath(process.out)


process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )






