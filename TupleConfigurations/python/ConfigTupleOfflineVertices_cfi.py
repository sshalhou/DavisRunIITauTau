####################################################################################################
# config file containing all vertex selections
# contains : 
#              vertexFilter - cms.string of initial cuts imposed on offlineSlimmedPrimaryVertices
#
#

import FWCore.ParameterSet.Config as cms
from and_string_concatonator import and_string_concatonator




####################################################################################################
####################################################################################################
####################################################################################################
# vertexFilter : initial cut applied to offlineSlimmedPrimaryVertices
# only objects passing these requirements will be considered 
# (everything failing is dropped)


########################
# user should modify the append statements below to change veryex filter cut settings
# they will be (&&) concatenated to form one string cut
# see (https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePhysicsCutParser) 
# for allowed syntax

filter_ = []

# ----------------------------------------------------
# ------------[user edit here]------------------------
filter_.append('isValid')
filter_.append('ndof >= 4')
filter_.append('z > -24')
filter_.append('z < +24')
filter_.append('position.Rho < 2.0')
# ----------------------------------------------------
# ----------------------------------------------------

vertexFilter = cms.string(and_string_concatonator(filter_))

####################################################################################################
####################################################################################################
####################################################################################################





