#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"


TupleLepton::TupleLepton()
{
	m_leptonType = 0;
}

void TupleLepton::fill(pat::Electron dummy)
{

	m_Electron.push_back(dummy);
	m_leptonType = TupleLeptonTypes::anElectron;

}


void TupleLepton::fill(pat::Muon dummy)
{
	m_Muon.push_back(dummy);
	m_leptonType = TupleLeptonTypes::aMuon;


}

void TupleLepton::fill(pat::Tau dummy)
{


	m_Tau.push_back(dummy);
	m_leptonType = TupleLeptonTypes::aTau;


}


//////////////////
// accessors
//////////////////
int TupleLepton::leptonType() const { return m_leptonType; }
std::vector<pat::Electron> TupleLepton::Electron() const { return m_Electron; }
std::vector<pat::Muon> TupleLepton::Muon() const { return m_Muon; }
std::vector<pat::Tau> TupleLepton::Tau() const { return m_Tau; }
