#ifndef DavisRunIITauTau_FlatTupleGenerator_JetHelper_h
#define DavisRunIITauTau_FlatTupleGenerator_JetHelper_h


/* class JetHelper :

	class & functions for ranking NtupleJets by Pt, counting jets passing ID, and finding 
  b-tag scale factors

  - note b-jet counting and application of the scale factors 
  has been moved to AnalysisRunII, due to the need for MC_eff

- Shalhout
*/




// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// needed by ntuple Tau producer
#include <vector>
#include <iostream>
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEvent.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLepton.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DavisRunIITauTau/FlatTupleGenerator/interface/bTagSFhelper.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;


/* ranking comparator */

bool NtupleJetOrderCompare(const std::pair<double, NtupleJet>& , const std::pair<double, NtupleJet>& ) ;





class JetHelper {




public:

  JetHelper();
  virtual ~JetHelper(){}

// helpers



/* new >= 76X functions   */
  void init(std::vector<NtupleJet>, std::string, double, NtupleLepton, NtupleLepton, bTagSFhelper, bool); 
  void init(std::vector<NtupleJet>, std::string, bTagSFhelper, bool); 



// getters 
	
  /* returns pt ordered jets passing the cut string set in init
  string can be fullyCorrected,  JECshiftedUp, JECshiftedDown, JERnomianl, JERup, JERdown */									 
  std::vector<NtupleJet> PtOrderedPassingJets(std::string);  
  

private:

	std::vector<std::pair<double, NtupleJet>> m_PtJetPairs_fullyCorrected;     /* holder for Pt-NtupleJet pairs */

  std::vector<std::pair<double, NtupleJet>> m_PtJetPairs_JECshiftedUp;     /* holder for Pt-NtupleJet pairs */

  std::vector<std::pair<double, NtupleJet>> m_PtJetPairs_JECshiftedDown;     /* holder for Pt-NtupleJet pairs */

  std::vector<std::pair<double, NtupleJet>> m_PtJetPairs_JERnomianl;     /* holder for Pt-NtupleJet pairs */

  std::vector<std::pair<double, NtupleJet>> m_PtJetPairs_JERup;     /* holder for Pt-NtupleJet pairs */

  std::vector<std::pair<double, NtupleJet>> m_PtJetPairs_JERdown;     /* holder for Pt-NtupleJet pairs */




};

#endif
