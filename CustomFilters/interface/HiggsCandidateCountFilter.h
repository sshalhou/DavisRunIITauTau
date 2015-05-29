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


namespace pat {


  class HiggsCandidateCountFilter : public edm::EDFilter {

    public:

      explicit HiggsCandidateCountFilter(const edm::ParameterSet & iConfig);
      virtual ~HiggsCandidateCountFilter();

    private:

      virtual bool filter(edm::Event & iEvent, const edm::EventSetup & iSetup);

    private:

      edm::InputTag electronSource_;
      edm::InputTag muonSource_;
      edm::InputTag tauSource_;
      bool countElectronElectrons_;
      bool countElectronMuons_;
      bool countElectronTaus_;
      bool countMuonMuons_;
      bool countMuonTaus_;
      bool countTauTaus_;
  };



}

#endif