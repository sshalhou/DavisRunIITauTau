/* clones a pat::Electron collection with embedded user floats including MVA ID*/


// system include files
#include <memory>
#include <assert.h>     

// user include files
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/ElectronClones.h"
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

typedef edm::Handle<edm::View<pat::Electron> > 	slimmedPatElectronCollection;


// constructor which clones and adds userFloats to the input collection

electronClones::electronClones(const slimmedPatElectronCollection& inputColl, const reco::Vertex & input_vertex,
				EGammaMvaEleEstimatorCSA14 & MVA_PHYS14nonTrig_, 
				std::string & MVA_PHYS14nonTrig_NAME_,
				edm::Handle<edm::TriggerResults> & triggerBits_,
				edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects_,
				edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales_,
				const edm::TriggerNames &names_,
				double trigMatchDRcut_,
				std::vector<int> trigMatchTypes_,
				std::vector<std::string> trigSummaryPathsAndFilters_,
				std::vector<std::string> rhoLabels_,
				std::vector<double> rhoValues_):
		electrons(inputColl),
		first_vertex(input_vertex),
		MVA_PHYS14nonTrig(MVA_PHYS14nonTrig_),
		MVA_PHYS14nonTrig_NAME(MVA_PHYS14nonTrig_NAME_),
		triggerBits(triggerBits_),
		triggerObjects(triggerObjects_),
		triggerPreScales(triggerPreScales_),
		names(names_),
		trigMatchDRcut(trigMatchDRcut_),
		trigMatchTypes(trigMatchTypes_),
		trigSummaryPathsAndFilters(trigSummaryPathsAndFilters_),
		rhoLabels(rhoLabels_),
		rhoValues(rhoValues_)
		{

		 clone();
		 fillUserFloats();		  

		}

// destructor 

electronClones::~electronClones(){ clones.clear();}


// clone the collection 


void electronClones::clone()
{
  edm::View<pat::Electron>::const_iterator electron;
  for(electron=electrons->begin(); electron!=electrons->end(); ++electron)
  {
  	clones.push_back(*electron);
  }
}




// fill user defined floats

void electronClones::fillUserFloats()
{

	TriggerInfoEmbeddingTool triggerEmbedderTool(triggerBits,triggerObjects,triggerPreScales,names,
											trigMatchDRcut,trigMatchTypes,trigSummaryPathsAndFilters);



	for (std::size_t i=0; i<clones.size(); i++)
	  {
	  	pat::Electron e = clones[i];

	  	/////////////
	  	// trigger info

	  	std::vector <std::string> userFloatNames;
	  	std::vector <float> userFloatVals;

	  	triggerEmbedderTool.getTriggerInfo(e,userFloatNames, userFloatVals); 
	  		



	  	for (std::size_t a = 0; a< userFloatNames.size(); ++a )
	  	{
	  		//std::cout<<"ele "<<i<<" "<<userFloatNames[a]<<" "<<userFloatVals[a]<<"\n";

		  	e.addUserFloat(userFloatNames[a],userFloatVals[a]);


	  	}

	  	///////////////////////////
	  	// dxy and dz

  		float dxy = 999.0;
		float dz = 999.0;

		// worried that we need a gsfTrack check here?
		//		assert(e.gsfTrack().isNonnull());

		if(e.gsfTrack().isNonnull())
		{
		  	dxy = e.gsfTrack()->dxy(first_vertex.position());
		  	dz = e.gsfTrack()->dz(first_vertex.position());
		}

	  	e.addUserFloat("dxy",dxy);
	  	e.addUserFloat("dz",dz);

	  	// push in the rho variants

	  	for (std::size_t x = 0; x<rhoLabels.size(); ++x )
	  	{
	  		e.addUserFloat(rhoLabels[x],rhoValues[x]);

	  	}

	  	////////////////////////////
	  	// evaluate the electron's relIso

	  	LeptonRelativeIsolationTool IsoTool;
	  	double deltaBeta = 0.5;
	  	double relIso = IsoTool.electronRelIso(e,deltaBeta);

	  	e.addUserFloat("DeltaBetaCorrectedRelIso",relIso);


	  	///////////////////////////
	  	// evaluate and add the mva IDs 

	  	float mva_val = MVA_PHYS14nonTrig.mvaValue(e,false);
	    e.addUserFloat(MVA_PHYS14nonTrig_NAME,mva_val);

	  	///////////////////////////
	    // once ready add the pass/fail based on the mva

	    e.addUserFloat("PASS_"+MVA_PHYS14nonTrig_NAME,1.00);


	  	///////////////////////////
	  	clones[i] = e;

	  }	



}

  



