/* for a pat::Electron, Muon or Tau collection embed accepted HLT trigger paths as UserFloats */


#ifndef DavisRunIITauTau_CustomPatCollectionProducers_TRIGGERINFOEMBEDDINGTOOL_h
#define DavisRunIITauTau_CustomPatCollectionProducers_TRIGGERINFOEMBEDDINGTOOL_h

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"

//#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"



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


class TriggerInfoEmbeddingTool
{

	// trigger related collections

	edm::Handle<edm::TriggerResults> & triggerBits;   
	edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects;
	edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales;
	const edm::TriggerNames & names;




	public:
		TriggerInfoEmbeddingTool(edm::Handle<edm::TriggerResults> &,
				edm::Handle<pat::TriggerObjectStandAloneCollection> &,
				edm::Handle<pat::PackedTriggerPrescales>&,
				const edm::TriggerNames &);

		virtual ~TriggerInfoEmbeddingTool();

	

		/* fill vectors of accepted paths - simple accept check without object or filter matching */
        void fillAcceptedPathsAndPrescales(std::vector<std::string> &, std::vector<float> &);





};

#endif
