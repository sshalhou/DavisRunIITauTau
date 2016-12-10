//
// Simple Lepton Count Filter

#include "DavisRunIITauTau/CustomFilters/interface/SimpleFilter.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"


using namespace pat;


SimpleFilter::SimpleFilter(const edm::ParameterSet & iConfig) {
  electronTags_ = iConfig.getParameter<vInputTag>("electronSources");
  muonTags_ = iConfig.getParameter<vInputTag>("muonSources");
  tauTags_ =   iConfig.getParameter<vInputTag>("tauSources");
  BOOSTEDtauTags_ =   iConfig.getParameter<vInputTag>("BOOSTEDtauSources");
  vertexSrc_ = iConfig.getParameter<edm::InputTag>("vertexSrc" );

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
    
  for(vInputTag::const_iterator it=BOOSTEDtauTags_.begin();it!=BOOSTEDtauTags_.end();it++) 
  {
    BOOSTEDtauSources_.push_back( consumes< edm::View< pat::Tau > >( *it ) );
  }
    
  vertexToken_ = consumes< edm::View<reco::Vertex> >(vertexSrc_);


}


SimpleFilter::~SimpleFilter() {
}


bool SimpleFilter::filter(edm::Event & iEvent, const edm::EventSetup & iSetup) {

  /* get the 1st vertex */

  // get vertex collection
  edm::Handle<edm::View<reco::Vertex> > vertices;
  iEvent.getByToken(vertexToken_,vertices);
  const reco::Vertex & first_vertex = vertices->at(0);



  /* from each collection add up the total count */

  std::size_t NUM_ELECTRONS = 0;
  std::size_t NUM_MUONS = 0;
  std::size_t NUM_TAUS = 0;
  std::size_t NUM_TAUS_BOOSTED = 0;

  /* count the electron totals */

  int number_good_eMu_Electrons  = 0;
  int number_good_eTau_Electrons = 0;
  int number_good_eE_Electrons  = 0;


  /* count the muon totals */

  int number_good_eMu_Muons  = 0;
  int number_good_muTau_Muons = 0;
  int number_good_MuMu_Muons  = 0;


  /* count the tau totals  */

  int number_good_tauTau_Taus  = 0;
  int number_good_eleTau_Taus = 0;
  int number_good_muTau_Taus  = 0;

  int number_good_tauTau_TausBoosted  = 0;
  int number_good_eleTau_TausBoosted = 0;
  int number_good_muTau_TausBoosted  = 0;



  for ( std::vector<edm::EDGetTokenT<edm::View< pat::Electron > > >::const_iterator electronSources_i = electronSources_.begin(); 
        electronSources_i != electronSources_.end(); ++electronSources_i )
  {
    edm::Handle< edm::View< pat::Electron > > temp;
    iEvent.getByToken(*electronSources_i, temp);
    
    /* apply some basic cuts */
   for(std::size_t aelec = 0; aelec<temp->size(); ++aelec)
    {
      const pat::Electron & elecToCheck = temp->at(aelec);

      ////////////////////////////////////////////////
      // electron basic cuts 
      ////////////////////////////////////////////////


      float dxy = NAN;
      float dz = NAN;
      float numberOfMissingInnerHits = NAN;

      if(elecToCheck.gsfTrack().isNonnull())
      {
          dxy = elecToCheck.gsfTrack()->dxy(first_vertex.position());
          dz = elecToCheck.gsfTrack()->dz(first_vertex.position());
          numberOfMissingInnerHits = elecToCheck.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::HitCategory::MISSING_INNER_HITS);
      }

      if(  !(fabs(dxy) < 0.045) ) continue;
      if(  !(fabs(dz) < 0.2) ) continue;
      if(  !(numberOfMissingInnerHits <= 1)  )  continue;
      if(  !(elecToCheck.passConversionVeto()) )    continue;  
      if(  !(fabs(elecToCheck.eta()) < 2.5) )    continue;  

      NUM_ELECTRONS += 1;

      /* the pT cuts need to be well below electron energy scale variation (about 10% above/below analysis cut should do fine) */

      /* code it this way to allow for future assym. shifts if needed */

      double pt = elecToCheck.pt();
      double pt_up = 1.1 * elecToCheck.pt();
      double pt_down = 0.9 * elecToCheck.pt();

      if( pt > 27.0 || pt_up > 27.0 || pt_down > 27.0) number_good_eTau_Electrons ++;
      if( pt > 13.0 || pt_up > 13.0 || pt_down > 13.0) number_good_eMu_Electrons ++;
      if( pt > 10.0 || pt_up > 10.0 || pt_down > 10.0) number_good_eE_Electrons ++;
    }
  }

  /* count the muon total */


  for ( std::vector<edm::EDGetTokenT<edm::View< pat::Muon > > >::const_iterator muonSources_i = muonSources_.begin(); 
        muonSources_i != muonSources_.end(); ++muonSources_i )
  {
    edm::Handle< edm::View< pat::Muon > > temp;
    iEvent.getByToken(*muonSources_i, temp);
    
    

    ////////////////////////////////////////////////
    // muon basic cuts 
    ////////////////////////////////////////////////

    for(std::size_t amuon = 0; amuon<temp->size(); ++amuon)
    {
      const pat::Muon & muonToCheck = temp->at(amuon);


      float dxy = 999.0;
      float dz = 999.0;

      if (muonToCheck.muonBestTrack().isNonnull())
      {
          dxy = muonToCheck.muonBestTrack()->dxy(first_vertex.position());
          dz = muonToCheck.muonBestTrack()->dz(first_vertex.position());
      }


      bool ichep2016_goodGlob = (muonToCheck.isGlobalMuon() && 
                                muonToCheck.globalTrack()->normalizedChi2() < 3 && 
                                muonToCheck.combinedQuality().chi2LocalPosition < 12 && 
                                muonToCheck.combinedQuality().trkKink < 20); 

      bool ichep2016_isMedium = (muonToCheck.isLooseMuon() &&                     
                    muonToCheck.innerTrack()->validFraction() > 0.49 && 
                    muonToCheck.segmentCompatibility()   >=   (ichep2016_goodGlob   ? 0.303 : 0.451));



      if(  !(fabs(dxy) < 0.045) ) continue;
      if(  !(fabs(dz) < 0.2) ) continue;
      if(  !(fabs(muonToCheck.eta()) <= 2.4) )    continue;  
      if(  !(ichep2016_isMedium) )  continue;

      NUM_MUONS += 1;


      /* the pT cuts need to be well below muon momentum scale variation (about 10% above/below analysis cut should do fine) */
      /* code it this way to allow for future assym. shifts if needed */

      double pt = muonToCheck.pt();
      double pt_up = 1.1 * muonToCheck.pt();
      double pt_down = 0.9 * muonToCheck.pt();

      if( pt > 24.0 || pt_up > 24.0 || pt_down > 24.0) number_good_muTau_Muons ++;
      if( pt > 10.0 || pt_up > 10.0 || pt_down > 10.0) number_good_eMu_Muons ++;
      if( pt > 10.0 || pt_up > 10.0 || pt_down > 10.0) number_good_MuMu_Muons ++;

    }




  }


  /* count the tau total */


  for ( std::vector<edm::EDGetTokenT<edm::View< pat::Tau > > >::const_iterator tauSources_i = tauSources_.begin(); 
        tauSources_i != tauSources_.end(); ++tauSources_i )
  { 

    edm::Handle< edm::View< pat::Tau > > temp;
    iEvent.getByToken(*tauSources_i, temp);
    
    ////////////////////////////////////////////////
    // tau basic cuts 
    ////////////////////////////////////////////////

    for(std::size_t atau = 0; atau<temp->size(); ++atau)
    {
      const pat::Tau & tauToCheck = temp->at(atau);


      pat::PackedCandidate const* packedLeadTauCand = dynamic_cast<pat::PackedCandidate const*>(tauToCheck.leadChargedHadrCand().get());
      float dz = packedLeadTauCand->dz();
     
      bool isoCheck = 0;
      if(tauToCheck.tauID("byTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ) isoCheck = 1;
      if(tauToCheck.tauID("byVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5) isoCheck = 1;
      if(tauToCheck.tauID("byLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ) isoCheck = 1;
      if(tauToCheck.tauID("byMediumIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ) isoCheck = 1;
      if(tauToCheck.tauID("byVLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ) isoCheck = 1;
      if(tauToCheck.tauID("byVVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5) isoCheck = 1;

      if ( !isoCheck ) continue;
      if(  !(fabs(dz) < 0.2) ) continue;
      if(  !(fabs(tauToCheck.eta()) <= 2.3) )    continue;  
      if(  !( tauToCheck.tauID("decayModeFinding") > 0.5 ) ) continue;

      NUM_TAUS += 1;

      /* evalualte the mvas */

      bool goodMVA_TauTau = (tauToCheck.tauID("againstElectronVLooseMVA6")> 0.5 && tauToCheck.tauID("againstMuonLoose3")>0.5);
      bool goodMVA_eleTau = (tauToCheck.tauID("againstElectronTightMVA6")> 0.5 && tauToCheck.tauID("againstMuonLoose3")>0.5);
      bool goodMVA_muTau = (tauToCheck.tauID("againstElectronVLooseMVA6")> 0.5 && tauToCheck.tauID("againstMuonTight3")>0.5);

      /* the pT cuts need to be well below tau energy scale variation (about 10% above/below analysis cut should do fine) */
      /* code it this way to allow for future assym. shifts if needed */

      double pt = tauToCheck.pt();
      double pt_up = 1.1 * tauToCheck.pt();
      double pt_down = 0.9 * tauToCheck.pt();

      if( ( pt > 40.0 || pt_up > 40.0 || pt_down > 40.0) && goodMVA_TauTau ) number_good_tauTau_Taus ++;
      if( ( pt > 20.0 || pt_up > 20.0 || pt_down > 20.0) && goodMVA_eleTau ) number_good_eleTau_Taus ++;
      if( ( pt > 20.0 || pt_up > 20.0 || pt_down > 20.0) && goodMVA_muTau ) number_good_muTau_Taus ++;

  
    }
  }


  /* count the BOOSTEDtau total */


  for ( std::vector<edm::EDGetTokenT<edm::View< pat::Tau > > >::const_iterator BOOSTEDtauSources_i = BOOSTEDtauSources_.begin(); 
        BOOSTEDtauSources_i != BOOSTEDtauSources_.end(); ++BOOSTEDtauSources_i )
  { 

    edm::Handle< edm::View< pat::Tau > > temp;
    iEvent.getByToken(*BOOSTEDtauSources_i, temp);
    
    ////////////////////////////////////////////////
    // BOOSTED tau basic cuts 
    ////////////////////////////////////////////////

    for(std::size_t atau = 0; atau<temp->size(); ++atau)
    {
      const pat::Tau & tauToCheck = temp->at(atau);


      pat::PackedCandidate const* packedLeadTauCand = dynamic_cast<pat::PackedCandidate const*>(tauToCheck.leadChargedHadrCand().get());
      float dz = packedLeadTauCand->dz();
     
      bool isoCheck = 0;
      if(tauToCheck.tauID("byTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ) isoCheck = 1;
      if(tauToCheck.tauID("byVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5) isoCheck = 1;
      if(tauToCheck.tauID("byLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ) isoCheck = 1;
      if(tauToCheck.tauID("byMediumIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ) isoCheck = 1;
      if(tauToCheck.tauID("byVLooseIsolationMVArun2v1DBdR03oldDMwLT") > 0.5 ) isoCheck = 1;
      if(tauToCheck.tauID("byVVTightIsolationMVArun2v1DBdR03oldDMwLT") > 0.5) isoCheck = 1;

      if ( !isoCheck ) continue;
      if(  !(fabs(dz) < 0.2) ) continue;
      if(  !(fabs(tauToCheck.eta()) <= 2.3) )    continue;  
      if(  !( tauToCheck.tauID("decayModeFinding") > 0.5 ) ) continue;

      NUM_TAUS_BOOSTED += 1;

      /* evalualte the mvas */

      bool goodMVA_TauTau = (tauToCheck.tauID("againstElectronVLooseMVA6")> 0.5 && tauToCheck.tauID("againstMuonLoose3")>0.5);
      bool goodMVA_eleTau = (tauToCheck.tauID("againstElectronTightMVA6")> 0.5 && tauToCheck.tauID("againstMuonLoose3")>0.5);
      bool goodMVA_muTau = (tauToCheck.tauID("againstElectronVLooseMVA6")> 0.5 && tauToCheck.tauID("againstMuonTight3")>0.5);

      /* the pT cuts need to be well below tau energy scale variation (about 10% above/below analysis cut should do fine) */
      /* code it this way to allow for future assym. shifts if needed */

      double pt = tauToCheck.pt();
      double pt_up = 1.1 * tauToCheck.pt();
      double pt_down = 0.9 * tauToCheck.pt();

      if( ( pt > 40.0 || pt_up > 40.0 || pt_down > 40.0) && goodMVA_TauTau ) number_good_tauTau_TausBoosted ++;
      if( ( pt > 20.0 || pt_up > 20.0 || pt_down > 20.0) && goodMVA_eleTau ) number_good_eleTau_TausBoosted ++;
      if( ( pt > 20.0 || pt_up > 20.0 || pt_down > 20.0) && goodMVA_muTau ) number_good_muTau_TausBoosted ++;

  
    }

 


  }





  // std::cout<<" ****** \n";
  // std::cout<<" SZS:: e, mu, tau counts = "<<NUM_ELECTRONS<<" , "<<NUM_MUONS<<" , "<<NUM_TAUS<<"\n";
  // std::cout<<" ZSZ : "<<" electrons in eTau, eMu, eE = "<<number_good_eTau_Electrons<<" , "<<number_good_eMu_Electrons<<" , "<<number_good_eE_Electrons<<"\n";
  // std::cout<<" ZSZ : "<<" muons in muTau, eMu, muMu = "<<number_good_muTau_Muons<<" , "<<number_good_eMu_Muons<<" , "<<number_good_MuMu_Muons<<"\n";

  // std::cout<<" zszBoostedTau counts "<<NUM_TAUS<<" in tauTau, eTau, muTau "<<number_good_tauTau_TausBoosted;
  // std::cout<<" , "<<number_good_eleTau_TausBoosted<<" , "<<number_good_muTau_TausBoosted<<" \n";

  // std::cout<<" zszTau counts "<<NUM_TAUS<<" in tauTau, eTau, muTau "<<number_good_tauTau_Taus;
  // std::cout<<" , "<<number_good_eleTau_Taus<<" , "<<number_good_muTau_Taus<<" \n";



  /* evaluate pass/fail for this event */
  /* does not allow for ll channels yet */


  bool KEEP = 0;

 if( number_good_eMu_Electrons >= 1 && number_good_eMu_Muons >= 1) KEEP = 1;
 if( number_good_eTau_Electrons >=1 && number_good_eleTau_Taus>= 1 ) KEEP = 1;
 if( number_good_eTau_Electrons >=1 && number_good_eleTau_TausBoosted>= 1 ) KEEP = 1;
 if( number_good_muTau_Muons >= 1 && number_good_muTau_Taus >= 1) KEEP = 1;
 if( number_good_muTau_Muons >= 1 && number_good_muTau_TausBoosted >= 1) KEEP = 1;
 if( number_good_tauTau_Taus >= 2 ) KEEP = 1;

 return (KEEP);

}











#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(SimpleFilter);
