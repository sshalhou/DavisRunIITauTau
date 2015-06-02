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

  // helpers

  stringVec JEC_labels() ; /* the available jec labels  */
  floatVec JEC_SFs() ; /* the available jec SFs */
  float JEC(std::string); /* return the JEC for available string assert if not available */
 
  // getters
 

  LorentzVector jet_p4() const; /* should have all corrections applied */
  double PU_jetID() const; /* raw value of PU jet ID discriminant */
  double PF_jetID() const; /* raw value of PF jet ID discriminant */
  double BTAG_discriminant() const; /* raw value of BTAG score */
  int BTAG_pass() const; /* b-tag pass-fail after application of b-tag SF */
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

  /* we will also access the PF jet ID relevant info using standard names */
  double NHF() const; 
  double NEMF() const; 
  double CHF() const; 
  double MUF() const; 
  double CEMF() const; 
  double NumConst() const; 
  double CHM() const; 



private:

  LorentzVector m_jet_p4;
  int m_PARTON_flavour;
  int m_HADRON_flavour;
  float m_jet_vertex_x;
  float m_jet_vertex_y;
  float m_jet_vertex_z;
  int m_isPFJet;
  double m_neutralHadronEnergyFraction;                /* NHF for PF jet ID */
  double m_neutralEmEnergyFraction;                    /* NEMF for PF jet ID */
  double m_chargedHadronEnergyFraction;                /* CHF for PF jet ID */
  double m_muonEnergyFraction;                         /* MUF for PF jet ID */
  double m_chargedEmEnergyFraction;                    /* CEMF for PF jet ID */
  double m_chargedMultiplicityPlusNeutralMultiplicity; /* NumConst for PF jet ID */
  double m_chargedMultiplicity;                        /* CHM for PF jet ID */
  std::vector<std::pair<std::string, float> >  m_JetEnergyCorrection;

  

  double m_PU_jetID;
  double m_PF_jetID;
  double m_BTAG_discriminant;
  int m_BTAG_pass;



};

typedef std::vector<NtupleJet> NtupleJetCollection;

#endif
