/* clones a pat::Tau collection with embedded user floats */
/* will also clone with corrected ES and systematic shifts of Energy Scale */


// system include files
#include <memory>
#include <assert.h>     

// user include files
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/TauClones.h"
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


// constructor which clones and adds userFloats to the input collection

TauClones::TauClones(const slimmedPatTauCollection& inputColl, const reco::Vertex & input_vertex,
	const float EsCorrectionFactor,
	const float EsShiftScaleFactorUp,
	const float EsShiftScaleFactorDown):
		taus(inputColl),
		first_vertex(input_vertex),
		EsCorrectionFactor(EsCorrectionFactor),
		EsShiftScaleFactorUp(EsShiftScaleFactorUp),
		EsShiftScaleFactorDown(EsShiftScaleFactorDown)
		{

		 clone();
		 ChangeEnergyAndFillUserFloats(clones);		  
		 ChangeEnergyAndFillUserFloats(clonesCorrectedNominalEsShift);		  
		 ChangeEnergyAndFillUserFloats(clonesCorrectedUpEsShift);		  
		 ChangeEnergyAndFillUserFloats(clonesCorrectedDownEsShift);		  


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

void TauClones::ChangeEnergyAndFillUserFloats(std::vector <pat::Tau> & clones)
{





	for (std::size_t i=0; i<clones.size(); i++)
	  {
	  	pat::Tau t = clones[i];

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

  



