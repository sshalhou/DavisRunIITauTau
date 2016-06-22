// -*- C++ -*-
//
// Package:    TrimmedPatMuonProducer
// Class:      TrimmedPatMuonProducer
//
/**\class TrimmedPatMuonProducer TrimmedPatMuonProducer.cc TEMP/TrimmedPatMuonProducer/src/TrimmedPatMuonProducer.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  shalhout shalhout
//         Created:  Mon Jul 14 12:35:16 CDT 2014
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// needed by ntuple muon producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Muon.h"
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
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"


typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;



//
// class declaration
//

class TrimmedPatMuonProducer : public edm::EDProducer {
public:
  explicit TrimmedPatMuonProducer(const edm::ParameterSet&);
  ~TrimmedPatMuonProducer();

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

  // ----------member data ---------------------------

  edm::InputTag muonSrc_;
  edm::EDGetTokenT<edm::View< pat::Muon > > muonToken_;

  unsigned int MAX_TO_KEEP_;
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
TrimmedPatMuonProducer::TrimmedPatMuonProducer(const edm::ParameterSet& iConfig):
muonSrc_(iConfig.getParameter<edm::InputTag>("muonSrc" )),
MAX_TO_KEEP_(iConfig.getParameter<unsigned int>("MAX_TO_KEEP" )),
NAME_(iConfig.getParameter<string>("NAME" ))
{


  produces<vector<pat::Muon>>(NAME_).setBranchAlias(NAME_);

  muonToken_ = consumes< edm::View<pat::Muon> >(muonSrc_);



  //register your products
  /* Examples
  produces<ExampleData2>();

  //if do put with a label
  produces<ExampleData2>("label");

  //if you want to put into the Run
  produces<ExampleData2,InRun>();
  */
  //now do what ever other initialization is needed

}


TrimmedPatMuonProducer::~TrimmedPatMuonProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TrimmedPatMuonProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{



  // get muon collection
  edm::Handle<edm::View<pat::Muon> > muons;
  iEvent.getByToken(muonToken_,muons);


  std::vector<pat::Muon> * storedMuons = new std::vector<pat::Muon>();


  for (std::size_t i = 0; i<muons->size(); i++)
  {
    if(i<MAX_TO_KEEP_)
    {
       const pat::Muon & muonToStore = muons->at(i);
       storedMuons->push_back(muonToStore);
    }
  }



  // add the muons to the event output
  std::auto_ptr<std::vector<pat::Muon> > eptr(storedMuons);
  iEvent.put(eptr,NAME_);


}

// ------------ method called once each job just before starting event loop  ------------
void
TrimmedPatMuonProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TrimmedPatMuonProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
TrimmedPatMuonProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
TrimmedPatMuonProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
TrimmedPatMuonProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
TrimmedPatMuonProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TrimmedPatMuonProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrimmedPatMuonProducer);
