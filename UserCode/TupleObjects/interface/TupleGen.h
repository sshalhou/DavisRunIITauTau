#ifndef UserCode_TupleObjects_TupleGen_h
#define UserCode_TupleObjects_TupleGen_h


// system include files
#include <memory>



// needed by ntuple Gens producer
#include <vector>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"

typedef math::XYZTLorentzVector LorentzVector;

class TupleGen
{



public:

  TupleGen();
  virtual ~TupleGen(){}

  // setters

  void set_p4(LorentzVector);

  // getters

  LorentzVector p4() const;


private:

  LorentzVector m_p4;
 



};

typedef std::vector<TupleGen> TupleGenCollection;

#endif
