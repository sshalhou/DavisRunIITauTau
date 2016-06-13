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
	double mtTotCalc(TLorentzVector, TLorentzVector, TLorentzVector);

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


	// elements of the TTree 

	/* davis specific */

	unsigned int pairRank; 
	int isOsPair; 

	/* event ID variables */

	unsigned int run;
	unsigned int event;
	unsigned int lumi;

	/* pile up */

	int npv;
	float npu;
	double rho;
	double puweight;

	/* leg_1 */

	double pt_1;
	double phi_1;
	double eta_1;
	double m_1;
	int    q_1;
	float  d0_1;
	float  dZ_1;
	double mt_1;			    /* using mva met */
	double pfmt_1; 
	double puppimt_1;
	float  iso_1;
	float  id_e_mva_nt_loose_1; /* non-triggering ele MVA score */
	int    gen_match_1; 	    /* H2TauTau group's gen-match codes, 
								   see DavisRunIITauTau/FlatTupleGenerator/interface/GenMcMatchTypes.h */ 
	float  againstElectronLooseMVA6_1;
	float  againstElectronMediumMVA6_1;
	float  againstElectronTightMVA6_1;
	float  againstElectronVLooseMVA6_1;
	float  againstElectronVTightMVA6_1;
	float  againstMuonLoose3_1;
	float  againstMuonTight3_1;
	float  byCombinedIsolationDeltaBetaCorrRaw3Hits_1;
	float  byIsolationMVA3newDMwoLTraw_1;
	float  byIsolationMVA3oldDMwoLTraw_1;
	float  byIsolationMVA3newDMwLTraw_1;
	float  byIsolationMVA3oldDMwLTraw_1;
	float  chargedIsoPtSum_1;
	float  decayModeFindingOldDMs_1;
	float  neutralIsoPtSum_1;
	float  puCorrPtSum_1;


	/* leg_2 */

	double pt_2;
	double phi_2;
	double eta_2;
	double m_2;
	int    q_2;
	float  d0_2;
	float  dZ_2;
	double mt_2;			    /* using mva met */
	double pfmt_2; 
	double puppimt_2;
	float  iso_2;
	float  id_e_mva_nt_loose_2; /* non-triggering ele MVA score */
	int    gen_match_2; 	    /* H2TauTau group's gen-match codes, 
								   see DavisRunIITauTau/FlatTupleGenerator/interface/GenMcMatchTypes.h */ 
	float  againstElectronLooseMVA6_2;
	float  againstElectronMediumMVA6_2;
	float  againstElectronTightMVA6_2;
	float  againstElectronVLooseMVA6_2;
	float  againstElectronVTightMVA6_2;
	float  againstMuonLoose3_2;
	float  againstMuonTight3_2;
	float  byCombinedIsolationDeltaBetaCorrRaw3Hits_2;
	float  byIsolationMVA3newDMwoLTraw_2;
	float  byIsolationMVA3oldDMwoLTraw_2;
	float  byIsolationMVA3newDMwLTraw_2;
	float  byIsolationMVA3oldDMwLTraw_2;
	float  chargedIsoPtSum_2;
	float  decayModeFindingOldDMs_2;
	float  neutralIsoPtSum_2;
	float  puCorrPtSum_2;
	float  trigweight_2;
	float  idisoweight_2;

	/* di-tau system */

	double pt_tt;
	double mt_tot; /* use mva met */	
	double m_vis;
	double m_sv;
	double mt_sv;

	/* met */

	double met;
	double metphi;
	double puppimet;
	double puppimetphi;
	double mvamet;
	double mvametphi;
	double pzetavis;
	double pzetamiss;     /*  using mva met */
	double pfpzetamiss;    /*  use pf met */
	double puppipzetamiss; /*  use puppi met */
	double mvacov00;
	double mvacov01;
	double mvacov10;
	double mvacov11;
	double metcov00;     /* using pf met */
	double metcov01;
	double metcov10;
	double metcov11;

	/* VBF system */

	// Only filled if njetspt20>=2 

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
	double jm_1;
	double jrawf_1; 
	double jmva_1;

	// for trailing jet in pt (pt > 20)

	double jpt_2; 
	double jeta_2;
	double jphi_2;
	double jm_2;
	double jrawf_2; 
	double jmva_2;

	// for leading b-jet in pt (pt > 20)

	double bpt_1;
	double beta_1;
	double bphi_1;
	double bm_1;
	double brawf_1;
	double bmva_1;
	float bcsv_1;
	
	// for trailing b-jet in pt (pt > 20)

	double bpt_2;
	double beta_2;
	double bphi_2;
	double bm_2;
	double brawf_2;
	double bmva_2;
	float bcsv_2;

	// extra vetoes

	float dilepton_veto; 	
	float extraelec_veto; 	
	float extramuon_veto;


	/* gen info */

	int NUP;
	double weight; /* global event weight (MC xSection and num events excluded) ? */
	double generatorEventWeight;


	// information related to sample and weights

	std::string DataSet; 	/* the dataset */
    int EventTotal; 		/* the number of events in the MC sample */ 
    std::string EventType;  /* description of the event, DATA, MC, EMBEDDED, etc. */
    std::string KeyName;    /* description of the sample as given during crab job */
    double CrossSection;    /* MC process cross section */
    double FilterEff;       /* gen level filter eff. (needed if any is applied) */



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