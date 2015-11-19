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

muonClones::muonClones(const slimmedPatMuonCollection& inputColl, const reco::Vertex & input_vertex,
				edm::Handle<edm::TriggerResults> & triggerBits_,
				edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects_,
				edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales_,
				const edm::TriggerNames &names_,			
				std::vector<std::string> rhoLabels_,
				std::vector<double> rhoValues_):
		muons(inputColl),
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


	TriggerInfoEmbeddingTool triggerEmbedderTool(triggerBits,triggerObjects,triggerPreScales,names);



	for (std::size_t i=0; i<clones.size(); i++)
	  {
	  	pat::Muon m = clones[i];


	  	///////////
	  	// check some muon ID standards


	  	m.addUserFloat("isGlobalMuon",m.isGlobalMuon());
	  	m.addUserFloat("isTrackerMuon",m.isTrackerMuon());
	  	m.addUserFloat("isPFMuon",m.isPFMuon());
	  	m.addUserFloat("isLooseMuon",m.isLooseMuon());
	  	m.addUserFloat("isSoftMuon",m.isSoftMuon(first_vertex));
	  	m.addUserFloat("isTightMuon",m.isTightMuon(first_vertex));


	  	//////////////
	  	// some additional muon ID quantities &
	  	// muon ID summary variables

	  	float isGoodGlobalMuon = 0.0;
	  	float passesMediumMuonId = 0.0;



	  	if(m.globalTrack().isNonnull())
	  	{
		  	m.addUserFloat("muonGlobalTrackNormChi2",m.globalTrack()->normalizedChi2());

  		  	if(m.isGlobalMuon() 
				&& m.globalTrack()->normalizedChi2()<3. 
			  	&& m.combinedQuality().chi2LocalPosition < 12.
			  	&& m.combinedQuality().trkKink   <   20.) { isGoodGlobalMuon = 1.0; }



	  	}
	  	else m.addUserFloat("muonGlobalTrackNormChi2",NAN);


	  	if(m.innerTrack().isNonnull())
	  	{
		  	m.addUserFloat("muonInnerTrkValidFraction",m.innerTrack()->validFraction());

		  	
		  	if(m.innerTrack()->validFraction() >= 0.8 
	  		&& m.segmentCompatibility()   >=   (isGoodGlobalMuon   ? 0.303 : 0.451)) passesMediumMuonId = 1.0;


	  	}
		else m.addUserFloat("muonInnerTrkValidFraction",NAN);


	  	m.addUserFloat("muonCombQualChi2LocalPosition",m.combinedQuality().chi2LocalPosition);
	  	m.addUserFloat("muonCombQualTrkKink",m.combinedQuality().trkKink);
	  	m.addUserFloat("muonSegmentCompatibility",m.segmentCompatibility());


	  	m.addUserFloat("isGoodGlobalMuon",isGoodGlobalMuon);
		
	  	/* new for 7-4-7 simple access via isMediumMuon */

	  	passesMediumMuonId = m.isMediumMuon();

		m.addUserFloat("passesMediumMuonId",passesMediumMuonId);
	  


		/////////////
	  	// trigger info

	  	std::vector <std::string> userFloatNames;
	  	std::vector <float> userFloatVals;

	  	triggerEmbedderTool.fillAcceptedPathsAndPrescales(userFloatNames, userFloatVals); 


	  	for (std::size_t a = 0; a< userFloatNames.size(); ++a )
	  	{
		  	m.addUserFloat(userFloatNames[a],userFloatVals[a]);
	  	}


	  	///////////////////////////
	  	// dxy and dz

  		float dxy = 999.0;
		float dz = 999.0;

		// worried that we need a innerTrack check here?
		//assert(m.innerTrack().isNonnull());


		if (m.muonBestTrack().isNonnull())
		{
		  	dxy = m.muonBestTrack()->dxy(first_vertex.position());
	  		dz = m.muonBestTrack()->dz(first_vertex.position());
		}


	  	m.addUserFloat("dxy",dxy);
	  	m.addUserFloat("dz",dz);



	  	// compute the muons' effective area 
	  	// for now hardcode to 2012 settings eventually need
	  	// this to be drawn from a config file


  		float EffArea = MuonEffectiveArea::GetMuonEffectiveArea(
  						MuonEffectiveArea::kMuGammaAndNeutralHadronIso04,
					    fabs(m.eta()), MuonEffectiveArea::kMuEAData2012);


	  	m.addUserFloat("EffectiveArea",EffArea);


		///////////////////////////
	  	// IP, IPerror, note : SIP = IP/fabs(IPerror) is the useful quantity

		m.addUserFloat("IP",fabs(m.dB(pat::Muon::PV3D)));
		m.addUserFloat("IPerror",(m.edB(pat::Muon::PV3D)));


		//////////////////////////
		// DepositR03TrackerOfficial, DepositR03ECal, DepositR03Hcal

	    m.addUserFloat("DepositR03TrackerOfficial",m.isolationR03().sumPt);
	    m.addUserFloat("DepositR03ECal",m.isolationR03().emEt);
	    m.addUserFloat("DepositR03Hcal",m.isolationR03().hadEt);


	  	// iso tool 
	  	LeptonRelativeIsolationTool IsoTool;


	  	// iso-related quantities

		double chargedHadron = m.pfIsolationR03().sumChargedHadronPt;
		double neutralHadron = m.pfIsolationR03().sumNeutralHadronEt;
		double photonIso = m.pfIsolationR03().sumPhotonEt;
		double PUchargedHadron = m.pfIsolationR03().sumPUPt;

	  	m.addUserFloat("chargedHadronIso", chargedHadron);
		m.addUserFloat("neutralHadronIso", neutralHadron);
		m.addUserFloat("photonIso", photonIso);
		m.addUserFloat("PUchargedHadronIso",  PUchargedHadron);



	  	// push in the rho variants, and the relative isol based on
	  	// each

	  	for (std::size_t x = 0; x<rhoLabels.size(); ++x )
	  	{
	  		m.addUserFloat("rho_"+rhoLabels[x],rhoValues[x]);

	  		float tempIso = IsoTool.muonEffAreaRhoRelIso(m, rhoValues[x],EffArea);
	  		m.addUserFloat("relativeIsol_"+rhoLabels[x],tempIso);


	  	}


	  	////////////////////////////
	  	// evaluate the muon's relIso

	  	double deltaBeta = 0.5;
	  	double relIso = IsoTool.muonRelIso(m,deltaBeta);

	  	m.addUserFloat("relativeIsol_DeltaBetaCorrectedRelIso",relIso);


	  	///////////////////////////
	  	clones[i] = m;

	  }	



}

  



