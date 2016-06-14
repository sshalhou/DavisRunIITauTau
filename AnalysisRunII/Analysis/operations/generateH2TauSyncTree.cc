#include "generateH2TauSyncTree.h"
#include <iostream>
#include <fstream>
#include <string>


generateH2TauSyncTree::generateH2TauSyncTree(FlatTreeReader R_, bool run_)
{
	m_run = run_;
	R = R_;

	// init counters
	num_total = 0;
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

	 std::cout<<"final count etau = "<<num_et<<"\n";
	 std::cout<<"final count mtau = "<<num_mt<<"\n";
	 std::cout<<"final count tt = "<<num_tt<<"\n";
	 std::cout<<"final count em = "<<num_em<<"\n";
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
	num_total ++; /* total events seen */


	// reset values
	reset();

	//////////////////////////////////////////////////////////////////////////////
	// some 4-vectors we will need

	TLorentzVector l1, l2, j1_20, j2_20;
	TLorentzVector pfMetVec, puppiMetVec, mvaMetVec;


	l1.SetPtEtaPhiM(R.getD("leg1_pt"),R.getD("leg1_eta"),R.getD("leg1_phi"),R.getD("leg1_M"));
	l2.SetPtEtaPhiM(R.getD("leg2_pt"),R.getD("leg2_eta"),R.getD("leg2_phi"),R.getD("leg2_M"));
	pfMetVec.SetPtEtaPhiM(R.getD("pfMET"),0.0,R.getD("pfMETphi"),0.0);
	puppiMetVec.SetPtEtaPhiM(R.getD("puppiMET"),0.0,R.getD("puppiMETphi"),0.0);
	mvaMetVec.SetPtEtaPhiM(R.getD("corr_mvaMET"),0.0,R.getD("corr_mvaMETphi"),0.0);

	//////////////////////////////////////////////////////////////////////////////

	run = R.getUI("run");
	event = R.getUI("event");
	lumi = R.getUI("luminosityBlock");

	npv = R.getI("NumberOfGoodVertices");
 	npu = R.getF("NumTruePileUpInt");
 	rho = R.getD("rho");
 	puweight = R.getD("puWeight");


 	// leg 1 info 

 	pt_1 = R.getD("leg1_pt");
	phi_1 = R.getD("leg1_phi");
	eta_1 = R.getD("leg1_eta");
	m_1 = R.getD("leg1_M");
	q_1 = R.getI("leg1_charge");
	d0_1 = R.getF("leg1_dxy");
	dZ_1 = R.getF("leg1_dz");
	mt_1 = R.getD("corr_MTmvaMET_leg1");
	pfmt_1 = R.getD("MTpfMET_leg1");
	puppimt_1 = R.getD("MTpuppiMET_leg1");
	iso_1 = R.getF("leg1_RelIso");
	id_e_mva_nt_loose_1 = R.getF("leg1_raw_electronMVA");
	gen_match_1 = R.getI("leg1_MCMatchType");

 	pt_2 = R.getD("leg2_pt");
	phi_2 = R.getD("leg2_phi");
	eta_2 = R.getD("leg2_eta");
	m_2 = R.getD("leg2_M");
	q_2 = R.getI("leg2_charge");
	d0_2 = R.getF("leg2_dxy");
	dZ_2 = R.getF("leg2_dz");
	mt_2 = R.getD("corr_MTmvaMET_leg2");
	pfmt_2 = R.getD("MTpfMET_leg2");
	puppimt_2 = R.getD("MTpuppiMET_leg2");
	iso_2 = R.getF("leg2_RelIso");
	id_e_mva_nt_loose_2 = R.getF("leg2_raw_electronMVA");
	gen_match_2 = R.getI("leg2_MCMatchType");



	//////////////////////
	// tau IDs          //
	//////////////////////


	// have in 1st FlatTuple try

	againstElectronTightMVA6_1 = R.getF("leg1_againstElectronTightMVA6");
	againstElectronVLooseMVA6_1 = R.getF("leg1_againstElectronVLooseMVA6");
	againstMuonLoose3_1 = R.getF("leg1_againstMuonLoose3");
	againstMuonTight3_1 = R.getF("leg1_againstMuonTight3");
	byCombinedIsolationDeltaBetaCorrRaw3Hits_1 = R.getF("leg1_byCombinedIsolationDeltaBetaCorrRaw3Hits");
	byIsolationMVA3newDMwLTraw_1 = R.getF("leg1_byIsolationMVA3newDMwLTraw");

	againstElectronTightMVA6_2 = R.getF("leg2_againstElectronTightMVA6");
	againstElectronVLooseMVA6_2 = R.getF("leg2_againstElectronVLooseMVA6");
	againstMuonLoose3_2 = R.getF("leg2_againstMuonLoose3");
	againstMuonTight3_2 = R.getF("leg2_againstMuonTight3");
	byCombinedIsolationDeltaBetaCorrRaw3Hits_2 = R.getF("leg2_byCombinedIsolationDeltaBetaCorrRaw3Hits");
	byIsolationMVA3newDMwLTraw_2 = R.getF("leg2_byIsolationMVA3newDMwLTraw");

	// don't have in 1st FlatTuple try
	
	//if(num_total%1000==0) std::cout<<" Remember to Turn on new tau IDs for round II flatTuples \n";

	againstElectronLooseMVA6_1 = R.getF("leg1_againstElectronLooseMVA6");
	againstElectronMediumMVA6_1 = R.getF("leg1_againstElectronMediumMVA6");
	againstElectronVTightMVA6_1 = R.getF("leg1_againstElectronVTightMVA6");
	byIsolationMVA3oldDMwLTraw_1 = R.getF("leg1_byIsolationMVA3oldDMwLTraw");
	chargedIsoPtSum_1 = R.getF("leg1_chargedIsoPtSum");
	neutralIsoPtSum_1 = R.getF("leg1_neutralIsoPtSum");
	puCorrPtSum_1 = R.getF("leg1_puCorrPtSum");

	againstElectronLooseMVA6_2 = R.getF("leg2_againstElectronLooseMVA6");
	againstElectronMediumMVA6_2 = R.getF("leg2_againstElectronMediumMVA6");
	againstElectronVTightMVA6_2 = R.getF("leg2_againstElectronVTightMVA6");
	byIsolationMVA3oldDMwLTraw_2 = R.getF("leg2_byIsolationMVA3oldDMwLTraw");
	chargedIsoPtSum_2 = R.getF("leg2_chargedIsoPtSum");
	neutralIsoPtSum_2 = R.getF("leg2_neutralIsoPtSum");
	puCorrPtSum_2 = R.getF("leg2_puCorrPtSum");

	decayModeFindingOldDMs_1 = R.getF("leg1_decayModeFinding");
	decayModeFindingOldDMs_2 = R.getF("leg2_decayModeFinding");



	// bad in 76X ---- will cause asserts

	// decayModeFindingOldDMs_1 = R.getF("leg1_decayModeFindingOldDMs");
	// byIsolationMVA3newDMwoLTraw_1 = R.getF("leg1_byIsolationMVA3newDMwoLTraw");
	// byIsolationMVA3oldDMwoLTraw_1 = R.getF("leg1_byIsolationMVA3oldDMwoLTraw");
	// decayModeFindingOldDMs_2 = R.getF("leg2_decayModeFindingOldDMs");
	// byIsolationMVA3newDMwoLTraw_2 = R.getF("leg2_byIsolationMVA3newDMwoLTraw");
	// byIsolationMVA3oldDMwoLTraw_2 = R.getF("leg2_byIsolationMVA3oldDMwoLTraw");


	pt_tt = (l1+l2+pfMetVec).Pt();
	mt_tot = mtTotCalc(l1, l2, mvaMetVec);
	m_vis = R.getD("VISMass");
	m_sv = R.getD("SVMass");
	mt_sv = R.getD("SVTransverseMass");


	met = R.getD("pfMET");
	metphi = R.getD("pfMETphi");	

	puppimet = R.getD("puppiMET");
	puppimetphi = R.getD("puppiMETphi");

	mvamet = R.getD("corr_mvaMET");
	mvametphi = R.getD("corr_mvaMETphi");
	

	pzetavis = pzetaVisCalc(l1,l2);
	pzetamiss = pzetaMissCalc(l1,l2,mvaMetVec);
	pfpzetamiss = pzetaMissCalc(l1,l2,pfMetVec);
	puppipzetamiss = pzetaMissCalc(l1,l2,puppiMetVec);
	mvacov00 = R.getD("mvaMET_cov00");
	mvacov01 = R.getD("mvaMET_cov01");
	mvacov10 = R.getD("mvaMET_cov10");
	mvacov11 = R.getD("mvaMET_cov11");
	metcov00 = R.getD("pfMET_cov00");
	metcov01 = R.getD("pfMET_cov01");
	metcov10 = R.getD("pfMET_cov10");
	metcov11 = R.getD("pfMET_cov11");


	////////////////////////////////////////////////////////
	// handling of jets & b-jets is different in Fall15   //


	std::vector<double> jets_pt = R.getVD("jets_pt");
	std::vector<double> jets_eta = R.getVD("jets_eta");
	std::vector<double> jets_phi = R.getVD("jets_phi");
	std::vector<double> jets_M = R.getVD("jets_M");
	std::vector<double> jets_PU_jetIdRaw = R.getVD("jets_PU_jetIdRaw");
	std::vector<bool> jets_PU_jetIdPassed = R.getVB("jets_PU_jetIdPassed");
	std::vector<bool> jets_PF_jetIdPassed = R.getVB("jets_PF_jetIdPassed");
	std::vector<float> jets_defaultBtagAlgorithm_RawScore = R.getVF("jets_defaultBtagAlgorithm_RawScore");
	std::vector<int> jets_PARTON_flavour = R.getVI("jets_PARTON_flavour");
	std::vector<int> jets_HADRON_flavour = R.getVI("jets_HADRON_flavour");
	std::vector<double> jets_BtagSF_LooseWpCentral = R.getVD("jets_BtagSF_LooseWpCentral");
	std::vector<double> jets_BtagSF_LooseWpUp = R.getVD("jets_BtagSF_LooseWpUp");
	std::vector<double> jets_BtagSF_LooseWpDown = R.getVD("jets_BtagSF_LooseWpDown");
	std::vector<double> jets_BtagSF_MediumWpCentral = R.getVD("jets_BtagSF_MediumWpCentral");
	std::vector<double> jets_BtagSF_MediumWpUp = R.getVD("jets_BtagSF_MediumWpUp");
	std::vector<double> jets_BtagSF_MediumWpDown = R.getVD("jets_BtagSF_MediumWpDown");
	std::vector<double> jets_BtagSF_TightWpCentral = R.getVD("jets_BtagSF_TightWpCentral");
	std::vector<double> jets_BtagSF_TightWpUp = R.getVD("jets_BtagSF_TightWpUp");
	std::vector<double> jets_BtagSF_TightWpDown = R.getVD("jets_BtagSF_TightWpDown");
	std::vector<double> jets_BtagEff_LooseWp = R.getVD("jets_BtagEff_LooseWp");
	std::vector<double> jets_BtagEff_MediumWp = R.getVD("jets_BtagEff_MediumWp");
	std::vector<double> jets_BtagEff_TightWp = R.getVD("jets_BtagEff_TightWp");
	std::vector<double> jets_IsBTagged_LooseWpCentral = R.getVD("jets_IsBTagged_LooseWpCentral");
	std::vector<double> jets_IsBTagged_LooseWpUp = R.getVD("jets_IsBTagged_LooseWpUp");
	std::vector<double> jets_IsBTagged_LooseWpDown = R.getVD("jets_IsBTagged_LooseWpDown");
	std::vector<double> jets_IsBTagged_MediumWpCentral = R.getVD("jets_IsBTagged_MediumWpCentral");
	std::vector<double> jets_IsBTagged_MediumWpUp = R.getVD("jets_IsBTagged_MediumWpUp");
	std::vector<double> jets_IsBTagged_MediumWpDown = R.getVD("jets_IsBTagged_MediumWpDown");
	std::vector<double> jets_IsBTagged_TightWpCentral = R.getVD("jets_IsBTagged_TightWpCentral");
	std::vector<double> jets_IsBTagged_TightWpUp = R.getVD("jets_IsBTagged_TightWpUp");
	std::vector<double> jets_IsBTagged_TightWpDown = R.getVD("jets_IsBTagged_TightWpDown");
	std::vector<bool> jets_PF_jetIdPassedTight = R.getVB("jets_PF_jetIdPassedTight");



	//////////////////// JET TEST ----- START

	// std::cout<<" ****>>> event "<<event<<"\n";


	// int test_njet = 0;


	// for(unsigned int t=0; t<jets_pt.size();++t)
	// {
	// 	bool cut_pt20 = 0;
	// 	bool cut_eta = 0;
	// 	bool cut_pf = 0;
	// 	bool cut_dr1 = 0;
	// 	bool cut_dr2 = 0;
	// 	j1_20.SetPtEtaPhiM(jets_pt[t],jets_eta[t],jets_phi[t],jets_M[t]);


	// 	if(jets_pt[t] > 20.)  					cut_pt20 = 1;
	// 	if(fabs(jets_eta[t]) < 4.7)				cut_eta = 1;
	// 	if(jets_PF_jetIdPassed[t] > 0.5)		cut_pf = 1;
	// 	if(j1_20.DeltaR(l1)>0.5)				cut_dr1 = 1;	
	// 	if(j1_20.DeltaR(l2) > 0.5)				cut_dr2 = 1;

	// 	// turn off problematic cuts
	// 	cut_dr2 = 1;

	// 	if(cut_pt20 && cut_eta && cut_pf && cut_dr1 && cut_dr2)
	// 	{	
	// 		test_njet++;
	// 		std::cout<<" ****************************>>> jet of pt = "<<jets_pt[t]<<" passes all cuts \n";
	// 	}	
	// 	else 
	// 	{
	// 		std::cout<<" ****************************>>> jet of pt = "<<jets_pt[t]<<" fails: ";
	// 		if(cut_pt20 == 0) std::cout<<" [pt cut] ";
	// 		if(cut_eta == 0)  std::cout<<" [eta cut] "; 	
	// 		if(cut_pf == 0)	  std::cout<<" [pf cut] "; 	
	// 		if(cut_dr1 == 0)  std::cout<<" [dr1 cut] ";	
	// 		if(cut_dr2 == 0)  std::cout<<" [dr2 cut] ";
	// 		std::cout<<"\n";
	// 	}


	// }	

	// std::cout<<" ****************************>>> njet = "<<test_njet<<"\n";

	

	//////////////////// JET TEST ----- END





	j1_20.SetPtEtaPhiM(0.,0.,0.,0.);
	j2_20.SetPtEtaPhiM(0.,0.,0.,0.);
	njetingap = 0;
	njetingap20 = 0;
	njetspt20 = 0;
	njets = 0;
	nbtag = 0;

	std::size_t b1_index = 99999.0;
	std::size_t b2_index = 99999.0;

	//std::cout<<"////////////////////////////////////////////////////// \n";
	//std::cout<<" event "<<event<<" njets20 = "<<jets_pt.size()<<" \n";


	for(std::size_t i = 0; i<jets_pt.size();++i)
	{

		// std::cout<<" ---------- jet pt  "<<jets_pt[i]<<" jet eta "<<fabs(jets_eta[i]);
		// std::cout<<" pf_passID "<<jets_PF_jetIdPassed[i];
		// std::cout<<" btagged "<<jets_IsBTagged_MediumWpCentral[i]<<" ";
		// std::cout<<" rawScore "<<jets_defaultBtagAlgorithm_RawScore[i]<<" ";


//		std::cout<<" tau_pt "<<pt_2<<" muon_pt "<<pt_1;

		//std::cout<<"\n";


		if( fabs(jets_eta[i]) < 4.7 && jets_pt[i] > 20 ) njetspt20 ++;
		if( fabs(jets_eta[i]) < 4.7 && jets_pt[i] > 30 ) njets ++;
		//if( fabs(jets_eta[i]) < 2.4 && jets_pt[i] > 20 && jets_defaultBtagAlgorithm_RawScore[i] > 0.80)
		if( fabs(jets_eta[i]) < 2.4 && jets_pt[i] > 20 && jets_IsBTagged_MediumWpCentral[i] > 0.5)
		{ 
			if(b1_index == 99999.0) b1_index = i;
			else if(b2_index == 99999.0) b2_index = i; 
			nbtag ++;
		}
	}	

	//std::cout<<" ---------- njets30 = "<<njets<<"\n";


	if(b1_index != 99999.0)
	{	
		bpt_1 = jets_pt[b1_index];
		beta_1 = jets_eta[b1_index];
		bphi_1 = jets_phi[b1_index];
		bm_1 = jets_M[b1_index];
		/* not kept brawf_1 */
		bmva_1 = jets_PU_jetIdRaw[b1_index];
		bcsv_1 = jets_defaultBtagAlgorithm_RawScore[b1_index];
	}

	if(b2_index != 99999.0)
	{
		bpt_2 = jets_pt[b2_index];
		beta_2 = jets_eta[b2_index];
		bphi_2 = jets_phi[b2_index];
		bm_2 = jets_M[b2_index];
		/* not kept brawf_1 */
		bmva_2 = jets_PU_jetIdRaw[b2_index];
		bcsv_2 = jets_defaultBtagAlgorithm_RawScore[b2_index];
	}

	if(jets_pt.size() >= 1) 
	{
		j1_20.SetPtEtaPhiM(jets_pt[0],jets_eta[0],jets_phi[0],jets_M[0]);
		jpt_1 = jets_pt[0];
		jeta_1 = jets_eta[0];
		jphi_1 = jets_phi[0];
		jm_1 = jets_M[0];
		jmva_1 = jets_PU_jetIdRaw[0];
		/* we dont keep jrawf_1 */
	}


	if(jets_pt.size() >= 2)
	{	
		j2_20.SetPtEtaPhiM(jets_pt[1],jets_eta[1],jets_phi[1],jets_M[1]);
		jpt_2 = jets_pt[1];
		jeta_2 = jets_eta[1];
		jphi_2 = jets_phi[1];
		jm_2 = jets_M[1];
		jmva_2 = jets_PU_jetIdRaw[1];
		/* we dont keep jrawf_2 */


		mjj = (j1_20+j2_20).M();
	 	jdeta = (j1_20.Eta()-j2_20.Eta());
	 	jdphi = (j1_20.Phi()-j2_20.Phi());



		 if(jets_eta.size()>2)
		 {
		 	for(std::size_t i = 2; i<jets_eta.size();++i)
		 	{
		 		double current_eta = jets_eta[i];
		 		double low_bound = std::min(jets_eta[0],jets_eta[1]);
		 		double high_bound = std::max(jets_eta[0],jets_eta[1]);

		 		if(current_eta>low_bound && high_bound>current_eta)
		 		{
		 			if(jets_pt[i]>20) njetingap20++;
		 			if(jets_pt[i]>30) njetingap++;
		 		}
		 	}
		 }
	} // at least 2 jets




	// extra lepton + dilepton vetoes

	dilepton_veto = 0.0;
	extraelec_veto = 0.0;
	extramuon_veto = 0.0;

	if(R.getF("DiMuon_Flag") > 0.5 || R.getF("DiElectron_Flag") > 0.5) dilepton_veto = 1.0;
	if(R.getF("ThirdElectron_Flag") > 0.5) extraelec_veto = 1.0;
	if(R.getF("ThirdMuon_Flag") > 0.5) extramuon_veto = 1.0;


	NUP = R.getI("hepNUP");
	generatorEventWeight = R.getD("generatorEventWeight");

	// information related to sample and weights

	DataSet = R.getS("DataSet");
    EventTotal = R.getI("EventTotal");
    EventType = R.getS("EventType");
    KeyName =  R.getS("KeyName");
    CrossSection =  R.getD("CrossSection");  
    FilterEff =  R.getD("FilterEff");



	if(R.getI("CandidateEventType")==3) {num_et++; tree_EleTau->Fill();}
	else if(R.getI("CandidateEventType")==2){num_em++; tree_EleMu->Fill();}
	else if(R.getI("CandidateEventType")==5){num_mt++; tree_MuTau->Fill();}
	else if(R.getI("CandidateEventType")==6) {num_tt++; tree_TauTau->Fill();}
	

	if(num_total%1000==0){
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

	T->Branch("pairRank",&pairRank);
	T->Branch("isOsPair",&isOsPair);
	
	T->Branch("run",&run);
	T->Branch("event",&event);
	T->Branch("lumi",&lumi);

	T->Branch("npv",&npv);
	T->Branch("npu",&npu);
	T->Branch("rho",&rho);
	T->Branch("puweight",&puweight);

	T->Branch("pt_1", &pt_1);
	T->Branch("phi_1", &phi_1);
	T->Branch("eta_1", &eta_1);
	T->Branch("m_1", &m_1);
	T->Branch("q_1", &q_1);
	T->Branch("d0_1", &d0_1);
	T->Branch("dZ_1", &dZ_1);
	T->Branch("mt_1", &mt_1);
	T->Branch("pfmt_1", &pfmt_1);
	T->Branch("puppimt_1", &puppimt_1);
	T->Branch("iso_1", &iso_1);
	T->Branch("id_e_mva_nt_loose_1", &id_e_mva_nt_loose_1);
	T->Branch("gen_match_1", &gen_match_1);
	T->Branch("againstElectronLooseMVA6_1", &againstElectronLooseMVA6_1);
	T->Branch("againstElectronMediumMVA6_1", &againstElectronMediumMVA6_1);
	T->Branch("againstElectronTightMVA6_1", &againstElectronTightMVA6_1);
	T->Branch("againstElectronVLooseMVA6_1", &againstElectronVLooseMVA6_1);
	T->Branch("againstElectronVTightMVA6_1", &againstElectronVTightMVA6_1);
	T->Branch("againstMuonLoose3_1", &againstMuonLoose3_1);
	T->Branch("againstMuonTight3_1", &againstMuonTight3_1);
	T->Branch("byCombinedIsolationDeltaBetaCorrRaw3Hits_1", &byCombinedIsolationDeltaBetaCorrRaw3Hits_1);
	T->Branch("byIsolationMVA3newDMwoLTraw_1", &byIsolationMVA3newDMwoLTraw_1);
	T->Branch("byIsolationMVA3oldDMwoLTraw_1", &byIsolationMVA3oldDMwoLTraw_1);
	T->Branch("byIsolationMVA3newDMwLTraw_1", &byIsolationMVA3newDMwLTraw_1);
	T->Branch("byIsolationMVA3oldDMwLTraw_1", &byIsolationMVA3oldDMwLTraw_1);
	T->Branch("chargedIsoPtSum_1", &chargedIsoPtSum_1);
	T->Branch("decayModeFindingOldDMs_1", &decayModeFindingOldDMs_1);
	T->Branch("neutralIsoPtSum_1", &neutralIsoPtSum_1);
	T->Branch("puCorrPtSum_1", &puCorrPtSum_1);
	//T->Branch("trigweight_1", &trigweight_1);
	//T->Branch("idisoweight_1", &idisoweight_1);

	T->Branch("pt_2", &pt_2);
	T->Branch("phi_2", &phi_2);
	T->Branch("eta_2", &eta_2);
	T->Branch("m_2", &m_2);
	T->Branch("q_2", &q_2);
	T->Branch("d0_2", &d0_2);
	T->Branch("dZ_2", &dZ_2);
	T->Branch("mt_2", &mt_2);
	T->Branch("pfmt_2", &pfmt_2);
	T->Branch("puppimt_2", &puppimt_2);
	T->Branch("iso_2", &iso_2);
	T->Branch("id_e_mva_nt_loose_2", &id_e_mva_nt_loose_2);
	T->Branch("gen_match_2", &gen_match_2);
	T->Branch("againstElectronLooseMVA6_2", &againstElectronLooseMVA6_2);
	T->Branch("againstElectronMediumMVA6_2", &againstElectronMediumMVA6_2);
	T->Branch("againstElectronTightMVA6_2", &againstElectronTightMVA6_2);
	T->Branch("againstElectronVLooseMVA6_2", &againstElectronVLooseMVA6_2);
	T->Branch("againstElectronVTightMVA6_2", &againstElectronVTightMVA6_2);
	T->Branch("againstMuonLoose3_2", &againstMuonLoose3_2);
	T->Branch("againstMuonTight3_2", &againstMuonTight3_2);
	T->Branch("byCombinedIsolationDeltaBetaCorrRaw3Hits_2", &byCombinedIsolationDeltaBetaCorrRaw3Hits_2);
	T->Branch("byIsolationMVA3newDMwoLTraw_2", &byIsolationMVA3newDMwoLTraw_2);
	T->Branch("byIsolationMVA3oldDMwoLTraw_2", &byIsolationMVA3oldDMwoLTraw_2);
	T->Branch("byIsolationMVA3newDMwLTraw_2", &byIsolationMVA3newDMwLTraw_2);
	T->Branch("byIsolationMVA3oldDMwLTraw_2", &byIsolationMVA3oldDMwLTraw_2);
	T->Branch("chargedIsoPtSum_2", &chargedIsoPtSum_2);
	T->Branch("decayModeFindingOldDMs_2", &decayModeFindingOldDMs_2);
	T->Branch("neutralIsoPtSum_2", &neutralIsoPtSum_2);
	T->Branch("puCorrPtSum_2", &puCorrPtSum_2);
	//T->Branch("trigweight_2", &trigweight_2);
	//T->Branch("idisoweight_2", &idisoweight_2);

	T->Branch("pt_tt", &pt_tt);
	T->Branch("mt_tot", &mt_tot);
	T->Branch("m_vis", &m_vis);
	T->Branch("m_sv", &m_sv);
	T->Branch("mt_sv", &mt_sv);

	T->Branch("met", &met);
	T->Branch("metphi", &metphi);
	T->Branch("puppimet", &puppimet);
	T->Branch("puppimetphi", &puppimetphi);
	T->Branch("mvamet", &mvamet);
	T->Branch("mvametphi", &mvametphi);
	T->Branch("pzetavis", &pzetavis);
	T->Branch("pzetamiss", &pzetamiss);
	T->Branch("pfpzetamiss", &pfpzetamiss);
	T->Branch("puppipzetamiss", &puppipzetamiss);
	T->Branch("mvacov00", &mvacov00);
	T->Branch("mvacov01", &mvacov01);
	T->Branch("mvacov10", &mvacov10);
	T->Branch("mvacov11", &mvacov11);
	T->Branch("metcov00", &metcov00);
	T->Branch("metcov01", &metcov01);
	T->Branch("metcov10", &metcov10);
	T->Branch("metcov11", &metcov11);


	T->Branch("mjj", &mjj);
	T->Branch("jdeta", &jdeta);
	T->Branch("njetingap", &njetingap);
	T->Branch("njetingap20", &njetingap20);
	T->Branch("jdphi", &jdphi);

	T->Branch("nbtag", &nbtag);
	T->Branch("njets", &njets);
	T->Branch("njetspt20", &njetspt20);

	T->Branch("jpt_1", &jpt_1);
	T->Branch("jeta_1", &jeta_1);
	T->Branch("jphi_1", &jphi_1);
	T->Branch("jm_1", &jm_1);
	T->Branch("jrawf_1", &jrawf_1);
	T->Branch("jmva_1", &jmva_1);

	T->Branch("jpt_2", &jpt_2);
	T->Branch("jeta_2", &jeta_2);
	T->Branch("jphi_2", &jphi_2);
	T->Branch("jm_2", &jm_2);
	T->Branch("jrawf_2", &jrawf_2);
	T->Branch("jmva_2", &jmva_2);

	T->Branch("bpt_1", &bpt_1);
	T->Branch("beta_1", &beta_1);
	T->Branch("bphi_1", &bphi_1);
	T->Branch("bm_1", &bm_1);
	T->Branch("brawf_1", &brawf_1);
	T->Branch("bmva_1", &bmva_1);
	T->Branch("bcsv_1", &bcsv_1);

	T->Branch("bpt_2", &bpt_2);
	T->Branch("beta_2", &beta_2);
	T->Branch("bphi_2", &bphi_2);
	T->Branch("bm_2", &bm_2);
	T->Branch("brawf_2", &brawf_2);
	T->Branch("bmva_2", &bmva_2);
	T->Branch("bcsv_2", &bcsv_2);

	T->Branch("dilepton_veto", &dilepton_veto);
	T->Branch("extraelec_veto", &extraelec_veto);
	T->Branch("extramuon_veto", &extramuon_veto);

	T->Branch("NUP", &NUP);
	T->Branch("weight", &weight);
	T->Branch("generatorEventWeight", &generatorEventWeight);

	T->Branch("DataSet", &DataSet);
	T->Branch("EventTotal", &EventTotal);
	T->Branch("EventType", &EventType);
	T->Branch("KeyName", &KeyName);
	T->Branch("CrossSection", &CrossSection);
	T->Branch("FilterEff", &FilterEff);

}

double generateH2TauSyncTree::mtTotCalc(TLorentzVector l1, TLorentzVector l2, TLorentzVector met )
{
        double value = 0.;

        double part1 = 2 * l1.Pt() * met.Pt() * (1-cos(l1.DeltaPhi(met)));
        double part2 = 2 * l2.Pt() * met.Pt() * (1-cos(l2.DeltaPhi(met)));
        double part3 = 2 * l1.Pt() * l2.Pt()  * (1-cos(l1.DeltaPhi(l2)));

        if( part1 + part2 + part3 > 0) value = sqrt( part1 + part2 + part3 );

        return value;
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
{	/* OLD no longer used for >= 76X */
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

	pairRank = 999;
	isOsPair = -999;

	run = 0;
	event = 0;
	lumi = 0;


	npv =  0;
	npu =  -999.0;
	rho =  -999.0;
	puweight = 1.0;

	pt_1  = -999.0;
	phi_1  = -999.0;
	eta_1  = -999.0;
	m_1  = -999.0;
	q_1  = 0;
	d0_1  = -999.0;
	dZ_1  = -999.0;
	mt_1  = -999.0;
	pfmt_1  = -999.0;
	puppimt_1  = -999.0;
	iso_1  = -999.0;
	id_e_mva_nt_loose_1  = -999.0;
	gen_match_1  = 0;
	againstElectronLooseMVA6_1  = -999.0;
	againstElectronMediumMVA6_1  = -999.0;
	againstElectronTightMVA6_1  = -999.0;
	againstElectronVLooseMVA6_1  = -999.0;
	againstElectronVTightMVA6_1  = -999.0;
	againstMuonLoose3_1  = -999.0;
	againstMuonTight3_1  = -999.0;
	byCombinedIsolationDeltaBetaCorrRaw3Hits_1  = -999.0;
	byIsolationMVA3newDMwoLTraw_1  = -999.0;
	byIsolationMVA3oldDMwoLTraw_1  = -999.0;
	byIsolationMVA3newDMwLTraw_1  = -999.0;
	byIsolationMVA3oldDMwLTraw_1  = -999.0;
	chargedIsoPtSum_1  = -999.0;
	decayModeFindingOldDMs_1  = -999.0;
	neutralIsoPtSum_1  = -999.0;
	puCorrPtSum_1  = -999.0;
	// trigweight_1  = -999.0;
	// idisoweight_1  = -999.0;

	pt_2  = -999.0;
	phi_2  = -999.0;
	eta_2  = -999.0;
	m_2  = -999.0;
	q_2  = 0;
	d0_2  = -999.0;
	dZ_2  = -999.0;
	mt_2  = -999.0;
	pfmt_2  = -999.0;
	puppimt_2  = -999.0;
	iso_2  = -999.0;
	id_e_mva_nt_loose_2  = -999.0;
	gen_match_2  = 0;
	againstElectronLooseMVA6_2  = -999.0;
	againstElectronMediumMVA6_2  = -999.0;
	againstElectronTightMVA6_2  = -999.0;
	againstElectronVLooseMVA6_2  = -999.0;
	againstElectronVTightMVA6_2  = -999.0;
	againstMuonLoose3_2  = -999.0;
	againstMuonTight3_2  = -999.0;
	byCombinedIsolationDeltaBetaCorrRaw3Hits_2  = -999.0;
	byIsolationMVA3newDMwoLTraw_2  = -999.0;
	byIsolationMVA3oldDMwoLTraw_2  = -999.0;
	byIsolationMVA3newDMwLTraw_2  = -999.0;
	byIsolationMVA3oldDMwLTraw_2  = -999.0;
	chargedIsoPtSum_2  = -999.0;
	decayModeFindingOldDMs_2  = -999.0;
	neutralIsoPtSum_2  = -999.0;
	puCorrPtSum_2  = -999.0;
	// trigweight_2  = -999.0;
	// idisoweight_2  = -999.0;
	
	pt_tt =  -999.0;
	mt_tot =  -999.0;
	m_vis =  -999.0;
	m_sv =  -999.0;
	mt_sv =  -999.0;

	met =  -999.0;
	metphi =  -999.0;
	puppimet =  -999.0;
	puppimetphi =  -999.0;
	mvamet =  -999.0;
	mvametphi =  -999.0;
	pzetavis =  -999.0;
	pzetamiss =  -999.0;    
	pfpzetamiss =  -999.0;  
	puppipzetamiss =  -999.0; 
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
	jm_1   = -999.0;
	jrawf_1 =  -999.0;
	jmva_1 =  -999.0;
	 
	 
	jpt_2 =  -999.0;
	jeta_2 =  -999.0;
	jphi_2 =  -999.0;
	jm_2   = -999.0;
	jrawf_2 =  -999.0;
	jmva_2 =  -999.0;
	 
	 
	bpt_1 =  -999.0;
	beta_1 =  -999.0;
	bphi_1 =  -999.0;
	bm_1 = -999.0;
	brawf_1 =  -999.0;
	bmva_1 =  -999.0;
	bcsv_1 =  -999.0;
	 
	 
	bpt_2 =  -999.0;
	beta_2 =  -999.0;
	bphi_2 =  -999.0;
	bm_2 = -999.0;
	brawf_2 =  -999.0;
	bmva_2 =  -999.0;
	bcsv_2 =  -999.0;

	dilepton_veto = 0;	
	extraelec_veto = 0; 	
	extramuon_veto = 0;

	NUP = 0;
	weight  = 1.0;
	generatorEventWeight = 1.0;

	DataSet = "NULL";
    EventTotal = 1;
    EventType = "NULL";
    KeyName = "NULL"; 
    CrossSection = 1.0;    
    FilterEff = 1.0; 
}
