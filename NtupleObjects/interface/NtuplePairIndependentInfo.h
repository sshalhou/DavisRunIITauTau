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
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"


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

  /* fill pileUp info */
  void fill_pileUpInfo(edm::Handle<std::vector<PileupSummaryInfo> >, std::string, std::string); /* strings are mc path, data path */

  /* fill the generator event weight */
  void fill_generatorEventWeight(double);

  /* fill NUP */
  void fill_hepNUP(int);

  // getters

  std::vector<NtupleGenParticle> genParticles() const; 
  std::vector<NtupleJet> jets() const; 
  reco::Vertex  primaryVertex() const;
  int  numberOfGoodVertices() const;
  double puWeight() const;
  double puWeightM1() const;
  double puWeightP1() const;
  float NumPileupInt() const;
  float NumTruePileUpInt() const;
  float NumPileupIntM1() const;
  float NumTruePileUpIntM1() const;
  float NumPileupIntP1() const;
  float NumTruePileUpIntP1() const;
  double generatorEventWeight() const;
  int hepNUP() const;

private:

  /* generator level particle records */
  std::vector<NtupleGenParticle> m_genParticles; 
  std::vector<NtupleJet> m_jets; 
  
  /* vertex information */
  int m_PV_numberOfGoodVertices;
  reco::Vertex m_primaryVertex;

  /* PileUp info */
  double m_puWeight; 
  double m_puWeightM1;
  double m_puWeightP1;
  float m_NumPileupInt;
  float m_NumTruePileUpInt;
  float m_NumPileupIntM1;
  float m_NumTruePileUpIntM1;
  float m_NumPileupIntP1;
  float m_NumTruePileUpIntP1;

  /* generator weight */
  double m_generatorEventWeight;

  /* n partons at gen level */
  int m_hepNUP;

};

typedef std::vector<NtuplePairIndependentInfo> NtuplePairIndependentInfoCollection;

#endif
