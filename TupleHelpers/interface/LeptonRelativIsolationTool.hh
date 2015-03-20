/* for a pat::Electron or pat::Muon return isolation used by H->tau tau group */


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

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


class LeptonRelativIsolationTool
{

	public:
		LeptonRelativIsolationTool();
		virtual ~LeptonRelativIsolationTool();

		// deltaBeta corrected relative isolation
		double electronRelIso(const pat::Electron &, double deltaBeta);		
		//double muonRelIso();		

  


};


// constructor 

LeptonRelativIsolationTool::LeptonRelativIsolationTool(){}
	
// destructor 

LeptonRelativIsolationTool::~LeptonRelativIsolationTool(){}


// electron relIso

double LeptonRelativIsolationTool::electronRelIso(const pat::Electron & e, double deltaBeta)
{
	double ReturnVal = 999.0;
	double PT = e.p4().Pt();
	if (PT == 0) {return ReturnVal;}


	// these are taken as is from mini-AOD slimmedElectrons
	double chargedHadron = e.chargedHadronIso();
	double totalNeutral = e.neutralHadronIso()+ e.photonIso();

	ReturnVal = chargedHadron + max(0.0, totalNeutral -  deltaBeta * chargedHadron  );
	ReturnVal = ReturnVal/PT;
	return ReturnVal;

}	





  



