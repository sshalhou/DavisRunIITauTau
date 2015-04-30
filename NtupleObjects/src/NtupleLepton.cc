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
 

}

// helpers

////////////////////////////////////////////////////////////////////
// print some of the member data - useful for debugging
////////////////////////////////////////////////////////////////////
void NtupleLepton::printLEP()
{

  std::cout<<"<LEPPRINT> ------------------> START: printing lepton \n";
  std::cout<<"<LEPPRINT> leptonType is "<<m_leptonType<<"\n";
  std::cout<<"<LEPPRINT> charge is "<<m_charge<<"\n";
  std::cout<<"<LEPPRINT> PF pdgId is "<<m_PFpdgId<<"\n";
  std::cout<<"<LEPPRINT> reco Pt,Eta,Phi,M "<<m_p4.Pt()<<" , "<<m_p4.Eta()<<" , "<<m_p4.Phi()<<" , "<<m_p4.M()<<"\n";
  std::cout<<"<LEPPRINT> GEN pdgId is "<<m_GENpdgId<<"\n";
  std::cout<<"<LEPPRINT> gen Pt,Eta,Phi,M "<<m_gen_p4.Pt()<<" , "<<m_gen_p4.Eta()<<" , "<<m_gen_p4.Phi()<<" , "<<m_gen_p4.M()<<"\n";
  std::cout<<"<LEPPRINT> GENMOTHER pdgId is "<<m_GENMOTHERpdgId<<"\n";
  std::cout<<"<LEPPRINT> gen mother Pt,Eta,Phi,M "<<m_genMother_p4.Pt()<<" , "<<m_genMother_p4.Eta()<<" , "<<m_genMother_p4.Phi()<<" , "<<m_genMother_p4.M()<<"\n";
  std::cout<<"<LEPPRINT> EffectiveArea "<<m_EffectiveArea<<"\n";
  std::cout<<"<LEPPRINT> dz "<<m_dz<<"\n";
  std::cout<<"<LEPPRINT> dxy "<<m_dxy<<"\n";
  std::cout<<"<LEPPRINT> known rho types and values : ";
    for(std::size_t i=0;i<m_rho_Labels.size();++i) std::cout<<"[ "<<m_rho_Labels[i]<<" = "<<m_rho_Values[i]<<" ] ";
    std::cout<<"\n";
  std::cout<<"<LEPPRINT> known relIso types and values : ";
    for(std::size_t i=0;i<m_relativeIsol_Labels.size();++i) std::cout<<"[ "<<m_relativeIsol_Labels[i]<<" = "<<m_relativeIsol_Values[i]<<" ] ";
    std::cout<<"\n";
  std::cout<<"<LEPPRINT> HLT ACCEPTED PATHS and PreScales : ";
    for(std::size_t i=0;i<m_HLTacceptedPaths.size();++i) std::cout<<"[ "<<m_HLTacceptedPaths[i]<<" = "<<m_HLTacceptedPathPreScales[i]<<" ] ";
    std::cout<<"\n";
 
  std::cout<<"<LEPPRINT> L1 trig obj Pt,Eta,Phi,M "<<m_L1TrigObj_p4.Pt()<<" , "<<m_L1TrigObj_p4.Eta()<<" , "<<m_L1TrigObj_p4.Phi()<<" , "<<m_L1TrigObj_p4.M()<<"\n";
  std::cout<<"<LEPPRINT> L1 trig obj minDR "<<m_L1TrigObjRecoObjDeltaR<<"\n";
  std::cout<<"<LEPPRINT> L1 trig obj's filters : ";
    for(std::size_t i=0;i<m_L1acceptedFilters.size();++i) std::cout<<"[ "<<m_L1acceptedFilters[i]<<" ] ";
    std::cout<<"\n";

  std::cout<<"<LEPPRINT> L3 trig obj Pt,Eta,Phi,M "<<m_L3TrigObj_p4.Pt()<<" , "<<m_L3TrigObj_p4.Eta()<<" , "<<m_L3TrigObj_p4.Phi()<<" , "<<m_L3TrigObj_p4.M()<<"\n";
  std::cout<<"<LEPPRINT> L3 trig obj minDR "<<m_L3TrigObjRecoObjDeltaR<<"\n";
  std::cout<<"<LEPPRINT> L3 trig obj's filters : ";
    for(std::size_t i=0;i<m_L3acceptedFilters.size();++i) std::cout<<"[ "<<m_L3acceptedFilters[i]<<" ] ";
    std::cout<<"\n";

  std::cout<<"<LEPPRINT> HLT isBOTH  : ";
    for(std::size_t i=0;i<m_pathSummary_isBOTH.size();++i) std::cout<<"[ "<<m_pathSummary_isBOTH[i]<<" ] ";
    std::cout<<"\n";  

  std::cout<<"<LEPPRINT> HLT isL3  : ";
    for(std::size_t i=0;i<m_pathSummary_isL3.size();++i) std::cout<<"[ "<<m_pathSummary_isL3[i]<<" ] ";
    std::cout<<"\n";  

  std::cout<<"<LEPPRINT> HLT isLF  : ";
    for(std::size_t i=0;i<m_pathSummary_isLF.size();++i) std::cout<<"[ "<<m_pathSummary_isLF[i]<<" ] ";
    std::cout<<"\n";  

  std::cout<<"<LEPPRINT> HLT all config filters passed  : ";
    for(std::size_t i=0;i<m_pathSummary_filterListPassed.size();++i) std::cout<<"[ "<<m_pathSummary_filterListPassed[i]<<" ] ";
    std::cout<<"\n";  

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
    else std::cout<<" NOT STORED "<<labels_[i]<<"\n";

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


