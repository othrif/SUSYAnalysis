from ROOT import TFile, gDirectory, TH1D
from time import gmtime, strftime

line = '//'+'-'*64
name_mc = []
type_mc = []
name_data = []
type_data = []
type_ntp = []

# mc
file = TFile( '/UserDisk2/othrif/susy/data/Ximo/v25/user.jpoveda.t0703_v25.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.DAOD_SUSY2.s2608_r6765_p2421_output.root.55742639/user.jpoveda.7101441._000018.output.root' )

mytree_mc = gDirectory.Get('AnaNtup')
#mytree_mc.Print()

for br in mytree_mc.GetListOfBranches():
    branchname_mc = br.GetName()
#    print 'branch ',branchname_mc,' with type_mc ',type(branchname_mc)
    for l in br.GetListOfLeaves():
        lname_mc, ltype_mc = l.GetName(), br.GetLeaf(l.GetName()).GetTypeName()
        name_mc.append(lname_mc)
        type_mc.append(ltype_mc)


# data
file = TFile( '/UserDisk2/othrif/susy/data/Ximo/v25/user.jpoveda.t0703_v25.periodJ.physics_Main.DAOD_SUSY2.grp15_v01_p2425_output.root.55634875/user.jpoveda.7098868._000052.output.root' )

mytree_data = gDirectory.Get('AnaNtup')
#mytree_data.Print()

for br in mytree_data.GetListOfBranches():
    branchname_data = br.GetName()
#    print 'branch ',branchname_data,' with type_data ',type(branchname_data)
    for l in br.GetListOfLeaves():
        lname_data, ltype_data = l.GetName(), br.GetLeaf(l.GetName()).GetTypeName()
        name_data.append(lname_data)
        type_data.append(ltype_data)

#print len(type_mc)
for x in range(0,len(type_mc)):
    tmp = type_mc[x]
    if "Bool_t" in tmp or "bool" in tmp:
        type_ntp.append('O')
    elif "UInt_t" in tmp:
        type_ntp.append('l')
    elif "Int_t" in tmp or "int" in tmp:
        type_ntp.append('I')
    elif "Double_t" in tmp or "double" in tmp or "float" in tmp or "Float_t" in tmp:
        type_ntp.append('F')

#for x in range(0,len(type_ntp)):
#    print x,' ', type_mc[x],' ', type_ntp[x]

###################################################################################################
# OldNtpBranches.h
###################################################################################################

OldNtpBranches = open('OldNtpBranches.h', 'w')

OldNtpBranches.write('//////////////////////////////////////////////////////////\n')
OldNtpBranches.write('// Author:      Othmane Rifki\n')
OldNtpBranches.write('// Contact:     othmane.rifki@cern.ch\n')
OldNtpBranches.write('// Description: MiniNtuple from Ximo AnaNtup\n')
OldNtpBranches.write('// Date %s\n' % strftime("%Y-%m-%d %H:%M:%S", gmtime()))
OldNtpBranches.write('//////////////////////////////////////////////////////////\n')
OldNtpBranches.write('\n')
OldNtpBranches.write('#ifndef OldNtpBranches_h\n')
OldNtpBranches.write('#define OldNtpBranches_h\n')
OldNtpBranches.write('\n')
OldNtpBranches.write('#include <TROOT.h>\n')
OldNtpBranches.write('#include <TChain.h>\n')
OldNtpBranches.write('#include <TFile.h>\n')
OldNtpBranches.write('\n')
OldNtpBranches.write('// Header file for the classes stored in the TTree if any.\n')
OldNtpBranches.write('#include <vector>\n')
OldNtpBranches.write('\n')
OldNtpBranches.write('// Fixed size dimensions of array or collections stored in the TTree if any.\n')
OldNtpBranches.write('\n')
OldNtpBranches.write('using name_mcspace std;\n')
OldNtpBranches.write('\n')
OldNtpBranches.write('class OldNtpBranches {\n')
OldNtpBranches.write(' public :\n')
OldNtpBranches.write('  TTree          *fChain;   //!pointer to the analyzed TTree or TChain\n')
OldNtpBranches.write('  Int_t           fCurrent; //!current Tree number in a TChain\n')
OldNtpBranches.write('  bool is_truth;\n')

OldNtpBranches.write('  %s\n' % line)

OldNtpBranches.write('  //  Declaration of leaf types\n')
for x in range(0,len(name_mc)):
    tmp = type_mc[x]
    if "vector" in tmp:
        tmp = tmp + "*"
    OldNtpBranches.write('  %-20s %-45s;\n' % (tmp,name_mc[x]))
#        print ('{0:30} {0:30};'.format(tmp,name_mc[x]))

OldNtpBranches.write('  %s\n' % line)


OldNtpBranches.write('  // List of branches')
for x in range(0,len(name_mc)):
    OldNtpBranches.write('  TBranch* b_%-20s;  //!\n' % (name_mc[x]))
#    print ('TBranch* b_{0:50};  //!'.format(name_mc[x]))

OldNtpBranches.write('  %s\n' % line)
OldNtpBranches.write('  OldNtpBranches(bool truth);\n')
OldNtpBranches.write('  ~OldNtpBranches();\n')
OldNtpBranches.write('  bool Init(TTree *tree);//true if MC is processed          \n')
OldNtpBranches.write('  void Init_MC(TTree *tree);\n')
OldNtpBranches.write('  void Init_DATA(TTree *tree);\n')
OldNtpBranches.write('  void Init_TRUTH(TTree *tree);\n')
OldNtpBranches.write('};')
OldNtpBranches.write('#endif')
OldNtpBranches.close()


###################################################################################################
# myevt.h
###################################################################################################

myevt = open('myevt.h','w')


myevt.write('//////////////////////////////////////////////////////////\n')
myevt.write('// Author:      Othmane Rifki\n')
myevt.write('// Contact:     othmane.rifki@cern.ch\n')
myevt.write('// Description: MiniNtuple from Ximo AnaNtup\n')
myevt.write('// Date %s\n' % strftime("%Y-%m-%d %H:%M:%S", gmtime()))
myevt.write('//////////////////////////////////////////////////////////\n')
myevt.write('\n')

myevt.write('#ifndef MYEVT_N_HH_\n')
myevt.write('#define MYEVT_N_HH_\n')
myevt.write('\n')
myevt.write('//_____________________________________________________________________________\n')
myevt.write('const Int_t MAXJETS = 100;\n')
myevt.write('const Int_t MAXLEPT = 25;\n')
myevt.write('\n')
myevt.write('//_____________________________________________________________________________\n')
myevt.write('//This is the format used to store the reduced ntuple\n')
myevt.write('struct my_event {\n')
myevt.write('\n')
myevt.write('  Bool_t isMC;\n')
myevt.write('  Double_t           sumWeight;\n')
myevt.write('  Double_t           sumWeightsq;\n')
myevt.write('  Double_t           rawEvents;\n')

myevt.write('\n')
myevt.write('\n')

myevt.write('  //  Declaration of leaf types\n')
for x in range(0,len(name_mc)):
    tmp = type_mc[x]
    if "vector" not in tmp:
        myevt.write('  %s\t %s;\n' % (tmp,name_mc[x]))
    elif ('vector<double>' or 'vector<float>') in tmp:
        if ("Jet_"in name_mc[x]):
            myevt.write('  Float_t\t %s[MAXJETS];\n' % (name_mc[x]))
        else: 
            myevt.write('  Float_t\t %s[MAXLEPT];\n' % (name_mc[x]))
    elif 'vector<bool>' in tmp:
        if ("Jet_"in name_mc[x]):
            myevt.write('  Bool_t\t %s[MAXJETS];\n' % (name_mc[x]))
        else: 
            myevt.write('  Bool_t\t %s[MAXLEPT];\n' % (name_mc[x]))
    elif 'vector<int>' in tmp:
        if ("Jet_"in name_mc[x]):
            myevt.write('  Int_t\t %s[MAXJETS];\n' % (name_mc[x]))
        else: 
            myevt.write('  Int_t\t %s[MAXLEPT];\n' % (name_mc[x]))
        
myevt.write('};\n')
myevt.write('\n')
myevt.write('typedef struct my_event myevt;\n')
myevt.write('\n')
myevt.write('#endif /* MYEVT_N_HH_ */\n')



myevt.close()




###################################################################################################
# src/OldNtpBranches.cxx
###################################################################################################

OldNtpBranches_CXX = open('OldNtpBranches.cxx','w')


OldNtpBranches_CXX.write('//////////////////////////////////////////////////////////\n')
OldNtpBranches_CXX.write('// Author:      Othmane Rifki\n')
OldNtpBranches_CXX.write('// Contact:     othmane.rifki@cern.ch\n')
OldNtpBranches_CXX.write('// Description: MiniNtuple from Ximo AnaNtup\n')
OldNtpBranches_CXX.write('// Date %s\n' % strftime("%Y-%m-%d %H:%M:%S", gmtime()))
OldNtpBranches_CXX.write('//////////////////////////////////////////////////////////\n')
OldNtpBranches_CXX.write('\n')


OldNtpBranches_CXX.write('#include "TTree.h"\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('#include "MiniNtuple/OldNtpBranches.h"\n')
OldNtpBranches_CXX.write('#include <iostream>\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('OldNtpBranches::OldNtpBranches(bool truth) {\n')
OldNtpBranches_CXX.write('  is_truth = truth;\n')
OldNtpBranches_CXX.write('}\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('OldNtpBranches::~OldNtpBranches() {\n')
OldNtpBranches_CXX.write('  if (!fChain)\n')
OldNtpBranches_CXX.write('    return;\n')
OldNtpBranches_CXX.write('  delete fChain->GetCurrentFile();\n')
OldNtpBranches_CXX.write('}\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('bool OldNtpBranches::Init(TTree *tree) {\n')
OldNtpBranches_CXX.write('  // The Init() function is called when the selector needs to initialize       \n')
OldNtpBranches_CXX.write('  // a new tree or chain. Typically here the branch addresses and branch       \n')
OldNtpBranches_CXX.write('  // pointers of the tree will be set.                                         \n')
OldNtpBranches_CXX.write('  // It is normally not necessary to make changes to the generated             \n')
OldNtpBranches_CXX.write('  // code, but the routine can be extended by the user if needed.              \n')
OldNtpBranches_CXX.write('  // Init() will be called many times when running on PROOF                    \n')
OldNtpBranches_CXX.write('  // (once per file to be processed).                                          \n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  bool isMC = false;\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  // Set branch addresses and branch pointers                                  \n')
OldNtpBranches_CXX.write('  if (!tree)\n')
OldNtpBranches_CXX.write('    return isMC;\n')
OldNtpBranches_CXX.write('  fChain = tree;\n')
OldNtpBranches_CXX.write('  fCurrent = -1;\n')
OldNtpBranches_CXX.write('  fChain->SetMakeClass(1);\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  if (!is_truth) {\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('    //We have to determine if we are opening data or MC    \n')
OldNtpBranches_CXX.write('    isMC = (fChain->FindBranch("El_chFlip") != NULL);\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('    //Now we can link the branches ot the variables properly \n')
OldNtpBranches_CXX.write('    if (isMC)\n')
OldNtpBranches_CXX.write('      Init_MC(tree);\n')
OldNtpBranches_CXX.write('    else\n')
OldNtpBranches_CXX.write('	  Init_DATA(tree);\n')
OldNtpBranches_CXX.write('        } else {\n')
OldNtpBranches_CXX.write('    isMC = is_truth;\n')
OldNtpBranches_CXX.write('    Init_TRUTH(tree);\n')
OldNtpBranches_CXX.write('  }\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  return isMC;\n')
OldNtpBranches_CXX.write('}\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('// linking MC variables to branches                                                        \n')
OldNtpBranches_CXX.write('void OldNtpBranches::Init_MC(TTree *tree) {\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  // The Init() function is called when the selector needs to initialize   \n')
OldNtpBranches_CXX.write('  // a new tree or chain. Typically here the branch addresses and branch \n')
OldNtpBranches_CXX.write('  // pointers of the tree will be set.                           \n')
OldNtpBranches_CXX.write('  // It is normally not necessary to make changes to the generated      \n')
OldNtpBranches_CXX.write('  // code, but the routine can be extended by the user if needed.      \n')
OldNtpBranches_CXX.write('  // Init() will be called many times when running on PROOF          \n')
OldNtpBranches_CXX.write('  // (once per file to be processed).                                         \n')
OldNtpBranches_CXX.write('  // declerations go here                                    \n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('   // Set object pointer\n')

for x in range(0,len(name_mc)):
    tmp = type_mc[x]
    if "vector" in tmp:
        OldNtpBranches_CXX.write('   %-20s = 0;  \n' % (name_mc[x]))

OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('   // Set branch addresses and branch pointers\n')
OldNtpBranches_CXX.write('   if (!tree) return;\n')
OldNtpBranches_CXX.write('   fChain = tree;\n')
OldNtpBranches_CXX.write('   fCurrent = -1;\n')
OldNtpBranches_CXX.write('   fChain->SetMakeClass(1);\n')
OldNtpBranches_CXX.write('   \n')

for x in range(0,len(name_mc)):
    OldNtpBranches_CXX.write('   fChain->SetBranchAddress("%-20s", &%-20s, &b_%-20s);\n' % (name_mc[x],name_mc[x],name_mc[x]))


OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  return;\n')
OldNtpBranches_CXX.write('}\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('// linking DATA variables to branches\n')
OldNtpBranches_CXX.write('void OldNtpBranches::Init_DATA(TTree *tree)\n')
OldNtpBranches_CXX.write('{\n')
OldNtpBranches_CXX.write('   // The Init() function is called when the selector needs to initialize\n')
OldNtpBranches_CXX.write('   // a new tree or chain. Typically here the branch addresses and branch\n')
OldNtpBranches_CXX.write('   // pointers of the tree will be set.\n')
OldNtpBranches_CXX.write('   // It is normally not necessary to make changes to the generated\n')
OldNtpBranches_CXX.write('   // code, but the routine can be extended by the user if needed.\n')
OldNtpBranches_CXX.write('   // Init() will be called many times when running on PROOF\n')
OldNtpBranches_CXX.write('   // (once per file to be processed).\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('\n')

for x in range(0,len(name_data)):
    tmp = type_data[x]
    if "vector" in tmp:
        OldNtpBranches_CXX.write('   %-20s = 0;  \n' % (name_data[x]))

OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('   // Set branch addresses and branch pointers\n')
OldNtpBranches_CXX.write('   if (!tree) return;\n')
OldNtpBranches_CXX.write('   fChain = tree;\n')
OldNtpBranches_CXX.write('   fCurrent = -1;\n')
OldNtpBranches_CXX.write('   fChain->SetMakeClass(1);\n')
OldNtpBranches_CXX.write('   \n')

for x in range(0,len(name_data)):
    OldNtpBranches_CXX.write('   fChain->SetBranchAddress("%-20s", &%-20s, &b_%-20s);\n' % (name_data[x],name_data[x],name_data[x]))

OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  return;\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('}\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('// linking TRUTH variables to branches                                   \n')
OldNtpBranches_CXX.write('void OldNtpBranches::Init_TRUTH(TTree *tree) {\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  // The Init() function is called when the selector needs to initialize \n')
OldNtpBranches_CXX.write('  // a new tree or chain. Typically here the branch addresses and branch \n')
OldNtpBranches_CXX.write('  // pointers of the tree will be set.                                   \n')
OldNtpBranches_CXX.write('  // It is normally not necessary to make changes to the generated       \n')
OldNtpBranches_CXX.write('  // code, but the routine can be extended by the user if needed.        \n')
OldNtpBranches_CXX.write('  // Init() will be called many times when running on PROOF              \n')
OldNtpBranches_CXX.write('  // (once per file to be processed).                                    \n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  // declerations go here                                                \n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('  return;\n')
OldNtpBranches_CXX.write('\n')
OldNtpBranches_CXX.write('}\n')






OldNtpBranches_CXX.close()



###################################################################################################
# src/SetNewNtpBranches.cxx
################################################################################################### 
SetNewNtpBranches = open('SetNewNtpBranches.cxx','w')


SetNewNtpBranches.write('//////////////////////////////////////////////////////////\n')
SetNewNtpBranches.write('// Author:      Othmane Rifki\n')
SetNewNtpBranches.write('// Contact:     othmane.rifki@cern.ch\n')
SetNewNtpBranches.write('// Description: MiniNtuple from Ximo AnaNtup\n')
SetNewNtpBranches.write('// Date %s\n' % strftime("%Y-%m-%d %H:%M:%S", gmtime()))
SetNewNtpBranches.write('//////////////////////////////////////////////////////////\n')
SetNewNtpBranches.write('\n')


SetNewNtpBranches.write('#include "TTree.h"\n')
SetNewNtpBranches.write('#include "TBranch.h"\n')
SetNewNtpBranches.write('#include "TLeaf.h"\n')
SetNewNtpBranches.write('\n')
SetNewNtpBranches.write('#include "MiniNtuple/TMiniNtuple.h"\n')
SetNewNtpBranches.write('#include "MiniNtuple/myevt.h"\n')
SetNewNtpBranches.write('\n')
SetNewNtpBranches.write('//___________________________________________________________________\n')
SetNewNtpBranches.write('void TMiniNtuple::SetNewNtpBranches() {\n')
SetNewNtpBranches.write('\n')
SetNewNtpBranches.write('  if(!b){\n')
SetNewNtpBranches.write('	b = t_MiniNtuple->Branch("myevt", evt, "isMC/O:sumWeight/D:sumWeightsq/D:rawEvents/D:')
for x in range(0,len(name_mc)):
    if "vector" in type_mc[x]:
        if "Jet_" in name_mc[x]:
            SetNewNtpBranches.write('%s[MAXJETS]/%s' % (name_mc[x],type_ntp[x]))
        else:
            SetNewNtpBranches.write('%s[MAXLEPT]/%s' % (name_mc[x],type_ntp[x]))
    else: 
        SetNewNtpBranches.write('%s/%s' % (name_mc[x],type_ntp[x]))
    if x < len(name_mc)-1:
        SetNewNtpBranches.write(':')
SetNewNtpBranches.write('", basket_size);\n')
SetNewNtpBranches.write('	b->SetCompressionLevel(1);\n')
SetNewNtpBranches.write('  }\n')
SetNewNtpBranches.write('\n')
SetNewNtpBranches.write('\n')
SetNewNtpBranches.write('\n')

for x in range(0,len(name_mc)):
    SetNewNtpBranches.write('   b->GetLeaf("%-40s")->SetAddress(&(evt->%-20s));\n' % (name_mc[x],name_mc[x]))

SetNewNtpBranches.write('\n')
SetNewNtpBranches.write('  //now we need to loop through the list of leaves to assign them proper values.\n')
SetNewNtpBranches.write('  TObjArray *ll = b->GetListOfLeaves();\n')
SetNewNtpBranches.write('  Int_t n_leaves = ll->GetEntries();\n')
SetNewNtpBranches.write('  TLeaf *l;\n')
SetNewNtpBranches.write('  intptr_t offset;\n')
SetNewNtpBranches.write('\n')
SetNewNtpBranches.write('  for (int i = 0; i < n_leaves; i++) {\n')
SetNewNtpBranches.write('    l = (TLeaf*) (ll->At(i));\n')
SetNewNtpBranches.write('    offset = (intptr_t) (l->GetValuePointer()) - (intptr_t) (&evt);\n')
SetNewNtpBranches.write('    l->SetOffset(offset);\n')
SetNewNtpBranches.write('  }\n')
SetNewNtpBranches.write('\n')
SetNewNtpBranches.write('}\n')


SetNewNtpBranches.close()




###################################################################################################
# src/TMiniNtuple.cxx 
################################################################################################### 
TMiniNtuple_CXX = open('TMiniNtuple.cxx','w')


TMiniNtuple_CXX.write('//////////////////////////////////////////////////////////\n')
TMiniNtuple_CXX.write('// Author:      Othmane Rifki\n')
TMiniNtuple_CXX.write('// Contact:     othmane.rifki@cern.ch\n')
TMiniNtuple_CXX.write('// Description: MiniNtuple from Ximo AnaNtup\n')
TMiniNtuple_CXX.write('// Date %s\n' % strftime("%Y-%m-%d %H:%M:%S", gmtime()))
TMiniNtuple_CXX.write('//////////////////////////////////////////////////////////\n')
TMiniNtuple_CXX.write('\n')



TMiniNtuple_CXX.write('#include <iostream>\n')
TMiniNtuple_CXX.write('#include <fstream>\n')
TMiniNtuple_CXX.write('#include <stdlib.h>\n')
TMiniNtuple_CXX.write('#include <strstream>\n')
TMiniNtuple_CXX.write('#include <cstring>\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('#include "TFile.h"\n')
TMiniNtuple_CXX.write('#include "TMath.h"\n')
TMiniNtuple_CXX.write('#include "TTree.h"\n')
TMiniNtuple_CXX.write('#include "TBranch.h"\n')
TMiniNtuple_CXX.write('#include "TLeaf.h"\n')
TMiniNtuple_CXX.write('#include "TRandom.h"\n')
TMiniNtuple_CXX.write('#include <TLorentzVector.h>\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('#include "MiniNtuple/TMiniNtuple_CXX.h"\n')
TMiniNtuple_CXX.write('#include "MiniNtuple/myevt.h"\n')
TMiniNtuple_CXX.write('#include "MiniNtuple/OldNtpBranches.h"\n')
TMiniNtuple_CXX.write('#include "MiniNtuple/JetQuarkLabelD3PD.h"\n')
TMiniNtuple_CXX.write('#include "MiniNtuple/RecoTruthMatch.h"\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('long double weightedSum_events = 0;\n')
TMiniNtuple_CXX.write('long double rawEvents = 0;\n')
TMiniNtuple_CXX.write('long double weightedSumsq_events = 0;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('//__________________________________________________________________________\n')
TMiniNtuple_CXX.write('TMiniNtuple::TMiniNtuple_CXX(const std::string& name, ISvcLocator* pSvcLocator) :\n')
TMiniNtuple_CXX.write('  Algorithm(name, pSvcLocator) {\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  declareProperty("OutputFileName", ntpName = "output.root");\n')
TMiniNtuple_CXX.write('  declareProperty("InputFileName", inpName);\n')
TMiniNtuple_CXX.write('  declareProperty("Debug", debug = true);\n')
TMiniNtuple_CXX.write('  declareProperty("ApplyLeptonSkim", m_applyLeptonSkim = false);\n')
TMiniNtuple_CXX.write('  declareProperty("MinLeptonPt", m_minLeptonPt = 9000.); //was 13 GeV\n')
TMiniNtuple_CXX.write('}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('//_____________________________________________________________________________\n')
TMiniNtuple_CXX.write('TMiniNtuple::~TMiniNtuple_CXX() {\n')
TMiniNtuple_CXX.write('}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('//_____________________________________________________________________________\n')
TMiniNtuple_CXX.write('StatusCode TMiniNtuple::initialize() {\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  StatusCode sc = StatusCode::SUCCESS;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  if (inpName.size() == 0)\n')
TMiniNtuple_CXX.write('	return StatusCode::FAILURE;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  //	t_inpNtuple = new TChain("susy");\n')
TMiniNtuple_CXX.write('  t_inpNtuple = new TChain("AnaNtup");\n')
TMiniNtuple_CXX.write('  std::cout << "Reading: " << inpName.at(0).data() << "\\n";\n')
TMiniNtuple_CXX.write('  if (t_inpNtuple->Add(inpName.at(0).data(), 0) == 0) { // the file is empty or it does not contain "AnaNtup" tree\n')
TMiniNtuple_CXX.write('	delete t_inpNtuple;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	t_inpNtuple = new TChain("truth");\n')
TMiniNtuple_CXX.write('	is_truth = true;\n')
TMiniNtuple_CXX.write('	if (t_inpNtuple->Add(inpName.at(0).data(), 0) == 0) {\n')
TMiniNtuple_CXX.write('	  std::cerr\n')
TMiniNtuple_CXX.write('		<< "\\nThe given file does not contain a susy or truth tree or is non-existent\\n";\n')
TMiniNtuple_CXX.write('	  return StatusCode::FAILURE;\n')
TMiniNtuple_CXX.write('	} else {\n')
TMiniNtuple_CXX.write('	  std::cout << "\\nProcessing a TruthD3PD dataset.\\n";\n')
TMiniNtuple_CXX.write('	}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  } else {\n')
TMiniNtuple_CXX.write('	is_truth = false;\n')
TMiniNtuple_CXX.write('	std::cout << "\\nPrecessing a SUSY_D3PD dataset.\\n";\n')
TMiniNtuple_CXX.write('  }\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  std::cout << "----- begin job: ---- \\n";\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  for (unsigned int i = 1; i < inpName.size(); i++) {\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	std::cout << "Reading: " << inpName.at(i).data() << "\\n";\n')
TMiniNtuple_CXX.write('	if (t_inpNtuple->Add(inpName.at(i).data(), 0) == 0) { // breaks if an empty file is given\n')
TMiniNtuple_CXX.write('	  std::cerr\n')
TMiniNtuple_CXX.write('		<< "\\nThe given file does not contain a susy or truth tree or is non-existent\\n";\n')
TMiniNtuple_CXX.write('	  return StatusCode::FAILURE;\n')
TMiniNtuple_CXX.write('	}\n')
TMiniNtuple_CXX.write('  }\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  long double beforeD = 0.;\n')
TMiniNtuple_CXX.write('  long double afterD = 0.;\n')
TMiniNtuple_CXX.write('  long double beforeDRaw = 0.;\n')
TMiniNtuple_CXX.write('  long double afterDRaw = 0.;\n')
TMiniNtuple_CXX.write('  long double beforeDsq = 0.;\n')
TMiniNtuple_CXX.write('  long double afterDsq = 0.;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  std::cout << "file    originalxAOD    DxAOD    originalxAODsq    DxAODsq" << std::endl;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  for (unsigned int i = 0; i < inpName.size(); i++) {\n')
TMiniNtuple_CXX.write('	std::cout << "file " << i << " ";\n')
TMiniNtuple_CXX.write('	TFile f(inpName.at(i).data(), "READ");\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	TH1D* h_events = (TH1D*) f.Get("DerivationStat_Weights");\n')
TMiniNtuple_CXX.write('	if (h_events != NULL) {  \n')
TMiniNtuple_CXX.write('	  std::cout << h_events->GetBinContent(1) << " ";\n')
TMiniNtuple_CXX.write('	  std::cout << h_events->GetBinContent(2) << " ";\n')
TMiniNtuple_CXX.write('	  beforeD += h_events->GetBinContent(1);\n')
TMiniNtuple_CXX.write('	  afterD += h_events->GetBinContent(2);\n')
TMiniNtuple_CXX.write('	}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	TH1D* h_events_sq = (TH1D*) f.Get("DerivationStat_Weights_Squared");\n')
TMiniNtuple_CXX.write('	if (h_events_sq != NULL) {  \n')
TMiniNtuple_CXX.write('	  std::cout << h_events_sq->GetBinContent(1) << " ";\n')
TMiniNtuple_CXX.write('	  std::cout << h_events_sq->GetBinContent(2) << " ";\n')
TMiniNtuple_CXX.write('	  beforeDsq += h_events_sq->GetBinContent(1);\n')
TMiniNtuple_CXX.write('	  afterDsq += h_events_sq->GetBinContent(2);\n')
TMiniNtuple_CXX.write('	}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	TH1D* h_events_raw = (TH1D*) f.Get("DerivationStat_RawEvents");\n')
TMiniNtuple_CXX.write('	if (h_events_raw != NULL) {  \n')
TMiniNtuple_CXX.write('	  std::cout << h_events_raw->GetBinContent(1) << " ";\n')
TMiniNtuple_CXX.write('	  std::cout << h_events_raw->GetBinContent(2) << " ";\n')
TMiniNtuple_CXX.write('	  beforeDRaw += h_events_raw->GetBinContent(1);\n')
TMiniNtuple_CXX.write('	  afterDRaw += h_events_raw->GetBinContent(2);\n')
TMiniNtuple_CXX.write('	}\n')
TMiniNtuple_CXX.write('	\n')
TMiniNtuple_CXX.write('	f.Close();\n')
TMiniNtuple_CXX.write('	\n')
TMiniNtuple_CXX.write('	std::cout << std::endl;\n')
TMiniNtuple_CXX.write('  }\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  weightedSum_events = beforeD;\n')
TMiniNtuple_CXX.write('  weightedSumsq_events = beforeDsq;\n')
TMiniNtuple_CXX.write('  rawEvents = beforeDRaw;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  std::cout << "before raw " << beforeDRaw << std::endl;\n')
TMiniNtuple_CXX.write('  std::cout << "after raw " << afterDRaw << std::endl;\n')
TMiniNtuple_CXX.write('  std::cout << "before " << beforeD << std::endl;\n')
TMiniNtuple_CXX.write('  std::cout << "after " << afterD << std::endl;\n')
TMiniNtuple_CXX.write('  std::cout << "before sq " << beforeDsq << std::endl;\n')
TMiniNtuple_CXX.write('  std::cout << "after sq " << afterDsq << std::endl;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  if (debug)\n')
TMiniNtuple_CXX.write('	std::cout << "opening output root file" << std::endl;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  outputRootFile = new TFile(ntpName.data(), "RECREATE");\n')
TMiniNtuple_CXX.write('  //  gDirectory->mkdir("DerivationStat")->cd();\n')
TMiniNtuple_CXX.write('  gDirectory->cd("/");\n')
TMiniNtuple_CXX.write('  m_h_events_raw = new TH1D("h_events_raw", "Raw Events before/after derivation", 2, -0.5, 1.5);\n')
TMiniNtuple_CXX.write('  m_h_events_raw->GetXaxis()->FindBin("original xAOD");\n')
TMiniNtuple_CXX.write('  m_h_events_raw->GetXaxis()->FindBin("DxAOD");\n')
TMiniNtuple_CXX.write('  m_h_events_raw->SetBinContent(1, beforeDRaw);\n')
TMiniNtuple_CXX.write('  m_h_events_raw->SetBinContent(2, afterDRaw);\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  m_h_events = new TH1D("h_events", "Events before/after derivation", 2, -0.5, 1.5);\n')
TMiniNtuple_CXX.write('  m_h_events->GetXaxis()->FindBin("original xAOD");\n')
TMiniNtuple_CXX.write('  m_h_events->GetXaxis()->FindBin("DxAOD");\n')
TMiniNtuple_CXX.write('  m_h_events->SetBinContent(1, beforeD);\n')
TMiniNtuple_CXX.write('  m_h_events->SetBinContent(2, afterD);\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  m_h_events_sq = new TH1D("h_events_sq", "Events before/after derivation (squared)", 2, -0.5, 1.5);\n')
TMiniNtuple_CXX.write('  m_h_events_sq->GetXaxis()->FindBin("original xAOD");\n')
TMiniNtuple_CXX.write('  m_h_events_sq->GetXaxis()->FindBin("DxAOD");\n')
TMiniNtuple_CXX.write('  m_h_events_sq->SetBinContent(1, beforeDsq);\n')
TMiniNtuple_CXX.write('  m_h_events_sq->SetBinContent(2, afterDsq);\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  if (debug)\n')
TMiniNtuple_CXX.write('	std::cout << "booking variables into the tree..." << std::endl;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  //Initialize the new tree:\n')
TMiniNtuple_CXX.write('  evt = new myevt;\n')
TMiniNtuple_CXX.write('  memset(evt, 0, sizeof(myevt));\n')
TMiniNtuple_CXX.write('  t_MiniNtuple = new TTree("MiniNtuple", "a reduced ntuple");\n')
TMiniNtuple_CXX.write('  b = NULL;\n')
TMiniNtuple_CXX.write('  SetNewNtpBranches();\n')
TMiniNtuple_CXX.write('  oldTree = new OldNtpBranches(is_truth);\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  return sc;\n')
TMiniNtuple_CXX.write('}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('//_____________________________________________________________________________\n')
TMiniNtuple_CXX.write('StatusCode TMiniNtuple::execute() {\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  StatusCode sc = StatusCode::SUCCESS;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  std::cout << "----- initializing the main event loop: ---- \\n";\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  //Here we implement the main event loop\n')
TMiniNtuple_CXX.write('  if (!t_inpNtuple)\n')
TMiniNtuple_CXX.write('	return StatusCode::FAILURE;\n')
TMiniNtuple_CXX.write('  Long64_t treeEntries = (Long64_t) t_inpNtuple->GetEntries();\n')
TMiniNtuple_CXX.write('  //	treeEntries = 100; // temporary\n')
TMiniNtuple_CXX.write('  std::cout << "Expect to process " << treeEntries << " entries" << std::endl;\n')
TMiniNtuple_CXX.write('  if (treeEntries == 0)\n')
TMiniNtuple_CXX.write('	return StatusCode::FAILURE;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  t_inpNtuple->GetEntry(0);\n')
TMiniNtuple_CXX.write('  evt->isMC = oldTree->Init(t_inpNtuple);\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  if (evt->isMC)\n')
TMiniNtuple_CXX.write('	std::cout << "Processing MC\\n";\n')
TMiniNtuple_CXX.write('  else\n')
TMiniNtuple_CXX.write('	std::cout << "Processing DATA\\n";\n')
TMiniNtuple_CXX.write('  \n')
TMiniNtuple_CXX.write('  int treeno = -1;\n')
TMiniNtuple_CXX.write('  for (Long64_t i = 0; i < treeEntries; i++) {\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	// only way I can get this to be reliable\n')
TMiniNtuple_CXX.write('	t_inpNtuple->GetEntry(i);\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	if (treeno != ((TChain*) t_inpNtuple)->GetTreeNumber()) {\n')
TMiniNtuple_CXX.write('	  evt->isMC = oldTree->Init(t_inpNtuple);\n')
TMiniNtuple_CXX.write('	  t_inpNtuple->GetEntry(i);\n')
TMiniNtuple_CXX.write('	  treeno = ((TChain*) t_inpNtuple)->GetTreeNumber();\n')
TMiniNtuple_CXX.write('	  //SetNewNtpBranches(); //TODO: Do we need this line?\n')
TMiniNtuple_CXX.write('	}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	// initializing ntuple variables\n')
TMiniNtuple_CXX.write('	InitNtpVar(evt);\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	//==========================================================================\n')
TMiniNtuple_CXX.write('	// We do all processing here:\n')
TMiniNtuple_CXX.write('	//	std::cout << "Event # " << i << "\\n";\n')
TMiniNtuple_CXX.write('\n')

# MC
TMiniNtuple_CXX.write('    if(evt->isMC){\n')

TMiniNtuple_CXX.write('      evt->sumWeight = weightedSum_events;\n')
TMiniNtuple_CXX.write('      evt->sumWeightsq = weightedSumsq_events;\n')
TMiniNtuple_CXX.write('      evt->rawEvents = rawEvents;\n')

for x in range(0,len(name_mc)):
    if 'vector' not in type_mc[x] and 'NEl' not in name_mc[x] and 'NMu' not in name_mc[x] and 'NJet' not in name_mc[x]:
        TMiniNtuple_CXX.write('      evt->%-40s = oldTree->%-40s;\n' % (name_mc[x], name_mc[x] ) )

TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('      //electrons\n')
TMiniNtuple_CXX.write('      int j = 0;\n')
TMiniNtuple_CXX.write('      for (int i = 0; i < oldTree->NEl; i++) {\n')
TMiniNtuple_CXX.write('		if (j == MAXLEPT) {\n')
TMiniNtuple_CXX.write('		  std::cout << "WARNING: Too many electrons\\n";\n')
TMiniNtuple_CXX.write('		  break;\n')
TMiniNtuple_CXX.write('	      }\n')

for x in range(0,len(name_mc)):
    if 'vector' in type_mc[x]:
        if 'El_' in name_mc[x]:
            TMiniNtuple_CXX.write('    evt->%s[j] = oldTree->%s->at(i);\n' % (name_mc[x], name_mc[x] ) )

TMiniNtuple_CXX.write('    j++;\n')
TMiniNtuple_CXX.write('   }\n')
TMiniNtuple_CXX.write('   evt->NEl = j;\n')

TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	//muons\n')
TMiniNtuple_CXX.write('	int j = 0;\n')
TMiniNtuple_CXX.write('	for (int i = 0; i < oldTree->NMu; i++) {\n')
TMiniNtuple_CXX.write('	  if (j == MAXLEPT) {\n')
TMiniNtuple_CXX.write('		std::cout << "WARNING: Too many muons\\n";\n')
TMiniNtuple_CXX.write('		break;\n')
TMiniNtuple_CXX.write('	  }\n')

for x in range(0,len(name_mc)):
    if 'vector' in type_mc[x]:
        if 'Mu_' in name_mc[x]:
            TMiniNtuple_CXX.write('    evt->%s[j] = oldTree->%s->at(i);\n' % (name_mc[x], name_mc[x] ) )

TMiniNtuple_CXX.write('    j++;\n')
TMiniNtuple_CXX.write('   }\n')
TMiniNtuple_CXX.write('   evt->NMu = j\n')

TMiniNtuple_CXX.write('	//jets\n')
TMiniNtuple_CXX.write('	j = 0;\n')
TMiniNtuple_CXX.write('	for (int i = 0; i < oldTree->NJet; i++) {\n')
TMiniNtuple_CXX.write('	  if (j == MAXJETS) {\n')
TMiniNtuple_CXX.write('		std::cout << "WARNING: Too many jets\\n";\n')
TMiniNtuple_CXX.write('		break;\n')
TMiniNtuple_CXX.write('	  }\n')

for x in range(0,len(name_mc)):
    if 'vector' in type_mc[x]:
        if 'Jet_' in name_mc[x]:
            TMiniNtuple_CXX.write('    evt->%s[j] = oldTree->%s->at(i);\n' % (name_mc[x], name_mc[x] ) )
TMiniNtuple_CXX.write('    j++;\n')
TMiniNtuple_CXX.write('   }\n')
TMiniNtuple_CXX.write('   evt->NJet = j;\n')




TMiniNtuple_CXX.write('}else{ \n')

TMiniNtuple_CXX.write('    evt->sumWeight = -1;\n')
TMiniNtuple_CXX.write('    evt->sumWeightsq = -1;\n')
TMiniNtuple_CXX.write('    evt->rawEvents = -1;\n')


for x in range(0,len(name_data)):
    if 'vector' not in type_data[x] and 'NEl' not in name_data[x] and 'NMu' not in name_data[x] and 'NJet' not in name_data[x]:
        TMiniNtuple_CXX.write('    evt->%-40s = oldTree->%-40s;\n' % (name_data[x], name_data[x] ) )

TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	//electrons\n')
TMiniNtuple_CXX.write('	int j = 0;\n')
TMiniNtuple_CXX.write('	for (int i = 0; i < oldTree->NEl; i++) {\n')
TMiniNtuple_CXX.write('	  if (j == MAXLEPT) {\n')
TMiniNtuple_CXX.write('		std::cout << "WARNING: Too many electrons\\n";\n')
TMiniNtuple_CXX.write('		break;\n')
TMiniNtuple_CXX.write('	  }\n')

for x in range(0,len(name_data)):
    if 'vector' in type_data[x]:
        if 'El_' in name_data[x]:
            TMiniNtuple_CXX.write('    evt->%s[j] = oldTree->%s->at(i);\n' % (name_data[x], name_data[x] ) )

TMiniNtuple_CXX.write('    j++;\n')
TMiniNtuple_CXX.write('   }\n')
TMiniNtuple_CXX.write('   evt->NEl = j;\n')

TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('	//muons\n')
TMiniNtuple_CXX.write('	int j = 0;\n')
TMiniNtuple_CXX.write('	for (int i = 0; i < oldTree->NMu; i++) {\n')
TMiniNtuple_CXX.write('	  if (j == MAXLEPT) {\n')
TMiniNtuple_CXX.write('		std::cout << "WARNING: Too many muons\\n";\n')
TMiniNtuple_CXX.write('		break;\n')
TMiniNtuple_CXX.write('	  }\n')

for x in range(0,len(name_data)):
    if 'vector' in type_data[x]:
        if 'Mu_' in name_data[x]:
            TMiniNtuple_CXX.write('    evt->%s[j] = oldTree->%s->at(i);\n' % (name_data[x], name_data[x] ) )

TMiniNtuple_CXX.write('    j++;\n')
TMiniNtuple_CXX.write('   }\n')
TMiniNtuple_CXX.write('   evt->NMu = j\n')

TMiniNtuple_CXX.write('	//jets\n')
TMiniNtuple_CXX.write('	j = 0;\n')
TMiniNtuple_CXX.write('	for (int i = 0; i < oldTree->NJet; i++) {\n')
TMiniNtuple_CXX.write('	  if (j == MAXJETS) {\n')
TMiniNtuple_CXX.write('		std::cout << "WARNING: Too many jets\\n";\n')
TMiniNtuple_CXX.write('		break;\n')
TMiniNtuple_CXX.write('	  }\n')

for x in range(0,len(name_data)):
    if 'vector' in type_data[x]:
        if 'Jet_' in name_data[x]:
            TMiniNtuple_CXX.write('    evt->%s[j] = oldTree->%s->at(i);\n' % (name_data[x], name_data[x] ) )
TMiniNtuple_CXX.write('    j++;\n')
TMiniNtuple_CXX.write('   }\n')
TMiniNtuple_CXX.write('   evt->NJet = j;\n')



TMiniNtuple_CXX.write('	  }\n')
TMiniNtuple_CXX.write('	//==========================================================================\n')
TMiniNtuple_CXX.write('	if (-1 == t_MiniNtuple->Fill()) { // fill root tree\n')
TMiniNtuple_CXX.write('	  std::cerr\n')
TMiniNtuple_CXX.write('		<< "ERROR: Can not fill the tree for the reduced ntuple.\n')
TMiniNtuple_CXX.write('";\n')
TMiniNtuple_CXX.write('	  return StatusCode::FAILURE;\n')
TMiniNtuple_CXX.write('	}\n')
TMiniNtuple_CXX.write('  }\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  return sc;\n')
TMiniNtuple_CXX.write('}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('//_____________________________________________________________________________\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('StatusCode TMiniNtuple::finalize() {\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  StatusCode sc = StatusCode::SUCCESS;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  outputRootFile = t_MiniNtuple->GetCurrentFile(); //just in case we switched to a new file\n')
TMiniNtuple_CXX.write('  outputRootFile->Write(); // close output root file\n')
TMiniNtuple_CXX.write('  outputRootFile->Close(); // close output root file\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  delete oldTree;\n')
TMiniNtuple_CXX.write('  delete evt;\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  std::cout << "----- end job: ---- \n')
TMiniNtuple_CXX.write('";\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  return sc;\n')
TMiniNtuple_CXX.write('}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('//____________________________________________________________________________\n')
TMiniNtuple_CXX.write('void TMiniNtuple::InitNtpVar(myevt *ev) {\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  //	ev->el_n = 0;\n')

TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  return;\n')
TMiniNtuple_CXX.write('}\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('//_____________________________________________________________________________\n')
TMiniNtuple_CXX.write('float TMiniNtuple::deltaR(float eta1, float phi1, float eta2, float phi2) {\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  float deltaR12 = phi1 - phi2;\n')
TMiniNtuple_CXX.write('  if (deltaR12 > TMath::Pi())\n')
TMiniNtuple_CXX.write('	deltaR12 -= 2 * TMath::Pi();\n')
TMiniNtuple_CXX.write('  if (deltaR12 < -TMath::Pi())\n')
TMiniNtuple_CXX.write('	deltaR12 += 2 * TMath::Pi();\n')
TMiniNtuple_CXX.write('\n')
TMiniNtuple_CXX.write('  deltaR12 = sqrt(deltaR12 * deltaR12 + (eta1 - eta2) * (eta1 - eta2));\n')
TMiniNtuple_CXX.write('  return deltaR12;\n')
TMiniNtuple_CXX.write('}\n')
TMiniNtuple_CXX.write('\n')


TMiniNtuple_CXX.close()

###################################################################################################
# MiniNtuple/TMiniNtuple.h
################################################################################################### 
TMiniNtuple_H = open('TMiniNtuple.h','w')


TMiniNtuple_H.write('//////////////////////////////////////////////////////////\n')
TMiniNtuple_H.write('// Author:      Othmane Rifki\n')
TMiniNtuple_H.write('// Contact:     othmane.rifki@cern.ch\n')
TMiniNtuple_H.write('// Description: MiniNtuple from Ximo AnaNtup\n')
TMiniNtuple_H.write('// Date %s\n' % strftime("%Y-%m-%d %H:%M:%S", gmtime()))
TMiniNtuple_H.write('//////////////////////////////////////////////////////////\n')
TMiniNtuple_H.write('\n')


TMiniNtuple_H.write('#include "TTree.h"\n')

TMiniNtuple_H.write('#ifndef MININTUPLE_HH_\n')
TMiniNtuple_H.write('#define MININTUPLE_HH_\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('#include "GaudiKernel/ToolHandle.h"\n')
TMiniNtuple_H.write('#include "GaudiKernel/Algorithm.h"\n')
TMiniNtuple_H.write('#include "GaudiKernel/Property.h"\n')
TMiniNtuple_H.write('#include "CLHEP/Units/SystemOfUnits.h"\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('#include <string>\n')
TMiniNtuple_H.write('#include <vector>\n')
TMiniNtuple_H.write('#include <stdlib.h>\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('#include "TTree.h"\n')
TMiniNtuple_H.write('#include "TChain.h"\n')
TMiniNtuple_H.write('#include "TFile.h"\n')
TMiniNtuple_H.write('#include "TH1D.h"\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('#include <MiniNtuple/myevt.h>\n')
TMiniNtuple_H.write('#include <MiniNtuple/OldNtpBranches.h>\n')
TMiniNtuple_H.write('#include "MiniNtuple/JetQuarkLabelD3PD.h"\n')
TMiniNtuple_H.write('#include "MiniNtuple/RecoTruthMatch.h"\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('//_____________________________________________________________\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('//memory management constants\n')
TMiniNtuple_H.write('const int basket_size = 256 * 1024; // basket size\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('//---------------------------------------------------------------------------------------\n')
TMiniNtuple_H.write('class TMiniNtuple: public Algorithm {\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('protected:\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('	// The struct stores the reduced event information\n')
TMiniNtuple_H.write('	myevt* evt;\n')
TMiniNtuple_H.write('	TFile* outputRootFile;\n')
TMiniNtuple_H.write('	TBranch	*b;\n')
TMiniNtuple_H.write('	TTree* t_MiniNtuple; //output Tree\n')
TMiniNtuple_H.write('	bool is_truth;\n')
TMiniNtuple_H.write('	std::vector<std::string> inpName;\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('	//D3PD\n')
TMiniNtuple_H.write('	TChain* t_inpNtuple;\n')
TMiniNtuple_H.write('	OldNtpBranches *oldTree; //stores D3PD variables\n')
TMiniNtuple_H.write('	std::string ntpName;\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('	bool debug;\n')
TMiniNtuple_H.write('	bool m_applyLeptonSkim;\n')
TMiniNtuple_H.write('	double m_minLeptonPt; \n')
TMiniNtuple_H.write('	TH1D * m_h_events_raw;\n')
TMiniNtuple_H.write('	TH1D * m_h_events;\n')
TMiniNtuple_H.write('	TH1D * m_h_events_sq;\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('public:\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('	TMiniNtuple(const std::string &name, ISvcLocator *pSvcLocator);\n')
TMiniNtuple_H.write('	~TMiniNtuple();\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('	StatusCode initialize();\n')
TMiniNtuple_H.write('	StatusCode execute();\n')
TMiniNtuple_H.write('	StatusCode finalize();\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('	// ****** other methods\n')
TMiniNtuple_H.write('	void InitNtpVar(myevt *ev); // initialize all the ntp variables\n')
TMiniNtuple_H.write('	void SetNewNtpBranches();\n')
TMiniNtuple_H.write('	void SetOldNtpBranches();\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('	// Service functions\n')
TMiniNtuple_H.write('	// These are executed for each event to fill the reduced ntuple\n')
TMiniNtuple_H.write('	// Each method assumes that the corresponding STNtuple block exists\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('	//we recalculate the number of tracks in a jet using track quality cuts\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('	float deltaR(float eta1, float phi1, float eta2, float phi2);\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('};\n')
TMiniNtuple_H.write('\n')
TMiniNtuple_H.write('#endif /* MININTUPLE_HH_ */\n')


TMiniNtuple_H.close()
