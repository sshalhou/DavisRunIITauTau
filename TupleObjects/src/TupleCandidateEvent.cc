#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"


TupleCandidateEvent::TupleCandidateEvent()
{

	CandidateEventType = 0;

}

////////////////
// pairs

void TupleCandidateEvent::set_pair(pat::Electron dummy1_, pat::Electron dummy2_) 
	{ 

		CandidateEventType = TupleCandidateEventTypes::EleEle;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);

	}

void TupleCandidateEvent::set_pair(pat::Electron dummy1_, pat::Muon dummy2_) 
	{ 

		CandidateEventType = TupleCandidateEventTypes::EleMuon;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);		

	}

void TupleCandidateEvent::set_pair(pat::Electron dummy1_, pat::Tau dummy2_) 
	{ 

		CandidateEventType = TupleCandidateEventTypes::EleTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);
	}

void TupleCandidateEvent::set_pair(pat::Muon dummy1_,     pat::Muon dummy2_) 
	{ 
	
		CandidateEventType = TupleCandidateEventTypes::MuonMuon;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);
	}

void TupleCandidateEvent::set_pair(pat::Muon dummy1_,     pat::Tau dummy2_) 
	{ 

		CandidateEventType = TupleCandidateEventTypes::MuonTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);
	}

void TupleCandidateEvent::set_pair(pat::Tau dummy1_,      pat::Tau dummy2_) 
	{ 

		CandidateEventType = TupleCandidateEventTypes::TauTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);

	}

// single objects


void TupleCandidateEvent::set_mvaMET(reco::PFMET dummy_) 
	{ 
		m_mvaMET.push_back(dummy_);
	}


void TupleCandidateEvent::set_vetoMuon(pat::Muon dummy_) 
	{ 
		m_vetoMuon.push_back(dummy_);
	}

void TupleCandidateEvent::set_vetoElectron(pat::Electron dummy_) 
	{ 
		m_vetoElectron.push_back(dummy_);
	}


//////////////////
// accessors
//////////////////
TupleLepton TupleCandidateEvent::leg1() const { return m_leg1; }
TupleLepton TupleCandidateEvent::leg2() const { return m_leg2; }
std::vector<reco::PFMET> TupleCandidateEvent::mvaMET() const { return m_mvaMET; }
std::vector<pat::Electron> TupleCandidateEvent::vetoElectron() const { return m_vetoElectron; }
std::vector<pat::Muon> TupleCandidateEvent::vetoMuon() const { return m_vetoMuon; }



