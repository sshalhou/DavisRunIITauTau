// -*- C++ -*-
//
// Package:    TupleElectronProducer
// Class:      TupleElectronProducer
//
/**\class TupleElectronProducer TupleElectronProducer.cc TEMP/TupleElectronProducer/src/TupleElectronProducer.cc

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

// needed by ntuple electron producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleElectron.h"
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

class TupleElectronProducer : public edm::EDProducer {
public:
  explicit TupleElectronProducer(const edm::ParameterSet&);
  ~TupleElectronProducer();

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

  edm::InputTag electronSrc_;
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
TupleElectronProducer::TupleElectronProducer(const edm::ParameterSet& iConfig):
electronSrc_(iConfig.getParameter<edm::InputTag>("electronSrc" ))
{


  produces<vector<TupleElectron>>(NAME_).setBranchAlias(NAME_);


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


TupleElectronProducer::~TupleElectronProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TupleElectronProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{


  // get electron collection
  edm::Handle<edm::View<pat::Electron> > electrons;
  iEvent.getByLabel(electronSrc_,electrons);


  auto_ptr<TupleElectronCollection> TupleElectrons (new TupleElectronCollection);

  const int TupleElectronSize = electrons->size();
  TupleElectrons->reserve( TupleElectronSize );

  edm::View<pat::Electron>::const_iterator electron;
  for(electron=electrons->begin(); electron!=electrons->end(); ++electron)
  {


    TupleElectron CurrentElectron;


    std::cout<<electron->userFloat("dxy")<<" = dxy "<<std::endl; 
    std::cout<<electron->userFloat("dz")<<" = dz "<<std::endl; 

    ////////////////
    //set_p4
    ////////////////
    CurrentElectron.set_p4(electron->p4());

//    std::cout<<cutSrc.getParameter<double>("SIGeleMu_minPt")<<std::endl;


//    std::cout<<electron->electronID("POG_MVA_ID_Run2_NonTrig_Tight")<<std::endl; 
    //std::cout<<electron.relIso(dBetaFactor=0.5, allCharged=0)<<std::endl;


// std::cout<<electron->electronID("cutBasedElectronID-CSA14-50ns-V1-standalone-loose")<<std::endl;
// std::cout<<electron->electronID("cutBasedElectronID-CSA14-50ns-V1-standalone-medium")<<std::endl;
// std::cout<<electron->electronID("cutBasedElectronID-CSA14-50ns-V1-standalone-tight")<<std::endl;
// std::cout<<electron->electronID("cutBasedElectronID-CSA14-50ns-V1-standalone-veto")<<std::endl;
// std::cout<<electron->electronID("cutBasedElectronID-CSA14-PU20bx25-V0-standalone-loose")<<std::endl;
// std::cout<<electron->electronID("cutBasedElectronID-CSA14-PU20bx25-V0-standalone-medium")<<std::endl;
// std::cout<<electron->electronID("cutBasedElectronID-CSA14-PU20bx25-V0-standalone-tight")<<std::endl;
// std::cout<<electron->electronID("cutBasedElectronID-CSA14-PU20bx25-V0-standalone-veto")<<std::endl;
// std::cout<<electron->electronID("eidLoose")<<std::endl;
// std::cout<<electron->electronID("eidRobustHighEnergy")<<std::endl;
// std::cout<<electron->electronID("eidRobustLoose")<<std::endl;
// std::cout<<electron->electronID("eidRobustTight")<<std::endl;
// std::cout<<electron->electronID("eidTight")<<std::endl;
// std::cout<<electron->electronID("heepElectronID-HEEPV50-CSA14-25ns")<<std::endl;
// std::cout<<electron->electronID("heepElectronID-HEEPV50-CSA14-startup")<<std::endl;



  ////////////
  // store the electron

  TupleElectrons->push_back(CurrentElectron);

}


iEvent.put( TupleElectrons, NAME_ );




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
TupleElectronProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TupleElectronProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
TupleElectronProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
TupleElectronProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
TupleElectronProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
TupleElectronProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TupleElectronProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TupleElectronProducer);
