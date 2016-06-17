import FWCore.ParameterSet.Config as cms
process = cms.Process('DavisNtuple') 

###################################
# preliminaries 
###################################

# how many events to run, -1 means run all 
MAX_EVENTS = -1

# dataset dummy for crab job 

dataSetName_ = "DUMMY_DATASET_NAME"

if MAX_EVENTS != -1:
	print '*****************************************************************'
	print '*****************************************************************'
	print '****** WARNING asking to stop run after only ', MAX_EVENTS, 'events  '
	print '****** If this is a crab job, things will NOT go well :(  '
	print '*****************************************************************'
	print '*****************************************************************'



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




if COMPUTE_SVMASS_AT_NTUPLE :
	print 'will compute SVmass (@ NTUPLE level) with log_m term = ', SVMASS_LOG_M
	if USE_MVAMET :
		print ' will use mva met in SVmass computation (WARNING --- no recoil corr @ Ntuple level)'
	else :
		print 'will use pfMET in SVmass computation'

else :
	print '**************************************************'
	print '***** NOTE: SV MASS COMPUTE IS OFF (@ NTUPLE level) *****'
	print '**************************************************'


print 'will build [',
if BUILD_ELECTRON_ELECTRON : print 'e-e',
if BUILD_ELECTRON_MUON : print 'e-mu',
if BUILD_ELECTRON_TAU : print 'e-tau',
if BUILD_MUON_MUON : print 'mu-mu',
if BUILD_MUON_TAU : print 'mu-tau',
if BUILD_TAU_TAU : print 'tau-tau',
if BUILD_TAU_ES_VARIANTS : print ' + tau Es Variants',
if BUILD_EFFICIENCY_TREE : print ' will generate eff tree for e+X, mu+X, and tau+X',
print ']'

print '-----------------------------------------------------------------'
print 'only keeping up to ', MAX_ELECTRON_COUNT, 'electrons, ', MAX_ELECTRON_COUNT, 'muons and ', MAX_ELECTRON_COUNT, ' taus '
print 'passing lepton selections for pair formation '
print '-----------------------------------------------------------------'

if(len(GEN_PARTICLES_TO_KEEP) > 0):
	print 'gen info retained for pdgIDs ' 
	print GEN_PARTICLES_TO_KEEP
else :
	print 'gen info retained for all pdgIDs '

print 'default btag algoritm = ', DEFAULT_BTAG_ALGORITHM



# import of standard configurations
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag

if sampleData.EventType == 'MC':
	process.GlobalTag = GlobalTag(process.GlobalTag, '76X_mcRun2_asymptotic_RunIIFall15DR76_v1', '')
	#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

if sampleData.EventType == 'DATA':
	process.GlobalTag = GlobalTag(process.GlobalTag, '76X_dataRun2_16Dec2015_v0', '')
	#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

print '********** HAVE MANUALLY SET GLOBAL TAG SET TO  *********************'
print '**********', process.GlobalTag.globaltag
print '*******************************************************'

print '********** Running in unscheduled mode **********'
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.options.allowUnscheduled = cms.untracked.bool(True)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(MAX_EVENTS) ) 

###################################
# input - configured for crab running
###################################

process.source = cms.Source("PoolSource")


###################################
# Cumulative Info
#     - keep info about every event seen
#     - before any selections are applied
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import mcGenWeightSrcInputTag

process.Cumulative = cms.EDAnalyzer('CumulativeInfoAdder',
	mcGenWeightSrc = mcGenWeightSrcInputTag
	)


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


###################################
# re-apply Jet Energy Corrections
# will use tools already available in MVA MET
####################################

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")


from RecoMET.METPUSubtraction.localSqlite import recorrectJets

if sampleData.EventType == 'MC':
	recorrectJets(process, False)

if sampleData.EventType == 'DATA':
	recorrectJets(process, True)

###################################
# apply jet filter onto 
# slimmed jet collection
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import jetFilter


process.filteredSlimmedJets = cms.EDFilter("PATJetRefSelector",
	src = cms.InputTag('patJetsReapplyJEC'),
	cut = jetFilter
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
# set up the electron ID (including mvas)

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring15_25ns_nonTrig_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff']


for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

wp80 = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring15-25ns-nonTrig-V1-wp80")
wp90 = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring15-25ns-nonTrig-V1-wp90")
wpVals = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring15NonTrig25nsV1Values")
wpCats = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring15NonTrig25nsV1Categories")
cutVeto = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-veto")



###################################
# perform custom parameter embedding
# in slimmed collections
#    - e.g. dz, relIso, mva outputs
# in the case of taus also handle
# the Energy scale variation
###################################



process.customSlimmedElectrons = cms.EDProducer('CustomPatElectronProducer' ,
							electronSrc =cms.InputTag('slimmedElectrons'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string(""),
						    BarrelEnergyShift = cms.double(1.0),
						    EndcapEnergyShift = cms.double(1.0),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),							
							rhoSources = rhoSourceList,
							eleMediumIdMap = wp80,
							eleTightIdMap = wp90,
							mvaValuesMap     = wpVals,
							mvaCategoriesMap = wpCats,
							eleVetoIdMap = cutVeto
							                 )




process.customSlimmedElectronsEsUp = cms.EDProducer('CustomPatElectronProducer' ,
							electronSrc =cms.InputTag('slimmedElectrons'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string(""),
						    BarrelEnergyShift = cms.double(1.01),
						    EndcapEnergyShift = cms.double(1.025),							
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),							
							rhoSources = rhoSourceList,
							eleMediumIdMap = wp80,
							eleTightIdMap = wp90,
							mvaValuesMap     = wpVals,
							mvaCategoriesMap = wpCats,
							eleVetoIdMap = cutVeto
							                 )


process.customSlimmedElectronsEsDown = cms.EDProducer('CustomPatElectronProducer' ,
							electronSrc =cms.InputTag('slimmedElectrons'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string(""),
						    BarrelEnergyShift = cms.double(0.99),
						    EndcapEnergyShift = cms.double(0.975),								
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),							
							rhoSources = rhoSourceList,
							eleMediumIdMap = wp80,
							eleTightIdMap = wp90,
							mvaValuesMap     = wpVals,
							mvaCategoriesMap = wpCats,
							eleVetoIdMap = cutVeto
							                 )



process.customSlimmedMuons = cms.EDProducer('CustomPatMuonProducer' ,
							muonSrc =cms.InputTag('slimmedMuons'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string("customSlimmedMuons"),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							rhoSources = rhoSourceList
							                 )




# produces all 3 tau variants 

process.customSlimmedTausTauEsNominal = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTaus'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string(""),
							#TauEsCorrection=cms.double(0.99),
							TauEsCorrection=cms.double(1.0),
							TauEsSystematicShift=cms.double(1.0),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							rhoSources = rhoSourceList
							                 )


process.customSlimmedTausTauEsUp = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTaus'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string(""),
							#TauEsCorrection=cms.double(0.99),
							TauEsCorrection=cms.double(1.0),
							TauEsSystematicShift=cms.double(1.03),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							rhoSources = rhoSourceList
							                 )



process.customSlimmedTausTauEsDown = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTaus'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string(""),
							#TauEsCorrection=cms.double(0.99),
							TauEsCorrection=cms.double(1.0),
							TauEsSystematicShift=cms.double(0.97),
							triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							rhoSources = rhoSourceList
							                 )



###################################
# apply lepton filters onto 
# custom slimmed lepton collections
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigTupleElectrons_cfi import electronFilter
from DavisRunIITauTau.TupleConfigurations.ConfigTupleMuons_cfi import muonFilter
from DavisRunIITauTau.TupleConfigurations.ConfigTupleTaus_cfi import tauFilter



process.filteredCustomElectrons = cms.EDFilter("PATElectronRefSelector",
	src = cms.InputTag('customSlimmedElectrons::DavisNtuple'),
	cut = electronFilter
	)

process.filteredCustomElectronsEsUp = cms.EDFilter("PATElectronRefSelector",
	src = cms.InputTag('customSlimmedElectronsEsUp::DavisNtuple'),
	cut = electronFilter
	)

process.filteredCustomElectronsEsDown = cms.EDFilter("PATElectronRefSelector",
	src = cms.InputTag('customSlimmedElectronsEsDown::DavisNtuple'),
	cut = electronFilter
	)


process.filteredCustomMuons = cms.EDFilter("PATMuonRefSelector",
	src = cms.InputTag('customSlimmedMuons:customSlimmedMuons:DavisNtuple'),
	cut = muonFilter
	)

process.filteredCustomTausEsNominal = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTausTauEsNominal::DavisNtuple'),
	cut = tauFilter
	)


process.filteredCustomTausEsUp = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTausTauEsUp::DavisNtuple'),
	cut = tauFilter
	)

process.filteredCustomTausEsDown = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTausTauEsDown::DavisNtuple'),
	cut = tauFilter
	)


##################################################
# apply the max lepton count cut for each type   #
##################################################


process.TrimmedFilteredCustomElectrons = cms.EDProducer('TrimmedPatElectronProducer' ,
   					 electronSrc = cms.InputTag("filteredCustomElectrons::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_ELECTRON_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomElectrons"))


process.TrimmedFilteredCustomElectronsEsUp = cms.EDProducer('TrimmedPatElectronProducer' ,
   					 electronSrc = cms.InputTag("filteredCustomElectronsEsUp::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_ELECTRON_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomElectronsEsUp"))


process.TrimmedFilteredCustomElectronsEsDown = cms.EDProducer('TrimmedPatElectronProducer' ,
   					 electronSrc = cms.InputTag("filteredCustomElectronsEsDown::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_ELECTRON_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomElectronsEsDown"))


process.TrimmedFilteredCustomMuons = cms.EDProducer('TrimmedPatMuonProducer' ,
   					 muonSrc = cms.InputTag("filteredCustomMuons::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_MUON_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomMuons"))



process.TrimmedFilteredCustomTausEsNominal = cms.EDProducer('TrimmedPatTauProducer' ,
   					 tauSrc = cms.InputTag("filteredCustomTausEsNominal::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_TAU_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomTausEsNominal"))


process.TrimmedFilteredCustomTausEsUp = cms.EDProducer('TrimmedPatTauProducer' ,
   					 tauSrc = cms.InputTag("filteredCustomTausEsUp::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_TAU_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomTausEsUp"))


process.TrimmedFilteredCustomTausEsDown = cms.EDProducer('TrimmedPatTauProducer' ,
   					 tauSrc = cms.InputTag("filteredCustomTausEsDown::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_TAU_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomTausEsDown"))



###################################
# apply e/mu veto filters onto 
# custom slimmed lepton collections
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigVetoElectrons_cfi import electronVetoFilter
from DavisRunIITauTau.TupleConfigurations.ConfigVetoMuons_cfi import muonVetoFilter


process.filteredVetoElectrons = cms.EDFilter("PATElectronRefSelector",
	src = cms.InputTag('customSlimmedElectrons::DavisNtuple'),
	cut = electronVetoFilter
	)

process.filteredVetoElectronsEsUp = cms.EDFilter("PATElectronRefSelector",
	src = cms.InputTag('customSlimmedElectronsEsUp::DavisNtuple'),
	cut = electronVetoFilter
	)

process.filteredVetoElectronsEsDown = cms.EDFilter("PATElectronRefSelector",
	src = cms.InputTag('customSlimmedElectronsEsDown::DavisNtuple'),
	cut = electronVetoFilter
	)

process.filteredVetoMuons = cms.EDFilter("PATMuonRefSelector",
	src = cms.InputTag('customSlimmedMuons:customSlimmedMuons:DavisNtuple'),
	cut = muonVetoFilter
	)



###################################
# double lepton requirement
# only applied if 
# BUILD_EFFICIENCY_TREE
# are all False
###################################


process.requireCandidateHiggsPair = cms.EDFilter("HiggsCandidateCountFilter",
  	electronSource = cms.InputTag("TrimmedFilteredCustomElectronsEsDown:TrimmedFilteredCustomElectronsEsDown:DavisNtuple"), # always count with Down ES shift
	muonSource     = cms.InputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),
	tauSource      = cms.InputTag("TrimmedFilteredCustomTausEsDown:TrimmedFilteredCustomTausEsDown:DavisNtuple"), # always count with Down ES shift
	countElectronElectrons = cms.bool(BUILD_ELECTRON_ELECTRON),
	countElectronMuons  = cms.bool(BUILD_ELECTRON_MUON),
	countElectronTaus = cms.bool(BUILD_ELECTRON_TAU),
	countMuonMuons = cms.bool(BUILD_MUON_MUON),
	countMuonTaus = cms.bool(BUILD_MUON_TAU),
	countTauTaus = cms.bool(BUILD_TAU_TAU),
    filter = cms.bool(True)
)

#########################################
# new MVA MET (pairwise) interface
# along with setup for tau ES var
##########################################

from RecoMET.METPUSubtraction.LeptonSelectionTools_cff import applyTauID as tauIDforMVAmetEsUp
from RecoMET.METPUSubtraction.LeptonSelectionTools_cff import applyTauID as tauIDforMVAmetEsDown
from RecoMET.METPUSubtraction.LeptonSelectionTools_cff import applyTauID as tauIDforMVAmetNominal

from RecoMET.METPUSubtraction.LeptonSelectionTools_cff import applyElectronID as electronIDforMVAmetUp
from RecoMET.METPUSubtraction.LeptonSelectionTools_cff import applyElectronID as electronIDforMVAmetDown
from RecoMET.METPUSubtraction.LeptonSelectionTools_cff import applyElectronID as electronIDforMVAmet


#######################################################
# special electron collections needed for mvamet   
# settings should match MVAMETConfiguration_cff.py
########################################################

electronIDforMVAmet(process, 
                label = "Tight", 
                src   = "customSlimmedElectrons",
                iso_map_charged_hadron  = '',
                iso_map_neutral_hadron  = '',
                iso_map_photon          = '',
                typeIso = "rhoCorr",
                electron_id_map = 'egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight',
                relativeIsolationCutVal = 0.12
                )

electronIDforMVAmetUp(process, 
                label = "Tight", 
                src   = "customSlimmedElectronsUp",
                iso_map_charged_hadron  = '',
                iso_map_neutral_hadron  = '',
                iso_map_photon          = '',
                typeIso = "rhoCorr",
                electron_id_map = 'egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight',
                relativeIsolationCutVal = 0.12
                )

electronIDforMVAmetDown(process, 
                label = "Tight", 
                src   = "customSlimmedElectronsEsDown",
                iso_map_charged_hadron  = '',
                iso_map_neutral_hadron  = '',
                iso_map_photon          = '',
                typeIso = "rhoCorr",
                electron_id_map = 'egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight',
                relativeIsolationCutVal = 0.12
                )





#######################################################
# special tau collections needed for mvamet   
# settings should match MVAMETConfiguration_cff.py
########################################################

tauIDforMVAmetNominal( process, 
            label = "Loose", 
            src = "customSlimmedTausTauEsNominal",
            muonCollection     = "slimmedMuons"+"Tight",
            electronCollection = "slimmedElectrons"+"Tight")


tauIDforMVAmetEsUp( process, 
            label = "Loose", 
            src = "customSlimmedTausTauEsUp",
            muonCollection     = "slimmedMuons"+"Tight",
            electronCollection = "slimmedElectrons"+"Tight")


tauIDforMVAmetEsDown( process, 
            label = "Loose", 
            src = "customSlimmedTausTauEsDown",
            muonCollection     = "slimmedMuons"+"Tight",
            electronCollection = "slimmedElectrons"+"Tight")


##################################
# init mva met 
##################################

from RecoMET.METPUSubtraction.MVAMETConfiguration_cff import runMVAMET
runMVAMET( process, jetCollectionPF = "patJetsReapplyJEC")


#################################
# modify the default mva met    #
#################################

process.MVAMET.srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
										   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
										   "TrimmedFilteredCustomTausEsNominal:TrimmedFilteredCustomTausEsNominal:DavisNtuple")

process.MVAMET.srcTaus = cms.InputTag("customSlimmedTausTauEsNominalLooseCleaned")
process.MVAMET.srcElectrons = cms.InputTag("customSlimmedElectronsTight")

process.MVAMET.requireOS = cms.bool(False)


##################################################################
# clone the default (with mods) and adjust for tau ES up
##################################################################

process.MVAMETtauEsUp = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
											   "TrimmedFilteredCustomTausEsUp:TrimmedFilteredCustomTausEsUp:DavisNtuple"),
												srcElectrons = cms.InputTag("customSlimmedElectronsTight"),
												srcTaus = cms.InputTag("customSlimmedTausTauEsUpLooseCleaned"),
												requireOS = cms.bool(False))


##################################################################
# clone the default (with mods) and adjust for tau ES down
##################################################################

process.MVAMETtauEsDown = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
											   "TrimmedFilteredCustomTausEsDown:TrimmedFilteredCustomTausEsDown:DavisNtuple"),
												srcElectrons = cms.InputTag("customSlimmedElectronsTight"),
												srcTaus = cms.InputTag("customSlimmedTausTauEsDownLooseCleaned"),
												requireOS = cms.bool(False))


##################################################################
# clone the default (with mods) and adjust for electron ES up
# since the electron ES systematic applies only for e+mu
# evaluate only e + mu pairs (that is why srcLeptons does not use taus)
##################################################################

process.MVAMETelectronEsUp = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectronsEsUp:TrimmedFilteredCustomElectronsEsUp:DavisNtuple"),
												srcElectrons = cms.InputTag("customSlimmedElectronsEsUpTight"),
												srcTaus = cms.InputTag("customSlimmedTausTauEsNominalLooseCleaned"),
												requireOS = cms.bool(False))


process.MVAMETelectronEsDown = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectronsEsDown:TrimmedFilteredCustomElectronsEsDown:DavisNtuple"),
												srcElectrons = cms.InputTag("customSlimmedElectronsEsDownTight"),
												srcTaus = cms.InputTag("customSlimmedTausTauEsNominalLooseCleaned"),
												requireOS = cms.bool(False))




###########



##################
# memory check 

if RUN_MEM_CHECK is True:
	process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1) )


# 

####################
# produce the TupleCandidateEvent pair + MET container

from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import generalConfig as TauIsoConfigRank
tauIsolForOrderingPair_ = TauIsoConfigRank.getParameter("tauIDisolationForRank")
smallerTauIsoValueIsBetter_ = TauIsoConfigRank.getParameter("tau_isSmallerValueMoreIsolated")

print "Tau_h + Tau_h pairs will be ordered by", tauIsolForOrderingPair_
if smallerTauIsoValueIsBetter_ is True:
	print " smaller value of tau iso is better isolated"
else:
	print " larger value of tau iso is better isolated"


process.TupleCandidateEvents = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("patpfMETT1"), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMET:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectrons","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.1),
	NAME=cms.string("TupleCandidateEvents"),
    doSVMass = cms.bool(COMPUTE_SVMASS_AT_NTUPLE),
    useMVAMET = cms.bool(USE_MVAMET),
    logMterm = cms.double(SVMASS_LOG_M),
    svMassVerbose = cms.int32(SVMASS_VERBOSE),
    # need to order the taus by isolation in tau_h + tau_h pairs
    tauIsolForOrderingPair = tauIsolForOrderingPair_,
    smallerTauIsoValueIsBetter = smallerTauIsoValueIsBetter_,
    EffElectronSrc = cms.InputTag("TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple"),
    EffMuonSrc = cms.InputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),
    EffTauSrc = cms.InputTag("TrimmedFilteredCustomTausEsNominal:TrimmedFilteredCustomTausEsNominal:DavisNtuple"),
    BuildEfficiencyTree = cms.bool(BUILD_EFFICIENCY_TREE)
						)	


process.TupleCandidateEventsTauEsUp = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("patpfMETT1"), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETtauEsUp:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectrons","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.1), 
	NAME=cms.string("TupleCandidateEventsTauEsUp"),
    doSVMass = cms.bool(COMPUTE_SVMASS_AT_NTUPLE),
    useMVAMET = cms.bool(USE_MVAMET),
    logMterm = cms.double(SVMASS_LOG_M),
    svMassVerbose = cms.int32(SVMASS_VERBOSE),
    # need to order the taus by isolation in tau_h + tau_h pairs
    tauIsolForOrderingPair = tauIsolForOrderingPair_,
    smallerTauIsoValueIsBetter = smallerTauIsoValueIsBetter_,
    EffElectronSrc = cms.InputTag("TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple"),
    EffMuonSrc = cms.InputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),
    EffTauSrc = cms.InputTag("TrimmedFilteredCustomTausEsUp:TrimmedFilteredCustomTausEsUp:DavisNtuple"),
    BuildEfficiencyTree = cms.bool(False)
						)	

process.TupleCandidateEventsTauEsDown = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("patpfMETT1"), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETtauEsDown:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectrons","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.1), 
	NAME=cms.string("TupleCandidateEventsTauEsDown"),
    doSVMass = cms.bool(COMPUTE_SVMASS_AT_NTUPLE),
    useMVAMET = cms.bool(USE_MVAMET),
    logMterm = cms.double(SVMASS_LOG_M),
    svMassVerbose = cms.int32(SVMASS_VERBOSE),
    # need to order the taus by isolation in tau_h + tau_h pairs
    tauIsolForOrderingPair = tauIsolForOrderingPair_,
    smallerTauIsoValueIsBetter = smallerTauIsoValueIsBetter_,
    EffElectronSrc = cms.InputTag("TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple"),
    EffMuonSrc = cms.InputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),
    EffTauSrc = cms.InputTag("TrimmedFilteredCustomTausEsDown:TrimmedFilteredCustomTausEsDown:DavisNtuple"),
    BuildEfficiencyTree = cms.bool(False)
						)	

process.TupleCandidateEventsElectronEsUp = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("patpfMETT1"), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETelectronEsUp:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectronsEsUp","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.1), 
	NAME=cms.string("TupleCandidateEventsElectronEsUp"),
    doSVMass = cms.bool(COMPUTE_SVMASS_AT_NTUPLE),
    useMVAMET = cms.bool(USE_MVAMET),
    logMterm = cms.double(SVMASS_LOG_M),
    svMassVerbose = cms.int32(SVMASS_VERBOSE),
    # need to order the taus by isolation in tau_h + tau_h pairs
    tauIsolForOrderingPair = tauIsolForOrderingPair_,
    smallerTauIsoValueIsBetter = smallerTauIsoValueIsBetter_,
    EffElectronSrc = cms.InputTag("TrimmedFilteredCustomElectronsEsUp:TrimmedFilteredCustomElectronsEsUp:DavisNtuple"),
    EffMuonSrc = cms.InputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),
    EffTauSrc = cms.InputTag("TrimmedFilteredCustomTausEsNominal:TrimmedFilteredCustomTausEsNominal:DavisNtuple"),
    BuildEfficiencyTree = cms.bool(False)
						)	



process.TupleCandidateEventsElectronEsDown = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("patpfMETT1"), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETelectronEsDown:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectronsEsDown","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.1), 
	NAME=cms.string("TupleCandidateEventsElectronEsDown"),
    doSVMass = cms.bool(COMPUTE_SVMASS_AT_NTUPLE),
    useMVAMET = cms.bool(USE_MVAMET),
    logMterm = cms.double(SVMASS_LOG_M),
    svMassVerbose = cms.int32(SVMASS_VERBOSE),
    # need to order the taus by isolation in tau_h + tau_h pairs
    tauIsolForOrderingPair = tauIsolForOrderingPair_,
    smallerTauIsoValueIsBetter = smallerTauIsoValueIsBetter_,
    EffElectronSrc = cms.InputTag("TrimmedFilteredCustomElectronsEsDown:TrimmedFilteredCustomElectronsEsDown:DavisNtuple"),
    EffMuonSrc = cms.InputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),
    EffTauSrc = cms.InputTag("TrimmedFilteredCustomTausEsNominal:TrimmedFilteredCustomTausEsNominal:DavisNtuple"),
    BuildEfficiencyTree = cms.bool(False)
						)	


#####################################
# config the NtupleEvents producer  #

from DavisRunIITauTau.TupleConfigurations.ConfigTupleTriggers_cfi import ConfigTriggerHelper

# this will set the correct trigger info for the given data type
ConfigTriggerHelperInstance = ConfigTriggerHelper(sampleData)

electronTriggerPathsAndFilters = ConfigTriggerHelperInstance.electronTriggerPathsAndFilters
electronTriggerMatch_DR = ConfigTriggerHelperInstance.electronTriggerMatch_DR
electronTriggerMatch_Types = ConfigTriggerHelperInstance.electronTriggerMatch_Types

muonTriggerPathsAndFilters = ConfigTriggerHelperInstance.muonTriggerPathsAndFilters
muonTriggerMatch_DR = ConfigTriggerHelperInstance.muonTriggerMatch_DR
muonTriggerMatch_Types = ConfigTriggerHelperInstance.muonTriggerMatch_Types

tauTriggerPathsAndFilters = ConfigTriggerHelperInstance.tauTriggerPathsAndFilters
tauTriggerMatch_DR = ConfigTriggerHelperInstance.tauTriggerMatch_DR
tauTriggerMatch_Types = ConfigTriggerHelperInstance.tauTriggerMatch_Types



process.NtupleEvents = cms.EDProducer('NtupleEventProducer' ,
				 tupleCandidateEventSrc = cms.InputTag("TupleCandidateEvents","TupleCandidateEvents","DavisNtuple"),
				 l1extraParticlesSrc = cms.InputTag("l1extraParticles","IsoTau","RECO"),
				 triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
				 triggerPreScaleSrc = cms.InputTag("patTrigger"),
				 triggerObjectSrc = cms.InputTag("selectedPatTrigger"),				 
				 electron_triggerMatchDRSrc = electronTriggerMatch_DR,
				 electron_triggerMatchTypesSrc = electronTriggerMatch_Types,
				 electron_triggerMatchPathsAndFiltersSrc = electronTriggerPathsAndFilters,
				 muon_triggerMatchDRSrc = muonTriggerMatch_DR,
				 muon_triggerMatchTypesSrc = muonTriggerMatch_Types,
				 muon_triggerMatchPathsAndFiltersSrc = muonTriggerPathsAndFilters,
				 tau_triggerMatchDRSrc = tauTriggerMatch_DR,
				 tau_triggerMatchTypesSrc = tauTriggerMatch_Types,
				 tau_triggerMatchPathsAndFiltersSrc = tauTriggerPathsAndFilters,
			     NAME=cms.string("NtupleEvents"))



process.NtupleEventsTauEsUp = cms.EDProducer('NtupleEventProducer' ,
				 tupleCandidateEventSrc = cms.InputTag("TupleCandidateEventsTauEsUp","TupleCandidateEventsTauEsUp","DavisNtuple"),
				 l1extraParticlesSrc = cms.InputTag("l1extraParticles","IsoTau","RECO"),
				 triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
				 triggerPreScaleSrc = cms.InputTag("patTrigger"),
				 triggerObjectSrc = cms.InputTag("selectedPatTrigger"),				 
				 electron_triggerMatchDRSrc = electronTriggerMatch_DR,
				 electron_triggerMatchTypesSrc = electronTriggerMatch_Types,
				 electron_triggerMatchPathsAndFiltersSrc = electronTriggerPathsAndFilters,
				 muon_triggerMatchDRSrc = muonTriggerMatch_DR,
				 muon_triggerMatchTypesSrc = muonTriggerMatch_Types,
				 muon_triggerMatchPathsAndFiltersSrc = muonTriggerPathsAndFilters,
				 tau_triggerMatchDRSrc = tauTriggerMatch_DR,
				 tau_triggerMatchTypesSrc = tauTriggerMatch_Types,
				 tau_triggerMatchPathsAndFiltersSrc = tauTriggerPathsAndFilters,
			     NAME=cms.string("NtupleEventsTauEsUp"))


process.NtupleEventsTauEsDown = cms.EDProducer('NtupleEventProducer' ,
				 tupleCandidateEventSrc = cms.InputTag("TupleCandidateEventsTauEsDown","TupleCandidateEventsTauEsDown","DavisNtuple"),
				 l1extraParticlesSrc = cms.InputTag("l1extraParticles","IsoTau","RECO"),
				 triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
				 triggerPreScaleSrc = cms.InputTag("patTrigger"),
				 triggerObjectSrc = cms.InputTag("selectedPatTrigger"),				 
				 electron_triggerMatchDRSrc = electronTriggerMatch_DR,
				 electron_triggerMatchTypesSrc = electronTriggerMatch_Types,
				 electron_triggerMatchPathsAndFiltersSrc = electronTriggerPathsAndFilters,
				 muon_triggerMatchDRSrc = muonTriggerMatch_DR,
				 muon_triggerMatchTypesSrc = muonTriggerMatch_Types,
				 muon_triggerMatchPathsAndFiltersSrc = muonTriggerPathsAndFilters,
				 tau_triggerMatchDRSrc = tauTriggerMatch_DR,
				 tau_triggerMatchTypesSrc = tauTriggerMatch_Types,
				 tau_triggerMatchPathsAndFiltersSrc = tauTriggerPathsAndFilters,
			     NAME=cms.string("NtupleEventsTauEsDown"))

process.NtupleEventsElectronEsUp = cms.EDProducer('NtupleEventProducer' ,
				 tupleCandidateEventSrc = cms.InputTag("TupleCandidateEventsElectronEsUp","TupleCandidateEventsElectronEsUp","DavisNtuple"),
				 l1extraParticlesSrc = cms.InputTag("l1extraParticles","IsoTau","RECO"),
				 triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
				 triggerPreScaleSrc = cms.InputTag("patTrigger"),
				 triggerObjectSrc = cms.InputTag("selectedPatTrigger"),				 
				 electron_triggerMatchDRSrc = electronTriggerMatch_DR,
				 electron_triggerMatchTypesSrc = electronTriggerMatch_Types,
				 electron_triggerMatchPathsAndFiltersSrc = electronTriggerPathsAndFilters,
				 muon_triggerMatchDRSrc = muonTriggerMatch_DR,
				 muon_triggerMatchTypesSrc = muonTriggerMatch_Types,
				 muon_triggerMatchPathsAndFiltersSrc = muonTriggerPathsAndFilters,
				 tau_triggerMatchDRSrc = tauTriggerMatch_DR,
				 tau_triggerMatchTypesSrc = tauTriggerMatch_Types,
				 tau_triggerMatchPathsAndFiltersSrc = tauTriggerPathsAndFilters,
			     NAME=cms.string("NtupleEventsElectronEsUp"))

process.NtupleEventsElectronEsDown = cms.EDProducer('NtupleEventProducer' ,
				 tupleCandidateEventSrc = cms.InputTag("TupleCandidateEventsElectronEsDown","TupleCandidateEventsElectronEsDown","DavisNtuple"),
				 l1extraParticlesSrc = cms.InputTag("l1extraParticles","IsoTau","RECO"),
				 triggerBitSrc = cms.InputTag("TriggerResults","","HLT"),
				 triggerPreScaleSrc = cms.InputTag("patTrigger"),
				 triggerObjectSrc = cms.InputTag("selectedPatTrigger"),				 
				 electron_triggerMatchDRSrc = electronTriggerMatch_DR,
				 electron_triggerMatchTypesSrc = electronTriggerMatch_Types,
				 electron_triggerMatchPathsAndFiltersSrc = electronTriggerPathsAndFilters,
				 muon_triggerMatchDRSrc = muonTriggerMatch_DR,
				 muon_triggerMatchTypesSrc = muonTriggerMatch_Types,
				 muon_triggerMatchPathsAndFiltersSrc = muonTriggerPathsAndFilters,
				 tau_triggerMatchDRSrc = tauTriggerMatch_DR,
				 tau_triggerMatchTypesSrc = tauTriggerMatch_Types,
				 tau_triggerMatchPathsAndFiltersSrc = tauTriggerPathsAndFilters,
			     NAME=cms.string("NtupleEventsElectronEsDown"))



#################################
# pair independent content

from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import PUjetIDworkingPoint
from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import PFjetIDworkingPoint
from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import TightPFjetIDworkingPoint
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import PUntupleWeightSettings
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import pileupSrcInputTag
#from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import mcGenWeightSrcInputTag
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import LHEEventProductSrcInputTag
from DavisRunIITauTau.TupleConfigurations.SampleMetaData_cfi import sampleInfo


print '****************************************************************************************************'
print '****  JERresolutionFile is ', "DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/Fall15_25nsV2_MC_PtResolution_AK4PFchs.txt"
print '****  JERscalefactorFile is ', "DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/Fall15_25nsV2_MC_SF_AK4PFchs.txt"
print '****   If not current, change in main python config : runII*.py'
print '****************************************************************************************************'

process.pairIndep = cms.EDProducer('NtuplePairIndependentInfoProducer',
							packedGenSrc = cms.InputTag('packedGenParticles'),
							prundedGenSrc =  cms.InputTag('prunedGenParticles'),
							NAME=cms.string("NtupleEventPairIndep"),
							JERresolutionFile = cms.string("DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/Fall15_25nsV2_MC_PtResolution_AK4PFchs.txt"),
							JERscalefactorFile = cms.string("DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/Fall15_25nsV2_MC_SF_AK4PFchs.txt"),
							genParticlesToKeep = GEN_PARTICLES_TO_KEEP,
							slimmedJetSrc = cms.InputTag('filteredSlimmedJets::DavisNtuple'),
							slimmedGenJetsSrc = cms.InputTag('slimmedGenJets'),
							defaultBtagAlgorithmNameSrc = cms.string(DEFAULT_BTAG_ALGORITHM),							
							PUjetIDworkingPointSrc = PUjetIDworkingPoint,
							PFjetIDworkingPointSrc = PFjetIDworkingPoint,
							TightPFjetIDworkingPointSrc = TightPFjetIDworkingPoint,
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							pileupSrc = pileupSrcInputTag,
							PUweightSettingsSrc = PUntupleWeightSettings,
							mcGenWeightSrc = mcGenWeightSrcInputTag,
				  			LHEEventProductSrc = LHEEventProductSrcInputTag,
				  			sampleInfoSrc = sampleData,						
							triggerResultsPatSrc = cms.InputTag("TriggerResults","","PAT"),
							triggerResultsRecoSrc = cms.InputTag("TriggerResults","","RECO"),
							rhoSource = cms.InputTag('fixedGridRhoFastjetAll')
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

process.p *= process.Cumulative
process.p *= process.filteredVertices

process.p *= process.patJetCorrFactorsReapplyJEC 
process.p *= process.patJetsReapplyJEC


process.p *= process.filteredSlimmedJets


process.p *= process.egmGsfElectronIDSequence
process.p *= process.customSlimmedElectrons
process.p *= process.customSlimmedElectronsEsUp
process.p *= process.customSlimmedElectronsEsDown
process.p *= process.customSlimmedMuons
process.p *= process.customSlimmedTausTauEsNominal
process.p *= process.customSlimmedTausTauEsUp
process.p *= process.customSlimmedTausTauEsDown
process.p *= process.filteredCustomElectrons
process.p *= process.filteredCustomElectronsEsUp
process.p *= process.filteredCustomElectronsEsDown
process.p *= process.filteredCustomMuons
process.p *= process.filteredCustomTausEsNominal
process.p *= process.filteredCustomTausEsUp
process.p *= process.filteredCustomTausEsDown

process.p *= process.TrimmedFilteredCustomElectrons
process.p *= process.TrimmedFilteredCustomElectronsEsUp
process.p *= process.TrimmedFilteredCustomElectronsEsDown

process.p *= process.TrimmedFilteredCustomMuons 
process.p *= process.TrimmedFilteredCustomTausEsNominal 
process.p *= process.TrimmedFilteredCustomTausEsUp 
process.p *= process.TrimmedFilteredCustomTausEsDown 



process.p *= process.filteredVetoElectrons
process.p *= process.filteredVetoElectronsEsUp
process.p *= process.filteredVetoElectronsEsDown

process.p *= process.filteredVetoMuons


if BUILD_EFFICIENCY_TREE is False:
	process.p *= process.requireCandidateHiggsPair

if BUILD_TAU_ES_VARIANTS is True :
	process.MVAMETtauEsUp
	process.MVAMETtauEsDown

if BUILD_ELECTRON_ES_VARIANTS is True :
	process.MVAMETelectronEsUp
	process.MVAMETelectronEsDown


process.p *= process.TupleCandidateEvents
process.p *= process.NtupleEvents


if BUILD_TAU_ES_VARIANTS is True :
	process.p *= process.TupleCandidateEventsTauEsUp
	process.p *= process.TupleCandidateEventsTauEsDown
	process.p *= process.NtupleEventsTauEsUp
	process.p *= process.NtupleEventsTauEsDown


if BUILD_ELECTRON_ES_VARIANTS is True :
	process.p *= process.TupleCandidateEventsElectronEsDown
	process.p *= process.TupleCandidateEventsElectronEsUp
	process.p *= process.NtupleEventsElectronEsUp
	process.p *= process.NtupleEventsElectronEsDown

process.p *= process.pairIndep
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
process.e = cms.EndPath()




