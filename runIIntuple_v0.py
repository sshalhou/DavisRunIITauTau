import FWCore.ParameterSet.Config as cms
process = cms.Process("Ntuple")

###################################
# preliminaries 
###################################


process.myProducerLabel = cms.EDProducer('Ntuple')
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import *


##################
# print the run settings 

print 'will build [',
if BUILD_ELECTRON_ELECTRON : print 'e-e',
if BUILD_ELECTRON_MUON : print 'e-mu',
if BUILD_ELECTRON_TAU : print 'e-tau',
if BUILD_MUON_MUON : print 'mu-mu',
if BUILD_MUON_TAU : print 'mu-tau',
if BUILD_TAU_TAU : print 'tau-tau',
if BUILD_TAU_ES_VARIANTS : print ' + tau Es Variants',
print ']'

if(len(GEN_PARTICLES_TO_KEEP) > 0):
	print 'gen info retained for pdgIDs ', GEN_PARTICLES_TO_KEEP
else :
	print 'gen info retained for all pdgIDs '

print 'default btag algoritm = ', DEFAULT_BTAG_ALGORITHM
if APPLY_BTAG_SF :
	print ' btag SFs will be applied with random seed = ', BTAG_SF_SEED

# import of standard configurations
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 50

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


############################
# define rho sources to be used in isol variants
rhoSourceList = cms.VInputTag(
	cms.InputTag('fixedGridRhoFastjetAll'),
	cms.InputTag('fixedGridRhoFastjetAllCalo'),
	cms.InputTag('fixedGridRhoFastjetCentralCalo'),
	cms.InputTag('fixedGridRhoFastjetCentralChargedPileUp'),
	cms.InputTag('fixedGridRhoFastjetCentralNeutral'),
	cms.InputTag('fixedGridRhoAll'))


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
							NAME=cms.string("customSlimmedElectrons"),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),							
							rhoSources = rhoSourceList
							                 )







process.customSlimmedMuons = cms.EDProducer('CustomPatMuonProducer' ,
							muonSrc =cms.InputTag('slimmedMuons::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::Ntuple'),
							NAME=cms.string("customSlimmedMuons"),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							rhoSources = rhoSourceList
							                 )



process.customSlimmedTaus = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTaus::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::Ntuple'),
							NAME=cms.string("customSlimmedTaus"),
							TauEsCorrection=cms.double(1.01),
							TauEsUpSystematic=cms.double(1.03),
							TauEsDownSystematic=cms.double(0.97),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger")
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
# apply jet filter onto 
# slimmed jet collection
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import jetFilter


process.filteredSlimmedJets = cms.EDFilter("PATJetRefSelector",
	src = cms.InputTag('slimmedJets::PAT'),
	cut = jetFilter
	)


###################################
# apply e/mu veto filters onto 
# custom slimmed lepton collections
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigVetoElectrons_cfi import electronVetoFilter
from DavisRunIITauTau.TupleConfigurations.ConfigVetoMuons_cfi import muonVetoFilter


process.filteredVetoElectrons = cms.EDFilter("PATElectronRefSelector",
	src = cms.InputTag('customSlimmedElectrons:customSlimmedElectrons:Ntuple'),
	cut = electronVetoFilter
	)

process.filteredVetoMuons = cms.EDFilter("PATMuonRefSelector",
	src = cms.InputTag('customSlimmedMuons:customSlimmedMuons:Ntuple'),
	cut = muonVetoFilter
	)


###################################
# double lepton requirement
# should go here
###################################


process.requireCandidateHiggsPair = cms.EDFilter("HiggsCandidateCountFilter",
  	electronSource = cms.InputTag("filteredCustomElectrons::Ntuple"),
	muonSource     = cms.InputTag("filteredCustomMuons::Ntuple"),
	tauSource      = cms.InputTag("filteredCustomTausEsDown::Ntuple"), # always count with down ES shift
	countElectronElectrons = cms.bool(BUILD_ELECTRON_ELECTRON),
	countElectronMuons  = cms.bool(BUILD_ELECTRON_MUON),
	countElectronTaus = cms.bool(BUILD_ELECTRON_TAU),
	countMuonMuons = cms.bool(BUILD_MUON_MUON),
	countMuonTaus = cms.bool(BUILD_MUON_TAU),
	countTauTaus = cms.bool(BUILD_TAU_TAU),
    filter = cms.bool(True)
)

###############################
# test -- start
################################

from DavisRunIITauTau.PythonHelperClasses.pairContainer_cff import PairWiseMetHelper


mvaMEThelper = PairWiseMetHelper(process)
#mvaMEThelper.initializeMVAmet()

# we also need to remake PFMET since it lacks met significance in Phys14
# this is unrelated to mvaMET

from RecoMET.METProducers.PFMET_cfi import pfMet
process.load("RecoMET/METProducers.METSignificance_cfi")
process.load("RecoMET/METProducers.METSignificanceParams_cfi")
process.pfMet = pfMet.clone(src = "packedPFCandidates")
process.pfMet.calculateSignificance = True
# before setting the above to true need to follow 
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMETSignificance


#################################
# pair independent content

from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import PUjetIDworkingPoint
from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import PFjetIDworkingPoint

process.pairIndep = cms.EDProducer('NtuplePairIndependentInfoProducer',
							packedGenSrc = cms.InputTag('packedGenParticles::PAT'),
							prundedGenSrc =  cms.InputTag('prunedGenParticles::PAT'),
							NAME=cms.string("NtupleEventPairIndep"),
							genParticlesToKeep = GEN_PARTICLES_TO_KEEP,
							slimmedJetSrc = cms.InputTag('filteredSlimmedJets::Ntuple'),
							defaultBtagAlgorithmNameSrc = cms.string(DEFAULT_BTAG_ALGORITHM),
							useBtagSFSrc = cms.bool(APPLY_BTAG_SF),
							useBtagSFSeedSrc = cms.uint32(BTAG_SF_SEED),
							PUjetIDworkingPointSrc = PUjetIDworkingPoint,
							PFjetIDworkingPointSrc = PFjetIDworkingPoint,
							vertexSrc =cms.InputTag('filteredVertices::Ntuple')

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
# keep everything produced by Tuple-Code
#################################
#process.out.outputCommands +=['drop *_*_*_*']
#rocess.out.outputCommands +=['drop *_*_*_*']
#process.out.outputCommands +=['keep TupleUserSpecifiedDatas_UserSpecifiedData_TupleUserSpecifiedData_PAT']




#################################
# keep everything produced by Ntuple
#################################
#process.out.outputCommands +=['keep *_*_*_Ntuple']
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1) )

###################################
# asked to keep trigger info 

#process.out.outputCommands +=['keep *_l1extraParticles_*_*']
process.out.outputCommands +=['drop *_*_*_*']
#process.out.outputCommands += ['keep TupleCandidateEvents_*_*_Ntuple']
process.out.outputCommands += ['keep NtupleEvents_NtupleEvent_*_Ntuple']
process.out.outputCommands += ['keep NtuplePairIndependentInfos_pairIndep_NtupleEventPairIndep_Ntuple']
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


process.p *= process.filteredVetoElectrons
process.p *= process.filteredVetoMuons

process.p *= process.requireCandidateHiggsPair



# test - start
mvaMEThelper.initializeMVAmet(process.p)
mvaMEThelper.runSingleLeptonProducers(process.p)
mvaMEThelper.runPairWiseMets(process.p)
process.p *= process.METSignificance
mvaMEThelper.run_pairMaker(process.p)
mvaMEThelper.writeToNtuple(process.p)
process.p *= process.filteredSlimmedJets
process.p *= process.pairIndep
# test -- end

process.e = cms.EndPath(process.out)


process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )






