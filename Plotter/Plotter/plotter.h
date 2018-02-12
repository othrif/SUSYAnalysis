/*****************************************************************************/
/*                                                                           */
/* File Name        : plotter.h                                              */
/* Author           : Othmane Rifki			                                 */
/* Email            : othmane.rifki@cern.ch			                         */
/*                                                                           */
/* Description      : Header file containing all plotting functions          */
/*                    All    -> All control and signal regions               */
/*                    Region -> For a single region, all the channels        */
/*                    Set    -> For a single channel,all distributions       */
/***** C 2016 ****************************************************************/

// These are standard C++ header files.
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>

// These are ROOT header files.
#include "Rtypes.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH1D.h"
#include "THStack.h"
#include "TRandom.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TObjArray.h"
#include "TMinuit.h"
#include "TGraphAsymmErrors.h"

using namespace std;

// Categories:
// ttV   -> ttW, ttZ
// VV    -> WZ, WW, ZZ
// Higgs -> ttH, Vh
// Rare  -> tt + WW/t/tt, tZ, VVV
// ttbar, single top
// Z + jets
// W + jets

//-----------------------------------------------------------------------------
// constants
//-----------------------------------------------------------------------------

//const Double_t lumi = 3193.68; // 2015 2.1% 
//const Double_t lumi = 579.264; // 2016 v37
//const Double_t lumi = 2613.83; // 2016 DS1
//const Double_t lumi = 2645.42; // 2016 06/23

//const Double_t lumi = 3193.68 + 2645.42; // 2015 + 2016
//const Double_t lumi = 3193.68 + 2613.83; // 5807.51// 2015 + 2016
//const Double_t lumi = 3193.68 + 6302.24;
const Double_t lumi = 36470.16;

const Int_t N_MC = 17;
const Int_t N_DataMC = N_MC+1;
const Int_t N_SIG = 1;
const Int_t N_FITS = 7;
const Int_t N_FAKE = N_FITS ;

//-----------------------------------------------------------------------------
// MC only 
// Input Files 
/*const string processes[N_MC] = {"ttW", "ttZ", "WW", "WZ", "ZZ", 
								"ttWW", "3t", "4t", "VVV", "powhegpythia6TTBar", "singletop", "powhegpythia8Zjets", "Wjets"};

// Processes description
const string description_mc[N_MC] = {"ttW", "ttZ", "WW", "WZ", "ZZ", 
									 "ttWW", "ttt", "tttt", "VVV", "ttbar", "single top", "Z+jets", "W+jets"};

const string description_mc_merged[N_MC] = {"ttW, ttZ", "", 
											"WW, WZ, ZZ", "", "", 
											"tt+WW/t/tt, VVV", "", "", "",
											"ttbar, single top", "",
											"Z+jets", "W+jets"};
*/
//-----------------------------------------------------------------------------
// Data/MC 

// Processes description
const string description_mc[N_DataMC] = {"data", "ttW", "ttZ", "WW", "WZ", "ZZ", 
										 "tth", "Vh",
										 "ttWW", "ttt", "tttt", "tZ", "VVV", "tWZ", 
										 "ttbar", "otherNP", "Z+jets", "W+jets"};

const string description_mc_merged[N_DataMC] = {"data", "ttW, ttZ", "", 
												"WW, WZ, ZZ", "", "",
												"tth, Wh, Zh", "", 
												"tt+WW/t/tt, t+Z/WZ, VVV", "", "", "", "", "",
												"single top, WWos, Wt", "ttbar", 
												"Z+jets", "W+jets"};

const string description_fake[N_FAKE] = {"data", "Prompt", "Charge Flip", "Fake EL HF", "Fake EL LF", "Fake MU HF", "Fake MU LF"};

// #tilde{b} #tilde{#chi}^{#pm}_{1} #tilde{#chi}^{1}_{0} #tilde{g}
/*const string description_SIG[N_SIG] = { "#tilde{g}1200, #tilde{#chi}^{}_{0}1", "#tilde{g}1200, #tilde{#chi}^{}_{0}600", "#tilde{g}1200, #tilde{#chi}^{}_{0}855" };*/


const string description_SIG[N_SIG] = {""};

// Processes indexes
// MC only
/*const Int_t ttV_ind = 0;
const Int_t VV_ind = 2;
//const Int_t Higgs_ind = 5;
const Int_t Rare_ind = 5; //8;
const Int_t Top_ind = 9;//13;

const int map_mc_merged[N_DataMC] = {-1, ttV_ind, -1, VV_ind, VV_ind, -1, Rare_ind, Rare_ind, Rare_ind,
								 -1, Top_ind, -1, -1};
								 
								 int ind=0;*/

// Data/MC 
const Int_t ttV_ind = 1;
const Int_t VV_ind = 3;
const Int_t Higgs_ind = 6;
const Int_t Rare_ind = 8;
const Int_t Top_ind = 14;


const int map_mc_merged[N_DataMC] = {-1, -1, ttV_ind, -1, VV_ind, VV_ind, 
									 -1, Higgs_ind,
									 -1, Rare_ind, Rare_ind, Rare_ind, Rare_ind, Rare_ind,
									 -1, -1, -1, -1};

int ind=1;
const Int_t ttW_ind = ind++;
const Int_t ttZ_ind = ind++;
const Int_t WW_ind = ind++;
const Int_t WZ_ind = ind++;
const Int_t ZZ_ind = ind++;
const Int_t tth_ind = ind++;
const Int_t Vh_ind = ind++;
const Int_t ttWW_ind = ind++;
const Int_t ttt_ind = ind++;
const Int_t tttt_ind = ind++;
const Int_t tZ_ind = ind++;
const Int_t VVV_ind = ind++;
const Int_t tWZ_ind = ind++;
const Int_t otherNP_ind = ind++;
const Int_t ttbar_ind = ind++;
const Int_t Zjets_ind = ind++;
const Int_t Wjets_ind = ind++;

int in_fit=2;
const Int_t charge_flip_ind_fit = in_fit++;
const Int_t fakes_el_hf_ind_fit = in_fit++;
const Int_t fakes_el_lf_ind_fit = in_fit++;
const Int_t fakes_mu_hf_ind_fit = in_fit++;
const Int_t fakes_mu_lf_ind_fit = in_fit++;


// N Systematics
const Int_t N_unc_paired = 12;
const Int_t N_unc_unpaired = 1;

//-----------------------------------------------------------------------------
// Structures
//-----------------------------------------------------------------------------

struct distr_set {  

  Float_t int_lumi;
  Double_t xsect[N_DataMC] = {1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.}; 

  string file_name[N_DataMC];
  string tag[N_DataMC];
  string syst_tag;
  
  Int_t color[N_DataMC]; //Fill colors of the histograms
  Int_t lineColor[N_DataMC]; //Line colors of the histograms

  //Corrections to the fake rates
  Double_t FR_lf_e; // light-flavor jet to electron
  Double_t FR_hf_e; // heavy-flavor jet to electron
  Double_t FR_lf_mu; // light-flavor jet to muon
  Double_t FR_hf_mu; // heavy flavor jet to muon
  Double_t charge_flip; // charge flip

  TH1D* NJETS[N_DataMC];
  TH1D* pt_jet1[N_DataMC];
  TH1D* pt_jet2[N_DataMC];
  TH1D* pt_jet3[N_DataMC];
  TH1D* pt_jet4[N_DataMC];
  TH1D* pt_jet5[N_DataMC];
  TH1D* NBJETS[N_DataMC];
  TH1D* pt_bjet1[N_DataMC];
  TH1D* pt_bjet2[N_DataMC];
  TH1D* pt_bjet3[N_DataMC];
  TH1D* pt_bjet4[N_DataMC];
  TH1D* mu1_pt[N_DataMC];
  TH1D* mu2_pt[N_DataMC];
  TH1D* mu3_pt[N_DataMC];
  TH1D* mu_eta[N_DataMC];
  TH1D* el1_pt[N_DataMC];
  TH1D* el2_pt[N_DataMC];
  TH1D* el3_pt[N_DataMC];
  TH1D* el_eta[N_DataMC];
  TH1D* MET[N_DataMC];
  TH1D* HT[N_DataMC];
  TH1D* Meff[N_DataMC];
  TH1D* mT[N_DataMC];
  TH1D* mT_min[N_DataMC];
  TH1D* MZ[N_DataMC];
  TH1D* Mlll[N_DataMC];
  TH1D* Mll[N_DataMC];
  TH1D* Mee[N_DataMC];
  TH1D* Mmumu[N_DataMC];
  TH1D* LEPPt[N_DataMC];
  TH1D* LEP1Pt[N_DataMC];
  TH1D* LEP2Pt[N_DataMC];
  TH1D* LEP3Pt[N_DataMC];
  TH1D* LEPChargeSum[N_DataMC];
  TH1D* lep_softest_pt[N_DataMC];

  //-------- Stacked Plots --------------------------------

  THStack* ST_NJETS;
  THStack* ST_pt_jet1;
  THStack* ST_pt_jet2;
  THStack* ST_pt_jet3;
  THStack* ST_pt_jet4;
  THStack* ST_pt_jet5;
  THStack* ST_NBJETS;
  THStack* ST_pt_bjet1;
  THStack* ST_pt_bjet2;
  THStack* ST_pt_bjet3;
  THStack* ST_pt_bjet4;
  THStack* ST_mu1_pt;
  THStack* ST_mu2_pt;
  THStack* ST_mu3_pt;
  THStack* ST_mu_eta;
  THStack* ST_el1_pt;
  THStack* ST_el2_pt;
  THStack* ST_el3_pt;
  THStack* ST_el_eta;
  THStack* ST_MET;
  THStack* ST_HT;
  THStack* ST_Meff;
  THStack* ST_mT;
  THStack* ST_mT_min;
  THStack* ST_MZ;
  THStack* ST_Mlll;
  THStack* ST_Mll;
  THStack* ST_Mee;
  THStack* ST_Mmumu;
  THStack* ST_LEPPt;
  THStack* ST_LEP1Pt;
  THStack* ST_LEP2Pt;
  THStack* ST_LEP3Pt;
  THStack* ST_LEPChargeSum;
  THStack* ST_lep_softest_pt;

  Double_t fakes_mean;
  Double_t fakes_stat;
  Double_t fakes_systup;
  Double_t fakes_systdn;

  Double_t backgr_mean[N_DataMC + 1];
  Double_t backgr_stat[N_DataMC + 1];
  Double_t backgr_systup[N_DataMC + 1];
  Double_t backgr_systdn[N_DataMC + 1];

};

typedef struct distr_set distrSet; // for each final state

//-----------------------------------------------------------------------------

struct distr_region {

  // SS/3L Incl channels
  distrSet fs_elel; // ee 
  distrSet fs_elmu; // em 
  distrSet fs_mumu; // mm 
  distrSet fs_3l; // mm 
  distrSet fs_comb; // combined

  // 3L Excl channels
  /*  distrSet fs_3e;
  distrSet fs_2eSS;
  distrSet fs_2eOS;
  distrSet fs_1eSS;
  distrSet fs_1eOS;
  distrSet fs_0e;
  distrSet fs_3L;*/

  Double_t backgr_mean[N_DataMC + 1];
  Double_t backgr_stat[N_DataMC + 1];
  Double_t backgr_systup[N_DataMC + 1];
  Double_t backgr_systdn[N_DataMC + 1];
};

typedef struct distr_region distrRegion;

//-----------------------------------------------------------------------------

struct distr_signature {
  
  // control regions
  distrRegion Incl; 
  distrRegion PRE; 
  distrRegion CR0b;  
  distrRegion CR1b; 
  distrRegion CR2b;  
  distrRegion CR3b; 
  
  // signal region
  distrRegion SR3L1;
  distrRegion SR3L2;
  distrRegion SR0b1;
  distrRegion SR0b2;
  distrRegion SR1b;
  distrRegion SR3b;
  distrRegion SR1b_DD;
  distrRegion SR3b_DD;
  distrRegion SR1b_GG;
  
  // Validation regions
  distrRegion VRWW;
  distrRegion VRWZ4j;
  distrRegion VRWZ5j;
  distrRegion VRttW;
  distrRegion VRttZ;

  /* distrRegion SR0b5j;
  distrRegion SR2b1;
  distrRegion SR2b2;
  distrRegion SR3L3b;*/ 
  
  TH1D* backgr_sum;
  TH1D* data_sum;

  TH1D* OPT1[N_FITS];
  TH1D* OPT2[N_FITS];
  TH1D* OPT3[N_FITS];
  TH1D* OPT4[N_FITS];
  TH1D* OPT5[N_FITS];
  TH1D* OPT6[N_FITS];
  Double_t FR_lf_e;
  Double_t FR_hf_e;
  Double_t FR_lf_mu;
  Double_t FR_hf_mu;
  Double_t CF;

};

typedef struct distr_signature distrSignature;
//-----------------------------------------------------------------------------

struct distr_all {

  // final state signatures
  distrSignature OS; 
  distrSignature SS3L; 
  distrSignature SS; 
  //  distrSignature L3; 

};

typedef struct distr_all distrAll;

//-----------------------------------------------------------------------------

struct distr_sig_set {  

  Float_t int_lumi;
  Double_t xsect[N_SIG] = {1.};//{1.,1.,1.}; 

  string file_name[N_SIG];
  string tag[N_SIG];
  string syst_tag;
  
  Int_t color[N_SIG]; //Fill colors of the histograms
  Int_t lineColor[N_SIG]; //Line colors of the histograms

  //Corrections to the fake rates
  Double_t FR_lf_e; // light-flavor jet to electron
  Double_t FR_hf_e; // heavy-flavor jet to electron
  Double_t FR_lf_mu; // light-flavor jet to muon
  Double_t FR_hf_mu; // heavy flavor jet to muon
  Double_t charge_flip; // charge flip

  TH1D* NJETS[N_SIG];
  TH1D* pt_jet1[N_SIG];
  TH1D* pt_jet2[N_SIG];
  TH1D* pt_jet3[N_SIG];
  TH1D* pt_jet4[N_SIG];
  TH1D* pt_jet5[N_SIG];
  TH1D* NBJETS[N_SIG];
  TH1D* pt_bjet1[N_SIG];
  TH1D* pt_bjet2[N_SIG];
  TH1D* pt_bjet3[N_SIG];
  TH1D* pt_bjet4[N_SIG];
  TH1D* mu1_pt[N_SIG];
  TH1D* mu2_pt[N_SIG];
  TH1D* mu3_pt[N_SIG];
  TH1D* mu_eta[N_SIG];
  TH1D* el1_pt[N_SIG];
  TH1D* el2_pt[N_SIG];
  TH1D* el3_pt[N_SIG];
  TH1D* el_eta[N_SIG];
  TH1D* MET[N_SIG];
  TH1D* HT[N_SIG];
  TH1D* Meff[N_SIG];
  TH1D* mT[N_SIG];
  TH1D* mT_min[N_SIG];
  TH1D* MZ[N_SIG];
  TH1D* Mlll[N_SIG];
  TH1D* Mll[N_SIG];
  TH1D* Mee[N_SIG];
  TH1D* Mmumu[N_SIG];
  TH1D* LEPPt[N_SIG];
  TH1D* LEP1Pt[N_SIG];
  TH1D* LEP2Pt[N_SIG];
  TH1D* LEP3Pt[N_SIG];
  TH1D* LEPChargeSum[N_SIG];
  TH1D* lep_softest_pt[N_SIG];

};

typedef struct distr_sig_set distrSigSet; // for each final state

//-----------------------------------------------------------------------------

struct distr_sig_region {

  // SS/3L Incl channels
  distrSigSet fs_elel; // ee 
  distrSigSet fs_elmu; // em 
  distrSigSet fs_mumu; // mm 
  //  distrSigSet fs_3l; // mm 
  distrSigSet fs_comb; // combined

  /*  // 3L Excl channels
  distrSigSet fs_3e;
  distrSigSet fs_2eSS;
  distrSigSet fs_2eOS;
  distrSigSet fs_1eSS;
  distrSigSet fs_1eOS;
  distrSigSet fs_0e;
  distrSigSet fs_3L;*/

};

typedef struct distr_sig_region distrSigRegion;

//-----------------------------------------------------------------------------

struct distr_sig_signature {

  // control regions
  distrSigRegion Incl; 
  distrSigRegion PRE; 
  distrSigRegion CR0b;  
  distrSigRegion CR1b; 
  distrSigRegion CR2b;  
  distrSigRegion CR3b; 

  // signal region
  distrSigRegion SR3L1;
  distrSigRegion SR3L2;
  distrSigRegion SR0b1;
  distrSigRegion SR0b2;
  distrSigRegion SR1b;
  distrSigRegion SR3b;
  distrSigRegion SR1b_DD;
  distrSigRegion SR3b_DD;
  distrSigRegion SR1b_GG;
  
  // Validation regions
  distrSigRegion VRWW;
  distrSigRegion VRWZ4j;
  distrSigRegion VRWZ5j;
  distrSigRegion VRttW;
  distrSigRegion VRttZ;

  /*  distrSigRegion SR0b5j;
  distrSigRegion SR2b1;
  distrSigRegion SR2b2;
  distrSigRegion SR3L3b;*/

  
  TH1D* backgr_sum;
  TH1D* data_sum;

};

typedef struct distr_sig_signature distrSigSignature;
//-----------------------------------------------------------------------------

struct distr_sig_all {

  // final state signatures
  distrSigSignature OS; 
  distrSigSignature SS3L; 
  distrSigSignature SS; 
  //  distrSigSignature L3; 

};

typedef struct distr_sig_all distrSigAll;

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Methods
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// read all input histograms for data and background                                                                              
void getData_All(distrAll& set, string tag, const char* syst_tag);
void getData_All(distrAll& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag);
void getData_Signature(distrSignature& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag);
void getData_Region(distrRegion& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag);
void getData_Set(distrSet& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag);
//-----------------------------------------------------------------------------                                                   
// read all input histograms for signal
void getData_SigAll(distrSigAll& set, string tag, const char* syst_tag);
void getData_SigAll(distrSigAll& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag);
void getData_SigSignature(distrSigSignature& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag);
void getData_SigRegion(distrSigRegion& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag);
void getData_SigSet(distrSigSet& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag);
//-----------------------------------------------------------------------------                                   
// scale luminosity
void scaleLumi_All(distrAll& set, Double_t sf);
void scaleLumi_Signature(distrSignature& set, Double_t sf);
void scaleLumi_Region(distrRegion& set, Double_t sf);
void scaleLumi_Set(distrSet& set, Double_t sf);
//-----------------------------------------------------------------------------                                   
// scale cross sections
void scaleXSect_All(distrAll& set, Int_t ind, Double_t sf);
void scaleXSect_Signature(distrSignature& set, Int_t ind, Double_t sf);
void scaleXSect_Region(distrRegion& set, Int_t ind, Double_t sf);
void scaleXSect_Set(distrSet& set, Int_t ind, Double_t sf);
//-----------------------------------------------------------------------------                                   
void scaleXSect_SigAll(distrSigAll& set, Int_t ind, Double_t sf);
void scaleXSect_SigSignature(distrSigSignature& set, Int_t ind, Double_t sf);
void scaleXSect_SigRegion(distrSigRegion& set, Int_t ind, Double_t sf);
void scaleXSect_SigSet(distrSigSet& set, Int_t ind, Double_t sf);
//-----------------------------------------------------------------------------                                   
// weight events based on luminosity and any factors such as fakes rates 
void weightData_All(distrAll& set);
void weightData_Signature(distrSignature& set);
void weightData_Region(distrRegion& set);
void weightData_Set(distrSet& set);
//-----------------------------------------------------------------------------                                            
void weightData_SigAll(distrSigAll& set);
void weightData_SigSignature(distrSigSignature& set);
void weightData_SigRegion(distrSigRegion& set);
void weightData_SigSet(distrSigSet& set);
//----------------------------------------------------------------------------- 
// scale luminosity to get the luminosity systematic
void scaleLumi_All(distrAll& set, Double_t sf);
void scaleLumi_Signature(distrSignature& set, Double_t sf);
void scaleLumi_Region(distrRegion& set, Double_t sf);
void scaleLumi_Set(distrSet& set, Double_t sf);
//-----------------------------------------------------------------------------                              
// build the stack out of background samples
void buildStack(distrSet& set);
void buildAStack(THStack* &st, TH1D* hist[N_DataMC], string* syst_tag);
//-----------------------------------------------------------------------------    
void draw_All(distrAll &set, distrAll &sig, distrAll* paired[N_unc_paired], distrAll* unpaired[N_unc_unpaired], const char* fit);
void draw_Signature(distrSignature &set, distrSigSignature &sig,distrSignature* paired[N_unc_paired], distrSignature* unpaired[N_unc_unpaired], const char* fit);             
void draw_Region(distrRegion &set, distrSigRegion &sig,distrRegion* paired[N_unc_paired], distrRegion* unpaired[N_unc_unpaired], const char* fit);             
void draw_Set(distrSet &set, distrSigSet &sig,  distrSet* paired[N_unc_paired], distrSet* unpaired[N_unc_unpaired], const char* fit);
//-----------------------------------------------------------------------------      
// where the magic happens, _long has all the samples N_DataMC, other has compressed samples as presented in the paper
void drawAVariable_test(THStack* &st, TH1D* hist[N_DataMC], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit);
void drawAVariable_normalized(THStack* &st, TH1D* hist[N_DataMC], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit);
void drawAVariable_all(THStack* &st, TH1D* hist[N_DataMC], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit);
void drawAVariable_merged(THStack* &st, TH1D* hist[N_DataMC], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit);
//-----------------------------------------------------------------------------      
// Error bars
double calcPoissonCLLower(double obs);
double calcPoissonCLUpper(double obs);
TGraphAsymmErrors* MakePoissonConfidenceLevelErrors(TH1D* hist);
TH1D* calculateFractError(TH1D *altered, TH1D *control);
TH1D* errorBars(THStack* central, TObjArray *paired, TObjArray *unpaired);
TH1D* errorBarsSys(TH1D* h, TObjArray *paired, TObjArray *unpaired);
//-----------------------------------------------------------------------------    
// helper functions
void ATLASLabel(Double_t x, Double_t y, bool Preliminary);
void myText(Double_t x, Double_t y, Color_t color, const char* text);
double GetMyMaximum(TH1D* h, int x_low, int x_high, bool is_log);
double GetMyMaximum(TGraphAsymmErrors* h);
double getStackIntegral(THStack* stack);
double getStackError(THStack* stack);
double getHistIntegral(TH1D* h);
double getHistError(TH1D* h);
bool hasLessEvents(TH1*h1,TH1*h2);
bool hasLessEventspair(std::pair<string,TH1D*> h1,std::pair<string,TH1D*> h2);
//-----------------------------------------------------------------------------             
// print backgrounds

//-----------------------------------------------------------------------------             
// mc fitter
//-----------------------------------------------------------------------------             
// the function calculated the five corrections to the fake rate coefficients
void getFakeRateCorr();
//-----------------------------------------------------------------------------
// calculated the poisson probability for a pair of distributions
Double_t CalLikelihood(TH1D* MC, TH1D* data);
//-----------------------------------------------------------------------------
// 	set.FR_lf_e = sf1; set.FR_lf_mu = sf2; set.FR_hf_e = sf3; set.FR_hf_mu = sf4;
void setFakeRates_All(distrAll& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4, Double_t cf);
void setFakeRates_Signature(distrSignature& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4, Double_t cf);
void setFakeRates_Region(distrRegion& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4, Double_t cf);
void setFakeRates_Set(distrSet& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4, Double_t cf);
void fcn_dist(distrSignature *set, TH1D* hist1[N_FITS], TH1D* hist2[N_FITS], TH1D* hist3[N_FITS], TH1D* hist4[N_FITS], TH1D* hist5[N_FITS], TH1D* hist6[N_FITS]);
//-----------------------------------------------------------------------------
double calcPoissonCLLower(Double_t q, Double_t obs);
double calcPoissonCLUpper(Double_t q, Double_t obs);
//-----------------------------------------------------------------------------
//void CalcBackgrounds(THStack* central, TObjArray *paired, TObjArray *unpaired, distrSet &my_set);
void CalcBackgrounds(TH1D* hist[N_FITS], TObjArray *paired, TObjArray *unpaired, distrSet &my_set);
void printBackgrounds(distrSet *my_set_elel, distrSet *my_set_elmu, distrSet *my_set_mumu);
//-----------------------------------------------------------------------------                                                                              
double getStackIntegral(THStack* stack);
double getStackError(THStack* stack);
double getHistIntegral(TH1D* h);
double getHistError(TH1D* h);
