/* clones a pat::Electron collection with embedded user floats */


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

#include "DataFormats/Common/interface/ValueMap.h"

#include "DataFormats/PatCandidates/interface/Electron.h"

#include "EgammaAnalysis/ElectronTools/interface/EGammaMvaEleEstimatorCSA14.h"




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

class electronClones
{

	// input electrons and vertex
	const slimmedPatElectronCollection& electrons;
	const reco::Vertex & first_vertex;

	// the list of mva ID evaluators and the names of thier embedded userFloats
	EGammaMvaEleEstimatorCSA14 & MVAS;
	std::string & MVA_NAMES;


	public:
		electronClones(const slimmedPatElectronCollection&, const reco::Vertex &,
				EGammaMvaEleEstimatorCSA14 &, 
				std::string &);

		virtual ~electronClones();

		// the cloned collection which will have the user floats embedded
		std::vector <pat::Electron> clones;






	private:
		void clone();
		void fillUserFloats();		  


};


// constructor which clones and adds userFloats to the input collection

electronClones::electronClones(const slimmedPatElectronCollection& inputColl, const reco::Vertex & input_vertex,
				 EGammaMvaEleEstimatorCSA14 & MVAS_, 
				 std::string & MVA_NAMES_):
		electrons(inputColl),
		first_vertex(input_vertex),
		MVAS(MVAS_),
		MVA_NAMES(MVA_NAMES_)
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





	for (std::size_t i=0; i<clones.size(); i++)
	  {
	  	pat::Electron e = clones[i];

	  	///////////////////////////
	  	// dxy and dz

  		float dxy = 999.0;
		float dz = 999.0;

	  	dxy = e.gsfTrack()->dxy(first_vertex.position());
	  	e.addUserFloat("dxy",dxy);

	  	dz = e.gsfTrack()->dz(first_vertex.position());
	  	e.addUserFloat("dz",dz);



	  	// add the mva IDs 


	  	float mva_val = MVAS.mvaValue(e,true);
	  	
		std::cout<<" pt = "<<e.p4().Pt()<<" ";
	    std::cout<<" mva from in "<<mva_val<<std::endl;


	  	// for (std::size_t mva = 0; mva<MVA_NAMES.size(); mva++)
	  	// {


	  	// 	EGammaMvaEleEstimatorCSA14 * A = &MVAS[mva];
	  	// 	//std::cout<<MVAS[mva]<<std::endl;
	  	// 	// float mva_val = MVAS[mva].mvaValue(e,true);
	  	

	  	// 	// std::cout<<MVA_NAMES[mva]<<" pt = "<<e.p4().Pt()<<" ";
		  //  //  std::cout<<" mva from in "<<mva_val<<std::endl;



	  	// }




	  	///////////////////////////
	  	clones[i] = e;

	  }	



}

  



