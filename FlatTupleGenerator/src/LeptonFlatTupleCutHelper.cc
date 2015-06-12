/* class LeptonFlatTupleCutHelper :

contains functions to apply simple cuts at the FlatTuple 
production stage based on cms.PSet and NtupleEvent arguments

- Shalhout
*/


#include "DavisRunIITauTau/FlatTupleGenerator/interface/LeptonFlatTupleCutHelper.h"







/* constructor */

LeptonFlatTupleCutHelper::LeptonFlatTupleCutHelper(){}

/* helpers */


void LeptonFlatTupleCutHelper::setEMuTauCutSets(edm::ParameterSet eCut, edm::ParameterSet muCut, edm::ParameterSet tauCut){
	 m_eCutSet = eCut;
	 m_muCutSet = muCut;
	 m_tauCutSet = tauCut;}


bool LeptonFlatTupleCutHelper::pairPasses(NtupleEvent pair)
{
	bool pass1 = 0;
	bool pass2 = 0;

	if(pair.leg1().leptonType()==TupleLeptonTypes::anElectron) pass1 = checkElectron(pair.leg1());
	else if(pair.leg1().leptonType()==TupleLeptonTypes::aMuon) pass1 = checkMuon(pair.leg1());
	else if(pair.leg1().leptonType()==TupleLeptonTypes::aTau) pass1 = checkTau(pair.leg1());


	if(pair.leg2().leptonType()==TupleLeptonTypes::anElectron) pass2 = checkElectron(pair.leg2());
	else if(pair.leg2().leptonType()==TupleLeptonTypes::aMuon) pass2 = checkMuon(pair.leg2());
	else if(pair.leg2().leptonType()==TupleLeptonTypes::aTau) pass2 = checkTau(pair.leg2());



	return (pass1 && pass2);
}


bool LeptonFlatTupleCutHelper::checkElectron(NtupleLepton electron)
{

	/* read the cut PSet */
	
	std::vector<double> Pt_Range = m_eCutSet.getParameter<std::vector<double>>("Pt");
	assert(Pt_Range.size()==2);
	
	std::vector<double> EtaAbs_Range = m_eCutSet.getParameter<std::vector<double>>("EtaAbs");
	assert(EtaAbs_Range.size()==2);

	std::vector<double> dxyAbs_Range = m_eCutSet.getParameter<std::vector<double>>("dxyAbs");
	assert(dxyAbs_Range.size()==2);

	std::vector<double> dzAbs_Range = m_eCutSet.getParameter<std::vector<double>>("dzAbs");
	assert(dzAbs_Range.size()==2);

	std::vector<double> relIso_Range = m_eCutSet.getParameter<std::vector<double>>("relIsoCut");
	assert(relIso_Range.size()==2);

 	std::string relIsoName = m_eCutSet.getParameter<std::string>("relIsoToCutOn");

 	/* evaluate electron quantities */

	double pt = electron.p4().pt();
	double absEta = fabs(electron.p4().eta());
	float absDxy = fabs(electron.dxy());
	float absDz = fabs(electron.dz());
	float relIso = electron.relativeIsol(relIsoName);


	return 
	(
		( pt >= Pt_Range[0] && Pt_Range[1] >= pt) && 
		( absEta >= EtaAbs_Range[0] && EtaAbs_Range[1] >= absEta) && 
		( absDxy >= dxyAbs_Range[0] && dxyAbs_Range[1] >= absDxy) && 
		( absDz >= dzAbs_Range[0] && dzAbs_Range[1] >= absDz) && 
		( relIso >= relIso_Range[0] && relIso_Range[1] >= relIso)
	);


}

bool LeptonFlatTupleCutHelper::checkMuon(NtupleLepton muon)
{
	/* read the cut PSet */
	
	std::vector<double> Pt_Range = m_muCutSet.getParameter<std::vector<double>>("Pt");
	assert(Pt_Range.size()==2);
	
	std::vector<double> EtaAbs_Range = m_muCutSet.getParameter<std::vector<double>>("EtaAbs");
	assert(EtaAbs_Range.size()==2);

	std::vector<double> dxyAbs_Range = m_muCutSet.getParameter<std::vector<double>>("dxyAbs");
	assert(dxyAbs_Range.size()==2);

	std::vector<double> dzAbs_Range = m_muCutSet.getParameter<std::vector<double>>("dzAbs");
	assert(dzAbs_Range.size()==2);

	std::vector<double> relIso_Range = m_muCutSet.getParameter<std::vector<double>>("relIsoCut");
	assert(relIso_Range.size()==2);

 	std::string relIsoName = m_muCutSet.getParameter<std::string>("relIsoToCutOn");

 	/* evaluate muon quantities */

	double pt = muon.p4().pt();
	double absEta = fabs(muon.p4().eta());
	float absDxy = fabs(muon.dxy());
	float absDz = fabs(muon.dz());
	float relIso = muon.relativeIsol(relIsoName);


	return 
	(
		( pt >= Pt_Range[0] && Pt_Range[1] >= pt) && 
		( absEta >= EtaAbs_Range[0] && EtaAbs_Range[1] >= absEta) && 
		( absDxy >= dxyAbs_Range[0] && dxyAbs_Range[1] >= absDxy) && 
		( absDz >= dzAbs_Range[0] && dzAbs_Range[1] >= absDz) && 
		( relIso >= relIso_Range[0] && relIso_Range[1] >= relIso)
	);



}

bool LeptonFlatTupleCutHelper::checkTau(NtupleLepton tau)
{

   /* read the cut PSet */
	
	std::vector<double> Pt_Range = m_tauCutSet.getParameter<std::vector<double>>("Pt");
	assert(Pt_Range.size()==2);
	
	std::vector<double> EtaAbs_Range = m_tauCutSet.getParameter<std::vector<double>>("EtaAbs");
	assert(EtaAbs_Range.size()==2);

	std::vector<double> tauID_Range = m_tauCutSet.getParameter<std::vector<double>>("tauIDCut");
	assert(tauID_Range.size()==2);

 	std::string tauIDName = m_tauCutSet.getParameter<std::string>("tauIDtoCutOn");

 	/* evaluate tau quantities */

	double pt = tau.p4().pt();
	double absEta = fabs(tau.p4().eta());
	float tauID = tau.tauID(tauIDName);


	return 
	(
		( pt >= Pt_Range[0] && Pt_Range[1] >= pt) && 
		( absEta >= EtaAbs_Range[0] && EtaAbs_Range[1] >= absEta) && 
		( tauID >= tauID_Range[0] && tauID_Range[1] >= tauID)
	);


}


