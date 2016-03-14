####################################################################################################
# config file containing settings for event weight computations @ the Ntuple level
# 			
#		  PUntupleWeightSettings cms.PSet contains :
#				
#			   - pileupSrcInputTag : the input pileup collection
#              - PUntupleWeightSettings(pileup_mcFilePath, pileup_dataFilePath) : PU source file locations : one for data, one for MC
#			   - mcGenWeightSrcInputTag 
#			   - LHEEventProductSrcInputTag : useful for stitching W and Z + njet samples

import FWCore.ParameterSet.Config as cms


# note pileupSrcInputTag was different for MC, embedded MC, and embedded Data in RunI
# pileupSrcInputTag = cms.InputTag('addPileupInfo') # for miniAODv1
pileupSrcInputTag = cms.InputTag('slimmedAddPileupInfo') # for miniAODv2



PUntupleWeightSettings = cms.PSet(
			pileup_mcFilePath = cms.string("DavisRunIITauTau/RunTimeDataInput/data/PileUpReWeightFiles/MC_Fall15_PU25_V1.root"),
			pileup_dataFilePath = cms.string("DavisRunIITauTau/RunTimeDataInput/data/PileUpReWeightFiles/Data_Pileup_2015D_Feb02.root")
			)

# mc weight 
mcGenWeightSrcInputTag = cms.InputTag('generator')

# NUP source 
LHEEventProductSrcInputTag = cms.InputTag('externalLHEProducer')