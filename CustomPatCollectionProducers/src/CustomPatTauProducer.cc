// -*- C++ -*-
//
// Package:    CustomPatTauProducer
// Class:      CustomPatTauProducer
//
/**\class CustomPatTauProducer CustomPatTauProducer.cc TEMP/CustomPatTauProducer/src/CustomPatTauProducer.cc

Description: produce 3 copies of the input pat::tau collection with user embedded info and ES variation

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



typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;
typedef std::vector<pat::Tau> PatTauCollection;
typedef std::vector<edm::InputTag> vInputTag;



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
  edm::EDGetTokenT<edm::View< pat::Tau > > tauToken_;

  string NAME_;
 
  edm::InputTag vertexSrc_;
  edm::EDGetTokenT< edm::View<reco::Vertex> > vertexToken_;



  double TauEsCorrection_;
  double TauEsUpSystematic_;
  double TauEsDownSystematic_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBitSrc_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPreScaleSrc_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectSrc_;
 

  std::string NAME_NOMINAL;
  std::string NAME_UP;
  std::string NAME_DOWN;

  vInputTag rhoSources_;
  std::vector < edm::EDGetTokenT<double> > rhoTokens_;




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
vertexSrc_(iConfig.getParameter<edm::InputTag>("vertexSrc" )),
TauEsCorrection_(iConfig.getParameter<double>("TauEsCorrection" )),
TauEsUpSystematic_(iConfig.getParameter<double>("TauEsUpSystematic" )),
TauEsDownSystematic_(iConfig.getParameter<double>("TauEsDownSystematic" )),
triggerBitSrc_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerBitSrc"))),
triggerPreScaleSrc_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("triggerPreScaleSrc"))),
triggerObjectSrc_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("triggerObjectSrc"))),
rhoSources_(iConfig.getParameter<vInputTag>("rhoSources" ))
{

  NAME_NOMINAL = NAME_+"TauEsNominal";
  NAME_UP = NAME_+"TauEsUp";
  NAME_DOWN = NAME_+"TauEsDown";

  produces<PatTauCollection>(NAME_NOMINAL).setBranchAlias(NAME_NOMINAL);
  produces<PatTauCollection>(NAME_UP).setBranchAlias(NAME_UP);
  produces<PatTauCollection>(NAME_DOWN).setBranchAlias(NAME_DOWN);

  tauToken_ = consumes< edm::View<pat::Tau> >(tauSrc_);

  vertexToken_ = consumes< edm::View<reco::Vertex> >(vertexSrc_);

  for(vInputTag::const_iterator it=rhoSources_.begin();it!=rhoSources_.end();it++) 
  {
    rhoTokens_.push_back( consumes<double >( *it ) );
  }




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
  iEvent.getByToken(vertexToken_,vertices);
  const reco::Vertex & first_vertex = vertices->at(0);

  // get Tau collection
  edm::Handle<edm::View<pat::Tau> > taus;
  iEvent.getByToken(tauToken_,taus);

  // get the rho variants

  std::vector<std::string> rhoNames;
  std::vector<double> rhos;


  for(std::size_t r = 0; r<rhoTokens_.size(); ++r)
  {
    edm::Handle<double> arho;
    iEvent.getByToken(rhoTokens_[r],arho);

    rhoNames.push_back(rhoSources_[r].label());
    rhos.push_back(*arho);
    //std::cout<<rhoSources_[r].label()<<" "<<*arho<<std::endl;

  }


// get trigger-related collections

    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<pat::PackedTriggerPrescales> triggerPreScales;

    iEvent.getByToken(triggerBitSrc_, triggerBits);
    iEvent.getByToken(triggerObjectSrc_, triggerObjects);
    iEvent.getByToken(triggerPreScaleSrc_, triggerPreScales);

    const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);

  // add the user embedded info and create ES corrected Sys. variants
  // for data no corrections will be applied due to the genJet requirement
  // need to be careful about this when embedded samples arrive

  TauClones allClones(taus,first_vertex,TauEsCorrection_,TauEsUpSystematic_,TauEsDownSystematic_,
                      triggerBits,triggerObjects,triggerPreScales,names,rhoNames,rhos);



  auto_ptr<PatTauCollection> storedTausNominal (new PatTauCollection);
  auto_ptr<PatTauCollection> storedTausUp (new PatTauCollection);
  auto_ptr<PatTauCollection> storedTausDown (new PatTauCollection);


  // control memory usage by reserving max size 
  std::size_t reserveSize =  taus->size();
  storedTausNominal->reserve( reserveSize );
  storedTausUp->reserve( reserveSize );
  storedTausDown->reserve( reserveSize );



  for (std::size_t i = 0; i<taus->size(); i++)
  {


    //const pat::Tau & original = allClones.clones[i];
    const pat::Tau & TauToStoreNominal = allClones.clonesCorrectedNominalEsShift[i];
    const pat::Tau & TauToStoreUp = allClones.clonesCorrectedUpEsShift[i];
    const pat::Tau & TauToStoreDown = allClones.clonesCorrectedDownEsShift[i];


    //dump userFloats -- test start
    // for (std::size_t ii = 0; ii < TauToStoreNominal.userFloatNames().size(); ii ++ )
    // {
    //     std::cout<<"nominal tau "<<i<<" "<<TauToStoreNominal.userFloatNames().at(ii)<<" "<<TauToStoreNominal.userFloat(TauToStoreNominal.userFloatNames().at(ii))<<"\n";
    // }
    
    // for (std::size_t ii = 0; ii < TauToStoreUp.userFloatNames().size(); ii ++ )
    // {
    //     std::cout<<"up tau "<<i<<" "<<TauToStoreUp.userFloatNames().at(ii)<<" "<<TauToStoreUp.userFloat(TauToStoreUp.userFloatNames().at(ii))<<"\n";
    // }

    // for (std::size_t ii = 0; ii < TauToStoreDown.userFloatNames().size(); ii ++ )
    // {
    //     std::cout<<"down tau "<<i<<" "<<TauToStoreDown.userFloatNames().at(ii)<<" "<<TauToStoreDown.userFloat(TauToStoreDown.userFloatNames().at(ii))<<"\n";
    // }
    //dump userFloats -- test end




    storedTausNominal->push_back(TauToStoreNominal);
    storedTausUp->push_back(TauToStoreUp);
    storedTausDown->push_back(TauToStoreDown);


  }

  // add the taus to the event output

  iEvent.put(storedTausNominal,NAME_NOMINAL);
  iEvent.put(storedTausUp,NAME_UP);
  iEvent.put(storedTausDown,NAME_DOWN);


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
