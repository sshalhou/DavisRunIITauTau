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


# very basic cuts on (H-candidate) muons
# to help control size of flatTuple and or define alternate TTrees in the same file
signalMuonCuts = cms.PSet(
				# format is vdouble(min,max)
				Pt = cms.vdouble(18.0,1e30),
				EtaAbs = cms.vdouble(0.0,2.1),
				dxyAbs = cms.vdouble(0.0,0.045),
			    dzAbs = cms.vdouble(0.0,0.2),
			    # name of relativeIsol we want to cut on 
			    relIsoToCutOn = cms.string("DeltaBetaCorrectedRelIso"), 
			    relIsoCut = cms.vdouble(-1e50,0.15)
							)

# very basic cuts on (H-candidate) electrons
signalElectronCuts = cms.PSet(
				# format is vdouble(min,max)
				Pt = cms.vdouble(10.0,1e30),
				EtaAbs = cms.vdouble(0.0,2.5),
				dxyAbs = cms.vdouble(0.0,0.045),
			    dzAbs = cms.vdouble(0.0,0.2),
			    # name of relativeIsol we want to cut on 
			    relIsoToCutOn = cms.string("DeltaBetaCorrectedRelIso"), 
			    relIsoCut = cms.vdouble(-1e50,0.15)
							)

# very basic cuts on (H-candidate) taus
signalTauCuts = cms.PSet(
				# format is vdouble(min,max)
				Pt = cms.vdouble(20.0,1e30),
				EtaAbs = cms.vdouble(0.0,2.3),
			    # name of a single tauID we want to cut on 
			    tauIDtoCutOn = cms.string("byCombinedIsolationDeltaBetaCorrRaw3Hits"), 
			    tauIDCut = cms.vdouble(-1e50,1.5)
							)



OSpSet = cms.PSet(

			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(True),
			keepSS = cms.bool(False),
			keepTauEsNominal = cms.bool(True),
			keepTauEsUp = cms.bool(False),
			keepTauEsDown = cms.bool(False),

			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"decayModeFindingNewDMs",
				"againstMuonLoose3",
				"againstElectronVLooseMVA5",
				"againstMuonLoose3",
				"againstElectronMediumMVA5")

					)

OSEsDownSet = cms.PSet(

			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(True),
			keepSS = cms.bool(False),
			keepTauEsNominal = cms.bool(False),
			keepTauEsUp = cms.bool(False),
			keepTauEsDown = cms.bool(True),

			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"decayModeFindingNewDMs",
				"againstMuonLoose3",
				"againstElectronVLooseMVA5",
				"againstMuonLoose3",
				"againstElectronMediumMVA5")

					)


OSEsUpSet = cms.PSet(

			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(True),
			keepSS = cms.bool(False),
			keepTauEsNominal = cms.bool(False),
			keepTauEsUp = cms.bool(True),
			keepTauEsDown = cms.bool(False),

			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"decayModeFindingNewDMs",
				"againstMuonLoose3",
				"againstElectronVLooseMVA5",
				"againstMuonLoose3",
				"againstElectronMediumMVA5")

					)

SSpSet = cms.PSet(

			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(False),
			keepSS = cms.bool(True),
			keepTauEsNominal = cms.bool(True),
			keepTauEsUp = cms.bool(False),
			keepTauEsDown = cms.bool(False),

			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"decayModeFindingNewDMs",
				"againstMuonLoose3",
				"againstElectronVLooseMVA5",
				"againstMuonLoose3",
				"againstElectronMediumMVA5")

					)



SSEsDownSet = cms.PSet(

			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(False),
			keepSS = cms.bool(True),
			keepTauEsNominal = cms.bool(False),
			keepTauEsUp = cms.bool(False),
			keepTauEsDown = cms.bool(True),

			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"decayModeFindingNewDMs",
				"againstMuonLoose3",
				"againstElectronVLooseMVA5",
				"againstMuonLoose3",
				"againstElectronMediumMVA5")

					)


SSEsUpSet = cms.PSet(

			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(False),
			keepSS = cms.bool(True),
			keepTauEsNominal = cms.bool(False),
			keepTauEsUp = cms.bool(True),
			keepTauEsDown = cms.bool(False),

			# the Tau IDs we would like to keep in the FlatTuple
			# note : the hardcoded MAX variable in FlatTupleGenerator.cc limits the 
			# number of these that we can keep 

			tauIDsToKeep = cms.vstring(
				"byCombinedIsolationDeltaBetaCorrRaw3Hits",
				"decayModeFindingNewDMs",
				"againstMuonLoose3",
				"againstElectronVLooseMVA5",
				"againstMuonLoose3",
				"againstElectronMediumMVA5")

					)

process.OS = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("OSxTauEsNominal"),
	TreeCutSrc = OSpSet,
	eCutSrc = signalElectronCuts,
	muCutSrc = signalMuonCuts,
	tauCutSrc = signalTauCuts
								)

process.OSEsDown = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("OSxTauEsDown"),
	TreeCutSrc = OSEsDownSet,
	eCutSrc = signalElectronCuts,
	muCutSrc = signalMuonCuts,
	tauCutSrc = signalTauCuts
								)



process.OSEsUp = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("OSxTauEsUp"),
	TreeCutSrc = OSEsUpSet,
	eCutSrc = signalElectronCuts,
	muCutSrc = signalMuonCuts,
	tauCutSrc = signalTauCuts
								)

process.SS = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("SSxTauEsNominal"),
	TreeCutSrc = SSpSet,
	eCutSrc = signalElectronCuts,
	muCutSrc = signalMuonCuts,
	tauCutSrc = signalTauCuts
								)


process.SSEsDown = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("SSxTauEsDown"),
	TreeCutSrc = SSEsDownSet,
	eCutSrc = signalElectronCuts,
	muCutSrc = signalMuonCuts,
	tauCutSrc = signalTauCuts
								)



process.SSEsUp = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("SSxTauEsUp"),
	TreeCutSrc = SSEsUpSet,
	eCutSrc = signalElectronCuts,
	muCutSrc = signalMuonCuts,
	tauCutSrc = signalTauCuts
								)


# the following is needed
# because not all events have both eTau and muTau
process.options = cms.untracked.PSet(
SkipEvent = cms.untracked.vstring('ProductNotFound')
)


process.p = cms.Path(process.OS+process.OSEsUp+process.OSEsDown+process.SS+process.SSEsUp+process.SSEsDown)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string("FlatTuple.root")
)
