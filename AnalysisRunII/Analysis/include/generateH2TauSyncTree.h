/* class generateH2TauSyncTree 
generate the H2TauTau group's standard sync trees (one tree produced per channel)
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
#include <vector>
#include <utility>
#include <iostream>
#include <TApplication.h>
#include <TLeaf.h>
#include <map>
#include <TString.h>
#include <assert.h>
#include "FlatTreeReader.h"


class generateH2TauSyncTree
{

public:
	generateH2TauSyncTree(FlatTreeReader, bool);
	virtual ~generateH2TauSyncTree();	
	void handleEvent();
	void finish();

private:
	FlatTreeReader R;
	bool m_run; /* did we want to run this operation? */ 
	void setupBranches(TTree*);
	// elements of the TTree 

	unsigned int run;
	unsigned int lumi;
	unsigned int event;

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



	// member pointers to TTrees & TFiles 
	
	TFile * outFile_MuTau;
	TFile * outFile_EleTau;
	TFile * outFile_TauTau;
	TFile * outFile_EleMu;

	TTree * tree_MuTau;
	TTree * tree_EleTau;
	TTree * tree_TauTau;
	TTree * tree_EleMu;
	


};

#endif  