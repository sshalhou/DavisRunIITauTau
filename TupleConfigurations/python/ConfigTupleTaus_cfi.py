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


# these are aligned with Wisconsin mono-H analysis for resolved tau channels
filter_.append('pt>20.0') 	   
filter_.append('abs(eta)<2.3') 
filter_.append('tauID("decayModeFinding")>0.5')
filter_.append('abs(userFloat("dz"))<0.2')
filter_.append('abs(charge)==1')
filter_.append('( (tauID("againstMuonLoose3") && tauID("againstElectronVLooseMVA6")) || (tauID("againstMuonTight3") && tauID("againstElectronVLooseMVA6")) || (tauID("againstMuonLoose3") && tauID("againstElectronTightMVA6")) )')



#filter_.append('(tauID("byTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byMediumIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byVLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byVVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5)')

# filter_.append('(tauID("byTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ||\
# 		tauID("byVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ||\
# 		tauID("byLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ||\
# 		tauID("byMediumIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ||\
# 		tauID("byVLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ||\
# 		tauID("byVVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ||\
# 		userFloat("rerunDiscriminationByIsolationMVArun2v1VLoose") > 0.5 ||\
# 		userFloat("rerunDiscriminationByIsolationMVArun2v1Loose") > 0.5  ||\
# 		userFloat("rerunDiscriminationByIsolationMVArun2v1Medium") > 0.5 ||\
# 		userFloat("rerunDiscriminationByIsolationMVArun2v1Tight") > 0.5  ||\
# 		userFloat("rerunDiscriminationByIsolationMVArun2v1VTight") > 0.5 ||\
# 		userFloat("rerunDiscriminationByIsolationMVArun2v1VVTight") > 0.5)')

filter_.append('(tauID("byLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5)')



# ----------------------------------------------------
# ----------------------------------------------------


tauFilter = cms.string(and_string_concatonator(filter_))



####################################################################################################
####################################################################################################
####################################################################################################





