#ifndef UserCode_TupleObjects_TupleJet_h
#define UserCode_TupleObjects_TupleJet_h


// system include files
#include <memory>



// needed by ntuple Jets producer
#include <vector>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"

typedef math::XYZTLorentzVector LorentzVector;

class TupleJet
{



public:

  TupleJet();
  virtual ~TupleJet(){}

  // setters

  void set_p4(LorentzVector);

  // getters

  LorentzVector p4() const;


private:

  LorentzVector m_p4;
 



};

typedef std::vector<TupleJet> TupleJetCollection;

#endif
