#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
TupleCandidateEventTypes candTypes_;


TupleCandidateEvent::TupleCandidateEvent()
{

	CandidateEventType = NAN;

}

////////////////
// pairs

void TupleCandidateEvent::set_pair(pat::Electron dummy1_, pat::Electron dummy2_) 
	{ 
		m_electron1 = dummy1_; 
		m_electron2 = dummy2_; 
		CandidateEventType = candTypes_.EleEle;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);

	}

void TupleCandidateEvent::set_pair(pat::Electron dummy1_, pat::Muon dummy2_) 
	{ 
		m_electron1 = dummy1_; 
		m_muon2 = dummy2_; 
		CandidateEventType = candTypes_.EleMuon;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);		

	}

void TupleCandidateEvent::set_pair(pat::Electron dummy1_, pat::Tau dummy2_) 
	{ 
		m_electron1 = dummy1_; 
		m_tau2 = dummy2_; 
		CandidateEventType = candTypes_.EleTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);
	}

void TupleCandidateEvent::set_pair(pat::Muon dummy1_,     pat::Muon dummy2_) 
	{ 
		m_muon1 = dummy1_; 
		m_muon2 = dummy2_; 
		CandidateEventType = candTypes_.MuonMuon;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);
	}

void TupleCandidateEvent::set_pair(pat::Muon dummy1_,     pat::Tau dummy2_) 
	{ 
		m_muon1 = dummy1_; 
		m_tau2 = dummy2_; 
		CandidateEventType = candTypes_.MuonTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);
	}

void TupleCandidateEvent::set_pair(pat::Tau dummy1_,      pat::Tau dummy2_) 
	{ 
		m_tau1 = dummy1_; 
		m_tau2 = dummy2_; 
		CandidateEventType = candTypes_.TauTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);

	}



//////////////////
// legs
//////////////////
TupleLepton TupleCandidateEvent::leg1() const { return m_leg1; }

TupleLepton TupleCandidateEvent::leg2() const { return m_leg2; }


//////////////////
// taus
//////////////////
pat::Tau TupleCandidateEvent::tau1() const { return m_tau1; }

pat::Tau TupleCandidateEvent::tau2() const { return m_tau2; }

//////////////////
// electrons
//////////////////

pat::Electron TupleCandidateEvent::electron1() const { return m_electron1; }

pat::Electron TupleCandidateEvent::electron2() const { return m_electron2; }

//////////////////
// muons
//////////////////
pat::Muon TupleCandidateEvent::muon1() const { return m_muon1; }

pat::Muon TupleCandidateEvent::muon2() const { return m_muon2; }
