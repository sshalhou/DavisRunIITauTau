/* clones a pat::Tau collection with embedded user floats */
/* will also clone with corrected ES and systematic shifts of Energy Scale */


// system include files
#include <memory>
#include <assert.h>     

// user include files
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/TauClones.h"
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/LeptonRelativeIsolationTool.h"
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/TauEnergyScaleTool.h"



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


// constructor which clones and adds userFloats to the input collection

TauClones::TauClones(const slimmedPatTauCollection& inputColl, const reco::Vertex & input_vertex,
	const float EsCorrectionFactor,
	const float EsShiftScaleFactorUp,
	const float EsShiftScaleFactorDown,
	edm::Handle<edm::TriggerResults> & triggerBits_,
	edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects_,
	edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales_,
	const edm::TriggerNames &names_):
		taus(inputColl),
		first_vertex(input_vertex),
		EsCorrectionFactor(EsCorrectionFactor),
		EsShiftScaleFactorUp(EsShiftScaleFactorUp),
		EsShiftScaleFactorDown(EsShiftScaleFactorDown),
		triggerBits(triggerBits_),
		triggerObjects(triggerObjects_),
		triggerPreScales(triggerPreScales_),
		names(names_)
		{

		 clone();
		 ChangeEnergyAndFillUserFloats(clones,1.0,1.0);		  
		 ChangeEnergyAndFillUserFloats(clonesCorrectedNominalEsShift,EsCorrectionFactor,1.0);		  
		 ChangeEnergyAndFillUserFloats(clonesCorrectedUpEsShift,EsCorrectionFactor,EsShiftScaleFactorUp);		  
		 ChangeEnergyAndFillUserFloats(clonesCorrectedDownEsShift,EsCorrectionFactor,EsShiftScaleFactorDown);		  


		}

// destructor 

TauClones::~TauClones(){ 
	clones.clear();
	clonesCorrectedNominalEsShift.clear();	
	clonesCorrectedUpEsShift.clear();
	clonesCorrectedDownEsShift.clear();
						}

// clone the collection 


void TauClones::clone()
{
  edm::View<pat::Tau>::const_iterator Tau;
  for(Tau=taus->begin(); Tau!=taus->end(); ++Tau)
  {
  	clones.push_back(*Tau);
  	clonesCorrectedNominalEsShift.push_back(*Tau);
	clonesCorrectedUpEsShift.push_back(*Tau);
	clonesCorrectedDownEsShift.push_back(*Tau);
  }
}




// fill user defined floats

void TauClones::ChangeEnergyAndFillUserFloats(std::vector <pat::Tau> & clones,
	const float CORRECTION, const float SYSTEMATIC)
{

	TriggerInfoEmbeddingTool triggerEmbedderTool(triggerBits,triggerObjects,triggerPreScales,names);

	TauEnergyScaleTool TauEsTool(CORRECTION,SYSTEMATIC);


	for (std::size_t i=0; i<clones.size(); i++)
	  {
	  	pat::Tau t = clones[i];


	  	/////////////////////
	  	// begin by correcting the Tau Es and
	  	// applying the correct systematic shift
	  	// should do this before computing things like isolation!

	  	TauEsTool.changeES(t);


		/////////////
	  	// trigger info

	  	std::vector <std::string> userFloatNames;
	  	std::vector <float> userFloatVals;

	  	triggerEmbedderTool.getTriggerInfo(t,userFloatNames, userFloatVals); 

	  	for (std::size_t a = 0; a< userFloatNames.size(); ++a )
	  	{
		  	t.addUserFloat("acceptedTriggerPrescale_"+userFloatNames[a],userFloatVals[a]);
	  	}



	  	///////////////////////////
	  	// dxy and dz
	  	// to be updated for taus

  		float dxy = 999.0;
		float dz = 999.0;

	  	t.addUserFloat("dxy",dxy);
	  	t.addUserFloat("dz",dz);

	  	////////////////////////////
	  	// evaluate the Tau's relIso

	  	LeptonRelativeIsolationTool IsoTool;
	  	double deltaBeta = 0.5;
	  	double relIso = IsoTool.tauRelIso(t,deltaBeta);

	  	t.addUserFloat("relIso",relIso);


	  	///////////////////////////
	  	clones[i] = t;

	  }	



}

  



