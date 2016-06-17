/* clones a pat::Electron collection with embedded user floats including MVA ID*/


// system include files
#include <memory>
#include <assert.h>     

// user include files
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/ElectronClones.h"
#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/LeptonRelativeIsolationTool.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"


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
				edm::Handle<edm::TriggerResults> & triggerBits_,
				edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects_,
				edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales_,
				const edm::TriggerNames &names_,				
				std::vector<std::string> rhoLabels_,
				std::vector<double> rhoValues_):
		electrons(inputColl),
		first_vertex(input_vertex),
		triggerBits(triggerBits_),
		triggerObjects(triggerObjects_),
		triggerPreScales(triggerPreScales_),
		names(names_),		
		rhoLabels(rhoLabels_),
		rhoValues(rhoValues_)
		{

		 clone();
		 fillUserFloats();		  

		}

// destructor 

electronClones::~electronClones(){ clones.clear();}

// cut based veto electron ID

float electronClones::passedCutBasedID(pat::Electron& e)
{	
	assert(1==2); /* this function should not be called anymore! since CMSSW742 there is better way for e cut-based ID*/


	float ABS_SC_ETA = fabs(e.superCluster()->eta());

	float c_dEtaIn  = 0;
	float c_dPhiIn  = 0;
	float c_full5x5_sigmaIetaIeta  = 0;
	float c_hOverE  = 0;
	float c_d0  = 0;
	float c_dz  = 0;
	float c_ooEmooP  = 0;
	float c_relIso  = 0;
	float c_expectedMissingInnerHits  = 0;

	if(ABS_SC_ETA<= 1.479)
	{
		c_dEtaIn  = 				 0.013625;
		c_dPhiIn  = 				 0.230374;
		c_full5x5_sigmaIetaIeta  =   0.011586;
		c_hOverE  =					 0.181130;
		c_d0  = 					 0.094095; 	
		c_dz  = 					 0.713070;
		c_ooEmooP  = 				 0.295751;
		c_relIso   = 				 0.158721;
		c_expectedMissingInnerHits = 2;

	}

	else if(ABS_SC_ETA > 1.479 && ABS_SC_ETA < 2.5 )  	
	{
		c_dEtaIn  = 				 0.011932;
		c_dPhiIn  = 				 0.255450;
		c_full5x5_sigmaIetaIeta  =   0.031849;
		c_hOverE  =					 0.223870;
		c_d0  = 					 0.342293; 	
		c_dz  = 					 0.953461;
		c_ooEmooP  = 				 0.155501;
		c_relIso   = 				 0.177032;
		c_expectedMissingInnerHits = 3;

	}

	if(!( fabs(e.deltaEtaSuperClusterTrackAtVtx()) < c_dEtaIn)) return 0;
	if(!( fabs(e.deltaPhiSuperClusterTrackAtVtx()) < c_dPhiIn)) return 0;
	if(!( e.full5x5_sigmaIetaIeta() < c_full5x5_sigmaIetaIeta)) return 0;
	if(!( e.hadronicOverEm() < c_hOverE)) return 0;
	if(!( fabs(e.userFloat("dxy")) < c_d0)) return 0;
	if(!( fabs(e.userFloat("dz")) < c_dz)) return 0;
	if(!( e.userFloat("ooEmooP") < c_ooEmooP)) return 0;
	if(!( e.userFloat("relativeIsol_DeltaBetaCorrectedRelIso") < c_relIso)) return 0;
	if(!( e.userFloat("numberOfMissingInnerHits") <=  c_expectedMissingInnerHits)) return 0;
	if(!( e.passConversionVeto())) return 0;

	return 1.0;
}


// pass-fail phys 14 MVA 
// return a pass/fail based on MVA score, pt, and absSuperClusterEta */
//		float passedCutBasedID(float, float, float); 


float electronClones::passedMVA(float MVAOUT, float PT, float ABS_SUPERCLUSTER_ETA, int WP)
{

	assert(1==2); /* this function should not be called anymore! since CMSSW742 there is better way for e mva ID*/

	float returnVal = 0.0;
	float ABSETA  = fabs(ABS_SUPERCLUSTER_ETA); // always ensure abs

	float low[3] = {-999.0,-999.0,-999.0};
	float high[3] = {-999.0,-999.0,-999.0};

	if(WP==80)
	{
		low[0] = -0.253;
		low[1] = 0.081;
		low[2] = -0.081;
		high[0] = 0.965;
		high[1] = 0.917;
		high[2] =  0.683;
	}
	else if(WP==90)
	{
		low[0] = -0.483;
		low[1] = -0.267;
		low[2] = -0.323;
		high[0] = 0.933;
		high[1] = 0.825;
		high[2] = 0.337;
	}

	// low-pt
	if(PT <= 10.0)
	{
		if(ABSETA < 0.8 && MVAOUT > low[0]) return 1.0;
		else if(ABSETA >= 0.8 && ABSETA<1.479 && MVAOUT > low[1] ) return 1.0;
		else if(ABSETA >= 1.479 && MVAOUT >  low[2]) return 1.0;
	}


	// high-pt
	else if(PT>10.0)
	{
		if(ABSETA < 0.8 && MVAOUT > high[0]  ) return 1.0;
		else if(ABSETA >= 0.8 && ABSETA<1.479 && MVAOUT > high[1] ) return 1.0;
		else if(ABSETA >= 1.479 && MVAOUT > high[2] ) return 1.0;
	}


	return returnVal;

} 


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

	TriggerInfoEmbeddingTool triggerEmbedderTool(triggerBits,triggerObjects,triggerPreScales,names);



	for (std::size_t i=0; i<clones.size(); i++)
	  {
	  	pat::Electron e = clones[i];

	  	/////////////
	  	// trigger info

	  	std::vector <std::string> userFloatNames;
	  	std::vector <float> userFloatVals;

	  	triggerEmbedderTool.fillAcceptedPathsAndPrescales(userFloatNames, userFloatVals); 
	  		



	  	for (std::size_t a = 0; a< userFloatNames.size(); ++a )
	  	{
	  		//std::cout<<"ele "<<i<<" "<<userFloatNames[a]<<" "<<userFloatVals[a]<<"\n";

		  	e.addUserFloat(userFloatNames[a],userFloatVals[a]);


	  	}


	  	////////////////////////
	  	// isEB, isEE, isEBEEGap, ...
		
		e.addUserFloat("isEB",e.isEB());
		e.addUserFloat("isEE",e.isEE());
		e.addUserFloat("isEBEEGap",e.isEBEEGap());
		e.addUserFloat("isEBEtaGap",e.isEBEtaGap());
		e.addUserFloat("isEBPhiGap",e.isEBPhiGap());
		e.addUserFloat("isEEDeeGap",e.isEEDeeGap());
		e.addUserFloat("isEERingGap",e.isEERingGap());



	  	////////////////////////
	  	// sigmaEtaEta, sigmaIeataIeta, sigmaIphiIphi

		e.addUserFloat("sigmaEtaEta",e.sigmaEtaEta());
		e.addUserFloat("sigmaIetaIeta",e.sigmaIetaIeta());
		e.addUserFloat("sigmaIphiIphi",e.sigmaIphiIphi());

		////////////
		// deltaPhiSuperClusterTrackAtVtx, deltaEtaSuperClusterTrackAtVtx, hadronicOverEm

		e.addUserFloat("deltaPhiSuperClusterTrackAtVtx",e.deltaPhiSuperClusterTrackAtVtx());
		e.addUserFloat("deltaEtaSuperClusterTrackAtVtx",e.deltaEtaSuperClusterTrackAtVtx());
		e.addUserFloat("hadronicOverEm",e.hadronicOverEm());


		///////////////////////////
	  	// IP, IPerror, note : SIP = IP/fabs(IPerror) is the useful quantity

		e.addUserFloat("IP",fabs(e.dB(pat::Electron::PV3D)));
		e.addUserFloat("IPerror",(e.edB(pat::Electron::PV3D)));


	  	///////////////////////////
	  	// dxy, dz, numberOfMissingInnerHits, passConversionVeto, hits, missing hits


  		float dxy = NAN;
		float dz = NAN;
		float numberOfMissingInnerHits = NAN;
		float numberOfMissingOuterHits = NAN;
		float numberOfTrackHits = NAN;

		// worried that we need a gsfTrack check here?
		//		assert(e.gsfTrack().isNonnull());

		if(e.gsfTrack().isNonnull())
		{
		  	dxy = e.gsfTrack()->dxy(first_vertex.position());
		  	dz = e.gsfTrack()->dz(first_vertex.position());
		  	numberOfMissingInnerHits = e.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::HitCategory::MISSING_INNER_HITS);
			numberOfMissingOuterHits = e.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::HitCategory::MISSING_OUTER_HITS);
			numberOfTrackHits = e.gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::HitCategory::TRACK_HITS);
	
		}

	  	e.addUserFloat("dxy",dxy);
	  	e.addUserFloat("dz",dz);
	  	e.addUserFloat("numberOfMissingInnerHits",numberOfMissingInnerHits);
	  	e.addUserFloat("numberOfMissingOuterHits",numberOfMissingOuterHits);
	  	e.addUserFloat("numberOfTrackHits",numberOfTrackHits);
	  	e.addUserFloat("passConversionVeto",e.passConversionVeto());



	  	// compute the electrons' effective area 
	  	// for now hardcode to 2012 settings eventually need
	  	// this to be drawn from a config file

	  	float absSuperClusterEta = NAN;
	  	float SuperClusterEta = NAN;


	  	if(e.superCluster().isNonnull())
		{
	  		absSuperClusterEta = fabs(e.superCluster()->eta());
	  		SuperClusterEta = e.superCluster()->eta();

  		}

	  	e.addUserFloat("SuperClusterEta",SuperClusterEta);



  		float EffArea = ElectronEffectiveArea::GetElectronEffectiveArea(
  						ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04,
					    absSuperClusterEta, ElectronEffectiveArea::kEleEAData2012);


	  	e.addUserFloat("EffectiveArea",EffArea);

	  	// iso tool 
	  	LeptonRelativeIsolationTool IsoTool;


	  	// iso-related quantities

	  	double chargedHadron = e.pfIsolationVariables().sumChargedHadronPt;
		double neutralHadron = e.pfIsolationVariables().sumNeutralHadronEt;
		double photonIso = e.pfIsolationVariables().sumPhotonEt;
		double PUchargedHadron = e.pfIsolationVariables().sumPUPt;


	  	e.addUserFloat("chargedHadronIso", chargedHadron);
		e.addUserFloat("neutralHadronIso", neutralHadron);
		e.addUserFloat("photonIso", photonIso);
		e.addUserFloat("PUchargedHadronIso",  PUchargedHadron);



	  	// push in the rho variants, and the relative isol based on
	  	// each

	  	for (std::size_t x = 0; x<rhoLabels.size(); ++x )
	  	{
	  		e.addUserFloat("rho_"+rhoLabels[x],rhoValues[x]);

	  		float tempIso = IsoTool.electronEffAreaRhoRelIso(e, rhoValues[x],EffArea);
	  		e.addUserFloat("relativeIsol_"+rhoLabels[x],tempIso);


	  	}

	  	////////////////////////////
	  	// evaluate the electron's relIso

	  	double deltaBeta = 0.5;
	  	double relIso = IsoTool.electronRelIso(e,deltaBeta);

	  	e.addUserFloat("relativeIsol_DeltaBetaCorrectedRelIso",relIso);
	  	

	    ////////////////
	    // evaluate the cut based electron ID, and add some variables it needs

	    float ooEmooP = 999.0;   /* What is this? copied from online CMSSW examples */
	    if(e.ecalEnergy() == 0 || !std::isfinite(e.ecalEnergy()) ) ooEmooP = 1e30;
	    else
	    {
	    	ooEmooP = fabs(1.0/e.ecalEnergy() - e.eSuperClusterOverP()/e.ecalEnergy() );
	    }
	    e.addUserFloat("ooEmooP",ooEmooP);
	    e.addUserFloat("full5x5_sigmaIetaIeta",e.full5x5_sigmaIetaIeta());


	    /* last call because needs all addUserFloats filled */
	  	// not needed in 74X and higher
	    //float passCutBasedVetoID = passedCutBasedID(e);
	   	//e.addUserFloat("passCutBasedVetoID",passCutBasedVetoID);

	  	///////////////////////////
	  	clones[i] = e;

	  }	



}

  



