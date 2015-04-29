/* for a pat::Electron, Muon or Tau collection embed trigger info as UserFloats */


// system include files
#include <memory>
#include <sstream>

// user include files

#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/TriggerInfoEmbeddingTool.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"

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

TriggerInfoEmbeddingTool::TriggerInfoEmbeddingTool(
				edm::Handle<edm::TriggerResults> & triggerBits_,
				edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects_,
				edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales_,
				const edm::TriggerNames &names_,
				double trigMatchDRcut_,
				std::vector<int> trigMatchTypes_,
				std::vector<std::string> trigSummaryPathsAndFilters_):
					triggerBits(triggerBits_),
					triggerObjects(triggerObjects_),
					triggerPreScales(triggerPreScales_),
					names(names_),
					trigMatchDRcut(trigMatchDRcut_),
					trigMatchTypes(trigMatchTypes_),
					trigSummaryPathsAndFilters(trigSummaryPathsAndFilters_)
					{}
	
// destructor 

TriggerInfoEmbeddingTool::~TriggerInfoEmbeddingTool(){}


// helpers 

bool TriggerInfoEmbeddingTool::wasAnyPathAccepted(std::vector<std::string> & pathNamesToFill, 
	std::vector<float> & pathPrescalesToFill)
	{
			for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) 
			{
				if(triggerBits->accept(i)) 
				{

					if(names.triggerName(i).find("HLT_")==0)
					{
						pathNamesToFill.push_back("AcceptWithPreScale_"+names.triggerName(i));
						pathPrescalesToFill.push_back(triggerPreScales->getPrescaleForIndex(i));
					}
				}
			}

	if (pathNamesToFill.size()>0) return 1;
	return 0;
	}

	void TriggerInfoEmbeddingTool::fillTrigFilterInfo(std::size_t index, std::vector<std::string> & fillStrings, std::vector<float> & fillFloats, 
		std::string prefix, std::vector<std::string> & runningFilterList)
	{

		pat::TriggerObjectStandAlone obj = (*triggerObjects)[index];

		//obj.unpackPathNames(names);

		for (std::string fil : obj.filterLabels())
		{
			if(obj.hasFilterLabel(fil)==1 && obj.filter(fil)==1)
			{
				fillStrings.push_back(prefix+"trigObjectFilter_"+fil);
				fillFloats.push_back(1.0);
				runningFilterList.push_back(fil);

			}
		}

	}		


	void TriggerInfoEmbeddingTool::TrigSummaryInfoHelper(TLorentzVector RecoObjVec, std::vector<std::string> & userFloatNames, std::vector<float> & userFloatValues)
	{

	 	
	 	// first get the kinematic info and all filters for
	 	// the best matched HLT L3 object and best L1 obj

	 	// L3 & L1 trigger object types allowed
	 	std::vector<int> allowedL3TrigObjectTypes;
	 	std::vector<int> allowedL1TrigObjectTypes;

	 	// master list of L1+L3 best match objects's filters :
	 	std::vector<std::string> L1plusL3FilterList;

 		for (int type : trigMatchTypes) 
 		{
 			if (type > 0) allowedL3TrigObjectTypes.push_back(type);
 			else allowedL1TrigObjectTypes.push_back(type);

 		}

 		std::size_t bestL3MatchIndex = getBestMatchedObject(RecoObjVec, allowedL3TrigObjectTypes,trigMatchDRcut);
 		std::size_t bestL1MatchIndex = getBestMatchedObject(RecoObjVec, allowedL1TrigObjectTypes,trigMatchDRcut);

		if(bestL1MatchIndex!=9999) 
 		{
 			fillTrigObjKinematics(bestL1MatchIndex, userFloatNames, userFloatValues,"L1Obj_");
		 	fillTrigFilterInfo(bestL1MatchIndex, userFloatNames, userFloatValues,"L1Obj_",L1plusL3FilterList);
	 	}

		if(bestL3MatchIndex!=9999) 
 		{
 			fillTrigObjKinematics(bestL3MatchIndex, userFloatNames, userFloatValues,"L3Obj_");
		 	fillTrigFilterInfo(bestL3MatchIndex, userFloatNames, userFloatValues,"L3Obj_",L1plusL3FilterList);
		 	fillTrigSummaryInfo(bestL3MatchIndex, userFloatNames, userFloatValues,L1plusL3FilterList);

	 	}



	 	// std::cout<<" tau L1 + L3 filters ";
	 	// for (std::string f : L1plusL3FilterList) std::cout<<f<<" ";
	 	// std::cout<<"\n";


	}


	void TriggerInfoEmbeddingTool::fillTrigSummaryInfo(std::size_t index, std::vector<std::string> & fillStrings, std::vector<float> & fillFloats,
														std::vector<std::string> combinedPassedL1andL3filters)
	{

		pat::TriggerObjectStandAlone obj = (*triggerObjects)[index];

		obj.unpackPathNames(names);
		std::vector<std::string> pathNamesAll  = obj.pathNames(false);
		//std::vector<std::string> pathNamesLast = obj.pathNames(true);
		
		for (std::string pathFilterString : trigSummaryPathsAndFilters)
		{
			//std::cout<<pathFilterString<<"\n";

			std::istringstream ss(pathFilterString);

			std::string dummy; /* becuase we use -- and not - */

			std::string variableName;
			std::getline(ss, variableName, '-'); std::getline(ss, dummy, '-');

			std::string pathName;
			std::getline(ss, pathName, '-'); std::getline(ss, dummy, '-');

			std::string andOrName;
			std::getline(ss, andOrName, '-'); std::getline(ss, dummy, '-');

			std::string buf;
			std::vector<std::string> filterNames;
			int FilterPassSum = 0;

			//std::vector<int> passed_correspondingFilter;

			while(std::getline(ss, buf, '-'))
			{
				filterNames.push_back(buf);
				std::getline(ss, dummy, '-');

			}

			// std::cout<<"----------\n";
			// std::cout<<" variableName: "<<variableName<<"\n";
			// std::cout<<" pathName: "<<pathName<<"\n";
			// std::cout<<" andOrName: "<<andOrName<<"\n";
			// std::cout<<"FilterNames : ";
			// for(std::string f : filterNames) std::cout<<f<<" ";
			// std::cout<<"\n";
			// std::cout<<"----------\n";


			/* following the HLT tutorial : 
			for each path record also if the object is associated 
			to a 'l3' filter (always true for the definition used in the PAT trigger producer) 
			and if it's associated to the last filter of a successfull path 
			(which means that this object did cause this trigger to succeed;
			however, it doesn't work on some multi-object triggers)
			
			see : https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATTrigger#TriggerObjectStandAlone
			
			bool hasPathName( const std::string& pathName, bool pathLastFilterAccepted = false, 
			bool pathL3FilterAccepted = true ) and
			
			bool path( const std::string& pathName, unsigned pathLastFilterAccepted = 0, 
			unsigned pathL3FilterAccepted = 1 ) ( ** ):
			
			checks, if a certain trigger path name is assigned to the 
			stand-alone trigger object with the optional parameters indicating, 
			if the trigger object should have been used in the final filter ( pathLastFilterAccepted ) 
			resp. in an L3 filter ( pathL3FilterAccepted ) and the path was succeeding;


			 bool hasFilterLabel( const std::string& filterLabel ) and
			 bool filter( const std::string& filterLabel ) ( ** ):
			 checks, if a certain HLT filter label is assigned to the stand-alone trigger object; 
			 (**) -1 not run, 0 failed, 1 passed

			 */

			// check if the object has the current HLT path : 
			// either passing a L3 filter on this path or
			// passing the last filter in the path

            int isBoth = obj.hasPathName( pathName, true, true ); 
            int isL3   = obj.hasPathName( pathName, false, true ); 
            int isLF   = obj.hasPathName( pathName, true, false ); 

			// check if the object passes the actual 
			// filters specified using AND or OR condition
            // the passed filters based on best matched L3 and L1 objects are 
            // in combinedPassedL1andL3filters

            for(std::string givenfil : filterNames)
            {
				for(std::string passedfil : combinedPassedL1andL3filters)
				{
					if (givenfil == passedfil) FilterPassSum++;
				}

            }


            int FilterListPassed = 0;

			/* no filters provided by user */ 
            if(filterNames.size()==0) 
            {
            	FilterListPassed = 1;

            }

			/* all filters passed */ 
			else if(andOrName=="AND" && FilterPassSum==int(filterNames.size()))
			{
				FilterListPassed = 1;
			}

			/* at least one filter passed */ 
			else if(andOrName=="OR" && FilterPassSum!=0)
			{
				FilterListPassed = 1;
			}






   			// store info

			fillStrings.push_back(variableName+"_isBOTH");
			fillFloats.push_back(isBoth);	

			fillStrings.push_back(variableName+"_isL3");
			fillFloats.push_back(isL3);	

			fillStrings.push_back(variableName+"_isLF");
			fillFloats.push_back(isLF);	

			fillStrings.push_back(variableName+"_filterListPassed");
			fillFloats.push_back(FilterListPassed);	

   //          std::cout<<"testing "<<pathName<<" ";
   //          std::cout<<" passed L1 + L3 filters ";
	 	// 	for (std::string f : combinedPassedL1andL3filters) std::cout<<f<<" ";
   //          std::cout<<"isBoth="<<isBoth<<" ";
   //          std::cout<<"isL3="<<isL3<<" ";
   //          std::cout<<"isLF="<<isLF<<" ";
   //          std::cout<<"FilterListPassed="<<FilterListPassed<<" ---> ";
			// std::cout<<"finalValue="<<finalValue<<" ";
			// std::cout<<"\n";		


		}


	}



	void TriggerInfoEmbeddingTool::fillTrigObjInfo(std::size_t index, std::vector<std::string> & fillStrings, std::vector<float> & fillFloats)
	{

		//pat::TriggerObjectStandAlone obj = (*triggerObjects)[index];
		
	}


	void TriggerInfoEmbeddingTool::fillTrigObjKinematics(std::size_t index, std::vector<std::string> & fillStrings, std::vector<float> & fillFloats, std::string prefix)
	{

		pat::TriggerObjectStandAlone obj = (*triggerObjects)[index];
		
		/* DR */
		fillStrings.push_back(prefix+"TrigObjRecoObjDeltaR"); 
		fillFloats.push_back(bestMatchDR_);

		/* pt, eta, phi, mass */

		fillStrings.push_back(prefix+"TrigObjPt"); 
		fillFloats.push_back(obj.pt());

		fillStrings.push_back(prefix+"TrigObjEta"); 
		fillFloats.push_back(obj.eta());

		fillStrings.push_back(prefix+"TrigObjPhi"); 
		fillFloats.push_back(obj.phi());

		fillStrings.push_back(prefix+"TrigObjMass"); 
		fillFloats.push_back(obj.mass());




	}


	std::size_t TriggerInfoEmbeddingTool::getBestMatchedObject(
				TLorentzVector RecoObjVec, std::vector<int> & AllowedTypes, float DRcut)
	{

		TLorentzVector TrigObjVec;
		std::size_t returnIndex = 9999;
		float minDR = 9999.99;

		for(std::size_t i = 0; i <(*triggerObjects).size(); ++i )
 		{

 			pat::TriggerObjectStandAlone obj = (*triggerObjects)[i];



			// check that the filterIDs contain at least one of the allowed types
			// for this reco object 

			bool objectIDtypeMatch = 0;

			for (std::size_t reco1 = 0; reco1 < AllowedTypes.size(); ++reco1)
			{
				for (std::size_t trig1 = 0; trig1 < obj.filterIds().size(); ++trig1)
				{

					if ((obj.filterIds()[trig1]) == (AllowedTypes[reco1])) 
					{
						objectIDtypeMatch = 1;
					}
				}

			}				

			if (!objectIDtypeMatch) continue;


			// check the DR between the reco and trigger objects
			TrigObjVec.SetPtEtaPhiM(obj.pt(),obj.eta(),obj.phi(),obj.mass());

			float currentDR = TrigObjVec.DeltaR(RecoObjVec);
			if(currentDR > DRcut) continue;

			// check if smallest DR
			if( currentDR < minDR )
			{
				minDR = currentDR;
				returnIndex = i;
			}

 		}

 		bestMatchDR_ = minDR;
 		return returnIndex;
 	}




	


void TriggerInfoEmbeddingTool::getTriggerInfo(pat::Electron & lepton,
		std::vector<std::string> & userFloatNames,
		std::vector<float> & userFloatValues)
		{

			// check if any paths were accepted, if so store them along with pre-scales
			// this is done without ref. to any trigger object, this feature is key for embedded
			// samples

			if(!wasAnyPathAccepted(userFloatNames, userFloatValues)) return;

			// lepton 4-vector
			TLorentzVector RecoObjVec;
		 	RecoObjVec.SetXYZT(lepton.p4().X(),lepton.p4().Y(),lepton.p4().Z(),lepton.p4().T());

			TrigSummaryInfoHelper(RecoObjVec, userFloatNames, userFloatValues);

	

		} 




void TriggerInfoEmbeddingTool::getTriggerInfo(pat::Muon & lepton,
		std::vector<std::string> & userFloatNames,
		std::vector<float> & userFloatValues)
		{

			// check if any paths were accepted, if so store them along with pre-scales
			if(!wasAnyPathAccepted(userFloatNames, userFloatValues)) return;


			// lepton 4-vector
			TLorentzVector RecoObjVec;
		 	RecoObjVec.SetXYZT(lepton.p4().X(),lepton.p4().Y(),lepton.p4().Z(),lepton.p4().T());

			TrigSummaryInfoHelper(RecoObjVec, userFloatNames, userFloatValues);

	
		}



void TriggerInfoEmbeddingTool::getTriggerInfo(pat::Tau & lepton,
		std::vector<std::string> & userFloatNames,
		std::vector<float> & userFloatValues)
		{


			// check if any paths were accepted, if so store them along with pre-scales
			if(!wasAnyPathAccepted(userFloatNames, userFloatValues)) return;


			// lepton 4-vector
			TLorentzVector RecoObjVec;
		 	RecoObjVec.SetXYZT(lepton.p4().X(),lepton.p4().Y(),lepton.p4().Z(),lepton.p4().T());


	 		TrigSummaryInfoHelper(RecoObjVec, userFloatNames, userFloatValues);


		}




