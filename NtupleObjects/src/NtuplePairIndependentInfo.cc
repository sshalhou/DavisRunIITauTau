#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "TLorentzVector.h"

NtuplePairIndependentInfo::NtuplePairIndependentInfo()
{

}

void NtuplePairIndependentInfo::fill_genParticle(NtupleGenParticle NgenPart)
  {
  	m_genParticles.push_back(NgenPart);

  };

void NtuplePairIndependentInfo::fill_jet(NtupleJet anNtupleJet)
  {
  	m_jets.push_back(anNtupleJet);

  };


std::vector<NtupleGenParticle> NtuplePairIndependentInfo::genParticles() const {return m_genParticles;}

std::vector<NtupleJet> NtuplePairIndependentInfo::jets() const {return m_jets;}
