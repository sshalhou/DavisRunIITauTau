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
	float raw_electronMVA() const; 
	float passFail_electronMVA() const; 




private:


	////////////////////////////////////////////////
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
    float       	m_raw_electronMVA;					//  value of electron MVA score
    int 			m_passFail_electronMVA;              // pass fail of electron MVA 

    										//
	//////////////////////////////////////////////////
	// meaniningful for taus	
	//////////////////////////////////////////////////
													//
	//LorentzVector 	m_pfJetRef_p4; 					//	 	the reco pf jet 4-vector
	//LorentzVector 	m_genJet;						//		the pat-matched genJet (for taus)	



 



};

typedef std::vector<NtupleLepton> NtupleLeptonCollection;

#endif
