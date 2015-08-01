
#include <iostream>
#include <map>
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <TTree.h>
#include <TFile.h>
#include "FlatTreeReader.h"
#include "simpleQuantityPrint.h"
#include "histogramLeptonQuantites.h"
#include "generateH2TauSyncTree.h"
#include "eleTauCutFlowTree.h"

int main(int argc, char* argv[])
{

/* check the arguments */
/* at a minimum need the TTree name and a root file + 1 operation */

if (argc < 3 || argc==3) 
{
	std::cout<<" invoke as ./make_syncTree \"PASSCUTS/FlatTuple\" file.root operation1 operation2 ... operationN \n";

	return -999;
}


/* parse the operations into a name bool map */

std::map <std::string, bool> operations_map;
for(int i = 3; i<argc; i++) operations_map[std::string(argv[i])] = 1;	





/* read in a FlatTuple file and ttree */

TFile file(std::string(argv[2]).c_str(),"READ");
TTree * T = (TTree*) file.Get(std::string(argv[1]).c_str());

if(!T) 
{
	std::cout<<"invalid file or tree, check command line arguments \n";
	return -999;
}


/* create a reader object and connect the TTree pointer */
FlatTreeReader R(T);


/* invoke the operations */
simpleQuantityPrint 	 SQP(R,operations_map["simpleQuantityPrint"]);
histogramLeptonQuantites HLQ(R,operations_map["histogramLeptonQuantites"]);
generateH2TauSyncTree    SYNC(R,operations_map["generateH2TauSyncTree"]);
eleTauCutFlowTree        ETAUCUT(R,operations_map["eleTauCutFlowTree"]);


long int entries = T->GetEntries();

std::cout<<" total events = "<<entries<<"\n";

for(long int e = 0; e<entries; ++e)
{
	
	T->GetEntry(e);

	if(e%1000 == 0)
	{
		std::cout<<" event "<<e<<" of "<<entries<<"\n";		

		/* only print this stuff once every 1000 events */
		if(operations_map["simpleQuantityPrint"]) SQP.handleEvent();

	}

	if(operations_map["histogramLeptonQuantites"]) HLQ.handleEvent();
	if(operations_map["generateH2TauSyncTree"]) SYNC.handleEvent();
	if(operations_map["eleTauCutFlowTree"]) ETAUCUT.handleEvent();


///////// EXAMPLE CODE SHOWING ACCESS  -- END


	if(e==entries-1) std::cout<<" event "<<e<<" of "<<entries<<"\n";		
 }

if(operations_map["simpleQuantityPrint"]) SQP.finish();
if(operations_map["histogramLeptonQuantites"]) HLQ.finish();
if(operations_map["generateH2TauSyncTree"]) SYNC.finish();
if(operations_map["eleTauCutFlowTree"]) ETAUCUT.finish();


return 0;	
}

