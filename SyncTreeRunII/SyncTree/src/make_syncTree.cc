
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TTree.h>
#include <TFile.h>
#include "FlatTreeReader.h"

int main(int argc, char* argv[])
{

/* check the arguments */
/* at a minimum need the TTree name and a root file */

if (argc < 2) 
{
	std::cout<<" invoke as ./make_syncTree \"PASSCUTS/FlatTuple\" file.root \n";

	return -999;
}


/* read in a FlatTuple file and ttree */

TFile file(std::string(argv[2]).c_str(),"READ");
TTree * T = (TTree*) file.Get(std::string(argv[1]).c_str());

if(!T) 
{
	std::cout<<"invalid file or tree, check command line arguments \n";
	return -999;
}

/* create a file and some histograms */

TFile outFile("outFile.root","RECREATE");
TH1F * AHIST = new TH1F("AHIST","AHIST",100,0,500);
AHIST->Sumw2();


/* create a reader object and connect the TTree pointer */
FlatTreeReader R(T);

long int entries = T->GetEntries();

std::cout<<" total events = "<<entries<<"\n";

for(long int e = 0; e<entries; ++e)
{
	
	T->GetEntry(e);

///////// EXAMPLE CODE SHOWING ACCESS 
	// unsigned int ev = R.getUI("event");
	// int candtype = R.getI("CandidateEventType");
	// double metPhi = R.getD("pfMETphi");
	// float dz1 = R.getF("leg1_dz");
	// bool isData = R.getB("isRealData");
	// std::string info = R.getS("treeInfoString");

	if(e%1000 == 0)
	{
		std::cout<<" event "<<e<<" of "<<entries<<"\n";
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
		std::vector<std::pair<int,double> > genDaughter_pt = R.getVPID("genDaughter_pt");

		for(std::size_t g = 0; g < genParticle_pdgId.size(); ++g)
		{
			std::cout<<" gen partcile @ index "<<g<<" has id = "<<genParticle_pdgId[g].second<<" ";
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
///////// EXAMPLE CODE SHOWING ACCESS  -- END



 }




return 0;	
}

