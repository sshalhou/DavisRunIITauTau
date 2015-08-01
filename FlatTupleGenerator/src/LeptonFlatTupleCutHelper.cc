/* class LeptonFlatTupleCutHelper :

contains functions to apply simple cuts at the FlatTuple 
production stage based on cms.PSet and NtupleEvent arguments

- Shalhout
*/


#include "DavisRunIITauTau/FlatTupleGenerator/interface/LeptonFlatTupleCutHelper.h"







/* constructor */

LeptonFlatTupleCutHelper::LeptonFlatTupleCutHelper(){}

/* main cut checking function */

bool LeptonFlatTupleCutHelper::cutEvaluator(NtupleEvent anEvent, std::vector<edm::ParameterSet> aVPSet)
{

	/* return True if empty cut set */
	if(aVPSet.size()==0) return 1;

	/* counters for all applicable cuts, and for those passing */

	int valid_cuts = 0;
	int passed_cuts = 0;

	/* get the 2 leptons & the CandidateEventType */

	NtupleLepton leg1 = anEvent.leg1();
	NtupleLepton leg2 = anEvent.leg2();
	int pairType = anEvent.CandidateEventType();

	/* loop through all PSets in aVPSet, require passing of all PSets with matching CandidateEventType
	(or no CandidateEventType specified) */


	for (std::size_t i = 0; i < aVPSet.size(); ++i)
	{
		edm::ParameterSet currentSet = (aVPSet.at(i));
		int forType = -999;
		if(currentSet.exists("candidatePairType"))
		{
			forType = decodeCandidateTypeString(currentSet.getParameter<std::string>("candidatePairType"));
		}

		if(pairType==forType || forType == -999)
		{
			/* we have a valid cut set */
			valid_cuts++;

			StringCutObjectSelector<NtupleLepton> leg1Cut(getAppropriateCutString(
													leg1.leptonType(), currentSet, 0));
			StringCutObjectSelector<NtupleLepton> leg2Cut(getAppropriateCutString(
													leg2.leptonType(), currentSet, 0));


			/* impose the cuts on pairs */
			bool passPairDRCut = 1;
			bool passPairTriggerCut = 1;

			if(currentSet.exists("minDR"))
			{

				TLorentzVector d1(0,0,0,0);
				TLorentzVector d2(0,0,0,0);
				double minDR = currentSet.getParameter<double>("minDR");
				d1.SetXYZT(leg1.p4().X(),leg1.p4().Y(),leg1.p4().Z(),leg1.p4().T());
				d2.SetXYZT(leg2.p4().X(),leg2.p4().Y(),leg2.p4().Z(),leg2.p4().T());
				if(d1.DeltaR(d2) < minDR) passPairDRCut = 0;
			}


			if(currentSet.exists("trigger"))
			{
				StringCutObjectSelector<NtupleEvent> triggerCut(currentSet.getParameter<std::string>("trigger"));

				passPairTriggerCut = triggerCut(anEvent);

			}



			//std::cout<<currentSet.getParameter<double>("minDR")<<" = minDR pass fail = "<<passPairDRCut<<"\n";
			//std::cout<<currentSet.getParameter<std::string>("trigger")<<" = trigger pass/fail = "<<passPairTriggerCut<<"\n";





			if(leg1Cut(leg1) && leg2Cut(leg2) && passPairDRCut && passPairTriggerCut) passed_cuts++;

		}


	}

return (valid_cuts==passed_cuts && valid_cuts!=0);
}

/* helpers */

int LeptonFlatTupleCutHelper::decodeCandidateTypeString(std::string thePairType)
{

	int returnVal = -999;
 
	if(thePairType=="EleEle") returnVal = TupleCandidateEventTypes::EleEle;
	if(thePairType=="EleMuon") returnVal = TupleCandidateEventTypes::EleMuon;
	if(thePairType=="EleTau") returnVal = TupleCandidateEventTypes::EleTau;
	if(thePairType=="MuonMuon") returnVal = TupleCandidateEventTypes::MuonMuon;
	if(thePairType=="MuonTau") returnVal = TupleCandidateEventTypes::MuonTau;
	if(thePairType=="TauTau") returnVal = TupleCandidateEventTypes::TauTau;



	assert(returnVal!=-999);
	return returnVal;
}



std::string LeptonFlatTupleCutHelper::getAppropriateCutString(int lepType, edm::ParameterSet aPSet, bool wantVetoCut)
{
	std::string returnString = "";

	if(!wantVetoCut)
	{

		if(lepType==TupleLeptonTypes::anElectron && aPSet.exists("electronID")) returnString = aPSet.getParameter<std::string>("electronID");
		else if(lepType==TupleLeptonTypes::aMuon && aPSet.exists("muonID")) returnString = aPSet.getParameter<std::string>("muonID");
		else if(lepType==TupleLeptonTypes::aTau && aPSet.exists("tauID")) returnString =  aPSet.getParameter<std::string>("tauID");
	}

return returnString;
}


std::vector<std::string> LeptonFlatTupleCutHelper::getCutSummary(std::vector<edm::ParameterSet> aVPSet)
{
	std::vector <std::string> theCuts;

	for (std::size_t i = 0; i < aVPSet.size(); ++i)
	{
		std::string currentCut = "";
		edm::ParameterSet currentSet = (aVPSet.at(i));


		if(currentSet.exists("candidatePairType"))
		{
			currentCut += " [ "+(currentSet.getParameter<std::string>("candidatePairType"));
			currentCut += " ] ";	
		}
		else currentCut+= " [ anyPairType ] ";

		if(currentSet.exists("electronID"))
		{
			currentCut += " [ electronID = "+(currentSet.getParameter<std::string>("electronID"));
			currentCut += " ] ";	
		}

		if(currentSet.exists("muonID"))
		{
			currentCut += " [ muonID = "+(currentSet.getParameter<std::string>("muonID"));
			currentCut += " ] ";	
		}


		if(currentSet.exists("tauID"))
		{
			currentCut += " [ tauID = "+(currentSet.getParameter<std::string>("tauID"));
			currentCut += " ] ";	
		}

		theCuts.push_back(currentCut);
	}


return theCuts;
}



