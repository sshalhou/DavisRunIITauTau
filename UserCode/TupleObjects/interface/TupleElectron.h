#ifndef UserCode_TupleObjects_TupleElectron_h
#define UserCode_TupleObjects_TupleElectron_h


// system include files
#include <memory>



// needed by ntuple Electrons producer
#include <vector>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"

typedef math::XYZTLorentzVector LorentzVector;

class TupleElectron
{



public:

  TupleElectron();
  virtual ~TupleElectron(){}

  // setters

  void set_p4(LorentzVector);

  // getters

  LorentzVector p4() const;


private:

  LorentzVector m_p4;
 



};

typedef std::vector<TupleElectron> TupleElectronCollection;

#endif
