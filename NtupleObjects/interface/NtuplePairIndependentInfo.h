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

  /* fill the gen level HT, Zmass, & numberOutgoingPartons - used for stitching */
  void fill_lheHT(double);
  void fill_lheOutGoingPartons(int);
  void fill_lheZmass(double);





  /* fill various MET filters */

  void fill_HBHENoiseFilter(bool);
  void fill_HBHENoiseIsoFilter(bool);
  void fill_CSCTightHalo2015Filter(bool);
  void fill_EcalDeadCellTriggerPrimitiveFilter(bool);
  void fill_goodVertices(bool);
  void fill_eeBadScFilter(bool);
  void fill_chargedHadronTrackResolutionFilter(bool);
  void fill_muonBadTrackFilter(bool);
  void fill_globalTightHalo2016Filter(bool);
  void fill_BadChargedCandidateFilter(bool);
  void fill_BadPFMuonFilter(bool);
  void fill_BadMuonTaggedMoriond17(bool);
  void fill_DuplicateMuonTaggedMoriond17(bool);


  /* fill the boson 4-vectors at gen level */

  void fill_GenBosonVisibleMomentum(LorentzVector);
  void fill_GenBosonTotalMomentum(LorentzVector); 

  /* fill the theory weights */

  void fill_originalXWGTUP(float);
  void fill_theory_scale_factors(std::vector<float>);




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
  double lheHT() const;
  int lheOutGoingPartons() const;
  double lheZmass() const;

  std::string DataSet() const;
  int EventTotal() const;
  std::string EventType() const;
  std::string KeyName() const;
  std::string DataCard() const;
  double CrossSection() const;
  double FilterEff() const;
  double CodeVersion() const;



  bool HBHENoiseFilter() const;
  bool HBHENoiseIsoFilter() const;
  bool CSCTightHalo2015Filter() const;
  bool EcalDeadCellTriggerPrimitiveFilter() const;
  bool goodVertices() const;
  bool eeBadScFilter() const;
  bool chargedHadronTrackResolutionFilter() const;
  bool muonBadTrackFilter() const;
  bool globalTightHalo2016Filter() const;
  bool BadChargedCandidateFilter() const;
  bool BadPFMuonFilter() const;
  bool BadMuonTaggedMoriond17() const;
  bool DuplicateMuonTaggedMoriond17() const;


  /* gen boson 4-vectors */

  LorentzVector GenBosonVisibleMomentum() const;
  LorentzVector GenBosonTotalMomentum() const;


  /* get theory weights */

  float originalXWGTUP() const;
  std::vector<float> theory_scale_factors() const;


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

  /* for HT and njet binned sample weight */
  double m_lheHT;
  int m_lheOutGoingPartons;
  double m_lheZmass;

  /* sample info */

  std::string m_DataSet;
  int m_EventTotal;
  std::string m_EventType;
  std::string m_KeyName;
  std::string m_DataCard;
  double m_CrossSection;
  double m_FilterEff;
  double m_CodeVersion;

  /* MET filters */

  bool m_HBHENoiseFilter;
  bool m_HBHENoiseIsoFilter;
  bool m_CSCTightHalo2015Filter;
  bool m_EcalDeadCellTriggerPrimitiveFilter;
  bool m_goodVertices;
  bool m_eeBadScFilter;
  bool m_chargedHadronTrackResolutionFilter;
  bool m_muonBadTrackFilter;
  bool m_globalTightHalo2016Filter;
  bool m_BadChargedCandidateFilter;
  bool m_BadPFMuonFilter;

  /* bad and duplicate muon filters, if true the event
     was tagged as having bad or duplicate muons */
  
  bool m_BadMuonTaggedMoriond17; 
  bool m_DuplicateMuonTaggedMoriond17;


  /* gen boson 4-vectors */

  LorentzVector m_GenBosonVisibleMomentum;
  LorentzVector m_GenBosonTotalMomentum;

  /* holder for theory unc. */

  float m_originalXWGTUP;
  std::vector<float> m_theory_scale_factors; /* these are all weight/originalXWGTUP, 
                                                only filled for lhe-valid MC samples (see log file for translation) */

};

typedef std::vector<NtuplePairIndependentInfo> NtuplePairIndependentInfoCollection;

#endif
