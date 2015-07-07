#ifndef DavisRunIITauTau_NtupleObjects_NtupleEvent_h
#define DavisRunIITauTau_NtupleObjects_NtupleEvent_h


//  include files
#include <memory>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleTrigObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"


typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;

class NtupleEvent
{



public:

  NtupleEvent();
  virtual ~NtupleEvent(){}


  // fillers 

	void fill(TupleCandidateEvent);
  void fillTriggerMatchesLeg1andLeg2(std::vector<NtupleTrigObject>,std::vector<NtupleTrigObject>);


  // helpers 

  ///////////////////
  // create a transverse mass
  // calculator given any
  // combination of the various
  // vector types floating around here

  template <class SomeVector, class AnotherVector>
  inline double GetTransverseMass(SomeVector V1, AnotherVector V2)
  {

    double pTxMET = sqrt(V1.x()*V1.x()+V1.y()*V1.y())*sqrt(V2.x()*V2.x()+V2.y()*V2.y());
    double CosDphi = cos(deltaPhi(V1.phi(), V2.phi()));
    double MtSq = (2 * pTxMET*(1-CosDphi));
    return sqrt(MtSq);

  }

  // getters

	int CandidateEventType() const; 
  float TauEsNumberSigmasShifted() const;
	NtupleLepton leg1() const; 
	NtupleLepton leg2() const; 
  std::vector<NtupleTrigObject> leg1_trigMatches() const; 
  std::vector<NtupleTrigObject> leg2_trigMatches() const; 
	std::vector<NtupleLepton> vetoElectron() const; 
 	std::vector<NtupleLepton> vetoMuon() const;
  std::vector<double> SVMass() const;
  std::vector<double> VISMass() const;
  int isOsPair() const;
  std::vector<double> MTmvaMET_leg1() const;
  std::vector<double> MTpfMET_leg1() const;
  std::vector<double> MTmvaMET_leg2() const;
  std::vector<double> MTpfMET_leg2() const;

  std::vector<reco::PFMET>  mvaMET() const;
  std::vector<pat::MET>  pfMET() const;

  std::vector<double>  pfMET_cov00() const;
  std::vector<double>  pfMET_cov01() const;
  std::vector<double>  pfMET_cov10() const;
  std::vector<double>  pfMET_cov11() const;

private:

	int m_CandidateEventType; 
  float m_TauEsNumberSigmasShifted;
  int m_isOsPair;
	NtupleLepton m_leg1; 
	NtupleLepton m_leg2; 
  std::vector<NtupleTrigObject> m_leg1_trigMatches; 
  std::vector<NtupleTrigObject> m_leg2_trigMatches; 
	std::vector<NtupleLepton> m_vetoElectron; 
 	std::vector<NtupleLepton> m_vetoMuon;
  std::vector<double> m_SVMass;
  std::vector<double> m_VISMass;
  /* for now these are just MT(leg1, MET) : later on we will want to rank leg1 & leg2 */
  std::vector<double> m_MTmvaMET_leg1;
  std::vector<double> m_MTpfMET_leg1;

  /* for now these are just MT(leg2, MET) : later on we will want to rank leg1 & leg2 */
  std::vector<double> m_MTmvaMET_leg2;
  std::vector<double> m_MTpfMET_leg2;
  std::vector<reco::PFMET>  m_mvaMET;
  std::vector<pat::MET>  m_pfMET;
  std::vector<double>  m_pfMET_cov00; // needed due to missing sig matrix in phys14 samples
  std::vector<double>  m_pfMET_cov01; // needed due to missing sig matrix in phys14 samples
  std::vector<double>  m_pfMET_cov10; // needed due to missing sig matrix in phys14 samples
  std::vector<double>  m_pfMET_cov11; // needed due to missing sig matrix in phys14 samples




};

typedef std::vector<NtupleEvent> NtupleEventCollection;

#endif
