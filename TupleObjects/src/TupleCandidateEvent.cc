#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"


TupleCandidateEvent::TupleCandidateEvent()
{

	m_CandidateEventType = -999;
}

////////////////
// pairs

void TupleCandidateEvent::set_pair(pat::Electron dummy1_, pat::Electron dummy2_) 
	{ 

		m_CandidateEventType = TupleCandidateEventTypes::EleEle;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);

	}

void TupleCandidateEvent::set_pair(pat::Electron dummy1_, pat::Muon dummy2_) 
	{ 

		m_CandidateEventType = TupleCandidateEventTypes::EleMuon;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);		

	}

void TupleCandidateEvent::set_pair(pat::Electron dummy1_, pat::Tau dummy2_) 
	{ 

		m_CandidateEventType = TupleCandidateEventTypes::EleTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);
	}

void TupleCandidateEvent::set_pair(pat::Muon dummy1_,     pat::Muon dummy2_) 
	{ 
	
		m_CandidateEventType = TupleCandidateEventTypes::MuonMuon;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);
	}

void TupleCandidateEvent::set_pair(pat::Muon dummy1_,     pat::Tau dummy2_) 
	{ 

		m_CandidateEventType = TupleCandidateEventTypes::MuonTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);
	}

void TupleCandidateEvent::set_pair(pat::Tau dummy1_,      pat::Tau dummy2_) 
	{ 

		m_CandidateEventType = TupleCandidateEventTypes::TauTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);

	}

// single objects


void TupleCandidateEvent::set_mvaMET(reco::PFMET dummy_) 
	{ 
		m_mvaMET.push_back(dummy_);
	}


void TupleCandidateEvent::set_pfMET(pat::MET dummy_) 
	{ 
		m_pfMET.push_back(dummy_);
	}


void TupleCandidateEvent::set_pfMET_covMatrix(double cov00,double cov01,double cov10,double cov11)
	{
 		m_pfMET_cov00.push_back(cov00);
 		m_pfMET_cov01.push_back(cov01);
 		m_pfMET_cov10.push_back(cov10);
 		m_pfMET_cov11.push_back(cov11);

	}




void TupleCandidateEvent::set_vetoMuon(pat::Muon dummy_) 
	{ 
		m_vetoMuon.push_back(dummy_);
	}

void TupleCandidateEvent::set_vetoElectron(pat::Electron dummy_) 
	{ 
		m_vetoElectron.push_back(dummy_);
	}

void TupleCandidateEvent::set_SVMass(double dummy_) 
	{ 
		m_SVMass.push_back(dummy_);
	}


//////////////////
// accessors
//////////////////
int TupleCandidateEvent::CandidateEventType() const { return m_CandidateEventType; }
TupleLepton TupleCandidateEvent::leg1() const { return m_leg1; }
TupleLepton TupleCandidateEvent::leg2() const { return m_leg2; }
std::vector<reco::PFMET> TupleCandidateEvent::mvaMET() const { return m_mvaMET; }
std::vector<pat::MET> TupleCandidateEvent::pfMET() const { return m_pfMET; }
std::vector<double> TupleCandidateEvent::pfMET_cov00() const { return m_pfMET_cov00; }
std::vector<double> TupleCandidateEvent::pfMET_cov01() const { return m_pfMET_cov01; }
std::vector<double> TupleCandidateEvent::pfMET_cov10() const { return m_pfMET_cov10; }
std::vector<double> TupleCandidateEvent::pfMET_cov11() const { return m_pfMET_cov11; }
std::vector<pat::Electron> TupleCandidateEvent::vetoElectron() const { return m_vetoElectron; }
std::vector<pat::Muon> TupleCandidateEvent::vetoMuon() const { return m_vetoMuon; }
std::vector<double> TupleCandidateEvent::SVMass() const {return m_SVMass;} 


