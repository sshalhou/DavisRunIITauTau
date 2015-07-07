#ifndef DavisRunIITauTau_NtupleObjects_NtupleTrigObject_h
#define DavisRunIITauTau_NtupleObjects_NtupleTrigObject_h


// system include files
#include <memory>



// needed by ntuple Muons producer
#include <vector>
#include <string>
#include <iostream>
#include "DataFormats/Math/interface/LorentzVector.h"



typedef math::XYZTLorentzVector LorentzVector;
typedef std::vector<std::string> stringVec;
typedef std::vector<float>  floatVec;
typedef std::vector<std::pair<std::string, float> >  stringFloatPairVec;

class NtupleTrigObject
{



public:
         
  NtupleTrigObject();
  virtual ~NtupleTrigObject(){}

// helpers

  void fillInfo(LorentzVector, std::vector <int>, stringFloatPairVec, 
  				   stringFloatPairVec, stringFloatPairVec, stringFloatPairVec);

  float HLTFilter(std::string) const;      	   /* return 1.0 if the triggerObject passed a provided filter string, 0.0 if failed */
  stringVec	HLTFilter_labels(); 		       /* return vector of HLT Filters that the object satisfies */

  float HLTPath_isL3(std::string) const;       /* return 1.0 if the triggerObject passed a provided path string and isL3, else return 0.0 */
  stringVec HLTPath_isL3labels();              /* return vector of HLT Paths that the object has isL3 true for */

  float HLTPath_isLF(std::string) const;       /* return 1.0 if the triggerObject passed a provided path string and isLF, else return 0.0 */
  stringVec HLTPath_isLFlabels();              /* return vector of HLT Paths that the object has isLF true for */

  float HLTPath_isBoth(std::string) const;     /* return 1.0 if the triggerObject passed a provided path string and isBoth, else return 0.0 */
  stringVec HLTPath_isBothlabels();		       /* return of HLT Paths that the object has isBoth true for */

// getters

  	LorentzVector p4() const; 									/* return the trigger object's 4-vector */
  	std::vector <int> triggerObjectTypes() const;  				/* return a vector since can have multiple types per object */
	
// filler	

private:
	LorentzVector m_p4;							
	std::vector <int> m_triggerObjectTypes; 				 /*  vector of the trig objects type IDs */
	stringFloatPairVec m_HLTFiltersPair;                        /*  pair of passed filters =  (filterName,1.0)  */
	stringFloatPairVec m_HLTPath_isL3Pair;                   /*  pair of passed path and isL3 =  (filterName, isL3)  */
	stringFloatPairVec m_HLTPath_isLFPair;                   /*  pair of passed path and isLF =  (filterName, isLF)  */
	stringFloatPairVec m_HLTPath_isBothPair;                 /*  pair of passed path and isBoth =  (filterName, isBoth)  */




};

typedef std::vector<NtupleTrigObject> NtupleTrigObjectCollection;

#endif
