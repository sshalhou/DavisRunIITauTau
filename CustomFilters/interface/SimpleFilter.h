//
// Simple Lepton Count Filter

#ifndef DavisRunIITauTau_CustomFilters_SimpleFilter_h
#define DavisRunIITauTau_CustomFilters_SimpleFilter_h

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"


namespace pat {


  class SimpleFilter : public edm::EDFilter {

    public:

      explicit SimpleFilter(const edm::ParameterSet & iConfig);
      virtual ~SimpleFilter();
      typedef std::vector<edm::InputTag> vInputTag;

    private:

      virtual bool filter(edm::Event & iEvent, const edm::EventSetup & iSetup);

      vInputTag electronTags_;
      std::vector<edm::EDGetTokenT< edm::View< pat::Electron > > > electronSources_;

      vInputTag muonTags_;
      std::vector<edm::EDGetTokenT< edm::View< pat::Muon > > > muonSources_;

      vInputTag tauTags_;
      std::vector<edm::EDGetTokenT< edm::View< pat::Tau > > > tauSources_;


      vInputTag BOOSTEDtauTags_;
      std::vector<edm::EDGetTokenT< edm::View< pat::Tau > > > BOOSTEDtauSources_;


      edm::InputTag vertexSrc_;
      edm::EDGetTokenT< edm::View<reco::Vertex> > vertexToken_;

  };

}

#endif