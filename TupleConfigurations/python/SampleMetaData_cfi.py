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
	CodeVersion = cms.double(0.0) # allow us to track differences as ntuples and flattuples evolve
				)


sampleInfo.append(aPSet)



###############################
aPSet = cms.PSet(	
	DataSet = cms.string("/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM"),
	EventTotal = cms.int32(28825132),
	EventType = cms.string("MC"), # valid EventTypes are :  MC, DATA, EMBEDDED (expand as needed)
	KeyName = cms.string("Spring15_MG5_aMCNLO_DYJetsToLL"), # a unique descriptor for this sample to be used throught all parts of the code
	CrossSection = cms.double(6025.0), # cross section in pb (include *BR if needed)
	FilterEff = cms.double(1.0), # generator level filter effi. 
	CodeVersion = cms.double(0.0) # allow us to track differences as ntuples and flattuples evolve
				)
sampleInfo.append(aPSet)
###############################