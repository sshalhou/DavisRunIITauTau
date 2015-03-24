// -*- C++ -*-
//
// Package:    TupleTauProducer
// Class:      TupleTauProducer
//
/**\class TupleTauProducer TupleTauProducer.cc TEMP/TupleTauProducer/src/TupleTauProducer.cc

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

// needed by ntuple Tau producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleTau.h"
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

class TupleTauProducer : public edm::EDProducer {
public:
  explicit TupleTauProducer(const edm::ParameterSet&);
  ~TupleTauProducer();

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

  edm::InputTag tauSrc_;
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
TupleTauProducer::TupleTauProducer(const edm::ParameterSet& iConfig):
tauSrc_(iConfig.getParameter<edm::InputTag>("tauSrc" ))
{


  produces<vector<TupleTau>>(NAME_).setBranchAlias(NAME_);


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


TupleTauProducer::~TupleTauProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TupleTauProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{


  // get Tau collection
  edm::Handle<edm::View<pat::Tau> > taus;
  iEvent.getByLabel(tauSrc_,taus);


  auto_ptr<TupleTauCollection> TupleTaus (new TupleTauCollection);

  const int TupleTauSize = taus->size();
  TupleTaus->reserve( TupleTauSize );

  edm::View<pat::Tau>::const_iterator Tau;
  for(Tau=taus->begin(); Tau!=taus->end(); ++Tau)
  {


    TupleTau CurrentTau;

    ////////////////
    //set_p4
    ////////////////
    CurrentTau.set_p4(Tau->p4());

    std::cout<<" ------> Tau with pt = "<<Tau->p4().Pt()<<std::endl;
    std::cout<<" ------> relIsol = "<<Tau->userFloat("relIso")<<std::endl;
    std::cout<<" ------> dxy = "<<Tau->userFloat("dxy")<<std::endl;
    std::cout<<" ------> dz = "<<Tau->userFloat("dz")<<std::endl;


  ////////////
  // store the Tau

  TupleTaus->push_back(CurrentTau);

}


iEvent.put( TupleTaus, NAME_ );




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
TupleTauProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TupleTauProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
TupleTauProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
TupleTauProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
TupleTauProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
TupleTauProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TupleTauProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TupleTauProducer);
