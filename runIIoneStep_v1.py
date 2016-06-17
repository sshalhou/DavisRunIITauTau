import FWCore.ParameterSet.Config as cms
process = cms.Process('DavisNtuple') 

###################################
# preliminaries 
###################################

# how many events to run, -1 means run all 
MAX_EVENTS = -1
#MAX_EVENTS = 9153

# datasets for local running 

dataSetName_ = "/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_= "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"
#dataSetName_="/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"

myfilelist = cms.untracked.vstring()

if dataSetName_ == "/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/pickeventsMissing26.root'])
	myfilelist.extend(['file:/uscms_data/d3/shalhout/pickevents_missingMuTau14.root'])
#	myfilelist.extend(['file:/uscms_data/d3/shalhout/miniAODv2_SyncSample.root'])

if dataSetName_ == "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/miniAODv2_DYnlo.root'])
if dataSetName_ == "/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/miniAODv2_ZZ4l.root'])
if dataSetName_ == "/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/monoHiggsRunIIFall15MiniAODv2_2HDMzpToA0h_1200_400.root'])
if dataSetName_ == "/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM":
	myfilelist.extend(['file:/uscms_data/d3/shalhout/WJetsToLNu_HT-100To200.root'])



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
# input - remove for crab running
###################################

process.source = cms.Source("PoolSource",fileNames=myfilelist)


# process.source = cms.Source("PoolSource",fileNames=myfilelist,
# 			eventsToProcess = cms.untracked.VEventRange('1:103608-1:103608','1:103610-1:103610','1:103649-1:103649','1:103706-1:103706','1:103769-1:103769','1:103806-1:103806',
# '1:103926-1:103926','1:104000-1:104000','1:104055-1:104055','1:104131-1:104131','1:109698-1:109698','1:109756-1:109756',
# '1:109758-1:109758','1:109804-1:109804','1:109843-1:109843','1:110007-1:110007','1:110137-1:110137','1:110254-1:110254',
# '1:110465-1:110465','1:110541-1:110541','1:110576-1:110576','1:110725-1:110725','1:110739-1:110739','1:113464-1:113464',
# '1:113473-1:113473','1:113510-1:113510','1:113544-1:113544','1:113635-1:113635','1:113656-1:113656','1:113737-1:113737',
# '1:113782-1:113782','1:114111-1:114111','1:114117-1:114117','1:115326-1:115326','1:115342-1:115342','1:115405-1:115405',
# '1:115681-1:115681','1:115719-1:115719','1:115757-1:115757','1:115778-1:115778','1:115972-1:115972','1:116133-1:116133',
# '1:116279-1:116279','1:117467-1:117467','1:117581-1:117581','1:117601-1:117601','1:117801-1:117801','1:117822-1:117822',
# '1:117833-1:117833','1:117932-1:117932','1:117963-1:117963','1:119022-1:119022','1:119102-1:119102','1:119148-1:119148',
# '1:119239-1:119239','1:119242-1:119242','1:119276-1:119276','1:119346-1:119346','1:119431-1:119431','1:119497-1:119497',
# '1:119530-1:119530','1:119709-1:119709','1:119789-1:119789','1:119832-1:119832','1:119855-1:119855','1:119978-1:119978',
# '1:119993-1:119993','1:120025-1:120025','1:120085-1:120085','1:120112-1:120112','1:120179-1:120179','1:123007-1:123007',
# '1:123076-1:123076','1:123091-1:123091','1:123146-1:123146','1:123293-1:123293','1:123384-1:123384','1:123454-1:123454',
# '1:123605-1:123605','1:123625-1:123625','1:123656-1:123656','1:123718-1:123718','1:123835-1:123835','1:123947-1:123947',
# '1:124007-1:124007','1:128578-1:128578','1:128681-1:128681','1:130256-1:130256','1:130260-1:130260','1:130290-1:130290',
# '1:130316-1:130316','1:130393-1:130393','1:130421-1:130421','1:130446-1:130446','1:130463-1:130463','1:130477-1:130477',
# '1:130589-1:130589','1:133622-1:133622','1:133633-1:133633','1:133728-1:133728','1:133741-1:133741','1:133842-1:133842',
# '1:133869-1:133869','1:133959-1:133959','1:133994-1:133994','1:134031-1:134031','1:134085-1:134085','1:134320-1:134320',
# '1:134372-1:134372','1:134518-1:134518','1:136762-1:136762','1:136798-1:136798','1:136892-1:136892','1:136984-1:136984',
# '1:137061-1:137061','1:137076-1:137076','1:137097-1:137097','1:137101-1:137101','1:137130-1:137130','1:137139-1:137139',
# '1:137148-1:137148','1:137379-1:137379','1:137421-1:137421','1:137433-1:137433','1:137453-1:137453','1:137526-1:137526',
# '1:137529-1:137529','1:137557-1:137557','1:137569-1:137569','1:137712-1:137712','1:137717-1:137717','1:137723-1:137723',
# '1:137748-1:137748','1:137766-1:137766','1:137789-1:137789','1:137810-1:137810','1:137837-1:137837','1:137933-1:137933',
# '1:138147-1:138147','1:138168-1:138168','1:138246-1:138246','1:138384-1:138384','1:138392-1:138392','1:138463-1:138463',
# '1:140202-1:140202','1:140580-1:140580','1:140651-1:140651','1:140658-1:140658','1:140685-1:140685','1:140707-1:140707',
# '1:144627-1:144627','1:144683-1:144683','1:144716-1:144716','1:144805-1:144805','1:144810-1:144810','1:144834-1:144834',
# '1:145109-1:145109','1:145717-1:145717','1:145833-1:145833','1:145874-1:145874','1:145910-1:145910','1:145912-1:145912',
# '1:145918-1:145918','1:145925-1:145925','1:145929-1:145929','1:145964-1:145964','1:146009-1:146009','1:146055-1:146055',
# '1:146074-1:146074','1:146122-1:146122','1:146127-1:146127','1:146156-1:146156','1:146223-1:146223','1:146232-1:146232'))

# '1:146241-1:146241','1:146248-1:146248','1:146406-1:146406','1:146423-1:146423','1:146460-1:146460','1:146528-1:146528',
# '1:146530-1:146530','1:146642-1:146642','1:146646-1:146646','1:146767-1:146767','1:146779-1:146779','1:158058-1:158058',
# '1:158189-1:158189','1:158222-1:158222','1:158312-1:158312','1:158341-1:158341','1:158350-1:158350','1:158365-1:158365',
# '1:158367-1:158367','1:158375-1:158375','1:162548-1:162548','1:162634-1:162634','1:162701-1:162701','1:162722-1:162722',
# '1:162823-1:162823','1:162868-1:162868','1:163340-1:163340','1:163349-1:163349','1:163372-1:163372','1:163420-1:163420',
# '1:163530-1:163530','1:163560-1:163560','1:163620-1:163620','1:166245-1:166245','1:166267-1:166267','1:166366-1:166366',
# '1:166386-1:166386','1:166405-1:166405','1:166457-1:166457','1:166489-1:166489','1:166524-1:166524','1:166607-1:166607',
# '1:166624-1:166624','1:168291-1:168291','1:168299-1:168299','1:170129-1:170129','1:170221-1:170221','1:171281-1:171281',
# '1:171396-1:171396','1:171413-1:171413','1:171460-1:171460','1:31751-1:31751','1:31783-1:31783','1:31866-1:31866',
# '1:31952-1:31952','1:31991-1:31991','1:32030-1:32030','1:4465-1:4465','1:4480-1:4480','1:4491-1:4491','1:4501-1:4501',
# '1:4536-1:4536','1:4545-1:4545','1:4609-1:4609','1:4732-1:4732','1:4774-1:4774','1:4778-1:4778','1:4945-1:4945',
# '1:4956-1:4956','1:4983-1:4983','1:53415-1:53415','1:53507-1:53507','1:53562-1:53562','1:53605-1:53605','1:53700-1:53700',
# '1:57089-1:57089','1:57136-1:57136','1:57163-1:57163','1:57177-1:57177','1:57280-1:57280','1:57420-1:57420','1:57436-1:57436',
# '1:6123-1:6123','1:6213-1:6213','1:6260-1:6260','1:6277-1:6277','1:6328-1:6328','1:6359-1:6359','1:6370-1:6370','1:6376-1:6376',
# '1:6445-1:6445','1:73396-1:73396','1:73454-1:73454','1:83154-1:83154','1:83263-1:83263','1:83290-1:83290','1:83291-1:83291',
# '1:83348-1:83348','1:83407-1:83407','1:83472-1:83472','1:83603-1:83603','1:83637-1:83637','1:84225-1:84225','1:84249-1:84249',
# '1:84255-1:84255','1:84385-1:84385','1:84528-1:84528','1:84598-1:84598','1:84733-1:84733','1:86630-1:86630',
# '1:86722-1:86722','1:86750-1:86750','1:86767-1:86767','1:86791-1:86791','1:86942-1:86942','1:90366-1:90366',
# '1:90367-1:90367','1:90436-1:90436','1:90477-1:90477','1:90521-1:90521','1:91978-1:91978','1:92027-1:92027',
# '1:92039-1:92039','1:92051-1:92051','1:92082-1:92082','1:92180-1:92180','1:92230-1:92230','1:92325-1:92325',
# '1:92356-1:92356','1:92382-1:92382','1:92408-1:92408','1:92409-1:92409','1:92424-1:92424','1:92486-1:92486'))



# process.source = cms.Source("PoolSource",fileNames=myfilelist,
# 			eventsToProcess = cms.untracked.VEventRange('1:4487-1:4487','1:4492-1:4492','1:4600-1:4600','1:4632-1:4632',
# 				'1:4721-1:4721','1:4789-1:4789','1:4804-1:4804','1:4814-1:4814','1:4830-1:4830',
# 				'1:4861-1:4861','1:4901-1:4901','1:4922-1:4922','1:53411-1:53411','1:53693-1:53693',
# 				'1:53712-1:53712','1:57146-1:57146','1:57157-1:57157','1:57182-1:57182','1:57231-1:57231',
# 				'1:57295-1:57295','1:57358-1:57358','1:57441-1:57441','1:73415-1:73415','1:73420-1:73420'))	




#eventsToProcess = cms.untracked.VEventRange('1:67566889-1:67566889','1:73662929-1:73662929','1:71967435-1:71967435',
#'1:32900395-1:32900395') )

#eventsToSkip = cms.untracked.VEventRange('1:1-1:4941')	)



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
# BUILD_EFFICIENCY_TREE is False
# make sure to give the VInputTag
# all variants of e, mu, and tau
# final collections 
###################################


process.requireCandidateHiggsPair = cms.EDFilter("HiggsCandidateCountFilter",
  	electronSources = cms.VInputTag("TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple",
  									"TrimmedFilteredCustomElectronsEsUp:TrimmedFilteredCustomElectronsEsUp:DavisNtuple",
  									"TrimmedFilteredCustomElectronsEsDown:TrimmedFilteredCustomElectronsEsDown:DavisNtuple"), 
	muonSources     = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple"),

	tauSources      = cms.VInputTag("TrimmedFilteredCustomTausEsNominal:TrimmedFilteredCustomTausEsNominal:DavisNtuple",
									"TrimmedFilteredCustomTausEsUp:TrimmedFilteredCustomTausEsUp:DavisNtuple",
									"TrimmedFilteredCustomTausEsDown:TrimmedFilteredCustomTausEsDown:DavisNtuple"), 
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
process.MVAMET.requireOS = cms.bool(False)


##################################################################
# clone the default (with mods) and adjust for tau ES up
##################################################################

process.MVAMETtauEsUp = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
											   "TrimmedFilteredCustomTausEsUp:TrimmedFilteredCustomTausEsUp:DavisNtuple"),
												requireOS = cms.bool(False))


##################################################################
# clone the default (with mods) and adjust for tau ES down
##################################################################

process.MVAMETtauEsDown = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectrons:TrimmedFilteredCustomElectrons:DavisNtuple", 
											   "TrimmedFilteredCustomTausEsDown:TrimmedFilteredCustomTausEsDown:DavisNtuple"),
												requireOS = cms.bool(False))


##################################################################
# clone the default (with mods) and adjust for electron ES up
# since the electron ES systematic applies only for e+mu
# evaluate only e + mu pairs (that is why srcLeptons does not use taus)
##################################################################

process.MVAMETelectronEsUp = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectronsEsUp:TrimmedFilteredCustomElectronsEsUp:DavisNtuple"),
												requireOS = cms.bool(False))


process.MVAMETelectronEsDown = process.MVAMET.clone(srcLeptons  = cms.VInputTag("TrimmedFilteredCustomMuons:TrimmedFilteredCustomMuons:DavisNtuple", 
											   "TrimmedFilteredCustomElectronsEsDown:TrimmedFilteredCustomElectronsEsDown:DavisNtuple"),
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

###################################
# output config - should not be in crab
# script 
###################################

DEBUG_NTUPLE = False

if DEBUG_NTUPLE is True :

	print "+++++ DEBUG NTUPLE ***** will create Ntuple for Debugging "
	print "+++++ DEBUG NTUPLE ***** with edmProvDump & edmDumpEventContent "

	process.out = cms.OutputModule("PoolOutputModule",
				fileName = cms.untracked.string('NtupleFile.root'),
				SelectEvents = cms.untracked.PSet(
				                SelectEvents = cms.vstring('p')
				                ),
				#outputCommands = cms.untracked.vstring('drop *')
				outputCommands = cms.untracked.vstring('keep *')

	)


process.TFileService = cms.Service("TFileService", fileName = cms.string("FlatTuple.root"))

if DEBUG_NTUPLE is True :
	process.e = cms.EndPath(process.out)
else :
	process.e = cms.EndPath()




