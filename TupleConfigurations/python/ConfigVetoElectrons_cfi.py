####################################################################################################
# config file containing all veto (for 2nd and 3rd electron vetos) electron pre-selections
# contains : 
#              electronVetoFilter - cms.string of initial cuts imposed on slimmedElectrons
#
#

import FWCore.ParameterSet.Config as cms
from and_string_concatonator import and_string_concatonator

####################################################################################################
####################################################################################################
####################################################################################################
# electronVetoFilter : initial cut applied to slimmedElectrons
# only objects passing these requirements will be considered 
# (everything failing is dropped)
# NOTE : these should be loose enough to encompass all possible 2nd and 3rd lepton vetos


########################
# user should modify the append statements below to change electron filter cut settings
# they will be (&&) concatenated to form one string cut
# see (https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePhysicsCutParser) 
# for allowed syntax

filter_ = []

# ----------------------------------------------------
# ------------[user edit here]------------------------
filter_.append('pt>10.0')
filter_.append('abs(eta)<2.5')
filter_.append('abs(userFloat("dxy")) < 0.045')
filter_.append('abs(userFloat("dz")) < 0.2')
filter_.append('userFloat("DeltaBetaCorrectedRelIso") < 0.3') # don't think this is what LLR is doing




# ----------------------------------------------------
# ----------------------------------------------------


electronVetoFilter = cms.string(and_string_concatonator(filter_))


####################################################################################################
####################################################################################################
####################################################################################################


