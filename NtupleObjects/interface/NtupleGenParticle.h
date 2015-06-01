#ifndef DavisRunIITauTau_NtupleObjects_NtupleGenParticle_h
#define DavisRunIITauTau_NtupleObjects_NtupleGenParticle_h


// system include files
#include <memory>



// needed by ntuple Muons producer
#include <vector>
#include <string>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;

class NtupleGenParticle
{



public:

  NtupleGenParticle();
  virtual ~NtupleGenParticle(){}

  // fillers 

  void initialize(reco::GenParticle);
  void add_daughter(int, int, LorentzVector); /* pdgId, status, p4 */
  void add_mother(int, int, LorentzVector); /* pdgId, status, p4 */


 
  // getters
 
  int gen_pdgId() const; 
  int gen_status() const; 
  LorentzVector gen_p4() const; 
  float gen_vertex_x() const; 
  float gen_vertex_y() const; 
  float gen_vertex_z() const; 
  std::vector <int> daughters_pdgId() const; 
  std::vector <int> daughters_status() const; 
  std::vector <LorentzVector> daughters_gen_p4() const; 
  std::vector <int> mothers_pdgId() const; 
  std::vector <int> mothers_status() const; 
  std::vector <LorentzVector> mothers_gen_p4() const; 


private:

  /* idea is that every genParticle contains knowledge of mother and all daughters */
  int m_gen_pdgId;
  int m_gen_status;
  LorentzVector m_gen_p4;
  float m_gen_vertex_x;
  float m_gen_vertex_y;
  float m_gen_vertex_z;
  std::vector <int> m_daughters_pdgId;
  std::vector <int> m_daughters_status;
  std::vector <LorentzVector> m_daughters_gen_p4;
  std::vector <int> m_mothers_pdgId;
  std::vector <int> m_mothers_status;
  std::vector <LorentzVector> m_mothers_gen_p4;



};

typedef std::vector<NtupleGenParticle> NtupleGenParticleCollection;

#endif
