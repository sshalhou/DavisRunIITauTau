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
typedef std::vector<std::pair<std::string, float> >  stringFloatPairVec;

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


  stringVec HLTAcceptedPath_Labels() ;     		 /* return the accepted HLT path names  */
  floatVec  HLTAcceptedPath_preScales() ;        /* return  the available jec SFs */
  
  /* note HLTpath now supports _v* version wildcards */
  float HLTpath(std::string) const;              /* return the PreScale for accepted path strings return 0 (not accepted) if not available */
 

  stringVec relativeIsol_Labels(); 			/* return the relativeIsolation names  */
  floatVec relativeIsol_Values(); 			/* return the relativeIsolation values  */
  float relativeIsol(std::string) const;          /* return the value for valid name strings assert if not available */


  stringVec rho_Labels(); 			/* return the rho names  */
  floatVec rho_Values(); 			/* return the rho values  */
  float rho(std::string) const;          /* return the rho value for valid name strings assert if not available */


  stringVec tauID_Labels(); 			/* return the tauID (including isolations) names  */
  floatVec tauID_Values(); 			/* return the tauID values  */
  float tauID(std::string) const;          /* return the tauID value for valid name strings assert if not available */


  // getters

  	float pt() const; 
  	float eta() const; 
	int leptonType() const; 
	LorentzVector p4() const; 
	LorentzVector gen_p4() const; 
	LorentzVector genMother_p4() const; 
	float dz() const; 
	float dxy() const; 
	float EffectiveArea() const; 
	int charge() const; 
	int PFpdgId() const; 
	int GENpdgId() const; 
	int GENMOTHERpdgId() const; 
	LorentzVector 	genJet_p4() const;
	int genJet_pdgId() const;

	float ZimpactTau() const;
	float numStrips() const;
	float numHadrons() const;
	int   decayMode() const;
	float dzTauVertex() const;
	float raw_electronMVA() const; 
	float category_electronMVA() const;
	float passFail_electronMVA80() const; 
	float passFail_electronMVA90() const; 
    float passFail_electronCutBasedID() const;   
    float ooEmooP() const;         				
    float full5x5_sigmaIetaIeta() const;   
	float TauEsVariant() const; 
	float ElectronEsVariant() const; 
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
	stringFloatPairVec m_HLTPaths;                     //  pair pathName : preScale 
	stringFloatPairVec m_relativeIsolations;           //  pair relativeIsolation name : value 
	stringFloatPairVec m_rhos;                         //  pair rho name : value 
	float			m_EffectiveArea; 				//  EffectiveArea (for e, mu) pulled from lepton UserFloat data
	int 			m_charge;						//	charge
    int 			m_PFpdgId;  					//	the pdg ID attached to the PF particle
	int 			m_GENpdgId;						//	the pdg ID of the default pat-matched gen particle	
	int 			m_GENMOTHERpdgId;				//	the pdg ID of the default pat-matched gen particle's mother	
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
    float m_category_electronMVA;						//  category of electron MVA score
    float m_passFail_electronMVA80;         			//  pass fail of electron MVA 
    float m_passFail_electronMVA90;         			//  pass fail of electron MVA 
    float m_passFail_electronCutBasedID;         		//  pass fail of electron cut-based veto ID 
    float m_ooEmooP;         							//  used for electron cut-based veto ID 
    float m_full5x5_sigmaIetaIeta;         				//  used for electron cut-based veto ID 
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
    float m_ElectronEsVariant;						//  -1 if ElectronEs DOWN, +1 if UP, 0 if Nominal

	//////////////////////////////////////////////////
	// paramenters meaningful for taus only
	//////////////////////////////////////////////////
    float m_TauEsVariant;							//  -1 if TauEs DOWN, +1 if UP, 0 if Nominal
	LorentzVector 	m_genJet_p4;					//  the pat-matched genJet p4
	int m_genJet_pdgId;								//  the pat-matched genJet pdgId
	float m_ZimpactTau; 							// tau-event vertex match quality parameter
	float m_numStrips;								//  number strips
	float m_numHadrons;								//	number hadrons
	int m_decayMode; 								//  tau decay mode code
	stringFloatPairVec m_tauIDs;                    //  pair rho name : value 
	float m_dzTauVertex; 							//  tau.z - vertex.z





 



};

typedef std::vector<NtupleLepton> NtupleLeptonCollection;

#endif
