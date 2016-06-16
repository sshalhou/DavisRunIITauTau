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
	const float EsShiftScaleFactor;

	// trigger related collections

	edm::Handle<edm::TriggerResults> & triggerBits;   
	edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects;
	edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales;
	const edm::TriggerNames & names;

	// rho related info
	std::vector<std::string> rhoLabels;
	std::vector<double> rhoValues;



	public:
		TauClones(const slimmedPatTauCollection&, const reco::Vertex &, const float, const float,
			edm::Handle<edm::TriggerResults> &,
			edm::Handle<pat::TriggerObjectStandAloneCollection> &,
			edm::Handle<pat::PackedTriggerPrescales>&,
			const edm::TriggerNames &,
			std::vector<std::string>,
			std::vector<double>);

		virtual ~TauClones();

		/////////////////////////////////////////////////////////////////////
		// the cloned collection which will have the user floats embedded and ES changed
		/////////////////////////////////////////////////////////////////////

		std::vector <pat::Tau> clonesCorrectedAndShifted; 



	private:
		void clone();
		// function to embed user quantities and change ES the 2 float arguments are 
		// Tau ES correction SF and the Systematic shift 
		// Tau P4 will be scaled by the product of the 2 floats 
		void ChangeEnergyAndFillUserFloats(std::vector <pat::Tau>&, const float, const float);		  


};





#endif
  



