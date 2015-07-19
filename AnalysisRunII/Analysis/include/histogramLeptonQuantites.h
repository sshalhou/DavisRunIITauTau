/* class histogramLeptonQuantites 
demo : histogram some lepton quantities for muon+Tau and electron+Tau events

-- Shalhout
*/


#ifndef Analysis_histogramLeptonQuantites_h
#define Analysis_histogramLeptonQuantites_h

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


class histogramLeptonQuantites
{

public:
	histogramLeptonQuantites(FlatTreeReader, bool);
	virtual ~histogramLeptonQuantites();	
	void handleEvent();
	void finish();

private:
	FlatTreeReader R;
	bool run; /* did we want to run this operation? */
	// add pointers to histograms or files here 
	TFile * outFile;
	TH1F * muon_pt;
	TH1F * electron_pt;
	TH1F * tau_pt_inETau;
	TH1F * tau_pt_inMuTau;


};

#endif  