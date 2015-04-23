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

  TupleLepton leg1() const;
  TupleLepton leg2() const;
  pat::Tau tau1() const;
  pat::Tau tau2() const;
  pat::Electron electron1() const;
  pat::Electron electron2() const;
  pat::Muon muon1() const;
  pat::Muon muon2() const;



private:

  TupleLepton m_leg1;
  TupleLepton m_leg2;
  pat::Tau m_tau1;
  pat::Tau m_tau2;
  pat::Electron m_electron1;
  pat::Electron m_electron2;
  pat::Muon m_muon1;
  pat::Muon m_muon2;

};

typedef std::vector<TupleCandidateEvent> TupleCandidateEventCollection;

#endif
