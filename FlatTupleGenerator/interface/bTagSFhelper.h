#ifndef DavisRunIITauTau_FlatTupleGenerator_bTagSFhelper_h
#define DavisRunIITauTau_FlatTupleGenerator_bTagSFhelper_h


/* class bTagSFhelper :

	set of tools to read b-tag scale factors and their 1 sigma +/- shifted variations
	for NtupleJets from standard CSV SF files
	
	this class also has functions for extracting efficiency values from root files containing TH2D
	histograms (these are used in the promote-demote method whenever SF > 1)

	bTagSFhelper also includes promote-demote functions for applying b-tag SFs on a per-jet basis
	based on code example : https://github.com/rappoccio/usercode/blob/Dev_53x/EDSHyFT/plugins/BTagSFUtil_tprime.h

	- note: this code draws heavily from Run I BtagSF.hh and 76X BTagCalibration examples


			 

- Shalhout
*/



#include <memory>
#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <TRandom3.h>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "TFile.h"
#include "TH2F.h"
#include "TRandom3.h"

class bTagSFhelper {

public:

/* args are (the CSV SF file, the loose b-tag eff root file, the medium b-tag eff root file, the tight b-tag eff root file) */
  bTagSFhelper(edm::FileInPath, edm::FileInPath, edm::FileInPath, edm::FileInPath); 
   virtual ~bTagSFhelper()
  { 
  	delete m_calib; 

  	m_LooseBtagEff->Close();
  	m_MediumBtagEff->Close();
  	m_TightBtagEff->Close();
	delete m_LooseBtagEff;
	delete m_MediumBtagEff;
	delete m_TightBtagEff;

	delete m_LooseEff_b;
	delete m_LooseEff_c;
	delete m_LooseEff_usdg;

	delete m_MediumEff_b;
	delete m_MediumEff_c;
	delete m_MediumEff_usdg;

	delete m_TightEff_b;
	delete m_TightEff_c;
	delete m_TightEff_usdg;

	delete m_LooseWpReaderCentral_forBorC;
	delete m_LooseWpReaderUp_forBorC;
	delete m_LooseWpReaderDown_forBorC;
	delete m_MediumWpReaderCentral_forBorC;
	delete m_MediumWpReaderUp_forBorC;
	delete m_MediumWpReaderDown_forBorC;
	delete m_TightWpReaderCentral_forBorC;
	delete m_TightWpReaderUp_forBorC;
	delete m_TightWpReaderDown_forBorC;


	delete m_LooseWpReaderCentral_forUDSG;
	delete m_LooseWpReaderUp_forUDSG;
	delete m_LooseWpReaderDown_forUDSG;
	delete m_MediumWpReaderCentral_forUDSG;
	delete m_MediumWpReaderUp_forUDSG;
	delete m_MediumWpReaderDown_forUDSG;
	delete m_TightWpReaderCentral_forUDSG;
	delete m_TightWpReaderUp_forUDSG;
	delete m_TightWpReaderDown_forUDSG;


	delete m_LooseEff_b;
	delete m_LooseEff_c;
	delete m_LooseEff_usdg;

	delete m_MediumEff_b;
	delete m_MediumEff_c;
	delete m_MediumEff_usdg;

	delete m_TightEff_b;
	delete m_TightEff_c;
	delete m_TightEff_usdg;

	delete m_rand;
  }

  /* call the InitForJet function once per jet, per btag WP. args are :
  [jet Pt], [jet Eta], [raw b-tag score], [hadronFlavour], isRealData */

  void InitForJet(double, double, double, int, bool);


  /* return the scale factors and btag eff, only valid after InitForJet is called for a jet */


	bool isTagged_LooseWpCentral() const;
	bool isTagged_LooseWpUp() const;
	bool isTagged_LooseWpDown() const;
	bool isTagged_MediumWpCentral() const;
	bool isTagged_MediumWpUp() const;
	bool isTagged_MediumWpDown() const;
	bool isTagged_TightWpCentral() const;
	bool isTagged_TightWpUp() const;
	bool isTagged_TightWpDown() const;

	double EFF_LooseWp() const;
	double EFF_MediumWp() const;
	double EFF_TightWp() const;

  /* after the btag SFs are applied can call these to get the final b-tag pass/fail */

	double SF_LooseWpCentral() const;
	double SF_LooseWpUp() const;
	double SF_LooseWpDown() const;
	double SF_MediumWpCentral() const;
	double SF_MediumWpUp() const;
	double SF_MediumWpDown() const;
	double SF_TightWpCentral() const;
	double SF_TightWpUp() const;
	double SF_TightWpDown() const;




private:


    double m_jetPt;
    double m_jetEta;
    double m_jetRawScore;
    int m_jetHadronFlavour;
    BTagCalibration * m_calib;

	BTagCalibrationReader * m_LooseWpReaderCentral_forBorC;
	BTagCalibrationReader * m_LooseWpReaderUp_forBorC;
	BTagCalibrationReader * m_LooseWpReaderDown_forBorC;

	BTagCalibrationReader * m_MediumWpReaderCentral_forBorC;
	BTagCalibrationReader * m_MediumWpReaderUp_forBorC;
	BTagCalibrationReader * m_MediumWpReaderDown_forBorC;

	BTagCalibrationReader * m_TightWpReaderCentral_forBorC;
	BTagCalibrationReader * m_TightWpReaderUp_forBorC;
	BTagCalibrationReader * m_TightWpReaderDown_forBorC;


	BTagCalibrationReader * m_LooseWpReaderCentral_forUDSG;
	BTagCalibrationReader * m_LooseWpReaderUp_forUDSG;
	BTagCalibrationReader * m_LooseWpReaderDown_forUDSG;

	BTagCalibrationReader * m_MediumWpReaderCentral_forUDSG;
	BTagCalibrationReader * m_MediumWpReaderUp_forUDSG;
	BTagCalibrationReader * m_MediumWpReaderDown_forUDSG;

	BTagCalibrationReader * m_TightWpReaderCentral_forUDSG;
	BTagCalibrationReader * m_TightWpReaderUp_forUDSG;
	BTagCalibrationReader * m_TightWpReaderDown_forUDSG;

	/* limits in which SFs are valid -- outside these the uncertainty is doubled */	

	double m_MaxBJetPt; /* this defines the valid upper limit for a b-jet pT */
	double m_MaxCJetPt; /* this defines the valid upper limit for a c-jet pT */
	double m_MaxLJetPt; /* this defines the valid upper limit for a udsg -jet pT */

	double m_MinBJetPt; /* this defines the valid lower limit for a b-jet pT */
	double m_MinCJetPt; /* this defines the valid lower limit for a c-jet pT */
	double m_MinLJetPt; /* this defines the valid lower limit for a udsg -jet pT */



	bool m_DoubleUncertainty; /* set to true if jet pt > max valid pT */

	/* the scale factors themselves, filled for a jet in the InitForJet function */

	double m_SF_LooseWpCentral;
	double m_SF_LooseWpUp;
	double m_SF_LooseWpDown;
	double m_SF_MediumWpCentral;
	double m_SF_MediumWpUp;
	double m_SF_MediumWpDown;
	double m_SF_TightWpCentral;
	double m_SF_TightWpUp;
	double m_SF_TightWpDown;

	/* the efficiency values themselves, filled for a jet in the InitForJet function */
	/* I have ignored any statistical error on these - not sure if we should have UP/DOWN variants or not*/

	double m_EFF_LooseWp;
	double m_EFF_MediumWp;
	double m_EFF_TightWp;

	/* the btag results - evalueded after scale factors are applied */


	bool m_isTagged_LooseWpCentral;
	bool m_isTagged_LooseWpUp;
	bool m_isTagged_LooseWpDown;
	bool m_isTagged_MediumWpCentral;
	bool m_isTagged_MediumWpUp;
	bool m_isTagged_MediumWpDown;
	bool m_isTagged_TightWpCentral;
	bool m_isTagged_TightWpUp;
	bool m_isTagged_TightWpDown;

	/* eff root files */

	TFile * m_LooseBtagEff;
	TFile * m_MediumBtagEff;
	TFile * m_TightBtagEff;

	/* eff histograms */

	TH2F * m_LooseEff_b;
	TH2F * m_LooseEff_c;
	TH2F * m_LooseEff_usdg;

	TH2F * m_MediumEff_b;
	TH2F * m_MediumEff_c;
	TH2F * m_MediumEff_usdg;

	TH2F * m_TightEff_b;
	TH2F * m_TightEff_c;
	TH2F * m_TightEff_usdg;

	TRandom3 * m_rand;

	/* PromoteDemoteBtags - function to apply promote demote method,
	arg list is (raw btag mva output, cut for loose working point, cut for medium working point, 
				cut for tight working point, isRealData?)
	called only in InitForJet */

	void PromoteDemoteBtags(double, double, double, double, bool);


};



#endif
