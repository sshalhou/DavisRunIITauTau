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
#include "TMatrix.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TauAnalysis/SVfitStandalone/interface/SVfitStandaloneAlgorithm.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h" /*TEMP*/
 

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

  /* sv mass is element 0, sv transverse mass is element 1 */
  std::vector<double> computeSVMassAndSVTransverseMass(reco::PFMET,std::vector<svFitStandalone::MeasuredTauLepton>);
  std::vector<double> computeSVMassAndSVTransverseMass(pat::MET,std::vector<svFitStandalone::MeasuredTauLepton>,double,double,double,double);


  // ----------member data ---------------------------

  edm::InputTag tauSrc_;
  edm::InputTag electronSrc_;
  edm::InputTag muonSrc_;
  edm::InputTag second_tauSrc_;
  edm::InputTag second_electronSrc_;
  edm::InputTag second_muonSrc_;
  edm::InputTag puppiMETSrc_;
  edm::InputTag pfMETSrc_;
  edm::InputTag mvaMETSrc_;
  edm::InputTag electronVetoSrc_;
  edm::InputTag muonVetoSrc_;
  double pairDeltaRmin_;
  double vetoDeltaRmin_;
  string NAME_;
  bool doSVMass_;
  bool useMVAMET_;
  double logMterm_;
  int svMassVerbose_;
  edm::InputTag pfCovMatrix_;

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
second_tauSrc_(iConfig.getParameter<edm::InputTag>("second_tauSrc" )),
second_electronSrc_(iConfig.getParameter<edm::InputTag>("second_electronSrc" )),
second_muonSrc_(iConfig.getParameter<edm::InputTag>("second_muonSrc" )),
puppiMETSrc_(iConfig.getParameter<edm::InputTag>("puppiMETSrc" )),
pfMETSrc_(iConfig.getParameter<edm::InputTag>("pfMETSrc" )),
mvaMETSrc_(iConfig.getParameter<edm::InputTag>("mvaMETSrc" )),
electronVetoSrc_(iConfig.getParameter<edm::InputTag>("electronVetoSrc" )),
muonVetoSrc_(iConfig.getParameter<edm::InputTag>("muonVetoSrc" )),
pairDeltaRmin_(iConfig.getParameter<double>("pairDeltaRmin" )),
vetoDeltaRmin_(iConfig.getParameter<double>("vetoDeltaRmin" )),
NAME_(iConfig.getParameter<string>("NAME" )),
doSVMass_(iConfig.getParameter<bool>("doSVMass" )),
useMVAMET_(iConfig.getParameter<bool>("useMVAMET" )),
logMterm_(iConfig.getParameter<double>("logMterm" )),
svMassVerbose_(iConfig.getParameter<int>("svMassVerbose" )),
pfCovMatrix_(iConfig.getParameter<edm::InputTag>("pfMetSig" ))
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

  // get 2nd Tau collection
  edm::Handle<edm::View<pat::Tau> > second_taus;
  iEvent.getByLabel(second_tauSrc_,second_taus);


  // get 2nd Electron collection
  edm::Handle<edm::View<pat::Electron> > second_electrons;
  iEvent.getByLabel(second_electronSrc_,second_electrons);

  // get 2nd Muon collection
  edm::Handle<edm::View<pat::Muon> > second_muons;
  iEvent.getByLabel(second_muonSrc_,second_muons);  

  // get VETO Electron collection
  edm::Handle<edm::View<pat::Electron> > veto_electrons;
  iEvent.getByLabel(electronVetoSrc_,veto_electrons);

  // get VETO Muon collection
  edm::Handle<edm::View<pat::Muon> > veto_muons;
  iEvent.getByLabel(muonVetoSrc_,veto_muons);


  // get mvaMET collection
  edm::Handle <std::vector<reco::PFMET> >  mvamets;
  iEvent.getByLabel(mvaMETSrc_,mvamets);

// get puppiMET collection
  edm::Handle <std::vector<pat::MET> >  puppimets;
  iEvent.getByLabel(puppiMETSrc_,puppimets);


  // get pfMET collection
  edm::Handle <std::vector<pat::MET> >  pfmets;
  iEvent.getByLabel(pfMETSrc_,pfmets);

  auto_ptr<TupleCandidateEventCollection> TupleCandidateEvents (new TupleCandidateEventCollection);



  // get met sig matrix & sig for PF met


  edm::Handle<math::Error<2>::type> pfCovMatrix;
  iEvent.getByLabel(pfCovMatrix_,pfCovMatrix);


  double PFsig00 = (*pfCovMatrix)(0,0);
  double PFsig01 = (*pfCovMatrix)(0,1);
  double PFsig10 = (*pfCovMatrix)(1,0);
  double PFsig11 = (*pfCovMatrix)(1,1);


 


  // electron-electron 
  if (electrons.isValid() && second_electrons.isValid())
  {
    for (std::size_t i=0; i<electrons->size(); ++i)
    {
      for (std::size_t ii=0; ii<second_electrons->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(electrons->at(i),second_electrons->at(ii));
          if(mvamets.isValid()) CurrentCandidateEvent.set_mvaMET(mvamets->at(0));
          CurrentCandidateEvent.set_puppiMET(puppimets->at(0));
          CurrentCandidateEvent.set_pfMET(pfmets->at(0));
          CurrentCandidateEvent.set_pfMET_covMatrix(PFsig00, PFsig01, PFsig10, PFsig11);

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(electrons->at(i).pt(), electrons->at(i).eta(), electrons->at(i).phi(),electrons->at(i).mass());
          l2.SetPtEtaPhiM(second_electrons->at(ii).pt(), second_electrons->at(ii).eta(), second_electrons->at(ii).phi(),second_electrons->at(ii).mass());

          if(l1.DeltaR(l2)<pairDeltaRmin_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
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
          second_electrons->at(ii).p4().pt(),second_electrons->at(ii).p4().eta(),second_electrons->at(ii).p4().phi(),
          svFitStandalone::electronMass));


        std::vector<double> sv_mass;
        sv_mass.clear();         

        if(useMVAMET_ && mvamets.isValid())
          sv_mass = computeSVMassAndSVTransverseMass(mvamets->at(0),measuredTauLeptons);
        else if (!useMVAMET_)
          sv_mass = computeSVMassAndSVTransverseMass(pfmets->at(0),measuredTauLeptons,PFsig00,PFsig10,PFsig01,PFsig11);



        CurrentCandidateEvent.set_SVMass(sv_mass[0]); // the sv mass
        CurrentCandidateEvent.set_SVTransverseMass(sv_mass[1]); // the sv transverse mass

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
          if(mvamets.isValid())CurrentCandidateEvent.set_mvaMET(mvamets->at(0));
          CurrentCandidateEvent.set_puppiMET(puppimets->at(0));
          CurrentCandidateEvent.set_pfMET(pfmets->at(0));
          CurrentCandidateEvent.set_pfMET_covMatrix(PFsig00, PFsig01, PFsig10, PFsig11);

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(electrons->at(i).pt(), electrons->at(i).eta(), electrons->at(i).phi(),electrons->at(i).mass());
          l2.SetPtEtaPhiM(muons->at(ii).pt(), muons->at(ii).eta(), muons->at(ii).phi(),muons->at(ii).mass());

          if(l1.DeltaR(l2)<vetoDeltaRmin_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
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



        std::vector<double> sv_mass;
        sv_mass.clear();              

        if(useMVAMET_ && mvamets.isValid())
          sv_mass = computeSVMassAndSVTransverseMass(mvamets->at(0),measuredTauLeptons);
        else if (!useMVAMET_)
          sv_mass = computeSVMassAndSVTransverseMass(pfmets->at(0),measuredTauLeptons,PFsig00,PFsig10,PFsig01,PFsig11);



        CurrentCandidateEvent.set_SVMass(sv_mass[0]); // the sv mass
        CurrentCandidateEvent.set_SVTransverseMass(sv_mass[1]); // the sv transverse mass

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
          if(mvamets.isValid())CurrentCandidateEvent.set_mvaMET(mvamets->at(0));          
          CurrentCandidateEvent.set_puppiMET(puppimets->at(0));
          CurrentCandidateEvent.set_pfMET(pfmets->at(0));
          CurrentCandidateEvent.set_pfMET_covMatrix(PFsig00, PFsig01, PFsig10, PFsig11);         

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(electrons->at(i).pt(), electrons->at(i).eta(), electrons->at(i).phi(),electrons->at(i).mass());
          l2.SetPtEtaPhiM(taus->at(ii).pt(), taus->at(ii).eta(), taus->at(ii).phi(),taus->at(ii).mass());

          if(l1.DeltaR(l2)<vetoDeltaRmin_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
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


        std::vector<double> sv_mass;
        sv_mass.clear();         

        

        if(useMVAMET_ && mvamets.isValid())
          sv_mass = computeSVMassAndSVTransverseMass(mvamets->at(0),measuredTauLeptons);
        else if (!useMVAMET_)
          sv_mass = computeSVMassAndSVTransverseMass(pfmets->at(0),measuredTauLeptons,PFsig00,PFsig10,PFsig01,PFsig11);



        CurrentCandidateEvent.set_SVMass(sv_mass[0]); // the sv mass
        CurrentCandidateEvent.set_SVTransverseMass(sv_mass[1]); // the sv transverse mass
       
        /* TEMP START */ 

        // if(taus->at(ii).userFloat("TauEsVariant")==0.0)
        // {
        //         NtupleLepton ntupLep1;
        //         NtupleLepton ntupLep2;

        //         ntupLep1.fill(CurrentCandidateEvent.leg1());        
        //         ntupLep1.printLEP();


        //         ntupLep2.fill(CurrentCandidateEvent.leg2());        
        //         ntupLep2.printLEP();
        // } // only for tau es 0


        /* TEMP END */ 

          TupleCandidateEvents->push_back(CurrentCandidateEvent);
        
      }
    }
  }  

  // muon-muon
  if (muons.isValid() && second_muons.isValid())
  {
    for (std::size_t i=0; i<muons->size(); ++i)
    {
      for (std::size_t ii=0; ii<second_muons->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(muons->at(i),second_muons->at(ii));
          if(mvamets.isValid())CurrentCandidateEvent.set_mvaMET(mvamets->at(0));  
          CurrentCandidateEvent.set_puppiMET(puppimets->at(0));
          CurrentCandidateEvent.set_pfMET(pfmets->at(0));
          CurrentCandidateEvent.set_pfMET_covMatrix(PFsig00, PFsig01, PFsig10, PFsig11);

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(muons->at(i).pt(), muons->at(i).eta(), muons->at(i).phi(),muons->at(i).mass());
          l2.SetPtEtaPhiM(second_muons->at(ii).pt(), second_muons->at(ii).eta(), second_muons->at(ii).phi(),second_muons->at(ii).mass());

          if(l1.DeltaR(l2)<vetoDeltaRmin_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
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
          second_muons->at(ii).p4().pt(),second_muons->at(ii).p4().eta(),second_muons->at(ii).p4().phi(),
          svFitStandalone::muonMass));


        std::vector<double> sv_mass;
        sv_mass.clear();

        if(useMVAMET_ && mvamets.isValid())
          sv_mass = computeSVMassAndSVTransverseMass(mvamets->at(0),measuredTauLeptons);
        else if (!useMVAMET_)
          sv_mass = computeSVMassAndSVTransverseMass(pfmets->at(0),measuredTauLeptons,PFsig00,PFsig10,PFsig01,PFsig11);



        CurrentCandidateEvent.set_SVMass(sv_mass[0]); // the sv mass
        CurrentCandidateEvent.set_SVTransverseMass(sv_mass[1]); // the sv transverse mass
        
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
          if(mvamets.isValid())CurrentCandidateEvent.set_mvaMET(mvamets->at(0));    
          CurrentCandidateEvent.set_puppiMET(puppimets->at(0));
          CurrentCandidateEvent.set_pfMET(pfmets->at(0));
          CurrentCandidateEvent.set_pfMET_covMatrix(PFsig00, PFsig01, PFsig10, PFsig11);

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(muons->at(i).pt(), muons->at(i).eta(), muons->at(i).phi(),muons->at(i).mass());
          l2.SetPtEtaPhiM(taus->at(ii).pt(), taus->at(ii).eta(), taus->at(ii).phi(),taus->at(ii).mass());
        
          if(l1.DeltaR(l2)<vetoDeltaRmin_) continue;


          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
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







        std::vector<double> sv_mass;
        sv_mass.clear(); 

        if(useMVAMET_ && mvamets.isValid())
          sv_mass = computeSVMassAndSVTransverseMass(mvamets->at(0),measuredTauLeptons);
        else if (!useMVAMET_)
          sv_mass = computeSVMassAndSVTransverseMass(pfmets->at(0),measuredTauLeptons,PFsig00,PFsig10,PFsig01,PFsig11);



        CurrentCandidateEvent.set_SVMass(sv_mass[0]); // the sv mass
        CurrentCandidateEvent.set_SVTransverseMass(sv_mass[1]); // the sv transverse mass

        /* TEMP START */ 


      //   if(taus->at(ii).userFloat("TauEsVariant")==0.0)
      //   {

      //   NtupleLepton ntupLep1;
      //   NtupleLepton ntupLep2;

      //   ntupLep1.fill(CurrentCandidateEvent.leg1());  
      //   ntupLep1.printLEP();


      //   ntupLep2.fill(CurrentCandidateEvent.leg2());        
      //   ntupLep2.printLEP();

      // }

        /* TEMP END */ 


          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      }
    }


  }

  // tau-tau
  if (taus.isValid() && second_taus.isValid())
  {

    for (std::size_t i=0; i<taus->size(); ++i)
    {
      for (std::size_t ii=0; ii<second_taus->size(); ++ii)
      {

          TupleCandidateEvent CurrentCandidateEvent;
          CurrentCandidateEvent.set_pair(taus->at(i),second_taus->at(ii));
          if(mvamets.isValid())CurrentCandidateEvent.set_mvaMET(mvamets->at(0));     
          CurrentCandidateEvent.set_puppiMET(puppimets->at(0));
          CurrentCandidateEvent.set_pfMET(pfmets->at(0));
          CurrentCandidateEvent.set_pfMET_covMatrix(PFsig00, PFsig01, PFsig10, PFsig11);

          // 4-vectors for veto candidate DR checks
          TLorentzVector l1,l2,vetoCand;
          l1.SetPtEtaPhiM(taus->at(i).pt(), taus->at(i).eta(), taus->at(i).phi(),taus->at(i).mass());
          l2.SetPtEtaPhiM(second_taus->at(ii).pt(), second_taus->at(ii).eta(), second_taus->at(ii).phi(),second_taus->at(ii).mass());

          if(l1.DeltaR(l2)<vetoDeltaRmin_) continue;

          ///////////////////
          /////// VETO ELECTRONS /////////////////////////////////////////////
          for (std::size_t ve=0; ve<veto_electrons->size(); ++ve)
          {          
            vetoCand.SetPtEtaPhiM(veto_electrons->at(ve).pt(), veto_electrons->at(ve).eta(), veto_electrons->at(ve).phi(),veto_electrons->at(ve).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
            {
              CurrentCandidateEvent.set_vetoElectron(veto_electrons->at(ve));
            }
          }
          /////// VETO MUONS /////////////////////////////////////////////

          for (std::size_t vm=0; vm<veto_muons->size(); ++vm)
          {          
             vetoCand.SetPtEtaPhiM(veto_muons->at(vm).pt(), veto_muons->at(vm).eta(), veto_muons->at(vm).phi(),veto_muons->at(vm).mass());
            if(vetoCand.DeltaR(l1) > vetoDeltaRmin_ && vetoCand.DeltaR(l2) > vetoDeltaRmin_ )
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
          second_taus->at(ii).p4().pt(),second_taus->at(ii).p4().eta(),second_taus->at(ii).p4().phi(),
          second_taus->at(ii).p4().mass()));





        std::vector<double> sv_mass;
        sv_mass.clear();         
        
        if(useMVAMET_ && mvamets.isValid())
          sv_mass = computeSVMassAndSVTransverseMass(mvamets->at(0),measuredTauLeptons);
        else if (!useMVAMET_)
          sv_mass = computeSVMassAndSVTransverseMass(pfmets->at(0),measuredTauLeptons,PFsig00,PFsig10,PFsig01,PFsig11);

        CurrentCandidateEvent.set_SVMass(sv_mass[0]); // the sv mass
        CurrentCandidateEvent.set_SVTransverseMass(sv_mass[1]); // the sv transverse mass

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

std::vector<double> TupleCandidateEventProducer::computeSVMassAndSVTransverseMass(reco::PFMET MET,std::vector<svFitStandalone::MeasuredTauLepton> MTL)
{

  std::vector<double> zero_return;
  zero_return.clear();
  zero_return.push_back(0.0);
  zero_return.push_back(0.0);

  if(!doSVMass_) return zero_return;




  // PFMET significance matrix
  TMatrixD covMET(2, 2); 
  covMET[0][0] = MET.getSignificanceMatrix()[0][0];
  covMET[1][0] = MET.getSignificanceMatrix()[1][0];
  covMET[0][1] = MET.getSignificanceMatrix()[0][1];
  covMET[1][1] = MET.getSignificanceMatrix()[1][1];
  if (svMassVerbose_)  covMET.Print();

 std::cout<<MTL.size()<<" size *** \n";
 SVfitStandaloneAlgorithm svFitAlgorithm(MTL, MET.px(),MET.py(), covMET, svMassVerbose_);

 if(logMterm_>0)  svFitAlgorithm.addLogM(true, logMterm_);
 else svFitAlgorithm.addLogM(false, 0.);


 //svFitAlgorithm.integrateVEGAS();
 //double retSVmass = svFitAlgorithm.getMass();


  //edm::FileInPath inputFileName_visPtResolution("TauAnalysis/SVfitStandalone/data/svFitVisMassAndPtResolutionPDF.root");
  //TH1::AddDirectory(false);  
  // TFile* inputFile_visPtResolution = new TFile(inputFileName_visPtResolution.fullPath().data());
  // svFitAlgorithm.shiftVisPt(true, inputFile_visPtResolution);
  svFitAlgorithm.integrateMarkovChain();
  std::vector<double> retSVmass;
  retSVmass.clear();

  retSVmass.push_back(svFitAlgorithm.getMass());
  retSVmass.push_back(svFitAlgorithm.transverseMass());

  std::cout<<" mass, transverseMass "<<retSVmass[0]<<" "<<retSVmass[1]<<"\n";

 return retSVmass;


}



std::vector<double> TupleCandidateEventProducer::computeSVMassAndSVTransverseMass(pat::MET MET,std::vector<svFitStandalone::MeasuredTauLepton> MTL,
 double sig00, double sig10, double sig01, double sig11)
{

/* this is a bit complicated since MET SIG is not in PHYS14 (and Spring15?) samples for slimmedMET */
  std::vector<double> zero_return;
  zero_return.clear();
  zero_return.push_back(0.0);
  zero_return.push_back(0.0);

  if(!doSVMass_) return zero_return;



  // PFMET significance matrix
  TMatrixD covMET(2, 2); 
  covMET[0][0] = sig00;
  covMET[1][0] = sig10;
  covMET[0][1] = sig01;
  covMET[1][1] = sig11;
  if (svMassVerbose_)  covMET.Print();

 SVfitStandaloneAlgorithm svFitAlgorithm(MTL, MET.px(),MET.py(), covMET, svMassVerbose_);

 // std::cout<<" cov 00, 10, 01, 11 "<<sig00<<" , "<<sig10<<" , "<<sig01<<" , "<<sig11<<"\n";
 // std::cout<<" met x, met y "<<MET.px()<<" "<<MET.py()<<"\n";
 // std::cout<<" leg 1 pt,eta,phi,M "<<MTL[0].pt()<<" "<<MTL[0].eta()<<" "<<MTL[0].phi()<<" "<<MTL[0].mass()<<"\n";
 // std::cout<<" leg 2 pt,eta,phi,M "<<MTL[1].pt()<<" "<<MTL[1].eta()<<" "<<MTL[1].phi()<<" "<<MTL[1].mass()<<"\n";


 if(logMterm_>0)  svFitAlgorithm.addLogM(true, logMterm_);
 else svFitAlgorithm.addLogM(false, 0.);


 //svFitAlgorithm.integrateVEGAS();
 //double retSVmass = svFitAlgorithm.getMass();


//   edm::FileInPath inputFileName_visPtResolution("TauAnalysis/SVfitStandalone/data/svFitVisMassAndPtResolutionPDF.root");
//   TH1::AddDirectory(false);  
//   TFile* inputFile_visPtResolution = new TFile(inputFileName_visPtResolution.fullPath().data());
//   svFitAlgorithm.shiftVisPt(true, inputFile_visPtResolution);

// std::cout<<" cov 00, 10, 01, 11 "<<sig00<<" , "<<sig10<<" , "<<sig01<<" , "<<sig11<<"\n";
//  std::cout<<" met x, met y "<<MET.px()<<" "<<MET.py()<<"\n";
//  std::cout<<" leg 1 pt,eta,phi,M "<<MTL[0].pt()<<" "<<MTL[0].eta()<<" "<<MTL[0].phi()<<" "<<MTL[0].mass()<<"\n";
//  std::cout<<" leg 2 pt,eta,phi,M "<<MTL[1].pt()<<" "<<MTL[1].eta()<<" "<<MTL[1].phi()<<" "<<MTL[1].mass()<<"\n";



  svFitAlgorithm.integrateMarkovChain();
  
  std::vector<double> retSVmass;
  retSVmass.clear();

  retSVmass.push_back(svFitAlgorithm.getMass());
  retSVmass.push_back(svFitAlgorithm.transverseMass());

  std::cout<<" mass, transverseMass "<<retSVmass[0]<<" "<<retSVmass[1]<<"\n";

 return retSVmass;


}



//define this as a plug-in
DEFINE_FWK_MODULE(TupleCandidateEventProducer);
