#ifndef UserCode_TupleObjects_TupleTau_h
#define UserCode_TupleObjects_TupleTau_h


// system include files
#include <memory>



// needed by ntuple Taus producer
#include <vector>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"

typedef math::XYZTLorentzVector LorentzVector;

class TupleTau
{



public:

  TupleTau();
  virtual ~TupleTau(){}

  // setters

  void set_p4(LorentzVector);

  // getters

  LorentzVector p4() const;


private:

  LorentzVector m_p4;
 



};

typedef std::vector<TupleTau> TupleTauCollection;

#endif
