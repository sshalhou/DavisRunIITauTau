#ifndef DavisRunIITauTau_NtupleObjects_NtupleJet_h
#define DavisRunIITauTau_NtupleObjects_NtupleJet_h


// system include files
#include <memory>
#include <cassert>



// needed by ntuple Muons producer
#include <vector>
#include <string>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"



typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;

class NtupleJet
{



public:

  NtupleJet();
  virtual ~NtupleJet(){}

  // fillers 

  void fill(pat::Jet);
  void fill_defaultBtagInfo(pat::Jet, std::string, bool, unsigned int, bool); /* theJet, bTagAlgoName, applySF, SFseed, isRealData */
  void fill_PUjetID(pat::Jet, std::string, double); /* theJet, DiscName, double CutMinimum */
  void fill_PFjetID(bool);

  // helpers

  stringVec JEC_labels() ;     /* the available jec labels  */
  floatVec JEC_SFs() ;         /* the available jec SFs */
  float JEC(std::string);      /* return the JEC for available string assert if not available */
 
  stringVec BTAG_labels() ;      /* the available b-tag algorithm labels  */
  floatVec BTAGraw_scores() ;    /* the raw b-tag algorithm outputs - no SFs are applied here */
  float BTAGraw(std::string);    /* return the raw b-tag score for available string assert if not available */

  // getters
 


  LorentzVector jet_p4() const; /* should have all corrections applied */
  LorentzVector GENjet_p4() const; /* as embedded in slimmedJets */
  int GENjet_pdgId() const; /* as embedded in slimmedJets */

  double PU_jetIdRaw() const;   /* raw value of PU jet ID discriminant */
  bool PU_jetIdPassed() const;   /* pass/fail  of PU jet ID discriminant */
  bool PF_jetIdPassed() const;      /* pass/fail of PF jet ID discriminant */
  int PARTON_flavour() const; 
  int HADRON_flavour() const; 
  float jet_vertex_x() const; 
  float jet_vertex_y() const; 
  float jet_vertex_z() const; 
  int isPFJet() const; 
  double neutralHadronEnergyFraction() const; 
  double neutralEmEnergyFraction() const; 
  double chargedHadronEnergyFraction() const; 
  double muonEnergyFraction() const; 
  double chargedEmEnergyFraction() const; 
  double chargedMultiplicityPlusNeutralMultiplicity() const; 
  double chargedMultiplicity() const; 
  double neutralMultiplicity() const;

  /* we will also access the PF jet ID relevant info using standard names */
  double NHF() const; 
  double NEMF() const; 
  double CHF() const; 
  double MUF() const; 
  double CEMF() const; 
  double NumConst() const; 
  double CHM() const; 
  double NumNeutralParticle() const;

  std::string defaultBtagAlgorithm_Name() const;
  double defaultBtagAlgorithm_RawScore() const;
  bool defaultBtagAlgorithm_isPassed() const;

  /* for easy use with cut strings */
  double pt() const; /* should have all corrections applied */
  double eta() const; /* should have all corrections applied */


private:

  LorentzVector m_jet_p4;
  LorentzVector m_GENjet_p4;
  int m_GENjet_pdgId;
  int m_PARTON_flavour;
  int m_HADRON_flavour;
  float m_jet_vertex_x;
  float m_jet_vertex_y;
  float m_jet_vertex_z;
  std::vector<std::pair<std::string, float> >  m_JetEnergyCorrection;
  std::vector<std::pair<std::string, float> >  m_BTAG;
  int m_isPFJet;
  double m_neutralHadronEnergyFraction;                 /* NHF for PF jet ID */
  double m_neutralEmEnergyFraction;                     /* NEMF for PF jet ID */
  double m_chargedHadronEnergyFraction;                 /* CHF for PF jet ID */
  double m_muonEnergyFraction;                          /* MUF for PF jet ID */
  double m_chargedEmEnergyFraction;                     /* CEMF for PF jet ID */
  double m_chargedMultiplicityPlusNeutralMultiplicity;  /* NumConst for PF jet ID */
  double m_chargedMultiplicity;                         /* CHM for PF jet ID */
  double m_neutralMultiplicity;                         /* NumNeutralParticle for PF jet ID */
  std::string m_defaultBtagAlgorithm_Name;              /* name of the default b-tag algorithm from ConfigNtupleContent_cfi.py */
  float m_defaultBtagAlgorithm_RawScore;                /* raw output of default b-tag algo */
  bool m_defaultBtagAlgorithm_isPassed;                 /* pass-fail of default b-tag algo after btagSF applied */
  double m_PU_jetIdRaw;                                 /* raw PU jet ID score */
  bool m_PU_jetIdPassed;                                /* pass/fail PU jet ID  */
  bool m_PF_jetIdPassed;                                /* pass/fail PF jet ID */



};

typedef std::vector<NtupleJet> NtupleJetCollection;

#endif
