####################################################################################################
# config file containing all muon selections
# contains : 
#              muonFilter - cms.string of initial cuts imposed on slimmedMuons
#
#

import FWCore.ParameterSet.Config as cms
from and_string_concatonator import and_string_concatonator

####################################################################################################
####################################################################################################
####################################################################################################
# muonFilter : initial cut applied to slimmedMuons
# only objects passing these requirements will be considered 
# (everything failing is dropped)


########################
# user should modify the append statements below to change muon filter cut settings
# they will be (&&) concatenated to form one string cut
# see (https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePhysicsCutParser) 
# for allowed syntax

filter_ = []

# ----------------------------------------------------
# ------------[user edit here]------------------------
filter_.append('pt>18.0')
filter_.append('abs(eta)<2.1')
filter_.append('abs(userFloat("dxy"))<0.045')
filter_.append('abs(userFloat("dz"))<0.2')

#filter_.append('userFloat("relIsol") < 0.01')
# ----------------------------------------------------
# ----------------------------------------------------


muonFilter = cms.string(and_string_concatonator(filter_))


####################################################################################################
####################################################################################################
####################################################################################################



###################################
# configuration file to determine
# what mini-AOD skimmedMuons are retained
# in TupleMuon collection
# will define :
# thinCuts = minimum skim requirements on muons (anything failing these will be thrown away)
# vetoCuts = minimum requirement to be a veto muon
# signal_muTauCuts = minimum requirement to be a signal mu + Tau_h final state muon
# signal_muMuCuts = minimum requirement to be a signal mu + muon final state muon
###################################


mu_Cuts = cms.PSet(
	######### thin cuts ##############
	THIN_minPt = cms.double(10.0),
	######### veto cuts ##############
	VETO_minPt = cms.double(10.0),
	######### muTau signal cuts ##############
	SIGmuTau_minPt = cms.double(10.0),
	######### muMu signal cuts ##############
	SIGeleMu_minPt = cms.double(10.0)
)

