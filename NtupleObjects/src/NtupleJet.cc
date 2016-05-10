#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "DavisRunIITauTau/External/interface/BtagSF.hh" /* causes problems if included in a .h file */

#include "TLorentzVector.h"
#include "TF1.h"
#include <math.h> 


NtupleJet::NtupleJet()
{
  m_jet_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_jet_p4_fullyCorrected.SetXYZT(NAN,NAN,NAN,NAN);
  m_jet_p4_JECshiftedUp.SetXYZT(NAN,NAN,NAN,NAN);
  m_jet_p4_JECshiftedDown.SetXYZT(NAN,NAN,NAN,NAN);
  m_jet_p4_JERnomianl.SetXYZT(NAN,NAN,NAN,NAN);
  m_jet_p4_JERup.SetXYZT(NAN,NAN,NAN,NAN);
  m_jet_p4_JERdown.SetXYZT(NAN,NAN,NAN,NAN);

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

  /* init these to 1.0 */
  m_JEC_uncertaintySF_up = 1.;
  m_JEC_uncertaintySF_down = 1.;
  m_JER_SF_nominal = 1.;
  m_JER_SF_up = 1.;
  m_JER_SF_down = 1.;
  m_JER_resolution = 1.;

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
    m_jet_p4 = aPatJet.p4(); /* this will be changed based on Use4VectorVariant calls */

    m_jet_p4_fullyCorrected = aPatJet.p4();  /* keep as a backup no matter what m_jet_p4 is set to */


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


/* set the up, down JEC uncertainty scale factors */
  void NtupleJet::fill_JEC_uncertaintySFs(double up_, double down_)
  {
    m_JEC_uncertaintySF_up = up_;
    m_JEC_uncertaintySF_down = down_;

    /* if this ever asserts it means you did not call NtupleJet::fill in order to init the 4-vector */
    assert(!isnan(m_jet_p4.pt()));

    m_jet_p4_JECshiftedUp = m_jet_p4;
    m_jet_p4_JECshiftedUp *= up_;

    m_jet_p4_JECshiftedDown = m_jet_p4;
    m_jet_p4_JECshiftedDown *= down_;    


    std::cout<<" jet with pT = "<<m_jet_p4.pt()<<" + JEC shift gives pT =  "<<m_jet_p4_JECshiftedUp.pt();
    std::cout<<" while - shift gives "<<m_jet_p4_JECshiftedDown.pt()<<"\n";


  }



/* set the nominal, up, down JER  scale factors */
/* see https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution#Smearing_procedures */

  void NtupleJet::fill_JER_SFs(double nominal_, double up_, double down_, LorentzVector genJet_, double resol_)
  {
    m_JER_SF_nominal = nominal_;
    m_JER_SF_up = up_;
    m_JER_SF_down = down_;
    m_JER_resolution = resol_;

    /* if this ever asserts it means you did not call NtupleJet::fill in order to init the 4-vector */
    assert(!isnan(m_jet_p4.pt()) && m_jet_p4.pt()>0.0);


    ///////////////////////////////////////////////
    // using hybrid method to scale/smear jets 
    ///////////////////////////////////////////////

    double pt_new_nominal = m_jet_p4.pt();
    double pt_new_up = m_jet_p4.pt();
    double pt_new_down = m_jet_p4.pt();

    ////////////////////////////////////////////////////////////////////////////
    ///// if have a genJet match use Scaling pT->max[0.,pTgen+SF*(pT–pTgen)]

    if( !isnan(genJet_.pt()) && genJet_.pt() > 0.0 )
    {

      pt_new_nominal = std::max(0., genJet_.pt() + m_JER_SF_nominal * (m_jet_p4.pt() - genJet_.pt()));
      pt_new_up = std::max(0., genJet_.pt() + m_JER_SF_up * (m_jet_p4.pt() - genJet_.pt()));
      pt_new_down = std::max(0., genJet_.pt() + m_JER_SF_down * (m_jet_p4.pt() - genJet_.pt()));

      std::cout<<" For a well-gen matched jet with pt = "<<m_jet_p4.pt()<<" ";
      std::cout<<" the new JER scaled pT is "<<pt_new_nominal<<" under a +1 sigma shift it is "<<pt_new_up;
      std::cout<<" and under a -1 sigma shift it is "<<pt_new_down<<" ";

    }

    ////////////////////////////////////////////////////////////////////////////
    ///// if don't have a genJet match randomly smear corrected reco jet pT using 
    ///// a Gaussian of the width √(SF^2-1) * sigma_MC_PT. 
    ///// This method only allows one to worsen the resolution (SF>1). 

    else
    {

      TF1 gausNOM("gausNOM","gaus",0.0,m_jet_p4.pt()*2.);
      TF1 gausUP("gausUP","gaus",0.0,m_jet_p4.pt()*2.);
      TF1 gausDN("gausDN","gaus",0.0,m_jet_p4.pt()*2.);

      gausNOM.SetParameter(0,1);
      gausUP.SetParameter(0,1);
      gausDN.SetParameter(0,1);

      gausNOM.SetParameter(1,m_jet_p4.pt());
      gausUP.SetParameter(1,m_jet_p4.pt());
      gausDN.SetParameter(1,m_jet_p4.pt());

      gausNOM.SetParameter(1,m_JER_resolution*sqrt(pow(m_JER_SF_nominal,2)-1));
      gausUP.SetParameter(2,m_JER_resolution*sqrt(pow(m_JER_SF_up,2)-1));
      gausDN.SetParameter(2,m_JER_resolution*sqrt(pow(m_JER_SF_down,2)-1));

      //std::cout<<" for pt of "<<m_jet_p4.pt()<<" get a width of "<<m_JER_resolution*sqrt(pow(m_JER_SF_nominal,2)-1)<<"\n";

      pt_new_nominal = std::max(0.,  gausNOM.GetRandom());
      pt_new_up = std::max(0., gausUP.GetRandom());
      pt_new_down = std::max(0., gausDN.GetRandom());


      std::cout<<" For a NON-gen matched jet with pt = "<<m_jet_p4.pt()<<" ";
      std::cout<<" the new JER scaled pT is "<<pt_new_nominal<<" under a +1 sigma shift it is "<<pt_new_up;
      std::cout<<" and under a -1 sigma shift it is "<<pt_new_down<<" ";


    }



    /* now fill the smeared 4-vectors */
  
  
    m_jet_p4_JERnomianl  = m_jet_p4;
    m_jet_p4_JERup       = m_jet_p4;
    m_jet_p4_JERdown     = m_jet_p4;


    m_jet_p4_JERnomianl  *=  (pt_new_nominal/m_jet_p4.pt());
    m_jet_p4_JERup       *=  (pt_new_up/m_jet_p4.pt());
    m_jet_p4_JERdown     *=  (pt_new_down/m_jet_p4.pt());

    std::cout<<" test nom, up, dn "<<m_jet_p4_JERnomianl.pt()<<" , "<<m_jet_p4_JERup.pt()<<" , "<<m_jet_p4_JERdown.pt()<<"\n";

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




  /* switch between different jet scale/resolution variants */
  /* string can be fullyCorrected,  JECshiftedUp, JECshiftedDown, JERnomianl, JERup, JERdown */

  void NtupleJet::Use4VectorVariant(std::string variant_)
  {
    assert(variant_ == "fullyCorrected" ||\
           variant_ == "JECshiftedUp" ||\
           variant_ == "JECshiftedDown" ||\
           variant_ == "JERnomianl" ||\
           variant_ == "JERup" ||\
           variant_ == "JERdown");
  
    if(variant_ == "fullyCorrected") m_jet_p4 = m_jet_p4_fullyCorrected;
    else if(variant_ == "JECshiftedUp") m_jet_p4 = m_jet_p4_JECshiftedUp;
    else if(variant_ == "JECshiftedDown") m_jet_p4 = m_jet_p4_JECshiftedDown;
    else if(variant_ == "JERnomianl") m_jet_p4 = m_jet_p4_JERnomianl;
    else if(variant_ == "JERup") m_jet_p4 = m_jet_p4_JERup;
    else if(variant_ == "JERdown") m_jet_p4 = m_jet_p4_JERdown;


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


  double NtupleJet::JEC_uncertaintySF_up() const { return m_JEC_uncertaintySF_up; }
  double NtupleJet::JEC_uncertaintySF_down() const { return m_JEC_uncertaintySF_down; }
  double NtupleJet::JER_SF_nominal() const { return m_JER_SF_nominal; }
  double NtupleJet::JER_SF_up() const { return m_JER_SF_up; }
  double NtupleJet::JER_SF_down() const { return m_JER_SF_down; }
  double NtupleJet::JER_resolution() const {return m_JER_resolution; }

  LorentzVector NtupleJet::jet_p4_JECshiftedUp() const { return m_jet_p4_JECshiftedUp; }
  LorentzVector NtupleJet::jet_p4_JECshiftedDown() const { return m_jet_p4_JECshiftedDown; }
  LorentzVector NtupleJet::jet_p4_JERnomianl() const { return m_jet_p4_JERnomianl; }
  LorentzVector NtupleJet::jet_p4_JERup() const { return m_jet_p4_JERup; }
  LorentzVector NtupleJet::jet_p4_JERdown() const { return m_jet_p4_JERdown; }
