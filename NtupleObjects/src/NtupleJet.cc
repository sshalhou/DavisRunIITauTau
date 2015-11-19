#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "DavisRunIITauTau/External/interface/BtagSF.hh" /* causes problems if included in a .h file */

#include "TLorentzVector.h"
#include <math.h> 

NtupleJet::NtupleJet()
{

  m_jet_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_GENjet_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_GENjet_pdgId = -999;
  m_PARTON_flavour = -999;
  m_HADRON_flavour = -999;
  m_jet_vertex_x = NAN;
  m_jet_vertex_y = NAN;
  m_jet_vertex_z = NAN;
  m_isPFJet = -999; 
  m_neutralHadronEnergyFraction = NAN;
  m_neutralEmEnergyFraction = NAN;
  m_chargedHadronEnergyFraction = NAN;
  m_muonEnergyFraction = NAN;
  m_chargedEmEnergyFraction = NAN;
  m_chargedMultiplicityPlusNeutralMultiplicity = NAN;
  m_chargedMultiplicity = NAN;
  m_neutralMultiplicity = NAN;
  m_defaultBtagAlgorithm_Name = "NULL";
  m_defaultBtagAlgorithm_RawScore = NAN;
  m_defaultBtagAlgorithm_isPassed = 0;
  m_PU_jetIdRaw = NAN;
  m_PU_jetIdPassed = 0;
  m_PF_jetIdPassed = 0;



}


// filler 

  void NtupleJet::fill_PFjetID(bool passFail)
  {
    m_PF_jetIdPassed = passFail;
  }


  void NtupleJet::fill_PUjetID(pat::Jet theJet, std::string DiscName, double CutMinimum)
  {

    m_PU_jetIdRaw = theJet.userFloat(DiscName);

    if(m_PU_jetIdRaw > CutMinimum) m_PU_jetIdPassed = 1;
    else m_PU_jetIdPassed = 0;

  }

  void NtupleJet::fill_defaultBtagInfo(pat::Jet theJet, std::string bTagAlgoName, 
                            bool applySF, unsigned int SFseed, bool isRealData)
  {

    m_defaultBtagAlgorithm_Name = bTagAlgoName;
    m_defaultBtagAlgorithm_RawScore = theJet.bDiscriminator(bTagAlgoName);

    BtagSF btagSFtool(SFseed);

    m_defaultBtagAlgorithm_isPassed = btagSFtool.isbtagged(
    theJet.pt(), theJet.eta(),
    m_defaultBtagAlgorithm_RawScore,
    theJet.partonFlavour(),
    isRealData,
    0,0,1);



  }


  void NtupleJet::fill(pat::Jet aPatJet)
  {

    m_jet_p4 = aPatJet.p4();
    if(aPatJet.genJet()) m_GENjet_p4 = aPatJet.genJet()->p4();
    if(aPatJet.genJet()) m_GENjet_pdgId = aPatJet.genJet()->pdgId();

    m_PARTON_flavour = aPatJet.partonFlavour();
    m_HADRON_flavour = aPatJet.hadronFlavour();
    m_jet_vertex_x = aPatJet.vertex().X();
    m_jet_vertex_y = aPatJet.vertex().Y();
    m_jet_vertex_z = aPatJet.vertex().Z();
    m_isPFJet = aPatJet.isPFJet();
    m_neutralHadronEnergyFraction = aPatJet.neutralHadronEnergyFraction();
    m_neutralEmEnergyFraction = aPatJet.neutralEmEnergyFraction();
    m_chargedHadronEnergyFraction = aPatJet.chargedHadronEnergyFraction();
    m_muonEnergyFraction = aPatJet.muonEnergyFraction();
    m_chargedEmEnergyFraction = aPatJet.chargedEmEnergyFraction();
    m_chargedMultiplicityPlusNeutralMultiplicity = aPatJet.chargedMultiplicity() + aPatJet.neutralMultiplicity();
    m_chargedMultiplicity = aPatJet.chargedMultiplicity();
    m_neutralMultiplicity = aPatJet.neutralMultiplicity();




  /* store the JEC label-SF pairs */

    for(std::size_t j=0; j<aPatJet.availableJECLevels().size(); ++j)
    {
      std::string current_string = aPatJet.availableJECLevels().at(j);
      float current_float = aPatJet.jecFactor(current_string);
      std::pair<std::string, float> aJEC(current_string,current_float);
      m_JetEnergyCorrection.push_back(aJEC);
    }

  /* store the BTAG label-rawOutput pairs */

    for(std::size_t b=0; b<aPatJet.getPairDiscri().size(); ++b)
    {
      std::string current_string = aPatJet.getPairDiscri().at(b).first;
      float current_float = aPatJet.bDiscriminator(current_string);
      std::pair<std::string, float> aBTAGALGOpair(current_string,current_float);
      m_BTAG.push_back(aBTAGALGOpair);
    }





  }





// helpers


///////////////////////////
// JEC related helpers 
////////////////////////////


////////////////
// return all labels for JEC
////////////////

  stringVec NtupleJet::JEC_labels()  
  { 
    stringVec m_JEC_labels;
    for(std::size_t x = 0; x < m_JetEnergyCorrection.size();++x) 
    { 
      m_JEC_labels.push_back(m_JetEnergyCorrection.at(x).first);
    }  

    return m_JEC_labels;
  }

///////////
// return all SFs for JEC
///////////

  floatVec NtupleJet::JEC_SFs()  
  {
    floatVec m_JEC_SFs;
    for(std::size_t x = 0; x < m_JetEnergyCorrection.size();++x) 
    {
      m_JEC_SFs.push_back(m_JetEnergyCorrection.at(x).second);
    }
    return m_JEC_SFs;
  }

///////////////
// return a given JEC SF for provided label
// asserts if label is unknown
///////////////

  float NtupleJet::JEC(std::string label_)
  {
    float returnValue = NAN;
    for(std::size_t x = 0; x < m_JetEnergyCorrection.size();++x) 
    { 
      if(m_JetEnergyCorrection.at(x).first == label_) returnValue = m_JetEnergyCorrection.at(x).second;

    }

    assert(isnan(returnValue)==0);
    return returnValue;
  }


///////////////////////////
// BTAG related helpers 
////////////////////////////


/////////////
// return all labels for BTAGs 
/////////////

  stringVec NtupleJet::BTAG_labels()  
  { 
    stringVec m_BTAG_labels;
    for(std::size_t x = 0; x < m_BTAG.size();++x) 
    { 
      m_BTAG_labels.push_back(m_BTAG.at(x).first);
    }  

    return m_BTAG_labels;
  }

/////////////
// return all raw output for avaliable BTAG algorithms
/////////////

  floatVec NtupleJet::BTAGraw_scores()  
  {
    floatVec m_BTAGraw_scores;
    for(std::size_t x = 0; x < m_BTAG.size();++x) 
    {
      m_BTAGraw_scores.push_back(m_BTAG.at(x).second);
    }
    return m_BTAGraw_scores;
  }

/////////////
// return a given BTAG algorithm's raw output for provided label
// asserts if label is unknown
/////////////

  float NtupleJet::BTAGraw(std::string label_)
  {
    float returnValue = NAN;
    for(std::size_t x = 0; x < m_BTAG.size();++x) 
    { 
      if(m_BTAG.at(x).first == label_) returnValue = m_BTAG.at(x).second;

    }

    assert(isnan(returnValue)==0);
    return returnValue;
  }




// getters 
 
  double NtupleJet::pt() const {return m_jet_p4.pt();}
  double NtupleJet::eta() const {return m_jet_p4.eta();}


  LorentzVector NtupleJet::jet_p4() const { return m_jet_p4; }
  LorentzVector NtupleJet::GENjet_p4() const { return m_GENjet_p4; }
  int NtupleJet::GENjet_pdgId() const { return m_GENjet_pdgId; }
  int NtupleJet::PARTON_flavour() const { return m_PARTON_flavour; }
  int NtupleJet::HADRON_flavour() const { return m_HADRON_flavour; }
  float NtupleJet::jet_vertex_x() const { return m_jet_vertex_x; }
  float NtupleJet::jet_vertex_y() const { return m_jet_vertex_y; }
  float NtupleJet::jet_vertex_z() const { return m_jet_vertex_z; }
  int NtupleJet::isPFJet() const { return m_isPFJet; }
 
  /* we will access the PF jet ID relevant info using easy to decode names */
  double NtupleJet::neutralHadronEnergyFraction() const { return m_neutralHadronEnergyFraction ; }
  double NtupleJet::neutralEmEnergyFraction() const { return m_neutralEmEnergyFraction ; }
  double NtupleJet::chargedHadronEnergyFraction() const { return m_chargedHadronEnergyFraction; } 
  double NtupleJet::muonEnergyFraction() const { return m_muonEnergyFraction; } 
  double NtupleJet::chargedEmEnergyFraction() const { return m_chargedEmEnergyFraction; } 
  double NtupleJet::chargedMultiplicityPlusNeutralMultiplicity() const { return m_chargedMultiplicityPlusNeutralMultiplicity; } 
  double NtupleJet::chargedMultiplicity() const { return m_chargedMultiplicity; } 
  double NtupleJet::neutralMultiplicity() const { return m_neutralMultiplicity; }

  /* we will also access the PF jet ID relevant info using standard names */
  double NtupleJet::NHF() const { return m_neutralHadronEnergyFraction; } 
  double NtupleJet::NEMF() const { return m_neutralEmEnergyFraction; } 
  double NtupleJet::CHF() const { return m_chargedHadronEnergyFraction; } 
  double NtupleJet::MUF() const { return m_muonEnergyFraction; } 
  double NtupleJet::CEMF() const { return m_chargedEmEnergyFraction; } 
  double NtupleJet::NumConst() const { return m_chargedMultiplicityPlusNeutralMultiplicity; } 
  double NtupleJet::CHM() const { return m_chargedMultiplicity; } 
  double NtupleJet::NumNeutralParticle() const {return m_neutralMultiplicity; }

  std::string NtupleJet::defaultBtagAlgorithm_Name() const { return m_defaultBtagAlgorithm_Name; }
  double NtupleJet::defaultBtagAlgorithm_RawScore() const { return m_defaultBtagAlgorithm_RawScore; }
  bool NtupleJet::defaultBtagAlgorithm_isPassed() const { return m_defaultBtagAlgorithm_isPassed; }
  double NtupleJet::PU_jetIdRaw() const { return m_PU_jetIdRaw; }
  bool NtupleJet::PU_jetIdPassed() const { return m_PU_jetIdPassed; }
  bool NtupleJet::PF_jetIdPassed() const { return m_PF_jetIdPassed; }



