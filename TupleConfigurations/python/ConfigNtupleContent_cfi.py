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
BUILD_ELECTRON_TAUBOOSTED = True
BUILD_MUON_TAUBOOSTED = True
BUILD_TAUBOOSTED_TAUBOOSTED = True


# new options (any one of these will run eff. flatTuple options)
BUILD_EFFICIENCY_TREE  = False


####################################################################################################
# MAX SIZE OF LEPTON LISTS-only keep 1st MAX_X_COUNT leptons passing all selections for pair formation)
####################################################################################################

MAX_ELECTRON_COUNT = 10
MAX_MUON_COUNT = 10
MAX_TAU_COUNT = 10


####################################################################################################
# edit the following to turn on/off Tau/electron ES variants
####################################################################################################

BUILD_TAU_ES_VARIANTS = True 
BUILD_ELECTRON_ES_VARIANTS = True # only used for e+mu channel


####################################################################################################
# some options to run SVFit at Ntuple level 
# in general you do not want to run SVFit at Ntuple level
# due to the lack of recoil corrections 
# setting COMPUTE_SVMASS to True is only useful for testing 
# actual SVFit should be configured in FlatTupleConfig_cfi.py
####################################################################################################

COMPUTE_SVMASS_AT_NTUPLE = False 
SVMASS_LOG_M = 0.0
SVMASS_VERBOSE = 2
USE_MVAMET = True #  True = use MVA MET for SVFit calc, False = use PFMET

####################################################################################################
# Set RUN_MEM_CHECK to True to run SimpleMemoryCheck
####################################################################################################

RUN_MEM_CHECK = True


####################################################################################################
# edit the following to adjust genParticle content (empty vector keeps everything! use abs values only)
# note : no filtering is applied on pdgId of particle's daughters or mothers 
####################################################################################################

GEN_PARTICLES_TO_KEEP = cms.vint32()


GEN_PARTICLES_TO_KEEP.append(1) # keep d-quarks
GEN_PARTICLES_TO_KEEP.append(2) # keep u-quarks
GEN_PARTICLES_TO_KEEP.append(3) # keep s-quarks
GEN_PARTICLES_TO_KEEP.append(4) # keep c-quarks
GEN_PARTICLES_TO_KEEP.append(5) # keep b-quarks
GEN_PARTICLES_TO_KEEP.append(6) # keep top-quarks
GEN_PARTICLES_TO_KEEP.append(9) # a gluon (also 21 in some schemes)
GEN_PARTICLES_TO_KEEP.append(11) # keep electrons (Must Always Keep!)
GEN_PARTICLES_TO_KEEP.append(12) # keep electron-neutrino
GEN_PARTICLES_TO_KEEP.append(13) # keep muons (Must Always Keep!)
GEN_PARTICLES_TO_KEEP.append(14) # keep muon-neutrino
GEN_PARTICLES_TO_KEEP.append(15) # keep taus (Must Always Keep!)
GEN_PARTICLES_TO_KEEP.append(16) # keep tau-neutrino
GEN_PARTICLES_TO_KEEP.append(17) # a non-SM tau' 
GEN_PARTICLES_TO_KEEP.append(18) # a nu'_tau (the dm particle) - from central prod.
GEN_PARTICLES_TO_KEEP.append(21) # a gluon (also 9 in some schemes)
GEN_PARTICLES_TO_KEEP.append(22) # a photon
GEN_PARTICLES_TO_KEEP.append(23) # keep Z
GEN_PARTICLES_TO_KEEP.append(24) # keep W
GEN_PARTICLES_TO_KEEP.append(25) # keep SM Higgs
GEN_PARTICLES_TO_KEEP.append(28) # the A0 - from central prod.
GEN_PARTICLES_TO_KEEP.append(32) # a Z' variant - from central prod.
GEN_PARTICLES_TO_KEEP.append(33) # a Z'' exo particle
GEN_PARTICLES_TO_KEEP.append(34) # a W' exo particle
GEN_PARTICLES_TO_KEEP.append(35) # keep non-SM Higgs
GEN_PARTICLES_TO_KEEP.append(36) # keep non-SM Higgs
GEN_PARTICLES_TO_KEEP.append(37) # keep non-SM Higgs
GEN_PARTICLES_TO_KEEP.append(211) # keep pi+, pi-
GEN_PARTICLES_TO_KEEP.append(111) # keep pi0
GEN_PARTICLES_TO_KEEP.append(9000001) # Z' variant - from private prod.
GEN_PARTICLES_TO_KEEP.append(9000007) # chi (the dm particle) - from private prod.


####################################################################################################
# edit the choice of the default b-tag algorithm
# note : for all jets, all BTAG algorithm raw scores are stored in the NtupleJet object
#        the default choice however, is stored directly as a float allowing for easier access
#        and is operated on by the BtagSF tool (if the applyBtagSF flag is set to True)
####################################################################################################

DEFAULT_BTAG_ALGORITHM = "pfCombinedInclusiveSecondaryVertexV2BJetTags"


####################################################################################################
####################################################################################################
####################################################################################################


