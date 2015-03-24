/* for a pat::Electron or pat::Muon return isolation used by H->tau tau group */


// system include files
#include <memory>

// user include files

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




// constructor 

LeptonRelativeIsolationTool::LeptonRelativeIsolationTool(){}
	
// destructor 

LeptonRelativeIsolationTool::~LeptonRelativeIsolationTool(){}


// electron relIso

double LeptonRelativeIsolationTool::electronRelIso(const pat::Electron & e, double deltaBeta)
{
	double ReturnVal = 999.0;
	double PT = e.p4().Pt();
	if (PT == 0) {return ReturnVal;}

	// should be careful to add FSR correction if recommended in the future

	// these are taken as is from mini-AOD slimmedElectrons

	double chargedHadron = e.chargedHadronIso();
	double neutralHadron = e.neutralHadronIso();
	double photonIso = e.photonIso();
	double PUchargedHadron = e.puChargedHadronIso();


	ReturnVal = chargedHadron + std::max(0.0, neutralHadron + photonIso -  deltaBeta * PUchargedHadron  );
	ReturnVal = ReturnVal/PT;
	return ReturnVal;

}	




// muon relIso

double LeptonRelativeIsolationTool::muonRelIso(const pat::Muon & m, double deltaBeta)
{
	double ReturnVal = 999.0;
	double PT = m.p4().Pt();
	if (PT == 0) {return ReturnVal;}


	// these are taken as is from mini-AOD slimmedMuons
	double chargedHadron = m.chargedHadronIso();
	double neutralHadron = m.neutralHadronIso();
	double photonIso = m.photonIso();
	double PUchargedHadron = m.puChargedHadronIso();

	// should be careful to add FSR correction if recommended in the future


	ReturnVal = chargedHadron + std::max(0.0, neutralHadron + photonIso -  deltaBeta * PUchargedHadron  );


	ReturnVal = ReturnVal/PT;
	return ReturnVal;

}	




// tau relIso

double LeptonRelativeIsolationTool::tauRelIso(const pat::Tau & t, double deltaBeta)
{
	double ReturnVal = 999.0;
	double PT = t.p4().Pt();
	if (PT == 0) {return ReturnVal;}


	// these are taken as is from mini-AOD slimmedMuons
	double chargedHadron = t.chargedHadronIso();
	double neutralHadron = t.neutralHadronIso();
	double photonIso = t.photonIso();
	double PUchargedHadron = t.puChargedHadronIso();

	// should be careful to add FSR correction if recommended in the future


	ReturnVal = chargedHadron + std::max(0.0, neutralHadron + photonIso -  deltaBeta * PUchargedHadron  );


	ReturnVal = ReturnVal/PT;
	return ReturnVal;

}	


