#include "DavisRunIITauTau/NtupleObjects/interface/NtuplePairIndependentInfo.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleLeptonTypes.h"
#include "DavisRunIITauTau/TupleObjects/interface/TupleCandidateEventTypes.h"
#include "TLorentzVector.h"

NtuplePairIndependentInfo::NtuplePairIndependentInfo()
{

}



std::vector<int> NtuplePairIndependentInfo::gen_IndexInRecord() const {return m_gen_IndexInRecord;}
//std::vector<std::vector<int>> NtuplePairIndependentInfo::gen_daughterIndicesInRecord() const {return m_gen_daughterIndicesInRecord;}; 
//std::vector<std::vector<int>> NtuplePairIndependentInfo::gen_motherIndicesInRecord() const {return m_gen_motherIndicesInRecord;}; 
std::vector<int> NtuplePairIndependentInfo::gen_pdgId() const {return m_gen_pdgId;}; 
std::vector<int> NtuplePairIndependentInfo::gen_status() const {return m_gen_status;}; 
std::vector<LorentzVector> NtuplePairIndependentInfo::gen_p4() const {return m_gen_p4;}; 
std::vector<float> NtuplePairIndependentInfo::gen_vertex_x() const {return m_gen_vertex_x;}; 
std::vector<float> NtuplePairIndependentInfo::gen_vertex_y() const {return m_gen_vertex_y;}; 
std::vector<float> NtuplePairIndependentInfo::gen_vertex_z() const {return m_gen_vertex_z;}; 



