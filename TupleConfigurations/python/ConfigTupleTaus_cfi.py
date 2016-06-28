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
filter_.append('pt>20.0') 	   
filter_.append('abs(eta)<2.3') 
filter_.append('tauID("decayModeFinding")>0.5')
filter_.append('abs(userFloat("dz"))<0.2')
filter_.append('abs(charge)==1')
# ----------------------------------------------------
# ----------------------------------------------------

from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import APPLY_POST_SYNC_TAU_CUTS as ApplyTauCuts_
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import post_sync_tauCutRaw as PostSyncTauIsoCuts_
from DavisRunIITauTau.FlatTupleGenerator.FlatTupleConfig_cfi import post_sync_tauAntiEMuRaw as PostSyncTauMVACuts_

if(ApplyTauCuts_):
	filter_.append(PostSyncTauIsoCuts_)
	filter_.append(PostSyncTauMVACuts_)

tauFilter = cms.string(and_string_concatonator(filter_))

if ApplyTauCuts_ :
	print '++++ with post sync tau ISO and MVA cuts applied, '
	print '++++ only considering taus which pass :'
	print '==========================================='
	print '==========================================='
	print tauFilter
	print '==========================================='
	print '==========================================='


####################################################################################################
####################################################################################################
####################################################################################################





