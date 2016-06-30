//
// Filter module to pick only eTau, muTau, or eMu events
// (based on number of possible pairs present)
// given collections of pat::Tau, pat::Electron, and pat::Muon
// no lepton-parameter cuts are applied at this filter level
// just a simple pair count

#ifndef DavisRunIITauTau_CustomFilters_HiggsCandidateCountFilter_h
#define DavisRunIITauTau_CustomFilters_HiggsCandidateCountFilter_h

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"

namespace pat {


  class HiggsCandidateCountFilter : public edm::EDFilter {

    public:

      explicit HiggsCandidateCountFilter(const edm::ParameterSet & iConfig);
      virtual ~HiggsCandidateCountFilter();
      typedef std::vector<edm::InputTag> vInputTag;

    private:

      virtual bool filter(edm::Event & iEvent, const edm::EventSetup & iSetup);

    private:

      vInputTag electronTags_;
      std::vector<edm::EDGetTokenT< edm::View< pat::Electron > > > electronSources_;

      vInputTag muonTags_;
      std::vector<edm::EDGetTokenT< edm::View< pat::Muon > > > muonSources_;

      vInputTag tauTags_;
      std::vector<edm::EDGetTokenT< edm::View< pat::Tau > > > tauSources_;

      bool countElectronElectrons_;
      bool countElectronMuons_;
      bool countElectronTaus_;
      bool countMuonMuons_;
      bool countMuonTaus_;
      bool countTauTaus_;
      std::string tauMVAfilter_EleTau_; 
      std::string tauMVAfilter_MuonTau_; 
      std::string tauMVAfilter_TauTau_; 
      std::string tauIsofilter_;
      std::vector<std::string> hlt_Filter_;

  };




template<typename T>
bool Davis_checkTriggerPathAccept(T lep_, std::vector<std::string> hlt_Filter_)
{

  /* format the trigger paths we want to check */

  std::vector <std::string> triggerSummaryChecksMod_;
  triggerSummaryChecksMod_.clear();

  for(std::size_t tt = 0; tt<hlt_Filter_.size(); ++tt)
  {

    std::string temp__ = "AcceptWithPreScale_" + hlt_Filter_[tt];
    temp__.erase(temp__.find("_v"),temp__.length());
    triggerSummaryChecksMod_.push_back(temp__);

  }

  // tauToCheck.userFloatNames()
  ///////////////////////////////////////
  for (std::size_t ii = 0; ii < lep_.userFloatNames().size(); ii ++ )
  {
    std::string test_ = lep_.userFloatNames()[ii];
    std::string testOrig_ = lep_.userFloatNames()[ii];

    if(test_.find("AcceptWithPreScale_") != std::string::npos)
    {
      test_.erase(test_.find("_v"),test_.length());

      for(std::size_t k = 0; k < triggerSummaryChecksMod_.size(); ++k)
      {
        if(test_ == triggerSummaryChecksMod_[k])
        {
          if(lep_.userFloat(testOrig_) == 1.0) return 1;
        }
      }              
    }
  }
  ///////////////////////////////////////
  // if made it here there was no match
  return 0;
}


}

#endif