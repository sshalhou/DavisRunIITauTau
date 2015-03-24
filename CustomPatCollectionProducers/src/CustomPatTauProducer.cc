// -*- C++ -*-
//
// Package:    CustomPatTauProducer
// Class:      CustomPatTauProducer
//
/**\class CustomPatTauProducer CustomPatTauProducer.cc TEMP/CustomPatTauProducer/src/CustomPatTauProducer.cc

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

// needed by ntuple Tau producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "Math/GenVector/VectorUtil.h"
#include "DataFormats/PatCandidates/interface/PFParticle.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/LeptonRelativeIsolationTool.h"
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/TauClones.h"

typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;



//
// class declaration
//

class CustomPatTauProducer : public edm::EDProducer {
public:
  explicit CustomPatTauProducer(const edm::ParameterSet&);
  ~CustomPatTauProducer();

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
  edm::ParameterSet cutSrc;
  edm::InputTag vertexSrc_;

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
CustomPatTauProducer::CustomPatTauProducer(const edm::ParameterSet& iConfig):
tauSrc_(iConfig.getParameter<edm::InputTag>("tauSrc" )),
NAME_(iConfig.getParameter<string>("NAME" )),
cutSrc(iConfig.getParameter<edm::ParameterSet>("cutSrc")),
vertexSrc_(iConfig.getParameter<edm::InputTag>("vertexSrc" ))
{


  produces<vector<pat::Tau>>(NAME_).setBranchAlias(NAME_);






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


CustomPatTauProducer::~CustomPatTauProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
CustomPatTauProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{



  // get vertex collection
  edm::Handle<edm::View<reco::Vertex> > vertices;
  iEvent.getByLabel(vertexSrc_,vertices);
  const reco::Vertex & first_vertex = vertices->at(0);

  // get Tau collection
  edm::Handle<edm::View<pat::Tau> > taus;
  iEvent.getByLabel(tauSrc_,taus);




  TauClones tauClone(taus,first_vertex); 



  std::vector<pat::Tau> * storedTaus = new std::vector<pat::Tau>();


  for (std::size_t i = 0; i<taus->size(); i++)
  {




    const pat::Tau & TauToStore = tauClone.clones[i];
    storedTaus->push_back(TauToStore);

  }

  // add the taus to the event output
  std::auto_ptr<std::vector<pat::Tau> > eptr(storedTaus);
  iEvent.put(eptr,NAME_);


}

// ------------ method called once each job just before starting event loop  ------------
void
CustomPatTauProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
CustomPatTauProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
CustomPatTauProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
CustomPatTauProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
CustomPatTauProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
CustomPatTauProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CustomPatTauProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CustomPatTauProducer);
