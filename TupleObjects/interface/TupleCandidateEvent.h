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

  // pair type 
  int CandidateEventType; 

  // setters

  void set_pair(pat::Electron, pat::Electron);
  void set_pair(pat::Electron, pat::Muon);
  void set_pair(pat::Electron, pat::Tau);
  void set_pair(pat::Muon, pat::Muon);
  void set_pair(pat::Muon, pat::Tau);
  void set_pair(pat::Tau, pat::Tau);
  void set_mvaMET(reco::PFMET); 
  void set_vetoElectron(pat::Electron);
  void set_vetoMuon(pat::Muon);


  TupleLepton leg1() const;
  TupleLepton leg2() const;
  std::vector<reco::PFMET>  mvaMET() const;
  std::vector<pat::Electron> vetoElectron() const;
  std::vector<pat::Muon> vetoMuon() const;


private:

  TupleLepton m_leg1;
  TupleLepton m_leg2;
  std::vector<reco::PFMET>  m_mvaMET;
  std::vector<pat::Electron> m_vetoElectron;
  std::vector<pat::Muon> m_vetoMuon;


};

typedef std::vector<TupleCandidateEvent> TupleCandidateEventCollection;

#endif
