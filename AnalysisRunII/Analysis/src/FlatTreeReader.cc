#include "FlatTreeReader.h"

FlatTreeReader::FlatTreeReader(TTree *tree) : fChain(0) 
{
   if (tree == 0) return;
   Init(tree);
}

FlatTreeReader::~FlatTreeReader()
{}


void FlatTreeReader::Init(TTree *tree)
{
	fChain = tree;	
  connectBranches();

}


void FlatTreeReader::checkCount(int count,std::string type_)
{
  if(count>=maxOfOneType)
  {
    std::cout<<"\n---- too many TTree elements of type "<<type_<<" have found ";
    std::cout<<count<<" so far. (the max allowed is "<<maxOfOneType<<") \n";
    std::cout<<" can change value of maxOfOneType in FlatTreeReader by hand ----\n";

  }
  assert(!(count>=maxOfOneType));
}


std::string FlatTreeReader::getType(std::string arg_)
{
  std::string returnName = "";
  TLeaf* theLeaf;
  theLeaf = fChain->GetLeaf(arg_.c_str());
  
  /* allow for trailing underscore ROOT inserts for some types */
  if(!theLeaf)
  { 
    
    theLeaf = fChain->GetLeaf((arg_+"_").c_str());
    if(!theLeaf)
    {
      std::cout<<"\n ---- no known TTree element "<<arg_<<" please check TTree or spelling ----\n";
      assert(theLeaf);
    }
  } 
  std::string BranchClassName = theLeaf->GetBranch()->GetClassName();
  std::string BranchTypeName = theLeaf->GetTypeName();

  if(BranchClassName.length()!=0) returnName = BranchClassName;
  else if(BranchTypeName.length()!=0) returnName = BranchTypeName;

  return returnName;
}


void FlatTreeReader::connectBranches()
{

  TIter iLeaf(fChain->GetListOfLeaves());
  const TLeaf* leaf = 0;

  /* counters for various object types */
  int scount = 0;       // string
  int icount = 0;       // int
  int uicount = 0;      // unsigned int
  int bcount = 0;       // bool
  int fcount = 0;       // float
  int dcount = 0;       // double
  int vicount = 0;      // vector < int >
  //int vuicount = 0;     // vector < unsigned int > support needs to be added
  int vbcount = 0;      // vector < bool > 
  int vfcount = 0;      // vector < float > 
  int vdcount = 0;      // vector < double > 
  int vscount = 0;      // vector < string > 
  int viipcount = 0;    // vector < pair <int, int> >
  int vidpcount = 0;    // vector < pair <int, double> >
  int vifpcount = 0;    // vector < pair <int, float> >


  while ((leaf = (const TLeaf*)iLeaf())) 
  {    
    /* get the leaf name */
    std::string title = leaf->GetName();

    /* get the type */
    std::string compName = getType(title);


    /* root also assigns members of objects their own leaf 
       example : genMother_pt.first 
       these should be accessed via genMother_pt itself
       not as their own vectors, so we will skip
    */  

    if(title.find(".")!=std::string::npos) continue;




    if(compName=="vector<pair<int,int> >")
    { 
      /* ROOT appends an underscore to these */
      title.erase(title.end()-1, title.end());
      viipcount++;
      checkCount(viipcount,compName);
      vIntIntPair_leaves[viipcount-1] = nullptr;
      b_vIntIntPair_leaves[viipcount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&vIntIntPair_leaves[viipcount-1],&b_vIntIntPair_leaves[viipcount-1]);
      read_map[title] = vIntIntPair_leaves[viipcount-1];

    }

    else if(compName=="vector<pair<int,double> >")
    { 
      /* ROOT appends an underscore to these */
      title.erase(title.end()-1, title.end());
      vidpcount++;
      checkCount(vidpcount,compName);
      vIntDoublePair_leaves[vidpcount-1] = nullptr;
      b_vIntDoublePair_leaves[vidpcount-1] = nullptr;
     fChain->SetBranchAddress(title.c_str(),&vIntDoublePair_leaves[vidpcount-1],&b_vIntDoublePair_leaves[vidpcount-1]);
     read_map[title] = vIntDoublePair_leaves[vidpcount-1];

    }

    else if(compName=="vector<pair<int,float> >")
    { 
      /* ROOT appends an underscore to these */
      title.erase(title.end()-1, title.end());
      vifpcount++;
      checkCount(vifpcount,compName);
      vIntFloatPair_leaves[vifpcount-1] = nullptr;
      b_vIntFloatPair_leaves[vifpcount-1] = nullptr;
     fChain->SetBranchAddress(title.c_str(),&vIntFloatPair_leaves[vifpcount-1],&b_vIntFloatPair_leaves[vifpcount-1]);
     read_map[title] = vIntFloatPair_leaves[vifpcount-1];

    }

    else if(compName=="string")
    { 
      
      scount++;
      checkCount(scount,compName);
      string_leaves[scount-1] = nullptr;
      b_string_leaves[scount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&string_leaves[scount-1],&b_string_leaves[scount-1]);
      read_map[title] = string_leaves[scount-1];
    }

    else if(compName=="Int_t")
    { 
      
      icount++;
      checkCount(icount,compName);
      int_leaves[icount-1] = 0;
      b_int_leaves[icount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&int_leaves[icount-1],&b_int_leaves[icount-1]);
      read_map[title] = &int_leaves[icount-1];
    }
    else if(compName=="UInt_t")
    { 
      
      uicount++;
      checkCount(uicount,compName);
      uint_leaves[uicount-1] = 0;
      b_uint_leaves[uicount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&uint_leaves[uicount-1],&b_uint_leaves[uicount-1]);
      read_map[title] = &uint_leaves[uicount-1];
    }

    else if(compName=="Bool_t")
    { 
      
      bcount++;
      checkCount(bcount,compName);
      bool_leaves[bcount-1] = 0;
      b_bool_leaves[bcount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&bool_leaves[bcount-1],&b_bool_leaves[bcount-1]);
      read_map[title] = &bool_leaves[bcount-1];
    }

    else if(compName=="Float_t")
    { 
      
      fcount++;
      checkCount(fcount,compName);
      float_leaves[fcount-1] = 0;
      b_float_leaves[fcount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&float_leaves[fcount-1],&b_float_leaves[fcount-1]);
      read_map[title] = &float_leaves[fcount-1];
    }

    else if(compName=="Double_t")
    { 
      
      dcount++;
      checkCount(dcount,compName);
      double_leaves[dcount-1] = 0;
      b_double_leaves[dcount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&double_leaves[dcount-1],&b_double_leaves[dcount-1]);
      read_map[title] = &double_leaves[dcount-1];
    }
    else if(compName=="vector<int>")
    { 
      
      vicount++;
      checkCount(vicount,compName);
      vint_leaves[vicount-1] = nullptr;
      b_vint_leaves[vicount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&vint_leaves[vicount-1],&b_vint_leaves[vicount-1]);
      read_map[title] = vint_leaves[vicount-1];
    }
    else if(compName=="vector<float>")
    { 
      
      vfcount++;
      checkCount(vfcount,compName);
      vfloat_leaves[vfcount-1] = nullptr;
      b_vfloat_leaves[vfcount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&vfloat_leaves[vfcount-1],&b_vfloat_leaves[vfcount-1]);
      read_map[title] = vfloat_leaves[vfcount-1];
    }
    else if(compName=="vector<double>")
    { 
      
      vdcount++;
      checkCount(vdcount,compName);
      vdouble_leaves[vdcount-1] = nullptr;
      b_vdouble_leaves[vdcount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&vdouble_leaves[vdcount-1],&b_vdouble_leaves[vdcount-1]);
      read_map[title] = vdouble_leaves[vdcount-1];
    }
    else if(compName=="vector<bool>")
    { 
      
      vbcount++;
      checkCount(vbcount,compName);
      vbool_leaves[vbcount-1] = nullptr;
      b_vbool_leaves[vbcount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&vbool_leaves[vbcount-1],&b_vbool_leaves[vbcount-1]);
      read_map[title] = vbool_leaves[vbcount-1];
    }
    else if(compName=="vector<string>")
    { 
      
      vscount++;
      checkCount(vscount,compName);
      vstring_leaves[vscount-1] = nullptr;
      b_vstring_leaves[vscount-1] = nullptr;
      fChain->SetBranchAddress(title.c_str(),&vstring_leaves[vscount-1],&b_vstring_leaves[vscount-1]);
      read_map[title] = vstring_leaves[vscount-1];
    }

    else 
    {
      std::cout<<"\n ---- SORRY could not understand type "<<compName<<" for leaf "<<leaf->GetName()<<"--- \n";
      std::cout<<"\n ---- You will need to add this manually to FlatTreeReader"<<" ---- \n";
      assert(0);
    }




  }
}

void FlatTreeReader::typeCheck(std::string testType, std::string leafName)
{
  std::string leafType = getType(leafName);
  if(testType!=leafType)
  {
      std::cout<<"\n ------ :( TTree element "<<leafName<<" is type "<<leafType<<" and not "<<testType<<"\n";
      assert(leafType==testType); 

  }  
}

unsigned int FlatTreeReader::getUI(std::string argString)
{
  typeCheck("UInt_t",argString);
  return *static_cast<unsigned int*>(read_map[argString]);
}


int FlatTreeReader::getI(std::string argString)
{
  typeCheck("Int_t",argString);
  return *static_cast<int*>(read_map[argString]);
}

double FlatTreeReader::getD(std::string argString)
{
  typeCheck("Double_t",argString);
  return *static_cast<double*>(read_map[argString]);
}

float FlatTreeReader::getF(std::string argString)
{
  typeCheck("Float_t",argString);
  return *static_cast<float*>(read_map[argString]);
}


bool FlatTreeReader::getB(std::string argString)
{
  typeCheck("Bool_t",argString);
  return *static_cast<bool*>(read_map[argString]);
}


std::string FlatTreeReader::getS(std::string argString)
{
  typeCheck("string",argString);
  return *static_cast<std::string*>(read_map[argString]);
}

std::vector<int> FlatTreeReader::getVI(std::string argString)
{
  typeCheck("vector<int>",argString);
  return (*static_cast< std::vector<int>* > (read_map[argString]));
}

std::vector<double> FlatTreeReader::getVD(std::string argString)
{
  typeCheck("vector<double>",argString);
  return (*static_cast< std::vector<double>* > (read_map[argString]));
}

std::vector<float> FlatTreeReader::getVF(std::string argString)
{
  typeCheck("vector<float>",argString);
  return (*static_cast< std::vector<float>* > (read_map[argString]));
}

std::vector<bool> FlatTreeReader::getVB(std::string argString)
{
  typeCheck("vector<bool>",argString);
  return (*static_cast< std::vector<bool>* > (read_map[argString]));
}

std::vector<std::string> FlatTreeReader::getVS(std::string argString)
{
  typeCheck("vector<string>",argString);
  return (*static_cast< std::vector<std::string>* > (read_map[argString]));

}


std::vector<std::pair<int,int> > FlatTreeReader::getVPII(std::string argString)
{
  typeCheck("vector<pair<int,int> >",argString);
  return (*static_cast< std::vector<std::pair<int,int> > * > (read_map[argString]));

}

std::vector<std::pair<int,double> > FlatTreeReader::getVPID(std::string argString)
{
  typeCheck("vector<pair<int,double> >",argString);
  return (*static_cast< std::vector<std::pair<int,double> > * > (read_map[argString]));

}

std::vector<std::pair<int,float> > FlatTreeReader::getVPIF(std::string argString)
{
  typeCheck("vector<pair<int,float> >",argString);
  return (*static_cast< std::vector<std::pair<int,float> > * > (read_map[argString]));

}









