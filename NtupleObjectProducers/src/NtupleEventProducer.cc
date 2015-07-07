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
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleTrigObject.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/NtupleObjectProducers/interface/NtupleTriggerObjectHelper.h"


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
  edm::EDGetTokenT<edm::TriggerResults> triggerBitSrc_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPreScaleSrc_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectSrc_;
  double electron_triggerMatchDRSrc_;
  std::vector<int> electron_triggerMatchTypesSrc_;
  std::vector<std::string> electron_triggerMatchPathsAndFiltersSrc_;
  double muon_triggerMatchDRSrc_;
  std::vector<int> muon_triggerMatchTypesSrc_;
  std::vector<std::string> muon_triggerMatchPathsAndFiltersSrc_;
  double tau_triggerMatchDRSrc_;
  std::vector<int> tau_triggerMatchTypesSrc_;
  std::vector<std::string> tau_triggerMatchPathsAndFiltersSrc_;
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
triggerBitSrc_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerBitSrc"))),
triggerPreScaleSrc_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("triggerPreScaleSrc"))),
triggerObjectSrc_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("triggerObjectSrc"))),
electron_triggerMatchDRSrc_(iConfig.getParameter<double>("electron_triggerMatchDRSrc" )),
electron_triggerMatchTypesSrc_(iConfig.getParameter<std::vector<int>>("electron_triggerMatchTypesSrc" )),
electron_triggerMatchPathsAndFiltersSrc_(iConfig.getParameter<std::vector<std::string>>("electron_triggerMatchPathsAndFiltersSrc" )),
muon_triggerMatchDRSrc_(iConfig.getParameter<double>("muon_triggerMatchDRSrc" )),
muon_triggerMatchTypesSrc_(iConfig.getParameter<std::vector<int>>("muon_triggerMatchTypesSrc" )),
muon_triggerMatchPathsAndFiltersSrc_(iConfig.getParameter<std::vector<std::string>>("muon_triggerMatchPathsAndFiltersSrc" )),
tau_triggerMatchDRSrc_(iConfig.getParameter<double>("tau_triggerMatchDRSrc" )),
tau_triggerMatchTypesSrc_(iConfig.getParameter<std::vector<int>>("tau_triggerMatchTypesSrc" )),
tau_triggerMatchPathsAndFiltersSrc_(iConfig.getParameter<std::vector<std::string>>("tau_triggerMatchPathsAndFiltersSrc" )),
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

    // get trigger-related collections

    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<pat::PackedTriggerPrescales> triggerPreScales;

    iEvent.getByToken(triggerBitSrc_, triggerBits);
    iEvent.getByToken(triggerObjectSrc_, triggerObjects);
    iEvent.getByToken(triggerPreScaleSrc_, triggerPreScales);

    const edm::TriggerNames &TRIGGERnames = iEvent.triggerNames(*triggerBits);





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




        /* add the trigger object match & filter info */
  
        NtupleTriggerObjectHelper trigObjHelper(triggerBits,triggerObjects,triggerPreScales,TRIGGERnames,
                       electron_triggerMatchDRSrc_,electron_triggerMatchTypesSrc_,electron_triggerMatchPathsAndFiltersSrc_,
                       muon_triggerMatchDRSrc_,muon_triggerMatchTypesSrc_,muon_triggerMatchPathsAndFiltersSrc_,
                       tau_triggerMatchDRSrc_,tau_triggerMatchTypesSrc_,tau_triggerMatchPathsAndFiltersSrc_);

        anNtupleEvent.fillTriggerMatchesLeg1andLeg2(trigObjHelper.getMatchedNtupleTrigObjectVector(anNtupleEvent.leg1()),
        trigObjHelper.getMatchedNtupleTrigObjectVector(anNtupleEvent.leg2()));


        // TriggerInfoEmbeddingTool electron_triggerEmbedderTool(triggerBits,triggerObjects,triggerPreScales,names,
        //               electron_trigMatchDRcut,electron_trigMatchTypes,electron_trigSummaryPathsAndFilters);

        // TriggerInfoEmbeddingTool muon_triggerEmbedderTool(triggerBits,triggerObjects,triggerPreScales,names,
        //               muon_trigMatchDRcut,muon_trigMatchTypes,muon_trigSummaryPathsAndFilters);

        // TriggerInfoEmbeddingTool tau_triggerEmbedderTool(triggerBits,triggerObjects,triggerPreScales,names,
        //               tau_trigMatchDRcut,tau_trigMatchTypes,tau_trigSummaryPathsAndFilters);

        // if(anNtupleEvent.leg1().leptonType()==TupleLeptonTypes::anElectron)
        // else if(anNtupleEvent.leg1().leptonType()==TupleLeptonTypes::aMuon)
        // else if(anNtupleEvent.leg1().leptonType()==TupleLeptonTypes::aTau)

        // if(anNtupleEvent.leg2().leptonType()==TupleLeptonTypes::anElectron)
        // else if(anNtupleEvent.leg2().leptonType()==TupleLeptonTypes::aMuon)
        // else if(anNtupleEvent.leg2().leptonType()==TupleLeptonTypes::aTau)



        /* push back the current pair */
         NtupleEvents->push_back(anNtupleEvent);
 

      }


  }

iEvent.put( NtupleEvents, NAME_ );











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
