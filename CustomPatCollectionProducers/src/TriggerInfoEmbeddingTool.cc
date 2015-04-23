/* for a pat::Electron, Muon or Tau collection embed trigger info as UserFloats */


// system include files
#include <memory>

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
				const edm::TriggerNames &names_):
					triggerBits(triggerBits_),
					triggerObjects(triggerObjects_),
					triggerPreScales(triggerPreScales_),
					names(names_){}
	
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
					pathNamesToFill.push_back(names.triggerName(i));
					pathPrescalesToFill.push_back(triggerPreScales->getPrescaleForIndex(i));

				}
			}

	if (pathNamesToFill.size()>0) return 1;
	return 0;
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
			if(currentDR > 0.5) continue;

			// check if smallest DR
			if( currentDR < minDR )
			{
				minDR = currentDR;
				returnIndex = i;
			}

 		}


 		return returnIndex;
 	}




	


void TriggerInfoEmbeddingTool::getTriggerInfo(pat::Electron & lepton,
		std::vector<std::string> & userFloatNames,
		std::vector<float> & userFloatValues)
		{

			// lepton 4-vector
			TLorentzVector RecoObjVec;
		 	RecoObjVec.SetXYZT(lepton.p4().X(),lepton.p4().Y(),lepton.p4().Z(),lepton.p4().T());

		 	// trigger object types allowed
		 	std::vector<int> allowedTrigObjectTypes;
	 		allowedTrigObjectTypes.push_back(trigger::TriggerObjectType::TriggerElectron);


	 		std::size_t bestMatchIndex = getBestMatchedObject(RecoObjVec, allowedTrigObjectTypes,0.5);
	 		if(bestMatchIndex!=9999) std::cout<<" ele "<<bestMatchIndex<<"\n";

		} 




void TriggerInfoEmbeddingTool::getTriggerInfo(pat::Muon & lepton,
		std::vector<std::string> & userFloatNames,
		std::vector<float> & userFloatValues)
		{
			// lepton 4-vector
			TLorentzVector RecoObjVec;
		 	RecoObjVec.SetXYZT(lepton.p4().X(),lepton.p4().Y(),lepton.p4().Z(),lepton.p4().T());

		 	// trigger object types allowed
		 	std::vector<int> allowedTrigObjectTypes;
	 		allowedTrigObjectTypes.push_back(trigger::TriggerObjectType::TriggerMuon);

	 		std::size_t bestMatchIndex = getBestMatchedObject(RecoObjVec, allowedTrigObjectTypes,0.5);
	 			if(bestMatchIndex!=9999) std::cout<<" mu "<<bestMatchIndex<<"\n";
		}



void TriggerInfoEmbeddingTool::getTriggerInfo(pat::Tau & lepton,
		std::vector<std::string> & userFloatNames,
		std::vector<float> & userFloatValues)
		{

			// lepton 4-vector
			TLorentzVector RecoObjVec;
		 	RecoObjVec.SetXYZT(lepton.p4().X(),lepton.p4().Y(),lepton.p4().Z(),lepton.p4().T());

		 	// trigger object types allowed
		 	std::vector<int> allowedTrigObjectTypes;
	 		allowedTrigObjectTypes.push_back(trigger::TriggerObjectType::TriggerTau);

	 		std::size_t bestMatchIndex = getBestMatchedObject(RecoObjVec, allowedTrigObjectTypes,0.5);
	 			if(bestMatchIndex!=9999) std::cout<<" tau "<<bestMatchIndex<<"\n";


		}




	// // create a vector to hold 'allowed' TriggerObjectIDs 
	// 		// for the given reco object (in this case electrons)
	// 		/* note - I only check |abs| matches on ID
	// 		  and negatives mean L1, pos means HLT */

	// 		std::vector<int> allowedTrigObjectTypes;
	// 		allowedTrigObjectTypes.push_back(trigger::TriggerObjectType::TriggerElectron);

	// 		// begin by getting accepted triggers, store 1.0 by default
	// 		// unless prescaled (in that case store the prescale value)

	// 		std::vector <std::string> passedPathNames;

	// 		//const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
	// 		for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) 
	// 		{
	// 			if(triggerBits->accept(i)) 
	// 			{
	// 				userFloatNames.push_back(names.triggerName(i));
	// 				userFloatValues.push_back(triggerPreScales->getPrescaleForIndex(i));
	// 				passedPathNames.push_back(names.triggerName(i));

	// 			}
	// 		}

	// 			TLorentzVector RecoObjVec;
	// 			RecoObjVec.SetXYZT(lepton.p4().X(),lepton.p4().Y(),lepton.p4().Z(),lepton.p4().T());
	// 			TLorentzVector TrigObjVec;

	// 		for (pat::TriggerObjectStandAlone obj : *triggerObjects)
	// 		{

	// 			// check the DR between the reco and trigger objects
	// 			TrigObjVec.SetPtEtaPhiM(obj.pt(),obj.eta(),obj.phi(),obj.mass());

	// 			float DR = TrigObjVec.DeltaR(RecoObjVec);
	// 			if(DR > 0.5) continue;

	// 			// check that the filterIDs contain at least one of the allowed types
	// 			// for this reco object (again I ignore sign)

	// 			bool objectIDtypeMatch = 0;

	// 			for (std::size_t reco1 = 0; reco1 < allowedTrigObjectTypes.size(); ++reco1)
	// 			{
	// 				for (std::size_t trig1 = 0; trig1 < obj.filterIds().size(); ++trig1)
	// 				{


	// 					if (abs(obj.filterIds()[trig1]) == abs(allowedTrigObjectTypes[reco1])) objectIDtypeMatch = 1;

	// 				}


	// 			}				

	// 			if (!objectIDtypeMatch) continue;

	// 			// get names of paths associated to this object
	// 			// pathNamesAll = any path associated to the object
	// 			// pathNamesLast = paths associated to the object for which it satisfies final filter in the path

	// 			obj.unpackPathNames(names);
	// 			std::vector<std::string> pathNamesAll  = obj.pathNames(false);
	// 			std::vector<std::string> pathNamesLast = obj.pathNames(true);

	// 			// loop over accepted paths

	// 			for(std::string acceptedPath : passedPathNames)
	// 			{
					
	// 				bool all = std::find(pathNamesAll.begin(), pathNamesAll.end(), acceptedPath) != pathNamesAll.end();
	// 				bool last = std::find(pathNamesLast.begin(), pathNamesLast.end(), acceptedPath) != pathNamesLast.end();

	// 				if (all==1 || last==1)
	// 				{	
	// 					std::cout<<"DR "<<DR<<" "<<obj.pt()<<" accepted path "<<acceptedPath<<" all, last : "<<all<<","<<last<<" ";					
	// 					std::cout << "\t   Type IDs:   ";
 // 				        for (unsigned h = 0; h < obj.filterIds().size(); ++h) std::cout << " " << obj.filterIds()[h]<<" " ;
	// 					std::cout << "\t   Filters:    ";
	// 			        for (unsigned h = 0; h < obj.filterLabels().size(); ++h) std::cout << " " << obj.filterLabels()[h];
	// 			        std::cout << std::endl;



	// 				}


	// 			}



	// 		}

