import FWCore.ParameterSet.Config as cms
process = cms.Process("DavisNtuple")

###################################
# preliminaries 
###################################

dataSetName_ = "DUMMY_DATASET_NAME"
#process.myProducerLabel = cms.EDProducer('Ntuple')
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import *

########################################
# figure out what dataset and type
# we have asked for

from DavisRunIITauTau.TupleConfigurations.getSampleInfoForDataSet import getSampleInfoForDataSet
sampleData = getSampleInfoForDataSet(dataSetName_)


##################
# print the run settings 
print '******************************************'
print '********  running Ntuple job over dataset with the following parameters : ' 
print '******************************************'

print sampleData
print '******************************************'
print '******************************************'


if COMPUTE_SVMASS :
	print 'will compute SVmass with log_m term = ', SVMASS_LOG_M
	if USE_MVAMET :
		print ' will use mva met in SVmass computation (no recoil corr yet)'
	else :
		print 'will use pfMET in SVmass computation (no recoil corr yet)'

else :
	print '******************************************'
	print '***** WARNING SV MASS COMPUTE IS OFF *****'
	print '******************************************'


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
	print 'gen info retained for pdgIDs ' 
	print GEN_PARTICLES_TO_KEEP
else :
	print 'gen info retained for all pdgIDs '

print 'default btag algoritm = ', DEFAULT_BTAG_ALGORITHM
if APPLY_BTAG_SF :
	print ' btag SFs will be applied with random seed = ', BTAG_SF_SEED



# import of standard configurations
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500

# mva MET --start
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff import *
from JetMETCorrections.Configuration.DefaultJEC_cff import *


# mva MET -- end

###################################
# input - remove for crab running
###################################

#myfilelist = cms.untracked.vstring()
#myfilelist.extend(['file:/uscms_data/d3/shalhout/Spring15_SUSYGluGlu160diTau.root'])
#process.source = cms.Source("PoolSource",fileNames=myfilelist)

process.source = cms.Source("PoolSource")

###################################
# vertex filtering 
#     - filter+clone vertex collection
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigTupleOfflineVertices_cfi import vertexFilter

process.filteredVertices = cms.EDFilter(
    "VertexSelector",
    src = cms.InputTag('offlineSlimmedPrimaryVertices'),
    #cut = vertexFilter,
    cut = cms.string(""), # off until studies show cuts are needed
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


##################
# set up the new electron mva (this is new compared to 7_2_X)

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_PHYS14_PU20bx25_nonTrig_V1_cff']
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

wp80 = cms.InputTag("egmGsfElectronIDs:mvaEleID-PHYS14-PU20bx25-nonTrig-V1-wp80")
wp90 = cms.InputTag("egmGsfElectronIDs:mvaEleID-PHYS14-PU20bx25-nonTrig-V1-wp90")
wpVals = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Phys14NonTrigValues")
wpCats = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Phys14NonTrigCategories")


###################################
# perform custom parameter embedding
# in slimmed collections
#    - e.g. dz, relIso, mva outputs
# in the case of taus also handle
# the Energy scale variation
###################################



process.customSlimmedElectrons = cms.EDProducer('CustomPatElectronProducer' ,
							electronSrc =cms.InputTag('slimmedElectrons::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string("customSlimmedElectrons"),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),							
							rhoSources = rhoSourceList,
							eleMediumIdMap = wp80,
							eleTightIdMap = wp90,
							mvaValuesMap     = wpVals,
							mvaCategoriesMap = wpCats
							                 )







process.customSlimmedMuons = cms.EDProducer('CustomPatMuonProducer' ,
							muonSrc =cms.InputTag('slimmedMuons::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string("customSlimmedMuons"),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							rhoSources = rhoSourceList
							                 )


# produces all 3 variants in ES at once 
process.customSlimmedTaus = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTaus::PAT'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string("customSlimmedTaus"),
							TauEsCorrection=cms.double(1.0),
							TauEsUpSystematic=cms.double(1.0),
							TauEsDownSystematic=cms.double(1.0),
							# TauEsCorrection=cms.double(1.01),
							# TauEsUpSystematic=cms.double(1.03),
							# TauEsDownSystematic=cms.double(0.97),
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
	src = cms.InputTag('customSlimmedElectrons:customSlimmedElectrons:DavisNtuple'),
	cut = electronFilter
	)

process.filteredCustomMuons = cms.EDFilter("PATMuonRefSelector",
	src = cms.InputTag('customSlimmedMuons:customSlimmedMuons:DavisNtuple'),
	cut = muonFilter
	)

process.filteredCustomTausEsNominal = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTaus:customSlimmedTausTauEsNominal:DavisNtuple'),
	cut = tauFilter
	)


process.filteredCustomTausEsUp = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTaus:customSlimmedTausTauEsUp:DavisNtuple'),
	cut = tauFilter
	)

process.filteredCustomTausEsDown = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTaus:customSlimmedTausTauEsDown:DavisNtuple'),
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
	src = cms.InputTag('customSlimmedElectrons:customSlimmedElectrons:DavisNtuple'),
	cut = electronVetoFilter
	)

process.filteredVetoMuons = cms.EDFilter("PATMuonRefSelector",
	src = cms.InputTag('customSlimmedMuons:customSlimmedMuons:DavisNtuple'),
	cut = muonVetoFilter
	)


###################################
# double lepton requirement
# should go here
###################################


process.requireCandidateHiggsPair = cms.EDFilter("HiggsCandidateCountFilter",
  	electronSource = cms.InputTag("filteredCustomElectrons::DavisNtuple"),
	muonSource     = cms.InputTag("filteredCustomMuons::DavisNtuple"),
	tauSource      = cms.InputTag("filteredCustomTausEsDown::DavisNtuple"), # always count with down ES shift
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
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import PUntupleWeightSettings
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import pileupSrcInputTag
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import mcGenWeightSrcInputTag
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import LHEEventProductSrcInputTag
from DavisRunIITauTau.TupleConfigurations.SampleMetaData_cfi import sampleInfo

process.pairIndep = cms.EDProducer('NtuplePairIndependentInfoProducer',
							packedGenSrc = cms.InputTag('packedGenParticles::PAT'),
							prundedGenSrc =  cms.InputTag('prunedGenParticles::PAT'),
							NAME=cms.string("NtupleEventPairIndep"),
							genParticlesToKeep = GEN_PARTICLES_TO_KEEP,
							slimmedJetSrc = cms.InputTag('filteredSlimmedJets::DavisNtuple'),
							defaultBtagAlgorithmNameSrc = cms.string(DEFAULT_BTAG_ALGORITHM),
							useBtagSFSrc = cms.bool(APPLY_BTAG_SF),
							useBtagSFSeedSrc = cms.uint32(BTAG_SF_SEED),
							PUjetIDworkingPointSrc = PUjetIDworkingPoint,
							PFjetIDworkingPointSrc = PFjetIDworkingPoint,
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							pileupSrc = pileupSrcInputTag,
							PUweightSettingsSrc = PUntupleWeightSettings,
							mcGenWeightSrc = mcGenWeightSrcInputTag,
				  			LHEEventProductSrc = LHEEventProductSrcInputTag,
				  			sampleInfoSrc = sampleData

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
process.out.outputCommands += ['keep NtupleEvents_NtupleEvent_*_DavisNtuple']
process.out.outputCommands += ['keep NtuplePairIndependentInfos_pairIndep_NtupleEventPairIndep_DavisNtuple']
#process.p = cms.Path(process.myProducerLabel)
process.p = cms.Path()
#process.p *= process.UserSpecifiedData

process.p *= process.filteredVertices

process.p *= process.egmGsfElectronIDSequence
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


# mva met - start
mvaMEThelper.initializeMVAmet(process.p)
mvaMEThelper.runSingleLeptonProducers(process.p)
mvaMEThelper.runPairWiseMets(process.p)
process.p *= process.METSignificance
mvaMEThelper.run_pairMaker(process.p)
mvaMEThelper.writeToNtuple(process.p)
# mva met -- end

process.p *= process.filteredSlimmedJets
process.p *= process.pairIndep
process.e = cms.EndPath(process.out)


process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )






