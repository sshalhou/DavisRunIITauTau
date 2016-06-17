###########################
# produce a FlatTuple from Ntuple
# useful for debugging jobs locally only
# not suggested for crab usage

import FWCore.ParameterSet.Config as cms

INPUT_FILE = "./NtupleFile.root"

myfilelist = cms.untracked.vstring()
myfilelist.extend(['file:'+INPUT_FILE])


# must manually specify the dataSetName_ corresponding to the input Ntuple 
dataSetName_ = "/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_= "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"

print '******************************************************************************************************'
print '***************** input Ntuple is ', INPUT_FILE
print '******************************************************************************************************'


print '******************************************************************************************************'
print 'running FlatTuple production job assuming Ntuple contents consistent with '
print ' DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi'
print '******************************************************************************************************'


from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import *


########################################
# figure out what dataset and type
# we have asked for

from DavisRunIITauTau.TupleConfigurations.getSampleInfoForDataSet import getSampleInfoForDataSet
sampleData = getSampleInfoForDataSet(dataSetName_)


##################
# print the run settings 
print '******************************************'
print '********  running FlatTuple job over dataset with the following parameters : ' 
print '******************************************'

print sampleData
print '******************************************'
print '******************************************'




process = cms.Process("FlatTuple")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


from DavisRunIITauTau.InputFlatFiles.FlatFileLists import testList 
#print testList


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
	    fileNames=myfilelist
    )




# the following is needed
# because not all events have both eTau and muTau
process.options = cms.untracked.PSet(
SkipEvent = cms.untracked.vstring('ProductNotFound')
)


# -- start FlatTuple production 

from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import generalConfig
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import defaultCuts
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import lowDeltaRCuts
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import svMassAtFlatTupleConfig
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import BUILD_LOWDR






print '*** AT FLatTuple level, the MVA MET will be corrected using ',
print  sampleData.RecoilCorrection, ' recoil corrections'

print '*** AT FLatTuple level, the MVA MET systematics will be added using ',
print  sampleData.MetSystematicType, ' settings '



process.BASELINE = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvents','NtupleEvents','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("BASELINE"),
	FillEffLeptonBranches = cms.bool(BUILD_EFFICIENCY_TREE), # everywhere else it should be always False
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)


process.BASELINEupTau = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsTauEsUp','NtupleEventsTauEsUp','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("BASELINEupTau"),
	FillEffLeptonBranches = cms.bool(False), 
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("UP"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.BASELINEdownTau = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsTauEsDown','NtupleEventsTauEsDown','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("BASELINEdownTau"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("DOWN"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.BASELINEupElectron = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsElectronEsUp','NtupleEventsElectronEsUp','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("BASELINEupElectron"),
	FillEffLeptonBranches = cms.bool(False), 
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("UP"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.BASELINEdownElectron = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsElectronEsDown','NtupleEventsElectronEsDown','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("BASELINEdownElectron"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("DOWN"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)




process.LOWDELTAR = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvents','NtupleEvents','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("LOWDELTAR"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)


process.LOWDELTARupTau = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsTauEsUp','NtupleEventsTauEsUp','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("LOWDELTARupTau"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("UP"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.LOWDELTARdownTau = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsTauEsDown','NtupleEventsTauEsDown','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("LOWDELTARdownTau"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("DOWN"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)



process.LOWDELTARupElectron = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsElectronEsUp','NtupleEventsElectronEsUp','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("LOWDELTARupElectron"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("UP"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.LOWDELTARdownElectron = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsElectronEsDown','NtupleEventsElectronEsDown','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("LOWDELTARdownElectron"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("DOWN"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)




process.p = cms.Path()

process.p *= process.BASELINE

if BUILD_TAU_ES_VARIANTS is True :
	process.p *= process.BASELINEupTau 
	process.p *= process.BASELINEdownTau

if BUILD_ELECTRON_ES_VARIANTS is True :
	process.p *= process.BASELINEupElectron
	process.p *= process.BASELINEdownElectron


if BUILD_LOWDR is True :
	process.p *= process.LOWDELTAR	
	if BUILD_TAU_ES_VARIANTS is True :
		process.p *= process.LOWDELTARupTau 
		process.p *= process.LOWDELTARdownTau
	if BUILD_ELECTRON_ES_VARIANTS is True :
		process.p *= process.LOWDELTARupElectron
		process.p *= process.LOWDELTARdownElectron



process.TFileService = cms.Service("TFileService", fileName = cms.string("FlatTuple.root"))


# -- end test

#process.p = cms.Path(process.OS+process.OSEsUp+process.OSEsDown+process.SS+process.SSEsUp+process.SSEsDown)




