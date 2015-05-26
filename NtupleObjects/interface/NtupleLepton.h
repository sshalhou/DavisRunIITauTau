#ifndef DavisRunIITauTau_NtupleObjects_NtupleLepton_h
#define DavisRunIITauTau_NtupleObjects_NtupleLepton_h


// system include files
#include <memory>



// needed by ntuple Muons producer
#include <vector>
#include <string>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;

class NtupleLepton
{



public:

  NtupleLepton();
  virtual ~NtupleLepton(){}

  // fillers 

  void fill(TupleLepton);
  void fill(pat::Electron);
  void fill(pat::Muon);
  void fill(pat::Tau);

  // helpers

  void fillGenLeptonInfo(reco::GenParticle);
  void userFloatVectorParser(stringVec & ,floatVec &);
  void printLEP();

  // getters

	int leptonType() const; 
	LorentzVector p4() const; 
	LorentzVector gen_p4() const; 
	LorentzVector genMother_p4() const; 
	float dz() const; 
	float dxy() const; 
	stringVec HLTacceptedPaths() const; 
	floatVec HLTacceptedPathPreScales() const; 
	float EffectiveArea() const; 
	int charge() const; 
	int PFpdgId() const; 
	int GENpdgId() const; 
	int GENMOTHERpdgId() const; 
	stringVec L1acceptedFilters() const; 
	float L1TrigObjRecoObjDeltaR() const; 
	LorentzVector L1TrigObj_p4() const; 
	stringVec L3acceptedFilters() const; 
	float L3TrigObjRecoObjDeltaR() const; 
	LorentzVector L3TrigObj_p4() const; 
	stringVec pathSummary_isBOTH() const; 
	stringVec pathSummary_isL3() const; 
	stringVec pathSummary_isLF() const; 
	stringVec pathSummary_filterListPassed() const; 
	stringVec relativeIsol_Labels() const; 
	floatVec relativeIsol_Values() const; 
	stringVec rho_Labels() const; 
	floatVec rho_Values() const; 
	LorentzVector 	genJet_p4() const;
	float numStrips() const;
	float numHadrons() const;
	float raw_electronMVA() const; 
	float passFail_electronMVA() const; 
	float TauEsVariant() const; 
	float IP() const; 								
	float IPerror() const; 							
	float PUchargedHadronIso() const; 					
	float chargedHadronIso() const; 			
	float neutralHadronIso() const; 			
	float photonIso() const; 			
	float DepositR03ECal() const; 	
	float DepositR03Hcal() const; 	
	float DepositR03TrackerOfficial() const; 	
	float isGlobalMuon() const; 	
	float isGoodGlobalMuon() const; 	
	float passesMediumMuonId() const; 	
	float isLooseMuon() const; 	
	float isPFMuon() const; 	
	float isSoftMuon() const; 	
	float isTightMuon() const; 	
	float isTrackerMuon() const; 	
	float muonCombQualChi2LocalPosition() const; 	
	float muonCombQualTrkKink() const; 	
	float muonGlobalTrackNormChi2() const; 	
	float muonInnerTrkValidFraction() const; 	
	float muonSegmentCompatibility() const; 	
	float SuperClusterEta() const;
	float hadronicOverEm() const;
	float isEB() const;
	float isEBEEGap() const;
	float isEBEtaGap() const;
	float isEBPhiGap() const;
	float isEE() const;
	float isEEDeeGap() const;
	float isEERingGap() const;
	float deltaEtaSuperClusterTrackAtVtx() const;
	float deltaPhiSuperClusterTrackAtVtx() const;
	float sigmaEtaEta() const;
	float sigmaIetaIeta() const;
	float sigmaIphiIphi() const;
	float numberOfMissingInnerHits() const;
	float numberOfMissingOuterHits() const;
	float numberOfTrackHits() const;
	float passConversionVeto() const;
	float againstElectronLoose() const;
	float againstElectronLooseMVA5() const;
	float againstElectronMVA5category() const;
	float againstElectronMVA5raw() const;
	float againstElectronMedium() const;
	float againstElectronMediumMVA5() const;
	float againstElectronTight() const;
	float againstElectronTightMVA5() const;
	float againstElectronVLooseMVA5() const;
	float againstElectronVTightMVA5() const;
	float againstMuonLoose() const;
	float againstMuonLoose2() const;
	float againstMuonLoose3() const;
	float againstMuonLooseMVA() const;
	float againstMuonMVAraw() const;
	float againstMuonMedium() const;
	float againstMuonMedium2() const;
	float againstMuonMediumMVA() const;
	float againstMuonTight() const;
	float againstMuonTight2() const;
	float againstMuonTight3() const;
	float againstMuonTightMVA() const;
	float byCombinedIsolationDeltaBetaCorrRaw3Hits() const;
	float byIsolationMVA3newDMwLTraw() const;
	float byIsolationMVA3newDMwoLTraw() const;
	float byIsolationMVA3oldDMwLTraw() const;
	float byIsolationMVA3oldDMwoLTraw() const;
	float byLooseCombinedIsolationDeltaBetaCorr3Hits() const;
	float byLooseIsolationMVA3newDMwLT() const;
	float byLooseIsolationMVA3newDMwoLT() const;
	float byLooseIsolationMVA3oldDMwLT() const;
	float byLooseIsolationMVA3oldDMwoLT() const;
	float byMediumCombinedIsolationDeltaBetaCorr3Hits() const;
	float byMediumIsolationMVA3newDMwLT() const;
	float byMediumIsolationMVA3newDMwoLT() const;
	float byMediumIsolationMVA3oldDMwLT() const;
	float byMediumIsolationMVA3oldDMwoLT() const;
	float byTightCombinedIsolationDeltaBetaCorr3Hits() const;
	float byTightIsolationMVA3newDMwLT() const;
	float byTightIsolationMVA3newDMwoLT() const;
	float byTightIsolationMVA3oldDMwLT() const;
	float byTightIsolationMVA3oldDMwoLT() const;
	float byVLooseIsolationMVA3newDMwLT() const;
	float byVLooseIsolationMVA3newDMwoLT() const;
	float byVLooseIsolationMVA3oldDMwLT() const;
	float byVLooseIsolationMVA3oldDMwoLT() const;
	float byVTightIsolationMVA3newDMwLT() const;
	float byVTightIsolationMVA3newDMwoLT() const;
	float byVTightIsolationMVA3oldDMwLT() const;
	float byVTightIsolationMVA3oldDMwoLT() const;
	float byVVTightIsolationMVA3newDMwLT() const;
	float byVVTightIsolationMVA3newDMwoLT() const;
	float byVVTightIsolationMVA3oldDMwLT() const;
	float byVVTightIsolationMVA3oldDMwoLT() const;
	float chargedIsoPtSum() const;
	float decayModeFinding() const;
	float decayModeFindingNewDMs() const;
	float neutralIsoPtSum() const;
	float puCorrPtSum() const;

private:

	//////////////////////////////////////////////////
	// paramenters meaningful for more than 1 lep type
	//////////////////////////////////////////////////
													//
	int 			m_leptonType;					//	the lepton type code defined in TupleObjects/TupleLeptonTypes.h
	LorentzVector 	m_p4; 							//	the reco 4-vector (all ntuple level corrections applied) 
	LorentzVector 	m_gen_p4;						//	the pat-matched gen particle 4-vector
	LorentzVector 	m_genMother_p4;					//	the pat-matched gen particle's mother's 4-vector
	float 		  	m_dz;							//	dz	- this is pulled from lepton UserFloat data
	float 		  	m_dxy;							//  dxy - this is pulled from lepton UserFloat data
	stringVec		m_HLTacceptedPaths;     		//  AcceptWithPreScale prefixed userFloat labels (hlt accept paths for the event)
	floatVec		m_HLTacceptedPathPreScales;     //	AcceptWithPreScale prefixed userFloat floats (preScale of accept paths, same index as paths)
	float			m_EffectiveArea; 				//  EffectiveArea (for e, mu) pulled from lepton UserFloat data
	int 			m_charge;						//	charge
    int 			m_PFpdgId;  					//	the pdg ID attached to the PF particle
	int 			m_GENpdgId;						//	the pdg ID of the default pat-matched gen particle	
	int 			m_GENMOTHERpdgId;				//	the pdg ID of the default pat-matched gen particle's mother	
	stringVec		m_L1acceptedFilters;     		//  best match L1 trig object accepted filters from userFloat labels
	float 			m_L1TrigObjRecoObjDeltaR;		//  min DR to a L1 trig object from userFloats
	LorentzVector	m_L1TrigObj_p4;					//  best match L1 trig obj p4  from userFloats
	stringVec		m_L3acceptedFilters;     		//  best match L3 trig object accepted filters from userFloat labels
	float 			m_L3TrigObjRecoObjDeltaR;		//  min DR to a L3 trig object from userFloats
	LorentzVector	m_L3TrigObj_p4;					//  best match L3 trig obj p4  from userFloats
	stringVec		m_pathSummary_isBOTH;			//	path summary variable names that have isBOTH==1 from userFloat labels & data	
	stringVec		m_pathSummary_isL3;				//	path summary variable names that have isL3==1 from userFloat labels & data	
	stringVec		m_pathSummary_isLF;				//	path summary variable names that have isLF==1 from userFloat labels & data	
	stringVec		m_pathSummary_filterListPassed;	//	path summary variable names that have filterListPassed==1 from userFloat labels & data	
	stringVec		m_relativeIsol_Labels;			// 	label strings of isolations in userFloat labels
    floatVec		m_relativeIsol_Values;			// 	value floats of isolations in userFloat data (same index order as labels)
    stringVec       m_rho_Labels;					//  label strings of rho in userFloat labels
    floatVec       	m_rho_Values;					//  value floats of rho in userFloat data (same index as rho strings)
	float m_IP;										//  for ele or muon dB(pat::X::PV3D)
	float m_IPerror;								//  for ele or muon edB(pat::X::PV3D)
	float m_PUchargedHadronIso;						//  iso parameter
	float m_chargedHadronIso;						//  iso parameter
	float m_neutralHadronIso;						//  iso parameter
	float m_photonIso;								//  iso parameter


	//////////////////////////////////////////////////
	// paramenters meaningful for muons only
	//////////////////////////////////////////////////
													//
	float m_DepositR03ECal;							//
	float m_DepositR03Hcal;							//
	float m_DepositR03TrackerOfficial;				//
	float m_isGlobalMuon;							// pat::Muon isGlobalMuon
	float m_isGoodGlobalMuon;						// pat::Muon isGlobalMuon + additional cuts
	float m_passesMediumMuonId;						// proposed meduim ID for Run II muons
	float m_isLooseMuon;							// pat::Muon isLooseMuon
	float m_isPFMuon;								// pat::Muon isPFMuon
	float m_isSoftMuon;								// pat::Muon isSoftMuon(first_vertex)
	float m_isTightMuon;							// pat::Muon isTightMuon(first_vertex)
	float m_isTrackerMuon;							// pat::Muon isTrackerMuon
	float m_muonCombQualChi2LocalPosition;			// used in medium muon ID
	float m_muonCombQualTrkKink;					// used in medium muon ID
	float m_muonGlobalTrackNormChi2;				// used in medium muon ID
	float m_muonInnerTrkValidFraction;				// used in medium muon ID
	float m_muonSegmentCompatibility;				// used in medium muon ID




	//////////////////////////////////////////////////
	// paramenters meaningful for electrons only
	//////////////////////////////////////////////////
    float m_raw_electronMVA;						//  value of electron MVA score
    float m_passFail_electronMVA;         			//  pass fail of electron MVA 
	float m_SuperClusterEta;
	float m_hadronicOverEm;
	float m_isEB;
	float m_isEBEEGap;
	float m_isEBEtaGap;
	float m_isEBPhiGap;
	float m_isEE;
	float m_isEEDeeGap;
	float m_isEERingGap;
	float m_deltaEtaSuperClusterTrackAtVtx;
	float m_deltaPhiSuperClusterTrackAtVtx;
	float m_sigmaEtaEta;
	float m_sigmaIetaIeta;
	float m_sigmaIphiIphi;
	float m_numberOfMissingInnerHits;
	float m_numberOfMissingOuterHits;
	float m_numberOfTrackHits;
	float m_passConversionVeto;

	//////////////////////////////////////////////////
	// paramenters meaningful for taus only
	//////////////////////////////////////////////////
    float m_TauEsVariant;							//  -1 if TauEs DOWN, +1 if UP, 0 if Nominal
	LorentzVector 	m_genJet_p4;					//  the pat-matched genJet p4
	float m_numStrips;								//  number strips
	float m_numHadrons;								//	number hadrons
	float m_againstElectronLoose;					//  a tauID (long list follows should probably trim!)
	float m_againstElectronLooseMVA5;
	float m_againstElectronMVA5category;
	float m_againstElectronMVA5raw;
	float m_againstElectronMedium;
	float m_againstElectronMediumMVA5;
	float m_againstElectronTight;
	float m_againstElectronTightMVA5;
	float m_againstElectronVLooseMVA5;
	float m_againstElectronVTightMVA5;
	float m_againstMuonLoose;
	float m_againstMuonLoose2;
	float m_againstMuonLoose3;
	float m_againstMuonLooseMVA;
	float m_againstMuonMVAraw;
	float m_againstMuonMedium;
	float m_againstMuonMedium2;
	float m_againstMuonMediumMVA;
	float m_againstMuonTight;
	float m_againstMuonTight2;
	float m_againstMuonTight3;
	float m_againstMuonTightMVA;
	float m_byCombinedIsolationDeltaBetaCorrRaw3Hits;
	float m_byIsolationMVA3newDMwLTraw;
	float m_byIsolationMVA3newDMwoLTraw;
	float m_byIsolationMVA3oldDMwLTraw;
	float m_byIsolationMVA3oldDMwoLTraw;
	float m_byLooseCombinedIsolationDeltaBetaCorr3Hits;
	float m_byLooseIsolationMVA3newDMwLT;
	float m_byLooseIsolationMVA3newDMwoLT;
	float m_byLooseIsolationMVA3oldDMwLT;
	float m_byLooseIsolationMVA3oldDMwoLT;
	float m_byMediumCombinedIsolationDeltaBetaCorr3Hits;
	float m_byMediumIsolationMVA3newDMwLT;
	float m_byMediumIsolationMVA3newDMwoLT;
	float m_byMediumIsolationMVA3oldDMwLT;
	float m_byMediumIsolationMVA3oldDMwoLT;
	float m_byTightCombinedIsolationDeltaBetaCorr3Hits;
	float m_byTightIsolationMVA3newDMwLT;
	float m_byTightIsolationMVA3newDMwoLT;
	float m_byTightIsolationMVA3oldDMwLT;
	float m_byTightIsolationMVA3oldDMwoLT;
	float m_byVLooseIsolationMVA3newDMwLT;
	float m_byVLooseIsolationMVA3newDMwoLT;
	float m_byVLooseIsolationMVA3oldDMwLT;
	float m_byVLooseIsolationMVA3oldDMwoLT;
	float m_byVTightIsolationMVA3newDMwLT;
	float m_byVTightIsolationMVA3newDMwoLT;
	float m_byVTightIsolationMVA3oldDMwLT;
	float m_byVTightIsolationMVA3oldDMwoLT;
	float m_byVVTightIsolationMVA3newDMwLT;
	float m_byVVTightIsolationMVA3newDMwoLT;
	float m_byVVTightIsolationMVA3oldDMwLT;
	float m_byVVTightIsolationMVA3oldDMwoLT;
	float m_chargedIsoPtSum;
	float m_decayModeFinding;
	float m_decayModeFindingNewDMs;
	float m_neutralIsoPtSum;
	float m_puCorrPtSum;




 



};

typedef std::vector<NtupleLepton> NtupleLeptonCollection;

#endif
