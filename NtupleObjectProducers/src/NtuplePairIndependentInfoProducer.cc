// -*- C++ -*-
//
// Package:    NtuplePairIndependentInfoProducer
// Class:      NtuplePairIndependentInfoProducer
//
/**\class NtuplePairIndependentInfoProducer NtuplePairIndependentInfoProducer.cc TEMP/NtuplePairIndependentInfoProducer/src/NtuplePairIndependentInfoProducer.cc

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
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleGenParticle.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;
typedef std::vector<edm::InputTag> VInputTag;


//
// class declaration
//

class NtuplePairIndependentInfoProducer : public edm::EDProducer {
public:
  explicit NtuplePairIndependentInfoProducer(const edm::ParameterSet&);
  ~NtuplePairIndependentInfoProducer();

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

  edm::InputTag packedGenSrc_;
  edm::InputTag prunedGenSrc_;
  string NAME_;
  std::vector<int> genParticlesToKeep_;
  edm::InputTag slimmedJetSrc_;


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
NtuplePairIndependentInfoProducer::NtuplePairIndependentInfoProducer(const edm::ParameterSet& iConfig):
packedGenSrc_(iConfig.getParameter<edm::InputTag>("packedGenSrc" )),
prunedGenSrc_(iConfig.getParameter<edm::InputTag>("prundedGenSrc" )),
NAME_(iConfig.getParameter<string>("NAME" )),
genParticlesToKeep_(iConfig.getParameter<std::vector<int>>("genParticlesToKeep" )),
slimmedJetSrc_(iConfig.getParameter<edm::InputTag>("slimmedJetSrc" ))
{


  produces<vector<NtuplePairIndependentInfo>>(NAME_).setBranchAlias(NAME_);


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


NtuplePairIndependentInfoProducer::~NtuplePairIndependentInfoProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
NtuplePairIndependentInfoProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  auto_ptr<NtuplePairIndependentInfoCollection> pairIndep (new NtuplePairIndependentInfoCollection);


  // get packedGen collection
  edm::Handle<edm::View<pat::PackedGenParticle> > packedGens;
  iEvent.getByLabel(packedGenSrc_,packedGens);

  // get prunedGen collection
  edm::Handle<edm::View<reco::GenParticle> > prunedGens;
  iEvent.getByLabel(prunedGenSrc_,prunedGens);


  std::size_t reserveSize =  prunedGens->size();
  pairIndep->reserve( reserveSize );


  // the instance of NtuplePairIndependentInfo we want to add to the event output

  NtuplePairIndependentInfo InfoToWrite;


  /////////////////////////////////////////////////////////////////
  /* start by adding gen particles to InfoToWrite */
  /////////////////////////////////////////////////////////////////

  std::vector<int> typesTokeep = genParticlesToKeep_;

  if(prunedGens.isValid()) 
  {

    for(std::size_t i = 0; i<prunedGens->size(); ++i)
    {
    
      //////////////////////////////////////////
      // check that pdgId is in typesTokeep

      bool keep = 0;
      int currentID = abs(prunedGens->at(i).pdgId());

      for(std::size_t s = 0; s<typesTokeep.size(); ++s)
      {

        if (currentID==typesTokeep[s]) keep = 1;

      }

      /* if no pdgIds were provided keep all */

      if(typesTokeep.size()==0) keep = 1;



      if(!keep) continue;

      NtupleGenParticle currentNtupleGenParticle;
      currentNtupleGenParticle.initialize((prunedGens->at(i)));


   for(std::size_t d = 0; d<prunedGens->at(i).numberOfDaughters(); ++d)
    {
      int ID = prunedGens->at(i).daughter(d)->pdgId();
      int STATUS = prunedGens->at(i).daughter(d)->status();
      LorentzVector P4 = prunedGens->at(i).daughter(d)->p4();
      currentNtupleGenParticle.add_daughter(ID, STATUS, P4);
    }

   for(std::size_t m = 0; m<prunedGens->at(i).numberOfMothers(); ++m)
    {
      int ID = prunedGens->at(i).mother(m)->pdgId();
      int STATUS = prunedGens->at(i).mother(m)->status();
      LorentzVector P4 = prunedGens->at(i).mother(m)->p4();
      currentNtupleGenParticle.add_mother(ID, STATUS, P4);
    }    

      InfoToWrite.fill_genParticle(currentNtupleGenParticle);


    }

  }

  /////////////////////////////////////////////////////////////////
  /* next add jets to InfoToWrite */
  /////////////////////////////////////////////////////////////////



  // get slimmedJet collection
  edm::Handle<edm::View<pat::Jet> > slimmedJets;
  iEvent.getByLabel(slimmedJetSrc_,slimmedJets);


  if(slimmedJets.isValid()) 
  {

    for(std::size_t i = 0; i<slimmedJets->size(); ++i)
    {

      NtupleJet currentNtupleJet;
      currentNtupleJet.fill((slimmedJets->at(i)));

      // temp -- start
      for( std::size_t t = 0; t<currentNtupleJet.JEC_labels().size(); ++t)
       {
        std::cout<<currentNtupleJet.JEC_labels().at(t)<<" "<<currentNtupleJet.JEC_SFs().at(t)<<"\n";
       } 

       std::cout<<" A good label : L1FastJet " << currentNtupleJet.JEC("L1FastJet")<<"\n";
       std::cout<<" A good label : Uncorrected " << currentNtupleJet.JEC("Uncorrected")<<"\n";


      // temp -- end

      InfoToWrite.fill_jet(currentNtupleJet);

    }
  }


  /////////////////////////////////////////////////////////////////
  /* next add InfoToWrite to pairIndep and write to the event */
  /////////////////////////////////////////////////////////////////


  pairIndep->push_back(InfoToWrite);

  iEvent.put( pairIndep, NAME_ );








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
NtuplePairIndependentInfoProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
NtuplePairIndependentInfoProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
NtuplePairIndependentInfoProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
NtuplePairIndependentInfoProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
NtuplePairIndependentInfoProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
NtuplePairIndependentInfoProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
NtuplePairIndependentInfoProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}



//define this as a plug-in
DEFINE_FWK_MODULE(NtuplePairIndependentInfoProducer);
