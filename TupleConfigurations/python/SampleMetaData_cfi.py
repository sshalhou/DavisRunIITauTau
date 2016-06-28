#########################
# sampleInfo list
# each sample shoud have all parameters filled 
# - S. Shalhout
#############################################################################

import FWCore.ParameterSet.Config as cms


sampleInfo = []

####################################################
# mini AOD Fall15 MC Samples                       #
####################################################


############
aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(62135699),
    NumberOfLumis = cms.int32(311528), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_DYlowMass_aMCatNLO_DY"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DYlowMass"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(18610.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("aMCatNLO_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(247512446),
    NumberOfLumis = cms.int32(3579013), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_DYInc_MG5_DY"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(6025.2), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############


############
aPSet = cms.PSet(   
    DataSet = cms.string("/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(65314144),
    NumberOfLumis = cms.int32(329585), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_DY1Jet_MG5_DY"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(1012.5), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############


############
aPSet = cms.PSet(   
    DataSet = cms.string("/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(20019059),
    NumberOfLumis = cms.int32(100295), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_DY2Jet_MG5_DY"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(332.8), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############



############
aPSet = cms.PSet(   
    DataSet = cms.string("/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(5701878),
    NumberOfLumis = cms.int32(28337), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_DY3Jet_MG5_DY"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(101.8), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############


############
aPSet = cms.PSet(   
    DataSet = cms.string("/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(4189017),
    NumberOfLumis = cms.int32(30804), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_DY4Jet_MG5_DY"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(54.8), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(6079415),
    NumberOfLumis = cms.int32(30842), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_DYhighMass_MG5_DY"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(6.657), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############


############
aPSet = cms.PSet(   
    DataSet = cms.string("/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext4-v1/MINIAODSIM"),
    EventTotal = cms.int32(187626200),
    NumberOfLumis = cms.int32(938131), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_TT_Powheg"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("TT"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(831.76), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("NONE"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for  t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::TOP"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############ 







######### END


####################################################
# mini AOD Fall15 MC Samples                           #
####################################################





############
aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(28751199),
    NumberOfLumis = cms.int32(1), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_DYJets_MG5_aMCNLO"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DY"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(6025.2), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("aMCatNLO_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############













############
aPSet = cms.PSet(   
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(469976),
    NumberOfLumis = cms.int32(1), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_SusyGG160"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("SUSY_SIGNAL"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("HIGGS"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############













############
aPSet = cms.PSet(   
    DataSet = cms.string("/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(10746497),
    NumberOfLumis = cms.int32(1), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_ZZ4l_MG5_aMCNLO"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(1.212), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("NONE"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############ 


############
aPSet = cms.PSet(   
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(1), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_2HDM_Zp1200_A0400"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("MONO_HIGGS"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("NONE"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(   
    DataSet = cms.string("/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(4949568),
    NumberOfLumis = cms.int32(1), # obtain from DAS using summary dataset command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_2HDM_WJetsToLNu_HT-100To200"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("W"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(359.7), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("MG5_W"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############ 







###############################