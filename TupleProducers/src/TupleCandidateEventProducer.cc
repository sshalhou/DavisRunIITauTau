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
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
 

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
  std::vector<double> computeSVMassAndSVTransverseMass(pat::MET,std::vector<svFitStandalone::MeasuredTauLepton>);
  std::vector<double> computeSVMassAndSVTransverseMass(pat::MET,std::vector<svFitStandalone::MeasuredTauLepton>,double,double,double,double);


  // ----------member data ---------------------------


  edm::InputTag puppiMETSrc_;
  edm::EDGetTokenT<edm::View< pat::MET > > puppiMETToken_;

  edm::InputTag pfMETSrc_;
  edm::EDGetTokenT<edm::View< pat::MET > > pfMETToken_;

  edm::InputTag mvaMETSrc_;
  edm::EDGetTokenT<edm::View< pat::MET > > mvaMETToken_;

  edm::InputTag electronVetoSrc_;
  edm::EDGetTokenT<edm::View< pat::Electron > > electronVetoToken_;

  edm::InputTag muonVetoSrc_;
  edm::EDGetTokenT<edm::View< pat::Muon > > muonVetoToken_;

  double pairDeltaRmin_;
  double vetoDeltaRmin_;

  string NAME_;
  bool doSVMass_;
  bool useMVAMET_;
  double logMterm_;
  int svMassVerbose_;


  edm::InputTag EffElectronSrc_;
  edm::EDGetTokenT<edm::View< pat::Electron > > EffElectronToken_;

  edm::InputTag EffMuonSrc_;
  edm::EDGetTokenT<edm::View< pat::Muon > > EffMuonToken_;

  edm::InputTag EffTauSrc_;
  edm::EDGetTokenT<edm::View< pat::Tau > > EffTauToken_;




  string tauIsolForOrderingPair_;
  bool BuildEfficiencyTree_;

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
EffElectronSrc_(iConfig.getParameter<edm::InputTag>("EffElectronSrc" )),
EffMuonSrc_(iConfig.getParameter<edm::InputTag>("EffMuonSrc" )),
EffTauSrc_(iConfig.getParameter<edm::InputTag>("EffTauSrc" )),
tauIsolForOrderingPair_(iConfig.getParameter<string>("tauIsolForOrderingPair" )),
BuildEfficiencyTree_(iConfig.getParameter<bool>("BuildEfficiencyTree" ))
{


  produces<vector<TupleCandidateEvent>>(NAME_).setBranchAlias(NAME_);

  mvaMETToken_ = consumes< edm::View<pat::MET> >(mvaMETSrc_);
  pfMETToken_ = consumes< edm::View<pat::MET> >(pfMETSrc_);
  puppiMETToken_ = consumes< edm::View<pat::MET> >(puppiMETSrc_);


  electronVetoToken_ = consumes< edm::View<pat::Electron> >(electronVetoSrc_);
  muonVetoToken_ = consumes< edm::View<pat::Muon> >(muonVetoSrc_);


  EffElectronToken_ = consumes< edm::View<pat::Electron> >(EffElectronSrc_);
  EffMuonToken_ = consumes< edm::View<pat::Muon> >(EffMuonSrc_);
  EffTauToken_ = consumes< edm::View<pat::Tau> >(EffTauSrc_);



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

  auto_ptr<TupleCandidateEventCollection> TupleCandidateEvents (new TupleCandidateEventCollection);


  // get mvaMET collection

  edm::Handle<edm::View<pat::MET> > mvamets;
  iEvent.getByToken(mvaMETToken_,mvamets);

  // get puppiMET collection
  edm::Handle <edm::View<pat::MET> >  puppimets;
  iEvent.getByToken(puppiMETToken_,puppimets);

  // get pfMET collection
  edm::Handle <edm::View<pat::MET> >  pfmets;
  iEvent.getByToken(pfMETToken_,pfmets);

  // get VETO Electron collection
  edm::Handle<edm::View<pat::Electron> > veto_electrons;
  iEvent.getByToken(electronVetoToken_,veto_electrons);

  // get VETO Muon collection
  edm::Handle<edm::View<pat::Muon> > veto_muons;
  iEvent.getByToken(muonVetoToken_,veto_muons);

  // get EFF Electron collection
  edm::Handle<edm::View<pat::Electron> > eff_electrons;
  iEvent.getByToken(EffElectronToken_,eff_electrons);

  // get EFF Muon collection
  edm::Handle<edm::View<pat::Muon> > eff_muons;
  iEvent.getByToken(EffMuonToken_,eff_muons);

  // get EFF Tau collection
  edm::Handle<edm::View<pat::Tau> > eff_taus;
  iEvent.getByToken(EffTauToken_,eff_taus);

  //////////////////////////////////////////////////
  /* fill eff lepton vector */
  //////////////////////////////////////////////////      

  TupleCandidateEvent EffCandidateEvent;

  // EFF ELECTRONS
  for (std::size_t e=0; e<eff_electrons->size(); ++e)
  {          
      EffCandidateEvent.add_EfficiencyLepton(eff_electrons->at(e));
  }
  // EFF MUONS
  for (std::size_t m=0; m<eff_muons->size(); ++m)
  {          
      EffCandidateEvent.add_EfficiencyLepton(eff_muons->at(m));
  }
  // EFF TAUS
  for (std::size_t t=0; t<eff_taus->size(); ++t)
  {          
      EffCandidateEvent.add_EfficiencyLepton(eff_taus->at(t));
  }

  /* MET info */
  /*
  std::cout<<" WARNING FOR EFF TTREE USING pair corrected MET - will often be invalid I think \n";
  if(mvamets.isValid()) EffCandidateEvent.set_mvaMET(mvamets->at(0));
  */
  EffCandidateEvent.set_puppiMET(puppimets->at(0));
  EffCandidateEvent.set_pfMET(pfmets->at(0));
  
  /* left over from when PF MET did not have sig matrix */
  EffCandidateEvent.set_pfMET_covMatrix(pfmets->at(0).getSignificanceMatrix()[0][0], 
    pfmets->at(0).getSignificanceMatrix()[1][0], pfmets->at(0).getSignificanceMatrix()[0][1], 
    pfmets->at(0).getSignificanceMatrix()[1][1]);


  /* finally set the type to EffCand */

  EffCandidateEvent.set_CandidateEventType(TupleCandidateEventTypes::EffCand);


  TupleCandidateEvents->push_back(EffCandidateEvent);

  //////////////////////////////////////////////////


  //////////////////////////////////////////////////
  /* fill met-pair based vector */
  //////////////////////////////////////////////////     

  std::cout<<" met valid ? "<<mvamets.isValid()<<NAME_<<"\n";
  if(mvamets.isValid())
  {


    std::cout<<" have "<<mvamets->size()<<" mva met entries \n";

    for(std::size_t m = 0; m < mvamets->size(); ++m)
    {

      /* NOTE NEED AN ELSE CASE FOR only 1 or 0 leptos, for scale factors */
      if( mvamets->at(m).hasUserCand("lepton0") && mvamets->at(m).hasUserCand("lepton1") )
      {


        // have a pair associated to this mva met

        TupleCandidateEvent CurrentCandidateEvent;
        if(mvamets.isValid()) CurrentCandidateEvent.set_mvaMET(mvamets->at(m));
        CurrentCandidateEvent.set_puppiMET(puppimets->at(0));
        CurrentCandidateEvent.set_pfMET(pfmets->at(0));
        
        /* left over from when PF MET did not have sig matrix */
        CurrentCandidateEvent.set_pfMET_covMatrix(pfmets->at(0).getSignificanceMatrix()[0][0], 
          pfmets->at(0).getSignificanceMatrix()[1][0], pfmets->at(0).getSignificanceMatrix()[0][1], 
          pfmets->at(0).getSignificanceMatrix()[1][1]);

        // leg and veto lepton 4-vectors 

        TLorentzVector l1,l2,vetoCand;

        //////////////////////////////////////////////////////////

        /* Need to invert MU + E pair leg ordering */
        if(mvamets->at(m).userCand("lepton0").get()->isMuon() &&\
           mvamets->at(m).userCand("lepton1").get()->isElectron())
        {

          const pat::Electron* leg1 = dynamic_cast<const pat::Electron*>(mvamets->at(m).userCand("lepton1").get());
          CurrentCandidateEvent.set_leg1(*leg1);
          l1.SetPtEtaPhiM(leg1->pt(), leg1->eta(), leg1->phi(),leg1->mass());          

          const pat::Muon* leg2 = dynamic_cast<const pat::Muon*>(mvamets->at(m).userCand("lepton0").get());
          CurrentCandidateEvent.set_leg2(*leg2);
          l2.SetPtEtaPhiM(leg2->pt(), leg2->eta(), leg2->phi(),leg2->mass());

        }

        /* In the case of tau_h + tau_h leg1 has to be the lowest isolation tau */
        else if(abs(mvamets->at(m).userCand("lepton0").get()->pdgId())==15 &&\
                abs(mvamets->at(m).userCand("lepton1").get()->pdgId())==15)
        {

          /* try default ordering */

          const pat::Tau* legA = dynamic_cast<const pat::Tau*>(mvamets->at(m).userCand("lepton0").get());
          const pat::Tau* legB = dynamic_cast<const pat::Tau*>(mvamets->at(m).userCand("lepton1").get());
            
          if(legA->tauID(tauIsolForOrderingPair_) <=\
             legB->tauID(tauIsolForOrderingPair_))
          {

            CurrentCandidateEvent.set_leg1(*legA);
            l1.SetPtEtaPhiM(legA->pt(), legA->eta(), legA->phi(),legA->mass());
        
            CurrentCandidateEvent.set_leg2(*legB);
            l2.SetPtEtaPhiM(legB->pt(), legB->eta(), legB->phi(),legB->mass());

            std::cout<<"DEFAULT DOUBLE TAU PAIR @ mvaMET INDEX "<<m<<" pt1 = "<<l1.Pt()<<" pt2 = "<<l2.Pt()<<" ";
            std::cout<<" isol 1 "<<legA->tauID(tauIsolForOrderingPair_)<<" ";
            std::cout<<" isol 2 "<<legB->tauID(tauIsolForOrderingPair_)<<"\n";
            
          }


          else /* invert */
          {

            CurrentCandidateEvent.set_leg1(*legB);
            l1.SetPtEtaPhiM(legB->pt(), legB->eta(), legB->phi(),legB->mass());
        
            CurrentCandidateEvent.set_leg2(*legA);
            l2.SetPtEtaPhiM(legA->pt(), legA->eta(), legA->phi(),legA->mass());

            std::cout<<"INVERTED DOUBLE TAU PAIR @ mvaMET INDEX "<<m<<" pt1 = "<<l1.Pt()<<" pt2 = "<<l2.Pt()<<" ";
            std::cout<<" isol 1 "<<legB->tauID(tauIsolForOrderingPair_)<<" ";
            std::cout<<" isol 2 "<<legA->tauID(tauIsolForOrderingPair_)<<"\n";

          }
           


          std::cout<<" JUST CREATED A TAU TAU DR = "<<l1.DeltaR(l2)<<"\n";

        }

        else
        {
          /////////////////////////////
          // electrons

          if(mvamets->at(m).userCand("lepton0").get()->isElectron())  
            {
              const pat::Electron* leg1 = dynamic_cast<const pat::Electron*>(mvamets->at(m).userCand("lepton0").get());
              CurrentCandidateEvent.set_leg1(*leg1);
              l1.SetPtEtaPhiM(leg1->pt(), leg1->eta(), leg1->phi(),leg1->mass());
            }
          if(mvamets->at(m).userCand("lepton1").get()->isElectron())  
            {
              const pat::Electron* leg2 = dynamic_cast<const pat::Electron*>(mvamets->at(m).userCand("lepton1").get());
              CurrentCandidateEvent.set_leg2(*leg2);
              l2.SetPtEtaPhiM(leg2->pt(), leg2->eta(), leg2->phi(),leg2->mass());
            }

          /////////////////////////////
          // muons

          if(mvamets->at(m).userCand("lepton0").get()->isMuon())  
            {
              const pat::Muon* leg1 = dynamic_cast<const pat::Muon*>(mvamets->at(m).userCand("lepton0").get());
              CurrentCandidateEvent.set_leg1(*leg1);
              l1.SetPtEtaPhiM(leg1->pt(), leg1->eta(), leg1->phi(),leg1->mass());
            }
          if(mvamets->at(m).userCand("lepton1").get()->isMuon())  
            {
              const pat::Muon* leg2 = dynamic_cast<const pat::Muon*>(mvamets->at(m).userCand("lepton1").get());
              CurrentCandidateEvent.set_leg2(*leg2);
              l2.SetPtEtaPhiM(leg2->pt(), leg2->eta(), leg2->phi(),leg2->mass());
            }

          /////////////////////////////
          // taus        

          if(abs(mvamets->at(m).userCand("lepton0").get()->pdgId())==15)  
            {
              const pat::Tau* leg1 = dynamic_cast<const pat::Tau*>(mvamets->at(m).userCand("lepton0").get());
              CurrentCandidateEvent.set_leg1(*leg1);
              l1.SetPtEtaPhiM(leg1->pt(), leg1->eta(), leg1->phi(),leg1->mass());
            }
          if(abs(mvamets->at(m).userCand("lepton1").get()->pdgId())==15)  
            {
              const pat::Tau* leg2 = dynamic_cast<const pat::Tau*>(mvamets->at(m).userCand("lepton1").get());
              CurrentCandidateEvent.set_leg2(*leg2);
              l2.SetPtEtaPhiM(leg2->pt(), leg2->eta(), leg2->phi(),leg2->mass());
            }


          //////////////////////////////////////////////////////////
        
        }




          // set the CandidateEventType

          CurrentCandidateEvent.set_CandidateEventType();

          std::cout<<" PT CHECK "<<l1.Pt()<<" "<<l2.Pt()<<" candidate type "<<CurrentCandidateEvent.CandidateEventType()<<"\n";
          assert( CurrentCandidateEvent.CandidateEventType()>=1 && CurrentCandidateEvent.CandidateEventType()<=10 );

          if(l1.DeltaR(l2)<pairDeltaRmin_) continue;

          std::cout<<" AFTER DR CUT  of "<<pairDeltaRmin_<<" get DR = "<<l1.DeltaR(l2)<<" pts are "<<l1.Pt()<<" "<<l2.Pt()<<"\n";

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

          std::cout<<" ---------->\n";
          std::cout<<" ---------->\n";
          std::cout<<" ---------->\n";
          std::cout<<" ----------> pt1, pt2 "<<l1.Pt()<<" "<<l2.Pt()<<" candidate type = "<<CurrentCandidateEvent.CandidateEventType()<<"\n";

          // SVMASS Convention *** 
          // In the etau and mutau channel, please add the electron or muon to the
          // measuredTauLeptons vector first and the hadronic tau second
          // In the emu channel, please add the electron before the muon
          // In the ee, mumu and tautau channel, please add the lepton of higher Pt first 

          std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
          measuredTauLeptons.clear();





          ////////////////////////////////////////////////////////
          // ele + ele choose higher pt leg to push back 1st    //
          ////////////////////////////////////////////////////////

          if(CurrentCandidateEvent.CandidateEventType()==TupleCandidateEventTypes::EleEle)
          {
            if(l1.Pt() >= l2.Pt())
            {
              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToElecDecay,l1.Pt(),l1.Eta(),l1.Phi(),svFitStandalone::electronMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToElecDecay,l2.Pt(),l2.Eta(),l2.Phi(),svFitStandalone::electronMass));
            }
            else
            {
              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToElecDecay,l2.Pt(),l2.Eta(),l2.Phi(),svFitStandalone::electronMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToElecDecay,l1.Pt(),l1.Eta(),l1.Phi(),svFitStandalone::electronMass));
            }
          }


          ////////////////////////////////////////////////////////
          // mu + mu choose higher pt leg to push back 1st    //
          ////////////////////////////////////////////////////////

          if(CurrentCandidateEvent.CandidateEventType()==TupleCandidateEventTypes::MuonMuon)
          {
            if(l1.Pt() >= l2.Pt())
            {
              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToMuDecay,l1.Pt(),l1.Eta(),l1.Phi(),svFitStandalone::muonMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToMuDecay,l2.Pt(),l2.Eta(),l2.Phi(),svFitStandalone::muonMass));
            }
            else
            {
              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToMuDecay,l2.Pt(),l2.Eta(),l2.Phi(),svFitStandalone::muonMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToMuDecay,l1.Pt(),l1.Eta(),l1.Phi(),svFitStandalone::muonMass));
            }
          }

          ////////////////////////////////////////////////////////
          // tau + tau choose higher pt leg to push back 1st    //
          ////////////////////////////////////////////////////////

          if(CurrentCandidateEvent.CandidateEventType()==TupleCandidateEventTypes::TauTau)
          {

            std::cout<<" TEST PRINT TAU 1 DECAY MODE : "<<CurrentCandidateEvent.leg1().Tau()[0].decayMode()<<"\n";
            std::cout<<" TEST PRINT TAU 2 DECAY MODE : "<<CurrentCandidateEvent.leg2().Tau()[0].decayMode()<<"\n";

            if(l1.Pt() >= l2.Pt())
            {
              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToHadDecay,l1.Pt(),l1.Eta(),l1.Phi(),l1.M(), CurrentCandidateEvent.leg1().Tau()[0].decayMode()));


              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToHadDecay,l2.Pt(),l2.Eta(),l2.Phi(),l2.M(), CurrentCandidateEvent.leg2().Tau()[0].decayMode()));
            }
            else
            {
              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToHadDecay,l2.Pt(),l2.Eta(),l2.Phi(),l2.M(), CurrentCandidateEvent.leg2().Tau()[0].decayMode()));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToHadDecay,l1.Pt(),l1.Eta(),l1.Phi(),l1.M(), CurrentCandidateEvent.leg1().Tau()[0].decayMode()));

           
            }
          }


          ////////////////////////////////////////////////////////
          // ele + mu choose ele leg to push back 1st    //
          ////////////////////////////////////////////////////////

          if(CurrentCandidateEvent.CandidateEventType()==TupleCandidateEventTypes::EleMuon)
          {

            if(CurrentCandidateEvent.leg1().leptonType()==TupleLeptonTypes::anElectron)
            {
              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToElecDecay,l1.Pt(),l1.Eta(),l1.Phi(),svFitStandalone::electronMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToMuDecay,l2.Pt(),l2.Eta(),l2.Phi(),svFitStandalone::muonMass));
            }
            else
            {
             measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToElecDecay,l2.Pt(),l2.Eta(),l2.Phi(),svFitStandalone::electronMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToMuDecay,l1.Pt(),l1.Eta(),l1.Phi(),svFitStandalone::muonMass));            
            }
          }


          ////////////////////////////////////////////////////////
          // ele + tau choose ele leg to push back 1st    //
          ////////////////////////////////////////////////////////

          if(CurrentCandidateEvent.CandidateEventType()==TupleCandidateEventTypes::EleTau)
          {

            if(CurrentCandidateEvent.leg1().leptonType()==TupleLeptonTypes::anElectron)
            {
              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToElecDecay,l1.Pt(),l1.Eta(),l1.Phi(),svFitStandalone::electronMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToHadDecay,l2.Pt(),l2.Eta(),l2.Phi(),l2.M(), CurrentCandidateEvent.leg2().Tau()[0].decayMode()));
            }
            else
            {
             measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToElecDecay,l2.Pt(),l2.Eta(),l2.Phi(),svFitStandalone::electronMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToHadDecay,l1.Pt(),l1.Eta(),l1.Phi(),l1.M(), CurrentCandidateEvent.leg1().Tau()[0].decayMode()));            
            }
          }


          ////////////////////////////////////////////////////////
          // mu + tau choose mu leg to push back 1st    //
          ////////////////////////////////////////////////////////

          if(CurrentCandidateEvent.CandidateEventType()==TupleCandidateEventTypes::MuonTau)
          {

            if(CurrentCandidateEvent.leg1().leptonType()==TupleLeptonTypes::aMuon)
            {
              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToMuDecay,l1.Pt(),l1.Eta(),l1.Phi(),svFitStandalone::muonMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToHadDecay,l2.Pt(),l2.Eta(),l2.Phi(),l2.M(), CurrentCandidateEvent.leg2().Tau()[0].decayMode()));
            }
            else
            {
             measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToMuDecay,l2.Pt(),l2.Eta(),l2.Phi(),svFitStandalone::muonMass));

              measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(
                svFitStandalone::kTauToHadDecay,l1.Pt(),l1.Eta(),l1.Phi(),l1.M(), CurrentCandidateEvent.leg1().Tau()[0].decayMode()));            
            }
          }

          std::vector<double> sv_mass;
          sv_mass.clear();         
          
          // need to make sure any hadronically decaying taus pass the new
          // decay mode finding otherwise svFit may crash or give random results

          bool goodTauDecays = 1;


          if(CurrentCandidateEvent.leg1().leptonType()==TupleLeptonTypes::aTau)
          {
            if( CurrentCandidateEvent.leg1().Tau()[0].tauID("decayModeFindingNewDMs") < 0.5 )  goodTauDecays = 0;
          }

          if(CurrentCandidateEvent.leg2().leptonType()==TupleLeptonTypes::aTau)
          {
            if( CurrentCandidateEvent.leg2().Tau()[0].tauID("decayModeFindingNewDMs") < 0.5 )  goodTauDecays = 0;
          }            

          std::cout<<" CHECKING GOOD TAU DECAYS AT NTUPLE LEVEL AND GET :  "<<goodTauDecays<<"\n";

          if(goodTauDecays) /* only call if no hadronic taus, or if hadronic taus have good decay */
          {  
            if(useMVAMET_ && mvamets.isValid())
              sv_mass = computeSVMassAndSVTransverseMass(mvamets->at(m),measuredTauLeptons);
            else if (!useMVAMET_ ) 
              sv_mass = computeSVMassAndSVTransverseMass(pfmets->at(0),measuredTauLeptons,pfmets->at(0).getSignificanceMatrix()[0][0], 
              pfmets->at(0).getSignificanceMatrix()[1][0], pfmets->at(0).getSignificanceMatrix()[0][1], 
              pfmets->at(0).getSignificanceMatrix()[1][1]);
          }
          else {sv_mass.push_back(0); sv_mass.push_back(0);}            

          CurrentCandidateEvent.set_SVMass(sv_mass[0]); // the sv mass
          CurrentCandidateEvent.set_SVTransverseMass(sv_mass[1]); // the sv transverse mass

          std::cout<<" PUSHING BACK TYPE "<<CurrentCandidateEvent.CandidateEventType()<<"\n";
          
          std::cout<<" TLOR DR = "<<l1.DeltaR(l2)<<"\n";
          
          TupleCandidateEvents->push_back(CurrentCandidateEvent);

      } // correctly formed mva met + leg1 + leg2
      else 
      {
        std::cout<<" a bad mva met \n";
      }


    } // mva met loop   
  }



std::cout<<" EVENT PAIR COUNT "<<TupleCandidateEvents->size()-1<<"\n";

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

std::vector<double> TupleCandidateEventProducer::computeSVMassAndSVTransverseMass(pat::MET MET,std::vector<svFitStandalone::MeasuredTauLepton> MTL)
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


  //std::cout<<" shiftVisPt turned off \n";
  edm::FileInPath inputFileName_visPtResolution("TauAnalysis/SVfitStandalone/data/svFitVisMassAndPtResolutionPDF.root");
  TH1::AddDirectory(false);  
  TFile* inputFile_visPtResolution = new TFile(inputFileName_visPtResolution.fullPath().data());
  svFitAlgorithm.shiftVisPt(true, inputFile_visPtResolution);
  svFitAlgorithm.integrateMarkovChain();
  std::vector<double> retSVmass;
  retSVmass.clear();

  retSVmass.push_back(svFitAlgorithm.getMass());
  retSVmass.push_back(svFitAlgorithm.transverseMass());

  std::cout<<" TESTINGXX in NTuple (mass, metx, mety) "<<retSVmass[0]<<" "<<MET.px()<<" "<<MET.py()<<"\n";

  std::cout<<" mass, transverseMass "<<retSVmass[0]<<" "<<retSVmass[1]<<"\n";

  inputFile_visPtResolution->Close();
  delete inputFile_visPtResolution;
  //        std::cout<<" **** TURN ON delete inputFile_visPtResolution \n";

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


  edm::FileInPath inputFileName_visPtResolution("TauAnalysis/SVfitStandalone/data/svFitVisMassAndPtResolutionPDF.root");
  TH1::AddDirectory(false);  
  TFile* inputFile_visPtResolution = new TFile(inputFileName_visPtResolution.fullPath().data());
  svFitAlgorithm.shiftVisPt(true, inputFile_visPtResolution);

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

  inputFile_visPtResolution->Close();
  delete inputFile_visPtResolution;
  return retSVmass;


}



//define this as a plug-in
DEFINE_FWK_MODULE(TupleCandidateEventProducer);
