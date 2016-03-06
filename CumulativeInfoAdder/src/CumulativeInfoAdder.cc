/* CumulativeInfoAdder imp */
#include "DavisRunIITauTau/CumulativeInfoAdder/interface/CumulativeInfoAdder.h" 




////////////////////////////////////////////
//	--- class constructor
////////////////////////////////////////////


CumulativeInfoAdder::CumulativeInfoAdder(const edm::ParameterSet& iConfig):
mcGenWeightSrc_(iConfig.getParameter<edm::InputTag>("mcGenWeightSrc"))
{

  mcGenWeightToken_ = consumes<GenEventInfoProduct>(mcGenWeightSrc_);

}


//////////////////////////////////////////////////
// class destructor 
//////////////////////////////////////////////////

CumulativeInfoAdder::~CumulativeInfoAdder(){}

//////////////////////////////////////////////////
// ------------ method called for each event  ------------
//////////////////////////////////////////////////

void CumulativeInfoAdder::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   using namespace edm;



  //////////////
  // init values

  reInit();


  ///////////////////////////////////////////////////////////////////////////
  /*   get the MC gen weight collection  */
  ///////////////////////////////////////////////////////////////////////////

  edm::Handle<GenEventInfoProduct> genEvtWeight;
  iEvent.getByToken(mcGenWeightToken_, genEvtWeight);

  if(genEvtWeight.isValid()) 
    {
      generatorEventWeight = genEvtWeight->weight();
     // std::cout<<" generatorEventWeight == "<<generatorEventWeight<<"\n";

    }



      CumulativeTuple->Fill();

}





//////////////////////////////////////////////////
// ------------ method called to reset values and clear vectors each event ----
//////////////////////////////////////////////////

 void CumulativeInfoAdder::reInit()
 {

  generatorEventWeight = 1.0;


 }

 //////////////////////////////////////////////////
// ------------ method called once each job just before starting event loop  ------------
//////////////////////////////////////////////////

void CumulativeInfoAdder::beginJob() 
{

   /* create TTree */
   
  edm::Service<TFileService> fs;
  CumulativeTuple = fs->make<TTree>("CumulativeTuple","CumulativeTuple");







  //////////////
  // init values

    reInit(); 



  /* the branches */

  CumulativeTuple->Branch("generatorEventWeight", &generatorEventWeight);
 

}

//////////////////////////////////////////////////
// ------------ method called once each job just after ending the event loop  ------------
//////////////////////////////////////////////////

void CumulativeInfoAdder::endJob() {}


/*
//////////////////////////////////////////////////
// ------------ method called when starting to processes a run  ------------
//////////////////////////////////////////////////

void CumulativeInfoAdder::beginRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a run  ------------
//////////////////////////////////////////////////

void CumulativeInfoAdder::endRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when starting to processes a luminosity block  ------------
//////////////////////////////////////////////////

void CumulativeInfoAdder::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a luminosity block  ------------
//////////////////////////////////////////////////

void CumulativeInfoAdder::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
//////////////////////////////////////////////////
*/
void CumulativeInfoAdder::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
  }
