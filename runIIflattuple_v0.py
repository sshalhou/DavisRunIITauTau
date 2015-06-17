import FWCore.ParameterSet.Config as cms

process = cms.Process("FlatTuple")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


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

TESTSET = cms.PSet(

			Mt = cms.vdouble(-1.0e30,30.0), # not used at the moment
			keepOS = cms.bool(True),
			keepSS = cms.bool(True),
			keepTauEsNominal = cms.bool(True),
			keepTauEsUp = cms.bool(False),
			keepTauEsDown = cms.bool(False),

			# how to rank pairs within this selection
			rankByPtSum = cms.bool(True),
			rankByIsolation = cms.bool(False),
			electronIsolationForRank = cms.string("DeltaBetaCorrectedRelIso"),
			muonIsolationForRank = cms.string("DeltaBetaCorrectedRelIso"),
			tauIDisolationForRank = cms.string("byCombinedIsolationDeltaBetaCorrRaw3Hits"),



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


# main cut vector PSet :
theCuts = cms.VPset(

	# for EleTau :
		cms.PSet(   candidatePairType = cms.string("EleTau"),
					electronCut = "(p4.pt>23 && abs(p4.eta)<2.1 && abs(dxy)<0.045 \
									&& abs(dz)<0.2 && relativeIsol('DeltaBetaCorrectedRelIso')<0.1)"),
					tauCut = 	  "(dz==0 && tauID('byCombinedIsolationDeltaBetaCorrRaw3Hits')<1.5


						abs(p4.eta)<2.1 && abs(dxy)<0.045 \
									&& abs(dz)<0.2 && relativeIsol('DeltaBetaCorrectedRelIso')<0.1)"),
				),

	# for MuTau :
		cms.PSet(
				 	candidatePairType = cms.string("MuonTau"),
					muonCut =  "(p4.pt>18 && abs(p4.eta)<2.1 && abs(dxy)<0.045 \
					&& abs(dz)<0.2 && relativeIsol('DeltaBetaCorrectedRelIso')<0.1)"

				),		
					

	# for TauTau
		cms.PSet(
				 	candidatePairType = cms.string("TauTau"),
					
									
				),



	# for EleMu :
		cms.PSet(
				 	candidatePairType = cms.string("EleMuon"),
					electronCut = "(p4.pt>10 && abs(p4.eta)<2.5 && abs(dxy)<0.045 \
					&& abs(dz)<0.2 && relativeIsol('DeltaBetaCorrectedRelIso')<0.15)",
					muonCut =  "(p4.pt>10 && abs(p4.eta)<2.5 && abs(dxy)<0.045 \
					&& abs(dz)<0.2 && relativeIsol('DeltaBetaCorrectedRelIso')<0.15)"
									
				)

				
)







process.XX = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvent','NtupleEvent','Ntuple'),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep','Ntuple'),
	NAME = cms.string("XX"),
	TreeCutSrc = TESTSET,
	candidateElectronCut = cms.string(electronCut),
	candidateMuonCut = cms.string(muonCut),
	candidateTauCut  = cms.string("p4.pt<-10"),
	vetoElectronCut  = cms.string(""),
	vetoMuonCut  = cms.string("")
								)



process.p = cms.Path(process.XX)

# -- end test

#process.p = cms.Path(process.OS+process.OSEsUp+process.OSEsDown+process.SS+process.SSEsUp+process.SSEsDown)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string("FlatTuple.root")
)
