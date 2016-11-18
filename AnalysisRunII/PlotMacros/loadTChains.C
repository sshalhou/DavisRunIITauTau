#include "TChain.h"
#include <iostream>
#include "TString.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <sstream>
#include <vector>
#include <algorithm>

void fileLoad();

void setup_files_muTau_test();
void setup_files_eleTau_test();
void setup_files_eleMu_test();
void setup_files_TauTau_test();

void setup_files_muTau();
void setup_files_eleTau();
void setup_files_eleMu();
void setup_files_TauTau();
void setup_upTau_files_muTau();
void setup_downTau_files_muTau();
void setup_upEle_files_eleTau();
void setup_downEle_files_eleTau();
void setup_upTau_files_eleTau();
void setup_downTau_files_eleTau();
void setup_upEle_files_eleMu();
void setup_downEle_files_eleMu();
void setup_upTau_files_TauTau();
void setup_downTau_files_TauTau();

void reset_files();

TChain * DATA = new TChain("TauCheck");

TChain * DY = new TChain("TauCheck");
TChain * W = new TChain("TauCheck");
TChain * TT = new TChain("TauCheck");
TChain * VV = new TChain("TauCheck");

TChain * GluGluHTauTau = new TChain("TauCheck");
TChain * VBFHTauTau = new TChain("TauCheck");
TChain * WminusHToTauTau_M125 = new TChain("TauCheck");
TChain * WplusHToTauTau_M125 = new TChain("TauCheck");
TChain * ttHJetTT = new TChain("TauCheck");

TChain * MZP600_MA0400  = new TChain("TauCheck");
TChain * MZP800_MA0400  = new TChain("TauCheck");
TChain * MZP1000_MA0400  = new TChain("TauCheck");
TChain * MZP1200_MA0400  = new TChain("TauCheck");
TChain * MZP1400_MA0700  = new TChain("TauCheck");

//BKG subgroups
//W
TChain * WJetsToLNu = new TChain("TauCheck");
TChain * W1JetsToLNu = new TChain("TauCheck");
TChain * W2JetsToLNu = new TChain("TauCheck");
TChain * W3JetsToLNu = new TChain("TauCheck");
TChain * W4JetsToLNu = new TChain("TauCheck");

//DY
TChain * DYhigh = new TChain("TauCheck");
TChain * DYlow = new TChain("TauCheck");
TChain * DYinc = new TChain("TauCheck");
TChain * DY1Jets = new TChain("TauCheck");
TChain * DY2Jets = new TChain("TauCheck");
TChain * DY3Jets = new TChain("TauCheck");
TChain * DY4Jets = new TChain("TauCheck");

//DY channels divided using bools
TChain * ZTT = new TChain("TauCheck");
TChain * ZJ = new TChain("TauCheck");
TChain * ZL = new TChain("TauCheck");

//ZH
TChain * ZHTauTau = new TChain("TauCheck");
//WH Main
TChain * WHTauTau = new TChain("TauCheck");
//VV
TChain * ST_t_channel_antitop_4f_leptonDecays = new TChain("TauCheck");
TChain * ST_t_channel_top_4f_leptonDecays = new TChain("TauCheck");
TChain * ST_tW_antitop_5f_inclusiveDecays = new TChain("TauCheck");
TChain * ST_tW_top_5f_inclusiveDecays = new TChain("TauCheck");
TChain * VVTo2L2Nu = new TChain("TauCheck");
TChain * WWTo1L1Nu2Q = new TChain("TauCheck");
TChain * WZJToLLLNu = new TChain("TauCheck");
TChain * WZTo1L1Nu2Q = new TChain("TauCheck");
TChain * WZTo1L3Nu = new TChain("TauCheck");
TChain * WZTo2L2Q = new TChain("TauCheck");
TChain * ZZTo2L2Q = new TChain("TauCheck");
TChain * ZZTo4L = new TChain("TauCheck");


void fileLoad (TChain * CHAIN, TString PATH_TO_FILES, std::string FILE_NAME)
{

	FILE * CondorJobs;
	CondorJobs = popen("xrdfs root://cmseos.fnal.gov ls "+PATH_TO_FILES,"r");
	std::vector <std::string> condorVector;

	if ( CondorJobs != NULL )
    {
      char aline [ 10000 ]; 
      while ( fgets ( aline, sizeof aline, CondorJobs ) != NULL ) 
      {
         std::string astring(aline);
         astring.erase( std::remove( astring.begin(), astring.end(), '\n' ), astring.end() ) ;
         astring = "root://cmsxrootd.fnal.gov/" + astring + "/" + FILE_NAME;
         condorVector.push_back(astring);
      }
      fclose ( CondorJobs );
    }

	for(std::size_t i = 0; i<condorVector.size(); ++i)
	{
		CHAIN->Add(condorVector[i].c_str());
	}

}

//small sample setup for testing

void setup_files_muTau_test()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" Mu tau TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_files_eleTau_test()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" Ele tau TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_files_eleMu_test()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" Ele Mu TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_files_TauTau_test()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/TEST/TEST/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" tau Tau TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_files_TauTau()
{
    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/Tau/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_TauTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_TauTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINE_TauTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" tau tau TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_files_eleMu()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/MuonEG/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleMu.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_EleMu.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINE_EleMu.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" electron-muon TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";


}

void setup_files_eleTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/SingleElectron/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_EleTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINE_EleTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" electron-tau TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_files_muTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/SingleMuon/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_MuTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_MuTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINE_MuTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" Mu tau TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_upTau_files_TauTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/Tau/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_TauTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_TauTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_TauTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" tau-tau [Tau ES UP] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}
void setup_downTau_files_TauTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/Tau/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_TauTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_TauTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_TauTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" tau-tau [Tau ES DOWN] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}
void setup_upEle_files_eleMu()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/MuonEG/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupElectron_EleMu.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleMu.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleMu.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" electron-muon [Electron ES UP] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";
}

void setup_downEle_files_eleMu()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/MuonEG/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleMu.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleMu.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" electron-muon [Electron ES DOWN] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_upTau_files_eleTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/SingleElectron/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_EleTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_EleTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_EleTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" electron-tau [Tau ES UP] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_downTau_files_eleTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/SingleElectron/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_EleTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_EleTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_EleTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" electron-tau [Tau ES DOWN] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_upEle_files_eleTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/SingleElectron/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupElectron_EleTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEupElectron_EleTau.root");
    
    //Consolidate TChains to main BKG categories

    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);

    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");

    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type

    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);

    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);

	std::cout<<" electron-tau [Electron ES UP] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_downEle_files_eleTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/SingleElectron/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEdownElectron_EleTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" electron-tau [Electron ES DOWN] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_upTau_files_muTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/SingleMuon/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_MuTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_MuTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEupTau_MuTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" muon-tau [Tau ES UP] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void setup_downTau_files_muTau()
{

    fileLoad(DATA, "/store/user/gfunk/NovProductionV2_76X/DATA/SingleMuon/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(GluGluHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_GluGluHTauTau/GluGluHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(VBFHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_VBFHTauTau/VBFHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(WminusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WminusHTauTau/WminusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(WplusHToTauTau_M125, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_WplusHTauTau/WplusHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(ZHTauTau, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ZHTauTau/ZHToTauTau_M125_13TeV_powheg_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(ttHJetTT, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_ttHJetTT/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
   
    fileLoad(TT, "/store/user/gfunk/NovProductionV2_76X/TT/TT_TuneCUETP8M1_13TeV-powheg-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(ST_t_channel_antitop_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(ST_t_channel_top_4f_leptonDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_MuTau.root");
  
    fileLoad(ST_tW_antitop_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(ST_tW_top_5f_inclusiveDecays, "/store/user/gfunk/NovProductionV2_76X/VV/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(VVTo2L2Nu, "/store/user/gfunk/NovProductionV2_76X/VV/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(WWTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(WZJToLLLNu, "/store/user/gfunk/NovProductionV2_76X/VV/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(WZTo1L1Nu2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(WZTo1L3Nu, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(WZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(ZZTo2L2Q, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(ZZTo4L, "/store/user/gfunk/NovProductionV2_76X/VV/ZZTo4L_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(W1JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
   
    fileLoad(W2JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(W3JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
 
    fileLoad(W4JetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
   
    fileLoad(WJetsToLNu, "/store/user/gfunk/NovProductionV2_76X/W/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
   
    fileLoad(DY1Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(DY2Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(DY3Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
	
    fileLoad(DY4Jets, "/store/user/gfunk/NovProductionV2_76X/DY/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
	
    fileLoad(DYinc, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(DYhigh, "/store/user/gfunk/NovProductionV2_76X/DY/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
	
    fileLoad(DYlow, "/store/user/gfunk/NovProductionV2_76X/DYlowMass/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(MZP600_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-600_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(MZP800_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-800_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(MZP1000_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1000_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    fileLoad(MZP1200_MA0400, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1200_MA0-400_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_MuTau.root");

    fileLoad(MZP1400_MA0700, "/store/user/gfunk/NovProductionV2_76X/SIGNAL_MONO_HIGGS/ZprimeToA0hToA0chichihtautau_2HDM_MZp-1400_MA0-700_13TeV-madgraph/", "davis_syncTree_BASELINEdownTau_MuTau.root");
    
    //Consolidate TChains to main BKG categories
    
    DY->Add(DYhigh);
    DY->Add(DYlow);
    DY->Add(DYinc);
    DY->Add(DY1Jets);
    DY->Add(DY2Jets);
    DY->Add(DY3Jets);
    DY->Add(DY4Jets);
    
    ZTT = (TChain*) DY->CopyTree("IsZTT==1");
    ZJ = (TChain*) DY->CopyTree("IsZJ==1");
    ZL = (TChain*) DY->CopyTree("IsZL==1");
    
    W->Add(WJetsToLNu);
    W->Add(W1JetsToLNu);
    W->Add(W2JetsToLNu);
    W->Add(W3JetsToLNu);
    W->Add(W4JetsToLNu);
    
    //TT is only one channel type
    
    VV->Add(ST_t_channel_antitop_4f_leptonDecays);
    VV->Add(ST_t_channel_top_4f_leptonDecays);
    VV->Add(ST_tW_antitop_5f_inclusiveDecays);
    VV->Add(ST_tW_top_5f_inclusiveDecays);
    VV->Add(VVTo2L2Nu);
    VV->Add(WWTo1L1Nu2Q);
    VV->Add(WZJToLLLNu);
    VV->Add(WZTo1L1Nu2Q);
    VV->Add(WZTo1L3Nu);
    VV->Add(WZTo2L2Q);
    VV->Add(ZZTo2L2Q);
    VV->Add(ZZTo4L);
    
    WHTauTau->Add(WminusHToTauTau_M125);
    WHTauTau->Add(WplusHToTauTau_M125);
    
	std::cout<<" muon-tau [Tau ES DOWN] TChains set up .... \n";
    std::cout<<" DATA size "<<DATA->GetEntries()<<"\n";
    std::cout<<" TT size "<<TT->GetEntries()<<"\n";
    std::cout<<" W size "<<W->GetEntries()<<"\n";
    std::cout<<" ZTT size "<<ZTT->GetEntries()<<"\n";
    std::cout<<" ZL size "<<ZL->GetEntries()<<"\n";
    std::cout<<" ZJ size "<<ZJ->GetEntries()<<"\n";
    std::cout<<" VV size "<<VV->GetEntries()<<"\n";
    std::cout<<" ZHTauTau size "<<ZHTauTau->GetEntries()<<"\n";
    std::cout<<" WHTauTau size "<<WHTauTau->GetEntries()<<"\n";
    std::cout<<" GluGluHTauTau size "<<GluGluHTauTau->GetEntries()<<"\n";
    std::cout<<" VBFHTauTau size "<<VBFHTauTau->GetEntries()<<"\n";
    std::cout<<" ttHJetTT size "<<ttHJetTT->GetEntries()<<"\n";

}

void reset_files()
{
    DATA->Reset();

    DY->Reset();
    W->Reset();
    TT->Reset();
    VV->Reset();

    GluGluHTauTau->Reset();
    VBFHTauTau->Reset();
    WminusHToTauTau_M125->Reset();
    WplusHToTauTau_M125->Reset();
    ttHJetTT->Reset();

    MZP600_MA0400 ->Reset();
    MZP800_MA0400 ->Reset();
    MZP1000_MA0400 ->Reset();
    MZP1200_MA0400 ->Reset();
    MZP1400_MA0700 ->Reset();

    //BKG subgroups
    //W
    WJetsToLNu->Reset();
    W1JetsToLNu->Reset();
    W2JetsToLNu->Reset();
    W3JetsToLNu->Reset();
    W4JetsToLNu->Reset();

    //DY
    DYhigh->Reset();
    DYlow->Reset();
    DYinc->Reset();
    DY1Jets->Reset();
    DY2Jets->Reset();
    DY3Jets->Reset();
    DY4Jets->Reset();
    
    //DY channels divided using bools
    ZTT->Reset();
    ZJ->Reset();
    ZL->Reset();
    
    //ZH
    ZHTauTau->Reset();
    //WH Main
    WHTauTau->Reset();
    //VV
    ST_t_channel_antitop_4f_leptonDecays->Reset();
    ST_t_channel_top_4f_leptonDecays->Reset();
    ST_tW_antitop_5f_inclusiveDecays->Reset();
    ST_tW_top_5f_inclusiveDecays->Reset();
    VVTo2L2Nu->Reset();
    WWTo1L1Nu2Q->Reset();
    WZJToLLLNu->Reset();
    WZTo1L1Nu2Q->Reset();
    WZTo1L3Nu->Reset();
    WZTo2L2Q->Reset();
    ZZTo2L2Q->Reset();
    ZZTo4L->Reset();
}
