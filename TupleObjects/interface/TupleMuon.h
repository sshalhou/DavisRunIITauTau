#ifndef DavisRunIITauTau_TupleObjects_TupleMuon_h
#define DavisRunIITauTau_TupleObjects_TupleMuon_h


// system include files
#include <memory>



// needed by ntuple Muons producer
#include <vector>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"

typedef math::XYZTLorentzVector LorentzVector;

class TupleMuon
{



public:

  TupleMuon();
  virtual ~TupleMuon(){}

  // setters

  void set_p4(LorentzVector);

  // getters

  LorentzVector p4() const;


private:

  LorentzVector m_p4;
 



};

typedef std::vector<TupleMuon> TupleMuonCollection;

#endif
