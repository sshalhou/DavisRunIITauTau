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

	//void fill(TupleCandidateEvent);


  // getters


  std::vector<int> gen_IndexInRecord() const; 
  //std::vector<std::vector<int>> gen_daughterIndicesInRecord() const; 
  //std::vector<std::vector<int>> gen_motherIndicesInRecord() const; 
  std::vector<int> gen_pdgId() const; 
  std::vector<int> gen_status() const; 
  std::vector<LorentzVector> gen_p4() const; 
  std::vector<float> gen_vertex_x() const; 
  std::vector<float> gen_vertex_y() const; 
  std::vector<float> gen_vertex_z() const; 


private:

  /* generator level event record */
  std::vector<int> m_gen_IndexInRecord; /* index in original mini-aod collection */
  //std::vector<std::vector<int>> m_gen_daughterIndicesInRecord; /* indices of all daughters */
  //std::vector<std::vector<int>> m_gen_motherIndicesInRecord; /* indices of all mothers */
  std::vector<int> m_gen_pdgId;
  std::vector<int> m_gen_status;
  std::vector<LorentzVector> m_gen_p4;
  std::vector<float> m_gen_vertex_x;
  std::vector<float> m_gen_vertex_y;
  std::vector<float> m_gen_vertex_z;


};

typedef std::vector<NtuplePairIndependentInfo> NtuplePairIndependentInfoCollection;

#endif
