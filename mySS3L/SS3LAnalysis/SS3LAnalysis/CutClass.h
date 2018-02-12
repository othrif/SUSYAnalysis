#ifndef Cut_h
#define Cut_h

using namespace std;

#include "TLorentzVector.h"
#include <vector>
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH2.h"
#include "TH1.h"
#include "TLorentzVector.h"

class CutClass {
public :

  //  CutClass(Int_t debug, Int_t dc3selection, Int_t readtype);
  CutClass();
  virtual ~CutClass();

   // Particle Structures
   typedef struct {
     Bool_t good;
     Bool_t goodOR;
     Int_t ID;
     Int_t NtupIndex;
     Double_t rMatchEle;
     Double_t rMatchMuon;
     Double_t EtCone20;
     Double_t EtCone30;
     Double_t EtCone40;

     Double_t PtCone20;
     Double_t PtCone30;
     Double_t PtCone40;

     Double_t PtVarCone20;
     Double_t PtVarCone30;
     Double_t PtVarCone40;

     Double_t LooseIso;
     Double_t MediumIso;
     Double_t TightIso;

     Int_t isLoose;
     Int_t isMedium;
     Int_t isTight;
     Int_t isLooseLH;
     Int_t isMediumLH;
     Int_t isTightLH;
     Int_t Author;

     TLorentzVector FourVector;
     TLorentzVector FourVectorEM;
     TLorentzVector FourVectorID;
     TLorentzVector FourVectorMS;
     Double_t etaS2;
     Double_t cl_eta;
     Double_t EMfrac;
     Double_t n90;
     Double_t quality;
     Double_t timing;
     Double_t HECf;
     Double_t EMJES;
     Double_t TileGap3f;
     Int_t    SamplingMax;
     Float_t  FSamplingMax;
     Float_t  BCH_CORR_JET;

     Int_t NPixHits;
     Int_t NSCTHits;
     Int_t NBlayHits;
     Int_t ExpBlayHits;
     Double_t d0pvtx;
     Double_t z0pvtx; 
     Double_t d0pvtxerr;
     Double_t sigd0;
     Double_t z0pvtxerr;

     Double_t d0old;
     Double_t sigd0old;

     Double_t JVF;
     Double_t JVT;
     Double_t LocTrFlav;

     Double_t d0;
     Double_t z0;
     UInt_t isEM;
     Double_t SV0;
     Double_t MV2c20;

     Int_t ExpBLayer;

     Int_t isCombined;
     Int_t Type;
     Int_t Origin;
     Int_t Barcode;

     Double_t SFweight;
     Double_t SFweightMedium;
     Double_t SFweightMediumLH;
     Double_t SFweightTight;
     Double_t SFweightTightLH;
     Double_t SFweightLooseLH;

     Double_t SFweightTrigMedium;
     Double_t SFweightTrigMediumLH;
     Double_t SFweightTrigTight;
     Double_t SFweightTrigTightLH;
     Double_t SFweightTrigLooseLH;

     Double_t SFwtrig;
     Double_t SFtrig_set33;
     Double_t SFtrig_set34;
     Double_t SFtrig_set35;
     Double_t SFtrig_set36;

     Int_t isBad;
     Int_t isTriggerMatch;
     Int_t isTriggerMatchMu18;
     Int_t isSig;
     Int_t isCosmic;

     Int_t isTriggerMatch_e12;
     Int_t isTriggerMatch_e17;
     Int_t isTriggerMatch_e24;
     Int_t isTriggerMatch_e50;

     Int_t isTriggerMatch_mu50;
     Int_t isTriggerMatch_mu26;
     Int_t isTriggerMatch_mu8;
     Int_t isTriggerMatch_mu14;
     Int_t isTriggerMatch_mu18;
     Int_t isTriggerMatch_MU10;
     Int_t isTriggerMatch_MU15;
     Int_t isTriggerMatch_MU20;

     Int_t Mother;
       Int_t chFlip;

   } Particle;

   virtual void     Sort(vector<Particle> vPart);
   // virtual bool     SortPt(Particle p1,Particle p2);

   // Pre-cut
   virtual bool     ElectronCrackVeto(vector<Particle> vEle);
   virtual void     OneLepton(vector<Particle> vEle, vector<Particle> vMu, bool Cut[3][3]);
   virtual bool     OneLepton(vector<Particle> vLep);
   virtual bool     TwoLeptonsOS(vector<Particle> vLep);
   virtual bool     TwoLeptonsSS(vector<Particle> vLep);
   virtual bool     ThreeLeptons(vector<Particle> vLep);
   virtual bool     mLLCutOS(vector<Particle> vLep,float  mllCut);
   virtual bool     mLLCutSS(vector<Particle> vLep,float  mllCut);
   virtual bool     mLLCut3L(vector<Particle> vLep,float  mllCut);
   virtual bool     ZeroLepton(vector<Particle> vLep);
   
   virtual bool     JetCuts(vector<Particle> vJet,int njets,float ptLeading,float ptLast);

   
   // Meff
   virtual float    MEff_RefFinal(vector<Particle> vJet, vector<Particle> vLep, float met, int nleptons, int njets);

   // Transverse sphericity
   //   virtual float    CalcSpher(vector<Particle> vJet, vector<Particle> vLep, int nleptons);
   virtual float    DiffPhi(float dPhi);
   virtual bool     DeltaPhiCut(vector<Particle> vP,float METphi, float ptLast);
  
   virtual float    MT_RefFinal(vector<Particle> vLep, float met, float phimet);
   
   virtual double   XSect(TString fname);

   float deltaR(TLorentzVector tlv1, TLorentzVector tlv2);
     
   virtual void  DumpParticle(Particle p);
   virtual void  RemoveBadParticles(vector<Particle>* vP);
   virtual void  RemoveBadParticles(vector<Particle> vP);

   // Some histos
   TH1F* ANA_Return;
   TH1* ANA_XSECT[10];
   TH1* ANA_XSECT_ELECT[10];
   TH1* ANA_XSECT_MUON[10];
   TH1* ANA_XSECT_MIXED[10];
   TH1* ANA_NB[10];
   TH1F* ANA_MEFF[10];
   TH1* ANA_MET[10];
   TH1* ANA_MET_MEFF[10];
   TH1* ANA_MT[10];
   TH1* ANA_ST[10];
   TH1* ANA_NEL[10];
   TH1* ANA_NLEP[10];
   TH1* ANA_NMU[10];
   
   TH1* ANA_PTJET1[10];
   TH1* ANA_PTJET2[10];
   TH1* ANA_PTJET3[10];
   TH1* ANA_PTJET4[10];
   
   TH1* ANA_PTLEP1[10];
   TH1* ANA_PTLEP2[10];
   
   TH1* ANA_NENTRIES;
   TH1* ANA_XSECT0;
   TH1* RMATCH_JET[10];
   TH1* RMATCH_EL[10];
   TH1* RMATCH_MU[10];
   
   TH1* ANA_MET_HighMT[10];
   TH1* ANA_MET_LowMT[10];
   
   TH1* ANA_MEFF_HighMT[10];
   TH1* ANA_MEFF_LowMT[10];
   
   TH2* ANA_MEFF_MT[10];
   TH2* ANA_MET_MT[10];
   
   TH1* ANA_MT_Ctrl;
   TH1* ANA_MT_Sig1;
   TH1* ANA_MET_Sig2;
   
   // Summary ntuple
   virtual void FillSummaryNtuple(int i,int EvNb,vector<Particle> vJet,vector<Particle> vLep,vector<Particle> vEle, 
				  vector<Particle> vMmu, double w, float MET,  float pxMiss, float pyMiss, 
				  float METphi,int nleptons);
   virtual void BookSummaryNtuple();
   virtual void WriteSummaryNtuple(const char * outfname);
   TTree *treeSummary;
   Float_t ptMiss;
   Float_t mT;
   Float_t st;
   Float_t meff;
   Float_t mTop_had;
   Float_t mW_had;
   Float_t mTop_lep;
   Float_t HT;
   Float_t oblate;
   Float_t weight;
   Int_t entry;
   Int_t event;
   Int_t nJet;
   Float_t chargeLep;
   Float_t etaJet[20];
   Float_t ptJet[20];

   // Analysis histograms
   virtual void     FillAnalysisHistograms(int i,vector<Particle> vJet,vector<Particle> vLep,vector<Particle> vEle, 
					   vector<Particle> vMmu, double w, float MET, float METphi,int nleptons,
					   int njets);
   virtual void     ScaleXSectHistogram(double xsect, double TotWeight);
   virtual void     FillNEntriesXsect(float nentr, float xsect, int ilast);

   void bookhistos(); 
   void savehistos(const char * outfname); 

   // Material from Xin
   virtual Double_t GetDR(Float_t eta1, Float_t phi1, Float_t eta2, Float_t phi2);
   virtual Double_t GetAveDR(Particle j1, Particle j2);
   virtual Double_t GetAveDR(Particle j1, Particle j2, Particle j3);
   virtual Double_t GetAveDR(Double_t pxMiss, Double_t pyMiss, Double_t pzMiss, Particle ib, Particle Lep);
   virtual Double_t GetPt(Double_t px1, Double_t py1, Double_t px2, Double_t py2);
   virtual Double_t GetPt(Double_t px1, Double_t py1, Double_t px2, Double_t py2, Double_t px3, Double_t py3);
   virtual Double_t GetMass(Double_t e1, Double_t px1, Double_t py1, Double_t pz1, Double_t e2, Double_t px2, Double_t py2, Double_t pz2);
   virtual Double_t GetMass(Double_t e1, Double_t px1, Double_t py1, Double_t pz1, Double_t e2, Double_t px2, Double_t py2, Double_t pz2, Double_t e3, Double_t px3, Double_t py3, Double_t pz3);
   virtual Double_t GetOblateness(vector<Particle> vJet, Int_t I4, Int_t I1, Int_t I2, Int_t I3, vector<Particle> vLep, Particle pMiss);

};
#endif

#ifdef CutClass_cxx
CutClass::CutClass(){
  // Nleptons, Njets, etc?

};

CutClass::~CutClass(){

};



double CutClass::XSect(TString fname){
  
  double xsect=1.;
  
  if( fname=="SU1") xsect=10.86;

  if( fname=="SU1_10TeV") xsect=2.41448;
  if( fname=="SU3_10TeV") xsect=5.4772*1.489;
  if( fname=="SU4_10TeV") xsect=107.597*1.53;
  if( fname=="SU6_10TeV") xsect=1.24619*1.489;

  if( fname=="T1_10TeV")    xsect=202.86*1.07;
  
  if( fname=="T1_xdata05")  xsect=202.86*1.07;
  if( fname=="T1_xdata05_All")  xsect=202.86*1.07;

  if( fname=="WenuNp0_xdata05")  xsect=10184.75*1.22;
  if( fname=="WenuNp1_xdata05")  xsect=2112.45*1.22;
  if( fname=="WenuNp2_xdata05")  xsect=676.07*1.22;
  if( fname=="WenuNp3_xdata05")  xsect=205.26*1.22;
  if( fname=="WenuNp4_xdata05")  xsect=57.45*1.22;
  if( fname=="WenuNp5_xdata05")  xsect=17.86*1.22;

  if( fname=="WmunuNp0_xdata05")  xsect=10125.70*1.22;
  if( fname=="WmunuNp1_xdata05")  xsect=2155.53*1.22;
  if( fname=="WmunuNp2_xdata05")  xsect=682.54*1.22;
  if( fname=="WmunuNp3_xdata05")  xsect=203.85*1.22;
  if( fname=="WmunuNp4_xdata05")  xsect=57.01*1.22;
  if( fname=="WmunuNp5_xdata05")  xsect=17.59*1.22;

  if( fname=="WtaunuNp0_xdata05")  xsect=10178.28*1.22;
  if( fname=="WtaunuNp1_xdata05")  xsect=2106.92*1.22;
  if( fname=="WtaunuNp2_xdata05")  xsect=672.78*1.22;
  if( fname=="WtaunuNp3_xdata05")  xsect=204.58*1.22;
  if( fname=="WtaunuNp4_xdata05")  xsect=56.79*1.22;
  if( fname=="WtaunuNp5_xdata05")  xsect=18.27*1.22;

  if( fname=="ZeeNp0_xdata05")  xsect=898.44*1.22;
  if( fname=="ZeeNp1_xdata05")  xsect=197.80*1.22;
  if( fname=="ZeeNp2_xdata05")  xsect=62.26*1.22;
  if( fname=="ZeeNp3_xdata05")  xsect=18.76*1.22;
  if( fname=="ZeeNp4_xdata05")  xsect=4.97*1.22;
  if( fname=="ZeeNp5_xdata05")  xsect=1.43*1.22;

  if( fname=="ZmumuNp0_xdata05")  xsect=895.27*1.22;
  if( fname=="ZmumuNp1_xdata05")  xsect=198.59*1.22;
  if( fname=="ZmumuNp2_xdata05")  xsect=63.49*1.22;
  if( fname=="ZmumuNp3_xdata05")  xsect=18.70*1.22;
  if( fname=="ZmumuNp4_xdata05")  xsect=4.99*1.22;
  if( fname=="ZmumuNp5_xdata05")  xsect=1.37*1.22;

  if( fname=="ZtautauNp0_xdata05")  xsect=893.00*1.22;
  if( fname=="ZtautauNp1_xdata05")  xsect=197.71*1.22;
  if( fname=="ZtautauNp2_xdata05")  xsect=63.63*1.22;
  if( fname=="ZtautauNp3_xdata05")  xsect=18.86*1.22;
  if( fname=="ZtautauNp4_xdata05")  xsect=4.98*1.22;
  if( fname=="ZtautauNp5_xdata05")  xsect=1.39*1.22;

  if( fname=="WbbNp0_xdata05")  xsect=5.13*1.22;
  if( fname=="WbbNp1_xdata05")  xsect=5.01*1.22;
  if( fname=="WbbNp2_xdata05")  xsect=2.89*1.22;
  if( fname=="WbbNp3_xdata05")  xsect=1.61*1.22;

  if( fname=="WW_xdata05")  xsect=42.04;
  if( fname=="WZ_xdata05")  xsect=16.24;
  if( fname=="ZZ_xdata05")  xsect=6.54;

  if( fname=="ZPhoton_xdata05")  xsect=11.11*0.67;
  if( fname=="WPhoton_xdata05")  xsect=35.59*0.63;

  if( fname=="J0_xdata05")  xsect=11698200000.;
  if( fname=="J1_xdata05")  xsect=863605000.;
  if( fname=="J2_xdata05")  xsect=56013300.;
  if( fname=="J3_xdata05")  xsect=3286720.;
  if( fname=="J4_xdata05")  xsect=151610.;
  if( fname=="J5_xdata05")  xsect=5088.42;
  if( fname=="J6_xdata05")  xsect=111.947;
  if( fname=="J7_xdata05")  xsect=1.07;
  if( fname=="J8_xdata05")  xsect=1.112E-3;

  if( fname=="ttbar_xdata05")  xsect=218.37;
  if( fname=="Wt_xdata05")  xsect=14.27;
  
  if( fname=="SU3_10TeV_topmix") xsect=5.4772*1.489;
  

  return(xsect);
}

void CutClass::bookhistos()
{
  
  char title[100], name[100];

  for(int i=0;i<10;i++) {
    sprintf(&title[0], "ANA_XSECT_%1d",i);
    sprintf(&name[0], "XSECT After cut %d",i);
    ANA_XSECT[i] = new TH1F(title,name,1,0,1);

    sprintf(&title[0], "ANA_XSECT_ELECT_%1d",i);
    sprintf(&name[0], "XSECT_ELECT After cut %d",i);
    ANA_XSECT_ELECT[i] = new TH1F(title,name,1,0,1);
    
    sprintf(&title[0], "ANA_XSECT_MUON_%1d",i);
    sprintf(&name[0], "XSECT_MUON After cut %d",i);
    ANA_XSECT_MUON[i] = new TH1F(title,name,1,0,1);  
  
    sprintf(&title[0], "ANA_XSECT_MIXED_%1d",i);
    sprintf(&name[0], "XSECT_MIXED After cut %d",i);
    ANA_XSECT_MIXED[i] = new TH1F(title,name,1,0,1);

    sprintf(&title[0], "ANA_NB_%1d",i);
    sprintf(&name[0], "NB After cut %d",i);
    ANA_NB[i] = new TH1F(title,name,1,0,1);

    sprintf(&title[0], "ANA_MEFF_%1d",i);
    sprintf(&name[0], "MEFF After cut %d",i);
    ANA_MEFF[i] = new TH1F(title,name,40,0,4000);

    sprintf(&title[0], "ANA_MET_%1d",i);
    sprintf(&name[0], "MET After cut %d",i);
    ANA_MET[i] = new TH1F(title,name,200,0,2000);

    sprintf(&title[0], "ANA_MET_MEFF_%1d",i);
    sprintf(&name[0], "MET/MEFF After cut %d",i);
    ANA_MET_MEFF[i] = new TH1F(title,name,50,0,1);

    sprintf(&title[0], "ANA_MET_HighMT%1d",i);
    sprintf(&name[0], "MET HighMTAfter cut %d",i);
    ANA_MET_HighMT[i] = new TH1F(title,name,200,0,2000);

    sprintf(&title[0], "ANA_MET_LowMT%1d",i);
    sprintf(&name[0], "MET LowMTAfter cut %d",i);
    ANA_MET_LowMT[i] = new TH1F(title,name,200,0,2000);

    sprintf(&title[0], "ANA_MEFF_HighMT%1d",i);
    sprintf(&name[0], "MEFF HighMTAfter cut %d",i);
    ANA_MEFF_HighMT[i] = new TH1F(title,name,400,0,4000);

    sprintf(&title[0], "ANA_MEFF_LowMT%1d",i);
    sprintf(&name[0], "MEFF LowMTAfter cut %d",i);
    ANA_MEFF_LowMT[i] = new TH1F(title,name,400,0,4000);

    sprintf(&title[0], "ANA_MT_%1d",i);
    sprintf(&name[0], "MT After cut %d",i);
    ANA_MT[i] = new TH1F(title,name,400,0,2000);

    sprintf(&title[0], "ANA_ST_%1d",i);
    sprintf(&name[0], "ST After cut %d",i);
    ANA_ST[i] = new TH1F(title,name,400,0,1);


    sprintf(&title[0], "ANA_NMU_%1d",i);
    sprintf(&name[0], "NMU After cut %d",i);
    ANA_NMU[i] = new TH1F(title,name,10,0,10);

    sprintf(&title[0], "ANA_NEL_%1d",i);
    sprintf(&name[0], "NMU After cut %d",i);
    ANA_NEL[i] = new TH1F(title,name,10,0,10);

    sprintf(&title[0], "ANA_NLEP_%1d",i);
    sprintf(&name[0], "NLEP After cut %d",i);
    ANA_NLEP[i] = new TH1F(title,name,10,0,10);

    sprintf(&title[0], "ANA_PTJET1_%1d",i);
    sprintf(&name[0], "PTJET1 After cut %d",i);
    ANA_PTJET1[i] = new TH1F(title,name,200,0,2000);

    sprintf(&title[0], "ANA_PTJET2_%1d",i);
    sprintf(&name[0], "PTJET2 After cut %d",i);
    ANA_PTJET2[i] = new TH1F(title,name,200,0,2000);

    sprintf(&title[0], "ANA_PTJET3_%1d",i);
    sprintf(&name[0], "PTJET3 After cut %d",i);
    ANA_PTJET3[i] = new TH1F(title,name,200,0,2000);

    sprintf(&title[0], "ANA_PTJET4_%1d",i);
    sprintf(&name[0], "PTJET4 After cut %d",i);
    ANA_PTJET4[i] = new TH1F(title,name,200,0,2000);


    sprintf(&title[0], "ANA_PTLEP1_%1d",i);
    sprintf(&name[0], "PTLEP1 After cut %d",i);
    ANA_PTLEP1[i] = new TH1F(title,name,200,0,2000);

    sprintf(&title[0], "ANA_PTLEP2_%1d",i);
    sprintf(&name[0], "PTLEP2 After cut %d",i);
    ANA_PTLEP2[i] = new TH1F(title,name,200,0,2000);


    sprintf(&title[0], "rMatch_%1d",i);
    sprintf(&name[0], "rMatch After cut %d",i);
    RMATCH_JET[i] = new TH1F(title,name,200,0,10);

    sprintf(&title[0], "rMatchEle_%1d",i);
    sprintf(&name[0], "rMatchEle After cut %d",i);
    RMATCH_EL[i] = new TH1F(title,name,200,0,10);

    sprintf(&title[0], "rMatchMuo_%1d",i);
    sprintf(&name[0], "rMatchMuo After cut %d",i);
    RMATCH_MU[i] = new TH1F(title,name,200,0,10);

    sprintf(&title[0], "ANA_MEFF_MT_%1d",i);
    sprintf(&name[0], "ANA_MEFF_MT After cut %d",i);
    ANA_MEFF_MT[i] = new TH2F(title,name,1000,0,4000,1000,0,4000); 
    
    sprintf(&title[0], "ANA_MET_MT_%1d",i);
    sprintf(&name[0], "ANA_MET_MT After cut %d",i);
    ANA_MET_MT[i] = new TH2F(title,name,1000,0,2000,1000,0,4000); 

  }

  ANA_MT_Ctrl  = new TH1F("ANA_MT_Ctrl","ANA_MT_Ctrl",200,0,600);
  ANA_MT_Sig1  = new TH1F("ANA_MT_Sig1","ANA_MT_Sig1",200,0,600);
  ANA_MET_Sig2 = new TH1F("ANA_MET_Sig2","ANA_MET_Sig2",100,0,800);


  ANA_NENTRIES=new TH1F("NumberEntries","NumberEntries",100000,0,10E6);
  ANA_XSECT0= new TH1F("ANA_XSECT0","ANA_XSECT0",1,0,1);

}


void CutClass::savehistos(const char * outfname)
{
  if (!outfname) outfname="myhistos.root";
  TFile f1(outfname,"recreate");
  f1.cd();

  for(int i=0;i<10;i++) {
    ANA_XSECT[i]->Write();
    ANA_XSECT_ELECT[i]->Write();
    ANA_XSECT_MUON[i]->Write();
    ANA_XSECT_MIXED[i]->Write();
    ANA_NB[i]->Write();
    ANA_MEFF[i]->Write();
    ANA_MET[i]->Write();
    ANA_MET_MEFF[i]->Write();
    ANA_MT[i]->Write();
    ANA_ST[i]->Write();
    ANA_NMU[i]->Write();
    ANA_NEL[i]->Write();
    ANA_NLEP[i]->Write();

    ANA_PTJET1[i]->Write();
    ANA_PTJET2[i]->Write();
    ANA_PTJET3[i]->Write();
    ANA_PTJET4[i]->Write();

    ANA_PTLEP1[i]->Write();
    ANA_PTLEP2[i]->Write();

    RMATCH_JET[i]->Write();
    RMATCH_EL[i]->Write();
    RMATCH_MU[i]->Write();

    ANA_MET_HighMT[i]->Write();
    ANA_MET_LowMT[i]->Write();
    ANA_MEFF_HighMT[i]->Write();
    ANA_MEFF_LowMT[i]->Write();


    ANA_MEFF_MT[i]->Write();
    ANA_MET_MT[i]->Write();
  }

  ANA_MT_Ctrl->Write(); 
  ANA_MT_Sig1->Write();  
  ANA_MET_Sig2->Write(); 

  ANA_NENTRIES->Write();
  ANA_XSECT0->Write();


  for(int i=0;i<10;i++) {
    delete ANA_XSECT[i];
    delete ANA_XSECT_ELECT[i];
    delete ANA_XSECT_MUON[i];
    delete ANA_XSECT_MIXED[i];
    delete ANA_NB[i];
    delete ANA_MEFF[i];
    delete ANA_MET[i];
    delete ANA_MET_MEFF[i];
    delete ANA_MT[i];
    delete ANA_ST[i];
    delete ANA_NMU[i];
    delete ANA_NEL[i];
    delete ANA_NLEP[i];

    delete ANA_PTJET1[i];
    delete ANA_PTJET2[i];
    delete ANA_PTJET3[i];
    delete ANA_PTJET4[i];

    delete ANA_PTLEP1[i];
    delete ANA_PTLEP2[i];

    delete RMATCH_JET[i];
    delete RMATCH_EL[i];
    delete RMATCH_MU[i];

    delete ANA_MET_HighMT[i];
    delete ANA_MET_LowMT[i];
    delete ANA_MEFF_HighMT[i];
    delete ANA_MEFF_LowMT[i];


    delete ANA_MEFF_MT[i];
    delete ANA_MET_MT[i];
  }

  delete ANA_MT_Ctrl; 
  delete ANA_MT_Sig1;  
  delete ANA_MET_Sig2; 

  delete ANA_NENTRIES;
  delete ANA_XSECT0;
  
}

class vect2D {
public :
  vect2D(double a1=0, double a2=0, double a3=0, double a4=0) {
    elems[0] = a1;
    elems[1] = a2;
    elems[2] = a3;
    elems[3] = a4;
  }
  double& operator[](unsigned int i) { return elems[i]; }
  const double& operator[](unsigned int i) const { return elems[i]; }
  vect2D& operator=(const vect2D& b) {
    for(unsigned int i=0;i<4;i++) {
      elems[i] = b[i];
    }
    return *this;
  }
  bool operator==(const vect2D& b) const {
    for(unsigned int i=0;i<4;i++) {
      if(elems[i] != b[i]) return false;
    }
    return true;
  }
  bool operator!=(const vect2D& b) const {
    if(b == *this) return false;
    else return true;
  }

protected:
  // 2D vector (phi,px,py,pt)
  double elems[4];
};

class vect2Dsort{
 public:
  bool operator()(const vect2D& o1, const vect2D& o2) {
    return o1[0] < o2[0];
  }
};

vect2D getsum(const std::vector<vect2D>& inlist) {
  double pxsum=0;
  double pysum=0;
  for(std::vector<vect2D>::const_iterator it=inlist.begin(); it != inlist.end() ; it++) {
    pxsum += (*it)[1];
    pysum += (*it)[2];
  }
  double phi  = (pxsum<0&&pysum==0 ? -M_PI : atan2(pysum,pxsum)); // [-pi,pi)
  double psum = sqrt(pxsum*pxsum+pysum*pysum);
  vect2D vectSum;
  vectSum[0] = phi;
  vectSum[1] = pxsum;
  vectSum[2] = pysum;
  vectSum[3] = psum;
  return vectSum;
}

void shift(std::vector<vect2D>& vlist) {
  vect2D v;
  v[0] =  vlist[vlist.size()-1][0]-M_PI;
  v[1] = -vlist[vlist.size()-1][1];
  v[2] = -vlist[vlist.size()-1][2];
  v[3] =  vlist[vlist.size()-1][3];
  vlist.insert(vlist.begin(),v);
  vlist.pop_back();
}

std::vector<vect2D> getthrustaxes(const std::vector<vect2D>& thelist) {
  std::vector<vect2D> vlist = thelist;
  std::vector<vect2D>::iterator iter = vlist.begin();
  while( iter != vlist.end() ) {
    if( (*iter)[3]==0 ) {
      iter = vlist.erase(iter);
    } else {
      iter++;
    }
  }
  if(vlist.size()<2) return vlist;

  for(std::vector<vect2D>::iterator it=vlist.begin(); it != vlist.end() ; it++) {
    if((*it)[0]<0) {
      (*it)[0] += M_PI;
      (*it)[1] = -(*it)[1];
      (*it)[2] = -(*it)[2];
    }
  }
  sort(vlist.begin(),vlist.end(),vect2Dsort());

  std::vector<vect2D> thrustaxes;
  double pmax=0;
  unsigned int i=0;
  while(i < vlist.size()) {
    vect2D sum = getsum(vlist);
    if(vlist[0][0]>(sum[0]-M_PI/2) && vlist[vlist.size()-1][0]<(sum[0]+M_PI/2)) {
      thrustaxes.push_back(sum);
      if(sum[3]>pmax) pmax = sum[3];
    }
    vect2D vlast1 = vlist[vlist.size()-1];
    vect2D vlast2 = vlist[vlist.size()-2];
    while(vlast1[0]==vlast2[0]) {
      shift(vlist);
      vlast1 = vlist[vlist.size()-1];
      vlast2 = vlist[vlist.size()-2];
      i++;
    }
    shift(vlist);
    i++;
  }

  std::vector<vect2D>::iterator it = thrustaxes.begin();
  while( it != thrustaxes.end() ) {
    if(fabs((*it)[3]-pmax)<1e-6) {
      it++;
    } else {
      it = thrustaxes.erase(it);
    }
  }

  return thrustaxes;
}

double getthrust(double thsPhi, double* pt, double* phi, unsigned int n) {
  double psum = 0;
  double ptot = 0;
  for(unsigned int i=0;i<n;i++) {
    psum += fabs(pt[i]*cos(phi[i])*cos(thsPhi)+pt[i]*sin(phi[i])*sin(thsPhi));
    ptot += pt[i];
  }

  double thrust = (ptot>0? psum/ptot : 0);
  return thrust;
}

double oblateness(double* pt, double* phi, unsigned int n) {
  std::vector<vect2D> thelist;
  for(unsigned int i=0;i<n;i++) {
    vect2D v(phi[i],pt[i]*cos(phi[i]),pt[i]*sin(phi[i]),pt[i]);
    thelist.push_back(v);
  }

  std::vector<vect2D> thrustaxes = getthrustaxes(thelist);
  double thsPhi = thrustaxes[0][0];

  double phiB = thsPhi-M_PI/2;
  if(phiB < -M_PI) phiB += 2*M_PI;

  double thsA = getthrust(thsPhi,pt,phi,n);
  double thsB = getthrust(phiB,pt,phi,n);

  return thsA-thsB;
}
#endif // #ifdef CutClass_cxx
