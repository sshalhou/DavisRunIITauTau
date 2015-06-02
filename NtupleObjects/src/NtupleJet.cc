#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "TLorentzVector.h"
#include <math.h> 

NtupleJet::NtupleJet()
{

  m_jet_p4.SetXYZT(NAN,NAN,NAN,NAN);
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





  //m_PU_jetID = NAN;
  //m_PF_jetID = NAN;
  //m_BTAG_discriminant = NAN;
  //m_BTAG_pass = -999;


}


// filler 

  void NtupleJet::fill(pat::Jet aPatJet)
  {

    m_jet_p4 = aPatJet.p4();
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




  /* store the JEC label-SF pairs */

    for(std::size_t j=0; j<aPatJet.availableJECLevels().size(); ++j)
    {
      std::string current_string = aPatJet.availableJECLevels().at(j);
      float current_float = aPatJet.jecFactor(current_string);
      std::pair<std::string, float> aJEC(current_string,current_float);
      m_JetEnergyCorrection.push_back(aJEC);
    }



    // m_gen_pdgId = genPart.pdgId();
    // m_gen_status = genPart.status();
    // m_gen_p4 = genPart.p4();


  }



    //   std::cout<<"jet [pt, vertex_z, hadFlav, partFlav, (jecLabel, jecValue), (b-tag, value)] = ["<<slimmedJets->at(i).p4()<<" , ";
    //   std::cout<<slimmedJets->at(i).vertex().Z()<<" , ";
    //   std::cout<<slimmedJets->at(i).hadronFlavour()<<" , ";
    //   std::cout<<slimmedJets->at(i).partonFlavour()<<" , ";
     
    //   for(std::size_t j=0; j<slimmedJets->at(i).availableJECLevels().size(); ++j)
    //   {
    //     std::cout<<" (label = "<<slimmedJets->at(i).availableJECLevels().at(j)<<" ";
    //     std::cout<<" value = "<<slimmedJets->at(i).jecFactor(slimmedJets->at(i).availableJECLevels().at(j))<<")";

    //   }

    //   std::cout<<" LABELS SIZE "<<slimmedJets->at(i).tagInfoLabels().size()<<"\n";
    //   std::cout<<" PAIR VECTOR SIZE "<<slimmedJets->at(i).getPairDiscri().size()<<"\n";

    //   for(std::size_t b =0; b<slimmedJets->at(i).getPairDiscri().size(); ++b)
    //   {

    //     std::cout<<" (btag = "<<slimmedJets->at(i).getPairDiscri().at(b).first<<" ";
    //     std::cout<<" (score = "<<slimmedJets->at(i).bDiscriminator(slimmedJets->at(i).getPairDiscri().at(b).first)<<")";


    //   }

    //   std::cout<<" combinedInclusiveSecondaryVertexV2BJetTags "<<slimmedJets->at(i).bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags")<<"\n";

    //   std::cout<<" PU JET ID  = "<<slimmedJets->at(i).userFloat("pileupJetId:fullDiscriminant")<<"\n";        
    //   std::cout<<" PF JET ID  = "<<slimmedJets->at(i).userFloat("pileupJetId:fullDiscriminant")<<"\n";        


    //   // std::cout<<slimmedJets->at(i).jecFactor("Uncorrected")<<" , ";
    //   // std::cout<<slimmedJets->at(i).jecFactor("L1FastJet")<<" , ";
    //   // std::cout<<slimmedJets->at(i).jecFactor("L2")<<" , ";
    //   // std::cout<<slimmedJets->at(i).jecFactor("L3")<<" , ";
    //   // std::cout<<slimmedJets->at(i).jecFactor("Residual")<<" , ";
    //   // std::cout<<slimmedJets->at(i).jecFactor("x");
    //   std::cout<<" ] \n";

    // }    




// getters 
 

  LorentzVector NtupleJet::jet_p4() const { return m_jet_p4; }
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

  /* we will also access the PF jet ID relevant info using standard names */
  double NtupleJet::NHF() const { return m_neutralHadronEnergyFraction; } 
  double NtupleJet::NEMF() const { return m_neutralEmEnergyFraction; } 
  double NtupleJet::CHF() const { return m_chargedHadronEnergyFraction; } 
  double NtupleJet::MUF() const { return m_muonEnergyFraction; } 
  double NtupleJet::CEMF() const { return m_chargedEmEnergyFraction; } 
  double NtupleJet::NumConst() const { return m_chargedMultiplicityPlusNeutralMultiplicity; } 
  double NtupleJet::CHM() const { return m_chargedMultiplicity; } 


  /* return available JEC labels and scale factors */

  // return all labels for JEC
  stringVec NtupleJet::JEC_labels()  
  { 
    stringVec m_JEC_labels;
    for(std::size_t x = 0; x < m_JetEnergyCorrection.size();++x) 
    { 
      m_JEC_labels.push_back(m_JetEnergyCorrection.at(x).first);
    }  

    return m_JEC_labels;
  }

  // return all SFs for JEC
  floatVec NtupleJet::JEC_SFs()  
  {
    floatVec m_JEC_SFs;
    for(std::size_t x = 0; x < m_JetEnergyCorrection.size();++x) 
    {
      m_JEC_SFs.push_back(m_JetEnergyCorrection.at(x).second);
    }
    return m_JEC_SFs;
  }

  // return a given JEC SF for provided label
  // asserts if label is unknown

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



  double NtupleJet::PU_jetID() const { return m_PU_jetID; }
  double NtupleJet::PF_jetID() const { return m_PF_jetID; }
  double NtupleJet::BTAG_discriminant() const { return m_BTAG_discriminant; }
  int NtupleJet::BTAG_pass() const { return m_BTAG_pass; }
 


