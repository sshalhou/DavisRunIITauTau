// -*- C++ -*-
//
// Package:    FlatTupleGenerator
// Class:      FlatTupleGenerator
//
/**\class FlatTupleGenerator FlatTupleGenerator.cc DavisRunIITauTau/FlatTupleGenerator/src/FlatTupleGenerator.cc

Description: [EDAnalyzer that creates FlatTuples for DavisRunIITauTau analysis using Ntuple as input]


Implementation:

*/
//
// Original Author:  shalhout shalhout
//         Created:  Tue Jun  4 04:25:53 CDT 2015
// $Id$
//
//



//  include files
#include <memory>
#include <string>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "Math/GenVector/VectorUtil.h"
#include <math.h>

// FWCore include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


// Custom object include files


#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleGenParticle.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DavisRunIITauTau/FlatTupleGenerator/interface/PairRankHelper.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/FlatTupleGenerator/interface/LeptonFlatTupleCutHelper.h"


using namespace edm;
using namespace std;
typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<edm::InputTag> vInputTag;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;



//////////////////////////////////////////////////
// class declaration
//////////////////////////////////////////////////

class FlatTupleGenerator : public edm::EDAnalyzer
{
public:
  explicit FlatTupleGenerator(const edm::ParameterSet&);
  ~FlatTupleGenerator();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void reInit();

  // ----------member data ---------------------------

  /* MASTER VALUE FOR MAX std::pair flattening */

  static const int MAX = 10;

  /* the input collection sources */

  edm::InputTag pairSrc_;
  edm::InputTag indepSrc_;
  std::string NAME_;  // use TauESNom, TauESUp, TauESDown, etc.
  edm::ParameterSet TreeCutSrc_;
  edm::ParameterSet eCutSrc_;
  edm::ParameterSet muCutSrc_;
  edm::ParameterSet tauCutSrc_;


  /* the cut parameters to be read from TreeCutSrc_ */

  std::vector<std::string> tauIDsToKeep;
  bool keepOS;
  bool keepSS;
  std::vector<double> MtCut;
  bool keepTauEsNominal;
  bool keepTauEsUp; 
  bool keepTauEsDown; 

  /* cut helper */
  LeptonFlatTupleCutHelper cutHelper;


  /* the TTree */
 
  	TTree * FlatTuple;



  /* the leaves : Idea here is to be as flat as possible - stick to simple objects */

   unsigned int  run ;
   unsigned int  luminosityBlock ;
   unsigned int  event ;
   bool  isRealData ;
   std::string treeInfoString; /* this will be filled as NAME_, should be something like TauEsNominal etc. */
   double VISMass; 

   /* leg 1 tau IDs */
   float l1_tauIDs[MAX];
  
   /* leg 2 tau IDs */
   float l2_tauIDs[MAX];



};

////////////////////////////////////////////
//	--- class constructor
////////////////////////////////////////////


FlatTupleGenerator::FlatTupleGenerator(const edm::ParameterSet& iConfig):
pairSrc_(iConfig.getParameter<edm::InputTag>("pairSrc" )),
indepSrc_(iConfig.getParameter<edm::InputTag>("indepSrc" )),
NAME_(iConfig.getParameter<string>("NAME" )),
TreeCutSrc_(iConfig.getParameter<edm::ParameterSet>("TreeCutSrc")),
eCutSrc_(iConfig.getParameter<edm::ParameterSet>("eCutSrc")),
muCutSrc_(iConfig.getParameter<edm::ParameterSet>("muCutSrc")),
tauCutSrc_(iConfig.getParameter<edm::ParameterSet>("tauCutSrc"))
{

  /* init the cut helper */

  cutHelper.setEMuTauCutSets(eCutSrc_,muCutSrc_,tauCutSrc_);

  /* read in the TreeCutSrc varaibles */

  tauIDsToKeep = TreeCutSrc_.getParameter<std::vector<std::string> >("tauIDsToKeep"); 
  assert(MAX>=tauIDsToKeep.size());

  MtCut = TreeCutSrc_.getParameter<std::vector<double> >("Mt"); 
  assert(MtCut.size()==2);
  keepOS = TreeCutSrc_.getParameter<bool>("keepOS");
  keepSS = TreeCutSrc_.getParameter<bool>("keepSS");
  keepTauEsNominal = TreeCutSrc_.getParameter<bool>("keepTauEsNominal");
  keepTauEsUp = TreeCutSrc_.getParameter<bool>("keepTauEsUp");
  keepTauEsDown = TreeCutSrc_.getParameter<bool>("keepTauEsDown");

  /* create TTree */
   
	edm::Service<TFileService> fs;
	FlatTuple = fs->make<TTree>("FlatTuple", "FlatTuple");

  //////////////
  // init values

	  reInit();	


  /* the branches */

  FlatTuple->Branch("run", &run);
  FlatTuple->Branch("luminosityBlock", &luminosityBlock);
  FlatTuple->Branch("event", &event);
  FlatTuple->Branch("isRealData", &isRealData);
  FlatTuple->Branch("treeInfoString", &treeInfoString);
  FlatTuple->Branch("VISMass", &VISMass);

  for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
  {

  FlatTuple->Branch(("l1_"+tauIDsToKeep.at(x)).c_str(), &l1_tauIDs[x]);
  FlatTuple->Branch(("l2_"+tauIDsToKeep.at(x)).c_str(), &l2_tauIDs[x]);
  }


}


//////////////////////////////////////////////////
// class destructor 
//////////////////////////////////////////////////

FlatTupleGenerator::~FlatTupleGenerator(){}


//////////////////////////////////////////////////
// ------------ method called for each event  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{




  //////////////
  // init values

  reInit();


  ///////////////
  // get inputs 

  edm::Handle< NtupleEventCollection > pairs;
  iEvent.getByLabel(pairSrc_, pairs);

  edm::Handle< NtuplePairIndependentInfoCollection > pairIndepInfos;
  iEvent.getByLabel(indepSrc_, pairIndepInfos);






  ///////////////////////////////////////////
  // for each event, store a vector of NtupleEvent (i.e. pair)
  // objects that pass the specified selection /* coming soon, for now keep all */

  std::vector<NtupleEvent> retainedPairs;
  retainedPairs.clear();

  /////////////////////////////////////
  // now loop through the pairs in the current event
  // and figure out which ones to retain 

  for(std::size_t p = 0; p<pairs->size(); ++p )
  {
    NtupleEvent currentPair =   ((*pairs)[p]);

    bool keepSignPair = ((keepOS && currentPair.isOsPair()==1) || (keepSS && currentPair.isOsPair()!=1));
    
    bool keepTauEsVariant = (
      
      (keepTauEsNominal && currentPair.TauEsNumberSigmasShifted()==0.0) ||
      (keepTauEsNominal && isnan(currentPair.TauEsNumberSigmasShifted())) || /* for eMu, muMu, EleEle */
      (keepTauEsUp && currentPair.TauEsNumberSigmasShifted()==1.0) ||
      (keepTauEsDown && currentPair.TauEsNumberSigmasShifted()==-1.0) 

      );



    if(cutHelper.pairPasses(currentPair) && keepSignPair && keepTauEsVariant) retainedPairs.push_back(currentPair);

  }

  std::cout<<" retained pairs size = "<<retainedPairs.size()<<"\n";
  if(retainedPairs.size()==0) return;



  /////////////////////////
  // next figure out how to rank the pairs 



  for(std::size_t p = 0; p<retainedPairs.size(); ++p )
  {

      reInit();

      ////////////////
      // fill some easy stuff first :

      run = iEvent.id().run();
      luminosityBlock = iEvent.id().luminosityBlock();
      event = iEvent.id().event();
      isRealData = iEvent.isRealData();
      treeInfoString = NAME_;

      ///////
      // now stuff depending on the current pair


  		NtupleEvent currentPair =   retainedPairs[p];
      std::cout<<" got it \n";
      std::cout<<" vis mass "<<currentPair.VISMass()[0]<<"\n";
  		
      VISMass = currentPair.VISMass()[0];

      
      ////////////////
      // fill the tauIDs for tau legs


        for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
        {
          
          if(currentPair.leg1().leptonType() == TupleLeptonTypes::aTau)
          {
              l1_tauIDs[x]  =  currentPair.leg1().tauID(tauIDsToKeep[x]);
          }

          if(currentPair.leg2().leptonType() == TupleLeptonTypes::aTau)
          {
              l2_tauIDs[x]  =  currentPair.leg2().tauID(tauIDsToKeep[x]);
          }

        }


      FlatTuple->Fill();

  }




  // PairRankHelper rankHelper;
  // rankHelper.process_pairs(retainedPairs);




}


//////////////////////////////////////////////////
// ------------ method called to reset values and clear vectors each event ----
//////////////////////////////////////////////////

 void FlatTupleGenerator::reInit()
 {

   run = 0;
   luminosityBlock = 0;
   event = 0;
   isRealData  = 0;
   treeInfoString = "NULL";
   VISMass  = NAN;

  for(int r =0; r<MAX;++r)
  {  l1_tauIDs[r] = NAN;
     l2_tauIDs[r] = NAN;
  }
 }

//////////////////////////////////////////////////
// ------------ method called once each job just before starting event loop  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginJob() {}

//////////////////////////////////////////////////
// ------------ method called once each job just after ending the event loop  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endJob() {}

//////////////////////////////////////////////////
// ------------ method called when starting to processes a run  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a run  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when starting to processes a luminosity block  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a luminosity block  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
  }

//define this as a plug-in
DEFINE_FWK_MODULE(FlatTupleGenerator);
