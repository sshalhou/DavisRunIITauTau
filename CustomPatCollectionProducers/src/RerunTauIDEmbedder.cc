// -*- C++ -*-
//
// Package:    RerunTauIDEmbedder
// Class:      RerunTauIDEmbedder
//
/**\class creat a new tau collection with embedded tau IDs (if rerun is needed)

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

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/PatCandidates/interface/PATTauDiscriminator.h"


typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;
typedef std::vector<pat::Tau> PatTauCollection;
typedef std::vector<edm::InputTag> vInputTag;



//
// class declaration
//

class RerunTauIDEmbedder : public edm::EDProducer {
public:
  explicit RerunTauIDEmbedder(const edm::ParameterSet&);
  ~RerunTauIDEmbedder();

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
  edm::EDGetTokenT<pat::TauCollection> tauToken_;

  edm::InputTag mvaIsolationSrc_;
  edm::EDGetTokenT<pat::PATTauDiscriminator> mvaIsolationToken_;

  edm::InputTag mvaIsolationVLooseSrc_;
  edm::EDGetTokenT<pat::PATTauDiscriminator> mvaIsolationVLooseToken_;

  edm::InputTag mvaIsolationLooseSrc_;
  edm::EDGetTokenT<pat::PATTauDiscriminator> mvaIsolationLooseToken_;

  edm::InputTag mvaIsolationMediumSrc_;
  edm::EDGetTokenT<pat::PATTauDiscriminator> mvaIsolationMediumToken_;

  edm::InputTag mvaIsolationTightSrc_;
  edm::EDGetTokenT<pat::PATTauDiscriminator> mvaIsolationTightToken_;

  edm::InputTag mvaIsolationVTightSrc_;
  edm::EDGetTokenT<pat::PATTauDiscriminator> mvaIsolationVTightToken_;

  edm::InputTag mvaIsolationVVTightSrc_;
  edm::EDGetTokenT<pat::PATTauDiscriminator> mvaIsolationVVTightToken_;


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
RerunTauIDEmbedder::RerunTauIDEmbedder(const edm::ParameterSet& iConfig):
tauSrc_(iConfig.getParameter<edm::InputTag>("tauSrc" )),
mvaIsolationSrc_(iConfig.getParameter<edm::InputTag>("mvaIsolationSrc")),
mvaIsolationVLooseSrc_(iConfig.getParameter<edm::InputTag>("mvaIsolationVLooseSrc")),
mvaIsolationLooseSrc_(iConfig.getParameter<edm::InputTag>("mvaIsolationLooseSrc")),
mvaIsolationMediumSrc_(iConfig.getParameter<edm::InputTag>("mvaIsolationMediumSrc")),
mvaIsolationTightSrc_(iConfig.getParameter<edm::InputTag>("mvaIsolationTightSrc")),
mvaIsolationVTightSrc_(iConfig.getParameter<edm::InputTag>("mvaIsolationVTightSrc")),
mvaIsolationVVTightSrc_(iConfig.getParameter<edm::InputTag>("mvaIsolationVVTightSrc")),
NAME_(iConfig.getParameter<string>("NAME" ))
{

  produces<PatTauCollection>(NAME_).setBranchAlias(NAME_);

  tauToken_ = consumes< pat::TauCollection >(tauSrc_);

  mvaIsolationToken_ = consumes<pat::PATTauDiscriminator>(mvaIsolationSrc_);
  mvaIsolationVLooseToken_ = consumes<pat::PATTauDiscriminator>(mvaIsolationVLooseSrc_);
  mvaIsolationLooseToken_ = consumes<pat::PATTauDiscriminator>(mvaIsolationLooseSrc_);
  mvaIsolationMediumToken_ = consumes<pat::PATTauDiscriminator>(mvaIsolationMediumSrc_);
  mvaIsolationTightToken_ = consumes<pat::PATTauDiscriminator>(mvaIsolationTightSrc_);
  mvaIsolationVTightToken_ = consumes<pat::PATTauDiscriminator>(mvaIsolationVTightSrc_);
  mvaIsolationVVTightToken_ = consumes<pat::PATTauDiscriminator>(mvaIsolationVVTightSrc_);

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


RerunTauIDEmbedder::~RerunTauIDEmbedder()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
RerunTauIDEmbedder::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{



  // get Tau collection
  edm::Handle<pat::TauCollection> taus;
  iEvent.getByToken(tauToken_,taus);


  // get the rerun Tau IDs
  edm::Handle<pat::PATTauDiscriminator> mvaIsoRaw;
  iEvent.getByToken(mvaIsolationToken_,mvaIsoRaw);

  edm::Handle<pat::PATTauDiscriminator> mvaIsoVLoose;
  iEvent.getByToken(mvaIsolationVLooseToken_,mvaIsoVLoose);

  edm::Handle<pat::PATTauDiscriminator> mvaIsoLoose;
  iEvent.getByToken(mvaIsolationLooseToken_,mvaIsoLoose);

  edm::Handle<pat::PATTauDiscriminator> mvaIsoMedium;
  iEvent.getByToken(mvaIsolationMediumToken_,mvaIsoMedium);

  edm::Handle<pat::PATTauDiscriminator> mvaIsoTight;
  iEvent.getByToken(mvaIsolationTightToken_,mvaIsoTight);

  edm::Handle<pat::PATTauDiscriminator> mvaIsoVTight;
  iEvent.getByToken(mvaIsolationVTightToken_,mvaIsoVTight);

  edm::Handle<pat::PATTauDiscriminator> mvaIsoVVTight;
  iEvent.getByToken(mvaIsolationVVTightToken_,mvaIsoVVTight);


  auto_ptr<PatTauCollection> storedTaus (new PatTauCollection);


  // control memory usage by reserving max size 
  std::size_t reserveSize =  taus->size();
  storedTaus->reserve( reserveSize );


  for (unsigned i = 0; i<taus->size(); i++)
  {

    pat::Tau * TauToStore = taus->at(i).clone();


    pat::TauRef tauRef(taus,i);


    // std::cout<<"mvaIsoRaw = "<<     (*mvaIsoRaw)[tauRef] <<" \n";
    // std::cout<<"mvaIsoVLoose = "<<      (*mvaIsoVLoose)[tauRef]<<" \n";
    // std::cout<<"mvaIsoLoose = "<<     (*mvaIsoLoose)[tauRef]<<" \n";
    // std::cout<<"mvaIsoMedium = "<<      (*mvaIsoMedium)[tauRef]<<" \n";
    // std::cout<<"mvaIsoTight = "<<     (*mvaIsoTight)[tauRef]<<" \n";
    // std::cout<<"mvaIsoVTight = "<<      (*mvaIsoVTight)[tauRef]<<" \n";
    // std::cout<<"mvaIsoVVTight = "<<     (*mvaIsoVVTight)[tauRef]<<" \n";

    TauToStore->addUserFloat("rerunDiscriminationByIsolationMVArun2v1raw",(*mvaIsoRaw)[tauRef]);
    TauToStore->addUserFloat("rerunDiscriminationByIsolationMVArun2v1VLoose",(*mvaIsoVLoose)[tauRef]);
    TauToStore->addUserFloat("rerunDiscriminationByIsolationMVArun2v1Loose",(*mvaIsoLoose)[tauRef]);
    TauToStore->addUserFloat("rerunDiscriminationByIsolationMVArun2v1Medium",(*mvaIsoMedium)[tauRef]);
    TauToStore->addUserFloat("rerunDiscriminationByIsolationMVArun2v1Tight",(*mvaIsoTight)[tauRef]);
    TauToStore->addUserFloat("rerunDiscriminationByIsolationMVArun2v1VTight",(*mvaIsoVTight)[tauRef]);
    TauToStore->addUserFloat("rerunDiscriminationByIsolationMVArun2v1VVTight",(*mvaIsoVVTight)[tauRef]);


    storedTaus->push_back(*TauToStore);
  }

  // add the taus to the event output

  iEvent.put(storedTaus,NAME_);


}

// ------------ method called once each job just before starting event loop  ------------
void
RerunTauIDEmbedder::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
RerunTauIDEmbedder::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
RerunTauIDEmbedder::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
RerunTauIDEmbedder::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
RerunTauIDEmbedder::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
RerunTauIDEmbedder::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RerunTauIDEmbedder::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RerunTauIDEmbedder);
