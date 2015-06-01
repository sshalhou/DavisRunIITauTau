#include "DavisRunIITauTau/NtupleObjects/interface/NtupleGenParticle.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "TLorentzVector.h"

NtupleGenParticle::NtupleGenParticle()
{
 
  m_gen_pdgId  = -999;
  m_gen_status  = -999;
  m_gen_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_gen_vertex_x = NAN;
  m_gen_vertex_y = NAN;
  m_gen_vertex_z = NAN;
 


}


// filler 

  void NtupleGenParticle::initialize(reco::GenParticle genPart)
  {

    m_gen_pdgId = genPart.pdgId();
    m_gen_status = genPart.status();
    m_gen_p4 = genPart.p4();
    m_gen_vertex_x = genPart.vertex().Z();
    m_gen_vertex_y = genPart.vertex().Y();
    m_gen_vertex_z = genPart.vertex().X();

  }



  void NtupleGenParticle::add_daughter(int ID, int STATUS, LorentzVector P4)
  {
      m_daughters_pdgId.push_back(ID);
      m_daughters_status.push_back(STATUS);
      m_daughters_gen_p4.push_back(P4);
  }
  void NtupleGenParticle::add_mother(int ID, int STATUS, LorentzVector P4)
  {

      m_mothers_pdgId.push_back(ID);
      m_mothers_status.push_back(STATUS);
      m_mothers_gen_p4.push_back(P4);

  }


// getters 
 
  int NtupleGenParticle::gen_pdgId() const { return m_gen_pdgId; }
  int NtupleGenParticle::gen_status() const { return m_gen_status; } 
  LorentzVector NtupleGenParticle::gen_p4() const { return m_gen_p4; } 
  float NtupleGenParticle::gen_vertex_x() const { return m_gen_vertex_x; } 
  float NtupleGenParticle::gen_vertex_y() const { return m_gen_vertex_y; } 
  float NtupleGenParticle::gen_vertex_z() const { return m_gen_vertex_z; } 
  std::vector <int> NtupleGenParticle::daughters_pdgId() const { return m_daughters_pdgId; } 
  std::vector <int> NtupleGenParticle::daughters_status() const { return m_daughters_status; } 
  std::vector <LorentzVector> NtupleGenParticle::daughters_gen_p4() const { return m_daughters_gen_p4; } 
  std::vector <int> NtupleGenParticle::mothers_pdgId() const { return m_mothers_pdgId; } 
  std::vector <int> NtupleGenParticle::mothers_status() const { return m_mothers_status; } 
  std::vector <LorentzVector> NtupleGenParticle::mothers_gen_p4() const { return m_mothers_gen_p4; } 


