#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"


TupleLepton::TupleLepton()
{
  m_p4.SetXYZT(NAN,NAN,NAN,NAN);
  m_isElectron = 0;
  m_isMuon = 0;
  m_isTau = 0;

}

void TupleLepton::fill(pat::Electron dummy)
{

	m_p4 = dummy.p4();
	m_isElectron = 1;

}


void TupleLepton::fill(pat::Muon dummy)
{

	m_p4 = dummy.p4();
	m_isMuon = 1;

}

void TupleLepton::fill(pat::Tau dummy)
{

	m_p4 = dummy.p4();
	m_isTau = 1;

}


//////////////////
// accessors
//////////////////
LorentzVector TupleLepton::p4() const { return m_p4; }
bool TupleLepton::isElectron() const { return m_isElectron; }
bool TupleLepton::isMuon() const { return m_isMuon; }
bool TupleLepton::isTau() const { return m_isTau; }


