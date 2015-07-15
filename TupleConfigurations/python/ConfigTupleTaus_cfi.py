####################################################################################################
# config file containing all tau selections
# contains : 
#              tauFilter - cms.string of initial cuts imposed on slimmedTaus
#
#

import FWCore.ParameterSet.Config as cms
from and_string_concatonator import and_string_concatonator

####################################################################################################
####################################################################################################
####################################################################################################
# tauFilter : initial cut applied to slimmedTaus
# only objects passing these requirements will be considered 
# (everything failing is dropped)


########################
# user should modify the append statements below to change tau filter cut settings
# they will be (&&) concatenated to form one string cut
# see (https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePhysicsCutParser) 
# for allowed syntax

filter_ = []

# ----------------------------------------------------
# ------------[user edit here]------------------------
filter_.append('pt>20.0') 	   # be careful here to allow for tau ES variation
filter_.append('abs(eta)<2.3') 
filter_.append('tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits")<2.0')
filter_.append(' (tauID("decayModeFinding")>0.5) || (tauID("decayModeFindingNewDMs")>0.5) ')
# ----------------------------------------------------
# ----------------------------------------------------


tauFilter = cms.string(and_string_concatonator(filter_))


####################################################################################################
####################################################################################################
####################################################################################################







###################################
# configuration file to determine
# what mini-AOD skimmedTaus are retained
# in TupleTau collection
# will define :
# thinCuts = minimum skim requirements on taus (anything failing these will be thrown away)
# vetoCuts = minimum requirement to be a veto Tau
# signal_eleTauCuts = minimum requirement to be a signal ele + Tau_h final state Tau
# signal_muTauCuts = minimum requirement to be a signal tau + Tau_h final state Tau
###################################


tau_Cuts = cms.PSet(
	######### thin cuts ##############
	THIN_minPt = cms.double(10.0),
	######### veto cuts ##############
	VETO_minPt = cms.double(10.0),
	######### eleTau signal cuts ##############
	SIGeleTau_minPt = cms.double(10.0),
	######### eleMu signal cuts ##############
	SIGmuTau_minPt = cms.double(10.0)
)

