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





std::vector<std::pair<std::string, float> > NtupleTriggerObjectHelper::isNtupleLeptonGoodForHLTPath(
                                            NtupleLepton nl)
{

    bool verbose = 0; 
    
    std::vector<std::pair<std::string, float> > returnPairVec;


    /* 1st get all the matched trigger objects and filters on all accepted paths */

    std::vector <NtupleTrigObject> trigObjMatches = getMatchedNtupleTrigObjectVector(nl);


    /* next decode the trigSummaryPathsAndFilters variables */

    std::vector<std::string> trigSummaryPathsAndFilters_;

    if(nl.leptonType()==TupleLeptonTypes::anElectron)
    {           
            trigSummaryPathsAndFilters_ = electron_trigSummaryPathsAndFilters;
    }
    else if(nl.leptonType()==TupleLeptonTypes::aMuon)
    {
            trigSummaryPathsAndFilters_ = muon_trigSummaryPathsAndFilters;
    }        
    else if(nl.leptonType()==TupleLeptonTypes::aTau)
    {          
            trigSummaryPathsAndFilters_ = tau_trigSummaryPathsAndFilters;
    }

    for (std::string pathFilterString : trigSummaryPathsAndFilters_)
    {

        if(verbose) std::cout<<" == SUMMARY FOR "<<pathFilterString<<" == \n";

        std::istringstream ss(pathFilterString);
        std::string dummy; /* becuase we use -- and not - */

        std::string pathName;
        std::getline(ss, pathName, '-'); std::getline(ss, dummy, '-');


        std::string andOrName;
        std::getline(ss, andOrName, '-'); std::getline(ss, dummy, '-');

        std::string buf;
        std::vector<std::string> filterNames;


        while(std::getline(ss, buf, '-'))
        {
            filterNames.push_back(buf);
            std::getline(ss, dummy, '-');
        }

        if(verbose) std::cout<<" ---------> pathName =  "<<pathName<<" \n";
        if(verbose) std::cout<<" ---------> andOrName =  "<<andOrName<<" \n";
        if(verbose) std::cout<<" ---------> checking   "<<filterNames.size()<<" filters \n";

     
        /* now check 3 conditions on isNtupleLeptonGoodForHLTPath */

        int condition1 = 0; /* path accepted */
        int condition2 = 0; /* a trigger object DR match */
        int condition3 = 0; /* filters meet conditions in trigSummaryPathsAndFilters_ */


        /* condition1 ---- checking wasAccept */


        if(nl.HLTpath(pathName)>0.0) condition1 = 1; /* > 0 allows for prescale values */

        /* condition2 ---- checking for any trigger object matches */

        if(trigObjMatches.size()!=0) condition2 = 1;

 
        /* condition 3 -- check the and or or of the filters */

        int FilterPassSum = 0;

        /* need to loop on all matched trigger objects to check total filters passed */

        for(std::size_t tIndx = 0; tIndx < trigObjMatches.size(); ++tIndx)
        {
            for(std::string givenfil : filterNames)
            {
                if(trigObjMatches[tIndx].HLTFilter(givenfil)==1.0)
                {
                   FilterPassSum++;     
                   if(verbose) std::cout<<" --------------------> trigObj # "<<tIndx<<" passes filter "<<givenfil<<"\n";
                }
            }


        }





        /* no filters provided by user */ 
        if(filterNames.size()==0) condition3 = 1;

        /* all filters passed */ 
        else if(andOrName=="AND" && FilterPassSum>=int(filterNames.size()))
        {
            condition3 = 1;
        }

        /* at least one filter passed */ 
        else if(andOrName=="OR" && FilterPassSum!=0)
        {
            condition3 = 1;
        }

        if(verbose) std::cout<<" ---------> condition1 = "<<condition1<<" ";
        if(verbose) std::cout<<" condition2 = "<<condition2<<" ";
        if(verbose) std::cout<<" condition3 = "<<condition3<<" \n";
        if(verbose) std::cout<<" ---------> for path "<<pathName<<" FINAL="<<condition1+condition2+condition3<<" for reco lepton type "<<nl.leptonType()<<"\n";
        if(verbose) std::cout<<"\n";

        // push back the result only if all 3 conditions passed with a 1.0, or 0 if any failed

        float allThreeCond = 0.0;
        if(condition1+condition2+condition3==3) allThreeCond = 1.0;


            
        returnPairVec.push_back(std::make_pair(pathName,allThreeCond));

        /* in case the original did not have a version wildcard add that in too */
        if(pathName.find('*')==std::string::npos) 
        {
            std::string wildCardVersion = pathName;
            wildCardVersion.erase(wildCardVersion.find("_v"),wildCardVersion.length());

            returnPairVec.push_back(std::make_pair(wildCardVersion,allThreeCond));

        }    
        


    }

    if(verbose) std::cout<<" all paths "<<returnPairVec.size()<<"\n";

    return returnPairVec;
}



std::vector <NtupleTrigObject> NtupleTriggerObjectHelper::getMatchedNtupleTrigObjectVector(NtupleLepton nl)
{
        bool verbose = 0; 
        std::vector <NtupleTrigObject> returnVec;

        /* local vars to hold lepton specific info */

        double DRmax_ = 0.5; /* this value is changed based on arguments and the lepton type below */
        std::vector<int> trigMatchTypes_;
        //std::vector<std::string> trigSummaryPathsAndFilters_;
        TLorentzVector RecoObjVec_;
        RecoObjVec_.SetXYZT(nl.p4().X(),nl.p4().Y(),nl.p4().Z(),nl.p4().T());
        TLorentzVector TrigObjVec_; /* set in loop */
 

        /* fix local vars based on leptonType */

        if(nl.leptonType()==TupleLeptonTypes::anElectron)
        {
               // DRmax_  = electron_trigMatchDRcut;
                trigMatchTypes_ = electron_trigMatchTypes;
                //trigSummaryPathsAndFilters_ = electron_trigSummaryPathsAndFilters;
        }
        else if(nl.leptonType()==TupleLeptonTypes::aMuon)
        {
               // DRmax_  = muon_trigMatchDRcut;
                trigMatchTypes_ = muon_trigMatchTypes;
                //trigSummaryPathsAndFilters_ = muon_trigSummaryPathsAndFilters;
        }        
        else if(nl.leptonType()==TupleLeptonTypes::aTau)
        {
               // DRmax_  = tau_trigMatchDRcut; 
                trigMatchTypes_ = tau_trigMatchTypes;
                //trigSummaryPathsAndFilters_ = tau_trigSummaryPathsAndFilters;
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
                if(verbose) std::cout<<"\n \n \n ";
                if(verbose) std::cout<<" -----> have a trigObj match of type/dr @ index "<<i<<" ";

                /* generate info needed to creat a NtupleTrigObject see NtupleTrigObject.h for meanings */

                LorentzVector nto_p4; nto_p4.SetXYZT(TrigObjVec_.X(),TrigObjVec_.Y(),TrigObjVec_.Z(),TrigObjVec_.T());
                std::vector <int> nto_triggerObjectTypes  = obj.filterIds(); /*  the trigger object type not a filter name */
                stringFloatPairVec HLTPath_isL3Pair;
                stringFloatPairVec HLTPath_isLFPair;
                stringFloatPairVec HLTPath_isBothPair;
                stringFloatPairVec HLTFiltersPair;                        


                if(verbose) std::cout<<" trig obj pt = "<<nto_p4.pt()<<" trig types = [ ";
                for(std::size_t x = 0; x<nto_triggerObjectTypes.size();++x)
                {
                       if(verbose)  std::cout<<nto_triggerObjectTypes[x]<<" ";

                }
                if(verbose) std::cout<<" ] \n ";

                /* unpack trigger names for current object */
                obj.unpackPathNames(names);


                /* loop over accepted HLT paths */
                if(verbose) std::cout<<"            passed hlt paths = [ ";

                for (std::size_t p = 0; p<nl.HLTAcceptedPath_Labels().size(); ++p)
                {       std::string pathName = nl.HLTAcceptedPath_Labels().at(p);
                        if(verbose) std::cout<<" \n < "<<pathName<<"  ";
                        float isBoth = float(obj.hasPathName( pathName, true,  true )); 
                        float isL3   = float(obj.hasPathName( pathName, false, true )); 
                        float isLF   = float(obj.hasPathName( pathName, true, false )); 

                        if(verbose) std::cout<<" (isBoth,isL3,isLF) = ("<<isBoth<<","<<isL3<<","<<isLF<<") > ";

                        HLTPath_isBothPair.push_back(std::make_pair (pathName,isBoth));
                        HLTPath_isL3Pair.push_back(std::make_pair (pathName,isL3));
                        HLTPath_isLFPair.push_back(std::make_pair (pathName,isLF));



                }
                if(verbose) std::cout<<" \n ";

                //HLTFiltersPair
        
                /* loop over all filters that this trig object has */

                if(verbose) std::cout<<"            passed hlt filters = [ ";

                for (std::string fil : obj.filterLabels())
                {
                        if(obj.hasFilterLabel(fil)==1 && obj.filter(fil)==1)
                        {

                                if(verbose) std::cout<<fil<<" ";
                                HLTFiltersPair.push_back(std::make_pair(fil,1.0));                       

                        }
                }
                if(verbose) std::cout<<" ] \n ";

                /* finally create and call fillInfo for trigger object and push it back */
                
                NtupleTrigObject anNtupleTrigObject;
                
                anNtupleTrigObject.fillInfo(nto_p4,nto_triggerObjectTypes,
                                HLTPath_isL3Pair, HLTPath_isLFPair, HLTPath_isBothPair, HLTFiltersPair );

                returnVec.push_back(anNtupleTrigObject);

        }


        if(verbose) std::cout<<" have found "<<returnVec.size()<<" matched trigger objects \n";


        return returnVec;
}

