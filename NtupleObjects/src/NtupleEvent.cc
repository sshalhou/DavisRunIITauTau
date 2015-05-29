#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "TLorentzVector.h"

NtupleEvent::NtupleEvent()
{
	m_CandidateEventType = -999;
	m_isOsPair = -999;

}


void NtupleEvent::fill(TupleCandidateEvent TCE)
{
	m_CandidateEventType = TCE.CandidateEventType();
	

	NtupleLepton ntupLep1; ntupLep1.fill(TCE.leg1());        
    NtupleLepton ntupLep2; ntupLep2.fill(TCE.leg2());        
	m_leg0  =  ntupLep1;
	m_leg1  =  ntupLep2;

	if (m_leg0.charge() == m_leg1.charge()) m_isOsPair = 0;
	else if (m_leg0.charge() == -1*m_leg1.charge()) m_isOsPair = 1;


	m_SVMass = TCE.SVMass();
	m_VISMass.push_back((m_leg0.p4()+m_leg1.p4()).M());
	math::PtEtaPhiMLorentzVector mvamet(TCE.mvaMET()[0].pt(),0.0,TCE.mvaMET()[0].phi(),0.0);
	math::PtEtaPhiMLorentzVector pfmet(TCE.pfMET()[0].pt(),0.0,TCE.pfMET()[0].phi(),0.0);


	m_MTmvaMET_leg0.push_back(GetTransverseMass(m_leg0.p4(),mvamet));
	m_MTpfMET_leg0.push_back(GetTransverseMass(m_leg0.p4(),pfmet));

	m_MTmvaMET_leg1.push_back(GetTransverseMass(m_leg1.p4(),mvamet));
	m_MTpfMET_leg1.push_back(GetTransverseMass(m_leg1.p4(),pfmet));

	m_mvaMET = TCE.mvaMET();
	m_pfMET = TCE.pfMET();
	m_pfMET_cov00 = TCE.pfMET_cov00();
	m_pfMET_cov01 = TCE.pfMET_cov01();
	m_pfMET_cov10 = TCE.pfMET_cov10();
	m_pfMET_cov11 = TCE.pfMET_cov11();


	for (std::size_t i = 0; i < TCE.vetoElectron().size(); ++i)
	{
		NtupleLepton tempLep; tempLep.fill(TCE.vetoElectron()[i]);
		m_vetoElectron.push_back(tempLep);

	}

	for (std::size_t i = 0; i < TCE.vetoMuon().size(); ++i)
	{
		NtupleLepton tempLep; tempLep.fill(TCE.vetoMuon()[i]);
		m_vetoMuon.push_back(tempLep);

	}


}



int NtupleEvent::CandidateEventType() const { return m_CandidateEventType; }
NtupleLepton NtupleEvent::leg0() const { return m_leg0; }
NtupleLepton NtupleEvent::leg1() const { return m_leg1; }
std::vector<NtupleLepton> NtupleEvent::vetoElectron() const {return m_vetoElectron;}
std::vector<NtupleLepton> NtupleEvent::vetoMuon() const {return  m_vetoMuon;}
std::vector<double> NtupleEvent::SVMass() const {return  m_SVMass;}
std::vector<double> NtupleEvent::VISMass() const {return  m_VISMass;}
int NtupleEvent::isOsPair() const {return m_isOsPair;}
std::vector<double> NtupleEvent::MTmvaMET_leg0() const {return m_MTmvaMET_leg0;}
std::vector<double> NtupleEvent::MTpfMET_leg0() const {return m_MTpfMET_leg0;}
std::vector<double> NtupleEvent::MTmvaMET_leg1() const {return m_MTmvaMET_leg1;}
std::vector<double> NtupleEvent::MTpfMET_leg1() const {return m_MTpfMET_leg1;}
std::vector<reco::PFMET>  NtupleEvent::mvaMET() const {return m_mvaMET;}
std::vector<pat::MET>  NtupleEvent::pfMET() const {return m_pfMET;}
std::vector<double>  NtupleEvent::pfMET_cov00() const {return m_pfMET_cov00;}
std::vector<double>  NtupleEvent::pfMET_cov01() const {return m_pfMET_cov01;}
std::vector<double>  NtupleEvent::pfMET_cov10() const {return m_pfMET_cov10;}
std::vector<double>  NtupleEvent::pfMET_cov11() const {return m_pfMET_cov11;}