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
      std::vector<edm::EDGetTokenT<reco::CandidateView > > electronSources_;

      vInputTag muonTags_;
      std::vector<edm::EDGetTokenT<reco::CandidateView > > muonSources_;

      vInputTag tauTags_;
      std::vector<edm::EDGetTokenT<reco::CandidateView > > tauSources_;

    
      bool countElectronElectrons_;
      bool countElectronMuons_;
      bool countElectronTaus_;
      bool countMuonMuons_;
      bool countMuonTaus_;
      bool countTauTaus_;
  };



}

#endif