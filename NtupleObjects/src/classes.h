#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleGenParticle.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"

#include "DataFormats/Common/interface/Wrapper.h"

struct dictionary
{
  NtupleLepton dummy0;
  edm::Wrapper<NtupleLeptonCollection> dummy1;	
  NtupleEvent dummy2;
  edm::Wrapper<NtupleEventCollection> dummy3;	  
  NtuplePairIndependentInfo dummy4;
  edm::Wrapper<NtuplePairIndependentInfoCollection> dummy5;	
  NtupleGenParticle dummy6;
  edm::Wrapper<NtupleGenParticleCollection> dummy7;	
  NtupleJet dummy8;
  edm::Wrapper<NtupleJetCollection> dummy9;	  
};

