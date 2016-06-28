/* CumulativeInfoAdder imp */
#include "DavisRunIITauTau/CumulativeInfoAdder/interface/CumulativeInfoAdder.h" 




////////////////////////////////////////////
//	--- class constructor
////////////////////////////////////////////


CumulativeInfoAdder::CumulativeInfoAdder(const edm::ParameterSet& iConfig):
mcGenWeightSrc_(iConfig.getParameter<edm::InputTag>("mcGenWeightSrc")),
LHEEventProductSrc_(iConfig.getParameter<edm::InputTag>("LHEEventProductSrc"))
{

  mcGenWeightToken_ = consumes<GenEventInfoProduct>(mcGenWeightSrc_);
  LHEEventProductToken_ = consumes<LHERunInfoProduct, edm::InRun> (LHEEventProductSrc_);

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


void CumulativeInfoAdder::endRun(edm::Run const& iRun, edm::EventSetup const& iEvent) 
{

  std::cout<<" CumulativeInfoAdder---END \n";


  edm::Handle<LHERunInfoProduct> LHEHandle;
  iRun.getByToken(LHEEventProductToken_,LHEHandle);

  //iRun.getByLabel( "externalLHEProducer", LHEHandle );

  std::cout<<" LHEHandle.isValid() "<<LHEHandle.isValid()<<"\n";

  if(LHEHandle.isValid())
  {
  

    typedef std::vector<LHERunInfoProduct::Header>::const_iterator headers_const_iterator;
 
    LHERunInfoProduct myLHERunInfoProduct = *(LHEHandle.product());
 
    for (headers_const_iterator iter=myLHERunInfoProduct.headers_begin(); iter!=myLHERunInfoProduct.headers_end(); iter++)
    {
        std::cout << iter->tag() << std::endl;
        std::vector<std::string> lines = iter->lines();
        for (unsigned int iLine = 0; iLine<lines.size(); iLine++) 
        {
          std::cout << lines.at(iLine);
        }
    }




  }


}




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
