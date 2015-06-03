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
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
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
	void fill_jet(NtupleJet);

  /* args are the 0th element in the vertex collection after quality cuts, size of the post-quality cut collection*/
  void fill_vertexInfo(reco::Vertex, unsigned int);


  // getters


  std::vector<NtupleGenParticle> genParticles() const; 
  std::vector<NtupleJet> jets() const; 
  reco::Vertex  primaryVertex() const;


private:

  /* generator level particle records */
  std::vector<NtupleGenParticle> m_genParticles; 
  std::vector<NtupleJet> m_jets; 
  /* vertex information */
  int m_PV_numberOfGoodVertices;
  reco::Vertex m_primaryVertex;



};

typedef std::vector<NtuplePairIndependentInfo> NtuplePairIndependentInfoCollection;

#endif
