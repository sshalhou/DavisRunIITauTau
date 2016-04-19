####################################################################################################
# master config file :
#    specify settings for pair building, Tau ES options, MET & SVMass, genParticle content

import FWCore.ParameterSet.Config as cms

####################################################################################################
# edit the following to turn on/off lepton pair types
####################################################################################################

BUILD_ELECTRON_ELECTRON = False
BUILD_ELECTRON_MUON = True
BUILD_ELECTRON_TAU = True
BUILD_MUON_MUON = False
BUILD_MUON_TAU = True
BUILD_TAU_TAU = True
# new options (any one of these will run eff. flatTuple options)
BUILD_ELECTRON_X = False
BUILD_MUON_X = False
BUILD_TAU_X = False

####################################################################################################
# MAX SIZE OF LEPTON LISTS-only keep 1st MAX_X_COUNT leptons passing all selections for pair formation)
####################################################################################################

MAX_ELECTRON_COUNT = 7
MAX_MUON_COUNT = 7
MAX_TAU_COUNT = 7


####################################################################################################
# edit the following to turn on/off Tau ES variants
####################################################################################################

BUILD_TAU_ES_VARIANTS = True # not needed in early sync


####################################################################################################
# edit the following MET settings 
####################################################################################################

USE_MVAMET = True #  True = MVA MET, False = PFMET

####################################################################################################
# edit the following SVMass settings 
####################################################################################################

COMPUTE_SVMASS = False 
SVMASS_LOG_M = 0.0
SVMASS_VERBOSE = 2

####################################################################################################
# Set RUN_MEM_CHECK to True to run SimpleMemoryCheck
####################################################################################################

RUN_MEM_CHECK = True


####################################################################################################
# edit the following to adjust genParticle content (empty vector keeps everything! use abs values only)
# note : no filtering is applied on pdgId of particle's daughters or mothers 
####################################################################################################

GEN_PARTICLES_TO_KEEP = cms.vint32()

GEN_PARTICLES_TO_KEEP.append(5) # keep b-quarks
GEN_PARTICLES_TO_KEEP.append(6) # keep top-quarks
GEN_PARTICLES_TO_KEEP.append(11) # keep electrons (Must Always Keep!)
GEN_PARTICLES_TO_KEEP.append(13) # keep muons (Must Always Keep!)
GEN_PARTICLES_TO_KEEP.append(15) # keep taus (Must Always Keep!)
GEN_PARTICLES_TO_KEEP.append(12) # keep electron-neutrino
GEN_PARTICLES_TO_KEEP.append(14) # keep muon-neutrino
GEN_PARTICLES_TO_KEEP.append(16) # keep tau-neutrino
GEN_PARTICLES_TO_KEEP.append(22) # keep photons
GEN_PARTICLES_TO_KEEP.append(23) # keep Z
GEN_PARTICLES_TO_KEEP.append(24) # keep W
GEN_PARTICLES_TO_KEEP.append(25) # keep SM Higgs
GEN_PARTICLES_TO_KEEP.append(35) # keep non-SM Higgs
GEN_PARTICLES_TO_KEEP.append(36) # keep non-SM Higgs
GEN_PARTICLES_TO_KEEP.append(37) # keep non-SM Higgs
GEN_PARTICLES_TO_KEEP.append(211) # keep pi+, pi-
GEN_PARTICLES_TO_KEEP.append(111) # keep pi0


####################################################################################################
# edit the choice of the default b-tag algorithm
# note : for all jets, all BTAG algorithm raw scores are stored in the NtupleJet object
#        the default choice however, is stored directly as a float allowing for easier access
#        and is operated on by the BtagSF tool (if the applyBtagSF flag is set to True)
####################################################################################################

DEFAULT_BTAG_ALGORITHM = "pfCombinedInclusiveSecondaryVertexV2BJetTags"
APPLY_BTAG_SF = False 						
BTAG_SF_SEED = 123456	#############################################################################
						# note : if BTAG_SF_SEED is anything other than 0, the seed of the TRandom3 
						#   	 used in the BtagSF tool will be set to that value
						#        if however, BTAG_SF_SEED is 0, then the seed defaults to 	
						#        (int)(eta+5)*100000) using a custom edit to the BtagSF.hh file 		

####################################################################################################
####################################################################################################
####################################################################################################


