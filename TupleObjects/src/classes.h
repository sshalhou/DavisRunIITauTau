#include "UserCode/TupleObjects/interface/TupleElectron.h"
#include "UserCode/TupleObjects/interface/TupleMuon.h"
#include "UserCode/TupleObjects/interface/TupleTau.h"
#include "UserCode/TupleObjects/interface/TupleJet.h"
#include "UserCode/TupleObjects/interface/TupleGen.h"


#include "DataFormats/Common/interface/Wrapper.h"


struct dictionary
{
  TupleElectron dummy0;
  edm::Wrapper<TupleElectronCollection> dummy1;
  TupleMuon dummy2;
  edm::Wrapper<TupleMuonCollection> dummy3;
  TupleTau dummy4;
  edm::Wrapper<TupleTauCollection> dummy5;
  TupleJet dummy6;
  edm::Wrapper<TupleJetCollection> dummy7;
  TupleGen dummy8;
  edm::Wrapper<TupleGenCollection> dummy9;


};

