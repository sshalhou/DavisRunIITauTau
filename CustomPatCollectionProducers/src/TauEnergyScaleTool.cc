/* given a pat::Tau and a Tau ES correction SF and a Tau ES systematic shift factor 
modify the Tau 4-vector */

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



// constructor which clones and adds userFloats to the input collection

TauEnergyScaleTool::TauEnergyScaleTool(
	const float EsCorrectionFactor,
	const float EsShiftScaleFactor):
		EsCorrectionFactor(EsCorrectionFactor),
		EsShiftScaleFactor(EsShiftScaleFactor){}

// destructor 

TauEnergyScaleTool::~TauEnergyScaleTool(){}


// clone the collection 


void TauEnergyScaleTool::changeES(pat::Tau& TauToChange)
{
  
    // logic to determine if correction should be applied

 	  size_t hadrons = 0;
    size_t strips = 0;

    // note the the runI version of these had signalPF  
    // instead of signal in the variable name
    hadrons = TauToChange.signalChargedHadrCands().size();
    strips =  TauToChange.signalGammaCands().size();


    double v4_sf = 1.0;
    double v4_sf_MASS = 1.0;

 	  /////////////////////
    // 1% correction for improved
    // MSSM analysis if matched to generator
    // level hadronic tau decay

    if ( TauToChange.genJet() && deltaR(TauToChange.p4(), TauToChange.genJet()->p4()) < 0.5 && TauToChange.genJet()->pt() > 8. )
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
      
      double pxS = TauToChange.px()*v4_sf;
      double pyS = TauToChange.py()*v4_sf;
      double pzS = TauToChange.pz()*v4_sf;
      double massS = TauToChange.mass()*v4_sf_MASS;
      double enS = TMath::Sqrt(pxS*pxS + pyS*pyS + pzS*pzS + massS*massS);
      
      EsCorrectedP4.SetPxPyPzE(pxS, pyS, pzS, enS );


   	//////////////////
    // store the new P4

    TauToChange.setP4(EsCorrectedP4);



  }





  



