/* just print some info for each FlatTuple event */

#include "simpleQuantityPrint.h"


simpleQuantityPrint::simpleQuantityPrint(FlatTreeReader R_, bool run_)
{
	
	R = R_;

}


simpleQuantityPrint::~simpleQuantityPrint()
{};	

void simpleQuantityPrint::handleEvent()
{


	/* simple types */
	std::cout<<"event = "<<R.getUI("event")<<" ";
	std::cout<<"CandidateEventType = "<<R.getI("CandidateEventType")<<" ";
	std::cout<<"pfMETphi = "<<R.getD("pfMETphi")<<" ";
	std::cout<<"leg1_dz = "<<R.getF("leg1_dz")<<" ";
	std::cout<<"isRealData = "<<R.getB("isRealData")<<" ";
	std::cout<<"treeInfoString = "<<R.getS("treeInfoString")<<"\n";

	/* vector types */

	std::vector<int> jets_PARTON_flavour = R.getVI("jets_PARTON_flavour");
	for(std::size_t i = 0; i<jets_PARTON_flavour.size();++i)
	{
		std::cout<<" jets_PARTON_flavour @ "<<i<<" is "<< jets_PARTON_flavour[i]<<"\n";
	}

	std::vector<double> jets_eta = R.getVD("jets_eta");
	for(std::size_t i = 0; i<jets_eta.size();++i)
	{
		std::cout<<" jets_eta @ "<<i<<" is "<< jets_eta[i]<<"\n";
	}


	std::vector<float> jets_defaultBtagAlgorithm_RawScore = R.getVF("jets_defaultBtagAlgorithm_RawScore");
	for(std::size_t i = 0; i<jets_defaultBtagAlgorithm_RawScore.size();++i)
	{
		std::cout<<" jets_defaultBtagAlgorithm_RawScore @ "<<i<<" is "<< jets_defaultBtagAlgorithm_RawScore[i]<<"\n";
	}

	std::vector<bool> jets_PU_jetIdPassed = R.getVB("jets_PU_jetIdPassed");
	for(std::size_t i = 0; i<jets_PU_jetIdPassed.size();++i)
	{
		std::cout<<" jets_PU_jetIdPassed @ "<<i<<" is "<< jets_PU_jetIdPassed[i]<<"\n";
	}

	// std::vector<std::string> AppliedLepCuts = R.getVS("AppliedLepCuts");
	// for(std::size_t i = 0; i<AppliedLepCuts.size();++i)
	// {
	// 	std::cout<<" AppliedLepCuts @ "<<i<<" is "<< AppliedLepCuts[i]<<"\n";
	// }

	/* more complete genParticle example, loop over gen particles, print daughters and mothers */

	std::vector<std::pair<int,int> > genParticle_pdgId = R.getVPII("genParticle_pdgId");
	std::vector<std::pair<int,double> > genParticle_pt = R.getVPID("genParticle_pt");
	std::vector<std::pair<int,int> > genDaughter_pdgId = R.getVPII("genDaughter_pdgId");
//	std::vector<std::pair<int,int> > genParticle_isPrompt = R.getVPII("genParticle_isPrompt");
//	std::vector<std::pair<int,int> > genParticle_isPromptFinalState = R.getVPII("genParticle_isPromptFinalState");
//	std::vector<std::pair<int,int> > genParticle_isDirectPromptTauDecayProduct = R.getVPII("genParticle_isDirectPromptTauDecayProduct");
//	std::vector<std::pair<int,int> > genParticle_isDirectPromptTauDecayProductFinalState = R.getVPII("genParticle_isDirectPromptTauDecayProductFinalState");
	std::vector<std::pair<int,double> > genDaughter_pt = R.getVPID("genDaughter_pt");

	for(std::size_t g = 0; g < genParticle_pdgId.size(); ++g)
	{
		std::cout<<" gen partcile @ index "<<g<<" has id = "<<genParticle_pdgId[g].second<<" ";
//		std::cout<<" and has isPrompt "<<genParticle_isPrompt[g].second<<" ";	
//		std::cout<<" and has isPromptFinalState "<<genParticle_isPromptFinalState[g].second<<" ";	
//		std::cout<<" and has isDirectPromptTauDecayProduct "<<genParticle_isDirectPromptTauDecayProduct[g].second<<" ";	
//		std::cout<<" and has isDirectPromptTauDecayProductFinalState "<<genParticle_isDirectPromptTauDecayProductFinalState[g].second<<" ";	
		std::cout<<"and has pT = "<<genParticle_pt[g].second<<" and has daughters with (id,Pt) of  = [ ";
	





		for(std::size_t d = 0; d < genDaughter_pt.size(); ++d)
		{
			/* the first element links daughters/mothers to the genPartcile */
			if(genDaughter_pt[d].first==genParticle_pdgId[g].first)
			{
				std::cout<<"("<<genDaughter_pdgId[d].second<<" , "<<genDaughter_pt[d].second<<") ";
			}		
		}	
		std::cout<<" ] \n";

	}




}



void simpleQuantityPrint::finish()
{

}
