#ifndef DavisRunIITauTau_CustomPatCollectionProducers_LEPTONRELATIVEISOLATIONTOOL_h
#define DavisRunIITauTau_CustomPatCollectionProducers_LEPTONRELATIVEISOLATIONTOOL_h


/* for a pat::Electron or pat::Muon return isolation used by H->tau tau group */



// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"

//#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"


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


class LeptonRelativeIsolationTool
{

	public:
		LeptonRelativeIsolationTool();
		virtual ~LeptonRelativeIsolationTool();

		// deltaBeta corrected relative isolation
		double electronRelIso(const pat::Electron &, double deltaBeta);		
		double muonRelIso(const pat::Muon &, double deltaBeta);		
		double tauRelIso(const pat::Tau &, double deltaBeta);		

		// effective area & rho corrected isolations
		double electronEArhoRelIso(const pat::Electron &, double rho, float EA);
  


};

#endif
