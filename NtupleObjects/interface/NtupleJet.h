#ifndef DavisRunIITauTau_NtupleObjects_NtupleJet_h
#define DavisRunIITauTau_NtupleObjects_NtupleJet_h


// system include files
#include <memory>
#include <cassert>



// needed by ntuple Jets producer
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
  void fill_defaultBtagInfo(pat::Jet, std::string); /* theJet, bTagAlgoName */
  void fill_PUjetID(pat::Jet, std::string, double); /* theJet, DiscName, double CutMinimum */
  void fill_PFjetID(bool);
  void fill_JEC_uncertaintySFs(double, double); /* set the up, down JEC uncertainty scale factors, call after NtupleJet::fill is called */

  /* set the nominal, up, down JER  scale factors, genJet match, and the absolute resolution
   for JER call only after NtupleJet::fill is called */

  void fill_JER_SFs(double, double, double, LorentzVector, double); 


  /* adjust the pass/fail of the m_defaultBtagAlgorithm_isPassed variable based on bTag SFs used with the 
   promote-demote method,
   1st argument=1 means keep as (or promote to) btagged, argument = 0 means keep as (or demote to) untagged 
   2nd argument is 0 for nominal, +1 for btag systematic up, -1 for btag systematic down */

   void promoteDemoteBtagTightWP(int, int); 
   void promoteDemoteBtagMediumWP(int, int); 
   void promoteDemoteBtagLooseWP(int, int); 


  // helpers

  stringVec JEC_labels() ;     /* the available jec labels  */
  floatVec JEC_SFs() ;         /* the available jec SFs */
  float JEC(std::string);      /* return the JEC for available string assert if not available */
 
  stringVec BTAG_labels() ;      /* the available b-tag algorithm labels  */
  floatVec BTAGraw_scores() ;    /* the raw b-tag algorithm outputs - no SFs are applied here */
  float BTAGraw(std::string);    /* return the raw b-tag score for available string assert if not available */



  /* switch m_jet_p4 member between different jet scale/resolution variants */
  /* string can be fullyCorrected,  JECshiftedUp, JECshiftedDown, JERnomianl, JERup, JERdown */

  void Use4VectorVariant(std::string); 


  // getters
 


  LorentzVector jet_p4() const; /* should have all corrections applied */
  
  LorentzVector jet_p4_JECshiftedUp() const;   /* jet 4-vector with the JEC shifted up one sigma for MC */
  LorentzVector jet_p4_JECshiftedDown() const; /* jet 4-vector with the JEC shifted down one sigma for MC */
  
  /* note these include a random gaus smear for non-gen matched jets, and so will not always give the same
  result */

  LorentzVector jet_p4_JERnomianl() const;   /* jet 4-vector with the JER smeared (or shifted) for MC */
  LorentzVector jet_p4_JERup() const;        /* jet 4-vector with the JER smeared (or shifted) with +one sigma uncertainty for MC*/
  LorentzVector jet_p4_JERdown() const;      /* jet 4-vector with the JER smeared (or shifted) with -one sigma uncertainty for MC*/




  LorentzVector GENjet_p4() const; /* as embedded in slimmedJets */
  int GENjet_pdgId() const; /* as embedded in slimmedJets */

  double JEC_uncertaintySF_down() const; /* return sf to shift JEC 1 sigma down */
  double JEC_uncertaintySF_up() const;   /* return sf to shift JEC 1 sigma up */
  double JER_SF_nominal() const;         /* return sf to correct MC JER to DATA */
  double JER_SF_up() const;              /* return sf to correct MC JER to DATA with 1 sigma systematic shift up */ 
  double JER_SF_down() const;            /* return sf to correct MC JER to DATA with 1 sigma systematic shift down */ 
  double JER_resolution() const;         /* return the absolute resolution for a MC jet */  

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


  bool defaultBtagAlgorithmLooseWP_isPassed() const;
  bool defaultBtagAlgorithmLooseWPShiftUp_isPassed() const;
  bool defaultBtagAlgorithmLooseWPShiftDown_isPassed() const;


  bool defaultBtagAlgorithmMediumWP_isPassed() const;
  bool defaultBtagAlgorithmMediumWPShiftUp_isPassed() const;
  bool defaultBtagAlgorithmMediumWPShiftDown_isPassed() const;

  bool defaultBtagAlgorithmTightWP_isPassed() const;
  bool defaultBtagAlgorithmTightWPShiftUp_isPassed() const;
  bool defaultBtagAlgorithmTightWPShiftDown_isPassed() const;

  /* for easy use with cut strings */
  double pt() const; /* should have all corrections applied */
  double eta() const; /* should have all corrections applied */


private:

  LorentzVector m_jet_p4; /* this will hold any of the variants based on call Use4VectorVariant calls */
  LorentzVector m_jet_p4_fullyCorrected; /* full JEC corrected p4 -- our nominal jet 4-vector */
  LorentzVector m_jet_p4_JECshiftedUp;
  LorentzVector m_jet_p4_JECshiftedDown;
  LorentzVector m_jet_p4_JERnomianl;
  LorentzVector m_jet_p4_JERup;
  LorentzVector m_jet_p4_JERdown;

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

 
  bool m_defaultBtagAlgorithmLooseWP_isPassed;          /* pass-fail of default b-tag algo after btagSF applied */
  bool m_defaultBtagAlgorithmLooseWPShiftUp_isPassed;   /* pass-fail of default b-tag algo after btagSF applied, with btag sys. 1 sigma up shift   */
  bool m_defaultBtagAlgorithmLooseWPShiftDown_isPassed; /* pass-fail of default b-tag algo after btagSF applied, with btag sys. 1 sigma down shift */

  bool m_defaultBtagAlgorithmMediumWP_isPassed;          /* pass-fail of default b-tag algo after btagSF applied */
  bool m_defaultBtagAlgorithmMediumWPShiftUp_isPassed;   /* pass-fail of default b-tag algo after btagSF applied, with btag sys. 1 sigma up shift   */
  bool m_defaultBtagAlgorithmMediumWPShiftDown_isPassed; /* pass-fail of default b-tag algo after btagSF applied, with btag sys. 1 sigma down shift */

  bool m_defaultBtagAlgorithmTightWP_isPassed;          /* pass-fail of default b-tag algo after btagSF applied */
  bool m_defaultBtagAlgorithmTightWPShiftUp_isPassed;   /* pass-fail of default b-tag algo after btagSF applied, with btag sys. 1 sigma up shift   */
  bool m_defaultBtagAlgorithmTightWPShiftDown_isPassed; /* pass-fail of default b-tag algo after btagSF applied, with btag sys. 1 sigma down shift */




  double m_PU_jetIdRaw;                                 /* raw PU jet ID score */
  bool m_PU_jetIdPassed;                                /* pass/fail PU jet ID  */
  bool m_PF_jetIdPassed;                                /* pass/fail PF jet ID */


  /* JEC and JER scale factors 
     the jets we use at miniAOD have JEC corrections applied
     but not JER smearing/scaling (this is valid for 76X in which JER mods. onto mini-AOD are not recommended)
  */

  double m_JEC_uncertaintySF_up;
  double m_JEC_uncertaintySF_down;
  double m_JER_SF_nominal;
  double m_JER_SF_up;
  double m_JER_SF_down;
  double m_JER_resolution;




};

typedef std::vector<NtupleJet> NtupleJetCollection;

#endif
