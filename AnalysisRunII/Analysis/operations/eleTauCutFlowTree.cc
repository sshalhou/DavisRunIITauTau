#include "eleTauCutFlowTree.h"



eleTauCutFlowTree::eleTauCutFlowTree(FlatTreeReader R_, bool run_)
{
	m_run = run_;
	R = R_;


	if(m_run)
	{

	outFile_EleTau  = new TFile("davis_cutFlow_EleTau.root","RECREATE");	
	tree_EleTau = new TTree("tree_EleTau","tree_EleTau");
	setupBranches(tree_EleTau);

	
	}

	else
	{
		outFile_EleTau  = nullptr; 	
		tree_EleTau = nullptr;
	}

}



void eleTauCutFlowTree::finish()
{
	if(m_run)
	{
	
		outFile_EleTau->cd();
		tree_EleTau->CloneTree()->Write("TauCheck");		
		outFile_EleTau->Close();


	}
}

eleTauCutFlowTree::~eleTauCutFlowTree()
{
	if(!m_run) /* Close on the outFile deletes the TH1F pointers */
	{
		delete tree_EleTau;

	}	
	delete outFile_EleTau;

	

};	

void eleTauCutFlowTree::handleEvent()
{
	// reset values
	reset();

	


	///// the tree elements

	run = R.getUI("run");
	event = R.getUI("event");
	lumi = R.getUI("luminosityBlock");
	
	if(R.getI("CandidateEventType")==3) isCorrectChannel = 1;
	if(R.getI("isOsPair")==1) isOsPair = 1;
	if(R.getUI("pairRank")==0) pairRank = 1;

	if(R.getD("leg1_pt") > 23.0 ) leg1_pt = 1;
	if(fabs(R.getD("leg1_eta")) < 2.1 ) leg1_eta = 1;
	if(fabs(R.getF("leg1_dxy")) < 0.045 ) leg1_dxy = 1;
	if(fabs(R.getF("leg1_dz")) < 0.2 ) leg1_dz = 1;
	if(R.getF("leg1_numberOfMissingInnerHits") <= 1 ) leg1_numberOfMissingInnerHits = 1;
	if(R.getF("leg1_passConversionVeto") == 1 ) leg1_passConversionVeto = 1;
	if(R.getF("leg1_passFail_electronMVA80") == 1 ) leg1_passFail_electronMVA80 = 1;


	if(R.getD("leg2_pt") > 20.0 ) leg2_pt = 1;
	if(fabs(R.getD("leg2_eta")) < 2.3 ) leg2_eta = 1;
	if(R.getF("leg2_decayModeFindingNewDMs") > 0.5 ) leg2_decayModeFindingNewDMs = 1;
	if(fabs(R.getF("leg2_dz")) < 0.2 ) leg2_dz = 1;
	if(fabs(R.getI("leg2_charge")) == 1 ) leg2_charge = 1;
	if(fabs(R.getF("leg2_dzTauVertex")) == 0 ) leg2_dzTauVertex = 1;
	if(R.getF("leg1_HLT_Ele32_eta2p1_WP75_Gsf")==1 && R.getD("leg1_pt")>33) single_obj_trigger = 1;
	if(R.getF("leg1_HLT_Ele32_eta2p1_WP75_Gsf")==1 ) single_obj_trigger_withoutPtCut = 1;
	if(R.getF("leg1_HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20")==1 && R.getF("leg2_HLT_Ele22_eta2p1_WP75_Gsf_LooseIsoPFTau20")==1) double_obj_trigger = 1;
	triggerOR = ( single_obj_trigger || double_obj_trigger);


	tree_EleTau->Fill();


}

void eleTauCutFlowTree::setupBranches(TTree * T)
{
	/* all trees get same branch address, but will only write event
	 to one tree per event based on CandidateEventType */

	T->Branch("run",&run);
	T->Branch("event",&event);
	T->Branch("lumi",&lumi);
	T->Branch("isCorrectChannel", &isCorrectChannel);
	T->Branch("pairRank", &pairRank);
	T->Branch("isOsPair", &isOsPair);
	T->Branch("leg1_pt", &leg1_pt);
	T->Branch("leg1_eta", &leg1_eta);
	T->Branch("leg1_dxy", &leg1_dxy);
	T->Branch("leg1_dz", &leg1_dz);
	T->Branch("leg1_numberOfMissingInnerHits", &leg1_numberOfMissingInnerHits);
	T->Branch("leg1_passConversionVeto", &leg1_passConversionVeto);
	T->Branch("leg1_passFail_electronMVA80", &leg1_passFail_electronMVA80);
	T->Branch("leg2_pt", &leg2_pt);
	T->Branch("leg2_eta", &leg2_eta);
	T->Branch("leg2_decayModeFindingNewDMs", &leg2_decayModeFindingNewDMs);
	T->Branch("leg2_dz", &leg2_dz);
	T->Branch("leg2_charge", &leg2_charge);
	T->Branch("leg2_dzTauVertex", &leg2_dzTauVertex);
	T->Branch("single_obj_trigger", &single_obj_trigger);
	T->Branch("single_obj_trigger_withoutPtCut", &single_obj_trigger_withoutPtCut);
	T->Branch("double_obj_trigger", &double_obj_trigger);
	T->Branch("triggerOR", &triggerOR);



}



void eleTauCutFlowTree::reset()
{

	run = 0;
	event = 0;
	lumi = 0;
	isCorrectChannel = 0;
	isOsPair = 0;
	pairRank = 0;
	leg1_pt = 0;
	leg1_eta = 0;
	leg1_dxy = 0;
	leg1_dz = 0;
	leg1_numberOfMissingInnerHits = 0;
	leg1_passConversionVeto = 0;
	leg1_passFail_electronMVA80 = 0;
	leg2_pt = 0;
	leg2_eta = 0;
	leg2_decayModeFindingNewDMs = 0;
	leg2_dz = 0;
	leg2_charge = 0;
	leg2_dzTauVertex = 0;
	single_obj_trigger = 0;
	single_obj_trigger_withoutPtCut	 = 0;
	double_obj_trigger = 0;
	triggerOR = 0;
	
}
