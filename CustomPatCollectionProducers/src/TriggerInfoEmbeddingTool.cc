/* for a pat::Electron, Muon or Tau collection embed accepted HLT trigger paths as UserFloats */


// system include files
#include <memory>
#include <sstream>

// user include files

#include "DavisRunIITauTau/CustomPatCollectionProducers/interface/TriggerInfoEmbeddingTool.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"

#include "TH1D.h"
#include <map>
#include "TFile.h"
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TString.h"




// constructor 

TriggerInfoEmbeddingTool::TriggerInfoEmbeddingTool(
				edm::Handle<edm::TriggerResults> & triggerBits_,
				edm::Handle<pat::TriggerObjectStandAloneCollection> & triggerObjects_,
				edm::Handle<pat::PackedTriggerPrescales> & triggerPreScales_,
				const edm::TriggerNames &names_):
					triggerBits(triggerBits_),
					triggerObjects(triggerObjects_),
					triggerPreScales(triggerPreScales_),
					names(names_)
					{}
	
// destructor 

TriggerInfoEmbeddingTool::~TriggerInfoEmbeddingTool(){}


// helpers 


void TriggerInfoEmbeddingTool::fillAcceptedPathsAndPrescales(std::vector<std::string> & pathNamesToFill, 
	std::vector<float> & pathPrescalesToFill)
	{
			for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) 
			{
				//std::cout<<names.triggerName(i)<<"\n";
				if(triggerBits->accept(i)) 
				{

					if(names.triggerName(i).find("HLT_")==0)
					{
						pathNamesToFill.push_back("AcceptWithPreScale_"+names.triggerName(i));
						pathPrescalesToFill.push_back(triggerPreScales->getPrescaleForIndex(i));
					}
				}
			}
	}





