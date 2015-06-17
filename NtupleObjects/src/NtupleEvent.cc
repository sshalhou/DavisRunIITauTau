#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "TLorentzVector.h"
#include <math.h> 
#include <assert.h> 
#include <string> 


NtupleEvent::NtupleEvent()
{
	m_CandidateEventType = -999;
	m_TauEsNumberSigmasShifted = NAN;
	m_isOsPair = -999;


   m_parameterKeys.insert("pt");
   m_parameterKeys.insert("eta");
   m_parameterKeys.insert("fabs(eta)");
   m_parameterKeys.insert("phi");
   m_parameterKeys.insert("dxy");
   m_parameterKeys.insert("fabs(dxy)");
   m_parameterKeys.insert("dz");
   m_parameterKeys.insert("fabs(dz)");


   m_targetKeys.insert("LEG1");
   m_targetKeys.insert("LEG2");
   m_targetKeys.insert("MUON1");
   m_targetKeys.insert("ELECTRON1");
   m_targetKeys.insert("TAU1");
   m_targetKeys.insert("MUON2");
   m_targetKeys.insert("ELECTRON2");
   m_targetKeys.insert("TAU2");
   m_targetKeys.insert("VETOMUONS");
   m_targetKeys.insert("VETOELECTRONS");
   m_targetKeys.insert("VETOTAUS");
   m_targetKeys.insert("PAIR");

}


void NtupleEvent::checkCutArgs(std::string parameterKey,std::string targetKey)
{

if(m_parameterKeys.find(parameterKey) == m_parameterKeys.end())
{

    std::cout << "calling NtupleEvent::applyCut with invalid parameterKey "<<parameterKey<<" ";
    std::cout << "valid parameterKeys limited to : "<<" ";

	for(std::set<std::string>::iterator it=m_parameterKeys.begin(); it!=m_parameterKeys.end(); ++it)
		{std::cout<<*it<<" ";}
	std::cout<<"\n";

	assert(m_parameterKeys.find(parameterKey) != m_parameterKeys.end());
}

if(m_targetKeys.find(targetKey) == m_targetKeys.end())
{

    std::cout << "calling NtupleEvent::applyCut with invalid targetKey "<<targetKey<<" ";
    std::cout << "valid targetKeys limited to : "<<" ";

	for(std::set<std::string>::iterator it=m_targetKeys.begin(); it!=m_targetKeys.end(); ++it)
		{std::cout<<*it<<" ";}
	std::cout<<"\n";

	assert(m_targetKeys.find(targetKey) != m_targetKeys.end());
}


}

bool NtupleEvent::applyCut(std::string parameterKey, double min, double max, std::string targetKey)
{

checkCutArgs(parameterKey,targetKey);
return callCut(parameterKey,min,max,targetKey);
}

bool NtupleEvent::callCut(std::string parameterKey, double min, double max, std::string targetKey)
{

if(	(targetKey!="VETOMUONS") &&
    (targetKey!="VETOELECTRONS") && 
    (targetKey!="VETOTAUS") &&
    (targetKey!="PAIR") )
	{

		NtupleLepton lep;

		if(targetKey=="LEG1") lep = m_leg1;
		else if(targetKey=="LEG2") lep = m_leg2;
		else if(targetKey=="MUON1" && m_leg1.leptonType()==TupleLeptonTypes::aMuon) lep = m_leg1;
		else if(targetKey=="MUON2" && m_leg2.leptonType()==TupleLeptonTypes::aMuon) lep = m_leg2;
		else if(targetKey=="ELECTRON1" && m_leg1.leptonType()==TupleLeptonTypes::anElectron) lep = m_leg1;
		else if(targetKey=="ELECTRON2" && m_leg2.leptonType()==TupleLeptonTypes::anElectron) lep = m_leg2;
		else if(targetKey=="TAU1" && m_leg1.leptonType()==TupleLeptonTypes::aTau) lep = m_leg1;
		else if(targetKey=="TAU2" && m_leg2.leptonType()==TupleLeptonTypes::aTau) lep = m_leg2;

		/* parameters identical for all lepton flavors */
		if(parameterKey=="pt") return  (lep.p4().pt()>=min && max> lep.p4().pt());
		if(parameterKey=="eta") return (lep.p4().eta()>=min && max> lep.p4().eta());
		if(parameterKey=="fabs(eta)") return (fabs(lep.p4().eta())>=min && max> fabs(lep.p4().eta()));
		if(parameterKey=="phi") return (lep.p4().phi()>=min && max> lep.p4().phi());
		if(parameterKey=="dxy") return (lep.dxy()>=min && max>lep.dxy());
		if(parameterKey=="dz") return (lep.dz()>=min && max>lep.dz());
		if(parameterKey=="fabs(dxy)") return (fabs(lep.dxy())>=min && max>fabs(lep.dxy()));
		if(parameterKey=="fabs(dz)") return (fabs(lep.dz())>=min && max>fabs(lep.dz()));
		

		/* parameters whose meaning can vary by lepton flavor */

		if(parameterKey.find("relativeIsol(")==0 && lep.leptonType()!=TupleLeptonTypes::aTau)
		{
			std::string arg = parameterKey;
			arg.erase(arg.begin(),arg.begin()+1+arg.find("("));
			arg.erase(arg.end()-1);
			return (lep.relativeIsol(arg)>=min && max>lep.relativeIsol(arg));

		}
			


		
	}




/* the default return is true since it is safer to keep events than cut them out */
return 1;
}






void NtupleEvent::fill(TupleCandidateEvent TCE)
{
	m_CandidateEventType = TCE.CandidateEventType();
	

	NtupleLepton ntupLep1; ntupLep1.fill(TCE.leg1());        
    NtupleLepton ntupLep2; ntupLep2.fill(TCE.leg2());        
	m_leg1 =  ntupLep1;
	m_leg2  =  ntupLep2;

	if(isnan(m_leg2.TauEsVariant()) == 0) m_TauEsNumberSigmasShifted = m_leg2.TauEsVariant();
	else if(isnan(m_leg1.TauEsVariant()) == 0) m_TauEsNumberSigmasShifted = m_leg1.TauEsVariant();



	if (m_leg1.charge() == m_leg2.charge()) m_isOsPair = 0;
	else if (m_leg1.charge() == -1*m_leg2.charge()) m_isOsPair = 1;


	m_SVMass = TCE.SVMass();
	m_VISMass.push_back((m_leg1.p4()+m_leg2.p4()).M());
	math::PtEtaPhiMLorentzVector mvamet(TCE.mvaMET()[0].pt(),0.0,TCE.mvaMET()[0].phi(),0.0);
	math::PtEtaPhiMLorentzVector pfmet(TCE.pfMET()[0].pt(),0.0,TCE.pfMET()[0].phi(),0.0);


	m_MTmvaMET_leg1.push_back(GetTransverseMass(m_leg1.p4(),mvamet));
	m_MTpfMET_leg1.push_back(GetTransverseMass(m_leg1.p4(),pfmet));

	m_MTmvaMET_leg2.push_back(GetTransverseMass(m_leg2.p4(),mvamet));
	m_MTpfMET_leg2.push_back(GetTransverseMass(m_leg2.p4(),pfmet));

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

	/* need to add the known isolation types, rhos, and tau IDs to the key lists */

	for (std::size_t x = 0; x<m_leg1.relativeIsol_Labels().size();++x)
	{
		std::string currentString = m_leg1.relativeIsol_Labels()[x];
		std::string addVal = "relativeIsol("+currentString+")";		
		if(m_parameterKeys.find(addVal) == m_parameterKeys.end()) 
		{
			std::cout<<addVal<<"\n";
			m_parameterKeys.insert(addVal);
		}
	}


	for (std::size_t x = 0; x<m_leg2.relativeIsol_Labels().size();++x)
	{
		std::string currentString = m_leg2.relativeIsol_Labels()[x];
		std::string addVal = "relativeIsol("+currentString+")";
		std::cout<<addVal<<"\n";
		if(m_parameterKeys.find(addVal) == m_parameterKeys.end())
		{
			std::cout<<addVal<<"\n";
			m_parameterKeys.insert(addVal);
		}
	}


	// leg1.relativeIsol_Labels();
	// leg2.relativeIsol_Labels();

	// leg1.rho_Labels();
	// leg2.rho_Labels();
	
	// leg1.tauID_Labels();
	// leg2.tauID_Labels();
		


 //   m_parameterKeys.insert("pt");




}



int NtupleEvent::CandidateEventType() const { return m_CandidateEventType; }
float NtupleEvent::TauEsNumberSigmasShifted() const {return m_TauEsNumberSigmasShifted;}
NtupleLepton NtupleEvent::leg1() const { return m_leg1; }
NtupleLepton NtupleEvent::leg2() const { return m_leg2; }
std::vector<NtupleLepton> NtupleEvent::vetoElectron() const {return m_vetoElectron;}
std::vector<NtupleLepton> NtupleEvent::vetoMuon() const {return  m_vetoMuon;}
std::vector<double> NtupleEvent::SVMass() const {return  m_SVMass;}
std::vector<double> NtupleEvent::VISMass() const {return  m_VISMass;}
int NtupleEvent::isOsPair() const {return m_isOsPair;}
std::vector<double> NtupleEvent::MTmvaMET_leg1() const {return m_MTmvaMET_leg1;}
std::vector<double> NtupleEvent::MTpfMET_leg1() const {return m_MTpfMET_leg1;}
std::vector<double> NtupleEvent::MTmvaMET_leg2() const {return m_MTmvaMET_leg2;}
std::vector<double> NtupleEvent::MTpfMET_leg2() const {return m_MTpfMET_leg2;}
std::vector<reco::PFMET>  NtupleEvent::mvaMET() const {return m_mvaMET;}
std::vector<pat::MET>  NtupleEvent::pfMET() const {return m_pfMET;}
std::vector<double>  NtupleEvent::pfMET_cov00() const {return m_pfMET_cov00;}
std::vector<double>  NtupleEvent::pfMET_cov01() const {return m_pfMET_cov01;}
std::vector<double>  NtupleEvent::pfMET_cov10() const {return m_pfMET_cov10;}
std::vector<double>  NtupleEvent::pfMET_cov11() const {return m_pfMET_cov11;}