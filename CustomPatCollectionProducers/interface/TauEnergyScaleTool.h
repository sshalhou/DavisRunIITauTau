/* given a pat::Tau and a Tau ES correction SF and a Tau ES systematic shift factor 
modify the Tau 4-vector */

#ifndef DavisRunIITauTau_CustomPatCollectionProducers_TauEnergyScaleTool_h
#define DavisRunIITauTau_CustomPatCollectionProducers_TauEnergyScaleTool_h

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


class TauEnergyScaleTool
{

	const float EsCorrectionFactor;
	const float EsShiftScaleFactor;


	public:
		TauEnergyScaleTool(const float, const float);
		virtual ~TauEnergyScaleTool();
		void changeES(pat::Tau &);

};

#endif
  