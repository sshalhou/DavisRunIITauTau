import FWCore.ParameterSet.Config as cms
process = cms.Process("Ntuple")




###################################
# preliminaries 
###################################


process.myProducerLabel = cms.EDProducer('Ntuple')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
# this next line seems to cause issues, unlike the example I am setting to False :
process.options = cms.untracked.PSet(allowUnscheduled = cms.untracked.bool(False))


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
							NAME=cms.string("customSlimmedTaus"),
							TauEsCorrection=cms.double(1.01),
							TauEsUpSystematic=cms.double(1.03),
							TauEsDownSystematic=cms.double(0.97)
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




from DavisRunIITauTau.PythonHelperClasses.pairContainer_cff import a_class_test
from DavisRunIITauTau.PythonHelperClasses.pairContainer_cff import b_class_test
from DavisRunIITauTau.PythonHelperClasses.pairContainer_cff import PairWiseMetHelper


#ATEST = a_class_test(process)
#BTEST = b_class_test(process)

from RecoMET.METPUSubtraction.mvaPFMET_cff import calibratedAK4PFJetsForPFMVAMEt
from RecoMET.METPUSubtraction.mvaPFMET_cff import puJetIdForPFMVAMEt
process.calibratedAK4PFJetsForPFMVAMEt = calibratedAK4PFJetsForPFMVAMEt.clone()
process.puJetIdForPFMVAMEt = puJetIdForPFMVAMEt.clone()


from JetMETCorrections.Configuration.DefaultJEC_cff import ak4PFJetsL1FastL2L3
process.load("RecoJets.JetProducers.ak4PFJets_cfi")
process.ak4PFJets.src = cms.InputTag("packedPFCandidates")
process.load("RecoMET.METPUSubtraction.mvaPFMET_cff")
process.pfMVAMEt.srcPFCandidates = cms.InputTag("packedPFCandidates")
process.pfMVAMEt.srcVertices = cms.InputTag("offlineSlimmedPrimaryVertices")
process.puJetIdForPFMVAMEt.jec =  cms.string('AK4PF')
process.puJetIdForPFMVAMEt.vertexes = cms.InputTag("offlineSlimmedPrimaryVertices")
process.puJetIdForPFMVAMEt.rho = cms.InputTag("fixedGridRhoFastjetAll")



prelimSequence  = cms.Sequence()
prelimSequence += process.calibratedAK4PFJetsForPFMVAMEt
prelimSequence += process.puJetIdForPFMVAMEt


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

# test - start
mvaMEThelper.runSingleLeptonProducers(process.p)
process.p *= prelimSequence
#mvaMEThelper.runMvaMetPrelims(process.p)
mvaMEThelper.runPairWiseMets(process.p)
#ATEST.printMCinfo(process.p)
#process.p *= process.XXX
#BTEST.makeLepCount(process.p)
# test - end

process.e = cms.EndPath(process.out)


process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

#################################
# keep everything produced by Tuple-Code
#################################
#process.out.outputCommands +=['drop *_*_*_*']
process.out.outputCommands +=['keep TupleUserSpecifiedDatas_UserSpecifiedData_TupleUserSpecifiedData_PAT']
process.out.outputCommands +=['keep *_*_*_*']






