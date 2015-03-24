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




	public:
		TauClones(const slimmedPatTauCollection&, const reco::Vertex &);

		virtual ~TauClones();

		// the cloned collection which will have the user floats embedded
		std::vector <pat::Tau> clones;

	private:
		void clone();
		void fillUserFloats();		  


};





#endif
  



