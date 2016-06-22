// -*- C++ -*-
//
// Package:    TrimmedPatTauProducer
// Class:      TrimmedPatTauProducer
//
/**\class TrimmedPatTauProducer TrimmedPatTauProducer.cc TEMP/TrimmedPatTauProducer/src/TrimmedPatTauProducer.cc

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

// needed by ntuple tau producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Tau.h"
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

class TrimmedPatTauProducer : public edm::EDProducer {
public:
  explicit TrimmedPatTauProducer(const edm::ParameterSet&);
  ~TrimmedPatTauProducer();

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

  edm::InputTag tauSrc_;
  edm::EDGetTokenT<edm::View< pat::Tau > > tauToken_;

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
TrimmedPatTauProducer::TrimmedPatTauProducer(const edm::ParameterSet& iConfig):
tauSrc_(iConfig.getParameter<edm::InputTag>("tauSrc" )),
MAX_TO_KEEP_(iConfig.getParameter<unsigned int>("MAX_TO_KEEP" )),
NAME_(iConfig.getParameter<string>("NAME" ))
{


  produces<vector<pat::Tau>>(NAME_).setBranchAlias(NAME_);

  tauToken_ = consumes< edm::View<pat::Tau> >(tauSrc_);



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


TrimmedPatTauProducer::~TrimmedPatTauProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TrimmedPatTauProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{


  // get Tau collection
  edm::Handle<edm::View<pat::Tau> > taus;
  iEvent.getByToken(tauToken_,taus);

  std::vector<pat::Tau> * storedTaus = new std::vector<pat::Tau>();


  for (std::size_t i = 0; i<taus->size(); i++)
  {
    if(i<MAX_TO_KEEP_)
    {
       const pat::Tau & tauToStore = taus->at(i);
       storedTaus->push_back(tauToStore);
    }
  }


//  std::cout<<"MAX_TO_KEEP = "<<MAX_TO_KEEP_<<"\n";
//  std::cout<<"KEEPING ONLY "<<storedTaus->size()<<" of "<<taus->size()<<" TOTAL TAUS \n";
  // add the taus to the event output
  std::auto_ptr<std::vector<pat::Tau> > eptr(storedTaus);
  iEvent.put(eptr,NAME_);


}

// ------------ method called once each job just before starting event loop  ------------
void
TrimmedPatTauProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TrimmedPatTauProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
TrimmedPatTauProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
TrimmedPatTauProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
TrimmedPatTauProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
TrimmedPatTauProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TrimmedPatTauProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrimmedPatTauProducer);
