#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "TLorentzVector.h"

NtuplePairIndependentInfo::NtuplePairIndependentInfo()
{
	m_PV_numberOfGoodVertices = 0;

}

void NtuplePairIndependentInfo::fill_genParticle(NtupleGenParticle NgenPart)
  {
  	m_genParticles.push_back(NgenPart);

  };

void NtuplePairIndependentInfo::fill_jet(NtupleJet anNtupleJet)
  {
  	m_jets.push_back(anNtupleJet);

  };


 void NtuplePairIndependentInfo::fill_vertexInfo(reco::Vertex vtx0, unsigned int collectionSize)
{
	m_PV_numberOfGoodVertices = collectionSize;
	m_primaryVertex = vtx0;
}



std::vector<NtupleGenParticle> NtuplePairIndependentInfo::genParticles() const {return m_genParticles;}
std::vector<NtupleJet> NtuplePairIndependentInfo::jets() const {return m_jets;}
reco::Vertex  NtuplePairIndependentInfo::primaryVertex() const {return m_primaryVertex;}
int NtuplePairIndependentInfo::numberOfGoodVertices() const {return m_PV_numberOfGoodVertices;}