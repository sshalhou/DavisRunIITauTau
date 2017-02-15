
/* class generateH2TauSyncTree
generate the H2TauTau group's standard sync trees (one tree produced per channel)
see : https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorking2015#Synchronisation_Ntuple
-- Shalhout
*/


#ifndef Analysis_generateH2TauSyncTree_h
#define Analysis_generateH2TauSyncTree_h

////////////////////////////

#include <TROOT.h>
#include <TMath.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TBranch.h>
#include <TIterator.h>
#include <TObject.h>
#include <TClassRef.h>
#include <TObjArray.h>
#include <TBranchElement.h>
#include <TLorentzVector.h>
#include <vector>
#include <utility>
#include <iostream>
#include <TApplication.h>
#include <TLeaf.h>
#include <map>
#include <TString.h>
#include <assert.h>
#include "TGraphErrors.h"
#include "FlatTreeReader.h"
#include <math.h>
#include "HTT-utilities/LepEffInterface/interface/ScaleFactor.h"
#include "HTT-utilities/QCDModelingEMu/interface/QCDModelForEMu.h"
#include <TGraphAsymmErrors.h>
#include <TRandom3.h>

/* new struct to contain jet info under a give correction or systematic shift */

struct jetDescription 
{

  int m_njets;      
  int m_njetspt20;    

  double m_mjj;     // Only filled if njetspt20>=2 
  double m_jdeta;     // Only filled if njetspt20>=2 
  double m_njetingap;   // Only filled if njetspt20>=2 
  double m_njetingap20; // Only filled if njetspt20>=2 
  double m_jdphi;     // Only filled if njetspt20>=2 

  double m_jpt_1; // for leading jet in pt (pt > 20)
  double m_jeta_1;  // for leading jet in pt (pt > 20)
  double m_jphi_1;  // for leading jet in pt (pt > 20)
  double m_jm_1;  // for leading jet in pt (pt > 20)
  double m_jmva_1;  // for leading jet in pt (pt > 20)

  double m_jpt_2;   // for trailing jet in pt (pt > 20)
  double m_jeta_2;  // for trailing jet in pt (pt > 20)
  double m_jphi_2;  // for trailing jet in pt (pt > 20)
  double m_jm_2;  // for trailing jet in pt (pt > 20)
  double m_jmva_2;  // for trailing jet in pt (pt > 20)

  int m_nbtag;          // (medium WP central)
  int m_nbtag_oneSigmaUp; // (medium WP UP : one sigma + shift in btag sys)
  int m_nbtag_oneSigmaDown; // (medium WP DOWN : one sigma - shift in btag sys)

  double m_bpt_1; // for leading b-jet in pt (pt > 20) (medium WP central)
  double m_beta_1;  // for leading b-jet in pt (pt > 20) (medium WP central)
  double m_bphi_1;  // for leading b-jet in pt (pt > 20) (medium WP central)
  double m_bm_1;  // for leading b-jet in pt (pt > 20) (medium WP central)
  double m_bmva_1;  // for leading b-jet in pt (pt > 20) (medium WP central)
  float m_bcsv_1; // for leading b-jet in pt (pt > 20) (medium WP central)
  
  double m_bpt_2;   // for trailing b-jet in pt (pt > 20) (medium WP central)
  double m_beta_2;  // for trailing b-jet in pt (pt > 20) (medium WP central)
  double m_bphi_2;  // for trailing b-jet in pt (pt > 20) (medium WP central)
  double m_bm_2;  // for trailing b-jet in pt (pt > 20) (medium WP central)
  double m_bmva_2;  // for trailing b-jet in pt (pt > 20) (medium WP central)
  float m_bcsv_2; // for trailing b-jet in pt (pt > 20) (medium WP central)

  int m_nbtag_LooseWp;          // (loose WP central)
  int m_nbtag_LooseWp_oneSigmaUp; // (loose WP UP : one sigma + shift in btag sys)
  int m_nbtag_LooseWp_oneSigmaDown; // (loose WP DOWN : one sigma - shift in btag sys)

  double m_bpt_1_LooseWp; // for leading b-jet in pt (pt > 20) (loose WP central)
  double m_beta_1_LooseWp;  // for leading b-jet in pt (pt > 20) (loose WP central)
  double m_bphi_1_LooseWp;  // for leading b-jet in pt (pt > 20) (loose WP central)
  double m_bm_1_LooseWp;  // for leading b-jet in pt (pt > 20) (loose WP central)
  double m_bmva_1_LooseWp;  // for leading b-jet in pt (pt > 20) (loose WP central)
  float m_bcsv_1_LooseWp; // for leading b-jet in pt (pt > 20) (loose WP central)
  
  double m_bpt_2_LooseWp;   // for trailing b-jet in pt (pt > 20) (loose WP central)
  double m_beta_2_LooseWp;  // for trailing b-jet in pt (pt > 20) (loose WP central)
  double m_bphi_2_LooseWp;  // for trailing b-jet in pt (pt > 20) (loose WP central)
  double m_bm_2_LooseWp;  // for trailing b-jet in pt (pt > 20) (loose WP central)
  double m_bmva_2_LooseWp;  // for trailing b-jet in pt (pt > 20) (loose WP central)
  float m_bcsv_2_LooseWp; // for trailing b-jet in pt (pt > 20) (loose WP central)

  int m_nbtag_TightWp;      // (tight WP central)
  int m_nbtag_TightWp_oneSigmaUp; // (tight WP UP : one sigma + shift in btag sys)
  int m_nbtag_TightWp_oneSigmaDown; // (tight WP DOWN : one sigma - shift in btag sys)

  double m_bpt_1_TightWp; // for leading b-jet in pt (pt > 20) (tight WP central)
  double m_beta_1_TightWp;  // for leading b-jet in pt (pt > 20) (tight WP central)
  double m_bphi_1_TightWp;  // for leading b-jet in pt (pt > 20) (tight WP central)
  double m_bm_1_TightWp;  // for leading b-jet in pt (pt > 20) (tight WP central)
  double m_bmva_1_TightWp;  // for leading b-jet in pt (pt > 20) (tight WP central)
  float m_bcsv_1_TightWp; // for leading b-jet in pt (pt > 20) (tight WP central)
  
  double m_bpt_2_TightWp;   // for trailing b-jet in pt (pt > 20) (tight WP central)
  double m_beta_2_TightWp;  // for trailing b-jet in pt (pt > 20) (tight WP central)
  double m_bphi_2_TightWp;  // for trailing b-jet in pt (pt > 20) (tight WP central)
  double m_bm_2_TightWp;  // for trailing b-jet in pt (pt > 20) (tight WP central)
  double m_bmva_2_TightWp;  // for trailing b-jet in pt (pt > 20) (tight WP central)
  float m_bcsv_2_TightWp; // for trailing b-jet in pt (pt > 20) (tight WP central)

  /* init to reset values */
  void reset()
  {

	m_njets = -999;
	m_njetspt20 = -999;
	m_mjj = -999.0;
	m_jdeta = -999.0;
	m_njetingap = -999.0;
	m_njetingap20 = -999.0;
	m_jdphi = -999.0;
	m_jpt_1 = -999.0;
	m_jeta_1 = -999.0;
	m_jphi_1 = -999.0;
	m_jm_1 = -999.0;
	m_jmva_1 = -999.0;
	m_jpt_2 = -999.0;
	m_jeta_2 = -999.0;
	m_jphi_2 = -999.0;
	m_jm_2 = -999.0;
	m_jmva_2 = -999.0;
	m_nbtag = -999;
	m_nbtag_oneSigmaUp = -999;
	m_nbtag_oneSigmaDown = -999;
	m_bpt_1 = -999.0;
	m_beta_1 = -999.0;
	m_bphi_1 = -999.0;
	m_bm_1 = -999.0;
	m_bmva_1 = -999.0;
	m_bcsv_1 = -999.0;
	m_bpt_2 = -999.0;
	m_beta_2 = -999.0;
	m_bphi_2 = -999.0;
	m_bm_2 = -999.0;
	m_bmva_2 = -999.0;
	m_bcsv_2 = -999.0;
	m_nbtag_LooseWp = -999;
	m_nbtag_LooseWp_oneSigmaUp = -999;
	m_nbtag_LooseWp_oneSigmaDown = -999;
	m_bpt_1_LooseWp = -999.0;
	m_beta_1_LooseWp = -999.0;
	m_bphi_1_LooseWp = -999.0;
	m_bm_1_LooseWp = -999.0;
	m_bmva_1_LooseWp = -999.0;
	m_bcsv_1_LooseWp = -999.0;
	m_bpt_2_LooseWp = -999.0;
	m_beta_2_LooseWp = -999.0;
	m_bphi_2_LooseWp = -999.0;
	m_bm_2_LooseWp = -999.0;
	m_bmva_2_LooseWp = -999.0;
	m_bcsv_2_LooseWp = -999.0;
	m_nbtag_TightWp = -999;
	m_nbtag_TightWp_oneSigmaUp = -999;
	m_nbtag_TightWp_oneSigmaDown = -999;
	m_bpt_1_TightWp = -999.0;
	m_beta_1_TightWp = -999.0;
	m_bphi_1_TightWp = -999.0;
	m_bm_1_TightWp = -999.0;
	m_bmva_1_TightWp = -999.0;
	m_bcsv_1_TightWp = -999.0;
	m_bpt_2_TightWp = -999.0;
	m_beta_2_TightWp = -999.0;
	m_bphi_2_TightWp = -999.0;
	m_bm_2_TightWp = -999.0;
	m_bmva_2_TightWp = -999.0;
	m_bcsv_2_TightWp = -999.0;

  }

};


class generateH2TauSyncTree
{

public:
	generateH2TauSyncTree(FlatTreeReader, bool, std::string);
	virtual ~generateH2TauSyncTree();	
	void handleEvent();
	void finish();
	double pzetaVisCalc(TLorentzVector, TLorentzVector);
	double pzetaMissCalc(TLorentzVector, TLorentzVector, TLorentzVector);
	void reset(); /* reset values each event */
	double mtTotCalc(TLorentzVector, TLorentzVector, TLorentzVector);
	double GetTransverseMass(TLorentzVector, TLorentzVector);

	double computeLPT(bool); /* arg is a bool flag for verbose running */

	std::vector <double> computePchi_and_Mmin(bool, double, double); /* args are (bool flag for verbose running, met, metPhi) */

	/* GetLeg1Leg2McTriggerWeights args : leg1, leg2, CandidateEventType, -1,0,1 
	for down nominal up shifted-systematic */
	
	std::vector<double> GetLeg1Leg2McTriggerWeights(TLorentzVector,TLorentzVector,int,int); 

	/* jet info collector */

	jetDescription jetINFOstruct;

private:

	FlatTreeReader R;
	bool m_run; /* did we want to run this operation? */ 
	void setupBranches(TTree*);
		
	// counters
	int num_total;
	int num_et;
	int num_em;
	int num_tt;
	int num_mt;

	// for QCD weights for eleMu channel

	// with DZeta cut ->
	QCDModelForEMu * qcdWeights;//("HTT-utilities/QCDModelingEMu/data/QCD_weight_emu.root"); 

	// w/o DZeta cut ->
	QCDModelForEMu * qcdWeightsNoDZeta; //("HTT-utilities/QCDModelingEMu/data/QCD_weight_emu_nodzeta.root"); 

    // Muon POG central muon sf tool
    
    /* for Trigger runs bcdef */
    
    TFile * sfFile_Muon_Trigger_BCDEF = new TFile("EfficienciesAndSF_TRIG_BCDEF.root","READ");
    TH2F * sfHisto_Muon_Trigger_BCDEF = (TH2F*)sfFile_Muon_Trigger_BCDEF->Get("/IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
    
    /* for Trigger runs gh */
    
    TFile * sfFile_Muon_Trigger_GH = new TFile("EfficienciesAndSF_TRIG_GH.root","READ");
    TH2F * sfHisto_Muon_Trigger_GH = (TH2F*)sfFile_Muon_Trigger_GH->Get("/IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
    
    /* for mediumID2016 runs bcdef */
    
    TFile * sfFile_Muon_MediumID2016_BCDEF = new TFile("EfficienciesAndSF_ID_BCDEF.root","READ");
    TH2F * sfHisto_Muon_MediumID2016_BCDEF = (TH2F*)sfFile_Muon_MediumID2016_BCDEF->Get("/MC_NUM_MediumID2016_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
    
    /* for Iso runs bcdef */
    
    TFile * sfFile_Muon_TightIso_BCDEF = new TFile("EfficienciesAndSF_ISO_BCDEF.root","READ");
    TH2F * sfHisto_Muon_TightIso_BCDEF = (TH2F*)sfFile_Muon_TightIso_BCDEF->Get("/TightISO_MediumID_pt_eta/abseta_pt_ratio");
    
    /* for mediumID2016 runs gh */
    
    TFile * sfFile_Muon_MediumID2016_GH = new TFile("EfficienciesAndSF_ID_GH.root","READ");
    TH2F * sfHisto_Muon_MediumID2016_GH = (TH2F*)sfFile_Muon_MediumID2016_GH->Get("/MC_NUM_MediumID2016_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
    
    /* for Iso runs gh */
    
    TFile * sfFile_Muon_TightIso_GH = new TFile("EfficienciesAndSF_ISO_GH.root","READ");
    TH2F * sfHisto_Muon_TightIso_GH = (TH2F*)sfFile_Muon_TightIso_GH->Get("/TightISO_MediumID_pt_eta/abseta_pt_ratio");

	// for HTT derived lepton ID and trigger scale factors and efficiencies

	/* for muTau (muon leg) */

	ScaleFactor * sfTool_Muon_IdIso0p15_eff;
	ScaleFactor * sfTool_Muon_SingleMu_eff;

	/* for eleMu (muon leg) */

	ScaleFactor * sfTool_Muon_IdIso0p20_eff;

	// for electron lepton ID and trigger scale factors and efficiencies 

	/* for eleTau (electron leg) */

	ScaleFactor * sfTool_Electron_IdIso0p10_eff;
	ScaleFactor * sfTool_Electron_SingleEle_eff;

	/* for eleMu (electron leg) */

	ScaleFactor * sfTool_Electron_IdIso0p15_eff;

	/* for eleMu combined trigger efficiency */

	ScaleFactor * sfTool_Muon_Mu8_eff;
	ScaleFactor * sfTool_Muon_Mu17_eff;
	ScaleFactor * sfTool_Electron_Ele17_eff;
	ScaleFactor * sfTool_Electron_Ele12_eff;

	// needed for V reweight

    //new 2016
	TFile* zReweightFile = new TFile("zpt_weights_2016.root","READ");
	TH2D *zweightHist = (TH2D*) zReweightFile->Get("zptmass_histo");
    
    // k factors from monojet group
    TFile* kFactorsFile = new TFile("kfactors.root", "READ");
    TH1F* EWK_Zcorr = (TH1F*) kFactorsFile->Get("/EWKcorr/Z");
    TH1F* EWK_Gcorr = (TH1F*) kFactorsFile->Get("/EWKcorr/photon");
    TH1F* EWK_Wcorr = (TH1F*) kFactorsFile->Get("/EWKcorr/W");
    TH1F* LO_Zcorr = (TH1F*) kFactorsFile->Get("/ZJets_LO/inv_pt");
    TH1F* LO_Gcorr = (TH1F*) kFactorsFile->Get("/GJets_LO/inv_pt_G");
    TH1F* LO_Wcorr = (TH1F*) kFactorsFile->Get("/WJets_LO/inv_pt");

    //referenced for LPT
    TFile* inFile = new TFile("pDistPlots.root","READ");
    TH1F *eHistoFrac = (TH1F*)inFile->Get("/demo/eVisFrac");
    TH1F *muHistoFrac = (TH1F*)inFile->Get("/demo/muVisFrac");
    TH1F *h1p0sHistoFrac = (TH1F*)inFile->Get("/demo/h1p0sVisFrac");
    TH1F *h1p1sHistoFrac = (TH1F*)inFile->Get("/demo/h1p1sVisFrac");
    TH1F *h3p0sHistoFrac = (TH1F*)inFile->Get("/demo/h3p0sVisFrac");

    //////////////////////////////////////////////////////////////////////////////////
	// elements of the TTree
    // make sure any new additions are initialized in the reset() function!
    //////////////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////
  	// BEGIN LIST OF Ntuple BRANCH-ASSOCIATED VARIABLES //
    //////////////////////////////////////////////////////

    /* tMVA flag */
    
    // bool flag_MVAEventType; -- this will need to be added back in by Garrett later
    // also needs to be added to the .cc file 
    //using int for analysis, train, or test -> -1.0,1

    int flag_MVAEventType;

    /* theory event weights */
    
    float originalXWGTUP;
    std::vector < float > theory_scale_factors; /* scale factors for theory variants, mapping is available in FlatTuple production log file */

	/* davis specific */

	unsigned int pairRank; 
	int isOsPair; 
    double genBosonTotal_pt, genBosonTotal_eta, genBosonTotal_phi, genBosonTotal_M; 	    /* the gen total 4-vector of W/Z/H */
	double genBosonVisible_pt, genBosonVisible_eta, genBosonVisible_phi, genBosonVisible_M; /* the gen visible 4-vector of W/Z/H */
    double genTopPt1;
    double genTopPt2;

	/* event ID variables */

	unsigned int run;
	unsigned int event;
	unsigned int evt;		/* this is what H2Tau group uses instead of 'event' */
	unsigned int lumi;

	/* pile up */

	int npv;
	float npu;
	double rho;
	double puweight;

	///////////////////////////
	/* leg_1 */
	///////////////////////////

	double pt_1;
	double phi_1;
	double eta_1;
	double m_1;
	float  iso_1;
	float  dZ_1;	
	float  dzTauVertex_1;
	float  d0_1;   /* this is dxy in flatTuple */
	int    q_1;
	float  id_e_mva_nt_loose_1; /* non-triggering ele MVA score */
	int    tau_decay_mode_1;    /* replaces strips and hadrons for Run II */
    float ZimpactTau_1;



	double mt_1;			        /* using mva met */
	double pfmt_1; 
	double puppimt_1;
	double mt_uncorr_1;			    /* using mva met, no recoil corr */

	/* only valid if tau es and e es shifts are 0 */

    double responseUP_MTmvaMET_1;
    double responseDOWN_MTmvaMET_1;
    double resolutionUP_MTmvaMET_1;
    double resolutionDOWN_MTmvaMET_1;


	/* H2TauTau group's gen-match codes, 
	   see DavisRunIITauTau/FlatTupleGenerator/interface/GenMcMatchTypes.h */ 

	int    gen_match_1; 	    
	double genMCmatch_pt_1;
	double genMCmatch_eta_1;
	double genMCmatch_phi_1;
	double genMCmatch_M_1;
	int    MCMatchPdgId_1;

	/* tau IDs */

	float byIsolationMVArun2v1DBoldDMwLTraw_1;
	float byTightIsolationMVArun2v1DBoldDMwLT_1;
	float byVTightIsolationMVArun2v1DBoldDMwLT_1;
	float byLooseIsolationMVArun2v1DBoldDMwLT_1;
	float byMediumIsolationMVArun2v1DBoldDMwLT_1;
	float byVLooseIsolationMVArun2v1DBoldDMwLT_1;
	float byVVTightIsolationMVArun2v1DBoldDMwLT_1;
	float againstElectronVLooseMVA6_1;
	float againstMuonTight3_1;
	float againstElectronTightMVA6_1;
	float againstMuonLoose3_1;
	float decayModeFinding_1;
	float byIsolationMVA3oldDMwLTraw_1;
	float byCombinedIsolationDeltaBetaCorrRaw3Hits_1;
	float byIsolationMVArun2v1DBnewDMwLTraw_1;
	float decayModeFindingNewDMs_1;

	///////////////////////////
	/* leg_2 */
	///////////////////////////

	double pt_2;
	double phi_2;
	double eta_2;
	double m_2;
	float  iso_2;
	float  dZ_2;
	float dzTauVertex_2;
	float  d0_2; /* this is dxy in flatTuple */
	int    q_2;
	float  id_e_mva_nt_loose_2; /* non-triggering ele MVA score */
	int    tau_decay_mode_2;    /* replaces strips and hadrons for Run II */
    float ZimpactTau_2;


	double mt_2;			        /* using mva met */
	double pfmt_2; 
	double puppimt_2;
	double mt_uncorr_2;			    /* using mva met, no recoil corr */

	/* only valid if tau es and e es shifts are 0 */

    double responseUP_MTmvaMET_2;
    double responseDOWN_MTmvaMET_2;
    double resolutionUP_MTmvaMET_2;
    double resolutionDOWN_MTmvaMET_2;


	/* H2TauTau group's gen-match codes, 
	   see DavisRunIITauTau/FlatTupleGenerator/interface/GenMcMatchTypes.h */ 

	int    gen_match_2; 	    
	double genMCmatch_pt_2;
	double genMCmatch_eta_2;
	double genMCmatch_phi_2;
	double genMCmatch_M_2;
	int    MCMatchPdgId_2;

	/* tau IDs */

	float byIsolationMVArun2v1DBoldDMwLTraw_2;
	float byTightIsolationMVArun2v1DBoldDMwLT_2;
	float byVTightIsolationMVArun2v1DBoldDMwLT_2;
	float byLooseIsolationMVArun2v1DBoldDMwLT_2;
	float byMediumIsolationMVArun2v1DBoldDMwLT_2;
	float byVLooseIsolationMVArun2v1DBoldDMwLT_2;
	float byVVTightIsolationMVArun2v1DBoldDMwLT_2;
	float againstElectronVLooseMVA6_2;
	float againstMuonTight3_2;
	float againstElectronTightMVA6_2;
	float againstMuonLoose3_2;
	float decayModeFinding_2;
	float byIsolationMVA3oldDMwLTraw_2;
	float byCombinedIsolationDeltaBetaCorrRaw3Hits_2;
	float byIsolationMVArun2v1DBnewDMwLTraw_2;
	float decayModeFindingNewDMs_2;

	/* di-tau system */

	double pt_tt;
	double DeltaR_leg1_leg2;
	double mt_tot; /* use mva met */	
	double m_vis;

	/* sv fit -- only keeping variants which use mvaMET, study by H2Tau group showed met variants have minimal impact on SVMass shape
	and so those are omitted */

	double m_sv;
	double mt_sv;
	double SVFit_mvaMET_diTau_pt;
	double SVFit_mvaMET_diTau_eta;
	double SVFit_mvaMET_diTau_phi;
	double SVFit_mvaMET_FittedMET;
	double SVFit_mvaMET_FittedMETphi;

	/* met */

	double mvamet;
	double mvametphi;

	double met;       /* this is pf met */
	double metphi;

	double puppimet;
	double puppimetphi;

	double uncorr_mvamet;
	double uncorr_mvametphi;

	/* met systematics -- only valid when tau es and electron energy scale shifts are 0 */

	double responseUP_mvaMET;
    double responseUP_mvaMETphi;

    double responseDOWN_mvaMET;
    double responseDOWN_mvaMETphi;

    double resolutionUP_mvaMET;
    double resolutionUP_mvaMETphi;

    double resolutionDOWN_mvaMET;
    double resolutionDOWN_mvaMETphi;


    /* met cov matricies */

   	double mvacov00;     /* using mva met */
	double mvacov01;
	double mvacov10;
	double mvacov11;
	
	double metcov00;     /* using pf met */
	double metcov01;
	double metcov10;
	double metcov11;

	/* other mets*/

	double genMET;
	double genMETphi;
	double genMETeta;
	double genMETmass;

	/* pzeta variables */

	double pzetavis;	     /*  using mva met */	
	
	double pzetamiss;        /*  using mva met */
	double pfpzetamiss;      /*  use pf met */
	double puppipzetamiss;   /*  use puppi met */

	/* systematic variants on pzeta variables -- only valid when tau es and electron energy scale shifts are 0 */

    double pzetamiss_responseUP;
    double pzetamiss_responseDOWN;
    double pzetamiss_resolutionUP;
    double pzetamiss_resolutionDOWN;
    double pzetamiss_uncorr;

    /* PF MET as used by mono-H analysis */

	double pfmet_raw_Pt; 
	double pfmet_raw_Phi;
	double pfmet_raw_MT1;
	double pfmet_raw_MT2;

	double pfmet_type1_Pt;  /* this is the default PF MET type 1 corrected */
	double pfmet_type1_Phi;
	double pfmet_type1_MT1;
	double pfmet_type1_MT2;

	double pfmet_type1_JetResUp_Pt; 
	double pfmet_type1_JetResUp_Phi;
	double pfmet_type1_JetResUp_MT1;
	double pfmet_type1_JetResUp_MT2;

	double pfmet_type1_JetResDown_Pt; 
	double pfmet_type1_JetResDown_Phi;
	double pfmet_type1_JetResDown_MT1;
	double pfmet_type1_JetResDown_MT2;

	double pfmet_type1_JetEnUp_Pt; 
	double pfmet_type1_JetEnUp_Phi;
	double pfmet_type1_JetEnUp_MT1;
	double pfmet_type1_JetEnUp_MT2;

	double pfmet_type1_JetEnDown_Pt; 
	double pfmet_type1_JetEnDown_Phi;
	double pfmet_type1_JetEnDown_MT1;
	double pfmet_type1_JetEnDown_MT2;

	double pfmet_type1_MuonEnUp_Pt; 
	double pfmet_type1_MuonEnUp_Phi;
	double pfmet_type1_MuonEnUp_MT1;
	double pfmet_type1_MuonEnUp_MT2;

	double pfmet_type1_MuonEnDown_Pt; 
	double pfmet_type1_MuonEnDown_Phi;
	double pfmet_type1_MuonEnDown_MT1;
	double pfmet_type1_MuonEnDown_MT2;

	double pfmet_type1_ElectronEnUp_Pt; 
	double pfmet_type1_ElectronEnUp_Phi;
	double pfmet_type1_ElectronEnUp_MT1;
	double pfmet_type1_ElectronEnUp_MT2;

	double pfmet_type1_ElectronEnDown_Pt; 
	double pfmet_type1_ElectronEnDown_Phi;
	double pfmet_type1_ElectronEnDown_MT1;
	double pfmet_type1_ElectronEnDown_MT2;

	double pfmet_type1_TauEnUp_Pt; 
	double pfmet_type1_TauEnUp_Phi;
	double pfmet_type1_TauEnUp_MT1;
	double pfmet_type1_TauEnUp_MT2;

	double pfmet_type1_TauEnDown_Pt; 
	double pfmet_type1_TauEnDown_Phi;
	double pfmet_type1_TauEnDown_MT1;
	double pfmet_type1_TauEnDown_MT2;

	double pfmet_type1_UnclusteredEnUp_Pt; 
	double pfmet_type1_UnclusteredEnUp_Phi;
	double pfmet_type1_UnclusteredEnUp_MT1;
	double pfmet_type1_UnclusteredEnUp_MT2;

	double pfmet_type1_UnclusteredEnDown_Pt; 
	double pfmet_type1_UnclusteredEnDown_Phi;
	double pfmet_type1_UnclusteredEnDown_MT1;
	double pfmet_type1_UnclusteredEnDown_MT2;

	double pfmet_type1_PhotonEnUp_Pt; 
	double pfmet_type1_PhotonEnUp_Phi;
	double pfmet_type1_PhotonEnUp_MT1;
	double pfmet_type1_PhotonEnUp_MT2;

	double pfmet_type1_PhotonEnDown_Pt; 
	double pfmet_type1_PhotonEnDown_Phi;
	double pfmet_type1_PhotonEnDown_MT1;
	double pfmet_type1_PhotonEnDown_MT2;


	/* JET system */
    /* this is a bit complicated :
	
	-- we have nominal jets with no _suffix which have the nominal JEC and JER applied 
	-- next, for nominal jets we have btagging performed under medium, loose, and tight wp, along with 
	   the b-tag systematic shifted variants
	-- next we have JEC and JER shifted jets, along with btagging performed under medium, loose, and tight wp

	*/


	///////////////////////////////////////////////////
	// NOMINAL JETS 								 //
	///////////////////////////////////////////////////

	int njets;			// nominal JEC and JER
	int njetspt20;		// nominal JEC and JER

	double mjj; 		// Only filled if njetspt20>=2 
	double jdeta;   	// Only filled if njetspt20>=2 
	double njetingap; 	// Only filled if njetspt20>=2 
	double njetingap20; // Only filled if njetspt20>=2 
	double jdphi; 		// Only filled if njetspt20>=2 

	double jpt_1;	// for leading jet in pt (pt > 20)
	double jeta_1;	// for leading jet in pt (pt > 20)
	double jphi_1;	// for leading jet in pt (pt > 20)
	double jm_1;	// for leading jet in pt (pt > 20)
	double jmva_1;	// for leading jet in pt (pt > 20)

	double jpt_2; 	// for trailing jet in pt (pt > 20)
	double jeta_2;	// for trailing jet in pt (pt > 20)
	double jphi_2;	// for trailing jet in pt (pt > 20)
	double jm_2;	// for trailing jet in pt (pt > 20)
	double jmva_2;	// for trailing jet in pt (pt > 20)


	///////////////////////////////////////////////////////	
	// NOMINAL JETS + Nominal btags  (medium WP central) //
	///////////////////////////////////////////////////////

	int nbtag;	    		// (medium WP central)
	int nbtag_oneSigmaUp;	// (medium WP UP : one sigma + shift in btag sys)
	int nbtag_oneSigmaDown;	// (medium WP DOWN : one sigma - shift in btag sys)

	double bpt_1;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double beta_1;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bphi_1;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bm_1;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bmva_1;	// for leading b-jet in pt (pt > 20) (medium WP central)
	float bcsv_1;	// for leading b-jet in pt (pt > 20) (medium WP central)
	
	double bpt_2; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double beta_2; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bphi_2; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bm_2; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bmva_2; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	float bcsv_2;	// for trailing b-jet in pt (pt > 20) (medium WP central)

	///////////////////////////////////////////////////////////	
	// NOMINAL JETS + Alternate WP btags  (loose WP central) //
	///////////////////////////////////////////////////////////

	int nbtag_LooseWp;	   			// (loose WP central)
	int nbtag_LooseWp_oneSigmaUp;	// (loose WP UP : one sigma + shift in btag sys)
	int nbtag_LooseWp_oneSigmaDown;	// (loose WP DOWN : one sigma - shift in btag sys)

	double bpt_1_LooseWp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double beta_1_LooseWp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bphi_1_LooseWp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bm_1_LooseWp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bmva_1_LooseWp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	float bcsv_1_LooseWp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	
	double bpt_2_LooseWp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double beta_2_LooseWp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bphi_2_LooseWp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bm_2_LooseWp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bmva_2_LooseWp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	float bcsv_2_LooseWp;	// for trailing b-jet in pt (pt > 20) (loose WP central)

	///////////////////////////////////////////////////////////////
	/* new (with 8_0_25 ) b-tag overall event weights for mono-H */
	///////////////////////////////////////////////////////////////

	double BtagEventSFproduct_looseWpDown;
	double BtagEventSFproduct_looseWpCentral;
	double BtagEventSFproduct_looseWpUp;
	double BtagEventSFproduct_mediumWpDown;
	double BtagEventSFproduct_mediumWpCentral;
	double BtagEventSFproduct_mediumWpUp;
	double BtagEventSFproduct_tightWpDown;
	double BtagEventSFproduct_tightWpCentral;
	double BtagEventSFproduct_tightWpUp;

	/* for non-nominal jets only keep the central values */
	double BtagEventSFproduct_looseWpCentral_JECshiftedUp;
	double BtagEventSFproduct_mediumWpCentral_JECshiftedUp;
	double BtagEventSFproduct_tightWpCentral_JECshiftedUp;

	double BtagEventSFproduct_looseWpCentral_JECshiftedDown;
	double BtagEventSFproduct_mediumWpCentral_JECshiftedDown;
	double BtagEventSFproduct_tightWpCentral_JECshiftedDown;

	double BtagEventSFproduct_looseWpCentral_JERup;
	double BtagEventSFproduct_mediumWpCentral_JERup;
	double BtagEventSFproduct_tightWpCentral_JERup;

	double BtagEventSFproduct_looseWpCentral_JERdown;
	double BtagEventSFproduct_mediumWpCentral_JERdown;
	double BtagEventSFproduct_tightWpCentral_JERdown;



	////////////////////////////////////////////////////////////	
	// NOMINAL JETS + Alternate WP btags  (tight WP central) //
	///////////////////////////////////////////////////////

	int nbtag_TightWp;	    // (tight WP central)
	int nbtag_TightWp_oneSigmaUp;	// (tight WP UP : one sigma + shift in btag sys)
	int nbtag_TightWp_oneSigmaDown;	// (tight WP DOWN : one sigma - shift in btag sys)

	double bpt_1_TightWp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double beta_1_TightWp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bphi_1_TightWp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bm_1_TightWp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bmva_1_TightWp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	float bcsv_1_TightWp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	
	double bpt_2_TightWp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double beta_2_TightWp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bphi_2_TightWp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bm_2_TightWp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bmva_2_TightWp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	float bcsv_2_TightWp;	// for trailing b-jet in pt (pt > 20) (tight WP central)




	///////////////////////////////////////////////////
	// JECshiftedUp JETS 								 //
	///////////////////////////////////////////////////

	int njets_JECshiftedUp;			// up JEC 
	int njetspt20_JECshiftedUp;		// up JEC 

	double mjj_JECshiftedUp; 		// Only filled if njetspt20>=2 
	double jdeta_JECshiftedUp;   	// Only filled if njetspt20>=2 
	double njetingap_JECshiftedUp; 	// Only filled if njetspt20>=2 
	double njetingap20_JECshiftedUp; // Only filled if njetspt20>=2 
	double jdphi_JECshiftedUp; 		// Only filled if njetspt20>=2 

	double jpt_1_JECshiftedUp;	// for leading jet in pt (pt > 20)
	double jeta_1_JECshiftedUp;	// for leading jet in pt (pt > 20)
	double jphi_1_JECshiftedUp;	// for leading jet in pt (pt > 20)
	double jm_1_JECshiftedUp;	// for leading jet in pt (pt > 20)
	double jmva_1_JECshiftedUp;	// for leading jet in pt (pt > 20)

	double jpt_2_JECshiftedUp; 	// for trailing jet in pt (pt > 20)
	double jeta_2_JECshiftedUp;	// for trailing jet in pt (pt > 20)
	double jphi_2_JECshiftedUp;	// for trailing jet in pt (pt > 20)
	double jm_2_JECshiftedUp;	// for trailing jet in pt (pt > 20)
	double jmva_2_JECshiftedUp;	// for trailing jet in pt (pt > 20)


	///////////////////////////////////////////////////////	
	// JECshiftedUp JETS + Nominal btags  (medium WP central) //
	///////////////////////////////////////////////////////

	int nbtag_JECshiftedUp;	    		// (medium WP central)

	double bpt_1_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double beta_1_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bphi_1_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bm_1_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bmva_1_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (medium WP central)
	float bcsv_1_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (medium WP central)
	
	double bpt_2_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double beta_2_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bphi_2_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bm_2_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bmva_2_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	float bcsv_2_JECshiftedUp;	// for trailing b-jet in pt (pt > 20) (medium WP central)

	///////////////////////////////////////////////////////////	
	// JECshiftedUp JETS + Alternate WP btags  (loose WP central) //
	///////////////////////////////////////////////////////////

	int nbtag_LooseWp_JECshiftedUp;	   			// (loose WP central)

	double bpt_1_LooseWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double beta_1_LooseWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bphi_1_LooseWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bm_1_LooseWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bmva_1_LooseWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	float bcsv_1_LooseWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (loose WP central)
	
	double bpt_2_LooseWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double beta_2_LooseWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bphi_2_LooseWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bm_2_LooseWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bmva_2_LooseWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	float bcsv_2_LooseWp_JECshiftedUp;	// for trailing b-jet in pt (pt > 20) (loose WP central)


	////////////////////////////////////////////////////////////	
	// JECshiftedUp JETS + Alternate WP btags  (tight WP central) //
	///////////////////////////////////////////////////////

	int nbtag_TightWp_JECshiftedUp;	    // (tight WP central)

	double bpt_1_TightWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double beta_1_TightWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bphi_1_TightWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bm_1_TightWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bmva_1_TightWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	float bcsv_1_TightWp_JECshiftedUp;	// for leading b-jet in pt (pt > 20) (tight WP central)
	
	double bpt_2_TightWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double beta_2_TightWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bphi_2_TightWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bm_2_TightWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bmva_2_TightWp_JECshiftedUp; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	float bcsv_2_TightWp_JECshiftedUp;	// for trailing b-jet in pt (pt > 20) (tight WP central)


	///////////////////////////////////////////////////
	// JECshiftedDown JETS 								 //
	///////////////////////////////////////////////////

	int njets_JECshiftedDown;			// down JEC
	int njetspt20_JECshiftedDown;		// down JEC

	double mjj_JECshiftedDown; 		// Only filled if njetspt20>=2 
	double jdeta_JECshiftedDown;   	// Only filled if njetspt20>=2 
	double njetingap_JECshiftedDown; 	// Only filled if njetspt20>=2 
	double njetingap20_JECshiftedDown; // Only filled if njetspt20>=2 
	double jdphi_JECshiftedDown; 		// Only filled if njetspt20>=2 

	double jpt_1_JECshiftedDown;	// for leading jet in pt (pt > 20)
	double jeta_1_JECshiftedDown;	// for leading jet in pt (pt > 20)
	double jphi_1_JECshiftedDown;	// for leading jet in pt (pt > 20)
	double jm_1_JECshiftedDown;	// for leading jet in pt (pt > 20)
	double jmva_1_JECshiftedDown;	// for leading jet in pt (pt > 20)

	double jpt_2_JECshiftedDown; 	// for trailing jet in pt (pt > 20)
	double jeta_2_JECshiftedDown;	// for trailing jet in pt (pt > 20)
	double jphi_2_JECshiftedDown;	// for trailing jet in pt (pt > 20)
	double jm_2_JECshiftedDown;	// for trailing jet in pt (pt > 20)
	double jmva_2_JECshiftedDown;	// for trailing jet in pt (pt > 20)


	///////////////////////////////////////////////////////	
	// JECshiftedDown JETS + Nominal btags  (medium WP central) //
	///////////////////////////////////////////////////////

	int nbtag_JECshiftedDown;	    		// (medium WP central)

	double bpt_1_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double beta_1_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bphi_1_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bm_1_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bmva_1_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	float bcsv_1_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	
	double bpt_2_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double beta_2_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bphi_2_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bm_2_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bmva_2_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	float bcsv_2_JECshiftedDown;	// for trailing b-jet in pt (pt > 20) (medium WP central)

	///////////////////////////////////////////////////////////	
	// JECshiftedDown JETS + Alternate WP btags  (loose WP central) //
	///////////////////////////////////////////////////////////

	int nbtag_LooseWp_JECshiftedDown;	   			// (loose WP central)

	double bpt_1_LooseWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double beta_1_LooseWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bphi_1_LooseWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bm_1_LooseWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bmva_1_LooseWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	float bcsv_1_LooseWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	
	double bpt_2_LooseWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double beta_2_LooseWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bphi_2_LooseWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bm_2_LooseWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bmva_2_LooseWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	float bcsv_2_LooseWp_JECshiftedDown;	// for trailing b-jet in pt (pt > 20) (loose WP central)


	////////////////////////////////////////////////////////////	
	// JECshiftedDown JETS + Alternate WP btags  (tight WP central) //
	///////////////////////////////////////////////////////

	int nbtag_TightWp_JECshiftedDown;	    // (tight WP central)

	double bpt_1_TightWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double beta_1_TightWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bphi_1_TightWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bm_1_TightWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bmva_1_TightWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	float bcsv_1_TightWp_JECshiftedDown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	
	double bpt_2_TightWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double beta_2_TightWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bphi_2_TightWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bm_2_TightWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bmva_2_TightWp_JECshiftedDown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	float bcsv_2_TightWp_JECshiftedDown;	// for trailing b-jet in pt (pt > 20) (tight WP central)



	///////////////////////////////////////////////////
	// JERshiftedUp JETS 								 //
	///////////////////////////////////////////////////

	int njets_JERup;			// up JER
	int njetspt20_JERup;		// up JER

	double mjj_JERup; 		// Only filled if njetspt20>=2 
	double jdeta_JERup;   	// Only filled if njetspt20>=2 
	double njetingap_JERup; 	// Only filled if njetspt20>=2 
	double njetingap20_JERup; // Only filled if njetspt20>=2 
	double jdphi_JERup; 		// Only filled if njetspt20>=2 

	double jpt_1_JERup;	// for leading jet in pt (pt > 20)
	double jeta_1_JERup;	// for leading jet in pt (pt > 20)
	double jphi_1_JERup;	// for leading jet in pt (pt > 20)
	double jm_1_JERup;	// for leading jet in pt (pt > 20)
	double jmva_1_JERup;	// for leading jet in pt (pt > 20)

	double jpt_2_JERup; 	// for trailing jet in pt (pt > 20)
	double jeta_2_JERup;	// for trailing jet in pt (pt > 20)
	double jphi_2_JERup;	// for trailing jet in pt (pt > 20)
	double jm_2_JERup;	// for trailing jet in pt (pt > 20)
	double jmva_2_JERup;	// for trailing jet in pt (pt > 20)


	///////////////////////////////////////////////////////	
	// JERshiftedUp JETS + Nominal btags  (medium WP central) //
	///////////////////////////////////////////////////////

	int nbtag_JERup;	    		// (medium WP central)

	double bpt_1_JERup;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double beta_1_JERup;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bphi_1_JERup;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bm_1_JERup;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bmva_1_JERup;	// for leading b-jet in pt (pt > 20) (medium WP central)
	float bcsv_1_JERup;	// for leading b-jet in pt (pt > 20) (medium WP central)
	
	double bpt_2_JERup; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double beta_2_JERup; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bphi_2_JERup; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bm_2_JERup; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bmva_2_JERup; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	float bcsv_2_JERup;	// for trailing b-jet in pt (pt > 20) (medium WP central)

	///////////////////////////////////////////////////////////	
	// JERshiftedUp JETS + Alternate WP btags  (loose WP central) //
	///////////////////////////////////////////////////////////

	int nbtag_LooseWp_JERup;	   			// (loose WP central)

	double bpt_1_LooseWp_JERup;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double beta_1_LooseWp_JERup;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bphi_1_LooseWp_JERup;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bm_1_LooseWp_JERup;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bmva_1_LooseWp_JERup;	// for leading b-jet in pt (pt > 20) (loose WP central)
	float bcsv_1_LooseWp_JERup;	// for leading b-jet in pt (pt > 20) (loose WP central)
	
	double bpt_2_LooseWp_JERup; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double beta_2_LooseWp_JERup; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bphi_2_LooseWp_JERup; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bm_2_LooseWp_JERup; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bmva_2_LooseWp_JERup; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	float bcsv_2_LooseWp_JERup;	// for trailing b-jet in pt (pt > 20) (loose WP central)


	////////////////////////////////////////////////////////////	
	// JERshiftedUp JETS + Alternate WP btags  (tight WP central) //
	///////////////////////////////////////////////////////

	int nbtag_TightWp_JERup;	    // (tight WP central)

	double bpt_1_TightWp_JERup;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double beta_1_TightWp_JERup;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bphi_1_TightWp_JERup;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bm_1_TightWp_JERup;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bmva_1_TightWp_JERup;	// for leading b-jet in pt (pt > 20) (tight WP central)
	float bcsv_1_TightWp_JERup;	// for leading b-jet in pt (pt > 20) (tight WP central)
	
	double bpt_2_TightWp_JERup; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double beta_2_TightWp_JERup; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bphi_2_TightWp_JERup; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bm_2_TightWp_JERup; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bmva_2_TightWp_JERup; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	float bcsv_2_TightWp_JERup;	// for trailing b-jet in pt (pt > 20) (tight WP central)


	///////////////////////////////////////////////////
	// JERshiftedDown JETS 								 //
	///////////////////////////////////////////////////

	int njets_JERdown;			// down JER 
	int njetspt20_JERdown;		// down JER 

	double mjj_JERdown; 		// Only filled if njetspt20>=2 
	double jdeta_JERdown;   	// Only filled if njetspt20>=2 
	double njetingap_JERdown; 	// Only filled if njetspt20>=2 
	double njetingap20_JERdown; // Only filled if njetspt20>=2 
	double jdphi_JERdown; 		// Only filled if njetspt20>=2 

	double jpt_1_JERdown;	// for leading jet in pt (pt > 20)
	double jeta_1_JERdown;	// for leading jet in pt (pt > 20)
	double jphi_1_JERdown;	// for leading jet in pt (pt > 20)
	double jm_1_JERdown;	// for leading jet in pt (pt > 20)
	double jmva_1_JERdown;	// for leading jet in pt (pt > 20)

	double jpt_2_JERdown; 	// for trailing jet in pt (pt > 20)
	double jeta_2_JERdown;	// for trailing jet in pt (pt > 20)
	double jphi_2_JERdown;	// for trailing jet in pt (pt > 20)
	double jm_2_JERdown;	// for trailing jet in pt (pt > 20)
	double jmva_2_JERdown;	// for trailing jet in pt (pt > 20)


	///////////////////////////////////////////////////////	
	// JERshiftedDown JETS + Nominal btags  (medium WP central) //
	///////////////////////////////////////////////////////

	int nbtag_JERdown;	    		// (medium WP central)

	double bpt_1_JERdown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double beta_1_JERdown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bphi_1_JERdown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bm_1_JERdown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	double bmva_1_JERdown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	float bcsv_1_JERdown;	// for leading b-jet in pt (pt > 20) (medium WP central)
	
	double bpt_2_JERdown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double beta_2_JERdown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bphi_2_JERdown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bm_2_JERdown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	double bmva_2_JERdown; 	// for trailing b-jet in pt (pt > 20) (medium WP central)
	float bcsv_2_JERdown;	// for trailing b-jet in pt (pt > 20) (medium WP central)

	///////////////////////////////////////////////////////////	
	// JERshiftedDown JETS + Alternate WP btags  (loose WP central) //
	///////////////////////////////////////////////////////////

	int nbtag_LooseWp_JERdown;	   			// (loose WP central)

	double bpt_1_LooseWp_JERdown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double beta_1_LooseWp_JERdown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bphi_1_LooseWp_JERdown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bm_1_LooseWp_JERdown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	double bmva_1_LooseWp_JERdown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	float bcsv_1_LooseWp_JERdown;	// for leading b-jet in pt (pt > 20) (loose WP central)
	
	double bpt_2_LooseWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double beta_2_LooseWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bphi_2_LooseWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bm_2_LooseWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	double bmva_2_LooseWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (loose WP central)
	float bcsv_2_LooseWp_JERdown;	// for trailing b-jet in pt (pt > 20) (loose WP central)


	////////////////////////////////////////////////////////////	
	// JERshiftedDown JETS + Alternate WP btags  (tight WP central) //
	///////////////////////////////////////////////////////

	int nbtag_TightWp_JERdown;	    // (tight WP central)

	double bpt_1_TightWp_JERdown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double beta_1_TightWp_JERdown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bphi_1_TightWp_JERdown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bm_1_TightWp_JERdown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	double bmva_1_TightWp_JERdown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	float bcsv_1_TightWp_JERdown;	// for leading b-jet in pt (pt > 20) (tight WP central)
	
	double bpt_2_TightWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double beta_2_TightWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bphi_2_TightWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bm_2_TightWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	double bmva_2_TightWp_JERdown; 	// for trailing b-jet in pt (pt > 20) (tight WP central)
	float bcsv_2_TightWp_JERdown;	// for trailing b-jet in pt (pt > 20) (tight WP central)
    
    //used in calculation
    
    double visFrac1;
    double visFrac1Prob;
    double visFrac2;
    double visFrac2Prob;
    double currentFracProb;
    double bestFracProb;
    double bestP;
    
    double ME_T;
    double ME_T_phi;
    double p_lt;
    double eta_l;
    double phi_l;
    double p_Taut;
    double eta_Tau;
    double phi_Tau;
    double M_l;

    double p_lx;
    double p_ly;
    double p_lz;
    double E_l;

    double p_vx;
    double p_vy;
    double E_v;

	// extra vetoes

	float dilepton_veto; 	
	float extraelec_veto; 	
	float extramuon_veto;

	// met filters needed for mono-H search

	bool HBHENoiseFilter;
	bool HBHENoiseIsoFilter;
	bool CSCTightHalo2015Filter;
	bool EcalDeadCellTriggerPrimitiveFilter;
	bool goodVerticesFilter;
	bool eeBadScFilter;
	bool chargedHadronTrackResolutionFilter;
	bool muonBadTrackFilter;
	bool globalTightHalo2016Filter;

	bool BadChargedCandidateFilter;
	bool BadPFMuonFilter;

	// bad and duplicate muon filters -- event is OK if these are 0

	bool BadMuonTaggedMoriond17;
	bool DuplicateMuonTaggedMoriond17;


	/* gen info */

	int NUP;
	double weight; /* global event weight (MC xSection and num events excluded) ? */
	double generatorEventWeight;
	double lheHT;
	int lheOutGoingPartons;
	double lheZmass;


	/* DY classification */

	int IsZTT;
    int IsZL;
    int IsZJ;
    int IsZLL;
    
    /* TT classification */
    
    bool IsTTT;

	// information related to sample and weights

	std::string DataSet; 	/* the dataset */
    int EventTotal; 		/* the number of events in the MC sample */ 
    std::string EventType;  /* description of the event, DATA, MC, EMBEDDED, etc. */
    std::string KeyName;    /* description of the sample as given during crab job */
	std::string DataCard; 	/* the DataCard type for the current sample */
    double CrossSection;    /* MC process cross section */
    double FilterEff;       /* gen level filter eff. (needed if any is applied) */
	bool isSmallTree;       /* was the FlatTuple produced under small tree conditions */


	// information related to systematic shifts on tau and ele energy scales

	float TauEsNumberSigmasShifted;			/* number of sigmas shifted -1, 0, 1 */
	float ElectronEsNumberSigmasShifted;	/* number of sigmas shifted -1, 0, 1 */


	/* extra lepton info is needed to allow for VH channel in SM Higgs search */

	std::vector<int> veto_leptonType; 			/* vector containing flavor code */
	std::vector<double> veto_pt; 				/* vectors of 4-vector components */
	std::vector<double> veto_eta; 
	std::vector<double> veto_phi;
	std::vector<double> veto_M; 
	std::vector<int> veto_charge; 
	std::vector<float> veto_dxy;  /* lepton dxy see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */
	std::vector<float> veto_dz;	  /* lepton dz see CustomPatCollectionProducers/src/{Electron,Muon,Tau}Clones.cc */
	std::vector<float> veto_RelIso;
	std::vector<float> veto_passesLooseMuonId;
	std::vector<float> veto_passesMediumMuonId;
	std::vector<float> veto_passesMediumMuonId_ICHEP16;
	std::vector<float> veto_passesMediumMuonId;
	std::vector<float> veto_passesTightMuonId;
	std::vector<float> veto_passElectronMVA80;
	std::vector<float> veto_passElectronMVA90;
	std::vector<float> veto_passElectronCutBased;
	std::vector<float> veto_isTrackerGlobalPFMuon;
	std::vector<float> veto_numberOfMissingInnerHits;
	std::vector<float> veto_numberOfMissingOuterHits;
	std::vector<float> veto_passConversionVeto;

	/* NOTE: these flags are 1 if the *lepton* passes the cuts associated with a veto
	they do not indicate whether or not the event passes the veto itself */

	std::vector<int> veto_LeptonPassesThirdElectronVetoCuts; 			
	std::vector<int> veto_LeptonPassesThirdMuonVetoCuts; 			
	std::vector<int> veto_LeptonPassesDiElectronVetoCuts; 	
	std::vector<int> veto_LeptonPassesDiMuonVetoCuts; 			
		
    
    //MVA variables /* need to expand to use all variants */
    
    double LPT;
    double P_chi; 		/* using mvaMET */
    double M_min;		/* using mvaMET */

    double P_chi_pf; 	/* using pfMET */
    double M_min_pf;	/* using pfMET */
    
    double P_chi_puppi; /* using puppiMET */
    double M_min_puppi;	/* using puppiMET */
    

    double P_chi_uncorr; 		/* using uncorrected mvaMET */
    double M_min_uncorr;		/* using uncorrected mvaMET */


    double P_chi_responseUP; 		/* using responseUP mvaMET */
    double M_min_responseUP;		/* using responseUP mvaMET */


    double P_chi_responseDOWN; 		/* using responseDOWN mvaMET */
    double M_min_responseDOWN;		/* using responseDOWN mvaMET */


    double P_chi_resolutionUP; 		/* using resolutionUP mvaMET */
    double M_min_resolutionUP;		/* using resolutionUP mvaMET */


    double P_chi_resolutionDOWN; 		/* using resolutionDOWN mvaMET */
    double M_min_resolutionDOWN;		/* using resolutionDOWN mvaMET */


    /////////////////////////
    // event weights       //
    /////////////////////////

    double final_weight; /* final event weight under nominal systematics */

    double nominalCrossSection_Weight; /* indluded in final_weight */
    double puWeight_Weight;			   /* indluded in final_weight */	
    double TopQuarkPtWeight_Weight;    /* indluded in final_weight */
    double ZReWeight_Weight;           /* indluded in final_weight */
    double ZReWeight_WeightUp;
    double ZReWeight_WeightDown;
    double KReWeight_Weight;           /* indluded in final_weight */
    double KReWeight_WeightUp;
    double KReWeight_WeightDown;
    double JTF_WeightUp;
    double JTF_WeightDown;
    double NLOReWeight_Weight;         /* indluded in final_weight */
    double ScaleFactorsForPair_Weight; /* NOMINAL VERSION indluded in final_weight */
    
    double ScaleFactorsForPair_WeightUp;
    double ScaleFactorsForPair_WeightDown;
    double QCDWeightForEleMuChannel_Weight;
    double QCDWeightForEleMuChannel_WeightUp;
    double QCDWeightForEleMuChannel_WeightDown;
    double QCDWeightForEleMuChannelNoPZetaCut_Weight;
    double QCDWeightForEleMuChannelNoPZetaCut_WeightUp;
    double QCDWeightForEleMuChannelNoPZetaCut_WeightDown;
    double highPtTauEff_WeightUp;
    double highPtTauEff_WeightDown;


    ///////////////
    // 2016 Triggers -- these need to be kept
    // current with triggerSummaryChecks_ in FlatTupleConfig_cfi.py

    double leg1_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg;
	double leg1_HLT_Ele25_eta2p1_WPTight_Gsf;
	double leg1_HLT_IsoMu22;
	double leg1_HLT_IsoTkMu22;
	double leg1_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
	double leg1_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
	double leg2_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg;
	double leg2_HLT_Ele25_eta2p1_WPTight_Gsf;
	double leg2_HLT_IsoMu22;
	double leg2_HLT_IsoTkMu22;
	double leg2_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
	double leg2_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;


  	////////////////////////////////////////////////////
  	// END LIST OF Ntuple BRANCH-ASSOCIATED VARIABLES //
    ////////////////////////////////////////////////////
  


	// member pointers to TTrees & TFiles 
	
	TFile * outFile_MuTau;
	TFile * outFile_EleTau;
	TFile * outFile_TauTau;
	TFile * outFile_EleMu;

	TTree * tree_MuTau;
	TTree * tree_EleTau;
	TTree * tree_TauTau;
	TTree * tree_EleMu;

	////////////////////////////////
	// jet & b-tag counter function

	void fillJetBranches(bool, bool, std::string, jetDescription&);


	//////////////////////////////
	// event weight handler 	//
	//////////////////////////////


	/* function: getFinalWeight
		-- return the standard weight used when filling histograms 
		-- product of :
			getNominalWeight() 
			R.getD("puWeight") 			(included only if not real data)
			getTopQuarkPtWeight() 		(1.0 if not ttbar)
			getZReWeight()      		(1.0 if not DY (excluding low mass sample))
				
	*/
	
	double getFinalWeight(bool); 


	/* function: getNominalWeight 
			-- nomial weight = (1000 * cross-section) / (crab_job_eff * EventTotal * FilterEff) in pb
			-- valid for all samples except data, W+jets, DY+jets, (returns to 1.0, for data)
			-- for DY and W+jets returns stiching weights
			-- for SUSY Higgs & mono-Higgs the cross-sections are set to 1.0 			
	*/

	double getNominalWeight(bool);          


	/* function: getTopQuarkPtWeight 
			-- returns  top_wt = sqrt(exp(0.156-0.00137*top_1_pt)*exp(0.156-0.00137*top_2_pt)) (with top_x_pt capped at 400)
			   for ttbar samples
			-- returns 1.0 for all other samples
	*/

	double getTopQuarkPtWeight(bool);          



	/* function: getZReWeight 
			-- returns  hist->GetBinContent(hist->GetXaxis()->FindBin(genMass),hist->GetYaxis()->FindBin(genpT))
			   for all DY samples (except low mass) from the TFile zReweightFile
			-- returns 1.0 for all other samples
	*/

	double getZReWeight(bool);          


	/* function: getNLOReWeight 
			-- returns  NLO Higgs Pt based reweight for SUSY signal samples			   
			-- returns 1.0 for all other samples
			-- args are verbose flag, and the (integer) value of tan beta used in the original MC (10 by default)
	*/

	double getNLOReWeight(bool, int);          

	/* function: getHighPtTauUncertainty(bool)
			-- returns  vector with element [0] = 1 + 0.2 * (gen_tauPt)/1000.0 and element [1] = 1 - 0.2 * (gen_tauPt)/1000.0
			-- for events with 2 hadronically decaying taus, uses the formula eff(leg1) + eff(leg2) - eff(leg1)*eff(leg2)
	*/

	std::vector<double> getHighPtTauUncertainty(bool);
    
	/* function getCentralMuonFactor :
		return a POG central SF for ID, ISO, and triggers for muon
		args are : 
                pt = pt of muon
				eta = abs(eta) of muon
                bool = do tri

	*/
	double getCentralMuonFactor(Double_t, Double_t, bool);
    
	/* function getKFactor :
		return a k factor for reweighting DY, W:
                bool = verbose option

	*/
	double getKFactor(bool);
    
	/* function getJetTauFakeFactor:
		return a factor for reweighting W,ZJ:
                bool = verbose option
                int = variant, 1 up, -1 down

	*/
	double getJetTauFakeFactor(bool, int);
    
	/* function getFinalScaleFactorsForPair : 
		return a combinded final SF for trigger, ID, and ISO for both legs of a piar
		args are : 
				bool  = verbose option
				int   = shift :  only used in tau+tau case, 0 returns nominal, +1 returns 1 sigma up shift, -1 returns down shifted sf 

	*/

	double getFinalScaleFactorsForPair(bool, int, bool);

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

	std::vector<double> getQCDWeightForEleMuChannel(bool);


	////////////////////////////////
	// scale factor helper functions
	void initScaleFactorParametersRunII();


	/////////////////////////////////
	// scale factor parameters

	// Run II efficiencies for HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg

    std::array <double, 5> Run2_TauTau_legTriggerEff_DataReal;
    std::array <double, 5> Run2_TauTau_legTriggerEff_DataFake;

	std::array <double, 5> Run2_TauTau_legTriggerEff_Data;
	std::array <double, 5> Run2_TauTau_legTriggerEff_DataUP;
	std::array <double, 5> Run2_TauTau_legTriggerEff_DataDOWN;

	std::array <double, 5> Run2_TauTau_legTriggerEff_Mc;
	std::array <double, 5> Run2_TauTau_legTriggerEff_McUP;
	std::array <double, 5> Run2_TauTau_legTriggerEff_McDOWN;


	// MC scale factor functions

	/* crystal ball (x) step function -- args can be either doubles, or pt  + std::array <double, 5>*/
	double CBeff(double x, double m0, double sigma, double alpha, double n, double norm);
	double CBeff(double x, std::array <double, 5>);

	//////////////////////////////
	// muon and electron Scale Factors 


	//////////////////////
	// SUSY Higgs Pt NLO reweight TOOL
	// based on https://github.com/CMS-HTT/NLOReweightingTool
	
	TGraphErrors* NLO_func[27][60];
	std::vector<int> NLO_marray = {80, 90, 100, 110, 120, 130, 140, 160, 180, 200, 250, 300, 350, 400, 450, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1500, 1600, 1800, 2000};

	void NLO_ReadFile();
	float NLO_returnNLOweight(Int_t, Int_t, Double_t);


};

#endif  
