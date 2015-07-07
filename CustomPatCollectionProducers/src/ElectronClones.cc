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
				EGammaMvaEleEstimatorCSA14 & MVA_PHYS14nonTrig_, 
				std::string & MVA_PHYS14nonTrig_NAME_,
				edm::Handle<edm::TriggerResults> & triggerBits_,
				edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects_,
				edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales_,
				const edm::TriggerNames &names_,				
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
		rhoLabels(rhoLabels_),
		rhoValues(rhoValues_)
		{

		 clone();
		 fillUserFloats();		  

		}

// destructor 

electronClones::~electronClones(){ clones.clear();}


// pass-fail phys 14 MVA 
// return a pass/fail based on MVA score, pt, and absSuperClusterEta */

float electronClones::passedPhys14MVA(float MVAOUT, float PT, float ABS_SUPERCLUSTER_ETA)
{
	float returnVal = 0.0;
	float ABSETA  = fabs(ABS_SUPERCLUSTER_ETA); // always ensure abs


	// low-pt
	if(PT <= 10.0)
	{

		if(ABSETA < 0.8 && MVAOUT > -0.202) return 1.0;
		else if(ABSETA >= 0.8 && ABSETA<1.479 && MVAOUT > -0.444) return 1.0;
		else if(ABSETA >= 1.479 && MVAOUT >  0.264) return 1.0;

	}


	// high-pt
	else if(PT>10.0)
	{

		if(ABSETA < 0.8 && MVAOUT > -0.110 ) return 1.0;
		else if(ABSETA >= 0.8 && ABSETA<1.479 && MVAOUT > -0.284) return 1.0;
		else if(ABSETA >= 1.479 && MVAOUT > -0.212) return 1.0;



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
		  	numberOfMissingInnerHits = e.gsfTrack()->hitPattern().numberOfHits(HitPattern::MISSING_INNER_HITS);
			numberOfMissingOuterHits = e.gsfTrack()->hitPattern().numberOfHits(HitPattern::MISSING_OUTER_HITS);
			numberOfTrackHits = e.gsfTrack()->hitPattern().numberOfHits(HitPattern::TRACK_HITS);
	
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

	  	e.addUserFloat("chargedHadronIso", e.chargedHadronIso());
		e.addUserFloat("neutralHadronIso", e.neutralHadronIso());
		e.addUserFloat("photonIso", e.photonIso());
		e.addUserFloat("PUchargedHadronIso",  e.puChargedHadronIso());



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


	  	///////////////////////////
	  	// evaluate and add the mva IDs 

	  	float mva_val = MVA_PHYS14nonTrig.mvaValue(e,false);
	    e.addUserFloat(MVA_PHYS14nonTrig_NAME,mva_val);

	  	///////////////////////////
	    // once ready add the pass/fail based on the mva

	    float passMVA14 = passedPhys14MVA(mva_val, e.pt(), absSuperClusterEta);
	    e.addUserFloat("PASS_"+MVA_PHYS14nonTrig_NAME,passMVA14);


	  	///////////////////////////
	  	clones[i] = e;

	  }	



}

  



