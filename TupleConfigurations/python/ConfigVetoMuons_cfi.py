####################################################################################################
# config file containing all veto (for 2nd and 3rd muon vetos) muon pre-selections
# contains : 
#              muonVetoFilter - cms.string of initial cuts imposed on slimmedMuons
#
#

import FWCore.ParameterSet.Config as cms
from and_string_concatonator import and_string_concatonator

####################################################################################################
####################################################################################################
####################################################################################################
# muonVetoFilter : initial cut applied to slimmedMuons
# only objects passing these requirements will be considered 
# (everything failing is dropped)
# NOTE : these should be loose enough to encompass all possible 2nd and 3rd lepton vetos


########################
# user should modify the append statements below to change muon filter cut settings
# they will be (&&) concatenated to form one string cut
# see (https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePhysicsCutParser) 
# for allowed syntax

filter_ = []

# ----------------------------------------------------
# ------------[user edit here]------------------------
filter_.append('pt>10.0')
filter_.append('abs(eta)<2.4')
filter_.append('abs(userFloat("dxy")) < 0.045')
filter_.append('abs(userFloat("dz")) < 0.2')
filter_.append('userFloat("DeltaBetaCorrectedRelIso") < 0.3') # don't think this is what LLR is doing




# ----------------------------------------------------
# ----------------------------------------------------


muonVetoFilter = cms.string(and_string_concatonator(filter_))


####################################################################################################
####################################################################################################
####################################################################################################


