####################################################################################################
# config file containing all veto (for 2nd and 3rd tau vetos) tau pre-selections
# contains : 
#              tauVetoFilter - cms.string of initial cuts imposed on slimmedTaus
#
#

import FWCore.ParameterSet.Config as cms
from and_string_concatonator import and_string_concatonator

####################################################################################################
####################################################################################################
####################################################################################################
# tauVetoFilter : initial cut applied to slimmedTaus
# only objects passing these requirements will be considered 
# (everything failing is dropped)
# NOTE : these should be loose enough to encompass all possible 2nd and 3rd lepton vetos


########################
# user should modify the append statements below to change tau filter cut settings
# they will be (&&) concatenated to form one string cut
# see (https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePhysicsCutParser) 
# for allowed syntax

filter_ = []

# must be inclusive of third e and Di-Tau vetos in
# FlatTupleConfig_cfi.py 
# ----------------------------------------------------
# ------------[user edit here]------------------------
filter_.append('pt>15.0') 	   
filter_.append('abs(eta)<2.3') 
filter_.append('tauID("decayModeFinding")>0.5')
filter_.append('abs(userFloat("dz"))<0.2')
filter_.append('abs(charge)==1')
filter_.append('( (tauID("againstMuonLoose3") && tauID("againstElectronVLooseMVA6")) || (tauID("againstMuonTight3") && tauID("againstElectronVLooseMVA6")) || (tauID("againstMuonLoose3") && tauID("againstElectronTightMVA6")) )')
filter_.append('(tauID("byTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byMediumIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byVLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 || tauID("byVVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5)')




# ----------------------------------------------------
# ----------------------------------------------------


tauVetoFilter = cms.string(and_string_concatonator(filter_))


####################################################################################################
####################################################################################################
####################################################################################################


