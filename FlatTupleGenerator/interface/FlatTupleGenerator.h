// -*- C++ -*-
// really simple flatTuple producer
// Package:    FlatTupleGenerator
// Class:      FlatTupleGenerator
//
//
// Description: [EDAnalyzer that creates FlatTuples for DavisRunIITauTau analysis using Ntuple as input]
//
//
// Original Author:  shalhout shalhout
//         Created:  Tue Jun  4 04:25:53 CDT 2015
// 


#ifndef DavisRunIITauTau_FlatTupleGenerator_FlatTupleGenerator_h
#define DavisRunIITauTau_FlatTupleGenerator_FlatTupleGenerator_h




//  include files
#include <memory>
#include <string>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "Math/GenVector/VectorUtil.h"
#include <math.h>

// FWCore include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


// Custom object include files


#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleGenParticle.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DavisRunIITauTau/FlatTupleGenerator/interface/PairRankHelper.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "DavisRunIITauTau/FlatTupleGenerator/interface/LeptonFlatTupleCutHelper.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"


using namespace edm;
using namespace std;
typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<edm::InputTag> vInputTag;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;

class FlatTupleGenerator : public edm::EDAnalyzer
{
public:
	explicit FlatTupleGenerator(const edm::ParameterSet&);
	~FlatTupleGenerator();

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
	virtual void beginJob() ;
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void endJob() ;

	virtual void beginRun(edm::Run const&, edm::EventSetup const&);
	virtual void endRun(edm::Run const&, edm::EventSetup const&);
	virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
	virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
	virtual void reInit();

	// ----------member data ---------------------------


  
  
	/* MASTER VALUE FOR Ntuples std::pair flattening, and generating branches on-the-fly based on
	   FlatTupleGenerator/python/FlatTupleConfig_cfi.py   */
  
  	static const int THE_MAX = 20; /* do we ever really want to keep >20 tauIDs, b-taggers etc? */

	/* the input collection sources */

	edm::InputTag pairSrc_;
	edm::InputTag indepSrc_;
	std::string NAME_;  // use TauESNom, TauESUp, TauESDown, etc.
	edm::ParameterSet EventCutSrc_;
	std::vector<edm::ParameterSet> LeptonCutVecSrc_;



	/* the parameters to be read from EventCutSrc_ in FlatTupleConfig_cfi.py */

	std::vector<std::string> tauIDsToKeep;
	std::vector<std::string> triggerSummaryChecks;
	bool keepOS;
	bool keepSS;
	bool keepTauEsNominal;
	bool keepTauEsUp; 
	bool keepTauEsDown; 
	bool rankByPtSum;
	bool rankByIsolation;
	std::string electronIsolationForRank;
	std::string muonIsolationForRank;
	std::string tauIDisolationForRank;

	std::string electronIsolationForRelIsoBranch; 
	std::string muonIsolationForRelIsoBranch;
	std::string tauIsolationForRelIsoBranch;
	std::string vetoElectronIsolationForRelIsoBranch; 
	std::string vetoMuonIsolationForRelIsoBranch;

	/* the lepton cut helper object */
	LeptonFlatTupleCutHelper LeptonCutHelper;

	/* the TTree */
	TTree * FlatTuple;

	/* the leaves : Idea here is to be as flat as possible - stick to simple objects */

	std::string treeInfoString;              /* this will be filled as NAME_, should be something like TauEsNominal etc. */
	std::vector<std::string> AppliedLepCuts; /* the cuts applied to the current tree */
	unsigned int  run ;				/* from mini-AOD, the run number */
	unsigned int  luminosityBlock ; /* from mini-AOD, the luminosityBlock */
	unsigned int  event ;     		/* from mini-AOD, the event number */
	bool  isRealData ;       		/* from mini-AOD, 1 if data, 0 if MC (be careful of embedded samples!) */
	unsigned int  pairRank ; 		/* since each event can have multiple TauTau pairs; zero is the best rank */	
	int isOsPair;		  			/* 1 if sign(leg1)!=sign(leg2), 0 otherwise */
	int CandidateEventType;  		/* see TupleObjects/interface/TupleCandidateEventTypes.h */
	float TauEsNumberSigmasShifted; /* number of sigmas the tau ES was shifted in this event */
	double SVMass; 		  			/* SVFit Mass could have used pfMET or mvaMET, see TupleConfigurations/python/ConfigNtupleContent_cfi.py */
	double VISMass; 	  			/* the visible mass  */
	double MTmvaMET_leg1; 			/* MT using mva MET & leg1 */
	double MTmvaMET_leg2; 			/* MT using mva MET & leg2 */
	double MTpfMET_leg1;  			/* MT using pf MET & leg1 */ 	
	double MTpfMET_leg2;  			/* MT using pf MET & leg2 */
	double mvaMET;		  			/* the MVA MET   - computed pairwise for leg1 and leg2 */
	double mvaMETphi;	  			/* the MVA MET phi - computed pairwise for leg1 and leg2 */	
	double mvaMET_cov00;  			/* MVA MET significnace matrix element 00 */
	double mvaMET_cov01;  			/* MVA MET significnace matrix element 01 */	
	double mvaMET_cov10;  			/* MVA MET significnace matrix element 10 */	
	double mvaMET_cov11;  			/* MVA MET significnace matrix element 11 */	  
	double pfMET;					/* the PF MET   - computed pairwise for leg1 and leg2 */
	double pfMETphi;				/* the PF MET phi  - computed pairwise for leg1 and leg2 */
	double pfMET_cov00; 			/* PF MET significnace matrix element 00 */
	double pfMET_cov01; 			/* PF MET significnace matrix element 01 */
	double pfMET_cov10; 			/* PF MET significnace matrix element 10 */
	double pfMET_cov11; 			/* PF MET significnace matrix element 11 */

	int leg1_leptonType, leg2_leptonType; 			/* the lepton flavor see TupleObjects/interface/TupleLeptonTypes.h */
	double leg1_pt, leg1_eta, leg1_phi, leg1_M; 	/* the reco 4-vector components of leg1 */
	double leg2_pt, leg2_eta, leg2_phi, leg2_M; 	/* the reco 4-vector components of leg2 */
	double leg1_gen_pt, leg1_gen_eta, leg1_gen_phi, leg1_gen_M; 			/* the PAT embedded gen-match object 4-vector components for leg1 */
	double leg2_gen_pt, leg2_gen_eta, leg2_gen_phi, leg2_gen_M; 			/* the PAT embedded gen-match object 4-vector components for leg2 */
	double leg1_genMother_pt, leg1_genMother_eta, leg1_genMother_phi, leg1_genMother_M; 	/* the PAT embedded gen-match object's mother's 4-vector components for leg1 */
	double leg2_genMother_pt, leg2_genMother_eta, leg2_genMother_phi, leg2_genMother_M; 	/* the PAT embedded gen-match object's mother's 4-vector components for leg2 */
	double leg1_genJet_pt, leg1_genJet_eta, leg1_genJet_phi, leg1_genJet_M; 	/* the PAT embedded gen-Jet object's 4-vector components for leg1 */
	double leg2_genJet_pt, leg2_genJet_eta, leg2_genJet_phi, leg2_genJet_M; 	/* the PAT embedded gen-Jet object's 4-vector components for leg2 */
	float leg1_dz, leg2_dz;				  	/* lepton dz see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */	
	float leg1_dxy, leg2_dxy;			  	/* lepton dxy see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */	
	float leg1_EffectiveArea, leg2_EffectiveArea; /* the effective area, see CustomPatCollectionProducers/src/{Electron,Muon}Clones.cc */
	int leg1_charge, leg2_charge;			/* sign of the lepton */
	int leg1_PFpdgId, leg2_PFpdgId;			/* the PDG ID code assigned by the PF reconstruction */
	int leg1_GENpdgId, leg2_GENpdgId;		/* the PDG ID code of the PAT-embedded generator particle match */
	int leg1_GENMOTHERpdgId, leg2_GENMOTHERpdgId; /* the PDG ID code of the PAT-embedded generator particle match's mother */
	float leg1_IP, leg2_IP; 			/* IP CustomPatCollectionProducers/src/{Electron,Muon}Clones.cc */
	float leg1_IPerror, leg2_IPerror;	/* error on IP CustomPatCollectionProducers/src/{Electron,Muon}Clones.cc */
	float leg1_PUchargedHadronIso, leg2_PUchargedHadronIso; /* isolation related quantity see CustomPatCollectionProducers/src/LeptonRelativeIsolationTool.cc */
	float leg1_chargedHadronIso, leg2_chargedHadronIso;     /* isolation related quantity see CustomPatCollectionProducers/src/LeptonRelativeIsolationTool.cc */
	float leg1_neutralHadronIso, leg2_neutralHadronIso;     /* isolation related quantity see CustomPatCollectionProducers/src/LeptonRelativeIsolationTool.cc */
	float leg1_photonIso, leg2_photonIso;                   /* isolation related quantity see CustomPatCollectionProducers/src/LeptonRelativeIsolationTool.cc */
	float leg1_DepositR03ECal, leg2_DepositR03ECal;  /* muon isolationR03 quantity, see /CustomPatCollectionProducers/src/MuonClones.cc */
	float leg1_DepositR03Hcal, leg2_DepositR03Hcal;  /* muon isolationR03 quantity, see /CustomPatCollectionProducers/src/MuonClones.cc */
	float leg1_DepositR03TrackerOfficial, leg2_DepositR03TrackerOfficial; /* muon isolationR03 quantity, see /CustomPatCollectionProducers/src/MuonClones.cc */

	/* muon ID related quanties, see CustomPatCollectionProducers/src/MuonClones.cc */
	float leg1_isGlobalMuon, leg2_isGlobalMuon;
	float leg1_isGoodGlobalMuon, leg2_isGoodGlobalMuon;
	float leg1_passesMediumMuonId, leg2_passesMediumMuonId;
	float leg1_isLooseMuon, leg2_isLooseMuon;
	float leg1_isPFMuon, leg2_isPFMuon;
	float leg1_isSoftMuon, leg2_isSoftMuon;
	float leg1_isTightMuon, leg2_isTightMuon;
	float leg1_isTrackerMuon, leg2_isTrackerMuon;
	float leg1_muonCombQualChi2LocalPosition, leg2_muonCombQualChi2LocalPosition;
	float leg1_muonCombQualTrkKink, leg2_muonCombQualTrkKink;
	float leg1_muonGlobalTrackNormChi2, leg2_muonGlobalTrackNormChi2;
	float leg1_muonInnerTrkValidFraction, leg2_muonInnerTrkValidFraction;
	float leg1_muonSegmentCompatibility, leg2_muonSegmentCompatibility;



	/* electron ID related quanties, see CustomPatCollectionProducers/src/ElectronClones.cc */

	float leg1_raw_electronMVA, leg2_raw_electronMVA;
	float leg1_passFail_electronMVA, leg2_passFail_electronMVA;
	float leg1_SuperClusterEta, leg2_SuperClusterEta;
	float leg1_hadronicOverEm, leg2_hadronicOverEm;
	float leg1_isEB, leg2_isEB;
	float leg1_isEBEEGap, leg2_isEBEEGap;
	float leg1_isEBEtaGap, leg2_isEBEtaGap;
	float leg1_isEBPhiGap, leg2_isEBPhiGap;
	float leg1_isEE, leg2_isEE;
	float leg1_isEEDeeGap, leg2_isEEDeeGap;
	float leg1_isEERingGap, leg2_isEERingGap;
	float leg1_deltaEtaSuperClusterTrackAtVtx, leg2_deltaEtaSuperClusterTrackAtVtx;
	float leg1_deltaPhiSuperClusterTrackAtVtx, leg2_deltaPhiSuperClusterTrackAtVtx;
	float leg1_sigmaEtaEta, leg2_sigmaEtaEta;
	float leg1_sigmaIetaIeta, leg2_sigmaIetaIeta;
	float leg1_sigmaIphiIphi, leg2_sigmaIphiIphi;
	float leg1_numberOfMissingInnerHits, leg2_numberOfMissingInnerHits;
	float leg1_numberOfMissingOuterHits, leg2_numberOfMissingOuterHits;
	float leg1_numberOfTrackHits, leg2_numberOfTrackHits;
	float leg1_passConversionVeto, leg2_passConversionVeto;

	/* tau related Info NEED TO ADD DOCUMENTATION TO WIKI*/
	float leg1_numStrips, leg2_numStrips;
	float leg1_numHadrons, leg2_numHadrons;
	float leg1_tauIDs[THE_MAX]; 		/* leg 1 tau IDs */
	float leg2_tauIDs[THE_MAX]; 		/* leg 2 tau IDs */

	/* trigger summmary holders, will need a bit more work to get stuff from the NtupleTrigObject 
	vectors themselves */

	float leg1_GoodForHLTPath[THE_MAX];	
	float leg2_GoodForHLTPath[THE_MAX];	

	/* isolation branch */

	float leg1_RelIso, leg2_RelIso; /* relative isolation - value depends on the FlatTupleConfig_cfi */

	/* extra electron and muon parameters (these are for the vetoes) */
	std::vector<int> veto_leptonType; 			/* vector containing flavor code */
	std::vector<double> veto_pt; 				/* vectors of 4-vector components */
	std::vector<double> veto_eta; 
	std::vector<double> veto_phi;
	std::vector<double> veto_M; 
	std::vector<float> veto_dxy;  /* lepton dxy see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */
	std::vector<float> veto_dz;	  /* lepton dz see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */
	std::vector<float> veto_RelIso;
	std::vector<float> veto_passesMediumMuonId;
	std::vector<float> veto_rawElectronMVA;

	int vertex_NumberOfGoodVertices; /* total number of good PV, see ConfigTupleOfflineVertices_cfi */ 
	double vertex_NDOF;   				 /* the primary vertex's # of degrees of freedom (not an int, so is it CHI2/NDOF?) */
	double vertex_CHI2;   				 /* the primary vertex's # of degrees of freedom */
	double vertex_positionRho;		 /* the primary vertex's position.Rho()  */ 	
	double vertex_positionX;		 /* the primary vertex's position.x()  */ 	
	double vertex_positionY;		 /* the primary vertex's position.y()  */ 
	double vertex_positionZ;		 /* the primary vertex's position.z() 		 */ 
	double vertex_positionTheta;	 /* the primary vertex's position.theta()  */ 	
	double vertex_positionEta;		 /* the primary vertex's position.eta()  */ 	
	double vertex_positionPhi;		 /* the primary vertex's position.phi()  */ 	



};  


//define this as a plug-in
DEFINE_FWK_MODULE(FlatTupleGenerator);
#endif
