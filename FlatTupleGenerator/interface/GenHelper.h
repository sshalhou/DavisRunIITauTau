#ifndef DavisRunIITauTau_FlatTupleGenerator_GenHelper_h
#define DavisRunIITauTau_FlatTupleGenerator_GenHelper_h


/* class GenHelper :

	class for handling GEN level info in the Davis Ntuple

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
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleGenParticle.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleLepton.h" 
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleEvent.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DavisRunIITauTau/FlatTupleGenerator/interface/GenMcMatchTypes.h"


typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;



class GenHelper {

public:

  GenHelper();
  virtual ~GenHelper(){}

// init

    void init(std::vector<NtupleGenParticle>, NtupleLepton, NtupleLepton, int );  // for regular pairs
    void init(std::vector<NtupleGenParticle>, std::vector<NtupleLepton>, int );   // for eff leptons
    
// functions called in init    
    void resetVars();
    void fillRecoIndependentInfo();

    void classifyTheEventForDY(); /* run 1 only */
    void classifyTheEventForRun2_DY();

// helper functions

    /* new RunII MC Matching function */
    void checkLegsForEorMuorGenJetMatches(int); /* argument is 1 for leg1 or 2 for leg2 or 3 for an effCand */

    /* check at gen level if event is Z->XX where the int argument is the |pdgID| of X */
    bool isZXXatGenLevel(std::vector<NtupleGenParticle>, int); /* run 1 only */
    bool isRecoTauGenTauMatched(NtupleLepton); /* run 1 only */
    bool isRecoTauGenEorMuMatched(NtupleLepton,std::vector<NtupleGenParticle>); /* run 1 only */
    bool isRecoTauGenEorMu_FROMZ_Matched(NtupleLepton,std::vector<NtupleGenParticle>); /* run 1 only */


// getters 

	  std::vector <std::pair< int, int>> genParticle_pdgId();
  	std::vector <std::pair< int, int>> genParticle_status();

    std::vector<std::pair< int, int>> genParticle_isPrompt();
    std::vector<std::pair< int, int>> genParticle_isPromptFinalState();
    std::vector<std::pair< int, int>> genParticle_isDirectPromptTauDecayProduct();
    std::vector<std::pair< int, int>> genParticle_isDirectPromptTauDecayProductFinalState();


  	std::vector <std::pair< int, double>> genParticle_pt();
  	std::vector <std::pair< int, double>> genParticle_eta();
  	std::vector <std::pair< int, double>> genParticle_phi();
  	std::vector <std::pair< int, double>> genParticle_M();

  	std::vector <pair < int, int>> genDaughter_pdgId();
  	std::vector <pair < int, int>> genDaughter_status();
  	std::vector <std::pair< int, double>> genDaughter_pt();
  	std::vector <std::pair< int, double>> genDaughter_eta();
  	std::vector <std::pair< int, double>> genDaughter_phi();
  	std::vector <std::pair< int, double>> genDaughter_M();


  	std::vector <std::pair< int, int>> genMother_pdgId();
  	std::vector <std::pair< int, int>> genMother_status();
  	std::vector <std::pair< int, double>> genMother_pt();
  	std::vector <std::pair< int, double>> genMother_eta();
  	std::vector <std::pair< int, double>> genMother_phi();
  	std::vector <std::pair< int, double>> genMother_M();

    /* Access Run II MC matching info */

    int leg1_MCMatchType(); /* match codes defined in GenMcMatchTypes.h */
    double leg1_genMCmatch_pt();
    double leg1_genMCmatch_eta(); 
    double leg1_genMCmatch_phi(); 
    double leg1_genMCmatch_M();
    int leg1_MCMatchPdgId();

    int leg2_MCMatchType(); /* match codes defined in GenMcMatchTypes.h */
    double leg2_genMCmatch_pt();
    double leg2_genMCmatch_eta(); 
    double leg2_genMCmatch_phi(); 
    double leg2_genMCmatch_M();
    int leg2_MCMatchPdgId();


    std::vector<int> effLep_MCMatchType(); /* match codes defined in GenMcMatchTypes.h */
    std::vector<double> effLep_genMCmatch_pt();
    std::vector<double> effLep_genMCmatch_eta(); 
    std::vector<double> effLep_genMCmatch_phi(); 
    std::vector<double> effLep_genMCmatch_M();
    std::vector<int> effLep_MCMatchPdgId();



    /* run II Z decay modes */

    int IsZTT();
    int IsZL();
    int IsZJ();
    int IsZLL();



    /* see https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorkingSummer2013#Backgrounds_Methods */

    bool EventHasZtoTauTau();        /* for events with a Z boson, is there a Z->tau tau decay */
    bool EventHasZtoEE();            /* for events with a Z boson, is there a Z->e e decay */
    bool EventHasZtoMM();            /* for events with a Z boson, is there a Z->mu mu decay */
    bool isDY_genZTTcase1();         /* (for e/mu + tau_h) : gen. Z->tau tau && tau_h leg has gen-tau match but no gen-e/mu match */
    bool isDY_genZTTcase2();         /* (for e/mu + tau_h) : gen. Z->tau tau && tau_h leg has gen-e/mu match */
    bool isDY_genZTTcaseEmbedded();  /* (for e/mu + tau_h in embedded samples) : tau_h leg has a gen tau match */
    bool isDY_genZL();               /* (for e/mu + tau_h) : NOT gen. Z->tau tau && tau_h leg a gen-e/mu match */ 
    bool isDY_genZJcase1();          /* (for e/mu + tau_h) : NOT gen. Z->tau tau && tau_h leg has no gen-e/mu match */     
    bool isDY_genZJcase2();          /* (for e/mu + tau_h) : gen. Z->tau tau && tau_h leg has no gen-e/mu match or gen tau match */  
    bool isDY_genZTTcase3();         /* (for tau_h+tau_h)  : gen. Z->tau tau is present */
    bool isDY_genZLL();              /* (for tau_h+tau_h)  : gen. Z->e e or Z->m m is present, both tau_h have gen-e/mu (from Z) match */ 
    bool isDY_genZJcase3();          /* (for tau_h+tau_h) :  defined as !m_isDY_genZTTcase3 && !m_isDY_genZLL */




private:

  float MCdrMatchRun2; /* should make this a python arg */



	NtupleLepton m_leg1;
	NtupleLepton m_leg2;
  NtupleLepton temp_effLep;

  std::vector<NtupleLepton> m_effLep;
	int m_CandidateEventType;
	std::vector<NtupleGenParticle> m_genVec;


  /* Private member Run II MC matching info */

  int m_leg1_MCMatchType; /* match codes defined in GenMcMatchTypes.h */
  double m_leg1_genMCmatch_pt;
  double m_leg1_genMCmatch_eta; 
  double m_leg1_genMCmatch_phi; 
  double m_leg1_genMCmatch_M;
  int m_leg1_MCMatchPdgId;

  int m_leg2_MCMatchType; /* match codes defined in GenMcMatchTypes.h */
  double m_leg2_genMCmatch_pt;
  double m_leg2_genMCmatch_eta; 
  double m_leg2_genMCmatch_phi;
  double m_leg2_genMCmatch_M;
  int m_leg2_MCMatchPdgId;

  int temp_effLep_MCMatchType; /* match codes defined in GenMcMatchTypes.h */
  double temp_effLep_genMCmatch_pt;
  double temp_effLep_genMCmatch_eta; 
  double temp_effLep_genMCmatch_phi; 
  double temp_effLep_genMCmatch_M;
  int temp_effLep_MCMatchPdgId;

  std::vector<int> m_effLep_MCMatchType; /* match codes defined in GenMcMatchTypes.h */
  std::vector<double> m_effLep_genMCmatch_pt;
  std::vector<double> m_effLep_genMCmatch_eta; 
  std::vector<double> m_effLep_genMCmatch_phi; 
  std::vector<double> m_effLep_genMCmatch_M;
  std::vector<int> m_effLep_MCMatchPdgId;



  /* run II Z decay modes */

  int m_IsZTT;
  int m_IsZL;
  int m_IsZJ;
  int m_IsZLL;


  /* decay mode of the Z (old run 1 info)*/
  /* see https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorkingSummer2013#Backgrounds_Methods */
	
  bool m_EventHasZtoTauTau; /* for events with a Z boson, is there a Z->tau tau decay */
	bool m_EventHasZtoEE;     /* for events with a Z boson, is there a Z->e e decay */
	bool m_EventHasZtoMM;     /* for events with a Z boson, is there a Z->mu mu decay */

  /* for ZTT,ZL,ZLL, and ZJ DY categ. */

  bool m_isDY_genZTTcase1;         /* (for e/mu + tau_h) : gen. Z->tau tau && tau_h leg has gen-tau match but no gen-e/mu match */
  bool m_isDY_genZTTcase2;         /* (for e/mu + tau_h) : gen. Z->tau tau && tau_h leg has gen-e/mu match */
  bool m_isDY_genZTTcaseEmbedded;  /* (for e/mu + tau_h in embedded samples) : tau_h leg has a gen tau match */
  bool m_isDY_genZL;               /* (for e/mu + tau_h) : NOT gen. Z->tau tau && tau_h leg a gen-e/mu match */ 
  bool m_isDY_genZJcase1;          /* (for e/mu + tau_h) : NOT gen. Z->tau tau && tau_h leg has no gen-e/mu match */     
  bool m_isDY_genZJcase2;          /* (for e/mu + tau_h) : gen. Z->tau tau && tau_h leg has no gen-e/mu match or gen tau match */  
  bool m_isDY_genZTTcase3;         /* (for tau_h+tau_h)  : gen. Z->tau tau is present */
  bool m_isDY_genZLL;              /* (for tau_h+tau_h)  : gen. Z->e e or Z->m m is present, both tau_h have gen-e/mu (from Z) match */ 
  bool m_isDY_genZJcase3;          /* (for tau_h+tau_h) :  defined as !m_isDY_genZTTcase3 && !m_isDY_genZLL */



  std::vector <std::pair< int, int>> m_genParticle_pdgId;
  std::vector <std::pair< int, int>> m_genParticle_status;

  std::vector<std::pair< int, int>> m_genParticle_isPrompt;
  std::vector<std::pair< int, int>> m_genParticle_isPromptFinalState;
  std::vector<std::pair< int, int>> m_genParticle_isDirectPromptTauDecayProduct;
  std::vector<std::pair< int, int>> m_genParticle_isDirectPromptTauDecayProductFinalState;


  std::vector <std::pair< int, double>> m_genParticle_pt;
  std::vector <std::pair< int, double>> m_genParticle_eta;
  std::vector <std::pair< int, double>> m_genParticle_phi;
  std::vector <std::pair< int, double>> m_genParticle_M;

  std::vector <pair < int, int>> m_genDaughter_pdgId;
  std::vector <pair < int, int>> m_genDaughter_status;
  std::vector <std::pair< int, double>> m_genDaughter_pt;
  std::vector <std::pair< int, double>> m_genDaughter_eta;
  std::vector <std::pair< int, double>> m_genDaughter_phi;
  std::vector <std::pair< int, double>> m_genDaughter_M;


  std::vector <std::pair< int, int>> m_genMother_pdgId;
  std::vector <std::pair< int, int>> m_genMother_status;
  std::vector <std::pair< int, double>> m_genMother_pt;
  std::vector <std::pair< int, double>> m_genMother_eta;
  std::vector <std::pair< int, double>> m_genMother_phi;
  std::vector <std::pair< int, double>> m_genMother_M;


};

#endif
