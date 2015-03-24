// -*- C++ -*-
//
// Package:    TupleMuonProducer
// Class:      TupleMuonProducer
//
/**\class TupleMuonProducer TupleMuonProducer.cc TEMP/TupleMuonProducer/src/TupleMuonProducer.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  shalhout shalhout
//         Created:  Tue Jun 24 09:44:10 CDT 2014
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
#include "DavisRunIITauTau/TupleObjects/interface/TupleMuon.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"



typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;


//
// class declaration
//

class TupleMuonProducer : public edm::EDProducer {
public:
  explicit TupleMuonProducer(const edm::ParameterSet&);
  ~TupleMuonProducer();

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

  edm::InputTag muonSrc_;
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
TupleMuonProducer::TupleMuonProducer(const edm::ParameterSet& iConfig):
muonSrc_(iConfig.getParameter<edm::InputTag>("muonSrc" ))
{


  produces<vector<TupleMuon>>(NAME_).setBranchAlias(NAME_);


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


TupleMuonProducer::~TupleMuonProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TupleMuonProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{


  // get muon collection
  edm::Handle<edm::View<pat::Muon> > muons;
  iEvent.getByLabel(muonSrc_,muons);


  auto_ptr<TupleMuonCollection> TupleMuons (new TupleMuonCollection);

  const int TupleMuonSize = muons->size();
  TupleMuons->reserve( TupleMuonSize );

  edm::View<pat::Muon>::const_iterator muon;
  for(muon=muons->begin(); muon!=muons->end(); ++muon)
  {


    TupleMuon CurrentMuon;

    ////////////////
    //set_p4
    ////////////////
    CurrentMuon.set_p4(muon->p4());

    std::cout<<" ------> muon with pt = "<<muon->p4().Pt()<<std::endl;
    std::cout<<" ------> relIsol = "<<muon->userFloat("relIso")<<std::endl;
    std::cout<<" ------> dxy = "<<muon->userFloat("dxy")<<std::endl;
    std::cout<<" ------> dz = "<<muon->userFloat("dz")<<std::endl;




//    std::cout<<cutSrc.getParameter<double>("SIGeleMu_minPt")<<std::endl;


//    std::cout<<muon->muonID("POG_MVA_ID_Run2_NonTrig_Tight")<<std::endl; 
    //std::cout<<muon.relIso(dBetaFactor=0.5, allCharged=0)<<std::endl;


// std::cout<<muon->muonID("cutBasedMuonID-CSA14-50ns-V1-standalone-loose")<<std::endl;
// std::cout<<muon->muonID("cutBasedMuonID-CSA14-50ns-V1-standalone-medium")<<std::endl;
// std::cout<<muon->muonID("cutBasedMuonID-CSA14-50ns-V1-standalone-tight")<<std::endl;
// std::cout<<muon->muonID("cutBasedMuonID-CSA14-50ns-V1-standalone-veto")<<std::endl;
// std::cout<<muon->muonID("cutBasedMuonID-CSA14-PU20bx25-V0-standalone-loose")<<std::endl;
// std::cout<<muon->muonID("cutBasedMuonID-CSA14-PU20bx25-V0-standalone-medium")<<std::endl;
// std::cout<<muon->muonID("cutBasedMuonID-CSA14-PU20bx25-V0-standalone-tight")<<std::endl;
// std::cout<<muon->muonID("cutBasedMuonID-CSA14-PU20bx25-V0-standalone-veto")<<std::endl;
// std::cout<<muon->muonID("eidLoose")<<std::endl;
// std::cout<<muon->muonID("eidRobustHighEnergy")<<std::endl;
// std::cout<<muon->muonID("eidRobustLoose")<<std::endl;
// std::cout<<muon->muonID("eidRobustTight")<<std::endl;
// std::cout<<muon->muonID("eidTight")<<std::endl;
// std::cout<<muon->muonID("heepMuonID-HEEPV50-CSA14-25ns")<<std::endl;
// std::cout<<muon->muonID("heepMuonID-HEEPV50-CSA14-startup")<<std::endl;



  ////////////
  // store the muon

  TupleMuons->push_back(CurrentMuon);

}


iEvent.put( TupleMuons, NAME_ );




/* This is an event example
//Read 'ExampleData' from the Event
Handle<ExampleData> pIn;
iEvent.getByLabel("example",pIn);

//Use the ExampleData to create an ExampleData2 which
// is put into the Event
std::auto_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
iEvent.put(pOut);
*/

/* this is an EventSetup example
//Read SetupData from the SetupRecord in the EventSetup
ESHandle<SetupData> pSetup;
iSetup.get<SetupRecord>().get(pSetup);
*/

}

// ------------ method called once each job just before starting event loop  ------------
void
TupleMuonProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TupleMuonProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
TupleMuonProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
TupleMuonProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
TupleMuonProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
TupleMuonProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TupleMuonProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TupleMuonProducer);
