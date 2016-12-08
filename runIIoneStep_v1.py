#################################################################
# preliminaries -- user edits 
#################################################################
#		 MAX_EVENTS    -- stop execution after MAX_EVENTS events, -1 to run all
#		 dataSetName_  -- full DBS name of dataSet	
#        myfilelist    -- the input list of miniAOD or Ntuple files
#		 DEBUG_NTUPLE  -- produce both ntuple & flatTuple if True
# 		 DEBUG_NTUPLE_INPUT -- input NtupleFile, output FlatTuple
#########################################################


######################################
# if DEBUG_NTUPLE is set to True
# will write both FlatTuple and Ntuple to disk
######################################

DEBUG_NTUPLE = False

######################################
# if DEBUG_NTUPLE_INPUT is set to True
# code will run on a (davis) Ntuple (not mini-AOD)
# and output a FlatTuple
######################################

DEBUG_NTUPLE_INPUT = False

######################################
# how many events to run, -1 means run all 
######################################

MAX_EVENTS = 5000

######################################
# datasets for local running 
######################################

dataSetName_ = "/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"
#dataSetName_ = "/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"

#dataSetName_= "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_ = "/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"
#dataSetName_ = "/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_ = "/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext4-v1/MINIAODSIM"
#dataSetName_="/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/SingleElectron/Run2015D-16Dec2015-v1/MINIAOD"
#dataSetName_="/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD"


######################################
#  list of files to process 
######################################

myfilelist = cms.untracked.vstring()

if dataSetName_ == "/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM":
	#myfilelist.extend(['file:/uscms_data/d3/shalhout/MonoH_2500_800_reHLT.root'])
	myfilelist.extend(['file:/uscms_data/d3/shalhout/SUSY_GG160_reHLT.root'])

if dataSetName_ == "/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/nonREHLT_file.root']) # smH 125 file for testing non-REHLT running

if dataSetName_ == "/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
#	myfilelist.extend(['file:/uscms_data/d3/shalhout/pickeventsMissing26.root'])
#	myfilelist.extend(['file:/uscms_data/d3/shalhout/pickevents_missingMuTau14.root'])
	myfilelist.extend(['file:/uscms/home/shalhout/EOS/mini_AOD/Fall15/miniAODv2_SyncSample.root'])
if dataSetName_=="/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/miniAODv2_DYlowMass.root'])	
if dataSetName_=="/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext4-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/miniAODv2_TTbar.root'])
if dataSetName_ == "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms/home/shalhout/EOS/mini_AOD/Fall15/miniAODv2_DYnlo.root'])
if dataSetName_ == "/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/miniAODv2_ZZ4l.root'])
if dataSetName_ == "/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/monoHiggsRunIIFall15MiniAODv2_2HDMzpToA0h_1200_400.root'])
if dataSetName_ == "/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/WJetsToLNu_HT-100To200.root'])
if dataSetName_ == "/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/miniAODv2_WJetsToLNu.root'])
if dataSetName_=="/SingleElectron/Run2015D-16Dec2015-v1/MINIAOD":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/Fall15_DATA_SingleElectron.root'])
if dataSetName_=="/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/Fall15_DATA_SingleMuon.root'])

if DEBUG_NTUPLE_INPUT is True:
	myfilelist = cms.untracked.vstring(['file:./NtupleFile.root'])

if MAX_EVENTS != -1:
	print '*****************************************************************'
	print '*****************************************************************'
	print '****** WARNING asking to stop run after only ', MAX_EVENTS, 'events  '
	print '****** If this is a crab job, things will NOT go well :(  '
	print '*****************************************************************'
	print '*****************************************************************'


########################################
# begin cmsRun job config
########################################

DAVISprocessName = "DavisNtuple"

if DEBUG_NTUPLE_INPUT is True:
	DAVISprocessName = "DavisNtupleDebug"



import FWCore.ParameterSet.Config as cms
process = cms.Process(DAVISprocessName) 


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


####################
# fix the HLT label 
# in reHLT samples it is HLT2
####################

HLTlabelType = 'HLT'

if sampleData.HLTversion == 'HLT2' :
	HLTlabelType = 'HLT2'


print 'Since in 2016 we mix reHLT and HLT samples, Determined HLT version (HLT2 or HLT) as ', HLTlabelType




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
if BUILD_ELECTRON_TAUBOOSTED : print 'e-tauBoosted',
if BUILD_MUON_TAUBOOSTED : print 'mu-tauBoosted',
if BUILD_TAUBOOSTED_TAUBOOSTED : print 'tauBoosted-tauBoosted',

if BUILD_TAU_ES_VARIANTS : print ' + tau Es Variants',
if BUILD_ELECTRON_ES_VARIANTS : print ' + electron Es Variants for eleMu channel (only!) '
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
process.MessageLogger.cerr.FwkReport.reportEvery = 500

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag

if sampleData.EventType == 'MC':
	process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_miniAODv2_v1', '')
	#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

if sampleData.EventType == 'DATA':
	process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Prompt_ICHEP16JEC_v0', '')
	#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

print '********** HAVE MANUALLY SET GLOBAL TAG SET TO  *********************'
print '**********', process.GlobalTag.globaltag
print '*******************************************************'

print '********** Running in unscheduled mode **********'
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.options.allowUnscheduled = cms.untracked.bool(True)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(MAX_EVENTS) ) 

###################################
# input - remove for crab running
###################################

# process.source = cms.Source("PoolSource",fileNames=myfilelist,
# 			eventsToProcess = cms.untracked.VEventRange('1:40203-1:40203','1:42012-1:42012','1:41436-1:41436'))	



process.source = cms.Source("PoolSource",fileNames=myfilelist)

# process.source = cms.Source("PoolSource",fileNames=myfilelist,
# 			eventsToProcess = cms.untracked.VEventRange('1:4465-1:4465','1:4442-1:4442','1:53532-1:53532',
#                         '1:84528-1:84528','1:92356-1:92356','1:109720-1:109720'))	


# process.source = cms.Source("PoolSource",fileNames=myfilelist,
# 			eventsToProcess = cms.untracked.VEventRange('1:4454-1:4454','1:4442-1:4442'))	



# process.source = cms.Source("PoolSource",fileNames=myfilelist,
# 			eventsToProcess = cms.untracked.VEventRange('1:4487-1:4487','1:4492-1:4492','1:4600-1:4600','1:4632-1:4632',
# 				'1:4721-1:4721','1:4789-1:4789','1:4804-1:4804','1:4814-1:4814','1:4830-1:4830',
# 				'1:4861-1:4861','1:4901-1:4901','1:4922-1:4922','1:53411-1:53411','1:53693-1:53693',
# 				'1:53712-1:53712','1:57146-1:57146','1:57157-1:57157','1:57182-1:57182','1:57231-1:57231',
# 				'1:57295-1:57295','1:57358-1:57358','1:57441-1:57441','1:73415-1:73415','1:73420-1:73420'))	

# process.source = cms.Source("PoolSource",fileNames=myfilelist,
# 			eventsToProcess = cms.untracked.VEventRange(
# '1:90327-1:90327','1:90328-1:90328','1:90335-1:90335','1:90336-1:90336','1:90347-1:90347',
# '1:90348-1:90348','1:90363-1:90363','1:90366-1:90366','1:90366-1:90366','1:90366-1:90366',
# '1:90367-1:90367','1:90385-1:90385'))



#eventsToProcess = cms.untracked.VEventRange('1:67566889-1:67566889','1:73662929-1:73662929','1:71967435-1:71967435',
#'1:32900395-1:32900395') )

#eventsToSkip = cms.untracked.VEventRange('1:1-1:4941')	)



###################################
# Cumulative Info
#     - keep info about every event seen
#     - before any selections are applied
###################################

from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import mcGenWeightSrcInputTag
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import LHEEventProductSrcInputTag

process.Cumulative = cms.EDAnalyzer('CumulativeInfoAdder',
	mcGenWeightSrc = mcGenWeightSrcInputTag,
	LHEEventProductSrc = LHEEventProductSrcInputTag
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

############################################
# TESTING A VERY SIMPLE VERY EARLY FILTER
############################################

process.SimpleFilter = cms.EDFilter("SimpleFilter",
  	electronSources = cms.VInputTag("slimmedElectrons"), 
	muonSources     = cms.VInputTag("slimmedMuons"),
	tauSources      = cms.VInputTag("slimmedTaus"),
	BOOSTEDtauSources      = cms.VInputTag("slimmedTausBoosted"),
	vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
    filter = cms.bool(True)
	)


###################################
# re-apply Jet Energy Corrections
# will use tools already available in MVA MET
####################################

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")


from RecoMET.METPUSubtraction.jet_recorrections import recorrectJets

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
	#src = cms.InputTag('slimmedJets'),
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
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							rhoSources = rhoSourceList
							                 )




# produces all 3 tau variants  -- BOOSTED



process.customSlimmedTausBoostedTauEsNominal = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTausBoosted'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string("BOOSTED"),
							#TauEsCorrection=cms.double(0.99),
							TauEsCorrection=cms.double(1.0),
							TauEsSystematicShift=cms.double(1.0),
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							rhoSources = rhoSourceList
							                 )


process.customSlimmedTausBoostedTauEsUp = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTausBoosted'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string("BOOSTED"),
							#TauEsCorrection=cms.double(0.99),
							TauEsCorrection=cms.double(1.0),
							TauEsSystematicShift=cms.double(1.03),
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
							triggerPreScaleSrc = cms.InputTag("patTrigger"),
							triggerObjectSrc = cms.InputTag("selectedPatTrigger"),
							rhoSources = rhoSourceList
							                 )



process.customSlimmedTausBoostedTauEsDown = cms.EDProducer('CustomPatTauProducer' ,
							tauSrc =cms.InputTag('slimmedTausBoosted'),
							vertexSrc =cms.InputTag('filteredVertices::DavisNtuple'),
							NAME=cms.string("BOOSTED"),
							#TauEsCorrection=cms.double(0.99),
							TauEsCorrection=cms.double(1.0),
							TauEsSystematicShift=cms.double(0.97),
							triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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





process.filteredCustomTausBoostedEsNominal = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTausBoostedTauEsNominal:BOOSTED:DavisNtuple'),
	cut = tauFilter
	)


process.filteredCustomTausBoostedEsUp = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTausBoostedTauEsUp:BOOSTED:DavisNtuple'),
	cut = tauFilter
	)

process.filteredCustomTausBoostedEsDown = cms.EDFilter("PATTauRefSelector",
	src = cms.InputTag('customSlimmedTausBoostedTauEsDown:BOOSTED:DavisNtuple'),
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




process.TrimmedFilteredCustomTausBoostedEsNominal = cms.EDProducer('TrimmedPatTauProducer' ,
   					 tauSrc = cms.InputTag("filteredCustomTausBoostedEsNominal::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_TAU_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomTausBoostedEsNominal"))


process.TrimmedFilteredCustomTausBoostedEsUp = cms.EDProducer('TrimmedPatTauProducer' ,
   					 tauSrc = cms.InputTag("filteredCustomTausBoostedEsUp::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_TAU_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomTausBoostedEsUp"))


process.TrimmedFilteredCustomTausBoostedEsDown = cms.EDProducer('TrimmedPatTauProducer' ,
   					 tauSrc = cms.InputTag("filteredCustomTausBoostedEsDown::DavisNtuple"),
				     MAX_TO_KEEP = cms.uint32(MAX_TAU_COUNT),
				     NAME=cms.string("TrimmedFilteredCustomTausBoostedEsDown"))






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
# BUILD_EFFICIENCY_TREE is False
# make sure to give the VInputTag
# all variants of e, mu, and tau
# final collections 
###################################

from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import post_sync_EleTau_tauMVACuts_  as tauMVAfilter_EleTau_
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import post_sync_MuonTau_tauMVACuts_ as tauMVAfilter_MuonTau_
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import post_sync_TauTau_tauMVACuts_  as tauMVAfilter_TauTau_
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import post_sync_tauIso_ as tauIsofilter_
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import triggerSummaryChecks_ as hlt_Filter_

process.requireCandidateHiggsPair = cms.EDFilter("HiggsCandidateCountFilter",
  	electronSources = cms.VInputTag("TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple",
  									"TrimmedFilteredCustomElectronsEsUp:TrimmedFilteredCustomElectronsEsUp:DavisNtuple",
  									"TrimmedFilteredCustomElectronsEsDown:TrimmedFilteredCustomElectronsEsDown:DavisNtuple"), 
	muonSources     = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),

	tauSources      = cms.VInputTag("TrimmedFilteredCustomTausEsNominal:TrimmedFilteredCustomTausEsNominal:DavisNtuple",
									"TrimmedFilteredCustomTausEsUp:TrimmedFilteredCustomTausEsUp:DavisNtuple",
									"TrimmedFilteredCustomTausEsDown:TrimmedFilteredCustomTausEsDown:DavisNtuple",
									"TrimmedFilteredCustomTausBoostedEsNominal:TrimmedFilteredCustomTausBoostedEsNominal:DavisNtuple",
									"TrimmedFilteredCustomTausBoostedEsUp:TrimmedFilteredCustomTausBoostedEsUp:DavisNtuple",
									"TrimmedFilteredCustomTausBoostedEsDown:TrimmedFilteredCustomTausBoostedEsDown:DavisNtuple"), 
	countElectronElectrons = cms.bool(BUILD_ELECTRON_ELECTRON),
	countElectronMuons  = cms.bool(BUILD_ELECTRON_MUON),
	countElectronTaus = cms.bool(BUILD_ELECTRON_TAU),
	countMuonMuons = cms.bool(BUILD_MUON_MUON),
	countMuonTaus = cms.bool(BUILD_MUON_TAU),
	countTauTaus = cms.bool(BUILD_TAU_TAU),
	tauMVAfilter_EleTau = tauMVAfilter_EleTau_,
	tauMVAfilter_MuonTau = tauMVAfilter_MuonTau_,
	tauMVAfilter_TauTau = tauMVAfilter_TauTau_,
	tauIsofilter = tauIsofilter_,
	hlt_Filter = hlt_Filter_,
    filter = cms.bool(True)
	)

#########################################
# RUN PF MET CORR AND ERRORS
##########################################


from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

if sampleData.EventType == 'MC':
	runMetCorAndUncFromMiniAOD(process, isData=False  )

if sampleData.EventType == 'DATA':
	runMetCorAndUncFromMiniAOD(process, isData=True )

# need to make sure our Ntuple producer uses this new MET while the MVA MET uses
# the original slimmedMETs collection

METforNtuple = DAVISprocessName




#########################################
# new MVA MET (pairwise) interface
# along with setup for tau ES var
##########################################

##################################
# init mva met 
##################################

from RecoMET.METPUSubtraction.MVAMETConfiguration_cff import runMVAMET
runMVAMET( process, jetCollectionPF = "patJetsReapplyJEC")
#runMVAMET( process, jetCollectionPF = "slimmedJets")


# there is a bug in MVA MET for 8X that requires user to manually set the srcMETs

BUGFIX_MET_TYPE = "PAT"

if sampleData.EventType == 'DATA':
	BUGFIX_MET_TYPE = "RECO"

process.MVAMET.srcMETs = cms.VInputTag( cms.InputTag("slimmedMETs", "", BUGFIX_MET_TYPE),
                                            cms.InputTag("patpfMET"),
                                            cms.InputTag("patpfMETT1"),
                                            cms.InputTag("patpfTrackMET"),
                                            cms.InputTag("patpfNoPUMET"),
                                            cms.InputTag("patpfPUCorrectedMET"),
                                            cms.InputTag("patpfPUMET"),
                                            cms.InputTag("slimmedMETsPuppi", "", BUGFIX_MET_TYPE) )




#################################
# modify the default mva met    #
#################################

process.MVAMET.srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
										   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
										   "TrimmedFilteredCustomTausEsNominal:TrimmedFilteredCustomTausEsNominal:DavisNtuple")
process.MVAMET.requireOS = cms.bool(False)


##################################################################
# clone the default (with mods) and adjust for tau ES up
##################################################################

process.MVAMETtauEsUp = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
											   "TrimmedFilteredCustomTausEsUp:TrimmedFilteredCustomTausEsUp:DavisNtuple"),
												requireOS = cms.bool(False),
												srcMETs = cms.VInputTag( cms.InputTag("slimmedMETs", "", BUGFIX_MET_TYPE),
	                                            cms.InputTag("patpfMET"),
	                                            cms.InputTag("patpfMETT1"),
	                                            cms.InputTag("patpfTrackMET"),
	                                            cms.InputTag("patpfNoPUMET"),
	                                            cms.InputTag("patpfPUCorrectedMET"),
	                                            cms.InputTag("patpfPUMET"),
	                                            cms.InputTag("slimmedMETsPuppi", "", BUGFIX_MET_TYPE) ) )


##################################################################
# clone the default (with mods) and adjust for tau ES down
##################################################################

process.MVAMETtauEsDown = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
											   "TrimmedFilteredCustomTausEsDown:TrimmedFilteredCustomTausEsDown:DavisNtuple"),
												requireOS = cms.bool(False),
												srcMETs = cms.VInputTag( cms.InputTag("slimmedMETs", "", BUGFIX_MET_TYPE),
	                                            cms.InputTag("patpfMET"),
	                                            cms.InputTag("patpfMETT1"),
	                                            cms.InputTag("patpfTrackMET"),
	                                            cms.InputTag("patpfNoPUMET"),
	                                            cms.InputTag("patpfPUCorrectedMET"),
	                                            cms.InputTag("patpfPUMET"),
	                                            cms.InputTag("slimmedMETsPuppi", "", BUGFIX_MET_TYPE) ) ) 


##################################################################
# clone the default (with mods) and adjust for tau BOOSTED ES nominal
##################################################################

process.MVAMETtauBoostedEsNominal = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
											   "TrimmedFilteredCustomTausBoostedEsNominal:TrimmedFilteredCustomTausBoostedEsNominal:DavisNtuple"),
												requireOS = cms.bool(False),
												srcMETs = cms.VInputTag( cms.InputTag("slimmedMETs", "", BUGFIX_MET_TYPE),
	                                            cms.InputTag("patpfMET"),
	                                            cms.InputTag("patpfMETT1"),
	                                            cms.InputTag("patpfTrackMET"),
	                                            cms.InputTag("patpfNoPUMET"),
	                                            cms.InputTag("patpfPUCorrectedMET"),
	                                            cms.InputTag("patpfPUMET"),
	                                            cms.InputTag("slimmedMETsPuppi", "", BUGFIX_MET_TYPE) ) )



##################################################################
# clone the default (with mods) and adjust for BOOSTED tau ES up
##################################################################

process.MVAMETtauBoostedEsUp = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
											   "TrimmedFilteredCustomTausBoostedEsUp:TrimmedFilteredCustomTausBoostedEsUp:DavisNtuple"),
												requireOS = cms.bool(False),
												srcMETs = cms.VInputTag( cms.InputTag("slimmedMETs", "", BUGFIX_MET_TYPE),
	                                            cms.InputTag("patpfMET"),
	                                            cms.InputTag("patpfMETT1"),
	                                            cms.InputTag("patpfTrackMET"),
	                                            cms.InputTag("patpfNoPUMET"),
	                                            cms.InputTag("patpfPUCorrectedMET"),
	                                            cms.InputTag("patpfPUMET"),
	                                            cms.InputTag("slimmedMETsPuppi", "", BUGFIX_MET_TYPE) ) )




##################################################################
# clone the default (with mods) and adjust for BOOSTED tau ES down
##################################################################

process.MVAMETtauBoostedEsDown = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
											   "TrimmedFilteredCustomTausBoostedEsDown:TrimmedFilteredCustomTausBoostedEsDown:DavisNtuple"),
												requireOS = cms.bool(False),
												srcMETs = cms.VInputTag( cms.InputTag("slimmedMETs", "", BUGFIX_MET_TYPE),
	                                            cms.InputTag("patpfMET"),
	                                            cms.InputTag("patpfMETT1"),
	                                            cms.InputTag("patpfTrackMET"),
	                                            cms.InputTag("patpfNoPUMET"),
	                                            cms.InputTag("patpfPUCorrectedMET"),
	                                            cms.InputTag("patpfPUMET"),
	                                            cms.InputTag("slimmedMETsPuppi", "", BUGFIX_MET_TYPE) ) ) 




##################################################################
# clone the default (with mods) and adjust for electron ES up
# since the electron ES systematic applies only for e+mu
# evaluate only e + mu pairs (that is why srcLeptons does not use taus)
##################################################################

process.MVAMETelectronEsUp = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectronsEsUp:TrimmedFilteredCustomElectronsEsUp:DavisNtuple"),
												requireOS = cms.bool(False),
												srcMETs = cms.VInputTag( cms.InputTag("slimmedMETs", "", BUGFIX_MET_TYPE),
	                                            cms.InputTag("patpfMET"),
	                                            cms.InputTag("patpfMETT1"),
	                                            cms.InputTag("patpfTrackMET"),
	                                            cms.InputTag("patpfNoPUMET"),
	                                            cms.InputTag("patpfPUCorrectedMET"),
	                                            cms.InputTag("patpfPUMET"),
	                                            cms.InputTag("slimmedMETsPuppi", "", BUGFIX_MET_TYPE) ) )



process.MVAMETelectronEsDown = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectronsEsDown:TrimmedFilteredCustomElectronsEsDown:DavisNtuple"),
												requireOS = cms.bool(False),
												srcMETs = cms.VInputTag( cms.InputTag("slimmedMETs", "", BUGFIX_MET_TYPE),
	                                            cms.InputTag("patpfMET"),
	                                            cms.InputTag("patpfMETT1"),
	                                            cms.InputTag("patpfTrackMET"),
	                                            cms.InputTag("patpfNoPUMET"),
	                                            cms.InputTag("patpfPUCorrectedMET"),
	                                            cms.InputTag("patpfPUMET"),
	                                            cms.InputTag("slimmedMETsPuppi", "", BUGFIX_MET_TYPE) ) )





###########



##################
# memory check 

if RUN_MEM_CHECK is True:
	#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1) )
	process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",ignoreTotal = cms.untracked.int32(1), showMallocInfo=cms.untracked.bool(True),
	monitorPssAndPrivate=cms.untracked.bool(True), moduleMemorySummary=cms.untracked.bool(True) )


# 

####################
# produce the TupleCandidateEvent pair + MET container

from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import generalConfig as TauIsoConfigRank
tauIsolForOrderingPair_ = TauIsoConfigRank.getParameter("tauIDisolationForRank")
smallerTauIsoValueIsBetter_ = TauIsoConfigRank.getParameter("tau_isSmallerValueMoreIsolated")


##############################################
# Decide how we will handle pair ranking     #
##############################################

rankParisByPt_ = TauIsoConfigRank.rankByPtSum

if rankParisByPt_ == True :
	print "******************************************************"
	print "***** WILL RANK PAIRS BY Pt "
	print "***** if not desired change variables rankByPtSum and rankByIsolation in FlatTupleConfig_cfi.py "
	print "******************************************************"

else :
	print "******************************************************"
	print "***** pairs will be ordered by ISOLATION "
	print "***** if not desired change variables rankByPtSum and rankByIsolation in FlatTupleConfig_cfi.py "
	print "***** Tau_h + Tau_h pairs will be ordered by", tauIsolForOrderingPair_
	if smallerTauIsoValueIsBetter_ is True:
		print "***** smaller value of tau iso is better isolated"
	else:
		print "***** larger value of tau iso is better isolated"
	print "******************************************************"



process.TupleCandidateEvents = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("slimmedMETs","",DAVISprocessName), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMET:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectrons","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.001),
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
    BuildEfficiencyTree = cms.bool(BUILD_EFFICIENCY_TREE),
    rankParisByPt = rankParisByPt_
						)	


process.TupleCandidateEventsTauEsUp = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("slimmedMETs","",DAVISprocessName), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETtauEsUp:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectrons","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.001), 
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
    BuildEfficiencyTree = cms.bool(False),
    rankParisByPt = rankParisByPt_
						)	

process.TupleCandidateEventsTauEsDown = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("slimmedMETs","",DAVISprocessName), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETtauEsDown:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectrons","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.001), 
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
    BuildEfficiencyTree = cms.bool(False),
    rankParisByPt = rankParisByPt_
						)	

process.TupleCandidateEventsBoosted = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("slimmedMETs","",DAVISprocessName), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETtauBoostedEsNominal:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectrons","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.001),
	NAME=cms.string("TupleCandidateEventsBoosted"),
    doSVMass = cms.bool(COMPUTE_SVMASS_AT_NTUPLE),
    useMVAMET = cms.bool(USE_MVAMET),
    logMterm = cms.double(SVMASS_LOG_M),
    svMassVerbose = cms.int32(SVMASS_VERBOSE),
    # need to order the taus by isolation in tau_h + tau_h pairs
    tauIsolForOrderingPair = tauIsolForOrderingPair_,
    smallerTauIsoValueIsBetter = smallerTauIsoValueIsBetter_,
    EffElectronSrc = cms.InputTag("TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple"),
    EffMuonSrc = cms.InputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),
    EffTauSrc = cms.InputTag("TrimmedFilteredCustomTausBoostedEsNominal:TrimmedFilteredCustomTausBoostedEsNominal:DavisNtuple"),
    BuildEfficiencyTree = cms.bool(BUILD_EFFICIENCY_TREE),
    rankParisByPt = rankParisByPt_
						)	


process.TupleCandidateEventsTauEsUpBoosted = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("slimmedMETs","",DAVISprocessName), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETtauBoostedEsUp:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectrons","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.001), 
	NAME=cms.string("TupleCandidateEventsTauEsUpBoosted"),
    doSVMass = cms.bool(COMPUTE_SVMASS_AT_NTUPLE),
    useMVAMET = cms.bool(USE_MVAMET),
    logMterm = cms.double(SVMASS_LOG_M),
    svMassVerbose = cms.int32(SVMASS_VERBOSE),
    # need to order the taus by isolation in tau_h + tau_h pairs
    tauIsolForOrderingPair = tauIsolForOrderingPair_,
    smallerTauIsoValueIsBetter = smallerTauIsoValueIsBetter_,
    EffElectronSrc = cms.InputTag("TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple"),
    EffMuonSrc = cms.InputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),
    EffTauSrc = cms.InputTag("TrimmedFilteredCustomTausBoostedEsUp:TrimmedFilteredCustomTausBoostedEsUp:DavisNtuple"),
    BuildEfficiencyTree = cms.bool(False),
    rankParisByPt = rankParisByPt_
						)	

process.TupleCandidateEventsTauEsDownBoosted = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("slimmedMETs","",DAVISprocessName), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETtauBoostedEsDown:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectrons","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.001), 
	NAME=cms.string("TupleCandidateEventsTauEsDownBoosted"),
    doSVMass = cms.bool(COMPUTE_SVMASS_AT_NTUPLE),
    useMVAMET = cms.bool(USE_MVAMET),
    logMterm = cms.double(SVMASS_LOG_M),
    svMassVerbose = cms.int32(SVMASS_VERBOSE),
    # need to order the taus by isolation in tau_h + tau_h pairs
    tauIsolForOrderingPair = tauIsolForOrderingPair_,
    smallerTauIsoValueIsBetter = smallerTauIsoValueIsBetter_,
    EffElectronSrc = cms.InputTag("TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple"),
    EffMuonSrc = cms.InputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),
    EffTauSrc = cms.InputTag("TrimmedFilteredCustomTausBoostedEsDown:TrimmedFilteredCustomTausBoostedEsDown:DavisNtuple"),
    BuildEfficiencyTree = cms.bool(False),
    rankParisByPt = rankParisByPt_
						)	

process.TupleCandidateEventsElectronEsUp = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("slimmedMETs","",DAVISprocessName), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETelectronEsUp:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectronsEsUp","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.001), 
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
    BuildEfficiencyTree = cms.bool(False),
    rankParisByPt = rankParisByPt_
						)	



process.TupleCandidateEventsElectronEsDown = cms.EDProducer('TupleCandidateEventProducer' ,
	puppiMETSrc = cms.InputTag("slimmedMETsPuppi"),
	pfMETSrc = cms.InputTag("slimmedMETs","",DAVISprocessName), # this has the updated JECs
	mvaMETSrc = cms.InputTag("MVAMETelectronEsDown:MVAMET:DavisNtuple"),
	electronVetoSrc =cms.InputTag("filteredVetoElectronsEsDown","","DavisNtuple"),
	muonVetoSrc = cms.InputTag("filteredVetoMuons","","DavisNtuple"),				
	pairDeltaRmin = cms.double(0.001), 
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
    BuildEfficiencyTree = cms.bool(False),
    rankParisByPt = rankParisByPt_
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
				 triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
				 triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
				 triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
				 triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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
				 triggerBitSrc = cms.InputTag("TriggerResults","",HLTlabelType),
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




################################
# 2016 BAD MUON FILTERS 
# we don't want cuts on these applied here 
# but in the final analysis, so we invoke them in 
# tagging as opposed to filter mode and we record the
# pass/fail result instead of rejecting the failed events
################################

process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadPFMuonFilter.taggingMode   = cms.bool(True)

process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadChargedCandidateFilter.taggingMode   = cms.bool(True)




#################################
# pair independent content

from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import PUjetIDworkingPoint
from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import PFjetIDworkingPoint
from DavisRunIITauTau.TupleConfigurations.ConfigJets_cfi import TightPFjetIDworkingPoint
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import PUntupleWeightSettings
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleWeights_cfi import pileupSrcInputTag
from DavisRunIITauTau.TupleConfigurations.SampleMetaData_cfi import sampleInfo


print '****************************************************************************************************'
print '****  JERresolutionFile is ', "DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/Spring16_25nsV6_MC_PtResolution_AK4PFchs.txt"
print '****  JERscalefactorFile is ', "DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/Spring16_25nsV6_MC_SF_AK4PFchs.txt"
print '****   If not current, change in main python config : runII*.py'
print '****************************************************************************************************'

process.pairIndep = cms.EDProducer('NtuplePairIndependentInfoProducer',
							packedGenSrc = cms.InputTag('packedGenParticles'),
							prundedGenSrc =  cms.InputTag('prunedGenParticles'),
							NAME=cms.string("NtupleEventPairIndep"),
							JERresolutionFile = cms.string("DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/Spring16_25nsV6_MC_PtResolution_AK4PFchs.txt"),
							JERscalefactorFile = cms.string("DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/Spring16_25nsV6_MC_SF_AK4PFchs.txt"),
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
							BadChargedCandidateFilterSrc = cms.InputTag("BadChargedCandidateFilter","","DavisNtuple"),
							BadPFMuonFilterSrc = cms.InputTag("BadPFMuonFilter","","DavisNtuple"),
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

# need to change this if running from Ntuple input 
FlatTupleProductionName = DAVISprocessName

if DEBUG_NTUPLE_INPUT is True:
	FlatTupleProductionName = "DavisNtuple"



process.BASELINE = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvents','NtupleEvents',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("BASELINE"),
	FillEffLeptonBranches = cms.bool(BUILD_EFFICIENCY_TREE), # everywhere else it should be always False
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)


process.BASELINEupTau = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsTauEsUp','NtupleEventsTauEsUp',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("BASELINEupTau"),
	FillEffLeptonBranches = cms.bool(False), 
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("UP"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.BASELINEdownTau = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsTauEsDown','NtupleEventsTauEsDown',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("BASELINEdownTau"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("DOWN"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.BASELINEupElectron = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsElectronEsUp','NtupleEventsElectronEsUp',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("BASELINEupElectron"),
	FillEffLeptonBranches = cms.bool(False), 
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("UP"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.BASELINEdownElectron = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsElectronEsDown','NtupleEventsElectronEsDown',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("BASELINEdownElectron"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("DOWN"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = defaultCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)




process.LOWDELTAR = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEvents','NtupleEvents',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("LOWDELTAR"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)


process.LOWDELTARupTau = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsTauEsUp','NtupleEventsTauEsUp',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("LOWDELTARupTau"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("UP"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.LOWDELTARdownTau = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsTauEsDown','NtupleEventsTauEsDown',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("LOWDELTARdownTau"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("DOWN"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)



process.LOWDELTARupElectron = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsElectronEsUp','NtupleEventsElectronEsUp',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("LOWDELTARupElectron"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("UP"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)

process.LOWDELTARdownElectron = cms.EDAnalyzer('FlatTupleGenerator',
	pairSrc = cms.InputTag('NtupleEventsElectronEsDown','NtupleEventsElectronEsDown',FlatTupleProductionName),
	indepSrc = cms.InputTag('pairIndep','NtupleEventPairIndep',FlatTupleProductionName),
	NAME = cms.string("LOWDELTARdownElectron"),
	FillEffLeptonBranches = cms.bool(False),	
	RecoilCorrection = sampleData.RecoilCorrection,
	MetSystematicType = sampleData.MetSystematicType,
	KeepTheoryScaleFactors = sampleData.KeepTheoryScaleFactors,
	EventCutSrc = generalConfig,
	TauEsVariantToKeep = cms.string("NOMINAL"), # only NOMINAL, UP or DOWN are valid
	ElectronEsVariantToKeep = cms.string("DOWN"), # only NOMINAL, UP or DOWN are valid
	LeptonCutVecSrc = lowDeltaRCuts,
	SVMassConfig = svMassAtFlatTupleConfig
	)


process.p = cms.Path()



if DEBUG_NTUPLE == DEBUG_NTUPLE_INPUT and DEBUG_NTUPLE_INPUT is True:
	print '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
	print '++++ FAIL both debug modes active, doing nothing .... '
	print '++++ change DEBUG_NTUPLE and/or DEBUG_NTUPLE_INPUT  .... '
	print '++++ in runIIoneStep_*.py .... '
	quit()

else :

	if DEBUG_NTUPLE_INPUT is True :
		print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
		print "+++++ DEBUG NTUPLE_INPUT ***** will run using Ntuple as input (not mini-AOD) "
		print "+++++ DEBUG NTUPLE_INPUT ***** and produce FlatTuple          "
		print "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"



	if DEBUG_NTUPLE_INPUT is False :
		process.p *= process.Cumulative
		process.p *= process.filteredVertices
		
		if BUILD_EFFICIENCY_TREE is False:
			process.p *= process.SimpleFilter

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

		process.p *= process.customSlimmedTausBoostedTauEsNominal
		process.p *= process.customSlimmedTausBoostedTauEsUp
		process.p *= process.customSlimmedTausBoostedTauEsDown

		process.p *= process.filteredCustomElectrons
		process.p *= process.filteredCustomElectronsEsUp
		process.p *= process.filteredCustomElectronsEsDown
		process.p *= process.filteredCustomMuons
		process.p *= process.filteredCustomTausEsNominal
		process.p *= process.filteredCustomTausEsUp
		process.p *= process.filteredCustomTausEsDown


		process.p *= process.filteredCustomTausBoostedEsNominal
		process.p *= process.filteredCustomTausBoostedEsUp
		process.p *= process.filteredCustomTausBoostedEsDown


		process.p *= process.TrimmedFilteredCustomElectrons
		process.p *= process.TrimmedFilteredCustomElectronsEsUp
		process.p *= process.TrimmedFilteredCustomElectronsEsDown

		process.p *= process.TrimmedFilteredCustomMuons 
		process.p *= process.TrimmedFilteredCustomTausEsNominal 
		process.p *= process.TrimmedFilteredCustomTausEsUp 
		process.p *= process.TrimmedFilteredCustomTausEsDown 

		process.p *= process.TrimmedFilteredCustomTausBoostedEsNominal 
		process.p *= process.TrimmedFilteredCustomTausBoostedEsUp 
		process.p *= process.TrimmedFilteredCustomTausBoostedEsDown 

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



		if (BUILD_ELECTRON_TAUBOOSTED or BUILD_MUON_TAUBOOSTED or BUILD_TAUBOOSTED_TAUBOOSTED) : 
			process.MVAMETtauBoostedEsNominal
			process.p *= process.TupleCandidateEventsBoosted


			if BUILD_TAU_ES_VARIANTS is True :
				process.MVAMETtauBoostedEsUp
				process.MVAMETtauBoostedEsDown
				process.p *= process.TupleCandidateEventsTauEsUpBoosted
				process.p *= process.TupleCandidateEventsTauEsDownBoosted
	

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


		# new MET Filters for 2016	
		process.p *= process.BadPFMuonFilter 
		process.p *= process.BadChargedCandidateFilter 

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

	###################################
	# output config - should not be in crab
	# script 
	###################################


	if DEBUG_NTUPLE is True :
		print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
		print "+++++ DEBUG NTUPLE ***** will create Ntuple for Debugging "
		print "+++++ DEBUG NTUPLE ***** with edmProvDump & edmDumpEventContent "
		print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

		process.out = cms.OutputModule("PoolOutputModule",
					fileName = cms.untracked.string('NtupleFile.root'),
					SelectEvents = cms.untracked.PSet(
					                SelectEvents = cms.vstring('p')
					                )					
		)

		from Configuration.EventContent.EventContent_cff import MINIAODSIMEventContent
		process.out.outputCommands = MINIAODSIMEventContent.outputCommands
		# will cause crash --> process.out.outputCommands.append("keep *")
		# if only want things needed for FlatTuple uncomment the next line
		#process.out.outputCommands.append("keep *")
		#process.out.outputCommands.append("keep TupleCandidateEvents*_*_*_DavisNtuple")
		process.out.outputCommands.append("keep NtupleEvents*_*_*_DavisNtuple")
		process.out.outputCommands.append("keep pairIndep*_*_*_DavisNtuple")
		process.out.outputCommands.append("keep NtuplePairIndependentInfos*_*_*_DavisNtuple")



	process.TFileService = cms.Service("TFileService", fileName = cms.string("FlatTuple.root"))

	if DEBUG_NTUPLE is True :
		process.e = cms.EndPath(process.out)
	else :
		process.e = cms.EndPath()




