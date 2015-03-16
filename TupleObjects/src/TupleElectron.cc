#include "DavisRunIITauTau/TupleObjects/interface/TupleElectron.h"


TupleElectron::TupleElectron()
{
  m_p4.SetXYZT(NAN,NAN,NAN,NAN);

}

//////////////////
// p4
//////////////////
void TupleElectron::set_p4(LorentzVector p4_) { m_p4 = p4_;}
LorentzVector TupleElectron::p4() const { return m_p4; }
