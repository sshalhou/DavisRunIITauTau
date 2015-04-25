// -*- C++ -*-
//
// Package:    CustomPatElectronProducer
// Class:      CustomPatElectronProducer
//
/**\class CustomPatElectronProducer CustomPatElectronProducer.cc TEMP/CustomPatElectronProducer/src/CustomPatElectronProducer.cc

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

// needed by ntuple electron producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Electron.h"
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
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaMvaEleEstimatorCSA14.h"
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/LeptonRelativeIsolationTool.h"
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/ElectronClones.h"


#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"



typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;
typedef std::vector<pat::Electron> PatElectronCollection;
typedef std::vector<edm::InputTag> vInputTag;

//
// class declaration
//

class CustomPatElectronProducer : public edm::EDProducer {
public:
  explicit CustomPatElectronProducer(const edm::ParameterSet&);
  ~CustomPatElectronProducer();

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
  edm::InputTag vertexSrc_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBitSrc_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPreScaleSrc_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectSrc_;
  double triggerMatchDRSrc_;
  std::vector<int> triggerMatchTypesSrc_;
  std::vector<std::string> triggerMatchPathsAndFiltersSrc_;
  vInputTag rhoSources_;

  // the mva ID estimator for CSA14 and Phs14(?)
  EGammaMvaEleEstimatorCSA14 MVA_NonTrigPhys14;

  // note: if additonal MVAs are needed add them in ElectronClones.h

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
CustomPatElectronProducer::CustomPatElectronProducer(const edm::ParameterSet& iConfig):
electronSrc_(iConfig.getParameter<edm::InputTag>("electronSrc" )),
NAME_(iConfig.getParameter<string>("NAME" )),
vertexSrc_(iConfig.getParameter<edm::InputTag>("vertexSrc" )),
triggerBitSrc_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerBitSrc"))),
triggerPreScaleSrc_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("triggerPreScaleSrc"))),
triggerObjectSrc_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("triggerObjectSrc"))),
triggerMatchDRSrc_(iConfig.getParameter<double>("triggerMatchDRSrc" )),
triggerMatchTypesSrc_(iConfig.getParameter<std::vector<int>>("triggerMatchTypesSrc" )),
triggerMatchPathsAndFiltersSrc_(iConfig.getParameter<std::vector<std::string>>("triggerMatchPathsAndFiltersSrc" )),
rhoSources_(iConfig.getParameter<vInputTag>("rhoSources" ))
{


  produces<PatElectronCollection>(NAME_).setBranchAlias(NAME_);


  // define the various MVA electron IDs that we want to (re)run on mini-AOD
  // since these are likely to change soon will stick with one variant for now


  std::vector<std::string> NonTrigPhys14;
  NonTrigPhys14.push_back(edm::FileInPath ("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB1_5_oldscenario2phys14_BDT.weights.xml").fullPath()) ; 
  NonTrigPhys14.push_back(edm::FileInPath ("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB2_5_oldscenario2phys14_BDT.weights.xml").fullPath()) ; 
  NonTrigPhys14.push_back(edm::FileInPath ("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EE_5_oldscenario2phys14_BDT.weights.xml").fullPath()) ; 
  NonTrigPhys14.push_back(edm::FileInPath ("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB1_10_oldscenario2phys14_BDT.weights.xml").fullPath()) ; 
  NonTrigPhys14.push_back(edm::FileInPath ("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB2_10_oldscenario2phys14_BDT.weights.xml").fullPath()) ; 
  NonTrigPhys14.push_back(edm::FileInPath ("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EE_10_oldscenario2phys14_BDT.weights.xml").fullPath()) ; 


  MVA_NonTrigPhys14.initialize("BDT",
                          EGammaMvaEleEstimatorCSA14::kNonTrigPhys14,
                          true,
                          NonTrigPhys14);






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


CustomPatElectronProducer::~CustomPatElectronProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
CustomPatElectronProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{



  // get vertex collection
  edm::Handle<edm::View<reco::Vertex> > vertices;
  iEvent.getByLabel(vertexSrc_,vertices);
  const reco::Vertex & first_vertex = vertices->at(0);

  // get electron collection
  edm::Handle<edm::View<pat::Electron> > electrons;
  iEvent.getByLabel(electronSrc_,electrons);

  // get the rho variants

  std::vector<std::string> rhoNames;
  std::vector<double> rhos;

  for(  edm::InputTag rs : rhoSources_ )
  {

  edm::Handle<double> arho;
  iEvent.getByLabel(rs,arho);

  rhoNames.push_back(rs.label());
  rhos.push_back(*arho);
  //std::cout<<rs.label()<<" "<<*arho<<std::endl;

  }



  // get trigger-related collections

    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<pat::PackedTriggerPrescales> triggerPreScales;

    iEvent.getByToken(triggerBitSrc_, triggerBits);
    iEvent.getByToken(triggerObjectSrc_, triggerObjects);
    iEvent.getByToken(triggerPreScaleSrc_, triggerPreScales);

    const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);



  // clone & fill the electron with user-computed quantities including mva

  std::string MVA_NonTrigPhys14_name = "MVA_NonTrigPhys14";
  electronClones ele(electrons,first_vertex,MVA_NonTrigPhys14,MVA_NonTrigPhys14_name,
                    triggerBits,triggerObjects,triggerPreScales,names,
                    triggerMatchDRSrc_,triggerMatchTypesSrc_,triggerMatchPathsAndFiltersSrc_,
                    rhoNames,rhos); 




  auto_ptr<PatElectronCollection> storedElectrons (new PatElectronCollection);


  for (std::size_t i = 0; i<electrons->size(); i++)
  {




    const pat::Electron & electronToStore = ele.clones[i];

    // if(electronToStore.userFloat("dxy"))
    // std::cout<<"TEST OK "<<electronToStore.userFloat("dxy")<<"\n";

    // if(electronToStore.userFloat("MMMMMM"))
    // std::cout<<"TEST NOT OK "<<electronToStore.userFloat("MMMMMM")<<"\n";
  

    // dump userFloats -- test start
    for (std::size_t ii = 0; ii < electronToStore.userFloatNames().size(); ii ++ )
    {
        std::cout<<"electron "<<i<<" "<<electronToStore.userFloatNames().at(ii)<<" "<<electronToStore.userFloat(electronToStore.userFloatNames().at(ii))<<"\n";
    }
    // dump userFloats -- test end


    storedElectrons->push_back(electronToStore);

  }

  // add the electrons to the event output
  iEvent.put(storedElectrons,NAME_);


}

// ------------ method called once each job just before starting event loop  ------------
void
CustomPatElectronProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
CustomPatElectronProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
CustomPatElectronProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
CustomPatElectronProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
CustomPatElectronProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
CustomPatElectronProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CustomPatElectronProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CustomPatElectronProducer);
