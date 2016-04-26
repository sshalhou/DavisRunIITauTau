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
typedef std::vector<std::pair<std::string, float> >  stringFloatPairVec;

class NtupleEvent
{



public:

  NtupleEvent();
  virtual ~NtupleEvent(){}


  // fillers 

	void fill(TupleCandidateEvent);
  void fillTriggerMatchesLeg1andLeg2(std::vector<NtupleTrigObject>,std::vector<NtupleTrigObject>);
  void fillTriggerMatchesForEffLepton(  std::vector<NtupleTrigObject> );
  void fillL1IsoTauMatchInfoLeg1andLeg2(edm::Handle<l1extra::L1JetParticleCollection>);
  void fillL1IsoTauMatchInfoForEffLepton(edm::Handle<l1extra::L1JetParticleCollection>);


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


  /* Functions : isLeg1GoodForHLTPath and isLeg2GoodForHLTPath 
     string argument is an HLT path
     for the HLT summaries requested in ConfigTupleTriggers_cfi.py 
     return 1.0 if the leg is a good HLT lepton :
     (path wasAccepted && filter conditions met && trigger obj match)
     return 0.0 if a bad HLT lepton or if no summary was requested in  
     ConfigTupleTriggers_cfi.py 
     (note : can still find non-summary requested trig info using leg1_trigMatches & leg1_trigMatches)
  */  

  /* return the highest pt of all matched trigger objects to each reco leg */
  float leg1MaxPtTriggerObjMatch() const;  
  float leg2MaxPtTriggerObjMatch() const;  
  float EffLeptonMaxPtTriggerObjMatch(std::size_t) const;  /* arg is the index of the EffLepton */
   


  float isLeg1GoodForHLTPath(std::string) const;   /* for an HLT path, return 1 if the leg is good for that path */
  float isLeg2GoodForHLTPath(std::string) const;  
  float isEffLeptonGoodForHLTPath(std::string, std::size_t) const;   /* 2nd arg is index of EffLepton */



  stringVec isLeg1GoodForHLTPath_Labels() ;         /* return the list of HLT path names (requested in ConfigTupleTriggers_cfi) for which reco lepton is GOOD */
  stringVec isLeg2GoodForHLTPath_Labels() ;         
  stringVec isEffLeptonGoodForHLTPath_Labels(std::size_t) ;  /* return the list of HLT path names (requested in ConfigTupleTriggers_cfi) for which eff lepton at index (arg) is GOOD */



  void fillTriggerSummariesLeg1andLeg2(stringFloatPairVec , 
                                        stringFloatPairVec ); /* fill the member data */

  void fillTriggerSummariesEffLepton(stringFloatPairVec); /* fill the member data */



  // getters

	int CandidateEventType() const; 
  float TauEsNumberSigmasShifted() const;
	NtupleLepton leg1() const; 
	NtupleLepton leg2() const; 
  std::vector< NtupleLepton > EffLepton() const;


  std::vector<NtupleTrigObject> leg1_trigMatches() const; 
  std::vector<NtupleTrigObject> leg2_trigMatches() const; 
  std::vector < std::vector<NtupleTrigObject> > EffLepton_trigMatches() const; 

  std::vector <LorentzVector> leg1_L1IsoTauDR05Matches() const; 
  std::vector <LorentzVector> leg2_L1IsoTauDR05Matches() const; 
  std::vector < std::vector <LorentzVector> > EffLepton_L1IsoTauDR05Matches() const; 


	std::vector<NtupleLepton> vetoElectron() const; 
 	std::vector<NtupleLepton> vetoMuon() const;
  std::vector<double> SVMass() const;
  std::vector<double> SVTransverseMass() const;
  std::vector<double> VISMass() const;
  int isOsPair() const;
  std::vector<double> MTmvaMET_leg1() const;
  std::vector<double> MTpfMET_leg1() const;
  std::vector<double> MTpuppiMET_leg1() const;

  std::vector<double> MTmvaMET_leg2() const;
  std::vector<double> MTpfMET_leg2() const;
  std::vector<double> MTpuppiMET_leg2() const;

  std::vector<pat::MET>  mvaMET() const;
  std::vector<pat::MET>  pfMET() const;
  std::vector<pat::MET>  puppiMET() const;

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
  
  std::vector<NtupleLepton> m_EffLepton;


  std::vector<NtupleTrigObject> m_leg1_trigMatches; 
  std::vector<NtupleTrigObject> m_leg2_trigMatches; 
  std::vector < std::vector<NtupleTrigObject> > m_EffLepton_trigMatches; 

  std::vector <LorentzVector> m_leg1_L1IsoTauDR05Matches; 
  std::vector <LorentzVector> m_leg2_L1IsoTauDR05Matches; 
  std::vector < std::vector <LorentzVector> > m_EffLepton_L1IsoTauDR05Matches; 



	std::vector<NtupleLepton> m_vetoElectron; 
 	std::vector<NtupleLepton> m_vetoMuon;
  std::vector<double> m_SVMass;
  std::vector<double> m_SVTransverseMass;
  std::vector<double> m_VISMass;
  /* for now these are just MT(leg1, MET) : later on we will want to rank leg1 & leg2 */
  std::vector<double> m_MTmvaMET_leg1;
  std::vector<double> m_MTpfMET_leg1;
  std::vector<double> m_MTpuppiMET_leg1;

  /* for now these are just MT(leg2, MET) : later on we will want to rank leg1 & leg2 */
  std::vector<double> m_MTmvaMET_leg2;
  std::vector<double> m_MTpfMET_leg2;
  std::vector<double> m_MTpuppiMET_leg2;

  std::vector<pat::MET>  m_mvaMET;
  std::vector<pat::MET>  m_pfMET; 
  std::vector<pat::MET>  m_puppiMET; 
  std::vector<double>  m_pfMET_cov00; // needed due to missing sig matrix in phys14/Spring15 samples
  std::vector<double>  m_pfMET_cov01; // needed due to missing sig matrix in phys14/Spring15 samples
  std::vector<double>  m_pfMET_cov10; // needed due to missing sig matrix in phys14/Spring15 samples
  std::vector<double>  m_pfMET_cov11; // needed due to missing sig matrix in phys14/Spring15 samples
  stringFloatPairVec m_isLeg1GoodForHLTPath; /* pair of HLT path : 1.0 meeting reco leg1 accept+match+filter */
  stringFloatPairVec m_isLeg2GoodForHLTPath; /* pair of HLT path : 1.0 meeting reco leg2 accept+match+filter */
  std::vector < stringFloatPairVec > m_isEffLeptonGoodForHLTPath;

};

typedef std::vector<NtupleEvent> NtupleEventCollection;

#endif
