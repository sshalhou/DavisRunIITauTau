// -*- C++ -*-
// really simple flatTuple producer
// Package:    CumulativeInfoAdder
// Class:      CumulativeInfoAdder
//
//
// Description: [EDAnalyzer that creates small ntuple to track info for all events in sample (even those failing skim)]
//
//
// Original Author:  shalhout shalhout
//         Created:  Tue Jun  4 04:25:53 CDT 2015
// 


#ifndef DavisRunIITauTau_CumulativeInfoAdder_CumulativeInfoAdder_h
#define DavisRunIITauTau_CumulativeInfoAdder_CumulativeInfoAdder_h




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
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
// Custom object include files


#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleGenParticle.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"


using namespace edm;
using namespace std;
typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<edm::InputTag> vInputTag;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;

class CumulativeInfoAdder : public edm::EDAnalyzer
{
public:
	explicit CumulativeInfoAdder(const edm::ParameterSet&);
	~CumulativeInfoAdder();

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      virtual void reInit(); 
  	  virtual void endRun(edm::Run const&, edm::EventSetup const&) override;



// private:
// 	virtual void beginJob() ;
// 	virtual void analyze(const edm::Event&, const edm::EventSetup&);
// 	virtual void endJob() ;

// 	virtual void beginRun(edm::Run const&, edm::EventSetup const&);
// 	virtual void endRun(edm::Run const&, edm::EventSetup const&);
// 	virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
// 	virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
// 	virtual void reInit();

	
	
	// ----------member data ---------------------------


	/* the TTree */
	TTree * CumulativeTuple;

	/* input */
	edm::InputTag mcGenWeightSrc_;
    edm::EDGetTokenT<GenEventInfoProduct> mcGenWeightToken_;

    edm::InputTag LHEEventProductSrc_;
  	edm::EDGetTokenT<LHERunInfoProduct> LHEEventProductToken_;
  

	/* variables for the TTree */

	double generatorEventWeight;


};  


//define this as a plug-in
DEFINE_FWK_MODULE(CumulativeInfoAdder);
#endif
