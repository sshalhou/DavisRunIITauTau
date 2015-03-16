#include "UserCode/TupleObjects/interface/TupleTau.h"


TupleTau::TupleTau()
{
  m_p4.SetXYZT(NAN,NAN,NAN,NAN);

}

//////////////////
// p4
//////////////////
void TupleTau::set_p4(LorentzVector p4_) { m_p4 = p4_;}
LorentzVector TupleTau::p4() const { return m_p4; }
