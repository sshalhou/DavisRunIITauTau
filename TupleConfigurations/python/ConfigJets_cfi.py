####################################################################################################
# config file containing jet pre-selections
# contains : 
#              jetFilter - cms.string of initial cuts imposed on slimmedJets
#			   jets failing these requirements will not be kept in the ntuple! 
#

import FWCore.ParameterSet.Config as cms
from and_string_concatonator import and_string_concatonator

####################################################################################################
####################################################################################################
####################################################################################################
# jetFilter : initial cut applied to slimmedJets
# only objects passing these requirements will be considered 
# (everything failing is dropped)


########################
# user should modify the append statements below to change jet filter cut settings
# they will be (&&) concatenated to form one string cut
# see (https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePhysicsCutParser) 
# for allowed syntax

filter_ = []

# ----------------------------------------------------
# ------------[user edit here]------------------------
filter_.append('pt>15.0') # be careful here to allow for JEC variation 
filter_.append('abs(eta)<4.7') 
# ----------------------------------------------------
# ----------------------------------------------------


jetFilter = cms.string(and_string_concatonator(filter_))


####################################################################################################
####################################################################################################
####################################################################################################





