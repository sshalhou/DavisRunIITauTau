//
// Filter module to pick only eTau, muTau, or eMu events
// (based on number of possible pairs present)
// given collections of pat::Tau, pat::Electron, and pat::Muon
// no lepton-parameter cuts are applied at this filter level
// just a simple pair count

#include "DavisRunIITauTau/CustomFilters/interface/HiggsCandidateCountFilter.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"


using namespace pat;


HiggsCandidateCountFilter::HiggsCandidateCountFilter(const edm::ParameterSet & iConfig) {
  electronSource_ = iConfig.getParameter<edm::InputTag>( "electronSource" );
  muonSource_     = iConfig.getParameter<edm::InputTag>( "muonSource" );
  tauSource_      = iConfig.getParameter<edm::InputTag>( "tauSource" );
  countElectronElectrons_  = iConfig.getParameter<bool>         ( "countElectronElectrons" );
  countElectronMuons_  = iConfig.getParameter<bool>         ( "countElectronMuons" );
  countElectronTaus_ = iConfig.getParameter<bool>         ( "countElectronTaus" );
  countMuonMuons_     = iConfig.getParameter<bool>         ( "countMuonMuons" );
  countMuonTaus_     = iConfig.getParameter<bool>         ( "countMuonTaus" );
  countTauTaus_ = iConfig.getParameter<bool>         ( "countTauTaus" );
}


HiggsCandidateCountFilter::~HiggsCandidateCountFilter() {
}


bool HiggsCandidateCountFilter::filter(edm::Event & iEvent, const edm::EventSetup & iSetup) {
  edm::Handle<edm::View<Electron> > electrons;
  iEvent.getByLabel(electronSource_, electrons);
  edm::Handle<edm::View<Muon> > muons;
  iEvent.getByLabel(muonSource_, muons);
  edm::Handle<edm::View<Tau> > taus;
  iEvent.getByLabel(tauSource_, taus);


  std::size_t NUM_TAUS = taus->size();
  std::size_t NUM_ELECTRONS = electrons->size();
  std::size_t NUM_MUONS = muons->size();

  std::cout<<" e, mu, tau size : "<<NUM_ELECTRONS<<" , "<<NUM_MUONS<<" , "<<NUM_TAUS<<" KEEP = ";

  bool KEEP = 0;

  ////////////////////////////////////////////////////
  // check for e+e if requested
  ////////////////////////////////////////////////////

    if(countElectronElectrons_)
    {
      if (NUM_ELECTRONS>1) KEEP = 1;
      
    } 

  ////////////////////////////////////////////////////
  // check for e+muon if requested
  ////////////////////////////////////////////////////

    if(countElectronMuons_)
    {
      if (NUM_MUONS > 0 && NUM_ELECTRONS>0) KEEP = 1;  
    } 


  ////////////////////////////////////////////////////
  // check for e+tau if requested
  ////////////////////////////////////////////////////

    if(countElectronTaus_)
    {
      if (NUM_TAUS > 0 && NUM_ELECTRONS>0) KEEP = 1;
    } 

  ////////////////////////////////////////////////////
  // check for muon+muon if requested
  ////////////////////////////////////////////////////

    if(countMuonMuons_)
    {
      if (NUM_MUONS>1) KEEP = 1;    
    } 


  ////////////////////////////////////////////////////
  // check for muon+tau if requested
  ////////////////////////////////////////////////////

    if(countMuonTaus_)
    {
      if (NUM_TAUS > 0 && NUM_MUONS>0) KEEP = 1;    
    } 

  ////////////////////////////////////////////////////
  // check for tau+tau if requested
  ////////////////////////////////////////////////////

    if(countTauTaus_)
    {
      if (NUM_TAUS > 1) KEEP = 1;    
    }

  std::cout<<KEEP<<"\n";
  return KEEP;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(HiggsCandidateCountFilter);
