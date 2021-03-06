#########################
# sampleInfo list
# each sample shoud have the fields name, type, nevents, and crossSection 
# - S. Shalhout
#############################################################################

import FWCore.ParameterSet.Config as cms


sampleInfo = []

##########################################
# example : template for adding samples  #
##########################################

aPSet = cms.PSet(	
	DataSet = cms.string("/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
	EventTotal = cms.int32(499610),
	EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
	KeyName = cms.string("Spring15_SUSY_GGH_160GeV"), # a unique descriptor for this sample to be used throught all parts of the code
	CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
	FilterEff = cms.double(1.0), # generator level filter effi. 
	CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
				)
sampleInfo.append(aPSet)



#########################################
# 2015Run D Data                        # 
#########################################



############
aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2015D-05Oct2015-v1/MINIAOD"),
    EventTotal = cms.int32(31298328),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_SingleMuonOct"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2015D-PromptReco-v4/MINIAOD"),
    EventTotal = cms.int32(48914840),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_SingleMuonPromptRv4"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2015D-05Oct2015-v1/MINIAOD"),
    EventTotal = cms.int32(48123667),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_SingleElectronOct"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2015D-PromptReco-v4/MINIAOD"),
    EventTotal = cms.int32(66419726),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_SingleElectronPromptRv4"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(
    DataSet = cms.string("/DoubleEG/Run2015D-05Oct2015-v1/MINIAOD"),
    EventTotal = cms.int32(37848934),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_DoubleEGOct"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(
    DataSet = cms.string("/DoubleEG/Run2015D-PromptReco-v4/MINIAOD"),
    EventTotal = cms.int32(42441153),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_DoubleEGPromptRv4"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2015D-05Oct2015-v2/MINIAOD"),
    EventTotal = cms.int32(4825579),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_MuonEGOct"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2015D-PromptReco-v4/MINIAOD"),
    EventTotal = cms.int32(6593259),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_MuonEGPromptRv4"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2015D-05Oct2015-v1/MINIAOD"),
    EventTotal = cms.int32(6101221),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_TauOct"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2015D-PromptReco-v4/MINIAOD"),
    EventTotal = cms.int32(7767762),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015D_TauPromptRv4"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015D")
)
sampleInfo.append(aPSet)
############


#########################################
# mini-AOD Version 2 MC samples         # 
#########################################

dataSetName_ = "MZP600_MA0300"
dataSetName_ = "MZP800_MA0300"
dataSetName_ = "MZP1000_MA0300"
dataSetName_ = "MZP1200_MA0300"
dataSetName_ = "MZP1400_MA0300"

############
aPSet = cms.PSet(   
    DataSet = cms.string("MZP600_MA0300"),
    EventTotal = cms.int32(1000),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_monoHiggsMZP600_MA0300"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("MZP800_MA0300"),
    EventTotal = cms.int32(998),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_monoHiggsMZP800_MA0300"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("MZP1000_MA0300"),
    EventTotal = cms.int32(998),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_monoHiggsMZP1000_MA0300"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("MZP1200_MA0300"),
    EventTotal = cms.int32(999),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_monoHiggsMZP1200_MA0300"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("MZP1400_MA0300"),
    EventTotal = cms.int32(1000),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_monoHiggsMZP1400_MA0300"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############



############
aPSet = cms.PSet(   
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM"),
    EventTotal = cms.int32(499610),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_SusyGG160"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM"),
    EventTotal = cms.int32(996944),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_ZZ"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(16.523), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/WW_TuneCUETP8M1_13TeV-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM"),
    EventTotal = cms.int32(993640),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_WW"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(115.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM"),
    EventTotal = cms.int32(978512),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_WZ"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(47.13), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM"),
    EventTotal = cms.int32(24184766),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_WJets"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(61526.7), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM"),
    EventTotal = cms.int32(28747969),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_DYJets"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(6025.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2_ext3-v1/MINIAODSIM"),
    EventTotal = cms.int32(96834559),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_TTbar"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(831.76), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM"),
    EventTotal = cms.int32(585353),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Spring15v2_ZH"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(0.0549587), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Spring15MCminiAODv2") # needed for correct trigger settings
                )
sampleInfo.append(aPSet)
############






##########################################
# Run2015B Datasets                      #
##########################################

aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2015B-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(3633477),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015B_SingleMuon"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015B")
)
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2015B-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(2718409),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015B_SingleElectronPromptReco"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015B")
)
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2015B-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(219680),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015B_MuonEG"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015B")
)
sampleInfo.append(aPSet)


aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2015B-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(226198),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015B_Tau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015B")
)
sampleInfo.append(aPSet)

##########################################
# Run2015C Datasets                      #
##########################################

aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2015C-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(15448925),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015C_SingleMuon"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015C")
)
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2015C-28Aug2015-v1/MINIAOD"),
    EventTotal = cms.int32(837157),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015C_SingleElectron"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015C")
)
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2015C-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(5238946),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015C_SingleElectronPromptReco"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015C")
)
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2015C-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(740507),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015C_MuonEG"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015C")
)
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/DoubleEG/Run2015C-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(16427605),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015C_DoubleEG"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015C")
)
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/DoubleMuon/Run2015C-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(12194649),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015C_DoubleMuon"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015C")
)
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/DoubleMuonLowMass/Run2015C-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(263374),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015C_DoubleMuonLowMass"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015C")
)
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2015C-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(1290957),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Run2015C_Tau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(0.0),
    ProductionInfo = cms.string("Run2015C")
)
sampleInfo.append(aPSet)




###########################
# first no-SVmass bkg run

############
aPSet = cms.PSet(
     DataSet = cms.string("/WW_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(994416),
     EventType = cms.string("MC"),
     KeyName = cms.string("WWinclusive"),
     CrossSection = cms.double(63.21),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(991232),
     EventType = cms.string("MC"),
     KeyName = cms.string("WZinclusive"),
     CrossSection = cms.double(22.82),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM"),
     EventTotal = cms.int32(996168),
     EventType = cms.string("MC"),
     KeyName = cms.string("ZZinclusive"),
     CrossSection = cms.double(10.32),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/ZZTo4L_13TeV_powheg_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(6652512),
     EventType = cms.string("MC"),
     KeyName = cms.string("ZZto4L"),
     CrossSection = cms.double(1.256),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/WWTo2L2Nu_13TeV-powheg/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(1930000),
     EventType = cms.string("MC"),
     KeyName = cms.string("WWTo2L2Nu"),
     CrossSection = cms.double(10.481),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/WWTo4Q_13TeV-powheg/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM"),
     EventTotal = cms.int32(1995200),
     EventType = cms.string("MC"),
     KeyName = cms.string("WWTo4Q"),
     CrossSection = cms.double(45.2),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/WWToLNuQQ_13TeV-powheg/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(1969600),
     EventType = cms.string("MC"),
     KeyName = cms.string("WWToLNuQQ"),
     CrossSection = cms.double(43.53),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(24711046),
     EventType = cms.string("MC"),
     KeyName = cms.string("WZTo1L1Nu2Q"),
     CrossSection = cms.double(10.96),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(1925000),
     EventType = cms.string("MC"),
     KeyName = cms.string("WZTo3LNu"),
     CrossSection = cms.double(4.42965),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(1000000),
     EventType = cms.string("MC"),
     KeyName = cms.string("ST_tW_antitop"),
     CrossSection = cms.double(35.6),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(995600),
     EventType = cms.string("MC"),
     KeyName = cms.string("ST_tW_top"),
     CrossSection = cms.double(35.6),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(24151270),
     EventType = cms.string("MC"),
     KeyName = cms.string("WJetsToLNu"),
     CrossSection = cms.double(61526.7),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM"),
     EventTotal = cms.int32(28825132),
     EventType = cms.string("MC"),
     KeyName = cms.string("DYJetsToLL"),
     CrossSection = cms.double(6025),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM"),
     EventTotal = cms.int32(19899500),
     EventType = cms.string("MC"),
     KeyName = cms.string("TTpowheg"),
     CrossSection = cms.double(831.76),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############
############
aPSet = cms.PSet(
     DataSet = cms.string("/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM"),
     EventTotal = cms.int32(585353),
     EventType = cms.string("MC"),
     KeyName = cms.string("ZHpowheg"),
     CrossSection = cms.double(1.0),
     FilterEff = cms.double(1.0),
     CodeVersion = cms.double(0.0),
     ProductionInfo = cms.string("Spring15MC") # needed for correct trigger settings
                 )
sampleInfo.append(aPSet)
############

 


###############################