#include "generateH2TauSyncTree.h"



generateH2TauSyncTree::generateH2TauSyncTree(FlatTreeReader R_, bool run_)
{
	m_run = run_;
	R = R_;

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

	run = R.getUI("run");
	event = R.getUI("event");
	lumi = R.getUI("luminosityBlock");

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
		byIsolationMVA3newDMwoLTraw_1 = R.getF("leg1_byIsolationMVA3newDMwoLTraw");
		byIsolationMVA3oldDMwoLTraw_1 = R.getF("leg1_byIsolationMVA3oldDMwoLTraw");
		byIsolationMVA3newDMwLTraw_1 = R.getF("leg1_byIsolationMVA3newDMwLTraw");
		byIsolationMVA3oldDMwLTraw_1 = R.getF("leg1_byIsolationMVA3oldDMwLTraw");
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
		byIsolationMVA3newDMwoLTraw_2 = R.getF("leg2_byIsolationMVA3newDMwoLTraw");
		byIsolationMVA3oldDMwoLTraw_2 = R.getF("leg2_byIsolationMVA3oldDMwoLTraw");
		byIsolationMVA3newDMwLTraw_2 = R.getF("leg2_byIsolationMVA3newDMwLTraw");
		byIsolationMVA3oldDMwLTraw_2 = R.getF("leg2_byIsolationMVA3oldDMwLTraw");
		chargedIsoPtSum_2 = R.getF("leg2_chargedIsoPtSum");
		decayModeFindingNewDMs_2 = R.getF("leg2_decayModeFindingNewDMs");
		neutralIsoPtSum_2 = R.getF("leg2_neutralIsoPtSum");
		puCorrPtSum_2 = R.getF("leg2_puCorrPtSum");	
	}



	std::cout<<" --- --------------\n ";

	std::cout<<R.getI("CandidateEventType")<<"\n";
	std::cout<<R.getI("CandidateEventType")<<"\n";

	/* see TupleCandidateEventTypes */
	if(R.getI("CandidateEventType")==2) tree_EleMu->Fill();
	else if(R.getI("CandidateEventType")==3) tree_EleTau->Fill();
	else if(R.getI("CandidateEventType")==5) tree_MuTau->Fill();
	else if(R.getI("CandidateEventType")==6) tree_TauTau->Fill();
	

}

void generateH2TauSyncTree::setupBranches(TTree * T)
{
	/* all trees get same branch address, but will only write event
	 to one tree per event based on CandidateEventType */

	T->Branch("run",&run);
	T->Branch("event",&event);
	T->Branch("lumi",&lumi);
	
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


}


