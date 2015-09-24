/* class syncTreeAnalysis 
generate tree where leaves represent various cuts
applied in ele+tau channel
-- Shalhout
*/


#ifndef Analysis_syncTreeAnalysis_h
#define Analysis_syncTreeAnalysis_h

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


class syncTreeAnalysis
{

public:
	syncTreeAnalysis(FlatTreeReader, bool);
	virtual ~syncTreeAnalysis();	
	void handleEvent();
	void finish();
	void reset(); /* reset values each event */

private:
	FlatTreeReader R;
	bool m_run; /* did we want to run this operation? */ 
	void setupBranches(TTree*);
		
	

	// elements of the TTree 

	unsigned int run;
	unsigned int lumi;
	unsigned int event;
	bool isCorrectChannel;
	bool isOsPair;
	bool pairRank;
	bool leg1_pt;
	bool leg1_eta;
	bool leg1_dxy;
	bool leg1_dz;
	bool leg1_numberOfMissingInnerHits;
	bool leg1_passConversionVeto;
	bool leg1_passFail_electronMVA80;
	bool leg2_pt;
	bool leg2_eta;
	bool leg2_decayModeFindingNewDMs;
	bool leg2_dz;
	bool leg2_charge;
	bool leg2_dzTauVertex;
	bool single_obj_trigger;
	bool single_obj_trigger_withoutPtCut;
	bool double_obj_trigger;
	bool triggerOR;





	// member pointers to TTrees & TFiles 
	
	TFile * outFile_EleTau;
	TTree * tree_EleTau;
	


};

#endif  