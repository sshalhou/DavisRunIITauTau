#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "TLorentzVector.h"

NtupleLepton::NtupleLepton()
{
  m_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_gen_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_genMother_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_leptonType = -999;
  m_charge = -999;
  m_PFpdgId = -999;
  m_GENpdgId = -999;
  m_GENMOTHERpdgId = -999;
  m_dz = NAN;
  m_dxy = NAN;
  m_EffectiveArea = NAN;
  m_raw_electronMVA = NAN;
  m_passFail_electronMVA = NAN; 
  m_TauEsVariant = NAN; 
  m_IP = NAN;                   
  m_IPerror = NAN;              
  m_PUchargedHadronIso = NAN;   
  m_chargedHadronIso = NAN;     
  m_neutralHadronIso = NAN;     
  m_photonIso = NAN;  
  m_DepositR03ECal = NAN;    
  m_DepositR03Hcal = NAN;    
  m_DepositR03TrackerOfficial = NAN;   
  m_isGlobalMuon = NAN;    
  m_isGoodGlobalMuon = NAN;    
  m_passesMediumMuonId = NAN;    
  m_isLooseMuon = NAN;   
  m_isPFMuon = NAN;    
  m_isSoftMuon = NAN;    
  m_isTightMuon = NAN;   
  m_isTrackerMuon = NAN;   
  m_muonCombQualChi2LocalPosition = NAN;   
  m_muonCombQualTrkKink = NAN;   
  m_muonGlobalTrackNormChi2 = NAN;   
  m_muonInnerTrkValidFraction = NAN;   
  m_muonSegmentCompatibility = NAN;    
  m_SuperClusterEta = NAN;
  m_hadronicOverEm = NAN;
  m_isEB = NAN;
  m_isEBEEGap = NAN;
  m_isEBEtaGap = NAN;
  m_isEBPhiGap = NAN;
  m_isEE = NAN;
  m_isEEDeeGap = NAN;
  m_isEERingGap = NAN;
  m_deltaEtaSuperClusterTrackAtVtx = NAN;
  m_deltaPhiSuperClusterTrackAtVtx = NAN;
  m_sigmaEtaEta = NAN;
  m_sigmaIetaIeta = NAN;
  m_sigmaIphiIphi = NAN;
  m_numberOfMissingInnerHits = NAN;
  m_numberOfMissingOuterHits = NAN;
  m_numberOfTrackHits = NAN;
  m_passConversionVeto = NAN;

  m_genJet_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_numStrips = NAN;
  m_numHadrons  = NAN;

}

// helpers




///////////////////////////
// tauID related helpers 
////////////////////////////


////////////////
// return all labels for tauID that were calculated for the event
////////////////

  stringVec NtupleLepton::tauID_Labels()  
  { 
    stringVec m_tauID_labels;
    for(std::size_t x = 0; x < m_tauIDs.size();++x) 
    { 
      m_tauID_labels.push_back(m_tauIDs.at(x).first);
    }  

    return m_tauID_labels;
  }

///////////
// return all values for computed tauIDs
///////////

  floatVec NtupleLepton::tauID_Values()  
  {
    floatVec m_tauID_values;
    for(std::size_t x = 0; x < m_tauIDs.size();++x) 
    {
      m_tauID_values.push_back(m_tauIDs.at(x).second);
    }
    return m_tauID_values;
  }

///////////////
// return a given tauID value for provided label
// assert that it is a known label
///////////////

  float NtupleLepton::tauID(std::string label_) const
  {
    float returnValue = NAN;
    for(std::size_t x = 0; x < m_tauIDs.size();++x) 
    { 
      if(m_tauIDs.at(x).first == label_) returnValue = m_tauIDs.at(x).second;

    }

    assert(isnan(returnValue)==0);
    return returnValue;
  }





///////////////////////////
// relativeIsol related helpers 
////////////////////////////


////////////////
// return all labels for relativeIsols that were calculated for the event
////////////////

  stringVec NtupleLepton::relativeIsol_Labels()  
  { 
    stringVec m_ISOL_labels;
    for(std::size_t x = 0; x < m_relativeIsolations.size();++x) 
    { 
      m_ISOL_labels.push_back(m_relativeIsolations.at(x).first);
    }  

    return m_ISOL_labels;
  }

///////////
// return all values for computed relativeIsols
///////////

  floatVec NtupleLepton::relativeIsol_Values()  
  {
    floatVec m_ISOL_values;
    for(std::size_t x = 0; x < m_relativeIsolations.size();++x) 
    {
      m_ISOL_values.push_back(m_relativeIsolations.at(x).second);
    }
    return m_ISOL_values;
  }

///////////////
// return a given relativeIsol value for provided label
// assert that it is a known label
///////////////

  float NtupleLepton::relativeIsol(std::string label_) const
  {
    float returnValue = NAN;
    for(std::size_t x = 0; x < m_relativeIsolations.size();++x) 
    { 
      if(m_relativeIsolations.at(x).first == label_) returnValue = m_relativeIsolations.at(x).second;

    }

    assert(isnan(returnValue)==0);
    return returnValue;
  }



///////////////////////////
// Rho related helpers 
////////////////////////////


////////////////
// return all labels for Rhos that were calculated for the event
////////////////

  stringVec NtupleLepton::rho_Labels()  
  { 
    stringVec m_RHO_labels;
    for(std::size_t x = 0; x < m_rhos.size();++x) 
    { 
      m_RHO_labels.push_back(m_rhos.at(x).first);
    }  

    return m_RHO_labels;
  }

///////////
// return all values for computed rhos
///////////

  floatVec NtupleLepton::rho_Values()  
  {
    floatVec m_RHO_values;
    for(std::size_t x = 0; x < m_rhos.size();++x) 
    {
      m_RHO_values.push_back(m_rhos.at(x).second);
    }
    return m_RHO_values;
  }

///////////////
// return a given rho value for provided label
// assert that it is a known label
///////////////

  float NtupleLepton::rho(std::string label_) const
  {
    float returnValue = NAN;
    for(std::size_t x = 0; x < m_rhos.size();++x) 
    { 
      if(m_rhos.at(x).first == label_) returnValue = m_rhos.at(x).second;

    }

    assert(isnan(returnValue)==0);
    return returnValue;
  }




///////////////////////////
// HLTPath related helpers 
////////////////////////////


////////////////
// return all labels for HLTPaths that were accepted for the event
////////////////

  stringVec NtupleLepton::HLTAcceptedPath_Labels()  
  { 
    stringVec m_HLT_labels;
    for(std::size_t x = 0; x < m_HLTPaths.size();++x) 
    { 
      m_HLT_labels.push_back(m_HLTPaths.at(x).first);
    }  

    return m_HLT_labels;
  }

///////////
// return all preScales for accepted HLTpaths
///////////

  floatVec NtupleLepton::HLTAcceptedPath_preScales()  
  {
    floatVec m_HLT_preScales;
    for(std::size_t x = 0; x < m_HLTPaths.size();++x) 
    {
      m_HLT_preScales.push_back(m_HLTPaths.at(x).second);
    }
    return m_HLT_preScales;
  }

///////////////
// return a given HLT preScale for provided label
// in general anything other than 0 means accepted 
// for un-prescaled triggers it will return 1.0
// retun '0 meaning not accepted' if label is unknown
///////////////

  float NtupleLepton::HLTpath(std::string label_) const
  {
    float returnValue = 0;
    for(std::size_t x = 0; x < m_HLTPaths.size();++x) 
    { 
      if(m_HLTPaths.at(x).first == label_) returnValue = m_HLTPaths.at(x).second;

    }

    return returnValue;
  }




////////////////////////////////////////////////////////////////////
// print some of the member data - useful for debugging
////////////////////////////////////////////////////////////////////
void NtupleLepton::printLEP()
{
  std::string type_print = "UNKNOWN_TYPE";
  if (m_leptonType == TupleLeptonTypes::anElectron) type_print = "Electron";
  else if (m_leptonType == TupleLeptonTypes::aMuon) type_print = "Muon";
  else if (m_leptonType == TupleLeptonTypes::aTau) type_print = "Tau";



  std::cout<<"<LEPPRINT "<<type_print<<"> ------------------> START: printing lepton \n";
  std::cout<<"<LEPPRINT "<<type_print<<"> leptonType is "<<m_leptonType<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> charge is "<<m_charge<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> PF pdgId is "<<m_PFpdgId<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> reco Pt,Eta,Phi,M "<<m_p4.Pt()<<" , "<<m_p4.Eta()<<" , "<<m_p4.Phi()<<" , "<<m_p4.M()<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> GEN pdgId is "<<m_GENpdgId<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> gen Pt,Eta,Phi,M "<<m_gen_p4.Pt()<<" , "<<m_gen_p4.Eta()<<" , "<<m_gen_p4.Phi()<<" , "<<m_gen_p4.M()<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> GENMOTHER pdgId is "<<m_GENMOTHERpdgId<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> gen mother Pt,Eta,Phi,M "<<m_genMother_p4.Pt()<<" , "<<m_genMother_p4.Eta()<<" , "<<m_genMother_p4.Phi()<<" , "<<m_genMother_p4.M()<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> EffectiveArea "<<m_EffectiveArea<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> dz "<<m_dz<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> dxy "<<m_dxy<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> known rho types and values : ";
    for(std::size_t i=0;i<m_rhos.size();++i) std::cout<<"[ "<<m_rhos[i].first<<" = "<<m_rhos[i].second<<" ] ";
    std::cout<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> known relIso types and values : ";
    for(std::size_t i=0;i<m_relativeIsolations.size();++i) std::cout<<"[ "<<m_relativeIsolations[i].first<<" = "<<m_relativeIsolations[i].second<<" ] ";
    std::cout<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> HLT ACCEPTED PATHS and PreScales : ";
    for(std::size_t i=0;i<m_HLTPaths.size();++i) std::cout<<"[ "<<m_HLTPaths[i].first<<" = "<<m_HLTPaths[i].second<<" ] ";
    std::cout<<"\n";
 
  std::cout<<"<LEPPRINT "<<type_print<<"> ELECTRON MVA RAW "<<m_raw_electronMVA<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> ELECTRON MVA PASSFAIL "<<m_passFail_electronMVA<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> TauEsVariant "<<m_TauEsVariant<<"\n";

std::cout<<"<LEPPRINT "<<type_print<<"> IP : " << m_IP << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> IPerror : " << m_IPerror << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> PUchargedHadronIso : " << m_PUchargedHadronIso << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> chargedHadronIso : " << m_chargedHadronIso << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> neutralHadronIso : " << m_neutralHadronIso << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> photonIso : " << m_photonIso << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> DepositR03ECal : " << m_DepositR03ECal << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> DepositR03Hcal : " << m_DepositR03Hcal << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> DepositR03TrackerOfficial : " << m_DepositR03TrackerOfficial << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isGlobalMuon : " << m_isGlobalMuon << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isGoodGlobalMuon : " << m_isGoodGlobalMuon << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> passesMediumMuonId : " << m_passesMediumMuonId << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isLooseMuon : " << m_isLooseMuon << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isPFMuon : " << m_isPFMuon << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isSoftMuon : " << m_isSoftMuon << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isTightMuon : " << m_isTightMuon << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isTrackerMuon : " << m_isTrackerMuon << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> muonCombQualChi2LocalPosition : " << m_muonCombQualChi2LocalPosition << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> muonCombQualTrkKink : " << m_muonCombQualTrkKink << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> muonGlobalTrackNormChi2 : " << m_muonGlobalTrackNormChi2 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> muonInnerTrkValidFraction : " << m_muonInnerTrkValidFraction << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> muonSegmentCompatibility : " << m_muonSegmentCompatibility << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> SuperClusterEta : " << m_SuperClusterEta << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> hadronicOverEm : " << m_hadronicOverEm << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isEB : " << m_isEB << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isEBEEGap : " << m_isEBEEGap << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isEBEtaGap : " << m_isEBEtaGap << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isEBPhiGap : " << m_isEBPhiGap << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isEE : " << m_isEE << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isEEDeeGap : " << m_isEEDeeGap << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> isEERingGap : " << m_isEERingGap << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> deltaEtaSuperClusterTrackAtVtx : " << m_deltaEtaSuperClusterTrackAtVtx << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> deltaPhiSuperClusterTrackAtVtx : " << m_deltaPhiSuperClusterTrackAtVtx << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> sigmaEtaEta : " << m_sigmaEtaEta << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> sigmaIetaIeta : " << m_sigmaIetaIeta << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> sigmaIphiIphi : " << m_sigmaIphiIphi << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> numberOfMissingInnerHits : " << m_numberOfMissingInnerHits << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> numberOfMissingOuterHits : " << m_numberOfMissingOuterHits << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> numberOfTrackHits : " << m_numberOfTrackHits << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> passConversionVeto : " << m_passConversionVeto << std::endl;

std::cout<<"<LEPPRINT "<<type_print<<"> known tauID types and values : ";
  for(std::size_t i=0;i<m_tauIDs.size();++i) std::cout<<"[ "<<m_tauIDs[i].first<<" = "<<m_tauIDs[i].second<<" ] ";
  std::cout<<"\n";


std::cout<<"<LEPPRINT "<<type_print<<"> num strips : " << m_numStrips << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> num hadrons : " << m_numHadrons << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> genJet p4 pt :  " << m_genJet_p4.pt() << std::endl;

  std::cout<<" END: printing lepton <------------------\n";

}


////////////////////////////////////////////////////////////////////
// Parse the userFloat labels and values into the proper member data
////////////////////////////////////////////////////////////////////
void NtupleLepton::userFloatVectorParser(stringVec & labels_,floatVec & values_)
{
  for(std::size_t i = 0; i<labels_.size(); ++i)
  {

    if(labels_[i].find("AcceptWithPreScale_")==0) 
    {  
      /* store the HLT path label-preScale pairs */
      std::string x = "AcceptWithPreScale_";
      std::string current_string = labels_[i].erase(0,x.length());
      float current_float = values_[i];
      std::pair<std::string, float> aPathPreScalePair(current_string,current_float);
      m_HLTPaths.push_back(aPathPreScalePair);
    }
    else if(labels_[i]=="EffectiveArea")  m_EffectiveArea = values_[i];
    else if(labels_[i]=="dxy")  m_dxy = values_[i];
    else if(labels_[i]=="dz")  m_dz = values_[i];
    else if (labels_[i].find("rho_")==0)
    {
      /* store the rho label-value pairs */
      std::string x = "rho_";
      std::string current_string = labels_[i].erase(0,x.length());
      float current_float = values_[i];
      std::pair<std::string, float> currentPair(current_string,current_float);
      m_rhos.push_back(currentPair);
    }
    else if (labels_[i].find("relativeIsol_")==0)
    {
      /* store the relIso label-value pairs */
      std::string x = "relativeIsol_";
      std::string current_string = labels_[i].erase(0,x.length());
      float current_float = values_[i];
      std::pair<std::string, float> currentPair(current_string,current_float);
      m_relativeIsolations.push_back(currentPair);        
    }
    else if (labels_[i].find("tauID_")==0)
    {
      /* store the rho label-value pairs */
      std::string x = "tauID_";
      std::string current_string = labels_[i].erase(0,x.length());
      float current_float = values_[i];
      std::pair<std::string, float> currentPair(current_string,current_float);
      m_tauIDs.push_back(currentPair);        
    }
    else if(labels_[i]=="MVA_NonTrigPhys14") {m_raw_electronMVA = values_[i];}  
    else if(labels_[i]=="PASS_MVA_NonTrigPhys14") {m_passFail_electronMVA = values_[i];}  
    else if(labels_[i]=="TauEsVariant") {m_TauEsVariant = values_[i];}      
    else if(labels_[i]=="IP") {m_IP = values_[i];}      
    else if(labels_[i]=="IPerror") { m_IPerror = values_[i];}      
    else if(labels_[i]=="PUchargedHadronIso") { m_PUchargedHadronIso = values_[i];}      
    else if(labels_[i]=="chargedHadronIso") { m_chargedHadronIso = values_[i];}      
    else if(labels_[i]=="neutralHadronIso") { m_neutralHadronIso = values_[i];}      
    else if(labels_[i]=="photonIso") {m_photonIso = values_[i];}      
    else if(labels_[i]=="DepositR03ECal") {m_DepositR03ECal = values_[i];}
    else if(labels_[i]=="DepositR03Hcal") {m_DepositR03Hcal = values_[i];}
    else if(labels_[i]=="DepositR03TrackerOfficial") {m_DepositR03TrackerOfficial = values_[i];}
    else if(labels_[i]=="isGlobalMuon") {m_isGlobalMuon = values_[i];}
    else if(labels_[i]=="isGoodGlobalMuon") {m_isGoodGlobalMuon = values_[i];}
    else if(labels_[i]=="passesMediumMuonId") {m_passesMediumMuonId = values_[i];}
    else if(labels_[i]=="isLooseMuon") {m_isLooseMuon = values_[i];}
    else if(labels_[i]=="isPFMuon") {m_isPFMuon = values_[i];}
    else if(labels_[i]=="isSoftMuon") {m_isSoftMuon = values_[i];}
    else if(labels_[i]=="isTightMuon") {m_isTightMuon = values_[i];}
    else if(labels_[i]=="isTrackerMuon") {m_isTrackerMuon = values_[i];}
    else if(labels_[i]=="muonCombQualChi2LocalPosition") {m_muonCombQualChi2LocalPosition = values_[i];}
    else if(labels_[i]=="muonCombQualTrkKink") {m_muonCombQualTrkKink = values_[i];}
    else if(labels_[i]=="muonGlobalTrackNormChi2") {m_muonGlobalTrackNormChi2 = values_[i];}
    else if(labels_[i]=="muonInnerTrkValidFraction") {m_muonInnerTrkValidFraction = values_[i];}
    else if(labels_[i]=="muonSegmentCompatibility") {m_muonSegmentCompatibility = values_[i];}
    else if(labels_[i]=="SuperClusterEta") {m_SuperClusterEta = values_[i];}
    else if(labels_[i]=="hadronicOverEm") {m_hadronicOverEm = values_[i];}
    else if(labels_[i]=="isEB") {m_isEB = values_[i];}
    else if(labels_[i]=="isEBEEGap") {m_isEBEEGap = values_[i];}
    else if(labels_[i]=="isEBEtaGap") {m_isEBEtaGap = values_[i];}
    else if(labels_[i]=="isEBPhiGap") {m_isEBPhiGap = values_[i];}
    else if(labels_[i]=="isEE") {m_isEE = values_[i];}
    else if(labels_[i]=="isEEDeeGap") {m_isEEDeeGap = values_[i];}
    else if(labels_[i]=="isEERingGap") {m_isEERingGap = values_[i];}
    else if(labels_[i]=="deltaEtaSuperClusterTrackAtVtx") {m_deltaEtaSuperClusterTrackAtVtx = values_[i];}
    else if(labels_[i]=="deltaPhiSuperClusterTrackAtVtx") {m_deltaPhiSuperClusterTrackAtVtx = values_[i];}
    else if(labels_[i]=="sigmaEtaEta") {m_sigmaEtaEta = values_[i];}
    else if(labels_[i]=="sigmaIetaIeta") {m_sigmaIetaIeta = values_[i];}
    else if(labels_[i]=="sigmaIphiIphi") {m_sigmaIphiIphi = values_[i];}
    else if(labels_[i]=="numberOfMissingInnerHits") {m_numberOfMissingInnerHits = values_[i];}
    else if(labels_[i]=="numberOfMissingOuterHits") {m_numberOfMissingOuterHits = values_[i];}
    else if(labels_[i]=="numberOfTrackHits") {m_numberOfTrackHits = values_[i];}
    else if(labels_[i]=="passConversionVeto") {m_passConversionVeto = values_[i];}
    else if(labels_[i]=="numHadrons") {m_numHadrons = values_[i];}
    else if(labels_[i]=="numStrips") {m_numStrips = values_[i];}
    else std::cout<<" NOT STORED "<<labels_[i]<<" = "<<values_[i]<<"\n";
  }
}
    
    
////////////////////////////////////////////////////////////////////
// Fill Gen Lepton Info based on pat embedded GenParticle
////////////////////////////////////////////////////////////////////

void NtupleLepton::fillGenLeptonInfo(reco::GenParticle genLepton)
{
  m_gen_p4 = genLepton.p4();
  m_GENpdgId = genLepton.pdgId();

  if(genLepton.mother())
  {
    m_genMother_p4 = genLepton.mother()->p4();
    m_GENMOTHERpdgId = genLepton.mother()->pdgId();

    // to avoid having e->e as mother due to different status, 
    // go up one more level

    if((m_GENMOTHERpdgId)==(m_GENpdgId) && genLepton.mother()->mother())
    {
      m_genMother_p4 = genLepton.mother()->mother()->p4();
      m_GENMOTHERpdgId = genLepton.mother()->mother()->pdgId();

    }

  }
}


// fillers 
////////////////////////////////////////////////////////////////////
// fill called with TupleLepton argument
////////////////////////////////////////////////////////////////////

void NtupleLepton::fill(TupleLepton dummy_)
{

  m_leptonType = dummy_.leptonType();


  if(dummy_.leptonType()== TupleLeptonTypes::anElectron)
  {
    fill(dummy_.Electron()[0]);

  }

  else if(dummy_.leptonType()== TupleLeptonTypes::aMuon)
  {

    fill(dummy_.Muon()[0]);


  }

  else if(dummy_.leptonType()== TupleLeptonTypes::aTau)
  {

    fill(dummy_.Tau()[0]);

  }

}


////////////////////////////////////////////////////////////////////
// fill called with pat::Electron argument
////////////////////////////////////////////////////////////////////

void NtupleLepton::fill(pat::Electron dummy_)
{
  m_leptonType = TupleLeptonTypes::anElectron;
  m_p4 = dummy_.p4();
  m_PFpdgId = dummy_.pdgId();
  m_charge = dummy_.charge();
  
  if(dummy_.genLepton()) fillGenLeptonInfo(*(dummy_.genLepton()));
  
  stringVec labels_;
  floatVec values_;
  for (std::size_t ii = 0; ii < dummy_.userFloatNames().size(); ii ++ )
  {
      labels_.push_back(dummy_.userFloatNames().at(ii));
      values_.push_back(dummy_.userFloat(dummy_.userFloatNames().at(ii)));
  }
  userFloatVectorParser(labels_,values_);


}

////////////////////////////////////////////////////////////////////
// fill called with pat::Muon argument
////////////////////////////////////////////////////////////////////


void NtupleLepton::fill(pat::Muon dummy_)
{
  m_leptonType = TupleLeptonTypes::aMuon;
  m_p4 = dummy_.p4();
  m_PFpdgId = dummy_.pdgId();
  m_charge = dummy_.charge();
  
  if(dummy_.genLepton()) fillGenLeptonInfo(*(dummy_.genLepton()));

  stringVec labels_;
  floatVec values_;
  for (std::size_t ii = 0; ii < dummy_.userFloatNames().size(); ii ++ )
  {
      labels_.push_back(dummy_.userFloatNames().at(ii));
      values_.push_back(dummy_.userFloat(dummy_.userFloatNames().at(ii)));
  }
  userFloatVectorParser(labels_,values_);

}

////////////////////////////////////////////////////////////////////
// fill called with pat::Tau argument
////////////////////////////////////////////////////////////////////


void NtupleLepton::fill(pat::Tau dummy_)
{
  m_leptonType = TupleLeptonTypes::aTau;
  m_p4 = dummy_.p4();
  m_PFpdgId = dummy_.pdgId();
  m_charge = dummy_.charge();
  
  if(dummy_.genJet()) { m_genJet_p4 = dummy_.genJet()->p4(); }

  if(dummy_.genLepton()) fillGenLeptonInfo(*(dummy_.genLepton()));

  stringVec labels_;
  floatVec values_;
  for (std::size_t ii = 0; ii < dummy_.userFloatNames().size(); ii ++ )
  {
      labels_.push_back(dummy_.userFloatNames().at(ii));
      values_.push_back(dummy_.userFloat(dummy_.userFloatNames().at(ii)));
  }
  userFloatVectorParser(labels_,values_);



}





// getters 

int NtupleLepton::leptonType() const { return m_leptonType; }
LorentzVector NtupleLepton::p4() const { return m_p4; }
LorentzVector NtupleLepton::gen_p4() const { return m_gen_p4; }
LorentzVector NtupleLepton::genMother_p4() const { return m_genMother_p4; }


float NtupleLepton::pt() const { return m_p4.pt(); }
float NtupleLepton::eta() const { return m_p4.eta(); }

float NtupleLepton::dz() const { return m_dz; }
float NtupleLepton::dxy() const { return m_dxy; }
float NtupleLepton::EffectiveArea() const { return m_EffectiveArea; }
int NtupleLepton::charge() const { return m_charge; }
int NtupleLepton::PFpdgId() const { return m_PFpdgId; }
int NtupleLepton::GENpdgId() const { return m_GENpdgId; }
int NtupleLepton::GENMOTHERpdgId() const { return m_GENMOTHERpdgId; }
float NtupleLepton::raw_electronMVA() const {return m_raw_electronMVA;}
float NtupleLepton::passFail_electronMVA() const {return m_passFail_electronMVA;} 
float NtupleLepton::TauEsVariant() const {return m_TauEsVariant;} 
float NtupleLepton::IP() const {return m_IP;} 
float NtupleLepton::IPerror() const {return m_IPerror;} 
float NtupleLepton::PUchargedHadronIso() const {return m_PUchargedHadronIso;} 
float NtupleLepton::chargedHadronIso() const {return m_chargedHadronIso;} 
float NtupleLepton::neutralHadronIso() const {return m_neutralHadronIso;} 
float NtupleLepton::photonIso() const {return m_photonIso;} 
float  NtupleLepton::DepositR03ECal() const {return m_DepositR03ECal;}  
float  NtupleLepton::DepositR03Hcal() const {return m_DepositR03Hcal;} 
float  NtupleLepton::DepositR03TrackerOfficial() const {return m_DepositR03TrackerOfficial;}   
float  NtupleLepton::isGlobalMuon() const {return m_isGlobalMuon;}    
float  NtupleLepton::isGoodGlobalMuon() const {return m_isGoodGlobalMuon;}    
float  NtupleLepton::passesMediumMuonId() const {return m_passesMediumMuonId;}    
float  NtupleLepton::isLooseMuon() const {return m_isLooseMuon;}   
float  NtupleLepton::isPFMuon() const {return m_isPFMuon;}    
float  NtupleLepton::isSoftMuon() const {return m_isSoftMuon;}    
float  NtupleLepton::isTightMuon() const {return m_isTightMuon;}   
float  NtupleLepton::isTrackerMuon() const {return m_isTrackerMuon;}   
float  NtupleLepton::muonCombQualChi2LocalPosition() const {return m_muonCombQualChi2LocalPosition;} 
float  NtupleLepton::muonCombQualTrkKink() const {return m_muonCombQualTrkKink;}   
float  NtupleLepton::muonGlobalTrackNormChi2() const {return m_muonGlobalTrackNormChi2;}   
float  NtupleLepton::muonInnerTrkValidFraction() const {return m_muonInnerTrkValidFraction;}   
float  NtupleLepton::muonSegmentCompatibility() const {return m_muonSegmentCompatibility;}    
float NtupleLepton::SuperClusterEta() const {return m_SuperClusterEta;}
float NtupleLepton::hadronicOverEm() const {return m_hadronicOverEm;}
float NtupleLepton::isEB() const {return m_isEB;}
float NtupleLepton::isEBEEGap() const {return m_isEBEEGap;}
float NtupleLepton::isEBEtaGap() const {return m_isEBEtaGap;}
float NtupleLepton::isEBPhiGap() const {return m_isEBPhiGap;}
float NtupleLepton::isEE() const {return m_isEE;}
float NtupleLepton::isEEDeeGap() const {return m_isEEDeeGap;}
float NtupleLepton::isEERingGap() const {return m_isEERingGap;}
float NtupleLepton::deltaEtaSuperClusterTrackAtVtx() const {return m_deltaEtaSuperClusterTrackAtVtx;}
float NtupleLepton::deltaPhiSuperClusterTrackAtVtx() const {return m_deltaPhiSuperClusterTrackAtVtx;}
float NtupleLepton::sigmaEtaEta() const {return m_sigmaEtaEta;}
float NtupleLepton::sigmaIetaIeta() const {return m_sigmaIetaIeta;}
float NtupleLepton::sigmaIphiIphi() const {return m_sigmaIphiIphi;}
float NtupleLepton::numberOfMissingInnerHits() const {return m_numberOfMissingInnerHits;}
float NtupleLepton::numberOfMissingOuterHits() const {return m_numberOfMissingOuterHits;}
float NtupleLepton::numberOfTrackHits() const {return m_numberOfTrackHits;}
float NtupleLepton::passConversionVeto() const {return m_passConversionVeto;}


LorentzVector NtupleLepton::genJet_p4() const {return m_genJet_p4;}
float NtupleLepton::numStrips() const {return m_numStrips;}
float NtupleLepton::numHadrons() const {return m_numHadrons;}
