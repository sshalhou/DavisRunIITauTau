
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <TTree.h>
#include <TFile.h>
#include "FlatTreeReader.h"
#include "simpleQuantityPrint.h"
#include "histogramLeptonQuantities.h"
#include "generateH2TauSyncTree.h"
#include "eleTauCutFlowTree.h"
#include "singleEventHistogramExample.h"
#include "syncTreeAnalysis.h"

int main(int argc, char* argv[])
{

/* check the arguments */
/* at a minimum need the TTree name and a root file (or text file list of root files) + 1 operation */

if (argc < 3 || argc==3) 
{
	std::cout<<" invoke as ./run_analysis \"PASSCUTS/FlatTuple\" file.root operation1 operation2 ... operationN \n";
	std::cout<<" or  as ./run_analysis \"PASSCUTS/FlatTuple\" file.txt operation1 operation2 ... operationN \n";
	std::cout<<" where file.txt is a list of root files \n";
	return -999;
}


/* master list ok known operations */

std::vector <std::string> known_operations;
known_operations.push_back("simpleQuantityPrint");
known_operations.push_back("histogramLeptonQuantities");
known_operations.push_back("generateH2TauSyncTree");
known_operations.push_back("eleTauCutFlowTree");
known_operations.push_back("singleEventHistogramExample");
known_operations.push_back("syncTreeAnalysis");


/* parse the operations into a name bool map */
/* and check that all requested operations are valid */

std::map <std::string, bool> operations_map;
for(int i = 3; i<argc; i++) 
{
	operations_map[std::string(argv[i])] = 1;	

	if (!(std::find(known_operations.begin(), known_operations.end(), std::string(argv[i])) != known_operations.end()))
	{
		std::cout<<" unknown operation : "<<std::string(argv[i])<<" please check known_operations in ./src/analysisDriver.cc \n";
		return -999;
	}
	else 
	{
		std::cout<<" *** ADDING OPERATION : "<<std::string(argv[i])<<" \n";
	}


}




/* read in a FlatTuple file and ttree */
TChain * T = new TChain(std::string(argv[1]).c_str());

// case 1 : a single .root file name :

if( std::string(argv[2]).find(".root") !=std::string::npos )
{
	std::cout<<" *** will process root file "<<std::string(argv[2])<<"\n";
	T->Add(std::string(argv[2]).c_str());
}
	
// case 2 : a txt file of .root file names :

else if( std::string(argv[2]).find(".txt") !=std::string::npos )
{
	std::string fileLine;
	std::ifstream txtFile ( std::string(argv[2]).c_str() );
	if (txtFile.is_open())
 	{
    	while ( getline (txtFile,fileLine) )
    	{
    		if( fileLine.find(".root") !=std::string::npos && fileLine.find("#") == std::string::npos) 
    			{
    				T->Add(fileLine.c_str());
		      		std::cout <<" *** adding file "<< fileLine <<" from text file "<<std::string(argv[2]).c_str()<<"\n";
    			}
    	}
    	txtFile.close();
  	}
}

else 
{
	std::cout<<" sorry, you must provide an argument such as file.root or textFile.txt \n";
	std::cout<<" invoke as ./run_analysis \"PASSCUTS/FlatTuple\" file.root operation1 operation2 ... operationN \n";
	std::cout<<" or  as ./run_analysis \"PASSCUTS/FlatTuple\" file.txt operation1 operation2 ... operationN \n";
	std::cout<<" where file.txt is a list of root files \n";
	return -999;
}


if(!T) 
{
	std::cout<<"invalid file, tree, or TChain, check command line arguments \n";
	return -999;
}


/* create a reader object and connect the TTree pointer */
FlatTreeReader R(T);


/* invoke the operations */
simpleQuantityPrint 	 SQP(R,operations_map["simpleQuantityPrint"]);
histogramLeptonQuantities HLQ(R,operations_map["histogramLeptonQuantities"]);
generateH2TauSyncTree    SYNC(R,operations_map["generateH2TauSyncTree"]);
eleTauCutFlowTree        ETAUCUT(R,operations_map["eleTauCutFlowTree"]);
singleEventHistogramExample TWOD(R,operations_map["singleEventHistogramExample"]);
syncTreeAnalysis SYNCTREEANA(R,operations_map["syncTreeAnalysis"]);


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

	if(operations_map["histogramLeptonQuantities"]) HLQ.handleEvent();
	if(operations_map["generateH2TauSyncTree"]) SYNC.handleEvent();
	if(operations_map["eleTauCutFlowTree"]) ETAUCUT.handleEvent();
    if(operations_map["singleEventHistogramExample"]) TWOD.handleEvent();
    if(operations_map["syncTreeAnalysis"]) SYNCTREEANA.handleEvent();

///////// EXAMPLE CODE SHOWING ACCESS  -- END


	if(e==entries-1) std::cout<<" event "<<e<<" of "<<entries<<"\n";		
 }

if(operations_map["simpleQuantityPrint"]) SQP.finish();
if(operations_map["histogramLeptonQuantities"]) HLQ.finish();
if(operations_map["generateH2TauSyncTree"]) SYNC.finish();
if(operations_map["eleTauCutFlowTree"]) ETAUCUT.finish();
if(operations_map["singleEventHistogramExample"]) TWOD.finish();
if(operations_map["syncTreeAnalysis"]) SYNCTREEANA.finish();


return 0;	
}

