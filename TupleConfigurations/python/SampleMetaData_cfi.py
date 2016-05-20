#########################
# sampleInfo list
# each sample shoud have the fields name, type, nevents, and crossSection 
# - S. Shalhout
#############################################################################

import FWCore.ParameterSet.Config as cms


sampleInfo = []

####################################################
# mini AOD Fall15 MC Samples                           #
####################################################


############
aPSet = cms.PSet(   
    DataSet = cms.string("/SUSYGluGluToHToTauTau_M-160_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(469976),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_SusyGG160"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(1.0), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("HIGGS"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for single t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON")
                )
sampleInfo.append(aPSet)
############


############
aPSet = cms.PSet(   
    DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(28751199),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_DYJets_MG5_aMCNLO"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(6025.2), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("aMCatNLO_DY"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for single t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::BOSON")
                )
sampleInfo.append(aPSet)
############

############
aPSet = cms.PSet(   
    DataSet = cms.string("/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"),
    EventTotal = cms.int32(10746497),
    EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
    KeyName = cms.string("Fall15_ZZ4l_MG5_aMCNLO"), # a unique descriptor for this sample to be used throught all parts of the code
    CrossSection = cms.double(1.212), # cross section in pb (include *BR if needed)
    FilterEff = cms.double(1.0), # generator level filter effi. 
    CodeVersion = cms.double(0.0), # allow us to track differences as ntuples and flattuples evolve
    ProductionInfo = cms.string("Fall15MCminiAOD"), # needed for correct trigger settings
    RecoilCorrection = cms.string("NONE"), # options are aMCatNLO_DY, aMCatNLO_W, MG5_DY, MG5_W, HIGGS, NONE (for data, ttbar, single-top and diboson)
    # for MetSystematicType use:
    #       "NONE" for data 
    #       "MEtSys::ProcessType::BOSON" for Z/W/Higgs
    #       "MEtSys::ProcessType::EWK" for single top and Diboson
    #       "MEtSys::ProcessType::TOP" for single t t-bar samples
    MetSystematicType = cms.string("MEtSys::ProcessType::EWK")
                )
sampleInfo.append(aPSet)
############ 


###############################