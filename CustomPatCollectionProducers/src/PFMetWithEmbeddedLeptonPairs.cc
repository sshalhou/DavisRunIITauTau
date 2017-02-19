// -*- C++ -*-
//
// Package:    PFMetWithEmbeddedLeptonPairs
// Class:      PFMetWithEmbeddedLeptonPairs
//
/**\class PFMetWithEmbeddedLeptonPairs PFMetWithEmbeddedLeptonPairs.cc TEMP/PFMetWithEmbeddedLeptonPairs/src/PFMetWithEmbeddedLeptonPairs.cc

Description: Given PFMET produce a vector <pat::MET> in which each entry is PFMET with an embedded lepton pair combination
  THIS IS USED ONLY TO ALLOW US TO RUN WITHOUT MVAMET
  DO NOT APPLY ANY CORRECTIONS TO THE MET HERE
  AS THIS PFMET will be used to FILL MVA MET variables in FLatTuple (which the analysis should ignore)
    

Implementation:
[Notes on implementation]
*/
//
// Original Author:  shalhout shalhout
//         Created:  Mon Jul 14 12:35:16 CDT 2014
// $Id$
//
//


#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include <DataFormats/METReco/interface/PFMET.h>
#include <DataFormats/PatCandidates/interface/MET.h>
#include <DataFormats/PatCandidates/interface/Electron.h>
#include <DataFormats/PatCandidates/interface/Tau.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/Jet.h>
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "CondFormats/EgammaObjects/interface/GBRForest.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include <TFile.h>
#include <TVector2.h>
#include <TMath.h>



// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// needed by ntuple electron producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"
#include "DataFormats/PatCandidates/interface/Conversion.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "Math/GenVector/VectorUtil.h"
#include "DataFormats/PatCandidates/interface/PFParticle.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/LeptonRelativeIsolationTool.h"
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/ElectronClones.h"


#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"



typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;
typedef std::vector<pat::Electron> PatElectronCollection;
typedef std::vector<edm::InputTag> vInputTag;

//
// class declaration
//

class PFMetWithEmbeddedLeptonPairs : public edm::EDProducer {
public:
  explicit PFMetWithEmbeddedLeptonPairs(const edm::ParameterSet&);
  ~PFMetWithEmbeddedLeptonPairs();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run&, edm::EventSetup const&);
  virtual void endRun(edm::Run&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

  // ----------member data ---------------------------
 
  edm::InputTag pfMETSrc_;
  edm::EDGetTokenT<edm::View< pat::MET > > pfMETToken_;

  std::vector<edm::EDGetTokenT<reco::CandidateView > > srcLeptons_;
  std::vector<edm::Ptr<reco::Candidate>> allLeptons_;

  string NAME_;
  

};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
PFMetWithEmbeddedLeptonPairs::PFMetWithEmbeddedLeptonPairs(const edm::ParameterSet& iConfig):
pfMETSrc_(iConfig.getParameter<edm::InputTag>("pfMETSrc" )),
NAME_(iConfig.getParameter<string>("NAME" ))
{


  produces<pat::METCollection>(NAME_).setBranchAlias(NAME_);

  pfMETToken_ = consumes< edm::View<pat::MET> >(pfMETSrc_);

  vInputTag srcLeptonsTags = iConfig.getParameter<vInputTag>("srcLeptons");
  for(vInputTag::const_iterator it=srcLeptonsTags.begin();it!=srcLeptonsTags.end();it++) {
    srcLeptons_.push_back( consumes<reco::CandidateView >( *it ) );
  }


}


PFMetWithEmbeddedLeptonPairs::~PFMetWithEmbeddedLeptonPairs()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
PFMetWithEmbeddedLeptonPairs::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  auto_ptr<pat::METCollection> storedMETS (new pat::METCollection);


  // get MET collection
  edm::Handle<edm::View<pat::MET> > met;
  iEvent.getByToken(pfMETToken_,met);

  allLeptons_.clear();

  for ( std::vector<edm::EDGetTokenT<reco::CandidateView > >::const_iterator srcLeptons_i = srcLeptons_.begin(); srcLeptons_i != srcLeptons_.end(); ++srcLeptons_i )
  {
    edm::Handle<reco::CandidateView> leptons;
    iEvent.getByToken(*srcLeptons_i, leptons);
    for (size_t i=0; i < leptons->size(); ++i)
      allLeptons_.push_back(leptons->ptrAt(i));
  }




  for( std::size_t lep0 = 0; lep0 < allLeptons_.size(); ++lep0)
  {

      for( std::size_t lep1 = lep0+1; lep1 < allLeptons_.size(); ++lep1)
      {
        storedMETS->push_back(met->at(0));  /* create a copy of pfMET (index is always 0)*/
        
        storedMETS->at(storedMETS->size()-1).addUserCand("lepton0",allLeptons_.at(lep0));
        storedMETS->at(storedMETS->size()-1).addUserCand("lepton1",allLeptons_.at(lep1));


      }

  }



  iEvent.put(storedMETS,NAME_);


}

// ------------ method called once each job just before starting event loop  ------------
void
PFMetWithEmbeddedLeptonPairs::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
PFMetWithEmbeddedLeptonPairs::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
PFMetWithEmbeddedLeptonPairs::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
PFMetWithEmbeddedLeptonPairs::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
PFMetWithEmbeddedLeptonPairs::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
PFMetWithEmbeddedLeptonPairs::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PFMetWithEmbeddedLeptonPairs::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PFMetWithEmbeddedLeptonPairs);
