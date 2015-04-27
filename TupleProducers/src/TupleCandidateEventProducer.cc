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
#include "TauAnalysis/SVfitStandalone/interface/SVfitStandaloneAlgorithm.h"


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
  double computeSVMass(reco::PFMET,std::vector<svFitStandalone::MeasuredTauLepton>);


  // ----------member data ---------------------------

  edm::InputTag tauSrc_;
  edm::InputTag electronSrc_;
  edm::InputTag muonSrc_;
  edm::InputTag pfMETSrc_;
  edm::InputTag mvaMETSrc_;
  edm::InputTag electronVetoSrc_;
  edm::InputTag muonVetoSrc_;
  double vetoDeltaR_;
  string NAME_;
  bool doSVMass_;
  bool useMVAMET_;
  double logMterm_;
  int svMassVerbose_;
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
pfMETSrc_(iConfig.getParameter<edm::InputTag>("pfMETSrc" )),
mvaMETSrc_(iConfig.getParameter<edm::InputTag>("mvaMETSrc" )),
electronVetoSrc_(iConfig.getParameter<edm::InputTag>("electronVetoSrc" )),
muonVetoSrc_(iConfig.getParameter<edm::InputTag>("muonVetoSrc" )),
vetoDeltaR_(iConfig.getParameter<double>("vetoDeltaR" )),
doSVMass_(iConfig.getParameter<bool>("doSVMass" )),
useMVAMET_(iConfig.getParameter<bool>("useMVAMET" )),
logMterm_(iConfig.getParameter<double>("logMterm" )),
svMassVerbose_(iConfig.getParameter<int>("svMassVerbose" ))
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

  // get VETO Electron collection
  edm::Handle<edm::View<pat::Electron> > veto_electrons;
  iEvent.getByLabel(electronVetoSrc_,veto_electrons);

  // get VETO Muon collection
  edm::Handle<edm::View<pat::Muon> > veto_muons;
  iEvent.getByLabel(muonVetoSrc_,veto_muons);


  // get mvaMET collection
  edm::Handle <std::vector<reco::PFMET> >  mvamets;
  iEvent.getByLabel(mvaMETSrc_,mvamets);

  // get pfMET collection
  edm::Handle <std::vector<reco::PFMET> >  pfmets;
  iEvent.getByLabel(pfMETSrc_,pfmets);

  auto_ptr<TupleCandidateEventCollection> TupleCandidateEvents (new TupleCandidateEventCollection);




 
  // electron-electron 
  if (electrons.isValid())
  {
    for (std::size_t i=0; i<electrons->size(); ++i)
    {
      for (std::size_t ii=i+1; ii<electrons->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(electrons->at(i),electrons->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(electrons->at(i).pt(), electrons->at(i).eta(), electrons->at(i).phi(),electrons->at(i).mass());
          l2.SetPtEtaPhiM(electrons->at(ii).pt(), electrons->at(ii).eta(), electrons->at(ii).phi(),electrons->at(ii).mass());

          if(l1.DeltaR(l2)<vetoDeltaR_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoMuon(veto_muons->at(vm));
            }
          }
          ///////////////////


        /////// SVMASS 
        std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
        measuredTauLeptons.clear();

        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToElecDecay, 
          electrons->at(i).p4().pt(),electrons->at(i).p4().eta(),electrons->at(i).p4().phi(),
          svFitStandalone::electronMass));

        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToElecDecay,
          electrons->at(ii).p4().pt(),electrons->at(ii).p4().eta(),electrons->at(ii).p4().phi(),
          svFitStandalone::electronMass));


        double sv_mass = 0.0;          

        if(useMVAMET_)
          sv_mass = computeSVMass(mvamets->at(0),measuredTauLeptons);
        else
          sv_mass = computeSVMass(pfmets->at(0),measuredTauLeptons);



        CurrentCandidateEvent.set_SVMass(sv_mass);

        TupleCandidateEvents->push_back(CurrentCandidateEvent);






      }
    }
  }



  // electron-muon
  if (electrons.isValid() && muons.isValid())
  {
    for (std::size_t i=0; i<electrons->size(); ++i)
    {
      for (std::size_t ii=0; ii<muons->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(electrons->at(i),muons->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(electrons->at(i).pt(), electrons->at(i).eta(), electrons->at(i).phi(),electrons->at(i).mass());
          l2.SetPtEtaPhiM(muons->at(ii).pt(), muons->at(ii).eta(), muons->at(ii).phi(),muons->at(ii).mass());

          if(l1.DeltaR(l2)<vetoDeltaR_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoMuon(veto_muons->at(vm));
            }
          }
          ///////////////////


        /////// SVMASS 
        std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
        measuredTauLeptons.clear();

        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToElecDecay, 
          electrons->at(i).p4().pt(),electrons->at(i).p4().eta(),electrons->at(i).p4().phi(),
          svFitStandalone::electronMass));

        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToMuDecay,
          muons->at(ii).p4().pt(),muons->at(ii).p4().eta(),muons->at(ii).p4().phi(),
          svFitStandalone::muonMass));


        double sv_mass = 0.0;          

        if(useMVAMET_)
          sv_mass = computeSVMass(mvamets->at(0),measuredTauLeptons);
        else
          sv_mass = computeSVMass(pfmets->at(0),measuredTauLeptons);



        CurrentCandidateEvent.set_SVMass(sv_mass);

          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      }
    }
  }

  // electron-tau
  if (electrons.isValid() && taus.isValid())
  {

    for (std::size_t i=0; i<electrons->size(); ++i)
    {
      for (std::size_t ii=0; ii<taus->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(electrons->at(i),taus->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));          
         
          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(electrons->at(i).pt(), electrons->at(i).eta(), electrons->at(i).phi(),electrons->at(i).mass());
          l2.SetPtEtaPhiM(taus->at(ii).pt(), taus->at(ii).eta(), taus->at(ii).phi(),taus->at(ii).mass());

          if(l1.DeltaR(l2)<vetoDeltaR_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoMuon(veto_muons->at(vm));
            }
          }
          ///////////////////


        /////// SVMASS 
        std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
        measuredTauLeptons.clear();


        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToElecDecay, 
          electrons->at(i).p4().pt(),electrons->at(i).p4().eta(),electrons->at(i).p4().phi(),
          svFitStandalone::electronMass));

        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToHadDecay,
          taus->at(ii).p4().pt(),taus->at(ii).p4().eta(),taus->at(ii).p4().phi(),
          taus->at(ii).p4().mass()));


        double sv_mass = 0.0;          

        if(useMVAMET_)
          sv_mass = computeSVMass(mvamets->at(0),measuredTauLeptons);
        else
          sv_mass = computeSVMass(pfmets->at(0),measuredTauLeptons);



        CurrentCandidateEvent.set_SVMass(sv_mass);

          TupleCandidateEvents->push_back(CurrentCandidateEvent);
        
      }
    }
  }  

  // muon-muon
  if (muons.isValid())
  {
    for (std::size_t i=0; i<muons->size(); ++i)
    {
      for (std::size_t ii=i+1; ii<muons->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(muons->at(i),muons->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));  

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(muons->at(i).pt(), muons->at(i).eta(), muons->at(i).phi(),muons->at(i).mass());
          l2.SetPtEtaPhiM(muons->at(ii).pt(), muons->at(ii).eta(), muons->at(ii).phi(),muons->at(ii).mass());

          if(l1.DeltaR(l2)<vetoDeltaR_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoMuon(veto_muons->at(vm));
            }
          }
          ///////////////////

        /////// SVMASS 
        std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
        measuredTauLeptons.clear();


        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToMuDecay, 
          muons->at(i).p4().pt(),muons->at(i).p4().eta(),muons->at(i).p4().phi(),
          svFitStandalone::muonMass));

        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToMuDecay,
          muons->at(ii).p4().pt(),muons->at(ii).p4().eta(),muons->at(ii).p4().phi(),
          svFitStandalone::muonMass));





        double sv_mass = 0.0;          

        if(useMVAMET_)
          sv_mass = computeSVMass(mvamets->at(0),measuredTauLeptons);
        else
          sv_mass = computeSVMass(pfmets->at(0),measuredTauLeptons);



        CurrentCandidateEvent.set_SVMass(sv_mass);

          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      }
    }

  }


  // muon-tau
  if (muons.isValid() && taus.isValid())
  {


    for (std::size_t i=0; i<muons->size(); ++i)
    {
      for (std::size_t ii=0; ii<taus->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(muons->at(i),taus->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));    

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(muons->at(i).pt(), muons->at(i).eta(), muons->at(i).phi(),muons->at(i).mass());
          l2.SetPtEtaPhiM(taus->at(ii).pt(), taus->at(ii).eta(), taus->at(ii).phi(),taus->at(ii).mass());
        
          if(l1.DeltaR(l2)<vetoDeltaR_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoMuon(veto_muons->at(vm));
            }
          }
          ///////////////////


        /////// SVMASS 
        std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
        measuredTauLeptons.clear();


        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToMuDecay, 
          muons->at(i).p4().pt(),muons->at(i).p4().eta(),muons->at(i).p4().phi(),
          svFitStandalone::muonMass));

        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToHadDecay,
          taus->at(ii).p4().pt(),taus->at(ii).p4().eta(),taus->at(ii).p4().phi(),
          taus->at(ii).p4().mass()));





        double sv_mass = 0.0;          

        if(useMVAMET_)
          sv_mass = computeSVMass(mvamets->at(0),measuredTauLeptons);
        else
          sv_mass = computeSVMass(pfmets->at(0),measuredTauLeptons);



        CurrentCandidateEvent.set_SVMass(sv_mass);

          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      }
    }


  }

  // tau-tau
  if (taus.isValid())
  {

    for (std::size_t i=0; i<taus->size(); ++i)
    {
      for (std::size_t ii=i+1; ii<taus->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(taus->at(i),taus->at(ii));
          CurrentCandidateEvent.set_mvaMET(mvamets->at(0));     

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(taus->at(i).pt(), taus->at(i).eta(), taus->at(i).phi(),taus->at(i).mass());
          l2.SetPtEtaPhiM(taus->at(ii).pt(), taus->at(ii).eta(), taus->at(ii).phi(),taus->at(ii).mass());

          if(l1.DeltaR(l2)<vetoDeltaR_) continue;

          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaR_ && vetoCand.DeltaR(l2) > vetoDeltaR_ )
            {
              CurrentCandidateEvent.set_vetoMuon(veto_muons->at(vm));
            }
          }
          ///////////////////


        /////// SVMASS 
        std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
        measuredTauLeptons.clear();





        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToHadDecay,
          taus->at(i).p4().pt(),taus->at(i).p4().eta(),taus->at(i).p4().phi(),
          taus->at(i).p4().mass()));

        measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
          svFitStandalone::kTauToHadDecay,
          taus->at(ii).p4().pt(),taus->at(ii).p4().eta(),taus->at(ii).p4().phi(),
          taus->at(ii).p4().mass()));



        double sv_mass = 0.0;          

        if(useMVAMET_)
          sv_mass = computeSVMass(mvamets->at(0),measuredTauLeptons);
        else
          sv_mass = computeSVMass(pfmets->at(0),measuredTauLeptons);



        CurrentCandidateEvent.set_SVMass(sv_mass);


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

double TupleCandidateEventProducer::computeSVMass(reco::PFMET MET,std::vector<svFitStandalone::MeasuredTauLepton> MTL)
{

  if(!doSVMass_) return 0.0;





  // PFMET significance matrix
  TMatrixD covMET(2, 2); 
  covMET[0][0] = MET.getSignificanceMatrix()[0][0];
  covMET[1][0] = MET.getSignificanceMatrix()[1][0];
  covMET[0][1] = MET.getSignificanceMatrix()[0][1];
  covMET[1][1] = MET.getSignificanceMatrix()[1][1];
  if (svMassVerbose_)  covMET.Print();

  SVfitStandaloneAlgorithm svFitAlgorithm(MTL, MET.px(),MET.py(), covMET, svMassVerbose_);

  if(logMterm_>0)  svFitAlgorithm.addLogM(true, logMterm_);
  else svFitAlgorithm.addLogM(false, 0.);


  svFitAlgorithm.integrateVEGAS();
  double retSVmass = svFitAlgorithm.getMass();

  return retSVmass;

}




//define this as a plug-in
DEFINE_FWK_MODULE(TupleCandidateEventProducer);
