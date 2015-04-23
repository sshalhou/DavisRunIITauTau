import FWCore.ParameterSet.Config as cms

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

	def runSingleLeptonProducers(self,p):
		singlePatLeptons = cms.Sequence()

		# the single electrons
		for i in range(0,self.max_leptons):
			moduleName = "singleElectron"+str(i)
			module = cms.EDProducer('SinglePatElectronProducer' ,
   					 electronSrc =cms.InputTag(self.electronSrc),
				     INDEX = cms.uint32(i),
				     NAME=cms.string(moduleName))
			setattr(self.process, moduleName, module)
			singlePatLeptons += module
			self.electronList.append(moduleName+':'+moduleName+':Ntuple')

		# the single muons
		for i in range(0,self.max_leptons):
			moduleName = "singleMuon"+str(i)
			module = cms.EDProducer('SinglePatMuonProducer' ,
   					 muonSrc =cms.InputTag(self.muonSrc),
				     INDEX = cms.uint32(i),
				     NAME=cms.string(moduleName))
			setattr(self.process, moduleName, module)
			singlePatLeptons += module
			self.muonList.append(moduleName+':'+moduleName+':Ntuple')



		# the single taus Es Nominal
		for i in range(0,self.max_leptons):
			moduleName = "singleTauEsNominal"+str(i)
			module = cms.EDProducer('SinglePatTauProducer' ,
   					 tauSrc =cms.InputTag(self.tauEsNominalSrc),
				     INDEX = cms.uint32(i),
				     NAME=cms.string(moduleName))
			setattr(self.process, moduleName, module)
			singlePatLeptons += module
			self.tauEsNominalList.append(moduleName+':'+moduleName+':Ntuple')


		# the single taus Es Up
		for i in range(0,self.max_leptons):
			moduleName = "singleTauEsUp"+str(i)
			module = cms.EDProducer('SinglePatTauProducer' ,
   					 tauSrc =cms.InputTag(self.tauEsUpSrc),
				     INDEX = cms.uint32(i),
				     NAME=cms.string(moduleName))
			setattr(self.process, moduleName, module)
			singlePatLeptons += module
			self.tauEsUpList.append(moduleName+':'+moduleName+':Ntuple')

		# the single taus Es Down
		for i in range(0,self.max_leptons):
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
		print 'no init coded yet ... '
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
		# electron + tau Es nominal
		for i in range(0, self.max_leptons):
			for j in range(0, self.max_leptons):
				moduleName = "mvaMetElectronxTauEsNominal"+str(i)+"x"+str(j)
				lep1SrcColl = cms.InputTag(self.electronList[i])
				lep2SrcColl = cms.InputTag(self.tauEsNominalList[j])
				module = self.process.pfMVAMEt.clone(
						srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
				setattr(self.process, moduleName, module)
				self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+moduleName+':Ntuple')])
				pairMets += module

		# electron + tau Es Up
		for i in range(0, self.max_leptons):
			for j in range(0, self.max_leptons):
				moduleName = "mvaMetElectronxTauEsUp"+str(i)+"x"+str(j)
				lep1SrcColl = cms.InputTag(self.electronList[i])
				lep2SrcColl = cms.InputTag(self.tauEsUpList[j])
				module = self.process.pfMVAMEt.clone(
						srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
				setattr(self.process, moduleName, module)
				self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+moduleName+':Ntuple')])
				pairMets += module

		# electron + tau Es Down
		for i in range(0, self.max_leptons):
			for j in range(0, self.max_leptons):
				moduleName = "mvaMetElectronxTauEsDown"+str(i)+"x"+str(j)
				lep1SrcColl = cms.InputTag(self.electronList[i])
				lep2SrcColl = cms.InputTag(self.tauEsDownList[j])
				module = self.process.pfMVAMEt.clone(
						srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
				setattr(self.process, moduleName, module)
				self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+moduleName+':Ntuple')])
				pairMets += module


		# muon + tau Es nominal
		for i in range(0, self.max_leptons):
			for j in range(0, self.max_leptons):
				moduleName = "mvaMetMuonxTauEsNominal"+str(i)+"x"+str(j)
				lep1SrcColl = cms.InputTag(self.muonList[i])
				lep2SrcColl = cms.InputTag(self.tauEsNominalList[j])
				module = self.process.pfMVAMEt.clone(
						srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
				setattr(self.process, moduleName, module)
				self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+moduleName+':Ntuple')])
				pairMets += module

		# muon + tau Es Up
		for i in range(0, self.max_leptons):
			for j in range(0, self.max_leptons):
				moduleName = "mvaMetMuonxTauEsUp"+str(i)+"x"+str(j)
				lep1SrcColl = cms.InputTag(self.muonList[i])
				lep2SrcColl = cms.InputTag(self.tauEsUpList[j])
				module = self.process.pfMVAMEt.clone(
						srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
				setattr(self.process, moduleName, module)
				self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+moduleName+':Ntuple')])
				pairMets += module

		# muon + tau Es Down
		for i in range(0, self.max_leptons):
			for j in range(0, self.max_leptons):
				moduleName = "mvaMetMuonxTauEsDown"+str(i)+"x"+str(j)
				lep1SrcColl = cms.InputTag(self.muonList[i])
				lep2SrcColl = cms.InputTag(self.tauEsDownList[j])
				module = self.process.pfMVAMEt.clone(
						srcLeptons = cms.VInputTag(lep1SrcColl,lep2SrcColl))
				setattr(self.process, moduleName, module)
				self.LepPairAndMetList.append([lep1SrcColl,lep2SrcColl,cms.InputTag(moduleName+':'+moduleName+':Ntuple')])
				pairMets += module


		p *= pairMets
		print self.LepPairAndMetList[0]
		return





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