#ifndef DavisRunIITauTau_NtupleObjects_NtuplePairIndependentInfo_h
#define DavisRunIITauTau_NtupleObjects_NtuplePairIndependentInfo_h


// system include files
#include <memory>



// needed by ntuple Muons producer
#include <vector>
#include <string>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleGenParticle.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;

class NtuplePairIndependentInfo
{



public:

  NtuplePairIndependentInfo();
  virtual ~NtuplePairIndependentInfo(){}

  // fillers 

	void fill_genParticle(NtupleGenParticle);


  // getters


  std::vector<NtupleGenParticle> genParticles() const; 
 

private:

  /* generator level particle records */
  std::vector<NtupleGenParticle> m_genParticles; 
 


};

typedef std::vector<NtuplePairIndependentInfo> NtuplePairIndependentInfoCollection;

#endif
