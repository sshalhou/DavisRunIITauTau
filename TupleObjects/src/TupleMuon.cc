#include "DavisRunIITauTau/TupleObjects/interface/TupleMuon.h"


TupleMuon::TupleMuon()
{
  m_p4.SetXYZT(NAN,NAN,NAN,NAN);

}

//////////////////
// p4
//////////////////
void TupleMuon::set_p4(LorentzVector p4_) { m_p4 = p4_;}
LorentzVector TupleMuon::p4() const { return m_p4; }
