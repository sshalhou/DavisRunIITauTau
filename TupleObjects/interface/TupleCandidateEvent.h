/* class to hold candidate events for H->tau tau analyses
each instance contains 2 leptons that can be any combination of
pat::Electron, pat::Muon, or pat::Tau (rankings to be defined later),
and a description of the event content 
MVA MET, SVMass, Jets, etc. will also be added here as well  */

#ifndef DavisRunIITauTau_TupleObjects_TupleCandidateEvent_h
#define DavisRunIITauTau_TupleObjects_TupleCandidateEvent_h


// system include files
#include <memory>
#include <vector>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"

typedef math::XYZTLorentzVector LorentzVector;



class TupleCandidateEvent
{



public:

  TupleCandidateEvent();
  virtual ~TupleCandidateEvent(){}


  // setters

  void set_leg1(const pat::Electron);
  void set_leg2(const pat::Electron);
  void set_leg1(const pat::Muon);
  void set_leg2(const pat::Muon);
  void set_leg1(const pat::Tau);
  void set_leg2(const pat::Tau);
  void set_CandidateEventType(); // dont forget to call this!


  void set_pair(pat::Electron, pat::Electron);
  void set_pair(pat::Electron, pat::Muon);
  void set_pair(pat::Electron, pat::Tau);
  void set_pair(pat::Muon, pat::Muon);
  void set_pair(pat::Muon, pat::Tau);
  void set_pair(pat::Tau, pat::Tau);
  void set_mvaMET(pat::MET); 
  void set_puppiMET(pat::MET); 
  void set_pfMET(pat::MET); 
  void set_pfMET_covMatrix(double,double,double,double);  // 00, 01, 10, 11 is the order  
  void set_vetoElectron(pat::Electron);
  void set_vetoMuon(pat::Muon);
  void set_SVMass(double);
  void set_SVTransverseMass(double);

  // getters
  
  int CandidateEventType() const;
  TupleLepton leg1() const;
  TupleLepton leg2() const;
  std::vector<pat::MET>  mvaMET() const;
  std::vector<pat::MET>  pfMET() const;
  std::vector<pat::MET>  puppiMET() const;
  std::vector<double>  pfMET_cov00() const;
  std::vector<double>  pfMET_cov01() const;
  std::vector<double>  pfMET_cov10() const;
  std::vector<double>  pfMET_cov11() const;  
  std::vector<pat::Electron> vetoElectron() const;
  std::vector<pat::Muon> vetoMuon() const;
  std::vector<double> SVMass() const;
  std::vector<double> SVTransverseMass() const;

private:


  int m_CandidateEventType; 
  TupleLepton m_leg1;
  TupleLepton m_leg2;
  std::vector<pat::MET>  m_mvaMET; // note : keep as a vector in case systematic variants are needed 
  std::vector<pat::MET>  m_pfMET; 
  std::vector<pat::MET>  m_puppiMET; 
  std::vector<double>  m_pfMET_cov00; // needed due to missing sig matrix in phys14/Spring15 samples
  std::vector<double>  m_pfMET_cov01; // needed due to missing sig matrix in phys14/Spring15 samples
  std::vector<double>  m_pfMET_cov10; // needed due to missing sig matrix in phys14/Spring15 samples
  std::vector<double>  m_pfMET_cov11; // needed due to missing sig matrix in phys14/Spring15 samples
  std::vector<pat::Electron> m_vetoElectron;
  std::vector<pat::Muon> m_vetoMuon;
  std::vector<double> m_SVMass;
  std::vector<double> m_SVTransverseMass;

};

typedef std::vector<TupleCandidateEvent> TupleCandidateEventCollection;

#endif
