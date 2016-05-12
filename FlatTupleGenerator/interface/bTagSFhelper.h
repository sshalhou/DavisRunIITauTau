#ifndef DavisRunIITauTau_FlatTupleGenerator_bTagSFhelper_h
#define DavisRunIITauTau_FlatTupleGenerator_bTagSFhelper_h


/* class bTagSFhelper :

	class to apply promote-demote method for handling b-tag scale factors to NtupleJet objects
	main impact of these functions is to modfiy the value returned by NtupleJet::defaultBtagAlgorithm_isPassed() 

	- note: this code draws heavily from Run I BtagSF.hh and BTagCalibration examples

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

class bTagSFhelper {

public:

  bTagSFhelper(edm::FileInPath); /* the file is the CSV SF file */
   virtual ~bTagSFhelper()
  { 
  	delete m_calib; 

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


  }

  /* call the InitForJet function once per jet, per btag WP. args are :
  [b-tag Loose working point cut],  [b-tag Medium working point cut], [b-tag Tight working point cut],
  [jet Pt], [jet Eta], [raw b-tag score], [hadronFlavour], [isRealData] */

  void InitForJet(double, double, double, double, double, double, int, bool);


  /* return the scale factors, only valid after InitForJet is called for a jet */

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

	TRandom3 m_Rand3;
	double m_btag_workingPointLooseCut;	  /* btag group's Loose btag cut */
	double m_btag_workingPointMediumCut;  /* btag group's Medium btag cut_ */
	double m_btag_workingPointTightCut;   /* btag group's Tight btag cut_ */
    double m_jetPt;
    double m_jetEta;
    double m_jetRawScore;
    double m_jetHadronFlavour;
    bool m_isRealData;
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

	double m_MaxBJetPt; /* this defines the valid upper limit for a b-jet pT */
	double m_MaxCJetPt; /* this defines the valid upper limit for a c-jet pT */
	double m_MaxLJetPt; /* this defines the valid upper limit for a udsg -jet pT */

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

};



#endif
