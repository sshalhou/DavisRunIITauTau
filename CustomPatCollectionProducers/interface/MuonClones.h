#ifndef DavisRunIITauTau_TupleHelpers_MUONCLONES_h
#define DavisRunIITauTau_TupleHelpers_MUONCLONES_h

/* clones a pat::Muon collection with embedded user floats */



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
#include "DataFormats/PatCandidates/interface/Muon.h"
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

typedef edm::Handle<edm::View<pat::Muon> > 	slimmedPatMuonCollection;

class muonClones
{

	// input muons and vertex
	const slimmedPatMuonCollection& muons;
	const reco::Vertex & first_vertex;

	// trigger related collections

	edm::Handle<edm::TriggerResults> & triggerBits;   
	edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects;
	edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales;
	const edm::TriggerNames & names;

	public:
		muonClones(const slimmedPatMuonCollection&, const reco::Vertex &,
			edm::Handle<edm::TriggerResults> &,
			edm::Handle<pat::TriggerObjectStandAloneCollection> &,
			edm::Handle<pat::PackedTriggerPrescales>&,
			const edm::TriggerNames &);

		virtual ~muonClones();

		// the cloned collection which will have the user floats embedded
		std::vector <pat::Muon> clones;

	private:
		void clone();
		void fillUserFloats();		  


};


 #endif 



