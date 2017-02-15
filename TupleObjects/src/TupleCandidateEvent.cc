#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"


TupleCandidateEvent::TupleCandidateEvent()
{

	m_CandidateEventType = -999;
}



// set up pair one leg at a time
// use these for 76X and above

  void TupleCandidateEvent::set_leg1(const pat::Electron dummy1_) {m_leg1.fill(dummy1_);}
  void TupleCandidateEvent::set_leg2(const pat::Electron dummy2_) {m_leg2.fill(dummy2_);}
  void TupleCandidateEvent::set_leg1(const pat::Muon dummy1_) {m_leg1.fill(dummy1_);}
  void TupleCandidateEvent::set_leg2(const pat::Muon dummy2_) {m_leg2.fill(dummy2_);}
  void TupleCandidateEvent::set_leg1(const pat::Tau dummy1_) {m_leg1.fill(dummy1_);}
  void TupleCandidateEvent::set_leg2(const pat::Tau dummy2_) {m_leg2.fill(dummy2_);}

// add leptons for efficiency measurements 

  void TupleCandidateEvent::add_EfficiencyLepton(const pat::Electron dummy_)
  {
  	TupleLepton TEMP;
  	TEMP.fill(dummy_);
  	m_EfficiencyLepton.push_back(TEMP);
  } 
  void TupleCandidateEvent::add_EfficiencyLepton(const pat::Muon dummy_) 
  {
   	TupleLepton TEMP;
  	TEMP.fill(dummy_);
  	m_EfficiencyLepton.push_back(TEMP); 	
  } 
  void TupleCandidateEvent::add_EfficiencyLepton(const pat::Tau dummy_) 
  {
    TupleLepton TEMP;
  	TEMP.fill(dummy_);
  	m_EfficiencyLepton.push_back(TEMP);	
  } 

void TupleCandidateEvent::set_CandidateEventType(int dummy_)
  {
  	m_CandidateEventType = dummy_;
  }


  void TupleCandidateEvent::set_CandidateEventType()
  {
  	if(m_leg1.leptonType()==TupleLeptonTypes::anElectron && m_leg2.leptonType()==TupleLeptonTypes::anElectron)
  	{
  		m_CandidateEventType = TupleCandidateEventTypes::EleEle;
  	}
  	

  	else if(m_leg1.leptonType()==TupleLeptonTypes::anElectron && m_leg2.leptonType()==TupleLeptonTypes::aMuon)
  	{
  		m_CandidateEventType = TupleCandidateEventTypes::EleMuon;
  	}
  	else if(m_leg2.leptonType()==TupleLeptonTypes::anElectron && m_leg1.leptonType()==TupleLeptonTypes::aMuon)
  	{
  		m_CandidateEventType = TupleCandidateEventTypes::EleMuon;
  	}
  	

  	else if(m_leg1.leptonType()==TupleLeptonTypes::anElectron && m_leg2.leptonType()==TupleLeptonTypes::aTau)
  	{
  		m_CandidateEventType = TupleCandidateEventTypes::EleTau;
  	}
  	else if(m_leg2.leptonType()==TupleLeptonTypes::anElectron && m_leg1.leptonType()==TupleLeptonTypes::aTau)
  	{
  		m_CandidateEventType = TupleCandidateEventTypes::EleTau;
  	}


  	else if(m_leg1.leptonType()==TupleLeptonTypes::aMuon && m_leg2.leptonType()==TupleLeptonTypes::aMuon)
  	{
  		m_CandidateEventType = TupleCandidateEventTypes::MuonMuon;
  	}
  	
  	else if(m_leg1.leptonType()==TupleLeptonTypes::aMuon && m_leg2.leptonType()==TupleLeptonTypes::aTau)
  	{
  		m_CandidateEventType = TupleCandidateEventTypes::MuonTau;
  	}
  	else if(m_leg2.leptonType()==TupleLeptonTypes::aMuon && m_leg1.leptonType()==TupleLeptonTypes::aTau)
  	{
  		m_CandidateEventType = TupleCandidateEventTypes::MuonTau;
  	}

  	else if(m_leg2.leptonType()==TupleLeptonTypes::aTau && m_leg1.leptonType()==TupleLeptonTypes::aTau)
  	{
  		m_CandidateEventType = TupleCandidateEventTypes::TauTau;
  	}

  	//std::cout<<" ASSIGNED "<<m_CandidateEventType<<"\n";

  }



////////////////
// pairs -- these are no longer used in 76X

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

void TupleCandidateEvent::set_pair(pat::Tau dummy1_, pat::Tau dummy2_) 
	{ 

		m_CandidateEventType = TupleCandidateEventTypes::TauTau;
		m_leg1.fill(dummy1_);
		m_leg2.fill(dummy2_);

	}

// single objects


void TupleCandidateEvent::set_mvaMET(pat::MET dummy_) 
	{ 
		m_mvaMET.push_back(dummy_);
	}


void TupleCandidateEvent::set_pfMET(pat::MET dummy_) 
	{ 
		m_pfMET.push_back(dummy_);
	}


void TupleCandidateEvent::set_puppiMET(pat::MET dummy_) 
	{ 
		m_puppiMET.push_back(dummy_);
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


void TupleCandidateEvent::set_vetoTau(pat::Tau dummy_) 
  { 
    m_vetoTau.push_back(dummy_);
  }


void TupleCandidateEvent::set_vetoElectron(pat::Electron dummy_) 
	{ 
		m_vetoElectron.push_back(dummy_);
	}

void TupleCandidateEvent::set_SVMass(double dummy_) 
	{ 
		m_SVMass.push_back(dummy_);
	}


void TupleCandidateEvent::set_SVTransverseMass(double dummy_) 
	{ 
		m_SVTransverseMass.push_back(dummy_);
	}




//////////////////
// accessors
//////////////////
int TupleCandidateEvent::CandidateEventType() const { return m_CandidateEventType; }
TupleLepton TupleCandidateEvent::leg1() const { return m_leg1; }
TupleLepton TupleCandidateEvent::leg2() const { return m_leg2; }
std::vector<TupleLepton> TupleCandidateEvent::EfficiencyLepton() const {return m_EfficiencyLepton;}
std::vector<pat::MET> TupleCandidateEvent::mvaMET() const { return m_mvaMET; }
std::vector<pat::MET> TupleCandidateEvent::pfMET() const { return m_pfMET; }
std::vector<pat::MET> TupleCandidateEvent::puppiMET() const { return m_puppiMET; }
std::vector<double> TupleCandidateEvent::pfMET_cov00() const { return m_pfMET_cov00; }
std::vector<double> TupleCandidateEvent::pfMET_cov01() const { return m_pfMET_cov01; }
std::vector<double> TupleCandidateEvent::pfMET_cov10() const { return m_pfMET_cov10; }
std::vector<double> TupleCandidateEvent::pfMET_cov11() const { return m_pfMET_cov11; }
std::vector<pat::Electron> TupleCandidateEvent::vetoElectron() const { return m_vetoElectron; }
std::vector<pat::Muon> TupleCandidateEvent::vetoMuon() const { return m_vetoMuon; }
std::vector<pat::Tau> TupleCandidateEvent::vetoTau() const { return m_vetoTau; }
std::vector<double> TupleCandidateEvent::SVMass() const {return m_SVMass;} 
std::vector<double> TupleCandidateEvent::SVTransverseMass() const {return m_SVTransverseMass;} 


