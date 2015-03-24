/* clones a pat::Tau collection and shifts Energy Scale */

// system include files
#include <memory>
#include <assert.h>     

// user include files
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

TauEnergyScaleTool::TauEnergyScaleTool(const slimmedPatTauCollection& inputColl,
	const float EsCorrectionFactor,
	const float EsShiftScaleFactor):
		taus(inputColl),
		EsCorrectionFactor(EsCorrectionFactor),
		EsShiftScaleFactor(EsShiftScaleFactor)
		{
		 clone();
		}

// destructor 

TauEnergyScaleTool::~TauEnergyScaleTool(){ clones.clear();}


// clone the collection 


void TauEnergyScaleTool::clone()
{
  edm::View<pat::Tau>::const_iterator Tau;
  for(Tau=taus->begin(); Tau!=taus->end(); ++Tau)
  {


  	//////////
    // new tau on which we 
    // will apply correction 
    // and systematic shift

    pat::Tau correctedTau(*Tau);

    // logic to determine if correction should be applied

 	size_t hadrons = 0;
    size_t strips = 0;

    hadrons = Tau->signalPFChargedHadrCands().size();
    strips = Tau->signalPFGammaCands().size();


    double v4_sf = 1.0;
    double v4_sf_MASS = 1.0;

 	/////////////////////
    // 1% correction for improved
    // MSSM analysis if matched to generator
    // level hadronic tau decay

    if ( Tau->genJet() && deltaR(Tau->p4(), Tau->genJet()->p4()) < 0.5 && Tau->genJet()->pt() > 8. )
    {

      if((hadrons==1 && strips>0) || (hadrons==3))
      {


        v4_sf = EsCorrectionFactor*EsShiftScaleFactor;
        v4_sf_MASS = EsCorrectionFactor*EsShiftScaleFactor;

      }

      else if (hadrons==1 && strips==0) 
       {


        v4_sf = EsCorrectionFactor*EsShiftScaleFactor;
        v4_sf_MASS = 1.00000;

       } 



    }

	//////////////
    // scale the 4-vector
    reco::Candidate::LorentzVector EsCorrectedP4(0.0,0.0,0.0,0.0);

    //std::cout<<" shifting 4-vectr by "<<v4_sf<<" and mass by "<<v4_sf_MASS<<"\n";
      
      double pxS = Tau->px()*v4_sf;
      double pyS = Tau->py()*v4_sf;
      double pzS = Tau->pz()*v4_sf;
      double massS = Tau->mass()*v4_sf_MASS;
      double enS = TMath::Sqrt(pxS*pxS + pyS*pyS + pzS*pzS + massS*massS);
      
      EsCorrectedP4.SetPxPyPzE(pxS, pyS, pzS, enS );


 	//////////////////
    // store the new P4

    correctedTau.setP4(EsCorrectedP4);





  	clones.push_back(correctedTau);
  }
}




  



