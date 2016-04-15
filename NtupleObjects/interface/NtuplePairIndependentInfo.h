#ifndef DavisRunIITauTau_NtupleObjects_NtuplePairIndependentInfo_h
#define DavisRunIITauTau_NtupleObjects_NtuplePairIndependentInfo_h


// system include files
#include <memory>



// needed by ntuple Muons producer
#include <vector>
#include <string>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleGenParticle.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;

class NtuplePairIndependentInfo
{



public:

  NtuplePairIndependentInfo();
  virtual ~NtuplePairIndependentInfo(){}

  // fillers 

	void fill_genParticle(NtupleGenParticle);
	void fill_jet(NtupleJet);

  /* args are the 0th element in the vertex collection after quality cuts, size of the post-quality cut collection*/
  void fill_vertexInfo(reco::Vertex, unsigned int);

  /* fill sample info */

  void fill_sampleInfo(edm::ParameterSet);

  /* fill pileUp info */
  void fill_pileUpInfo(edm::Handle<std::vector<PileupSummaryInfo> >, std::string, std::string); /* strings are mc path, data path */

  /* fill the generator event weight */
  void fill_generatorEventWeight(double);

  /* fill NUP */
  void fill_hepNUP(int);


  /* fill various MET filters */

  void fill_HBHENoiseFilter(bool);
  void fill_HBHEIsoNoiseFilter(bool);
  void fill_CSCTightHaloFilter(bool);
  void fill_goodVerticesFilter(bool);
  void fill_eeBadScFilter(bool);
  void fill_EcalDeadCellTriggerPrimitiveFilter(bool);


  /* fill the boson 4-vectors at gen level */

  void fill_GenBosonVisibleMomentum(LorentzVector);
  void fill_GenBosonTotalMomentum(LorentzVector); 



  // getters

  std::vector<NtupleGenParticle> genParticles() const; 
  std::vector<NtupleJet> jets() const; 
  reco::Vertex  primaryVertex() const;
  int  numberOfGoodVertices() const;
  double puWeight() const;
  double puWeightM1() const;
  double puWeightP1() const;
  float NumPileupInt() const;
  float NumTruePileUpInt() const;
  float NumPileupIntM1() const;
  float NumTruePileUpIntM1() const;
  float NumPileupIntP1() const;
  float NumTruePileUpIntP1() const;
  double generatorEventWeight() const;
  int hepNUP() const;

  std::string DataSet() const;
  int EventTotal() const;
  std::string EventType() const;
  std::string KeyName() const;
  double CrossSection() const;
  double FilterEff() const;
  double CodeVersion() const;

  bool HBHENoiseFilter() const;
  bool HBHEIsoNoiseFilter() const;
  bool CSCTightHaloFilter() const;
  bool goodVerticesFilter() const;
  bool eeBadScFilter() const;
  bool EcalDeadCellTriggerPrimitiveFilter() const;


  /* gen boson 4-vectors */

  LorentzVector GenBosonVisibleMomentum() const;
  LorentzVector GenBosonTotalMomentum() const;


private:

  /* generator level particle records */
  std::vector<NtupleGenParticle> m_genParticles; 
  std::vector<NtupleJet> m_jets; 
  
  /* vertex information */
  int m_PV_numberOfGoodVertices;
  reco::Vertex m_primaryVertex;

  /* PileUp info */
  double m_puWeight; 
  double m_puWeightM1;
  double m_puWeightP1;
  float m_NumPileupInt;
  float m_NumTruePileUpInt;
  float m_NumPileupIntM1;
  float m_NumTruePileUpIntM1;
  float m_NumPileupIntP1;
  float m_NumTruePileUpIntP1;

  /* generator weight */
  double m_generatorEventWeight;

  /* n partons at gen level */
  int m_hepNUP;

  /* sample info */

  std::string m_DataSet;
  int m_EventTotal;
  std::string m_EventType;
  std::string m_KeyName;
  double m_CrossSection;
  double m_FilterEff;
  double m_CodeVersion;

  /* MET filters */

  bool m_HBHENoiseFilter;
  bool m_HBHEIsoNoiseFilter;
  bool m_CSCTightHaloFilter;
  bool m_goodVerticesFilter;
  bool m_eeBadScFilter;
  bool m_EcalDeadCellTriggerPrimitiveFilter;

  /* gen boson 4-vectors */

  LorentzVector m_GenBosonVisibleMomentum;
  LorentzVector m_GenBosonTotalMomentum;

};

typedef std::vector<NtuplePairIndependentInfo> NtuplePairIndependentInfoCollection;

#endif
