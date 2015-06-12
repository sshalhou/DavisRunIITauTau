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

bool NtupleRankCompare(const std::pair<double, NtupleEvent>& , const std::pair<double, NtupleEvent>& ) ;


class PairRankHelper {


public:

  PairRankHelper();
  virtual ~PairRankHelper(){}

// helpers




  void process_pairs();
  void print_ranking();

  /* return sumPt or isolation product*/

  double getSumPt(NtupleEvent);
  double getIsolProduct(NtupleEvent,std::string, std::string, std::string);


  /* for sumPt ranking */
  void init(std::vector<NtupleEvent>); 
  
  /* for isolation ranking note : the 3 strings are passed to 
  electron.relativeIsol(), muon.relativeIsol(), tau.tauID() in that order  */

  void init(std::vector<NtupleEvent>,std::string, std::string, std::string); 

// getters

  std::vector<std::pair<std::size_t, NtupleEvent>> returnRankedPairVec(); /* return ranked ranking:pair vector m_finalRanking */


private:

	std::vector<std::pair<double, NtupleEvent>> m_CriterionLepPair; /* vec<std::pair> of the criterion for ranking and the pair */
	std::vector<std::pair <double, NtupleEvent>> m_OSRanking; /* the OS ranked rank:LeptonPair std::pair */
	std::vector<std::pair <double, NtupleEvent>> m_SSRanking; /* the SS ranked rank:LeptonPair std::pair */
   	std::vector<std::pair <std::size_t, NtupleEvent>> m_finalRanking; /* the final ranked rank:LeptonPair std::pair */
   	std::vector<std::pair <double, NtupleEvent>> m_finalRankedCriterion; /* the final ranked criterion:LeptonPair std::pair */






};

#endif
