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

  m_DataSet = "NULL";
  m_EventTotal = -999;
  m_EventType = "NULL";
  m_KeyName = "NULL";
  m_CrossSection = NAN;
  m_FilterEff = NAN;
  m_CodeVersion = NAN;

  m_HBHENoiseFilter = 1;
  m_HBHEIsoNoiseFilter = 1;
  m_CSCTightHaloFilter = 1;
  m_goodVerticesFilter = 1;
  m_eeBadScFilter = 1;
  m_EcalDeadCellTriggerPrimitiveFilter = 1;

  m_GenBosonVisibleMomentum.SetXYZT(NAN,NAN,NAN,NAN);
  m_GenBosonTotalMomentum.SetXYZT(NAN,NAN,NAN,NAN);

}


void  NtuplePairIndependentInfo::fill_GenBosonVisibleMomentum(LorentzVector X)
{  
  m_GenBosonVisibleMomentum  = X;
}
void  NtuplePairIndependentInfo::fill_GenBosonTotalMomentum(LorentzVector X) 
{
  m_GenBosonTotalMomentum  = X;
}


void  NtuplePairIndependentInfo::fill_HBHEIsoNoiseFilter(bool arg)
  {
    m_HBHEIsoNoiseFilter = arg;
  }

 

void  NtuplePairIndependentInfo::fill_HBHENoiseFilter(bool arg)
  {
    m_HBHENoiseFilter = arg;
  }

void  NtuplePairIndependentInfo::fill_CSCTightHaloFilter(bool arg)
  {
    m_CSCTightHaloFilter = arg;
  }

void  NtuplePairIndependentInfo::fill_goodVerticesFilter(bool arg)
  {
    m_goodVerticesFilter = arg;
  }

void  NtuplePairIndependentInfo::fill_eeBadScFilter(bool arg)
  {
    m_eeBadScFilter = arg;
  }

void  NtuplePairIndependentInfo::fill_EcalDeadCellTriggerPrimitiveFilter(bool arg)
  {
    m_EcalDeadCellTriggerPrimitiveFilter = arg;
  }


void  NtuplePairIndependentInfo::fill_sampleInfo(edm::ParameterSet argSet)
  {

    m_DataSet = argSet.getParameter< std::string >("DataSet");
    m_EventTotal = argSet.getParameter< int >("EventTotal");
    m_EventType = argSet.getParameter< std::string >("EventType");
    m_KeyName = argSet.getParameter< std::string >("KeyName");
    m_CrossSection = argSet.getParameter< double >("CrossSection");
    m_FilterEff = argSet.getParameter< double >("FilterEff");
    m_CodeVersion = argSet.getParameter< double >("CodeVersion");

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

std::string NtuplePairIndependentInfo::DataSet() const { return m_DataSet; };
int NtuplePairIndependentInfo::EventTotal() const { return m_EventTotal; };
std::string NtuplePairIndependentInfo::EventType() const { return m_EventType; };
std::string NtuplePairIndependentInfo::KeyName() const { return m_KeyName; };
double NtuplePairIndependentInfo::CrossSection() const { return m_CrossSection; };
double NtuplePairIndependentInfo::FilterEff() const { return m_FilterEff; };
double NtuplePairIndependentInfo::CodeVersion() const { return m_CodeVersion; };

bool NtuplePairIndependentInfo::HBHEIsoNoiseFilter() const { return m_HBHEIsoNoiseFilter; };

bool NtuplePairIndependentInfo::HBHENoiseFilter() const { return m_HBHENoiseFilter; };
bool NtuplePairIndependentInfo::CSCTightHaloFilter() const { return m_CSCTightHaloFilter; };
bool NtuplePairIndependentInfo::goodVerticesFilter() const { return m_goodVerticesFilter; };
bool NtuplePairIndependentInfo::eeBadScFilter() const { return m_eeBadScFilter; };
bool NtuplePairIndependentInfo::EcalDeadCellTriggerPrimitiveFilter() const { return m_EcalDeadCellTriggerPrimitiveFilter; };

LorentzVector  NtuplePairIndependentInfo::GenBosonVisibleMomentum() const { return m_GenBosonVisibleMomentum; };
LorentzVector  NtuplePairIndependentInfo::GenBosonTotalMomentum() const { return m_GenBosonTotalMomentum; };

