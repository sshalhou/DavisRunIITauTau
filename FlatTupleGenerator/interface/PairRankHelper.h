#ifndef DavisRunIITauTau_FlatTupleGenerator_PairRankHelper_h
#define DavisRunIITauTau_FlatTupleGenerator_PairRankHelper_h


/* class PairRankHelper :

	object to hold a vector<NtupleEvent> object
	along with information related to (and functions to determine) 
	candidate leg ordering
	and the pair's rank within the overall event


the ultimate design goal is that in the TTree we can access the best pair using rank==0, the 2nd
best by rank == 1 etc. 

- Shalhout
*/



// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// needed by ntuple Tau producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TauAnalysis/SVfitStandalone/interface/SVfitStandaloneAlgorithm.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
 

typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;
typedef std::vector<edm::InputTag> VInputTag;

/* ranking comparator */

/* the double is the sumPt */
bool NtupleRankCompare_SumPt(const std::pair<double, NtupleEvent>& , const std::pair<double, NtupleEvent>& ) ;

/* the double[0] = leg1 isol, while double[1] = leg2 isol */


/////////////////////////////////////
class IsolThenPtComparator {

public:

  IsolThenPtComparator(bool, bool);
  virtual ~IsolThenPtComparator(){}

  /* the key operator for the IsolThenPt based Comparator */
  bool operator()( const std::pair<std::vector<double>, NtupleEvent>& p1, const std::pair<std::vector<double>, NtupleEvent>& p2) 
  {
    //  never compare non-similar lepton flavor pairs (i.e. eTau vs muTau is invalid)
    assert ( p1.second.CandidateEventType() == p2.second.CandidateEventType() );

    ////////////////////////////////////////////////////
    // the H2Tau 2015 default
    // ranking logic is leg1 isolation, then leg1 pt,
    // then leg2 isolation, then leg2 pt
    // -- special care needs to be used for e + mu channel
    // where leg1 = muon ONLY FOR RANKING, and is electron in all other cases
    ////////////////////////////////////////////////////
   
    ///////////////
    // begin comparsion logic :

    //////////////////////////////////////////////////
    // logic for non e+mu channels
    //////////////////////////////////////////////////
    if(p1.second.CandidateEventType() != TupleCandidateEventTypes::EleMuon)
    {
      // compare leg1 isolations 1st, these are already set to first by getIsolOfLeg1 in init function
      if(p1.first[0] != p2.first[0] && p1.first[0]!=-999)
      {  
        if(m_leg1_isSmallerMoreIsolated) return p1.first[0] < p2.first[0]; 
        else return p1.first[0] > p2.first[0]; 
      } 

      // if equal leg1 isolations go to leg1 pT
      else if(p1.second.leg1().pt() != p2.second.leg1().pt())  return (p1.second.leg1().pt() > p2.second.leg1().pt());

      // if equal leg1 pT go to leg2 isolations
      else if(p1.first[1] != p2.first[1] && p2.first[1]!=-999)  
      {
         if(m_leg2_isSmallerMoreIsolated) return p1.first[1] < p2.first[1]; 
         else return p1.first[1] > p2.first[1]; 
      }
      // if equal leg 2 isol go to leg2 pT
      else if(p1.second.leg2().pt() != p2.second.leg2().pt())  return (p1.second.leg2().pt() > p2.second.leg2().pt());

      // finally just return true since the are the same pair and order does not matter
      else return 1;
    }
    //////////////////////////////////////////////////

    //////////////////////////////////////////////////
    // logic for  e+mu channels
    //////////////////////////////////////////////////
    else 
    {

      // 1st compare muon (leg2) isolations :
      if(p1.first[1] != p2.first[1] && p2.first[1]!=-999)  
      {
        if(m_leg2_isSmallerMoreIsolated) return p1.first[1] < p2.first[1]; 
        else return p1.first[1] > p2.first[1]; 
      }

      // next compare muon (leg2) pT :
      else if(p1.second.leg2().pt() != p2.second.leg2().pt())  return (p1.second.leg2().pt() > p2.second.leg2().pt());

      // next compare electron (leg1) isolations :
      if(p1.first[0] != p2.first[0] && p1.first[0]!=-999)  
      {
        if(m_leg1_isSmallerMoreIsolated) return p1.first[0] < p2.first[0];  
        else return p1.first[0] > p2.first[0]; 
      }

      // next compare electron (leg1) pT :
      else if(p1.second.leg1().pt() != p2.second.leg1().pt())  return (p1.second.leg1().pt() > p2.second.leg1().pt());

      // finally just return true since the are the same pair and order does not matter
      else return 1;

    }
    //////////////////////////////////////////////////

  } // operator

  private:
    
    bool m_leg1_isSmallerMoreIsolated;
    bool m_leg2_isSmallerMoreIsolated;


};
/////////////////////////////////////


class PairRankHelper {


public:

  PairRankHelper();
  virtual ~PairRankHelper(){}

// helpers

  void process_pairs_SumPtRank();
  void process_pairs_IsolRank();

  /* return sumPt or isolation product*/

  double getSumPt(NtupleEvent);
  std::vector<double> getIsolOfLeg1andLeg2(NtupleEvent,std::string, std::string, std::string);


  /* for sumPt ranking */
  void init(std::vector<NtupleEvent>); 
  
  /* for isolation ranking note : the 3 strings are passed to 
  electron.relativeIsol(), muon.relativeIsol(), tau.tauID() 
  and bools for isSmallerValueMoreIsolated (leg1,leg2)
  in that order  */

  void init(std::vector<NtupleEvent>,std::string, std::string, std::string, bool, bool); 

// getters

  std::vector<std::pair<std::size_t, NtupleEvent>> returnRankedPairVec(); /* return ranked ranking:pair vector m_finalRanking */


private:

  /* things need some cleanup since H2Tau method is different from what KLUB described */

  std::string eIsol_;
  std::string muIsol_;
  std::string tauID_;
  std::vector<std::pair <std::size_t, NtupleEvent>> m_finalRanking; /* the final ranked rank:LeptonPair std::pair */
  std::vector< std::pair<double, NtupleEvent> > m_CriterionLepPair_SumPt;
  std::vector< std::pair<std::vector<double>, NtupleEvent> > m_CriterionLepPair_Isol;





};

#endif
