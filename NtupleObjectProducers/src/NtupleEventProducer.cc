// -*- C++ -*-
//
// Package:    NtupleEventProducer
// Class:      NtupleEventProducer
//
/**\class NtupleEventProducer NtupleEventProducer.cc TEMP/NtupleEventProducer/src/NtupleEventProducer.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  shalhout shalhout
//         Created:  Tue May 29 09:44:10 CDT 2015
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
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TauAnalysis/SVfitStandalone/interface/SVfitStandaloneAlgorithm.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
 

typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;
typedef std::vector<edm::InputTag> VInputTag;


//
// class declaration
//

class NtupleEventProducer : public edm::EDProducer {
public:
  explicit NtupleEventProducer(const edm::ParameterSet&);
  ~NtupleEventProducer();

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

  VInputTag tupleCandidateEventSrc_;
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
NtupleEventProducer::NtupleEventProducer(const edm::ParameterSet& iConfig):
tupleCandidateEventSrc_(iConfig.getParameter<VInputTag>("tupleCandidateEventSrc" )),
NAME_(iConfig.getParameter<string>("NAME" ))
{


  produces<vector<NtupleEvent>>(NAME_).setBranchAlias(NAME_);


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


NtupleEventProducer::~NtupleEventProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
NtupleEventProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  auto_ptr<NtupleEventCollection> NtupleEvents (new NtupleEventCollection);
  std::size_t reserveSize =  tupleCandidateEventSrc_.size();
  NtupleEvents->reserve( reserveSize );



  for(std::size_t i = 0; i < tupleCandidateEventSrc_.size(); ++i)
  {


    // get the ith pair collection

      edm::Handle<std::vector<TupleCandidateEvent> > pairs;
      iEvent.getByLabel(tupleCandidateEventSrc_[i],pairs);

      if(!pairs.isValid()) continue;

      for(std::size_t ii = 0; ii<pairs->size(); ii++)
      {

        const TupleCandidateEvent aPair =  (*pairs)[ii];
        NtupleEvent anNtupleEvent;
        anNtupleEvent.fill(aPair);
        NtupleEvents->push_back(anNtupleEvent);


      }


  }

iEvent.put( NtupleEvents, NAME_ );


//tupleCandidateEventSrc_

  // edm::Handle<std::vector<TupleCandidateEventCollection>> pairs;
  // iEvent.getByLabel(tupleCandidateEventSrc_,pairs);

  // std::cout<<" SIZE "<<pairs.size()<<"\n";

  // for(vInputTag::const_iterator it=srcLeptonsTags.begin();it!=srcLeptonsTags.end();it++) {
  //   srcLeptons_.push_back( consumes<reco::CandidateView >( *it ) );
  // }

  // get TupleEvent collections
  // edm::Handle<std::vector<TupleCandidateEventCollection>> pairs;
  // iEvent.getByLabel(tupleCandidateEventSrc_,pairs);


//   for(std::size_t p = 0; p < tupleCandidateEventSrc_.size(); ++p)
// {     
//       std::cout<<" getting "<<tupleCandidateEventSrc_[p]<<std::endl;
//       edm::Handle <TupleCandidateEventCollection>  pair_vec;
//       iEvent.getByLabel(tupleCandidateEventSrc_[p], pair_vec);

//       if(!pair_vec.isValid()) continue;

//      std::cout<<pair_vec

//       edm::View<TupleCandidateEvent>::const_iterator pair;

//   for(pair=pair_vec->begin(); pair!=pair_vec->end(); ++pair)
//   {

// }
      // for(std::size_t pp = 0; pp < pair_vec.size(); ++pp)
      // {
      //  }
       

      //     const TupleCandidateEvent aPair =  (*pair_vec)[pp];

      //     if(!aPair.isValid()) continue;


      //     std::cout<<"pair #"<<p<<" is of type "<<aPair.CandidateEventType()<<"\n";

      //     // NtupleEvent anNtupleEvent;
      //     // anNtupleEvent.fill(aPair);
      //     // iEvent.put( NtupleEvents, NAME_ );
      // }

//}










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
NtupleEventProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
NtupleEventProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
NtupleEventProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
NtupleEventProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
NtupleEventProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
NtupleEventProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
NtupleEventProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}



//define this as a plug-in
DEFINE_FWK_MODULE(NtupleEventProducer);
