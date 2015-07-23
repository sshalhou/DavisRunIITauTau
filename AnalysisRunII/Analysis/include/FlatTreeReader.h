/* Class to help take care of reading in a FlatTuple TTree
  does not require knowledge of the TTree structure :

  support of Branch types :

  vector<pair<int,int> >
  vector<pair<int,double> >
  vector<pair<int,float> >
  string
  Int_t         (aka int)
  UInt_t        (aka unsinged int)
  Bool_t        (aka bool)
  Float_t       (aka float)
  Double_t      (aka double)
  vector<int>
  vector<float>
  vector<double>
  vector<bool>
  vector<string>

  anything else can be added as long as you have the rootcint dict for it
  and add a case to FlatTreeReader::connectBranches

  - Shalhout
*/

#ifndef Analysis_FlatTreeReader_h
#define Analysis_FlatTreeReader_h

////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TBranch.h>
#include <TIterator.h>
#include <TObject.h>
#include <TClassRef.h>
#include <TObjArray.h>
#include <TBranchElement.h>
#include <vector>
#include <utility>
#include <iostream>
#include <TApplication.h>
#include <TLeaf.h>
#include <map>
#include <TString.h>
#include <assert.h>




class FlatTreeReader
{

public:
	
	TTree         *fChain;   
  int           fCurrent; 
  static const int maxOfOneType = 300;

	FlatTreeReader(TTree *tree=0);
	virtual ~FlatTreeReader();

  /* value access function called by the user */

  unsigned int   getUI(std::string);         /* access unsigned int value */
  int            getI(std::string);          /* access int value */
  double         getD(std::string);          /* access double value */
  float          getF(std::string);          /* access float value */
  bool           getB(std::string);          /* access bool value */
  std::string    getS(std::string);          /* access string value */

  std::vector<int>         getVI(std::string);       /* access vector<int>  */
  std::vector<double>      getVD(std::string);       /* access vector<double>  */
  std::vector<float>       getVF(std::string);       /* access vector<float>  */
  std::vector<bool>        getVB(std::string);       /* access vector<bool>  */
  std::vector<std::string> getVS(std::string);       /* access vector<string>  */

  std::vector<std::pair<int,int> >    getVPII(std::string);       /* access vector<pair<int,int> >  */
  std::vector<std::pair<int,double> > getVPID(std::string);       /* access vector<pair<int,double> >  */
  std::vector<std::pair<int,float> >  getVPIF(std::string);       /* access vector<pair<int,float> >  */


private:
  
  virtual void  Init(TTree *tree);
  virtual void connectBranches();

  /* asserts if encountered > maxOfOneType leaves of a one type */
  /* user can then adjust */
  void checkCount(int,std::string);

  /* returns a type string for the TTree element argument names */
  std::string getType(std::string);

  /* assert and print message if the 1 string which is a type, does not match type of leaf of name = (2nd arg) */
  void typeCheck(std::string, std::string);



  /* map between leaf names and pointers */
  std::map <std::string, void*> read_map;


  /* handle int member data */
  int int_leaves[maxOfOneType];
  TBranch *  b_int_leaves[maxOfOneType];
  
  /* handle unsigned int member data */
  unsigned int uint_leaves[maxOfOneType];
  TBranch *  b_uint_leaves[maxOfOneType];

  /* handle float member data */
  float float_leaves[maxOfOneType];
  TBranch *  b_float_leaves[maxOfOneType];

  /* handle double member data */
  double double_leaves[maxOfOneType];
  TBranch *  b_double_leaves[maxOfOneType];

  /* handle bool member data */
  bool bool_leaves[maxOfOneType];
  TBranch *  b_bool_leaves[maxOfOneType];

  /* handle string member data */
  std::string * string_leaves[maxOfOneType];
  TBranch *  b_string_leaves[maxOfOneType];

  /* handle vector<int> member data */
  std::vector<int>  *vint_leaves[maxOfOneType];
  TBranch *  b_vint_leaves[maxOfOneType];

  /* handle vector<float> member data */
  std::vector<float>  *vfloat_leaves[maxOfOneType];
  TBranch *  b_vfloat_leaves[maxOfOneType];


  /* handle vector<double> member data */
  std::vector<double>  *vdouble_leaves[maxOfOneType];
  TBranch *  b_vdouble_leaves[maxOfOneType];

  /* handle vector<bool> member data */
  std::vector<bool>  *vbool_leaves[maxOfOneType];
  TBranch *  b_vbool_leaves[maxOfOneType];

  /* handle vector<string> member data */
  std::vector<std::string>  *vstring_leaves[maxOfOneType];
  TBranch *  b_vstring_leaves[maxOfOneType];

  /* handle std::vector <std::pair< int, int>> member data */

  std::vector <std::pair< int, int> > *vIntIntPair_leaves[maxOfOneType];
  TBranch *  b_vIntIntPair_leaves[maxOfOneType];

  /* handle std::vector <std::pair< int, double>> member data */
  
  std::vector <std::pair< int, double> > *vIntDoublePair_leaves[maxOfOneType];
  TBranch *  b_vIntDoublePair_leaves[maxOfOneType];


 /* handle std::vector <std::pair< int, float>> member data */
  
  std::vector <std::pair< int, float> > *vIntFloatPair_leaves[maxOfOneType];
  TBranch *  b_vIntFloatPair_leaves[maxOfOneType];

};

////////////////////////////
#endif  




