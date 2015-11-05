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

typedef math::XYZTLorentzVector LorentzVector;
using namespace std;
using namespace edm;
using namespace pat;



class GenHelper {

public:

  GenHelper();
  virtual ~GenHelper(){}

// init

    void init(std::vector<NtupleGenParticle>, NtupleLepton, NtupleLepton, int ); 
    void classifyTheEventForDY();

// helper functions

    /* check at gen level if event is Z->XX where the int argument is the |pdgID| of X */
    bool isZXXatGenLevel(std::vector<NtupleGenParticle>, int);
    bool isRecoTauGenTauMatched(NtupleLepton);
    bool isRecoTauGenEorMuMatched(NtupleLepton,std::vector<NtupleGenParticle>);
    bool isRecoTauGenEorMu_FROMZ_Matched(NtupleLepton,std::vector<NtupleGenParticle>);



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


	NtupleLepton m_leg1;
	NtupleLepton m_leg2;
	int m_CandidateEventType;
	std::vector<NtupleGenParticle> m_genVec;


  /* decay mode of the Z */
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
