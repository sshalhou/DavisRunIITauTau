import FWCore.ParameterSet.Config as cms
from DavisRunIITauTau.TupleConfigurations.ConfigNtupleContent_cfi import *

# class PairWiseMetHelper will:
#		 run SingleLeptonProducers
# 		 keep lists of single lepton collections
#        for H candidate pair lists (collection1, collection2)
#        run MVA met for lepton pairs
#        and keep lists of collection1, collection2, mva met12




class PairWiseMetHelper:
	def __init__(self,theProcess):

		self.process = theProcess

		# the maximum number of leptons (not pairs!) to consider
		# note this will result in many, many empty collections if set too large
		# and may cause missed pairings if set too low 

		self.max_leptons = 7

		# the lepton collection sources (cange defaults with setLeptonSources)

		self.electronSrc 		= 'filteredCustomElectrons::Ntuple'
		self.muonSrc 			= 'filteredCustomMuons::Ntuple'
		self.tauEsNominalSrc 	= 'filteredCustomTausEsNominal::Ntuple'
		self.tauEsUpSrc 		= 'filteredCustomTausEsUp::Ntuple'
		self.tauEsDownSrc 		= 'filteredCustomTausEsDown::Ntuple'

		# lists containing single lepton collections

		self.electronList = []
		self.muonList = []
		self.tauEsNominalList = []
		self.tauEsUpList = []
		self.tauEsDownList = []
		self.LepPairAndMetList = []

		# VInputTag for holding TupleCandidateEvents

		self.tupleCandidateEvents = cms.VInputTag()

	def runSingleLeptonProducers(self,p):
		singlePatLeptons = cms.Sequence()

		# the single electrons
		for i in range(0,self.max_leptons+1):
			moduleName = "singleElectron"+str(i)
			module = cms.EDProducer('SinglePatElectronProducer' ,
   					 electronSrc =cms.InputTag(self.electronSrc),
				     INDEX = cms.uint32(i),
				     NAME=cms.string(moduleName))
			setattr(self.process, moduleName, module)
			singlePatLeptons += module
			self.electronList.append(moduleName+':'+moduleName+':Ntuple')

		# the single muons
		for i in range(0,self.max_leptons+1):
			moduleName = "singleMuon"+str(i)
			module = cms.EDProducer('SinglePatMuonProducer' ,
   					 muonSrc =cms.InputTag(self.muonSrc),
				     INDEX = cms.uint32(i),
				     NAME=cms.string(moduleName))
			setattr(self.process, moduleName, module)
			singlePatLeptons += module
			self.muonList.append(moduleName+':'+moduleName+':Ntuple')



		# the single taus Es Nominal
		for i in range(0,self.max_leptons+1):
			moduleName = "singleTauEsNominal"+str(i)
			module = cms.EDProducer('SinglePatTauProducer' ,
   					 tauSrc =cms.InputTag(self.tauEsNominalSrc),
				     INDEX = cms.uint32(i),
				     NAME=cms.string(moduleName))
			setattr(self.process, moduleName, module)
			singlePatLeptons += module
			self.tauEsNominalList.append(moduleName+':'+moduleName+':Ntuple')


		# the single taus Es Up
		if BUILD_TAU_ES_VARIANTS is True :
			for i in range(0,self.max_leptons+1):
				moduleName = "singleTauEsUp"+str(i)
				module = cms.EDProducer('SinglePatTauProducer' ,
	   					 tauSrc =cms.InputTag(self.tauEsUpSrc),
					     INDEX = cms.uint32(i),
					     NAME=cms.string(moduleName))
				setattr(self.process, moduleName, module)
				singlePatLeptons += module
				self.tauEsUpList.append(moduleName+':'+moduleName+':Ntuple')

		# the single taus Es Down
		if BUILD_TAU_ES_VARIANTS is True :
			for i in range(0,self.max_leptons+1):
				moduleName = "singleTauEsDown"+str(i)
				module = cms.EDProducer('SinglePatTauProducer' ,
	   					 tauSrc =cms.InputTag(self.tauEsDownSrc),
					     INDEX = cms.uint32(i),
					     NAME=cms.string(moduleName))
				setattr(self.process, moduleName, module)
				singlePatLeptons += module
				self.tauEsDownList.append(moduleName+':'+moduleName+':Ntuple')


		p *= singlePatLeptons
		return

	def initializeMVAmet(self,p):
		#print 'no init coded yet ... '
		# self.process.load('Configuration.StandardSequences.Services_cff')
		# self.process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
		# self.process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
		# from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
		# self.process.GlobalTag = GlobalTag(self.process.GlobalTag, 'auto:run2_mc', '')
		self.process.load("RecoJets.JetProducers.ak4PFJets_cfi")
		self.process.ak4PFJets.doAreaFastjet = cms.bool(True) 
		self.process.ak4PFJets.src = cms.InputTag("packedPFCandidates")
		from JetMETCorrections.Configuration.DefaultJEC_cff import ak4PFJetsL1FastL2L3
		self.process.load("RecoMET.METPUSubtraction.mvaPFMET_cff")
		#process.pfMVAMEt.srcLeptons = cms.VInputTag("slimmedElectrons")
		self.process.pfMVAMEt.srcPFCandidates = cms.InputTag("packedPFCandidates")
		self.process.pfMVAMEt.srcVertices = cms.InputTag("offlineSlimmedPrimaryVertices")
		self.process.pfMVAMEt.minNumLeptons = cms.int32(2) 
		self.process.puJetIdForPFMVAMEt.jec =  cms.string('AK4PF')
		#self.process.puJetIdForPFMVAMEt.jets = cms.InputTag("ak4PFJets")
		self.process.puJetIdForPFMVAMEt.vertexes = cms.InputTag("offlineSlimmedPrimaryVertices")
		self.process.puJetIdForPFMVAMEt.rho = cms.InputTag("fixedGridRhoFastjetAll")
		p *= self.process.ak4PFJets
		p *= self.process.calibratedAK4PFJetsForPFMVAMEt
		p *= self.process.puJetIdForPFMVAMEt
		return

	def setLeptonSources(self,electronSrc,muonSrc,tauEsNominalSrc,tauEsUpSrc,tauEsDownSrc):
		self.electronSrc_ = electronSrc
		self.muonSrc_ = muonSrc
		self.tauEsNominalSrc_ = tauEsNominalSrc
		self.tauEsUpSrc_ = tauEsUpSrc
		self.tauEsDownSrc_ = tauEsDownSrc
		return

	# def runMvaMetPrelims(self,p):
	# 	prelimSequence  = cms.Sequence()
	# 	self.process.calibratedAK4PFJetsForPFMVAMEt = calibratedAK4PFJetsForPFMVAMEt.clone()
	# 	self.process.puJetIdForPFMVAMEt = puJetIdForPFMVAMEt.clone()
	# 	prelimSequence += self.process.calibratedAK4PFJetsForPFMVAMEt
	# 	prelimSequence += self.process.puJetIdForPFMVAMEt
	# 	p *= prelimSequence
	# 	return

	def runPairWiseMets(self,p):
		pairMets = cms.Sequence()		
	
		# electron + electron
		if BUILD_ELECTRON_ELECTRON is True :
			for i in range(0, self.max_leptons+1):
				for j in range(i+1, self.max_leptons+1):
					moduleName = "mvaMetElectronxElectron"+str(i)+"x"+str(j)
					lep1SrcColl = cms.InputTag(self.electronList[i])
					lep2SrcColl = cms.InputTag(self.electronList[j])
					module = self.process.pfMVAMEt.clone(
							srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
					setattr(self.process, moduleName, module)
					self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
					pairMets += module


		# muon + muon
		if BUILD_MUON_MUON is True :
			for i in range(0, self.max_leptons+1):
				for j in range(i+1, self.max_leptons+1):
					moduleName = "mvaMetMuonxMuon"+str(i)+"x"+str(j)
					lep1SrcColl = cms.InputTag(self.muonList[i])
					lep2SrcColl = cms.InputTag(self.muonList[j])
					module = self.process.pfMVAMEt.clone(
							srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
					setattr(self.process, moduleName, module)
					self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
					pairMets += module


		# tau Es nominal + tau Es nominal
		if BUILD_TAU_TAU is True :
			for i in range(0, self.max_leptons+1):
				for j in range(i+1, self.max_leptons+1):
					moduleName = "mvaMetTauEsNominalxTauEsNominal"+str(i)+"x"+str(j)
					lep1SrcColl = cms.InputTag(self.tauEsNominalList[i])
					lep2SrcColl = cms.InputTag(self.tauEsNominalList[j])
					module = self.process.pfMVAMEt.clone(
							srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
					setattr(self.process, moduleName, module)
					self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
					pairMets += module


		# tau Es Up + tau Es Up
		if BUILD_TAU_TAU is True :
			if BUILD_TAU_ES_VARIANTS is True :
				for i in range(0, self.max_leptons+1):
					for j in range(i+1, self.max_leptons+1):
						moduleName = "mvaMetTauEsUpxTauEsUp"+str(i)+"x"+str(j)
						lep1SrcColl = cms.InputTag(self.tauEsUpList[i])
						lep2SrcColl = cms.InputTag(self.tauEsUpList[j])
						module = self.process.pfMVAMEt.clone(
								srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
						setattr(self.process, moduleName, module)
						self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
						pairMets += module

		# tau Es Down + tau Es Down
		if BUILD_TAU_TAU is True :
			if BUILD_TAU_ES_VARIANTS is True :
				for i in range(0, self.max_leptons+1):
					for j in range(i+1, self.max_leptons+1):
						moduleName = "mvaMetTauEsDownxTauEsDown"+str(i)+"x"+str(j)
						lep1SrcColl = cms.InputTag(self.tauEsDownList[i])
						lep2SrcColl = cms.InputTag(self.tauEsDownList[j])
						module = self.process.pfMVAMEt.clone(
								srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
						setattr(self.process, moduleName, module)
						self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
						pairMets += module

		# electron + tau Es nominal
		if BUILD_ELECTRON_TAU is True :
			for i in range(0, self.max_leptons+1):
				for j in range(0, self.max_leptons+1):
					moduleName = "mvaMetElectronxTauEsNominal"+str(i)+"x"+str(j)
					lep1SrcColl = cms.InputTag(self.electronList[i])
					lep2SrcColl = cms.InputTag(self.tauEsNominalList[j])
					module = self.process.pfMVAMEt.clone(
							srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
					setattr(self.process, moduleName, module)
					self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
					pairMets += module

		# electron + tau Es Up
		if BUILD_ELECTRON_TAU is True :
			if BUILD_TAU_ES_VARIANTS is True:
				for i in range(0, self.max_leptons+1):
					for j in range(0, self.max_leptons+1):
						moduleName = "mvaMetElectronxTauEsUp"+str(i)+"x"+str(j)
						lep1SrcColl = cms.InputTag(self.electronList[i])
						lep2SrcColl = cms.InputTag(self.tauEsUpList[j])
						module = self.process.pfMVAMEt.clone(
								srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
						setattr(self.process, moduleName, module)
						self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
						pairMets += module

		# electron + tau Es Down
		if BUILD_ELECTRON_TAU is True :
			if BUILD_TAU_ES_VARIANTS is True:		
				for i in range(0, self.max_leptons+1):
					for j in range(0, self.max_leptons+1):
						moduleName = "mvaMetElectronxTauEsDown"+str(i)+"x"+str(j)
						lep1SrcColl = cms.InputTag(self.electronList[i])
						lep2SrcColl = cms.InputTag(self.tauEsDownList[j])
						module = self.process.pfMVAMEt.clone(
								srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
						setattr(self.process, moduleName, module)
						self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
						pairMets += module

		# muon + tau Es nominal
		if BUILD_MUON_TAU is True :
			for i in range(0, self.max_leptons+1):
				for j in range(0, self.max_leptons+1):
					moduleName = "mvaMetMuonxTauEsNominal"+str(i)+"x"+str(j)
					lep1SrcColl = cms.InputTag(self.muonList[i])
					lep2SrcColl = cms.InputTag(self.tauEsNominalList[j])
					module = self.process.pfMVAMEt.clone(
							srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
					setattr(self.process, moduleName, module)
					self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
					pairMets += module

		# muon + tau Es Up
		if BUILD_MUON_TAU is True :
			if BUILD_TAU_ES_VARIANTS is True :
				for i in range(0, self.max_leptons+1):
					for j in range(0, self.max_leptons+1):
						moduleName = "mvaMetMuonxTauEsUp"+str(i)+"x"+str(j)
						lep1SrcColl = cms.InputTag(self.muonList[i])
						lep2SrcColl = cms.InputTag(self.tauEsUpList[j])
						module = self.process.pfMVAMEt.clone(
								srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
						setattr(self.process, moduleName, module)
						self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
						pairMets += module

		# muon + tau Es Down
		if BUILD_MUON_TAU is True :
			if BUILD_TAU_ES_VARIANTS is True :
				for i in range(0, self.max_leptons+1):
					for j in range(0, self.max_leptons+1):
						moduleName = "mvaMetMuonxTauEsDown"+str(i)+"x"+str(j)
						lep1SrcColl = cms.InputTag(self.muonList[i])
						lep2SrcColl = cms.InputTag(self.tauEsDownList[j])
						module = self.process.pfMVAMEt.clone(
								srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
						setattr(self.process, moduleName, module)
						self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+':Ntuple'),str(i)+"x"+str(j)])
						pairMets += module

		p *= pairMets
		return

	def run_pairMaker(self,p):
		pairMaker = cms.Sequence()
		for leplepmet in self.LepPairAndMetList:
			print leplepmet
			# figure out the correct sources
			tauSrc_ = cms.InputTag('')
			electronSrc_ = cms.InputTag('')
			muonSrc_ = cms.InputTag('')
			second_tauSrc_ = cms.InputTag('')
			second_electronSrc_ = cms.InputTag('')
			second_muonSrc_ = cms.InputTag('')			
			pairName = ''
			for k in range(0, len(leplepmet)-1):
				if 'singleMuon' in str(leplepmet[k]) and 'singleMuon' not in str(muonSrc_):
					muonSrc_ = leplepmet[k]
					pairName = pairName + 'Muon'
				elif 'singleMuon' in str(leplepmet[k]) and 'singleMuon' in str(muonSrc_):
					second_muonSrc_ = leplepmet[k]
					pairName = pairName + 'Muon'					
				elif 'singleElectron' in str(leplepmet[k]) and 'singleElectron' not in str(electronSrc_):
					electronSrc_ = leplepmet[k]
					pairName = pairName + 'Electron'
				elif 'singleElectron' in str(leplepmet[k]) and 'singleElectron' in str(electronSrc_):
					second_electronSrc_ = leplepmet[k]
					pairName = pairName + 'Electron'				


				elif 'singleTau' in str(leplepmet[k]) and 'singleTau' not in str(tauSrc_):
					tauSrc_ = leplepmet[k]
					pairName = pairName + 'Tau'					
					if 'TauEsNominal' in str(leplepmet[k]):
						pairName = pairName + 'EsNominal'					
					elif 'TauEsUp' in str(leplepmet[k]):
						pairName = pairName + 'EsUp'					
					elif 'TauEsDown' in str(leplepmet[k]):
						pairName = pairName + 'EsDown'	

				elif 'singleTau' in str(leplepmet[k]) and 'singleTau' in str(tauSrc_):
					second_tauSrc_ = leplepmet[k]
					pairName = pairName + 'Tau'					
					if 'TauEsNominal' in str(leplepmet[k]):
						pairName = pairName + 'EsNominal'					
					elif 'TauEsUp' in str(leplepmet[k]):
						pairName = pairName + 'EsUp'					
					elif 'TauEsDown' in str(leplepmet[k]):
						pairName = pairName + 'EsDown'	



			##############
			# print '***', leplepmet, '***'
			# print '--> muonSrc_', muonSrc_
			# print '--> 2nd muonSrc_', second_muonSrc_
			# print '--> electronSrc_', electronSrc_
			# print '--> 2nd electronSrc_', second_electronSrc_
			# print '--> tauSrc_', tauSrc_
			# print '--> 2nd tauSrc_', second_tauSrc_
			# print '--> metSrc_', leplepmet[2]
			##############


			#print leplepmet, '--->', pairName+leplepmet[3]
			moduleName = "TuplePair"+pairName+leplepmet[3]
			module = cms.EDProducer('TupleCandidateEventProducer' ,
							tauSrc = tauSrc_,
							electronSrc = electronSrc_,
							muonSrc = muonSrc_,
							second_tauSrc = second_tauSrc_,
							second_electronSrc = second_electronSrc_,
							second_muonSrc = second_muonSrc_,							
							pfMETSrc = cms.InputTag("slimmedMETs"),
							mvaMETSrc = leplepmet[2],
						    electronVetoSrc =cms.InputTag("filteredVetoElectrons","","Ntuple"),
						    muonVetoSrc = cms.InputTag("filteredVetoMuons","","Ntuple"),				
						    # should be small since don't want one of the pair in the veto list
						    # note : this is used for DR(leg1, leg2) >, and for overlap removal from the
						    # veto e and mu lists
						    vetoDeltaR = cms.double(0.1), 
							NAME=cms.string(moduleName),
						    doSVMass = cms.bool(COMPUTE_SVMASS),
						    useMVAMET = cms.bool(USE_MVAMET),
						    logMterm = cms.double(SVMASS_LOG_M),
						    svMassVerbose = cms.int32(SVMASS_VERBOSE),
						    sig00 = cms.InputTag("METSignificance:CovarianceMatrix00:Ntuple"),
						    sig10 = cms.InputTag("METSignificance:CovarianceMatrix10:Ntuple"),
						    sig01 = cms.InputTag("METSignificance:CovarianceMatrix01:Ntuple"),
						    sig11 = cms.InputTag("METSignificance:CovarianceMatrix11:Ntuple")
									)	
			setattr(self.process, moduleName, module)
			pairMaker += module
			self.tupleCandidateEvents.append(cms.InputTag(moduleName+":"+moduleName+":Ntuple"))		
		p *= pairMaker
		print self.tupleCandidateEvents
		return


	def writeToNtuple(self,p):
		pairWriter = cms.Sequence()
		moduleName = "NtupleEvent"
		module = cms.EDProducer('NtupleEventProducer' ,
				 tupleCandidateEventSrc = self.tupleCandidateEvents,
			     NAME=cms.string(moduleName))
		setattr(self.process, moduleName, module)
		pairWriter += module
		p *= pairWriter
		return

# process.TupleEventPair = cms.EDProducer('TupleCandidateEventProducer' ,
# 							tauSrc =cms.InputTag("singleTauEsNominal0","singleTauEsNominal0","Ntuple"),
# 							electronSrc =cms.InputTag("singleElectron0","singleElectron0","Ntuple"),
# 							muonSrc =cms.InputTag(''),
# 							pfMETSrc = cms.InputTag("slimmedMETs"),
# 							mvaMETSrc = cms.InputTag("mvaMetElectronxTauEsNominal0x0::Ntuple"),
# 						    electronVetoSrc =cms.InputTag("filteredVetoElectrons","","Ntuple"),
# 						    muonVetoSrc = cms.InputTag("filteredVetoMuons","","Ntuple"),				
# 						    # should be small since don't want one of the pair in the veto list
# 						    # note : this is used for DR(leg1, leg2) >, and for overlap removal from the
# 						    # veto e and mu lists
# 						    vetoDeltaR = cms.double(0.1), 
# 							NAME=cms.string("TuplePair"),
# 						    doSVMass = cms.bool(True),
# 						    useMVAMET = cms.bool(True),
# 						    logMterm = cms.double(2.),
# 						    svMassVerbose = cms.int32(1),
# 						    sig00 = cms.InputTag("METSignificance:CovarianceMatrix00:Ntuple"),
# 						    sig10 = cms.InputTag("METSignificance:CovarianceMatrix10:Ntuple"),
# 						    sig01 = cms.InputTag("METSignificance:CovarianceMatrix01:Ntuple"),
# 						    sig11 = cms.InputTag("METSignificance:CovarianceMatrix11:Ntuple")
# 									)										





class b_class_test:
	def __init__(self,theProcess):
		self.process = theProcess
		self.NAME = cms.string('LepCounts::Ntuple')
		# self.process.LepCounts = cms.EDProducer('PatLeptonCountContainerProducer',
		# 						electronSrc =cms.InputTag('filteredCustomElectrons::Ntuple'),
		# 						muonSrc =cms.InputTag('filteredCustomMuons::Ntuple'),
		# 						tauEsNominalSrc =cms.InputTag('filteredCustomTausEsNominal::Ntuple'),
		# 						tauEsUpSrc =cms.InputTag('filteredCustomTausEsUp::Ntuple'),
		# 						tauEsDownSrc =cms.InputTag('filteredCustomTausEsDown::Ntuple'),
		# 						NAME=self.NAME)
	def makeLepCount(self,p):
		#p *= self.process.LepCounts
		return

class a_class_test:
	def __init__(self,theProcess):
		self.process = theProcess
		self.process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
		self.process.printTree = cms.EDAnalyzer("ParticleListDrawer",
				maxEventsToPrint = cms.untracked.int32(-1),
				printVertex = cms.untracked.bool(False),
				src = cms.InputTag("prunedGenParticles"))
	def printMCinfo(self,p):
		p *= self.process.printTree	
		return