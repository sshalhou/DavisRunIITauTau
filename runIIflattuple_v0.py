import FWCore.ParameterSet.Config as cms

process = cms.Process("FlatTuple")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )


from DavisRunIITauTau.InputFlatFiles.FlatFileLists import testList 
#print testList

myfilelist = cms.untracked.vstring()

## turn off for crab jobs
# for aFile in testList:
# 	formatted_name = "file:"+aFile
# 	print 'adding file', formatted_name
# 	myfilelist.extend([formatted_name])

myfilelist.extend(['file:/uscms_data/d3/shalhout/RunIIWorking/UpdateEId/CMSSW_7_4_7/src/NtupleFile.root'])

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
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import svMassAtFlatTupleConfig


process.PASSCUTS = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("PASSCUTS"),
	EventCutSrc = generalConfig,
	LeptonCutVecSrc = theCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.NOCUTS = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','DavisNtuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','DavisNtuple'),
	NAME = cms.string("NOCUTS"),
	EventCutSrc = generalConfig,
	LeptonCutVecSrc = cms.VPSet(),
	SVMassConfig = svMassAtFlatTupleConfig
	)



process.p = cms.Path(process.PASSCUTS + process.NOCUTS)
#process.p = cms.Path(process.PASSCUTS)


process.TFileService = cms.Service("TFileService", fileName = cms.string("FlatTuple.root"))


# -- end test

#process.p = cms.Path(process.OS+process.OSEsUp+process.OSEsDown+process.SS+process.SSEsUp+process.SSEsDown)




