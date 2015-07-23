#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "TLorentzVector.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

NtuplePairIndependentInfo::NtuplePairIndependentInfo()
{
	m_PV_numberOfGoodVertices = 0;
	m_puWeight = 1.0;
	m_puWeightM1 = 1.0;
	m_puWeightP1 = 1.0;
	m_NumPileupInt = 1.0;
	m_NumTruePileUpInt = 1.0;
	m_NumPileupIntM1 = 1.0;
	m_NumTruePileUpIntM1 = 1.0;
	m_NumPileupIntP1 = 1.0;
	m_NumTruePileUpIntP1 = 1.0;
  m_generatorEventWeight = 1.0;
  m_hepNUP = -999;
}

void  NtuplePairIndependentInfo::fill_hepNUP(int arg)
  {
    m_hepNUP = arg;
  }

void  NtuplePairIndependentInfo::fill_generatorEventWeight(double argWeight)
  {
    m_generatorEventWeight = argWeight;
  }

void NtuplePairIndependentInfo::fill_genParticle(NtupleGenParticle NgenPart)
  {
  	m_genParticles.push_back(NgenPart);

  };

void NtuplePairIndependentInfo::fill_jet(NtupleJet anNtupleJet)
  {
  	m_jets.push_back(anNtupleJet);

  };


 void NtuplePairIndependentInfo::fill_vertexInfo(reco::Vertex vtx0, unsigned int collectionSize)
{
	m_PV_numberOfGoodVertices = collectionSize;
	m_primaryVertex = vtx0;
}


void NtuplePairIndependentInfo::fill_pileUpInfo(edm::Handle<std::vector<PileupSummaryInfo> > PupInfo,
												std::string pileup_mcFilePath,
												std::string pileup_dataFilePath
													)
{

	bool verbose = 0;
	

	///////////////
    // non-valid PU Collection

    if(!PupInfo.isValid())
    {

		m_puWeight = 1.0;
		m_puWeightM1 = 1.0;
		m_puWeightP1 = 1.0;
		m_NumPileupInt = 1.0;
		m_NumTruePileUpInt = 1.0;
		m_NumPileupIntM1 = 1.0;
		m_NumTruePileUpIntM1 = 1.0;
		m_NumPileupIntP1 = 1.0;
		m_NumTruePileUpIntP1 = 1.0;

		if(verbose) std::cout<<"  NON VALID PU COLLECTION " << std::endl;


      	return;
    }


    /////////////////
    // for valid PU collections, compute a pileup weight

    edm::FileInPath mcFilePath = edm::FileInPath(pileup_mcFilePath);
    edm::FileInPath dataFilePath = edm::FileInPath(pileup_dataFilePath);



    edm::LumiReWeighting LumiWeights_(
    mcFilePath.fullPath().c_str(),
    dataFilePath.fullPath().c_str(),
    "pileup",
    "pileup");


    std::vector<PileupSummaryInfo>::const_iterator PVI;


    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI)
    {

      int BX = PVI->getBunchCrossing();



      if(BX==0)
      {
        m_NumTruePileUpInt = PVI->getTrueNumInteractions();
        m_NumPileupInt = PVI->getPU_NumInteractions();
      }
      else if(BX == -1)
      {
        m_NumTruePileUpIntM1 = PVI->getTrueNumInteractions();
        m_NumPileupIntM1 = PVI->getPU_NumInteractions();
      }
      else if(BX == 1)
      {
        m_NumTruePileUpIntP1 = PVI->getTrueNumInteractions();
        m_NumPileupIntP1 = PVI->getPU_NumInteractions();
      }
    }


    m_puWeight = LumiWeights_.weight( m_NumTruePileUpInt );
    m_puWeightM1 = LumiWeights_.weight( m_NumTruePileUpIntM1 );
    m_puWeightP1 = LumiWeights_.weight( m_NumTruePileUpIntP1 );

	if(verbose) std::cout<<"puWeight = "<< m_puWeight << std::endl;
	if(verbose) std::cout<<"puWeightM1 = "<< m_puWeightM1 << std::endl;
	if(verbose) std::cout<<"puWeightP1 = "<< m_puWeightP1 << std::endl;
	if(verbose) std::cout<<"NumPileupInt = "<< m_NumPileupInt << std::endl;
	if(verbose) std::cout<<"NumTruePileUpInt = "<< m_NumTruePileUpInt << std::endl;
	if(verbose) std::cout<<"NumPileupIntM1 = "<< m_NumPileupIntM1 << std::endl;
	if(verbose) std::cout<<"NumTruePileUpIntM1 = "<< m_NumTruePileUpIntM1 << std::endl;
	if(verbose) std::cout<<"NumPileupIntP1 = "<< m_NumPileupIntP1 << std::endl;
	if(verbose) std::cout<<"NumTruePileUpIntP1 = "<< m_NumTruePileUpIntP1 << std::endl;
    
}



std::vector<NtupleGenParticle> NtuplePairIndependentInfo::genParticles() const {return m_genParticles;}
std::vector<NtupleJet> NtuplePairIndependentInfo::jets() const {return m_jets;}
reco::Vertex  NtuplePairIndependentInfo::primaryVertex() const {return m_primaryVertex;}
int NtuplePairIndependentInfo::numberOfGoodVertices() const {return m_PV_numberOfGoodVertices;}

double NtuplePairIndependentInfo::puWeight() const { return m_puWeight; };
double NtuplePairIndependentInfo::puWeightM1() const { return m_puWeightM1; };
double NtuplePairIndependentInfo::puWeightP1() const { return m_puWeightP1; };
float NtuplePairIndependentInfo::NumPileupInt() const { return m_NumPileupInt; };
float NtuplePairIndependentInfo::NumTruePileUpInt() const { return m_NumTruePileUpInt; };
float NtuplePairIndependentInfo::NumPileupIntM1() const { return m_NumPileupIntM1; };
float NtuplePairIndependentInfo::NumTruePileUpIntM1() const { return m_NumTruePileUpIntM1; };
float NtuplePairIndependentInfo::NumPileupIntP1() const { return m_NumPileupIntP1; };
float NtuplePairIndependentInfo::NumTruePileUpIntP1() const { return m_NumTruePileUpIntP1; };
double NtuplePairIndependentInfo::generatorEventWeight() const {return m_generatorEventWeight; };
int NtuplePairIndependentInfo::hepNUP() const {return m_hepNUP; };
