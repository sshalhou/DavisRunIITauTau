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
  electronTags_ = iConfig.getParameter<vInputTag>("electronSources");
  muonTags_ = iConfig.getParameter<vInputTag>("muonSources");
  tauTags_ = iConfig.getParameter<vInputTag>("tauSources");
  countElectronElectrons_  = iConfig.getParameter<bool>         ( "countElectronElectrons" );
  countElectronMuons_  = iConfig.getParameter<bool>         ( "countElectronMuons" );
  countElectronTaus_ = iConfig.getParameter<bool>         ( "countElectronTaus" );
  countMuonMuons_     = iConfig.getParameter<bool>         ( "countMuonMuons" );
  countMuonTaus_     = iConfig.getParameter<bool>         ( "countMuonTaus" );
  countTauTaus_ = iConfig.getParameter<bool>         ( "countTauTaus" );
  tauMVAfilter_EleTau_ = iConfig.getParameter<std::string>         ( "tauMVAfilter_EleTau" );
  tauMVAfilter_MuonTau_ = iConfig.getParameter<std::string>         ( "tauMVAfilter_MuonTau" );
  tauMVAfilter_TauTau_ = iConfig.getParameter<std::string>         ( "tauMVAfilter_TauTau" );
  tauIsofilter_ = iConfig.getParameter<std::string>         ( "tauIsofilter" );
  hlt_Filter_ = iConfig.getParameter < std::vector <std::string> > ("hlt_Filter");

  for(vInputTag::const_iterator it=electronTags_.begin();it!=electronTags_.end();it++) 
  {
    electronSources_.push_back( consumes< edm::View< pat::Electron > >( *it ) );
  }
    
  for(vInputTag::const_iterator it=muonTags_.begin();it!=muonTags_.end();it++) 
  {
    muonSources_.push_back( consumes< edm::View< pat::Muon > >( *it ) );
  }
    
  for(vInputTag::const_iterator it=tauTags_.begin();it!=tauTags_.end();it++) 
  {
    tauSources_.push_back( consumes< edm::View< pat::Tau > >( *it ) );
  }
    


}


HiggsCandidateCountFilter::~HiggsCandidateCountFilter() {
}


bool HiggsCandidateCountFilter::filter(edm::Event & iEvent, const edm::EventSetup & iSetup) {

  /* triggers */

  bool ACCEPTED_ON_HLT_PATH = 0;


  /* from each collection vector find the MAX size */

  std::size_t NUM_ELECTRONS = 0;
  std::size_t NUM_MUONS = 0;
  std::size_t NUM_TAUS = 0;

  ////////////////////
  // Electrons

  for ( std::vector<edm::EDGetTokenT<edm::View< pat::Electron > > >::const_iterator electronSources_i = electronSources_.begin(); 
        electronSources_i != electronSources_.end(); ++electronSources_i )
  {
    edm::Handle< edm::View< pat::Electron > > temp;
    iEvent.getByToken(*electronSources_i, temp);
    
    if(temp->size() > NUM_ELECTRONS) NUM_ELECTRONS = temp->size();


    for(std::size_t aelec = 0; aelec<temp->size(); ++aelec)
    {
      const pat::Electron & elecToCheck = temp->at(aelec);
      
      /* since all custom davis leptons hold all passing hlt paths, 
        only call if not already satisfied */
      
      if(ACCEPTED_ON_HLT_PATH == 0)
      {
        if(Davis_checkTriggerPathAccept(elecToCheck, hlt_Filter_)) ACCEPTED_ON_HLT_PATH = 1;
        
      } 
    }


  }

  ////////////////////
  // Muons

  for ( std::vector<edm::EDGetTokenT<edm::View< pat::Muon > > >::const_iterator muonSources_i = muonSources_.begin(); 
        muonSources_i != muonSources_.end(); ++muonSources_i )
  {
    edm::Handle< edm::View< pat::Muon > > temp;
    iEvent.getByToken(*muonSources_i, temp);
    
    if(temp->size() > NUM_MUONS) NUM_MUONS = temp->size();



    for(std::size_t amuon = 0; amuon<temp->size(); ++amuon)
    {
      const pat::Muon & muonToCheck = temp->at(amuon);
      
      /* since all custom davis leptons hold all passing hlt paths, 
        only call if not already satisfied */
      
      if(ACCEPTED_ON_HLT_PATH == 0)
      {
        if(Davis_checkTriggerPathAccept(muonToCheck, hlt_Filter_)) ACCEPTED_ON_HLT_PATH = 1;
        
      } 
    }


  }


  ////////////////////
  // Taus

  /* in the tau case want to check if they pass basic MVA cuts */
  int num_taus_passing_EleTau_MVAs = 0;
  int num_taus_passing_MuonTau_MVAs = 0;
  int num_taus_passing_TauTau_MVAs = 0;

  StringCutObjectSelector<pat::Tau> tauCut_EleTau(tauMVAfilter_EleTau_);
  StringCutObjectSelector<pat::Tau> tauCut_MuonTau(tauMVAfilter_MuonTau_);
  StringCutObjectSelector<pat::Tau> tauCut_TauTau(tauMVAfilter_TauTau_);
  StringCutObjectSelector<pat::Tau> tauCut_Iso(tauIsofilter_);

  for ( std::vector<edm::EDGetTokenT<edm::View< pat::Tau > > >::const_iterator tauSources_i = tauSources_.begin(); 
        tauSources_i != tauSources_.end(); ++tauSources_i )
  {
    edm::Handle< edm::View< pat::Tau > > temp;
    iEvent.getByToken(*tauSources_i, temp);
    
    if(temp->size() > NUM_TAUS) NUM_TAUS = temp->size();

    int local_passEleTau = 0;
    int local_passMuonTau = 0;
    int local_passTauTau = 0;

    for(std::size_t atau = 0; atau<temp->size(); ++atau)
    {
      const pat::Tau & tauToCheck = temp->at(atau);
      if(tauCut_EleTau(tauToCheck)  && tauCut_Iso(tauToCheck)) local_passEleTau += 1;
      if(tauCut_MuonTau(tauToCheck) && tauCut_Iso(tauToCheck)) local_passMuonTau += 1;
      if(tauCut_TauTau(tauToCheck)  && tauCut_Iso(tauToCheck)) local_passTauTau += 1;

      /* since all custom davis leptons hold all passing hlt paths, only call if not already satisfied */
      if(ACCEPTED_ON_HLT_PATH == 0)
      {
        if(Davis_checkTriggerPathAccept(tauToCheck, hlt_Filter_)) ACCEPTED_ON_HLT_PATH = 1;
      } 
    }

    if(local_passEleTau  > num_taus_passing_EleTau_MVAs  )  num_taus_passing_EleTau_MVAs = local_passEleTau;
    if(local_passMuonTau > num_taus_passing_MuonTau_MVAs ) num_taus_passing_MuonTau_MVAs = local_passMuonTau;
    if(local_passTauTau  > num_taus_passing_TauTau_MVAs  ) num_taus_passing_TauTau_MVAs = local_passTauTau;
    
  }


 // std::cout<<" e, mu, tau size : "<<NUM_ELECTRONS<<" , "<<NUM_MUONS<<" , "<<NUM_TAUS<<" KEEP = ";

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
      if (NUM_TAUS > 0 && NUM_ELECTRONS>0 && num_taus_passing_EleTau_MVAs > 0) KEEP = 1;
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
      if (NUM_TAUS > 0 && NUM_MUONS>0 && num_taus_passing_MuonTau_MVAs > 0) KEEP = 1;    
    } 



  ////////////////////////////////////////////////////
  // check for tau+tau if requested
  ////////////////////////////////////////////////////

    if(countTauTaus_)
    {
      if (NUM_TAUS > 1 && num_taus_passing_TauTau_MVAs > 1) KEEP = 1;    
    }

 // if(KEEP && !ACCEPTED_ON_HLT_PATH) std::cout<<" EVENT FAIL DUE TO TRIGGER \n";    

  return (KEEP && ACCEPTED_ON_HLT_PATH);
}











#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(HiggsCandidateCountFilter);
