#include "DavisRunIITauTau/NtupleObjects/interface/NtupleTrigObject.h"
#include "TLorentzVector.h"


NtupleTrigObject::NtupleTrigObject()
{}


void NtupleTrigObject::fillInfo(LorentzVector lv_,
				std::vector <int> types_, 
				stringFloatPairVec HLTPath_isL3Pair_,
	            stringFloatPairVec HLTPath_isLFPair_,
    	        stringFloatPairVec HLTPath_isBothPair_,
			    stringFloatPairVec HLTFiltersPair_)
{
 
	m_p4 = lv_;
	m_triggerObjectTypes = types_;
	m_HLTPath_isL3Pair = HLTPath_isL3Pair_;
	m_HLTPath_isLFPair = HLTPath_isLFPair_;
	m_HLTPath_isBothPair = HLTPath_isBothPair_;
	m_HLTFiltersPair = HLTFiltersPair_;

}

// helpers

////////////////
// pair decoders- these check (given a string path or filter name)
// if the trigger obj meet the filter requirements  (HLTFilter)
// if the trigger object was a L3 filter on the path given (HLTPath_isL3)
// if the trigger object was a LF (last) filter on the path given (HLTPath_isLF)
// if the trigger object was a Both (L3+LF) filter on the path given (HLTPath_isBoth)
////////////////


float NtupleTrigObject::HLTFilter(std::string label_) const
{
	float returnValue = 0;
	for(std::size_t x = 0; x < m_HLTFiltersPair.size();++x) 
	{ 
  		if(m_HLTFiltersPair.at(x).first == label_) returnValue = m_HLTFiltersPair.at(x).second;
	}

	return returnValue;
}

float NtupleTrigObject::HLTPath_isL3(std::string label_) const
{
	float returnValue = 0;
	for(std::size_t x = 0; x < m_HLTPath_isL3Pair.size();++x) 
	{ 
  		if(m_HLTPath_isL3Pair.at(x).first == label_) returnValue = m_HLTPath_isL3Pair.at(x).second;
	}

	return returnValue;
}


float NtupleTrigObject::HLTPath_isLF(std::string label_) const
{
	float returnValue = 0;
	for(std::size_t x = 0; x < m_HLTPath_isLFPair.size();++x) 
	{ 
  		if(m_HLTPath_isLFPair.at(x).first == label_) returnValue = m_HLTPath_isLFPair.at(x).second;
	}

	return returnValue;
}


float NtupleTrigObject::HLTPath_isBoth(std::string label_) const
{
	float returnValue = 0;
	for(std::size_t x = 0; x < m_HLTPath_isBothPair.size();++x) 
	{ 
  		if(m_HLTPath_isBothPair.at(x).first == label_) returnValue = m_HLTPath_isBothPair.at(x).second;
	}

	return returnValue;
}


////////////////
// label returns
////////////////


stringVec NtupleTrigObject::HLTFilter_labels()  
{ 
	stringVec m_dummy;
	for(std::size_t x = 0; x < m_HLTFiltersPair.size();++x) 
	{ 
	  m_dummy.push_back(m_HLTFiltersPair.at(x).first);
	}  

	return m_dummy;
}


stringVec NtupleTrigObject::HLTPath_isL3labels()  
{ 
	stringVec m_dummy;
	for(std::size_t x = 0; x < m_HLTPath_isL3Pair.size();++x) 
	{ 
	  m_dummy.push_back(m_HLTPath_isL3Pair.at(x).first);
	}  

	return m_dummy;
}

stringVec NtupleTrigObject::HLTPath_isLFlabels()  
{ 
	stringVec m_dummy;
	for(std::size_t x = 0; x < m_HLTPath_isLFPair.size();++x) 
	{ 
	  m_dummy.push_back(m_HLTPath_isLFPair.at(x).first);
	}  

	return m_dummy;
}

stringVec NtupleTrigObject::HLTPath_isBothlabels()  
{ 
	stringVec m_dummy;
	for(std::size_t x = 0; x < m_HLTPath_isBothPair.size();++x) 
	{ 
	  m_dummy.push_back(m_HLTPath_isBothPair.at(x).first);
	}  

	return m_dummy;
}



// getters 
LorentzVector NtupleTrigObject::p4() const { return m_p4; }
std::vector <int> NtupleTrigObject::triggerObjectTypes() const { return m_triggerObjectTypes; }


