#########################
# sampleInfo list
# each sample shoud have all parameters filled 
# - S. Shalhout
#############################################################################

import FWCore.ParameterSet.Config as cms


sampleInfo = []

####################################################
# mini AOD Fall15 DATA Samples                       #
####################################################


############
aPSet = cms.PSet(   
    DataSet = cms.string("/SingleElectron/Run2015D-16Dec2015-v1/MINIAOD"),
    EventTotal = cms.int32(134140420),
    NumberOfLumis = cms.int32(46528), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("DATA"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_SingleElectronRunD"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DATA"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2015D"), # needed for correct trigger settings
    RecoilCorrection = cms.string("NONE"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD"),
    EventTotal = cms.int32(91999861),
    NumberOfLumis = cms.int32(46254), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("DATA"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_SingleMuonRunD"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("DATA"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Run2015D"), # needed for correct trigger settings
    RecoilCorrection = cms.string("NONE"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for t t-bar samples
    MetSystematicType = cms.string("NONE"),
    KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
                )
sampleInfo.append(aPSet)
############


####################################################
# mini AOD Fall15 MC Samples                       #
####################################################


############
aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"),
    EventTotal = cms.int32(62135699),
    NumberOfLumis = cms.int32(311528), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
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
    MaxLumiBlock = cms.int32(3654994), # obtain using DAS website and run,lumi dataset="XXX" command
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
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
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
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
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
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
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
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
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
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
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
    #MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    MaxLumiBlock = cms.int32(1000000), # obtain using DAS website and run,lumi dataset="XXX" command
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




######### start p2
#######################

############
aPSet = cms.PSet(   
    DataSet = cms.string("/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(15301695),
    NumberOfLumis = cms.int32(73642), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_ZZTo2L2Q"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(3.22), # cross section in pb (include *BR if needed)
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
    DataSet = cms.string("/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(10747136),
    NumberOfLumis = cms.int32(51138), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_ZZTo4L"), # a unique descriptor for this sample to be used throught all parts of the code
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
    DataSet = cms.string("/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(1703772),
    NumberOfLumis = cms.int32(8579), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_WZTo1L3Nu"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(3.05), # cross section in pb (include *BR if needed)
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
    DataSet = cms.string("/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(1937499),
    NumberOfLumis = cms.int32(10002), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_WZJToLLLNu"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(4.708), # cross section in pb (include *BR if needed)
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
    DataSet = cms.string("/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(5201691),
    NumberOfLumis = cms.int32(26143), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_WWTo1L1Nu2Q"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(49.997), # cross section in pb (include *BR if needed)
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
    DataSet = cms.string("/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(19742520),
    NumberOfLumis = cms.int32(96200), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_WZTo1L1Nu2Q"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(10.71), # cross section in pb (include *BR if needed)
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
    DataSet = cms.string("/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(2855237),
    NumberOfLumis = cms.int32(14409), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_VVTo2L2Nu"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(11.95), # cross section in pb (include *BR if needed)
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
    DataSet = cms.string("/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(25704656),
    NumberOfLumis = cms.int32(125226), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_WZTo2L2Q"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(5.595), # cross section in pb (include *BR if needed)
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
    DataSet = cms.string("/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(1000000),
    NumberOfLumis = cms.int32(5000), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_STtWtop"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(35.6), # cross section in pb (include *BR if needed)
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
    DataSet = cms.string("/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(999400),
    NumberOfLumis = cms.int32(9995), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_STtWantitop"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(35.6), # cross section in pb (include *BR if needed)
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
    DataSet = cms.string("/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(3299200),
    NumberOfLumis = cms.int32(16496), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_STtchantop"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(136.02), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(0.324), # generator level filter effi. 
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
    DataSet = cms.string("/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(1630900),
    NumberOfLumis = cms.int32(16309), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_STtchanantitop"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("VV"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(80.95), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(0.324), # generator level filter effi. 
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
    DataSet = cms.string("/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(47161328),
    NumberOfLumis = cms.int32(237748), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_WJetsToLNu"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("W"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(61526.7), # cross section in pb (include *BR if needed)
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

############
aPSet = cms.PSet(   
    DataSet = cms.string("/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(45442170),
    NumberOfLumis = cms.int32(224266), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_W1JetsToLNu"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("W"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(9644.5), # cross section in pb (include *BR if needed)
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


############
aPSet = cms.PSet(   
    DataSet = cms.string("/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(30190119),
    NumberOfLumis = cms.int32(150053), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_W2JetsToLNu"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("W"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(3144.5), # cross section in pb (include *BR if needed)
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


############
aPSet = cms.PSet(   
    DataSet = cms.string("/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(19141299),
    NumberOfLumis = cms.int32(124420), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_W3JetsToLNu"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("W"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(954.8), # cross section in pb (include *BR if needed)
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


############
aPSet = cms.PSet(   
    DataSet = cms.string("/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(8995605),
    NumberOfLumis = cms.int32(49250), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_W4JetsToLNu"), # a unique descriptor for this sample to be used throught all parts of the code
    DataCard = cms.string("W"), # sample classification for H2TauTau datacards 
    CrossSection = cms.double(485.6), # cross section in pb (include *BR if needed)
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



#######################
######### end p2


################# start p3


############
aPSet = cms.PSet(
    DataSet = cms.string("/GluGluHToTauTau_M120_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v3/MINIAODSIM"),
    EventTotal = cms.int32(200000),
    NumberOfLumis = cms.int32(1000),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command    
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_GluGluHTauTau_M120powheg"),
    DataCard = cms.string("SIGNAL_GluGluHTauTau"),
    CrossSection = cms.double(3.30712),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(1498800),
    NumberOfLumis = cms.int32(7502),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_GluGluHTauTau_M125powheg"),
    DataCard = cms.string("SIGNAL_GluGluHTauTau"),
    CrossSection = cms.double(2.76758),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/GluGluToHToTauTau_M125_13TeV_amcatnloFXFX_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(5791488),
    NumberOfLumis = cms.int32(32353),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_ggHTauTau_M125amcatnlo"),
    DataCard = cms.string("SIGNAL_ggHTauTau"),
    CrossSection = cms.double(2.76758),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/GluGluHToTauTau_M130_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(199800),
    NumberOfLumis = cms.int32(1003),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_GluGluHTauTau_M130powheg"),
    DataCard = cms.string("SIGNAL_GluGluHTauTau"),
    CrossSection = cms.double(2.23054),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/VBFHToTauTau_M120_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(200000),
    NumberOfLumis = cms.int32(1057),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_VBFHTauTau_M120powheg"),
    DataCard = cms.string("SIGNAL_VBFHTauTau"),
    CrossSection = cms.double(0.274663),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(1497868),
    NumberOfLumis = cms.int32(7708),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_VBFHTauTau_M125powheg"),
    DataCard = cms.string("SIGNAL_VBFHTauTau"),
    CrossSection = cms.double(0.237131),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/VBFHToTauTau_M125_13TeV_amcatnloFXFX_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(1998200),
    NumberOfLumis = cms.int32(9991),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_VBFHTauTau_M125amcatnlo"),
    DataCard = cms.string("SIGNAL_VBFHTauTau"),
    CrossSection = cms.double(0.237131),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/VBFHToTauTau_M130_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(200000),
    NumberOfLumis = cms.int32(1041),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_VBFHTauTau_M130powheg"),
    DataCard = cms.string("SIGNAL_VBFHTauTau"),
    CrossSection = cms.double(0.196762),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/WplusHToTauTau_M120_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(60000),
    NumberOfLumis = cms.int32(309),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_WplusHTauTau_M120powheg"),
    DataCard = cms.string("SIGNAL_WplusHTauTau"),
    CrossSection = cms.double(0.0667288),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/WplusHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(441504),
    NumberOfLumis = cms.int32(2287),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_WplusHTauTau_M125powheg"),
    DataCard = cms.string("SIGNAL_WplusHTauTau"),
    CrossSection = cms.double(0.0526617),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/WplusHToTauTau_M130_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(60000),
    NumberOfLumis = cms.int32(613),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_WplusHTauTau_M130powheg"),
    DataCard = cms.string("SIGNAL_WplusHTauTau"),
    CrossSection = cms.double(0.0401043),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/WminusHToTauTau_M120_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(60000),
    NumberOfLumis = cms.int32(301),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_WminusHTauTau_M120powheg"),
    DataCard = cms.string("SIGNAL_WminusHTauTau"),
    CrossSection = cms.double(0.0425222),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/WminusHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/MINIAODSIM"),
    EventTotal = cms.int32(438800),
    NumberOfLumis = cms.int32(2194),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_WminusHTauTau_M125powheg"),
    DataCard = cms.string("SIGNAL_WminusHTauTau"),
    CrossSection = cms.double(0.0334003),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/WminusHToTauTau_M130_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(60000),
    NumberOfLumis = cms.int32(331),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_WminusHTauTau_M130powheg"),
    DataCard = cms.string("SIGNAL_WminusHTauTau"),
    CrossSection = cms.double(0.0252972),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/ZHToTauTau_M120_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(78392),
    NumberOfLumis = cms.int32(781),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_ZHTauTau_M120powheg"),
    DataCard = cms.string("SIGNAL_ZHTauTau"),
    CrossSection = cms.double(0.0693742),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(595348),
    NumberOfLumis = cms.int32(6014),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_ZHTauTau_M125powheg"),
    DataCard = cms.string("SIGNAL_ZHTauTau"),
    CrossSection = cms.double(0.0554205),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/ZHToTauTau_M130_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(79452),
    NumberOfLumis = cms.int32(425),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_ZHTauTau_M130powheg"),
    DataCard = cms.string("SIGNAL_ZHTauTau"),
    CrossSection = cms.double(0.0427228),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/ttHJetToTT_M120_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(192515),
    NumberOfLumis = cms.int32(1004),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_ttHJetTT_M120amcatnlo"),
    DataCard = cms.string("SIGNAL_ttHJetTT"),
    CrossSection = cms.double(0.0397651),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v3/MINIAODSIM"),
    EventTotal = cms.int32(782537),
    NumberOfLumis = cms.int32(8438),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_ttHJetTT_M125amcatnlo"),
    DataCard = cms.string("SIGNAL_ttHJetTT"),
    CrossSection = cms.double(0.0317952),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/ttHJetToTT_M130_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(191049),
    NumberOfLumis = cms.int32(970),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_ttHJetTT_M130amcatnlo"),
    DataCard = cms.string("SIGNAL_ttHJetTT"),
    CrossSection = cms.double(0.024556),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-80_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(499264),
    NumberOfLumis = cms.int32(2637),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M80"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-90_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(497150),
    NumberOfLumis = cms.int32(2617),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M90"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-100_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(500000),
    NumberOfLumis = cms.int32(2505),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M100"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-110_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(497984),
    NumberOfLumis = cms.int32(2965),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M110"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-120_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(475603),
    NumberOfLumis = cms.int32(2418),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M120"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-130_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(497273),
    NumberOfLumis = cms.int32(2736),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M130"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-140_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(499243),
    NumberOfLumis = cms.int32(2638),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M140"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(469976),
    NumberOfLumis = cms.int32(2545),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M160"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-180_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(498368),
    NumberOfLumis = cms.int32(3054),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M180"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-200_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(198194),
    NumberOfLumis = cms.int32(1098),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M200"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-250_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM"),
    EventTotal = cms.int32(196868),
    NumberOfLumis = cms.int32(1006),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M250"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-300_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM"),
    EventTotal = cms.int32(199657),
    NumberOfLumis = cms.int32(1165),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M300"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-350_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(185804),
    NumberOfLumis = cms.int32(1021),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M350"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-400_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v3/MINIAODSIM"),
    EventTotal = cms.int32(98414),
    NumberOfLumis = cms.int32(498),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M400"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-450_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(527),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M450"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-500_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99551),
    NumberOfLumis = cms.int32(665),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M500"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-600_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(94751),
    NumberOfLumis = cms.int32(639),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M600"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-700_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99536),
    NumberOfLumis = cms.int32(644),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M700"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-800_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(758),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M800"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-900_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99294),
    NumberOfLumis = cms.int32(563),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M900"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-1000_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(671),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M1000"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-1200_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(901),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M1200"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-1400_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(95604),
    NumberOfLumis = cms.int32(609),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M1400"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-1500_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99829),
    NumberOfLumis = cms.int32(584),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M1500"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-1600_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99166),
    NumberOfLumis = cms.int32(713),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M1600"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-1800_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99694),
    NumberOfLumis = cms.int32(652),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M1800"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-2000_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99240),
    NumberOfLumis = cms.int32(855),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M2000"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-2300_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(827),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M2300"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-2600_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99597),
    NumberOfLumis = cms.int32(742),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M2600"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-2900_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(98794),
    NumberOfLumis = cms.int32(983),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M2900"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-3200_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99247),
    NumberOfLumis = cms.int32(791),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggHTauTau_M3200"),
    DataCard = cms.string("SIGNAL_SUSYggHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-80_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(500000),
    NumberOfLumis = cms.int32(2782),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M80"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-90_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(498386),
    NumberOfLumis = cms.int32(3088),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M90"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-100_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(497190),
    NumberOfLumis = cms.int32(4624),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M100"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-110_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(494258),
    NumberOfLumis = cms.int32(2841),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M110"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-120_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(496820),
    NumberOfLumis = cms.int32(2500),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M120"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-130_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(492220),
    NumberOfLumis = cms.int32(2673),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M130"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-140_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(499592),
    NumberOfLumis = cms.int32(3673),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M140"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(495853),
    NumberOfLumis = cms.int32(2631),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M160"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-180_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(487120),
    NumberOfLumis = cms.int32(3480),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M180"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-200_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/MINIAODSIM"),
    EventTotal = cms.int32(196740),
    NumberOfLumis = cms.int32(1207),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M200"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-250_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(199436),
    NumberOfLumis = cms.int32(1061),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M250"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-300_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(200000),
    NumberOfLumis = cms.int32(1191),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M300"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-350_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(198650),
    NumberOfLumis = cms.int32(1177),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M350"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-400_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99174),
    NumberOfLumis = cms.int32(601),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M400"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-450_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(526),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M450"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-500_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(605),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M500"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-600_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(687),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M600"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-700_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99274),
    NumberOfLumis = cms.int32(821),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M700"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-800_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(98548),
    NumberOfLumis = cms.int32(815),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M800"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-900_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99306),
    NumberOfLumis = cms.int32(573),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M900"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-1000_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(569),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M1000"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-1200_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(562),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M1200"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-1400_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(722),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M1400"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-1500_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(97625),
    NumberOfLumis = cms.int32(673),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M1500"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-1600_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99588),
    NumberOfLumis = cms.int32(967),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M1600"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-1800_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(99232),
    NumberOfLumis = cms.int32(517),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M1800"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-2000_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(97176),
    NumberOfLumis = cms.int32(579),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M2000"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-2300_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v4/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(569),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M2300"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-2600_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(661),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M2600"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-2900_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(719),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M2900"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############ 

############
aPSet = cms.PSet(
    DataSet = cms.string("/SUSYGluGluToBBHToTauTau_M-3200_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(605),
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
    EventType = cms.string("MC"),
    KeyName = cms.string("Fall15_SUSYggBBHTauTau_M3200"),
    DataCard = cms.string("SIGNAL_SUSYggBBHTauTau"),
    CrossSection = cms.double(1.0),
    FilterEff = cms.double(1.0),
    CodeVersion = cms.double(1.0),
    ProductionInfo = cms.string("Fall15MCminiAOD"),
    RecoilCorrection = cms.string("HIGGS"),
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
    KeepTheoryScaleFactors = cms.bool(False)
                )
sampleInfo.append(aPSet)
############


################# end p3



######### END


####################################################
# mini AOD Fall15 MC Samples                           #
####################################################





############
aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(28751199),
    NumberOfLumis = cms.int32(1), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
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
# aPSet = cms.PSet(   
#     DataSet = cms.string("/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
#     EventTotal = cms.int32(469976),
#     NumberOfLumis = cms.int32(1), # obtain from DAS using summary dataset command
#     MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
#     EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
#     KeyName = cms.string("Fall15_SusyGG160"), # a unique descriptor for this sample to be used throught all parts of the code
#     DataCard = cms.string("SUSY_SIGNAL"), # sample classification for H2TauTau datacards 
#     CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
#     FilterEff = cms.double(1.0), # generator level filter effi. 
#     CodeVersion = cms.double(1.0), # allow us to track differences as ntuples and flattuples evolve
#     ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
#     RecoilCorrection = cms.string("HIGGS"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for mono-H, data, ttbar, single-top and diboson)
#     # for MetSystematicType use:
#     #       "NONE" for data 
#     #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
#     #       "MEtSys::ProcessType::EWK" for single top and Diboson
#     #       "MEtSys::ProcessType::TOP" for t t-bar samples
#     MetSystematicType = cms.string("MEtSys::ProcessType::BOSON"),
#     KeepTheoryScaleFactors = cms.bool(False) # usually only needed for mono-H signals since H2Tau group does the rest
#                 )
# sampleInfo.append(aPSet)
############















############
aPSet = cms.PSet(   
    DataSet = cms.string("/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(100000),
    NumberOfLumis = cms.int32(1), # obtain from DAS using summary dataset command
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
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
    MaxLumiBlock = cms.int32(1), # obtain using DAS website and run,lumi dataset="XXX" command
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