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
	const edm::TriggerNames &names_,
	std::vector<std::string> rhoLabels_,
	std::vector<double> rhoValues_):
		taus(inputColl),
		first_vertex(input_vertex),
		EsCorrectionFactor(EsCorrectionFactor),
		EsShiftScaleFactorUp(EsShiftScaleFactorUp),
		EsShiftScaleFactorDown(EsShiftScaleFactorDown),
		triggerBits(triggerBits_),
		triggerObjects(triggerObjects_),
		triggerPreScales(triggerPreScales_),
		names(names_),
		rhoLabels(rhoLabels_),
		rhoValues(rhoValues_)
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

	  	/////////////////////////
	  	// add a userfloat to track TauEs variant 

	  	if(SYSTEMATIC==1.0)
	  	{
	  		t.addUserFloat("TauEsVariant",0.0);
	  	}
	  	else if(SYSTEMATIC>1.0)
	  	{
	  		t.addUserFloat("TauEsVariant",1.0);
	  	}
	  	else if(SYSTEMATIC<1.0)
	  	{
	  		t.addUserFloat("TauEsVariant",-1.0);
	  	}


		/////////////
	  	// trigger info

	  	std::vector <std::string> userFloatNames;
	  	std::vector <float> userFloatVals;

	  	triggerEmbedderTool.fillAcceptedPathsAndPrescales(userFloatNames, userFloatVals); 

	  	for (std::size_t a = 0; a< userFloatNames.size(); ++a )
	  	{
		  	t.addUserFloat(userFloatNames[a],userFloatVals[a]);
	  	}



	  	///////////////////////////
	  	// dxy and dz
	  	// to be updated for taus

		float dzTauVertex = t.vertex().z() - first_vertex.z();
	  	pat::PackedCandidate const* packedLeadTauCand = dynamic_cast<pat::PackedCandidate const*>(t.leadChargedHadrCand().get());
	  	float dz = packedLeadTauCand->dz();

	  	t.addUserFloat("dxy",t.dxy());
	  	t.addUserFloat("dz",dz);
	  	t.addUserFloat("dzTauVertex",dzTauVertex);

	  	////////////////////
	  	// ZimpactTau

	  	float ZimpactTau = first_vertex.z() + (130.0)/tan(t.theta());
	  	t.addUserFloat("ZimpactTau",ZimpactTau);


	  	// iso-related quantities

	  	t.addUserFloat("chargedHadronIso", t.chargedHadronIso());
		t.addUserFloat("neutralHadronIso", t.neutralHadronIso());
		t.addUserFloat("photonIso", t.photonIso());
		t.addUserFloat("PUchargedHadronIso",  t.puChargedHadronIso());


		// tau IDs and MVA isolations

		for (std::size_t p=0; p<t.tauIDs().size(); ++p)
		{

			t.addUserFloat("tauID_"+t.tauIDs()[p].first,t.tauIDs()[p].second);

		}



		////////////////
		// strip and hadron counts

		t.addUserFloat("numStrips",  float(t.signalGammaCands().size()));
		t.addUserFloat("numHadrons", float(t.signalChargedHadrCands().size()));

	  	// push in the rho variants, and the relative isol based on
	  	// each

	  	for (std::size_t x = 0; x<rhoLabels.size(); ++x )
	  	{
	  		t.addUserFloat("rho_"+rhoLabels[x],rhoValues[x]);
	  	}


	  	////////////////////////////
	  	// evaluate the Tau's relIso

	  	LeptonRelativeIsolationTool IsoTool;
	  	double deltaBeta = 0.5;
	  	double relIso = IsoTool.tauRelIso(t,deltaBeta);

	  	t.addUserFloat("relativeIsol_DeltaBetaCorrectedRelIso",relIso);


	  	///////////////////////////
	  	clones[i] = t;

	  }	



}

  



