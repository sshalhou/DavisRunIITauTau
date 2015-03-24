/* clones a pat::Muon collection with embedded user floats */


// system include files
#include <memory>
#include <assert.h>     

// user include files

#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/MuonClones.h"
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

typedef edm::Handle<edm::View<pat::Muon> > 	slimmedPatMuonCollection;

// constructor which clones and adds userFloats to the input collection

muonClones::muonClones(const slimmedPatMuonCollection& inputColl, const reco::Vertex & input_vertex):
		muons(inputColl),
		first_vertex(input_vertex)
		{

		 clone();
		 fillUserFloats();		  

		}

// destructor 

muonClones::~muonClones(){ clones.clear();}


// clone the collection 


void muonClones::clone()
{
  edm::View<pat::Muon>::const_iterator muon;
  for(muon=muons->begin(); muon!=muons->end(); ++muon)
  {
  	clones.push_back(*muon);
  }
}




// fill user defined floats

void muonClones::fillUserFloats()
{





	for (std::size_t i=0; i<clones.size(); i++)
	  {
	  	pat::Muon m = clones[i];

	  	///////////////////////////
	  	// dxy and dz

  		float dxy = 999.0;
		float dz = 999.0;

		// worried that we need a innerTrack check here?
		//assert(m.innerTrack().isNonnull());


		if (m.innerTrack().isNonnull())
		{
		  	dxy = m.innerTrack()->dxy(first_vertex.position());
	  		dz = m.innerTrack()->dz(first_vertex.position());
		}


	  	m.addUserFloat("dxy",dxy);
	  	m.addUserFloat("dz",dz);

	  	////////////////////////////
	  	// evaluate the muon's relIso

	  	LeptonRelativeIsolationTool IsoTool;
	  	double deltaBeta = 0.5;
	  	double relIso = IsoTool.muonRelIso(m,deltaBeta);

	  	m.addUserFloat("relIso",relIso);


	  	///////////////////////////
	  	clones[i] = m;

	  }	



}

  



