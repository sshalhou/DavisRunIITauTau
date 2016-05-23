####################################################################################################
# config file containing all trigger setup info for HLT pats at the event level
# and also for lepton-trigObject matching

import FWCore.ParameterSet.Config as cms
from doubleHyphen_string_concatonator import doubleHyphen_string_concatonator

####################################################################################################
# User Provided Arguments for Trigger Setup : 
####################################################################################################
#	- trigger object match max DR
#
#	- trigger object match types: cms.vint32(+81, +82)
#
#  			see :  https://github.com/cms-sw/cmssw/blob/CMSSW_7_2_X/DataFormats/HLTReco/interface/TriggerTypeDefs.h
#
#   - specific path and filters to summarize (vstring with components sep. by --): 
#
#	    vstring('PATHNAME1--FILTER REQ. AND/OR--FILTER_1--FILTER_2--FILTER_N',
#		  	     PATHNAME2--FILTER REQ. AND/OR--FILTER_1--FILTER_2--FILTER_N')
#
#       Note : HLT_SOMETHING_v* version wildcards are supported, but in that case be careful of changing
#		       filter requirements
#								
###############
# *** NOTES ***
###############
# 
# [1a] ALL HLT paths that were accepted for the event are embedded 
#      during creation of CustomPat{e,mu,tau} Collections --> these are UserFloat("HLT_XYZ_v1")
#      note : cuts version wildcards not supported at this stage - yet	
#
# [1b] ALL HLT paths that were accepted for the event are kept in NtupleEvent's 
#	   NtupleLeptons (i.e. leg1() and leg2(); see HLTpath function in NtupleLepton.h) 
#      note : version wildcards (_v*) are supported in the HLTpath function
# 
# [2] ALL TriggerObjects matched to leg1 and leg2 meeting DR and object match type requirments are stored in 
#     NtupleEvent as a vector of NtupleTrigObject (i.e. leg1_trigMatches and leg2_trigMatches)
#
# [3a] Each NtupleTrigObject retains isL3, isLF, & isBoth
#     (see https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATTrigger#TriggerObjectStandAlone)   
#     evaluated for each accepted HLT path
#
# [3b] Each NtupleTrigObject has a list of all Filters the object satisfies (from any HLT path, not just accepted ones)  
#
# [4] Summary Variables : For ease of checking HLT paths, trigger matching & filters, NtupleEvent now contains 
#     the following built in functions :
#
#						isLeg1GoodForHLTPath('HLT_WHATEVER')
#                       isLeg2GoodForHLTPath('HLT_WHATEVER')
#
#    these return 1.0 if  'specific path and filters to summarize' are satisfied by the given leg
#
#  [5] a unique if block should be defined for each sample type (based on ProductionInfo in the meta data)
####################################################################################################

####################################################################################################
# Configuration :
####################################################################################################



class ConfigTriggerHelper:
	def __init__(self,sampleDataArg):
		self.sampleData_ = sampleDataArg

		# DR match between lepton at reco and the triggerObject

		self.electronTriggerMatch_DR = cms.double(0.5)
		self.muonTriggerMatch_DR = cms.double(0.5)
		self.tauTriggerMatch_DR = cms.double(0.5)

		# allowed types for triggerObject matching

		self.electronTriggerMatch_Types = cms.vint32(+81, +82)
		self.muonTriggerMatch_Types = cms.vint32(+83)
		self.tauTriggerMatch_Types = cms.vint32(-86,+84)


		########################
		# user should modify the append statements below to change lepton trigger settings
		# strings will be (--) concatenated to form one string 

		# master list to hold all paths & filters, will be converted to vsrting

		self.electron_masterList_ = []
		self.muon_masterList_ = []
		self.tau_masterList_ = []


		# specific path strings to be concatenated and then grouped into one vstring object
		# don't forget to append to masterList_ 


		if(self.sampleData_.ProductionInfo == 'Run2015B'):
			#########################################################		
			# HLT paths and filters for Run2015B  Data -- START		#
			#########################################################
			print '******** SETTING TRIGGER INFO FOR ', self.sampleData_.ProductionInfo

			####  Run2015B path : Mu23+Ele12 #####

			mlist1_ = []
			mlist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2') # path
			mlist1_.append('AND') # AND or OR of the following filters
			mlist1_.append('hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23') # filter
			self.muon_masterList_.append(mlist1_)

			elist1_ = []
			elist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2') # path
			elist1_.append('AND') # AND or OR of the following filters
			elist1_.append('hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist1_)


			#### Run2015B path : Mu8+Ele23 #####

			mlist2_ = []
			mlist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2') # path
			mlist2_.append('AND') # AND or OR of the following filters
			mlist2_.append('hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8') # filter
			self.muon_masterList_.append(mlist2_)

			elist2_ = []
			elist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2') # path
			elist2_.append('AND') # AND or OR of the following filters
			elist2_.append('hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist2_)


			#### Run2015B path : Iso Mu 17 PF tau 20 #####

			mlist5_ = []
			mlist5_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v2') # path
			mlist5_.append('AND') # AND or OR of the following filters
			mlist5_.append('hltL3crIsoL1sMu16erTauJet20erL1f0L2f10QL3f17QL3trkIsoFiltered0p09') # filter
			mlist5_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
			self.muon_masterList_.append(mlist5_)

			tlist1_ = []
			tlist1_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v2') # path
			tlist1_.append('AND') # AND or OR of the following filters
			tlist1_.append('hltPFTau20TrackLooseIsoAgainstMuon') # filter
			tlist1_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
			self.tau_masterList_.append(tlist1_)

			#### Run2015B path : Iso Mu 24 #####

			mlist3_ = []
			mlist3_.append('HLT_IsoMu24_eta2p1_v2') # path
			mlist3_.append('AND') # AND or OR of the following filters
			mlist3_.append('hltL3crIsoL1sMu20Eta2p1L1f0L2f10QL3f24QL3trkIsoFiltered0p09') # filter
			self.muon_masterList_.append(mlist3_)


			#### Run2015B path : Ele22 PF tau 20 #####

			elist3_ = []
			elist3_.append('HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v1') # path
			elist3_.append('AND') # AND or OR of the following filters
			elist3_.append('hltSingleEle22WPLooseGsfTrackIsoFilter') # filter
			elist3_.append('hltOverlapFilterIsoEle22WPLooseGsfLooseIsoPFTau20') # filter
			self.electron_masterList_.append(elist3_)

			tlist2_ = []
			tlist2_.append('HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v1') # path
			tlist2_.append('AND') # AND or OR of the following filters
			tlist2_.append('hltPFTau20TrackLooseIso') # filter
			tlist2_.append('hltOverlapFilterIsoEle22WPLooseGsfLooseIsoPFTau20') # filter
			self.tau_masterList_.append(tlist2_)


			#### Run2015B path : Ele32 #####

			elist4_ = []
			elist4_.append('HLT_Ele32_eta2p1_WPTight_Gsf_v1') # path
			elist4_.append('AND') # AND or OR of the following filters
			elist4_.append('hltEle32WPTightGsfTrackIsoFilter') # filter
			self.electron_masterList_.append(elist4_)








			#### Run2015B path : Double Med Iso PF Tau 40 #####

			tlist3_ = []
			tlist3_.append('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v2') # path
			tlist3_.append('AND') # AND or OR of the following filters
			tlist3_.append('hltDoublePFTau40TrackPt1MediumIsolationDz02Reg') # filter
			self.tau_masterList_.append(tlist3_)


			#########################################################		
			# HLT paths and filters for Run2015B Data   -- END		#
			#########################################################


		if(self.sampleData_.ProductionInfo == 'Run2015C'):
			#########################################################		
			# HLT paths and filters for Run2015C  Data -- START		#
			#########################################################
			print '******** SETTING TRIGGER INFO FOR ', self.sampleData_.ProductionInfo

			####  Run2015C path : Mu23+Ele12 #####

			mlist1_ = []
			mlist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2') # path
			mlist1_.append('AND') # AND or OR of the following filters
			mlist1_.append('hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23') # filter
			self.muon_masterList_.append(mlist1_)

			elist1_ = []
			elist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2') # path
			elist1_.append('AND') # AND or OR of the following filters
			elist1_.append('hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist1_)


			#### Run2015C path : Mu8+Ele23 #####

			mlist2_ = []
			mlist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2') # path
			mlist2_.append('AND') # AND or OR of the following filters
			mlist2_.append('hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8') # filter
			self.muon_masterList_.append(mlist2_)

			elist2_ = []
			elist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2') # path
			elist2_.append('AND') # AND or OR of the following filters
			elist2_.append('hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist2_)


			#### Run2015C path : Iso Mu 17 PF tau 20 #####

			mlist5_ = []
			mlist5_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v2') # path
			mlist5_.append('AND') # AND or OR of the following filters
			mlist5_.append('hltL3crIsoL1sMu16erTauJet20erL1f0L2f10QL3f17QL3trkIsoFiltered0p09') # filter
			mlist5_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
			self.muon_masterList_.append(mlist5_)

			tlist1_ = []
			tlist1_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v2') # path
			tlist1_.append('AND') # AND or OR of the following filters
			tlist1_.append('hltPFTau20TrackLooseIsoAgainstMuon') # filter
			tlist1_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
			self.tau_masterList_.append(tlist1_)

			#### Run2015C path : Iso Mu 24 #####

			mlist3_ = []
			mlist3_.append('HLT_IsoMu24_eta2p1_v2') # path
			mlist3_.append('AND') # AND or OR of the following filters
			mlist3_.append('hltL3crIsoL1sMu20Eta2p1L1f0L2f10QL3f24QL3trkIsoFiltered0p09') # filter
			self.muon_masterList_.append(mlist3_)


			#### Run2015C path : Ele22 PF tau 20 #####

			elist3_ = []
			elist3_.append('HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v1') # path
			elist3_.append('AND') # AND or OR of the following filters
			elist3_.append('hltEle22WPLooseL1IsoEG20erTau20erGsfTrackIsoFilter') # filter
			elist3_.append('hltOverlapFilterIsoEle22WPLooseGsfLooseIsoPFTau20') # filter
			self.electron_masterList_.append(elist3_)

			tlist2_ = []
			tlist2_.append('HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v1') # path
			tlist2_.append('AND') # AND or OR of the following filters
			tlist2_.append('hltPFTau20TrackLooseIso') # filter
			tlist2_.append('hltOverlapFilterIsoEle22WPLooseGsfLooseIsoPFTau20') # filter
			self.tau_masterList_.append(tlist2_)


			#### Run2015C path : Ele32 #####

			elist4_ = []
			elist4_.append('HLT_Ele32_eta2p1_WPTight_Gsf_v1') # path
			elist4_.append('AND') # AND or OR of the following filters
			elist4_.append('hltEle32WPTightGsfTrackIsoFilter') # filter
			self.electron_masterList_.append(elist4_)


			#### Run2015C path : Double Med Iso PF Tau 40 #####

			tlist3_ = []
			tlist3_.append('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v2') # path
			tlist3_.append('AND') # AND or OR of the following filters
			tlist3_.append('hltDoublePFTau40TrackPt1MediumIsolationDz02Reg') # filter
			self.tau_masterList_.append(tlist3_)


			#########################################################		
			# HLT paths and filters for Run2015C Data   -- END		#
			#########################################################

		if(self.sampleData_.ProductionInfo == 'Run2015D'):
			#########################################################		
			# HLT paths and filters for Run2015D  Data -- START		#
			# updated for Fall 15 mini AOD	
			#########################################################
			print '******** SETTING TRIGGER INFO FOR ', self.sampleData_.ProductionInfo

			####  Run2015D path : Mu17+Ele12 #####

			mlist1_ = []
			mlist1_.append('HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') # path
			mlist1_.append('AND') # AND or OR of the following filters
			mlist1_.append('hltMu17TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered17') # filter
			self.muon_masterList_.append(mlist1_)

			elist1_ = []
			elist1_.append('HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') # path
			elist1_.append('AND') # AND or OR of the following filters
			elist1_.append('hltMu17TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist1_)


			#### Run2015D path : Mu8+Ele17 #####

			mlist2_ = []
			mlist2_.append('HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*') # path
			mlist2_.append('AND') # AND or OR of the following filters
			mlist2_.append('hltMu8TrkIsoVVLEle17CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8') # filter
			self.muon_masterList_.append(mlist2_)

			elist2_ = []
			elist2_.append('HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*') # path
			elist2_.append('AND') # AND or OR of the following filters
			elist2_.append('hltMu8TrkIsoVVLEle17CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist2_)


			#### Run2015D path : Iso Mu 18 #####

			mlist3_ = []
			mlist3_.append('HLT_IsoMu18_v*') # path
			mlist3_.append('AND') # AND or OR of the following filters
			mlist3_.append('hltL3crIsoL1sMu16L1f0L2f10QL3f18QL3trkIsoFiltered0p09') # filter
			self.muon_masterList_.append(mlist3_)


			#### Run2015D path : Ele23 #####

			elist4_ = []
			elist4_.append('HLT_Ele23_WPLoose_Gsf_v*') # path
			elist4_.append('AND') # AND or OR of the following filters
			elist4_.append('hltEle23WPLooseGsfTrackIsoFilter') # filter
			self.electron_masterList_.append(elist4_)


			#### Run2015D path : Double Med Iso PF Tau 35 #####

			tlist3_ = []
			tlist3_.append('HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*') # path
			tlist3_.append('AND') # AND or OR of the following filters
			tlist3_.append('hltDoublePFTau35TrackPt1MediumIsolationDz02Reg') # filter
			self.tau_masterList_.append(tlist3_)


			#########################################################		
			# HLT paths and filters for Run2015D Data   -- END		#
			#########################################################


		if(self.sampleData_.ProductionInfo == 'Spring15MC'):
			#########################################################		
			# HLT paths and filters for Spring15MC   -- START		#
			#########################################################
			print '******** SETTING TRIGGER INFO FOR ', self.sampleData_.ProductionInfo
			####  Spring15MC path : Mu23+Ele12 #####

			mlist1_ = []
			mlist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1') # path
			mlist1_.append('AND') # AND or OR of the following filters
			mlist1_.append('hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23') # filter
			self.muon_masterList_.append(mlist1_)

			elist1_ = []
			elist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1') # path
			elist1_.append('AND') # AND or OR of the following filters
			elist1_.append('hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist1_)

			#### Spring15MC path : Mu8+Ele23 #####

			mlist2_ = []
			mlist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1') # path
			mlist2_.append('AND') # AND or OR of the following filters
			mlist2_.append('hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8') # filter
			self.muon_masterList_.append(mlist2_)

			elist2_ = []
			elist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1') # path
			elist2_.append('AND') # AND or OR of the following filters
			elist2_.append('hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist2_)

			#### Spring15MC path : Iso Mu 24 #####

			mlist3_ = []
			mlist3_.append('HLT_IsoMu24_eta2p1_v1') # path
			mlist3_.append('AND') # AND or OR of the following filters
			mlist3_.append('hltL3crIsoL1sMu20Eta2p1L1f0L2f10QL3f24QL3trkIsoFiltered0p09') # filter
			self.muon_masterList_.append(mlist3_)

			#### Spring15MC path : Iso Mu 27 #####

			mlist4_ = []
			mlist4_.append('HLT_IsoMu27_v1') # path
			mlist4_.append('AND') # AND or OR of the following filters
			mlist4_.append('hltL3crIsoL1sMu25L1f0L2f10QL3f27QL3trkIsoFiltered0p09') # filter
			self.muon_masterList_.append(mlist4_)


			#### Spring15MC path : Iso Mu 17 PF tau 20 #####

			mlist5_ = []
			mlist5_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1') # path
			mlist5_.append('AND') # AND or OR of the following filters
			mlist5_.append('hltL3crIsoL1sMu16erTauJet20erL1f0L2f10QL3f17QL3trkIsoFiltered0p09') # filter
			mlist5_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
			self.muon_masterList_.append(mlist5_)

			tlist1_ = []
			tlist1_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v1') # path
			tlist1_.append('AND') # AND or OR of the following filters
			tlist1_.append('hltPFTau20TrackLooseIsoAgainstMuon') # filter
			tlist1_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
			self.tau_masterList_.append(tlist1_)

			#### Spring15MC path : Ele22 PF tau 20 #####

			elist3_ = []
			elist3_.append('HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20_v1') # path
			elist3_.append('AND') # AND or OR of the following filters
			elist3_.append('hltEle22WP75L1IsoEG20erTau20erGsfTrackIsoFilter') # filter
			elist3_.append('hltOverlapFilterIsoEle22WP75GsfLooseIsoPFTau20') # filter
			self.electron_masterList_.append(elist3_)

			tlist2_ = []
			tlist2_.append('HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20_v1') # path
			tlist2_.append('AND') # AND or OR of the following filters
			tlist2_.append('hltPFTau20TrackLooseIso') # filter
			tlist2_.append('hltOverlapFilterIsoEle22WP75GsfLooseIsoPFTau20') # filter
			self.tau_masterList_.append(tlist2_)


			#### Spring15MC path : Ele32 #####

			elist4_ = []
			elist4_.append('HLT_Ele32_eta2p1_WP75_Gsf_v1') # path
			elist4_.append('AND') # AND or OR of the following filters
			elist4_.append('hltEle32WP75GsfTrackIsoFilter') # filter
			self.electron_masterList_.append(elist4_)

			#### Spring15MC path : Double Med Iso PF Tau 40 #####

			tlist3_ = []
			tlist3_.append('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v1') # path
			tlist3_.append('AND') # AND or OR of the following filters
			tlist3_.append('hltDoublePFTau40TrackPt1MediumIsolationDz02Reg') # filter
			self.tau_masterList_.append(tlist3_)

			#########################################################		
			# HLT paths and filters for Spring15 MC   -- END		#
			#########################################################

		if(self.sampleData_.ProductionInfo == 'Spring15MCminiAODv2'):
			#########################################################		
			# HLT paths and filters for Spring15MCminiAODv2   -- START		#
			#########################################################
			print '******** SETTING TRIGGER INFO FOR ', self.sampleData_.ProductionInfo
			####  Spring15MCminiAODv2 path : Mu23+Ele12 #####

			mlist1_ = []
			mlist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') # path
			mlist1_.append('AND') # AND or OR of the following filters
			mlist1_.append('hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23') # filter
			self.muon_masterList_.append(mlist1_)

			elist1_ = []
			elist1_.append('HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') # path
			elist1_.append('AND') # AND or OR of the following filters
			elist1_.append('hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist1_)

			#### Spring15MCminiAODv2 path : Mu8+Ele23 #####

			mlist2_ = []
			mlist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*') # path
			mlist2_.append('AND') # AND or OR of the following filters
			mlist2_.append('hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8') # filter
			self.muon_masterList_.append(mlist2_)

			elist2_ = []
			elist2_.append('HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*') # path
			elist2_.append('AND') # AND or OR of the following filters
			elist2_.append('hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist2_)

			#### Spring15MCminiAODv2 path : Iso Mu 24 #####

			mlist3_ = []
			mlist3_.append('HLT_IsoMu24_eta2p1_v*') # path
			mlist3_.append('AND') # AND or OR of the following filters
			mlist3_.append('hltL3crIsoL1sMu20Eta2p1L1f0L2f10QL3f24QL3trkIsoFiltered0p09') # filter
			self.muon_masterList_.append(mlist3_)

			#### Spring15MCminiAODv2 path : Iso Mu 27 #####

			mlist4_ = []
			mlist4_.append('HLT_IsoMu27_v*') # path
			mlist4_.append('AND') # AND or OR of the following filters
			mlist4_.append('hltL3crIsoL1sMu25L1f0L2f10QL3f27QL3trkIsoFiltered0p09') # filter
			self.muon_masterList_.append(mlist4_)


			#### Spring15MCminiAODv2 path : Iso Mu 17 PF tau 20 #####

			mlist5_ = []
			mlist5_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v*') # path
			mlist5_.append('AND') # AND or OR of the following filters
			mlist5_.append('hltL3crIsoL1sMu16erTauJet20erL1f0L2f10QL3f17QL3trkIsoFiltered0p09') # filter
			mlist5_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
			self.muon_masterList_.append(mlist5_)

			tlist1_ = []
			tlist1_.append('HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v*') # path
			tlist1_.append('AND') # AND or OR of the following filters
			tlist1_.append('hltPFTau20TrackLooseIsoAgainstMuon') # filter
			tlist1_.append('hltOverlapFilterIsoMu17LooseIsoPFTau20') # filter
			self.tau_masterList_.append(tlist1_)

			#### Spring15MCminiAODv2 path : Ele22 PF tau 20 #####

			elist3_ = []
			elist3_.append('HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20_v*') # path
			elist3_.append('AND') # AND or OR of the following filters
			elist3_.append('hltEle22WP75L1IsoEG20erTau20erGsfTrackIsoFilter') # filter
			elist3_.append('hltOverlapFilterIsoEle22WP75GsfLooseIsoPFTau20') # filter
			self.electron_masterList_.append(elist3_)

			tlist2_ = []
			tlist2_.append('HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20_v*') # path
			tlist2_.append('AND') # AND or OR of the following filters
			tlist2_.append('hltPFTau20TrackLooseIso') # filter
			tlist2_.append('hltOverlapFilterIsoEle22WP75GsfLooseIsoPFTau20') # filter
			self.tau_masterList_.append(tlist2_)


			#### Spring15MCminiAODv2 path : Ele32 #####

			elist4_ = []
			elist4_.append('HLT_Ele32_eta2p1_WP75_Gsf_v*') # path
			elist4_.append('AND') # AND or OR of the following filters
			elist4_.append('hltEle32WP75GsfTrackIsoFilter') # filter
			self.electron_masterList_.append(elist4_)

			#### Spring15MCminiAODv2 path : Double Med Iso PF Tau 40 #####

			tlist3_ = []
			tlist3_.append('HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v*') # path
			tlist3_.append('AND') # AND or OR of the following filters
			tlist3_.append('hltDoublePFTau40TrackPt1MediumIsolationDz02Reg') # filter
			self.tau_masterList_.append(tlist3_)

			#### Spring15MCminiAODv2 path : Iso Mu 17 ##### 

			mlist6_ = []
			mlist6_.append('HLT_IsoMu17_eta2p1_v*') # path
			mlist6_.append('AND') # AND or OR of the following filters
			mlist6_.append('hltL3crIsoL1sSingleMu16erL1f0L2f10QL3f17QL3trkIsoFiltered0p09') # filter
			self.muon_masterList_.append(mlist6_)

			#### Spring15MCminiAODv2 path : Ele22 ##### 

			elist5_ = []
			elist5_.append('HLT_Ele22_eta2p1_WP75_Gsf_v*') # path
			elist5_.append('AND') # AND or OR of the following filters
			elist5_.append('hltSingleEle22WP75GsfTrackIsoFilter') # filter
			self.electron_masterList_.append(elist5_)


			#########################################################		
			# HLT paths and filters for Spring15MCminiAODv2 MC   -- END		#
			#########################################################


		if(self.sampleData_.ProductionInfo == 'Fall15MCminiAOD'):
			#########################################################		
			# HLT paths and filters for Fall15MCminiAOD   -- START		#
			#########################################################
			print '******** SETTING TRIGGER INFO FOR ', self.sampleData_.ProductionInfo
			####  Fall15MCminiAOD path : Mu17+Ele12 #####

			mlist1_ = []
			mlist1_.append('HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') # path
			mlist1_.append('AND') # AND or OR of the following filters
			mlist1_.append('hltMu17TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered17') # filter
			self.muon_masterList_.append(mlist1_)

			elist1_ = []
			elist1_.append('HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*') # path
			elist1_.append('AND') # AND or OR of the following filters
			elist1_.append('hltMu17TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist1_)

			# #### Fall15MCminiAOD path : Mu8+Ele17 #####

			mlist2_ = []
			mlist2_.append('HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*') # path
			mlist2_.append('AND') # AND or OR of the following filters
			mlist2_.append('hltMu8TrkIsoVVLEle17CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8') # filter
			self.muon_masterList_.append(mlist2_)

			elist2_ = []
			elist2_.append('HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*') # path
			elist2_.append('AND') # AND or OR of the following filters
			elist2_.append('hltMu8TrkIsoVVLEle17CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter') # filter
			self.electron_masterList_.append(elist2_)

			# #### Fall15MCminiAOD path : Iso Mu 18 #####

			mlist3_ = []
			mlist3_.append('HLT_IsoMu18_v*') # path
			mlist3_.append('AND') # AND or OR of the following filters
			mlist3_.append('hltL3crIsoL1sMu16L1f0L2f10QL3f18QL3trkIsoFiltered0p09') # filter
			self.muon_masterList_.append(mlist3_)		


			# #### Fall15MCminiAOD path : Ele23 #####

			elist4_ = []
			elist4_.append('HLT_Ele23_WPLoose_Gsf_v*') # path
			elist4_.append('AND') # AND or OR of the following filters
			elist4_.append('hltEle23WPLooseGsfTrackIsoFilter') # filter
			self.electron_masterList_.append(elist4_)


			# #### Fall15MCminiAOD path : Double Med Iso PF Tau 35 #####

			tlist3_ = []
			tlist3_.append('HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*') # path
			tlist3_.append('AND') # AND or OR of the following filters
			tlist3_.append('hltDoublePFTau35TrackPt1MediumIsolationDz02Reg') # filter
			self.tau_masterList_.append(tlist3_)

			#########################################################		
			# HLT paths and filters for Fall15MCminiAOD MC   -- END		#
			#########################################################



		####################################################################################################
		# form the actual vsrting to be passed  -- electrons

		self.electronTriggerPathsAndFilters = cms.vstring()

		for alist in self.electron_masterList_:
			self.electronTriggerPathsAndFilters.append(doubleHyphen_string_concatonator(alist))

		####################################################################################################
		# form the actual vsrting to be passed  -- muons

		self.muonTriggerPathsAndFilters = cms.vstring()

		for alist in self.muon_masterList_:
			self.muonTriggerPathsAndFilters.append(doubleHyphen_string_concatonator(alist))

		####################################################################################################
		# form the actual vsrting to be passed  -- taus

		self.tauTriggerPathsAndFilters = cms.vstring()

		for alist in self.tau_masterList_:
			self.tauTriggerPathsAndFilters.append(doubleHyphen_string_concatonator(alist))

	def printSampleInfo(self):
		print self.sampleData_
		return

	def printTriggerInfo(self):
		print 'e legs', self.electronTriggerPathsAndFilters
		print 'mu legs', self.muonTriggerPathsAndFilters
		print 'tau legs', self.tauTriggerPathsAndFilters
		return


####################################################################################################
####################################################################################################
####################################################################################################




