#include "generateH2TauSyncTree.h"
#include <iostream>
#include <fstream>
#include <string>


generateH2TauSyncTree::generateH2TauSyncTree(FlatTreeReader R_, bool run_)
{
	m_run = run_;
	R = R_;

	// init counters
	num_et = 0;
	num_em = 0;
	num_tt = 0;
	num_mt = 0;

	if(m_run)
	{

	outFile_MuTau = new TFile("davis_syncTree_MuTau.root","RECREATE");
	outFile_EleTau  = new TFile("davis_syncTree_EleTau.root","RECREATE");
	outFile_TauTau  = new TFile("davis_syncTree_TauTau.root","RECREATE");
	outFile_EleMu  = new TFile("davis_syncTree_EleMu.root","RECREATE");

	tree_MuTau = new TTree("tree_MuTau","tree_MuTau");
	tree_EleTau = new TTree("tree_EleTau","tree_EleTau");
	tree_TauTau = new TTree("tree_TauTau","tree_TauTau");
	tree_EleMu = new TTree("tree_EleMu","tree_EleMu");

	setupBranches(tree_MuTau);
	setupBranches(tree_EleTau);
	setupBranches(tree_TauTau);
	setupBranches(tree_EleMu);


	// READ IN THE MET FILTER VETO FILES
	std::ifstream file_DoubleEG("MET_FILTER/eventlist_DoubleEG_csc2015.txt");
	std::ifstream file_MuonEG("MET_FILTER/eventlist_MuonEG_csc2015.txt");
	std::ifstream file_SingleElectron("MET_FILTER/eventlist_SingleElectron_csc2015.txt");
	std::ifstream file_SingleMuon("MET_FILTER/eventlist_SingleMuon_csc2015.txt");
	std::ifstream file_Tau("MET_FILTER/eventlist_Tau_csc2015.txt");

	std::string aline;
	if (file_DoubleEG.is_open())
	{
		while ( getline (file_DoubleEG,aline) )
		{
		  metFilter_DoubleEG.push_back(aline);
		}
		file_DoubleEG.close();
	}

	if (file_MuonEG.is_open())
	{
		while ( getline (file_MuonEG,aline) )
		{
		  metFilter_MuonEG.push_back(aline);
		}
		file_MuonEG.close();
	}

	if (file_SingleElectron.is_open())
	{
		while ( getline (file_SingleElectron,aline) )
		{
		  metFilter_SingleElectron.push_back(aline);
		}
		file_SingleElectron.close();
	}

	if (file_SingleMuon.is_open())
	{
		while ( getline (file_SingleMuon,aline) )
		{
		  metFilter_SingleMuon.push_back(aline);
		}
		file_SingleMuon.close();
	}

	if (file_Tau.is_open())
	{
		while ( getline (file_Tau,aline) )
		{
		  metFilter_Tau.push_back(aline);
		}
		file_Tau.close();
	}

	std::cout<<" file_DoubleEG "<<metFilter_DoubleEG.size()<<"\n";
	std::cout<<" file_MuonEG "<<metFilter_MuonEG.size()<<"\n";
	std::cout<<" file_SingleElectron "<<metFilter_SingleElectron.size()<<"\n";
	std::cout<<" file_SingleMuon "<<metFilter_SingleMuon.size()<<"\n";
	std::cout<<" file_Tau "<<metFilter_Tau.size()<<"\n";





	}

	else
	{
		outFile_MuTau = nullptr;
		outFile_EleTau  = nullptr; 
		outFile_TauTau  = nullptr;
		outFile_EleMu  = nullptr;

		tree_MuTau = nullptr;
		tree_EleTau = nullptr;
		tree_TauTau = nullptr;
		tree_EleMu = nullptr;
	}

}



void generateH2TauSyncTree::finish()
{
	if(m_run)
	{
		outFile_MuTau->cd();
		tree_MuTau->CloneTree()->Write("TauCheck");	/* need to clone because of shared addresses */		
		outFile_MuTau->Close();

		outFile_EleTau->cd();
		tree_EleTau->CloneTree()->Write("TauCheck");		
		outFile_EleTau->Close();

		outFile_TauTau->cd();
		tree_TauTau->CloneTree()->Write("TauCheck");		
		outFile_TauTau->Close();		

		outFile_EleMu->cd();
		tree_EleMu->CloneTree()->Write("TauCheck");		
		outFile_EleMu->Close();

	}
}

generateH2TauSyncTree::~generateH2TauSyncTree()
{
	if(!m_run) /* Close on the outFile deletes the TH1F pointers */
	{
		delete tree_MuTau;
		delete tree_EleTau;
		delete tree_TauTau;
		delete tree_EleMu;
	}	
	delete outFile_MuTau;
	delete outFile_EleTau;
	delete outFile_TauTau;
	delete outFile_EleMu;
	

};	

void generateH2TauSyncTree::handleEvent()
{
	// reset values
	reset();

	// some 4-vectors we will need

	TLorentzVector l1, l2, pfMetVec, j1_20, j2_20;

	l1.SetPtEtaPhiM(R.getD("leg1_pt"),R.getD("leg1_eta"),R.getD("leg1_phi"),R.getD("leg1_M"));
	l2.SetPtEtaPhiM(R.getD("leg2_pt"),R.getD("leg2_eta"),R.getD("leg2_phi"),R.getD("leg2_M"));
	pfMetVec.SetPtEtaPhiM(R.getD("pfMET"),0.0,R.getD("pfMETphi"),0.0);

	// extra lepton + dilepton vetoes

	setExtraLepVetoes(l1, l2);

	// Only fill if njetspt20>=2 
		
	std::vector<double> jets20_pt = R.getVD("jets_pt");
	std::vector<double> jets20_eta = R.getVD("jets_eta");
	std::vector<double> jets20_phi = R.getVD("jets_phi");
	std::vector<double> jets20_M = R.getVD("jets_M");
	std::vector<double> jets20_MVA = R.getVD("jets_PU_jetIdRaw");

	std::vector<double> Bjets_pt = R.getVD("bjets_pt");
	std::vector<double> Bjets_eta = R.getVD("bjets_eta");
	std::vector<double> Bjets_phi = R.getVD("bjets_phi");
	std::vector<double> Bjets_M = R.getVD("bjets_M");
	std::vector<double> Bjets_MVA = R.getVD("bjets_PU_jetIdRaw");
	std::vector<float> Bjets_CSV = R.getVF("bjets_defaultBtagAlgorithm_RawScore");


	if(R.getI("numberOfJets")>=1) j1_20.SetPtEtaPhiM(jets20_pt[0],jets20_eta[0],jets20_phi[0],jets20_M[0]);

	if(R.getI("numberOfJets")>=2)
	{	
		j2_20.SetPtEtaPhiM(jets20_pt[1],jets20_eta[1],jets20_phi[1],jets20_M[1]);
	

		mjj = (j1_20+j2_20).M();
	 	jdeta = (j1_20.Eta()-j2_20.Eta());
	 	jdphi = (j1_20.Phi()-j2_20.Phi());

		 njetingap = 0;
		 njetingap20 = 0;

		 if(jets20_eta.size()>2)
		 {
		 	for(std::size_t i = 2; i<jets20_eta.size();++i)
		 	{
		 		double current_eta = jets20_eta[i];
		 		double low_bound = std::min(jets20_eta[0],jets20_eta[1]);
		 		double high_bound = std::max(jets20_eta[0],jets20_eta[1]);

		 		if(current_eta>low_bound && high_bound>current_eta)
		 		{
		 			if(jets20_pt[i]>20) njetingap20++;
		 			if(jets20_pt[i]>30) njetingap++;
		 		}



		 	}

		 }


	}

	/// some jet info 

	nbtag =  R.getI("numberOfBJets");
	njets =  R.getI("numberOfJets30");
	njetspt20 =  R.getI("numberOfJets");
	 
	if(njetspt20>=1)
	{ 
		jpt_1 =  jets20_pt[0];
		jeta_1 =  jets20_eta[0];
		jphi_1 =  jets20_phi[0];
		jrawf_1 =  1.0;
		jmva_1 =  jets20_MVA[0];
	} 

	if(njetspt20>=2)
	{ 
		jpt_2 =  jets20_pt[1];
		jeta_2 =  jets20_eta[1];
		jphi_2 =  jets20_phi[1];
		jrawf_2 =  1.0;
		jmva_2 =  jets20_MVA[1];
	} 


	if(nbtag>=1)
	{
		bpt_1 =  Bjets_pt[0];
		beta_1 =  Bjets_eta[0];
		bphi_1 =  Bjets_phi[0];
		brawf_1 =  1.0;
		bmva_1 =  Bjets_MVA[0];
		bcsv_1 =  Bjets_CSV[0];
	}

	if(nbtag>=2)
	{
		bpt_2 =  Bjets_pt[1];
		beta_2 =  Bjets_eta[1];
		bphi_2 =  Bjets_phi[1];
		brawf_2 =  1.0;
		bmva_2 =  Bjets_MVA[1];
		bcsv_2 =  Bjets_CSV[1];
	}	 




	///// the tree elements

	run = R.getUI("run");
	event = R.getUI("event");
	lumi = R.getUI("luminosityBlock");

	isOsPair = R.getI("isOsPair");
	pairRank = R.getUI("pairRank");
	npv = R.getI("NumberOfGoodVertices");
	npu = R.getF("NumTruePileUpInt");
	rho = R.getD("rho");

	pt_1 = R.getD("leg1_pt");
	phi_1 = R.getD("leg1_phi");
	eta_1 = R.getD("leg1_eta");
	m_1 = R.getD("leg1_M");
	q_1 = R.getI("leg1_charge");
	d0_1 = R.getF("leg1_dxy");
	dZ_1 = R.getF("leg1_dz");
	mt_1 = R.getD("MTpfMET_leg1");
	iso_1 = R.getF("leg1_RelIso");

	if(R.getI("leg1_leptonType") == 1)
	{
		id_e_mva_nt_loose_1 = R.getF("leg1_raw_electronMVA");
	}
	if(R.getI("leg1_leptonType") == 3)
	{
		againstElectronLooseMVA5_1 = R.getF("leg1_againstElectronLooseMVA5");
		againstElectronMediumMVA5_1 = R.getF("leg1_againstElectronMediumMVA5");
		againstElectronTightMVA5_1 = R.getF("leg1_againstElectronTightMVA5");
		againstElectronVLooseMVA5_1 = R.getF("leg1_againstElectronVLooseMVA5");
		againstElectronVTightMVA5_1 = R.getF("leg1_againstElectronVTightMVA5");
		againstMuonLoose3_1 = R.getF("leg1_againstMuonLoose3");
		againstMuonTight3_1 = R.getF("leg1_againstMuonTight3");
		byCombinedIsolationDeltaBetaCorrRaw3Hits_1 = R.getF("leg1_byCombinedIsolationDeltaBetaCorrRaw3Hits");
		// byIsolationMVA3newDMwoLTraw_1 = R.getF("leg1_byIsolationMVA3newDMwoLTraw");
		// byIsolationMVA3oldDMwoLTraw_1 = R.getF("leg1_byIsolationMVA3oldDMwoLTraw");
		// byIsolationMVA3newDMwLTraw_1 = R.getF("leg1_byIsolationMVA3newDMwLTraw");
		// byIsolationMVA3oldDMwLTraw_1 = R.getF("leg1_byIsolationMVA3oldDMwLTraw");
		chargedIsoPtSum_1 = R.getF("leg1_chargedIsoPtSum");
		decayModeFindingNewDMs_1 = R.getF("leg1_decayModeFindingNewDMs");
		neutralIsoPtSum_1 = R.getF("leg1_neutralIsoPtSum");
		puCorrPtSum_1 = R.getF("leg1_puCorrPtSum");	
	}

	pt_2 = R.getD("leg2_pt");
	phi_2 = R.getD("leg2_phi");
	eta_2 = R.getD("leg2_eta");
	m_2 = R.getD("leg2_M");
	q_2 = R.getI("leg2_charge");
	d0_2 = R.getF("leg2_dxy");
	dZ_2 = R.getF("leg2_dz");
	mt_2 = R.getD("MTpfMET_leg1");
	iso_2 = R.getF("leg2_RelIso");

	if(R.getI("leg2_leptonType") == 1)
	{
		id_e_mva_nt_loose_2 = R.getF("leg2_raw_electronMVA");
	}
	if(R.getI("leg2_leptonType") == 3)
	{
		againstElectronLooseMVA5_2 = R.getF("leg2_againstElectronLooseMVA5");
		againstElectronMediumMVA5_2 = R.getF("leg2_againstElectronMediumMVA5");
		againstElectronTightMVA5_2 = R.getF("leg2_againstElectronTightMVA5");
		againstElectronVLooseMVA5_2 = R.getF("leg2_againstElectronVLooseMVA5");
		againstElectronVTightMVA5_2 = R.getF("leg2_againstElectronVTightMVA5");
		againstMuonLoose3_2 = R.getF("leg2_againstMuonLoose3");
		againstMuonTight3_2 = R.getF("leg2_againstMuonTight3");
		byCombinedIsolationDeltaBetaCorrRaw3Hits_2 = R.getF("leg2_byCombinedIsolationDeltaBetaCorrRaw3Hits");
		//byIsolationMVA3newDMwoLTraw_2 = R.getF("leg2_byIsolationMVA3newDMwoLTraw");
		//byIsolationMVA3oldDMwoLTraw_2 = R.getF("leg2_byIsolationMVA3oldDMwoLTraw");
		//byIsolationMVA3newDMwLTraw_2 = R.getF("leg2_byIsolationMVA3newDMwLTraw");
		//byIsolationMVA3oldDMwLTraw_2 = R.getF("leg2_byIsolationMVA3oldDMwLTraw");
		chargedIsoPtSum_2 = R.getF("leg2_chargedIsoPtSum");
		decayModeFindingNewDMs_2 = R.getF("leg2_decayModeFindingNewDMs");
		neutralIsoPtSum_2 = R.getF("leg2_neutralIsoPtSum");
		puCorrPtSum_2 = R.getF("leg2_puCorrPtSum");	
	}


	m_vis = R.getD("VISMass");
	pt_tt = (l1+l2+pfMetVec).Pt();



	met = R.getD("pfMET");
	metphi = R.getD("pfMETphi");	
	metcov00 = R.getD("pfMET_cov00");
	metcov01 = R.getD("pfMET_cov01");
	metcov10 = R.getD("pfMET_cov10");
	metcov11 = R.getD("pfMET_cov11");

	mvamet = R.getD("mvaMET");
	mvametphi = R.getD("mvaMETphi");
	mvacov00 = R.getD("mvaMET_cov00");
	mvacov01 = R.getD("mvaMET_cov01");
	mvacov10 = R.getD("mvaMET_cov10");
	mvacov11 = R.getD("mvaMET_cov11");

	if(R.getI("CandidateEventType")==2) 
	{		
		pzetavis = pzetaVisCalc(l1,l2);
		pzetamiss = pzetaMissCalc(l1,l2,pfMetVec);
	}



	// the DY info

	isZtt = R.getB("EventHasZtoTauTau");
	isZee = R.getB("EventHasZtoEE");
	isZmm = R.getB("EventHasZtoMM"); 

	/* needs a gen loop to be fully right WHY DID THEY CHANGE ALL THESE FROM ZL, ZTT etc.*/
	isZmt = 0;
	isZet = 0;
	isZem = 0;
	isZEE = 0;  	
	isZMM = 0;  	
	isZLL = 0;  	
	isFake = 0;


	trigweight_1 = 0;
	trigweight_2 = 0;
		

	generatorEventWeight = R.getD("generatorEventWeight");
	DataSet = R.getS("DataSet");
    EventTotal = R.getI("EventTotal");
    EventType = R.getS("EventType");
    KeyName =  R.getS("KeyName");
    CrossSection =  R.getD("CrossSection");  
    FilterEff =  R.getD("FilterEff");




if(R.getI("CandidateEventType")==2)
{
	/* e+mu HLT Paths for Phys14 */
	if(R.getF("leg1_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL") == 1.0) trigweight_1 = 1.0;
	if(R.getF("leg2_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL") == 1.0) trigweight_2 = 1.0;

	if(R.getF("leg1_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL") == 1.0) trigweight_1 = 1.0;
	if(R.getF("leg2_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL") == 1.0) trigweight_2 = 1.0;

}

if(R.getI("CandidateEventType")==3)
{
	/* e+tau HLT Paths for Phys14 */
	if(R.getF("leg1_HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20") == 1.0) trigweight_1 = 1.0;
	if(R.getF("leg2_HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20") == 1.0) trigweight_2 = 1.0;


	if(R.getF("leg1_HLT_Ele32_eta2p1_WP75_Gsf") == 1.0) trigweight_1 = 1.0;
	/* no 2nd leg really, so use leg1 */ if(R.getF("leg1_HLT_Ele32_eta2p1_WP75_Gsf") == 1.0) trigweight_2 = 1.0;

}


if(R.getI("CandidateEventType")==5)
{
	/* mu+tau HLT Paths for Phys14 */
	if(R.getF("leg1_HLT_IsoMu17_eta2p1_LooseIsoPFTau20") == 1.0) trigweight_1 = 1.0;
	if(R.getF("leg2_HLT_IsoMu17_eta2p1_LooseIsoPFTau20") == 1.0) trigweight_2 = 1.0;
	
	if(R.getF("leg1_HLT_IsoMu24_eta2p1") == 1.0) trigweight_1 = 1.0;
	/* no 2nd leg really, so use leg1 */ if(R.getF("leg1_HLT_IsoMu24_eta2p1") == 1.0) trigweight_2 = 1.0;

}

if(R.getI("CandidateEventType")==6)
{
	/* tau+tau HLT Paths for Phys14 */
	if(R.getF("leg1_HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg") == 1.0) trigweight_1 = 1.0;
	if(R.getF("leg2_HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg") == 1.0) trigweight_2 = 1.0;

}


	// std::cout<<" --- --------------\n ";


	
	/* some additional cuts */
	//if(R.getUI("pairRank") != 0) return;
	//if(R.getI("isOsPair") != 1) return;
	if(fabs(R.getI("leg1_charge")) != 1) return;
	if(fabs(R.getI("leg2_charge")) != 1) return;



	// MET FILTER FLAGS
	
	std::string checkString = std::to_string(run)+":"+std::to_string(lumi)+":"+std::to_string(event);
	bool GOOD_MET_FLAG = 1;





	if(KeyName == "Run2015D_TauOct" || KeyName == "Run2015D_TauPromptRv4")
	{
		if (std::find(metFilter_Tau.begin(), metFilter_Tau.end(), 
		checkString) != metFilter_Tau.end()) 
			{
				std::cout<<" BAD in metFilter_Tau "<<checkString<<"\n";
				GOOD_MET_FLAG = 0;
			}
	}

	if(KeyName == "Run2015D_MuonEGOct" || KeyName == "Run2015D_MuonEGPromptRv4")
	{
		if (std::find(metFilter_MuonEG.begin(), metFilter_MuonEG.end(), 
		checkString) != metFilter_MuonEG.end()) 
			{
				std::cout<<" BAD in metFilter_MuonEG "<<checkString<<"\n";
				GOOD_MET_FLAG = 0;
			}
	}



	if(KeyName == "Run2015D_DoubleEGPromptRv4" || KeyName == "Run2015D_DoubleEGOct")
	{
		if (std::find(metFilter_DoubleEG.begin(), metFilter_DoubleEG.end(), 
		checkString) != metFilter_DoubleEG.end()) 
			{
				std::cout<<" BAD in metFilter_DoubleEG "<<checkString<<"\n";
				GOOD_MET_FLAG = 0;
			}
	}



	if(KeyName == "Run2015D_SingleElectronPromptRv4" || KeyName == "Run2015D_SingleElectronOct")
	{
		if (std::find(metFilter_SingleElectron.begin(), metFilter_SingleElectron.end(), 
		checkString) != metFilter_SingleElectron.end()) 
			{
				std::cout<<" BAD in metFilter_SingleElectron "<<checkString<<"\n";
				GOOD_MET_FLAG = 0;
			}
	}


	if(KeyName == "Run2015D_SingleMuonPromptRv4" || KeyName == "Run2015D_SingleMuonOct")
	{
		if (std::find(metFilter_SingleMuon.begin(), metFilter_SingleMuon.end(), 
		checkString) != metFilter_SingleMuon.end()) 
			{
				std::cout<<" BAD in metFilter_SingleMuon "<<checkString<<"\n";
				GOOD_MET_FLAG = 0;
			}
	}

	/////////// DON'T CHANGE VALUES AFTER THIS :)
	/* see TupleCandidateEventTypes */

	if(R.getI("CandidateEventType")==3 && l1.DeltaR(l2) > 0.5 && l1.Pt()>24 && GOOD_MET_FLAG) {num_et++; tree_EleTau->Fill();}
	else if(R.getI("CandidateEventType")==2 && l1.DeltaR(l2) > 0.3  && GOOD_MET_FLAG ){num_em++; tree_EleMu->Fill();}
	else if(R.getI("CandidateEventType")==5 && l1.DeltaR(l2) > 0.5 && l1.Pt()>19  && GOOD_MET_FLAG){num_mt++; tree_MuTau->Fill();}
	else if(R.getI("CandidateEventType")==6 && l1.DeltaR(l2) > 0.5  && GOOD_MET_FLAG) {num_tt++; tree_TauTau->Fill();}
	
	if(num_et%1000==0){
	 std::cout<<" etau = "<<num_et<<"\n";
	 std::cout<<" mtau = "<<num_mt<<"\n";
	 std::cout<<" tt = "<<num_tt<<"\n";
	 std::cout<<" em = "<<num_em<<"\n";
	}


}

void generateH2TauSyncTree::setupBranches(TTree * T)
{
	/* all trees get same branch address, but will only write event
	 to one tree per event based on CandidateEventType */

	T->Branch("run",&run);
	T->Branch("event",&event);
	T->Branch("lumi",&lumi);
	T->Branch("isOsPair",&isOsPair);
	
	T->Branch("pairRank",&pairRank);
	T->Branch("npv",&npv);
	T->Branch("npu",&npu);
	T->Branch("rho",&rho);
	
	T->Branch("pt_1", &pt_1);
	T->Branch("phi_1", &phi_1);
	T->Branch("eta_1", &eta_1);
	T->Branch("m_1", &m_1);
	T->Branch("q_1", &q_1);
	T->Branch("d0_1", &d0_1);
	T->Branch("dZ_1", &dZ_1);
	T->Branch("mt_1", &mt_1);
	T->Branch("iso_1", &iso_1);
	T->Branch("id_e_mva_nt_loose_1", &id_e_mva_nt_loose_1);
	T->Branch("againstElectronLooseMVA5_1", &againstElectronLooseMVA5_1);
	T->Branch("againstElectronMediumMVA5_1", &againstElectronMediumMVA5_1);
	T->Branch("againstElectronTightMVA5_1", &againstElectronTightMVA5_1);
	T->Branch("againstElectronVLooseMVA5_1", &againstElectronVLooseMVA5_1);
	T->Branch("againstElectronVTightMVA5_1", &againstElectronVTightMVA5_1);
	T->Branch("againstMuonLoose3_1", &againstMuonLoose3_1);
	T->Branch("againstMuonTight3_1", &againstMuonTight3_1);
	T->Branch("byCombinedIsolationDeltaBetaCorrRaw3Hits_1", &byCombinedIsolationDeltaBetaCorrRaw3Hits_1);
	T->Branch("byIsolationMVA3newDMwoLTraw_1", &byIsolationMVA3newDMwoLTraw_1);
	T->Branch("byIsolationMVA3oldDMwoLTraw_1", &byIsolationMVA3oldDMwoLTraw_1);
	T->Branch("byIsolationMVA3newDMwLTraw_1", &byIsolationMVA3newDMwLTraw_1);
	T->Branch("byIsolationMVA3oldDMwLTraw_1", &byIsolationMVA3oldDMwLTraw_1);
	T->Branch("chargedIsoPtSum_1", &chargedIsoPtSum_1);
	T->Branch("decayModeFindingNewDMs_1", &decayModeFindingNewDMs_1);
	T->Branch("neutralIsoPtSum_1", &neutralIsoPtSum_1);
	T->Branch("puCorrPtSum_1", &puCorrPtSum_1);

	T->Branch("pt_2", &pt_2);
	T->Branch("phi_2", &phi_2);
	T->Branch("eta_2", &eta_2);
	T->Branch("m_2", &m_2);
	T->Branch("q_2", &q_2);
	T->Branch("d0_2", &d0_2);
	T->Branch("dZ_2", &dZ_2);
	T->Branch("mt_2", &mt_2);
	T->Branch("iso_2", &iso_2);
	T->Branch("id_e_mva_nt_loose_2", &id_e_mva_nt_loose_2);
	T->Branch("againstElectronLooseMVA5_2", &againstElectronLooseMVA5_2);
	T->Branch("againstElectronMediumMVA5_2", &againstElectronMediumMVA5_2);
	T->Branch("againstElectronTightMVA5_2", &againstElectronTightMVA5_2);
	T->Branch("againstElectronVLooseMVA5_2", &againstElectronVLooseMVA5_2);
	T->Branch("againstElectronVTightMVA5_2", &againstElectronVTightMVA5_2);
	T->Branch("againstMuonLoose3_2", &againstMuonLoose3_2);
	T->Branch("againstMuonTight3_2", &againstMuonTight3_2);
	T->Branch("byCombinedIsolationDeltaBetaCorrRaw3Hits_2", &byCombinedIsolationDeltaBetaCorrRaw3Hits_2);
	T->Branch("byIsolationMVA3newDMwoLTraw_2", &byIsolationMVA3newDMwoLTraw_2);
	T->Branch("byIsolationMVA3oldDMwoLTraw_2", &byIsolationMVA3oldDMwoLTraw_2);
	T->Branch("byIsolationMVA3newDMwLTraw_2", &byIsolationMVA3newDMwLTraw_2);
	T->Branch("byIsolationMVA3oldDMwLTraw_2", &byIsolationMVA3oldDMwLTraw_2);
	T->Branch("chargedIsoPtSum_2", &chargedIsoPtSum_2);
	T->Branch("decayModeFindingNewDMs_2", &decayModeFindingNewDMs_2);
	T->Branch("neutralIsoPtSum_2", &neutralIsoPtSum_2);
	T->Branch("puCorrPtSum_2", &puCorrPtSum_2);

	T->Branch("pt_tt" , &pt_tt);
	T->Branch("m_vis" , &m_vis);
	T->Branch("met" , &met);
	T->Branch("metphi" , &metphi);
	T->Branch("mvamet" , &mvamet);
	T->Branch("mvametphi" , &mvametphi);
	T->Branch("pzetavis" , &pzetavis);
	T->Branch("pzetamiss" , &pzetamiss);
	T->Branch("mvacov00" , &mvacov00);
	T->Branch("mvacov01" , &mvacov01);
	T->Branch("mvacov10" , &mvacov10);
	T->Branch("mvacov11" , &mvacov11);
	T->Branch("metcov00" , &metcov00);
	T->Branch("metcov01" , &metcov01);
	T->Branch("metcov10" , &metcov10);
	T->Branch("metcov11" , &metcov11);
	
	T->Branch("mjj" , &mjj);
	T->Branch("jdeta" , &jdeta);
	T->Branch("njetingap" , &njetingap);
	T->Branch("njetingap20" , &njetingap20);
	T->Branch("jdphi" , &jdphi);

	T->Branch("nbtag" , &nbtag);
	T->Branch("njets" , &njets);
	T->Branch("njetspt20" , &njetspt20);

	T->Branch("jpt_1" , &jpt_1);
	T->Branch("jeta_1" , &jeta_1);
	T->Branch("jphi_1" , &jphi_1);
	T->Branch("jrawf_1" , &jrawf_1);
	T->Branch("jmva_1" , &jmva_1);

	T->Branch("jpt_2" , &jpt_2);
	T->Branch("jeta_2" , &jeta_2);
	T->Branch("jphi_2" , &jphi_2);
	T->Branch("jrawf_2" , &jrawf_2);
	T->Branch("jmva_2" , &jmva_2);

	T->Branch("bpt_1" , &bpt_1);
	T->Branch("beta_1" , &beta_1);
	T->Branch("bphi_1" , &bphi_1);
	T->Branch("brawf_1" , &brawf_1);
	T->Branch("bmva_1" , &bmva_1);
	T->Branch("bcsv_1" , &bcsv_1);

	T->Branch("bpt_2" , &bpt_2);
	T->Branch("beta_2" , &beta_2);
	T->Branch("bphi_2" , &bphi_2);
	T->Branch("brawf_2" , &brawf_2);
	T->Branch("bmva_2" , &bmva_2);
	T->Branch("bcsv_2" , &bcsv_2);

	T->Branch("dilepton_veto", &dilepton_veto);
	T->Branch("extraelec_veto", &extraelec_veto);
	T->Branch("extramuon_veto", &extramuon_veto);

	

	T->Branch("isZtt", &isZtt);
	T->Branch("isZee", &isZee);
	T->Branch("isZmm", &isZmm);
	T->Branch("isZmt", &isZmt);
	T->Branch("isZet", &isZet);
	T->Branch("isZem", &isZem);
	T->Branch("isZEE", &isZEE);
	T->Branch("isZMM", &isZMM);
	T->Branch("isZLL", &isZLL);
	T->Branch("isFake", &isFake);

	T->Branch("trigweight_1", &trigweight_1);
	T->Branch("trigweight_2", &trigweight_2);


	T->Branch("generatorEventWeight", &generatorEventWeight);
	T->Branch("DataSet", &DataSet);
	T->Branch("EventTotal", &EventTotal);
	T->Branch("EventType", &EventType);
	T->Branch("KeyName", &KeyName);
	T->Branch("CrossSection", &CrossSection);
	T->Branch("FilterEff", &FilterEff);


}



double generateH2TauSyncTree::pzetaVisCalc(TLorentzVector e, TLorentzVector mu)
{
	double value = 0;

	double den = sqrt(pow((cos(e.Phi())+cos(mu.Phi())),2) + pow((sin(e.Phi())+sin(mu.Phi())),2));
	double num = (e.Px()+mu.Px())*(cos(e.Phi())+cos(mu.Phi()));
	num += (e.Py()+mu.Py())*(sin(e.Phi())+cos(mu.Phi()));

	if(den!=0) value = num/den;


	return value;
}
double generateH2TauSyncTree::pzetaMissCalc(TLorentzVector e, TLorentzVector mu, TLorentzVector met)
{

	double value = 0;

	double den = sqrt(pow((cos(e.Phi())+cos(mu.Phi())),2) + pow((sin(e.Phi())+sin(mu.Phi())),2));
	double num = 	(met.Px())*(cos(e.Phi())+cos(mu.Phi()));
	num += (met.Py())*(sin(e.Phi())+sin(mu.Phi()));

	if(den!=0) value = num/den;
	return value;

}

void generateH2TauSyncTree::setExtraLepVetoes(TLorentzVector l1_, TLorentzVector l2_)
{
	dilepton_veto = 0;	
	extraelec_veto = 0; 	
	extramuon_veto = 0;

	std::vector<int> veto_leptonType = R.getVI("veto_leptonType");
	std::vector<double> veto_pt  = R.getVD("veto_pt");
	std::vector<double> veto_eta = R.getVD("veto_eta");
	std::vector<double> veto_phi = R.getVD("veto_phi");
	std::vector<double> veto_M = R.getVD("veto_M");
	std::vector<float> veto_dxy = R.getVF("veto_dxy");
	std::vector<float> veto_dz = R.getVF("veto_dz");
	std::vector<int> veto_charge  = R.getVI("veto_charge");
    std::vector<float> veto_passElectronMVA90  = R.getVF("veto_passElectronMVA90");
	std::vector<float> veto_passElectronCutBased  = R.getVF("veto_passElectronCutBased");
	std::vector<float> veto_isTrackerGlobalPFMuon  = R.getVF("veto_isTrackerGlobalPFMuon");
    std::vector<float> veto_RelIso  = R.getVF("veto_RelIso");
	std::vector<float> veto_passesMediumMuonId  = R.getVF("veto_passesMediumMuonId");


	// check for extra electrons
	for(std::size_t i = 0; i<veto_leptonType.size();++i)
	{
		TLorentzVector ex;
		ex.SetPtEtaPhiM(veto_pt[i],veto_eta[i],veto_phi[i],veto_M[i]);

		/* see TupleLeptonTypes.h */	
		if( veto_leptonType[i]==1			 &&\
		    veto_pt[i]>10.0 				 &&\
			fabs(veto_eta[i])<2.5 			 &&\
			fabs(veto_dxy[i])<0.045 		 &&\
			fabs(veto_dz[i])<0.2 			 &&\
			veto_passElectronMVA90[i]==1.0 	 &&\
			veto_RelIso[i] < 0.3			 &&\
			l1_.DeltaR(ex) > 0.5 			 &&\
			l2_.DeltaR(ex) > 0.5)		
		{
			extraelec_veto = 1.0; break;
		}		
	}

	// check for extra muons
	for(std::size_t i = 0; i<veto_leptonType.size();++i)
	{
		TLorentzVector ex;
		ex.SetPtEtaPhiM(veto_pt[i],veto_eta[i],veto_phi[i],veto_M[i]);

		/* see TupleLeptonTypes.h */	
		if( veto_leptonType[i]==2			 &&\
		    veto_pt[i]>10.0 				 &&\
			fabs(veto_eta[i])<2.4 			 &&\
			fabs(veto_dxy[i])<0.045 		 &&\
			fabs(veto_dz[i])<0.2 			 &&\
			veto_passesMediumMuonId[i]==1.0  &&\
			veto_RelIso[i] < 0.3			 &&\
			l1_.DeltaR(ex) > 0.5 			 &&\
			l2_.DeltaR(ex) > 0.5)		
		{
			extramuon_veto = 1.0; break;
		}		
	}


	// check for di-electrons 
	// tricky since both could be in veto collection or veto+leg1 or veto+leg2

	std::vector <TLorentzVector> positiveElectronCands;
	std::vector <TLorentzVector> negativeElectronCands;

	if(R.getI("leg1_charge")==1 && R.getI("leg1_leptonType")==1) positiveElectronCands.push_back(l1_);
	if(R.getI("leg1_charge")==-1 && R.getI("leg1_leptonType")==1) negativeElectronCands.push_back(l1_);
	if(R.getI("leg2_charge")==1 && R.getI("leg2_leptonType")==1) positiveElectronCands.push_back(l2_);
	if(R.getI("leg2_charge")==-1 && R.getI("leg2_leptonType")==1) negativeElectronCands.push_back(l2_);

	for(std::size_t i = 0; i<veto_leptonType.size();++i)
	{
		TLorentzVector ex;
		ex.SetPtEtaPhiM(veto_pt[i],veto_eta[i],veto_phi[i],veto_M[i]);

		/* see TupleLeptonTypes.h */	
		if( veto_leptonType[i]==1			  &&\
		    veto_pt[i]>15.0 				  &&\
			fabs(veto_eta[i])<2.5 			  &&\
			fabs(veto_dxy[i])<0.045 		  &&\
			fabs(veto_dz[i])<0.2 			  &&\
			veto_passElectronCutBased[i]==1.0 &&\
			veto_RelIso[i] < 0.3)
		{
			if(veto_charge[i]==1) positiveElectronCands.push_back(ex);
			if(veto_charge[i]==-1) negativeElectronCands.push_back(ex);
		}		
	}

	for(std::size_t p=0; p<positiveElectronCands.size();++p)
	{
		for(std::size_t n=0; n<negativeElectronCands.size();++n)
		{
			if(positiveElectronCands[p].DeltaR(negativeElectronCands[n]) > 0.15) 
			{
				dilepton_veto = 1;
				return; /* no need to check diMuon since share same var */
			}

		}
	}

	// check for di-muons 
	// tricky since both could be in veto collection or veto+leg1 or veto+leg2

	std::vector <TLorentzVector> positiveMuonCands;
	std::vector <TLorentzVector> negativeMuonCands;

	if(R.getI("leg1_charge")==1 && R.getI("leg1_leptonType")==2) positiveMuonCands.push_back(l1_);
	if(R.getI("leg1_charge")==-1 && R.getI("leg1_leptonType")==2) negativeMuonCands.push_back(l1_);
	if(R.getI("leg2_charge")==1 && R.getI("leg2_leptonType")==2) positiveMuonCands.push_back(l2_);
	if(R.getI("leg2_charge")==-1 && R.getI("leg2_leptonType")==2) negativeMuonCands.push_back(l2_);

	for(std::size_t i = 0; i<veto_leptonType.size();++i)
	{
		TLorentzVector ex;
		ex.SetPtEtaPhiM(veto_pt[i],veto_eta[i],veto_phi[i],veto_M[i]);

		/* see TupleLeptonTypes.h */	
		if( veto_leptonType[i]==2			   &&\
		    veto_pt[i]>15.0 				   &&\
			fabs(veto_eta[i])<2.4 			   &&\
			fabs(veto_dxy[i])<0.045 		   &&\
			fabs(veto_dz[i])<0.2 			   &&\
			veto_isTrackerGlobalPFMuon[i]==1.0 &&\
			veto_RelIso[i] < 0.3)
		{
			if(veto_charge[i]==1) positiveMuonCands.push_back(ex);
			if(veto_charge[i]==-1) negativeMuonCands.push_back(ex);
		}		
	}

	for(std::size_t p=0; p<positiveMuonCands.size();++p)
	{
		for(std::size_t n=0; n<negativeMuonCands.size();++n)
		{
			if(positiveMuonCands[p].DeltaR(negativeMuonCands[n]) > 0.15) 
			{
				dilepton_veto = 1;
				return; 
			}

		}
	}


}

void generateH2TauSyncTree::reset()
{

	run = 0;
	event = 0;
	lumi = 0;
	pairRank = 999;
	isOsPair = -999;
	npv =  0;
	npu =  -999.0;
	rho =  -999.0;
	 
	pt_1 =  -999.0;
	phi_1 =  -999.0;
	eta_1 =  -999.0;
	m_1 =  -999.0;
	q_1 =  0;
	d0_1 =  -999.0;
	dZ_1 =  -999.0;
	mt_1 =  -999.0;
	iso_1 =  -999.0;
	id_e_mva_nt_loose_1 =  -999.0;
	againstElectronLooseMVA5_1 =  -999.0;
	againstElectronMediumMVA5_1 =  -999.0;
	againstElectronTightMVA5_1 =  -999.0;
	againstElectronVLooseMVA5_1 =  -999.0;
	againstElectronVTightMVA5_1 =  -999.0;
	againstMuonLoose3_1 =  -999.0;
	againstMuonTight3_1 =  -999.0;
	byCombinedIsolationDeltaBetaCorrRaw3Hits_1 =  -999.0;
	byIsolationMVA3newDMwoLTraw_1 =  -999.0;
	byIsolationMVA3oldDMwoLTraw_1 =  -999.0;
	byIsolationMVA3newDMwLTraw_1 =  -999.0;
	byIsolationMVA3oldDMwLTraw_1 =  -999.0;
	chargedIsoPtSum_1 =  -999.0;
	decayModeFindingNewDMs_1 =  -999.0;
	neutralIsoPtSum_1 =  -999.0;
	puCorrPtSum_1 =  -999.0;
	 
	 
	pt_2 =  -999.0;
	phi_2 =  -999.0;
	eta_2 =  -999.0;
	m_2 =  -999.0;
	q_2 =  0;
	d0_2 =  -999.0;
	dZ_2 =  -999.0;
	mt_2 =  -999.0;
	iso_2 =  -999.0;
	id_e_mva_nt_loose_2 =  -999.0;
	againstElectronLooseMVA5_2 =  -999.0;
	againstElectronMediumMVA5_2 =  -999.0;
	againstElectronTightMVA5_2 =  -999.0;
	againstElectronVLooseMVA5_2 =  -999.0;
	againstElectronVTightMVA5_2 =  -999.0;
	againstMuonLoose3_2 =  -999.0;
	againstMuonTight3_2 =  -999.0;
	byCombinedIsolationDeltaBetaCorrRaw3Hits_2 =  -999.0;
	byIsolationMVA3newDMwoLTraw_2 =  -999.0;
	byIsolationMVA3oldDMwoLTraw_2 =  -999.0;
	byIsolationMVA3newDMwLTraw_2 =  -999.0;
	byIsolationMVA3oldDMwLTraw_2 =  -999.0;
	chargedIsoPtSum_2 =  -999.0;
	decayModeFindingNewDMs_2 =  -999.0;
	neutralIsoPtSum_2 =  -999.0;
	puCorrPtSum_2 =  -999.0;
	 
	pt_tt =  -999.0;
	m_vis =  -999.0;
	 
	met =  -999.0;
	metphi =  -999.0;
	mvamet =  -999.0;
	mvametphi =  -999.0;
	pzetavis =  -999.0;
	pzetamiss =  -999.0;
	mvacov00 =  -999.0;
	mvacov01 =  -999.0;
	mvacov10 =  -999.0;
	mvacov11 =  -999.0;
	metcov00 =  -999.0;
	metcov01 =  -999.0;
	metcov10 =  -999.0;
	metcov11 =  -999.0;
	 
	mjj =  -999.0;
	jdeta =  -999.0;
	njetingap =  -999.0;
	njetingap20 =  -999.0;
	jdphi =  -999.0;

	nbtag =  0;
	njets =  0;
	njetspt20 =  0;
	 
	 
	jpt_1 =  -999.0;
	jeta_1 =  -999.0;
	jphi_1 =  -999.0;
	jrawf_1 =  -999.0;
	jmva_1 =  -999.0;
	 
	 
	jpt_2 =  -999.0;
	jeta_2 =  -999.0;
	jphi_2 =  -999.0;
	jrawf_2 =  -999.0;
	jmva_2 =  -999.0;
	 
	 
	bpt_1 =  -999.0;
	beta_1 =  -999.0;
	bphi_1 =  -999.0;
	brawf_1 =  -999.0;
	bmva_1 =  -999.0;
	bcsv_1 =  -999.0;
	 
	 
	bpt_2 =  -999.0;
	beta_2 =  -999.0;
	bphi_2 =  -999.0;
	brawf_2 =  -999.0;
	bmva_2 =  -999.0;
	bcsv_2 =  -999.0;

	dilepton_veto = 0;	
	extraelec_veto = 0; 	
	extramuon_veto = 0;

	isZtt = 0;  	
	isZmt = 0;  	
	isZet = 0;  	
	isZee = 0;  	
	isZmm = 0;  	
	isZem = 0;  	
	isZEE = 0;  	
	isZMM = 0;  	
	isZLL = 0;  	
	isFake = 0;

	trigweight_1 = 0;
	trigweight_2 = 0;

    generatorEventWeight = 1.0;
	DataSet = "NULL";
    EventTotal = 1;
    EventType = "NULL";
    KeyName = "NULL"; 
    CrossSection = 1.0;    
    FilterEff = 1.0; 
}
