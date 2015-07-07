// system include files
#include <memory>
#include <sstream>

// user include files

#include "DavisRunIITauTau/NtupleObjectProducers/interface/NtupleTriggerObjectHelper.h"

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

NtupleTriggerObjectHelper::NtupleTriggerObjectHelper(
                                edm::Handle<edm::TriggerResults> & triggerBits_,
                                edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects_,
                                edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales_,
                                const edm::TriggerNames &names_,
                                double electron_trigMatchDRcut_,
                                std::vector<int> electron_trigMatchTypes_,
                                std::vector<std::string> electron_trigSummaryPathsAndFilters_,
                                double muon_trigMatchDRcut_,
                                std::vector<int> muon_trigMatchTypes_,
                                std::vector<std::string> muon_trigSummaryPathsAndFilters_,
                                double tau_trigMatchDRcut_,
                                std::vector<int> tau_trigMatchTypes_,
                                std::vector<std::string> tau_trigSummaryPathsAndFilters_):
                                        triggerBits(triggerBits_),
                                        triggerObjects(triggerObjects_),
                                        triggerPreScales(triggerPreScales_),
                                        names(names_),
                                        electron_trigMatchDRcut(electron_trigMatchDRcut_),
                                        electron_trigMatchTypes(electron_trigMatchTypes_),
                                        electron_trigSummaryPathsAndFilters(electron_trigSummaryPathsAndFilters_),
                                        muon_trigMatchDRcut(muon_trigMatchDRcut_),
                                        muon_trigMatchTypes(muon_trigMatchTypes_),
                                        muon_trigSummaryPathsAndFilters(muon_trigSummaryPathsAndFilters_),
                                        tau_trigMatchDRcut(tau_trigMatchDRcut_),
                                        tau_trigMatchTypes(tau_trigMatchTypes_),
                                        tau_trigSummaryPathsAndFilters(tau_trigSummaryPathsAndFilters_)
                                        {}
        
// destructor 

NtupleTriggerObjectHelper::~NtupleTriggerObjectHelper(){}


std::vector <NtupleTrigObject> NtupleTriggerObjectHelper::getMatchedNtupleTrigObjectVector(NtupleLepton nl)
{

        std::vector <NtupleTrigObject> returnVec;

        /* local vars to hold lepton specific info */

        double DRmax_ = 0.5; /* this value is changed based on arguments and the lepton type below */
        std::vector<int> trigMatchTypes_;
        std::vector<std::string> trigSummaryPathsAndFilters_;
        TLorentzVector RecoObjVec_;
        RecoObjVec_.SetXYZT(nl.p4().X(),nl.p4().Y(),nl.p4().Z(),nl.p4().T());
        TLorentzVector TrigObjVec_; /* set in loop */
 

        /* fix local vars based on leptonType */

        if(nl.leptonType()==TupleLeptonTypes::anElectron)
        {
               // DRmax_  = electron_trigMatchDRcut;
                trigMatchTypes_ = electron_trigMatchTypes;
                trigSummaryPathsAndFilters_ = electron_trigSummaryPathsAndFilters;
        }
        else if(nl.leptonType()==TupleLeptonTypes::aMuon)
        {
               // DRmax_  = muon_trigMatchDRcut;
                trigMatchTypes_ = muon_trigMatchTypes;
                trigSummaryPathsAndFilters_ = muon_trigSummaryPathsAndFilters;
        }        
        else if(nl.leptonType()==TupleLeptonTypes::aTau)
        {
               // DRmax_  = tau_trigMatchDRcut; 
                trigMatchTypes_ = tau_trigMatchTypes;
                trigSummaryPathsAndFilters_ = tau_trigSummaryPathsAndFilters;
        }


        /* begin loop over the trigger objects and find all matches */

        for(std::size_t i = 0; i <(*triggerObjects).size(); ++i )
        {

                pat::TriggerObjectStandAlone obj = (*triggerObjects)[i];

                // check that the filterIDs contain at least one of the allowed types
                // for this reco object 

                bool objectIDtypeMatch = 0;

                for (std::size_t reco1 = 0; reco1 < trigMatchTypes_.size(); ++reco1)
                {
                        if(obj.hasTriggerObjectType(trigMatchTypes_[reco1])) objectIDtypeMatch = 1;
                }       

                if (!objectIDtypeMatch) continue;


                // check the DR between the reco and trigger objects
                TrigObjVec_.SetPtEtaPhiM(obj.pt(),obj.eta(),obj.phi(),obj.mass());

                float currentDR = TrigObjVec_.DeltaR(RecoObjVec_);
                if(currentDR > DRmax_) continue;

                /* have a match */
                std::cout<<"\n \n \n ";
                std::cout<<" -----> have a trigObj match of type/dr @ index "<<i<<" ";

                /* generate info needed to creat a NtupleTrigObject see NtupleTrigObject.h for meanings */

                LorentzVector nto_p4; nto_p4.SetXYZT(TrigObjVec_.X(),TrigObjVec_.Y(),TrigObjVec_.Z(),TrigObjVec_.T());
                std::vector <int> nto_triggerObjectTypes  = obj.filterIds(); /*  the trigger object type not a filter name */
                stringFloatPairVec HLTPath_isL3Pair;
                stringFloatPairVec HLTPath_isLFPair;
                stringFloatPairVec HLTPath_isBothPair;
                stringFloatPairVec HLTFiltersPair;                        


                std::cout<<" trig obj pt = "<<nto_p4.pt()<<" trig types = [ ";
                for(std::size_t x = 0; x<nto_triggerObjectTypes.size();++x)
                {
                        std::cout<<nto_triggerObjectTypes[x]<<" ";

                }
                std::cout<<" ] \n ";

                /* unpack trigger names for current object */
                obj.unpackPathNames(names);


                /* loop over accepted HLT paths */
                std::cout<<"            passed hlt paths = [ ";

                for (std::size_t p = 0; p<nl.HLTAcceptedPath_Labels().size(); ++p)
                {       std::string pathName = nl.HLTAcceptedPath_Labels().at(p);
                        std::cout<<" \n < "<<pathName<<"  ";
                        float isBoth = float(obj.hasPathName( pathName, true,  true )); 
                        float isL3   = float(obj.hasPathName( pathName, false, true )); 
                        float isLF   = float(obj.hasPathName( pathName, true, false )); 

                        std::cout<<" (isBoth,isL3,isLF) = ("<<isBoth<<","<<isL3<<","<<isLF<<") > ";

                        HLTPath_isBothPair.push_back(std::make_pair (pathName,isBoth));
                        HLTPath_isL3Pair.push_back(std::make_pair (pathName,isL3));
                        HLTPath_isLFPair.push_back(std::make_pair (pathName,isLF));



                }
                std::cout<<" \n ";

                //HLTFiltersPair
        
                /* loop over all filters that this trig object has */

                std::cout<<"            passed hlt filters = [ ";

                for (std::string fil : obj.filterLabels())
                {
                        if(obj.hasFilterLabel(fil)==1 && obj.filter(fil)==1)
                        {

                                std::cout<<fil<<" ";
                                HLTFiltersPair.push_back(std::make_pair(fil,1.0));                       

                        }
                }
                std::cout<<" ] \n ";

                /* finally create and call fillInfo for trigger object and push it back */
                
                NtupleTrigObject anNtupleTrigObject;
                
                anNtupleTrigObject.fillInfo(nto_p4,nto_triggerObjectTypes,
                                HLTPath_isL3Pair, HLTPath_isLFPair, HLTPath_isBothPair, HLTFiltersPair );

                returnVec.push_back(anNtupleTrigObject);

        }


        std::cout<<" have found "<<returnVec.size()<<" matched trigger objects \n";


        return returnVec;
}

