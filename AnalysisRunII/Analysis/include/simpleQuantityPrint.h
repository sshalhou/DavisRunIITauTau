/* class simpleQuantityPrint 
demo : print some event information for the Davis FlatTuple

-- Shalhout
*/


#ifndef Analysis_simpleQuantityPrint_h
#define Analysis_simpleQuantityPrint_h

////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
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


class simpleQuantityPrint
{

public:
	simpleQuantityPrint(FlatTreeReader, bool);
	virtual ~simpleQuantityPrint();	
	void handleEvent();
	void finish();

private:
	FlatTreeReader R;


};

#endif  
