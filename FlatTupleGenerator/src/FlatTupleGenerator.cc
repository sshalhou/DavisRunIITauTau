// -*- C++ -*-
//
// Package:    FlatTupleGenerator
// Class:      FlatTupleGenerator
//
/**\class FlatTupleGenerator FlatTupleGenerator.cc DavisRunIITauTau/FlatTupleGenerator/src/FlatTupleGenerator.cc

Description: [EDAnalyzer that creates FlatTuples for DavisRunIITauTau analysis using Ntuple as input]


Implementation:

*/
//
// Original Author:  shalhout shalhout
//         Created:  Tue Jun  4 04:25:53 CDT 2015
// $Id$
//
//



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



//////////////////////////////////////////////////
// class declaration
//////////////////////////////////////////////////

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

  /* MASTER VALUE FOR MAX std::pair flattening */

  static const int MAX = 10;

  /* the input collection sources */

  edm::InputTag pairSrc_;
  edm::InputTag indepSrc_;
  std::string NAME_;  // use TauESNom, TauESUp, TauESDown, etc.
  edm::ParameterSet EventCutSrc_;
  std::vector<edm::ParameterSet> LeptonCutVecSrc_;
  


  /* the parameters to be read from EventCutSrc_ */

  std::vector<std::string> tauIDsToKeep;
  bool keepOS;
  bool keepSS;
  std::vector<double> MtCut;
  bool keepTauEsNominal;
  bool keepTauEsUp; 
  bool keepTauEsDown; 
  bool rankByPtSum;
  bool rankByIsolation;
  std::string electronIsolationForRank;
  std::string muonIsolationForRank;
  std::string tauIDisolationForRank;

  /* the lepton cut helper object */
  LeptonFlatTupleCutHelper LeptonCutHelper;

  /* the TTree */
 
  TTree * FlatTuple;



  /* the leaves : Idea here is to be as flat as possible - stick to simple objects */

  std::string treeInfoString;           /* this will be filled as NAME_, should be something like TauEsNominal etc. */
  std::vector<std::string> AppliedLepCuts; /* the cuts applied to the current tree */
  unsigned int  run ;
  unsigned int  luminosityBlock ;
  unsigned int  event ;
  unsigned int  pairRank ; /* zero is the best rank */
  bool  isRealData ;
  double VISMass; 
  float l1_tauIDs[MAX]; /* leg 1 tau IDs */
  float l2_tauIDs[MAX]; /* leg 2 tau IDs */

  int CandidateEventType; 
  float TauEsNumberSigmasShifted;
  int isOsPair;
  double SVMass;
  double MTmvaMET_leg1;
  double MTpfMET_leg1;
  double MTmvaMET_leg2;
  double MTpfMET_leg2;
  double mvaMET;
  double mvaMETphi;
  double mvaMET_cov00; 
  double mvaMET_cov01; 
  double mvaMET_cov10; 
  double mvaMET_cov11;   
  double pfMET;
  double pfMETphi;
  double pfMET_cov00; 
  double pfMET_cov01; 
  double pfMET_cov10; 
  double pfMET_cov11; 

  int leg1_leptonType;
  float leg1_dz;
  float leg1_dxy;
  float leg1_EffectiveArea;
  int leg1_charge;
  int leg1_PFpdgId;
  int leg1_GENpdgId;
  int leg1_GENMOTHERpdgId;
  float leg1_L1TrigObjRecoObjDeltaR;
  float leg1_L3TrigObjRecoObjDeltaR;
  float leg1_IP;
  float leg1_IPerror;
  float leg1_PUchargedHadronIso;
  float leg1_chargedHadronIso;
  float leg1_neutralHadronIso;
  float leg1_photonIso;
  float leg1_DepositR03ECal;
  float leg1_DepositR03Hcal;
  float leg1_DepositR03TrackerOfficial;
  float leg1_isGlobalMuon;
  float leg1_isGoodGlobalMuon;
  float leg1_passesMediumMuonId;
  float leg1_isLooseMuon;
  float leg1_isPFMuon;
  float leg1_isSoftMuon;
  float leg1_isTightMuon;
  float leg1_isTrackerMuon;
  float leg1_muonCombQualChi2LocalPosition;
  float leg1_muonCombQualTrkKink;
  float leg1_muonGlobalTrackNormChi2;
  float leg1_muonInnerTrkValidFraction;
  float leg1_muonSegmentCompatibility;
  float leg1_raw_electronMVA;
  float leg1_passFail_electronMVA;
  float leg1_SuperClusterEta;
  float leg1_hadronicOverEm;
  float leg1_isEB;
  float leg1_isEBEEGap;
  float leg1_isEBEtaGap;
  float leg1_isEBPhiGap;
  float leg1_isEE;
  float leg1_isEEDeeGap;
  float leg1_isEERingGap;
  float leg1_deltaEtaSuperClusterTrackAtVtx;
  float leg1_deltaPhiSuperClusterTrackAtVtx;
  float leg1_sigmaEtaEta;
  float leg1_sigmaIetaIeta;
  float leg1_sigmaIphiIphi;
  float leg1_numberOfMissingInnerHits;
  float leg1_numberOfMissingOuterHits;
  float leg1_numberOfTrackHits;
  float leg1_passConversionVeto;
  float leg1_TauEsVariant;
  float leg1_numStrips;
  float leg1_numHadrons;

  int leg2_leptonType;
  float leg2_dz;
  float leg2_dxy;
  float leg2_EffectiveArea;
  int leg2_charge;
  int leg2_PFpdgId;
  int leg2_GENpdgId;
  int leg2_GENMOTHERpdgId;
  float leg2_L1TrigObjRecoObjDeltaR;
  float leg2_L3TrigObjRecoObjDeltaR;
  float leg2_IP;
  float leg2_IPerror;
  float leg2_PUchargedHadronIso;
  float leg2_chargedHadronIso;
  float leg2_neutralHadronIso;
  float leg2_photonIso;
  float leg2_DepositR03ECal;
  float leg2_DepositR03Hcal;
  float leg2_DepositR03TrackerOfficial;
  float leg2_isGlobalMuon;
  float leg2_isGoodGlobalMuon;
  float leg2_passesMediumMuonId;
  float leg2_isLooseMuon;
  float leg2_isPFMuon;
  float leg2_isSoftMuon;
  float leg2_isTightMuon;
  float leg2_isTrackerMuon;
  float leg2_muonCombQualChi2LocalPosition;
  float leg2_muonCombQualTrkKink;
  float leg2_muonGlobalTrackNormChi2;
  float leg2_muonInnerTrkValidFraction;
  float leg2_muonSegmentCompatibility;
  float leg2_raw_electronMVA;
  float leg2_passFail_electronMVA;
  float leg2_SuperClusterEta;
  float leg2_hadronicOverEm;
  float leg2_isEB;
  float leg2_isEBEEGap;
  float leg2_isEBEtaGap;
  float leg2_isEBPhiGap;
  float leg2_isEE;
  float leg2_isEEDeeGap;
  float leg2_isEERingGap;
  float leg2_deltaEtaSuperClusterTrackAtVtx;
  float leg2_deltaPhiSuperClusterTrackAtVtx;
  float leg2_sigmaEtaEta;
  float leg2_sigmaIetaIeta;
  float leg2_sigmaIphiIphi;
  float leg2_numberOfMissingInnerHits;
  float leg2_numberOfMissingOuterHits;
  float leg2_numberOfTrackHits;
  float leg2_passConversionVeto;
  float leg2_TauEsVariant;
  float leg2_numStrips;
  float leg2_numHadrons;

  double leg2_pt;
  double leg2_gen_pt;
  double leg2_genMother_pt;
  double leg2_L1TrigObj_pt;
  double leg2_L3TrigObj_pt;
  double leg2_genJet_pt;
  double leg1_pt;
  double leg1_gen_pt;
  double leg1_genMother_pt;
  double leg1_L1TrigObj_pt;
  double leg1_L3TrigObj_pt;
  double leg1_genJet_pt;
  double leg2_eta;
  double leg2_gen_eta;
  double leg2_genMother_eta;
  double leg2_L1TrigObj_eta;
  double leg2_L3TrigObj_eta;
  double leg2_genJet_eta;
  double leg1_eta;
  double leg1_gen_eta;
  double leg1_genMother_eta;
  double leg1_L1TrigObj_eta;
  double leg1_L3TrigObj_eta;
  double leg1_genJet_eta;
  double leg2_phi;
  double leg2_gen_phi;
  double leg2_genMother_phi;
  double leg2_L1TrigObj_phi;
  double leg2_L3TrigObj_phi;
  double leg2_genJet_phi;
  double leg1_phi;
  double leg1_gen_phi;
  double leg1_genMother_phi;
  double leg1_L1TrigObj_phi;
  double leg1_L3TrigObj_phi;
  double leg1_genJet_phi;
  double leg2_M;
  double leg2_gen_M;
  double leg2_genMother_M;
  double leg2_L1TrigObj_M;
  double leg2_L3TrigObj_M;
  double leg2_genJet_M;
  double leg1_M;
  double leg1_gen_M;
  double leg1_genMother_M;
  double leg1_L1TrigObj_M;
  double leg1_L3TrigObj_M;
  double leg1_genJet_M;


};

////////////////////////////////////////////
//	--- class constructor
////////////////////////////////////////////


FlatTupleGenerator::FlatTupleGenerator(const edm::ParameterSet& iConfig):
pairSrc_(iConfig.getParameter<edm::InputTag>("pairSrc" )),
indepSrc_(iConfig.getParameter<edm::InputTag>("indepSrc" )),
NAME_(iConfig.getParameter<string>("NAME" )),
EventCutSrc_(iConfig.getParameter<edm::ParameterSet>("EventCutSrc")),
LeptonCutVecSrc_(iConfig.getParameter<std::vector<edm::ParameterSet>>("LeptonCutVecSrc"))
{



  /* read in the EventCutSrc varaibles */

  tauIDsToKeep = EventCutSrc_.getParameter<std::vector<std::string> >("tauIDsToKeep"); 
  assert(MAX>=tauIDsToKeep.size());

  MtCut = EventCutSrc_.getParameter<std::vector<double> >("Mt"); 
  assert(MtCut.size()==2);
  keepOS = EventCutSrc_.getParameter<bool>("keepOS");
  keepSS = EventCutSrc_.getParameter<bool>("keepSS");
  keepTauEsNominal = EventCutSrc_.getParameter<bool>("keepTauEsNominal");
  keepTauEsUp = EventCutSrc_.getParameter<bool>("keepTauEsUp");
  keepTauEsDown = EventCutSrc_.getParameter<bool>("keepTauEsDown");
  rankByPtSum = EventCutSrc_.getParameter<bool>("rankByPtSum");
  rankByIsolation = EventCutSrc_.getParameter<bool>("rankByIsolation");
  assert(rankByPtSum!=rankByIsolation);
  electronIsolationForRank = EventCutSrc_.getParameter<std::string>("electronIsolationForRank");
  muonIsolationForRank = EventCutSrc_.getParameter<std::string>("muonIsolationForRank");
  tauIDisolationForRank = EventCutSrc_.getParameter<std::string>("tauIDisolationForRank");





  /* create TTree */
   
	edm::Service<TFileService> fs;
	FlatTuple = fs->make<TTree>("FlatTuple", "FlatTuple");

  //////////////
  // init values

	  reInit();	


  /* the branches */

  FlatTuple->Branch("run", &run);
  FlatTuple->Branch("luminosityBlock", &luminosityBlock);
  FlatTuple->Branch("event", &event);
  FlatTuple->Branch("pairRank",&pairRank);
  FlatTuple->Branch("isRealData", &isRealData);
  FlatTuple->Branch("treeInfoString", &treeInfoString);
  FlatTuple->Branch("AppliedLepCuts", &AppliedLepCuts);
  FlatTuple->Branch("VISMass", &VISMass);

  for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
  {

  FlatTuple->Branch(("leg1_"+tauIDsToKeep.at(x)).c_str(), &l1_tauIDs[x]);
  FlatTuple->Branch(("leg2_"+tauIDsToKeep.at(x)).c_str(), &l2_tauIDs[x]);
  }

  FlatTuple->Branch("CandidateEventType", &CandidateEventType);
  FlatTuple->Branch("TauEsNumberSigmasShifted", &TauEsNumberSigmasShifted);
  FlatTuple->Branch("isOsPair", &isOsPair);
  FlatTuple->Branch("SVMass", &SVMass);
  FlatTuple->Branch("MTmvaMET_leg1", &MTmvaMET_leg1);
  FlatTuple->Branch("MTpfMET_leg1", &MTpfMET_leg1);
  FlatTuple->Branch("MTmvaMET_leg2", &MTmvaMET_leg2);
  FlatTuple->Branch("MTpfMET_leg2", &MTpfMET_leg2);
  FlatTuple->Branch("mvaMET", &mvaMET);
  FlatTuple->Branch("mvaMETphi", &mvaMETphi);
  FlatTuple->Branch("mvaMET_cov00", &mvaMET_cov00);
  FlatTuple->Branch("mvaMET_cov01", &mvaMET_cov01);
  FlatTuple->Branch("mvaMET_cov10", &mvaMET_cov10);
  FlatTuple->Branch("mvaMET_cov11", &mvaMET_cov11);
  FlatTuple->Branch("pfMET", &pfMET);
  FlatTuple->Branch("pfMETphi", &pfMETphi);
  FlatTuple->Branch("pfMET_cov00", &pfMET_cov00);
  FlatTuple->Branch("pfMET_cov01", &pfMET_cov01);
  FlatTuple->Branch("pfMET_cov10", &pfMET_cov10);
  FlatTuple->Branch("pfMET_cov11", &pfMET_cov11);

  FlatTuple->Branch("leg1_leptonType", &leg1_leptonType);
  FlatTuple->Branch("leg1_dz", &leg1_dz);
  FlatTuple->Branch("leg1_dxy", &leg1_dxy);
  FlatTuple->Branch("leg1_EffectiveArea", &leg1_EffectiveArea);
  FlatTuple->Branch("leg1_charge", &leg1_charge);
  FlatTuple->Branch("leg1_PFpdgId", &leg1_PFpdgId);
  FlatTuple->Branch("leg1_GENpdgId", &leg1_GENpdgId);
  FlatTuple->Branch("leg1_GENMOTHERpdgId", &leg1_GENMOTHERpdgId);
  FlatTuple->Branch("leg1_L1TrigObjRecoObjDeltaR", &leg1_L1TrigObjRecoObjDeltaR);
  FlatTuple->Branch("leg1_L3TrigObjRecoObjDeltaR", &leg1_L3TrigObjRecoObjDeltaR);
  FlatTuple->Branch("leg1_IP", &leg1_IP);
  FlatTuple->Branch("leg1_IPerror", &leg1_IPerror);
  FlatTuple->Branch("leg1_PUchargedHadronIso", &leg1_PUchargedHadronIso);
  FlatTuple->Branch("leg1_chargedHadronIso", &leg1_chargedHadronIso);
  FlatTuple->Branch("leg1_neutralHadronIso", &leg1_neutralHadronIso);
  FlatTuple->Branch("leg1_photonIso", &leg1_photonIso);
  FlatTuple->Branch("leg1_DepositR03ECal", &leg1_DepositR03ECal);
  FlatTuple->Branch("leg1_DepositR03Hcal", &leg1_DepositR03Hcal);
  FlatTuple->Branch("leg1_DepositR03TrackerOfficial", &leg1_DepositR03TrackerOfficial);
  FlatTuple->Branch("leg1_isGlobalMuon", &leg1_isGlobalMuon);
  FlatTuple->Branch("leg1_isGoodGlobalMuon", &leg1_isGoodGlobalMuon);
  FlatTuple->Branch("leg1_passesMediumMuonId", &leg1_passesMediumMuonId);
  FlatTuple->Branch("leg1_isLooseMuon", &leg1_isLooseMuon);
  FlatTuple->Branch("leg1_isPFMuon", &leg1_isPFMuon);
  FlatTuple->Branch("leg1_isSoftMuon", &leg1_isSoftMuon);
  FlatTuple->Branch("leg1_isTightMuon", &leg1_isTightMuon);
  FlatTuple->Branch("leg1_isTrackerMuon", &leg1_isTrackerMuon);
  FlatTuple->Branch("leg1_muonCombQualChi2LocalPosition", &leg1_muonCombQualChi2LocalPosition);
  FlatTuple->Branch("leg1_muonCombQualTrkKink", &leg1_muonCombQualTrkKink);
  FlatTuple->Branch("leg1_muonGlobalTrackNormChi2", &leg1_muonGlobalTrackNormChi2);
  FlatTuple->Branch("leg1_muonInnerTrkValidFraction", &leg1_muonInnerTrkValidFraction);
  FlatTuple->Branch("leg1_muonSegmentCompatibility", &leg1_muonSegmentCompatibility);
  FlatTuple->Branch("leg1_raw_electronMVA", &leg1_raw_electronMVA);
  FlatTuple->Branch("leg1_passFail_electronMVA", &leg1_passFail_electronMVA);
  FlatTuple->Branch("leg1_SuperClusterEta", &leg1_SuperClusterEta);
  FlatTuple->Branch("leg1_hadronicOverEm", &leg1_hadronicOverEm);
  FlatTuple->Branch("leg1_isEB", &leg1_isEB);
  FlatTuple->Branch("leg1_isEBEEGap", &leg1_isEBEEGap);
  FlatTuple->Branch("leg1_isEBEtaGap", &leg1_isEBEtaGap);
  FlatTuple->Branch("leg1_isEBPhiGap", &leg1_isEBPhiGap);
  FlatTuple->Branch("leg1_isEE", &leg1_isEE);
  FlatTuple->Branch("leg1_isEEDeeGap", &leg1_isEEDeeGap);
  FlatTuple->Branch("leg1_isEERingGap", &leg1_isEERingGap);
  FlatTuple->Branch("leg1_deltaEtaSuperClusterTrackAtVtx", &leg1_deltaEtaSuperClusterTrackAtVtx);
  FlatTuple->Branch("leg1_deltaPhiSuperClusterTrackAtVtx", &leg1_deltaPhiSuperClusterTrackAtVtx);
  FlatTuple->Branch("leg1_sigmaEtaEta", &leg1_sigmaEtaEta);
  FlatTuple->Branch("leg1_sigmaIetaIeta", &leg1_sigmaIetaIeta);
  FlatTuple->Branch("leg1_sigmaIphiIphi", &leg1_sigmaIphiIphi);
  FlatTuple->Branch("leg1_numberOfMissingInnerHits", &leg1_numberOfMissingInnerHits);
  FlatTuple->Branch("leg1_numberOfMissingOuterHits", &leg1_numberOfMissingOuterHits);
  FlatTuple->Branch("leg1_numberOfTrackHits", &leg1_numberOfTrackHits);
  FlatTuple->Branch("leg1_passConversionVeto", &leg1_passConversionVeto);
  FlatTuple->Branch("leg1_TauEsVariant", &leg1_TauEsVariant);
  FlatTuple->Branch("leg1_numStrips", &leg1_numStrips);
  FlatTuple->Branch("leg1_numHadrons", &leg1_numHadrons);
  FlatTuple->Branch("leg2_leptonType", &leg2_leptonType);
  FlatTuple->Branch("leg2_dz", &leg2_dz);
  FlatTuple->Branch("leg2_dxy", &leg2_dxy);
  FlatTuple->Branch("leg2_EffectiveArea", &leg2_EffectiveArea);
  FlatTuple->Branch("leg2_charge", &leg2_charge);
  FlatTuple->Branch("leg2_PFpdgId", &leg2_PFpdgId);
  FlatTuple->Branch("leg2_GENpdgId", &leg2_GENpdgId);
  FlatTuple->Branch("leg2_GENMOTHERpdgId", &leg2_GENMOTHERpdgId);
  FlatTuple->Branch("leg2_L1TrigObjRecoObjDeltaR", &leg2_L1TrigObjRecoObjDeltaR);
  FlatTuple->Branch("leg2_L3TrigObjRecoObjDeltaR", &leg2_L3TrigObjRecoObjDeltaR);
  FlatTuple->Branch("leg2_IP", &leg2_IP);
  FlatTuple->Branch("leg2_IPerror", &leg2_IPerror);
  FlatTuple->Branch("leg2_PUchargedHadronIso", &leg2_PUchargedHadronIso);
  FlatTuple->Branch("leg2_chargedHadronIso", &leg2_chargedHadronIso);
  FlatTuple->Branch("leg2_neutralHadronIso", &leg2_neutralHadronIso);
  FlatTuple->Branch("leg2_photonIso", &leg2_photonIso);
  FlatTuple->Branch("leg2_DepositR03ECal", &leg2_DepositR03ECal);
  FlatTuple->Branch("leg2_DepositR03Hcal", &leg2_DepositR03Hcal);
  FlatTuple->Branch("leg2_DepositR03TrackerOfficial", &leg2_DepositR03TrackerOfficial);
  FlatTuple->Branch("leg2_isGlobalMuon", &leg2_isGlobalMuon);
  FlatTuple->Branch("leg2_isGoodGlobalMuon", &leg2_isGoodGlobalMuon);
  FlatTuple->Branch("leg2_passesMediumMuonId", &leg2_passesMediumMuonId);
  FlatTuple->Branch("leg2_isLooseMuon", &leg2_isLooseMuon);
  FlatTuple->Branch("leg2_isPFMuon", &leg2_isPFMuon);
  FlatTuple->Branch("leg2_isSoftMuon", &leg2_isSoftMuon);
  FlatTuple->Branch("leg2_isTightMuon", &leg2_isTightMuon);
  FlatTuple->Branch("leg2_isTrackerMuon", &leg2_isTrackerMuon);
  FlatTuple->Branch("leg2_muonCombQualChi2LocalPosition", &leg2_muonCombQualChi2LocalPosition);
  FlatTuple->Branch("leg2_muonCombQualTrkKink", &leg2_muonCombQualTrkKink);
  FlatTuple->Branch("leg2_muonGlobalTrackNormChi2", &leg2_muonGlobalTrackNormChi2);
  FlatTuple->Branch("leg2_muonInnerTrkValidFraction", &leg2_muonInnerTrkValidFraction);
  FlatTuple->Branch("leg2_muonSegmentCompatibility", &leg2_muonSegmentCompatibility);
  FlatTuple->Branch("leg2_raw_electronMVA", &leg2_raw_electronMVA);
  FlatTuple->Branch("leg2_passFail_electronMVA", &leg2_passFail_electronMVA);
  FlatTuple->Branch("leg2_SuperClusterEta", &leg2_SuperClusterEta);
  FlatTuple->Branch("leg2_hadronicOverEm", &leg2_hadronicOverEm);
  FlatTuple->Branch("leg2_isEB", &leg2_isEB);
  FlatTuple->Branch("leg2_isEBEEGap", &leg2_isEBEEGap);
  FlatTuple->Branch("leg2_isEBEtaGap", &leg2_isEBEtaGap);
  FlatTuple->Branch("leg2_isEBPhiGap", &leg2_isEBPhiGap);
  FlatTuple->Branch("leg2_isEE", &leg2_isEE);
  FlatTuple->Branch("leg2_isEEDeeGap", &leg2_isEEDeeGap);
  FlatTuple->Branch("leg2_isEERingGap", &leg2_isEERingGap);
  FlatTuple->Branch("leg2_deltaEtaSuperClusterTrackAtVtx", &leg2_deltaEtaSuperClusterTrackAtVtx);
  FlatTuple->Branch("leg2_deltaPhiSuperClusterTrackAtVtx", &leg2_deltaPhiSuperClusterTrackAtVtx);
  FlatTuple->Branch("leg2_sigmaEtaEta", &leg2_sigmaEtaEta);
  FlatTuple->Branch("leg2_sigmaIetaIeta", &leg2_sigmaIetaIeta);
  FlatTuple->Branch("leg2_sigmaIphiIphi", &leg2_sigmaIphiIphi);
  FlatTuple->Branch("leg2_numberOfMissingInnerHits", &leg2_numberOfMissingInnerHits);
  FlatTuple->Branch("leg2_numberOfMissingOuterHits", &leg2_numberOfMissingOuterHits);
  FlatTuple->Branch("leg2_numberOfTrackHits", &leg2_numberOfTrackHits);
  FlatTuple->Branch("leg2_passConversionVeto", &leg2_passConversionVeto);
  FlatTuple->Branch("leg2_TauEsVariant", &leg2_TauEsVariant);
  FlatTuple->Branch("leg2_numStrips", &leg2_numStrips);
  FlatTuple->Branch("leg2_numHadrons", &leg2_numHadrons);

  FlatTuple->Branch("leg2_pt", &leg2_pt);
  FlatTuple->Branch("leg2_gen_pt", &leg2_gen_pt);
  FlatTuple->Branch("leg2_genMother_pt", &leg2_genMother_pt);
  FlatTuple->Branch("leg2_L1TrigObj_pt", &leg2_L1TrigObj_pt);
  FlatTuple->Branch("leg2_L3TrigObj_pt", &leg2_L3TrigObj_pt);
  FlatTuple->Branch("leg2_genJet_pt", &leg2_genJet_pt);
  FlatTuple->Branch("leg1_pt", &leg1_pt);
  FlatTuple->Branch("leg1_gen_pt", &leg1_gen_pt);
  FlatTuple->Branch("leg1_genMother_pt", &leg1_genMother_pt);
  FlatTuple->Branch("leg1_L1TrigObj_pt", &leg1_L1TrigObj_pt);
  FlatTuple->Branch("leg1_L3TrigObj_pt", &leg1_L3TrigObj_pt);
  FlatTuple->Branch("leg1_genJet_pt", &leg1_genJet_pt);
  FlatTuple->Branch("leg2_eta", &leg2_eta);
  FlatTuple->Branch("leg2_gen_eta", &leg2_gen_eta);
  FlatTuple->Branch("leg2_genMother_eta", &leg2_genMother_eta);
  FlatTuple->Branch("leg2_L1TrigObj_eta", &leg2_L1TrigObj_eta);
  FlatTuple->Branch("leg2_L3TrigObj_eta", &leg2_L3TrigObj_eta);
  FlatTuple->Branch("leg2_genJet_eta", &leg2_genJet_eta);
  FlatTuple->Branch("leg1_eta", &leg1_eta);
  FlatTuple->Branch("leg1_gen_eta", &leg1_gen_eta);
  FlatTuple->Branch("leg1_genMother_eta", &leg1_genMother_eta);
  FlatTuple->Branch("leg1_L1TrigObj_eta", &leg1_L1TrigObj_eta);
  FlatTuple->Branch("leg1_L3TrigObj_eta", &leg1_L3TrigObj_eta);
  FlatTuple->Branch("leg1_genJet_eta", &leg1_genJet_eta);
  FlatTuple->Branch("leg2_phi", &leg2_phi);
  FlatTuple->Branch("leg2_gen_phi", &leg2_gen_phi);
  FlatTuple->Branch("leg2_genMother_phi", &leg2_genMother_phi);
  FlatTuple->Branch("leg2_L1TrigObj_phi", &leg2_L1TrigObj_phi);
  FlatTuple->Branch("leg2_L3TrigObj_phi", &leg2_L3TrigObj_phi);
  FlatTuple->Branch("leg2_genJet_phi", &leg2_genJet_phi);
  FlatTuple->Branch("leg1_phi", &leg1_phi);
  FlatTuple->Branch("leg1_gen_phi", &leg1_gen_phi);
  FlatTuple->Branch("leg1_genMother_phi", &leg1_genMother_phi);
  FlatTuple->Branch("leg1_L1TrigObj_phi", &leg1_L1TrigObj_phi);
  FlatTuple->Branch("leg1_L3TrigObj_phi", &leg1_L3TrigObj_phi);
  FlatTuple->Branch("leg1_genJet_phi", &leg1_genJet_phi);
  FlatTuple->Branch("leg2_M", &leg2_M);
  FlatTuple->Branch("leg2_gen_M", &leg2_gen_M);
  FlatTuple->Branch("leg2_genMother_M", &leg2_genMother_M);
  FlatTuple->Branch("leg2_L1TrigObj_M", &leg2_L1TrigObj_M);
  FlatTuple->Branch("leg2_L3TrigObj_M", &leg2_L3TrigObj_M);
  FlatTuple->Branch("leg2_genJet_M", &leg2_genJet_M);
  FlatTuple->Branch("leg1_M", &leg1_M);
  FlatTuple->Branch("leg1_gen_M", &leg1_gen_M);
  FlatTuple->Branch("leg1_genMother_M", &leg1_genMother_M);
  FlatTuple->Branch("leg1_L1TrigObj_M", &leg1_L1TrigObj_M);
  FlatTuple->Branch("leg1_L3TrigObj_M", &leg1_L3TrigObj_M);
  FlatTuple->Branch("leg1_genJet_M", &leg1_genJet_M);


}


//////////////////////////////////////////////////
// class destructor 
//////////////////////////////////////////////////

FlatTupleGenerator::~FlatTupleGenerator(){}


//////////////////////////////////////////////////
// ------------ method called for each event  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{




  //////////////
  // init values

  reInit();


  ///////////////
  // get inputs 

  edm::Handle< NtupleEventCollection > pairs;
  iEvent.getByLabel(pairSrc_, pairs);

  edm::Handle< NtuplePairIndependentInfoCollection > pairIndepInfos;
  iEvent.getByLabel(indepSrc_, pairIndepInfos);





  ///////////////////////////////////////////
  // for each event, store a vector of NtupleEvent (i.e. pair)
  // objects that pass the specified selection /* coming soon, for now keep all */

  std::vector<NtupleEvent> retainedPairs;
  retainedPairs.clear();

  /////////////////////////////////////
  // now loop through the pairs in the current event
  // and figure out which ones to retain 

  for(std::size_t p = 0; p<pairs->size(); ++p )
  {
    NtupleEvent currentPair =   ((*pairs)[p]);

    bool keepSignPair = ((keepOS && currentPair.isOsPair()==1) || (keepSS && currentPair.isOsPair()!=1));
    
    bool keepTauEsVariant = (
      
      (keepTauEsNominal && currentPair.TauEsNumberSigmasShifted()==0.0) ||
      (keepTauEsNominal && isnan(currentPair.TauEsNumberSigmasShifted())) || /* for eMu, muMu, EleEle */
      (keepTauEsUp && currentPair.TauEsNumberSigmasShifted()==1.0) ||
      (keepTauEsDown && currentPair.TauEsNumberSigmasShifted()==-1.0) 

      );


    /* check if the cuts pass */

    bool leptonCutsPass = LeptonCutHelper.cutEvaluator(currentPair, LeptonCutVecSrc_);
    std::cout<<" lepton cuts ===> "<<leptonCutsPass<<"for type "<<currentPair.CandidateEventType()<<"\n";


   if(keepSignPair && keepTauEsVariant && leptonCutsPass) retainedPairs.push_back(currentPair);

  }

  std::cout<<" retained pairs size = "<<retainedPairs.size()<<"\n";
  if(retainedPairs.size()==0) return;



  /////////////////////////
  // next figure out how to rank the pairs 


  PairRankHelper rankHelper;

  if(rankByPtSum) rankHelper.init(retainedPairs);
  else if(rankByIsolation) rankHelper.init(retainedPairs,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank);

  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank = rankHelper.returnRankedPairVec();


  // rankHelper.process_pairs(retainedPairs);



  for(std::size_t p = 0; p<retainedPairsWithRank.size(); ++p )
  {

      reInit();

      ////////////////
      // fill some easy stuff first :

      run = iEvent.id().run();
      luminosityBlock = iEvent.id().luminosityBlock();
      event = iEvent.id().event();
      isRealData = iEvent.isRealData();
      treeInfoString = NAME_;

      AppliedLepCuts = LeptonCutHelper.getCutSummary(LeptonCutVecSrc_);

      ///////
      // now stuff depending on the current pair


  		NtupleEvent currentPair =   retainedPairsWithRank[p].second;


      VISMass = currentPair.VISMass()[0];
      pairRank = retainedPairsWithRank[p].first;
      
      ////////////////
      // fill the tauIDs for tau legs


        for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
        {
          
          if(currentPair.leg1().leptonType() == TupleLeptonTypes::aTau)
          {
              l1_tauIDs[x]  =  currentPair.leg1().tauID(tauIDsToKeep[x]);
          }

          if(currentPair.leg2().leptonType() == TupleLeptonTypes::aTau)
          {
              l2_tauIDs[x]  =  currentPair.leg2().tauID(tauIDsToKeep[x]);
          }

        }

      CandidateEventType = currentPair.CandidateEventType();
      TauEsNumberSigmasShifted = currentPair.TauEsNumberSigmasShifted();
      isOsPair = currentPair.isOsPair();
      SVMass = currentPair.SVMass()[0];
      MTmvaMET_leg1 = currentPair.MTmvaMET_leg1()[0];
      MTpfMET_leg1 = currentPair.MTpfMET_leg1()[0];
      MTmvaMET_leg2 = currentPair.MTmvaMET_leg2()[0];
      MTpfMET_leg2 = currentPair.MTpfMET_leg2()[0];
      mvaMET = currentPair.mvaMET()[0].pt();
      mvaMETphi = currentPair.mvaMET()[0].phi();
      mvaMET_cov00 = currentPair.mvaMET()[0].getSignificanceMatrix()[0][0];
      mvaMET_cov01 = currentPair.mvaMET()[0].getSignificanceMatrix()[0][1];
      mvaMET_cov10 = currentPair.mvaMET()[0].getSignificanceMatrix()[1][0];
      mvaMET_cov11 = currentPair.mvaMET()[0].getSignificanceMatrix()[1][1];
      pfMET = currentPair.pfMET()[0].pt();
      pfMETphi = currentPair.pfMET()[0].phi();
      pfMET_cov00 = currentPair.pfMET_cov00()[0];
      pfMET_cov01 = currentPair.pfMET_cov01()[0];
      pfMET_cov10 = currentPair.pfMET_cov10()[0];
      pfMET_cov11 = currentPair.pfMET_cov11()[0];  


      leg1_leptonType = currentPair.leg1().leptonType();
      leg1_dz = currentPair.leg1().dz();
      leg1_dxy = currentPair.leg1().dxy();
      leg1_EffectiveArea = currentPair.leg1().EffectiveArea();
      leg1_charge = currentPair.leg1().charge();
      leg1_PFpdgId = currentPair.leg1().PFpdgId();
      leg1_GENpdgId = currentPair.leg1().GENpdgId();
      leg1_GENMOTHERpdgId = currentPair.leg1().GENMOTHERpdgId();
      leg1_L1TrigObjRecoObjDeltaR = currentPair.leg1().L1TrigObjRecoObjDeltaR();
      leg1_L3TrigObjRecoObjDeltaR = currentPair.leg1().L3TrigObjRecoObjDeltaR();
      leg1_IP = currentPair.leg1().IP();
      leg1_IPerror = currentPair.leg1().IPerror();
      leg1_PUchargedHadronIso = currentPair.leg1().PUchargedHadronIso();
      leg1_chargedHadronIso = currentPair.leg1().chargedHadronIso();
      leg1_neutralHadronIso = currentPair.leg1().neutralHadronIso();
      leg1_photonIso = currentPair.leg1().photonIso();
      leg1_DepositR03ECal = currentPair.leg1().DepositR03ECal();
      leg1_DepositR03Hcal = currentPair.leg1().DepositR03Hcal();
      leg1_DepositR03TrackerOfficial = currentPair.leg1().DepositR03TrackerOfficial();
      leg1_isGlobalMuon = currentPair.leg1().isGlobalMuon();
      leg1_isGoodGlobalMuon = currentPair.leg1().isGoodGlobalMuon();
      leg1_passesMediumMuonId = currentPair.leg1().passesMediumMuonId();
      leg1_isLooseMuon = currentPair.leg1().isLooseMuon();
      leg1_isPFMuon = currentPair.leg1().isPFMuon();
      leg1_isSoftMuon = currentPair.leg1().isSoftMuon();
      leg1_isTightMuon = currentPair.leg1().isTightMuon();
      leg1_isTrackerMuon = currentPair.leg1().isTrackerMuon();
      leg1_muonCombQualChi2LocalPosition = currentPair.leg1().muonCombQualChi2LocalPosition();
      leg1_muonCombQualTrkKink = currentPair.leg1().muonCombQualTrkKink();
      leg1_muonGlobalTrackNormChi2 = currentPair.leg1().muonGlobalTrackNormChi2();
      leg1_muonInnerTrkValidFraction = currentPair.leg1().muonInnerTrkValidFraction();
      leg1_muonSegmentCompatibility = currentPair.leg1().muonSegmentCompatibility();
      leg1_raw_electronMVA = currentPair.leg1().raw_electronMVA();
      leg1_passFail_electronMVA = currentPair.leg1().passFail_electronMVA();
      leg1_SuperClusterEta = currentPair.leg1().SuperClusterEta();
      leg1_hadronicOverEm = currentPair.leg1().hadronicOverEm();
      leg1_isEB = currentPair.leg1().isEB();
      leg1_isEBEEGap = currentPair.leg1().isEBEEGap();
      leg1_isEBEtaGap = currentPair.leg1().isEBEtaGap();
      leg1_isEBPhiGap = currentPair.leg1().isEBPhiGap();
      leg1_isEE = currentPair.leg1().isEE();
      leg1_isEEDeeGap = currentPair.leg1().isEEDeeGap();
      leg1_isEERingGap = currentPair.leg1().isEERingGap();
      leg1_deltaEtaSuperClusterTrackAtVtx = currentPair.leg1().deltaEtaSuperClusterTrackAtVtx();
      leg1_deltaPhiSuperClusterTrackAtVtx = currentPair.leg1().deltaPhiSuperClusterTrackAtVtx();
      leg1_sigmaEtaEta = currentPair.leg1().sigmaEtaEta();
      leg1_sigmaIetaIeta = currentPair.leg1().sigmaIetaIeta();
      leg1_sigmaIphiIphi = currentPair.leg1().sigmaIphiIphi();
      leg1_numberOfMissingInnerHits = currentPair.leg1().numberOfMissingInnerHits();
      leg1_numberOfMissingOuterHits = currentPair.leg1().numberOfMissingOuterHits();
      leg1_numberOfTrackHits = currentPair.leg1().numberOfTrackHits();
      leg1_passConversionVeto = currentPair.leg1().passConversionVeto();
      leg1_TauEsVariant = currentPair.leg1().TauEsVariant();
      leg1_numStrips = currentPair.leg1().numStrips();
      leg1_numHadrons = currentPair.leg1().numHadrons();
      leg2_leptonType = currentPair.leg2().leptonType();
      leg2_dz = currentPair.leg2().dz();
      leg2_dxy = currentPair.leg2().dxy();
      leg2_EffectiveArea = currentPair.leg2().EffectiveArea();
      leg2_charge = currentPair.leg2().charge();
      leg2_PFpdgId = currentPair.leg2().PFpdgId();
      leg2_GENpdgId = currentPair.leg2().GENpdgId();
      leg2_GENMOTHERpdgId = currentPair.leg2().GENMOTHERpdgId();
      leg2_L1TrigObjRecoObjDeltaR = currentPair.leg2().L1TrigObjRecoObjDeltaR();
      leg2_L3TrigObjRecoObjDeltaR = currentPair.leg2().L3TrigObjRecoObjDeltaR();
      leg2_IP = currentPair.leg2().IP();
      leg2_IPerror = currentPair.leg2().IPerror();
      leg2_PUchargedHadronIso = currentPair.leg2().PUchargedHadronIso();
      leg2_chargedHadronIso = currentPair.leg2().chargedHadronIso();
      leg2_neutralHadronIso = currentPair.leg2().neutralHadronIso();
      leg2_photonIso = currentPair.leg2().photonIso();
      leg2_DepositR03ECal = currentPair.leg2().DepositR03ECal();
      leg2_DepositR03Hcal = currentPair.leg2().DepositR03Hcal();
      leg2_DepositR03TrackerOfficial = currentPair.leg2().DepositR03TrackerOfficial();
      leg2_isGlobalMuon = currentPair.leg2().isGlobalMuon();
      leg2_isGoodGlobalMuon = currentPair.leg2().isGoodGlobalMuon();
      leg2_passesMediumMuonId = currentPair.leg2().passesMediumMuonId();
      leg2_isLooseMuon = currentPair.leg2().isLooseMuon();
      leg2_isPFMuon = currentPair.leg2().isPFMuon();
      leg2_isSoftMuon = currentPair.leg2().isSoftMuon();
      leg2_isTightMuon = currentPair.leg2().isTightMuon();
      leg2_isTrackerMuon = currentPair.leg2().isTrackerMuon();
      leg2_muonCombQualChi2LocalPosition = currentPair.leg2().muonCombQualChi2LocalPosition();
      leg2_muonCombQualTrkKink = currentPair.leg2().muonCombQualTrkKink();
      leg2_muonGlobalTrackNormChi2 = currentPair.leg2().muonGlobalTrackNormChi2();
      leg2_muonInnerTrkValidFraction = currentPair.leg2().muonInnerTrkValidFraction();
      leg2_muonSegmentCompatibility = currentPair.leg2().muonSegmentCompatibility();
      leg2_raw_electronMVA = currentPair.leg2().raw_electronMVA();
      leg2_passFail_electronMVA = currentPair.leg2().passFail_electronMVA();
      leg2_SuperClusterEta = currentPair.leg2().SuperClusterEta();
      leg2_hadronicOverEm = currentPair.leg2().hadronicOverEm();
      leg2_isEB = currentPair.leg2().isEB();
      leg2_isEBEEGap = currentPair.leg2().isEBEEGap();
      leg2_isEBEtaGap = currentPair.leg2().isEBEtaGap();
      leg2_isEBPhiGap = currentPair.leg2().isEBPhiGap();
      leg2_isEE = currentPair.leg2().isEE();
      leg2_isEEDeeGap = currentPair.leg2().isEEDeeGap();
      leg2_isEERingGap = currentPair.leg2().isEERingGap();
      leg2_deltaEtaSuperClusterTrackAtVtx = currentPair.leg2().deltaEtaSuperClusterTrackAtVtx();
      leg2_deltaPhiSuperClusterTrackAtVtx = currentPair.leg2().deltaPhiSuperClusterTrackAtVtx();
      leg2_sigmaEtaEta = currentPair.leg2().sigmaEtaEta();
      leg2_sigmaIetaIeta = currentPair.leg2().sigmaIetaIeta();
      leg2_sigmaIphiIphi = currentPair.leg2().sigmaIphiIphi();
      leg2_numberOfMissingInnerHits = currentPair.leg2().numberOfMissingInnerHits();
      leg2_numberOfMissingOuterHits = currentPair.leg2().numberOfMissingOuterHits();
      leg2_numberOfTrackHits = currentPair.leg2().numberOfTrackHits();
      leg2_passConversionVeto = currentPair.leg2().passConversionVeto();
      leg2_TauEsVariant = currentPair.leg2().TauEsVariant();
      leg2_numStrips = currentPair.leg2().numStrips();
      leg2_numHadrons = currentPair.leg2().numHadrons();

      leg2_pt = currentPair.leg2().p4().pt();
      leg2_gen_pt = currentPair.leg2().gen_p4().pt();
      leg2_genMother_pt = currentPair.leg2().genMother_p4().pt();
      leg2_L1TrigObj_pt = currentPair.leg2().L1TrigObj_p4().pt();
      leg2_L3TrigObj_pt = currentPair.leg2().L3TrigObj_p4().pt();
      leg2_genJet_pt = currentPair.leg2().genJet_p4().pt();
      leg1_pt = currentPair.leg1().p4().pt();
      leg1_gen_pt = currentPair.leg1().gen_p4().pt();
      leg1_genMother_pt = currentPair.leg1().genMother_p4().pt();
      leg1_L1TrigObj_pt = currentPair.leg1().L1TrigObj_p4().pt();
      leg1_L3TrigObj_pt = currentPair.leg1().L3TrigObj_p4().pt();
      leg1_genJet_pt = currentPair.leg1().genJet_p4().pt();
      leg2_eta = currentPair.leg2().p4().eta();
      leg2_gen_eta = currentPair.leg2().gen_p4().eta();
      leg2_genMother_eta = currentPair.leg2().genMother_p4().eta();
      leg2_L1TrigObj_eta = currentPair.leg2().L1TrigObj_p4().eta();
      leg2_L3TrigObj_eta = currentPair.leg2().L3TrigObj_p4().eta();
      leg2_genJet_eta = currentPair.leg2().genJet_p4().eta();
      leg1_eta = currentPair.leg1().p4().eta();
      leg1_gen_eta = currentPair.leg1().gen_p4().eta();
      leg1_genMother_eta = currentPair.leg1().genMother_p4().eta();
      leg1_L1TrigObj_eta = currentPair.leg1().L1TrigObj_p4().eta();
      leg1_L3TrigObj_eta = currentPair.leg1().L3TrigObj_p4().eta();
      leg1_genJet_eta = currentPair.leg1().genJet_p4().eta();
      leg2_phi = currentPair.leg2().p4().phi();
      leg2_gen_phi = currentPair.leg2().gen_p4().phi();
      leg2_genMother_phi = currentPair.leg2().genMother_p4().phi();
      
      leg2_L1TrigObj_phi = currentPair.leg2().L1TrigObj_p4().phi();
      leg2_L3TrigObj_phi = currentPair.leg2().L3TrigObj_p4().phi();
      leg2_genJet_phi = currentPair.leg2().genJet_p4().phi();
      leg1_phi = currentPair.leg1().p4().phi();
      leg1_gen_phi = currentPair.leg1().gen_p4().phi();
      leg1_genMother_phi = currentPair.leg1().genMother_p4().phi();
      leg1_L1TrigObj_phi = currentPair.leg1().L1TrigObj_p4().phi();
      leg1_L3TrigObj_phi = currentPair.leg1().L3TrigObj_p4().phi();
      leg1_genJet_phi = currentPair.leg1().genJet_p4().phi();
      leg2_M = currentPair.leg2().p4().M();
      leg2_gen_M = currentPair.leg2().gen_p4().M();
      leg2_genMother_M = currentPair.leg2().genMother_p4().M();
      leg2_L1TrigObj_M = currentPair.leg2().L1TrigObj_p4().M();
      leg2_L3TrigObj_M = currentPair.leg2().L3TrigObj_p4().M();
      leg2_genJet_M = currentPair.leg2().genJet_p4().M();
      leg1_M = currentPair.leg1().p4().M();
      leg1_gen_M = currentPair.leg1().gen_p4().M();
      leg1_genMother_M = currentPair.leg1().genMother_p4().M();
      leg1_L1TrigObj_M = currentPair.leg1().L1TrigObj_p4().M();
      leg1_L3TrigObj_M = currentPair.leg1().L3TrigObj_p4().M();
      leg1_genJet_M = currentPair.leg1().genJet_p4().M();



      FlatTuple->Fill();

  }








}


//////////////////////////////////////////////////
// ------------ method called to reset values and clear vectors each event ----
//////////////////////////////////////////////////

 void FlatTupleGenerator::reInit()
 {

   run = 0;
   luminosityBlock = 0;
   event = 0;
   pairRank = 999;
   isRealData  = 0;
   treeInfoString = "NULL";
   VISMass  = NAN;
   AppliedLepCuts.clear();

  for(int r =0; r<MAX;++r)
  {  l1_tauIDs[r] = NAN;
     l2_tauIDs[r] = NAN;
  }

  CandidateEventType = -999; 
  TauEsNumberSigmasShifted = NAN;
  isOsPair = -999;
  SVMass = NAN;
  MTmvaMET_leg1 = NAN;
  MTpfMET_leg1 = NAN;
  MTmvaMET_leg2 = NAN;
  MTpfMET_leg2 = NAN;
  mvaMET = NAN;
  mvaMETphi = NAN;
  mvaMET_cov00 = NAN;
  mvaMET_cov01 = NAN; 
  mvaMET_cov10 = NAN; 
  mvaMET_cov11 = NAN;   
  pfMET = NAN;
  pfMETphi = NAN;
  pfMET_cov00 = NAN; 
  pfMET_cov01 = NAN; 
  pfMET_cov10 = NAN; 
  pfMET_cov11 = NAN;   

  leg1_dz = NAN;
  leg1_dxy = NAN;
  leg1_EffectiveArea = NAN;
  leg1_L1TrigObjRecoObjDeltaR = NAN;
  leg1_L3TrigObjRecoObjDeltaR = NAN;
  leg1_IP = NAN;
  leg1_IPerror = NAN;
  leg1_PUchargedHadronIso = NAN;
  leg1_chargedHadronIso = NAN;
  leg1_neutralHadronIso = NAN;
  leg1_photonIso = NAN;
  leg1_DepositR03ECal = NAN;
  leg1_DepositR03Hcal = NAN;
  leg1_DepositR03TrackerOfficial = NAN;
  leg1_isGlobalMuon = NAN;
  leg1_isGoodGlobalMuon = NAN;
  leg1_passesMediumMuonId = NAN;
  leg1_isLooseMuon = NAN;
  leg1_isPFMuon = NAN;
  leg1_isSoftMuon = NAN;
  leg1_isTightMuon = NAN;
  leg1_isTrackerMuon = NAN;
  leg1_muonCombQualChi2LocalPosition = NAN;
  leg1_muonCombQualTrkKink = NAN;
  leg1_muonGlobalTrackNormChi2 = NAN;
  leg1_muonInnerTrkValidFraction = NAN;
  leg1_muonSegmentCompatibility = NAN;
  leg1_raw_electronMVA = NAN;
  leg1_passFail_electronMVA = NAN;
  leg1_SuperClusterEta = NAN;
  leg1_hadronicOverEm = NAN;
  leg1_isEB = NAN;
  leg1_isEBEEGap = NAN;
  leg1_isEBEtaGap = NAN;
  leg1_isEBPhiGap = NAN;
  leg1_isEE = NAN;
  leg1_isEEDeeGap = NAN;
  leg1_isEERingGap = NAN;
  leg1_deltaEtaSuperClusterTrackAtVtx = NAN;
  leg1_deltaPhiSuperClusterTrackAtVtx = NAN;
  leg1_sigmaEtaEta = NAN;
  leg1_sigmaIetaIeta = NAN;
  leg1_sigmaIphiIphi = NAN;
  leg1_numberOfMissingInnerHits = NAN;
  leg1_numberOfMissingOuterHits = NAN;
  leg1_numberOfTrackHits = NAN;
  leg1_passConversionVeto = NAN;
  leg1_TauEsVariant = NAN;
  leg1_numStrips = NAN;
  leg1_numHadrons = NAN;
  leg2_dz = NAN;
  leg2_dxy = NAN;
  leg2_EffectiveArea = NAN;
  leg2_L1TrigObjRecoObjDeltaR = NAN;
  leg2_L3TrigObjRecoObjDeltaR = NAN;
  leg2_IP = NAN;
  leg2_IPerror = NAN;
  leg2_PUchargedHadronIso = NAN;
  leg2_chargedHadronIso = NAN;
  leg2_neutralHadronIso = NAN;
  leg2_photonIso = NAN;
  leg2_DepositR03ECal = NAN;
  leg2_DepositR03Hcal = NAN;
  leg2_DepositR03TrackerOfficial = NAN;
  leg2_isGlobalMuon = NAN;
  leg2_isGoodGlobalMuon = NAN;
  leg2_passesMediumMuonId = NAN;
  leg2_isLooseMuon = NAN;
  leg2_isPFMuon = NAN;
  leg2_isSoftMuon = NAN;
  leg2_isTightMuon = NAN;
  leg2_isTrackerMuon = NAN;
  leg2_muonCombQualChi2LocalPosition = NAN;
  leg2_muonCombQualTrkKink = NAN;
  leg2_muonGlobalTrackNormChi2 = NAN;
  leg2_muonInnerTrkValidFraction = NAN;
  leg2_muonSegmentCompatibility = NAN;
  leg2_raw_electronMVA = NAN;
  leg2_passFail_electronMVA = NAN;
  leg2_SuperClusterEta = NAN;
  leg2_hadronicOverEm = NAN;
  leg2_isEB = NAN;
  leg2_isEBEEGap = NAN;
  leg2_isEBEtaGap = NAN;
  leg2_isEBPhiGap = NAN;
  leg2_isEE = NAN;
  leg2_isEEDeeGap = NAN;
  leg2_isEERingGap = NAN;
  leg2_deltaEtaSuperClusterTrackAtVtx = NAN;
  leg2_deltaPhiSuperClusterTrackAtVtx = NAN;
  leg2_sigmaEtaEta = NAN;
  leg2_sigmaIetaIeta = NAN;
  leg2_sigmaIphiIphi = NAN;
  leg2_numberOfMissingInnerHits = NAN;
  leg2_numberOfMissingOuterHits = NAN;
  leg2_numberOfTrackHits = NAN;
  leg2_passConversionVeto = NAN;
  leg2_TauEsVariant = NAN;
  leg2_numStrips = NAN;
  leg2_numHadrons = NAN;

  leg1_leptonType = -999;
  leg1_charge = -999;
  leg1_PFpdgId = -999;
  leg1_GENpdgId = -999;
  leg1_GENMOTHERpdgId = -999;
  leg2_leptonType = -999;
  leg2_charge = -999;
  leg2_PFpdgId = -999;
  leg2_GENpdgId = -999;
  leg2_GENMOTHERpdgId = -999;


  leg2_pt = NAN;
  leg2_gen_pt = NAN;
  leg2_genMother_pt = NAN;
  leg2_L1TrigObj_pt = NAN;
  leg2_L3TrigObj_pt = NAN;
  leg2_genJet_pt = NAN;
  leg1_pt = NAN;
  leg1_gen_pt = NAN;
  leg1_genMother_pt = NAN;
  leg1_L1TrigObj_pt = NAN;
  leg1_L3TrigObj_pt = NAN;
  leg1_genJet_pt = NAN;
  leg2_eta = NAN;
  leg2_gen_eta = NAN;
  leg2_genMother_eta = NAN;
  leg2_L1TrigObj_eta = NAN;
  leg2_L3TrigObj_eta = NAN;
  leg2_genJet_eta = NAN;
  leg1_eta = NAN;
  leg1_gen_eta = NAN;
  leg1_genMother_eta = NAN;
  leg1_L1TrigObj_eta = NAN;
  leg1_L3TrigObj_eta = NAN;
  leg1_genJet_eta = NAN;
  leg2_phi = NAN;
  leg2_gen_phi = NAN;
  leg2_genMother_phi = NAN;
  leg2_L1TrigObj_phi = NAN;
  leg2_L3TrigObj_phi = NAN;
  leg2_genJet_phi = NAN;
  leg1_phi = NAN;
  leg1_gen_phi = NAN;
  leg1_genMother_phi = NAN;
  leg1_L1TrigObj_phi = NAN;
  leg1_L3TrigObj_phi = NAN;
  leg1_genJet_phi = NAN;
  leg2_M = NAN;
  leg2_gen_M = NAN;
  leg2_genMother_M = NAN;
  leg2_L1TrigObj_M = NAN;
  leg2_L3TrigObj_M = NAN;
  leg2_genJet_M = NAN;
  leg1_M = NAN;
  leg1_gen_M = NAN;
  leg1_genMother_M = NAN;
  leg1_L1TrigObj_M = NAN;
  leg1_L3TrigObj_M = NAN;
  leg1_genJet_M = NAN;

 }

//////////////////////////////////////////////////
// ------------ method called once each job just before starting event loop  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginJob() {}

//////////////////////////////////////////////////
// ------------ method called once each job just after ending the event loop  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endJob() {}

//////////////////////////////////////////////////
// ------------ method called when starting to processes a run  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a run  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when starting to processes a luminosity block  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a luminosity block  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
  }

//define this as a plug-in
DEFINE_FWK_MODULE(FlatTupleGenerator);
