####################################################################################################
# config file containing jet pre-selections
# contains : 
#              jetFilter - cms.string of initial cuts imposed on slimmedJets
#			   jets failing these requirements will not be kept in the ntuple! 
#
#              PUjetIDworkingPoint - cms.PSet : working point for the PileUp (PU) Jet ID
#			   						 with custom additions :
#										PUjetID_AbsEtaBoundries - definition of the |eta| range bounds
#			   							PUjetID_PtBoundries - definition of the pT range bounds
#										DiscriminantName - string to access raw PU jet ID score in pat::Jet userFloats
#
#
#			   PFjetIDworkingPoint - cms.PSet
#
#
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
# based on RecoJets/JetProducers/python/PileupJetIDCutParams_cfi.py
# with PUjetID_PtBoundries & PUjetID_AbsEtaBoundries added to the PSet
# format the working point and eta boundries for our use
# based on modified full_5x_wp looseID 
####################################################################################################

PUjetIDworkingPoint  = cms.PSet(


		# custom additions 

		PUjetID_PtBoundries 	= 	  cms.vdouble(0.0, 10.0, 20.0, 30.0, 50.0), 
		PUjetID_AbsEtaBoundries =     cms.vdouble(0.0, 2.5, 2.75, 3.0, 5.0),				
		DiscriminantName = 			  cms.string("pileupJetId:fullDiscriminant"),

		# make sure the pt ranges match up exactly to PUjetID_PtBoundries
		# 		for exampe 0.0, 10.0 ---> ptRange_010
		# 		for exampe 20.0, 30.0 ---> ptRange_2030
		# 		(note the eta ranges go accross the vdoubles)
		# must always start with ptRange_ prefix

		ptRange_010   =  cms.vdouble(-0.95,-0.97,-0.97,-0.97),
		ptRange_1020   =  cms.vdouble(-0.95,-0.97,-0.97,-0.97),
		ptRange_2030   =  cms.vdouble(-0.63,-0.60,-0.55,-0.45), 
		ptRange_3050   =  cms.vdouble(-0.63,-0.60,-0.55,-0.45)
								)

####################################################################################################
#	Set up the cut values for the PF jet ID working point
#   based on loose 8 TeV point for now 
#   see : https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_13_TeV_data
####################################################################################################
	
	# each cms.vdouble in this PSet has the following format : ETA_MIN, ETA_MAX, CUT_VAL, isCutValMaximum
	# note : if isCutValMaximum = 1.0 then the requirement is parameter < CUT_VAL
	#		 if isCutValMaximum = 0 then the requirement is parameter > CUT_VAL	
	#		 the jet's eta must fall between ETA_MIN and ETA_MAX for the cut to be applied 

PFjetIDworkingPoint = cms.PSet(

		# for any eta
		NHF  				= cms.vdouble(-1000.0,1000.0,0.99,1.0), 	# NHF < 0.99
		NEMF  				= cms.vdouble(-1000.0,1000.0,0.99,1.0), 	# NEMF < 0.99	
		NumConst  			= cms.vdouble(-1000.0,1000.0,1.0,0.0),		# NumConst > 1
		MUF  			    = cms.vdouble(-1000.0,1000.0,0.8,1.0),	    # MUF < 0.8
		
		# for eta range -2.4 <= eta <= 2.4
		CHF 				= cms.vdouble(-2.4,2.4,0.0,0.0),			# CHF > 0
		CHM  				= cms.vdouble(-2.4,2.4,0.0,0.0),			# CHM > 0
		CEMF  				= cms.vdouble(-2.4,2.4,0.99,1.0)  			# CEMF < 0.99




									)
	
####################################################################################################
####################################################################################################
####################################################################################################





