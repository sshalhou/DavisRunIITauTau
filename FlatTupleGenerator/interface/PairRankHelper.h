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

  std::vector<std::pair <std::size_t, NtupleEvent>> rank_pairs_BySumPt(std::vector<NtupleEvent>);


// fillers

  void process_pairs(std::vector<NtupleEvent>);
  void process_pairs_RANKDEMO(std::vector<NtupleEvent>);
// getters



private:

	std::vector<NtupleEvent> m_InputPairs; 			/* the unranked pairs */
    std::vector<NtupleEvent> m_OSpairsNoRank; 		/* the opposite sign unranked pairs */
    std::vector<NtupleEvent> m_SSpairsNoRank; 		/* the same sign unranked pairs */
	std::vector<bool> m_InvertLegs;					/* flags true if should invert leg0 <-> leg1 ordering in the pair (same index order as m_InputPairs) */
	std::vector<int> m_PairRanks;					/* the ordering Rank of each pair in m_InputPairs (same index order as m_InputPairs) */


};

#endif
