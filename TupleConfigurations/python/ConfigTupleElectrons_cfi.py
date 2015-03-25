####################################################################################################
# config file containing all electron selections
# contains : 
#              electronFilter - cms.string of initial cuts imposed on slimmedElectrons
#
#

import FWCore.ParameterSet.Config as cms
from and_string_concatonator import and_string_concatonator

####################################################################################################
####################################################################################################
####################################################################################################
# electronFilter : initial cut applied to slimmedElectrons
# only objects passing these requirements will be considered 
# (everything failing is dropped)


########################
# user should modify the append statements below to change electron filter cut settings
# they will be (&&) concatenated to form one string cut
# see (https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePhysicsCutParser) 
# for allowed syntax

filter_ = []

# ----------------------------------------------------
# ------------[user edit here]------------------------
filter_.append('pt>0.0')
#filter_.append('userFloat("relIsol") < 0.01')
# ----------------------------------------------------
# ----------------------------------------------------


electronFilter = cms.string(and_string_concatonator(filter_))


####################################################################################################
####################################################################################################
####################################################################################################


###################################
# configuration file to determine
# what mini-AOD skimmedElectrons are retained
# in TupleElectron collection
# will define :
# thinCuts = minimum skim requirements on electrons (anything failing these will be thrown away)
# vetoCuts = minimum requirement to be a veto electron
# signal_eleTauCuts = minimum requirement to be a signal ele + Tau_h final state electron
# signal_eleMuCuts = minimum requirement to be a signal ele + muon final state electron
###################################


ele_Cuts = cms.PSet(
	######### thin cuts ##############
	THIN_minPt = cms.double(10.0),
	######### veto cuts ##############
	VETO_minPt = cms.double(10.0),
	######### eleTau signal cuts ##############
	SIGeleTau_minPt = cms.double(10.0),
	######### eleMu signal cuts ##############
	SIGeleMu_minPt = cms.double(10.0)
)

