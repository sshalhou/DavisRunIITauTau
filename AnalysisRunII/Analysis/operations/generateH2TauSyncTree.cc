#include "generateH2TauSyncTree.h"
#include <iostream>
#include <fstream>
#include <string>


generateH2TauSyncTree::generateH2TauSyncTree(FlatTreeReader R_, bool run_, std::string fileOutName_)
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

	std::string MuTauName = "davis_syncTree_"+fileOutName_+"MuTau.root";
	std::string EleTauName = "davis_syncTree_"+fileOutName_+"EleTau.root";
	std::string TauTauName = "davis_syncTree_"+fileOutName_+"TauTau.root";
	std::string EleMuName = "davis_syncTree_"+fileOutName_+"EleMu.root";


	outFile_MuTau = new TFile(MuTauName.c_str(),"RECREATE");
	outFile_EleTau  = new TFile(EleTauName.c_str(),"RECREATE");
	outFile_TauTau  = new TFile(TauTauName.c_str(),"RECREATE");
	outFile_EleMu  = new TFile(EleMuName.c_str(),"RECREATE");

	tree_MuTau = new TTree("tree_MuTau","tree_MuTau");
	tree_EleTau = new TTree("tree_EleTau","tree_EleTau");
	tree_TauTau = new TTree("tree_TauTau","tree_TauTau");
	tree_EleMu = new TTree("tree_EleMu","tree_EleMu");

	setupBranches(tree_MuTau);
	setupBranches(tree_EleTau);
	setupBranches(tree_TauTau);
	setupBranches(tree_EleMu);

	/* init the susy signal pt reweight tool */
	NLO_ReadFile();	


	/* init qcd weight tool */


	// with DZeta cut ->
	qcdWeights = new QCDModelForEMu("QCD_weight_emu.root");

	// w/o DZeta cut ->
	qcdWeightsNoDZeta = new QCDModelForEMu("QCD_weight_emu_nodzeta.root");


	/* init lepton sf tool */

	sfTool_Muon_IdIso0p10_eff = new ScaleFactor();
	sfTool_Muon_SingleMu_eff = new ScaleFactor();
	sfTool_Muon_IdIso0p15_eff = new ScaleFactor();
	sfTool_Electron_IdIso0p10_eff = new ScaleFactor();
	sfTool_Electron_SingleEle_eff = new ScaleFactor();
	sfTool_Electron_IdIso0p15_eff = new ScaleFactor();
	sfTool_Muon_Mu8_eff = new ScaleFactor();
	sfTool_Muon_Mu17_eff = new ScaleFactor();
	sfTool_Electron_Ele17_eff = new ScaleFactor();
	sfTool_Electron_Ele12_eff = new ScaleFactor();

	sfTool_Muon_IdIso0p10_eff->init_ScaleFactor("Muon_IdIso0p1_fall15.root");
	sfTool_Muon_SingleMu_eff->init_ScaleFactor("Muon_SingleMu_eff.root");
	sfTool_Muon_IdIso0p15_eff->init_ScaleFactor("Muon_IdIso0p15_fall15.root");
	sfTool_Electron_IdIso0p10_eff->init_ScaleFactor("Electron_IdIso0p1_fall15.root");
	sfTool_Electron_SingleEle_eff->init_ScaleFactor("Electron_SingleEle_eff.root");
	sfTool_Electron_IdIso0p15_eff->init_ScaleFactor("Electron_IdIso0p15_fall15.root");
	sfTool_Muon_Mu8_eff->init_ScaleFactor("Muon_Mu8_fall15.root");
	sfTool_Muon_Mu17_eff->init_ScaleFactor("Muon_Mu17_fall15.root");
	sfTool_Electron_Ele17_eff->init_ScaleFactor("Electron_Ele17_fall15.root");
	sfTool_Electron_Ele12_eff->init_ScaleFactor("Electron_Ele12_fall15.root");

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


	initScaleFactorParametersRunII();

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

	/* count the total events seen */

	num_total ++; 


	/* reset values before handling each event */

	reset();

    /* set tMVA flag type */
    float FRACTION_  = 0.1; /* this is how much of a mc sample is testing, and training - so 0.1 means 10% test, 10% train, 80% analysis */
    TRandom3 rand_;
    rand_.SetSeed(0); /* unique random pattern, once before the event loop */
    float randVal = rand_.Uniform(1.);
    
    if (randVal < FRACTION_)
    {
        flag_MVAEventType = 0;
    }
    else if ((randVal > FRACTION_) && (randVal < 2.*FRACTION_))
    {
        flag_MVAEventType = 1;
    }
    else {flag_MVAEventType = -1;}

	/* note: two factors can control what variables are available in the FlatTuple 
	  -- (1) both tau ES and electron ES are nominal (it will be nan for channels without e or tau)
	  -- (2) the FlatTuple was not produced under small tree conditions 
	
	  the following booleans will allow us to handle the differences in FlatTuple content without 
	  reader asserts
	*/

	bool eventHasNominalLeptonEnergyScales = (fabs(R.getF("TauEsNumberSigmasShifted")) != 1. && fabs(R.getF("ElectronEsNumberSigmasShifted")) != 1.);
	bool eventIsNotSmallTree = !(R.getB("isSmallTree"));


	/* declare & init 4-vectors for computation of event quantities */

	TLorentzVector l1(0.,0.,0.,0.); /* leg1 */
	TLorentzVector l2(0.,0.,0.,0.); /* leg2 */

	TLorentzVector mvaMetVec(0.,0.,0.,0.);	
	TLorentzVector mvaMetVec_uncorr(0.,0.,0.,0.);	
	TLorentzVector mvaMetVec_responseUP(0.,0.,0.,0.);	
	TLorentzVector mvaMetVec_responseDOWN(0.,0.,0.,0.);	
	TLorentzVector mvaMetVec_resolutionUP(0.,0.,0.,0.);	
	TLorentzVector mvaMetVec_resolutionDOWN(0.,0.,0.,0.);	
	TLorentzVector pfMetVec(0.,0.,0.,0.);
	TLorentzVector puppiMetVec(0.,0.,0.,0.);

	/* set leg1 4-vector */

	l1.SetPtEtaPhiM(R.getD("leg1_pt"),R.getD("leg1_eta"),R.getD("leg1_phi"),R.getD("leg1_M"));

	/* set the leg2 4-vector */

	l2.SetPtEtaPhiM(R.getD("leg2_pt"),R.getD("leg2_eta"),R.getD("leg2_phi"),R.getD("leg2_M"));


	/* set the MET 4-vectors */

	mvaMetVec.SetPtEtaPhiM(R.getD("corr_mvaMET"),0.0,R.getD("corr_mvaMETphi"),0.0);
	mvaMetVec_uncorr.SetPtEtaPhiM(R.getD("uncorr_mvaMET"),0.0,R.getD("uncorr_mvaMETphi"),0.0);

	/* some variants of met are only stored for nominal Energy scale */

   	if(eventHasNominalLeptonEnergyScales)
   	{
		mvaMetVec_responseUP.SetPtEtaPhiM(R.getD("responseUP_mvaMET"),0.0,R.getD("responseUP_mvaMETphi"),0.0);
		mvaMetVec_responseDOWN.SetPtEtaPhiM(R.getD("responseDOWN_mvaMET"),0.0,R.getD("responseDOWN_mvaMETphi"),0.0);
		mvaMetVec_resolutionUP.SetPtEtaPhiM(R.getD("resolutionUP_mvaMET"),0.0,R.getD("resolutionUP_mvaMETphi"),0.0);
		mvaMetVec_resolutionDOWN.SetPtEtaPhiM(R.getD("resolutionDOWN_mvaMET"),0.0,R.getD("resolutionDOWN_mvaMETphi"),0.0);
   	}

   	/* alternate mets */

	pfMetVec.SetPtEtaPhiM(R.getD("pfMET"),0.0,R.getD("pfMETphi"),0.0);
	puppiMetVec.SetPtEtaPhiM(R.getD("puppiMET"),0.0,R.getD("puppiMETphi"),0.0);


    /* The LHE weights & Scale Factor Vector, mapping is available in FlatTuple production log file */
    
    originalXWGTUP = R.getF("originalXWGTUP");
    
    if( R.getS("DataCard") == "SIGNAL_MONO_HIGGS" && eventHasNominalLeptonEnergyScales)
    {
        theory_scale_factors = R.getVF("theory_scale_factors");
    }


    /* basic info */

	pairRank = R.getUI("pairRank");
 	isOsPair = R.getI("isOsPair");


 	/* gen boson/top info */

	genBosonTotal_pt = R.getD("genBosonTotal_pt"); 
    genBosonTotal_eta = R.getD("genBosonTotal_eta");
    genBosonTotal_phi = R.getD("genBosonTotal_phi");
    genBosonTotal_M = R.getD("genBosonTotal_M");

	genBosonVisible_pt = R.getD("genBosonVisible_pt");
	genBosonVisible_eta = R.getD("genBosonVisible_eta");
	genBosonVisible_phi = R.getD("genBosonVisible_phi");
	genBosonVisible_M = R.getD("genBosonVisible_M");

	genTopPt1 = R.getD("genTopPt1");
	genTopPt2 = R.getD("genTopPt2");

	/* event ID */

	run = R.getUI("run");
	event = R.getUI("event");
	evt = R.getUI("event");
	lumi = R.getUI("luminosityBlock");

	/* vertices & pileup */

	npv = R.getI("NumberOfGoodVertices");
 	npu = R.getF("NumTruePileUpInt");
 	rho = R.getD("rho");
 	puweight = R.getD("puWeight");

	/* leg 1 quantities */

 	pt_1 				= R.getD("leg1_pt");
	phi_1 				= R.getD("leg1_phi");
	eta_1 				= R.getD("leg1_eta");
	m_1 				= R.getD("leg1_M");
	iso_1 				= R.getF("leg1_RelIso");
	dZ_1 				= R.getF("leg1_dz");
	d0_1 				= R.getF("leg1_dxy");
	q_1 				= R.getI("leg1_charge");
	id_e_mva_nt_loose_1 = R.getF("leg1_raw_electronMVA");
	tau_decay_mode_1 	= R.getI("leg1_decayMode");
	ZimpactTau_1 		= R.getF("leg1_ZimpactTau");
	dzTauVertex_1 		= R.getF("leg1_dzTauVertex");
	mt_1  				= R.getD("corr_MTmvaMET_leg1");
	pfmt_1 				= GetTransverseMass(pfMetVec,l1);
	puppimt_1 			= GetTransverseMass(puppiMetVec,l1);
	mt_uncorr_1   		= GetTransverseMass(mvaMetVec_uncorr,l1);

	if(eventHasNominalLeptonEnergyScales)
	{
		responseUP_MTmvaMET_1		=  GetTransverseMass(mvaMetVec_responseUP,l1);
		responseDOWN_MTmvaMET_1		=  GetTransverseMass(mvaMetVec_responseDOWN,l1);
		resolutionUP_MTmvaMET_1		=  GetTransverseMass(mvaMetVec_resolutionUP,l1);
		resolutionDOWN_MTmvaMET_1	=  GetTransverseMass(mvaMetVec_resolutionDOWN,l1);
	}


	gen_match_1 		= R.getI("leg1_MCMatchType");
	genMCmatch_pt_1		= R.getD("leg1_genMCmatch_pt");
	genMCmatch_eta_1	= R.getD("leg1_genMCmatch_eta");
	genMCmatch_phi_1	= R.getD("leg1_genMCmatch_phi");
	genMCmatch_M_1		= R.getD("leg1_genMCmatch_M");
	MCMatchPdgId_1		= R.getI("leg1_MCMatchPdgId");


	byIsolationMVArun2v1DBoldDMwLTraw_1 = R.getF("leg1_byIsolationMVArun2v1DBoldDMwLTraw");
	byTightIsolationMVArun2v1DBoldDMwLT_1 = R.getF("leg1_byTightIsolationMVArun2v1DBoldDMwLT");
	byVTightIsolationMVArun2v1DBoldDMwLT_1 = R.getF("leg1_byVTightIsolationMVArun2v1DBoldDMwLT");
	byLooseIsolationMVArun2v1DBoldDMwLT_1 = R.getF("leg1_byLooseIsolationMVArun2v1DBoldDMwLT");
	byMediumIsolationMVArun2v1DBoldDMwLT_1 = R.getF("leg1_byMediumIsolationMVArun2v1DBoldDMwLT");
	byVLooseIsolationMVArun2v1DBoldDMwLT_1 = R.getF("leg1_byVLooseIsolationMVArun2v1DBoldDMwLT");
	byVVTightIsolationMVArun2v1DBoldDMwLT_1 = R.getF("leg1_byVVTightIsolationMVArun2v1DBoldDMwLT");
	againstElectronVLooseMVA6_1 = R.getF("leg1_againstElectronVLooseMVA6");
	againstMuonTight3_1 = R.getF("leg1_againstMuonTight3");
	againstElectronTightMVA6_1 = R.getF("leg1_againstElectronTightMVA6");
	againstMuonLoose3_1 = R.getF("leg1_againstMuonLoose3");
	decayModeFinding_1 = R.getF("leg1_decayModeFinding");
	byIsolationMVA3oldDMwLTraw_1 = R.getF("leg1_byIsolationMVA3oldDMwLTraw");
	byCombinedIsolationDeltaBetaCorrRaw3Hits_1 = R.getF("leg1_byCombinedIsolationDeltaBetaCorrRaw3Hits");
	byIsolationMVArun2v1DBnewDMwLTraw_1 = R.getF("leg1_byIsolationMVArun2v1DBnewDMwLTraw");
	decayModeFindingNewDMs_1 = R.getF("leg1_decayModeFindingNewDMs");


	/* leg 2 quantities */

 	pt_2 				= R.getD("leg2_pt");
	phi_2 				= R.getD("leg2_phi");
	eta_2 				= R.getD("leg2_eta");
	m_2 				= R.getD("leg2_M");
	iso_2 				= R.getF("leg2_RelIso");
	dZ_2 				= R.getF("leg2_dz");
	d0_2 				= R.getF("leg2_dxy");
	q_2 				= R.getI("leg2_charge");
	id_e_mva_nt_loose_2 = R.getF("leg2_raw_electronMVA");
	tau_decay_mode_2 	= R.getI("leg2_decayMode");
	ZimpactTau_2 		= R.getF("leg2_ZimpactTau");
	dzTauVertex_2 		= R.getF("leg2_dzTauVertex");
	mt_2  				= R.getD("corr_MTmvaMET_leg2");
	pfmt_2 				= GetTransverseMass(pfMetVec,l2);
	puppimt_2 			= GetTransverseMass(puppiMetVec,l2);
	mt_uncorr_2   		= GetTransverseMass(mvaMetVec_uncorr,l2);

	if(eventHasNominalLeptonEnergyScales)
	{
		responseUP_MTmvaMET_2		=  GetTransverseMass(mvaMetVec_responseUP,l2);
		responseDOWN_MTmvaMET_2		=  GetTransverseMass(mvaMetVec_responseDOWN,l2);
		resolutionUP_MTmvaMET_2		=  GetTransverseMass(mvaMetVec_resolutionUP,l2);
		resolutionDOWN_MTmvaMET_2	=  GetTransverseMass(mvaMetVec_resolutionDOWN,l2);
	}


	gen_match_2 		= R.getI("leg2_MCMatchType");
	genMCmatch_pt_2		= R.getD("leg2_genMCmatch_pt");
	genMCmatch_eta_2	= R.getD("leg2_genMCmatch_eta");
	genMCmatch_phi_2	= R.getD("leg2_genMCmatch_phi");
	genMCmatch_M_2		= R.getD("leg2_genMCmatch_M");
	MCMatchPdgId_2		= R.getI("leg2_MCMatchPdgId");


	byIsolationMVArun2v1DBoldDMwLTraw_2 = R.getF("leg2_byIsolationMVArun2v1DBoldDMwLTraw");
	byTightIsolationMVArun2v1DBoldDMwLT_2 = R.getF("leg2_byTightIsolationMVArun2v1DBoldDMwLT");
	byVTightIsolationMVArun2v1DBoldDMwLT_2 = R.getF("leg2_byVTightIsolationMVArun2v1DBoldDMwLT");
	byLooseIsolationMVArun2v1DBoldDMwLT_2 = R.getF("leg2_byLooseIsolationMVArun2v1DBoldDMwLT");
	byMediumIsolationMVArun2v1DBoldDMwLT_2 = R.getF("leg2_byMediumIsolationMVArun2v1DBoldDMwLT");
	byVLooseIsolationMVArun2v1DBoldDMwLT_2 = R.getF("leg2_byVLooseIsolationMVArun2v1DBoldDMwLT");
	byVVTightIsolationMVArun2v1DBoldDMwLT_2 = R.getF("leg2_byVVTightIsolationMVArun2v1DBoldDMwLT");
	againstElectronVLooseMVA6_2 = R.getF("leg2_againstElectronVLooseMVA6");
	againstMuonTight3_2 = R.getF("leg2_againstMuonTight3");
	againstElectronTightMVA6_2 = R.getF("leg2_againstElectronTightMVA6");
	againstMuonLoose3_2 = R.getF("leg2_againstMuonLoose3");
	decayModeFinding_2 = R.getF("leg2_decayModeFinding");
	byIsolationMVA3oldDMwLTraw_2 = R.getF("leg2_byIsolationMVA3oldDMwLTraw");
	byCombinedIsolationDeltaBetaCorrRaw3Hits_2 = R.getF("leg2_byCombinedIsolationDeltaBetaCorrRaw3Hits");
	byIsolationMVArun2v1DBnewDMwLTraw_2 = R.getF("leg2_byIsolationMVArun2v1DBnewDMwLTraw");
	decayModeFindingNewDMs_2 = R.getF("leg2_decayModeFindingNewDMs");


	/* di-tau system */

	pt_tt = (l1+l2+mvaMetVec).Pt();
	mt_tot = mtTotCalc(l1, l2, mvaMetVec);
	m_vis = R.getD("VISMass");
	DeltaR_leg1_leg2 = R.getD("DeltaR_leg1_leg2");


	/* sv fit -- only keeping variants which use mvaMET, study by H2Tau group showed met variants have minimal impact on SVMass shape
	and so those are omitted */

	m_sv 						= R.getD("SVMass");
	mt_sv 						= R.getD("SVTransverseMass");
	SVFit_mvaMET_diTau_pt		= R.getD("SVFit_mvaMET_diTau_pt");
	SVFit_mvaMET_diTau_eta		= R.getD("SVFit_mvaMET_diTau_eta");
	SVFit_mvaMET_diTau_phi		= R.getD("SVFit_mvaMET_diTau_phi");
	SVFit_mvaMET_FittedMET		= R.getD("SVFit_mvaMET_FittedMET");
	SVFit_mvaMET_FittedMETphi	= R.getD("SVFit_mvaMET_FittedMETphi");


	/* met-related branches */

	mvamet				= R.getD("corr_mvaMET");
	mvametphi			= R.getD("corr_mvaMETphi");
	met					= R.getD("pfMET");
	metphi				= R.getD("pfMETphi");
	puppimet			= R.getD("puppiMET");	
	puppimetphi			= R.getD("puppiMETphi");
	uncorr_mvamet		= R.getD("uncorr_mvaMET");
	uncorr_mvametphi	= R.getD("uncorr_mvaMETphi");


   	if(eventHasNominalLeptonEnergyScales)
   	{
   		responseUP_mvaMET			= R.getD("responseUP_mvaMET");
   		responseUP_mvaMETphi		= R.getD("responseUP_mvaMETphi");
   		responseDOWN_mvaMET			= R.getD("responseDOWN_mvaMET");
   		responseDOWN_mvaMETphi		= R.getD("responseDOWN_mvaMETphi");
   		resolutionUP_mvaMET			= R.getD("resolutionUP_mvaMET");
   		resolutionUP_mvaMETphi		= R.getD("resolutionUP_mvaMETphi");
   		resolutionDOWN_mvaMET		= R.getD("resolutionDOWN_mvaMET");
   		resolutionDOWN_mvaMETphi	= R.getD("resolutionDOWN_mvaMETphi");
   	}

	/* sig matrix using mva met */

	mvacov00			= R.getD("mvaMET_cov00");     
	mvacov01			= R.getD("mvaMET_cov01");
	mvacov10			= R.getD("mvaMET_cov10");
	mvacov11			= R.getD("mvaMET_cov11");

	/* sig matrix using pf met */

	if(eventIsNotSmallTree)
	{
		metcov00			= R.getD("pfMET_cov00");     
		metcov01			= R.getD("pfMET_cov01");
		metcov10			= R.getD("pfMET_cov10");
		metcov11			= R.getD("pfMET_cov11");
	}



	/* p_zeta variables */


	pzetavis 			= pzetaVisCalc(l1,l2);

	pzetamiss			= pzetaMissCalc(l1,l2,mvaMetVec);
	pfpzetamiss 		= pzetaMissCalc(l1,l2,pfMetVec);
	puppipzetamiss		= pzetaMissCalc(l1,l2,puppiMetVec);
	pzetamiss_uncorr	= pzetaMissCalc(l1,l2,mvaMetVec_uncorr);

   	if(eventHasNominalLeptonEnergyScales)
   	{   
		pzetamiss_responseUP 		= pzetaMissCalc(l1,l2,mvaMetVec_responseUP);
		pzetamiss_responseDOWN 		= pzetaMissCalc(l1,l2,mvaMetVec_responseDOWN);
		pzetamiss_resolutionUP		= pzetaMissCalc(l1,l2,mvaMetVec_resolutionUP);
		pzetamiss_resolutionDOWN	= pzetaMissCalc(l1,l2,mvaMetVec_resolutionDOWN);
   	}


  

   	/* fill the jet and b-tag info */

   	/* for nominal jets */
   	std::string argString = "";

   	jetINFOstruct.reset();
	fillJetBranches(eventHasNominalLeptonEnergyScales, eventIsNotSmallTree, argString, jetINFOstruct);


	njets = jetINFOstruct.m_njets;
	njetspt20 = jetINFOstruct.m_njetspt20;
	mjj = jetINFOstruct.m_mjj;
	jdeta = jetINFOstruct.m_jdeta;
	njetingap = jetINFOstruct.m_njetingap;
	njetingap20 = jetINFOstruct.m_njetingap20;
	jdphi = jetINFOstruct.m_jdphi;
	jpt_1 = jetINFOstruct.m_jpt_1;
	jeta_1 = jetINFOstruct.m_jeta_1;
	jphi_1 = jetINFOstruct.m_jphi_1;
	jm_1 = jetINFOstruct.m_jm_1;
	jmva_1 = jetINFOstruct.m_jmva_1;
	jpt_2 = jetINFOstruct.m_jpt_2;
	jeta_2 = jetINFOstruct.m_jeta_2;
	jphi_2 = jetINFOstruct.m_jphi_2;
	jm_2 = jetINFOstruct.m_jm_2;
	jmva_2 = jetINFOstruct.m_jmva_2;
	nbtag = jetINFOstruct.m_nbtag;
	nbtag_oneSigmaUp = jetINFOstruct.m_nbtag_oneSigmaUp;
	nbtag_oneSigmaDown = jetINFOstruct.m_nbtag_oneSigmaDown;
	bpt_1 = jetINFOstruct.m_bpt_1;
	beta_1 = jetINFOstruct.m_beta_1;
	bphi_1 = jetINFOstruct.m_bphi_1;
	bm_1 = jetINFOstruct.m_bm_1;
	bmva_1 = jetINFOstruct.m_bmva_1;
	bcsv_1 = jetINFOstruct.m_bcsv_1;
	bpt_2 = jetINFOstruct.m_bpt_2;
	beta_2 = jetINFOstruct.m_beta_2;
	bphi_2 = jetINFOstruct.m_bphi_2;
	bm_2 = jetINFOstruct.m_bm_2;
	bmva_2 = jetINFOstruct.m_bmva_2;
	bcsv_2 = jetINFOstruct.m_bcsv_2;
	nbtag_LooseWp = jetINFOstruct.m_nbtag_LooseWp;
	nbtag_LooseWp_oneSigmaUp = jetINFOstruct.m_nbtag_LooseWp_oneSigmaUp;
	nbtag_LooseWp_oneSigmaDown = jetINFOstruct.m_nbtag_LooseWp_oneSigmaDown;
	bpt_1_LooseWp = jetINFOstruct.m_bpt_1_LooseWp;
	beta_1_LooseWp = jetINFOstruct.m_beta_1_LooseWp;
	bphi_1_LooseWp = jetINFOstruct.m_bphi_1_LooseWp;
	bm_1_LooseWp = jetINFOstruct.m_bm_1_LooseWp;
	bmva_1_LooseWp = jetINFOstruct.m_bmva_1_LooseWp;
	bcsv_1_LooseWp = jetINFOstruct.m_bcsv_1_LooseWp;
	bpt_2_LooseWp = jetINFOstruct.m_bpt_2_LooseWp;
	beta_2_LooseWp = jetINFOstruct.m_beta_2_LooseWp;
	bphi_2_LooseWp = jetINFOstruct.m_bphi_2_LooseWp;
	bm_2_LooseWp = jetINFOstruct.m_bm_2_LooseWp;
	bmva_2_LooseWp = jetINFOstruct.m_bmva_2_LooseWp;
	bcsv_2_LooseWp = jetINFOstruct.m_bcsv_2_LooseWp;
	nbtag_TightWp = jetINFOstruct.m_nbtag_TightWp;
	nbtag_TightWp_oneSigmaUp = jetINFOstruct.m_nbtag_TightWp_oneSigmaUp;
	nbtag_TightWp_oneSigmaDown = jetINFOstruct.m_nbtag_TightWp_oneSigmaDown;
	bpt_1_TightWp = jetINFOstruct.m_bpt_1_TightWp;
	beta_1_TightWp = jetINFOstruct.m_beta_1_TightWp;
	bphi_1_TightWp = jetINFOstruct.m_bphi_1_TightWp;
	bm_1_TightWp = jetINFOstruct.m_bm_1_TightWp;
	bmva_1_TightWp = jetINFOstruct.m_bmva_1_TightWp;
	bcsv_1_TightWp = jetINFOstruct.m_bcsv_1_TightWp;
	bpt_2_TightWp = jetINFOstruct.m_bpt_2_TightWp;
	beta_2_TightWp = jetINFOstruct.m_beta_2_TightWp;
	bphi_2_TightWp = jetINFOstruct.m_bphi_2_TightWp;
	bm_2_TightWp = jetINFOstruct.m_bm_2_TightWp;
	bmva_2_TightWp = jetINFOstruct.m_bmva_2_TightWp;
	bcsv_2_TightWp = jetINFOstruct.m_bcsv_2_TightWp;


   	/* for _JECshiftedUp jets */
   	argString = "_JECshiftedUp";

   	jetINFOstruct.reset();
	fillJetBranches(eventHasNominalLeptonEnergyScales, eventIsNotSmallTree, argString, jetINFOstruct);

	njets_JECshiftedUp = jetINFOstruct.m_njets;
	njetspt20_JECshiftedUp = jetINFOstruct.m_njetspt20;
	mjj_JECshiftedUp = jetINFOstruct.m_mjj;
	jdeta_JECshiftedUp = jetINFOstruct.m_jdeta;
	njetingap_JECshiftedUp = jetINFOstruct.m_njetingap;
	njetingap20_JECshiftedUp = jetINFOstruct.m_njetingap20;
	jdphi_JECshiftedUp = jetINFOstruct.m_jdphi;
	jpt_1_JECshiftedUp = jetINFOstruct.m_jpt_1;
	jeta_1_JECshiftedUp = jetINFOstruct.m_jeta_1;
	jphi_1_JECshiftedUp = jetINFOstruct.m_jphi_1;
	jm_1_JECshiftedUp = jetINFOstruct.m_jm_1;
	jmva_1_JECshiftedUp = jetINFOstruct.m_jmva_1;
	jpt_2_JECshiftedUp = jetINFOstruct.m_jpt_2;
	jeta_2_JECshiftedUp = jetINFOstruct.m_jeta_2;
	jphi_2_JECshiftedUp = jetINFOstruct.m_jphi_2;
	jm_2_JECshiftedUp = jetINFOstruct.m_jm_2;
	jmva_2_JECshiftedUp = jetINFOstruct.m_jmva_2;
	nbtag_JECshiftedUp = jetINFOstruct.m_nbtag;
	bpt_1_JECshiftedUp = jetINFOstruct.m_bpt_1;
	beta_1_JECshiftedUp = jetINFOstruct.m_beta_1;
	bphi_1_JECshiftedUp = jetINFOstruct.m_bphi_1;
	bm_1_JECshiftedUp = jetINFOstruct.m_bm_1;
	bmva_1_JECshiftedUp = jetINFOstruct.m_bmva_1;
	bcsv_1_JECshiftedUp = jetINFOstruct.m_bcsv_1;
	bpt_2_JECshiftedUp = jetINFOstruct.m_bpt_2;
	beta_2_JECshiftedUp = jetINFOstruct.m_beta_2;
	bphi_2_JECshiftedUp = jetINFOstruct.m_bphi_2;
	bm_2_JECshiftedUp = jetINFOstruct.m_bm_2;
	bmva_2_JECshiftedUp = jetINFOstruct.m_bmva_2;
	bcsv_2_JECshiftedUp = jetINFOstruct.m_bcsv_2;
	nbtag_LooseWp_JECshiftedUp = jetINFOstruct.m_nbtag_LooseWp;
	bpt_1_LooseWp_JECshiftedUp = jetINFOstruct.m_bpt_1_LooseWp;
	beta_1_LooseWp_JECshiftedUp = jetINFOstruct.m_beta_1_LooseWp;
	bphi_1_LooseWp_JECshiftedUp = jetINFOstruct.m_bphi_1_LooseWp;
	bm_1_LooseWp_JECshiftedUp = jetINFOstruct.m_bm_1_LooseWp;
	bmva_1_LooseWp_JECshiftedUp = jetINFOstruct.m_bmva_1_LooseWp;
	bcsv_1_LooseWp_JECshiftedUp = jetINFOstruct.m_bcsv_1_LooseWp;
	bpt_2_LooseWp_JECshiftedUp = jetINFOstruct.m_bpt_2_LooseWp;
	beta_2_LooseWp_JECshiftedUp = jetINFOstruct.m_beta_2_LooseWp;
	bphi_2_LooseWp_JECshiftedUp = jetINFOstruct.m_bphi_2_LooseWp;
	bm_2_LooseWp_JECshiftedUp = jetINFOstruct.m_bm_2_LooseWp;
	bmva_2_LooseWp_JECshiftedUp = jetINFOstruct.m_bmva_2_LooseWp;
	bcsv_2_LooseWp_JECshiftedUp = jetINFOstruct.m_bcsv_2_LooseWp;
	nbtag_TightWp_JECshiftedUp = jetINFOstruct.m_nbtag_TightWp;
	bpt_1_TightWp_JECshiftedUp = jetINFOstruct.m_bpt_1_TightWp;
	beta_1_TightWp_JECshiftedUp = jetINFOstruct.m_beta_1_TightWp;
	bphi_1_TightWp_JECshiftedUp = jetINFOstruct.m_bphi_1_TightWp;
	bm_1_TightWp_JECshiftedUp = jetINFOstruct.m_bm_1_TightWp;
	bmva_1_TightWp_JECshiftedUp = jetINFOstruct.m_bmva_1_TightWp;
	bcsv_1_TightWp_JECshiftedUp = jetINFOstruct.m_bcsv_1_TightWp;
	bpt_2_TightWp_JECshiftedUp = jetINFOstruct.m_bpt_2_TightWp;
	beta_2_TightWp_JECshiftedUp = jetINFOstruct.m_beta_2_TightWp;
	bphi_2_TightWp_JECshiftedUp = jetINFOstruct.m_bphi_2_TightWp;
	bm_2_TightWp_JECshiftedUp = jetINFOstruct.m_bm_2_TightWp;
	bmva_2_TightWp_JECshiftedUp = jetINFOstruct.m_bmva_2_TightWp;
	bcsv_2_TightWp_JECshiftedUp = jetINFOstruct.m_bcsv_2_TightWp;




   	/* for _JECshiftedDown jets */
   	argString = "_JECshiftedDown";

   	jetINFOstruct.reset();
	fillJetBranches(eventHasNominalLeptonEnergyScales, eventIsNotSmallTree, argString, jetINFOstruct);

	njets_JECshiftedDown = jetINFOstruct.m_njets;
	njetspt20_JECshiftedDown = jetINFOstruct.m_njetspt20;
	mjj_JECshiftedDown = jetINFOstruct.m_mjj;
	jdeta_JECshiftedDown = jetINFOstruct.m_jdeta;
	njetingap_JECshiftedDown = jetINFOstruct.m_njetingap;
	njetingap20_JECshiftedDown = jetINFOstruct.m_njetingap20;
	jdphi_JECshiftedDown = jetINFOstruct.m_jdphi;
	jpt_1_JECshiftedDown = jetINFOstruct.m_jpt_1;
	jeta_1_JECshiftedDown = jetINFOstruct.m_jeta_1;
	jphi_1_JECshiftedDown = jetINFOstruct.m_jphi_1;
	jm_1_JECshiftedDown = jetINFOstruct.m_jm_1;
	jmva_1_JECshiftedDown = jetINFOstruct.m_jmva_1;
	jpt_2_JECshiftedDown = jetINFOstruct.m_jpt_2;
	jeta_2_JECshiftedDown = jetINFOstruct.m_jeta_2;
	jphi_2_JECshiftedDown = jetINFOstruct.m_jphi_2;
	jm_2_JECshiftedDown = jetINFOstruct.m_jm_2;
	jmva_2_JECshiftedDown = jetINFOstruct.m_jmva_2;
	nbtag_JECshiftedDown = jetINFOstruct.m_nbtag;
	bpt_1_JECshiftedDown = jetINFOstruct.m_bpt_1;
	beta_1_JECshiftedDown = jetINFOstruct.m_beta_1;
	bphi_1_JECshiftedDown = jetINFOstruct.m_bphi_1;
	bm_1_JECshiftedDown = jetINFOstruct.m_bm_1;
	bmva_1_JECshiftedDown = jetINFOstruct.m_bmva_1;
	bcsv_1_JECshiftedDown = jetINFOstruct.m_bcsv_1;
	bpt_2_JECshiftedDown = jetINFOstruct.m_bpt_2;
	beta_2_JECshiftedDown = jetINFOstruct.m_beta_2;
	bphi_2_JECshiftedDown = jetINFOstruct.m_bphi_2;
	bm_2_JECshiftedDown = jetINFOstruct.m_bm_2;
	bmva_2_JECshiftedDown = jetINFOstruct.m_bmva_2;
	bcsv_2_JECshiftedDown = jetINFOstruct.m_bcsv_2;
	nbtag_LooseWp_JECshiftedDown = jetINFOstruct.m_nbtag_LooseWp;
	bpt_1_LooseWp_JECshiftedDown = jetINFOstruct.m_bpt_1_LooseWp;
	beta_1_LooseWp_JECshiftedDown = jetINFOstruct.m_beta_1_LooseWp;
	bphi_1_LooseWp_JECshiftedDown = jetINFOstruct.m_bphi_1_LooseWp;
	bm_1_LooseWp_JECshiftedDown = jetINFOstruct.m_bm_1_LooseWp;
	bmva_1_LooseWp_JECshiftedDown = jetINFOstruct.m_bmva_1_LooseWp;
	bcsv_1_LooseWp_JECshiftedDown = jetINFOstruct.m_bcsv_1_LooseWp;
	bpt_2_LooseWp_JECshiftedDown = jetINFOstruct.m_bpt_2_LooseWp;
	beta_2_LooseWp_JECshiftedDown = jetINFOstruct.m_beta_2_LooseWp;
	bphi_2_LooseWp_JECshiftedDown = jetINFOstruct.m_bphi_2_LooseWp;
	bm_2_LooseWp_JECshiftedDown = jetINFOstruct.m_bm_2_LooseWp;
	bmva_2_LooseWp_JECshiftedDown = jetINFOstruct.m_bmva_2_LooseWp;
	bcsv_2_LooseWp_JECshiftedDown = jetINFOstruct.m_bcsv_2_LooseWp;
	nbtag_TightWp_JECshiftedDown = jetINFOstruct.m_nbtag_TightWp;
	bpt_1_TightWp_JECshiftedDown = jetINFOstruct.m_bpt_1_TightWp;
	beta_1_TightWp_JECshiftedDown = jetINFOstruct.m_beta_1_TightWp;
	bphi_1_TightWp_JECshiftedDown = jetINFOstruct.m_bphi_1_TightWp;
	bm_1_TightWp_JECshiftedDown = jetINFOstruct.m_bm_1_TightWp;
	bmva_1_TightWp_JECshiftedDown = jetINFOstruct.m_bmva_1_TightWp;
	bcsv_1_TightWp_JECshiftedDown = jetINFOstruct.m_bcsv_1_TightWp;
	bpt_2_TightWp_JECshiftedDown = jetINFOstruct.m_bpt_2_TightWp;
	beta_2_TightWp_JECshiftedDown = jetINFOstruct.m_beta_2_TightWp;
	bphi_2_TightWp_JECshiftedDown = jetINFOstruct.m_bphi_2_TightWp;
	bm_2_TightWp_JECshiftedDown = jetINFOstruct.m_bm_2_TightWp;
	bmva_2_TightWp_JECshiftedDown = jetINFOstruct.m_bmva_2_TightWp;
	bcsv_2_TightWp_JECshiftedDown = jetINFOstruct.m_bcsv_2_TightWp;
	





   	/* for _JERup jets */
   	argString = "_JERup";

   	jetINFOstruct.reset();
	fillJetBranches(eventHasNominalLeptonEnergyScales, eventIsNotSmallTree, argString, jetINFOstruct);

	njets_JERup = jetINFOstruct.m_njets;
	njetspt20_JERup = jetINFOstruct.m_njetspt20;
	mjj_JERup = jetINFOstruct.m_mjj;
	jdeta_JERup = jetINFOstruct.m_jdeta;
	njetingap_JERup = jetINFOstruct.m_njetingap;
	njetingap20_JERup = jetINFOstruct.m_njetingap20;
	jdphi_JERup = jetINFOstruct.m_jdphi;
	jpt_1_JERup = jetINFOstruct.m_jpt_1;
	jeta_1_JERup = jetINFOstruct.m_jeta_1;
	jphi_1_JERup = jetINFOstruct.m_jphi_1;
	jm_1_JERup = jetINFOstruct.m_jm_1;
	jmva_1_JERup = jetINFOstruct.m_jmva_1;
	jpt_2_JERup = jetINFOstruct.m_jpt_2;
	jeta_2_JERup = jetINFOstruct.m_jeta_2;
	jphi_2_JERup = jetINFOstruct.m_jphi_2;
	jm_2_JERup = jetINFOstruct.m_jm_2;
	jmva_2_JERup = jetINFOstruct.m_jmva_2;
	nbtag_JERup = jetINFOstruct.m_nbtag;
	bpt_1_JERup = jetINFOstruct.m_bpt_1;
	beta_1_JERup = jetINFOstruct.m_beta_1;
	bphi_1_JERup = jetINFOstruct.m_bphi_1;
	bm_1_JERup = jetINFOstruct.m_bm_1;
	bmva_1_JERup = jetINFOstruct.m_bmva_1;
	bcsv_1_JERup = jetINFOstruct.m_bcsv_1;
	bpt_2_JERup = jetINFOstruct.m_bpt_2;
	beta_2_JERup = jetINFOstruct.m_beta_2;
	bphi_2_JERup = jetINFOstruct.m_bphi_2;
	bm_2_JERup = jetINFOstruct.m_bm_2;
	bmva_2_JERup = jetINFOstruct.m_bmva_2;
	bcsv_2_JERup = jetINFOstruct.m_bcsv_2;
	nbtag_LooseWp_JERup = jetINFOstruct.m_nbtag_LooseWp;
	bpt_1_LooseWp_JERup = jetINFOstruct.m_bpt_1_LooseWp;
	beta_1_LooseWp_JERup = jetINFOstruct.m_beta_1_LooseWp;
	bphi_1_LooseWp_JERup = jetINFOstruct.m_bphi_1_LooseWp;
	bm_1_LooseWp_JERup = jetINFOstruct.m_bm_1_LooseWp;
	bmva_1_LooseWp_JERup = jetINFOstruct.m_bmva_1_LooseWp;
	bcsv_1_LooseWp_JERup = jetINFOstruct.m_bcsv_1_LooseWp;
	bpt_2_LooseWp_JERup = jetINFOstruct.m_bpt_2_LooseWp;
	beta_2_LooseWp_JERup = jetINFOstruct.m_beta_2_LooseWp;
	bphi_2_LooseWp_JERup = jetINFOstruct.m_bphi_2_LooseWp;
	bm_2_LooseWp_JERup = jetINFOstruct.m_bm_2_LooseWp;
	bmva_2_LooseWp_JERup = jetINFOstruct.m_bmva_2_LooseWp;
	bcsv_2_LooseWp_JERup = jetINFOstruct.m_bcsv_2_LooseWp;
	nbtag_TightWp_JERup = jetINFOstruct.m_nbtag_TightWp;
	bpt_1_TightWp_JERup = jetINFOstruct.m_bpt_1_TightWp;
	beta_1_TightWp_JERup = jetINFOstruct.m_beta_1_TightWp;
	bphi_1_TightWp_JERup = jetINFOstruct.m_bphi_1_TightWp;
	bm_1_TightWp_JERup = jetINFOstruct.m_bm_1_TightWp;
	bmva_1_TightWp_JERup = jetINFOstruct.m_bmva_1_TightWp;
	bcsv_1_TightWp_JERup = jetINFOstruct.m_bcsv_1_TightWp;
	bpt_2_TightWp_JERup = jetINFOstruct.m_bpt_2_TightWp;
	beta_2_TightWp_JERup = jetINFOstruct.m_beta_2_TightWp;
	bphi_2_TightWp_JERup = jetINFOstruct.m_bphi_2_TightWp;
	bm_2_TightWp_JERup = jetINFOstruct.m_bm_2_TightWp;
	bmva_2_TightWp_JERup = jetINFOstruct.m_bmva_2_TightWp;
	bcsv_2_TightWp_JERup = jetINFOstruct.m_bcsv_2_TightWp;
	



   	/* for _JERdown jets */
   	argString = "_JERdown";

   	jetINFOstruct.reset();
	fillJetBranches(eventHasNominalLeptonEnergyScales, eventIsNotSmallTree, argString, jetINFOstruct);

	njets_JERdown = jetINFOstruct.m_njets;
	njetspt20_JERdown = jetINFOstruct.m_njetspt20;
	mjj_JERdown = jetINFOstruct.m_mjj;
	jdeta_JERdown = jetINFOstruct.m_jdeta;
	njetingap_JERdown = jetINFOstruct.m_njetingap;
	njetingap20_JERdown = jetINFOstruct.m_njetingap20;
	jdphi_JERdown = jetINFOstruct.m_jdphi;
	jpt_1_JERdown = jetINFOstruct.m_jpt_1;
	jeta_1_JERdown = jetINFOstruct.m_jeta_1;
	jphi_1_JERdown = jetINFOstruct.m_jphi_1;
	jm_1_JERdown = jetINFOstruct.m_jm_1;
	jmva_1_JERdown = jetINFOstruct.m_jmva_1;
	jpt_2_JERdown = jetINFOstruct.m_jpt_2;
	jeta_2_JERdown = jetINFOstruct.m_jeta_2;
	jphi_2_JERdown = jetINFOstruct.m_jphi_2;
	jm_2_JERdown = jetINFOstruct.m_jm_2;
	jmva_2_JERdown = jetINFOstruct.m_jmva_2;
	nbtag_JERdown = jetINFOstruct.m_nbtag;
	bpt_1_JERdown = jetINFOstruct.m_bpt_1;
	beta_1_JERdown = jetINFOstruct.m_beta_1;
	bphi_1_JERdown = jetINFOstruct.m_bphi_1;
	bm_1_JERdown = jetINFOstruct.m_bm_1;
	bmva_1_JERdown = jetINFOstruct.m_bmva_1;
	bcsv_1_JERdown = jetINFOstruct.m_bcsv_1;
	bpt_2_JERdown = jetINFOstruct.m_bpt_2;
	beta_2_JERdown = jetINFOstruct.m_beta_2;
	bphi_2_JERdown = jetINFOstruct.m_bphi_2;
	bm_2_JERdown = jetINFOstruct.m_bm_2;
	bmva_2_JERdown = jetINFOstruct.m_bmva_2;
	bcsv_2_JERdown = jetINFOstruct.m_bcsv_2;
	nbtag_LooseWp_JERdown = jetINFOstruct.m_nbtag_LooseWp;
	bpt_1_LooseWp_JERdown = jetINFOstruct.m_bpt_1_LooseWp;
	beta_1_LooseWp_JERdown = jetINFOstruct.m_beta_1_LooseWp;
	bphi_1_LooseWp_JERdown = jetINFOstruct.m_bphi_1_LooseWp;
	bm_1_LooseWp_JERdown = jetINFOstruct.m_bm_1_LooseWp;
	bmva_1_LooseWp_JERdown = jetINFOstruct.m_bmva_1_LooseWp;
	bcsv_1_LooseWp_JERdown = jetINFOstruct.m_bcsv_1_LooseWp;
	bpt_2_LooseWp_JERdown = jetINFOstruct.m_bpt_2_LooseWp;
	beta_2_LooseWp_JERdown = jetINFOstruct.m_beta_2_LooseWp;
	bphi_2_LooseWp_JERdown = jetINFOstruct.m_bphi_2_LooseWp;
	bm_2_LooseWp_JERdown = jetINFOstruct.m_bm_2_LooseWp;
	bmva_2_LooseWp_JERdown = jetINFOstruct.m_bmva_2_LooseWp;
	bcsv_2_LooseWp_JERdown = jetINFOstruct.m_bcsv_2_LooseWp;
	nbtag_TightWp_JERdown = jetINFOstruct.m_nbtag_TightWp;
	bpt_1_TightWp_JERdown = jetINFOstruct.m_bpt_1_TightWp;
	beta_1_TightWp_JERdown = jetINFOstruct.m_beta_1_TightWp;
	bphi_1_TightWp_JERdown = jetINFOstruct.m_bphi_1_TightWp;
	bm_1_TightWp_JERdown = jetINFOstruct.m_bm_1_TightWp;
	bmva_1_TightWp_JERdown = jetINFOstruct.m_bmva_1_TightWp;
	bcsv_1_TightWp_JERdown = jetINFOstruct.m_bcsv_1_TightWp;
	bpt_2_TightWp_JERdown = jetINFOstruct.m_bpt_2_TightWp;
	beta_2_TightWp_JERdown = jetINFOstruct.m_beta_2_TightWp;
	bphi_2_TightWp_JERdown = jetINFOstruct.m_bphi_2_TightWp;
	bm_2_TightWp_JERdown = jetINFOstruct.m_bm_2_TightWp;
	bmva_2_TightWp_JERdown = jetINFOstruct.m_bmva_2_TightWp;
	bcsv_2_TightWp_JERdown = jetINFOstruct.m_bcsv_2_TightWp;
	


	// extra lepton + dilepton vetoes

	dilepton_veto = 0.0;
	extraelec_veto = 0.0;
	extramuon_veto = 0.0;

	if(R.getF("DiMuon_Flag") > 0.5 || R.getF("DiElectron_Flag") > 0.5) dilepton_veto = 1.0;
	if(R.getF("ThirdElectron_Flag") > 0.5) extraelec_veto = 1.0;
	if(R.getF("ThirdMuon_Flag") > 0.5) extramuon_veto = 1.0;

	/* veto leptons needed as is from FlatTuple for VH channels of SM Higgs analysis */

	veto_leptonType = R.getVI("veto_leptonType");
	veto_pt = R.getVD("veto_pt");
	veto_eta = R.getVD("veto_eta");
	veto_phi = R.getVD("veto_phi");
	veto_M = R.getVD("veto_M");
	veto_charge = R.getVI("veto_charge");
	veto_dxy = R.getVF("veto_dxy");
	veto_dz = R.getVF("veto_dz");
	veto_RelIso = R.getVF("veto_RelIso");
	veto_passesMediumMuonId = R.getVF("veto_passesMediumMuonId");
	veto_passElectronMVA80 = R.getVF("veto_passElectronMVA80");
	veto_passElectronMVA90 = R.getVF("veto_passElectronMVA90");
	veto_passElectronCutBased = R.getVF("veto_passElectronCutBased");
	veto_isTrackerGlobalPFMuon = R.getVF("veto_isTrackerGlobalPFMuon");
	veto_numberOfMissingInnerHits = R.getVF("veto_numberOfMissingInnerHits");
	veto_numberOfMissingOuterHits = R.getVF("veto_numberOfMissingOuterHits");
	veto_passConversionVeto = R.getVF("veto_passConversionVeto");
	veto_LeptonPassesThirdElectronVetoCuts = R.getVI("veto_LeptonPassesThirdElectronVetoCuts");
	veto_LeptonPassesThirdMuonVetoCuts = R.getVI("veto_LeptonPassesThirdMuonVetoCuts");
	veto_LeptonPassesDiElectronVetoCuts = R.getVI("veto_LeptonPassesDiElectronVetoCuts");
	veto_LeptonPassesDiMuonVetoCuts = R.getVI("veto_LeptonPassesDiMuonVetoCuts");


	/* MET FILTERS */
	HBHENoiseFilter 					= R.getB("HBHENoiseFilter");
	HBHENoiseIsoFilter 				  	= R.getB("HBHENoiseIsoFilter");
	CSCTightHalo2015Filter 			   	= R.getB("CSCTightHalo2015Filter");
	EcalDeadCellTriggerPrimitiveFilter 	= R.getB("EcalDeadCellTriggerPrimitiveFilter");
	goodVerticesFilter 					= R.getB("goodVerticesFilter");
	eeBadScFilter 						= R.getB("eeBadScFilter");
	chargedHadronTrackResolutionFilter 	= R.getB("chargedHadronTrackResolutionFilter");
	muonBadTrackFilter 					= R.getB("muonBadTrackFilter");



	/* lhe and gen info */

	NUP = R.getI("hepNUP");
	weight = 1.0; //weight  to be computed
	generatorEventWeight = R.getD("generatorEventWeight");
	lheHT = R.getD("lheHT");
	lheOutGoingPartons = R.getI("lheOutGoingPartons");
	lheZmass = R.getD("lheZmass");
	

	/* dy classification */
	IsZTT = R.getI("IsZTT");
	IsZL = R.getI("IsZL");
	IsZJ = R.getI("IsZJ");
	IsZLL = R.getI("IsZLL");
	
	/* summary info */
	DataSet = R.getS("DataSet");
	EventTotal = R.getI("EventTotal");
	EventType = R.getS("EventType");
	KeyName = R.getS("KeyName");
	DataCard = R.getS("DataCard");
	CrossSection = R.getD("CrossSection");
	FilterEff = R.getD("FilterEff");
	isSmallTree = R.getB("isSmallTree");
	TauEsNumberSigmasShifted = R.getF("TauEsNumberSigmasShifted");
	ElectronEsNumberSigmasShifted = R.getF("ElectronEsNumberSigmasShifted");


	//////////////////////////////////////////////////////////////////////////////

	// tMVA variable calculations


	LPT = computeLPT(0);



	// Pchi and Mmin Calculations

	std::vector <double> dummyPchiMmin;


	dummyPchiMmin = computePchi_and_Mmin(0, R.getD("corr_mvaMET"), R.getD("corr_mvaMETphi"));
    P_chi = dummyPchiMmin[0];
    M_min = dummyPchiMmin[1];

	dummyPchiMmin = computePchi_and_Mmin(0, R.getD("uncorr_mvaMET"), R.getD("uncorr_mvaMETphi"));
	P_chi_uncorr = dummyPchiMmin[0];
	M_min_uncorr= dummyPchiMmin[1];
	

	dummyPchiMmin = computePchi_and_Mmin(0, R.getD("pfMET"), R.getD("pfMETphi"));
	P_chi_pf = dummyPchiMmin[0];
	M_min_pf = dummyPchiMmin[1];
	
	dummyPchiMmin = computePchi_and_Mmin(0, R.getD("puppiMET"), R.getD("puppiMETphi"));
	P_chi_puppi = dummyPchiMmin[0];
	M_min_puppi = dummyPchiMmin[1];
	

	if(eventHasNominalLeptonEnergyScales)
	{
		dummyPchiMmin = computePchi_and_Mmin(0, R.getD("responseUP_mvaMET"), R.getD("responseUP_mvaMETphi"));
		P_chi_responseUP = dummyPchiMmin[0];
		M_min_responseUP = dummyPchiMmin[1];
		
		dummyPchiMmin = computePchi_and_Mmin(0, R.getD("responseDOWN_mvaMET"), R.getD("responseDOWN_mvaMETphi"));
		P_chi_responseDOWN = dummyPchiMmin[0];
		M_min_responseDOWN = dummyPchiMmin[1];
		
		dummyPchiMmin = computePchi_and_Mmin(0, R.getD("resolutionUP_mvaMET"), R.getD("resolutionUP_mvaMETphi"));
		P_chi_resolutionUP = dummyPchiMmin[0];
		M_min_resolutionUP = dummyPchiMmin[1];
		
		dummyPchiMmin = computePchi_and_Mmin(0, R.getD("resolutionDOWN_mvaMET"), R.getD("resolutionDOWN_mvaMETphi"));
		P_chi_resolutionDOWN = dummyPchiMmin[0];
		M_min_resolutionDOWN = dummyPchiMmin[1];
	}


	/* handle event weights */

    final_weight = getFinalWeight(0);
    nominalCrossSection_Weight = getNominalWeight(0);
    puWeight_Weight = R.getD("puWeight");
    TopQuarkPtWeight_Weight = getTopQuarkPtWeight(0);
    ZReWeight_Weight = getZReWeight(0);
    NLOReWeight_Weight = getNLOReWeight(0,10);

    ScaleFactorsForPair_Weight = getFinalScaleFactorsForPair(0,0);
    ScaleFactorsForPair_WeightUp  = getFinalScaleFactorsForPair(0,1);
    ScaleFactorsForPair_WeightDown = getFinalScaleFactorsForPair(0,-1);


	std::vector <double> qcd_eleMu = getQCDWeightForEleMuChannel(0);

    QCDWeightForEleMuChannel_Weight = qcd_eleMu[0];
    QCDWeightForEleMuChannel_WeightUp = qcd_eleMu[1];
    QCDWeightForEleMuChannel_WeightDown = qcd_eleMu[2];
    QCDWeightForEleMuChannelNoPZetaCut_Weight = qcd_eleMu[3];
	QCDWeightForEleMuChannelNoPZetaCut_WeightUp = qcd_eleMu[4];
    QCDWeightForEleMuChannelNoPZetaCut_WeightDown = qcd_eleMu[5];

	std::vector<double> highPtTauEff = getHighPtTauUncertainty(0);
    highPtTauEff_WeightUp = highPtTauEff[0];
    highPtTauEff_WeightDown = highPtTauEff[1];


	///////// cutoff ---- XXXXX 



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

/* given met and met phi return a size 2 vector with P_chi at [0] and M_min at [1] */
std::vector <double> generateH2TauSyncTree::computePchi_and_Mmin(bool verbose_, double ME_T, double ME_T_phi)
{

	if(verbose_)
	{
		std::cout<<" calling computePchi_and_Mmin function \n";
	}

	std::vector<double> returnVector;
	returnVector.clear();

    double P_chi_ =  -999.0;
  	double M_min_ =  -999.0;


    double p_lt = 0;
    double eta_l = 0;
    double phi_l = 0;
    double p_Taut = 0;
    double eta_Tau = 0;
    double phi_Tau = 0;
    double M_l = 0;

    double p_lx = 0;
    double p_ly = 0;
    double p_lz = 0;
    double E_l = 0;

    double p_vx = 0;
    double p_vy = 0;
    double E_v = 0;
    
    //Pchi and Mmin Calculations
    
    if ((R.getI("leg1_leptonType") == 1 && R.getI("leg2_leptonType") == 3) || (R.getI("leg1_leptonType") == 2 && R.getI("leg2_leptonType") == 3))
    {

		if(verbose_)
		{
			std::cout<<" valid lepton types for Pchi and Mmin computation ";
		}

    
        p_lt = R.getD("leg1_pt");
        eta_l = R.getD("leg1_eta");
        phi_l = R.getD("leg1_phi");
        M_l = R.getD("leg1_M");

        p_Taut = R.getD("leg2_pt");//Added 03/16/2016
        eta_Tau = R.getD("leg2_eta");//Added 03/16/2016
        phi_Tau = R.getD("leg2_phi");//Added 03/16/2016
    
       //Calculate p_lx and p_ly   
        p_lx = p_lt*cos(phi_l);
        p_ly = p_lt*sin(phi_l);
       
       //Calculate p_lz
        p_lz = p_lt*TMath::SinH(eta_l);

       //Calculate E_l
        E_l = TMath::Sqrt(M_l*M_l + p_lt*p_lt*TMath::CosH(eta_l)*TMath::CosH(eta_l));
       
       //Calculate p_vx and p_vy 
        p_vx = ME_T*TMath::Cos(ME_T_phi);
        p_vy = ME_T*TMath::Sin(ME_T_phi);
       
       //Calculate E_v
        E_v = (ME_T*E_l)/(TMath::Sqrt(E_l*E_l - p_lz*p_lz));
       

       //Calculate P_chi
        P_chi_ = ME_T*(TMath::Cos(phi_l)*TMath::Cos(ME_T_phi) + TMath::Sin(phi_l)*TMath::Sin(ME_T_phi));

       //Calculate M_min
        M_min_ = TMath::Sqrt(((E_l + E_v)*(E_l + E_v)) - ((p_lx + p_vx)*(p_lx + p_vx)) - ((p_ly + p_vy)*(p_ly + p_vy)) - ((1 + (E_v/E_l))*(1 + (E_v/E_l))*p_lz*p_lz));

    

        if(verbose_)
		{
			std::cout<<" returning [ P_chi_ = "<< P_chi_<< " , M_min_ = "<< M_min_ <<" ] \n";
		}

    }

    else
    {
		if(verbose_)
		{
			std::cout<<" invalid lepton types for Pchi and Mmin computation, returning [-999.0, -999.0] \n";
		}

    }


    returnVector.clear();
    returnVector.push_back(P_chi_);
    returnVector.push_back(M_min_);

	return returnVector;
}






double generateH2TauSyncTree::computeLPT( bool verbose_)
{

    // LPT Calculation 

	double LPT_ = 0.0;    
    double visFrac1 = 0.;
    double visFrac1Prob = 0.;
    double visFrac2 = 0.;
    double visFrac2Prob = 0.;
    double currentFracProb = 0.;
    double bestFracProb = 0.;
    double bestP = 0.;


    TVector3 tauVisVec1;
    TVector3 tauVisVec2;
    TVector3 totalVisVec;
    tauVisVec1.SetPtEtaPhi(R.getD("leg1_pt"),R.getD("leg1_eta"),R.getD("leg1_phi"));
    tauVisVec2.SetPtEtaPhi(R.getD("leg2_pt"),R.getD("leg2_eta"),R.getD("leg2_phi"));
    totalVisVec = tauVisVec1 + tauVisVec2;
    //double totalVisPt = totalVisVec.Pt();
    //assign leg PDF histograms
    
    if(verbose_)
    {
    	std::cout << "Start PDF Loops " << R.getI("CandidateEventType") << std::endl;
	    std::cout << "Leg One Decay Mode: " << R.getI("leg1_decayMode") << std::endl;
    	std::cout << "Leg One Num Hads: " << R.getF("leg1_numHadrons") << std::endl;
    	std::cout << "Leg One Num Strips: " << R.getF("leg1_numStrips") << std::endl;
    	std::cout << "Leg Two Decay Mode: " << R.getI("leg2_decayMode") << std::endl;
    	std::cout << "Leg Two Num Hads: " << R.getF("leg2_numHadrons") << std::endl;
    	std::cout << "Leg Two Num Strips: " << R.getF("leg2_numStrips") << std::endl;
    }


    for (int i = 0; i < eHistoFrac->GetNbinsX(); i++)
    {
        if((R.getI("CandidateEventType")==1) || (R.getI("CandidateEventType")==2) || (R.getI("CandidateEventType")==3))
        {
            visFrac1 = eHistoFrac->GetXaxis()->GetBinCenter(i);
            visFrac1Prob = eHistoFrac->GetBinContent(i);
        }
        else if ((R.getI("CandidateEventType")==4) || (R.getI("CandidateEventType")==5))
        {
            visFrac1 = muHistoFrac->GetXaxis()->GetBinCenter(i);
            visFrac1Prob = muHistoFrac->GetBinContent(i);
        }
        else
        {
            if (R.getI("leg1_decayMode")==0)
            {
                visFrac1 = h1p0sHistoFrac->GetXaxis()->GetBinCenter(i);
                visFrac1Prob = h1p0sHistoFrac->GetBinContent(i);
            }
            else if (R.getI("leg1_decayMode")==1)
            {
                visFrac1 = h1p1sHistoFrac->GetXaxis()->GetBinCenter(i);
                visFrac1Prob = h1p1sHistoFrac->GetBinContent(i);
            }
            else if (R.getI("leg1_decayMode")==10)
            {
                visFrac1 = h3p0sHistoFrac->GetXaxis()->GetBinCenter(i);
                visFrac1Prob = h3p0sHistoFrac->GetBinContent(i);
            }
            
        }
        
        //find constrained fraction
        visFrac2 = 2 * (1/visFrac1) * ((tauVisVec1.Mag()*tauVisVec2.Mag())-(tauVisVec1.Dot(tauVisVec2)))/(pow(125.,2));
        
        //find PDF value from constrained fraction
        if(R.getI("CandidateEventType")==1)
        {
            visFrac2Prob = eHistoFrac->GetBinContent(eHistoFrac->FindBin(visFrac2));
        }
        else if ((R.getI("CandidateEventType")==2) || (R.getI("CandidateEventType")==4))
        {
            visFrac2Prob = muHistoFrac->GetBinContent(muHistoFrac->FindBin(visFrac2));
        }
        else
        {
            if (R.getI("leg2_decayMode")==0)
            {
                visFrac2Prob = h1p0sHistoFrac->GetBinContent(h1p0sHistoFrac->FindBin(visFrac2));
            }
            else if (R.getI("leg2_decayMode")==1)
            {
                visFrac2Prob = h1p1sHistoFrac->GetBinContent(h1p1sHistoFrac->FindBin(visFrac2));
            }
            else if (R.getI("leg2_decayMode")==10)
            {
                visFrac2Prob = h3p0sHistoFrac->GetBinContent(h3p0sHistoFrac->FindBin(visFrac2));
            }

        }
        if (visFrac2 > 1.03)
        {
            visFrac2Prob = 0;
        }
        TVector3 tauVec1;
        TVector3 tauVec2;
        TVector3 totalVec;
        tauVec1.SetPtEtaPhi((R.getD("leg1_pt") * (1/visFrac1)),R.getD("leg1_eta"),R.getD("leg1_phi"));
        tauVec2.SetPtEtaPhi((R.getD("leg2_pt") * (1/visFrac2)),R.getD("leg2_eta"),R.getD("leg2_phi"));
        totalVec = tauVec1 + tauVec2;
        double totalP = totalVec.Pt();
        currentFracProb = visFrac1Prob * visFrac2Prob;
        if (currentFracProb > bestFracProb)
        {
            bestFracProb = currentFracProb;
            bestP = totalP;
        }
    }
    

    LPT_ = bestP;

    if(verbose_)
    {
    	std::cout << "best P :" << bestP << std::endl;
	    std::cout << "best Prob: " << bestFracProb << std::endl;
    }


    return LPT_;
}



void generateH2TauSyncTree::setupBranches(TTree * T)
{
	/* all trees get same branch address, but will only write event
	 to one tree per event based on CandidateEventType */

	T->Branch("final_weight", &final_weight);
	T->Branch("nominalCrossSection_Weight", &nominalCrossSection_Weight);
	T->Branch("puWeight_Weight", &puWeight_Weight);
	T->Branch("TopQuarkPtWeight_Weight", &TopQuarkPtWeight_Weight);
	T->Branch("ZReWeight_Weight", &ZReWeight_Weight);
	T->Branch("NLOReWeight_Weight", &NLOReWeight_Weight);
	T->Branch("ScaleFactorsForPair_Weight", &ScaleFactorsForPair_Weight);
	T->Branch("ScaleFactorsForPair_WeightUp", &ScaleFactorsForPair_WeightUp);
	T->Branch("ScaleFactorsForPair_WeightDown", &ScaleFactorsForPair_WeightDown);
	T->Branch("QCDWeightForEleMuChannel_Weight", &QCDWeightForEleMuChannel_Weight);
	T->Branch("QCDWeightForEleMuChannel_WeightUp", &QCDWeightForEleMuChannel_WeightUp);
	T->Branch("QCDWeightForEleMuChannel_WeightDown", &QCDWeightForEleMuChannel_WeightDown);
	T->Branch("QCDWeightForEleMuChannelNoPZetaCut_Weight", &QCDWeightForEleMuChannelNoPZetaCut_Weight);
	T->Branch("QCDWeightForEleMuChannelNoPZetaCut_WeightUp", &QCDWeightForEleMuChannelNoPZetaCut_WeightUp);
	T->Branch("QCDWeightForEleMuChannelNoPZetaCut_WeightDown", &QCDWeightForEleMuChannelNoPZetaCut_WeightDown);
	T->Branch("highPtTauEff_WeightUp", &highPtTauEff_WeightUp);
	T->Branch("highPtTauEff_WeightDown", &highPtTauEff_WeightDown);

    T->Branch("flag_MVAEventType", &flag_MVAEventType);

	T->Branch("originalXWGTUP", &originalXWGTUP);
	T->Branch("theory_scale_factors", &theory_scale_factors);
	T->Branch("pairRank", &pairRank);
	T->Branch("isOsPair", &isOsPair);
	T->Branch("genBosonTotal_pt", &genBosonTotal_pt);
	T->Branch("genBosonTotal_eta", &genBosonTotal_eta);
	T->Branch("genBosonTotal_phi", &genBosonTotal_phi);
	T->Branch("genBosonTotal_M", &genBosonTotal_M);
	T->Branch("genBosonVisible_pt", &genBosonVisible_pt);
	T->Branch("genBosonVisible_eta", &genBosonVisible_eta);
	T->Branch("genBosonVisible_phi", &genBosonVisible_phi);
	T->Branch("genBosonVisible_M", &genBosonVisible_M);
	T->Branch("genTopPt1", &genTopPt1);
	T->Branch("genTopPt2", &genTopPt2);
	T->Branch("run", &run);
	T->Branch("event", &event);
	T->Branch("evt", &evt);
	T->Branch("lumi", &lumi);
	T->Branch("npv", &npv);
	T->Branch("npu", &npu);
	T->Branch("rho", &rho);
	T->Branch("puweight", &puweight);
	T->Branch("pt_1", &pt_1);
	T->Branch("phi_1", &phi_1);
	T->Branch("eta_1", &eta_1);
	T->Branch("m_1", &m_1);
	T->Branch("iso_1", &iso_1);
	T->Branch("dZ_1", &dZ_1);
	T->Branch("dzTauVertex_1",&dzTauVertex_1);
	T->Branch("d0_1", &d0_1);
	T->Branch("q_1", &q_1);
	T->Branch("id_e_mva_nt_loose_1", &id_e_mva_nt_loose_1);
	T->Branch("tau_decay_mode_1", &tau_decay_mode_1);
	T->Branch("ZimpactTau_1", &ZimpactTau_1);
	T->Branch("mt_1", &mt_1);
	T->Branch("pfmt_1", &pfmt_1);
	T->Branch("puppimt_1", &puppimt_1);
	T->Branch("mt_uncorr_1", &mt_uncorr_1);
	T->Branch("responseUP_MTmvaMET_1", &responseUP_MTmvaMET_1);
	T->Branch("responseDOWN_MTmvaMET_1", &responseDOWN_MTmvaMET_1);
	T->Branch("resolutionUP_MTmvaMET_1", &resolutionUP_MTmvaMET_1);
	T->Branch("resolutionDOWN_MTmvaMET_1", &resolutionDOWN_MTmvaMET_1);
	T->Branch("gen_match_1", &gen_match_1);
	T->Branch("genMCmatch_pt_1", &genMCmatch_pt_1);
	T->Branch("genMCmatch_eta_1", &genMCmatch_eta_1);
	T->Branch("genMCmatch_phi_1", &genMCmatch_phi_1);
	T->Branch("genMCmatch_M_1", &genMCmatch_M_1);
	T->Branch("MCMatchPdgId_1", &MCMatchPdgId_1);
	T->Branch("byIsolationMVArun2v1DBoldDMwLTraw_1", &byIsolationMVArun2v1DBoldDMwLTraw_1);
	T->Branch("byTightIsolationMVArun2v1DBoldDMwLT_1", &byTightIsolationMVArun2v1DBoldDMwLT_1);
	T->Branch("byVTightIsolationMVArun2v1DBoldDMwLT_1", &byVTightIsolationMVArun2v1DBoldDMwLT_1);
	T->Branch("byLooseIsolationMVArun2v1DBoldDMwLT_1", &byLooseIsolationMVArun2v1DBoldDMwLT_1);
	T->Branch("byMediumIsolationMVArun2v1DBoldDMwLT_1", &byMediumIsolationMVArun2v1DBoldDMwLT_1);
	T->Branch("byVLooseIsolationMVArun2v1DBoldDMwLT_1", &byVLooseIsolationMVArun2v1DBoldDMwLT_1);
	T->Branch("byVVTightIsolationMVArun2v1DBoldDMwLT_1", &byVVTightIsolationMVArun2v1DBoldDMwLT_1);
	T->Branch("againstElectronVLooseMVA6_1", &againstElectronVLooseMVA6_1);
	T->Branch("againstMuonTight3_1", &againstMuonTight3_1);
	T->Branch("againstElectronTightMVA6_1", &againstElectronTightMVA6_1);
	T->Branch("againstMuonLoose3_1", &againstMuonLoose3_1);
	T->Branch("decayModeFinding_1", &decayModeFinding_1);
	T->Branch("byIsolationMVA3oldDMwLTraw_1", &byIsolationMVA3oldDMwLTraw_1);
	T->Branch("byCombinedIsolationDeltaBetaCorrRaw3Hits_1", &byCombinedIsolationDeltaBetaCorrRaw3Hits_1);
	T->Branch("byIsolationMVArun2v1DBnewDMwLTraw_1", &byIsolationMVArun2v1DBnewDMwLTraw_1);
	T->Branch("decayModeFindingNewDMs_1", &decayModeFindingNewDMs_1);
	T->Branch("pt_2", &pt_2);
	T->Branch("phi_2", &phi_2);
	T->Branch("eta_2", &eta_2);
	T->Branch("m_2", &m_2);
	T->Branch("iso_2", &iso_2);
	T->Branch("dZ_2", &dZ_2);
	T->Branch("dzTauVertex_2", &dzTauVertex_2);
	T->Branch("d0_2", &d0_2);
	T->Branch("q_2", &q_2);
	T->Branch("id_e_mva_nt_loose_2", &id_e_mva_nt_loose_2);
	T->Branch("tau_decay_mode_2", &tau_decay_mode_2);
	T->Branch("ZimpactTau_2", &ZimpactTau_2);
	T->Branch("mt_2", &mt_2);
	T->Branch("pfmt_2", &pfmt_2);
	T->Branch("puppimt_2", &puppimt_2);
	T->Branch("mt_uncorr_2", &mt_uncorr_2);
	T->Branch("responseUP_MTmvaMET_2", &responseUP_MTmvaMET_2);
	T->Branch("responseDOWN_MTmvaMET_2", &responseDOWN_MTmvaMET_2);
	T->Branch("resolutionUP_MTmvaMET_2", &resolutionUP_MTmvaMET_2);
	T->Branch("resolutionDOWN_MTmvaMET_2", &resolutionDOWN_MTmvaMET_2);
	T->Branch("gen_match_2", &gen_match_2);
	T->Branch("genMCmatch_pt_2", &genMCmatch_pt_2);
	T->Branch("genMCmatch_eta_2", &genMCmatch_eta_2);
	T->Branch("genMCmatch_phi_2", &genMCmatch_phi_2);
	T->Branch("genMCmatch_M_2", &genMCmatch_M_2);
	T->Branch("MCMatchPdgId_2", &MCMatchPdgId_2);
	T->Branch("byIsolationMVArun2v1DBoldDMwLTraw_2", &byIsolationMVArun2v1DBoldDMwLTraw_2);
	T->Branch("byTightIsolationMVArun2v1DBoldDMwLT_2", &byTightIsolationMVArun2v1DBoldDMwLT_2);
	T->Branch("byVTightIsolationMVArun2v1DBoldDMwLT_2", &byVTightIsolationMVArun2v1DBoldDMwLT_2);
	T->Branch("byLooseIsolationMVArun2v1DBoldDMwLT_2", &byLooseIsolationMVArun2v1DBoldDMwLT_2);
	T->Branch("byMediumIsolationMVArun2v1DBoldDMwLT_2", &byMediumIsolationMVArun2v1DBoldDMwLT_2);
	T->Branch("byVLooseIsolationMVArun2v1DBoldDMwLT_2", &byVLooseIsolationMVArun2v1DBoldDMwLT_2);
	T->Branch("byVVTightIsolationMVArun2v1DBoldDMwLT_2", &byVVTightIsolationMVArun2v1DBoldDMwLT_2);
	T->Branch("againstElectronVLooseMVA6_2", &againstElectronVLooseMVA6_2);
	T->Branch("againstMuonTight3_2", &againstMuonTight3_2);
	T->Branch("againstElectronTightMVA6_2", &againstElectronTightMVA6_2);
	T->Branch("againstMuonLoose3_2", &againstMuonLoose3_2);
	T->Branch("decayModeFinding_2", &decayModeFinding_2);
	T->Branch("byIsolationMVA3oldDMwLTraw_2", &byIsolationMVA3oldDMwLTraw_2);
	T->Branch("byCombinedIsolationDeltaBetaCorrRaw3Hits_2", &byCombinedIsolationDeltaBetaCorrRaw3Hits_2);
	T->Branch("byIsolationMVArun2v1DBnewDMwLTraw_2", &byIsolationMVArun2v1DBnewDMwLTraw_2);
	T->Branch("decayModeFindingNewDMs_2", &decayModeFindingNewDMs_2);
	T->Branch("pt_tt", &pt_tt);
	T->Branch("DeltaR_leg1_leg2", &DeltaR_leg1_leg2);
	T->Branch("mt_tot", &mt_tot);
	T->Branch("m_vis", &m_vis);
	T->Branch("m_sv", &m_sv);
	T->Branch("mt_sv", &mt_sv);
	T->Branch("SVFit_mvaMET_diTau_pt", &SVFit_mvaMET_diTau_pt);
	T->Branch("SVFit_mvaMET_diTau_eta", &SVFit_mvaMET_diTau_eta);
	T->Branch("SVFit_mvaMET_diTau_phi", &SVFit_mvaMET_diTau_phi);
	T->Branch("SVFit_mvaMET_FittedMET", &SVFit_mvaMET_FittedMET);
	T->Branch("SVFit_mvaMET_FittedMETphi", &SVFit_mvaMET_FittedMETphi);
	T->Branch("mvamet", &mvamet);
	T->Branch("mvametphi", &mvametphi);
	T->Branch("met", &met);
	T->Branch("metphi", &metphi);
	T->Branch("puppimet", &puppimet);
	T->Branch("puppimetphi", &puppimetphi);
	T->Branch("uncorr_mvamet", &uncorr_mvamet);
	T->Branch("uncorr_mvametphi", &uncorr_mvametphi);
	T->Branch("responseUP_mvaMET", &responseUP_mvaMET);
	T->Branch("responseUP_mvaMETphi", &responseUP_mvaMETphi);
	T->Branch("responseDOWN_mvaMET", &responseDOWN_mvaMET);
	T->Branch("responseDOWN_mvaMETphi", &responseDOWN_mvaMETphi);
	T->Branch("resolutionUP_mvaMET", &resolutionUP_mvaMET);
	T->Branch("resolutionUP_mvaMETphi", &resolutionUP_mvaMETphi);
	T->Branch("resolutionDOWN_mvaMET", &resolutionDOWN_mvaMET);
	T->Branch("resolutionDOWN_mvaMETphi", &resolutionDOWN_mvaMETphi);
	T->Branch("mvacov00", &mvacov00);
	T->Branch("mvacov01", &mvacov01);
	T->Branch("mvacov10", &mvacov10);
	T->Branch("mvacov11", &mvacov11);
	T->Branch("metcov00", &metcov00);
	T->Branch("metcov01", &metcov01);
	T->Branch("metcov10", &metcov10);
	T->Branch("metcov11", &metcov11);
	T->Branch("pzetavis", &pzetavis);
	T->Branch("pzetamiss", &pzetamiss);
	T->Branch("pfpzetamiss", &pfpzetamiss);
	T->Branch("puppipzetamiss", &puppipzetamiss);
	T->Branch("pzetamiss_responseUP", &pzetamiss_responseUP);
	T->Branch("pzetamiss_responseDOWN", &pzetamiss_responseDOWN);
	T->Branch("pzetamiss_resolutionUP", &pzetamiss_resolutionUP);
	T->Branch("pzetamiss_resolutionDOWN", &pzetamiss_resolutionDOWN);
	T->Branch("pzetamiss_uncorr", &pzetamiss_uncorr);
	T->Branch("njets", &njets);
	T->Branch("njetspt20", &njetspt20);
	T->Branch("mjj", &mjj);
	T->Branch("jdeta", &jdeta);
	T->Branch("njetingap", &njetingap);
	T->Branch("njetingap20", &njetingap20);
	T->Branch("jdphi", &jdphi);
	T->Branch("jpt_1", &jpt_1);
	T->Branch("jeta_1", &jeta_1);
	T->Branch("jphi_1", &jphi_1);
	T->Branch("jm_1", &jm_1);
	T->Branch("jmva_1", &jmva_1);
	T->Branch("jpt_2", &jpt_2);
	T->Branch("jeta_2", &jeta_2);
	T->Branch("jphi_2", &jphi_2);
	T->Branch("jm_2", &jm_2);
	T->Branch("jmva_2", &jmva_2);
	T->Branch("nbtag", &nbtag);
	T->Branch("nbtag_oneSigmaUp", &nbtag_oneSigmaUp);
	T->Branch("nbtag_oneSigmaDown", &nbtag_oneSigmaDown);
	T->Branch("bpt_1", &bpt_1);
	T->Branch("beta_1", &beta_1);
	T->Branch("bphi_1", &bphi_1);
	T->Branch("bm_1", &bm_1);
	T->Branch("bmva_1", &bmva_1);
	T->Branch("bcsv_1", &bcsv_1);
	T->Branch("bpt_2", &bpt_2);
	T->Branch("beta_2", &beta_2);
	T->Branch("bphi_2", &bphi_2);
	T->Branch("bm_2", &bm_2);
	T->Branch("bmva_2", &bmva_2);
	T->Branch("bcsv_2", &bcsv_2);
	T->Branch("nbtag_LooseWp", &nbtag_LooseWp);
	T->Branch("nbtag_LooseWp_oneSigmaUp", &nbtag_LooseWp_oneSigmaUp);
	T->Branch("nbtag_LooseWp_oneSigmaDown", &nbtag_LooseWp_oneSigmaDown);
	T->Branch("bpt_1_LooseWp", &bpt_1_LooseWp);
	T->Branch("beta_1_LooseWp", &beta_1_LooseWp);
	T->Branch("bphi_1_LooseWp", &bphi_1_LooseWp);
	T->Branch("bm_1_LooseWp", &bm_1_LooseWp);
	T->Branch("bmva_1_LooseWp", &bmva_1_LooseWp);
	T->Branch("bcsv_1_LooseWp", &bcsv_1_LooseWp);
	T->Branch("bpt_2_LooseWp", &bpt_2_LooseWp);
	T->Branch("beta_2_LooseWp", &beta_2_LooseWp);
	T->Branch("bphi_2_LooseWp", &bphi_2_LooseWp);
	T->Branch("bm_2_LooseWp", &bm_2_LooseWp);
	T->Branch("bmva_2_LooseWp", &bmva_2_LooseWp);
	T->Branch("bcsv_2_LooseWp", &bcsv_2_LooseWp);
	T->Branch("nbtag_TightWp", &nbtag_TightWp);
	T->Branch("nbtag_TightWp_oneSigmaUp", &nbtag_TightWp_oneSigmaUp);
	T->Branch("nbtag_TightWp_oneSigmaDown", &nbtag_TightWp_oneSigmaDown);
	T->Branch("bpt_1_TightWp", &bpt_1_TightWp);
	T->Branch("beta_1_TightWp", &beta_1_TightWp);
	T->Branch("bphi_1_TightWp", &bphi_1_TightWp);
	T->Branch("bm_1_TightWp", &bm_1_TightWp);
	T->Branch("bmva_1_TightWp", &bmva_1_TightWp);
	T->Branch("bcsv_1_TightWp", &bcsv_1_TightWp);
	T->Branch("bpt_2_TightWp", &bpt_2_TightWp);
	T->Branch("beta_2_TightWp", &beta_2_TightWp);
	T->Branch("bphi_2_TightWp", &bphi_2_TightWp);
	T->Branch("bm_2_TightWp", &bm_2_TightWp);
	T->Branch("bmva_2_TightWp", &bmva_2_TightWp);
	T->Branch("bcsv_2_TightWp", &bcsv_2_TightWp);
	T->Branch("njets_JECshiftedUp", &njets_JECshiftedUp);
	T->Branch("njetspt20_JECshiftedUp", &njetspt20_JECshiftedUp);
	T->Branch("mjj_JECshiftedUp", &mjj_JECshiftedUp);
	T->Branch("jdeta_JECshiftedUp", &jdeta_JECshiftedUp);
	T->Branch("njetingap_JECshiftedUp", &njetingap_JECshiftedUp);
	T->Branch("njetingap20_JECshiftedUp", &njetingap20_JECshiftedUp);
	T->Branch("jdphi_JECshiftedUp", &jdphi_JECshiftedUp);
	T->Branch("jpt_1_JECshiftedUp", &jpt_1_JECshiftedUp);
	T->Branch("jeta_1_JECshiftedUp", &jeta_1_JECshiftedUp);
	T->Branch("jphi_1_JECshiftedUp", &jphi_1_JECshiftedUp);
	T->Branch("jm_1_JECshiftedUp", &jm_1_JECshiftedUp);
	T->Branch("jmva_1_JECshiftedUp", &jmva_1_JECshiftedUp);
	T->Branch("jpt_2_JECshiftedUp", &jpt_2_JECshiftedUp);
	T->Branch("jeta_2_JECshiftedUp", &jeta_2_JECshiftedUp);
	T->Branch("jphi_2_JECshiftedUp", &jphi_2_JECshiftedUp);
	T->Branch("jm_2_JECshiftedUp", &jm_2_JECshiftedUp);
	T->Branch("jmva_2_JECshiftedUp", &jmva_2_JECshiftedUp);
	T->Branch("nbtag_JECshiftedUp", &nbtag_JECshiftedUp);
	T->Branch("bpt_1_JECshiftedUp", &bpt_1_JECshiftedUp);
	T->Branch("beta_1_JECshiftedUp", &beta_1_JECshiftedUp);
	T->Branch("bphi_1_JECshiftedUp", &bphi_1_JECshiftedUp);
	T->Branch("bm_1_JECshiftedUp", &bm_1_JECshiftedUp);
	T->Branch("bmva_1_JECshiftedUp", &bmva_1_JECshiftedUp);
	T->Branch("bcsv_1_JECshiftedUp", &bcsv_1_JECshiftedUp);
	T->Branch("bpt_2_JECshiftedUp", &bpt_2_JECshiftedUp);
	T->Branch("beta_2_JECshiftedUp", &beta_2_JECshiftedUp);
	T->Branch("bphi_2_JECshiftedUp", &bphi_2_JECshiftedUp);
	T->Branch("bm_2_JECshiftedUp", &bm_2_JECshiftedUp);
	T->Branch("bmva_2_JECshiftedUp", &bmva_2_JECshiftedUp);
	T->Branch("bcsv_2_JECshiftedUp", &bcsv_2_JECshiftedUp);
	T->Branch("nbtag_LooseWp_JECshiftedUp", &nbtag_LooseWp_JECshiftedUp);
	T->Branch("bpt_1_LooseWp_JECshiftedUp", &bpt_1_LooseWp_JECshiftedUp);
	T->Branch("beta_1_LooseWp_JECshiftedUp", &beta_1_LooseWp_JECshiftedUp);
	T->Branch("bphi_1_LooseWp_JECshiftedUp", &bphi_1_LooseWp_JECshiftedUp);
	T->Branch("bm_1_LooseWp_JECshiftedUp", &bm_1_LooseWp_JECshiftedUp);
	T->Branch("bmva_1_LooseWp_JECshiftedUp", &bmva_1_LooseWp_JECshiftedUp);
	T->Branch("bcsv_1_LooseWp_JECshiftedUp", &bcsv_1_LooseWp_JECshiftedUp);
	T->Branch("bpt_2_LooseWp_JECshiftedUp", &bpt_2_LooseWp_JECshiftedUp);
	T->Branch("beta_2_LooseWp_JECshiftedUp", &beta_2_LooseWp_JECshiftedUp);
	T->Branch("bphi_2_LooseWp_JECshiftedUp", &bphi_2_LooseWp_JECshiftedUp);
	T->Branch("bm_2_LooseWp_JECshiftedUp", &bm_2_LooseWp_JECshiftedUp);
	T->Branch("bmva_2_LooseWp_JECshiftedUp", &bmva_2_LooseWp_JECshiftedUp);
	T->Branch("bcsv_2_LooseWp_JECshiftedUp", &bcsv_2_LooseWp_JECshiftedUp);
	T->Branch("nbtag_TightWp_JECshiftedUp", &nbtag_TightWp_JECshiftedUp);
	T->Branch("bpt_1_TightWp_JECshiftedUp", &bpt_1_TightWp_JECshiftedUp);
	T->Branch("beta_1_TightWp_JECshiftedUp", &beta_1_TightWp_JECshiftedUp);
	T->Branch("bphi_1_TightWp_JECshiftedUp", &bphi_1_TightWp_JECshiftedUp);
	T->Branch("bm_1_TightWp_JECshiftedUp", &bm_1_TightWp_JECshiftedUp);
	T->Branch("bmva_1_TightWp_JECshiftedUp", &bmva_1_TightWp_JECshiftedUp);
	T->Branch("bcsv_1_TightWp_JECshiftedUp", &bcsv_1_TightWp_JECshiftedUp);
	T->Branch("bpt_2_TightWp_JECshiftedUp", &bpt_2_TightWp_JECshiftedUp);
	T->Branch("beta_2_TightWp_JECshiftedUp", &beta_2_TightWp_JECshiftedUp);
	T->Branch("bphi_2_TightWp_JECshiftedUp", &bphi_2_TightWp_JECshiftedUp);
	T->Branch("bm_2_TightWp_JECshiftedUp", &bm_2_TightWp_JECshiftedUp);
	T->Branch("bmva_2_TightWp_JECshiftedUp", &bmva_2_TightWp_JECshiftedUp);
	T->Branch("bcsv_2_TightWp_JECshiftedUp", &bcsv_2_TightWp_JECshiftedUp);
	T->Branch("njets_JECshiftedDown", &njets_JECshiftedDown);
	T->Branch("njetspt20_JECshiftedDown", &njetspt20_JECshiftedDown);
	T->Branch("mjj_JECshiftedDown", &mjj_JECshiftedDown);
	T->Branch("jdeta_JECshiftedDown", &jdeta_JECshiftedDown);
	T->Branch("njetingap_JECshiftedDown", &njetingap_JECshiftedDown);
	T->Branch("njetingap20_JECshiftedDown", &njetingap20_JECshiftedDown);
	T->Branch("jdphi_JECshiftedDown", &jdphi_JECshiftedDown);
	T->Branch("jpt_1_JECshiftedDown", &jpt_1_JECshiftedDown);
	T->Branch("jeta_1_JECshiftedDown", &jeta_1_JECshiftedDown);
	T->Branch("jphi_1_JECshiftedDown", &jphi_1_JECshiftedDown);
	T->Branch("jm_1_JECshiftedDown", &jm_1_JECshiftedDown);
	T->Branch("jmva_1_JECshiftedDown", &jmva_1_JECshiftedDown);
	T->Branch("jpt_2_JECshiftedDown", &jpt_2_JECshiftedDown);
	T->Branch("jeta_2_JECshiftedDown", &jeta_2_JECshiftedDown);
	T->Branch("jphi_2_JECshiftedDown", &jphi_2_JECshiftedDown);
	T->Branch("jm_2_JECshiftedDown", &jm_2_JECshiftedDown);
	T->Branch("jmva_2_JECshiftedDown", &jmva_2_JECshiftedDown);
	T->Branch("nbtag_JECshiftedDown", &nbtag_JECshiftedDown);
	T->Branch("bpt_1_JECshiftedDown", &bpt_1_JECshiftedDown);
	T->Branch("beta_1_JECshiftedDown", &beta_1_JECshiftedDown);
	T->Branch("bphi_1_JECshiftedDown", &bphi_1_JECshiftedDown);
	T->Branch("bm_1_JECshiftedDown", &bm_1_JECshiftedDown);
	T->Branch("bmva_1_JECshiftedDown", &bmva_1_JECshiftedDown);
	T->Branch("bcsv_1_JECshiftedDown", &bcsv_1_JECshiftedDown);
	T->Branch("bpt_2_JECshiftedDown", &bpt_2_JECshiftedDown);
	T->Branch("beta_2_JECshiftedDown", &beta_2_JECshiftedDown);
	T->Branch("bphi_2_JECshiftedDown", &bphi_2_JECshiftedDown);
	T->Branch("bm_2_JECshiftedDown", &bm_2_JECshiftedDown);
	T->Branch("bmva_2_JECshiftedDown", &bmva_2_JECshiftedDown);
	T->Branch("bcsv_2_JECshiftedDown", &bcsv_2_JECshiftedDown);
	T->Branch("nbtag_LooseWp_JECshiftedDown", &nbtag_LooseWp_JECshiftedDown);
	T->Branch("bpt_1_LooseWp_JECshiftedDown", &bpt_1_LooseWp_JECshiftedDown);
	T->Branch("beta_1_LooseWp_JECshiftedDown", &beta_1_LooseWp_JECshiftedDown);
	T->Branch("bphi_1_LooseWp_JECshiftedDown", &bphi_1_LooseWp_JECshiftedDown);
	T->Branch("bm_1_LooseWp_JECshiftedDown", &bm_1_LooseWp_JECshiftedDown);
	T->Branch("bmva_1_LooseWp_JECshiftedDown", &bmva_1_LooseWp_JECshiftedDown);
	T->Branch("bcsv_1_LooseWp_JECshiftedDown", &bcsv_1_LooseWp_JECshiftedDown);
	T->Branch("bpt_2_LooseWp_JECshiftedDown", &bpt_2_LooseWp_JECshiftedDown);
	T->Branch("beta_2_LooseWp_JECshiftedDown", &beta_2_LooseWp_JECshiftedDown);
	T->Branch("bphi_2_LooseWp_JECshiftedDown", &bphi_2_LooseWp_JECshiftedDown);
	T->Branch("bm_2_LooseWp_JECshiftedDown", &bm_2_LooseWp_JECshiftedDown);
	T->Branch("bmva_2_LooseWp_JECshiftedDown", &bmva_2_LooseWp_JECshiftedDown);
	T->Branch("bcsv_2_LooseWp_JECshiftedDown", &bcsv_2_LooseWp_JECshiftedDown);
	T->Branch("nbtag_TightWp_JECshiftedDown", &nbtag_TightWp_JECshiftedDown);
	T->Branch("bpt_1_TightWp_JECshiftedDown", &bpt_1_TightWp_JECshiftedDown);
	T->Branch("beta_1_TightWp_JECshiftedDown", &beta_1_TightWp_JECshiftedDown);
	T->Branch("bphi_1_TightWp_JECshiftedDown", &bphi_1_TightWp_JECshiftedDown);
	T->Branch("bm_1_TightWp_JECshiftedDown", &bm_1_TightWp_JECshiftedDown);
	T->Branch("bmva_1_TightWp_JECshiftedDown", &bmva_1_TightWp_JECshiftedDown);
	T->Branch("bcsv_1_TightWp_JECshiftedDown", &bcsv_1_TightWp_JECshiftedDown);
	T->Branch("bpt_2_TightWp_JECshiftedDown", &bpt_2_TightWp_JECshiftedDown);
	T->Branch("beta_2_TightWp_JECshiftedDown", &beta_2_TightWp_JECshiftedDown);
	T->Branch("bphi_2_TightWp_JECshiftedDown", &bphi_2_TightWp_JECshiftedDown);
	T->Branch("bm_2_TightWp_JECshiftedDown", &bm_2_TightWp_JECshiftedDown);
	T->Branch("bmva_2_TightWp_JECshiftedDown", &bmva_2_TightWp_JECshiftedDown);
	T->Branch("bcsv_2_TightWp_JECshiftedDown", &bcsv_2_TightWp_JECshiftedDown);
	T->Branch("njets_JERup", &njets_JERup);
	T->Branch("njetspt20_JERup", &njetspt20_JERup);
	T->Branch("mjj_JERup", &mjj_JERup);
	T->Branch("jdeta_JERup", &jdeta_JERup);
	T->Branch("njetingap_JERup", &njetingap_JERup);
	T->Branch("njetingap20_JERup", &njetingap20_JERup);
	T->Branch("jdphi_JERup", &jdphi_JERup);
	T->Branch("jpt_1_JERup", &jpt_1_JERup);
	T->Branch("jeta_1_JERup", &jeta_1_JERup);
	T->Branch("jphi_1_JERup", &jphi_1_JERup);
	T->Branch("jm_1_JERup", &jm_1_JERup);
	T->Branch("jmva_1_JERup", &jmva_1_JERup);
	T->Branch("jpt_2_JERup", &jpt_2_JERup);
	T->Branch("jeta_2_JERup", &jeta_2_JERup);
	T->Branch("jphi_2_JERup", &jphi_2_JERup);
	T->Branch("jm_2_JERup", &jm_2_JERup);
	T->Branch("jmva_2_JERup", &jmva_2_JERup);
	T->Branch("nbtag_JERup", &nbtag_JERup);
	T->Branch("bpt_1_JERup", &bpt_1_JERup);
	T->Branch("beta_1_JERup", &beta_1_JERup);
	T->Branch("bphi_1_JERup", &bphi_1_JERup);
	T->Branch("bm_1_JERup", &bm_1_JERup);
	T->Branch("bmva_1_JERup", &bmva_1_JERup);
	T->Branch("bcsv_1_JERup", &bcsv_1_JERup);
	T->Branch("bpt_2_JERup", &bpt_2_JERup);
	T->Branch("beta_2_JERup", &beta_2_JERup);
	T->Branch("bphi_2_JERup", &bphi_2_JERup);
	T->Branch("bm_2_JERup", &bm_2_JERup);
	T->Branch("bmva_2_JERup", &bmva_2_JERup);
	T->Branch("bcsv_2_JERup", &bcsv_2_JERup);
	T->Branch("nbtag_LooseWp_JERup", &nbtag_LooseWp_JERup);
	T->Branch("bpt_1_LooseWp_JERup", &bpt_1_LooseWp_JERup);
	T->Branch("beta_1_LooseWp_JERup", &beta_1_LooseWp_JERup);
	T->Branch("bphi_1_LooseWp_JERup", &bphi_1_LooseWp_JERup);
	T->Branch("bm_1_LooseWp_JERup", &bm_1_LooseWp_JERup);
	T->Branch("bmva_1_LooseWp_JERup", &bmva_1_LooseWp_JERup);
	T->Branch("bcsv_1_LooseWp_JERup", &bcsv_1_LooseWp_JERup);
	T->Branch("bpt_2_LooseWp_JERup", &bpt_2_LooseWp_JERup);
	T->Branch("beta_2_LooseWp_JERup", &beta_2_LooseWp_JERup);
	T->Branch("bphi_2_LooseWp_JERup", &bphi_2_LooseWp_JERup);
	T->Branch("bm_2_LooseWp_JERup", &bm_2_LooseWp_JERup);
	T->Branch("bmva_2_LooseWp_JERup", &bmva_2_LooseWp_JERup);
	T->Branch("bcsv_2_LooseWp_JERup", &bcsv_2_LooseWp_JERup);
	T->Branch("nbtag_TightWp_JERup", &nbtag_TightWp_JERup);
	T->Branch("bpt_1_TightWp_JERup", &bpt_1_TightWp_JERup);
	T->Branch("beta_1_TightWp_JERup", &beta_1_TightWp_JERup);
	T->Branch("bphi_1_TightWp_JERup", &bphi_1_TightWp_JERup);
	T->Branch("bm_1_TightWp_JERup", &bm_1_TightWp_JERup);
	T->Branch("bmva_1_TightWp_JERup", &bmva_1_TightWp_JERup);
	T->Branch("bcsv_1_TightWp_JERup", &bcsv_1_TightWp_JERup);
	T->Branch("bpt_2_TightWp_JERup", &bpt_2_TightWp_JERup);
	T->Branch("beta_2_TightWp_JERup", &beta_2_TightWp_JERup);
	T->Branch("bphi_2_TightWp_JERup", &bphi_2_TightWp_JERup);
	T->Branch("bm_2_TightWp_JERup", &bm_2_TightWp_JERup);
	T->Branch("bmva_2_TightWp_JERup", &bmva_2_TightWp_JERup);
	T->Branch("bcsv_2_TightWp_JERup", &bcsv_2_TightWp_JERup);
	T->Branch("njets_JERdown", &njets_JERdown);
	T->Branch("njetspt20_JERdown", &njetspt20_JERdown);
	T->Branch("mjj_JERdown", &mjj_JERdown);
	T->Branch("jdeta_JERdown", &jdeta_JERdown);
	T->Branch("njetingap_JERdown", &njetingap_JERdown);
	T->Branch("njetingap20_JERdown", &njetingap20_JERdown);
	T->Branch("jdphi_JERdown", &jdphi_JERdown);
	T->Branch("jpt_1_JERdown", &jpt_1_JERdown);
	T->Branch("jeta_1_JERdown", &jeta_1_JERdown);
	T->Branch("jphi_1_JERdown", &jphi_1_JERdown);
	T->Branch("jm_1_JERdown", &jm_1_JERdown);
	T->Branch("jmva_1_JERdown", &jmva_1_JERdown);
	T->Branch("jpt_2_JERdown", &jpt_2_JERdown);
	T->Branch("jeta_2_JERdown", &jeta_2_JERdown);
	T->Branch("jphi_2_JERdown", &jphi_2_JERdown);
	T->Branch("jm_2_JERdown", &jm_2_JERdown);
	T->Branch("jmva_2_JERdown", &jmva_2_JERdown);
	T->Branch("nbtag_JERdown", &nbtag_JERdown);
	T->Branch("bpt_1_JERdown", &bpt_1_JERdown);
	T->Branch("beta_1_JERdown", &beta_1_JERdown);
	T->Branch("bphi_1_JERdown", &bphi_1_JERdown);
	T->Branch("bm_1_JERdown", &bm_1_JERdown);
	T->Branch("bmva_1_JERdown", &bmva_1_JERdown);
	T->Branch("bcsv_1_JERdown", &bcsv_1_JERdown);
	T->Branch("bpt_2_JERdown", &bpt_2_JERdown);
	T->Branch("beta_2_JERdown", &beta_2_JERdown);
	T->Branch("bphi_2_JERdown", &bphi_2_JERdown);
	T->Branch("bm_2_JERdown", &bm_2_JERdown);
	T->Branch("bmva_2_JERdown", &bmva_2_JERdown);
	T->Branch("bcsv_2_JERdown", &bcsv_2_JERdown);
	T->Branch("nbtag_LooseWp_JERdown", &nbtag_LooseWp_JERdown);
	T->Branch("bpt_1_LooseWp_JERdown", &bpt_1_LooseWp_JERdown);
	T->Branch("beta_1_LooseWp_JERdown", &beta_1_LooseWp_JERdown);
	T->Branch("bphi_1_LooseWp_JERdown", &bphi_1_LooseWp_JERdown);
	T->Branch("bm_1_LooseWp_JERdown", &bm_1_LooseWp_JERdown);
	T->Branch("bmva_1_LooseWp_JERdown", &bmva_1_LooseWp_JERdown);
	T->Branch("bcsv_1_LooseWp_JERdown", &bcsv_1_LooseWp_JERdown);
	T->Branch("bpt_2_LooseWp_JERdown", &bpt_2_LooseWp_JERdown);
	T->Branch("beta_2_LooseWp_JERdown", &beta_2_LooseWp_JERdown);
	T->Branch("bphi_2_LooseWp_JERdown", &bphi_2_LooseWp_JERdown);
	T->Branch("bm_2_LooseWp_JERdown", &bm_2_LooseWp_JERdown);
	T->Branch("bmva_2_LooseWp_JERdown", &bmva_2_LooseWp_JERdown);
	T->Branch("bcsv_2_LooseWp_JERdown", &bcsv_2_LooseWp_JERdown);
	T->Branch("nbtag_TightWp_JERdown", &nbtag_TightWp_JERdown);
	T->Branch("bpt_1_TightWp_JERdown", &bpt_1_TightWp_JERdown);
	T->Branch("beta_1_TightWp_JERdown", &beta_1_TightWp_JERdown);
	T->Branch("bphi_1_TightWp_JERdown", &bphi_1_TightWp_JERdown);
	T->Branch("bm_1_TightWp_JERdown", &bm_1_TightWp_JERdown);
	T->Branch("bmva_1_TightWp_JERdown", &bmva_1_TightWp_JERdown);
	T->Branch("bcsv_1_TightWp_JERdown", &bcsv_1_TightWp_JERdown);
	T->Branch("bpt_2_TightWp_JERdown", &bpt_2_TightWp_JERdown);
	T->Branch("beta_2_TightWp_JERdown", &beta_2_TightWp_JERdown);
	T->Branch("bphi_2_TightWp_JERdown", &bphi_2_TightWp_JERdown);
	T->Branch("bm_2_TightWp_JERdown", &bm_2_TightWp_JERdown);
	T->Branch("bmva_2_TightWp_JERdown", &bmva_2_TightWp_JERdown);
	T->Branch("bcsv_2_TightWp_JERdown", &bcsv_2_TightWp_JERdown);
	T->Branch("dilepton_veto", &dilepton_veto);
	T->Branch("extraelec_veto", &extraelec_veto);
	T->Branch("extramuon_veto", &extramuon_veto);
	T->Branch("HBHENoiseFilter", &HBHENoiseFilter);
	T->Branch("HBHENoiseIsoFilter", &HBHENoiseIsoFilter);
	T->Branch("CSCTightHalo2015Filter", &CSCTightHalo2015Filter);
	T->Branch("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter);
	T->Branch("goodVerticesFilter", &goodVerticesFilter);
	T->Branch("eeBadScFilter", &eeBadScFilter);
	T->Branch("chargedHadronTrackResolutionFilter", &chargedHadronTrackResolutionFilter);
	T->Branch("muonBadTrackFilter", &muonBadTrackFilter);
	T->Branch("NUP", &NUP);
	T->Branch("weight", &weight);
	T->Branch("generatorEventWeight", &generatorEventWeight);
	T->Branch("lheHT", &lheHT);
	T->Branch("lheOutGoingPartons", &lheOutGoingPartons);
	T->Branch("lheZmass", &lheZmass);
	T->Branch("IsZTT", &IsZTT);
	T->Branch("IsZL", &IsZL);
	T->Branch("IsZJ", &IsZJ);
	T->Branch("IsZLL", &IsZLL);
	T->Branch("DataSet=", &DataSet);
	T->Branch("EventTotal", &EventTotal);
	T->Branch("EventType=", &EventType);
	T->Branch("KeyName=", &KeyName);
	T->Branch("DataCard=", &DataCard);
	T->Branch("CrossSection", &CrossSection);
	T->Branch("FilterEff", &FilterEff);
	T->Branch("isSmallTree", &isSmallTree);
	T->Branch("TauEsNumberSigmasShifted", &TauEsNumberSigmasShifted);
	T->Branch("ElectronEsNumberSigmasShifted", &ElectronEsNumberSigmasShifted);
	T->Branch("veto_leptonType", &veto_leptonType);
	T->Branch("veto_pt", &veto_pt);
	T->Branch("veto_eta", &veto_eta);
	T->Branch("veto_phi", &veto_phi);
	T->Branch("veto_M", &veto_M);
	T->Branch("veto_charge", &veto_charge);
	T->Branch("veto_dxy", &veto_dxy);
	T->Branch("veto_dz", &veto_dz);
	T->Branch("veto_RelIso", &veto_RelIso);
	T->Branch("veto_passesMediumMuonId", &veto_passesMediumMuonId);
	T->Branch("veto_passElectronMVA80", &veto_passElectronMVA80);
	T->Branch("veto_passElectronMVA90", &veto_passElectronMVA90);
	T->Branch("veto_passElectronCutBased", &veto_passElectronCutBased);
	T->Branch("veto_isTrackerGlobalPFMuon", &veto_isTrackerGlobalPFMuon);
	T->Branch("veto_numberOfMissingInnerHits", &veto_numberOfMissingInnerHits);
	T->Branch("veto_numberOfMissingOuterHits", &veto_numberOfMissingOuterHits);
	T->Branch("veto_passConversionVeto", &veto_passConversionVeto);
	T->Branch("veto_LeptonPassesThirdElectronVetoCuts", &veto_LeptonPassesThirdElectronVetoCuts);
	T->Branch("veto_LeptonPassesThirdMuonVetoCuts", &veto_LeptonPassesThirdMuonVetoCuts);
	T->Branch("veto_LeptonPassesDiElectronVetoCuts", &veto_LeptonPassesDiElectronVetoCuts);
	T->Branch("veto_LeptonPassesDiMuonVetoCuts", &veto_LeptonPassesDiMuonVetoCuts);
	T->Branch("LPT", &LPT);
	T->Branch("P_chi", &P_chi);
	T->Branch("M_min", &M_min);
	T->Branch("P_chi_pf", &P_chi_pf);
	T->Branch("M_min_pf", &M_min_pf);
	T->Branch("P_chi_puppi", &P_chi_puppi);
	T->Branch("M_min_puppi", &M_min_puppi);
	T->Branch("P_chi_uncorr", &P_chi_uncorr);
	T->Branch("M_min_uncorr", &M_min_uncorr);
	T->Branch("P_chi_responseUP", &P_chi_responseUP);
	T->Branch("M_min_responseUP", &M_min_responseUP);
	T->Branch("P_chi_responseDOWN", &P_chi_responseDOWN);
	T->Branch("M_min_responseDOWN", &M_min_responseDOWN);
	T->Branch("P_chi_resolutionUP", &P_chi_resolutionUP);
	T->Branch("M_min_resolutionUP", &M_min_resolutionUP);
	T->Branch("P_chi_resolutionDOWN", &P_chi_resolutionDOWN);
	T->Branch("M_min_resolutionDOWN", &M_min_resolutionDOWN);




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



void generateH2TauSyncTree::reset()
{

	/* in general set :

		-- weights to 1.0
		-- floats and doubles to -999.0  ** be careful when cutting to exclude -999.0 for example iso < 0.1 will pass!!! **
		-- ints to -999  ** be careful when cutting to exclude -999.0 for example pT < 100 will pass!!! **
		-- strings to "NULL"
		-- bool to 0
		-- and use .clear() on vectors

	*/


	final_weight = 1.0;
	nominalCrossSection_Weight = 1.0;
	puWeight_Weight = 1.0;
	TopQuarkPtWeight_Weight = 1.0;
	ZReWeight_Weight = 1.0;
	NLOReWeight_Weight = 1.0;
	ScaleFactorsForPair_Weight = 1.0;
	ScaleFactorsForPair_WeightUp = 1.0;
	ScaleFactorsForPair_WeightDown = 1.0;
	QCDWeightForEleMuChannel_Weight = 1.0;
	QCDWeightForEleMuChannel_WeightUp = 1.0;
	QCDWeightForEleMuChannel_WeightDown = 1.0;
	QCDWeightForEleMuChannelNoPZetaCut_Weight = 1.0;
	QCDWeightForEleMuChannelNoPZetaCut_WeightUp = 1.0;
	QCDWeightForEleMuChannelNoPZetaCut_WeightDown = 1.0;
	highPtTauEff_WeightUp = 1.0;
	highPtTauEff_WeightDown = 1.0;

    flag_MVAEventType = -999;

    originalXWGTUP = 1.0;			/* always init a weight to 1.0 */
    theory_scale_factors.clear();	/* std::vectors are reset using clear() */

	pairRank = 999;
	isOsPair = -999;
    genBosonTotal_pt = -999.;
    genBosonTotal_eta = -999.;
    genBosonTotal_phi = -999.;
    genBosonTotal_M = -999.;

	genBosonVisible_pt = -999.;
	genBosonVisible_eta = -999.;
	genBosonVisible_phi = -999.;
	genBosonVisible_M = -999.;

	genTopPt1 = -999.;
	genTopPt2 = -999.;

	run = 0;
	event = 0;
	evt = 0;
	lumi = 0;

	npv =  0;
	npu =  -999.0;
	rho =  -999.0;
	puweight = 1.0;



	pt_1 = -999.0;
	phi_1 = -999.0;
	eta_1 = -999.0;
	m_1 = -999.0;
	iso_1 = -999.0;
	dZ_1 = -999.0;
	dzTauVertex_1 = -999.0;
	d0_1 = -999.0;
	q_1 = -999;
	id_e_mva_nt_loose_1 = -999.0;
	tau_decay_mode_1 = -999;
	ZimpactTau_1 = -999.0;
	mt_1 = -999.0;
	pfmt_1 = -999.0;
	puppimt_1 = -999.0;
	mt_uncorr_1 = -999.0;
	responseUP_MTmvaMET_1 = -999.0;
	responseDOWN_MTmvaMET_1 = -999.0;
	resolutionUP_MTmvaMET_1 = -999.0;
	resolutionDOWN_MTmvaMET_1 = -999.0;
	gen_match_1 = -999;
	genMCmatch_pt_1 = -999.0;
	genMCmatch_eta_1 = -999.0;
	genMCmatch_phi_1 = -999.0;
	genMCmatch_M_1 = -999.0;
	MCMatchPdgId_1 = -999;
	byIsolationMVArun2v1DBoldDMwLTraw_1 = -999.0;
	byTightIsolationMVArun2v1DBoldDMwLT_1 = -999.0;
	byVTightIsolationMVArun2v1DBoldDMwLT_1 = -999.0;
	byLooseIsolationMVArun2v1DBoldDMwLT_1 = -999.0;
	byMediumIsolationMVArun2v1DBoldDMwLT_1 = -999.0;
	byVLooseIsolationMVArun2v1DBoldDMwLT_1 = -999.0;
	byVVTightIsolationMVArun2v1DBoldDMwLT_1 = -999.0;
	againstElectronVLooseMVA6_1 = -999.0;
	againstMuonTight3_1 = -999.0;
	againstElectronTightMVA6_1 = -999.0;
	againstMuonLoose3_1 = -999.0;
	decayModeFinding_1 = -999.0;
	byIsolationMVA3oldDMwLTraw_1 = -999.0;
	byCombinedIsolationDeltaBetaCorrRaw3Hits_1 = -999.0;
	byIsolationMVArun2v1DBnewDMwLTraw_1 = -999.0;
	decayModeFindingNewDMs_1 = -999.0;

	pt_2 = -999.0;
	phi_2 = -999.0;
	eta_2 = -999.0;
	m_2 = -999.0;
	iso_2 = -999.0;
	dZ_2 = -999.0;
	dzTauVertex_2 = -999.0;
	d0_2 = -999.0;
	q_2 = -999;
	id_e_mva_nt_loose_2 = -999.0;
	tau_decay_mode_2 = -999;
	ZimpactTau_2 = -999.0;
	mt_2 = -999.0;
	pfmt_2 = -999.0;
	puppimt_2 = -999.0;
	mt_uncorr_2 = -999.0;
	responseUP_MTmvaMET_2 = -999.0;
	responseDOWN_MTmvaMET_2 = -999.0;
	resolutionUP_MTmvaMET_2 = -999.0;
	resolutionDOWN_MTmvaMET_2 = -999.0;
	gen_match_2 = -999;
	genMCmatch_pt_2 = -999.0;
	genMCmatch_eta_2 = -999.0;
	genMCmatch_phi_2 = -999.0;
	genMCmatch_M_2 = -999.0;
	MCMatchPdgId_2 = -999;
	byIsolationMVArun2v1DBoldDMwLTraw_2 = -999.0;
	byTightIsolationMVArun2v1DBoldDMwLT_2 = -999.0;
	byVTightIsolationMVArun2v1DBoldDMwLT_2 = -999.0;
	byLooseIsolationMVArun2v1DBoldDMwLT_2 = -999.0;
	byMediumIsolationMVArun2v1DBoldDMwLT_2 = -999.0;
	byVLooseIsolationMVArun2v1DBoldDMwLT_2 = -999.0;
	byVVTightIsolationMVArun2v1DBoldDMwLT_2 = -999.0;
	againstElectronVLooseMVA6_2 = -999.0;
	againstMuonTight3_2 = -999.0;
	againstElectronTightMVA6_2 = -999.0;
	againstMuonLoose3_2 = -999.0;
	decayModeFinding_2 = -999.0;
	byIsolationMVA3oldDMwLTraw_2 = -999.0;
	byCombinedIsolationDeltaBetaCorrRaw3Hits_2 = -999.0;
	byIsolationMVArun2v1DBnewDMwLTraw_2 = -999.0;
	decayModeFindingNewDMs_2 = -999.0;

	pt_tt = -999.0;
	DeltaR_leg1_leg2 = -999.0;
	mt_tot = -999.0;
	m_vis = -999.0;
	m_sv = -999.0;
	mt_sv = -999.0;
	SVFit_mvaMET_diTau_pt = -999.0;
	SVFit_mvaMET_diTau_eta = -999.0;
	SVFit_mvaMET_diTau_phi = -999.0;
	SVFit_mvaMET_FittedMET = -999.0;
	SVFit_mvaMET_FittedMETphi = -999.0;
	mvamet = -999.0;
	mvametphi = -999.0;
	met = -999.0;
	metphi = -999.0;
	puppimet = -999.0;
	puppimetphi = -999.0;
	uncorr_mvamet = -999.0;
	uncorr_mvametphi = -999.0;
	responseUP_mvaMET = -999.0;
	responseUP_mvaMETphi = -999.0;
	responseDOWN_mvaMET = -999.0;
	responseDOWN_mvaMETphi = -999.0;
	resolutionUP_mvaMET = -999.0;
	resolutionUP_mvaMETphi = -999.0;
	resolutionDOWN_mvaMET = -999.0;
	resolutionDOWN_mvaMETphi = -999.0;
	mvacov00 = -999.0;
	mvacov01 = -999.0;
	mvacov10 = -999.0;
	mvacov11 = -999.0;
	metcov00 = -999.0;
	metcov01 = -999.0;
	metcov10 = -999.0;
	metcov11 = -999.0;
	pzetavis = -999.0;
	pzetamiss = -999.0;
	pfpzetamiss = -999.0;
	puppipzetamiss = -999.0;
	pzetamiss_responseUP = -999.0;
	pzetamiss_responseDOWN = -999.0;
	pzetamiss_resolutionUP = -999.0;
	pzetamiss_resolutionDOWN = -999.0;
	pzetamiss_uncorr = -999.0;


	njets = -999;
	njetspt20 = -999;
	mjj = -999.0;
	jdeta = -999.0;
	njetingap = -999.0;
	njetingap20 = -999.0;
	jdphi = -999.0;
	jpt_1 = -999.0;
	jeta_1 = -999.0;
	jphi_1 = -999.0;
	jm_1 = -999.0;
	jmva_1 = -999.0;
	jpt_2 = -999.0;
	jeta_2 = -999.0;
	jphi_2 = -999.0;
	jm_2 = -999.0;
	jmva_2 = -999.0;
	nbtag = -999;
	nbtag_oneSigmaUp = -999;
	nbtag_oneSigmaDown = -999;
	bpt_1 = -999.0;
	beta_1 = -999.0;
	bphi_1 = -999.0;
	bm_1 = -999.0;
	bmva_1 = -999.0;
	bcsv_1 = -999.0;
	bpt_2 = -999.0;
	beta_2 = -999.0;
	bphi_2 = -999.0;
	bm_2 = -999.0;
	bmva_2 = -999.0;
	bcsv_2 = -999.0;
	nbtag_LooseWp = -999;
	nbtag_LooseWp_oneSigmaUp = -999;
	nbtag_LooseWp_oneSigmaDown = -999;
	bpt_1_LooseWp = -999.0;
	beta_1_LooseWp = -999.0;
	bphi_1_LooseWp = -999.0;
	bm_1_LooseWp = -999.0;
	bmva_1_LooseWp = -999.0;
	bcsv_1_LooseWp = -999.0;
	bpt_2_LooseWp = -999.0;
	beta_2_LooseWp = -999.0;
	bphi_2_LooseWp = -999.0;
	bm_2_LooseWp = -999.0;
	bmva_2_LooseWp = -999.0;
	bcsv_2_LooseWp = -999.0;
	nbtag_TightWp = -999;
	nbtag_TightWp_oneSigmaUp = -999;
	nbtag_TightWp_oneSigmaDown = -999;
	bpt_1_TightWp = -999.0;
	beta_1_TightWp = -999.0;
	bphi_1_TightWp = -999.0;
	bm_1_TightWp = -999.0;
	bmva_1_TightWp = -999.0;
	bcsv_1_TightWp = -999.0;
	bpt_2_TightWp = -999.0;
	beta_2_TightWp = -999.0;
	bphi_2_TightWp = -999.0;
	bm_2_TightWp = -999.0;
	bmva_2_TightWp = -999.0;
	bcsv_2_TightWp = -999.0;
	njets_JECshiftedUp = -999;
	njetspt20_JECshiftedUp = -999;
	mjj_JECshiftedUp = -999.0;
	jdeta_JECshiftedUp = -999.0;
	njetingap_JECshiftedUp = -999.0;
	njetingap20_JECshiftedUp = -999.0;
	jdphi_JECshiftedUp = -999.0;
	jpt_1_JECshiftedUp = -999.0;
	jeta_1_JECshiftedUp = -999.0;
	jphi_1_JECshiftedUp = -999.0;
	jm_1_JECshiftedUp = -999.0;
	jmva_1_JECshiftedUp = -999.0;
	jpt_2_JECshiftedUp = -999.0;
	jeta_2_JECshiftedUp = -999.0;
	jphi_2_JECshiftedUp = -999.0;
	jm_2_JECshiftedUp = -999.0;
	jmva_2_JECshiftedUp = -999.0;
	nbtag_JECshiftedUp = -999;
	bpt_1_JECshiftedUp = -999.0;
	beta_1_JECshiftedUp = -999.0;
	bphi_1_JECshiftedUp = -999.0;
	bm_1_JECshiftedUp = -999.0;
	bmva_1_JECshiftedUp = -999.0;
	bcsv_1_JECshiftedUp = -999.0;
	bpt_2_JECshiftedUp = -999.0;
	beta_2_JECshiftedUp = -999.0;
	bphi_2_JECshiftedUp = -999.0;
	bm_2_JECshiftedUp = -999.0;
	bmva_2_JECshiftedUp = -999.0;
	bcsv_2_JECshiftedUp = -999.0;
	nbtag_LooseWp_JECshiftedUp = -999;
	bpt_1_LooseWp_JECshiftedUp = -999.0;
	beta_1_LooseWp_JECshiftedUp = -999.0;
	bphi_1_LooseWp_JECshiftedUp = -999.0;
	bm_1_LooseWp_JECshiftedUp = -999.0;
	bmva_1_LooseWp_JECshiftedUp = -999.0;
	bcsv_1_LooseWp_JECshiftedUp = -999.0;
	bpt_2_LooseWp_JECshiftedUp = -999.0;
	beta_2_LooseWp_JECshiftedUp = -999.0;
	bphi_2_LooseWp_JECshiftedUp = -999.0;
	bm_2_LooseWp_JECshiftedUp = -999.0;
	bmva_2_LooseWp_JECshiftedUp = -999.0;
	bcsv_2_LooseWp_JECshiftedUp = -999.0;
	nbtag_TightWp_JECshiftedUp = -999;
	bpt_1_TightWp_JECshiftedUp = -999.0;
	beta_1_TightWp_JECshiftedUp = -999.0;
	bphi_1_TightWp_JECshiftedUp = -999.0;
	bm_1_TightWp_JECshiftedUp = -999.0;
	bmva_1_TightWp_JECshiftedUp = -999.0;
	bcsv_1_TightWp_JECshiftedUp = -999.0;
	bpt_2_TightWp_JECshiftedUp = -999.0;
	beta_2_TightWp_JECshiftedUp = -999.0;
	bphi_2_TightWp_JECshiftedUp = -999.0;
	bm_2_TightWp_JECshiftedUp = -999.0;
	bmva_2_TightWp_JECshiftedUp = -999.0;
	bcsv_2_TightWp_JECshiftedUp = -999.0;
	njets_JECshiftedDown = -999;
	njetspt20_JECshiftedDown = -999;
	mjj_JECshiftedDown = -999.0;
	jdeta_JECshiftedDown = -999.0;
	njetingap_JECshiftedDown = -999.0;
	njetingap20_JECshiftedDown = -999.0;
	jdphi_JECshiftedDown = -999.0;
	jpt_1_JECshiftedDown = -999.0;
	jeta_1_JECshiftedDown = -999.0;
	jphi_1_JECshiftedDown = -999.0;
	jm_1_JECshiftedDown = -999.0;
	jmva_1_JECshiftedDown = -999.0;
	jpt_2_JECshiftedDown = -999.0;
	jeta_2_JECshiftedDown = -999.0;
	jphi_2_JECshiftedDown = -999.0;
	jm_2_JECshiftedDown = -999.0;
	jmva_2_JECshiftedDown = -999.0;
	nbtag_JECshiftedDown = -999;
	bpt_1_JECshiftedDown = -999.0;
	beta_1_JECshiftedDown = -999.0;
	bphi_1_JECshiftedDown = -999.0;
	bm_1_JECshiftedDown = -999.0;
	bmva_1_JECshiftedDown = -999.0;
	bcsv_1_JECshiftedDown = -999.0;
	bpt_2_JECshiftedDown = -999.0;
	beta_2_JECshiftedDown = -999.0;
	bphi_2_JECshiftedDown = -999.0;
	bm_2_JECshiftedDown = -999.0;
	bmva_2_JECshiftedDown = -999.0;
	bcsv_2_JECshiftedDown = -999.0;
	nbtag_LooseWp_JECshiftedDown = -999;
	bpt_1_LooseWp_JECshiftedDown = -999.0;
	beta_1_LooseWp_JECshiftedDown = -999.0;
	bphi_1_LooseWp_JECshiftedDown = -999.0;
	bm_1_LooseWp_JECshiftedDown = -999.0;
	bmva_1_LooseWp_JECshiftedDown = -999.0;
	bcsv_1_LooseWp_JECshiftedDown = -999.0;
	bpt_2_LooseWp_JECshiftedDown = -999.0;
	beta_2_LooseWp_JECshiftedDown = -999.0;
	bphi_2_LooseWp_JECshiftedDown = -999.0;
	bm_2_LooseWp_JECshiftedDown = -999.0;
	bmva_2_LooseWp_JECshiftedDown = -999.0;
	bcsv_2_LooseWp_JECshiftedDown = -999.0;
	nbtag_TightWp_JECshiftedDown = -999;
	bpt_1_TightWp_JECshiftedDown = -999.0;
	beta_1_TightWp_JECshiftedDown = -999.0;
	bphi_1_TightWp_JECshiftedDown = -999.0;
	bm_1_TightWp_JECshiftedDown = -999.0;
	bmva_1_TightWp_JECshiftedDown = -999.0;
	bcsv_1_TightWp_JECshiftedDown = -999.0;
	bpt_2_TightWp_JECshiftedDown = -999.0;
	beta_2_TightWp_JECshiftedDown = -999.0;
	bphi_2_TightWp_JECshiftedDown = -999.0;
	bm_2_TightWp_JECshiftedDown = -999.0;
	bmva_2_TightWp_JECshiftedDown = -999.0;
	bcsv_2_TightWp_JECshiftedDown = -999.0;
	njets_JERup = -999;
	njetspt20_JERup = -999;
	mjj_JERup = -999.0;
	jdeta_JERup = -999.0;
	njetingap_JERup = -999.0;
	njetingap20_JERup = -999.0;
	jdphi_JERup = -999.0;
	jpt_1_JERup = -999.0;
	jeta_1_JERup = -999.0;
	jphi_1_JERup = -999.0;
	jm_1_JERup = -999.0;
	jmva_1_JERup = -999.0;
	jpt_2_JERup = -999.0;
	jeta_2_JERup = -999.0;
	jphi_2_JERup = -999.0;
	jm_2_JERup = -999.0;
	jmva_2_JERup = -999.0;
	nbtag_JERup = -999;
	bpt_1_JERup = -999.0;
	beta_1_JERup = -999.0;
	bphi_1_JERup = -999.0;
	bm_1_JERup = -999.0;
	bmva_1_JERup = -999.0;
	bcsv_1_JERup = -999.0;
	bpt_2_JERup = -999.0;
	beta_2_JERup = -999.0;
	bphi_2_JERup = -999.0;
	bm_2_JERup = -999.0;
	bmva_2_JERup = -999.0;
	bcsv_2_JERup = -999.0;
	nbtag_LooseWp_JERup = -999;
	bpt_1_LooseWp_JERup = -999.0;
	beta_1_LooseWp_JERup = -999.0;
	bphi_1_LooseWp_JERup = -999.0;
	bm_1_LooseWp_JERup = -999.0;
	bmva_1_LooseWp_JERup = -999.0;
	bcsv_1_LooseWp_JERup = -999.0;
	bpt_2_LooseWp_JERup = -999.0;
	beta_2_LooseWp_JERup = -999.0;
	bphi_2_LooseWp_JERup = -999.0;
	bm_2_LooseWp_JERup = -999.0;
	bmva_2_LooseWp_JERup = -999.0;
	bcsv_2_LooseWp_JERup = -999.0;
	nbtag_TightWp_JERup = -999;
	bpt_1_TightWp_JERup = -999.0;
	beta_1_TightWp_JERup = -999.0;
	bphi_1_TightWp_JERup = -999.0;
	bm_1_TightWp_JERup = -999.0;
	bmva_1_TightWp_JERup = -999.0;
	bcsv_1_TightWp_JERup = -999.0;
	bpt_2_TightWp_JERup = -999.0;
	beta_2_TightWp_JERup = -999.0;
	bphi_2_TightWp_JERup = -999.0;
	bm_2_TightWp_JERup = -999.0;
	bmva_2_TightWp_JERup = -999.0;
	bcsv_2_TightWp_JERup = -999.0;
	njets_JERdown = -999;
	njetspt20_JERdown = -999;
	mjj_JERdown = -999.0;
	jdeta_JERdown = -999.0;
	njetingap_JERdown = -999.0;
	njetingap20_JERdown = -999.0;
	jdphi_JERdown = -999.0;
	jpt_1_JERdown = -999.0;
	jeta_1_JERdown = -999.0;
	jphi_1_JERdown = -999.0;
	jm_1_JERdown = -999.0;
	jmva_1_JERdown = -999.0;
	jpt_2_JERdown = -999.0;
	jeta_2_JERdown = -999.0;
	jphi_2_JERdown = -999.0;
	jm_2_JERdown = -999.0;
	jmva_2_JERdown = -999.0;
	nbtag_JERdown = -999;
	bpt_1_JERdown = -999.0;
	beta_1_JERdown = -999.0;
	bphi_1_JERdown = -999.0;
	bm_1_JERdown = -999.0;
	bmva_1_JERdown = -999.0;
	bcsv_1_JERdown = -999.0;
	bpt_2_JERdown = -999.0;
	beta_2_JERdown = -999.0;
	bphi_2_JERdown = -999.0;
	bm_2_JERdown = -999.0;
	bmva_2_JERdown = -999.0;
	bcsv_2_JERdown = -999.0;
	nbtag_LooseWp_JERdown = -999;
	bpt_1_LooseWp_JERdown = -999.0;
	beta_1_LooseWp_JERdown = -999.0;
	bphi_1_LooseWp_JERdown = -999.0;
	bm_1_LooseWp_JERdown = -999.0;
	bmva_1_LooseWp_JERdown = -999.0;
	bcsv_1_LooseWp_JERdown = -999.0;
	bpt_2_LooseWp_JERdown = -999.0;
	beta_2_LooseWp_JERdown = -999.0;
	bphi_2_LooseWp_JERdown = -999.0;
	bm_2_LooseWp_JERdown = -999.0;
	bmva_2_LooseWp_JERdown = -999.0;
	bcsv_2_LooseWp_JERdown = -999.0;
	nbtag_TightWp_JERdown = -999;
	bpt_1_TightWp_JERdown = -999.0;
	beta_1_TightWp_JERdown = -999.0;
	bphi_1_TightWp_JERdown = -999.0;
	bm_1_TightWp_JERdown = -999.0;
	bmva_1_TightWp_JERdown = -999.0;
	bcsv_1_TightWp_JERdown = -999.0;
	bpt_2_TightWp_JERdown = -999.0;
	beta_2_TightWp_JERdown = -999.0;
	bphi_2_TightWp_JERdown = -999.0;
	bm_2_TightWp_JERdown = -999.0;
	bmva_2_TightWp_JERdown = -999.0;
	bcsv_2_TightWp_JERdown = -999.0;

	dilepton_veto = -999.0;
	extraelec_veto = -999.0;
	extramuon_veto = -999.0;

	HBHENoiseFilter = 0;
	HBHENoiseIsoFilter = 0;
	CSCTightHalo2015Filter = 0;
	EcalDeadCellTriggerPrimitiveFilter = 0;
	goodVerticesFilter = 0;
	eeBadScFilter = 0;
	chargedHadronTrackResolutionFilter = 0;
	muonBadTrackFilter = 0;

	NUP = -999;
	weight = 1.0;
	generatorEventWeight = 1.0;
	lheHT = -999.0;
	lheOutGoingPartons = -999;
	lheZmass = -999.0;

	IsZTT = -999;
	IsZL = -999;
	IsZJ = -999;
	IsZLL = -999;

	DataSet= "NULL";
	EventTotal = -999;
	EventType= "NULL";
	KeyName= "NULL";
	DataCard= "NULL";
	CrossSection = -999.0;
	FilterEff = -999.0;
	isSmallTree = 0;
	TauEsNumberSigmasShifted = -999.0;
	ElectronEsNumberSigmasShifted = -999.0;

	veto_leptonType.clear();
	veto_pt.clear();
	veto_eta.clear();
	veto_phi.clear();
	veto_M.clear();
	veto_charge.clear();
	veto_dxy.clear();
	veto_dz.clear();
	veto_RelIso.clear();
	veto_passesMediumMuonId.clear();
	veto_passElectronMVA80.clear();
	veto_passElectronMVA90.clear();
	veto_passElectronCutBased.clear();
	veto_isTrackerGlobalPFMuon.clear();
	veto_numberOfMissingInnerHits.clear();
	veto_numberOfMissingOuterHits.clear();
	veto_passConversionVeto.clear();
	veto_LeptonPassesThirdElectronVetoCuts.clear();
	veto_LeptonPassesThirdMuonVetoCuts.clear();
	veto_LeptonPassesDiElectronVetoCuts.clear();
	veto_LeptonPassesDiMuonVetoCuts.clear();


    LPT = -999.;


	//  expanded for sys. + alternate mets

    P_chi = -999.;
    M_min = -999.;
    
	P_chi_pf = -999.0;
	M_min_pf = -999.0;
	P_chi_puppi = -999.0;
	M_min_puppi = -999.0;
	P_chi_uncorr = -999.0;
	M_min_uncorr = -999.0;
	P_chi_responseUP = -999.0;
	M_min_responseUP = -999.0;
	P_chi_responseDOWN = -999.0;
	M_min_responseDOWN = -999.0;
	P_chi_resolutionUP = -999.0;
	M_min_resolutionUP = -999.0;
	P_chi_resolutionDOWN = -999.0;
	M_min_resolutionDOWN = -999.0;




}

std::vector<double> generateH2TauSyncTree::GetLeg1Leg2McTriggerWeights(TLorentzVector l1,TLorentzVector l2,
			int candType, int sysShift)
{
	std::vector<double> returnVec; /* index 0 is leg1 sf, index 1 is leg2 sf */
	returnVec.clear();




	return returnVec;

}

double generateH2TauSyncTree::CBeff(double pt, std::array <double, 5> par)
{
	/* note : arg must be ordered in this way :
	 m0    = par[0]
	 sigma = par[1] 
	 alpha = par[2]
	 n     = par[3]
	 norm =  par[4]
	*/

	return CBeff(pt, par[0], par[1], par[2] , par[3] , par[4]);

}



double generateH2TauSyncTree::CBeff(double pt, double m0, double sigma, double alpha, double n, double norm)
{
	/* from python in https://indico.cern.ch/event/489915/contributions/
	1167924/attachments/1227657/1798150/htt_12_2_2016.pdf#page=6*/
	
	double sqrtPiOver2 = std::sqrt(TMath::PiOver2());
	double sqrt2 = std::sqrt(2.);
	double sig = fabs(sigma);
	double t = (pt - m0)/sig * alpha /fabs(alpha);
	double absAlpha = fabs(alpha/sig); 

	double a = TMath::Power(n/absAlpha, n) * TMath::Exp(-0.5*absAlpha*absAlpha); 
	double b = absAlpha - n/absAlpha;
	double arg = absAlpha/sqrt2; 

	double ApproxErf = 1.;

	if (arg > 5.)  		  ApproxErf = 1.; 
	else if (arg < -5.)   ApproxErf = - 1.;
	else  				  ApproxErf = TMath::Erf(arg);

	double leftArea    = ( 1. +  ApproxErf) * sqrtPiOver2; 
	double rightArea   = ( a *1./TMath::Power(absAlpha-b, n-1) ) / (n-1) ;
	double area        = leftArea + rightArea; 


	if (t <= absAlpha )
	{
		arg = t / sqrt2;
		if (arg > 5.)        ApproxErf = 1.;
		else if (arg < -5.)  ApproxErf = -1.;
		else  			     ApproxErf = TMath::Erf(arg);
	
		return norm * (1+ ApproxErf) * sqrtPiOver2 / area; 
	}


	else
	{
		double num = norm * (leftArea + a * (1./TMath::Power(t-b,n-1) - 1./TMath::Power(absAlpha - b,n-1)) / (1-n));
		return (num / area);
	}
}




void generateH2TauSyncTree::initScaleFactorParametersRunII()
{

	// Run II efficiencies for HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg

	Run2_TauTau_legTriggerEff_Data = {3.45412e+01 , 5.63353e+00 , 2.49242e+00 , 3.35896e+00 , 1.00000e+00};
	Run2_TauTau_legTriggerEff_DataUP = {3.31713e+01 , 5.66551e+00 , 1.87175e+00 , 8.07790e+00 , 1.00000e+00};
	Run2_TauTau_legTriggerEff_DataDOWN = {3.56264e+01 , 5.30711e+00 , 2.81591e+00 , 2.40649e+00 , 9.99958e-01};
	Run2_TauTau_legTriggerEff_Mc = {3.60274e+01 , 5.89434e+00 , 5.82870e+00 , 1.83737e+00 , 9.58000e-01};
	Run2_TauTau_legTriggerEff_McUP = {3.56012e+01 , 5.97209e+00 , 6.09604e+00 , 1.68740e+00 , 9.87653e-01};
	Run2_TauTau_legTriggerEff_McDOWN = {3.62436e+01 , 5.58461e+00 , 5.12924e+00 , 2.05921e+00 , 9.32305e-01};
}





double generateH2TauSyncTree::GetTransverseMass(TLorentzVector L, TLorentzVector T)
{
  double pTxMET = sqrt(L.X()*L.X()+L.Y()*L.Y())*sqrt(T.X()*T.X()+T.Y()*T.Y());
  double CosDphi = cos(L.DeltaPhi(T));
  double MtSq = (2 * pTxMET*(1-CosDphi));
  return sqrt(MtSq);

}



void generateH2TauSyncTree::fillJetBranches(bool eventHasNominalLeptonEnergyScales, bool eventIsNotSmallTree,
											std::string variantString, jetDescription &jetDesc)
{


	////////////////////////////////////////////////////////////////////////
	// based on variantString, figure out which jet collection to access  //

	assert( variantString == "" ||\
	   variantString == "_JECshiftedUp" ||\
	   variantString == "_JECshiftedDown" ||\
	   variantString == "_JERup" ||\
	   variantString == "_JERdown" );





  	/////////////////////////////////////////////////////
  	//  JETS + btagging  + alternate btags      //
  	/////////////////////////////////////////////////////


	/* these jet variables are accessible in FlatTuple only 
	   if dealing with nominal jets OR nominal Tau/Electron Energy Scale */

	std::vector<double> jets_pt; 						jets_pt.clear();
	std::vector<double> jets_eta; 						jets_eta.clear();
	std::vector<double> jets_phi; 						jets_phi.clear();
	std::vector<double> jets_M; 						jets_M.clear();
	std::vector<double> jets_IsBTagged_LooseWpCentral; 	jets_IsBTagged_LooseWpCentral.clear();
	std::vector<double> jets_IsBTagged_MediumWpCentral; jets_IsBTagged_MediumWpCentral.clear();
	std::vector<double> jets_IsBTagged_TightWpCentral; 	jets_IsBTagged_TightWpCentral.clear();


	if( eventHasNominalLeptonEnergyScales || variantString=="" )
	{

		jets_pt 						=  R.getVD("jets_pt"+variantString);
		jets_eta 						=  R.getVD("jets_eta"+variantString);
		jets_phi 						=  R.getVD("jets_phi"+variantString);
		jets_M 							=  R.getVD("jets_M"+variantString);
		jets_IsBTagged_LooseWpCentral 	=  R.getVD("jets_IsBTagged_LooseWpCentral"+variantString);
		jets_IsBTagged_MediumWpCentral	=  R.getVD("jets_IsBTagged_MediumWpCentral"+variantString);
		jets_IsBTagged_TightWpCentral 	=  R.getVD("jets_IsBTagged_TightWpCentral"+variantString);

	}


	/* these jet variables are accessible in FlatTuple only if dealing 
	   with nominal jets AND nominal Tau/Electron Energy Scale */


	std::vector<double>	jets_IsBTagged_LooseWpUp;	 jets_IsBTagged_LooseWpUp.clear();
	std::vector<double> jets_IsBTagged_LooseWpDown;	 jets_IsBTagged_LooseWpDown.clear();
	std::vector<double>	jets_IsBTagged_MediumWpUp;	 jets_IsBTagged_MediumWpUp.clear();
	std::vector<double>	jets_IsBTagged_MediumWpDown; jets_IsBTagged_MediumWpDown.clear();
	std::vector<double>	jets_IsBTagged_TightWpUp;	 jets_IsBTagged_TightWpUp.clear();
	std::vector<double>	jets_IsBTagged_TightWpDown;	 jets_IsBTagged_TightWpDown.clear();


	/* only kept b-tag shifts in nominal case */
	if( eventHasNominalLeptonEnergyScales && variantString=="" )
	{
		jets_IsBTagged_LooseWpUp  	= R.getVD("jets_IsBTagged_LooseWpUp"+variantString);
		jets_IsBTagged_LooseWpDown  = R.getVD("jets_IsBTagged_LooseWpDown"+variantString);
		jets_IsBTagged_MediumWpUp  	= R.getVD("jets_IsBTagged_MediumWpUp"+variantString);
		jets_IsBTagged_MediumWpDown = R.getVD("jets_IsBTagged_MediumWpDown"+variantString);
		jets_IsBTagged_TightWpUp  	= R.getVD("jets_IsBTagged_TightWpUp"+variantString);
		jets_IsBTagged_TightWpDown  = R.getVD("jets_IsBTagged_TightWpDown"+variantString);
	}

	/* these jet variables are accessible in FlatTuple only if dealing 
	   with nominal jets */


	std::vector<float> jets_defaultBtagAlgorithm_RawScore; 		jets_defaultBtagAlgorithm_RawScore.clear();
	std::vector<double> jets_PU_jetIdRaw; 						jets_PU_jetIdRaw.clear();

	if( variantString=="" )
	{
		jets_defaultBtagAlgorithm_RawScore 	=  R.getVF("jets_defaultBtagAlgorithm_RawScore"+variantString);
		jets_PU_jetIdRaw 					=  R.getVD("jets_PU_jetIdRaw"+variantString);
	}

	
	/* counters for nominal JEC and JER jets */
	/* reset the b-tag counters to zero since we are counting them now */

	jetDesc.m_njets				= 0;
	jetDesc.m_njetspt20			= 0;

	jetDesc.m_njetingap 		= 0;	// Only filled if njetspt20>=2 
	jetDesc.m_njetingap20  		= 0; 	// Only filled if njetspt20>=2 

	/* b-tag counters */

   	jetDesc.m_nbtag 				= 0; // (medium WP central)
    jetDesc.m_nbtag_oneSigmaUp 		= 0; // (medium WP UP : one sigma + shift in btag sys)
    jetDesc.m_nbtag_oneSigmaDown	= 0; // (medium WP DOWN : one sigma - shift in btag sys)

	jetDesc.m_nbtag_LooseWp					= 0;  // (loose WP central)
	jetDesc.m_nbtag_LooseWp_oneSigmaUp		= 0;  // (loose WP UP : one sigma + shift in btag sys)
	jetDesc.m_nbtag_LooseWp_oneSigmaDown	= 0;  // (loose WP DOWN : one sigma - shift in btag sys)

	jetDesc.m_nbtag_TightWp					= 0;  // (tight WP central)
	jetDesc.m_nbtag_TightWp_oneSigmaUp 		= 0;  // (tight WP UP : one sigma + shift in btag sys)
	jetDesc.m_nbtag_TightWp_oneSigmaDown	= 0;  // (tight WP DOWN : one sigma - shift in btag sys)

	/* vectors to hold B-tagged jet pair index */
	
	std::vector < std::size_t > Bjet_pair;			// (medium Wp central)
	Bjet_pair.clear();

	std::vector < std::size_t > Bjet_pairUP;		// (medium Wp central + 1 sigma shift UP on btag sys.)
	Bjet_pairUP.clear();

	std::vector < std::size_t > Bjet_pairDOWN;		// (medium Wp central - 1 sigma shift DOWN on btag sys.)
	Bjet_pairDOWN.clear();

	std::vector < std::size_t > Bjet_pair_looseWp;	// (loose Wp central)
	Bjet_pair_looseWp.clear();

	std::vector < std::size_t > Bjet_pair_looseWpUP;  // (loose Wp central shift UP)
	Bjet_pair_looseWpUP.clear();

	std::vector < std::size_t > Bjet_pair_looseWpDOWN; // (loose Wp central shift DOWN)
	Bjet_pair_looseWpDOWN.clear();

	std::vector < std::size_t > Bjet_pair_tightWp;		// (tight Wp central)
	Bjet_pair_tightWp.clear();

	std::vector < std::size_t > Bjet_pair_tightWpUP;	// (tight Wp central shift UP)
	Bjet_pair_tightWpUP.clear();

	std::vector < std::size_t > Bjet_pair_tightWpDOWN;	// (tight Wp central shift DOWN)
	Bjet_pair_tightWpDOWN.clear();


	/* begin a loop on the nominal jets to figure out b-tagging */

	for(std::size_t i = 0; i<jets_pt.size();++i)
 	{ 		

 		if( fabs(jets_eta[i]) < 4.7 && jets_pt[i] > 30)  jetDesc.m_njets++;		
		if( fabs(jets_eta[i]) < 4.7 && jets_pt[i] > 20)  jetDesc.m_njetspt20++;


 		if( fabs(jets_eta[i]) < 2.4 && jets_pt[i] > 20) 
 		{	
 			if( eventHasNominalLeptonEnergyScales || variantString=="" )
 			{
	 			if(jets_IsBTagged_LooseWpCentral[i] > 0.5)	Bjet_pair_looseWp.push_back(i);
	 			if(jets_IsBTagged_MediumWpCentral[i] > 0.5)	Bjet_pair.push_back(i);
	 			if(jets_IsBTagged_TightWpCentral[i] > 0.5)	Bjet_pair_tightWp.push_back(i);
	 		}

			if( eventHasNominalLeptonEnergyScales  && variantString=="" )
			{
				if(jets_IsBTagged_LooseWpUp[i] > 0.5)		Bjet_pair_looseWpUP.push_back(i);  	
				if(jets_IsBTagged_LooseWpDown[i] > 0.5)		Bjet_pair_looseWpDOWN.push_back(i);  
				if(jets_IsBTagged_MediumWpUp[i] > 0.5)		Bjet_pairUP.push_back(i);  	
				if(jets_IsBTagged_MediumWpDown[i] > 0.5)	Bjet_pairDOWN.push_back(i); 
				if(jets_IsBTagged_TightWpUp[i] > 0.5)		Bjet_pair_tightWpUP.push_back(i);  	
				if(jets_IsBTagged_TightWpDown[i] > 0.5)		Bjet_pair_tightWpDOWN.push_back(i);  
			}
		}
 	}


 	/* begin computation of branches for nomina jets & b-tags */


	//////////////////////////////////////////////////////////////////////////////
	// some 4-vectors we will need

	TLorentzVector   j1_20(0.,0.,0.,0.);
	TLorentzVector   j2_20(0.,0.,0.,0.);

	if(jets_pt.size() >= 1) 
	{
		j1_20.SetPtEtaPhiM(jets_pt[0],jets_eta[0],jets_phi[0],jets_M[0]);
		jetDesc.m_jpt_1 = jets_pt[0];
		jetDesc.m_jeta_1 = jets_eta[0];
		jetDesc.m_jphi_1 = jets_phi[0];
		jetDesc.m_jm_1 = jets_M[0];
		if( variantString=="" ) jetDesc.m_jmva_1 = jets_PU_jetIdRaw[0];
	}


	if(jets_pt.size() >= 2)
	{	
		j2_20.SetPtEtaPhiM(jets_pt[1],jets_eta[1],jets_phi[1],jets_M[1]);
		jetDesc.m_jpt_2 = jets_pt[1];
		jetDesc.m_jeta_2 = jets_eta[1];
		jetDesc.m_jphi_2 = jets_phi[1];
		jetDesc.m_jm_2 = jets_M[1];
		if( variantString=="" ) jetDesc.m_jmva_2 = jets_PU_jetIdRaw[1];


		jetDesc.m_mjj = (j1_20+j2_20).M();
	 	jetDesc.m_jdeta = (j1_20.Eta()-j2_20.Eta());
	 	jetDesc.m_jdphi = (j1_20.Phi()-j2_20.Phi());



		 if(jets_eta.size()>2)
		 {
		 	for(std::size_t i = 2; i<jets_eta.size();++i)
		 	{
		 		double current_eta = jets_eta[i];
		 		double low_bound = std::min(jets_eta[0],jets_eta[1]);
		 		double high_bound = std::max(jets_eta[0],jets_eta[1]);

		 		if(current_eta>low_bound && high_bound>current_eta)
		 		{
		 			if(jets_pt[i]>20) jetDesc.m_njetingap20++;
		 			if(jets_pt[i]>30) jetDesc.m_njetingap++;
		 		}
		 	}
		 }
	} // at least 2 jets

	/* handle the b-tag counts, since b-tag counts are small and +, ignore std::size_t vs int difference here */

   	jetDesc.m_nbtag 						= Bjet_pair.size();
    jetDesc.m_nbtag_oneSigmaUp 				= Bjet_pairUP.size();
    jetDesc.m_nbtag_oneSigmaDown			= Bjet_pairDOWN.size();

	jetDesc.m_nbtag_LooseWp					= Bjet_pair_looseWp.size();		
	jetDesc.m_nbtag_LooseWp_oneSigmaUp		= Bjet_pair_looseWpUP.size();
	jetDesc.m_nbtag_LooseWp_oneSigmaDown	= Bjet_pair_looseWpDOWN.size();

	jetDesc.m_nbtag_TightWp					= Bjet_pair_tightWp.size();
	jetDesc.m_nbtag_TightWp_oneSigmaUp 		= Bjet_pair_tightWpUP.size();
	jetDesc.m_nbtag_TightWp_oneSigmaDown	= Bjet_pair_tightWpDOWN.size();


	/* handle b-jet 1 and 2 quantities */

	if(Bjet_pair_looseWp.size() > 0)
	{
		jetDesc.m_bpt_1_LooseWp 		= jets_pt[Bjet_pair_looseWp[0]];
		jetDesc.m_beta_1_LooseWp 		= jets_eta[Bjet_pair_looseWp[0]];
		jetDesc.m_bphi_1_LooseWp 		= jets_phi[Bjet_pair_looseWp[0]];
		jetDesc.m_bm_1_LooseWp 			= jets_M[Bjet_pair_looseWp[0]];
		

		if( variantString=="" ) 
		{
			jetDesc.m_bmva_1_LooseWp 		= jets_PU_jetIdRaw[Bjet_pair_looseWp[0]];
			jetDesc.m_bcsv_1_LooseWp 		= jets_defaultBtagAlgorithm_RawScore[Bjet_pair_looseWp[0]];
		}	

		if(Bjet_pair_looseWp.size() > 1)
		{
			jetDesc.m_bpt_2_LooseWp 		= jets_pt[Bjet_pair_looseWp[1]];
			jetDesc.m_beta_2_LooseWp 		= jets_eta[Bjet_pair_looseWp[1]];
			jetDesc.m_bphi_2_LooseWp 		= jets_phi[Bjet_pair_looseWp[1]];
			jetDesc.m_bm_2_LooseWp 			= jets_M[Bjet_pair_looseWp[1]];
			if( variantString=="" ) 
			{
				jetDesc.m_bmva_2_LooseWp 		= jets_PU_jetIdRaw[Bjet_pair_looseWp[1]];
				jetDesc.m_bcsv_2_LooseWp 		= jets_defaultBtagAlgorithm_RawScore[Bjet_pair_looseWp[1]];
			}
		} 
	}
	if(Bjet_pair.size() > 0)
	{
		jetDesc.m_bpt_1 		= jets_pt[Bjet_pair[0]];
		jetDesc.m_beta_1 		= jets_eta[Bjet_pair[0]];
		jetDesc.m_bphi_1 		= jets_phi[Bjet_pair[0]];
		jetDesc.m_bm_1 			= jets_M[Bjet_pair[0]];
		if( variantString=="" ) 			{
			jetDesc.m_bmva_1 		= jets_PU_jetIdRaw[Bjet_pair[0]];
			jetDesc.m_bcsv_1 		= jets_defaultBtagAlgorithm_RawScore[Bjet_pair[0]];
		}	

		if(Bjet_pair.size() > 1)
		{

			jetDesc.m_bpt_2 		= jets_pt[Bjet_pair[1]];
			jetDesc.m_beta_2 		= jets_eta[Bjet_pair[1]];
			jetDesc.m_bphi_2 		= jets_phi[Bjet_pair[1]];
			jetDesc.m_bm_2 			= jets_M[Bjet_pair[1]];
			if( variantString=="" ) 
			{
				jetDesc.m_bmva_2 		= jets_PU_jetIdRaw[Bjet_pair[1]];
				jetDesc.m_bcsv_2 		= jets_defaultBtagAlgorithm_RawScore[Bjet_pair[1]];
			}
		} 
	}
	if(Bjet_pair_tightWp.size() > 0)
	{

		jetDesc.m_bpt_1_TightWp 		= jets_pt[Bjet_pair_tightWp[0]];
		jetDesc.m_beta_1_TightWp 		= jets_eta[Bjet_pair_tightWp[0]];
		jetDesc.m_bphi_1_TightWp 		= jets_phi[Bjet_pair_tightWp[0]];
		jetDesc.m_bm_1_TightWp 			= jets_M[Bjet_pair_tightWp[0]];
		if( variantString=="" ) 
		{
			jetDesc.m_bmva_1_TightWp 		= jets_PU_jetIdRaw[Bjet_pair_tightWp[0]];
			jetDesc.m_bcsv_1_TightWp 		= jets_defaultBtagAlgorithm_RawScore[Bjet_pair_tightWp[0]];
		}

		if(Bjet_pair_tightWp.size() > 1)
		{

			jetDesc.m_bpt_2_TightWp 		= jets_pt[Bjet_pair_tightWp[1]];
			jetDesc.m_beta_2_TightWp 		= jets_eta[Bjet_pair_tightWp[1]];
			jetDesc.m_bphi_2_TightWp 		= jets_phi[Bjet_pair_tightWp[1]];
			jetDesc.m_bm_2_TightWp 			= jets_M[Bjet_pair_tightWp[1]];
			if( variantString=="" ) 
			{
				jetDesc.m_bmva_2_TightWp 		= jets_PU_jetIdRaw[Bjet_pair_tightWp[1]];
				jetDesc.m_bcsv_2_TightWp 		= jets_defaultBtagAlgorithm_RawScore[Bjet_pair_tightWp[1]];
			}
		} 
	}	
	
}


double generateH2TauSyncTree::getFinalWeight(bool verbose_)
{

	// init weight

	double returnWeight_ = 1.0;


	/* include the nominal cross section / events weight */

	returnWeight_ *= getNominalWeight(verbose_);

	/* for MC include the puWeight */

	if(R.getB("isRealData") == 0)
	{
		returnWeight_ *= R.getD("puWeight");
	}


	/* include top pt rewight (this returns 1.0 for non ttbar sample ) */

	returnWeight_ *=  getTopQuarkPtWeight(verbose_);


	/* include z reweight (this returns 1.0 for non DY (and also 1.0 for low mass DY)) */

	returnWeight_ *=   getZReWeight(verbose_);

	/* include susy ggH NLO weight (1.0 for non valid samples ) 
		susy signal samples use 10 as tan beta --- need to double check on this
	*/

	returnWeight_ *= getNLOReWeight(verbose_, 10 );


	/* include trigger x id x iso scale factor */

	returnWeight_ *= getFinalScaleFactorsForPair(0,0);

	return returnWeight_;
}





/* function: getNominalWeight 
		-- nomial weight = (1000 * cross-section) / (crab_job_eff * EventTotal * FilterEff) in pb
		-- valid for all samples except data, W+jets, DY+jets, (returns to 1.0, for data)
		-- for DY and W+jets returns stiching weights		
		-- for SUSY Higgs & mono-Higgs the cross-sections are set to 1.0 			
*/

double generateH2TauSyncTree::getNominalWeight(bool verbose_)
{

	/* return 1.0 for data */

	if(R.getB("isRealData") == 1) 
	{
		if(verbose_) std::cout<<" real data, nominal weight returned as 1.0 \n";
		return 1.0;
	}
	


	if(R.getS("KeyName") == "Fall15_DY1Jet_MG5_DY" ||\
	   R.getS("KeyName") == "Fall15_DY2Jet_MG5_DY" ||\
	   R.getS("KeyName") == "Fall15_DY3Jet_MG5_DY" ||\
	   R.getS("KeyName") == "Fall15_DY4Jet_MG5_DY" ||\
	   R.getS("KeyName") == "Fall15_DYInc_MG5_DY"  ||\
	   R.getS("KeyName") == "Fall15_DYInc_MG5_DY"  ||\
	   R.getS("KeyName") == "Fall15_DYhighMass_MG5_DY")	
	{
		if(verbose_) std::cout<<R.getS("KeyName")<<" is DY + jets MG5, nominal weight returned as stitching weight \n"; 

		int outgoingJets_ = R.getI("lheOutGoingPartons");
		double genBosonMass_ = R.getD("genBosonTotal_M");

		/* for correct treatment divided by Z->tt, Z->ee, and Z->mumu */


    	if(R.getB("isZTTatGenLevel") == 1)
    	{

			if(outgoingJets_==0 && genBosonMass_ <= 150.0) return 0.024618874;
			if(outgoingJets_==0 && genBosonMass_ >  150.0) return 0.001276291;
			if(outgoingJets_==1 && genBosonMass_ <= 150.0) return 0.010713441;
			if(outgoingJets_==1 && genBosonMass_ >  150.0) return 0.001195827;
			if(outgoingJets_==2 && genBosonMass_ <= 150.0) return 0.011198121;
			if(outgoingJets_==2 && genBosonMass_ >  150.0) return 0.001201632;
			if(outgoingJets_==3 && genBosonMass_ <= 150.0) return 0.011565680;
			if(outgoingJets_==3 && genBosonMass_ >  150.0) return 0.001205744;
			if(outgoingJets_>=4 && genBosonMass_ <= 150.0) return 0.009662968;
			if(outgoingJets_>=4 && genBosonMass_ >  150.0) return 0.001181490;


    	}	

	    if(R.getB("isZEEatGenLevel") == 1 || R.getB("isZMMatGenLevel") == 1)
	    {

			if(outgoingJets_==0 && genBosonMass_ <= 150.0)  return 		0.024618874;
			if(outgoingJets_==0 && genBosonMass_ >  150.0)  return 		0.024618874;
			if(outgoingJets_==1 && genBosonMass_ <= 150.0)  return 		0.010713441;
			if(outgoingJets_==1 && genBosonMass_ >  150.0)  return 		0.010713441;
			if(outgoingJets_==2 && genBosonMass_ <= 150.0)  return 		0.011198121;
			if(outgoingJets_==2 && genBosonMass_ >  150.0)  return 		0.011198121;
			if(outgoingJets_==3 && genBosonMass_ <= 150.0)  return 		0.011565680;
			if(outgoingJets_==3 && genBosonMass_ >  150.0)  return 		0.011565680;
			if(outgoingJets_>=4 && genBosonMass_ <= 150.0)  return 		0.009662968;
			if(outgoingJets_>=4 && genBosonMass_ >  150.0)  return 		0.009662968;

	    }



	}


	if(R.getS("KeyName") == "Fall15_WJetsToLNu" ||\
	   R.getS("KeyName") == "Fall15_W1JetsToLNu" ||\
	   R.getS("KeyName") == "Fall15_W2JetsToLNu" ||\
	   R.getS("KeyName") == "Fall15_W3JetsToLNu" ||\
	   R.getS("KeyName") == "Fall15_W4JetsToLNu")
	{
		if(verbose_) std::cout<<R.getS("KeyName")<<" is W + jets, nominal weight returned as stitching weight \n"; 

		int outgoingJets_ = R.getI("lheOutGoingPartons");

		if(outgoingJets_==0) return 1.30460066773353;
		if(outgoingJets_==1) return 0.21623381588984;
		if(outgoingJets_==2) return 0.11590066273500;
		if(outgoingJets_==3) return 0.05859814170525;
		if(outgoingJets_>=4) return 0.06288760531249;
	}



	/* for other samples return the nominal weight */

	double nominal_weight = ( 1000.0 * R.getD("CrossSection") ) / ( R.getI("EventTotal") * R.getD("FilterEff"));

	/* for a few samples crab job running was not 100% so we need to compensate for the missing fraction */


	if(R.getS("KeyName") == "Fall15_ZZTo2L2Q")
	{
		nominal_weight *= 1.0/0.999347654;

	}

	if(R.getS("KeyName") == "Fall15_SUSYggBBHTauTau_M2600")
	{
		nominal_weight *= 1.0/0.98685;

	}




	return nominal_weight;


}




/* function: getTopQuarkPtWeight 
		-- returns  top_wt = sqrt(exp(0.156-0.00137*top_1_pt)*exp(0.156-0.00137*top_2_pt)) (with top_x_pt capped at 400)
		   for ttbar samples
		-- returns 1.0 for all other samples
*/

double generateH2TauSyncTree::getTopQuarkPtWeight(bool verbose_)
{

	double returnWeight_ = 1.0;

	if(R.getS("KeyName") == "Fall15_TT_Powheg")
	{

		double top_1_pt = std::min(R.getD("genTopPt1"), 400.0);
		double top_2_pt = std::min(R.getD("genTopPt2"), 400.0);

		returnWeight_ = sqrt(exp(0.156-0.00137*top_1_pt)*exp(0.156-0.00137*top_2_pt));


		if(verbose_) std::cout<<" in top sample with pt1, pt2 = "<<top_1_pt<<" , "<<top_2_pt<<" get top pt weight = "<<returnWeight_<<"\n";



	}

	return returnWeight_;

}          



double generateH2TauSyncTree::getZReWeight(bool verbose_)
{
	double returnWeight_ = 1.0;

	bool calc = 0;

	if(R.getS("KeyName") == "Fall15_DY1Jet_MG5_DY") 			calc = 1;
	else if(R.getS("KeyName") == "Fall15_DY2Jet_MG5_DY")		calc = 1;
	else if(R.getS("KeyName") == "Fall15_DY3Jet_MG5_DY")		calc = 1;
	else if(R.getS("KeyName") == "Fall15_DY4Jet_MG5_DY")		calc = 1;
	else if(R.getS("KeyName") == "Fall15_DYInc_MG5_DY")			calc = 1;
	else if(R.getS("KeyName") == "Fall15_DYhighMass_MG5_DY")	calc = 1;


	if(calc == 0)
	{
		if(verbose_) std::cout<<" non dy sample, return z reweight as 1.0 \n";
		return 1.0;
	}


	double genpT 	= R.getD("genBosonTotal_pt");
	double genMass 	= R.getD("genBosonTotal_M");
	returnWeight_ = zweightHist->GetBinContent(zweightHist->GetXaxis()->FindBin(genMass),
											   zweightHist->GetYaxis()->FindBin(genpT));

	if(verbose_) 
	{
		std::cout<<"  for dy sample, return z reweight wt( "<<genMass<<" , "<<	genpT <<" ) = "<<returnWeight_<<"\n";

	}

	return returnWeight_;

}        










/* function: getHighPtTauUncertainty(bool)
		-- returns  vector with element [0] = 1 + 0.2 * (gen_tauPt)/1000.0 and element [1] = 1 - 0.2 * (gen_tauPt)/1000.0
		-- for events with 2 hadronically decaying taus, uses the formula eff(leg1) + eff(leg2) - eff(leg1)*eff(leg2)
*/

std::vector<double> generateH2TauSyncTree::getHighPtTauUncertainty(bool verbose_)
{
	std::vector<double> returnVec_; 
	returnVec_.clear();

	double unc1 = 0.;
	double unc2 = 0.;
	double eff1 = 1.0;
	double eff2 = 1.0;

	/* leg1 */
	if(R.getI("leg1_leptonType") == 3 && R.getI("leg1_MCMatchType")==5)
	{
		unc1 = 0.2 * R.getD("leg1_genMCmatch_pt")/1000.0;
		if(verbose_) std::cout<<" applying high pt tau eff unc. to leg1 \n";

	}

	/* leg2 */
	if(R.getI("leg2_leptonType") == 3 && R.getI("leg2_MCMatchType")==5)
	{

		unc2 = 0.2 * R.getD("leg2_genMCmatch_pt")/1000.0;
		if(verbose_) std::cout<<" applying high pt tau eff unc. to leg2 \n";

	}

	/* if MC compute the uncertainty */
	if(R.getB("isRealData") == 0)
	{
		/* get the up shift */
		eff1 = 1 + (unc1 + unc2 - unc1 * unc2);

		/* get the down shift */
		eff2 = 1 - (unc1 + unc2 - unc1 * unc2);


	}

	returnVec_.clear();
	returnVec_.push_back(eff1);
	returnVec_.push_back(eff2);

	return returnVec_;

}   


/* function: getNLOReWeight 
		-- returns  NLO Higgs Pt based reweight for SUSY signal samples			   
		-- returns 1.0 for all other samples
*/

double generateH2TauSyncTree::getNLOReWeight(bool verbose_, int tanBeta_)
{
	bool eval_ = 0;
	int mass_ = 0;


		if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M80") {eval_ = 1; mass_ = 80;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M90") {eval_ = 1; mass_ = 90;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M100") {eval_ = 1; mass_ = 100;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M110") {eval_ = 1; mass_ = 110;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M120") {eval_ = 1; mass_ = 120;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M130") {eval_ = 1; mass_ = 130;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M140") {eval_ = 1; mass_ = 140;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M160") {eval_ = 1; mass_ = 160;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M180") {eval_ = 1; mass_ = 180;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M200") {eval_ = 1; mass_ = 200;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M250") {eval_ = 1; mass_ = 250;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M300") {eval_ = 1; mass_ = 300;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M350") {eval_ = 1; mass_ = 350;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M400") {eval_ = 1; mass_ = 400;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M450") {eval_ = 1; mass_ = 450;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M500") {eval_ = 1; mass_ = 500;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M600") {eval_ = 1; mass_ = 600;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M700") {eval_ = 1; mass_ = 700;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M800") {eval_ = 1; mass_ = 800;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M900") {eval_ = 1; mass_ = 900;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M1000") {eval_ = 1; mass_ = 1000;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M1200") {eval_ = 1; mass_ = 1200;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M1400") {eval_ = 1; mass_ = 1400;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M1500") {eval_ = 1; mass_ = 1500;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M1600") {eval_ = 1; mass_ = 1600;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M1800") {eval_ = 1; mass_ = 1800;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M2000") {eval_ = 1; mass_ = 2000;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M2300") {eval_ = 1; mass_ = 2300;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M2600") {eval_ = 1; mass_ = 2600;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M2900") {eval_ = 1; mass_ = 2900;}
	else if( R.getS("KeyName") == "Fall15_SUSYggHTauTau_M3200") {eval_ = 1; mass_ = 3200;}


	/* return 1.0 for all non SUSY GGH samples */
	if(!eval_) return 1.0;


	/* else evalualte the NLO reweight */

	return NLO_returnNLOweight(mass_, tanBeta_, R.getD("genBosonTotal_pt"));

}




/* adapted from https://github.com/CMS-HTT/NLOReweightingTool */
void  generateH2TauSyncTree::NLO_ReadFile()
{

  TFile *file = new TFile("Reweight.root");

  const int num_of_tb = 60;  

  int imass = 0;
  for(auto mass: NLO_marray){
    for(int tanb=0; tanb < num_of_tb; tanb++){

      TString wname = "weight_MSSM_";
      wname += mass;
      wname += "_tanb_";
      wname += tanb + 1;

      //      std::cout << wname << " " << NLO_func[imass][tanb] << " " << NLO_func[imass][tanb]->GetBinContent(1) << std::endl;
      // NLO_func[imass][tanb] = (TGraphErrors*) gROOT->FindObject(wname); /* original code, replaced by Get */

	  NLO_func[imass][tanb] = (TGraphErrors*) file->Get(wname);

    }    
    imass++;
  }

}


/* adapted from https://github.com/CMS-HTT/NLOReweightingTool */
float generateH2TauSyncTree::NLO_returnNLOweight(Int_t mass, Int_t tanb, Double_t pt)
{


  if(pt > 800){
    //    std::cout << "[INFO] pT = " << pt << " exceeds the range --> set it to 800." << std::endl;    
    pt = 800;
  }

  auto iter = std::find(NLO_marray.begin(), NLO_marray.end(), mass);
  size_t index = std::distance(NLO_marray.begin(), iter);

  if(index == NLO_marray.size()){
    std::cout << "[WARNING] Invalid mass point ... " << mass << " -> return weight 1" << std::endl;    
    return 1;
  }
  
  if(tanb <1 || tanb > 60){
    std::cout << "[WARNING] Invalid tan(beta) point ... " << tanb << " -> return weight 1" << std::endl;
    return 1;
  }

  return NLO_func[index][tanb-1]->Eval(pt) ;

}



/* function: getQCDWeightForEleMuChannel(bool)
	-- returns a size 6 double vector with elements :

	double qcdweight @ element 0
	double qcdweightup @ element 1 
	double qcdweightdown @ element 2 
	double qcdweightNoDZeta @ element 3 
	double qcdweightupNoDZeta @ element 4
	double qcdweightdownNoDZeta @ element 5 

	all set to 1.0 in case not e+mu channel

*/

std::vector<double> generateH2TauSyncTree::getQCDWeightForEleMuChannel(bool verbose)
{


	std::vector <double> returnVec;
	returnVec.clear();

	// accessing OS/SS extrapolation factor as a function
	// of pt(e), pt(mu), and dR(e,mu)

	if(R.getI("CandidateEventType") != 2) 
	{
		if(verbose) std::cout<<" qcd weights for ele mu channel called for non ele-mu channel returning <1.0> \n";
		for(int k=0; k<6; ++k) returnVec.push_back(1.0);
		return returnVec;

	}

	if(verbose) std::cout<<" qcd weights for ele mu channel called for ele-mu channel returning weights vector \n";
		


	double pt_e = R.getD("leg1_pt");
	double pt_m = R.getD("leg2_pt");
	double dR = R.getD("DeltaR_leg1_leg2");


	/* should always have leg1 = e and leg2 = mu, but just in case order changes in the future */
	if(R.getI("leg1_leptonType")!=1 && R.getI("leg2_leptonType") == 1)  pt_e = R.getD("leg2_pt");
	if(R.getI("leg2_leptonType")!=2 && R.getI("leg1_leptonType") == 2)   pt_m = R.getD("leg1_pt");


	double qcdweight = qcdWeights->getWeight(pt_e,pt_m,dR);

	// accessing OS/SS extrapolation factor corresponding
	// to +1sigma systematic variation of QCD background shape

	double qcdweightup = qcdWeights->getWeightUp(pt_e,pt_m,dR);

	// We suggest to compute OS/SS extrapolation factor
	// corresponding to the -1sigma systematic variation
	// of the QCD background shape as

	double qcdweightdown = 1; 
	if(qcdweightup != 0) qcdweightdown = qcdweight * qcdweight / qcdweightup;



	double qcdweightNoDZeta = qcdWeightsNoDZeta->getWeight(pt_e,pt_m,dR);

	// accessing OS/SS extrapolation factor corresponding
	// to +1sigma systematic variation of QCD background shape

	double qcdweightupNoDZeta = qcdWeightsNoDZeta->getWeightUp(pt_e,pt_m,dR);

	// We suggest to compute OS/SS extrapolation factor
	// corresponding to the -1sigma systematic variation
	// of the QCD background shape as

	double qcdweightdownNoDZeta = 1; 
	if(qcdweightupNoDZeta != 0) qcdweightdownNoDZeta = qcdweightNoDZeta * qcdweightNoDZeta / qcdweightupNoDZeta;


	returnVec.push_back(qcdweight);
	returnVec.push_back(qcdweightup);
	returnVec.push_back(qcdweightdown);
	returnVec.push_back(qcdweightNoDZeta);
	returnVec.push_back(qcdweightupNoDZeta);
	returnVec.push_back(qcdweightdownNoDZeta);


	return returnVec;
}


double generateH2TauSyncTree::getFinalScaleFactorsForPair(bool verbose, int sysShift)
{
	double returnSF = 1.0;

	/* muon + tau */
	if(R.getI("CandidateEventType") == 5)
	{
		if(verbose) std::cout<<" id x iso x trigger sf for Muon + Tau \n";

		double muonID = 1.0;
		double muonTrigger = 1.0;

		/* muon */
		double pt1 = 0.0;
		double eta1 = 0.0;

		/* should always have leg1 = mu and leg2 = tau, but just in case order changes in the future */
		if(R.getI("leg1_leptonType")==2 && R.getI("leg2_leptonType") == 3)  
		{
			pt1 = R.getD("leg1_pt");
			eta1 = R.getD("leg1_eta");


		}

		if(R.getI("leg2_leptonType")==2 && R.getI("leg1_leptonType") == 3)   
		{
			pt1 = R.getD("leg2_pt");
			eta1 = R.getD("leg2_eta");


		}


		muonID = sfTool_Muon_IdIso0p10_eff->get_ScaleFactor(pt1,eta1);
		muonTrigger = sfTool_Muon_SingleMu_eff->get_ScaleFactor(pt1,eta1);

		returnSF = muonID * muonTrigger;

	/////////////////////////////////////
		return returnSF;
	}



	/* electron + tau */
	if(R.getI("CandidateEventType") == 3)
	{

		if(verbose) std::cout<<" id x iso x trigger sf for Electron + Tau \n";


		double electronID = 1.0;
		double electronTrigger = 1.0;

		/* electron */
		double pt1 = 0.0;
		double eta1 = 0.0;


		/* should always have leg1 = electron and leg2 = tau, but just in case order changes in the future */
		if(R.getI("leg1_leptonType")==1 && R.getI("leg2_leptonType") == 3)  
		{
			pt1 = R.getD("leg1_pt");
			eta1 = R.getD("leg1_eta");


		}

		if(R.getI("leg2_leptonType")==1 && R.getI("leg1_leptonType") == 3)   
		{
			pt1 = R.getD("leg2_pt");
			eta1 = R.getD("leg2_eta");


		}


		electronID = sfTool_Electron_IdIso0p10_eff->get_ScaleFactor(pt1,eta1);
		electronTrigger = sfTool_Electron_SingleEle_eff->get_ScaleFactor(pt1,eta1);

		returnSF = electronID * electronTrigger;

	/////////////////////////////////////
		return returnSF;
	}




	/* electron + muon */
	if(R.getI("CandidateEventType") == 2)
	{

		if(verbose) std::cout<<" id x iso x trigger sf for Electron + Muon \n";


		double effData = 1.0;
		double effMC = 1.0;
		double electronID = 1.0;
		double muonID = 1.0;
		double SF = 1.0;


		/* electron */
		double pt1 = 0.0;
		double eta1 = 0.0;

		/* muon */
		double pt2 = 0.0;
		double eta2 = 0.0;


		/* should always have leg1 = electron and leg2 = muon, but just in case order changes in the future */
		if(R.getI("leg1_leptonType")==1 && R.getI("leg2_leptonType") == 2)  
		{
			pt1 = R.getD("leg1_pt");
			eta1 = R.getD("leg1_eta");

			pt2 = R.getD("leg2_pt");
			eta2 = R.getD("leg2_eta");
		}

		if(R.getI("leg2_leptonType")==1 && R.getI("leg1_leptonType") == 2)   
		{
			pt1 = R.getD("leg2_pt");
			eta1 = R.getD("leg2_eta");

			pt2 = R.getD("leg1_pt");
			eta2 = R.getD("leg1_eta");
		}


		electronID = sfTool_Electron_IdIso0p15_eff->get_ScaleFactor(pt1,eta1);
		muonID = sfTool_Muon_IdIso0p15_eff->get_ScaleFactor(pt2,eta2);







 		/* effData = eff_data(Mu17)*eff_data(Ele12)
 		+eff_data(Mu8)*eff_data(Ele17)-eff_data(Mu17)*eff_data(Ele17) */

		effData =  sfTool_Muon_Mu17_eff->get_EfficiencyData(pt2, eta2)*sfTool_Electron_Ele12_eff->get_EfficiencyData(pt1, eta1);
		effData += sfTool_Muon_Mu8_eff->get_EfficiencyData(pt2, eta2)*sfTool_Electron_Ele17_eff->get_EfficiencyData(pt1, eta1);
		effData -= sfTool_Muon_Mu17_eff->get_EfficiencyData(pt2, eta2) * sfTool_Electron_Ele17_eff->get_EfficiencyData(pt1, eta1);  		


 		/* effMC = eff_MC(Mu17)*eff_MC(Ele12)
 		+eff_MC(Mu8)*eff_MC(Ele17)-eff_MC(Mu17)*eff_MC(Ele17)  */


		effMC =  sfTool_Muon_Mu17_eff->get_EfficiencyMC(pt2, eta2)*sfTool_Electron_Ele12_eff->get_EfficiencyMC(pt1, eta1);
		effMC += sfTool_Muon_Mu8_eff->get_EfficiencyMC(pt2, eta2)*sfTool_Electron_Ele17_eff->get_EfficiencyMC(pt1, eta1);
		effMC -= sfTool_Muon_Mu17_eff->get_EfficiencyMC(pt2, eta2) * sfTool_Electron_Ele17_eff->get_EfficiencyMC(pt1, eta1);  		


		if(effMC!=0.) SF = effData/effMC;


		returnSF = electronID * muonID * SF;

	/////////////////////////////////////
		return returnSF;
	}





	/* tau + tau */
	if(R.getI("CandidateEventType") == 6)
	{

		if(verbose) 
		{
			std::cout<<"  trigger sf for Tau + Tau with systematic shifted "<<sysShift<<" sigmas \n";
		}

		double effData1 = 1.0;
		double effMC1 = 1.0;
		double SF1 = 1.0;

		double effData2 = 1.0;
		double effMC2 = 1.0;
		double SF2 = 1.0;


		/* tau1 */
		double pt1 = R.getD("leg1_pt");

		/* tau2 */
		double pt2 = R.getD("leg2_pt");

		/* make sure sysShift is valid */
		assert (sysShift==0 || sysShift==1 || sysShift == -1);


		if( sysShift == 0)
		{
			effData1 = CBeff( pt1, Run2_TauTau_legTriggerEff_Data);
			effData2 = CBeff( pt2, Run2_TauTau_legTriggerEff_Data);

			effMC1 = CBeff( pt1, Run2_TauTau_legTriggerEff_Mc);
			effMC2 = CBeff( pt2, Run2_TauTau_legTriggerEff_Mc);

			if(effMC1!=0) SF1 = effData1/effMC1;
			if(effMC2!=0)  SF2 = effData2/effMC2;

			returnSF = SF1 * SF2;
		}

		else if( sysShift == 1) /* defined as up data over down mc */
		{
			effData1 = CBeff( pt1, Run2_TauTau_legTriggerEff_DataUP);
			effData2 = CBeff( pt2, Run2_TauTau_legTriggerEff_DataUP);

			effMC1 = CBeff( pt1, Run2_TauTau_legTriggerEff_McDOWN);
			effMC2 = CBeff( pt2, Run2_TauTau_legTriggerEff_McDOWN);

			if(effMC1!=0) SF1 = effData1/effMC1;
			if(effMC2!=0)  SF2 = effData2/effMC2;

			returnSF = SF1 * SF2;
		}



		else if( sysShift == -1) /* defined as down data over up mc */
		{
			effData1 = CBeff( pt1, Run2_TauTau_legTriggerEff_DataDOWN);
			effData2 = CBeff( pt2, Run2_TauTau_legTriggerEff_DataDOWN);

			effMC1 = CBeff( pt1, Run2_TauTau_legTriggerEff_McUP);
			effMC2 = CBeff( pt2, Run2_TauTau_legTriggerEff_McUP);

			if(effMC1!=0) SF1 = effData1/effMC1;
			if(effMC2!=0)  SF2 = effData2/effMC2;

			returnSF = SF1 * SF2;
		}

	/////////////////////////////////////
		return returnSF;
	}


	/* if reaches here then print a warning */
	std::cout<<"WARNING ---- Trigger x ID x ISO sf not available for CandidateEventType "<<R.getI("CandidateEventType")<<" using 1.0 \n";
	return returnSF;
}




