#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "TLorentzVector.h"
#include <math.h> 
#include <assert.h> 
#include <string> 


NtupleEvent::NtupleEvent()
{
	m_CandidateEventType = -999;
	m_TauEsNumberSigmasShifted = NAN;
	m_ElectronEsNumberSigmasShifted = NAN;
	m_isOsPair = -999;
	m_isRealData = 0;
	m_isBoostedChannel = 0;
}

///// get max pt of all trigger objects match to a given reco leg


float NtupleEvent::leg1MaxPtTriggerObjMatch() const
{

	float max_pt = -9999.999;
	for(std::size_t i = 0; i< m_leg1_trigMatches.size(); ++i)
	{
		if(m_leg1_trigMatches[i].p4().pt()> max_pt) max_pt = m_leg1_trigMatches[i].p4().pt();
	}


//	std::cout<<" leg 1 max pt "<<max_pt<<"\n";
	return max_pt;
}

float NtupleEvent::leg2MaxPtTriggerObjMatch() const
{


	float max_pt = -9999.999;
	for(std::size_t i = 0; i< m_leg2_trigMatches.size(); ++i)
	{
		if(m_leg2_trigMatches[i].p4().pt()> max_pt) max_pt = m_leg2_trigMatches[i].p4().pt();
	}


//	std::cout<<" leg 2 max pt "<<max_pt<<"\n";
	return max_pt;

}


float NtupleEvent::EffLeptonMaxPtTriggerObjMatch(std::size_t index_) const
{

	float max_pt = -9999.999;
	for(std::size_t i = 0; i< m_EffLepton_trigMatches[index_].size(); ++i)
	{
		if(m_EffLepton_trigMatches[index_][i].p4().pt()> max_pt) max_pt = m_EffLepton_trigMatches[index_][i].p4().pt();
	}


//	std::cout<<" leg 1 max pt "<<max_pt<<"\n";
	return max_pt;
}


/////

void NtupleEvent::fillTriggerMatchesLeg1andLeg2(std::vector<NtupleTrigObject> trigVec1,std::vector<NtupleTrigObject> trigVec2)
{

  m_leg1_trigMatches = trigVec1;
  m_leg2_trigMatches = trigVec2;

}

void NtupleEvent::fillTriggerMatchesForEffLepton(std::vector<NtupleTrigObject> trigVec_)
{

  m_EffLepton_trigMatches.push_back(trigVec_);

}




/* trigger summary helpers */

/* fill them */

void NtupleEvent::fillTriggerSummariesLeg1andLeg2(stringFloatPairVec isLeg1GoodForHLTPath_, 
												  stringFloatPairVec isLeg2GoodForHLTPath_)
{

   m_isLeg1GoodForHLTPath = isLeg1GoodForHLTPath_;
   m_isLeg2GoodForHLTPath = isLeg2GoodForHLTPath_;


}

void NtupleEvent::fillTriggerSummariesEffLepton(stringFloatPairVec isEffLeptonGoodForHLTPath_)
{

   m_isEffLeptonGoodForHLTPath.push_back(isEffLeptonGoodForHLTPath_);

}




/* get list of paths based on ConfigTupleTriggers_cfi that the leg is good for */
/* note may contain duplicates with and without version wildcard */
  
stringVec NtupleEvent::isLeg1GoodForHLTPath_Labels()  
{ 
	stringVec dummy;
	for(std::size_t x = 0; x < m_isLeg1GoodForHLTPath.size();++x) 
	{ 
  		dummy.push_back(m_isLeg1GoodForHLTPath.at(x).first);
	}  

return dummy;
}

stringVec NtupleEvent::isLeg2GoodForHLTPath_Labels()  
{ 
	stringVec dummy;
	for(std::size_t x = 0; x < m_isLeg2GoodForHLTPath.size();++x) 
	{ 
  		dummy.push_back(m_isLeg2GoodForHLTPath.at(x).first);
	}  

return dummy;
}

stringVec NtupleEvent::isEffLeptonGoodForHLTPath_Labels(std::size_t index_)  
{ 
	stringVec dummy;
	for(std::size_t x = 0; x < m_isEffLeptonGoodForHLTPath[index_].size();++x) 
	{ 
  		dummy.push_back(m_isEffLeptonGoodForHLTPath[index_].at(x).first);
	}  

return dummy;
}



/* functions that check if a leg is good for a trigger */
/* only valid for those in ConfigTupleTriggers_cfi */
/* for all the rest you need to check manually in leg1_trigMatches & leg2_trigMatches */
/* version wildcards are  OK, but could suffer from filter problems if filter list changes 
between versions of the HLT path */

float NtupleEvent::isLeg1GoodForHLTPath(std::string label_) const
{
	float returnValue = 0.0;
	for(std::size_t x = 0; x < m_isLeg1GoodForHLTPath.size();++x) 
	{ 
	  if(m_isLeg1GoodForHLTPath.at(x).first == label_) returnValue = m_isLeg1GoodForHLTPath.at(x).second;

	}

	return returnValue;
}



float NtupleEvent::isLeg2GoodForHLTPath(std::string label_) const
{
	float returnValue = 0.0;
	//std::cout<<" testing trig leg2  m_isLeg2GoodForHLTPath size "<<m_isLeg2GoodForHLTPath.size()<<"\n";

	for(std::size_t x = 0; x < m_isLeg2GoodForHLTPath.size();++x) 
	{ 
	  if(m_isLeg2GoodForHLTPath.at(x).first == label_) returnValue = m_isLeg2GoodForHLTPath.at(x).second;

	}

	return returnValue;
}

float NtupleEvent::isEffLeptonGoodForHLTPath(std::string label_, std::size_t index_) const
{
	float returnValue = 0.0;
	for(std::size_t x = 0; x < m_isEffLeptonGoodForHLTPath[index_].size();++x) 
	{ 
	  if(m_isEffLeptonGoodForHLTPath[index_].at(x).first == label_) returnValue = m_isEffLeptonGoodForHLTPath[index_].at(x).second;

	}

	return returnValue;
}


void NtupleEvent::fillL1IsoTauMatchInfoLeg1andLeg2(edm::Handle<l1extra::L1JetParticleCollection> L1IsoTaus)
{




	/* loop over L1IsoTaus */

 	if(L1IsoTaus.isValid()) 
 	{
		for(l1extra::L1JetParticleCollection::const_iterator i = L1IsoTaus->begin(); i != L1IsoTaus->end(); ++i) 
		{
			if(deltaR(m_leg1.p4(),i->p4()) < 0.5) m_leg1_L1IsoTauDR05Matches.push_back(i->p4());
			if(deltaR(m_leg2.p4(),i->p4()) < 0.5) m_leg2_L1IsoTauDR05Matches.push_back(i->p4());

		}
	}

	// std::cout<<L1IsoTaus->size()<<" = total isoTaus ";
	// std::cout<<" leg1 matches to "<<m_leg1_L1IsoTauDR05Matches.size();
	// std::cout<<" while leg2 matches "<<m_leg2_L1IsoTauDR05Matches.size()<<"\n";


}


void NtupleEvent::fillL1IsoTauMatchInfoForEffLepton(edm::Handle<l1extra::L1JetParticleCollection> L1IsoTaus)
{



 	if(L1IsoTaus.isValid()) 
 	{

 		for(std::size_t e = 0; e<m_EffLepton.size(); ++e)
		{ 			
			std::vector <LorentzVector> tempVec;

			for(l1extra::L1JetParticleCollection::const_iterator i = L1IsoTaus->begin(); i != L1IsoTaus->end(); ++i) 
			{
				if(deltaR(m_EffLepton.at(e).p4(),i->p4()) < 0.5) tempVec.push_back(i->p4());
			}

			// std::cout<<L1IsoTaus->size()<<" = total isoTaus ";
			// std::cout<<" eff lepton at index "<<e<<" matches to "<<tempVec.size()<<" of them \n";

			m_EffLepton_L1IsoTauDR05Matches.push_back(tempVec);
			tempVec.clear();

		}
	}



//  std::vector < std::vector <LorentzVector> > m_EffLepton_L1IsoTauDR05Matches; 



}



void NtupleEvent::fill(TupleCandidateEvent TCE)
{
	m_CandidateEventType = TCE.CandidateEventType();
	
	if(m_CandidateEventType == TupleCandidateEventTypes::EffCand)
	{
		for(std::size_t i = 0; i<TCE.EfficiencyLepton().size(); ++i)
		{

			NtupleLepton ntupLepTEMP;
			ntupLepTEMP.fill(TCE.EfficiencyLepton().at(i));
			m_EffLepton.push_back(ntupLepTEMP);

		}

		// items not directly related to the leptons


		math::PtEtaPhiMLorentzVector pfmet(TCE.pfMET()[0].pt(),0.0,TCE.pfMET()[0].phi(),0.0);
		math::PtEtaPhiMLorentzVector puppimet(TCE.puppiMET()[0].pt(),0.0,TCE.puppiMET()[0].phi(),0.0);

		m_pfMET = TCE.pfMET();
		m_puppiMET = TCE.puppiMET();

		m_pfMET_cov00 = TCE.pfMET_cov00();
		m_pfMET_cov01 = TCE.pfMET_cov01();
		m_pfMET_cov10 = TCE.pfMET_cov10();
		m_pfMET_cov11 = TCE.pfMET_cov11();

	}



	else if(m_CandidateEventType != TupleCandidateEventTypes::EffCand)
	{
		NtupleLepton ntupLep1; ntupLep1.fill(TCE.leg1());        
	    NtupleLepton ntupLep2; ntupLep2.fill(TCE.leg2());        
		m_leg1 =  ntupLep1;
		m_leg2  =  ntupLep2;

		if(isnan(m_leg2.TauEsVariant()) == 0) m_TauEsNumberSigmasShifted = m_leg2.TauEsVariant();
		else if(isnan(m_leg1.TauEsVariant()) == 0) m_TauEsNumberSigmasShifted = m_leg1.TauEsVariant();

		if(isnan(m_leg2.ElectronEsVariant()) == 0) m_ElectronEsNumberSigmasShifted = m_leg2.ElectronEsVariant();
		else if(isnan(m_leg1.ElectronEsVariant()) == 0) m_ElectronEsNumberSigmasShifted = m_leg1.ElectronEsVariant();




		if (m_leg1.charge() == m_leg2.charge()) m_isOsPair = 0;
		else if (m_leg1.charge() == -1*m_leg2.charge()) m_isOsPair = 1;


		m_SVMass = TCE.SVMass();
		m_SVTransverseMass = TCE.SVTransverseMass();
		m_VISMass.push_back((m_leg1.p4()+m_leg2.p4()).M());
		math::PtEtaPhiMLorentzVector mvamet(TCE.mvaMET()[0].pt(),0.0,TCE.mvaMET()[0].phi(),0.0);
		math::PtEtaPhiMLorentzVector pfmet(TCE.pfMET()[0].pt(),0.0,TCE.pfMET()[0].phi(),0.0);
		math::PtEtaPhiMLorentzVector puppimet(TCE.puppiMET()[0].pt(),0.0,TCE.puppiMET()[0].phi(),0.0);


		m_MTmvaMET_leg1.push_back(GetTransverseMass(m_leg1.p4(),mvamet));
		m_MTpfMET_leg1.push_back(GetTransverseMass(m_leg1.p4(),pfmet));
		m_MTpuppiMET_leg1.push_back(GetTransverseMass(m_leg1.p4(),puppimet));


		m_MTmvaMET_leg2.push_back(GetTransverseMass(m_leg2.p4(),mvamet));
		m_MTpfMET_leg2.push_back(GetTransverseMass(m_leg2.p4(),pfmet));
		m_MTpuppiMET_leg2.push_back(GetTransverseMass(m_leg2.p4(),puppimet));


		m_mvaMET = TCE.mvaMET();
		m_pfMET = TCE.pfMET();
		m_puppiMET = TCE.puppiMET();

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

		for (std::size_t i = 0; i < TCE.vetoTau().size(); ++i)
		{
			NtupleLepton tempLep; tempLep.fill(TCE.vetoTau()[i]);
			m_vetoTau.push_back(tempLep);

		}


	}

}

/* set real data or MC */

void NtupleEvent::set_isRealData(bool dummy_)
{
	m_isRealData = dummy_;
}


void NtupleEvent::set_isBoostedChannel(bool dummy_)
{
	m_isBoostedChannel = dummy_;
}


/* the next function helps to easily apply the cut 

DeltaR(isotau1,offlinetau1) < 0.5
DeltaR(isotau2,offlinetau2) < 0.5
Where isotau1.pt()>28 GeV and isotau2.pt()>28 GeV, and isotau1 != isotau2
which is needed for the 2015 tau_h tau_h trigger
*/

bool NtupleEvent::PairPassesDoubleTauIsoTau28MatchCut() const
{

	for(std::size_t a = 0; a<m_leg1_L1IsoTauDR05Matches.size(); ++a)
	{
		if( m_leg1_L1IsoTauDR05Matches.at(a).pt() > 28 )
		{

			for(std::size_t b = 0; b<m_leg2_L1IsoTauDR05Matches.size(); ++b)				
			{
				if( m_leg2_L1IsoTauDR05Matches.at(b).pt() > 28 )
				{				

					if( deltaR(m_leg1_L1IsoTauDR05Matches.at(a),m_leg2_L1IsoTauDR05Matches.at(b))>0.001 ) 
					{
						// std::cout<<" NOT THE SAME ISOTAU ";
						// std::cout<<" pt "<<m_leg1_L1IsoTauDR05Matches.at(a).pt()<<" vs "<<m_leg2_L1IsoTauDR05Matches.at(b).pt()<<" ";
						// std::cout<<" eta "<<m_leg1_L1IsoTauDR05Matches.at(a).eta()<<" vs "<<m_leg2_L1IsoTauDR05Matches.at(b).eta()<<" ";
						// std::cout<<" phi "<<m_leg1_L1IsoTauDR05Matches.at(a).phi()<<" vs "<<m_leg2_L1IsoTauDR05Matches.at(b).phi()<<" ";

						return 1;
					}
					/* just for print out */
					//else 
					//{	
						// std::cout<<" IDENTICAL ISOTAU ";
						// std::cout<<" pt "<<m_leg1_L1IsoTauDR05Matches.at(a).pt()<<" vs "<<m_leg2_L1IsoTauDR05Matches.at(b).pt()<<" ";
						// std::cout<<" eta "<<m_leg1_L1IsoTauDR05Matches.at(a).eta()<<" vs "<<m_leg2_L1IsoTauDR05Matches.at(b).eta()<<" ";
						// std::cout<<" phi "<<m_leg1_L1IsoTauDR05Matches.at(a).phi()<<" vs "<<m_leg2_L1IsoTauDR05Matches.at(b).phi()<<" ";
					//}
				}

			}

		}  
	}

	return 0;
}




int NtupleEvent::CandidateEventType() const { return m_CandidateEventType; }
float NtupleEvent::TauEsNumberSigmasShifted() const {return m_TauEsNumberSigmasShifted;}
float NtupleEvent::ElectronEsNumberSigmasShifted() const {return m_ElectronEsNumberSigmasShifted;}

NtupleLepton NtupleEvent::leg1() const { return m_leg1; }
NtupleLepton NtupleEvent::leg2() const { return m_leg2; }
std::vector<NtupleLepton> NtupleEvent::EffLepton() const {return m_EffLepton;}

bool NtupleEvent::isRealData() const {return m_isRealData; }
bool NtupleEvent::isBoostedChannel() const {return m_isBoostedChannel; }


std::vector<NtupleTrigObject> NtupleEvent::leg1_trigMatches() const { return m_leg1_trigMatches; }
std::vector<NtupleTrigObject> NtupleEvent::leg2_trigMatches() const { return m_leg2_trigMatches; }
std::vector < std::vector<NtupleTrigObject> > NtupleEvent::EffLepton_trigMatches() const { return m_EffLepton_trigMatches; }

std::vector <LorentzVector>  NtupleEvent::leg1_L1IsoTauDR05Matches() const { return m_leg1_L1IsoTauDR05Matches; }
std::vector <LorentzVector>  NtupleEvent::leg2_L1IsoTauDR05Matches() const { return m_leg2_L1IsoTauDR05Matches; }
std::vector < std::vector <LorentzVector> >  NtupleEvent::EffLepton_L1IsoTauDR05Matches()  const { return m_EffLepton_L1IsoTauDR05Matches; }

std::vector<NtupleLepton> NtupleEvent::vetoElectron() const {return m_vetoElectron;}
std::vector<NtupleLepton> NtupleEvent::vetoMuon() const {return  m_vetoMuon;}
std::vector<NtupleLepton> NtupleEvent::vetoTau() const {return  m_vetoTau;}

std::vector<double> NtupleEvent::SVMass() const {return  m_SVMass;}
std::vector<double> NtupleEvent::SVTransverseMass() const {return m_SVTransverseMass;}
std::vector<double> NtupleEvent::VISMass() const {return  m_VISMass;}
int NtupleEvent::isOsPair() const {return m_isOsPair;}
std::vector<double> NtupleEvent::MTmvaMET_leg1() const {return m_MTmvaMET_leg1;}
std::vector<double> NtupleEvent::MTpfMET_leg1() const {return m_MTpfMET_leg1;}
std::vector<double> NtupleEvent::MTpuppiMET_leg1() const {return m_MTpuppiMET_leg1;}

std::vector<double> NtupleEvent::MTmvaMET_leg2() const {return m_MTmvaMET_leg2;}
std::vector<double> NtupleEvent::MTpfMET_leg2() const {return m_MTpfMET_leg2;}
std::vector<double> NtupleEvent::MTpuppiMET_leg2() const {return m_MTpuppiMET_leg2;}

std::vector<pat::MET>  NtupleEvent::mvaMET() const {return m_mvaMET;}
std::vector<pat::MET>  NtupleEvent::pfMET() const {return m_pfMET;}
std::vector<pat::MET>  NtupleEvent::puppiMET() const {return m_puppiMET;}

std::vector<double>  NtupleEvent::pfMET_cov00() const {return m_pfMET_cov00;}
std::vector<double>  NtupleEvent::pfMET_cov01() const {return m_pfMET_cov01;}
std::vector<double>  NtupleEvent::pfMET_cov10() const {return m_pfMET_cov10;}
std::vector<double>  NtupleEvent::pfMET_cov11() const {return m_pfMET_cov11;}
