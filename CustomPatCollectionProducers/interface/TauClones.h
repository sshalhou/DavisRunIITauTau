#ifndef DavisRunIITauTau_CustomPatCollectionProducers_TauCLONES_h
#define DavisRunIITauTau_CustomPatCollectionProducers_TauCLONES_h



/* clones a pat::Tau collection with embedded user floats */

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
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/LeptonRelativeIsolationTool.h"

#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/TriggerInfoEmbeddingTool.h"


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

class TauClones
{

	// input taus and vertex
	const slimmedPatTauCollection& taus;
	const reco::Vertex & first_vertex;
	const float EsCorrectionFactor;
	const float EsShiftScaleFactorUp;
	const float EsShiftScaleFactorDown;

	// trigger related collections

	edm::Handle<edm::TriggerResults> & triggerBits;   
	edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects;
	edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales;
	const edm::TriggerNames & names;
	double trigMatchDRcut;
	std::vector<int> trigMatchTypes;
	std::vector<std::string> trigSummaryPathsAndFilters;



	public:
		TauClones(const slimmedPatTauCollection&, const reco::Vertex &, const float, const float, const float,
			edm::Handle<edm::TriggerResults> &,
			edm::Handle<pat::TriggerObjectStandAloneCollection> &,
			edm::Handle<pat::PackedTriggerPrescales>&,
			const edm::TriggerNames &,
			double,
			std::vector<int>,
			std::vector<std::string>);

		virtual ~TauClones();

		/////////////////////////////////////////////////////////////////////
		// the cloned collection which will have the user floats embedded and ES changed
		/////////////////////////////////////////////////////////////////////
		/* only change is embedded userFloats */

		std::vector <pat::Tau> clones; 

		/* embed userFloats and correct Es */

		std::vector <pat::Tau> clonesCorrectedNominalEsShift; 

		/* embed userFloats and correct Es and sys. shift Up */

		std::vector <pat::Tau> clonesCorrectedUpEsShift; 

		/* embed userFloats and correct Es and sys. shift Down */

		std::vector <pat::Tau> clonesCorrectedDownEsShift; 


	private:
		void clone();
		// function to embed user quantities and change ES the 2 float arguments are 
		// Tau ES correction SF and the Systematic shift 
		// Tau P4 will be scaled by the product of the 2 floats 
		void ChangeEnergyAndFillUserFloats(std::vector <pat::Tau>&, const float, const float);		  


};





#endif
  



