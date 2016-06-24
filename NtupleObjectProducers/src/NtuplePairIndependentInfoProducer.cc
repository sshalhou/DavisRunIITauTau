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
#include "FWCore/Framework/interface/ESHandle.h"

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
#include "DavisRunIITauTau/External/interface/PUPFjetIdHelper.hh"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
/* for JEC Uncertainty */

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "PhysicsTools/PatAlgos/plugins/JetCorrFactorsProducer.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include <FWCore/Framework/interface/EventSetup.h>
#include <DataFormats/PatCandidates/interface/Jet.h>
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include <CondFormats/DataRecord/interface/JetResolutionRcd.h>
#include <CondFormats/DataRecord/interface/JetResolutionScaleFactorRcd.h>
#include "DataFormats/Math/interface/deltaR.h"

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
  edm::EDGetTokenT<edm::View< pat::PackedGenParticle > > packedGenToken_;

  edm::InputTag prunedGenSrc_;
  edm::EDGetTokenT<edm::View< reco::GenParticle > > prunedGenToken_;

  string NAME_;

  /* JER txt files */
  std::string rFile_string_; 
  std::string sfFile_string_;

  std::vector<int> genParticlesToKeep_;
  
  edm::InputTag slimmedJetSrc_;
  edm::EDGetTokenT<edm::View< pat::Jet > > slimmedJetToken_;

  edm::InputTag slimmedGenJetsSrc_;
  edm::EDGetTokenT<edm::View< reco::GenJet > > slimmedGenJetsToken_;



  string defaultBtagAlgorithmNameSrc_;

  edm::ParameterSet PUjetIDworkingPointSrc_;
  edm::ParameterSet PFjetIDworkingPointSrc_;
  edm::ParameterSet TightPFjetIDworkingPointSrc_;


  edm::InputTag vertexSrc_;
  edm::EDGetTokenT<edm::View< reco::Vertex > > vertexToken_;
  

  edm::InputTag pileupSrc_;
  edm::EDGetTokenT< std::vector<PileupSummaryInfo> > pileupToken_;
  


  edm::ParameterSet PUweightSettingsSrc_;
  
  edm::InputTag mcGenWeightSrc_;
  edm::EDGetTokenT< GenEventInfoProduct > mcGenWeightToken_;


  edm::InputTag LHEEventProductSrc_;
  edm::EDGetTokenT<LHEEventProduct> LHEEventProductToken_;
  


  edm::ParameterSet sampleInfoSrc_;


/* in 74X these needed to be rerun on miniAOD,
in 76X we can access directly from miniAOD */

  // edm::InputTag HBHENoiseFilterResultSrc_;  
  // edm::EDGetTokenT<bool> HBHENoiseFilterResultToken_;

  // edm::InputTag HBHEIsoNoiseFilterResultSrc_;  
  // edm::EDGetTokenT<bool> HBHEIsoNoiseFilterResultToken_;



  /* parameters for MET Filters; we code 2 versions of TriggerResults 
     to support both PAT and RECO processes (only used if isValid checks out) */  

  edm::EDGetTokenT<edm::TriggerResults> triggerResultsPatSrc_;
  edm::EDGetTokenT<edm::TriggerResults> triggerResultsRecoSrc_;

  edm::InputTag rhoSource_;
  edm::EDGetTokenT<double> rhoToken_;

  /* resolution tools */

  JME::JetResolution resolution_r;
  JME::JetResolutionScaleFactor resolution_sf;

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
rFile_string_(iConfig.getParameter<string>("JERresolutionFile" )), 
sfFile_string_(iConfig.getParameter<string>("JERscalefactorFile" )),
genParticlesToKeep_(iConfig.getParameter<std::vector<int>>("genParticlesToKeep" )),
slimmedJetSrc_(iConfig.getParameter<edm::InputTag>("slimmedJetSrc" )),
slimmedGenJetsSrc_(iConfig.getParameter<edm::InputTag>("slimmedGenJetsSrc" )),
defaultBtagAlgorithmNameSrc_(iConfig.getParameter<string>("defaultBtagAlgorithmNameSrc" )),
PUjetIDworkingPointSrc_(iConfig.getParameter<edm::ParameterSet>("PUjetIDworkingPointSrc")),
PFjetIDworkingPointSrc_(iConfig.getParameter<edm::ParameterSet>("PFjetIDworkingPointSrc")),
TightPFjetIDworkingPointSrc_(iConfig.getParameter<edm::ParameterSet>("TightPFjetIDworkingPointSrc")),
vertexSrc_(iConfig.getParameter<edm::InputTag>("vertexSrc" )),
pileupSrc_(iConfig.getParameter<edm::InputTag>("pileupSrc" )),
PUweightSettingsSrc_(iConfig.getParameter<edm::ParameterSet>("PUweightSettingsSrc")),
mcGenWeightSrc_(iConfig.getParameter<edm::InputTag>("mcGenWeightSrc")),
LHEEventProductSrc_(iConfig.getParameter<edm::InputTag>("LHEEventProductSrc")),
sampleInfoSrc_(iConfig.getParameter<edm::ParameterSet>("sampleInfoSrc")),
// not needed for >= 76X
// HBHENoiseFilterResultSrc_(iConfig.getParameter<edm::InputTag>("HBHENoiseFilterResultSrc")),
// HBHEIsoNoiseFilterResultSrc_(iConfig.getParameter<edm::InputTag>("HBHEIsoNoiseFilterResultSrc")),
triggerResultsPatSrc_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResultsPatSrc"))),
triggerResultsRecoSrc_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResultsRecoSrc"))),
rhoSource_(iConfig.getParameter<edm::InputTag>("rhoSource" ))
{

  produces<vector<NtuplePairIndependentInfo>>(NAME_).setBranchAlias(NAME_);

  //HBHENoiseFilterResultToken_ = consumes< bool > (HBHENoiseFilterResultSrc_);
  //HBHEIsoNoiseFilterResultToken_ = consumes< bool > (HBHEIsoNoiseFilterResultSrc_);
  LHEEventProductToken_ = consumes<LHEEventProduct> (LHEEventProductSrc_);
  mcGenWeightToken_ = consumes< GenEventInfoProduct > (mcGenWeightSrc_);
  pileupToken_ = consumes< std::vector<PileupSummaryInfo> >  (pileupSrc_);
  slimmedJetToken_ = consumes<edm::View< pat::Jet > > (slimmedJetSrc_);
  slimmedGenJetsToken_ = consumes<edm::View< reco::GenJet > > (slimmedGenJetsSrc_);
  vertexToken_ = consumes<edm::View< reco::Vertex > > (vertexSrc_);
  packedGenToken_ = consumes<edm::View< pat::PackedGenParticle > > (packedGenSrc_);
  prunedGenToken_ = consumes<edm::View< reco::GenParticle > > (prunedGenSrc_);
  rhoToken_ = consumes< double > (rhoSource_);


  /* access the MC pT resolution */

  edm::FileInPath rFile(rFile_string_);
  std::string rFile_string = rFile.fullPath();
  resolution_r = JME::JetResolution(rFile_string);

  /* access the resolution SFs */
  edm::FileInPath sfFile(sfFile_string_);
  std::string sfFile_string = sfFile.fullPath();
  resolution_sf = JME::JetResolutionScaleFactor(sfFile_string);



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
  iEvent.getByToken(packedGenToken_,packedGens);

  // get prunedGen collection
  edm::Handle<edm::View<reco::GenParticle> > prunedGens;
  iEvent.getByToken(prunedGenToken_,prunedGens);

  // get rho 

  edm::Handle<double> arho;
  iEvent.getByToken(rhoToken_,arho);

  double rho_forJER = *arho;
//  std::cout<<" RHO to be used for JER SF tool is "<<rho_forJER<<"\n";


  std::size_t reserveSize = 1; /* only one per event */
  pairIndep->reserve( reserveSize );
  

  // the instance of NtuplePairIndependentInfo we want to add to the event output

  NtuplePairIndependentInfo InfoToWrite;


  ////////////////////////////////////////
  /* fill the sample info PSet   */
  ////////////////////////////////////////

  InfoToWrite.fill_sampleInfo(sampleInfoSrc_);

  /////////////////////////////////////////////////////////////////
  /* start by adding gen particles to InfoToWrite */
  /////////////////////////////////////////////////////////////////

  std::vector<int> typesTokeep = genParticlesToKeep_;

  if(prunedGens.isValid()) 
  {

    /* need to keep Z/W/Higgs 4-momentums summed both vis and total */

    LorentzVector GenBosonVisibleMomentum(0,0,0,0);
    LorentzVector GenBosonTotalMomentum(0,0,0,0);


    for(std::size_t i = 0; i<prunedGens->size(); ++i)
    {

      int fromHardProcessFinalState = prunedGens->at(i).fromHardProcessFinalState();
      int isElectron = prunedGens->at(i).isElectron();
      int isMuon = prunedGens->at(i).isMuon();
      int isDirectHardProcessTauDecayProduct = prunedGens->at(i).statusFlags().isDirectHardProcessTauDecayProduct();
      int isNeutrino = (abs(prunedGens->at(i).pdgId())==12 || abs(prunedGens->at(i).pdgId())==14 || abs(prunedGens->at(i).pdgId())==16);

      if( (fromHardProcessFinalState && (isMuon || isElectron || isNeutrino)) || isDirectHardProcessTauDecayProduct )
      {
        GenBosonTotalMomentum += prunedGens->at(i).p4();
      }
      if( (fromHardProcessFinalState && (isMuon || isElectron)) || (isDirectHardProcessTauDecayProduct && !isNeutrino) )
      {
        GenBosonVisibleMomentum += prunedGens->at(i).p4();
      }

      // std::cout<<" TOT MOM "<<GenBosonTotalMomentum.Pt()<<" ";
      // std::cout<<" VIS MOM "<<GenBosonVisibleMomentum.Pt()<<"\n";

      InfoToWrite.fill_GenBosonTotalMomentum(GenBosonTotalMomentum); 
      InfoToWrite.fill_GenBosonVisibleMomentum(GenBosonVisibleMomentum);



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
  iEvent.getByToken(slimmedJetToken_,slimmedJets);


  // get the slimmedGenJets collection 

  
  edm::Handle<edm::View<reco::GenJet> > slimmedGenJets;
  iEvent.getByToken(slimmedGenJetsToken_,slimmedGenJets);


  // instance of our PUPFjetIdHelper 

  PUPFjetIdHelper puANDpf_IdHelper;


  // decode the parameter set for the PU jet ID

  std::vector<double> pu_ptBounds =  PUjetIDworkingPointSrc_.getParameter<std::vector<double> >("PUjetID_PtBoundries");
  std::vector<double> pu_etaBounds =  PUjetIDworkingPointSrc_.getParameter<std::vector<double> >("PUjetID_AbsEtaBoundries");
  std::string pu_DiscName = PUjetIDworkingPointSrc_.getParameter<std::string> ("DiscriminantName");



  ///////////////////////////////
  // JEC and JER systematics   // - SETUP
  ///////////////////////////////

//////////
// JEC  // -- need the total uncertainty 
//////////
  
  /* "Uncertainty" gives the total sum of all JEC unc. sources 
   if individual JEC sources are needed see 
   https://twiki.cern.ch/twiki/bin/view/CMS/JECUncertaintySources#Code_example */


  edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get("AK4PFchs",JetCorParColl); 
  JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"]; 
  JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(JetCorPar);


//////////
// JER  // -- for 2015 data, recommended not to apply any additional smearing on MC
//////////     on top of miniAOD, however we want the sf, sf+ and sf- for systematics


  // setup the resolution sf tool
  // JME::JetResolutionScaleFactor resolution_pt = JME::JetResolution::get(iSetup, "AK4PFchs_pt");
  // JME::JetResolutionScaleFactor resolution_phi = JME::JetResolution::get(iSetup, "AK4PFchs_phi");




  ///////////////////////////////



  if(slimmedJets.isValid()) 
  {

    for(std::size_t i = 0; i<slimmedJets->size(); ++i)
    {

      NtupleJet currentNtupleJet;
      
 
      /* init the jet */
      currentNtupleJet.fill((slimmedJets->at(i)));
 

     /* start JEC and JER sf. computation */

      /* for MC, get the total JEC uncertainty */
      double JECuncertainty = 0.0;
      double JEC_SF_up = 1.0;
      double JEC_SF_down = 1.0;

      if(!iEvent.isRealData())
      {

        /* JEC */
        jecUnc->setJetEta(slimmedJets->at(i).eta());
        jecUnc->setJetPt(slimmedJets->at(i).pt());

        JECuncertainty = jecUnc->getUncertainty(true);
        JEC_SF_up   = 1 + (1.0 * JECuncertainty);
        JEC_SF_down = 1 + (-1.0 * JECuncertainty);
        currentNtupleJet.fill_JEC_uncertaintySFs(JEC_SF_up, JEC_SF_down);


        // std::cout<<" jet at index "<<i<<" has pt & eta = "<<slimmedJets->at(i).pt()<<" , "<<slimmedJets->at(i).eta()<<" ";
        // std::cout<<" and has total uncertainty  = "<<JECuncertainty<<" giving an up. shift scale factor = ";
        // std::cout<<currentNtupleJet.JEC_uncertaintySF_up()<<" and a down JEC shift scale factor = "<<currentNtupleJet.JEC_uncertaintySF_down()<<"\n";



        /* JER */


        // the pT resolution

        JME::JetParameters parameters_res;
        parameters_res.set(JME::Binning::JetPt, slimmedJets->at(i).pt());
        parameters_res.set({JME::Binning::JetEta, slimmedJets->at(i).eta()});
        parameters_res.set({JME::Binning::Rho, rho_forJER});

        float sigma_MC_PT = resolution_r.getResolution(parameters_res);
    

        // the SFs
        // JME::JetParameters parameters_sf = {{JME::Binning::JetEta, slimmedJets->at(i).eta()}, 
        //                                  {JME::Binning::Rho, rho_forJER}};
        // the example code https://github.com/blinkseb/cmssw/blob/jer_fix_76x/JetMETCorrections/Modules/plugins/JetResolutionDemo.cc#L74
        // does not use rho

        float sf = resolution_sf.getScaleFactor({{JME::Binning::JetEta, slimmedJets->at(i).eta()}}); 
        float sf_up = resolution_sf.getScaleFactor({{JME::Binning::JetEta, slimmedJets->at(i).eta()}}, Variation::UP);
        float sf_down = resolution_sf.getScaleFactor({{JME::Binning::JetEta, slimmedJets->at(i).eta()}}, Variation::DOWN);
        LorentzVector genJetMatchForJER;
        genJetMatchForJER.SetXYZT(0,0,0,0);

        /* look for a GenJet match - this is used for the JER smearing */
        if(slimmedGenJets.isValid()) 
        {
        //  std::cout<<" VALID slimmedGenJets \n";



          for(std::size_t g = 0; g<slimmedGenJets->size(); ++g)
          {



            /* The matching should require dR(reco jet, gen jet)<Rcone/2 and dpt=abs(pT-pTgen)<3*sigma_MC, 
            where Rcone is the AK cone parameter, and sigma_MC_pT is jet pT absolute resolution. */

              double dPt = fabs( slimmedJets->at(i).pt() -  slimmedGenJets->at(g).pt() );
              double maxDiff = 3.0 * sigma_MC_PT;
              double dR = deltaR(slimmedJets->at(i).p4(), slimmedGenJets->at(g).p4());
  

            if( dR < 0.4/2 && dPt < maxDiff)
            {
              // std::cout<<" have a DR match to the jet @ index "<<i<<" and ";
              // std::cout<<" dPt = "<<dPt<<" and maxDiff = "<<maxDiff<<"\n";
              genJetMatchForJER = slimmedGenJets->at(g).p4();
              break;
            }


          }
        

        }

        // std::cout<<" for jet at index i with pt = "<<slimmedJets->at(i).pt()<<" found a genJet match with pT of ";
        // std::cout<<genJetMatchForJER.pt()<<" (0 means no match) which compares to the embedded genJet pt as ";
        // std::cout<<currentNtupleJet.GENjet_p4().pt()<<"\n";



        currentNtupleJet.fill_JER_SFs(sf, sf_up, sf_down, genJetMatchForJER, sigma_MC_PT);


        // std::cout<<" JER sf, sf+, sf-, resolution "<<currentNtupleJet.JER_SF_nominal()<<" "<<currentNtupleJet.JER_SF_up();
        // std::cout<<" "<<currentNtupleJet.JER_SF_down()<<" "<<currentNtupleJet.JER_resolution()<<"\n";




      }





      /* fill b-tag info for default btagger */
      currentNtupleJet.fill_defaultBtagInfo(slimmedJets->at(i), 
                            defaultBtagAlgorithmNameSrc_);
  

      /* fill the PU jet ID */
      std::pair <std::string, unsigned int> nameAndIndex =
                          puANDpf_IdHelper.getPtRangeStringAndEtaIndex(
                          "ptRange_", pu_ptBounds, 
                          pu_etaBounds, 
                          slimmedJets->at(i).pt(), 
                          fabs(slimmedJets->at(i).eta()));

                    

      std::vector<double> pu_cutsByEta =  PUjetIDworkingPointSrc_.getParameter<std::vector<double> >(nameAndIndex.first);
      currentNtupleJet.fill_PUjetID(slimmedJets->at(i),pu_DiscName, pu_cutsByEta[nameAndIndex.second]);


      /* fill the PF jet ID */

       bool passPF = puANDpf_IdHelper.passPfId(PFjetIDworkingPointSrc_, slimmedJets->at(i).eta(),
                currentNtupleJet.NHF(), currentNtupleJet.NEMF(), 
                currentNtupleJet.NumConst(), currentNtupleJet.MUF(), currentNtupleJet.CHF(),
                 currentNtupleJet.CHM(), currentNtupleJet.CEMF(), currentNtupleJet.NumNeutralParticle());

       bool passPFtight = puANDpf_IdHelper.passPfId(TightPFjetIDworkingPointSrc_, slimmedJets->at(i).eta(),
                currentNtupleJet.NHF(), currentNtupleJet.NEMF(), 
                currentNtupleJet.NumConst(), currentNtupleJet.MUF(), currentNtupleJet.CHF(),
                 currentNtupleJet.CHM(), currentNtupleJet.CEMF(), currentNtupleJet.NumNeutralParticle());



      currentNtupleJet.fill_PFjetID(passPF);   
      currentNtupleJet.fill_PFjetIDTight(passPFtight);   

      InfoToWrite.fill_jet(currentNtupleJet);



    }
  }

  ///////////////////////////////////////////////////////////////////////////
  /*   get 1st element in the vertex collection and write it to the event */
  ///////////////////////////////////////////////////////////////////////////

  edm::Handle<edm::View<reco::Vertex> > vertices;
  iEvent.getByToken(vertexToken_,vertices);
  
  InfoToWrite.fill_vertexInfo(vertices->at(0),vertices->size());

  ///////////////////////////////////////////////////////////////////////////
  /*   get the pileUp collection info */
  ///////////////////////////////////////////////////////////////////////////

  edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;
  iEvent.getByToken(pileupToken_, PupInfo);

  /* get the mc and data pu file paths */
  
  std::string pileup_mcFilePath = PUweightSettingsSrc_.getParameter<std::string> ("pileup_mcFilePath");
  std::string pileup_dataFilePath = PUweightSettingsSrc_.getParameter<std::string> ("pileup_dataFilePath");
  InfoToWrite.fill_pileUpInfo(PupInfo,pileup_mcFilePath,pileup_dataFilePath); /* path argument order is mc, data */

  ///////////////////////////////////////////////////////////////////////////
  /*   get the MC gen weight collection  */
  ///////////////////////////////////////////////////////////////////////////

  edm::Handle<GenEventInfoProduct> genEvtWeight;
  iEvent.getByToken(mcGenWeightToken_,genEvtWeight);

  if(genEvtWeight.isValid()) 
    {
      InfoToWrite.fill_generatorEventWeight(genEvtWeight->weight());
    }

  /////////////////////////////////////////////////////////////////////////////////////
  /*   get the MC generated LHE collection - for NUP used in n-jet sample stitching  */
  /////////////////////////////////////////////////////////////////////////////////////

  edm::Handle<LHEEventProduct > LHEHandle;
  iEvent.getByToken(LHEEventProductToken_,LHEHandle);

  //std::cout<<" LHEHandle.isValid() "<<LHEHandle.isValid()<<"\n";

  if(LHEHandle.isValid())
  {

    InfoToWrite.fill_hepNUP((LHEHandle.product()->hepeup()).NUP);


    //////////////// -- weights start
    float orig = float(LHEHandle.product()->originalXWGTUP());

    std::vector <float> theory_sf;

    for(size_t i = 0; i < LHEHandle.product()->weights().size(); ++i)
    {
      float sf = 1.0;
      if(orig != 0) sf = float(LHEHandle.product()->weights()[i].wgt)/orig;
      theory_sf.push_back(sf);
    }

    InfoToWrite.fill_originalXWGTUP(orig);
    InfoToWrite.fill_theory_scale_factors(theory_sf);
    //////////////// -- weights end




    const lhef::HEPEUP& lheEvent = LHEHandle.product()->hepeup();
    std::vector<lhef::HEPEUP::FiveVector> lheParticles = lheEvent.PUP;
  
    double lheHt = 0.; /* this is the gen level HT */
    double lheZmass = 0.; /* this is the gen level Z mass */

    size_t numParticles = lheParticles.size();
    int nOutgoing = 0; /* gen level njets aka. Number of outgoing partons */

    std::vector <TLorentzVector> lhe_Z;
    lhe_Z.clear();

    for ( size_t idxParticle = 0; idxParticle < numParticles; ++idxParticle ) 
    {
      int absPdgId = TMath::Abs(lheEvent.IDUP[idxParticle]);
      int status = lheEvent.ISTUP[idxParticle];
     

      // Z decay products 
      if ( status == 1 && (absPdgId == 11 || absPdgId == 13 || absPdgId == 15)  ) 
      {  
        TLorentzVector lvect(lheParticles[idxParticle].x[0],lheParticles[idxParticle].x[1],lheParticles[idxParticle].x[2],lheParticles[idxParticle].x[3]);
        lhe_Z.push_back(lvect);
      }  

      // quarks and gluons
      if ( status == 1 && ((absPdgId >= 1 && absPdgId <= 6) || absPdgId == 21) ) 
      { 
        // first entry is px, second py
        lheHt += TMath::Sqrt(TMath::Power(lheParticles[idxParticle][0], 2.) + TMath::Power(lheParticles[idxParticle][1], 2.)); 
        ++nOutgoing;
      } 


    }


    if(lhe_Z.size()==2) lheZmass = (lhe_Z[0] + lhe_Z[1]).M();

    //std::cout<<" gen level HT  = "<<lheHt<<" gen level outgoing partons = "<<nOutgoing<<" gen level Z mass  = "<<lheZmass<<"\n";


    InfoToWrite.fill_lheHT(lheHt);
    InfoToWrite.fill_lheOutGoingPartons(nOutgoing);
    InfoToWrite.fill_lheZmass(lheZmass);

  }

  ////////////////////////////////////////////////////////////////////
  /* check the met filters and write them to the event              */ 
  ////////////////////////////////////////////////////////////////////

  ///////////////////////////////////
  // filters re-run on MINI-AOD    //
  ///////////////////////////////////
  // not needed for >= 76X

  // bool Flag_HBHENoiseFilter = 0;
  // bool Flag_HBHEIsoNoiseFilter = 0;

  // edm::Handle<bool> HBHENoiseFilterResult;
  // iEvent.getByToken(HBHENoiseFilterResultToken_,HBHENoiseFilterResult);
  // Flag_HBHENoiseFilter = *HBHENoiseFilterResult;

  // edm::Handle<bool> HBHEIsoNoiseFilterResult;
  // iEvent.getByToken(HBHEIsoNoiseFilterResultToken_,HBHEIsoNoiseFilterResult);
  // Flag_HBHEIsoNoiseFilter = *HBHEIsoNoiseFilterResult;

  ///////////////////////////////////
  // filters read from MINI-AOD    //
  ///////////////////////////////////

  bool Flag_HBHENoiseFilter = 0;                    // TO BE USED
  bool Flag_HBHENoiseIsoFilter = 0;                 //  TO BE USED
  bool Flag_CSCTightHalo2015Filter = 0;             //  TO BE USED
  bool Flag_EcalDeadCellTriggerPrimitiveFilter = 0; //  TO BE USED
  bool Flag_goodVertices = 0;                       //  TO BE USED
  bool Flag_eeBadScFilter = 0;                      //  TO BE USED
  bool Flag_chargedHadronTrackResolutionFilter = 0; //  do not use - those are under study 76X
  bool Flag_muonBadTrackFilter = 0;                 //  do not use - those are under study for 76X



  /* mini-AOD existing met filters; for some samples the process is PAT
  for others it is RECO */

  edm::Handle<edm::TriggerResults> triggerBitsPat;
  iEvent.getByToken(triggerResultsPatSrc_, triggerBitsPat);
  
  edm::Handle<edm::TriggerResults> triggerBitsReco;
  iEvent.getByToken(triggerResultsRecoSrc_, triggerBitsReco);
  
  if( triggerBitsPat.isValid() )
  {
    const edm::TriggerNames &namesPat = iEvent.triggerNames(*triggerBitsPat);
    /////////////
    for (unsigned int i = 0, n = triggerBitsPat->size(); i < n; ++i) 
    {
      if( namesPat.triggerName(i) == "Flag_HBHENoiseFilter") Flag_HBHENoiseFilter = triggerBitsPat->accept(i);
      else if( namesPat.triggerName(i) == "Flag_HBHENoiseIsoFilter") Flag_HBHENoiseIsoFilter = triggerBitsPat->accept(i);
      else if( namesPat.triggerName(i) == "Flag_CSCTightHalo2015Filter") Flag_CSCTightHalo2015Filter = triggerBitsPat->accept(i);
      else if( namesPat.triggerName(i) == "Flag_EcalDeadCellTriggerPrimitiveFilter") Flag_EcalDeadCellTriggerPrimitiveFilter = triggerBitsPat->accept(i);
      else if( namesPat.triggerName(i) == "Flag_goodVertices") Flag_goodVertices = triggerBitsPat->accept(i);
      else if( namesPat.triggerName(i) == "Flag_eeBadScFilter") Flag_eeBadScFilter = triggerBitsPat->accept(i);
      else if( namesPat.triggerName(i) == "Flag_chargedHadronTrackResolutionFilter") Flag_chargedHadronTrackResolutionFilter = triggerBitsPat->accept(i);
      else if( namesPat.triggerName(i) == "Flag_muonBadTrackFilter") Flag_muonBadTrackFilter = triggerBitsPat->accept(i);
    } 
    /////////////
  } 

  else if( triggerBitsReco.isValid() )
  {
    const edm::TriggerNames &namesReco = iEvent.triggerNames(*triggerBitsReco);
    /////////////
    for (unsigned int i = 0, n = triggerBitsReco->size(); i < n; ++i) 
    {
      
      if( namesReco.triggerName(i) == "Flag_HBHENoiseFilter") Flag_HBHENoiseFilter = triggerBitsReco->accept(i);
      else if( namesReco.triggerName(i) == "Flag_HBHENoiseIsoFilter") Flag_HBHENoiseIsoFilter = triggerBitsReco->accept(i);
      else if( namesReco.triggerName(i) == "Flag_CSCTightHalo2015Filter") Flag_CSCTightHalo2015Filter = triggerBitsReco->accept(i);
      else if( namesReco.triggerName(i) == "Flag_EcalDeadCellTriggerPrimitiveFilter") Flag_EcalDeadCellTriggerPrimitiveFilter = triggerBitsReco->accept(i);
      else if( namesReco.triggerName(i) == "Flag_goodVertices") Flag_goodVertices = triggerBitsReco->accept(i);
      else if( namesReco.triggerName(i) == "Flag_eeBadScFilter") Flag_eeBadScFilter = triggerBitsReco->accept(i);
      else if( namesReco.triggerName(i) == "Flag_chargedHadronTrackResolutionFilter") Flag_chargedHadronTrackResolutionFilter = triggerBitsReco->accept(i);
      else if( namesReco.triggerName(i) == "Flag_muonBadTrackFilter") Flag_muonBadTrackFilter = triggerBitsReco->accept(i);

    } 
    /////////////
  } 



  //////////////////////////////////////////////////
  // set the flag values into the InfoToWrite     //
  //////////////////////////////////////////////////

  InfoToWrite.fill_HBHENoiseFilter(Flag_HBHENoiseFilter);
  InfoToWrite.fill_HBHENoiseIsoFilter(Flag_HBHENoiseIsoFilter);
  InfoToWrite.fill_CSCTightHalo2015Filter(Flag_CSCTightHalo2015Filter);
  InfoToWrite.fill_EcalDeadCellTriggerPrimitiveFilter(Flag_EcalDeadCellTriggerPrimitiveFilter);
  InfoToWrite.fill_goodVertices(Flag_goodVertices);
  InfoToWrite.fill_eeBadScFilter(Flag_eeBadScFilter);
  InfoToWrite.fill_chargedHadronTrackResolutionFilter(Flag_chargedHadronTrackResolutionFilter);
  InfoToWrite.fill_muonBadTrackFilter(Flag_muonBadTrackFilter);





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
