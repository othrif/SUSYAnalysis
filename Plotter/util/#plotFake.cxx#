// To DO:
// add flags: luminosity, SS or OS, ratio, signal, signal grid
// revisit ratio and uncertainty
/*****************************************************************************/
/*                                                                           */
/* File Name        : plotMC.cxx                                             */
/* Description      : Plot pure MC                                           */
/* Author           : Othmane Rifki			                                 */
/* Email            : othmane.rifki@cern.ch			                         */
/*                                                                           */
/* Description      :                                                        */
/*                                                                           */
/***** C 2016 ****************************************************************/

// These are standard C++ header files.
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>

// These are ROOT header files.
#include "TMath.h"
#include "Rtypes.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TFile.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH1F.h"
#include "TH1D.h"
#include "THStack.h"
#include "TRandom.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLine.h"
#include "TObjArray.h"
#include "TMinuit.h"
#include "RooStats/NumberCountingUtils.h"

//here are the project-specific files
#include "Plotter/plotter.h"
#include "Utils/AtlasUtils.h"
#include "Utils/AtlasStyle.h"

using namespace std;

//-----------------------------------------------------------------------------
// TO DO: integrate in code
//string FS = "SS3L";
//string FS = "OS";
char* path;
char* folder;
string fit_type="REPLACETHIS";
bool test_me = false;
bool draw_sig = false;
bool draw_ratio = true;
bool show_yield = true;
bool reduced = false;

double my_FR_lf_e = 1.;
double my_FR_lf_mu = 1.;
double my_FR_hf_e = 1.;
double my_FR_hf_mu = 1.;
double my_charge_flip = 1.;
double my_FR_lf_e_err = 0.;
double my_FR_lf_mu_err = 0.;
double my_FR_hf_e_err = 0.;
double my_FR_hf_mu_err = 0.;
double my_charge_flip_err = 0.;

//-----------------------------------------------------------------------------

void getData_All(distrAll& set, string tag, const char* syst_tag) {
  
  getData_All(set, "" + tag, "", -1, syst_tag);

  return;
}

//-----------------------------------------------------------------------------

void getData_All(distrAll& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {

  std::cout << "SS3L ..." << std::endl;  
  getData_Signature(set.SS3L, "SS3L" + tag, "", -1, syst_tag);
  //  std::cout << "OS ..." << std::endl;  
  //  getData_Signature(set.OS, "OS" + tag, "", -1, syst_tag);
  //  std::cout << "SS ..." << std::endl;  
  //  getData_Signature(set.SS, "SS" + tag, "", -1, syst_tag);
  /*		std::cout << "3L ..." << std::endl;  
			getData_Signature(set.L3, "3L" + tag, "", -1, syst_tag);*/

  return;
}

//-----------------------------------------------------------------------------

void getData_Signature(distrSignature& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {

  /*  getData_Region(set.Incl, "Incl_" + tag, "", -1, syst_tag);
  getData_Region(set.PRE, "PRE_" + tag, "", -1, syst_tag);
  getData_Region(set.CR0b, "CR0b_" + tag, "", -1, syst_tag);
  getData_Region(set.CR1b, "CR1b_" + tag, "", -1, syst_tag);*/
  getData_Region(set.SR3L1, "SR3L1_" + tag, "", -1, syst_tag);
  getData_Region(set.SR3L2, "SR3L2_" + tag, "", -1, syst_tag);
  getData_Region(set.SR0b1, "SR0b1_" + tag, "", -1, syst_tag);
  getData_Region(set.SR0b2, "SR0b2_" + tag, "", -1, syst_tag);
  getData_Region(set.SR1b, "SR1b_" + tag, "", -1, syst_tag);
  getData_Region(set.SR3b, "SR3b_" + tag, "", -1, syst_tag);
  getData_Region(set.SR1b_DD, "SR1b_DD_" + tag, "", -1, syst_tag);
  getData_Region(set.SR3b_DD, "SR3b_DD_" + tag, "", -1, syst_tag);
  getData_Region(set.SR1b_GG, "SR1b_GG_" + tag, "", -1, syst_tag);
  getData_Region(set.VRWW, "VRWW_" + tag, "", -1, syst_tag);
  getData_Region(set.VRWZ4j, "VRWZ4j_" + tag, "", -1, syst_tag);
  getData_Region(set.VRWZ5j, "VRWZ5j_" + tag, "", -1, syst_tag);
  getData_Region(set.VRttW, "VRttW_" + tag, "", -1, syst_tag);
  getData_Region(set.VRttZ, "VRttZ_" + tag, "", -1, syst_tag);

  // getData_Region(set.SR0b5j, "SR0b5j_" + tag, "", -1, syst_tag);
  // getData_Region(set.SR2b1, "SR2b1_" + tag, "", -1, syst_tag);
  // getData_Region(set.SR2b2, "SR2b2_" + tag, "", -1, syst_tag);
  // getData_Region(set.SR3L3b, "SR3L3b_" + tag, "", -1, syst_tag);

  return;
}

//-----------------------------------------------------------------------------

void getData_Region(distrRegion& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {

  getData_Set(set.fs_elel, "ee_" + tag, "", -1, syst_tag);
  getData_Set(set.fs_elmu, "em_" + tag, "", -1, syst_tag);
  getData_Set(set.fs_mumu, "mm_" + tag, "", -1, syst_tag);
  //  getData_Set(set.fs_3l, "3l_" + tag, "", -1, syst_tag);
  getData_Set(set.fs_comb, "comb_" + tag, "", -1, syst_tag);

  return;
}

//-----------------------------------------------------------------------------

void getData_Set(distrSet& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag){

  set.int_lumi = lumi;
  set.syst_tag = syst_tag;
  char temp_file[512];
  char temp_tag[256];
  TFile *f_data;

  //     Default                                                                                                                                        
  set.FR_lf_e = 1.;
  set.FR_hf_e = 1.;
  set.FR_lf_mu = 1.;
  set.FR_hf_mu = 1.;
  set.charge_flip = 1.;

  //  std::sprintf(temp_file, "%s/%s/merged.%s.root", path, folder, folder);
  std::sprintf(temp_file, "%s/merged.%s.root", path, folder);
  f_data = new TFile(temp_file, "READ");

  for (int i = 0; i < N_DataMC; i++){
	set.color[i] = 0;
	set.lineColor[i] = 1;
  }

  // 	Specify the colors
  set.color[1] = kTeal;
  set.color[2] = kOrange-2;
  set.color[3] = kRed+2;
  set.color[4] = kRed-10;
  set.color[5] = kOrange + 5; 
  set.color[6] = kOrange - 6; 
  set.color[7] = kTeal + 4;
  set.color[8] = kAzure +7;
  set.color[9] = kViolet;
  set.color[10] = kGray;
  set.color[11] = TColor::GetColor("#00cc00"); 
  set.color[12] = kRed - 9; 
  set.color[13] = TColor::GetColor("#ff0000"); 
  set.color[14] = TColor::GetColor("#ffff99"); 
  set.color[15] = TColor::GetColor("#99ccff"); 
  set.color[16] = 38; 

  const string files[N_FAKE] = {"data", "real", "chmisid", "fake_HF_e", "fake_LF_e", "fake_HF_m", "fake_LF_m"};

  
  for (int i = 0; i < N_FAKE; i++) {
	// NJETS
	std::sprintf(temp_tag, "NJETS_%s_%s", files[i].c_str(),tag.data());
	//   	std::cout << temp_tag << std::endl;
	set.NJETS[i] =(TH1D*) f_data->Get(temp_tag);
	std::sprintf(temp_tag, "NJETS_%s", tag.data());
	//	std::printf("NJETS_%s\n", tag.data());
	set.NJETS[i]->SetName(temp_tag);
	set.NJETS[i]->SetDirectory(gROOT);
	set.NJETS[i]->SetLineColor(set.lineColor[i]);
	set.NJETS[i]->SetFillColor(set.color[i]);
	set.NJETS[i]->SetLineWidth(1);
	if(!test_me){
	  // pt_jet1
	  std::sprintf(temp_tag, "pt_jet1_%s_%s", files[i].c_str(),tag.data());
	  set.pt_jet1[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_jet1_%s", tag.data());
	  set.pt_jet1[i]->SetName(temp_tag);
	  set.pt_jet1[i]->SetDirectory(gROOT);
	  set.pt_jet1[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet1[i]->SetFillColor(set.color[i]);
	  set.pt_jet1[i]->SetLineWidth(1);

	  // pt_jet2
	  std::sprintf(temp_tag, "pt_jet2_%s_%s", files[i].c_str(),tag.data());
	  set.pt_jet2[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_jet2_%s", tag.data());
	  set.pt_jet2[i]->SetName(temp_tag);
	  set.pt_jet2[i]->SetDirectory(gROOT);
	  set.pt_jet2[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet2[i]->SetFillColor(set.color[i]);
	  set.pt_jet2[i]->SetLineWidth(1);

	  // pt_jet3
	  std::sprintf(temp_tag, "pt_jet3_%s_%s", files[i].c_str(),tag.data());
	  set.pt_jet3[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_jet3_%s", tag.data());
	  set.pt_jet3[i]->SetName(temp_tag);
	  set.pt_jet3[i]->SetDirectory(gROOT);
	  set.pt_jet3[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet3[i]->SetFillColor(set.color[i]);
	  set.pt_jet3[i]->SetLineWidth(1);

	  if(reduced){
		// pt_jet4
		std::sprintf(temp_tag, "pt_jet4_%s_%s", files[i].c_str(),tag.data());
		set.pt_jet4[i] =(TH1D*) f_data->Get(temp_tag);
		std::sprintf(temp_tag, "pt_jet4_%s", tag.data());
		set.pt_jet4[i]->SetName(temp_tag);
		set.pt_jet4[i]->SetDirectory(gROOT);
		set.pt_jet4[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet4[i]->SetFillColor(set.color[i]);
		set.pt_jet4[i]->SetLineWidth(1);

		// pt_jet5
		std::sprintf(temp_tag, "pt_jet5_%s_%s", files[i].c_str(),tag.data());
		set.pt_jet5[i] =(TH1D*) f_data->Get(temp_tag);
		std::sprintf(temp_tag, "pt_jet5_%s", tag.data());
		set.pt_jet5[i]->SetName(temp_tag);
		set.pt_jet5[i]->SetDirectory(gROOT);
		set.pt_jet5[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet5[i]->SetFillColor(set.color[i]);
		set.pt_jet5[i]->SetLineWidth(1);
	  }
	  // NBJETS
	  std::sprintf(temp_tag, "NBJETS_%s_%s", files[i].c_str(),tag.data());
	  set.NBJETS[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "NBJETS_%s", tag.data());
	  set.NBJETS[i]->SetName(temp_tag);
	  set.NBJETS[i]->SetDirectory(gROOT);
	  set.NBJETS[i]->SetLineColor(set.lineColor[i]);
	  set.NBJETS[i]->SetFillColor(set.color[i]);
	  set.NBJETS[i]->SetLineWidth(1);

	  // pt_bjet1
	  std::sprintf(temp_tag, "pt_bjet1_%s_%s", files[i].c_str(),tag.data());
	  set.pt_bjet1[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_bjet1_%s", tag.data());
	  set.pt_bjet1[i]->SetName(temp_tag);
	  set.pt_bjet1[i]->SetDirectory(gROOT);
	  set.pt_bjet1[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet1[i]->SetFillColor(set.color[i]);
	  set.pt_bjet1[i]->SetLineWidth(1);

	  // pt_bjet2
	  std::sprintf(temp_tag, "pt_bjet2_%s_%s", files[i].c_str(),tag.data());
	  set.pt_bjet2[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_bjet2_%s", tag.data());
	  set.pt_bjet2[i]->SetName(temp_tag);
	  set.pt_bjet2[i]->SetDirectory(gROOT);
	  set.pt_bjet2[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet2[i]->SetFillColor(set.color[i]);
	  set.pt_bjet2[i]->SetLineWidth(1);

	  // pt_bjet3
	  std::sprintf(temp_tag, "pt_bjet3_%s_%s", files[i].c_str(),tag.data());
	  set.pt_bjet3[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_bjet3_%s", tag.data());
	  set.pt_bjet3[i]->SetName(temp_tag);
	  set.pt_bjet3[i]->SetDirectory(gROOT);
	  set.pt_bjet3[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet3[i]->SetFillColor(set.color[i]);
	  set.pt_bjet3[i]->SetLineWidth(1);
	  if(reduced){
		// pt_bjet4
		std::sprintf(temp_tag, "pt_bjet4_%s_%s", files[i].c_str(),tag.data());
		set.pt_bjet4[i] =(TH1D*) f_data->Get(temp_tag);
		std::sprintf(temp_tag, "pt_bjet4_%s", tag.data());
		set.pt_bjet4[i]->SetName(temp_tag);
		set.pt_bjet4[i]->SetDirectory(gROOT);
		set.pt_bjet4[i]->SetLineColor(set.lineColor[i]);
		set.pt_bjet4[i]->SetFillColor(set.color[i]);
		set.pt_bjet4[i]->SetLineWidth(1);
	  }
	  // mu1_pt
	  std::sprintf(temp_tag, "mu1_pt_%s_%s", files[i].c_str(),tag.data());
	  set.mu1_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu1_pt_%s", tag.data());
	  set.mu1_pt[i]->SetName(temp_tag);
	  set.mu1_pt[i]->SetDirectory(gROOT);
	  set.mu1_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu1_pt[i]->SetFillColor(set.color[i]);
	  set.mu1_pt[i]->SetLineWidth(1);

	  // mu2_pt
	  std::sprintf(temp_tag, "mu2_pt_%s_%s", files[i].c_str(),tag.data());
	  set.mu2_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu2_pt_%s", tag.data());
	  set.mu2_pt[i]->SetName(temp_tag);
	  set.mu2_pt[i]->SetDirectory(gROOT);
	  set.mu2_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu2_pt[i]->SetFillColor(set.color[i]);
	  set.mu2_pt[i]->SetLineWidth(1);

	  // mu3_pt
	  std::sprintf(temp_tag, "mu3_pt_%s_%s", files[i].c_str(),tag.data());
	  set.mu3_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu3_pt_%s", tag.data());
	  set.mu3_pt[i]->SetName(temp_tag);
	  set.mu3_pt[i]->SetDirectory(gROOT);
	  set.mu3_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu3_pt[i]->SetFillColor(set.color[i]);
	  set.mu3_pt[i]->SetLineWidth(1);

	  // mu_eta
	  std::sprintf(temp_tag, "mu_eta_%s_%s", files[i].c_str(),tag.data());
	  set.mu_eta[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu_eta_%s", tag.data());
	  set.mu_eta[i]->SetName(temp_tag);
	  set.mu_eta[i]->SetDirectory(gROOT);
	  set.mu_eta[i]->SetLineColor(set.lineColor[i]);
	  set.mu_eta[i]->SetFillColor(set.color[i]);
	  set.mu_eta[i]->SetLineWidth(1);

	  // el1_pt
	  std::sprintf(temp_tag, "el1_pt_%s_%s", files[i].c_str(),tag.data());
	  set.el1_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el1_pt_%s", tag.data());
	  set.el1_pt[i]->SetName(temp_tag);
	  set.el1_pt[i]->SetDirectory(gROOT);
	  set.el1_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el1_pt[i]->SetFillColor(set.color[i]);
	  set.el1_pt[i]->SetLineWidth(1);

	  // el2_pt
	  std::sprintf(temp_tag, "el2_pt_%s_%s", files[i].c_str(),tag.data());
	  set.el2_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el2_pt_%s", tag.data());
	  set.el2_pt[i]->SetName(temp_tag);
	  set.el2_pt[i]->SetDirectory(gROOT);
	  set.el2_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el2_pt[i]->SetFillColor(set.color[i]);
	  set.el2_pt[i]->SetLineWidth(1);

	  // el3_pt
	  std::sprintf(temp_tag, "el3_pt_%s_%s", files[i].c_str(),tag.data());
	  set.el3_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el3_pt_%s", tag.data());
	  set.el3_pt[i]->SetName(temp_tag);
	  set.el3_pt[i]->SetDirectory(gROOT);
	  set.el3_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el3_pt[i]->SetFillColor(set.color[i]);
	  set.el3_pt[i]->SetLineWidth(1);

	  // el_eta
	  std::sprintf(temp_tag, "el_eta_%s_%s", files[i].c_str(),tag.data());
	  set.el_eta[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el_eta_%s", tag.data());
	  set.el_eta[i]->SetName(temp_tag);
	  set.el_eta[i]->SetDirectory(gROOT);
	  set.el_eta[i]->SetLineColor(set.lineColor[i]);
	  set.el_eta[i]->SetFillColor(set.color[i]);
	  set.el_eta[i]->SetLineWidth(1);

	  // MET
	  std::sprintf(temp_tag, "MET_%s_%s", files[i].c_str(),tag.data());
	  set.MET[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "MET_%s", tag.data());
	  set.MET[i]->SetName(temp_tag);
	  set.MET[i]->SetDirectory(gROOT);
	  set.MET[i]->SetLineColor(set.lineColor[i]);
	  set.MET[i]->SetFillColor(set.color[i]);
	  set.MET[i]->SetLineWidth(1);

	  // HT
	  std::sprintf(temp_tag, "HT_%s_%s", files[i].c_str(),tag.data());
	  set.HT[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "HT_%s", tag.data());
	  set.HT[i]->SetName(temp_tag);
	  set.HT[i]->SetDirectory(gROOT);
	  set.HT[i]->SetLineColor(set.lineColor[i]);
	  set.HT[i]->SetFillColor(set.color[i]);
	  set.HT[i]->SetLineWidth(1);

	  // Meff
	  std::sprintf(temp_tag, "Meff_%s_%s", files[i].c_str(),tag.data());
	  set.Meff[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Meff_%s", tag.data());
	  set.Meff[i]->SetName(temp_tag);
	  set.Meff[i]->SetDirectory(gROOT);
	  set.Meff[i]->SetLineColor(set.lineColor[i]);
	  set.Meff[i]->SetFillColor(set.color[i]);
	  set.Meff[i]->SetLineWidth(1);

	  // mT
	  std::sprintf(temp_tag, "mT_%s_%s", files[i].c_str(),tag.data());
	  set.mT[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mT_%s", tag.data());
	  set.mT[i]->SetName(temp_tag);
	  set.mT[i]->SetDirectory(gROOT);
	  set.mT[i]->SetLineColor(set.lineColor[i]);
	  set.mT[i]->SetFillColor(set.color[i]);
	  set.mT[i]->SetLineWidth(1);

	  // mT_min
	  std::sprintf(temp_tag, "mT_min_%s_%s", files[i].c_str(),tag.data());
	  set.mT_min[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mT_min_%s", tag.data());
	  set.mT_min[i]->SetName(temp_tag);
	  set.mT_min[i]->SetDirectory(gROOT);
	  set.mT_min[i]->SetLineColor(set.lineColor[i]);
	  set.mT_min[i]->SetFillColor(set.color[i]);
	  set.mT_min[i]->SetLineWidth(1);
	  if(reduced){
		// MZ
		std::sprintf(temp_tag, "MZ_%s_%s", files[i].c_str(),tag.data());
		set.MZ[i] =(TH1D*) f_data->Get(temp_tag);
		std::sprintf(temp_tag, "MZ_%s", tag.data());
		set.MZ[i]->SetName(temp_tag);
		set.MZ[i]->SetDirectory(gROOT);
		set.MZ[i]->SetLineColor(set.lineColor[i]);
		set.MZ[i]->SetFillColor(set.color[i]);
		set.MZ[i]->SetLineWidth(1);

		// Mlll
		std::sprintf(temp_tag, "Mlll_%s_%s", files[i].c_str(),tag.data());
		set.Mlll[i] =(TH1D*) f_data->Get(temp_tag);
		std::sprintf(temp_tag, "Mlll_%s", tag.data());
		set.Mlll[i]->SetName(temp_tag);
		set.Mlll[i]->SetDirectory(gROOT);
		set.Mlll[i]->SetLineColor(set.lineColor[i]);
		set.Mlll[i]->SetFillColor(set.color[i]);
		set.Mlll[i]->SetLineWidth(1);
	  }
	  // Mee
	  std::sprintf(temp_tag, "Mee_%s_%s", files[i].c_str(),tag.data());
	  set.Mee[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Mee_%s", tag.data());
	  set.Mee[i]->SetName(temp_tag);
	  set.Mee[i]->SetDirectory(gROOT);
	  set.Mee[i]->SetLineColor(set.lineColor[i]);
	  set.Mee[i]->SetFillColor(set.color[i]);
	  set.Mee[i]->SetLineWidth(1);

	  // Mmumu
	  std::sprintf(temp_tag, "Mmumu_%s_%s", files[i].c_str(),tag.data());
	  set.Mmumu[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Mmumu_%s", tag.data());
	  set.Mmumu[i]->SetName(temp_tag);
	  set.Mmumu[i]->SetDirectory(gROOT);
	  set.Mmumu[i]->SetLineColor(set.lineColor[i]);
	  set.Mmumu[i]->SetFillColor(set.color[i]);
	  set.Mmumu[i]->SetLineWidth(1);

	  // LEPPt
	  std::sprintf(temp_tag, "LEPPt_%s_%s", files[i].c_str(),tag.data());
	  set.LEPPt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "LEPPt_%s", tag.data());
	  set.LEPPt[i]->SetName(temp_tag);
	  set.LEPPt[i]->SetDirectory(gROOT);
	  set.LEPPt[i]->SetLineColor(set.lineColor[i]);
	  set.LEPPt[i]->SetFillColor(set.color[i]);
	  set.LEPPt[i]->SetLineWidth(1);

	  // LEP1Pt
	  std::sprintf(temp_tag, "LEP1Pt_%s_%s", files[i].c_str(),tag.data());
	  set.LEP1Pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "LEP1Pt_%s", tag.data());
	  set.LEP1Pt[i]->SetName(temp_tag);
	  set.LEP1Pt[i]->SetDirectory(gROOT);
	  set.LEP1Pt[i]->SetLineColor(set.lineColor[i]);
	  set.LEP1Pt[i]->SetFillColor(set.color[i]);
	  set.LEP1Pt[i]->SetLineWidth(1);

	  // LEP2Pt
	  std::sprintf(temp_tag, "LEP2Pt_%s_%s", files[i].c_str(),tag.data());
	  set.LEP2Pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "LEP2Pt_%s", tag.data());
	  set.LEP2Pt[i]->SetName(temp_tag);
	  set.LEP2Pt[i]->SetDirectory(gROOT);
	  set.LEP2Pt[i]->SetLineColor(set.lineColor[i]);
	  set.LEP2Pt[i]->SetFillColor(set.color[i]);
	  set.LEP2Pt[i]->SetLineWidth(1);

	  // LEP3Pt
	  std::sprintf(temp_tag, "LEP3Pt_%s_%s", files[i].c_str(),tag.data());
	  set.LEP3Pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "LEP3Pt_%s", tag.data());
	  set.LEP3Pt[i]->SetName(temp_tag);
	  set.LEP3Pt[i]->SetDirectory(gROOT);
	  set.LEP3Pt[i]->SetLineColor(set.lineColor[i]);
	  set.LEP3Pt[i]->SetFillColor(set.color[i]);
	  set.LEP3Pt[i]->SetLineWidth(1);

	  // LEPChargeSum
	  std::sprintf(temp_tag, "LEPChargeSum_%s_%s", files[i].c_str(),tag.data());
	  set.LEPChargeSum[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "LEPChargeSum_%s", tag.data());
	  set.LEPChargeSum[i]->SetName(temp_tag);
	  set.LEPChargeSum[i]->SetDirectory(gROOT);
	  set.LEPChargeSum[i]->SetLineColor(set.lineColor[i]);
	  set.LEPChargeSum[i]->SetFillColor(set.color[i]);
	  set.LEPChargeSum[i]->SetLineWidth(1);
	  if(reduced){
		// lep_softest_pt
		std::sprintf(temp_tag, "lep_softest_pt_%s_%s", files[i].c_str(),tag.data());
		set.lep_softest_pt[i] =(TH1D*) f_data->Get(temp_tag);
		std::sprintf(temp_tag, "lep_softest_pt_%s", tag.data());
		set.lep_softest_pt[i]->SetName(temp_tag);
		set.lep_softest_pt[i]->SetDirectory(gROOT);
		set.lep_softest_pt[i]->SetLineColor(set.lineColor[i]);
		set.lep_softest_pt[i]->SetFillColor(set.color[i]);
		set.lep_softest_pt[i]->SetLineWidth(1);
	  }
	}
  }
  
  f_data->Close("R");
  
  return;
}

//-----------------------------------------------------------------------------

void getData_SigAll(distrSigAll& set, string tag, const char* syst_tag) {
  
  getData_SigAll(set, tag, "", -1, syst_tag);

  return;
}

//-----------------------------------------------------------------------------

void getData_SigAll(distrSigAll& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {
  
  std::cout << " SS3L ..." << std::endl;  
  getData_SigSignature(set.SS3L, "SS3L" + tag, "", -1, syst_tag);
  //  std::cout << "reading signal OS ..." << std::endl;  
  //  getData_SigSignature(set.OS, "OS" + tag, "", -1, syst_tag);
  //  std::cout << "reading signal SS ..." << std::endl;  
  //  getData_SigSignature(set.SS, "SS" + tag, "", -1, syst_tag);
  /*		  std::cout << "reading signal 3L ..." << std::endl;  
			  getData_SigSignature(set.L3, "3L" + tag, "", -1, syst_tag);
  */
  return;
}

//-----------------------------------------------------------------------------

void getData_SigSignature(distrSigSignature& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {
  
  /*  getData_SigRegion(set.Incl, "Incl_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.PRE, "PRE_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.CR0b, "CR0b_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.CR1b, "CR1b_" + tag, "", -1, syst_tag);*/
  getData_SigRegion(set.SR3L1, "SR3L1_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR3L2, "SR3L2_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR0b1, "SR0b1_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR0b2, "SR0b2_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR1b, "SR1b_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR3b, "SR3b_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR1b_DD, "SR1b_DD_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR3b_DD, "SR3b_DD_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR1b_GG, "SR1b_GG_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.VRWW, "VRWW_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.VRWZ4j, "VRWZ4j_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.VRWZ5j, "VRWZ5j_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.VRttW, "VRttW_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.VRttZ, "VRttZ_" + tag, "", -1, syst_tag);

  // getData_SigRegion(set.SR0b5j, "SR0b5j_" + tag, "", -1, syst_tag);
  // getData_SigRegion(set.SR2b1, "SR2b1_" + tag, "", -1, syst_tag);
  // getData_SigRegion(set.SR2b2, "SR2b2_" + tag, "", -1, syst_tag);
  // getData_SigRegion(set.SR3L3b, "SR3L3b_" + tag, "", -1, syst_tag);
  

  return;
}

//-----------------------------------------------------------------------------

void getData_SigRegion(distrSigRegion& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {

  getData_SigSet(set.fs_elel, "ee_" + tag, "", -1, syst_tag);
  getData_SigSet(set.fs_elmu, "em_" + tag, "", -1, syst_tag);
  getData_SigSet(set.fs_mumu, "mm_" + tag, "", -1, syst_tag);
  //  getData_SigSet(set.fs_3l, "3l_" + tag, "", -1, syst_tag);
  getData_SigSet(set.fs_comb, "comb_" + tag, "", -1, syst_tag);

  return;
}

//-----------------------------------------------------------------------------

void getData_SigSet(distrSigSet& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag){
  
  set.int_lumi = lumi;	
  set.syst_tag = syst_tag;
  char temp_file[512];
  char temp_tag[256];
  TFile *f_data;
  
  const string files[N_SIG] = {"GG_ttn1_1200_5000_855"};//{"ttn1_1200_5000_1", "ttn1_1200_5000_600", "ttn1_1200_5000_855"}; 
  
  for (int i = 0; i < N_SIG; i++){
	std::sprintf(temp_file, "%s/%s.root", path,files[i].c_str());
	set.file_name[i] = temp_file;
	set.color[i] = 0;
	set.lineColor[i] = 1;
  }
  
  set.lineColor[0] = kRed; //kMagenta; //
  set.lineColor[1] = kBlue; //
  set.lineColor[2] = 3; //
  
  for (int i = 0; i < N_SIG; i++) {
	f_data = new TFile(set.file_name[i].data(), "READ");

	// NJETS
	std::sprintf(temp_tag, "NJETS_%s_mc_%s", files[i].c_str(), tag.data());
	set.NJETS[i] =(TH1D*) f_data->Get(temp_tag);
	if(!draw_sig)
	  set.NJETS[i]->Reset();
	set.NJETS[i]->SetName(temp_tag);
	set.NJETS[i]->SetDirectory(gROOT);
	set.NJETS[i]->SetLineColor(set.lineColor[i]);
	set.NJETS[i]->SetFillColor(set.color[i]);
	set.NJETS[i]->SetLineWidth(1);
	if(!test_me){
	  // pt_jet1
	  std::sprintf(temp_tag, "pt_jet1_%s_mc_%s", files[i].c_str(), tag.data());
	  set.pt_jet1[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.pt_jet1[i]->Reset();
	  set.pt_jet1[i]->SetName(temp_tag);
	  set.pt_jet1[i]->SetDirectory(gROOT);
	  set.pt_jet1[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet1[i]->SetFillColor(set.color[i]);
	  set.pt_jet1[i]->SetLineWidth(1);
	  // pt_jet2
	  std::sprintf(temp_tag, "pt_jet2_%s_mc_%s", files[i].c_str(), tag.data());
	  set.pt_jet2[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.pt_jet2[i]->Reset();
	  set.pt_jet2[i]->SetName(temp_tag);
	  set.pt_jet2[i]->SetDirectory(gROOT);
	  set.pt_jet2[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet2[i]->SetFillColor(set.color[i]);
	  set.pt_jet2[i]->SetLineWidth(1);
	  // pt_jet3
	  std::sprintf(temp_tag, "pt_jet3_%s_mc_%s", files[i].c_str(), tag.data());
	  set.pt_jet3[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.pt_jet3[i]->Reset();
	  set.pt_jet3[i]->SetName(temp_tag);
	  set.pt_jet3[i]->SetDirectory(gROOT);
	  set.pt_jet3[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet3[i]->SetFillColor(set.color[i]);
	  set.pt_jet3[i]->SetLineWidth(1);
	  if(reduced){
		// pt_jet4
		std::sprintf(temp_tag, "pt_jet4_%s_mc_%s", files[i].c_str(), tag.data());
		set.pt_jet4[i] =(TH1D*) f_data->Get(temp_tag);
		if(!draw_sig)
		  set.pt_jet4[i]->Reset();
		set.pt_jet4[i]->SetName(temp_tag);
		set.pt_jet4[i]->SetDirectory(gROOT);
		set.pt_jet4[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet4[i]->SetFillColor(set.color[i]);
		set.pt_jet4[i]->SetLineWidth(1);
		// pt_jet5
		std::sprintf(temp_tag, "pt_jet5_%s_mc_%s", files[i].c_str(), tag.data());
		set.pt_jet5[i] =(TH1D*) f_data->Get(temp_tag);
		if(!draw_sig)
		  set.pt_jet5[i]->Reset();
		set.pt_jet5[i]->SetName(temp_tag);
		set.pt_jet5[i]->SetDirectory(gROOT);
		set.pt_jet5[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet5[i]->SetFillColor(set.color[i]);
		set.pt_jet5[i]->SetLineWidth(1);
	  }
	  // NBJETS
	  std::sprintf(temp_tag, "NBJETS_%s_mc_%s", files[i].c_str(), tag.data());
	  set.NBJETS[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.NBJETS[i]->Reset();
	  set.NBJETS[i]->SetName(temp_tag);
	  set.NBJETS[i]->SetDirectory(gROOT);
	  set.NBJETS[i]->SetLineColor(set.lineColor[i]);
	  set.NBJETS[i]->SetFillColor(set.color[i]);
	  set.NBJETS[i]->SetLineWidth(1);
	  // pt_bjet1
	  std::sprintf(temp_tag, "pt_bjet1_%s_mc_%s", files[i].c_str(), tag.data());
	  set.pt_bjet1[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.pt_bjet1[i]->Reset();
	  set.pt_bjet1[i]->SetName(temp_tag);
	  set.pt_bjet1[i]->SetDirectory(gROOT);
	  set.pt_bjet1[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet1[i]->SetFillColor(set.color[i]);
	  set.pt_bjet1[i]->SetLineWidth(1);
	  // pt_bjet2
	  std::sprintf(temp_tag, "pt_bjet2_%s_mc_%s", files[i].c_str(), tag.data());
	  set.pt_bjet2[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.pt_bjet2[i]->Reset();
	  set.pt_bjet2[i]->SetName(temp_tag);
	  set.pt_bjet2[i]->SetDirectory(gROOT);
	  set.pt_bjet2[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet2[i]->SetFillColor(set.color[i]);
	  set.pt_bjet2[i]->SetLineWidth(1);
	  // pt_bjet3
	  std::sprintf(temp_tag, "pt_bjet3_%s_mc_%s", files[i].c_str(), tag.data());
	  set.pt_bjet3[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.pt_bjet3[i]->Reset();
	  set.pt_bjet3[i]->SetName(temp_tag);
	  set.pt_bjet3[i]->SetDirectory(gROOT);
	  set.pt_bjet3[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet3[i]->SetFillColor(set.color[i]);
	  set.pt_bjet3[i]->SetLineWidth(1);
	  if(reduced){
		// pt_bjet4
		std::sprintf(temp_tag, "pt_bjet4_%s_mc_%s", files[i].c_str(), tag.data());
		set.pt_bjet4[i] =(TH1D*) f_data->Get(temp_tag);
		if(!draw_sig)
		  set.pt_bjet4[i]->Reset();
		set.pt_bjet4[i]->SetName(temp_tag);
		set.pt_bjet4[i]->SetDirectory(gROOT);
		set.pt_bjet4[i]->SetLineColor(set.lineColor[i]);
		set.pt_bjet4[i]->SetFillColor(set.color[i]);
		set.pt_bjet4[i]->SetLineWidth(1);
	  }
	  // mu1_pt
	  std::sprintf(temp_tag, "mu1_pt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.mu1_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.mu1_pt[i]->Reset();
	  set.mu1_pt[i]->SetName(temp_tag);
	  set.mu1_pt[i]->SetDirectory(gROOT);
	  set.mu1_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu1_pt[i]->SetFillColor(set.color[i]);
	  set.mu1_pt[i]->SetLineWidth(1);
	  // mu2_pt
	  std::sprintf(temp_tag, "mu2_pt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.mu2_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.mu2_pt[i]->Reset();
	  set.mu2_pt[i]->SetName(temp_tag);
	  set.mu2_pt[i]->SetDirectory(gROOT);
	  set.mu2_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu2_pt[i]->SetFillColor(set.color[i]);
	  set.mu2_pt[i]->SetLineWidth(1);
	  // mu3_pt
	  std::sprintf(temp_tag, "mu3_pt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.mu3_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.mu3_pt[i]->Reset();
	  set.mu3_pt[i]->SetName(temp_tag);
	  set.mu3_pt[i]->SetDirectory(gROOT);
	  set.mu3_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu3_pt[i]->SetFillColor(set.color[i]);
	  set.mu3_pt[i]->SetLineWidth(1);
	  // mu_eta
	  std::sprintf(temp_tag, "mu_eta_%s_mc_%s", files[i].c_str(), tag.data());
	  set.mu_eta[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.mu_eta[i]->Reset();
	  set.mu_eta[i]->SetName(temp_tag);
	  set.mu_eta[i]->SetDirectory(gROOT);
	  set.mu_eta[i]->SetLineColor(set.lineColor[i]);
	  set.mu_eta[i]->SetFillColor(set.color[i]);
	  set.mu_eta[i]->SetLineWidth(1);
	  // el1_pt
	  std::sprintf(temp_tag, "el1_pt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.el1_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.el1_pt[i]->Reset();
	  set.el1_pt[i]->SetName(temp_tag);
	  set.el1_pt[i]->SetDirectory(gROOT);
	  set.el1_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el1_pt[i]->SetFillColor(set.color[i]);
	  set.el1_pt[i]->SetLineWidth(1);
	  // el2_pt
	  std::sprintf(temp_tag, "el2_pt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.el2_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.el2_pt[i]->Reset();
	  set.el2_pt[i]->SetName(temp_tag);
	  set.el2_pt[i]->SetDirectory(gROOT);
	  set.el2_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el2_pt[i]->SetFillColor(set.color[i]);
	  set.el2_pt[i]->SetLineWidth(1);
	  // el3_pt
	  std::sprintf(temp_tag, "el3_pt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.el3_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.el3_pt[i]->Reset();
	  set.el3_pt[i]->SetName(temp_tag);
	  set.el3_pt[i]->SetDirectory(gROOT);
	  set.el3_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el3_pt[i]->SetFillColor(set.color[i]);
	  set.el3_pt[i]->SetLineWidth(1);
	  // el_eta
	  std::sprintf(temp_tag, "el_eta_%s_mc_%s", files[i].c_str(), tag.data());
	  set.el_eta[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.el_eta[i]->Reset();
	  set.el_eta[i]->SetName(temp_tag);
	  set.el_eta[i]->SetDirectory(gROOT);
	  set.el_eta[i]->SetLineColor(set.lineColor[i]);
	  set.el_eta[i]->SetFillColor(set.color[i]);
	  set.el_eta[i]->SetLineWidth(1);
	  // MET
	  std::sprintf(temp_tag, "MET_%s_mc_%s", files[i].c_str(), tag.data());
	  set.MET[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.MET[i]->Reset();
	  set.MET[i]->SetName(temp_tag);
	  set.MET[i]->SetDirectory(gROOT);
	  set.MET[i]->SetLineColor(set.lineColor[i]);
	  set.MET[i]->SetFillColor(set.color[i]);
	  set.MET[i]->SetLineWidth(1);
	  // HT
	  std::sprintf(temp_tag, "HT_%s_mc_%s", files[i].c_str(), tag.data());
	  set.HT[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.HT[i]->Reset();
	  set.HT[i]->SetName(temp_tag);
	  set.HT[i]->SetDirectory(gROOT);
	  set.HT[i]->SetLineColor(set.lineColor[i]);
	  set.HT[i]->SetFillColor(set.color[i]);
	  set.HT[i]->SetLineWidth(1);
	  // Meff
	  std::sprintf(temp_tag, "Meff_%s_mc_%s", files[i].c_str(), tag.data());
	  set.Meff[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.Meff[i]->Reset();
	  set.Meff[i]->SetName(temp_tag);
	  set.Meff[i]->SetDirectory(gROOT);
	  set.Meff[i]->SetLineColor(set.lineColor[i]);
	  set.Meff[i]->SetFillColor(set.color[i]);
	  set.Meff[i]->SetLineWidth(1);
	  // mT
	  std::sprintf(temp_tag, "mT_%s_mc_%s", files[i].c_str(), tag.data());
	  set.mT[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.mT[i]->Reset();
	  set.mT[i]->SetName(temp_tag);
	  set.mT[i]->SetDirectory(gROOT);
	  set.mT[i]->SetLineColor(set.lineColor[i]);
	  set.mT[i]->SetFillColor(set.color[i]);
	  set.mT[i]->SetLineWidth(1);
	  // mT_min
	  std::sprintf(temp_tag, "mT_min_%s_mc_%s", files[i].c_str(), tag.data());
	  set.mT_min[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.mT_min[i]->Reset();
	  set.mT_min[i]->SetName(temp_tag);
	  set.mT_min[i]->SetDirectory(gROOT);
	  set.mT_min[i]->SetLineColor(set.lineColor[i]);
	  set.mT_min[i]->SetFillColor(set.color[i]);
	  set.mT_min[i]->SetLineWidth(1);
	  if(reduced){
		// MZ
		std::sprintf(temp_tag, "MZ_%s_mc_%s", files[i].c_str(), tag.data());
		set.MZ[i] =(TH1D*) f_data->Get(temp_tag);
		if(!draw_sig)
		  set.MZ[i]->Reset();
		set.MZ[i]->SetName(temp_tag);
		set.MZ[i]->SetDirectory(gROOT);
		set.MZ[i]->SetLineColor(set.lineColor[i]);
		set.MZ[i]->SetFillColor(set.color[i]);
		set.MZ[i]->SetLineWidth(1);
		// Mlll
		std::sprintf(temp_tag, "Mlll_%s_mc_%s", files[i].c_str(), tag.data());
		set.Mlll[i] =(TH1D*) f_data->Get(temp_tag);
		if(!draw_sig)
		  set.Mlll[i]->Reset();
		set.Mlll[i]->SetName(temp_tag);
		set.Mlll[i]->SetDirectory(gROOT);
		set.Mlll[i]->SetLineColor(set.lineColor[i]);
		set.Mlll[i]->SetFillColor(set.color[i]);
		set.Mlll[i]->SetLineWidth(1);
	  }
	  // Mee
	  std::sprintf(temp_tag, "Mee_%s_mc_%s", files[i].c_str(), tag.data());
	  set.Mee[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.Mee[i]->Reset();
	  set.Mee[i]->SetName(temp_tag);
	  set.Mee[i]->SetDirectory(gROOT);
	  set.Mee[i]->SetLineColor(set.lineColor[i]);
	  set.Mee[i]->SetFillColor(set.color[i]);
	  set.Mee[i]->SetLineWidth(1);
	  // Mmumu
	  std::sprintf(temp_tag, "Mmumu_%s_mc_%s", files[i].c_str(), tag.data());
	  set.Mmumu[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.Mmumu[i]->Reset();
	  set.Mmumu[i]->SetName(temp_tag);
	  set.Mmumu[i]->SetDirectory(gROOT);
	  set.Mmumu[i]->SetLineColor(set.lineColor[i]);
	  set.Mmumu[i]->SetFillColor(set.color[i]);
	  set.Mmumu[i]->SetLineWidth(1);
	  // LEPPt
	  std::sprintf(temp_tag, "LEPPt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.LEPPt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.LEPPt[i]->Reset();
	  set.LEPPt[i]->SetName(temp_tag);
	  set.LEPPt[i]->SetDirectory(gROOT);
	  set.LEPPt[i]->SetLineColor(set.lineColor[i]);
	  set.LEPPt[i]->SetFillColor(set.color[i]);
	  set.LEPPt[i]->SetLineWidth(1);
	  // LEP1Pt
	  std::sprintf(temp_tag, "LEP1Pt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.LEP1Pt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.LEP1Pt[i]->Reset();
	  set.LEP1Pt[i]->SetName(temp_tag);
	  set.LEP1Pt[i]->SetDirectory(gROOT);
	  set.LEP1Pt[i]->SetLineColor(set.lineColor[i]);
	  set.LEP1Pt[i]->SetFillColor(set.color[i]);
	  set.LEP1Pt[i]->SetLineWidth(1);
	  // LEP2Pt
	  std::sprintf(temp_tag, "LEP2Pt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.LEP2Pt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.LEP2Pt[i]->Reset();
	  set.LEP2Pt[i]->SetName(temp_tag);
	  set.LEP2Pt[i]->SetDirectory(gROOT);
	  set.LEP2Pt[i]->SetLineColor(set.lineColor[i]);
	  set.LEP2Pt[i]->SetFillColor(set.color[i]);
	  set.LEP2Pt[i]->SetLineWidth(1);
	  // LEP3Pt
	  std::sprintf(temp_tag, "LEP3Pt_%s_mc_%s", files[i].c_str(), tag.data());
	  set.LEP3Pt[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.LEP3Pt[i]->Reset();
	  set.LEP3Pt[i]->SetName(temp_tag);
	  set.LEP3Pt[i]->SetDirectory(gROOT);
	  set.LEP3Pt[i]->SetLineColor(set.lineColor[i]);
	  set.LEP3Pt[i]->SetFillColor(set.color[i]);
	  set.LEP3Pt[i]->SetLineWidth(1);
	  // LEPChargeSum
	  std::sprintf(temp_tag, "LEPChargeSum_%s_mc_%s", files[i].c_str(), tag.data());
	  set.LEPChargeSum[i] =(TH1D*) f_data->Get(temp_tag);
	  if(!draw_sig)
		set.LEPChargeSum[i]->Reset();
	  set.LEPChargeSum[i]->SetName(temp_tag);
	  set.LEPChargeSum[i]->SetDirectory(gROOT);
	  set.LEPChargeSum[i]->SetLineColor(set.lineColor[i]);
	  set.LEPChargeSum[i]->SetFillColor(set.color[i]);
	  set.LEPChargeSum[i]->SetLineWidth(1);
	  if(reduced){
		// lep_softest_pt
		std::sprintf(temp_tag, "lep_softest_pt_%s_mc_%s", files[i].c_str(), tag.data());
		set.lep_softest_pt[i] =(TH1D*) f_data->Get(temp_tag);
		if(!draw_sig)
		  set.lep_softest_pt[i]->Reset();
		set.lep_softest_pt[i]->SetName(temp_tag);
		set.lep_softest_pt[i]->SetDirectory(gROOT);
		set.lep_softest_pt[i]->SetLineColor(set.lineColor[i]);
		set.lep_softest_pt[i]->SetFillColor(set.color[i]);
		set.lep_softest_pt[i]->SetLineWidth(1);
	  }
	}
  }
  
  f_data->Close("R");
  
  return;
}

//-----------------------------------------------------------------------------
// Scale luminsoity
//-----------------------------------------------------------------------------

void scaleLumi_All(distrAll& set, Double_t sf) {

  scaleLumi_Signature(set.SS3L, sf);
  //  scaleLumi_Signature(set.OS, sf);
  //  scaleLumi_Signature(set.SS, sf);
  /*	  scaleLumi_Signature(set.L3, sf);*/

  return;
}

//-----------------------------------------------------------------------------

void scaleLumi_Signature(distrSignature& set, Double_t sf) {

  /*  scaleLumi_Region(set.Incl, sf);
  scaleLumi_Region(set.PRE, sf);
  scaleLumi_Region(set.CR0b, sf);
  scaleLumi_Region(set.CR1b, sf);*/
  scaleLumi_Region(set.SR3L1, sf);
  scaleLumi_Region(set.SR3L2, sf);
  scaleLumi_Region(set.SR0b1, sf);
  scaleLumi_Region(set.SR0b2, sf);
  scaleLumi_Region(set.SR1b, sf);
  scaleLumi_Region(set.SR3b, sf);
  scaleLumi_Region(set.SR1b_DD, sf);
  scaleLumi_Region(set.SR3b_DD, sf);
  scaleLumi_Region(set.SR1b_GG, sf);
  scaleLumi_Region(set.VRWW, sf);
  scaleLumi_Region(set.VRWZ4j, sf);
  scaleLumi_Region(set.VRWZ5j, sf);
  scaleLumi_Region(set.VRttW, sf);
  scaleLumi_Region(set.VRttZ, sf);

  // scaleLumi_Region(set.SR0b5j, sf);
  // scaleLumi_Region(set.SR2b1, sf);
  // scaleLumi_Region(set.SR2b2, sf);
  // scaleLumi_Region(set.SR3L3b, sf);

  return;
}

//-----------------------------------------------------------------------------

void scaleLumi_Region(distrRegion& set, Double_t sf) {
  
  scaleLumi_Set(set.fs_elel, sf);
  scaleLumi_Set(set.fs_elmu, sf);
  scaleLumi_Set(set.fs_mumu, sf);
  //  scaleLumi_Set(set.fs_3l, sf);
  scaleLumi_Set(set.fs_comb, sf);
    
  return;
}

//-----------------------------------------------------------------------------

void scaleLumi_Set(distrSet& set, Double_t sf) {

  set.int_lumi *= sf;
  
  return;
}

//-----------------------------------------------------------------------------
// Scale cross sections
//-----------------------------------------------------------------------------

void scaleXSect_All(distrAll& set, Int_t ind, Double_t sf) {

  scaleXSect_Signature(set.SS3L, ind, sf);
  //  scaleXSect_Signature(set.OS, ind, sf);
  //  scaleXSect_Signature(set.SS, ind, sf);
  /*	  scaleXSect_Signature(set.L3, ind, sf);*/

  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_Signature(distrSignature& set, Int_t ind, Double_t sf) {

  /*  scaleXSect_Region(set.Incl,  ind,  sf);
  scaleXSect_Region(set.PRE,  ind,  sf);
  scaleXSect_Region(set.CR0b,  ind,  sf);
  scaleXSect_Region(set.CR1b,  ind,  sf);*/
  scaleXSect_Region(set.SR3L1,  ind,  sf);
  scaleXSect_Region(set.SR3L2,  ind,  sf);
  scaleXSect_Region(set.SR0b1,  ind,  sf);
  scaleXSect_Region(set.SR0b2,  ind,  sf);
  scaleXSect_Region(set.SR1b,  ind,  sf);
  scaleXSect_Region(set.SR3b,  ind,  sf);
  scaleXSect_Region(set.SR1b_DD,  ind,  sf);
  scaleXSect_Region(set.SR3b_DD,  ind,  sf);
  scaleXSect_Region(set.SR1b_GG,  ind,  sf);
  scaleXSect_Region(set.VRWW,  ind,  sf);
  scaleXSect_Region(set.VRWZ4j,  ind,  sf);
  scaleXSect_Region(set.VRWZ5j,  ind,  sf);
  scaleXSect_Region(set.VRttW,  ind,  sf);
  scaleXSect_Region(set.VRttZ,  ind,  sf);

  // scaleXSect_Region(set.SR0b5j,  ind,  sf);
  // scaleXSect_Region(set.SR2b1,  ind,  sf);
  // scaleXSect_Region(set.SR2b2,  ind,  sf);
  // scaleXSect_Region(set.SR3L3b,  ind,  sf);

  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_Region(distrRegion& set, Int_t ind, Double_t sf) {
  
  scaleXSect_Set(set.fs_elel, ind, sf);
  scaleXSect_Set(set.fs_elmu, ind, sf);
  scaleXSect_Set(set.fs_mumu, ind, sf);
  //  scaleXSect_Set(set.fs_3l, ind, sf);
  scaleXSect_Set(set.fs_comb, ind, sf);
    
  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_Set(distrSet& set, Int_t ind, Double_t sf) {

  set.xsect[ind] *= sf;
  
  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_SigAll(distrSigAll& set, Int_t ind, Double_t sf) {

  scaleXSect_SigSignature(set.SS3L, ind, sf);
  //  scaleXSect_SigSignature(set.OS, ind, sf);
  //  scaleXSect_SigSignature(set.SS, ind, sf);
  /*	  scaleXSect_SigSignature(set.L3, ind, sf);*/

  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_SigSignature(distrSigSignature& set, Int_t ind, Double_t sf) {

  /*  scaleXSect_SigRegion(set.Incl, ind, sf);
  scaleXSect_SigRegion(set.PRE, ind, sf);
  scaleXSect_SigRegion(set.CR0b, ind, sf);
  scaleXSect_SigRegion(set.CR1b, ind, sf);*/
  scaleXSect_SigRegion(set.SR3L1, ind, sf);
  scaleXSect_SigRegion(set.SR3L2, ind, sf);
  scaleXSect_SigRegion(set.SR0b1, ind, sf);
  scaleXSect_SigRegion(set.SR0b2, ind, sf);
  scaleXSect_SigRegion(set.SR1b, ind, sf);
  scaleXSect_SigRegion(set.SR3b, ind, sf);
  scaleXSect_SigRegion(set.SR1b_DD, ind, sf);
  scaleXSect_SigRegion(set.SR3b_DD, ind, sf);
  scaleXSect_SigRegion(set.SR1b_GG, ind, sf);
  scaleXSect_SigRegion(set.VRWW, ind, sf);
  scaleXSect_SigRegion(set.VRWZ4j, ind, sf);
  scaleXSect_SigRegion(set.VRWZ5j, ind, sf);
  scaleXSect_SigRegion(set.VRttW, ind, sf);
  scaleXSect_SigRegion(set.VRttZ, ind, sf);

  // scaleXSect_SigRegion(set.SR0b5j, ind, sf);
  // scaleXSect_SigRegion(set.SR2b1, ind, sf);
  // scaleXSect_SigRegion(set.SR2b2, ind, sf);
  // scaleXSect_SigRegion(set.SR3L3b, ind, sf);

  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_SigRegion(distrSigRegion& set, Int_t ind, Double_t sf) {
  
  scaleXSect_SigSet(set.fs_elel, ind, sf);
  scaleXSect_SigSet(set.fs_elmu, ind, sf);
  scaleXSect_SigSet(set.fs_mumu, ind, sf);
  //  scaleXSect_SigSet(set.fs_3l, ind, sf);
  scaleXSect_SigSet(set.fs_comb, ind, sf);
    
  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_SigSet(distrSigSet& set, Int_t ind, Double_t sf) {

  set.xsect[ind] *= sf;
  
  return;
}

//-----------------------------------------------------------------------------
// Set fake rates
//-----------------------------------------------------------------------------

void setFakeRates_All(distrAll& set, Double_t cf, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4) {
 
  setFakeRates_Signature(set.SS3L, cf, sf1, sf2, sf3, sf4);

  return;
}

//-----------------------------------------------------------------------------

void setFakeRates_Signature(distrSignature& set, Double_t cf, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4) {

  /*  setFakeRates_Region(set.Incl, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.PRE, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.CR0b, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.CR1b, cf, sf1, sf2, sf3, sf4);*/
  setFakeRates_Region(set.SR3L1, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.SR3L2, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.SR0b1, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.SR0b2, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.SR1b, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.SR3b, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.SR1b_DD, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.SR3b_DD, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.SR1b_GG, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.VRWW, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.VRWZ4j, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.VRWZ5j, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.VRttW, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Region(set.VRttZ, cf, sf1, sf2, sf3, sf4);

  // setFakeRates_Region(set.SR0b5j, cf, sf1, sf2, sf3, sf4);
  // setFakeRates_Region(set.SR2b1, cf, sf1, sf2, sf3, sf4);
  // setFakeRates_Region(set.SR2b2, cf, sf1, sf2, sf3, sf4);
  // setFakeRates_Region(set.SR3L3b, cf, sf1, sf2, sf3, sf4);

  return;
}

//-----------------------------------------------------------------------------

void setFakeRates_Region(distrRegion& set, Double_t cf, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4) {
      
  setFakeRates_Set(set.fs_elel, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Set(set.fs_elmu, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Set(set.fs_mumu, cf, sf1, sf2, sf3, sf4);
  //  setFakeRates_Set(set.fs_3l, cf, sf1, sf2, sf3, sf4);
  setFakeRates_Set(set.fs_comb, cf, sf1, sf2, sf3, sf4);

  return;
}

//-----------------------------------------------------------------------------

void setFakeRates_Set(distrSet& set, Double_t cf, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4) {

  set.charge_flip = cf;
  set.FR_hf_e = sf1;
  set.FR_lf_e = sf2;
  set.FR_hf_mu = sf3;
  set.FR_lf_mu = sf4;

  return;
}


//-----------------------------------------------------------------------------
// Weight histograms
//-----------------------------------------------------------------------------

void weightData_All(distrAll& set) {

  weightData_Signature(set.SS3L);
  //  weightData_Signature(set.OS);
  //  weightData_Signature(set.SS);
  /*	  weightData_Signature(set.L3);*/

  return;
}

//-----------------------------------------------------------------------------

void weightData_Signature(distrSignature& set) {

  /*  weightData_Region(set.Incl);
  weightData_Region(set.PRE);
  weightData_Region(set.CR0b);
  weightData_Region(set.CR1b);*/
  weightData_Region(set.SR3L1);
  weightData_Region(set.SR3L2);
  weightData_Region(set.SR0b1);
  weightData_Region(set.SR0b2);
  weightData_Region(set.SR1b);
  weightData_Region(set.SR3b);
  weightData_Region(set.SR1b_DD);
  weightData_Region(set.SR3b_DD);
  weightData_Region(set.SR1b_GG);
  weightData_Region(set.VRWW);
  weightData_Region(set.VRWZ4j);
  weightData_Region(set.VRWZ5j);
  weightData_Region(set.VRttW);
  weightData_Region(set.VRttZ);

  /*weightData_Region(set.SR0b5j);
	weightData_Region(set.SR2b1);
	weightData_Region(set.SR2b2);
	weightData_Region(set.SR3L3b);*/

  return;
}

//-----------------------------------------------------------------------------

void weightData_Region(distrRegion& set) {
  
  weightData_Set(set.fs_elel);
  weightData_Set(set.fs_elmu);
  weightData_Set(set.fs_mumu);
  //  weightData_Set(set.fs_3l);
  weightData_Set(set.fs_comb);
    
  buildStack(set.fs_elel);
  buildStack(set.fs_elmu);
  buildStack(set.fs_mumu);  
  //  buildStack(set.fs_3l);  
  buildStack(set.fs_comb);

  return;
}

//-----------------------------------------------------------------------------

void weightData_Set(distrSet& set) {

  Double_t weight[N_FAKE];
  Double_t sf = 1.;

  for (int i = 1; i < N_FAKE; i++) { // TO DO: start from 1 if 0 is data OR just create a new class for DATA or MC

	weight[i] = set.int_lumi * set.xsect[i] ;

	sf = 1.;
	if (i == charge_flip_ind_fit) 
	  sf = fabs(set.charge_flip); 

	if (i == fakes_el_hf_ind_fit) 
	  sf = fabs(set.FR_hf_e); 

	if (i == fakes_el_lf_ind_fit) 
	  sf = fabs(set.FR_lf_e); 

	if (i == fakes_mu_hf_ind_fit) 
	  sf = fabs(set.FR_hf_mu); 

	if (i == fakes_mu_lf_ind_fit) 
	  sf = fabs(set.FR_lf_mu); 
	  
	set.NJETS[i]->Scale(weight[i]*sf);
	if(!test_me){
	  set.pt_jet1[i]->Scale(weight[i]*sf);
	  set.pt_jet2[i]->Scale(weight[i]*sf);
	  set.pt_jet3[i]->Scale(weight[i]*sf);
	  if(reduced){
		set.pt_jet4[i]->Scale(weight[i]*sf);
		set.pt_jet5[i]->Scale(weight[i]*sf);
	  }
	  set.NBJETS[i]->Scale(weight[i]*sf);
	  set.pt_bjet1[i]->Scale(weight[i]*sf);
	  set.pt_bjet2[i]->Scale(weight[i]*sf);
	  set.pt_bjet3[i]->Scale(weight[i]*sf);
	  if(reduced){
		set.pt_bjet4[i]->Scale(weight[i]*sf);
	  }
	  set.mu1_pt[i]->Scale(weight[i]*sf);
	  set.mu2_pt[i]->Scale(weight[i]*sf);
	  set.mu3_pt[i]->Scale(weight[i]*sf);
	  set.mu_eta[i]->Scale(weight[i]*sf);
	  set.el1_pt[i]->Scale(weight[i]*sf);
	  set.el2_pt[i]->Scale(weight[i]*sf);
	  set.el3_pt[i]->Scale(weight[i]*sf);
	  set.el_eta[i]->Scale(weight[i]*sf);
	  set.MET[i]->Scale(weight[i]*sf);
	  set.HT[i]->Scale(weight[i]*sf);
	  set.Meff[i]->Scale(weight[i]*sf);
	  set.mT[i]->Scale(weight[i]*sf);
	  set.mT_min[i]->Scale(weight[i]*sf);
	  if(reduced){
		set.MZ[i]->Scale(weight[i]*sf);
		set.Mlll[i]->Scale(weight[i]*sf);
	  }
	  set.Mee[i]->Scale(weight[i]*sf);
	  set.Mmumu[i]->Scale(weight[i]*sf);
	  set.LEPPt[i]->Scale(weight[i]*sf);
	  set.LEP1Pt[i]->Scale(weight[i]*sf);
	  set.LEP2Pt[i]->Scale(weight[i]*sf);
	  set.LEP3Pt[i]->Scale(weight[i]*sf);
	  set.LEPChargeSum[i]->Scale(weight[i]*sf);
	  if(reduced){
		set.lep_softest_pt[i]->Scale(weight[i]*sf);}
	}
  }

  return;
}

//-----------------------------------------------------------------------------

void weightData_SigAll(distrSigAll& set) {

  weightData_SigSignature(set.SS3L);
  //  weightData_SigSignature(set.OS);
  //  weightData_SigSignature(set.SS);
  /*	  weightData_SigSignature(set.L3);*/

  return;
}

//-----------------------------------------------------------------------------

void weightData_SigSignature(distrSigSignature& set) {

  /*  weightData_SigRegion(set.Incl);
  weightData_SigRegion(set.PRE);
  weightData_SigRegion(set.CR0b);
  weightData_SigRegion(set.CR1b);*/
  weightData_SigRegion(set.SR3L1);
  weightData_SigRegion(set.SR3L2);
  weightData_SigRegion(set.SR0b1);
  weightData_SigRegion(set.SR0b2);
  weightData_SigRegion(set.SR1b);
  weightData_SigRegion(set.SR3b);
  weightData_SigRegion(set.SR1b_DD);
  weightData_SigRegion(set.SR3b_DD);
  weightData_SigRegion(set.SR1b_GG);
  weightData_SigRegion(set.VRWW);
  weightData_SigRegion(set.VRWZ4j);
  weightData_SigRegion(set.VRWZ5j);
  weightData_SigRegion(set.VRttW);
  weightData_SigRegion(set.VRttZ);

  // weightData_SigRegion(set.SR0b5j);
  // weightData_SigRegion(set.SR2b1);
  // weightData_SigRegion(set.SR2b2);
  // weightData_SigRegion(set.SR3L3b);

  return;
}

//-----------------------------------------------------------------------------

void weightData_SigRegion(distrSigRegion& set) {

  weightData_SigSet(set.fs_elel);
  weightData_SigSet(set.fs_elmu);
  weightData_SigSet(set.fs_mumu);
  //  weightData_SigSet(set.fs_3l);
  weightData_SigSet(set.fs_comb);

  return;
}

//-----------------------------------------------------------------------------

void weightData_SigSet(distrSigSet& set) {

  Double_t weight[N_SIG];
  for (int i = 0; i < N_SIG; i++){ 

	weight[i] = set.int_lumi * set.xsect[i] ; // normalize to Lumi
  
	double sf = 1.;
	set.NJETS[i]->Scale(weight[i]*sf);
	if(!test_me){
	  set.pt_jet1[i]->Scale(weight[i]*sf);
	  set.pt_jet2[i]->Scale(weight[i]*sf);
	  set.pt_jet3[i]->Scale(weight[i]*sf);
	  if(reduced){
		set.pt_jet4[i]->Scale(weight[i]*sf);
		set.pt_jet5[i]->Scale(weight[i]*sf);
	  }
	  set.NBJETS[i]->Scale(weight[i]*sf);
	  set.pt_bjet1[i]->Scale(weight[i]*sf);
	  set.pt_bjet2[i]->Scale(weight[i]*sf);
	  set.pt_bjet3[i]->Scale(weight[i]*sf);
	  if(reduced){
		set.pt_bjet4[i]->Scale(weight[i]*sf);
	  }
	  set.mu1_pt[i]->Scale(weight[i]*sf);
	  set.mu2_pt[i]->Scale(weight[i]*sf);
	  set.mu3_pt[i]->Scale(weight[i]*sf);
	  set.mu_eta[i]->Scale(weight[i]*sf);
	  set.el1_pt[i]->Scale(weight[i]*sf);
	  set.el2_pt[i]->Scale(weight[i]*sf);
	  set.el3_pt[i]->Scale(weight[i]*sf);
	  set.el_eta[i]->Scale(weight[i]*sf);
	  set.MET[i]->Scale(weight[i]*sf);
	  set.HT[i]->Scale(weight[i]*sf);
	  set.Meff[i]->Scale(weight[i]*sf);
	  set.mT[i]->Scale(weight[i]*sf);
	  set.mT_min[i]->Scale(weight[i]*sf);
	  if(reduced){
		set.MZ[i]->Scale(weight[i]*sf);
		set.Mlll[i]->Scale(weight[i]*sf);
	  }
	  set.Mee[i]->Scale(weight[i]*sf);
	  set.Mmumu[i]->Scale(weight[i]*sf);
	  set.LEPPt[i]->Scale(weight[i]*sf);
	  set.LEP1Pt[i]->Scale(weight[i]*sf);
	  set.LEP2Pt[i]->Scale(weight[i]*sf);
	  set.LEP3Pt[i]->Scale(weight[i]*sf);
	  set.LEPChargeSum[i]->Scale(weight[i]*sf);
	  if(reduced){
		set.lep_softest_pt[i]->Scale(weight[i]*sf);}
	}
  }
  return;
}

//-----------------------------------------------------------------------------

void buildStack(distrSet& set) {

  buildAStack(set.ST_NJETS, set.NJETS, &set.syst_tag);
  if(!test_me){
	buildAStack(set.ST_pt_jet1, set.pt_jet1, &set.syst_tag);
	buildAStack(set.ST_pt_jet2, set.pt_jet2, &set.syst_tag);
	buildAStack(set.ST_pt_jet3, set.pt_jet3, &set.syst_tag);
	if(reduced){
	  buildAStack(set.ST_pt_jet4, set.pt_jet4, &set.syst_tag);
	  buildAStack(set.ST_pt_jet5, set.pt_jet5, &set.syst_tag);
	}
	buildAStack(set.ST_NBJETS, set.NBJETS, &set.syst_tag);
	buildAStack(set.ST_pt_bjet1, set.pt_bjet1, &set.syst_tag);
	buildAStack(set.ST_pt_bjet2, set.pt_bjet2, &set.syst_tag);
	buildAStack(set.ST_pt_bjet3, set.pt_bjet3, &set.syst_tag);
	if(reduced){
	  buildAStack(set.ST_pt_bjet4, set.pt_bjet4, &set.syst_tag);
	}
	buildAStack(set.ST_mu1_pt, set.mu1_pt, &set.syst_tag);
	buildAStack(set.ST_mu2_pt, set.mu2_pt, &set.syst_tag);
	buildAStack(set.ST_mu3_pt, set.mu3_pt, &set.syst_tag);
	buildAStack(set.ST_mu_eta, set.mu_eta, &set.syst_tag);
	buildAStack(set.ST_el1_pt, set.el1_pt, &set.syst_tag);
	buildAStack(set.ST_el2_pt, set.el2_pt, &set.syst_tag);
	buildAStack(set.ST_el3_pt, set.el3_pt, &set.syst_tag);
	buildAStack(set.ST_el_eta, set.el_eta, &set.syst_tag);
	buildAStack(set.ST_MET, set.MET, &set.syst_tag);
	buildAStack(set.ST_HT, set.HT, &set.syst_tag);
	buildAStack(set.ST_Meff, set.Meff, &set.syst_tag);
	buildAStack(set.ST_mT, set.mT, &set.syst_tag);
	buildAStack(set.ST_mT_min, set.mT_min, &set.syst_tag);
	if(reduced){
	  buildAStack(set.ST_MZ, set.MZ, &set.syst_tag);
	  buildAStack(set.ST_Mlll, set.Mlll, &set.syst_tag);
	}
	buildAStack(set.ST_Mee, set.Mee, &set.syst_tag);
	buildAStack(set.ST_Mmumu, set.Mmumu, &set.syst_tag);
	buildAStack(set.ST_LEPPt, set.LEPPt, &set.syst_tag);
	buildAStack(set.ST_LEP1Pt, set.LEP1Pt, &set.syst_tag);
	buildAStack(set.ST_LEP2Pt, set.LEP2Pt, &set.syst_tag);
	buildAStack(set.ST_LEP3Pt, set.LEP3Pt, &set.syst_tag);
	buildAStack(set.ST_LEPChargeSum, set.LEPChargeSum, &set.syst_tag);
	if(reduced){
	  buildAStack(set.ST_lep_softest_pt, set.lep_softest_pt, &set.syst_tag);}
  }
  return;
}

//-----------------------------------------------------------------------------

void buildAStack(THStack* &st, TH1D* hist[N_FAKE], string *syst_tag) {
  /*
  //We build Stacked plots here
  char my_name[256];
  sprintf(my_name, "HSTACK_%s%s", hist[0]->GetName(), syst_tag->data());
  st = new THStack(my_name, "Hstack");
  
  // Sort histograms before building the stack
  std::list <TH1D*> mc_hists;
  for (int i = 1; i < N_FAKE; i++) {
  mc_hists.push_back(hist[i]);
  }
  mc_hists.sort(hasLessEvents);
  std::list<TH1D*>::const_iterator iterator;
  for(  iterator = mc_hists.begin(); iterator != mc_hists.end(); ++iterator)
  st->Add(*iterator);
  */

  //We build Stacked plots here                                                                                                                             
  char my_name[256];
  sprintf(my_name, "HSTACK_%s%s", hist[0]->GetName(), syst_tag->data());
  st = new THStack(my_name, "Hstack");

  for (int i = 1; i < N_FAKE; i++) {
	st->Add(hist[i]);
  }


  st->Draw("hist");
  st->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
  st->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());

  return;
}  

//-----------------------------------------------------------------------------

bool hasLessEvents(TH1*h1,TH1*h2){
  double n1=h1->Integral(1,h1->GetNbinsX());
  double n2=h2->Integral(1,h2->GetNbinsX());
  return n1<n2;
}

//-----------------------------------------------------------------------------

bool hasLessEventspair(std::pair<string,TH1D*> h1, std::pair<string,TH1D*> h2){
  double n1=h1.second->Integral(1,h1.second->GetNbinsX());
  double n2=h2.second->Integral(1,h2.second->GetNbinsX());
  return n1<n2;
}

//-----------------------------------------------------------------------------

void draw_All(distrAll &set, distrSigAll &sig, distrAll* paired[N_unc_paired], distrAll* unpaired[N_unc_unpaired], const char* fit){

  distrSignature* paired_SS3L[N_unc_paired];
  distrSignature* unpaired_SS3L[N_unc_unpaired];
  distrSignature* paired_OS[N_unc_paired];
  distrSignature* unpaired_OS[N_unc_unpaired];
  distrSignature* paired_SS[N_unc_paired];
  distrSignature* unpaired_SS[N_unc_unpaired];
  /*	  distrSignature* paired_L3[N_unc_paired];
		  distrSignature* unpaired_L3[N_unc_unpaired];*/

  for (int j = 0; j < N_unc_paired; j++) {
    distrAll* temp_set = paired[j];
	paired_SS3L[j] = (&(temp_set->SS3L));
	paired_OS[j] = (&(temp_set->OS));
	paired_SS[j] = (&(temp_set->SS));
	/*	paired_L3[j] = (&(temp_set->L3));*/
  }

  for (int j = 0; j < N_unc_unpaired; j++) {
    distrAll* temp_set = unpaired[j];
	unpaired_SS3L[j] = (&(temp_set->SS3L));
	unpaired_OS[j] = (&(temp_set->OS));
	unpaired_SS[j] = (&(temp_set->SS));
	/*	unpaired_L3[j] = (&(temp_set->L3));*/
  }

  draw_Signature(set.SS3L, sig.SS3L, paired_SS3L, unpaired_SS3L, fit);
  //  draw_Signature(set.OS, sig.OS, paired_OS, unpaired_OS, fit);
  //  draw_Signature(set.SS, sig.SS, paired_SS, unpaired_SS, fit);
  /*	  draw_Signature(set.L3, sig.L3, paired_L3, unpaired_L3, fit);*/

  return;
}

//-----------------------------------------------------------------------------

void draw_Signature(distrSignature &set, distrSigSignature &sig, distrSignature* paired[N_unc_paired], distrSignature* unpaired[N_unc_unpaired], const char* fit){

  distrRegion* paired_Incl[N_unc_paired];
  distrRegion* unpaired_Incl[N_unc_unpaired];
  distrRegion* paired_PRE[N_unc_paired];
  distrRegion* unpaired_PRE[N_unc_unpaired];
  distrRegion* paired_CR0b[N_unc_paired];
  distrRegion* unpaired_CR0b[N_unc_unpaired];
  distrRegion* paired_CR1b[N_unc_paired];
  distrRegion* unpaired_CR1b[N_unc_unpaired];
  distrRegion* paired_SR3L1[N_unc_paired];
  distrRegion* unpaired_SR3L1[N_unc_unpaired];
  distrRegion* paired_SR3L2[N_unc_paired];
  distrRegion* unpaired_SR3L2[N_unc_unpaired];
  distrRegion* paired_SR0b1[N_unc_paired];
  distrRegion* unpaired_SR0b1[N_unc_unpaired];
  distrRegion* paired_SR0b2[N_unc_paired];
  distrRegion* unpaired_SR0b2[N_unc_unpaired];
  distrRegion* paired_SR1b[N_unc_paired];
  distrRegion* unpaired_SR1b[N_unc_unpaired];
  distrRegion* paired_SR3b[N_unc_paired];
  distrRegion* unpaired_SR3b[N_unc_unpaired];
  distrRegion* paired_SR1b_DD[N_unc_paired];
  distrRegion* unpaired_SR1b_DD[N_unc_unpaired];
  distrRegion* paired_SR3b_DD[N_unc_paired];
  distrRegion* unpaired_SR3b_DD[N_unc_unpaired];
  distrRegion* paired_SR1b_GG[N_unc_paired];
  distrRegion* unpaired_SR1b_GG[N_unc_unpaired];
  distrRegion* paired_SR0b5j[N_unc_paired];
  distrRegion* unpaired_SR0b5j[N_unc_unpaired];
  distrRegion* paired_SR2b1[N_unc_paired];
  distrRegion* unpaired_SR2b1[N_unc_unpaired];
  distrRegion* paired_SR2b2[N_unc_paired];
  distrRegion* unpaired_SR2b2[N_unc_unpaired];
  distrRegion* paired_SR3L3b[N_unc_paired];
  distrRegion* unpaired_SR3L3b[N_unc_unpaired];
  distrRegion* paired_VRWW[N_unc_paired];
  distrRegion* unpaired_VRWW[N_unc_unpaired];
  distrRegion* paired_VRWZ4j[N_unc_paired];
  distrRegion* unpaired_VRWZ4j[N_unc_unpaired];
  distrRegion* paired_VRWZ5j[N_unc_paired];
  distrRegion* unpaired_VRWZ5j[N_unc_unpaired];
  distrRegion* paired_VRttW[N_unc_paired];
  distrRegion* unpaired_VRttW[N_unc_unpaired];
  distrRegion* paired_VRttZ[N_unc_paired];
  distrRegion* unpaired_VRttZ[N_unc_unpaired];

  for (int j = 0; j < N_unc_paired; j++) {
    distrSignature* temp_set = paired[j];
	/*	paired_Incl[j] = (&(temp_set->Incl));
	paired_PRE[j] = (&(temp_set->PRE));
	paired_CR0b[j] = (&(temp_set->CR0b));
	paired_CR1b[j] = (&(temp_set->CR1b));*/
	paired_SR3L1[j] = (&(temp_set->SR3L1));
	paired_SR3L2[j] = (&(temp_set->SR3L2));
	paired_SR0b1[j] = (&(temp_set->SR0b1));
	paired_SR0b2[j] = (&(temp_set->SR0b2));
	paired_SR1b[j] = (&(temp_set->SR1b));
	paired_SR3b[j] = (&(temp_set->SR3b));
	paired_SR1b_DD[j] = (&(temp_set->SR1b_DD));
	paired_SR3b_DD[j] = (&(temp_set->SR3b_DD));
	paired_SR1b_GG[j] = (&(temp_set->SR1b_GG));
	paired_VRWW[j] = (&(temp_set->VRWW));
	paired_VRWZ4j[j] = (&(temp_set->VRWZ4j));	
	paired_VRWZ5j[j] = (&(temp_set->VRWZ5j));
	paired_VRttW[j] = (&(temp_set->VRttW));
	paired_VRttZ[j] = (&(temp_set->VRttZ));

	/*paired_SR0b5j[j] = (&(temp_set->SR0b5j));
	  paired_SR2b1[j] = (&(temp_set->SR2b1));
	  paired_SR2b2[j] = (&(temp_set->SR2b2));
	  paired_SR3L3b[j] = (&(temp_set->SR3L3b));*/

  }

  for (int j = 0; j < N_unc_unpaired; j++) {
    distrSignature* temp_set = unpaired[j];
	/*	unpaired_Incl[j] = (&(temp_set->Incl));
	unpaired_PRE[j] = (&(temp_set->PRE));
	unpaired_CR0b[j] = (&(temp_set->CR0b));
	unpaired_CR1b[j] = (&(temp_set->CR1b));*/
	unpaired_SR3L1[j] = (&(temp_set->SR3L1));
	unpaired_SR3L2[j] = (&(temp_set->SR3L2));
	unpaired_SR0b1[j] = (&(temp_set->SR0b1));
	unpaired_SR0b2[j] = (&(temp_set->SR0b2));
	unpaired_SR1b[j] = (&(temp_set->SR1b));
	unpaired_SR3b[j] = (&(temp_set->SR3b));
	unpaired_SR1b_DD[j] = (&(temp_set->SR1b_DD));
	unpaired_SR3b_DD[j] = (&(temp_set->SR3b_DD));
	unpaired_SR1b_GG[j] = (&(temp_set->SR1b_GG));
	unpaired_VRWW[j] = (&(temp_set->VRWW));
	unpaired_VRWZ4j[j] = (&(temp_set->VRWZ4j));
	unpaired_VRWZ5j[j] = (&(temp_set->VRWZ5j));
	unpaired_VRttW[j] = (&(temp_set->VRttW));
	unpaired_VRttZ[j] = (&(temp_set->VRttZ));

	/*
	  unpaired_SR0b5j[j] = (&(temp_set->SR0b5j));
	  unpaired_SR2b1[j] = (&(temp_set->SR2b1));
	  unpaired_SR2b2[j] = (&(temp_set->SR2b2));
	  unpaired_SR3L3b[j] = (&(temp_set->SR3L3b));
	*/

  }

  /*  draw_Region(set.Incl, sig.Incl, paired_Incl, unpaired_Incl, fit);
  draw_Region(set.PRE, sig.PRE, paired_PRE, unpaired_PRE, fit);
  draw_Region(set.CR0b, sig.CR0b, paired_CR0b, unpaired_CR0b, fit);
  draw_Region(set.CR1b, sig.CR1b, paired_CR1b, unpaired_CR1b, fit);*/
  draw_Region(set.SR3L1, sig.SR3L1, paired_SR3L1, unpaired_SR3L1, fit);
  draw_Region(set.SR3L2, sig.SR3L2, paired_SR3L2, unpaired_SR3L2, fit);
  draw_Region(set.SR0b1, sig.SR0b1, paired_SR0b1, unpaired_SR0b1, fit);
  draw_Region(set.SR0b2, sig.SR0b2, paired_SR0b2, unpaired_SR0b2, fit);
  draw_Region(set.SR1b, sig.SR1b, paired_SR1b, unpaired_SR1b, fit);
  draw_Region(set.SR3b, sig.SR3b, paired_SR3b, unpaired_SR3b, fit);
  draw_Region(set.SR1b_DD, sig.SR1b_DD, paired_SR1b_DD, unpaired_SR1b_DD, fit);
  draw_Region(set.SR3b_DD, sig.SR3b_DD, paired_SR3b_DD, unpaired_SR3b_DD, fit);
  draw_Region(set.SR1b_GG, sig.SR1b_GG, paired_SR1b_GG, unpaired_SR1b_GG, fit);
  draw_Region(set.VRWW, sig.VRWW, paired_VRWW, unpaired_VRWW, fit);
  draw_Region(set.VRWZ4j, sig.VRWZ4j, paired_VRWZ4j, unpaired_VRWZ4j, fit);
  draw_Region(set.VRWZ5j, sig.VRWZ5j, paired_VRWZ5j, unpaired_VRWZ5j, fit);
  draw_Region(set.VRttW, sig.VRttW, paired_VRttW, unpaired_VRttW, fit);
  draw_Region(set.VRttZ, sig.VRttZ, paired_VRttZ, unpaired_VRttZ, fit);

  /*draw_Region(set.SR0b5j, sig.SR0b5j, paired_SR0b5j, unpaired_SR0b5j, fit);
	draw_Region(set.SR2b1, sig.SR2b1, paired_SR2b1, unpaired_SR2b1, fit);
	draw_Region(set.SR2b2, sig.SR2b2, paired_SR2b2, unpaired_SR2b2, fit);
	draw_Region(set.SR3L3b, sig.SR3L3b, paired_SR3L3b, unpaired_SR3L3b, fit);*/

  return;
}

//-----------------------------------------------------------------------------

void draw_Region(distrRegion &set, distrSigRegion &sig,distrRegion* paired[N_unc_paired], distrRegion* unpaired[N_unc_unpaired], const char* fit){

  distrSet *paired_elel[N_unc_paired];
  distrSet *paired_elmu[N_unc_paired];
  distrSet *paired_mumu[N_unc_paired];
  distrSet *paired_3l[N_unc_paired];
  distrSet *paired_comb[N_unc_paired];

  distrSet *unpaired_elel[N_unc_unpaired];
  distrSet *unpaired_elmu[N_unc_unpaired];
  distrSet *unpaired_mumu[N_unc_unpaired];
  distrSet *unpaired_3l[N_unc_unpaired];
  distrSet *unpaired_comb[N_unc_unpaired];

  for (int j = 0; j < N_unc_paired; j++) {
    distrRegion* temp_set = (distrRegion*) paired[j];
	paired_elel[j] = &(temp_set->fs_elel);
    paired_elmu[j] = &(temp_set->fs_elmu);
    paired_mumu[j] = &(temp_set->fs_mumu);
	//    paired_3l[j] = &(temp_set->fs_3l);
    paired_comb[j] = &(temp_set->fs_comb);
  }

  for (int j = 0; j < N_unc_unpaired; j++) {
    distrRegion* temp_set = (distrRegion*) unpaired[j];
	unpaired_elel[j] = &(temp_set->fs_elel);
    unpaired_elmu[j] = &(temp_set->fs_elmu);
    unpaired_mumu[j] = &(temp_set->fs_mumu);
	//    unpaired_3l[j] = &(temp_set->fs_3l);
    unpaired_comb[j] = &(temp_set->fs_comb);
  }

  draw_Set(set.fs_elel, sig.fs_elel, paired_elel, unpaired_elel, fit);
  draw_Set(set.fs_elmu, sig.fs_elmu, paired_elmu, unpaired_elmu, fit);
  draw_Set(set.fs_mumu, sig.fs_mumu, paired_mumu, unpaired_mumu, fit);
  //  draw_Set(set.fs_3l, sig.fs_3l, paired_3l, unpaired_3l, fit);
  draw_Set(set.fs_comb, sig.fs_comb, paired_comb, unpaired_comb, fit);

  return;
}

//-----------------------------------------------------------------------------

void draw_Set(distrSet &set, distrSigSet &sig,  distrSet* paired[N_unc_paired], distrSet* unpaired[N_unc_unpaired], const char* fit){

  TObjArray *paired_NJETS = new TObjArray(N_unc_paired);
  TObjArray *unpaired_NJETS = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_jet1 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_jet1 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_jet2 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_jet2 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_jet3 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_jet3 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_jet4 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_jet4 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_jet5 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_jet5 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_NBJETS = new TObjArray(N_unc_paired);
  TObjArray *unpaired_NBJETS = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_bjet1 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_bjet1 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_bjet2 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_bjet2 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_bjet3 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_bjet3 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_bjet4 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_bjet4 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mu1_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mu1_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mu2_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mu2_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mu3_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mu3_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mu_eta = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mu_eta = new TObjArray(N_unc_unpaired);
  TObjArray *paired_el1_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_el1_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_el2_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_el2_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_el3_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_el3_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_el_eta = new TObjArray(N_unc_paired);
  TObjArray *unpaired_el_eta = new TObjArray(N_unc_unpaired);
  TObjArray *paired_MET = new TObjArray(N_unc_paired);
  TObjArray *unpaired_MET = new TObjArray(N_unc_unpaired);
  TObjArray *paired_HT = new TObjArray(N_unc_paired);
  TObjArray *unpaired_HT = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Meff = new TObjArray(N_unc_paired);
  TObjArray *unpaired_Meff = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mT = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mT = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mT_min = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mT_min = new TObjArray(N_unc_unpaired);
  TObjArray *paired_MZ = new TObjArray(N_unc_paired);
  TObjArray *unpaired_MZ = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Mlll = new TObjArray(N_unc_paired);
  TObjArray *unpaired_Mlll = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Mee = new TObjArray(N_unc_paired);
  TObjArray *unpaired_Mee = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Mmumu = new TObjArray(N_unc_paired);
  TObjArray *unpaired_Mmumu = new TObjArray(N_unc_unpaired);
  TObjArray *paired_LEPPt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_LEPPt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_LEP1Pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_LEP1Pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_LEP2Pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_LEP2Pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_LEP3Pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_LEP3Pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_LEPChargeSum = new TObjArray(N_unc_paired);
  TObjArray *unpaired_LEPChargeSum = new TObjArray(N_unc_unpaired);
  TObjArray *paired_lep_softest_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_lep_softest_pt = new TObjArray(N_unc_unpaired);
  
  for (int j = 0; j < N_unc_paired; j++) {
	distrSet* temp_set = paired[j];

	paired_NJETS->Add(temp_set->ST_NJETS);
	if(!test_me){
	  paired_pt_jet1->Add(temp_set->ST_pt_jet1);
	  paired_pt_jet2->Add(temp_set->ST_pt_jet2);
	  paired_pt_jet3->Add(temp_set->ST_pt_jet3);
	  if(reduced){
		paired_pt_jet4->Add(temp_set->ST_pt_jet4);
		paired_pt_jet5->Add(temp_set->ST_pt_jet5);
	  }
	  paired_NBJETS->Add(temp_set->ST_NBJETS);
	  paired_pt_bjet1->Add(temp_set->ST_pt_bjet1);
	  paired_pt_bjet2->Add(temp_set->ST_pt_bjet2);
	  paired_pt_bjet3->Add(temp_set->ST_pt_bjet3);
	  if(reduced){
		paired_pt_bjet4->Add(temp_set->ST_pt_bjet4);
	  }
	  paired_mu1_pt->Add(temp_set->ST_mu1_pt);
	  paired_mu2_pt->Add(temp_set->ST_mu2_pt);
	  paired_mu3_pt->Add(temp_set->ST_mu3_pt);
	  paired_mu_eta->Add(temp_set->ST_mu_eta);
	  paired_el1_pt->Add(temp_set->ST_el1_pt);
	  paired_el2_pt->Add(temp_set->ST_el2_pt);
	  paired_el3_pt->Add(temp_set->ST_el3_pt);
	  paired_el_eta->Add(temp_set->ST_el_eta);
	  paired_MET->Add(temp_set->ST_MET);
	  paired_HT->Add(temp_set->ST_HT);
	  paired_Meff->Add(temp_set->ST_Meff);
	  paired_mT->Add(temp_set->ST_mT);
	  paired_mT_min->Add(temp_set->ST_mT_min);
	  if(reduced){
		paired_MZ->Add(temp_set->ST_MZ);
		paired_Mlll->Add(temp_set->ST_Mlll);
	  }
	  paired_Mee->Add(temp_set->ST_Mee);
	  paired_Mmumu->Add(temp_set->ST_Mmumu);
	  paired_LEPPt->Add(temp_set->ST_LEPPt);
	  paired_LEP1Pt->Add(temp_set->ST_LEP1Pt);
	  paired_LEP2Pt->Add(temp_set->ST_LEP2Pt);
	  paired_LEP3Pt->Add(temp_set->ST_LEP3Pt);
	  paired_LEPChargeSum->Add(temp_set->ST_LEPChargeSum);
	  if(reduced){
		paired_lep_softest_pt->Add(temp_set->ST_lep_softest_pt);}
	}
  }

  for (int j = 0; j < N_unc_unpaired; j++) {
	distrSet* temp_set = unpaired[j];
	unpaired_NJETS->Add(temp_set->ST_NJETS);
	if(!test_me){
	  unpaired_pt_jet1->Add(temp_set->ST_pt_jet1);
	  unpaired_pt_jet2->Add(temp_set->ST_pt_jet2);
	  unpaired_pt_jet3->Add(temp_set->ST_pt_jet3);
	  if(reduced){
		unpaired_pt_jet4->Add(temp_set->ST_pt_jet4);
		unpaired_pt_jet5->Add(temp_set->ST_pt_jet5);
	  }
	  unpaired_NBJETS->Add(temp_set->ST_NBJETS);
	  unpaired_pt_bjet1->Add(temp_set->ST_pt_bjet1);
	  unpaired_pt_bjet2->Add(temp_set->ST_pt_bjet2);
	  unpaired_pt_bjet3->Add(temp_set->ST_pt_bjet3);
	  if(reduced){
		unpaired_pt_bjet4->Add(temp_set->ST_pt_bjet4);
	  }
	  unpaired_mu1_pt->Add(temp_set->ST_mu1_pt);
	  unpaired_mu2_pt->Add(temp_set->ST_mu2_pt);
	  unpaired_mu3_pt->Add(temp_set->ST_mu3_pt);
	  unpaired_mu_eta->Add(temp_set->ST_mu_eta);
	  unpaired_el1_pt->Add(temp_set->ST_el1_pt);
	  unpaired_el2_pt->Add(temp_set->ST_el2_pt);
	  unpaired_el3_pt->Add(temp_set->ST_el3_pt);
	  unpaired_el_eta->Add(temp_set->ST_el_eta);
	  unpaired_MET->Add(temp_set->ST_MET);
	  unpaired_HT->Add(temp_set->ST_HT);
	  unpaired_Meff->Add(temp_set->ST_Meff);
	  unpaired_mT->Add(temp_set->ST_mT);
	  unpaired_mT_min->Add(temp_set->ST_mT_min);
	  if(reduced){
		unpaired_MZ->Add(temp_set->ST_MZ);
		unpaired_Mlll->Add(temp_set->ST_Mlll);
	  }
	  unpaired_Mee->Add(temp_set->ST_Mee);
	  unpaired_Mmumu->Add(temp_set->ST_Mmumu);
	  unpaired_LEPPt->Add(temp_set->ST_LEPPt);
	  unpaired_LEP1Pt->Add(temp_set->ST_LEP1Pt);
	  unpaired_LEP2Pt->Add(temp_set->ST_LEP2Pt);
	  unpaired_LEP3Pt->Add(temp_set->ST_LEP3Pt);
	  unpaired_LEPChargeSum->Add(temp_set->ST_LEPChargeSum);
	  if(reduced){
		unpaired_lep_softest_pt->Add(temp_set->ST_lep_softest_pt);}
	}
  }

  //  drawAVariable_test(set.ST_NJETS, set.NJETS, sig.NJETS, paired_NJETS, unpaired_NJETS, fit);
  drawAVariable_all(set.ST_NJETS, set.NJETS, sig.NJETS, paired_NJETS, unpaired_NJETS, fit);

  //  drawAVariable_normalized(set.ST_NJETS, set.NJETS, sig.NJETS, paired_NJETS, unpaired_NJETS, fit);
  //  drawAVariable_merged(set.ST_NJETS, set.NJETS, sig.NJETS, paired_NJETS, unpaired_NJETS, fit);
  if(!test_me){
	drawAVariable_all(set.ST_pt_jet1, set.pt_jet1, sig.pt_jet1, paired_pt_jet1, unpaired_pt_jet1, fit);
	//drawAVariable_merged(set.ST_pt_jet1, set.pt_jet1, sig.pt_jet1, paired_pt_jet1, unpaired_pt_jet1, fit);
	drawAVariable_all(set.ST_pt_jet2, set.pt_jet2, sig.pt_jet2, paired_pt_jet2, unpaired_pt_jet2, fit);
	//drawAVariable_merged(set.ST_pt_jet2, set.pt_jet2, sig.pt_jet2, paired_pt_jet2, unpaired_pt_jet2, fit);
	drawAVariable_all(set.ST_pt_jet3, set.pt_jet3, sig.pt_jet3, paired_pt_jet3, unpaired_pt_jet3, fit);
	//drawAVariable_merged(set.ST_pt_jet3, set.pt_jet3, sig.pt_jet3, paired_pt_jet3, unpaired_pt_jet3, fit);
	if(reduced){
	  drawAVariable_all(set.ST_pt_jet4, set.pt_jet4, sig.pt_jet4, paired_pt_jet4, unpaired_pt_jet4, fit);
	  //drawAVariable_merged(set.ST_pt_jet4, set.pt_jet4, sig.pt_jet4, paired_pt_jet4, unpaired_pt_jet4, fit);
	  drawAVariable_all(set.ST_pt_jet5, set.pt_jet5, sig.pt_jet5, paired_pt_jet5, unpaired_pt_jet5, fit);
	  //drawAVariable_merged(set.ST_pt_jet5, set.pt_jet5, sig.pt_jet5, paired_pt_jet5, unpaired_pt_jet5, fit);
	}
	drawAVariable_all(set.ST_NBJETS, set.NBJETS, sig.NBJETS, paired_NBJETS, unpaired_NBJETS, fit);
	//drawAVariable_merged(set.ST_NBJETS, set.NBJETS, sig.NBJETS, paired_NBJETS, unpaired_NBJETS, fit);
	drawAVariable_all(set.ST_pt_bjet1, set.pt_bjet1, sig.pt_bjet1, paired_pt_bjet1, unpaired_pt_bjet1, fit);
	//drawAVariable_merged(set.ST_pt_bjet1, set.pt_bjet1, sig.pt_bjet1, paired_pt_bjet1, unpaired_pt_bjet1, fit);
	drawAVariable_all(set.ST_pt_bjet2, set.pt_bjet2, sig.pt_bjet2, paired_pt_bjet2, unpaired_pt_bjet2, fit);
	//drawAVariable_merged(set.ST_pt_bjet2, set.pt_bjet2, sig.pt_bjet2, paired_pt_bjet2, unpaired_pt_bjet2, fit);
	drawAVariable_all(set.ST_pt_bjet3, set.pt_bjet3, sig.pt_bjet3, paired_pt_bjet3, unpaired_pt_bjet3, fit);
	//drawAVariable_merged(set.ST_pt_bjet3, set.pt_bjet3, sig.pt_bjet3, paired_pt_bjet3, unpaired_pt_bjet3, fit);
	if(reduced){
	  drawAVariable_all(set.ST_pt_bjet4, set.pt_bjet4, sig.pt_bjet4, paired_pt_bjet4, unpaired_pt_bjet4, fit);
	  //drawAVariable_merged(set.ST_pt_bjet4, set.pt_bjet4, sig.pt_bjet4, paired_pt_bjet4, unpaired_pt_bjet4, fit);
	}
	drawAVariable_all(set.ST_mu1_pt, set.mu1_pt, sig.mu1_pt, paired_mu1_pt, unpaired_mu1_pt, fit);
	//drawAVariable_merged(set.ST_mu1_pt, set.mu1_pt, sig.mu1_pt, paired_mu1_pt, unpaired_mu1_pt, fit);
	drawAVariable_all(set.ST_mu2_pt, set.mu2_pt, sig.mu2_pt, paired_mu2_pt, unpaired_mu2_pt, fit);
	//drawAVariable_merged(set.ST_mu2_pt, set.mu2_pt, sig.mu2_pt, paired_mu2_pt, unpaired_mu2_pt, fit);
	drawAVariable_all(set.ST_mu3_pt, set.mu3_pt, sig.mu3_pt, paired_mu3_pt, unpaired_mu3_pt, fit);
	//drawAVariable_merged(set.ST_mu3_pt, set.mu3_pt, sig.mu3_pt, paired_mu3_pt, unpaired_mu3_pt, fit);
	drawAVariable_all(set.ST_mu_eta, set.mu_eta, sig.mu_eta, paired_mu_eta, unpaired_mu_eta, fit);
	//drawAVariable_merged(set.ST_mu_eta, set.mu_eta, sig.mu_eta, paired_mu_eta, unpaired_mu_eta, fit);
	drawAVariable_all(set.ST_el1_pt, set.el1_pt, sig.el1_pt, paired_el1_pt, unpaired_el1_pt, fit);
	//drawAVariable_merged(set.ST_el1_pt, set.el1_pt, sig.el1_pt, paired_el1_pt, unpaired_el1_pt, fit);
	drawAVariable_all(set.ST_el2_pt, set.el2_pt, sig.el2_pt, paired_el2_pt, unpaired_el2_pt, fit);
	//drawAVariable_merged(set.ST_el2_pt, set.el2_pt, sig.el2_pt, paired_el2_pt, unpaired_el2_pt, fit);
	drawAVariable_all(set.ST_el3_pt, set.el3_pt, sig.el3_pt, paired_el3_pt, unpaired_el3_pt, fit);
	//drawAVariable_merged(set.ST_el3_pt, set.el3_pt, sig.el3_pt, paired_el3_pt, unpaired_el3_pt, fit);
	drawAVariable_all(set.ST_el_eta, set.el_eta, sig.el_eta, paired_el_eta, unpaired_el_eta, fit);
	//drawAVariable_merged(set.ST_el_eta, set.el_eta, sig.el_eta, paired_el_eta, unpaired_el_eta, fit);
	drawAVariable_all(set.ST_MET, set.MET, sig.MET, paired_MET, unpaired_MET, fit);
	//drawAVariable_merged(set.ST_MET, set.MET, sig.MET, paired_MET, unpaired_MET, fit);
	drawAVariable_all(set.ST_HT, set.HT, sig.HT, paired_HT, unpaired_HT, fit);
	//drawAVariable_merged(set.ST_HT, set.HT, sig.HT, paired_HT, unpaired_HT, fit);
	drawAVariable_all(set.ST_Meff, set.Meff, sig.Meff, paired_Meff, unpaired_Meff, fit);
	//drawAVariable_merged(set.ST_Meff, set.Meff, sig.Meff, paired_Meff, unpaired_Meff, fit);
	drawAVariable_all(set.ST_mT, set.mT, sig.mT, paired_mT, unpaired_mT, fit);
	//drawAVariable_merged(set.ST_mT, set.mT, sig.mT, paired_mT, unpaired_mT, fit);
	drawAVariable_all(set.ST_mT_min, set.mT_min, sig.mT_min, paired_mT_min, unpaired_mT_min, fit);
	//drawAVariable_merged(set.ST_mT_min, set.mT_min, sig.mT_min, paired_mT_min, unpaired_mT_min, fit);
	if(reduced){
	  drawAVariable_all(set.ST_MZ, set.MZ, sig.MZ, paired_MZ, unpaired_MZ, fit);
	  //drawAVariable_merged(set.ST_MZ, set.MZ, sig.MZ, paired_MZ, unpaired_MZ, fit);
	  drawAVariable_all(set.ST_Mlll, set.Mlll, sig.Mlll, paired_Mlll, unpaired_Mlll, fit);
	  //drawAVariable_merged(set.ST_Mlll, set.Mlll, sig.Mlll, paired_Mlll, unpaired_Mlll, fit);
	}
	drawAVariable_all(set.ST_Mee, set.Mee, sig.Mee, paired_Mee, unpaired_Mee, fit);
	//drawAVariable_merged(set.ST_Mee, set.Mee, sig.Mee, paired_Mee, unpaired_Mee, fit);
	drawAVariable_all(set.ST_Mmumu, set.Mmumu, sig.Mmumu, paired_Mmumu, unpaired_Mmumu, fit);
	//drawAVariable_merged(set.ST_Mmumu, set.Mmumu, sig.Mmumu, paired_Mmumu, unpaired_Mmumu, fit);
	drawAVariable_all(set.ST_LEPPt, set.LEPPt, sig.LEPPt, paired_LEPPt, unpaired_LEPPt, fit);
	//drawAVariable_merged(set.ST_LEPPt, set.LEPPt, sig.LEPPt, paired_LEPPt, unpaired_LEPPt, fit);
	drawAVariable_all(set.ST_LEP1Pt, set.LEP1Pt, sig.LEP1Pt, paired_LEP1Pt, unpaired_LEP1Pt, fit);
	//drawAVariable_merged(set.ST_LEP1Pt, set.LEP1Pt, sig.LEP1Pt, paired_LEP1Pt, unpaired_LEP1Pt, fit);
	drawAVariable_all(set.ST_LEP2Pt, set.LEP2Pt, sig.LEP2Pt, paired_LEP2Pt, unpaired_LEP2Pt, fit);
	//drawAVariable_merged(set.ST_LEP2Pt, set.LEP2Pt, sig.LEP2Pt, paired_LEP2Pt, unpaired_LEP2Pt, fit);
	drawAVariable_all(set.ST_LEP3Pt, set.LEP3Pt, sig.LEP3Pt, paired_LEP3Pt, unpaired_LEP3Pt, fit);
	//drawAVariable_merged(set.ST_LEP3Pt, set.LEP3Pt, sig.LEP3Pt, paired_LEP3Pt, unpaired_LEP3Pt, fit);
	drawAVariable_all(set.ST_LEPChargeSum, set.LEPChargeSum, sig.LEPChargeSum, paired_LEPChargeSum, unpaired_LEPChargeSum, fit);
	//drawAVariable_merged(set.ST_LEPChargeSum, set.LEPChargeSum, sig.LEPChargeSum, paired_LEPChargeSum, unpaired_LEPChargeSum, fit);
	if(reduced){
	  drawAVariable_all(set.ST_lep_softest_pt, set.lep_softest_pt, sig.lep_softest_pt, paired_lep_softest_pt, unpaired_lep_softest_pt, fit);
	  //drawAVariable_merged(set.ST_lep_softest_pt, set.lep_softest_pt, sig.lep_softest_pt, paired_lep_softest_pt, unpaired_lep_softest_pt, fit);
	}
  }    

  CalcBackgrounds(set.NJETS, paired_NJETS, unpaired_NJETS, set);

  delete paired_NJETS;
  delete unpaired_NJETS;
  delete paired_pt_jet1;
  delete unpaired_pt_jet1;
  delete paired_pt_jet2;
  delete unpaired_pt_jet2;
  delete paired_pt_jet3;
  delete unpaired_pt_jet3;
  delete paired_pt_jet4;
  delete unpaired_pt_jet4;
  delete paired_pt_jet5;
  delete unpaired_pt_jet5;
  delete paired_NBJETS;
  delete unpaired_NBJETS;
  delete paired_pt_bjet1;
  delete unpaired_pt_bjet1;
  delete paired_pt_bjet2;
  delete unpaired_pt_bjet2;
  delete paired_pt_bjet3;
  delete unpaired_pt_bjet3;
  delete paired_pt_bjet4;
  delete unpaired_pt_bjet4;
  delete paired_mu1_pt;
  delete unpaired_mu1_pt;
  delete paired_mu2_pt;
  delete unpaired_mu2_pt;
  delete paired_mu3_pt;
  delete unpaired_mu3_pt;
  delete paired_mu_eta;
  delete unpaired_mu_eta;
  delete paired_el1_pt;
  delete unpaired_el1_pt;
  delete paired_el2_pt;
  delete unpaired_el2_pt;
  delete paired_el3_pt;
  delete unpaired_el3_pt;
  delete paired_el_eta;
  delete unpaired_el_eta;
  delete paired_MET;
  delete unpaired_MET;
  delete paired_HT;
  delete unpaired_HT;
  delete paired_Meff;
  delete unpaired_Meff;
  delete paired_mT;
  delete unpaired_mT;
  delete paired_mT_min;
  delete unpaired_mT_min;
  delete paired_MZ;
  delete unpaired_MZ;
  delete paired_Mlll;
  delete unpaired_Mlll;
  delete paired_Mee;
  delete unpaired_Mee;
  delete paired_Mmumu;
  delete unpaired_Mmumu;
  delete paired_LEPPt;
  delete unpaired_LEPPt;
  delete paired_LEP1Pt;
  delete unpaired_LEP1Pt;
  delete paired_LEP2Pt;
  delete unpaired_LEP2Pt;
  delete paired_LEP3Pt;
  delete unpaired_LEP3Pt;
  delete paired_LEPChargeSum;
  delete unpaired_LEPChargeSum;
  delete paired_lep_softest_pt;
  delete unpaired_lep_softest_pt;

  return;
}

// draw simple for tests
//-----------------------------------------------------------------------------
void drawAVariable_test(THStack* &st, TH1D* hist[N_FAKE], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit){
  
  TCanvas* myPlots = new TCanvas("c1", "c1", 50, 50, 600, 600);
  TPad* myPad = (TPad*) myPlots->cd();
	
  //	hist[0]->Draw("9"); // for data
  st->Draw("9 hist");
  //	err_brs->Draw("9 same  E2");
  //	hist[0]->Draw("9 same");
  for (int i = 0; i < N_SIG; i++)
	sig[i]->Draw("9 hist same");

  TLegend* leg;
  leg = new TLegend(0.65, 0.55, 0.87, 0.92);

  char temp[128];
  std::vector<std::pair<string,TH1D*>> desc;
  for (int i = 1; i < N_FAKE; i++) 
	desc.push_back(std::make_pair(description_mc[i],hist[i]));	
  std::sort(desc.begin(), desc.end(), hasLessEventspair);
  std::vector<std::pair<string,TH1D*>>::reverse_iterator desc_it = desc.rbegin();
  for (; desc_it != desc.rend(); ++desc_it){
	if(show_yield)
	  std::sprintf(temp, "%s (%.1e)", (*desc_it).first.data(), (*desc_it).second->Integral());
	else
	  std::sprintf(temp, "%s", (*desc_it).first.data());
	leg->AddEntry((*desc_it).second, temp , "f");
  }

  for (int i = 0; i < N_SIG; i++){
	std::sprintf(temp, "%s (%.1e)", description_SIG[i].data(), sig[i]->Integral());
	leg->AddEntry(sig[i], temp, "l");
  }

  leg->Draw("same");
  myPad->RedrawAxis();
  myPlots->Update();

  char my_extension[256] = "";
  sprintf(my_extension, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s.pdf", hist[0]->GetName());
  myPlots->Print(my_extension);

  delete myPlots;

  return;
}

// draw simple for tests
//-----------------------------------------------------------------------------
void drawAVariable_normalized(THStack* &st, TH1D* hist[N_FAKE], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit){
  
  for (int ilog=0; ilog<2; ilog++){
	// prepare to plot
	int x_low = -1; // range of the x-axis
	int x_high = -1; 
	bool is_log = ilog;
	double sig_max = 0;
	double sig_int = 0;
	double max = 0;
	for (int i = 0; i < N_SIG; i++)
	  if (sig[i] != NULL) {
		max = GetMyMaximum(sig[i], x_low, x_high, is_log);
		if (sig_max < max) {
		  sig_max = max;
		  sig_int = sig[i]->Integral();
		}
	  }

	TCanvas* myPlots = new TCanvas("c1", "c1", 50, 50, 600, 600);
	TPad* myPad = (TPad*) myPlots->cd();
	if (is_log)
	  myPad->SetLogy(1);
	else
	  myPad->SetLogy(0);
  
	TObjArray* fStack = st->GetStack();
	TH1D* background = (TH1D*) fStack->At(fStack->GetSize() - 1)->Clone();

	double background_maximum = GetMyMaximum(background, x_low, x_high, is_log);
	double background_integral = background->Integral();
	double new_maximum = sig_max;
	double new_int = sig_int;
	if (new_maximum < background_maximum){
	  new_maximum = background_maximum;
	  new_int = background_integral;
	}

	if (is_log) {
	  st->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  background->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	} else {
	  //	  st->SetMaximum(1.28 * new_maximum);
	  //	  background->SetMaximum(1.28 * new_maximum);
	  st->SetMaximum(background_integral * new_maximum/new_int);
	  background->SetMaximum(background_integral * new_maximum/new_int);
	}

	if ((st->GetMaximum() == 0) && (hist[0]->GetEntries() == 0) && (new_maximum == 0)) {
	  return;
	}
  
	if (is_log) {
	  st->SetMinimum(0.2);
	  background->SetMinimum(0.2);
	} else {
	  st->SetMinimum(0);
	  background->SetMinimum(0);
	}
  
	background->SetFillColor(kGray);
	background->GetYaxis()->SetTitleOffset(1.6);
	background->DrawNormalized("hist");
	if(sig_max>0)
	  for (int i = 0; i < N_SIG; i++)
		sig[i]->DrawNormalized("9 same hist");

	TLegend* leg;
	leg = new TLegend(0.65, 0.75, 0.97, 0.92);
	std::string legendHeader = "Normalized MC ";
	string signature;

	// regions
	if (strstr(hist[0]->GetName(), "_SS3L") != NULL){
	  legendHeader += "SS3L ";
	  signature = "SS3L";
	}
	else if (strstr(hist[0]->GetName(), "_SS") != NULL){
	  legendHeader += "SS ";
	  signature = "SS";
	}
	else if (strstr(hist[0]->GetName(), "_3L") != NULL){
	  legendHeader += "3L ";
	  signature = "3L";
	}
	else if (strstr(hist[0]->GetName(), "_OS") != NULL){
	  legendHeader += "OS ";
	  signature = "OS";
	}

	if (strstr(hist[0]->GetName(), "_Incl_") != NULL)
	  legendHeader += ", Inclusive, ";

	if (strstr(hist[0]->GetName(), "_PRE_") != NULL)
	  legendHeader += ", Preselection, ";

	if (strstr(hist[0]->GetName(), "_CR0b_") != NULL)
	  legendHeader += ", CR0b, ";

	if (strstr(hist[0]->GetName(), "_CR1b_") != NULL)
	  legendHeader += ", CR1b, ";

	if (strstr(hist[0]->GetName(), "_CR2b_") != NULL)
	  legendHeader += ", CR2b, ";

	if (strstr(hist[0]->GetName(), "_CR3b_") != NULL)
	  legendHeader += ", CR3b, ";

	if (strstr(hist[0]->GetName(), "_SR3L1_") != NULL)
	  legendHeader += ", SR3L1, ";
	if (strstr(hist[0]->GetName(), "_SR3L2_") != NULL)
	  legendHeader += ", SR3L2, ";
	if (strstr(hist[0]->GetName(), "_SR0b1_") != NULL)
	  legendHeader += ", SR0b1, ";
	if (strstr(hist[0]->GetName(), "_SR0b2_") != NULL)
	  legendHeader += ", SR0b2, ";
	if (strstr(hist[0]->GetName(), "_SR1b_") != NULL)
	  legendHeader += ", SR1b, ";
	if (strstr(hist[0]->GetName(), "_SR3b_") != NULL)
	  legendHeader += ", SR3b, ";
	if (strstr(hist[0]->GetName(), "_SR1b_DD_") != NULL)
	  legendHeader += ", SR1b_DD, ";
	if (strstr(hist[0]->GetName(), "_SR3b_DD_") != NULL)
	  legendHeader += ", SR3b_DD, ";
	if (strstr(hist[0]->GetName(), "_SR1b_GG_") != NULL)
	  legendHeader += ", SR1b_GG, ";
	if (strstr(hist[0]->GetName(), "_SR0b5j_") != NULL)
	  legendHeader += ", SR0b5j, ";
	if (strstr(hist[0]->GetName(), "_SR2b1_") != NULL)
	  legendHeader += ", SR2b1, ";
	if (strstr(hist[0]->GetName(), "_SR2b2_") != NULL)
	  legendHeader += ", SR2b2, ";
	if (strstr(hist[0]->GetName(), "_SR3L3b_") != NULL)
	  legendHeader += ", SR3L3b, ";
	if (strstr(hist[0]->GetName(), "_VRWW_") != NULL)
	  legendHeader += ", VRWW, ";
	if (strstr(hist[0]->GetName(), "_VRWZ4j_") != NULL)
	  legendHeader += ", VRWZ4j, ";
	if (strstr(hist[0]->GetName(), "_VRWZ5j_") != NULL)
	  legendHeader += ", VRWZ5j, ";
	if (strstr(hist[0]->GetName(), "_VRttW_") != NULL)
	  legendHeader += ", VRttW, ";
	if (strstr(hist[0]->GetName(), "_VRttZ_") != NULL)
	  legendHeader += ", VRttZ, ";


	// channels
	if (strstr(hist[0]->GetName(), "_comb_") != NULL)
	  legendHeader += "ee+e#mu+#mu#mu";

	if (strstr(hist[0]->GetName(), "_ee_") != NULL)
	  legendHeader += "ee";
	
	if (strstr(hist[0]->GetName(), "_em_") != NULL)
	  legendHeader += "e#mu";
	
	if (strstr(hist[0]->GetName(), "_mm_") != NULL)
	  legendHeader += "#mu#mu";

	if (strstr(hist[0]->GetName(), "_3l_") != NULL)
	  legendHeader += "3L+";

	leg->SetHeader(legendHeader.data());
	leg->AddEntry(background, "background", "f");
	if(sig_max>0)
	  for (int i = 0; i < N_SIG; i++)
		leg->AddEntry(sig[i], description_SIG[i].data(), "l");
	leg->Draw("same");

	TLatex *l1 = new TLatex();
	l1->SetNDC();
	l1->SetTextFont(73);
	l1->SetTextSize(28);
	l1->SetTextColor(kBlack);
	l1->DrawLatex(0.19, 0.885, "ATLAS ");
	
	TLatex *l2 = new TLatex();
	l2->SetNDC();
	l2->SetTextFont(43);
	l2->SetTextSize(28);
	l2->SetTextColor(kBlack);
	l2->DrawLatex(0.19 + 0.155, 0.885, "Internal");

	TLatex *l3 = new TLatex();
	l3->SetNDC();
	l3->SetTextFont(43);
	l3->SetTextSize(14);
	l3->SetTextColor(kBlack);
	char lumilabel[512];
	sprintf(lumilabel, "#sqrt{s}=13 TeV, #intLdt=%.0f fb^{-1}", lumi/1000.);
	l3->DrawLatex(0.2, 0.83, lumilabel);

	myPad->RedrawAxis();
	myPlots->Update();

	char fpath[512];
	char my_extension[256] = "";
	sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s", folder);
	int res = mkdir(fpath, 0700);
	sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s/%s-fit", folder, fit_type.c_str());
	res = mkdir(fpath, 0700);
	sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s/%s-fit/normalized", folder, fit_type.c_str());
	res = mkdir(fpath, 0700);
	if(ilog){
	  sprintf(fpath, "%s/log", fpath);
	  res = mkdir(fpath, 0700);
	  sprintf(fpath, "%s/%s", fpath, signature.c_str());
	  res = mkdir(fpath, 0700);
	  sprintf(my_extension, "%s/%s_log.pdf", fpath, hist[0]->GetName());
	}
	else{
	  sprintf(fpath, "%s/linear", fpath);
	  res = mkdir(fpath, 0700);
	  sprintf(fpath, "%s/%s", fpath, signature.c_str());
	  res = mkdir(fpath, 0700);
	  sprintf(my_extension, "%s/%s.pdf", fpath, hist[0]->GetName());
	}
	myPlots->Print(my_extension);
  
	delete myPlots;
  }

  return;
}

// draw all
//-----------------------------------------------------------------------------
void drawAVariable_all(THStack* &st, TH1D* hist[N_FAKE], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit){  

  if(hist[0]->Integral() == 0 ) return;

  //We build Stacked plots here
  char my_name[256];
  sprintf(my_name, "HSTACK_%s", hist[0]->GetName());
  THStack* my_st = new THStack(my_name, "Hstack");
  
  // Sort histograms before building the stack
  std::list <TH1D*> mc_hists;
  for (int i = 1; i < N_FAKE; i++) {
	mc_hists.push_back(hist[i]);
  }
  mc_hists.sort(hasLessEvents);
  std::list<TH1D*>::const_iterator iterator;
  for(  iterator = mc_hists.begin(); iterator != mc_hists.end(); ++iterator)
	my_st->Add(*iterator);


  for (int ilog=0; ilog<1; ilog++){
	// prepare to plot
	int x_low = -1; // range of the x-axis
	int x_high = -1; 
	bool is_log = ilog;
	double sig_max = 0;
	double max = 0;
	for (int i = 0; i < N_SIG; i++)
	  if (sig[i] != NULL) {
		max = GetMyMaximum(sig[i], x_low, x_high, is_log);
		if (sig_max < max) {
		  sig_max = max;
		}
	  }

	if ((my_st->GetMaximum() == 0) /*&& (hist[0]->GetEntries() == 0) && (sig_max == 0)*/) {
	  return;
	}

	//	TCanvas* myPlots = new TCanvas("c1", "c1", 50, 50, 600, 600);
	TCanvas* myPlots;
	TPad* myPad1;
	TPad* myPad2 = NULL;

	if(draw_ratio){
	  const double bt_fr2 = 0.35;
	  const double vert_size2 = (int) (600. * 0.84 / (1 - bt_fr2));
	  myPlots = new TCanvas("c2", "c2", 50, 50, 600, (int) vert_size2);
	  myPlots->Divide(1, 2);

	  myPad1 = (TPad*) myPlots->cd(1);
	  myPad1->SetPad(0, bt_fr2, 1, 1);
	  myPad1->SetBottomMargin(0.0);
	  myPad1->SetTopMargin(0.05 * 600. / ((1. - bt_fr2) * vert_size2));

	  myPad2 = (TPad*) myPlots->cd(2);
	  myPad2->SetPad(0, 0.0, 1, bt_fr2);
	  myPad2->SetTopMargin(0.0);
	  myPad2->SetBottomMargin(0.16 * 600. / (vert_size2 * bt_fr2));

	}
	else
	  myPlots = new TCanvas("c1", "c1", 50, 50, 600, 600);
	
	myPad1 = (TPad*) myPlots->cd(1);

	if (is_log)
	  myPad1->SetLogy(1);
	else
	  myPad1->SetLogy(0);

	TObjArray* fStack = my_st->GetStack();
	TH1D* background = (TH1D*) fStack->At(fStack->GetSize() - 1)->Clone();
	double background_maximum = GetMyMaximum(background, x_low, x_high, is_log);
	double new_maximum = sig_max;
	if (new_maximum < background_maximum)
	  new_maximum = background_maximum;
	double data_maximum = GetMyMaximum(hist[0], x_low, x_high, is_log);
	if (new_maximum < data_maximum)
	  new_maximum = data_maximum;

	TH1D *err_brs = errorBars(st, paired, unpaired);
	//error-bars are included into the calculations of maximum
	double err_brs_maximum = GetMyMaximum(err_brs, x_low, x_high, is_log);
	if (err_brs_maximum > new_maximum)
	  new_maximum = err_brs_maximum;

	//----------------------------
	if (x_low > 0 && x_high > 0) {
	  hist[0]->GetXaxis()->SetRange(x_low, x_high);
	  my_st->GetXaxis()->SetRange(x_low, x_high);
	  err_brs->GetXaxis()->SetRange(x_low, x_high);
	  background->GetXaxis()->SetRange(x_low, x_high);
	}

	if (is_log) {
	  hist[0]->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  my_st->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  err_brs->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  background->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	} else {
	  hist[0]->SetMaximum(1.28 * new_maximum);
	  my_st->SetMaximum(1.28 * new_maximum);
	  err_brs->SetMaximum(1.28 * new_maximum);
	  background->SetMaximum(1.28 * new_maximum);
	}
  
	if (is_log) {
	  hist[0]->SetMinimum(0.2);
	  my_st->SetMinimum(0.2);
	  err_brs->SetMinimum(0.2);
	  background->SetMinimum(0.2);
	} else {
	  hist[0]->SetMinimum(0);
	  my_st->SetMinimum(0);
	  err_brs->SetMinimum(0);
	  background->SetMinimum(0);
	}

    hist[0]->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
    hist[0]->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());
    hist[0]->GetYaxis()->SetTitleOffset(1.6);

    // Handle poisson uncertainties  only for data                                                                                                                              
    TGraphAsymmErrors *my_data = new TGraphAsymmErrors(hist[0]);
    for (int p = 0; p < my_data->GetN(); p++){
      double x, y;
      my_data->GetPoint(p,x,y);
      if(y>0){
        my_data->SetPointError(p,0,0,
                               fabs(calcPoissonCLLower(0.68, y)-y),
                               fabs(calcPoissonCLUpper(0.68, y)-y));
      } else
        {
          my_data->RemovePoint(p);
          p=-1;
        }
    }
    // final formatting before plotting                                                                                                                                         
    hist[0]->SetFillColor(1);
    hist[0]->SetLineWidth(1);
    hist[0]->SetLineColor(1);
    hist[0]->SetLineStyle(1);
    hist[0]->SetFillStyle(1001);
    hist[0]->SetMarkerStyle(20);
    hist[0]->SetMarkerSize(1.2);
    hist[0]->GetXaxis()->SetLabelFont(42);
    hist[0]->GetXaxis()->SetLabelSize(0.05);
    hist[0]->GetXaxis()->SetTitleSize(0.05);
    hist[0]->GetXaxis()->SetTitleOffset(1.4);
    hist[0]->GetXaxis()->SetTitleFont(42);
    hist[0]->GetYaxis()->SetLabelFont(42);
    hist[0]->GetYaxis()->SetLabelSize(0.05);
    hist[0]->GetYaxis()->SetTitleSize(0.05);
    hist[0]->GetYaxis()->SetTitleOffset(1.4);
    hist[0]->GetYaxis()->SetTitleFont(42);
    my_data->SetLineColor(1);

	hist[0]->Draw("axis 9");
    my_st->Draw("9 hist same");
    err_brs->Draw("9 same  E2");
    if(my_data != NULL)
      my_data->Draw("pez same");
    else
      hist[0]->Draw("9 same");

    if (sig_max > 0) {
      for (int i = 0; i < N_SIG; i++)
        sig[i]->Draw("9 hist same");
    }

	// total MC
	background->SetLineColor(kBlue);
	background->SetFillColor(kWhite);
	background->SetLineWidth(2);
	background->Draw("9 HIST same");

    TLegend* leg2;
    leg2 = new TLegend(0.65, 0.8, 0.87, 0.835);
    if(draw_sig)
      leg2 = new TLegend(0.65, 0.795, 0.87, 0.839552);
    leg2->SetTextAlign(12);
    leg2->SetFillColor(0);
    leg2->SetFillStyle(0);
    leg2->SetTextSize(0.02);
    leg2->SetTextFont(42);
    leg2->SetBorderSize(0);
    err_brs->SetTitle("");
    leg2->AddEntry(err_brs, "", "f");

    TLegend* leg;
    leg = new TLegend(0.65, 0.55, 0.87, 0.92);
    leg->SetTextAlign(12);
    leg->SetFillColor(0);
    leg->SetTextSize(0.02);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
	
	/*	TLegend* leg;
		leg = new TLegend(0.65, 0.55, 0.87, 0.92);
		leg->SetTextAlign(12);
		leg->SetFillColor(0);
		//  leg->SetTextSize(0.032);
		leg->SetBorderSize(0);*/

	std::string legendHeader = "MC ";
	legendHeader += fit_type;
	legendHeader += "-fit ";

	//	std::string legendHeader = "MC Post-fit ";
	string signature;

	// regions
	if (strstr(hist[0]->GetName(), "_SS3L") != NULL){
	  legendHeader += "SS3L ";
	  signature = "SS3L";
	}
	else if (strstr(hist[0]->GetName(), "_SS") != NULL){
	  legendHeader += "SS ";
	  signature = "SS";
	}
	else if (strstr(hist[0]->GetName(), "_3L") != NULL){
	  legendHeader += "3L ";
	  signature = "3L";
	}
	else if (strstr(hist[0]->GetName(), "_OS") != NULL){
	  legendHeader += "OS ";
	  signature = "OS";
	}
	if (strstr(hist[0]->GetName(), "_Incl_") != NULL)
	  legendHeader += ", Inclusive, ";

	if (strstr(hist[0]->GetName(), "_PRE_") != NULL)
	  legendHeader += ", Preselection, ";

	if (strstr(hist[0]->GetName(), "_CR0b_") != NULL)
	  legendHeader += ", CR0b, ";

	if (strstr(hist[0]->GetName(), "_CR1b_") != NULL)
	  legendHeader += ", CR1b, ";

	if (strstr(hist[0]->GetName(), "_CR2b_") != NULL)
	  legendHeader += ", CR2b, ";

	if (strstr(hist[0]->GetName(), "_CR3b_") != NULL)
	  legendHeader += ", CR3b, ";
	if (strstr(hist[0]->GetName(), "_SR3L1_") != NULL)
	  legendHeader += ", SR3L1, ";
	if (strstr(hist[0]->GetName(), "_SR3L2_") != NULL)
	  legendHeader += ", SR3L2, ";
	if (strstr(hist[0]->GetName(), "_SR0b1_") != NULL)
	  legendHeader += ", SR0b1, ";
	if (strstr(hist[0]->GetName(), "_SR0b2_") != NULL)
	  legendHeader += ", SR0b2, ";
	if (strstr(hist[0]->GetName(), "_SR1b_") != NULL)
	  legendHeader += ", SR1b, ";
	if (strstr(hist[0]->GetName(), "_SR3b_") != NULL)
	  legendHeader += ", SR3b, ";
	if (strstr(hist[0]->GetName(), "_SR1b_DD_") != NULL)
	  legendHeader += ", SR1b_DD, ";
	if (strstr(hist[0]->GetName(), "_SR3b_DD_") != NULL)
	  legendHeader += ", SR3b_DD, ";
	if (strstr(hist[0]->GetName(), "_SR1b_GG_") != NULL)
	  legendHeader += ", SR1b_GG, ";
	if (strstr(hist[0]->GetName(), "_SR0b5j_") != NULL)
	  legendHeader += ", SR0b5j, ";
	if (strstr(hist[0]->GetName(), "_SR2b1_") != NULL)
	  legendHeader += ", SR2b1, ";
	if (strstr(hist[0]->GetName(), "_SR2b2_") != NULL)
	  legendHeader += ", SR2b2, ";
	if (strstr(hist[0]->GetName(), "_SR3L3b_") != NULL)
	  legendHeader += ", SR3L3b, ";
	if (strstr(hist[0]->GetName(), "_VRWW_") != NULL)
	  legendHeader += ", VRWW, ";
	if (strstr(hist[0]->GetName(), "_VRWZ4j_") != NULL)
	  legendHeader += ", VRWZ4j, ";
	if (strstr(hist[0]->GetName(), "_VRWZ5j_") != NULL)
	  legendHeader += ", VRWZ5j, ";
	if (strstr(hist[0]->GetName(), "_VRttW_") != NULL)
	  legendHeader += ", VRttW, ";
	if (strstr(hist[0]->GetName(), "_VRttZ_") != NULL)
	  legendHeader += ", VRttZ, ";

	// channels
	if (strstr(hist[0]->GetName(), "_comb_") != NULL)
	  legendHeader += "ee+e#mu+#mu#mu";

	if (strstr(hist[0]->GetName(), "_ee_") != NULL)
	  legendHeader += "ee";
	
	if (strstr(hist[0]->GetName(), "_em_") != NULL)
	  legendHeader += "e#mu";
	
	if (strstr(hist[0]->GetName(), "_mm_") != NULL)
	  legendHeader += "#mu#mu";

	if (strstr(hist[0]->GetName(), "_3l_") != NULL)
	  legendHeader += "3L+";

	leg->SetHeader(legendHeader.data());
	char temp[128];
	if(show_yield)
	  std::sprintf(temp, "Data  (%.1e)", hist[0]->Integral());
    else
	  std::sprintf(temp, "Data ");
    leg->AddEntry(hist[0], temp, "p");
    if(show_yield)
	  std::sprintf(temp, "Total MC (%.1e)", background->Integral());
    else
	  std::sprintf(temp, "Total MC");
    leg->AddEntry(background, temp , "fl");

	std::vector<std::pair<string,TH1D*>> desc;
    for (int i = 1; i < N_FAKE; i++)
      desc.push_back(std::make_pair(description_fake[i],hist[i]));
	std::sort(desc.begin(), desc.end(), hasLessEventspair);
	std::vector<std::pair<string,TH1D*>>::reverse_iterator desc_it = desc.rbegin();
    for (; desc_it != desc.rend(); ++desc_it){
      if(show_yield)
		std::sprintf(temp, "%s (%.1e)", (*desc_it).first.data(), (*desc_it).second->Integral());
	  else
		std::sprintf(temp, "%s", (*desc_it).first.data());
      leg->AddEntry((*desc_it).second, temp , "f");
    }

    if (sig_max > 0)
      for (int i = 0; i < N_SIG; i++){
        if(show_yield)
		  std::sprintf(temp, "%s (%.1e)", description_SIG[i].data(), sig[i]->Integral());
        else
		  std::sprintf(temp, "%s", description_SIG[i].data());
		leg->AddEntry(sig[i], temp, "l");
      }

    leg->Draw("same");
    leg2->Draw("same");

	TLatex *l1 = new TLatex();
	l1->SetNDC();
	l1->SetTextFont(73);
	l1->SetTextSize(28);
	l1->SetTextColor(kBlack);
	l1->DrawLatex(0.19, 0.885, "ATLAS ");
	
	TLatex *l2 = new TLatex();
	l2->SetNDC();
	l2->SetTextFont(43);
	l2->SetTextSize(28);
	l2->SetTextColor(kBlack);
	l2->DrawLatex(0.19 + 0.155, 0.885, "Internal");

	TLatex *l3 = new TLatex();
	l3->SetNDC();
	l3->SetTextFont(43);
	l3->SetTextSize(14);
	l3->SetTextColor(kBlack);
	char lumilabel[512];
	sprintf(lumilabel, "#sqrt{s}=13 TeV, #intLdt=%.2f fb^{-1}", lumi/1000.);
	l3->DrawLatex(0.2, 0.83, lumilabel);

	myPad1->RedrawAxis();
	//	myPlots->Update();

	if(draw_ratio){

	  myPlots->cd(2);
	  myPad2->SetLogy(0);

	  //	  TPad *myPad1Ratio = new TPad("myPad1Ratio", "",0,0,1,0.33);
	  myPad2->Draw();
	  myPad2->cd();
	  myPad2->Range(-1.310127,-1.200858,3.753165,2.802001);
	  myPad2->SetFillColor(0);
	  myPad2->SetBorderMode(0);
	  myPad2->SetBorderSize(0);
	  myPad2->SetTickx(1);
	  myPad2->SetTicky(1);
	  myPad2->SetLeftMargin(0.16);
	  myPad2->SetRightMargin(0.05);
	  myPad2->SetTopMargin(0.0005);
	  myPad2->SetBottomMargin(0.3);
	  myPad2->SetFrameBorderMode(0);
	  myPad2->SetFrameBorderMode(0);
   


	  TH1D *TH1DaxisRatio = (TH1D*) hist[0]->Clone();
	  TH1DaxisRatio->SetBinContent(1,-1);
	  TH1DaxisRatio->SetBinContent(2,-1);
	  TH1DaxisRatio->SetBinContent(3,-1);
	  TH1DaxisRatio->SetBinContent(4,-1);
	  TH1DaxisRatio->SetMinimum(0);
	  TH1DaxisRatio->SetMaximum(2.8);
	  TH1DaxisRatio->SetEntries(16);
	  TH1DaxisRatio->SetStats(0);
	  TH1DaxisRatio->SetLineWidth(2);
	  TH1DaxisRatio->SetMarkerStyle(20);
	  TH1DaxisRatio->SetMarkerSize(1.2);
	  TH1DaxisRatio->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
	  //   TH1DaxisRatio->GetXaxis()->SetNdivisions(4);
	  TH1DaxisRatio->GetXaxis()->SetLabelFont(42);
	  TH1DaxisRatio->GetXaxis()->SetLabelSize(0.12);
	  TH1DaxisRatio->GetXaxis()->SetTitleSize(0.12);
	  TH1DaxisRatio->GetXaxis()->SetTitleOffset(1.0);
	  TH1DaxisRatio->GetXaxis()->SetTitleFont(42);
	  TH1DaxisRatio->GetYaxis()->SetTitle("data/MC");
	  TH1DaxisRatio->GetYaxis()->SetNdivisions(505);
	  TH1DaxisRatio->GetYaxis()->SetLabelFont(42);
	  TH1DaxisRatio->GetYaxis()->SetLabelSize(0.12);
	  TH1DaxisRatio->GetYaxis()->SetTitleSize(0.12);
	  TH1DaxisRatio->GetYaxis()->SetTitleOffset(0.5);
	  TH1DaxisRatio->GetYaxis()->SetTitleFont(42);
	  TH1DaxisRatio->GetZaxis()->SetLabelFont(42);
	  TH1DaxisRatio->GetZaxis()->SetLabelSize(0.05);
	  TH1DaxisRatio->GetZaxis()->SetTitleSize(0.05);
	  TH1DaxisRatio->GetZaxis()->SetTitleFont(42);
	  TH1DaxisRatio->Draw("axis");
 
	  myPad1->Update();
	  myPad1->Modified();
	  TLine *line = new TLine(myPad1->GetUxmin(),1,myPad1->GetUxmax(),1);
	  line->SetLineStyle(2);
	  line->SetLineWidth(2);
	  line->Draw();
	  line = new TLine(myPad1->GetUxmin(),1.5,myPad1->GetUxmax(),1.5);
	  line->SetLineStyle(2);
	  line->SetLineWidth(2);
	  line->Draw();
	  line = new TLine(myPad1->GetUxmin(),2,myPad1->GetUxmax(),2);
	  line->SetLineStyle(2);
	  line->SetLineWidth(2);
	  line->Draw();
	  line = new TLine(myPad1->GetUxmin(),0.5,myPad1->GetUxmax(),0.5);
	  line->SetLineStyle(2);
	  line->SetLineWidth(2);
	  line->Draw();
   
	  TH1F *Graph_g_hRatio3014 =  (TH1F*)  hist[0]->Clone(); //new TH1F("Graph_g_hRatio3014","",100,-0.9,3.9);
	  for (int k = 1; k <= Graph_g_hRatio3014->GetNbinsX(); k++)
		if (background->GetBinContent(k) != 0) {
		  Graph_g_hRatio3014->SetBinContent(k, Graph_g_hRatio3014->GetBinContent(k) / background->GetBinContent(k));
		  Graph_g_hRatio3014->SetBinError(k, Graph_g_hRatio3014->GetBinError(k) / background->GetBinContent(k));
		} else {
		  Graph_g_hRatio3014->SetBinContent(k, 0);
		  Graph_g_hRatio3014->SetBinError(k, 0);
		}

	  Graph_g_hRatio3014->SetMinimum(0.09234416);
	  Graph_g_hRatio3014->SetMaximum(5.600989);
	  Graph_g_hRatio3014->SetDirectory(0);
	  Graph_g_hRatio3014->SetStats(0);
	  Graph_g_hRatio3014->SetLineWidth(2);
	  Graph_g_hRatio3014->SetMarkerStyle(20);
	  Graph_g_hRatio3014->SetMarkerSize(1.2);
	  Graph_g_hRatio3014->GetXaxis()->SetLabelFont(42);
	  Graph_g_hRatio3014->GetXaxis()->SetLabelSize(0.05);
	  Graph_g_hRatio3014->GetXaxis()->SetTitleSize(0.05);
	  Graph_g_hRatio3014->GetXaxis()->SetTitleOffset(1.4);
	  Graph_g_hRatio3014->GetXaxis()->SetTitleFont(42);
	  Graph_g_hRatio3014->GetYaxis()->SetLabelFont(42);
	  Graph_g_hRatio3014->GetYaxis()->SetLabelSize(0.05);
	  Graph_g_hRatio3014->GetYaxis()->SetTitleSize(0.05);
	  Graph_g_hRatio3014->GetYaxis()->SetTitleOffset(1.4);
	  Graph_g_hRatio3014->GetYaxis()->SetTitleFont(42);
	  Graph_g_hRatio3014->GetZaxis()->SetLabelFont(42);
	  Graph_g_hRatio3014->GetZaxis()->SetLabelSize(0.05);
	  Graph_g_hRatio3014->GetZaxis()->SetTitleSize(0.05);
	  Graph_g_hRatio3014->GetZaxis()->SetTitleFont(42);
	  Graph_g_hRatio3014->Draw("same");

	  TH1D* error_band = (TH1D*) err_brs->Clone("Ratio_error_band");
	  for (int k = 1; k <= error_band->GetNbinsX(); k++)
		if (background->GetBinContent(k) != 0) {
		  error_band->SetBinContent(k, error_band->GetBinContent(k) / background->GetBinContent(k));
		  error_band->SetBinError(k, error_band->GetBinError(k) / background->GetBinContent(k));
		  // TO DO: check on the error bars function that symmetrizes the error
		  //  std::cout << "not 1 = " << err_brs->GetBinContent(k) / background->GetBinContent(k) << std::endl;
		} else {
		  error_band->SetBinContent(k, 1);
		  error_band->SetBinError(k, 0);
		}
	  error_band->SetLineColor(kYellow);
	  error_band->Draw("e2 9 same");

	  myPad2->RedrawAxis();
	}

	myPad1->RedrawAxis();
	myPlots->Update();

	if( strstr(hist[0]->GetName(), "SR") == NULL ){
	  // Save plots
	  char fpath[512];
	  char my_extension[256] = "";
	  sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s", folder);
	  int res = mkdir(fpath, 0700);
	  sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s/%s-fit", folder, fit_type.c_str());
	  res = mkdir(fpath, 0700);
	  sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s/%s-fit/all", folder, fit_type.c_str());
	  res = mkdir(fpath, 0700);
	  if(ilog){
		sprintf(fpath, "%s/log", fpath);
		res = mkdir(fpath, 0700);
		sprintf(fpath, "%s/%s", fpath, signature.c_str());
		res = mkdir(fpath, 0700);
		sprintf(my_extension, "%s/%s_log.pdf", fpath, hist[0]->GetName());
	  }
	  else{
		sprintf(fpath, "%s/linear", fpath);
		res = mkdir(fpath, 0700);
		sprintf(fpath, "%s/%s", fpath, signature.c_str());
		res = mkdir(fpath, 0700);
		sprintf(my_extension, "%s/%s.pdf", fpath, hist[0]->GetName());
	  }
	  myPlots->Print(my_extension);
	}
	delete myPlots;
  }

  
  return;
}

// draw merged stacked plots, "drawAVariable_long" draws all of them
//-----------------------------------------------------------------------------
void drawAVariable_merged(THStack* &st, TH1D* hist[N_FAKE], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit){
  
  int color[N_FAKE];
  //Specify the colors

  int ind=1;
  color[ind++] =  TColor::GetColor("#cc99ff"); //kTeal; // ttW, ttZ
  color[ind++] = 0;
  color[ind++] = TColor::GetColor("#3399ff"); // WW, WZ, ZZ
  color[ind++] = 0;
  color[ind++] = 0;
  color[ind++] = kOrange-2; // tth, Wh, Zh
  color[ind++] = 0;
  color[ind++] = 0; 
  color[ind++] =  TColor::GetColor("#339900"); //kAzure +7; // tt+WW/t/tt, tZ, VVV
  color[ind++] = 0;
  color[ind++] = 0;
  color[ind++] = 0;
  color[ind++] = 0;
  color[ind++] = TColor::GetColor("#ffcc99"); //kOrange - 6; // ttbar, single top
  color[ind++] = 0;
  color[ind++] = TColor::GetColor("#993300"); //kTeal + 4; // Z+jets
  color[ind++] = kGray; // W+jets

  for (int ilog=0; ilog<2; ilog++){
	
	// setup the merging machinery
	TH1D *my_hist[N_FAKE];
	char my_name[256];
	for (int i = 1; i < N_FAKE; i++)
	  if (map_mc_merged[i] == -1) {
		sprintf(my_name, "Merged_%s", hist[i]->GetName());
		my_hist[i] = (TH1D*) hist[i]->Clone(my_name);
		my_hist[i]->SetFillColor(color[i]);
		my_hist[i]->SetLineWidth(1);
		my_hist[i]->SetLineColor(1);
		my_hist[i]->SetLineStyle(1);
		my_hist[i]->SetFillStyle(1001);
	  }

	for (int i = 1; i < N_FAKE; i++)
	  if (map_mc_merged[i] > -1) {
		my_hist[map_mc_merged[i]]->Add(hist[i]);
	  }

	//We build Stacked plots here

	sprintf(my_name, "Merged_HSTACK_%s", hist[0]->GetName());
	THStack* my_st = new THStack(my_name, "Hstack");
	
	std::vector<std::pair<string,TH1D*>> desc;
	for (int i = 1; i < N_FAKE; i++)
	  if (map_mc_merged[i] == -1)  
		desc.push_back(std::make_pair(description_mc_merged[i],my_hist[i]));	
  
	std::sort(desc.begin(), desc.end(), hasLessEventspair);
	std::vector<std::pair<string,TH1D*>>::iterator desc_iterator;
	for ( desc_iterator = desc.begin(); desc_iterator != desc.end(); ++desc_iterator){
	  my_st->Add((*desc_iterator).second);
	}
	
	// prepare to plot
	int x_low = -1; // range of the x-axis
	int x_high = -1; 
	bool is_log = ilog;
	double sig_max = 0;
	double max = 0;
	for (int i = 0; i < N_SIG; i++)
	  if (sig[i] != NULL) {
		max = GetMyMaximum(sig[i], x_low, x_high, is_log);
		if (sig_max < max) {
		  sig_max = max;
		}
	  }

	if ((my_st->GetMaximum() == 0) && (hist[0]->GetEntries() == 0) && (sig_max == 0)) {
	  return;
	}

	if(hist[0]->GetEntries() == 0)
	  draw_ratio = false;

	TCanvas* myPlots = new TCanvas("c1", "c1", 50, 50, 600, 600);
	TPad* myPad = (TPad*) myPlots->cd();
	if (is_log)
	  myPad->SetLogy(1);
	else
	  myPad->SetLogy(0);

	TObjArray* fStack = my_st->GetStack();
	TH1D* background = (TH1D*) fStack->At(fStack->GetSize() - 1)->Clone();
	double background_maximum = GetMyMaximum(background, x_low, x_high, is_log);
	double new_maximum = sig_max;
	if (new_maximum < background_maximum)
	  new_maximum = background_maximum;
	double data_maximum = GetMyMaximum(hist[0], x_low, x_high, is_log);
	if (new_maximum < data_maximum)
	  new_maximum = data_maximum;

	TH1D *err_brs = errorBars(my_st, paired, unpaired);
	//error-bars are included into the calculations of maximum
	double err_brs_maximum = GetMyMaximum(err_brs, x_low, x_high, is_log);
	if (new_maximum < err_brs_maximum)
	  new_maximum = err_brs_maximum;
	
	//----------------------------
	if (x_low > 0 && x_high > 0) {
	  hist[0]->GetXaxis()->SetRange(x_low, x_high);
	  my_st->GetXaxis()->SetRange(x_low, x_high);
	  err_brs->GetXaxis()->SetRange(x_low, x_high);
	  background->GetXaxis()->SetRange(x_low, x_high);
	}

	if (is_log) {
	  hist[0]->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  my_st->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  err_brs->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  background->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	} else {
	  hist[0]->SetMaximum(1.28 * new_maximum);
	  my_st->SetMaximum(1.28 * new_maximum);
	  err_brs->SetMaximum(1.28 * new_maximum);
	  background->SetMaximum(1.28 * new_maximum);
	}
  
	if (is_log) {
	  hist[0]->SetMinimum(0.2);
	  my_st->SetMinimum(0.2);
	  err_brs->SetMinimum(0.2);
	  background->SetMinimum(0.2);
	} else {
	  hist[0]->SetMinimum(0);
	  my_st->SetMinimum(0);
	  err_brs->SetMinimum(0);
	  background->SetMinimum(0);
	}

	//  my_st->GetXaxis()->SetNdivisions(2 + x_high - x_low);

	hist[0]->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
	hist[0]->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());	
	hist[0]->GetYaxis()->SetTitleOffset(1.6);

	// Handle poisson uncertainties  only for data
	TGraphAsymmErrors *my_data = new TGraphAsymmErrors(hist[0]);
	for (int p = 0; p < my_data->GetN(); p++){
	  double x, y;
	  my_data->GetPoint(p,x,y);
	  if(y>0){
		my_data->SetPointError(p,0,0,
							   fabs(calcPoissonCLLower(0.68, y)-y),
							   fabs(calcPoissonCLUpper(0.68, y)-y));
	  } else
		{
		  my_data->RemovePoint(p);
		  p=-1;
		}
	}

	// final formatting before plotting
	hist[0]->SetFillColor(1);
	hist[0]->SetLineWidth(1);
	hist[0]->SetLineColor(1);
	hist[0]->SetLineStyle(1);
	hist[0]->SetFillStyle(1001);
	hist[0]->SetMarkerStyle(20);
	hist[0]->SetMarkerSize(1.2);
	hist[0]->GetXaxis()->SetLabelFont(42);
	hist[0]->GetXaxis()->SetLabelSize(0.05);
	hist[0]->GetXaxis()->SetTitleSize(0.05);
	hist[0]->GetXaxis()->SetTitleOffset(1.4);
	hist[0]->GetXaxis()->SetTitleFont(42);
	hist[0]->GetYaxis()->SetLabelFont(42);
	hist[0]->GetYaxis()->SetLabelSize(0.05);
	hist[0]->GetYaxis()->SetTitleSize(0.05);
	hist[0]->GetYaxis()->SetTitleOffset(1.4);
	hist[0]->GetYaxis()->SetTitleFont(42);
	my_data->SetLineColor(1);

	hist[0]->Draw("axis 9");
	my_st->Draw("9 hist same");
	err_brs->Draw("9 same  E2");
	if(my_data != NULL)
	  my_data->Draw("pez same");
	else
	  hist[0]->Draw("9 same");
	// total MC
	background->SetLineColor(kBlue);
	background->SetFillColor(kWhite);
	background->SetLineWidth(2);
	background->Draw("9 HIST same");
	if (sig_max > 0) {
	  for (int i = 0; i < N_SIG; i++)
		sig[i]->Draw("9 hist same");
	}

	TLegend* leg2;
	leg2 = new TLegend(0.65, 0.810435, 0.87, 0.845217);
	if(!draw_sig)
	  leg2 = new TLegend(0.65, 0.795, 0.87, 0.839552);
	leg2->SetTextAlign(12);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->SetTextSize(0.02);
	leg2->SetTextFont(42);
	leg2->SetBorderSize(0);
	err_brs->SetTitle("");
	leg2->AddEntry(err_brs, "", "f");

	TLegend* leg;
	leg = new TLegend(0.65, 0.55, 0.87, 0.92);
	leg->SetTextAlign(12);
	leg->SetFillColor(0);
	leg->SetTextSize(0.02);
	leg->SetTextFont(42);
	leg->SetBorderSize(0);

	//	std::string legendHeader = "MC ";
	std::string legendHeader = "";
	string signature;

	// regions
	if (strstr(hist[0]->GetName(), "_SS3L") != NULL){
	  legendHeader += "SS3L ";
	  signature = "SS3L";
	}
	else if (strstr(hist[0]->GetName(), "_SS") != NULL){
	  legendHeader += "SS ";
	  signature = "SS";
	}
	else if (strstr(hist[0]->GetName(), "_3L") != NULL){
	  legendHeader += "3L ";
	  signature = "3L";
	}
	else if (strstr(hist[0]->GetName(), "_OS") != NULL){
	  legendHeader += "OS ";
	  signature = "OS";
	}
	if (strstr(hist[0]->GetName(), "_Incl_") != NULL)
	  legendHeader += ", Inclusive, ";

	if (strstr(hist[0]->GetName(), "_PRE_") != NULL)
	  legendHeader += ", Preselection, ";

	if (strstr(hist[0]->GetName(), "_CR0b_") != NULL)
	  legendHeader += ", CR0b, ";

	if (strstr(hist[0]->GetName(), "_CR1b_") != NULL)
	  legendHeader += ", CR1b, ";

	if (strstr(hist[0]->GetName(), "_CR2b_") != NULL)
	  legendHeader += ", CR2b, ";

	if (strstr(hist[0]->GetName(), "_CR3b_") != NULL)
	  legendHeader += ", CR3b, ";

	if (strstr(hist[0]->GetName(), "_SR3L1_") != NULL)
	  legendHeader += ", SR3L1, ";
	if (strstr(hist[0]->GetName(), "_SR3L2_") != NULL)
	  legendHeader += ", SR3L2, ";
	if (strstr(hist[0]->GetName(), "_SR0b1_") != NULL)
	  legendHeader += ", SR0b1, ";
	if (strstr(hist[0]->GetName(), "_SR0b2_") != NULL)
	  legendHeader += ", SR0b2, ";
	if (strstr(hist[0]->GetName(), "_SR1b_") != NULL)
	  legendHeader += ", SR1b, ";
	if (strstr(hist[0]->GetName(), "_SR3b_") != NULL)
	  legendHeader += ", SR3b, ";
	if (strstr(hist[0]->GetName(), "_SR1b_DD_") != NULL)
	  legendHeader += ", SR1b_DD, ";
	if (strstr(hist[0]->GetName(), "_SR3b_DD_") != NULL)
	  legendHeader += ", SR3b_DD, ";
	if (strstr(hist[0]->GetName(), "_SR1b_GG_") != NULL)
	  legendHeader += ", SR1b_GG, ";
	if (strstr(hist[0]->GetName(), "_SR0b5j_") != NULL)
	  legendHeader += ", SR0b5j, ";
	if (strstr(hist[0]->GetName(), "_SR2b1_") != NULL)
	  legendHeader += ", SR2b1, ";
	if (strstr(hist[0]->GetName(), "_SR2b2_") != NULL)
	  legendHeader += ", SR2b2, ";
	if (strstr(hist[0]->GetName(), "_SR3L3b_") != NULL)
	  legendHeader += ", SR3L3b, ";
	if (strstr(hist[0]->GetName(), "_VRWW_") != NULL)
	  legendHeader += ", VRWW, ";
	if (strstr(hist[0]->GetName(), "_VRWZ4j_") != NULL)
	  legendHeader += ", VRWZ4j, ";
	if (strstr(hist[0]->GetName(), "_VRWZ5j_") != NULL)
	  legendHeader += ", VRWZ5j, ";
	if (strstr(hist[0]->GetName(), "_VRttW_") != NULL)
	  legendHeader += ", VRttW, ";
	if (strstr(hist[0]->GetName(), "_VRttZ_") != NULL)
	  legendHeader += ", VRttZ, ";

	// channels
	if (strstr(hist[0]->GetName(), "_comb_") != NULL)
	  legendHeader += "ee+e#mu+#mu#mu";

	if (strstr(hist[0]->GetName(), "_ee_") != NULL)
	  legendHeader += "ee";
	
	if (strstr(hist[0]->GetName(), "_em_") != NULL)
	  legendHeader += "e#mu";
	
	if (strstr(hist[0]->GetName(), "_mm_") != NULL)
	  legendHeader += "#mu#mu";

	if (strstr(hist[0]->GetName(), "_3l_") != NULL)
	  legendHeader += "3L+";
	
	// TO DO: could have 0 events in SR after unblinding!
	if(hist[0]->GetEntries() == 0)
	  legendHeader += ", blinded";
	leg->SetHeader(legendHeader.data());

	char temp[128];
	if(show_yield)
	  std::sprintf(temp, "Data  (%.1e)", hist[0]->Integral());
	else
	  std::sprintf(temp, "Data ");
	leg->AddEntry(hist[0], temp, "p");
	if(show_yield)
	  std::sprintf(temp, "Total MC (%.1e)", background->Integral());
	else
	  std::sprintf(temp, "Total MC");
	leg->AddEntry(background, temp , "fl");  
	
	std::vector<std::pair<string,TH1D*>>::reverse_iterator desc_it = desc.rbegin();
	for (; desc_it != desc.rend(); ++desc_it){
	  if(show_yield)
		std::sprintf(temp, "%s (%.1e)", (*desc_it).first.data(), (*desc_it).second->Integral());
	  else
		std::sprintf(temp, "%s", (*desc_it).first.data());
	  leg->AddEntry((*desc_it).second, temp , "f");
	}
	
	if (sig_max > 0) 
	  for (int i = 0; i < N_SIG; i++){
		double zExp = RooStats::NumberCountingUtils::BinomialExpZ(sig[i]->Integral(),  background->Integral(), .3);
		if(show_yield)
		  std::sprintf(temp, "%s (%.1e, %.1f)", description_SIG[i].data(), sig[i]->Integral(), zExp);
		else
		  std::sprintf(temp, "%s", description_SIG[i].data());
		leg->AddEntry(sig[i], temp, "l");
	  }
	
	leg->Draw("same");
	leg2->Draw("same");

	TLatex *l1 = new TLatex();
	l1->SetNDC();
	l1->SetTextFont(73);
	l1->SetTextSize(28);
	l1->SetTextColor(kBlack);
	l1->DrawLatex(0.19, 0.885, "ATLAS ");
	
	TLatex *l2 = new TLatex();
	l2->SetNDC();
	l2->SetTextFont(43);
	l2->SetTextSize(28);
	l2->SetTextColor(kBlack);
	l2->DrawLatex(0.19 + 0.155, 0.885, "Internal");

	TLatex *l3 = new TLatex();
	l3->SetNDC();
	l3->SetTextFont(43);
	l3->SetTextSize(14);
	l3->SetTextColor(kBlack);
	char lumilabel[512];
	sprintf(lumilabel, "#sqrt{s}=13 TeV, #intLdt=%.0f fb^{-1}", lumi/1000.);
	l3->DrawLatex(0.2, 0.83, lumilabel);

	myPad->RedrawAxis();
	myPlots->Update();


	if(draw_ratio){
	  TPad *myPadRatio = new TPad("myPadRatio", "",0,0,1,0.33);
	  myPadRatio->Draw();
	  myPadRatio->cd();
	  myPadRatio->Range(-1.310127,-1.200858,3.753165,2.802001);
	  myPadRatio->SetFillColor(0);
	  myPadRatio->SetBorderMode(0);
	  myPadRatio->SetBorderSize(0);
	  myPadRatio->SetTickx(1);
	  myPadRatio->SetTicky(1);
	  myPadRatio->SetLeftMargin(0.16);
	  myPadRatio->SetRightMargin(0.05);
	  myPadRatio->SetTopMargin(0.0005);
	  myPadRatio->SetBottomMargin(0.3);
	  myPadRatio->SetFrameBorderMode(0);
	  myPadRatio->SetFrameBorderMode(0);
   


	  TH1D *TH1DaxisRatio = (TH1D*) hist[0]->Clone();
	  TH1DaxisRatio->SetBinContent(1,-1);
	  TH1DaxisRatio->SetBinContent(2,-1);
	  TH1DaxisRatio->SetBinContent(3,-1);
	  TH1DaxisRatio->SetBinContent(4,-1);
	  TH1DaxisRatio->SetMinimum(0);
	  TH1DaxisRatio->SetMaximum(2.8);
	  TH1DaxisRatio->SetEntries(16);
	  TH1DaxisRatio->SetStats(0);
	  TH1DaxisRatio->SetLineWidth(2);
	  TH1DaxisRatio->SetMarkerStyle(20);
	  TH1DaxisRatio->SetMarkerSize(1.2);
	  TH1DaxisRatio->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
	  //   TH1DaxisRatio->GetXaxis()->SetNdivisions(4);
	  TH1DaxisRatio->GetXaxis()->SetLabelFont(42);
	  TH1DaxisRatio->GetXaxis()->SetLabelSize(0.12);
	  TH1DaxisRatio->GetXaxis()->SetTitleSize(0.12);
	  TH1DaxisRatio->GetXaxis()->SetTitleOffset(1.0);
	  TH1DaxisRatio->GetXaxis()->SetTitleFont(42);
	  TH1DaxisRatio->GetYaxis()->SetTitle("data/MC");
	  TH1DaxisRatio->GetYaxis()->SetNdivisions(505);
	  TH1DaxisRatio->GetYaxis()->SetLabelFont(42);
	  TH1DaxisRatio->GetYaxis()->SetLabelSize(0.12);
	  TH1DaxisRatio->GetYaxis()->SetTitleSize(0.12);
	  TH1DaxisRatio->GetYaxis()->SetTitleOffset(0.5);
	  TH1DaxisRatio->GetYaxis()->SetTitleFont(42);
	  TH1DaxisRatio->GetZaxis()->SetLabelFont(42);
	  TH1DaxisRatio->GetZaxis()->SetLabelSize(0.05);
	  TH1DaxisRatio->GetZaxis()->SetTitleSize(0.05);
	  TH1DaxisRatio->GetZaxis()->SetTitleFont(42);
	  TH1DaxisRatio->Draw("axis");
 
	  myPad->Update();
	  myPad->Modified();
	  TLine *line = new TLine(myPad->GetUxmin(),1,myPad->GetUxmax(),1);
	  line->SetLineStyle(2);
	  line->SetLineWidth(2);
	  line->Draw();
	  line = new TLine(myPad->GetUxmin(),1.5,myPad->GetUxmax(),1.5);
	  line->SetLineStyle(2);
	  line->SetLineWidth(2);
	  line->Draw();
	  line = new TLine(myPad->GetUxmin(),2,myPad->GetUxmax(),2);
	  line->SetLineStyle(2);
	  line->SetLineWidth(2);
	  line->Draw();
	  line = new TLine(myPad->GetUxmin(),0.5,myPad->GetUxmax(),0.5);
	  line->SetLineStyle(2);
	  line->SetLineWidth(2);
	  line->Draw();
   
	  TH1F *Graph_g_hRatio3014 =  (TH1F*)  hist[0]->Clone(); //new TH1F("Graph_g_hRatio3014","",100,-0.9,3.9);
	  for (int k = 1; k <= Graph_g_hRatio3014->GetNbinsX(); k++)
		if (background->GetBinContent(k) != 0) {
		  Graph_g_hRatio3014->SetBinContent(k, Graph_g_hRatio3014->GetBinContent(k) / background->GetBinContent(k));
		  Graph_g_hRatio3014->SetBinError(k, Graph_g_hRatio3014->GetBinError(k) / background->GetBinContent(k));
		} else {
		  Graph_g_hRatio3014->SetBinContent(k, 0);
		  Graph_g_hRatio3014->SetBinError(k, 0);
		}

	  Graph_g_hRatio3014->SetMinimum(0.09234416);
	  Graph_g_hRatio3014->SetMaximum(5.600989);
	  Graph_g_hRatio3014->SetDirectory(0);
	  Graph_g_hRatio3014->SetStats(0);
	  Graph_g_hRatio3014->SetLineWidth(2);
	  Graph_g_hRatio3014->SetMarkerStyle(20);
	  Graph_g_hRatio3014->SetMarkerSize(1.2);
	  Graph_g_hRatio3014->GetXaxis()->SetLabelFont(42);
	  Graph_g_hRatio3014->GetXaxis()->SetLabelSize(0.05);
	  Graph_g_hRatio3014->GetXaxis()->SetTitleSize(0.05);
	  Graph_g_hRatio3014->GetXaxis()->SetTitleOffset(1.4);
	  Graph_g_hRatio3014->GetXaxis()->SetTitleFont(42);
	  Graph_g_hRatio3014->GetYaxis()->SetLabelFont(42);
	  Graph_g_hRatio3014->GetYaxis()->SetLabelSize(0.05);
	  Graph_g_hRatio3014->GetYaxis()->SetTitleSize(0.05);
	  Graph_g_hRatio3014->GetYaxis()->SetTitleOffset(1.4);
	  Graph_g_hRatio3014->GetYaxis()->SetTitleFont(42);
	  Graph_g_hRatio3014->GetZaxis()->SetLabelFont(42);
	  Graph_g_hRatio3014->GetZaxis()->SetLabelSize(0.05);
	  Graph_g_hRatio3014->GetZaxis()->SetTitleSize(0.05);
	  Graph_g_hRatio3014->GetZaxis()->SetTitleFont(42);
	  Graph_g_hRatio3014->Draw("same");

	  TH1D* error_band = (TH1D*) err_brs->Clone("Ratio_error_band");
	  for (int k = 1; k <= error_band->GetNbinsX(); k++)
		if (background->GetBinContent(k) != 0) {
		  error_band->SetBinContent(k, error_band->GetBinContent(k) / background->GetBinContent(k));
		  error_band->SetBinError(k, error_band->GetBinError(k) / background->GetBinContent(k));
		  // TO DO: check on the error bars function that symmetrizes the error
		  //		  std::cout << "not 1 = " << err_brs->GetBinContent(k) / background->GetBinContent(k) << std::endl;
		} else {
		  error_band->SetBinContent(k, 1);
		  error_band->SetBinError(k, 0);
		}
	  error_band->Draw("e2 9 same");
	}


	// Save plots

	char fpath[512];
	char my_extension[256] = "";
	sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s", folder);
	int res = mkdir(fpath, 0700);
	sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s/%s-fit", folder, fit_type.c_str());
	res = mkdir(fpath, 0700);
	sprintf(fpath, "/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s/%s-fit/merged", folder, fit_type.c_str());
	res = mkdir(fpath, 0700);
	if(ilog){
	  sprintf(fpath, "%s/log", fpath);
	  res = mkdir(fpath, 0700);
	  sprintf(fpath, "%s/%s", fpath, signature.c_str());
	  res = mkdir(fpath, 0700);
	  sprintf(my_extension, "%s/%s_log.pdf", fpath, hist[0]->GetName());
	  //	  sprintf(my_extension, "%s/%s_log.C", fpath, hist[0]->GetName());
	}
	else{
	  sprintf(fpath, "%s/linear", fpath);
	  res = mkdir(fpath, 0700);
	  sprintf(fpath, "%s/%s", fpath, signature.c_str());
	  res = mkdir(fpath, 0700);
	  sprintf(my_extension, "%s/%s.pdf", fpath, hist[0]->GetName());
	}
	myPlots->Print(my_extension);
	
	delete myPlots;
  }


  return;
}

//-----------------------------------------------------------------------------
// Calculates the maximum value and takes into account the legend
//-----------------------------------------------------------------------------

double GetMyMaximum(TH1D* h, int x_low, int x_high, bool is_log) {

  double default_max = 0;
  double my_max = 0;
  double in_bin = 0;

  int low_bin = 1;
  if (x_low > 0 && x_low <= h->GetNbinsX())
	low_bin = x_low;

  int high_bin = h->GetNbinsX();
  if (x_high > 0 && x_high <= h->GetNbinsX())
	high_bin = x_high;

  for (int i = low_bin; i <= high_bin; i++) {
	in_bin = h->GetBinContent(i) + h->GetBinError(i);
	if (in_bin > default_max)
	  default_max = in_bin;
  }

  in_bin = 0;
  int first_bin = low_bin + (int) (0.615 * (1 + high_bin - low_bin));
  for (int i = first_bin; i <= high_bin && i < h->GetNbinsX(); i++) {
	in_bin = h->GetBinContent(i) + fabs(h->GetBinError(i));
	if (in_bin > my_max)
	  my_max = in_bin;
  }

  const double ratio = 2. / 1.15;

  if (is_log) {

	if (log(my_max / 0.2) * ratio > log(default_max / 0.2))
	  my_max = pow(my_max / 0.2, ratio) * 0.2;
	else
	  my_max = default_max;

  } else {

	if (my_max * ratio > default_max)
	  my_max = my_max * ratio;
	else
	  my_max = default_max;

  }

  return my_max;
}

//-----------------------------------------------------------------------------
// Error bar machinery
//-----------------------------------------------------------------------------

TH1D* errorBars(THStack* central, TObjArray *paired, TObjArray *unpaired) {

  TObjArray* fStack = central->GetStack();
  TH1D* h = (TH1D*) fStack->At(fStack->GetSize() - 1)->Clone();
  h->SetTitle(Form("errors_%s", h->GetName()));

  Int_t N_bins = h->GetNbinsX();

  Int_t N_unc_paird = paired->GetSize();
  Int_t N_unc_unpaird = unpaired->GetSize();

  double pos_err, neg_err, mean_value, value, stat_error;
  for (int i = 1; i <= N_bins; i++) {

	//We should use statistical uncertainties provided by the central value
	stat_error = h->GetBinError(i);
	pos_err = pow(stat_error, 2);
	neg_err = pow(stat_error, 2);
	mean_value = h->GetBinContent(i);

	//paired systematics
	for (int j = 0; j < N_unc_paird; j++) {

	  THStack *paired_st = (THStack*) paired->At(j);
	  TObjArray* fStack = paired_st->GetStack();
	  TH1D* hp = (TH1D*) fStack->At(fStack->GetSize() - 1)->Clone();
	  value = hp->GetBinContent(i);

	  //p or m JES
	  if (value > mean_value)
		pos_err += pow(value - mean_value, 2);
	  else
		neg_err += pow(value - mean_value, 2);
	}

	//unpaired systematics
	for (int j = 0; j < N_unc_unpaird; j++) {

	  THStack *unpaired_st = (THStack*) unpaired->At(j);
	  TObjArray* fStack = unpaired_st->GetStack();
	  TH1D* hp = (TH1D*) fStack->At(fStack->GetSize() - 1)->Clone();
	  value = hp->GetBinContent(i);

	  pos_err += pow(value - mean_value, 2);
	  neg_err += pow(value - mean_value, 2);

	}

	pos_err = sqrt(pos_err);
	neg_err = sqrt(neg_err);

	h->SetBinContent(i, mean_value + (pos_err - neg_err) / 2.);
	h->SetBinError(i, (pos_err + neg_err) / 2.);
  }

  h->SetFillStyle(3554);
  h->SetFillColor(1);
  h->SetMarkerSize(0);

  return h;

}

// Calculate lower confidence limit
//   e.g. to calculate the 68% lower limit for 2 observed events:
//      calcPoissonCLLower(0.68, 2.)
double calcPoissonCLLower(Double_t q, Double_t obs) {
  Double_t LL = 0.;
  if (obs >= 0.) {
    Double_t a = (1. - q) / 2.; // = 0.025 for 95% confidence interval
    LL = TMath::ChisquareQuantile(a, 2.*obs) / 2.;
  }
  return LL;
}

// Calculate upper confidence limit
//   e.g. to calculate the 68% upper limit for 2 observed events:
//      calcPoissonCLUpper(0.68, 2.)
double calcPoissonCLUpper(Double_t q, Double_t obs) {
  Double_t UL = 0.;
  if (obs >= 0.) {
    Double_t a = 1. - (1. - q) / 2.; // = 0.025 for 95% confidence interval
    UL = TMath::ChisquareQuantile(a, 2.* (obs + 1.)) / 2.;
  }
  return UL;
}


//-----------------------------------------------------------------------------
// Here we print out the number of background events
//-----------------------------------------------------------------------------
//void CalcBackgrounds(THStack* central, TObjArray *paired, TObjArray *unpaired, distrSet &my_set) {
void CalcBackgrounds( TH1D* hist[N_FAKE], TObjArray *paired, TObjArray *unpaired, distrSet &my_set) {

  //  TList* cList = central->GetHists();

  int n_bins;

  double syst_up = 0;
  double syst_dn = 0;
  double mean = 0;
  double value = 0;

  double fakes_mean = 0;
  double fakes_stat = 0;
  double fakes_systup = 0;
  double fakes_systdn = 0;

  double total = 0;
  double total_stat = 0;
  double total_syst_up = 0;
  double total_syst_dn = 0;

  Int_t N_unc_paird = paired->GetSize();

  // TList* of TH1*
  //  for (int i = 0; i < (N_FAKE - 1); i++) { // start from i = 0 in the MC stack 
  for (int i = 1; i < (N_FAKE ); i++) { // start from i = 1 in the MC histograms

	syst_up = 0;
	syst_dn = 0;
	//	TH1D* hc = (TH1D*) cList->At(i);
	TH1D* hc = 	(TH1D*) hist[i]->Clone(); 
	n_bins = hc->GetNbinsX();
	mean = hc->Integral(0, n_bins + 1);
	total += mean;
	//	std::cout << i << " " << description_fake[i] << ": mean=" << mean << std::endl; 
	//paired systematics
	for (int j = 0; j < N_unc_paird; j++) {

	  THStack* st = (THStack*) paired->At(j);
	  TList* pList = st->GetHists();
	  TH1D* hp = (TH1D*) pList->At(i-1);
	  n_bins = hp->GetNbinsX();
	  value = hp->Integral(0, n_bins + 1);
	  //	  std::cout << j << " value=" << value << " // name " << hp->GetName() << std::endl;

	  //p or m 
	  if (value > mean)
		syst_up += pow(value - mean, 2);
	  else
		syst_dn += pow(value - mean, 2);

	  //uncertainty for the sum of the contributions
	  //	  if (i == (N_FAKE - 2)) { // now "total" includes all the contributions from MC (thus -2)
	  if (i == (N_FAKE - 1)) { // now "total" includes all the contributions from MC (thus -1)
		TObjArray* fStack = st->GetStack();
		TH1D* ht = (TH1D*) fStack->At(fStack->GetSize() - 1);
		n_bins = ht->GetNbinsX();
		double t_value = ht->Integral(0, n_bins + 1);

		//Check if "total" is calculated correctly
		/*		{
				TObjArray* my_fStack = central->GetStack();
				TH1D* my_h = (TH1D*) my_fStack->At(my_fStack->GetSize() - 1);
				n_bins = my_h->GetNbinsX();
				double my_total = my_h->Integral(0, n_bins + 1);
				if (fabs((total - my_total) / (total + my_total)) > 1e-3)
				std::cout << "\n\n Total is calculated incorrectly: " << total << " vs " << my_total << "\n";
				}*/

		if (t_value > total)
		  total_syst_up += pow(total - t_value, 2);
		else
		  total_syst_dn += pow(total - t_value, 2);
		//		std::cout << "Total       ===>           " << total << " t_value=" << t_value << std::endl; 
	  }
	}

	if(i == fakes_el_hf_ind_fit || i == fakes_el_lf_ind_fit || i == fakes_mu_hf_ind_fit || i == fakes_mu_lf_ind_fit ){
	  fakes_mean += mean;
	  //	  fakes_stat += pow(getHistError((TH1D*) cList->At(i)),2);
	  fakes_stat += pow(getHistError((TH1D*) hist[i]),2);
	  fakes_systup += syst_up;
	  fakes_systdn += syst_dn;
	}

	syst_up = sqrt(syst_up);
	syst_dn = sqrt(syst_dn);

	//	std::cout << "\n " << description_fake[i + 1] << " & " << mean << " $\\pm$ " << getHistError((TH1D*) cList->At(i))
	//			  << " $^{+" << syst_up << "}_{-" << syst_dn << "}$";

	/*	my_set.backgr_mean[i + 1] = mean;
		my_set.backgr_stat[i + 1] = getHistError((TH1D*) cList->At(i));
		my_set.backgr_systup[i + 1] = syst_up;
		my_set.backgr_systdn[i + 1] = syst_dn;*/

	my_set.backgr_mean[i] = mean;
	my_set.backgr_stat[i] = getHistError((TH1D*) hist[i]);
	my_set.backgr_systup[i] = syst_up;
	my_set.backgr_systdn[i] = syst_dn;

	total_stat += pow(getHistError((TH1D*) hist[i]), 2);
  }



  fakes_stat = sqrt(fakes_stat);
  fakes_systup = sqrt(fakes_systup);
  fakes_systdn = sqrt(fakes_systdn);
  my_set.fakes_mean = fakes_mean;
  my_set.fakes_stat = fakes_stat;
  my_set.fakes_systup = fakes_systup;
  my_set.fakes_systdn = fakes_systdn;
  total_stat = sqrt(total_stat);
  total_syst_up = sqrt(total_syst_up);
  total_syst_dn = sqrt(total_syst_dn);
  my_set.backgr_mean[N_DataMC] = total;
  my_set.backgr_stat[N_DataMC] = total_stat;
  my_set.backgr_systup[N_DataMC] = total_syst_up;
  my_set.backgr_systdn[N_DataMC] = total_syst_dn;

  //  std::cout << "\n Total & " << total << " $\\pm$ " << total_stat << " $^{+" << total_syst_up << "}_{-" << total_syst_dn<< "}$";

  return;

}

//-----------------------------------------------------------------------------                                                                        

double getStackIntegral(THStack* stack) {

  TObjArray* fStack = stack->GetStack();
  TH1D* h = (TH1D*) fStack->At(fStack->GetSize() - 1);
  return h->Integral(0, h->GetNbinsX() + 1, ""); // includes underflow and overflow bins                                                                 
}

//-----------------------------------------------------------------------------                                                                            
double getStackError(THStack* stack) {

  TObjArray* fStack = stack->GetStack();
  TH1D* h = (TH1D*) fStack->At(fStack->GetSize() - 1);

  double error = 0;
  for (int i = 0; i <= h->GetNbinsX() + 1; i++) // includes underflow and overflow bins                                                                    
    error += pow(h->GetBinError(i), 2);

  return sqrt(error);

}

//-----------------------------------------------------------------------------                                                                            
double getHistIntegral(TH1D* h) {

  return h->Integral(0, h->GetNbinsX() + 1, ""); // includes underflow and overflow bins                                                                   
}
//-----------------------------------------------------------------------------                                                                            
double getHistError(TH1D* h) {

  double error = 0;
  for (int i = 0; i <= h->GetNbinsX() + 1; i++) // includes underflow and overflow bins                                                                    
    error += pow(h->GetBinError(i), 2);

  return sqrt(error);

}

/*
//-----------------------------------------------------------------------------
void printBackgrounds(distrSet *my_set_elel, distrSet *my_set_elmu, distrSet *my_set_mumu){

std::cout << std::fixed << std::setprecision(2) << "\n \\begin{tabular}{ l l l l } \n";

std::cout << "\nPrompt Isolated ";
std::cout << "& " << my_set_elel->backgr_mean[1] << "$\\pm$" << my_set_elel->backgr_stat[1] << "$^{+" << my_set_elel->backgr_systup[1] << "}_{-" << my_set_elel->backgr_systdn[1] << "}$ ";
std::cout << "& " << my_set_elmu->backgr_mean[1] << "$\\pm$" << my_set_elmu->backgr_stat[1] << "$^{+" << my_set_elmu->backgr_systup[1] << "}_{-" << my_set_elmu->backgr_systdn[1] << "}$ ";
std::cout << "& " << my_set_mumu->backgr_mean[1] << "$\\pm$" << my_set_mumu->backgr_stat[1] << "$^{+" << my_set_mumu->backgr_systup[1] << "}_{-" << my_set_mumu->backgr_systdn[1] << "}$ ";
std::cout << "& " << my_set_elel->backgr_mean[1]+ my_set_elmu->backgr_mean[1]+ my_set_mumu->backgr_mean[1]
<< "$\\pm$" << sqrt(my_set_elel->backgr_stat[1]*my_set_elel->backgr_stat[1] + my_set_elmu->backgr_stat[1]*my_set_elmu->backgr_stat[1] +my_set_mumu->backgr_stat[1]*my_set_mumu->backgr_stat[1]) 
<< "$^{+" << my_set_elel->backgr_systup[1]+my_set_elmu->backgr_systup[1]+my_set_mumu->backgr_systup[1] << "}_{-" << my_set_elel->backgr_systdn[1]+my_set_elmu->backgr_systdn[1]+my_set_mumu->backgr_systdn[1] << "}$ ";
std::cout << " \\\\ \n";


std::cout << "\nCharge Flip ";
std::cout << "& " << my_set_elel->backgr_mean[charge_flip_ind_fit] << "$\\pm$" << my_set_elel->backgr_stat[charge_flip_ind_fit] << "$^{+" << my_set_elel->backgr_systup[charge_flip_ind_fit] << "}_{-" << my_set_elel->backgr_systdn[charge_flip_ind_fit] << "}$ ";
std::cout << "& " << my_set_elmu->backgr_mean[charge_flip_ind_fit] << "$\\pm$" << my_set_elmu->backgr_stat[charge_flip_ind_fit] << "$^{+" << my_set_elmu->backgr_systup[charge_flip_ind_fit] << "}_{-" << my_set_elmu->backgr_systdn[charge_flip_ind_fit] << "}$ ";
std::cout << "& " << my_set_mumu->backgr_mean[charge_flip_ind_fit] << "$\\pm$" << my_set_mumu->backgr_stat[charge_flip_ind_fit] << "$^{+" << my_set_mumu->backgr_systup[charge_flip_ind_fit] << "}_{-" << my_set_mumu->backgr_systdn[charge_flip_ind_fit] << "}$ ";
std::cout << "& " << my_set_elel->backgr_mean[charge_flip_ind_fit]+my_set_elmu->backgr_mean[charge_flip_ind_fit]+my_set_mumu->backgr_mean[charge_flip_ind_fit]
<< "$\\pm$" << sqrt( my_set_elel->backgr_stat[charge_flip_ind_fit]*my_set_elel->backgr_stat[charge_flip_ind_fit] + my_set_elmu->backgr_stat[charge_flip_ind_fit]*my_set_elmu->backgr_stat[charge_flip_ind_fit] + my_set_mumu->backgr_stat[charge_flip_ind_fit]*my_set_mumu->backgr_stat[charge_flip_ind_fit] ) << "$^{+" << my_set_elel->backgr_systup[charge_flip_ind_fit]+my_set_elmu->backgr_systup[charge_flip_ind_fit]+my_set_mumu->backgr_systup[charge_flip_ind_fit] << "}_{-" << my_set_elel->backgr_systdn[charge_flip_ind_fit]
+my_set_elmu->backgr_systdn[charge_flip_ind_fit]+my_set_mumu->backgr_systdn[charge_flip_ind_fit] << "}$ "
;
std::cout << " \\\\";
 
std::cout << "\nFakes ";
std::cout << "& " << my_set_elel->fakes_mean << "$\\pm$" << my_set_elel->fakes_stat 
<< "$^{+" << my_set_elel->fakes_systup << "}_{-" << my_set_elel->fakes_systdn << "}$ ";
std::cout << "& " << my_set_elmu->fakes_mean << "$\\pm$" << my_set_elmu->fakes_stat 
<< "$^{+" << my_set_elmu->fakes_systup << "}_{-" << my_set_elmu->fakes_systdn << "}$ ";
std::cout << "& " << my_set_mumu->fakes_mean << "$\\pm$" << my_set_mumu->fakes_stat 
<< "$^{+" << my_set_mumu->fakes_systup << "}_{-" << my_set_mumu->fakes_systdn << "}$ ";
// =
std::cout << "& " << my_set_elel->fakes_mean+my_set_elmu->fakes_mean+my_set_mumu->fakes_mean << "$\\pm$" 
<< sqrt(my_set_elel->fakes_stat*my_set_elel->fakes_stat +  my_set_elmu->fakes_stat*my_set_elmu->fakes_stat 
+ my_set_mumu->fakes_stat*my_set_mumu->fakes_stat)
<< "$^{+" << my_set_elel->fakes_systup + my_set_elmu->fakes_systup + my_set_mumu->fakes_systup 
<< "}_{-" << my_set_elel->fakes_systdn + my_set_elmu->fakes_systdn + my_set_mumu->fakes_systdn << "}$ ";
std::cout << " \\\\ \n";

std::cout << "\nTotal ";
std::cout << "& " << my_set_elel->backgr_mean[N_DataMC] << "$\\pm$" << my_set_elel->backgr_stat[N_DataMC] << "$^{+" << my_set_elel->backgr_systup[N_DataMC] << "}_{-" << my_set_elel->backgr_systdn[N_DataMC] << "}$ ";
std::cout << "& " << my_set_elmu->backgr_mean[N_DataMC] << "$\\pm$" << my_set_elmu->backgr_stat[N_DataMC] << "$^{+" << my_set_elmu->backgr_systup[N_DataMC] << "}_{-" << my_set_elmu->backgr_systdn[N_DataMC] << "}$ ";
std::cout << "& " << my_set_mumu->backgr_mean[N_DataMC] << "$\\pm$" << my_set_mumu->backgr_stat[N_DataMC] << "$^{+" << my_set_mumu->backgr_systup[N_DataMC] << "}_{-" << my_set_mumu->backgr_systdn[N_DataMC] << "}$ ";
std::cout << "& " << my_set_elel->backgr_mean[N_DataMC]+ my_set_elmu->backgr_mean[N_DataMC]+ my_set_mumu->backgr_mean[N_DataMC]
<< "$\\pm$" << sqrt(my_set_elel->backgr_stat[N_DataMC]*my_set_elel->backgr_stat[N_DataMC]+my_set_elmu->backgr_stat[N_DataMC]*my_set_elmu->backgr_stat[N_DataMC]+my_set_mumu->backgr_stat[N_DataMC]*my_set_mumu->backgr_stat[N_DataMC])  << "$^{+" << my_set_elel->backgr_systup[N_DataMC]+my_set_elmu->backgr_systup[N_DataMC]+my_set_mumu->backgr_systup[N_DataMC] << "}_{-" << my_set_elel->backgr_systdn[N_DataMC]+my_set_elmu->backgr_systdn[N_DataMC]+my_set_mumu->backgr_systdn[N_DataMC] << "}$ ";
std::cout << " \\\\ ";
  
std::cout << "\nObserved ";
Int_t n_bins = (Int_t)(my_set_elel->NJETS[0]->GetNbinsX()); 
std::cout << "& " << my_set_elel->NJETS[0]->Integral(0, n_bins + 1);
std::cout << "& " << my_set_elmu->NJETS[0]->Integral(0, n_bins + 1);
std::cout << "& " << my_set_mumu->NJETS[0]->Integral(0, n_bins + 1);
std::cout << "& " << my_set_elel->NJETS[0]->Integral(0, n_bins + 1)+ my_set_elmu->NJETS[0]->Integral(0, n_bins + 1)+ my_set_mumu->NJETS[0]->Integral(0, n_bins + 1);
std::cout << " \\\\ \n";
std::cout << "\\end{tabular}\n";

return;
}
*/
//-----------------------------------------------------------------------------

void printBackgrounds(distrAll *my_set){
  // Here we print backgrounds in all regions and all channels

  char logfile[512];
  sprintf(logfile,"/afs/cern.ch/work/o/othrif/workarea/results/v48/Plots/%s/yields_%s.txt", folder, fit_type.c_str());
  FILE *fp;
  fp=fopen(logfile, "w+");

  // Inclusive in channels (ee+em+mm)
  Int_t   n_bins = (Int_t)(my_set->SS3L.SR3L1.fs_comb.NJETS[0]->GetNbinsX());

  fprintf(fp,"----------------------------------------------\n");
  fprintf(fp,"----------------------------------------------\n");
  fprintf(fp,"----------------------------------------------\n");
  
  // Signal Regions
  fprintf(fp,"\n Signal regions \\\\ \n");
  fprintf(fp,"\n\n$ee + e\\mu + \\mu\\mu$ channel\\\\");
  fprintf(fp,"\n \\begin{tabular}{ l l l l l l l l l l} ");
  fprintf(fp,"\n &   SR3L1 & SR3L2 & SR0b1 & SR0b2 & SR1b & SR3b & SR1b_DD & SR3b_DD & SR1b_GG\\\\");
  fprintf(fp,"\nFakes & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ \\\\",  
  my_set->SS3L.SR3L1.fs_comb.fakes_mean, my_set->SS3L.SR3L1.fs_comb.fakes_stat, my_set->SS3L.SR3L1.fs_comb.fakes_systup, my_set->SS3L.SR3L1.fs_comb.fakes_systdn,
  my_set->SS3L.SR3L2.fs_comb.fakes_mean, my_set->SS3L.SR3L2.fs_comb.fakes_stat, my_set->SS3L.SR3L2.fs_comb.fakes_systup, my_set->SS3L.SR3L2.fs_comb.fakes_systdn,
  my_set->SS3L.SR0b1.fs_comb.fakes_mean, my_set->SS3L.SR0b1.fs_comb.fakes_stat, my_set->SS3L.SR0b1.fs_comb.fakes_systup, my_set->SS3L.SR0b1.fs_comb.fakes_systdn,
  my_set->SS3L.SR0b2.fs_comb.fakes_mean, my_set->SS3L.SR0b2.fs_comb.fakes_stat, my_set->SS3L.SR0b2.fs_comb.fakes_systup, my_set->SS3L.SR0b2.fs_comb.fakes_systdn,
  my_set->SS3L.SR1b.fs_comb.fakes_mean, my_set->SS3L.SR1b.fs_comb.fakes_stat, my_set->SS3L.SR1b.fs_comb.fakes_systup, my_set->SS3L.SR1b.fs_comb.fakes_systdn,
  my_set->SS3L.SR3b.fs_comb.fakes_mean, my_set->SS3L.SR3b.fs_comb.fakes_stat, my_set->SS3L.SR3b.fs_comb.fakes_systup, my_set->SS3L.SR3b.fs_comb.fakes_systdn,
  my_set->SS3L.SR1b_DD.fs_comb.fakes_mean, my_set->SS3L.SR1b_DD.fs_comb.fakes_stat, my_set->SS3L.SR1b_DD.fs_comb.fakes_systup, my_set->SS3L.SR1b_DD.fs_comb.fakes_systdn,
  my_set->SS3L.SR3b_DD.fs_comb.fakes_mean, my_set->SS3L.SR3b_DD.fs_comb.fakes_stat, my_set->SS3L.SR3b_DD.fs_comb.fakes_systup, my_set->SS3L.SR3b_DD.fs_comb.fakes_systdn,
  my_set->SS3L.SR1b_GG.fs_comb.fakes_mean, my_set->SS3L.SR1b_GG.fs_comb.fakes_stat, my_set->SS3L.SR1b_GG.fs_comb.fakes_systup, my_set->SS3L.SR1b_GG.fs_comb.fakes_systdn
  );
  fprintf(fp,"\nCharge flip & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$  & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$  & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$  & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$\\\\",
  my_set->SS3L.SR3L1.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.SR3L1.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.SR3L1.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR3L1.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.SR3L2.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.SR3L2.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.SR3L2.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR3L2.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.SR0b1.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.SR0b1.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.SR0b1.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR0b1.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.SR0b2.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.SR0b2.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.SR0b2.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR0b2.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.SR1b.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.SR1b.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.SR1b.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR1b.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.SR3b.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.SR3b.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.SR3b.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR3b.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.SR1b_DD.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.SR1b_DD.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.SR1b_DD.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR1b_DD.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.SR3b_DD.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.SR3b_DD.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.SR3b_DD.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR3b_DD.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.SR1b_GG.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.SR1b_GG.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.SR1b_GG.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.SR1b_GG.fs_comb.backgr_systdn[charge_flip_ind_fit]
  );
  fprintf(fp,"\nPrompt & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$  & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$  & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$  & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ \\\\",
  my_set->SS3L.SR3L1.fs_comb.backgr_mean[1], my_set->SS3L.SR3L1.fs_comb.backgr_stat[1], my_set->SS3L.SR3L1.fs_comb.backgr_systup[1], my_set->SS3L.SR3L1.fs_comb.backgr_systdn[1],
  my_set->SS3L.SR3L2.fs_comb.backgr_mean[1], my_set->SS3L.SR3L2.fs_comb.backgr_stat[1], my_set->SS3L.SR3L2.fs_comb.backgr_systup[1], my_set->SS3L.SR3L2.fs_comb.backgr_systdn[1],
  my_set->SS3L.SR0b1.fs_comb.backgr_mean[1], my_set->SS3L.SR0b1.fs_comb.backgr_stat[1], my_set->SS3L.SR0b1.fs_comb.backgr_systup[1], my_set->SS3L.SR0b1.fs_comb.backgr_systdn[1],
  my_set->SS3L.SR0b2.fs_comb.backgr_mean[1], my_set->SS3L.SR0b2.fs_comb.backgr_stat[1], my_set->SS3L.SR0b2.fs_comb.backgr_systup[1], my_set->SS3L.SR0b2.fs_comb.backgr_systdn[1],
  my_set->SS3L.SR1b.fs_comb.backgr_mean[1], my_set->SS3L.SR1b.fs_comb.backgr_stat[1], my_set->SS3L.SR1b.fs_comb.backgr_systup[1], my_set->SS3L.SR1b.fs_comb.backgr_systdn[1],
  my_set->SS3L.SR3b.fs_comb.backgr_mean[1], my_set->SS3L.SR3b.fs_comb.backgr_stat[1], my_set->SS3L.SR3b.fs_comb.backgr_systup[1], my_set->SS3L.SR3b.fs_comb.backgr_systdn[1],
  my_set->SS3L.SR1b_DD.fs_comb.backgr_mean[1], my_set->SS3L.SR1b_DD.fs_comb.backgr_stat[1], my_set->SS3L.SR1b_DD.fs_comb.backgr_systup[1], my_set->SS3L.SR1b_DD.fs_comb.backgr_systdn[1],
  my_set->SS3L.SR3b_DD.fs_comb.backgr_mean[1], my_set->SS3L.SR3b_DD.fs_comb.backgr_stat[1], my_set->SS3L.SR3b_DD.fs_comb.backgr_systup[1], my_set->SS3L.SR3b_DD.fs_comb.backgr_systdn[1],
  my_set->SS3L.SR1b_GG.fs_comb.backgr_mean[1], my_set->SS3L.SR1b_GG.fs_comb.backgr_stat[1], my_set->SS3L.SR1b_GG.fs_comb.backgr_systup[1], my_set->SS3L.SR1b_GG.fs_comb.backgr_systdn[1]
  );

  fprintf(fp,"\nTotal & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ \\\\",
  my_set->SS3L.SR3L1.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.SR3L1.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.SR3L1.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR3L1.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.SR3L2.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.SR3L2.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.SR3L2.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR3L2.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.SR0b1.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.SR0b1.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.SR0b1.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR0b1.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.SR0b2.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.SR0b2.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.SR0b2.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR0b2.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.SR1b.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.SR1b.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.SR1b.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR1b.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.SR3b.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.SR3b.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.SR3b.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR3b.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.SR1b_DD.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.SR1b_DD.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.SR1b_DD.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR1b_DD.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.SR3b_DD.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.SR3b_DD.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.SR3b_DD.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR3b_DD.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.SR1b_GG.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.SR1b_GG.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.SR1b_GG.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.SR1b_GG.fs_comb.backgr_systdn[N_DataMC]
  );
    fprintf(fp,"\nData & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f & %.2f \\\\",
  my_set->SS3L.SR3L1.fs_comb.NJETS[0]->Integral(0, n_bins+1), 
  my_set->SS3L.SR3L2.fs_comb.NJETS[0]->Integral(0, n_bins+1), 
  my_set->SS3L.SR0b1.fs_comb.NJETS[0]->Integral(0, n_bins+1), 
  my_set->SS3L.SR0b2.fs_comb.NJETS[0]->Integral(0, n_bins+1), 
  my_set->SS3L.SR1b.fs_comb.NJETS[0]->Integral(0, n_bins+1),
  my_set->SS3L.SR3b.fs_comb.NJETS[0]->Integral(0, n_bins+1),
  my_set->SS3L.SR1b_DD.fs_comb.NJETS[0]->Integral(0, n_bins+1),
  my_set->SS3L.SR3b_DD.fs_comb.NJETS[0]->Integral(0, n_bins+1),
  my_set->SS3L.SR1b_GG.fs_comb.NJETS[0]->Integral(0, n_bins+1)
  );
  fprintf(fp,"\n \\end{tabular}\n");
   
  // Validation Regions
  fprintf(fp,"\n Signal regions \\\\ \n");
  fprintf(fp,"\n\n$ee + e\\mu + \\mu\\mu$ channel\\\\");
  fprintf(fp,"\n \\begin{tabular}{ l l l l l} ");
  fprintf(fp,"\n & VRWW & VRWZ4j & VRWZ5j & VRttW & VRttZ \\\\");
  fprintf(fp,"\nFakes & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$  \\\\",  
  my_set->SS3L.VRWW.fs_comb.fakes_mean, my_set->SS3L.VRWW.fs_comb.fakes_stat, my_set->SS3L.VRWW.fs_comb.fakes_systup, my_set->SS3L.VRWW.fs_comb.fakes_systdn,
  my_set->SS3L.VRWZ4j.fs_comb.fakes_mean, my_set->SS3L.VRWZ4j.fs_comb.fakes_stat, my_set->SS3L.VRWZ4j.fs_comb.fakes_systup, my_set->SS3L.VRWZ4j.fs_comb.fakes_systdn,
  my_set->SS3L.VRWZ5j.fs_comb.fakes_mean, my_set->SS3L.VRWZ5j.fs_comb.fakes_stat, my_set->SS3L.VRWZ5j.fs_comb.fakes_systup, my_set->SS3L.VRWZ5j.fs_comb.fakes_systdn,
  my_set->SS3L.VRttW.fs_comb.fakes_mean, my_set->SS3L.VRttW.fs_comb.fakes_stat, my_set->SS3L.VRttW.fs_comb.fakes_systup, my_set->SS3L.VRttW.fs_comb.fakes_systdn,
  my_set->SS3L.VRttZ.fs_comb.fakes_mean, my_set->SS3L.VRttZ.fs_comb.fakes_stat, my_set->SS3L.VRttZ.fs_comb.fakes_systup, my_set->SS3L.VRttZ.fs_comb.fakes_systdn
  );
  fprintf(fp,"\nCharge flip & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$\\\\",
  my_set->SS3L.VRWW.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.VRWW.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.VRWW.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.VRWW.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.VRWZ4j.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.VRWZ4j.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.VRWZ4j.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.VRWZ4j.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.VRWZ5j.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.VRWZ5j.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.VRWZ5j.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.VRWZ5j.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.VRttW.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.VRttW.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.VRttW.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.VRttW.fs_comb.backgr_systdn[charge_flip_ind_fit],
  my_set->SS3L.VRttZ.fs_comb.backgr_mean[charge_flip_ind_fit], my_set->SS3L.VRttZ.fs_comb.backgr_stat[charge_flip_ind_fit], my_set->SS3L.VRttZ.fs_comb.backgr_systup[charge_flip_ind_fit], my_set->SS3L.VRttZ.fs_comb.backgr_systdn[charge_flip_ind_fit]
  );
  fprintf(fp,"\nPrompt & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ \\\\",
  my_set->SS3L.VRWW.fs_comb.backgr_mean[1], my_set->SS3L.VRWW.fs_comb.backgr_stat[1], my_set->SS3L.VRWW.fs_comb.backgr_systup[1], my_set->SS3L.VRWW.fs_comb.backgr_systdn[1],
  my_set->SS3L.VRWZ4j.fs_comb.backgr_mean[1], my_set->SS3L.VRWZ4j.fs_comb.backgr_stat[1], my_set->SS3L.VRWZ4j.fs_comb.backgr_systup[1], my_set->SS3L.VRWZ4j.fs_comb.backgr_systdn[1],
  my_set->SS3L.VRWZ5j.fs_comb.backgr_mean[1], my_set->SS3L.VRWZ5j.fs_comb.backgr_stat[1], my_set->SS3L.VRWZ5j.fs_comb.backgr_systup[1], my_set->SS3L.VRWZ5j.fs_comb.backgr_systdn[1],
  my_set->SS3L.VRttW.fs_comb.backgr_mean[1], my_set->SS3L.VRttW.fs_comb.backgr_stat[1], my_set->SS3L.VRttW.fs_comb.backgr_systup[1], my_set->SS3L.VRttW.fs_comb.backgr_systdn[1],
  my_set->SS3L.VRttZ.fs_comb.backgr_mean[1], my_set->SS3L.VRttZ.fs_comb.backgr_stat[1], my_set->SS3L.VRttZ.fs_comb.backgr_systup[1], my_set->SS3L.VRttZ.fs_comb.backgr_systdn[1]
  );

  fprintf(fp,"\nTotal & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ & %.2f$\\pm$%.2f$^{+%.2f}_{-%.2f}$ \\\\",
  my_set->SS3L.VRWW.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.VRWW.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.VRWW.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.VRWW.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.VRWZ4j.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.VRWZ4j.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.VRWZ4j.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.VRWZ4j.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.VRWZ5j.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.VRWZ5j.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.VRWZ5j.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.VRWZ5j.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.VRttW.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.VRttW.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.VRttW.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.VRttW.fs_comb.backgr_systdn[N_DataMC],
  my_set->SS3L.VRttZ.fs_comb.backgr_mean[N_DataMC], my_set->SS3L.VRttZ.fs_comb.backgr_stat[N_DataMC], my_set->SS3L.VRttZ.fs_comb.backgr_systup[N_DataMC], my_set->SS3L.VRttZ.fs_comb.backgr_systdn[N_DataMC]
  );
  		  fprintf(fp,"\nData & %.2f & %.2f & %.2f & %.2f & %.2f  \\\\",
  		  my_set->SS3L.VRWW.fs_comb.NJETS[0]->Integral(0, n_bins+1), 
  		  my_set->SS3L.VRWZ4j.fs_comb.NJETS[0]->Integral(0, n_bins+1), 
            my_set->SS3L.VRWZ5j.fs_comb.NJETS[0]->Integral(0, n_bins+1), 
  		  my_set->SS3L.VRttW.fs_comb.NJETS[0]->Integral(0, n_bins+1), 
  		  my_set->SS3L.VRttZ.fs_comb.NJETS[0]->Integral(0, n_bins+1)
  //		  my_set->SS3L.SR1b.fs_comb.NJETS[0]->Integral(0, n_bins+1),
  //		  my_set->SS3L.SR3b.fs_comb.NJETS[0]->Integral(0, n_bins+1),
  //		  my_set->SS3L.SR1b_DD.fs_comb.NJETS[0]->Integral(0, n_bins+1),
  //		  my_set->SS3L.SR3b_DD.fs_comb.NJETS[0]->Integral(0, n_bins+1),
  //		  my_set->SS3L.SR1b_GG.fs_comb.NJETS[0]->Integral(0, n_bins+1)
				  );
  fprintf(fp,"\n \\end{tabular}\n");

  // ee channel

  // em channel

  // mm channel

  

  fclose(fp);

  return;
}



//-----------------------------------------------------------------------------
// Main routine
//-----------------------------------------------------------------------------

int main(int argc, char **argv ) {
  
  if (argc < 3) {
	std::cout << "Usage: " << argv[0] << " PATH FOLDER\n";
	return 1;
  }

  SetAtlasStyle(); 
  
  //------------------------------------------
  // tags
  const string tag = "";
  path = argv[1];
  folder = argv[2];
  //------------------------------------------

  //------------------------------------------
  // Define distributions
  
  // Background and data at detector level
  distrAll det_lvl;
  
  // SUSY signal
  distrSigAll signal;

  // Paired systematics
  
  //Fr(HF-->e)
  distrAll det_lvl_pFrE;
  distrAll det_lvl_mFrE;
  
  //Fr(HF-->mu)
  distrAll det_lvl_pFrMu;
  distrAll det_lvl_mFrMu;
  
  //Fr(LF-->e)
  distrAll det_lvl_pFlE;
  distrAll det_lvl_mFlE;
  
  //Fr(LF-->mu)
  distrAll det_lvl_pFlMu;
  distrAll det_lvl_mFlMu;
  
  //charge-flip
  distrAll det_lvl_pCF;
  distrAll det_lvl_mCF;
  
  // Luminosity
  distrAll det_lvl_pLUMI;
  distrAll det_lvl_mLUMI;
  //  distrAll* det_lvl_pLUMI = malloc(sizeof(distrAll));
  //  distrAll* det_lvl_mLUMI = malloc(sizeof(distrAll));
  
  // cross sections
  //distrAll det_lvl_pTTbar;
  //  distrAll det_lvl_mTTbar;

  // Unpaired systematics
  
  // Generator
  //  distrAll det_lvl_pGen;


  for(int itr=0; itr<1; itr++){ 
	itr = 0;
	std::cout << "itr " << itr << std::endl;
  
	//------------------------------------------
	// Get data
	std::cout << "\nStart reading files...\n";

	std::cout << "\n// Nominal\n";
	std::cout << "reading data ";
	getData_All(det_lvl, tag, "");
	std::cout << "reading signal ";
	getData_SigAll(signal, tag, ""); // comment out if you don't want to plot signal
	
	// fakes
  
	// Fr(HF-->e)
	std::cout << "reading HF El ";
	getData_All(det_lvl_pFrE, tag, "_pFrE");
	getData_All(det_lvl_mFrE, tag, "_mFrE");
  
	// Fr(HF-->mu)
	std::cout << "reading HF Mu ";
	getData_All(det_lvl_pFrMu, tag, "_pFrMu");
	getData_All(det_lvl_mFrMu, tag, "_mFrMu");
  
	// Fr(LF-->e)
	std::cout << "reading LF El ";
	getData_All(det_lvl_pFlE, tag, "_pFlE");
	getData_All(det_lvl_mFlE, tag, "_mFlE");
  
	// Fr(LF-->mu)
	std::cout << "reading LF Mu ";
	getData_All(det_lvl_pFlMu, tag, "_pFlMu");
	getData_All(det_lvl_mFlMu, tag, "_mFlMu");   

	// charge-flip
	std::cout << "reading Charge flip ";
	getData_All(det_lvl_pCF, tag, "_pCF");
	getData_All(det_lvl_mCF, tag, "_mCF");
  
  
	std::cout << "// Systematics for luminosity\n";
	std::cout << "==> up\n";
	getData_All(det_lvl_pLUMI, tag, "_pLUMI");
	std::cout << "==> down\n";
	getData_All(det_lvl_mLUMI, tag, "_mLUMI");
	
	/*	  std::cout << "Systematics for ttbar cross section\n\n";
		  std::cout << "==> up\n";
		  getData_All(det_lvl_pTTbar, tag, "_pTTbar");
		  std::cout << "==> down\n";
		  getData_All(det_lvl_mTTbar, tag, "_mTTbar");

		  std::cout << "Systematics for ttbar generator\n\n";
		  getData_All(det_lvl_pGen, tag, "powhegpythia6TTBar", ttbar_ind, "pGen");
	*/

	std::cout << "\n...done reading files\n";
	//------------------------------------------
	// Scalings  
	std::cout << "\nStart scaling ...\n";
  
	//luminosity
	Float_t c_lumi_up = 1. + 0.04;//0.05;
	Float_t c_lumi_dn = 1. - 0.04;//0.05;
	//  scaleLumi_All(det_lvl_pLUMI, c_lumi_up);
	//  scaleLumi_All(det_lvl_mLUMI, c_lumi_dn);
  
	//scale ttbar x-section
	//  scaleXSect_All(det_lvl_pTTbar, ttbar_ind, (1. + 0.0));
	//  scaleXSect_All(det_lvl_mTTbar, ttbar_ind, (1. - 0.0));

	// scale signal xsection up to see it
	//scaleXSect_SigAll(signal, 0, 100);
	//  scaleXSect_SigAll(signal, 1, 1e8);
	//  scaleXSect_SigAll(signal, 2, 1e8);

	std::cout << "\n...done scaling\n";
  
	char inputfile[512];
	sprintf(inputfile,"/afs/cern.ch/work/o/othrif/workarea/myFramework/Plotter/data/%s/input_fit_%s.log", folder, folder);
	FILE *fpin = fopen(inputfile,"r");

	if(itr==0)
	  fit_type = "Pre";
  
	if(fpin && itr==1){
	  int n=0; float x[5]={0.0}; float xerr[5]={0.0};
	  while (!feof(fpin)) {
		fscanf(fpin, "%f %f",  &x[n], &xerr[n] );
		printf("%-25s %f %f\n", description_fake[n+2].c_str(), x[n], xerr[n]);
		n++;
	  }
	
	  my_charge_flip = x[0];
	  my_FR_hf_e =  x[1];
	  my_FR_lf_e = x[2];
	  my_FR_hf_mu = x[3];
	  my_FR_lf_mu = x[4];
	  my_charge_flip_err = xerr[0];
	  my_FR_hf_e_err = xerr[1];
	  my_FR_lf_e_err = xerr[2];
	  my_FR_hf_mu_err = xerr[3];
	  my_FR_lf_mu_err = xerr[4];  
	  fit_type = "Post";
	}
	else
	  printf("Couldn't open %s\n", inputfile);
  
  
	printf("Corrections\n");
	printf("chFlip: %.2f %.2f\n", my_charge_flip, my_charge_flip_err);
	printf("HF EL: %.2f %.2f\n", my_FR_hf_e, my_FR_hf_e_err);
	printf("LF EL: %.2f %.2f\n", my_FR_lf_e, my_FR_lf_e_err);
	printf("HF MU: %.2f %.2f\n", my_FR_hf_mu, my_FR_hf_mu_err);
	printf("LF MU: %.2f %.2f\n", my_FR_lf_mu, my_FR_lf_mu_err);
	printf("\n\n");
  

	//****************************************************************************//   
	setFakeRates_All(det_lvl, my_charge_flip, my_FR_hf_e, my_FR_lf_e, my_FR_hf_mu, my_FR_lf_mu);
	setFakeRates_All(det_lvl_pLUMI, my_charge_flip, my_FR_hf_e, my_FR_lf_e, my_FR_hf_mu, my_FR_lf_mu);
	setFakeRates_All(det_lvl_mLUMI, my_charge_flip, my_FR_hf_e, my_FR_lf_e, my_FR_hf_mu, my_FR_lf_mu);
	
	//heavy-flavor jets
	setFakeRates_All(det_lvl_pFrE, my_charge_flip, my_FR_hf_e +  my_FR_hf_e_err, my_FR_lf_e, my_FR_hf_mu, my_FR_lf_mu);
	setFakeRates_All(det_lvl_mFrE, my_charge_flip, my_FR_hf_e - my_FR_hf_e_err, my_FR_lf_e, my_FR_hf_mu, my_FR_lf_mu);
	setFakeRates_All(det_lvl_pFrMu, my_charge_flip, my_FR_hf_e, my_FR_lf_e, my_FR_hf_mu + my_FR_hf_mu_err, my_FR_lf_mu);
	setFakeRates_All(det_lvl_mFrMu, my_charge_flip, my_FR_hf_e, my_FR_lf_e, my_FR_hf_mu - my_FR_hf_mu_err, my_FR_lf_mu);
	
	//light-flavor jets
	setFakeRates_All(det_lvl_pFlE, my_charge_flip, my_FR_hf_e, my_FR_lf_e +  my_FR_lf_e_err, my_FR_hf_mu, my_FR_lf_mu);
	setFakeRates_All(det_lvl_mFlE, my_charge_flip, my_FR_hf_e, my_FR_lf_e -  my_FR_lf_e_err, my_FR_hf_mu, my_FR_lf_mu);
	setFakeRates_All(det_lvl_pFlMu, my_charge_flip, my_FR_hf_e, my_FR_lf_e, my_FR_hf_mu, my_FR_lf_mu + my_FR_lf_mu_err);
	setFakeRates_All(det_lvl_mFlMu, my_charge_flip, my_FR_hf_e, my_FR_lf_e, my_FR_hf_mu, my_FR_lf_mu- my_FR_lf_mu_err);
  
	//charge-flip
	setFakeRates_All(det_lvl_pCF, my_charge_flip + my_charge_flip_err, my_FR_hf_e, my_FR_lf_e, my_FR_hf_mu, my_FR_lf_mu);
	setFakeRates_All(det_lvl_mCF, my_charge_flip - my_charge_flip_err, my_FR_hf_e, my_FR_lf_e, my_FR_hf_mu, my_FR_lf_mu);
	
	//------------------------------------------
	// Weight with new scales 
	std::cout << "\nStart re-weighting...\n";
	std::cout << "\nRe-weighting background and data\n";
	weightData_All(det_lvl);
	std::cout << "\nRe-weighting signal\n";
	weightData_SigAll(signal);
	
	  std::cout << "\nRe-weighting luminosity\n";
	  weightData_All(det_lvl_pLUMI);
	  weightData_All(det_lvl_mLUMI);
  
	  std::cout << "\nRe-weighting fakes\n";
	  weightData_All(det_lvl_pCF);
	  weightData_All(det_lvl_mCF);
  
	  weightData_All(det_lvl_pFrE);
	  weightData_All(det_lvl_mFrE);
  
	  weightData_All(det_lvl_pFlE);
	  weightData_All(det_lvl_mFlE);
  
	  weightData_All(det_lvl_pFrMu);
	  weightData_All(det_lvl_mFrMu);

	  weightData_All(det_lvl_pFlMu);
	  weightData_All(det_lvl_mFlMu);
	
	//  std::cout << "\nRe-weighting cross sections\n";
	//  weightData_All(det_lvl_pTTbar);
	//  weightData_All(det_lvl_mTTbar);

	//  std::cout << "\nRe-weighting alternate generators\n";
	//  weightData_All(det_lvl_pGen);

	std::cout << "\n...done re-weighting histograms\n";
	//------------------------------------------
  
	//------------------------------------------
	// Error-bar machinery
	distrAll* paired[N_unc_paired];
	distrAll *unpaired[N_unc_unpaired];

	int ind_paired=0;
	paired[ind_paired++] = &det_lvl_pLUMI;
	paired[ind_paired++] = &det_lvl_mLUMI;
  
	paired[ind_paired++] = &det_lvl_pCF;
	paired[ind_paired++] = &det_lvl_mCF;

	paired[ind_paired++] = &det_lvl_pFrE;
	paired[ind_paired++] = &det_lvl_mFrE;

	paired[ind_paired++] = &det_lvl_pFrMu;
	paired[ind_paired++] = &det_lvl_mFrMu;

	paired[ind_paired++] = &det_lvl_pFlE;
	paired[ind_paired++] = &det_lvl_mFlE;

	paired[ind_paired++] = &det_lvl_pFlMu;
	paired[ind_paired++] = &det_lvl_mFlMu;
  
	//  paired[ind_paired++] = &det_lvl;//_pTTbar;
	//  paired[ind_paired++] = &det_lvl;//_mTTbar;

	int ind_unpaired=0;
	unpaired[ind_unpaired++] = &det_lvl;//;//_pGen;

	//------------------------------------------
 
	//------------------------------------------
	// Draw observables
	draw_All(det_lvl, signal, paired, unpaired, "MC");
	//------------------------------------------

	/*  
	//----------------------------------------------------------------------
	std::cout << "\n\n ---------------------- PRE -------------------- \n\n";
	printBackgrounds(&(det_lvl.SS3L.incl.fs_elel), &(det_lvl.SS3L.incl.fs_elmu), &(det_lvl.SS3L.incl.fs_mumu));
	std::cout << "\n\n ---------------------- CR0b -------------------- \n\n";
	printBackgrounds(&(det_lvl.SS3L.CR0b.fs_elel), &(det_lvl.SS3L.CR0b.fs_elmu), &(det_lvl.SS3L.CR0b.fs_mumu));
	std::cout << "\n\n ---------------------- CR1b -------------------- \n\n";
	printBackgrounds(&(det_lvl.SS3L.CR1b.fs_elel), &(det_lvl.SS3L.CR1b.fs_elmu), &(det_lvl.SS3L.CR1b.fs_mumu));
	*/
	printBackgrounds(&det_lvl);
  } // for itr

  gSystem->Exit(0);
  return 0;

}
