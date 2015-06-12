import FWCore.ParameterSet.Config as cms

process = cms.Process("FlatTuple")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


myfilelist = cms.untracked.vstring()
myfilelist.extend(['file:/uscms_data/d3/shalhout/RunIIWorking/CMSSW_7_2_3_patch1/src/NtupleFile.root'])
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
	    fileNames=myfilelist
    )


testPSet = cms.PSet(
	
			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"decayModeFindingNewDMs",
				"againstMuonLoose3",
				"againstElectronVLooseMVA5",
				"againstMuonLoose3",
				"againstElectronMediumMVA5"),

			# cuts on specific tauID algorithms this is a VPSet
			# where each member PSet includes :
			# string name, double min, double max			
			# any events with tauID(name) < min or > max will not be kept 
			# should not include anything here that depends on the lepton pair type

			tauIDsAndCuts = cms.vdouble()

			# # additional cuts on tau legs
			# minimum_tauPt = cms.double(30.0),
			# maximum_tauPt = cms.double(1e30),
			# minimum_tauAbsEta = cms.double(30.0),
			# maximum_tauAbsEta = cms.double(1e30),





			# # the baisc cut parameters for tau ID #

			# minimum_tauPt = cms.double(30.0),
			# maximum_tauPt = cms.double(1e30),
			# tau_isolationVariableName = cms.string(""), 




			# tauPt = cms.vdouble(30.0,1.0e20),
			# electronPt = cms.vdouble(24.0,1.0e20),
			# muonPt = cms.vdouble(20.0,1.0e20),
			# Mt = cms.vdouble(30.0,1.0e29),
			# VisMass = cms.vdouble(25.0,100.0),	
			# isOS = cms.vdouble(1),
			# TauEsShift = cms.int32(0.0)
					)


process.TEST = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("TauEsNominal"),
	TreeCutSrc = testPSet
								)





# the following is needed
# because not all events have both eTau and muTau
process.options = cms.untracked.PSet(
SkipEvent = cms.untracked.vstring('ProductNotFound')
)


process.p = cms.Path(process.TEST)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string("FlatTuple.root")
)
