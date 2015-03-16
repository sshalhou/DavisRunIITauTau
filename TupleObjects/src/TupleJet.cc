#include "DavisRunIITauTau/TupleObjects/interface/TupleJet.h"


TupleJet::TupleJet()
{
  m_p4.SetXYZT(NAN,NAN,NAN,NAN);

}

//////////////////
// p4
//////////////////
void TupleJet::set_p4(LorentzVector p4_) { m_p4 = p4_;}
LorentzVector TupleJet::p4() const { return m_p4; }
