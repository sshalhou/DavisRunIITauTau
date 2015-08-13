/* class singleEventHistogramExample 
demo : example of making a unique TH2F histogram for each event

-- Shalhout
*/


#ifndef Analysis_singleEventHistogramExample_h
#define Analysis_singleEventHistogramExample_h

////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
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


class singleEventHistogramExample
{

public:
	singleEventHistogramExample(FlatTreeReader, bool);
	virtual ~singleEventHistogramExample();	
	void handleEvent();
	void finish();

private:
	FlatTreeReader R;
	bool run; /* did we want to run this operation? */
	// add pointers to histograms or files here 
	TFile * outFile;	
	std::vector< TH2F * > the_histograms; // one hist per event 
	TH2F * manyEvents;


};

#endif  