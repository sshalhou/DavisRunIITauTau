/* for an NtupleLepton populate trigger object matches & filter information */

#ifndef DavisRunIITauTau_NtupleObjectProducers_NtupleTriggerObjectHelper_h
#define DavisRunIITauTau_NtupleObjectProducers_NtupleTriggerObjectHelper_h


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

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleTrigObject.h"

#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"


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


class NtupleTriggerObjectHelper
{
	 // trigger related collections

        edm::Handle<edm::TriggerResults> & triggerBits;   
        edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects;
        edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales;
        const edm::TriggerNames & names;
        
        double electron_trigMatchDRcut;
        std::vector<int> electron_trigMatchTypes;
        std::vector<std::string> electron_trigSummaryPathsAndFilters;

        double muon_trigMatchDRcut;
        std::vector<int> muon_trigMatchTypes;
        std::vector<std::string> muon_trigSummaryPathsAndFilters;

        double tau_trigMatchDRcut;
        std::vector<int> tau_trigMatchTypes;
        std::vector<std::string> tau_trigSummaryPathsAndFilters;


	public:
        NtupleTriggerObjectHelper(edm::Handle<edm::TriggerResults> &,
                        edm::Handle<pat::TriggerObjectStandAloneCollection> &,
                        edm::Handle<pat::PackedTriggerPrescales>&,
                        const edm::TriggerNames &,
                        double, std::vector<int>, std::vector<std::string>,
                        double, std::vector<int>, std::vector<std::string>,
                        double, std::vector<int>, std::vector<std::string>);

        virtual ~NtupleTriggerObjectHelper();

        /* return a vector of matched Ntuple Trigger Objects given an NtupleLepton */
       
        std::vector <NtupleTrigObject> getMatchedNtupleTrigObjectVector(NtupleLepton);


        /* for a given NtupleLepton return std::vector of std::pair(HLTpath, X) where
        X = (HLT wasAccept && trigObject was matched && all Filters met) 
        based on summary config in ConfigTupleTriggers_cfi.py */

        std::vector<std::pair<std::string, float> > isNtupleLeptonGoodForHLTPath(NtupleLepton);

};


#endif


