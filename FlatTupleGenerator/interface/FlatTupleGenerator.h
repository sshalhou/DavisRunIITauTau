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
#include "DavisRunIITauTau/FlatTupleGenerator/interface/JetHelper.h"
#include "DavisRunIITauTau/FlatTupleGenerator/interface/GenHelper.h"
#include "DavisRunIITauTau/FlatTupleGenerator/interface/GenMcMatchTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
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
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      virtual void reInit(); 
      virtual void handlePairIndepInfo(const edm::Event&, const edm::EventSetup&, NtuplePairIndependentInfo); 
      virtual void handleCurrentEventInfo(const edm::Event&, const edm::EventSetup&, NtupleEvent); 
      virtual void handleSVFitCall(const edm::Event&, const edm::EventSetup&, NtupleEvent); 
      virtual void handleLeg1AndLeg2Info(const edm::Event&, const edm::EventSetup&, NtupleEvent); 
      virtual void handleEffLeptonInfo(const edm::Event&, const edm::EventSetup&, NtupleEvent); 


// private:
// 	virtual void beginJob() ;
// 	virtual void analyze(const edm::Event&, const edm::EventSetup&);
// 	virtual void endJob() ;

// 	virtual void beginRun(edm::Run const&, edm::EventSetup const&);
// 	virtual void endRun(edm::Run const&, edm::EventSetup const&);
// 	virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
// 	virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
// 	virtual void reInit();

	JetHelper jethelper;
	GenHelper genhelper;
	
	// ----------member data ---------------------------


	/* the TTree */
	TTree * FlatTuple;

	/* MASTER VALUE FOR Ntuples std::pair flattening, and generating branches on-the-fly based on
	   FlatTupleGenerator/python/FlatTupleConfig_cfi.py   */
  
  	static const int THE_MAX = 30; /* do we ever really want to keep >30 tauIDs, b-taggers etc? */

	/* the input collection sources */

	edm::InputTag pairSrc_;
    edm::EDGetTokenT<edm::View< NtupleEvent > > pairToken_;


	edm::InputTag indepSrc_;
	edm::EDGetTokenT<edm::View< NtuplePairIndependentInfo > > indepToken_;
	
	std::string NAME_;  // use a descriptive name for your FlatTuple
	edm::ParameterSet EventCutSrc_;
	std::string TauEsVariantToKeep_;  // should be NOMINAL, UP or DOWN
	std::vector<edm::ParameterSet> LeptonCutVecSrc_;
	edm::ParameterSet svMassAtFlatTupleConfig_;	

	/* the parameters to be read from SVMassConfig in FlatTupleConfig_cfi.py */


	bool flatTuple_useMVAmet;
	bool flatTuple_recomputeSVmass;
	bool flatTuple_svMassVerbose;
	double flatTuple_logMterm;



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

	/* some info about the dataset */
	std::string DataSet; 	/* the dataset */
    int EventTotal; 		/* the number of events in the MC sample */ 
    std::string EventType;  /* description of the event, DATA, MC, EMBEDDED, etc. */
    std::string KeyName;    /* description of the sample as given during crab job */
    double CrossSection;    /* MC process cross section */
    double FilterEff;       /* gen level filter eff. (needed if any is applied) */
    double CodeVersion;     /* Davis code tracking version number */


	/* jet and b-jet cut strings */
	std::string jetIDcut;
	std::string BjetIDcut;
	double jetLeptonDRmin;

	/* the lepton cut helper object */
	LeptonFlatTupleCutHelper LeptonCutHelper;



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
	double SVTransverseMass; 		/* SVFit Transverse Mass could have used pfMET or mvaMET, see TupleConfigurations/python/ConfigNtupleContent_cfi.py */
	double VISMass; 	  			/* the visible mass  */
	double MTmvaMET_leg1; 			/* MT using mva MET & leg1 */
	double MTmvaMET_leg2; 			/* MT using mva MET & leg2 */
	double MTpfMET_leg1;  			/* MT using pf MET & leg1 */ 	
	double MTpfMET_leg2;  			/* MT using pf MET & leg2 */
	double MTpuppiMET_leg1;  		/* MT using puppi MET & leg1 */ 	
	double MTpuppiMET_leg2;  		/* MT using puppi MET & leg2 */
	double mvaMET;		  			/* the MVA MET   - computed pairwise for leg1 and leg2 */
	double mvaMETphi;	  			/* the MVA MET phi - computed pairwise for leg1 and leg2 */	
	double mvaMET_cov00;  			/* MVA MET significnace matrix element 00 */
	double mvaMET_cov01;  			/* MVA MET significnace matrix element 01 */	
	double mvaMET_cov10;  			/* MVA MET significnace matrix element 10 */	
	double mvaMET_cov11;  			/* MVA MET significnace matrix element 11 */	  
	double pfMET;					/* the PF MET   - type 1 corr */
	double pfMETphi;				/* the PF MET phi  - type 1 corr */
	double puppiMET;				/* the puppi MET   - type 1 corr(?) */
	double puppiMETphi;				/* the puppi MET phi  - type 1 corr(?) */

	double genMET;					/* the gen-level MET   */
	double genMETphi;				/* the gen-level MET phi  */

	double RAWpfMET;				/* the PF MET   - RAW */
	double RAWpfMETphi;				/* the PF MET phi  - RAW */
	double RAWpuppiMET;				/* the puppi MET   - RAW */
	double RAWpuppiMETphi;			/* the puppi MET phi  - RAW */


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
	float leg1_category_electronMVA, leg2_category_electronMVA;
	float leg1_passFail_electronMVA80, leg2_passFail_electronMVA80;
	float leg1_passFail_electronMVA90, leg2_passFail_electronMVA90;
    float leg1_passFail_electronCutBasedID,leg2_passFail_electronCutBasedID;
    float leg1_ooEmooP, leg2_ooEmooP;				
    float leg1_full5x5_sigmaIetaIeta, leg2_full5x5_sigmaIetaIeta;
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
	float leg1_ZimpactTau, leg2_ZimpactTau;
	float leg1_numStrips, leg2_numStrips;
	float leg1_dzTauVertex, leg2_dzTauVertex;
	float leg1_numHadrons, leg2_numHadrons;
	int leg1_decayMode, leg2_decayMode;
	float leg1_tauIDs[THE_MAX]; 		/* leg 1 tau IDs */
	float leg2_tauIDs[THE_MAX]; 		/* leg 2 tau IDs */

	/* trigger summmary holders, will need a bit more work to get stuff from the NtupleTrigObject 
	vectors themselves */

	float leg1_GoodForHLTPath[THE_MAX];	
	float leg2_GoodForHLTPath[THE_MAX];	

	/* isolation branch */

	float leg1_RelIso, leg2_RelIso; /* relative isolation - value depends on the FlatTupleConfig_cfi */



	/* parameters for EffLeptons */

	std::vector<int> effLep_leptonType; 			/* the lepton flavor see TupleObjects/std::vector<int>erface/TupleLeptonTypes.h */
	std::vector<double> effLep_pt, effLep_eta, effLep_phi, effLep_M; 	/* the reco 4-vector components of effLeptons */
	std::vector<double> effLep_gen_pt, effLep_gen_eta, effLep_gen_phi, effLep_gen_M; 			/* the PAT gen-match object 4-vector components for effLeptons */
	std::vector<double> effLep_genMother_pt, effLep_genMother_eta, effLep_genMother_phi, effLep_genMother_M; 	/* the PAT embedded gen-match object's mother's 4-vector components for effLeptons */
	std::vector<double> effLep_genJet_pt, effLep_genJet_eta, effLep_genJet_phi, effLep_genJet_M; 	/* the PAT embedded gen-Jet object's 4-vector components for effLep */
	std::vector<float> effLep_dz;				  	/* lepton dz see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */	
	std::vector<float> effLep_dxy;			  	/* lepton dxy see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */	
	std::vector<float> effLep_EffectiveArea; /* the effective area, see CustomPatCollectionProducers/src/{Electron,Muon}Clones.cc */
	std::vector<int> effLep_charge;			/* sign of the lepton */
	std::vector<int> effLep_PFpdgId;			/* the PDG ID code assigned by the PF reconstruction */
	std::vector<int> effLep_GENpdgId;		/* the PDG ID code of the PAT-embedded generator particle match */
	std::vector<int> effLep_GENMOTHERpdgId; /* the PDG ID code of the PAT-embedded generator particle match's mother */
	std::vector<float> effLep_IP; 			/* IP CustomPatCollectionProducers/src/{Electron,Muon}Clones.cc */
	std::vector<float> effLep_IPerror;	/* error on IP CustomPatCollectionProducers/src/{Electron,Muon}Clones.cc */
	std::vector<float> effLep_PUchargedHadronIso; /* isolation related quantity see CustomPatCollectionProducers/src/LeptonRelativeIsolationTool.cc */
	std::vector<float> effLep_chargedHadronIso;     /* isolation related quantity see CustomPatCollectionProducers/src/LeptonRelativeIsolationTool.cc */
	std::vector<float> effLep_neutralHadronIso;     /* isolation related quantity see CustomPatCollectionProducers/src/LeptonRelativeIsolationTool.cc */
	std::vector<float> effLep_photonIso;                   /* isolation related quantity see CustomPatCollectionProducers/src/LeptonRelativeIsolationTool.cc */
	std::vector<float> effLep_DepositR03ECal;  /* muon isolationR03 quantity, see /CustomPatCollectionProducers/src/MuonClones.cc */
	std::vector<float> effLep_DepositR03Hcal;  /* muon isolationR03 quantity, see /CustomPatCollectionProducers/src/MuonClones.cc */
	std::vector<float> effLep_DepositR03TrackerOfficial; /* muon isolationR03 quantity, see /CustomPatCollectionProducers/src/MuonClones.cc */
	std::vector<float> effLep_isGlobalMuon;
	std::vector<float> effLep_isGoodGlobalMuon;
	std::vector<float> effLep_passesMediumMuonId;
	std::vector<float> effLep_isLooseMuon;
	std::vector<float> effLep_isPFMuon;
	std::vector<float> effLep_isSoftMuon;
	std::vector<float> effLep_isTightMuon;
	std::vector<float> effLep_isTrackerMuon;
	std::vector<float> effLep_muonCombQualChi2LocalPosition;
	std::vector<float> effLep_muonCombQualTrkKink;
	std::vector<float> effLep_muonGlobalTrackNormChi2;
	std::vector<float> effLep_muonInnerTrkValidFraction;
	std::vector<float> effLep_muonSegmentCompatibility;
	std::vector<float> effLep_raw_electronMVA;
	std::vector<float> effLep_category_electronMVA;
	std::vector<float> effLep_passFail_electronMVA80;
	std::vector<float> effLep_passFail_electronMVA90;
	std::vector<float> effLep_passFail_electronCutBasedID;
    std::vector<float> effLep_ooEmooP;
    std::vector<float> effLep_full5x5_sigmaIetaIeta;
	std::vector<float> effLep_SuperClusterEta;
	std::vector<float> effLep_hadronicOverEm;
	std::vector<float> effLep_isEB;
	std::vector<float> effLep_isEBEEGap;
	std::vector<float> effLep_isEBEtaGap;
	std::vector<float> effLep_isEBPhiGap;
	std::vector<float> effLep_isEE;
	std::vector<float> effLep_isEEDeeGap;
	std::vector<float> effLep_isEERingGap;
	std::vector<float> effLep_deltaEtaSuperClusterTrackAtVtx;
	std::vector<float> effLep_deltaPhiSuperClusterTrackAtVtx;
	std::vector<float> effLep_sigmaEtaEta;
	std::vector<float> effLep_sigmaIetaIeta;
	std::vector<float> effLep_sigmaIphiIphi;
	std::vector<float> effLep_numberOfMissingInnerHits;
	std::vector<float> effLep_numberOfMissingOuterHits;
	std::vector<float> effLep_numberOfTrackHits;
	std::vector<float> effLep_passConversionVeto;
	std::vector<float> effLep_ZimpactTau;
	std::vector<float> effLep_numStrips;
	std::vector<float> effLep_dzTauVertex;
	std::vector<float> effLep_numHadrons;
	std::vector<int> effLep_decayMode;
	std::vector<float> effLep_RelIso; /* relative isolation - value depends on the FlatTupleConfig_cfi */


	std::vector< std::pair<int, std::vector<float> > > effLep_tauIDs;
	std::vector< std::pair<int, std::vector<float> > > effLep_GoodForHLTPath;




	/* extra electron and muon parameters (these are for the vetoes) */
	std::vector<int> veto_leptonType; 			/* vector containing flavor code */
	std::vector<double> veto_pt; 				/* vectors of 4-vector components */
	std::vector<double> veto_eta; 
	std::vector<double> veto_phi;
	std::vector<double> veto_M; 
	std::vector<int> veto_charge; 
	std::vector<float> veto_dxy;  /* lepton dxy see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */
	std::vector<float> veto_dz;	  /* lepton dz see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */
	std::vector<float> veto_RelIso;
	std::vector<float> veto_passesMediumMuonId;
	std::vector<float> veto_rawElectronMVA;
	std::vector<float> veto_categoryElectronMVA;
	std::vector<float> veto_passElectronMVA80;
	std::vector<float> veto_passElectronMVA90;
	std::vector<float> veto_passElectronCutBased;
	std::vector<float> veto_isTrackerGlobalPFMuon;

	/* primary vertex info */
	int NumberOfGoodVertices; /* total number of good PV, see ConfigTupleOfflineVertices_cfi */ 
	double vertex_NDOF;   				 /* the primary vertex's # of degrees of freedom (not an int, so is it CHI2/NDOF?) */
	double vertex_CHI2;   				 /* the primary vertex's # of degrees of freedom */
	double vertex_positionRho;		 /* the primary vertex's position.Rho()  */ 	
	double vertex_positionX;		 /* the primary vertex's position.x()  */ 	
	double vertex_positionY;		 /* the primary vertex's position.y()  */ 
	double vertex_positionZ;		 /* the primary vertex's position.z() 		 */ 
	double vertex_positionTheta;	 /* the primary vertex's position.theta()  */ 	
	double vertex_positionEta;		 /* the primary vertex's position.eta()  */ 	
	double vertex_positionPhi;		 /* the primary vertex's position.phi()  */ 	

	/* MET filters */

	bool HBHEIsoNoiseFilter;
	bool HBHENoiseFilter;
	bool CSCTightHaloFilter;
	bool goodVerticesFilter;
	bool eeBadScFilter;
	bool EcalDeadCellTriggerPrimitiveFilter;


	/* pileUp & other weight info */

	double puWeight;
	float NumPileupInt;
	float NumTruePileUpInt;
	double generatorEventWeight;
	int hepNUP;

	/* jet/b-jet summary info */

	int numberOfJets;  /* overall number of jets passing jet selection */
	int numberOfJets30;  /* overall number of jets passing jet selection + pT > 30 cut */
	int numberOfBJets;  /* overall number of btagged jets passing b-jet selection, can overlap with numberOfJets */

	/* Good Jets (passing JetCuts, ranked in Pt) info, note JEC info is to be added */
	std::vector<double> jets_pt; 				/* vectors of 4-vector components */
	std::vector<double> jets_eta; 
	std::vector<double> jets_phi;
	std::vector<double> jets_M; 
	std::vector<double> jets_PU_jetIdRaw; 
	std::vector<bool>   jets_PU_jetIdPassed; 
	std::vector<bool>   jets_PF_jetIdPassed;
	std::vector<float>  jets_defaultBtagAlgorithm_RawScore;                 /*  raw output of default (see ConfigNtupleContent_cfi.py) b-tag algo */
  	std::vector<bool>   jets_defaultBtagAlgorithm_isPassed;                 /*  pass-fail of default (see ConfigNtupleContent_cfi.py) b-tag algo after btagSF applied */
  	std::vector<int>    jets_PARTON_flavour;
  	std::vector<int>    jets_HADRON_flavour;

	/* Good B-tag Jets, [by design, will overlap with Good Jets!] 
	(passing bJetCuts, ranked in Pt) info, note JEC info is to be added */
	std::vector<double> bjets_pt; 											/* vectors of 4-vector components */
	std::vector<double> bjets_eta; 
	std::vector<double> bjets_phi;
	std::vector<double> bjets_M; 
	std::vector<double> bjets_PU_jetIdRaw; 
	std::vector<bool>   bjets_PU_jetIdPassed; 
	std::vector<bool>   bjets_PF_jetIdPassed;
	std::vector<float>  bjets_defaultBtagAlgorithm_RawScore;                 /*  raw output of default (see ConfigNtupleContent_cfi.py) b-tag algo */
  	std::vector<bool>   bjets_defaultBtagAlgorithm_isPassed;                 /*  pass-fail of default (see ConfigNtupleContent_cfi.py) b-tag algo after btagSF applied */
  	std::vector<int>    bjets_PARTON_flavour;
  	std::vector<int>    bjets_HADRON_flavour;

  	/* gen particles - kind of complicated, but we don't want custom objects in this code */

  	
  	std::vector <std::pair< int, int>> genParticle_pdgId;
  	std::vector <std::pair< int, int>> genParticle_status;
  	std::vector <std::pair< int, int>> genParticle_isPrompt;
  	std::vector <std::pair< int, int>> genParticle_isPromptFinalState;
  	std::vector <std::pair< int, int>> genParticle_isDirectPromptTauDecayProduct;
  	std::vector <std::pair< int, int>> genParticle_isDirectPromptTauDecayProductFinalState;


  	std::vector <std::pair< int, double>> genParticle_pt;
  	std::vector <std::pair< int, double>> genParticle_eta;
  	std::vector <std::pair< int, double>> genParticle_phi;
  	std::vector <std::pair< int, double>> genParticle_M;

  	std::vector <pair < int, int>> genDaughter_pdgId;
  	std::vector <pair < int, int>> genDaughter_status;
  	std::vector <std::pair< int, double>> genDaughter_pt;
  	std::vector <std::pair< int, double>> genDaughter_eta;
  	std::vector <std::pair< int, double>> genDaughter_phi;
  	std::vector <std::pair< int, double>> genDaughter_M;


  	std::vector <std::pair< int, int>> genMother_pdgId;
  	std::vector <std::pair< int, int>> genMother_status;
  	std::vector <std::pair< int, double>> genMother_pt;
  	std::vector <std::pair< int, double>> genMother_eta;
  	std::vector <std::pair< int, double>> genMother_phi;
  	std::vector <std::pair< int, double>> genMother_M;

  	// new gen level classification for leg 1 and 2 and effLeptons
  	// note this (along with Recoil corrections and MET Systematics are ONLY available
  	// at the FlatTuple level)
  	// note the gen matches are not the same as the pat embedded 4-vectors above

  	int leg1_MCMatchType; /* match codes defined in GenMcMatchTypes.h */
  	double leg1_genMCmatch_pt, leg1_genMCmatch_eta, leg1_genMCmatch_phi, leg1_genMCmatch_M; /* see https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorking2015#MC_Matching */ 
    int leg1_MCMatchPdgId;

  	int leg2_MCMatchType; /* match codes defined in GenMcMatchTypes.h */
  	double leg2_genMCmatch_pt, leg2_genMCmatch_eta, leg2_genMCmatch_phi, leg2_genMCmatch_M; /* see https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorking2015#MC_Matching */ 
    int leg2_MCMatchPdgId;


	std::vector<int> effLep_MCMatchType; /* match codes defined in GenMcMatchTypes.h */
	std::vector<double> effLep_genMCmatch_pt;
	std::vector<double> effLep_genMCmatch_eta; 
	std::vector<double> effLep_genMCmatch_phi; 
	std::vector<double> effLep_genMCmatch_M;
	std::vector<int> effLep_MCMatchPdgId;


	/* event summary flags for DY + jets */

    int IsZTT;
    int IsZL;
    int IsZJ;
    int IsZLL;

   	/* things missing from sync tree */

  	double rho;                    /* fixedGridRhoFastjetAll */

    /* gen level boson 4-vectors Z/W/H */
    double genBosonTotal_pt, genBosonTotal_eta, genBosonTotal_phi, genBosonTotal_M; 	    /* the gen total 4-vector of W/Z/H */
	double genBosonVisible_pt, genBosonVisible_eta, genBosonVisible_phi, genBosonVisible_M; /* the gen visible 4-vector of W/Z/H */

};  


//define this as a plug-in
DEFINE_FWK_MODULE(FlatTupleGenerator);
#endif
