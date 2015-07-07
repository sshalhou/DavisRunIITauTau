import FWCore.ParameterSet.Config as cms

process = cms.Process("FlatTuple")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(50)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )


myfilelist = cms.untracked.vstring()
myfilelist.extend(['file:/uscms_data/d3/shalhout/RunIIWorking/CMSSW_7_2_3_patch1/src/NtupleFile.root'])
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
	    fileNames=myfilelist
    )




# the following is needed
# because not all events have both eTau and muTau
process.options = cms.untracked.PSet(
SkipEvent = cms.untracked.vstring('ProductNotFound')
)

# -- start test

from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import generalConfig
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import theCuts


process.PASSCUTS = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("PASSCUTS"),
	EventCutSrc = generalConfig,
	LeptonCutVecSrc = theCuts
	)

process.NOCUTS = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("NOCUTS"),
	EventCutSrc = generalConfig,
	LeptonCutVecSrc = cms.VPSet()
	)

process.p = cms.Path(process.PASSCUTS + process.NOCUTS)

# -- end test

#process.p = cms.Path(process.OS+process.OSEsUp+process.OSEsDown+process.SS+process.SSEsUp+process.SSEsDown)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string("FlatTuple.root")
)
