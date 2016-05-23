/* class generateH2TauSyncTree 
generate the H2TauTau group's standard sync trees (one tree produced per channel)
see : https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorking2015#Synchronisation_Ntuple
-- Shalhout
*/


#ifndef Analysis_generateH2TauSyncTree_h
#define Analysis_generateH2TauSyncTree_h

////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
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
#include "FlatTreeReader.h"
#include <math.h>


class generateH2TauSyncTree
{

public:
	generateH2TauSyncTree(FlatTreeReader, bool);
	virtual ~generateH2TauSyncTree();	
	void handleEvent();
	void finish();
	double pzetaVisCalc(TLorentzVector, TLorentzVector);
	double pzetaMissCalc(TLorentzVector, TLorentzVector, TLorentzVector);
	void reset(); /* reset values each event */
	void setExtraLepVetoes(TLorentzVector, TLorentzVector);

private:
	FlatTreeReader R;
	bool m_run; /* did we want to run this operation? */ 
	void setupBranches(TTree*);
		
	// counters
	int num_et;
	int num_em;
	int num_tt;
	int num_mt;

    // read histograms for likelihood method
      TFile* inFile = new TFile("pDistPlots.root","READ");
      TH1F *eHistoFrac = (TH1F*)inFile->Get("/demo/eVisFrac");
      TH1F *muHistoFrac = (TH1F*)inFile->Get("/demo/muVisFrac");
      TH1F *h1p0sHistoFrac = (TH1F*)inFile->Get("/demo/h1p0sVisFrac");
      TH1F *h1p1sHistoFrac = (TH1F*)inFile->Get("/demo/h1p1sVisFrac");
      TH1F *h1p2sHistoFrac = (TH1F*)inFile->Get("/demo/h1p2sVisFrac");
      TH1F *h1p3sHistoFrac = (TH1F*)inFile->Get("/demo/h1p3sVisFrac");
      TH1F *h3p0sHistoFrac = (TH1F*)inFile->Get("/demo/h3p0sVisFrac");
      TH1F *h3p1sHistoFrac = (TH1F*)inFile->Get("/demo/h3p1sVisFrac");


	// elements of the TTree 

	unsigned int run;
	unsigned int lumi;
	unsigned int event;

	unsigned int pairRank; // davis specific
	int isOsPair; // davis specific

	int npv;
	float npu;
	double rho;

	double pt_1;
	double phi_1;
	double eta_1;
	double m_1;
	int q_1;
	float d0_1;
	float dZ_1;
	double mt_1;	
	float iso_1;
	float id_e_mva_nt_loose_1;
	float againstElectronLooseMVA5_1;
	float againstElectronMediumMVA5_1;
	float againstElectronTightMVA5_1;
	float againstElectronVLooseMVA5_1;
	float againstElectronVTightMVA5_1;
	float againstMuonLoose3_1;
	float againstMuonTight3_1;
	float byCombinedIsolationDeltaBetaCorrRaw3Hits_1;
	float byIsolationMVA3newDMwoLTraw_1;
	float byIsolationMVA3oldDMwoLTraw_1;
	float byIsolationMVA3newDMwLTraw_1;
	float byIsolationMVA3oldDMwLTraw_1;
	float chargedIsoPtSum_1;
	float decayModeFindingNewDMs_1;
	float neutralIsoPtSum_1;
	float puCorrPtSum_1;


	double pt_2;
	double phi_2;
	double eta_2;
	double m_2;
	int q_2;
	float d0_2;
	float dZ_2;
	double mt_2;	
	float iso_2;
	float id_e_mva_nt_loose_2;
	float againstElectronLooseMVA5_2;
	float againstElectronMediumMVA5_2;
	float againstElectronTightMVA5_2;
	float againstElectronVLooseMVA5_2;
	float againstElectronVTightMVA5_2;
	float againstMuonLoose3_2;
	float againstMuonTight3_2;
	float byCombinedIsolationDeltaBetaCorrRaw3Hits_2;
	float byIsolationMVA3newDMwoLTraw_2;
	float byIsolationMVA3oldDMwoLTraw_2;
	float byIsolationMVA3newDMwLTraw_2;
	float byIsolationMVA3oldDMwLTraw_2;
	float chargedIsoPtSum_2;
	float decayModeFindingNewDMs_2;
	float neutralIsoPtSum_2;
	float puCorrPtSum_2;

	double pt_tt;
	double m_vis;
	
	double met;
	double metphi;
	double mvamet;
	double mvametphi;
	double pzetavis;
	double pzetamiss;
	double mvacov00;
	double mvacov01;
	double mvacov10;
	double mvacov11;
	double metcov00;
	double metcov01;
	double metcov10;
	double metcov11;

	// Only fill if njetspt20>=2 
	double mjj;
	double jdeta;
	double njetingap;
	double njetingap20;
	double jdphi;


	// for jet counting 

	int nbtag;
	int njets;
	int njetspt20;

	// for leading jet in pt (pt > 20)
	
	double jpt_1;
	double jeta_1;
	double jphi_1;
	double jrawf_1; /* don't have yet */
	double jmva_1;

	// for trailing jet in pt (pt > 20)

	double jpt_2; 
	double jeta_2;
	double jphi_2;
	double jrawf_2; /* don't have yet */
	double jmva_2;

	// for leading b-jet in pt (pt > 20)

	double bpt_1;
	double beta_1;
	double bphi_1;
	double brawf_1;
	double bmva_1;
	float bcsv_1;
	
	// for trailing b-jet in pt (pt > 20)

	double bpt_2;
	double beta_2;
	double bphi_2;
	double brawf_2;
	double bmva_2;
	float bcsv_2;

	// extra vetoes

	float dilepton_veto; 	
	float extraelec_veto; 	
	float extramuon_veto;

	// DY info

	bool isZtt;  	
	bool isZmt;  	
	bool isZet;  	
	bool isZee;  	
	bool isZmm;  	
	bool isZem;  	
	bool isZEE;  	
	bool isZMM;  	
	bool isZLL;  	
	bool isFake;  

	// trigger info

	float trigweight_1 ;
	float trigweight_2 ;


	// information related to sample and weights


	double generatorEventWeight;
	std::string DataSet; 	/* the dataset */
    int EventTotal; 		/* the number of events in the MC sample */ 
    std::string EventType;  /* description of the event, DATA, MC, EMBEDDED, etc. */
    std::string KeyName;    /* description of the sample as given during crab job */
    double CrossSection;    /* MC process cross section */
    double FilterEff;       /* gen level filter eff. (needed if any is applied) */



    ///function Methods variables
    
    //Likelihood Higgs Pt variables
    
    //save to Tree
    double genPt;
    double matchedLikelihoodPt;
    double unmatchedLikelihoodPt;
    double visPt;
    
    //used in Calculation
    double visFrac1;
    double visFrac1Prob;
    double visFrac2;
    double visFrac2Prob;
    double currentFracProb;
    double bestFracProb;
    double bestP;
    double totalGenP;
    double ratioGL;


    //Pchi & Mmin function variables

    //Number of Events to be Put in the Tree

    //Variables from Simulation File
    double ME_T;//Originally set to a ridiculous value, for debugging
    double ME_T_phi; //phi_T in Pchi code
    double p_lt;
    double eta_l;
    double phi_l;
    double p_Taut;//Added 03/16/2016
    double eta_Tau;//Added 03/16/2016
    double phi_Tau;//Added 03/16/2016
    double M_l;

    //Variables calculated in the code
    double p_lx;//Originally set to a ridiculous value, for debugging
    double p_ly;
    double p_lz;
    double E_l;

    double p_vx;
    double p_vy;
    double E_v;

    double M_min;
    double P_chi;



	// member pointers to TTrees & TFiles 
	
	TFile * outFile_MuTau;
	TFile * outFile_EleTau;
	TFile * outFile_TauTau;
	TFile * outFile_EleMu;

	TTree * tree_MuTau;
	TTree * tree_EleTau;
	TTree * tree_TauTau;
	TTree * tree_EleMu;

	// to hold run:lumi:event from MET 
	// filter veto files 	

	std::vector < std::string > metFilter_DoubleEG;
	std::vector < std::string > metFilter_MuonEG;
	std::vector < std::string > metFilter_SingleElectron;
	std::vector < std::string > metFilter_SingleMuon;
	std::vector < std::string > metFilter_Tau;


};

#endif  