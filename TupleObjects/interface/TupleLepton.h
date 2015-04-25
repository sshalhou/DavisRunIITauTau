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

#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"


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

  int leptonType() const;


 std::vector< pat::Electron > Electron() const;
 std::vector< pat::Muon > Muon() const;
 std::vector< pat::Tau > Tau() const;

private:

  int m_leptonType;
  std::vector<pat::Electron> m_Electron;
  std::vector<pat::Muon> m_Muon;
  std::vector<pat::Tau> m_Tau;


};

typedef std::vector<TupleLepton> TupleLeptonCollection;

#endif
