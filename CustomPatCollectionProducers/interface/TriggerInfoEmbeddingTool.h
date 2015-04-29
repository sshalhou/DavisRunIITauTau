/* for a pat::Electron, Muon or Tau collection embed trigger info as UserFloats */


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
	float bestMatchDR_;
	double trigMatchDRcut;
	std::vector<int> trigMatchTypes;
	std::vector<std::string> trigSummaryPathsAndFilters;



	public:
		TriggerInfoEmbeddingTool(edm::Handle<edm::TriggerResults> &,
				edm::Handle<pat::TriggerObjectStandAloneCollection> &,
				edm::Handle<pat::PackedTriggerPrescales>&,
				const edm::TriggerNames &,
				double,
				std::vector<int>,
				std::vector<std::string>);

		virtual ~TriggerInfoEmbeddingTool();

		void getTriggerInfo(pat::Electron &, std::vector<std::string> &, std::vector<float> &);		
		void getTriggerInfo(pat::Muon &, std::vector<std::string> &, std::vector<float> &);		
		void getTriggerInfo(pat::Tau &, std::vector<std::string> &, std::vector<float> &);		

	private:

		/* fill vectors of accepted paths and return False if size is zero */
        bool wasAnyPathAccepted(std::vector<std::string> &, std::vector<float> &);

        /* return best matched trigger obj index based on reco 4-vector DR and set of TriggerObjTypes*/
		std::size_t getBestMatchedObject(TLorentzVector, std::vector<int> &, float);

		/* fill std::vectors with trigger obj's DR, pt, eta, phi, mass */
		void fillTrigObjKinematics(std::size_t, std::vector<std::string> &, std::vector<float> &, std::string);


		/* fill std::vectors with trigger obj's IDs, paths & filters as concatenated strings (need 1.0 for values) */
		void fillTrigObjInfo(std::size_t, std::vector<std::string> &, std::vector<float> &);

		/* fill trigger filter info for all filters passed by the matchedObject */
		void fillTrigFilterInfo(std::size_t, std::vector<std::string> &, std::vector<float> &, std::string, std::vector<std::string> &);


		/* fill trigger summary info based on trigSummaryPathsAndFilters */
		/* calls fillTrigFilterInfo & fillTrigObjKinematics */

		void TrigSummaryInfoHelper(TLorentzVector, std::vector<std::string> &, std::vector<float> &);

		void fillTrigSummaryInfo(std::size_t, std::vector<std::string> &, std::vector<float> &, std::vector<std::string>);


};

#endif
