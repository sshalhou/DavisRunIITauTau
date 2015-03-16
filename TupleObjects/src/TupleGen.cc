#include "UserCode/TupleObjects/interface/TupleGen.h"


TupleGen::TupleGen()
{
  m_p4.SetXYZT(NAN,NAN,NAN,NAN);

}

//////////////////
// p4
//////////////////
void TupleGen::set_p4(LorentzVector p4_) { m_p4 = p4_;}
LorentzVector TupleGen::p4() const { return m_p4; }
