#ifndef DavisRunIITauTau_CustomPatCollectionProducers_TauEnergyScaleTool_h
#define DavisRunIITauTau_CustomPatCollectionProducers_TauEnergyScaleTool_h



/* clones a pat::Tau collection and shifts Energy Scale */

// system include files
#include <memory>
#include <assert.h>     

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"

//#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/Tau.h"



#include "TH1D.h"
#include <map>
#include "TFile.h"
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TString.h"

typedef edm::Handle<edm::View<pat::Tau> > 	slimmedPatTauCollection;

class TauEnergyScaleTool
{

	// input taus and vertex
	const slimmedPatTauCollection& taus;
	const float EsCorrectionFactor;
	const float EsShiftScaleFactor;


	public:
		TauEnergyScaleTool(const slimmedPatTauCollection&, const float, const float);
		virtual ~TauEnergyScaleTool();
		
		// the cloned collection which will have the tau ES shifted
		std::vector <pat::Tau> clones;

	private:
		void clone();

};

#endif
  