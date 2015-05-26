#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "TLorentzVector.h"

NtupleLepton::NtupleLepton()
{
  m_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_gen_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_genMother_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_L1TrigObj_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_L3TrigObj_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_leptonType = -999;
  m_charge = -999;
  m_PFpdgId = -999;
  m_GENpdgId = -999;
  m_GENMOTHERpdgId = -999;
  m_dz = NAN;
  m_dxy = NAN;
  m_EffectiveArea = NAN;
  m_L1TrigObjRecoObjDeltaR = NAN;
  m_L3TrigObjRecoObjDeltaR = NAN;
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
  m_againstElectronLoose = NAN;
  m_againstElectronLooseMVA5 = NAN;
  m_againstElectronMVA5category = NAN;
  m_againstElectronMVA5raw = NAN;
  m_againstElectronMedium = NAN;
  m_againstElectronMediumMVA5 = NAN;
  m_againstElectronTight = NAN;
  m_againstElectronTightMVA5 = NAN;
  m_againstElectronVLooseMVA5 = NAN;
  m_againstElectronVTightMVA5 = NAN;
  m_againstMuonLoose = NAN;
  m_againstMuonLoose2 = NAN;
  m_againstMuonLoose3 = NAN;
  m_againstMuonLooseMVA = NAN;
  m_againstMuonMVAraw = NAN;
  m_againstMuonMedium = NAN;
  m_againstMuonMedium2 = NAN;
  m_againstMuonMediumMVA = NAN;
  m_againstMuonTight = NAN;
  m_againstMuonTight2 = NAN;
  m_againstMuonTight3 = NAN;
  m_againstMuonTightMVA = NAN;
  m_byCombinedIsolationDeltaBetaCorrRaw3Hits = NAN;
  m_byIsolationMVA3newDMwLTraw = NAN;
  m_byIsolationMVA3newDMwoLTraw = NAN;
  m_byIsolationMVA3oldDMwLTraw = NAN;
  m_byIsolationMVA3oldDMwoLTraw = NAN;
  m_byLooseCombinedIsolationDeltaBetaCorr3Hits = NAN;
  m_byLooseIsolationMVA3newDMwLT = NAN;
  m_byLooseIsolationMVA3newDMwoLT = NAN;
  m_byLooseIsolationMVA3oldDMwLT = NAN;
  m_byLooseIsolationMVA3oldDMwoLT = NAN;
  m_byMediumCombinedIsolationDeltaBetaCorr3Hits = NAN;
  m_byMediumIsolationMVA3newDMwLT = NAN;
  m_byMediumIsolationMVA3newDMwoLT = NAN;
  m_byMediumIsolationMVA3oldDMwLT = NAN;
  m_byMediumIsolationMVA3oldDMwoLT = NAN;
  m_byTightCombinedIsolationDeltaBetaCorr3Hits = NAN;
  m_byTightIsolationMVA3newDMwLT = NAN;
  m_byTightIsolationMVA3newDMwoLT = NAN;
  m_byTightIsolationMVA3oldDMwLT = NAN;
  m_byTightIsolationMVA3oldDMwoLT = NAN;
  m_byVLooseIsolationMVA3newDMwLT = NAN;
  m_byVLooseIsolationMVA3newDMwoLT = NAN;
  m_byVLooseIsolationMVA3oldDMwLT = NAN;
  m_byVLooseIsolationMVA3oldDMwoLT = NAN;
  m_byVTightIsolationMVA3newDMwLT = NAN;
  m_byVTightIsolationMVA3newDMwoLT = NAN;
  m_byVTightIsolationMVA3oldDMwLT = NAN;
  m_byVTightIsolationMVA3oldDMwoLT = NAN;
  m_byVVTightIsolationMVA3newDMwLT = NAN;
  m_byVVTightIsolationMVA3newDMwoLT = NAN;
  m_byVVTightIsolationMVA3oldDMwLT = NAN;
  m_byVVTightIsolationMVA3oldDMwoLT = NAN;
  m_chargedIsoPtSum = NAN;
  m_decayModeFinding = NAN;
  m_decayModeFindingNewDMs = NAN;
  m_neutralIsoPtSum = NAN;
  m_puCorrPtSum = NAN;  
  m_genJet_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_numStrips = NAN;
  m_numHadrons  = NAN;

}

// helpers

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
    for(std::size_t i=0;i<m_rho_Labels.size();++i) std::cout<<"[ "<<m_rho_Labels[i]<<" = "<<m_rho_Values[i]<<" ] ";
    std::cout<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> known relIso types and values : ";
    for(std::size_t i=0;i<m_relativeIsol_Labels.size();++i) std::cout<<"[ "<<m_relativeIsol_Labels[i]<<" = "<<m_relativeIsol_Values[i]<<" ] ";
    std::cout<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> HLT ACCEPTED PATHS and PreScales : ";
    for(std::size_t i=0;i<m_HLTacceptedPaths.size();++i) std::cout<<"[ "<<m_HLTacceptedPaths[i]<<" = "<<m_HLTacceptedPathPreScales[i]<<" ] ";
    std::cout<<"\n";
 
  std::cout<<"<LEPPRINT "<<type_print<<"> L1 trig obj Pt,Eta,Phi,M "<<m_L1TrigObj_p4.Pt()<<" , "<<m_L1TrigObj_p4.Eta()<<" , "<<m_L1TrigObj_p4.Phi()<<" , "<<m_L1TrigObj_p4.M()<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> L1 trig obj minDR "<<m_L1TrigObjRecoObjDeltaR<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> L1 trig obj's filters : ";
    for(std::size_t i=0;i<m_L1acceptedFilters.size();++i) std::cout<<"[ "<<m_L1acceptedFilters[i]<<" ] ";
    std::cout<<"\n";

  std::cout<<"<LEPPRINT "<<type_print<<"> L3 trig obj Pt,Eta,Phi,M "<<m_L3TrigObj_p4.Pt()<<" , "<<m_L3TrigObj_p4.Eta()<<" , "<<m_L3TrigObj_p4.Phi()<<" , "<<m_L3TrigObj_p4.M()<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> L3 trig obj minDR "<<m_L3TrigObjRecoObjDeltaR<<"\n";
  std::cout<<"<LEPPRINT "<<type_print<<"> L3 trig obj's filters : ";
    for(std::size_t i=0;i<m_L3acceptedFilters.size();++i) std::cout<<"[ "<<m_L3acceptedFilters[i]<<" ] ";
    std::cout<<"\n";

  std::cout<<"<LEPPRINT "<<type_print<<"> HLT isBOTH  : ";
    for(std::size_t i=0;i<m_pathSummary_isBOTH.size();++i) std::cout<<"[ "<<m_pathSummary_isBOTH[i]<<" ] ";
    std::cout<<"\n";  

  std::cout<<"<LEPPRINT "<<type_print<<"> HLT isL3  : ";
    for(std::size_t i=0;i<m_pathSummary_isL3.size();++i) std::cout<<"[ "<<m_pathSummary_isL3[i]<<" ] ";
    std::cout<<"\n";  

  std::cout<<"<LEPPRINT "<<type_print<<"> HLT isLF  : ";
    for(std::size_t i=0;i<m_pathSummary_isLF.size();++i) std::cout<<"[ "<<m_pathSummary_isLF[i]<<" ] ";
    std::cout<<"\n";  

  std::cout<<"<LEPPRINT "<<type_print<<"> HLT all config filters passed  : ";
    for(std::size_t i=0;i<m_pathSummary_filterListPassed.size();++i) std::cout<<"[ "<<m_pathSummary_filterListPassed[i]<<" ] ";
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
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronLoose : " << m_againstElectronLoose << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronLooseMVA5 : " << m_againstElectronLooseMVA5 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronMVA5category : " << m_againstElectronMVA5category << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronMVA5raw : " << m_againstElectronMVA5raw << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronMedium : " << m_againstElectronMedium << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronMediumMVA5 : " << m_againstElectronMediumMVA5 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronTight : " << m_againstElectronTight << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronTightMVA5 : " << m_againstElectronTightMVA5 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronVLooseMVA5 : " << m_againstElectronVLooseMVA5 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstElectronVTightMVA5 : " << m_againstElectronVTightMVA5 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonLoose : " << m_againstMuonLoose << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonLoose2 : " << m_againstMuonLoose2 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonLoose3 : " << m_againstMuonLoose3 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonLooseMVA : " << m_againstMuonLooseMVA << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonMVAraw : " << m_againstMuonMVAraw << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonMedium : " << m_againstMuonMedium << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonMedium2 : " << m_againstMuonMedium2 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonMediumMVA : " << m_againstMuonMediumMVA << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonTight : " << m_againstMuonTight << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonTight2 : " << m_againstMuonTight2 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonTight3 : " << m_againstMuonTight3 << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> againstMuonTightMVA : " << m_againstMuonTightMVA << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byCombinedIsolationDeltaBetaCorrRaw3Hits : " << m_byCombinedIsolationDeltaBetaCorrRaw3Hits << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byIsolationMVA3newDMwLTraw : " << m_byIsolationMVA3newDMwLTraw << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byIsolationMVA3newDMwoLTraw : " << m_byIsolationMVA3newDMwoLTraw << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byIsolationMVA3oldDMwLTraw : " << m_byIsolationMVA3oldDMwLTraw << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byIsolationMVA3oldDMwoLTraw : " << m_byIsolationMVA3oldDMwoLTraw << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byLooseCombinedIsolationDeltaBetaCorr3Hits : " << m_byLooseCombinedIsolationDeltaBetaCorr3Hits << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byLooseIsolationMVA3newDMwLT : " << m_byLooseIsolationMVA3newDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byLooseIsolationMVA3newDMwoLT : " << m_byLooseIsolationMVA3newDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byLooseIsolationMVA3oldDMwLT : " << m_byLooseIsolationMVA3oldDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byLooseIsolationMVA3oldDMwoLT : " << m_byLooseIsolationMVA3oldDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byMediumCombinedIsolationDeltaBetaCorr3Hits : " << m_byMediumCombinedIsolationDeltaBetaCorr3Hits << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byMediumIsolationMVA3newDMwLT : " << m_byMediumIsolationMVA3newDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byMediumIsolationMVA3newDMwoLT : " << m_byMediumIsolationMVA3newDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byMediumIsolationMVA3oldDMwLT : " << m_byMediumIsolationMVA3oldDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byMediumIsolationMVA3oldDMwoLT : " << m_byMediumIsolationMVA3oldDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byTightCombinedIsolationDeltaBetaCorr3Hits : " << m_byTightCombinedIsolationDeltaBetaCorr3Hits << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byTightIsolationMVA3newDMwLT : " << m_byTightIsolationMVA3newDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byTightIsolationMVA3newDMwoLT : " << m_byTightIsolationMVA3newDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byTightIsolationMVA3oldDMwLT : " << m_byTightIsolationMVA3oldDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byTightIsolationMVA3oldDMwoLT : " << m_byTightIsolationMVA3oldDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVLooseIsolationMVA3newDMwLT : " << m_byVLooseIsolationMVA3newDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVLooseIsolationMVA3newDMwoLT : " << m_byVLooseIsolationMVA3newDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVLooseIsolationMVA3oldDMwLT : " << m_byVLooseIsolationMVA3oldDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVLooseIsolationMVA3oldDMwoLT : " << m_byVLooseIsolationMVA3oldDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVTightIsolationMVA3newDMwLT : " << m_byVTightIsolationMVA3newDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVTightIsolationMVA3newDMwoLT : " << m_byVTightIsolationMVA3newDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVTightIsolationMVA3oldDMwLT : " << m_byVTightIsolationMVA3oldDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVTightIsolationMVA3oldDMwoLT : " << m_byVTightIsolationMVA3oldDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVVTightIsolationMVA3newDMwLT : " << m_byVVTightIsolationMVA3newDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVVTightIsolationMVA3newDMwoLT : " << m_byVVTightIsolationMVA3newDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVVTightIsolationMVA3oldDMwLT : " << m_byVVTightIsolationMVA3oldDMwLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> byVVTightIsolationMVA3oldDMwoLT : " << m_byVVTightIsolationMVA3oldDMwoLT << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> chargedIsoPtSum : " << m_chargedIsoPtSum << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> decayModeFinding : " << m_decayModeFinding << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> decayModeFindingNewDMs : " << m_decayModeFindingNewDMs << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> neutralIsoPtSum : " << m_neutralIsoPtSum << std::endl;
std::cout<<"<LEPPRINT "<<type_print<<"> puCorrPtSum : " << m_puCorrPtSum << std::endl;
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

  float trigL1Pt = NAN;
  float trigL1Eta = NAN;
  float trigL1Phi = NAN;
  float trigL1Mass = NAN;
  float trigL3Pt = NAN;
  float trigL3Eta = NAN;
  float trigL3Phi = NAN;
  float trigL3Mass = NAN;


  for(std::size_t i = 0; i<labels_.size(); ++i)
  {
   // std::cout<<labels_[i]<<" "<<values_[i]<<"\n";

    if(labels_[i].find("AcceptWithPreScale_")==0) 
      {
        std::string x = "AcceptWithPreScale_";
        m_HLTacceptedPaths.push_back(labels_[i].erase(0,x.length()));
        m_HLTacceptedPathPreScales.push_back(values_[i]);
      }
    else if(labels_[i]=="EffectiveArea")  m_EffectiveArea = values_[i];
    else if(labels_[i]=="dxy")  m_dxy = values_[i];
    else if(labels_[i]=="dz")  m_dz = values_[i];
    else if (labels_[i].find("L1Obj_TrigObjRecoObjDeltaR")!=std::string::npos)
      { m_L1TrigObjRecoObjDeltaR = values_[i];}
    else if (labels_[i].find("L1Obj_TrigObjPt")!=std::string::npos)
      { trigL1Pt = values_[i];}
    else if (labels_[i].find("L1Obj_TrigObjEta")!=std::string::npos)
      { trigL1Eta = values_[i];}
    else if (labels_[i].find("L1Obj_TrigObjPhi")!=std::string::npos)
      { trigL1Phi = values_[i];}
    else if (labels_[i].find("L1Obj_TrigObjMass")!=std::string::npos)
      { trigL1Mass = values_[i];}
    else if (labels_[i].find("L3Obj_TrigObjRecoObjDeltaR")!=std::string::npos)
      { m_L3TrigObjRecoObjDeltaR = values_[i];}
    else if (labels_[i].find("L3Obj_TrigObjPt")!=std::string::npos)
      { trigL3Pt = values_[i];}
    else if (labels_[i].find("L3Obj_TrigObjEta")!=std::string::npos)
      { trigL3Eta = values_[i];}
    else if (labels_[i].find("L3Obj_TrigObjPhi")!=std::string::npos)
      { trigL3Phi = values_[i];}
    else if (labels_[i].find("L3Obj_TrigObjMass")!=std::string::npos)
      { trigL3Mass = values_[i];}
    else if (labels_[i].find("rho_")==0)
      {
        std::string x = "rho_";
        m_rho_Labels.push_back(labels_[i].erase(0,x.length()));
        m_rho_Values.push_back(values_[i]);
      }
    else if (labels_[i].find("relativeIsol_")==0)
      {
        std::string x = "relativeIsol_";
        m_relativeIsol_Labels.push_back(labels_[i].erase(0,x.length()));
        m_relativeIsol_Values.push_back(values_[i]);
      }
    else if(labels_[i].find("L1Obj_trigObjectFilter_")==0)
      {
        std::string x = "L1Obj_trigObjectFilter_";
        m_L1acceptedFilters.push_back(labels_[i].erase(0,x.length()));
      }
    else if(labels_[i].find("L3Obj_trigObjectFilter_")==0)
      {
        std::string x = "L3Obj_trigObjectFilter_";
        m_L3acceptedFilters.push_back(labels_[i].erase(0,x.length()));
      }
    else if(labels_[i].find("trigObjectPathSummary_")==0 && labels_[i].find("_isBOTH")!=std::string::npos)
      {
        if(values_[i]==1)
        {
          std::string x = "trigObjectPathSummary_";
          std::string y = "_isBOTH";
          std::string sansPrefix = labels_[i].erase(0,x.length());
          m_pathSummary_isBOTH.push_back(sansPrefix.erase(sansPrefix.length()-y.length(),sansPrefix.length()));
        }
      }
    else if(labels_[i].find("trigObjectPathSummary_")==0 && labels_[i].find("_isL3")!=std::string::npos)
      {  
        if(values_[i]==1)
        {
          std::string x = "trigObjectPathSummary_";
          std::string y = "_isL3";
          std::string sansPrefix = labels_[i].erase(0,x.length());
          m_pathSummary_isL3.push_back(sansPrefix.erase(sansPrefix.length()-y.length(),sansPrefix.length()));
        }

      }
    else if(labels_[i].find("trigObjectPathSummary_")==0 && labels_[i].find("_isLF")!=std::string::npos)
      {

        if(values_[i]==1)
        {
          std::string x = "trigObjectPathSummary_";
          std::string y = "_isLF";
          std::string sansPrefix = labels_[i].erase(0,x.length());
          m_pathSummary_isLF.push_back(sansPrefix.erase(sansPrefix.length()-y.length(),sansPrefix.length()));
        }


      }
    else if(labels_[i].find("trigObjectPathSummary_")==0 && labels_[i].find("_filterListPassed")!=std::string::npos)
      {

        if(values_[i]==1)
        {
          std::string x = "trigObjectPathSummary_";
          std::string y = "_filterListPassed";
          std::string sansPrefix = labels_[i].erase(0,x.length());
          m_pathSummary_filterListPassed.push_back(sansPrefix.erase(sansPrefix.length()-y.length(),sansPrefix.length()));
        }


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
    else if(labels_[i]=="againstElectronLoose") {m_againstElectronLoose = values_[i];}
    else if(labels_[i]=="againstElectronLooseMVA5") {m_againstElectronLooseMVA5 = values_[i];}
    else if(labels_[i]=="againstElectronMVA5category") {m_againstElectronMVA5category = values_[i];}
    else if(labels_[i]=="againstElectronMVA5raw") {m_againstElectronMVA5raw = values_[i];}
    else if(labels_[i]=="againstElectronMedium") {m_againstElectronMedium = values_[i];}
    else if(labels_[i]=="againstElectronMediumMVA5") {m_againstElectronMediumMVA5 = values_[i];}
    else if(labels_[i]=="againstElectronTight") {m_againstElectronTight = values_[i];}
    else if(labels_[i]=="againstElectronTightMVA5") {m_againstElectronTightMVA5 = values_[i];}
    else if(labels_[i]=="againstElectronVLooseMVA5") {m_againstElectronVLooseMVA5 = values_[i];}
    else if(labels_[i]=="againstElectronVTightMVA5") {m_againstElectronVTightMVA5 = values_[i];}
    else if(labels_[i]=="againstMuonLoose") {m_againstMuonLoose = values_[i];}
    else if(labels_[i]=="againstMuonLoose2") {m_againstMuonLoose2 = values_[i];}
    else if(labels_[i]=="againstMuonLoose3") {m_againstMuonLoose3 = values_[i];}
    else if(labels_[i]=="againstMuonLooseMVA") {m_againstMuonLooseMVA = values_[i];}
    else if(labels_[i]=="againstMuonMVAraw") {m_againstMuonMVAraw = values_[i];}
    else if(labels_[i]=="againstMuonMedium") {m_againstMuonMedium = values_[i];}
    else if(labels_[i]=="againstMuonMedium2") {m_againstMuonMedium2 = values_[i];}
    else if(labels_[i]=="againstMuonMediumMVA") {m_againstMuonMediumMVA = values_[i];}
    else if(labels_[i]=="againstMuonTight") {m_againstMuonTight = values_[i];}
    else if(labels_[i]=="againstMuonTight2") {m_againstMuonTight2 = values_[i];}
    else if(labels_[i]=="againstMuonTight3") {m_againstMuonTight3 = values_[i];}
    else if(labels_[i]=="againstMuonTightMVA") {m_againstMuonTightMVA = values_[i];}
    else if(labels_[i]=="byCombinedIsolationDeltaBetaCorrRaw3Hits") {m_byCombinedIsolationDeltaBetaCorrRaw3Hits = values_[i];}
    else if(labels_[i]=="byIsolationMVA3newDMwLTraw") {m_byIsolationMVA3newDMwLTraw = values_[i];}
    else if(labels_[i]=="byIsolationMVA3newDMwoLTraw") {m_byIsolationMVA3newDMwoLTraw = values_[i];}
    else if(labels_[i]=="byIsolationMVA3oldDMwLTraw") {m_byIsolationMVA3oldDMwLTraw = values_[i];}
    else if(labels_[i]=="byIsolationMVA3oldDMwoLTraw") {m_byIsolationMVA3oldDMwoLTraw = values_[i];}
    else if(labels_[i]=="byLooseCombinedIsolationDeltaBetaCorr3Hits") {m_byLooseCombinedIsolationDeltaBetaCorr3Hits = values_[i];}
    else if(labels_[i]=="byLooseIsolationMVA3newDMwLT") {m_byLooseIsolationMVA3newDMwLT = values_[i];}
    else if(labels_[i]=="byLooseIsolationMVA3newDMwoLT") {m_byLooseIsolationMVA3newDMwoLT = values_[i];}
    else if(labels_[i]=="byLooseIsolationMVA3oldDMwLT") {m_byLooseIsolationMVA3oldDMwLT = values_[i];}
    else if(labels_[i]=="byLooseIsolationMVA3oldDMwoLT") {m_byLooseIsolationMVA3oldDMwoLT = values_[i];}
    else if(labels_[i]=="byMediumCombinedIsolationDeltaBetaCorr3Hits") {m_byMediumCombinedIsolationDeltaBetaCorr3Hits = values_[i];}
    else if(labels_[i]=="byMediumIsolationMVA3newDMwLT") {m_byMediumIsolationMVA3newDMwLT = values_[i];}
    else if(labels_[i]=="byMediumIsolationMVA3newDMwoLT") {m_byMediumIsolationMVA3newDMwoLT = values_[i];}
    else if(labels_[i]=="byMediumIsolationMVA3oldDMwLT") {m_byMediumIsolationMVA3oldDMwLT = values_[i];}
    else if(labels_[i]=="byMediumIsolationMVA3oldDMwoLT") {m_byMediumIsolationMVA3oldDMwoLT = values_[i];}
    else if(labels_[i]=="byTightCombinedIsolationDeltaBetaCorr3Hits") {m_byTightCombinedIsolationDeltaBetaCorr3Hits = values_[i];}
    else if(labels_[i]=="byTightIsolationMVA3newDMwLT") {m_byTightIsolationMVA3newDMwLT = values_[i];}
    else if(labels_[i]=="byTightIsolationMVA3newDMwoLT") {m_byTightIsolationMVA3newDMwoLT = values_[i];}
    else if(labels_[i]=="byTightIsolationMVA3oldDMwLT") {m_byTightIsolationMVA3oldDMwLT = values_[i];}
    else if(labels_[i]=="byTightIsolationMVA3oldDMwoLT") {m_byTightIsolationMVA3oldDMwoLT = values_[i];}
    else if(labels_[i]=="byVLooseIsolationMVA3newDMwLT") {m_byVLooseIsolationMVA3newDMwLT = values_[i];}
    else if(labels_[i]=="byVLooseIsolationMVA3newDMwoLT") {m_byVLooseIsolationMVA3newDMwoLT = values_[i];}
    else if(labels_[i]=="byVLooseIsolationMVA3oldDMwLT") {m_byVLooseIsolationMVA3oldDMwLT = values_[i];}
    else if(labels_[i]=="byVLooseIsolationMVA3oldDMwoLT") {m_byVLooseIsolationMVA3oldDMwoLT = values_[i];}
    else if(labels_[i]=="byVTightIsolationMVA3newDMwLT") {m_byVTightIsolationMVA3newDMwLT = values_[i];}
    else if(labels_[i]=="byVTightIsolationMVA3newDMwoLT") {m_byVTightIsolationMVA3newDMwoLT = values_[i];}
    else if(labels_[i]=="byVTightIsolationMVA3oldDMwLT") {m_byVTightIsolationMVA3oldDMwLT = values_[i];}
    else if(labels_[i]=="byVTightIsolationMVA3oldDMwoLT") {m_byVTightIsolationMVA3oldDMwoLT = values_[i];}
    else if(labels_[i]=="byVVTightIsolationMVA3newDMwLT") {m_byVVTightIsolationMVA3newDMwLT = values_[i];}
    else if(labels_[i]=="byVVTightIsolationMVA3newDMwoLT") {m_byVVTightIsolationMVA3newDMwoLT = values_[i];}
    else if(labels_[i]=="byVVTightIsolationMVA3oldDMwLT") {m_byVVTightIsolationMVA3oldDMwLT = values_[i];}
    else if(labels_[i]=="byVVTightIsolationMVA3oldDMwoLT") {m_byVVTightIsolationMVA3oldDMwoLT = values_[i];}
    else if(labels_[i]=="chargedIsoPtSum") {m_chargedIsoPtSum = values_[i];}
    else if(labels_[i]=="decayModeFinding") {m_decayModeFinding = values_[i];}
    else if(labels_[i]=="decayModeFindingNewDMs") {m_decayModeFindingNewDMs = values_[i];}
    else if(labels_[i]=="neutralIsoPtSum") {m_neutralIsoPtSum = values_[i];}
    else if(labels_[i]=="puCorrPtSum") {m_puCorrPtSum = values_[i];}
    else if(labels_[i]=="numHadrons") {m_numHadrons = values_[i];}
    else if(labels_[i]=="numStrips") {m_numStrips = values_[i];}

    else std::cout<<" NOT STORED "<<labels_[i]<<" = "<<values_[i]<<"\n";

  }
  /////////////////////////////////////////
  // set the trig 4-vectors
  if(trigL1Pt==trigL1Pt)
  {
  TLorentzVector L1;
  L1.SetPtEtaPhiM(trigL1Pt,trigL1Eta,trigL1Phi,trigL1Mass);
  m_L1TrigObj_p4.SetXYZT(L1.X(),L1.Y(),L1.Z(),L1.T());
  }

  if(trigL3Pt==trigL3Pt)
  {
  TLorentzVector L3;
  L3.SetPtEtaPhiM(trigL3Pt,trigL3Eta,trigL3Phi,trigL3Mass);
  m_L3TrigObj_p4.SetXYZT(L3.X(),L3.Y(),L3.Z(),L3.T());
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
LorentzVector NtupleLepton::L1TrigObj_p4() const { return m_L1TrigObj_p4; }
LorentzVector NtupleLepton::L3TrigObj_p4() const { return m_L3TrigObj_p4; }


float NtupleLepton::dz() const { return m_dz; }
float NtupleLepton::dxy() const { return m_dxy; }
stringVec NtupleLepton::HLTacceptedPaths() const { return m_HLTacceptedPaths; }
floatVec NtupleLepton::HLTacceptedPathPreScales() const { return m_HLTacceptedPathPreScales; }
float NtupleLepton::EffectiveArea() const { return m_EffectiveArea; }
int NtupleLepton::charge() const { return m_charge; }
int NtupleLepton::PFpdgId() const { return m_PFpdgId; }
int NtupleLepton::GENpdgId() const { return m_GENpdgId; }
int NtupleLepton::GENMOTHERpdgId() const { return m_GENMOTHERpdgId; }

stringVec NtupleLepton::L1acceptedFilters() const { return m_L1acceptedFilters; }
float NtupleLepton::L1TrigObjRecoObjDeltaR() const { return m_L1TrigObjRecoObjDeltaR; }
stringVec NtupleLepton::L3acceptedFilters() const { return m_L3acceptedFilters; }
float NtupleLepton::L3TrigObjRecoObjDeltaR() const { return m_L3TrigObjRecoObjDeltaR; }
stringVec NtupleLepton::pathSummary_isBOTH() const { return m_pathSummary_isBOTH; }
stringVec NtupleLepton::pathSummary_isL3() const { return m_pathSummary_isL3; }
stringVec NtupleLepton::pathSummary_isLF() const { return m_pathSummary_isLF; }
stringVec NtupleLepton::pathSummary_filterListPassed() const { return m_pathSummary_filterListPassed; }
stringVec NtupleLepton::relativeIsol_Labels() const { return m_relativeIsol_Labels; }
floatVec NtupleLepton::relativeIsol_Values() const { return m_relativeIsol_Values; }
stringVec NtupleLepton::rho_Labels() const { return m_rho_Labels; }
floatVec NtupleLepton::rho_Values() const { return m_rho_Values; }
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
float NtupleLepton::againstElectronLoose() const {return m_againstElectronLoose;}
float NtupleLepton::againstElectronLooseMVA5() const {return m_againstElectronLooseMVA5;}
float NtupleLepton::againstElectronMVA5category() const {return m_againstElectronMVA5category;}
float NtupleLepton::againstElectronMVA5raw() const {return m_againstElectronMVA5raw;}
float NtupleLepton::againstElectronMedium() const {return m_againstElectronMedium;}
float NtupleLepton::againstElectronMediumMVA5() const {return m_againstElectronMediumMVA5;}
float NtupleLepton::againstElectronTight() const {return m_againstElectronTight;}
float NtupleLepton::againstElectronTightMVA5() const {return m_againstElectronTightMVA5;}
float NtupleLepton::againstElectronVLooseMVA5() const {return m_againstElectronVLooseMVA5;}
float NtupleLepton::againstElectronVTightMVA5() const {return m_againstElectronVTightMVA5;}
float NtupleLepton::againstMuonLoose() const {return m_againstMuonLoose;}
float NtupleLepton::againstMuonLoose2() const {return m_againstMuonLoose2;}
float NtupleLepton::againstMuonLoose3() const {return m_againstMuonLoose3;}
float NtupleLepton::againstMuonLooseMVA() const {return m_againstMuonLooseMVA;}
float NtupleLepton::againstMuonMVAraw() const {return m_againstMuonMVAraw;}
float NtupleLepton::againstMuonMedium() const {return m_againstMuonMedium;}
float NtupleLepton::againstMuonMedium2() const {return m_againstMuonMedium2;}
float NtupleLepton::againstMuonMediumMVA() const {return m_againstMuonMediumMVA;}
float NtupleLepton::againstMuonTight() const {return m_againstMuonTight;}
float NtupleLepton::againstMuonTight2() const {return m_againstMuonTight2;}
float NtupleLepton::againstMuonTight3() const {return m_againstMuonTight3;}
float NtupleLepton::againstMuonTightMVA() const {return m_againstMuonTightMVA;}
float NtupleLepton::byCombinedIsolationDeltaBetaCorrRaw3Hits() const {return m_byCombinedIsolationDeltaBetaCorrRaw3Hits;}
float NtupleLepton::byIsolationMVA3newDMwLTraw() const {return m_byIsolationMVA3newDMwLTraw;}
float NtupleLepton::byIsolationMVA3newDMwoLTraw() const {return m_byIsolationMVA3newDMwoLTraw;}
float NtupleLepton::byIsolationMVA3oldDMwLTraw() const {return m_byIsolationMVA3oldDMwLTraw;}
float NtupleLepton::byIsolationMVA3oldDMwoLTraw() const {return m_byIsolationMVA3oldDMwoLTraw;}
float NtupleLepton::byLooseCombinedIsolationDeltaBetaCorr3Hits() const {return m_byLooseCombinedIsolationDeltaBetaCorr3Hits;}
float NtupleLepton::byLooseIsolationMVA3newDMwLT() const {return m_byLooseIsolationMVA3newDMwLT;}
float NtupleLepton::byLooseIsolationMVA3newDMwoLT() const {return m_byLooseIsolationMVA3newDMwoLT;}
float NtupleLepton::byLooseIsolationMVA3oldDMwLT() const {return m_byLooseIsolationMVA3oldDMwLT;}
float NtupleLepton::byLooseIsolationMVA3oldDMwoLT() const {return m_byLooseIsolationMVA3oldDMwoLT;}
float NtupleLepton::byMediumCombinedIsolationDeltaBetaCorr3Hits() const {return m_byMediumCombinedIsolationDeltaBetaCorr3Hits;}
float NtupleLepton::byMediumIsolationMVA3newDMwLT() const {return m_byMediumIsolationMVA3newDMwLT;}
float NtupleLepton::byMediumIsolationMVA3newDMwoLT() const {return m_byMediumIsolationMVA3newDMwoLT;}
float NtupleLepton::byMediumIsolationMVA3oldDMwLT() const {return m_byMediumIsolationMVA3oldDMwLT;}
float NtupleLepton::byMediumIsolationMVA3oldDMwoLT() const {return m_byMediumIsolationMVA3oldDMwoLT;}
float NtupleLepton::byTightCombinedIsolationDeltaBetaCorr3Hits() const {return m_byTightCombinedIsolationDeltaBetaCorr3Hits;}
float NtupleLepton::byTightIsolationMVA3newDMwLT() const {return m_byTightIsolationMVA3newDMwLT;}
float NtupleLepton::byTightIsolationMVA3newDMwoLT() const {return m_byTightIsolationMVA3newDMwoLT;}
float NtupleLepton::byTightIsolationMVA3oldDMwLT() const {return m_byTightIsolationMVA3oldDMwLT;}
float NtupleLepton::byTightIsolationMVA3oldDMwoLT() const {return m_byTightIsolationMVA3oldDMwoLT;}
float NtupleLepton::byVLooseIsolationMVA3newDMwLT() const {return m_byVLooseIsolationMVA3newDMwLT;}
float NtupleLepton::byVLooseIsolationMVA3newDMwoLT() const {return m_byVLooseIsolationMVA3newDMwoLT;}
float NtupleLepton::byVLooseIsolationMVA3oldDMwLT() const {return m_byVLooseIsolationMVA3oldDMwLT;}
float NtupleLepton::byVLooseIsolationMVA3oldDMwoLT() const {return m_byVLooseIsolationMVA3oldDMwoLT;}
float NtupleLepton::byVTightIsolationMVA3newDMwLT() const {return m_byVTightIsolationMVA3newDMwLT;}
float NtupleLepton::byVTightIsolationMVA3newDMwoLT() const {return m_byVTightIsolationMVA3newDMwoLT;}
float NtupleLepton::byVTightIsolationMVA3oldDMwLT() const {return m_byVTightIsolationMVA3oldDMwLT;}
float NtupleLepton::byVTightIsolationMVA3oldDMwoLT() const {return m_byVTightIsolationMVA3oldDMwoLT;}
float NtupleLepton::byVVTightIsolationMVA3newDMwLT() const {return m_byVVTightIsolationMVA3newDMwLT;}
float NtupleLepton::byVVTightIsolationMVA3newDMwoLT() const {return m_byVVTightIsolationMVA3newDMwoLT;}
float NtupleLepton::byVVTightIsolationMVA3oldDMwLT() const {return m_byVVTightIsolationMVA3oldDMwLT;}
float NtupleLepton::byVVTightIsolationMVA3oldDMwoLT() const {return m_byVVTightIsolationMVA3oldDMwoLT;}
float NtupleLepton::chargedIsoPtSum() const {return m_chargedIsoPtSum;}
float NtupleLepton::decayModeFinding() const {return m_decayModeFinding;}
float NtupleLepton::decayModeFindingNewDMs() const {return m_decayModeFindingNewDMs;}
float NtupleLepton::neutralIsoPtSum() const {return m_neutralIsoPtSum;}
float NtupleLepton::puCorrPtSum() const {return m_puCorrPtSum;}
LorentzVector NtupleLepton::genJet_p4() const {return m_genJet_p4;}
float NtupleLepton::numStrips() const {return m_numStrips;}
float NtupleLepton::numHadrons() const {return m_numHadrons;}
