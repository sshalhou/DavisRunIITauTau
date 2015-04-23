/* custom lepton object to allow interchangable access
of pat::Electron, pat::Muon, & pat::Tau parameters 
blind of the specific lepton type
*/




#ifndef DavisRunIITauTau_TupleObjects_TupleLepton_h
#define DavisRunIITauTau_TupleObjects_TupleLepton_h


// system include files
#include <memory>



#include <vector>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"



typedef math::XYZTLorentzVector LorentzVector;

class TupleLepton 
{



public:

  TupleLepton();
  virtual ~TupleLepton(){}

  // fillers

  void fill(pat::Electron);
  void fill(pat::Muon);
  void fill(pat::Tau);
 
  // getters

  LorentzVector p4() const;
  bool isElectron() const;
  bool isMuon() const;
  bool isTau() const;


private:

  LorentzVector m_p4;
  bool m_isElectron;
  bool m_isMuon;
  bool m_isTau;


};

typedef std::vector<TupleLepton> TupleLeptonCollection;

#endif
