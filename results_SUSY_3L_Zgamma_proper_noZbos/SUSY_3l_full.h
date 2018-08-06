#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

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

//-----------------------------------------------------------------------------
const Int_t N_SETS = 12; // data+ number of background samples

const Int_t N_SIG = 2; // number of signal samples (overlay)

const Int_t N_unc_paired = 38;
const Int_t N_unc_unpaired = 3;

bool CONF_NOTE = false; // Prints "Atlas Preliminary"

const Double_t lumi = 13025800.;

//The cross sections are in nb-1
const Double_t x_sect[N_SETS] = { 0., 22.37e-3, //single top
		11.11e-3, //ttbar
		1.245, 1.245, //Z+jets
		9.91e-3, 9.91e-3, //Z+bbar (from the top group. need NLO predictions)
		4.401e-4, 10.47e-6, //ttbarW+ ttbarZ+ttbarWW,  WWW*+WW*Z+ZZZ*
		5.743e-3, 8.235e-3, 9.726e-3 }; //  WW, ZZ, WZ

//The cross sections are in nb-1
const Double_t x_sect_SIG[N_SIG] = { 0.033e-3, 0.060e-3 };

const string description[N_SETS] = { "Data 2012, #sqrt{s}=8 TeV", "Wt", "t#bar{t}", "Z#rightarrow#mu#mu",
		"Z#rightarrowee", "Zb#bar{b}, Z#rightarrow#mu#mu", "Zb#bar{b}, Z#rightarrowee", "t#bar{t}V, t#bar{t}WW",
		"WWW, WWZ, ZZZ", "WW", "ZZ", "WZ" };

const string description_SIG[N_SIG] = { "#tilde{b}500, #tilde{#chi}^{#pm}_{}300, #tilde{#chi}^{0}_{}150",
		"#tilde{g}900, #tilde{#chi}^{0}_{}500" };

const Int_t zmm_ind = 3;
const Int_t zee_ind = 4;

const Int_t zmmbb_ind = 5;
const Int_t zeebb_ind = 6;

const Int_t wz_ind = 11;
const Int_t zz_ind = 10;
const Int_t ww_ind = 9;

const Int_t ttbarV_ind = 7;
const Int_t VVV_ind = 8;

const Int_t ttbar_ind = 2;
const Int_t st_Wt_ind = 1;

const double em_ee = 1.09; // effieicnecy for muons divided by efficiency for electrons

//Here we specify destination
const int merge_map[N_SETS] = { 0, 0, 0, 0, zmm_ind, zmm_ind, zmm_ind, 0, ttbarV_ind, 0, ww_ind, ww_ind };

const string description_short[N_SETS] = { "Data #sqrt{s}=8 TeV", "Wt", "t#bar{t}", "Z+jets", "", "", "",
		"t#bar{t}V, t#bar{t}WW, VVV", "", "WW, ZZ, WZ", "", "" };

//-----------------------------------------------------------------------------
struct distr_set {

	Float_t int_lumi;

	string file_name[N_SETS];
	string tag[N_SETS];

	string syst_tag;

	Double_t xsect[N_SETS];
	Double_t num_of_evts[N_SETS]; // only for MC

	Int_t color[N_SETS]; //Fill colors of the histograms
	Int_t lineColor[N_SETS]; //Line colors of the histograms

	//Corrections to the fake rates
	Double_t FR_lf_e; // light-flavor jet to electron
	Double_t FR_hf_e; // heavy-flavor jet to electron
	Double_t FR_lf_mu; // light-flavor jet to muon
	Double_t FR_hf_mu; // heavy flavor jet to muon

	//muons
	TH1D* mu1_pt[N_SETS];
	TH1D* mu2_pt[N_SETS];
	TH1D* mu3_pt[N_SETS];

	TH1D* mu1_D0[N_SETS];
	TH1D* mu2_D0[N_SETS];
	TH1D* mu3_D0[N_SETS];

	//TH1D* mu1_ptcone02[N_SETS];
	//TH1D* mu2_ptcone02[N_SETS];
	//TH1D* mu3_ptcone02[N_SETS];

	//TH1D* mu1_ptcone03[N_SETS];
	//TH1D* mu2_ptcone03[N_SETS];
	//TH1D* mu3_ptcone03[N_SETS];

	TH1D* mu1_etcone02[N_SETS];
	TH1D* mu2_etcone02[N_SETS];
	TH1D* mu3_etcone02[N_SETS];

	//TH1D* mu1_etcone03[N_SETS];
	//TH1D* mu2_etcone03[N_SETS];
	//TH1D* mu3_etcone03[N_SETS];

	TH1D* mu1_D0sig[N_SETS];
	TH1D* mu2_D0sig[N_SETS];
	TH1D* mu3_D0sig[N_SETS];

	TH1D* mu_eta[N_SETS];
	TH1D* mu_phi[N_SETS];

	//electrons
	TH1D* el1_pt[N_SETS];
	TH1D* el2_pt[N_SETS];
	TH1D* el3_pt[N_SETS];

	TH1D* el1_D0[N_SETS];
	TH1D* el2_D0[N_SETS];
	TH1D* el3_D0[N_SETS];

	//TH1D* el1_ptcone02[N_SETS];
	//TH1D* el2_ptcone02[N_SETS];
	//TH1D* el3_ptcone02[N_SETS];

	//TH1D* el1_ptcone03[N_SETS];
	//TH1D* el2_ptcone03[N_SETS];
	//TH1D* el3_ptcone03[N_SETS];

	TH1D* el1_etcone02[N_SETS];
	TH1D* el2_etcone02[N_SETS];
	TH1D* el3_etcone02[N_SETS];

	//TH1D* el1_etcone03[N_SETS];
	//TH1D* el2_etcone03[N_SETS];
	//TH1D* el3_etcone03[N_SETS];

	TH1D* el1_isTight[N_SETS];
	TH1D* el2_isTight[N_SETS];
	TH1D* el3_isTight[N_SETS];

	TH1D* el_eta[N_SETS];
	TH1D* el_phi[N_SETS];

	//misc
	TH1D* met[N_SETS];
	TH1D* metL[N_SETS];

	TH1D* MZ[N_SETS];

	//jets
	TH1D* N_jets[N_SETS];
	TH1D* pt_jet1[N_SETS];
	TH1D* pt_jet2[N_SETS];
	TH1D* pt_jet3[N_SETS];
	TH1D* pt_jet4[N_SETS];

	//-------- Stacked Plots --------------------------------
	//muons
	THStack* ST_mu1_pt;
	THStack* ST_mu2_pt;
	THStack* ST_mu3_pt;

	THStack* ST_mu1_D0;
	THStack* ST_mu2_D0;
	THStack* ST_mu3_D0;

	//THStack* ST_mu1_ptcone02;
	//THStack* ST_mu2_ptcone02;
	//THStack* ST_mu3_ptcone02;

	//THStack* ST_mu1_ptcone03;
	//THStack* ST_mu2_ptcone03;
	//THStack* ST_mu3_ptcone03;

	THStack* ST_mu1_etcone02;
	THStack* ST_mu2_etcone02;
	THStack* ST_mu3_etcone02;

	//THStack* ST_mu1_etcone03;
	//THStack* ST_mu2_etcone03;
	//THStack* ST_mu3_etcone03;

	THStack* ST_mu1_D0sig;
	THStack* ST_mu2_D0sig;
	THStack* ST_mu3_D0sig;

	THStack* ST_mu_eta;
	THStack* ST_mu_phi;

	//electrons
	THStack* ST_el1_pt;
	THStack* ST_el2_pt;
	THStack* ST_el3_pt;

	THStack* ST_el1_D0;
	THStack* ST_el2_D0;
	THStack* ST_el3_D0;

	//THStack* ST_el1_ptcone02;
	//THStack* ST_el2_ptcone02;
	//THStack* ST_el3_ptcone02;

	//THStack* ST_el1_ptcone03;
	//THStack* ST_el2_ptcone03;
	//THStack* ST_el3_ptcone03;

	THStack* ST_el1_etcone02;
	THStack* ST_el2_etcone02;
	THStack* ST_el3_etcone02;

	//THStack* ST_el1_etcone03;
	//THStack* ST_el2_etcone03;
	//THStack* ST_el3_etcone03;

	THStack* ST_el1_isTight;
	THStack* ST_el2_isTight;
	THStack* ST_el3_isTight;

	THStack* ST_el_eta;
	THStack* ST_el_phi;

	//misc
	THStack* ST_met;
	THStack* ST_metL;

	THStack* ST_MZ;

	//jets
	THStack* ST_N_jets;
	THStack* ST_pt_jet1;
	THStack* ST_pt_jet2;
	THStack* ST_pt_jet3;
	THStack* ST_pt_jet4;

	Double_t backgr_mean[N_SETS + 1];
	Double_t backgr_stat[N_SETS + 1];
	Double_t backgr_systup[N_SETS + 1];
	Double_t backgr_systdn[N_SETS + 1];

};

typedef struct distr_set distrSet; //1 final state;

//-----------------------------------------------------------------------------
struct distr_region {

	distrSet fs_3e;
	distrSet fs_2eSS;
	distrSet fs_2eOS;
	distrSet fs_1eSS;
	distrSet fs_1eOS;
	distrSet fs_0e;

	//misc
	TH1D* met[N_SETS];
	TH1D* metL[N_SETS];

	//jets
	TH1D* N_jets[N_SETS];

	//misc
	THStack* ST_met;
	THStack* ST_metL;

	//jets
	THStack* ST_N_jets;

	Double_t backgr_mean[N_SETS + 1];
	Double_t backgr_stat[N_SETS + 1];
	Double_t backgr_systup[N_SETS + 1];
	Double_t backgr_systdn[N_SETS + 1];

};

typedef struct distr_region distrRegion;

//-----------------------------------------------------------------------------
struct distr_all {

	distrRegion charge;
	distrRegion full;
	distrRegion zbos;
	distrRegion comb;
	distrRegion top;

	TH1D* backgr_sum;
	TH1D* data_sum;

};

typedef struct distr_all distrAll;

//-----------------------------------------------------------------------------
struct distr_sig {

	Float_t int_lumi;

	string file_name[N_SIG];
	string tag[N_SIG];

	string syst_tag;

	Double_t xsect[N_SIG];
	Double_t num_of_evts[N_SIG]; // only for MC

	Int_t color[N_SIG]; //Fill colors of the histograms
	Int_t lineColor[N_SIG]; //Line colors of the histograms

	//muons
	TH1D* mu1_pt[N_SIG];
	TH1D* mu2_pt[N_SIG];
	TH1D* mu3_pt[N_SIG];

	TH1D* mu1_D0[N_SIG];
	TH1D* mu2_D0[N_SIG];
	TH1D* mu3_D0[N_SIG];

	//TH1D* mu1_ptcone02[N_SIG];
	//TH1D* mu2_ptcone02[N_SIG];
	//TH1D* mu3_ptcone02[N_SIG];

	//TH1D* mu1_ptcone03[N_SIG];
	//TH1D* mu2_ptcone03[N_SIG];
	//TH1D* mu3_ptcone03[N_SIG];

	TH1D* mu1_etcone02[N_SIG];
	TH1D* mu2_etcone02[N_SIG];
	TH1D* mu3_etcone02[N_SIG];

	//TH1D* mu1_etcone03[N_SIG];
	//TH1D* mu2_etcone03[N_SIG];
	//TH1D* mu3_etcone03[N_SIG];

	TH1D* mu1_D0sig[N_SIG];
	TH1D* mu2_D0sig[N_SIG];
	TH1D* mu3_D0sig[N_SIG];

	TH1D* mu_eta[N_SIG];
	TH1D* mu_phi[N_SIG];

	//electrons
	TH1D* el1_pt[N_SIG];
	TH1D* el2_pt[N_SIG];
	TH1D* el3_pt[N_SIG];

	TH1D* el1_D0[N_SIG];
	TH1D* el2_D0[N_SIG];
	TH1D* el3_D0[N_SIG];

	//TH1D* el1_ptcone02[N_SIG];
	//TH1D* el2_ptcone02[N_SIG];
	//TH1D* el3_ptcone02[N_SIG];

	//TH1D* el1_ptcone03[N_SIG];
	//TH1D* el2_ptcone03[N_SIG];
	//TH1D* el3_ptcone03[N_SIG];

	TH1D* el1_etcone02[N_SIG];
	TH1D* el2_etcone02[N_SIG];
	TH1D* el3_etcone02[N_SIG];

	//TH1D* el1_etcone03[N_SIG];
	//TH1D* el2_etcone03[N_SIG];
	//TH1D* el3_etcone03[N_SIG];

	TH1D* el1_isTight[N_SIG];
	TH1D* el2_isTight[N_SIG];
	TH1D* el3_isTight[N_SIG];

	TH1D* el_eta[N_SIG];
	TH1D* el_phi[N_SIG];

	//misc
	TH1D* met[N_SIG];
	TH1D* metL[N_SIG];

	TH1D* MZ[N_SIG];

	//jets
	TH1D* N_jets[N_SIG];
	TH1D* pt_jet1[N_SIG];
	TH1D* pt_jet2[N_SIG];
	TH1D* pt_jet3[N_SIG];
	TH1D* pt_jet4[N_SIG];

};

typedef struct distr_sig distrSig; //1 final state;

//-----------------------------------------------------------------------------
struct distr_sigRegion {

	distrSig fs_3e;
	distrSig fs_2eSS;
	distrSig fs_2eOS;
	distrSig fs_1eSS;
	distrSig fs_1eOS;
	distrSig fs_0e;

// colbined for the six final states
	TH1D* N_jets[N_SIG];
	TH1D* met[N_SIG];
	TH1D* metL[N_SIG];

};

typedef struct distr_sigRegion distrSigRegion;

//-----------------------------------------------------------------------------
void getData(distrAll& set, string tag, const char* syst_tag);
// The "tag" is used to specified a systematic dataset
void getData(distrAll& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind, const char* syst_tag);
void getData_Region(distrRegion& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind,
		const char* syst_tag);
void
getData_FS(distrSet& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind, const char* syst_tag);

//-----------------------------------------------------------------------------
void getData_SigRegion(distrSigRegion& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind,
		const char* syst_tag);

void getData_SIG(distrSig& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind,
		const char* syst_tag);

//-----------------------------------------------------------------------------
void scaleXSect(distrAll& set, Int_t ind, Double_t sf);
void scaleXSect_Region(distrRegion& set, Int_t ind, Double_t sf);
void scaleXSect_FS(distrSet& set, Int_t ind, Double_t sf);

//-----------------------------------------------------------------------------
void scaleLumi(distrAll& set, Double_t sf);
void scaleLumi_Region(distrRegion& set, Double_t sf);
void scaleLumi_FS(distrSet& set, Double_t sf);

//-----------------------------------------------------------------------------
void weightData(distrAll& set);
void weightData_Region(distrRegion& set);
void weightData_FS(distrSet& set);

//-----------------------------------------------------------------------------
void weightData_SigRegion(distrSigRegion& set);
void weightData_SIG(distrSig& set);

//-----------------------------------------------------------------------------
void buildStack(distrSet& set);

void buildAStack(THStack* &st, TH1D* hist[N_SETS], string* syst_tag);

//-----------------------------------------------------------------------------
void drawObservables(distrAll &set, distrSigRegion* sig, distrAll* paired[N_unc_paired],
		distrAll* unpaired[N_unc_unpaired]);
void draw_Region(distrRegion &set, distrSigRegion* sig, distrRegion* paired[N_unc_paired],
		distrRegion* unpaired[N_unc_unpaired]);
void draw_FS(distrSet &set, distrSig* sig, distrSet *paired[N_unc_paired], distrSet *unpaired[N_unc_unpaired]);
void drawAVariable(THStack* &st, TH1D* hist[N_SETS], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired);
void drawAVariable_short(THStack* &st, TH1D* hist[N_SETS], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired);

double calcPoissonCLLower(double obs);
double calcPoissonCLUpper(double obs);
TGraphAsymmErrors* MakePoissonConfidenceLevelErrors(TH1D* hist);

void ATLASLabel(Double_t x, Double_t y, bool Preliminary);
void myText(Double_t x, Double_t y, Color_t color, const char* text);

double GetMyMaximum(TH1D* h, int x_low, int x_high, bool is_log);
double GetMyMaximum(TGraphAsymmErrors* h);

//-----------------------------------------------------------------------------
TH1D* calculateFractError(TH1D *altered, TH1D *control);

//-----------------------------------------------------------------------------
//helper functions
double getHistIntegral(TH1D* h);
double getStackIntegral(THStack* stack);
double getStackError(THStack* stack);
double getHistError(TH1D* h);

//-----------------------------------------------------------------------------
TH1D* errorBars(THStack* central, TObjArray *paired, TObjArray *unpaired);

//-----------------------------------------------------------------------------
void printBackgrounds(THStack* central, TObjArray *paired, TObjArray *unpaired);
void CalcBackgrounds(THStack* central, TObjArray *paired, TObjArray *unpaired, distrSet &set);
void CalcBackgrounds(THStack* central, TObjArray *paired, TObjArray *unpaired, distrRegion &my_set);
void printBackgrounds(distrSet *my_set_0e, distrSet *my_set_1eSS, distrSet *my_set_1eOS, distrSet *my_set_2eSS,
		distrSet *my_set_2eOS, distrSet *my_set_3e);
void printBackgrounds(distrRegion *my_set);

//-----------------------------------------------------------------------------
//void printErrorBars(THStack* central, TObjArray *paired, TObjArray *unpaired, const string* descr);
//-----------------------------------------------------------------------------
//void printErrorBars(THStack* central, TObjArray *paired, TObjArray *unpaired, const string* descr, Int_t QCD_ind);

//-----------------------------------------------------------------------------
//TH1D* errorBars(TH1D* central, TObjArray *paired, TObjArray *unpaired);

//-----------------------------------------------------------------------------
//TH1D* errorBars(TH1D* central, TObjArray *paired, TObjArray *unpaired, bool incl_stat);

//-----------------------------------------------------------------------------
//void printErrorBars(TH1D* central, TObjArray *paired, TObjArray *unpaired, const char* description);
//-----------------------------------------------------------------------------
// Printing out the errors on the background predictions.
//-----------------------------------------------------------------------------
//void printErrorBars(TH1D* central, TObjArray *paired, TObjArray *unpaired, const char* description, Int_t QCD_ind);

//-----------------------------------------------------------------------------
//void printXsect(TH1D* jet_mult, TH1D* err_brs, TH1D* jet_mult_pLUMI, TH1D* jet_mult_mLUMI);

//-----------------------------------------------------------------------------
//void printXsectNoLumi(TH1D* jet_mult, TH1D* err_brs);

//-----------------------------------------------------------------------------
// the function calculated the four corrections to the fake rate coefficients
void getFakeRateCorr(distrAll* set);

//-----------------------------------------------------------------------------
// poisson likelihood
static void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
//-----------------------------------------------------------------------------
// calculated the poisson probability for a pair of distributions
Double_t CalLikelihood(TH1D* MC, TH1D* data);

//-----------------------------------------------------------------------------
// 	set.FR_lf_e = sf1; set.FR_lf_mu = sf2; set.FR_hf_e = sf3; set.FR_hf_mu = sf4;
//
void setFakeRates(distrAll& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4);
void setFakeRates_Region(distrRegion& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4);
void setFakeRates_FS(distrSet& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4);
