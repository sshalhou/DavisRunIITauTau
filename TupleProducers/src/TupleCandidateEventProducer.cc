// -*- C++ -*-
//
// Package:    TupleCandidateEventProducer
// Class:      TupleCandidateEventProducer
//
/**\class TupleCandidateEventProducer TupleCandidateEventProducer.cc TEMP/TupleCandidateEventProducer/src/TupleCandidateEventProducer.cc

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
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
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

class TupleCandidateEventProducer : public edm::EDProducer {
public:
  explicit TupleCandidateEventProducer(const edm::ParameterSet&);
  ~TupleCandidateEventProducer();

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
  edm::InputTag electronSrc_;
  edm::InputTag muonSrc_;
  edm::InputTag mvaMETSrc_;

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
TupleCandidateEventProducer::TupleCandidateEventProducer(const edm::ParameterSet& iConfig):
tauSrc_(iConfig.getParameter<edm::InputTag>("tauSrc" )),
electronSrc_(iConfig.getParameter<edm::InputTag>("electronSrc" )),
muonSrc_(iConfig.getParameter<edm::InputTag>("muonSrc" )),
mvaMETSrc_(iConfig.getParameter<edm::InputTag>("mvaMETSrc" ))
{


  produces<vector<TupleCandidateEvent>>(NAME_).setBranchAlias(NAME_);


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


TupleCandidateEventProducer::~TupleCandidateEventProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TupleCandidateEventProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{


  // get Tau collection
  edm::Handle<edm::View<pat::Tau> > taus;
  iEvent.getByLabel(tauSrc_,taus);


  // get Electron collection
  edm::Handle<edm::View<pat::Electron> > electrons;
  iEvent.getByLabel(electronSrc_,electrons);

  // get Muon collection
  edm::Handle<edm::View<pat::Muon> > muons;
  iEvent.getByLabel(muonSrc_,muons);

  // get mvaMET collection
  //edm::Handle<edm::View<reco::PFMET> > mvamets;
  edm::Handle <std::vector<reco::PFMET> >  mvamets;
  iEvent.getByLabel(mvaMETSrc_,mvamets);

  auto_ptr<TupleCandidateEventCollection> TupleCandidateEvents (new TupleCandidateEventCollection);




 
  // electron-electron 
  if (electrons.isValid())
  {
    for (unsigned int i=0; i<electrons->size(); ++i)
    {
      for (unsigned int ii=i+1; ii<electrons->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(electrons->at(i),electrons->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));
          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      }
    }
  }



  // electron-muon
  if (electrons.isValid() && muons.isValid())
  {
    for (unsigned int i=0; i<electrons->size(); ++i)
    {
      for (unsigned int ii=0; ii<muons->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(electrons->at(i),muons->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));
          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      }
    }
  }

  // electron-tau
  if (electrons.isValid() && taus.isValid())
  {

    for (unsigned int i=0; i<electrons->size(); ++i)
    {
      for (unsigned int ii=0; ii<taus->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(electrons->at(i),taus->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));          
          std::cout<<" create a veto lepton index finder \n";
          std::cout<<" to allow you to embed the veto e or m into the pair if needded\n";
          std::cout<<" this means that the customSlimmed stuff has to be loose enough to \n";
          std::cout<<" have both selected and veto leptons.\n";
          TupleCandidateEvents->push_back(CurrentCandidateEvent);
        
      }
    }
  }  

  // muon-muon
  if (muons.isValid())
  {
    for (unsigned int i=0; i<muons->size(); ++i)
    {
      for (unsigned int ii=i+1; ii<muons->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(muons->at(i),muons->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));          
          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      }
    }

  }


  // muon-tau
  if (muons.isValid() && taus.isValid())
  {


    for (unsigned int i=0; i<muons->size(); ++i)
    {
      for (unsigned int ii=0; ii<taus->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(muons->at(i),taus->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));          
          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      }
    }


  }

  // tau-tau
  if (taus.isValid())
  {

    for (unsigned int i=0; i<taus->size(); ++i)
    {
      for (unsigned int ii=i+1; ii<taus->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(taus->at(i),taus->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));          
          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      }
    }


  }











iEvent.put( TupleCandidateEvents, NAME_ );




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
TupleCandidateEventProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TupleCandidateEventProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
TupleCandidateEventProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
TupleCandidateEventProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
TupleCandidateEventProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
TupleCandidateEventProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TupleCandidateEventProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TupleCandidateEventProducer);
