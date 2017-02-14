#########################
# sampleInfo list
# each sample shoud have all parameters filled 
# - S. Shalhout
#############################################################################

import FWCore.ParameterSet.Config as cms


sampleInfo = []

# ############ EXAMPLE FOR A 2016  Sample
# aPSet = cms.PSet(   
#     DataSet = cms.string("/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
#     EventTotal = cms.int32(1498800),
#     NumberOfLumis = cms.int32(7502), # obtain from DAS using summary dataset command
#     MaxLumiBlock = cms.int32(7508), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
#     EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
#     KeyName = cms.string("SM_SIGNAL_OLDHLT_125GG"), # a unique descriptor for this sample to be used throught all parts of the code
#     DataCard = cms.string("SM_SIGNAL"), # sample classification for H2TauTau datacards 
#     CrossSection = cms.double(2.0), # cross section in pb (include *BR if needed)
#     FilterEff = cms.double(1.0), # generator level filter effi. 
#     CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
#     ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
#     RecoilCorrection = cms.string("HIGGS"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
#     # for MetSystematicType use:
#     #       "NONE" for data 
#     #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
#     #       "MEtSys::ProcessType::EWK" for single top and Diboson
#     #       "MEtSys::ProcessType::TOP" for t t-bar samples
#     MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
#     KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
#     HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
#                 )
# sampleInfo.append(aPSet)
# ########### 

#############
# 2017 MC 
#############

aPSet = cms.PSet(
    DataSet = cms.string("/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"),
    EventTotal = cms.int32(1),
    NumberOfLumis = cms.int32(1),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("MC"),
    KeyName = cms.string("VBF_TAUTAU"),
    DataCard = cms.string("SMHiggs"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(3.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



#############
# 2016 DATA 
################


aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016B-23Sep2016-v2/MINIAOD"),
    EventTotal = cms.int32(1422819),
    NumberOfLumis = cms.int32(6736),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_Run2016B-23Sep2016-v2"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD"),
    EventTotal = cms.int32(246440440),
    NumberOfLumis = cms.int32(59819),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_Run2016B-23Sep2016-v3"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(97259854),
    NumberOfLumis = cms.int32(18769),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_Run2016C-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(148167727),
    NumberOfLumis = cms.int32(30238),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_Run2016D-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(117321545),
    NumberOfLumis = cms.int32(27153),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_Run2016E-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(70593532),
    NumberOfLumis = cms.int32(19441),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_Run2016F-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(153363109),
    NumberOfLumis = cms.int32(46318),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_Run2016G-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


# zero event sample
# aPSet = cms.PSet(
#     DataSet = cms.string("/SingleElectron/Run2016H-PromptReco-v1/MINIAOD"),
#     EventTotal = cms.int32(0),
#     NumberOfLumis = cms.int32(145),
#     MaxLumiBlock = cms.int32(1),
#     EventType = cms.string("DATA"),
#     KeyName = cms.string("SingleElectron_Run2016H-PromptReco-v1"),
#     DataCard = cms.string("DATA"),
#     CrossSection = cms.double(1.0),
#     FilterEff = cms.double(1.0),
#     CodeVersion = cms.double(2.0),
#     ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
#     RecoilCorrection = cms.string("NONE"),
#     MetSystematicType = cms.string("NONE"),
#     KeepTheoryScaleFactors = cms.bool(False),
#     HLTversion = cms.string("HLT")
#        )
# sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016H-PromptReco-v2/MINIAOD"),
    EventTotal = cms.int32(126863489),
    NumberOfLumis = cms.int32(53032),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_Run2016H-PromptReco-v2"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleElectron/Run2016H-PromptReco-v3/MINIAOD"),
    EventTotal = cms.int32(3191585),
    NumberOfLumis = cms.int32(1356),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleElectron_Run2016H-PromptReco-v3"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



# zero event sample
# aPSet = cms.PSet(
#     DataSet = cms.string("/SingleMuon/Run2016B-23Sep2016-v2/MINIAOD"),
#     EventTotal = cms.int32(0),
#     NumberOfLumis = cms.int32(0),
#     MaxLumiBlock = cms.int32(1),
#     EventType = cms.string("DATA"),
#     KeyName = cms.string("SingleMuon_Run2016B-23Sep2016-v2"),
#     DataCard = cms.string("DATA"),
#     CrossSection = cms.double(1.0),
#     FilterEff = cms.double(1.0),
#     CodeVersion = cms.double(2.0),
#     ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
#     RecoilCorrection = cms.string("NONE"),
#     MetSystematicType = cms.string("NONE"),
#     KeepTheoryScaleFactors = cms.bool(False),
#     HLTversion = cms.string("HLT")
#        )
# sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD"),
    EventTotal = cms.int32(158145722),
    NumberOfLumis = cms.int32(58962),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_Run2016B-23Sep2016-v3"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(67441308),
    NumberOfLumis = cms.int32(18611),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_Run2016C-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(98017996),
    NumberOfLumis = cms.int32(30072),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_Run2016D-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(90984718),
    NumberOfLumis = cms.int32(26871),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_Run2016E-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(65425108),
    NumberOfLumis = cms.int32(19189),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_Run2016F-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016G-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(149916849),
    NumberOfLumis = cms.int32(45788),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_Run2016G-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016H-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(29162),
    NumberOfLumis = cms.int32(5605),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_Run2016H-PromptReco-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016H-PromptReco-v2/MINIAOD"),
    EventTotal = cms.int32(171134793),
    NumberOfLumis = cms.int32(57260),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_Run2016H-PromptReco-v2"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/SingleMuon/Run2016H-PromptReco-v3/MINIAOD"),
    EventTotal = cms.int32(4393222),
    NumberOfLumis = cms.int32(1329),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("SingleMuon_Run2016H-PromptReco-v3"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


# zero event sample
# aPSet = cms.PSet(
#     DataSet = cms.string("/Tau/Run2016B-23Sep2016-v2/MINIAOD"),
#     EventTotal = cms.int32(0),
#     NumberOfLumis = cms.int32(0),
#     MaxLumiBlock = cms.int32(1),
#     EventType = cms.string("DATA"),
#     KeyName = cms.string("Tau_Run2016B-23Sep2016-v2"),
#     DataCard = cms.string("DATA"),
#     CrossSection = cms.double(1.0),
#     FilterEff = cms.double(1.0),
#     CodeVersion = cms.double(2.0),
#     ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
#     RecoilCorrection = cms.string("NONE"),
#     MetSystematicType = cms.string("NONE"),
#     KeepTheoryScaleFactors = cms.bool(False),
#     HLTversion = cms.string("HLT")
#        )
# sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016B-23Sep2016-v3/MINIAOD"),
    EventTotal = cms.int32(68727458),
    NumberOfLumis = cms.int32(59642),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_Run2016B-23Sep2016-v3"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016C-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(36931473),
    NumberOfLumis = cms.int32(18810),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_Run2016C-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016D-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(56827771),
    NumberOfLumis = cms.int32(30295),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_Run2016D-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016E-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(58348773),
    NumberOfLumis = cms.int32(27199),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_Run2016E-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016F-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(40549716),
    NumberOfLumis = cms.int32(19584),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_Run2016F-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016G-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(79578661),
    NumberOfLumis = cms.int32(46543),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_Run2016G-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


# a 5 event sample?
aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016H-PromptReco-v1/MINIAOD"),
    EventTotal = cms.int32(5),
    NumberOfLumis = cms.int32(5711),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_Run2016H-PromptReco-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016H-PromptReco-v2/MINIAOD"),
    EventTotal = cms.int32(76504267),
    NumberOfLumis = cms.int32(60516),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_Run2016H-PromptReco-v2"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/Tau/Run2016H-PromptReco-v3/MINIAOD"),
    EventTotal = cms.int32(1898072),
    NumberOfLumis = cms.int32(1373),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("Tau_Run2016H-PromptReco-v3"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2016B-23Sep2016-v2/MINIAOD"),
    EventTotal = cms.int32(225271),
    NumberOfLumis = cms.int32(6607),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("MuonEG_Run2016B-23Sep2016-v2"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2016B-23Sep2016-v3/MINIAOD"),
    EventTotal = cms.int32(32727796),
    NumberOfLumis = cms.int32(58962),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("MuonEG_Run2016B-23Sep2016-v3"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2016C-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(15405678),
    NumberOfLumis = cms.int32(18611),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("MuonEG_Run2016C-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2016D-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(23482352),
    NumberOfLumis = cms.int32(30072),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("MuonEG_Run2016D-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2016E-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(22519303),
    NumberOfLumis = cms.int32(26871),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("MuonEG_Run2016E-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2016F-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(16002165),
    NumberOfLumis = cms.int32(19204),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("MuonEG_Run2016F-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2016G-23Sep2016-v1/MINIAOD"),
    EventTotal = cms.int32(33854612),
    NumberOfLumis = cms.int32(45788),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("MuonEG_Run2016G-23Sep2016-v1"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


# zero event sample
# aPSet = cms.PSet(
#     DataSet = cms.string("/MuonEG/Run2016H-PromptReco-v1/MINIAOD"),
#     EventTotal = cms.int32(0),
#     NumberOfLumis = cms.int32(5605),
#     MaxLumiBlock = cms.int32(1),
#     EventType = cms.string("DATA"),
#     KeyName = cms.string("MuonEG_Run2016H-PromptReco-v1"),
#     DataCard = cms.string("DATA"),
#     CrossSection = cms.double(1.0),
#     FilterEff = cms.double(1.0),
#     CodeVersion = cms.double(2.0),
#     ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
#     RecoilCorrection = cms.string("NONE"),
#     MetSystematicType = cms.string("NONE"),
#     KeepTheoryScaleFactors = cms.bool(False),
#     HLTversion = cms.string("HLT")
#        )
# sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2016H-PromptReco-v2/MINIAOD"),
    EventTotal = cms.int32(28705853),
    NumberOfLumis = cms.int32(57260),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("MuonEG_Run2016H-PromptReco-v2"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MuonEG/Run2016H-PromptReco-v3/MINIAOD"),
    EventTotal = cms.int32(770494),
    NumberOfLumis = cms.int32(1329),
    MaxLumiBlock = cms.int32(1),
    EventType = cms.string("DATA"),
    KeyName = cms.string("MuonEG_Run2016H-PromptReco-v3"),
    DataCard = cms.string("DATA"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)





#########################
# 2016 monoH signals 
########################

aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-300_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(99337),
    NumberOfLumis = cms.int32(599),
    MaxLumiBlock = cms.int32(603),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp600_MA0300_nonHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(94000),
    NumberOfLumis = cms.int32(470),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp600_MA0400_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98600),
    NumberOfLumis = cms.int32(493),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp800_MA0400_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-500_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98000),
    NumberOfLumis = cms.int32(490),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp800_MA0500_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-600_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp800_MA0600_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-300_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98549),
    NumberOfLumis = cms.int32(543),
    MaxLumiBlock = cms.int32(551),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1000_MA0300_nonHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v2/MINIAODSIM"),
    EventTotal = cms.int32(98200),
    NumberOfLumis = cms.int32(491),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1000_MA0400_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-500_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v2/MINIAODSIM"),
    EventTotal = cms.int32(97000),
    NumberOfLumis = cms.int32(485),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1000_MA0500_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-700_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v2/MINIAODSIM"),
    EventTotal = cms.int32(97600),
    NumberOfLumis = cms.int32(488),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1000_MA0700_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-800_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1000_MA0800_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-300_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98757),
    NumberOfLumis = cms.int32(556),
    MaxLumiBlock = cms.int32(563),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1200_MA0300_nonHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(97000),
    NumberOfLumis = cms.int32(485),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1200_MA0400_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-500_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(96000),
    NumberOfLumis = cms.int32(480),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1200_MA0500_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-600_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1200_MA0600_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-700_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1200_MA0700_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-800_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1200_MA0800_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-300_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(659),
    MaxLumiBlock = cms.int32(659),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1400_MA0300_nonHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(99200),
    NumberOfLumis = cms.int32(496),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1400_MA0400_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-500_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1400_MA0500_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(97000),
    NumberOfLumis = cms.int32(485),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1400_MA0700_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-800_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(97000),
    NumberOfLumis = cms.int32(485),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1400_MA0800_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-300_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(601),
    MaxLumiBlock = cms.int32(601),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1700_MA0300_nonHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1700_MA0400_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-500_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1700_MA0500_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-600_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1700_MA0600_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-700_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1700_MA0700_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1700_MA0-800_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(99600),
    NumberOfLumis = cms.int32(498),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1700_MA0800_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-300_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(585),
    MaxLumiBlock = cms.int32(585),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2000_MA0300_nonHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2000_MA0400_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-500_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2000_MA0500_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-600_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(95800),
    NumberOfLumis = cms.int32(479),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2000_MA0600_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-700_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(99000),
    NumberOfLumis = cms.int32(495),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2000_MA0700_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2000_MA0-800_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(97200),
    NumberOfLumis = cms.int32(486),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2000_MA0800_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-300_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(93340),
    NumberOfLumis = cms.int32(505),
    MaxLumiBlock = cms.int32(541),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2500_MA0300_nonHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(97400),
    NumberOfLumis = cms.int32(487),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2500_MA0400_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-500_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98400),
    NumberOfLumis = cms.int32(492),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2500_MA0500_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-600_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(99600),
    NumberOfLumis = cms.int32(498),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2500_MA0600_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-700_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(95000),
    NumberOfLumis = cms.int32(475),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2500_MA0700_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-2500_MA0-800_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(500),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp2500_MA0800_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-1000_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(96760),
    NumberOfLumis = cms.int32(598),
    MaxLumiBlock = cms.int32(618),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10000_MChi1000_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-10_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98946),
    NumberOfLumis = cms.int32(563),
    MaxLumiBlock = cms.int32(569),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10000_MChi10_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-150_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(524),
    MaxLumiBlock = cms.int32(524),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10000_MChi150_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(509),
    MaxLumiBlock = cms.int32(509),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10000_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-500_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(95976),
    NumberOfLumis = cms.int32(573),
    MaxLumiBlock = cms.int32(597),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10000_MChi500_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10000_MChi-50_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(96235),
    NumberOfLumis = cms.int32(512),
    MaxLumiBlock = cms.int32(532),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10000_MChi50_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-1000_MChi-1000_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(96428),
    NumberOfLumis = cms.int32(540),
    MaxLumiBlock = cms.int32(560),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp1000_MChi1000_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-1000_MChi-150_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(531),
    MaxLumiBlock = cms.int32(531),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp1000_MChi150_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-1000_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(97240),
    NumberOfLumis = cms.int32(564),
    MaxLumiBlock = cms.int32(580),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp1000_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-100_MChi-10_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(99365),
    NumberOfLumis = cms.int32(626),
    MaxLumiBlock = cms.int32(630),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp100_MChi10_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-100_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(527),
    MaxLumiBlock = cms.int32(527),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp100_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-1000_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(514),
    MaxLumiBlock = cms.int32(514),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10_MChi1000_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-10_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(99272),
    NumberOfLumis = cms.int32(546),
    MaxLumiBlock = cms.int32(550),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10_MChi10_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-150_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98898),
    NumberOfLumis = cms.int32(539),
    MaxLumiBlock = cms.int32(545),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10_MChi150_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(97116),
    NumberOfLumis = cms.int32(539),
    MaxLumiBlock = cms.int32(555),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-500_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98131),
    NumberOfLumis = cms.int32(630),
    MaxLumiBlock = cms.int32(642),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10_MChi500_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-10_MChi-50_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(532),
    MaxLumiBlock = cms.int32(532),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp10_MChi50_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-15_MChi-10_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(525),
    MaxLumiBlock = cms.int32(525),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp15_MChi10_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-1995_MChi-1000_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(532),
    MaxLumiBlock = cms.int32(532),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp1995_MChi1000_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-2000_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(531),
    MaxLumiBlock = cms.int32(531),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp2000_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-2000_MChi-500_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(97220),
    NumberOfLumis = cms.int32(525),
    MaxLumiBlock = cms.int32(540),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp2000_MChi500_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-200_MChi-150_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(575),
    MaxLumiBlock = cms.int32(575),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp200_MChi150_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-200_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(502),
    MaxLumiBlock = cms.int32(502),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp200_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-200_MChi-50_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(528),
    MaxLumiBlock = cms.int32(528),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp200_MChi50_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-20_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(595),
    MaxLumiBlock = cms.int32(595),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp20_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-295_MChi-150_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98205),
    NumberOfLumis = cms.int32(493),
    MaxLumiBlock = cms.int32(502),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp295_MChi150_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-300_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(96532),
    NumberOfLumis = cms.int32(557),
    MaxLumiBlock = cms.int32(577),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp300_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-300_MChi-50_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98590),
    NumberOfLumis = cms.int32(559),
    MaxLumiBlock = cms.int32(567),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp300_MChi50_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-500_MChi-150_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(619),
    MaxLumiBlock = cms.int32(619),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp500_MChi150_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-500_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(507),
    MaxLumiBlock = cms.int32(507),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp500_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-500_MChi-500_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(97705),
    NumberOfLumis = cms.int32(511),
    MaxLumiBlock = cms.int32(523),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp500_MChi500_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-50_MChi-10_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(558),
    MaxLumiBlock = cms.int32(558),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp50_MChi10_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-50_MChi-1_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(512),
    MaxLumiBlock = cms.int32(512),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp50_MChi1_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-50_MChi-50_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(537),
    MaxLumiBlock = cms.int32(537),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp50_MChi50_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-95_MChi-50_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(98832),
    NumberOfLumis = cms.int32(508),
    MaxLumiBlock = cms.int32(514),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp95_MChi50_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/MonoHtautau_ZpBaryonic_MZp-995_MChi-500_13TeV-madgraph/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(99192),
    NumberOfLumis = cms.int32(614),
    MaxLumiBlock = cms.int32(619),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_ZpBar_MZp995_MChi500_nonHLT"),
    DataCard = cms.string("MonoHiggs_ZpBaryonic"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-300_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(96085),
    NumberOfLumis = cms.int32(662),
    MaxLumiBlock = cms.int32(689),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp800_MA0300_nonHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-600_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(94000),
    NumberOfLumis = cms.int32(470),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1000_MA0600_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-600_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v2/MINIAODSIM"),
    EventTotal = cms.int32(95000),
    NumberOfLumis = cms.int32(475),
    MaxLumiBlock = cms.int32(500),
    EventType = cms.string("MC"),
    KeyName = cms.string("SIG_2HDM_MZp1400_MA0600_reHLT"),
    DataCard = cms.string("MonoHiggs_2HDM"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)





########################
# 2016 MC Samples      #
########################

aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-100To200_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(5010869),
    NumberOfLumis = cms.int32(24400),
    MaxLumiBlock = cms.int32(25684),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT100To200"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-200To400_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(5099631),
    NumberOfLumis = cms.int32(43786),
    MaxLumiBlock = cms.int32(44279),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT200To400"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-400To600_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(1020309),
    NumberOfLumis = cms.int32(9231),
    MaxLumiBlock = cms.int32(9237),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT400To600"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-600To800_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(5712221),
    NumberOfLumis = cms.int32(46369),
    MaxLumiBlock = cms.int32(48000),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT600To800"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v3/MINIAODSIM"),
    EventTotal = cms.int32(1944423),
    NumberOfLumis = cms.int32(14236),
    MaxLumiBlock = cms.int32(16019),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT800To1200"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(369514),
    NumberOfLumis = cms.int32(2776),
    MaxLumiBlock = cms.int32(2782),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT1200To2500"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(405752),
    NumberOfLumis = cms.int32(2494),
    MaxLumiBlock = cms.int32(2500),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZJetsToNuNu_HT2500ToInf"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)

aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(27546978),
    NumberOfLumis = cms.int32(139674),
    MaxLumiBlock = cms.int32(153587),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT100To200"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(14888384),
    NumberOfLumis = cms.int32(109051),
    MaxLumiBlock = cms.int32(111421),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT200To400"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(5469282),
    NumberOfLumis = cms.int32(40145),
    MaxLumiBlock = cms.int32(43325),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT400To600"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(14410862),
    NumberOfLumis = cms.int32(85268),
    MaxLumiBlock = cms.int32(92869),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT600To800"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(6314257),
    NumberOfLumis = cms.int32(49431),
    MaxLumiBlock = cms.int32(53849),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT800To1200"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(6817172),
    NumberOfLumis = cms.int32(65198),
    MaxLumiBlock = cms.int32(74143),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT1200To2500"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(2254248),
    NumberOfLumis = cms.int32(21537),
    MaxLumiBlock = cms.int32(23167),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_HT2500ToInf"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT"),
       )
sampleInfo.append(aPSet)





aPSet = cms.PSet(
    DataSet = cms.string("/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext3-v1/MINIAODSIM"),
    EventTotal = cms.int32(92925926),
    NumberOfLumis = cms.int32(466566),
    MaxLumiBlock = cms.int32(502066),
    EventType = cms.string("MC"),
    KeyName = cms.string("TTbar_reHLT"),
    DataCard = cms.string("TT"),
    CrossSection = cms.double(831.76),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::TOP"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)

# aPSet = cms.PSet(
#     DataSet = cms.string("/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_re_reHLT_80X_mcRun2_asymptotic_v14_ext3-v1/MINIAODSIM"),
#     EventTotal = cms.int32(92925926),
#     NumberOfLumis = cms.int32(466566),
#     MaxLumiBlock = cms.int32(502066),
#     EventType = cms.string("MC"),
#     KeyName = cms.string("TTbar_reHLT"),
#     DataCard = cms.string("TT"),
#     CrossSection = cms.double(831.76),
#     FilterEff = cms.double(1.0),
#     CodeVersion = cms.double(2.0),
#     ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
#     RecoilCorrection = cms.string("NONE"),
#     MetSystematicType = cms.string("MEtSys::ProcessType::TOP"),
#     KeepTheoryScaleFactors = cms.bool(False),
#     HLTversion = cms.string("HLT2")
#        )
# sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(28210360),
    NumberOfLumis = cms.int32(142265),
    MaxLumiBlock = cms.int32(373943),
    EventType = cms.string("MC"),
    KeyName = cms.string("WJetsToLNu_nonReHLT"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(61526.7),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(39855520),
    NumberOfLumis = cms.int32(196647),
    MaxLumiBlock = cms.int32(273863),
    EventType = cms.string("MC"),
    KeyName = cms.string("W1JetsToLNu_nonReHLT"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(9644.5),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(29984239),
    NumberOfLumis = cms.int32(149034),
    MaxLumiBlock = cms.int32(151861),
    EventType = cms.string("MC"),
    KeyName = cms.string("W2JetsToLNu_nonReHLT"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(3144.5),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(19869053),
    NumberOfLumis = cms.int32(129154),
    MaxLumiBlock = cms.int32(130000),
    EventType = cms.string("MC"),
    KeyName = cms.string("W3JetsToLNu_nonReHLT"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(954.8),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(9174756),
    NumberOfLumis = cms.int32(50232),
    MaxLumiBlock = cms.int32(51996),
    EventType = cms.string("MC"),
    KeyName = cms.string("W4JetsToLNu_nonReHLT"),
    DataCard = cms.string("W"),
    CrossSection = cms.double(485.6),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(1654964),
    NumberOfLumis = cms.int32(8334),
    MaxLumiBlock = cms.int32(8583),
    EventType = cms.string("MC"),
    KeyName = cms.string("WZTo1L3Nu_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(3.05),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(19500618),
    NumberOfLumis = cms.int32(95023),
    MaxLumiBlock = cms.int32(120900),
    EventType = cms.string("MC"),
    KeyName = cms.string("WZTo1L1Nu2Q_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(10.71),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(25996157),
    NumberOfLumis = cms.int32(126715),
    MaxLumiBlock = cms.int32(155764),
    EventType = cms.string("MC"),
    KeyName = cms.string("WZTo2L2Q_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(5.595),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(985000),
    NumberOfLumis = cms.int32(9851),
    MaxLumiBlock = cms.int32(10001),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_tW_antitop_5f_incDec_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(35.6),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"),
    EventTotal = cms.int32(998400),
    NumberOfLumis = cms.int32(4992),
    MaxLumiBlock = cms.int32(5000),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_tW_top_5f_incDec_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(35.6),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(3279200),
    NumberOfLumis = cms.int32(16396),
    MaxLumiBlock = cms.int32(16500),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_t-channel_top_4f_lepDec_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(136.02),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(1682400),
    NumberOfLumis = cms.int32(16824),
    MaxLumiBlock = cms.int32(17000),
    EventType = cms.string("MC"),
    KeyName = cms.string("ST_t-channel_antitop_4f_lepDec_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(80.95),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(5235265),
    NumberOfLumis = cms.int32(26315),
    MaxLumiBlock = cms.int32(26443),
    EventType = cms.string("MC"),
    KeyName = cms.string("WWTo1L1Nu2Q_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(1.212),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(15498581),
    NumberOfLumis = cms.int32(74587),
    MaxLumiBlock = cms.int32(92189),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZZTo2L2Q_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(3.22),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(2944584),
    NumberOfLumis = cms.int32(14859),
    MaxLumiBlock = cms.int32(40780),
    EventType = cms.string("MC"),
    KeyName = cms.string("VVTo2L2Nu_nonReHLT"),
    DataCard = cms.string("VV"),
    CrossSection = cms.double(11.95),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"),
    EventTotal = cms.int32(490805),
    NumberOfLumis = cms.int32(2455),
    MaxLumiBlock = cms.int32(2501),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKWMinus2Jets_WToLNu_M-50_nonReHLT"),
    DataCard = cms.string("EWKW"),
    CrossSection = cms.double(20.25),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(496800),
    NumberOfLumis = cms.int32(2484),
    MaxLumiBlock = cms.int32(2500),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKWPlus2Jets_WToLNu_M-50_nonReHLT"),
    DataCard = cms.string("EWKW"),
    CrossSection = cms.double(25.62),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_W"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(139089),
    NumberOfLumis = cms.int32(696),
    MaxLumiBlock = cms.int32(751),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKZ2Jets_ZToLL_M-50_nonReHLT"),
    DataCard = cms.string("EWKZ"),
    CrossSection = cms.double(25.62),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/EWKZ2Jets_ZToNuNu_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(298400),
    NumberOfLumis = cms.int32(1495),
    MaxLumiBlock = cms.int32(1503),
    EventType = cms.string("MC"),
    KeyName = cms.string("EWKZ2Jets_ZToNuNu_nonReHLT"),
    DataCard = cms.string("EWKZ"),
    CrossSection = cms.double(10.01),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("MG5_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(464435),
    NumberOfLumis = cms.int32(2324),
    MaxLumiBlock = cms.int32(2502),
    EventType = cms.string("MC"),
    KeyName = cms.string("GluGluHToWWTo2L2Nu_M125_ReHLT"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(10.01),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(498600),
    NumberOfLumis = cms.int32(2548),
    MaxLumiBlock = cms.int32(2555),
    EventType = cms.string("MC"),
    KeyName = cms.string("VBFHToWWTo2L2Nu_M125_ReHLT"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.0858),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(1498800),
    NumberOfLumis = cms.int32(7502),
    MaxLumiBlock = cms.int32(7508),
    EventType = cms.string("MC"),
    KeyName = cms.string("GluGluHToTauTau_M125_ReHLT"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(2.767578),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(1497468),
    NumberOfLumis = cms.int32(7706),
    MaxLumiBlock = cms.int32(7719),
    EventType = cms.string("MC"),
    KeyName = cms.string("VBFHToTauTau_M125_ReHLT"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.2371314),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WplusHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(437580),
    NumberOfLumis = cms.int32(2267),
    MaxLumiBlock = cms.int32(2331),
    EventType = cms.string("MC"),
    KeyName = cms.string("WplusHToTauTau_M125_ReHLT"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.04304355),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WminusHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(439400),
    NumberOfLumis = cms.int32(2197),
    MaxLumiBlock = cms.int32(2250),
    EventType = cms.string("MC"),
    KeyName = cms.string("WminusHToTauTau_M125_ReHLT"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.04304355),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(597821),
    NumberOfLumis = cms.int32(6039),
    MaxLumiBlock = cms.int32(6061),
    EventType = cms.string("MC"),
    KeyName = cms.string("ZHToTauTau_M125_ReHLT"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.0554268),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
    EventTotal = cms.int32(782155),
    NumberOfLumis = cms.int32(8436),
    MaxLumiBlock = cms.int32(9124),
    EventType = cms.string("MC"),
    KeyName = cms.string("ttHJetToTT_M125_ReHLT"),
    DataCard = cms.string("SMHIGGS"),
    CrossSection = cms.double(0.0320424),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT2")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(5046183),
    NumberOfLumis = cms.int32(25332),
    MaxLumiBlock = cms.int32(25776),
    EventType = cms.string("MC"),
    KeyName = cms.string("WGToLNuG_nonReHLT"),
    DataCard = cms.string("WG"),
    CrossSection = cms.double(489),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WGstarToLNuMuMu_012Jets_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(2219185),
    NumberOfLumis = cms.int32(12769),
    MaxLumiBlock = cms.int32(13000),
    EventType = cms.string("MC"),
    KeyName = cms.string("WGstarToLNuMuMu_012Jets_nonReHLT"),
    DataCard = cms.string("WG"),
    CrossSection = cms.double(2.793),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/WGstarToLNuEE_012Jets_13TeV-madgraph/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(2226335),
    NumberOfLumis = cms.int32(11798),
    MaxLumiBlock = cms.int32(12000),
    EventType = cms.string("MC"),
    KeyName = cms.string("WGstarToLNuEE_012Jets_nonReHLT"),
    DataCard = cms.string("WG"),
    CrossSection = cms.double(3.526),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("NONE"),
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/DYJetsToNuNu_PtZ-100To250_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(5330318),
    NumberOfLumis = cms.int32(33163),
    MaxLumiBlock = cms.int32(33333),
    EventType = cms.string("MC"),
    KeyName = cms.string("DYJetsToNuNu_PtZ-100To250_nonReHLT"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("aMCatNLO_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/DYJetsToNuNu_PtZ-250To400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(1025999),
    NumberOfLumis = cms.int32(6655),
    MaxLumiBlock = cms.int32(6907),
    EventType = cms.string("MC"),
    KeyName = cms.string("DYJetsToNuNu_PtZ-250To400_nonReHLT"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("aMCatNLO_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/DYJetsToNuNu_PtZ-400To650_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(1049341),
    NumberOfLumis = cms.int32(6113),
    MaxLumiBlock = cms.int32(6125),
    EventType = cms.string("MC"),
    KeyName = cms.string("DYJetsToNuNu_PtZ-400To650_nonReHLT"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("aMCatNLO_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)



aPSet = cms.PSet(
    DataSet = cms.string("/DYJetsToNuNu_PtZ-650ToInf_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(1017947),
    NumberOfLumis = cms.int32(8485),
    MaxLumiBlock = cms.int32(8534),
    EventType = cms.string("MC"),
    KeyName = cms.string("DYJetsToNuNu_PtZ-650ToInf_nonReHLT"),
    DataCard = cms.string("DYINV"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(2.0),
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"),
    RecoilCorrection = cms.string("aMCatNLO_DY"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False),
    HLTversion = cms.string("HLT")
       )
sampleInfo.append(aPSet)


aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(49877138),
    NumberOfLumis = cms.int32(721082), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(3655000), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("DYIncusiveExt1_nonReHLT"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(5765.4), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(2.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
    HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
                )
sampleInfo.append(aPSet)

aPSet = cms.PSet(   
    DataSet = cms.string("/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(65485168),
    NumberOfLumis = cms.int32(330450), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(342500), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("DY1Jet_nonReHLT"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(1012.5), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(2.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
    HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
                )
sampleInfo.append(aPSet)

aPSet = cms.PSet(   
    DataSet = cms.string("/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(19695514),
    NumberOfLumis = cms.int32(98678), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(100500), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("DY2Jet_nonReHLT"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(332.8), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(2.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
    HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
                )
sampleInfo.append(aPSet)

aPSet = cms.PSet(   
    DataSet = cms.string("/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(5753813),
    NumberOfLumis = cms.int32(28573), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(29408), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("DY3Jet_nonReHLT"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(101.8), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(2.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
    HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
                )
sampleInfo.append(aPSet)

aPSet = cms.PSet(   
    DataSet = cms.string("/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(4101383),
    NumberOfLumis = cms.int32(30162), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(31929), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("DY4Jet_nonReHLT"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(54.8), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(2.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
    HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
                )
sampleInfo.append(aPSet)

aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(6108651),
    NumberOfLumis = cms.int32(30989), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(31099), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("DYhighMass_nonReHLT"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY_highMASS"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(6.657), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(2.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
    HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
                )
sampleInfo.append(aPSet)


aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
    EventTotal = cms.int32(34926099),
    NumberOfLumis = cms.int32(248523), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(252696), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("DYlowMass_nonReHLT"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY_lowMASS"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(18610), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(2.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
    HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
                )
sampleInfo.append(aPSet)





###########
aPSet = cms.PSet(   
    DataSet = cms.string("TEMP_DATA"),
    EventTotal = cms.int32(134140420),
    NumberOfLumis = cms.int32(46528), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
    EventType = cms.string("DATA"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("TEMP"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DATA"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(2.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
    RecoilCorrection = cms.string("NONE"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
    HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
                )
sampleInfo.append(aPSet)
############


# ###########################
# # 2016 reHLT MC
# ###########################

# ############
# aPSet = cms.PSet(   
#     DataSet = cms.string("/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"),
#     EventTotal = cms.int32(498892),
#     NumberOfLumis = cms.int32(2708), # obtain from DAS using summary dataset command
#     MaxLumiBlock = cms.int32(2708), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
#     EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
#     KeyName = cms.string("SUSY_SIGNAL_REHLT_160GG"), # a unique descriptor for this sample to be used throught all parts of the code
#     DataCard = cms.string("SUSY_SIGNAL"), # sample classification for H2TauTau datacards 
#     CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
#     FilterEff = cms.double(1.0), # generator level filter effi. 
#     CodeVersion = cms.double(2.0), # allow us to track differences as ntuples and flattuples evolve
#     ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
#     RecoilCorrection = cms.string("HIGGS"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
#     # for MetSystematicType use:
#     #       "NONE" for data 
#     #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
#     #       "MEtSys::ProcessType::EWK" for single top and Diboson
#     #       "MEtSys::ProcessType::TOP" for t t-bar samples
#     MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
#     KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
#     HLTversion = cms.string("HLT2") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
#                 )
# sampleInfo.append(aPSet)
# ############ 



# ############
# aPSet = cms.PSet(   
#     DataSet = cms.string("/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"),
#     EventTotal = cms.int32(1498800),
#     NumberOfLumis = cms.int32(7502), # obtain from DAS using summary dataset command
#     MaxLumiBlock = cms.int32(7508), # obtain using DAS website and run,lumi dataset="XXX" command, used only for large MC samples
#     EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
#     KeyName = cms.string("SM_SIGNAL_OLDHLT_125GG"), # a unique descriptor for this sample to be used throught all parts of the code
#     DataCard = cms.string("SM_SIGNAL"), # sample classification for H2TauTau datacards 
#     CrossSection = cms.double(2.0), # cross section in pb (include *BR if needed)
#     FilterEff = cms.double(1.0), # generator level filter effi. 
#     CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
#     ProductionInfo = cms.string("Run2016_B_C_D_E_F_G_H"), # needed for correct trigger settings
#     RecoilCorrection = cms.string("HIGGS"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
#     # for MetSystematicType use:
#     #       "NONE" for data 
#     #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
#     #       "MEtSys::ProcessType::EWK" for single top and Diboson
#     #       "MEtSys::ProcessType::TOP" for t t-bar samples
#     MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
#     KeepTheoryScaleFactors = cms.bool(False), # usually only needed for mono-H signals since H2Tau group does the rest
#     HLTversion = cms.string("HLT") # in the 2016 September MC reHLT HLT is called HLT2 instead of HLT
#                 )
# sampleInfo.append(aPSet)
############ 









###############################