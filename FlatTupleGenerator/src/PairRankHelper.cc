/* class PairRankHelper :

contains function to take in rank criteria + a vector of NtupleEvent objects
and return a std::vector<std::pair<NtupleEvent,int>> where the int represents 
the pair's rank 

the idea is that in the TTree we can access the best pair using rank==0, the 2nd
best by rank == 1 etc. 

- Shalhout
*/


#include "DavisRunIITauTau/FlatTupleGenerator/interface/PairRankHelper.h"

/* ranking comparators */

bool NtupleRankCompare_IsolLeg1( const std::pair<std::vector<double>, NtupleEvent>& p1, const std::pair<std::vector<double>, NtupleEvent>& p2) 
{
   // std::cout<<" ASSERT COND "<<p1.second.CandidateEventType()<<" "<<p2.second.CandidateEventType()<<"\n";

//  never compare non-similar lepton flavor pairs (i.e. eTau vs muTau is invalid)
  assert ( p1.second.CandidateEventType() == p2.second.CandidateEventType() );

  ////////////////////////////////////////////////////
  // the H2Tau 2015 default
  // ranking logic is leg1 isolation, then leg1 pt,
  // then leg2 isolation, then leg2 pt
  // -- special care needs to be used for e + mu channel
  // where leg1 = muon ONLY FOR RANKING, and is electron in all other cases
  ////////////////////////////////////////////////////
 
  ///////////////
  // begin comparsion logic :

  //////////////////////////////////////////////////
  // logic for non e+mu channels
  //////////////////////////////////////////////////
  if(p1.second.CandidateEventType() != TupleCandidateEventTypes::EleMuon)
  {
    // compare leg1 isolations 1st, these are already set to first by getIsolOfLeg1 in init function
    if(p1.first[0] != p2.first[0] && p1.first[0]!=-999)  return p1.first[0] < p2.first[0]; 

    // if equal leg1 isolations go to leg1 pT
    else if(p1.second.leg1().pt() != p2.second.leg1().pt())  return (p1.second.leg1().pt() > p2.second.leg1().pt());

    // if equal leg1 pT go to leg2 isolations
    else if(p1.first[1] != p2.first[1] && p2.first[0]!=-999)  return p1.first[1] < p2.first[1]; 

    // if equal leg 2 isol go to leg2 pT
    else if(p1.second.leg2().pt() != p2.second.leg2().pt())  return (p1.second.leg2().pt() > p2.second.leg2().pt());

    // finally just return true since the are the same pair and order does not matter
    else return 1;
  }
  //////////////////////////////////////////////////

  //////////////////////////////////////////////////
  // logic for  e+mu channels
  //////////////////////////////////////////////////
  else 
  {

    // 1st compare muon (leg2) isolations :
    if(p1.first[1] != p2.first[1] && p2.first[0]!=-999)  return p1.first[1] < p2.first[1]; 

    // next compare muon (leg2) pT :
    else if(p1.second.leg2().pt() != p2.second.leg2().pt())  return (p1.second.leg2().pt() > p2.second.leg2().pt());

    // next compare electron (leg1) isolations :
    if(p1.first[0] != p2.first[0] && p1.first[0]!=-999)  return p1.first[0] < p2.first[0]; 

    // next compare electron (leg1) pT :
    else if(p1.second.leg1().pt() != p2.second.leg1().pt())  return (p1.second.leg1().pt() > p2.second.leg1().pt());

    // finally just return true since the are the same pair and order does not matter
    else return 1;

  }
  //////////////////////////////////////////////////

}

bool NtupleRankCompare_SumPt( const std::pair<double, NtupleEvent>& p1, const std::pair<double, NtupleEvent>& p2) 
{
  // simple pt sum comparison
   if(p1.first != p2.first)  return p1.first > p2.first;	
   else return 1;  
}

/* constructor */

PairRankHelper::PairRankHelper(){}


/* init for sumPt ranking */
void PairRankHelper::init(std::vector<NtupleEvent> pairs)
{



  for(std::size_t i = 0; i<pairs.size(); ++i)
  {
    double criterion = getSumPt(pairs[i]);
    std::pair<double, NtupleEvent> apair(criterion, pairs[i]);
    m_CriterionLepPair_SumPt.push_back(apair);
   }

   std::sort(m_CriterionLepPair_SumPt.begin(), m_CriterionLepPair_SumPt.end(), NtupleRankCompare_SumPt);
   
   m_finalRanking.clear();

   for(std::size_t x = 0; x<m_CriterionLepPair_SumPt.size(); ++x)
   {
      m_finalRanking.push_back( std::make_pair(x, m_CriterionLepPair_SumPt[x].second ) );

   }

}

/* init for isolation based ranking: 1st take pair with most isolated leg1, if leg1 is tied in isoaltion
prefer pair with higher leg1 pt, then if tied, compare leg2 isolation, then if still tied leg2 pt  */

void PairRankHelper::init(std::vector<NtupleEvent> pairs,std::string eIsol, std::string muIsol, std::string tauID)
{

  bool verbose = 0;

  eIsol_ = eIsol;
  muIsol_ = muIsol;
  tauID_ = tauID;

  for(std::size_t i = 0; i<pairs.size(); ++i)
  {
    std::vector<double> criterion = getIsolOfLeg1andLeg2(pairs[i],eIsol,muIsol,tauID);
    std::pair<std::vector<double>, NtupleEvent> apair(criterion, pairs[i]);
    m_CriterionLepPair_Isol.push_back(apair);
  }

   //std::cout<<" TOTAL m_CriterionLepPair_Isol "<<m_CriterionLepPair_Isol.size()<<"\n";



  if(verbose)
  { 
    std::cout<<" ----- new ranking by isolation -------- \n";

     for(std::size_t x = 0; x<m_CriterionLepPair_Isol.size(); ++x)
     {
        if(verbose)
        {
           std::cout<<" PRE-SORTED RANK "<<x<<" has (l1_isol, l1_pt, l2_isol, l2_pt) = ( ";
           std::cout<<m_CriterionLepPair_Isol[x].first[0]<<" , "; 
           std::cout<<m_CriterionLepPair_Isol[x].second.leg1().pt()<<" , "; 
           std::cout<<m_CriterionLepPair_Isol[x].first[1]<<" , "; 
           std::cout<<m_CriterionLepPair_Isol[x].second.leg2().pt()<<" ) \n "; 
        }

      }
  }

   std::sort(m_CriterionLepPair_Isol.begin(), m_CriterionLepPair_Isol.end(), NtupleRankCompare_IsolLeg1);

   m_finalRanking.clear();




   for(std::size_t x = 0; x<m_CriterionLepPair_Isol.size(); ++x)
   {
      if(verbose)
      {
         std::cout<<" SORTED RANK "<<x<<" has (l1_isol, l1_pt, l2_isol, l2_pt) = ( ";
         std::cout<<m_CriterionLepPair_Isol[x].first[0]<<" , "; 
         std::cout<<m_CriterionLepPair_Isol[x].second.leg1().pt()<<" , "; 
         std::cout<<m_CriterionLepPair_Isol[x].first[1]<<" , "; 
         std::cout<<m_CriterionLepPair_Isol[x].second.leg2().pt()<<" ) \n "; 
      }


      m_finalRanking.push_back( std::make_pair(x, m_CriterionLepPair_Isol[x].second ) );

   }




} 




/* helpers */



  double PairRankHelper::getSumPt(NtupleEvent pair)
  {
  	return pair.leg1().p4().pt()+pair.leg2().p4().pt();
  }

  std::vector<double> PairRankHelper::getIsolOfLeg1andLeg2(NtupleEvent pair,std::string eIsol, std::string muIsol, std::string tauID)
  {

  		double criterion1 = 1.0;
      double criterion2 = 1.0;
      std::vector<double> criterion;

  		if(pair.leg1().leptonType()==TupleLeptonTypes::anElectron) criterion1 *= pair.leg1().relativeIsol(eIsol);
  		else if(pair.leg1().leptonType()==TupleLeptonTypes::aMuon) criterion1 *= pair.leg1().relativeIsol(muIsol);
  		else if(pair.leg1().leptonType()==TupleLeptonTypes::aTau)	 criterion1 *= pair.leg1().tauID(tauID);

  		if(pair.leg2().leptonType()==TupleLeptonTypes::anElectron) criterion2 *= pair.leg2().relativeIsol(eIsol);
  		else if(pair.leg2().leptonType()==TupleLeptonTypes::aMuon) criterion2 *= pair.leg2().relativeIsol(muIsol);
  		else if(pair.leg2().leptonType()==TupleLeptonTypes::aTau)  criterion2 *= pair.leg2().tauID(tauID);

      criterion.clear();      
      criterion.push_back(criterion1);
      criterion.push_back(criterion2);

  		return criterion;


  }

std::vector<std::pair<std::size_t, NtupleEvent>> PairRankHelper::returnRankedPairVec()
{
	return m_finalRanking;

}






