// To DO:
// Current code if for MC only
// Have to add another code for DataMC
// add flags: luminosity, SS or OS, ratio, signal, signal grid
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
#include "TObjArray.h"
#include "TMinuit.h"
#include "RooStats/NumberCountingUtils.h"

//here are the project-specific files
#include "Plotter/plotter_MCSignal.h"
#include "Utils/AtlasUtils.h"
#include "Utils/AtlasStyle.h"

using namespace std;

//-----------------------------------------------------------------------------
// TO DO: integrate in code
//string FS = "SS3L";
//string FS = "OS";
char* path;
char* folder;
bool test_me = false;
//-----------------------------------------------------------------------------

void getData_All(distrAll& set, string tag, const char* syst_tag) {
  
  getData_All(set, "" + tag, "", -1, syst_tag);

  return;
}

//-----------------------------------------------------------------------------

void getData_All(distrAll& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {

  std::cout << "reading data SS3L ..." << std::endl;  
  getData_Signature(set.SS3L, "SS3L" + tag, "", -1, syst_tag);
  /*std::cout << "reading data OS ..." << std::endl;  
	getData_Signature(set.OS, "OS" + tag, "", -1, syst_tag);
	std::cout << "reading data SS ..." << std::endl;  
	getData_Signature(set.SS, "SS" + tag, "", -1, syst_tag);
	std::cout << "reading data 3L ..." << std::endl;  
	getData_Signature(set.L3, "3L" + tag, "", -1, syst_tag);*/

  return;
}

//-----------------------------------------------------------------------------

void getData_Signature(distrSignature& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {

  getData_Region(set.PRE, "PRE_" + tag, "", -1, syst_tag);
  getData_Region(set.SR3b, "SR1b1_" + tag, "", -1, syst_tag);

  getData_Region(set.SR3bmNJETS, "SR1b2_" + tag, "", -1, syst_tag);
  getData_Region(set.SR3bmNBJETS, "SRlow_" + tag, "", -1, syst_tag);
  getData_Region(set.SR3bmMET, "SRhigh_" + tag, "", -1, syst_tag);
  getData_Region(set.SR3bmMeff, "SR3b1_" + tag, "", -1, syst_tag);
  /*getData_Region(set.CR0b, "CR0b_" + tag, "", -1, syst_tag);
	getData_Region(set.CR1b, "CR1b_" + tag, "", -1, syst_tag);
	getData_Region(set.CR2b, "CR2b_" + tag, "", -1, syst_tag);
	getData_Region(set.CR3b, "CR3b_" + tag, "", -1, syst_tag);
	getData_Region(set.SR3L1, "SR3L1_" + tag, "", -1, syst_tag);  
	getData_Region(set.SR3L2, "SR3L2_" + tag, "", -1, syst_tag);
	getData_Region(set.SR0b1, "SR0b1_" + tag, "", -1, syst_tag);
	getData_Region(set.SR0b2, "SR0b2_" + tag, "", -1, syst_tag);
	getData_Region(set.SR0b5, "SR0b5_" + tag, "", -1, syst_tag)j;
	getData_Region(set.SR1b1, "SR1b1_" + tag, "", -1, syst_tag);
	getData_Region(set.SR1b2, "SR1b2_" + tag, "", -1, syst_tag);
	getData_Region(set.SR2b1, "SR2b1_" + tag, "", -1, syst_tag);
	getData_Region(set.SR2b2, "SR2b2_" + tag, "", -1, syst_tag);
	getData_Region(set.SR3b1, "SR3b1_" + tag, "", -1, syst_tag);
	getData_Region(set.SR3b2, "SR3b2_" + tag, "", -1, syst_tag);
	getData_Region(set.SRCMS, "SRCMS_" + tag, "", -1, syst_tag);
	getData_Region(set.SR3L;, "SR3L;_" + tag, "", -1, syst_tag);*/

  return;
}

//-----------------------------------------------------------------------------

void getData_Region(distrRegion& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {

  //  getData_Set(set.fs_elel, "ee_" + tag, "", -1, syst_tag);
  //  getData_Set(set.fs_elmu, "em_" + tag, "", -1, syst_tag);
  // getData_Set(set.fs_mumu, "mm_" + tag, "", -1, syst_tag);
  getData_Set(set.fs_comb, "comb_" + tag, "", -1, syst_tag);

  return;
}

//-----------------------------------------------------------------------------

void getData_Set(distrSet& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag){

  set.int_lumi = 1.; //lumi;
  set.syst_tag = syst_tag;
  char temp_file[512];
  char temp_tag[256];
  TFile *f_data;

  set.file_name[0] = tag;

  std::sprintf(temp_file, "%s/%s/merged.%s.root", path, folder, folder);
  f_data = new TFile(temp_file, "READ");

  for (int i = 0; i < N_MC; i++){
	set.color[i] = 0;
	set.lineColor[i] = 1;
  }

  // 	Specify the colors
  set.color[0] = 27; 
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
  
  for (int i = 0; i < N_MC; i++) {

 // N-1 plots first
	std::cout << tag.data() << std::endl;
	if(strstr(tag.data(),"METoMeff") != NULL ){
		// NJETS
	std::sprintf(temp_tag, "Meff_%s_mc_%s", processes[i].c_str(),tag.data());
	std::printf("Meff_%s_mc_%s\n", processes[i].c_str(),tag.data());
	set.NJETS[i] =(TH1D*) f_data->Get(temp_tag);
	std::sprintf(temp_tag, "METoMeff_%s", tag.data());
	set.NJETS[i]->SetName(temp_tag);
	set.NJETS[i]->SetDirectory(gROOT);
	set.NJETS[i]->SetLineColor(set.lineColor[i]);
	set.NJETS[i]->SetFillColor(set.color[i]);
	set.NJETS[i]->SetLineWidth(1);
  }
	else if(strstr(tag.data(),"Meff") != NULL ){
		  // Meff
	  std::sprintf(temp_tag, "Meff_%s_mc_%s", processes[i].c_str(),tag.data());
	std::printf("Meff_%s_mc_%s\n", processes[i].c_str(),tag.data());
	  set.Meff[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Meff_%s", tag.data());
	  set.Meff[i]->SetName(temp_tag);
	  set.Meff[i]->SetDirectory(gROOT);
	  set.Meff[i]->SetLineColor(set.lineColor[i]);
	  set.Meff[i]->SetFillColor(set.color[i]);
	  set.Meff[i]->SetLineWidth(1);

  }
	else if(strstr(tag.data(),"NBJETS") != NULL ){
		// NBJETS
	std::sprintf(temp_tag, "NBJETS_%s_mc_%s", processes[i].c_str(),tag.data());
	std::printf("NBJETS_%s_mc_%s\n", processes[i].c_str(),tag.data());
	set.NBJETS[i] =(TH1D*) f_data->Get(temp_tag);
	std::sprintf(temp_tag, "NBJETS_%s", tag.data());
	set.NBJETS[i]->SetName(temp_tag);
	set.NBJETS[i]->SetDirectory(gROOT);
	set.NBJETS[i]->SetLineColor(set.lineColor[i]);
	set.NBJETS[i]->SetFillColor(set.color[i]);
	set.NBJETS[i]->SetLineWidth(1);
  }
	else if(strstr(tag.data(),"MET") != NULL ){
		  // MET
	  std::sprintf(temp_tag, "MET_%s_mc_%s", processes[i].c_str(),tag.data());
	std::printf("MET_%s_mc_%s\n", processes[i].c_str(),tag.data());
	  set.MET[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "MET_%s", tag.data());
	  set.MET[i]->SetName(temp_tag);
	  set.MET[i]->SetDirectory(gROOT);
	  set.MET[i]->SetLineColor(set.lineColor[i]);
	  set.MET[i]->SetFillColor(set.color[i]);
	  set.MET[i]->SetLineWidth(1);

  }
  else{

	// NJETS
	std::sprintf(temp_tag, "NJETS_%s_mc_%s", processes[i].c_str(),tag.data());
	std::printf("NJETS_%s_mc_%s\n", processes[i].c_str(),tag.data());
	set.NJETS[i] =(TH1D*) f_data->Get(temp_tag);
	std::sprintf(temp_tag, "NJETS_%s", tag.data());
	set.NJETS[i]->SetName(temp_tag);
	set.NJETS[i]->SetDirectory(gROOT);
	set.NJETS[i]->SetLineColor(set.lineColor[i]);
	set.NJETS[i]->SetFillColor(set.color[i]);
	set.NJETS[i]->SetLineWidth(1);
	if(!test_me){
	  // pt_jet1
	  std::sprintf(temp_tag, "pt_jet1_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.pt_jet1[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_jet1_%s", tag.data());
	  set.pt_jet1[i]->SetName(temp_tag);
	  set.pt_jet1[i]->SetDirectory(gROOT);
	  set.pt_jet1[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet1[i]->SetFillColor(set.color[i]);
	  set.pt_jet1[i]->SetLineWidth(1);

	  // pt_jet2
	  std::sprintf(temp_tag, "pt_jet2_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.pt_jet2[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_jet2_%s", tag.data());
	  set.pt_jet2[i]->SetName(temp_tag);
	  set.pt_jet2[i]->SetDirectory(gROOT);
	  set.pt_jet2[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet2[i]->SetFillColor(set.color[i]);
	  set.pt_jet2[i]->SetLineWidth(1);

	  // NBJETS
	  std::sprintf(temp_tag, "NBJETS_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.NBJETS[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "NBJETS_%s", tag.data());
	  set.NBJETS[i]->SetName(temp_tag);
	  set.NBJETS[i]->SetDirectory(gROOT);
	  set.NBJETS[i]->SetLineColor(set.lineColor[i]);
	  set.NBJETS[i]->SetFillColor(set.color[i]);
	  set.NBJETS[i]->SetLineWidth(1);

	  // pt_bjet1
	  std::sprintf(temp_tag, "pt_bjet1_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.pt_bjet1[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_bjet1_%s", tag.data());
	  set.pt_bjet1[i]->SetName(temp_tag);
	  set.pt_bjet1[i]->SetDirectory(gROOT);
	  set.pt_bjet1[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet1[i]->SetFillColor(set.color[i]);
	  set.pt_bjet1[i]->SetLineWidth(1);

	  // pt_bjet2
	  std::sprintf(temp_tag, "pt_bjet2_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.pt_bjet2[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_bjet2_%s", tag.data());
	  set.pt_bjet2[i]->SetName(temp_tag);
	  set.pt_bjet2[i]->SetDirectory(gROOT);
	  set.pt_bjet2[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet2[i]->SetFillColor(set.color[i]);
	  set.pt_bjet2[i]->SetLineWidth(1);

	  // Nmu
	  //	  std::sprintf(temp_tag, "Nmu_%s_mc_%s", processes[i].c_str(),tag.data());
	  std::sprintf(temp_tag, "mu1_pt_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.Nmu[i] =(TH1D*) f_data->Get(temp_tag);
	  //	  std::sprintf(temp_tag, "Nmu_%s", tag.data());
	  std::sprintf(temp_tag, "mu1_pt_%s", tag.data());
	  set.Nmu[i]->SetName(temp_tag);
	  set.Nmu[i]->SetDirectory(gROOT);
	  set.Nmu[i]->SetLineColor(set.lineColor[i]);
	  set.Nmu[i]->SetFillColor(set.color[i]);
	  set.Nmu[i]->SetLineWidth(1);

	  // mu1_pt
	  std::sprintf(temp_tag, "mu1_pt_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.mu1_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu1_pt_%s", tag.data());
	  set.mu1_pt[i]->SetName(temp_tag);
	  set.mu1_pt[i]->SetDirectory(gROOT);
	  set.mu1_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu1_pt[i]->SetFillColor(set.color[i]);
	  set.mu1_pt[i]->SetLineWidth(1);

	  // mu2_pt
	  std::sprintf(temp_tag, "mu2_pt_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.mu2_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu2_pt_%s", tag.data());
	  set.mu2_pt[i]->SetName(temp_tag);
	  set.mu2_pt[i]->SetDirectory(gROOT);
	  set.mu2_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu2_pt[i]->SetFillColor(set.color[i]);
	  set.mu2_pt[i]->SetLineWidth(1);

	  // mu_eta
	  std::sprintf(temp_tag, "mu_eta_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.mu_eta[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu_eta_%s", tag.data());
	  set.mu_eta[i]->SetName(temp_tag);
	  set.mu_eta[i]->SetDirectory(gROOT);
	  set.mu_eta[i]->SetLineColor(set.lineColor[i]);
	  set.mu_eta[i]->SetFillColor(set.color[i]);
	  set.mu_eta[i]->SetLineWidth(1);

	  // Nel
	  //	  std::sprintf(temp_tag, "Nel_%s_mc_%s", processes[i].c_str(),tag.data());
	  std::sprintf(temp_tag, "el1_pt_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.Nel[i] =(TH1D*) f_data->Get(temp_tag);
	  //	  std::sprintf(temp_tag, "Nel_%s", tag.data());
	  std::sprintf(temp_tag, "el1_pt_%s", tag.data());
	  set.Nel[i]->SetName(temp_tag);
	  set.Nel[i]->SetDirectory(gROOT);
	  set.Nel[i]->SetLineColor(set.lineColor[i]);
	  set.Nel[i]->SetFillColor(set.color[i]);
	  set.Nel[i]->SetLineWidth(1);

	  // el1_pt
	  std::sprintf(temp_tag, "el1_pt_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.el1_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el1_pt_%s", tag.data());
	  set.el1_pt[i]->SetName(temp_tag);
	  set.el1_pt[i]->SetDirectory(gROOT);
	  set.el1_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el1_pt[i]->SetFillColor(set.color[i]);
	  set.el1_pt[i]->SetLineWidth(1);

	  // el2_pt
	  std::sprintf(temp_tag, "el2_pt_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.el2_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el2_pt_%s", tag.data());
	  set.el2_pt[i]->SetName(temp_tag);
	  set.el2_pt[i]->SetDirectory(gROOT);
	  set.el2_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el2_pt[i]->SetFillColor(set.color[i]);
	  set.el2_pt[i]->SetLineWidth(1);

	  // el_eta
	  std::sprintf(temp_tag, "el_eta_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.el_eta[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el_eta_%s", tag.data());
	  set.el_eta[i]->SetName(temp_tag);
	  set.el_eta[i]->SetDirectory(gROOT);
	  set.el_eta[i]->SetLineColor(set.lineColor[i]);
	  set.el_eta[i]->SetFillColor(set.color[i]);
	  set.el_eta[i]->SetLineWidth(1);

	  // MET
	  std::sprintf(temp_tag, "MET_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.MET[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "MET_%s", tag.data());
	  set.MET[i]->SetName(temp_tag);
	  set.MET[i]->SetDirectory(gROOT);
	  set.MET[i]->SetLineColor(set.lineColor[i]);
	  set.MET[i]->SetFillColor(set.color[i]);
	  set.MET[i]->SetLineWidth(1);

	  // Meff
	  std::sprintf(temp_tag, "Meff_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.Meff[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Meff_%s", tag.data());
	  set.Meff[i]->SetName(temp_tag);
	  set.Meff[i]->SetDirectory(gROOT);
	  set.Meff[i]->SetLineColor(set.lineColor[i]);
	  set.Meff[i]->SetFillColor(set.color[i]);
	  set.Meff[i]->SetLineWidth(1);

	  // METoMeff
	  //	  std::sprintf(temp_tag, "METoMeff_%s_mc_%s", processes[i].c_str(),tag.data());
	  std::sprintf(temp_tag, "MET_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.METoMeff[i] =(TH1D*) f_data->Get(temp_tag);
	  //	  std::sprintf(temp_tag, "METoMeff_%s", tag.data());
	  std::sprintf(temp_tag, "MET_%s", tag.data());
	  set.METoMeff[i]->SetName(temp_tag);
	  set.METoMeff[i]->SetDirectory(gROOT);
	  set.METoMeff[i]->SetLineColor(set.lineColor[i]);
	  set.METoMeff[i]->SetFillColor(set.color[i]);
	  set.METoMeff[i]->SetLineWidth(1);

	  // mT_min
	  std::sprintf(temp_tag, "mT_min_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.mT_min[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mT_min_%s", tag.data());
	  set.mT_min[i]->SetName(temp_tag);
	  set.mT_min[i]->SetDirectory(gROOT);
	  set.mT_min[i]->SetLineColor(set.lineColor[i]);
	  set.mT_min[i]->SetFillColor(set.color[i]);
	  set.mT_min[i]->SetLineWidth(1);

	  // Mee
	  std::sprintf(temp_tag, "Mee_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.Mee[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Mee_%s", tag.data());
	  set.Mee[i]->SetName(temp_tag);
	  set.Mee[i]->SetDirectory(gROOT);
	  set.Mee[i]->SetLineColor(set.lineColor[i]);
	  set.Mee[i]->SetFillColor(set.color[i]);
	  set.Mee[i]->SetLineWidth(1);

	  // Mmumu
	  std::sprintf(temp_tag, "Mmumu_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.Mmumu[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Mmumu_%s", tag.data());
	  set.Mmumu[i]->SetName(temp_tag);
	  set.Mmumu[i]->SetDirectory(gROOT);
	  set.Mmumu[i]->SetLineColor(set.lineColor[i]);
	  set.Mmumu[i]->SetFillColor(set.color[i]);
	  set.Mmumu[i]->SetLineWidth(1);

	  // Nlep
	  //	  std::sprintf(temp_tag, "Nlep_%s_mc_%s", processes[i].c_str(),tag.data());
	  std::sprintf(temp_tag, "Mmumu_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.Nlep[i] =(TH1D*) f_data->Get(temp_tag);
	  //	  std::sprintf(temp_tag, "Nlep_%s", tag.data());
	  std::sprintf(temp_tag, "Mmumu_%s", tag.data());
	  set.Nlep[i]->SetName(temp_tag);
	  set.Nlep[i]->SetDirectory(gROOT);
	  set.Nlep[i]->SetLineColor(set.lineColor[i]);
	  set.Nlep[i]->SetFillColor(set.color[i]);
	  set.Nlep[i]->SetLineWidth(1);

	  // LEPChargeSum
	  std::sprintf(temp_tag, "LEPChargeSum_%s_mc_%s", processes[i].c_str(),tag.data());
	  set.LEPChargeSum[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "LEPChargeSum_%s", tag.data());
	  set.LEPChargeSum[i]->SetName(temp_tag);
	  set.LEPChargeSum[i]->SetDirectory(gROOT);
	  set.LEPChargeSum[i]->SetLineColor(set.lineColor[i]);
	  set.LEPChargeSum[i]->SetFillColor(set.color[i]);
	  set.LEPChargeSum[i]->SetLineWidth(1);
	
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
  
  std::cout << "reading signal SS3L ..." << std::endl;  
  getData_SigSignature(set.SS3L, "SS3L" + tag, "", -1, syst_tag);
  /*std::cout << "reading signal OS ..." << std::endl;  
	getData_SigSignature(set.OS, "OS" + tag, "", -1, syst_tag);
	std::cout << "reading signal SS ..." << std::endl;  
	getData_SigSignature(set.SS, "SS" + tag, "", -1, syst_tag);
	std::cout << "reading signal 3L ..." << std::endl;  
	getData_SigSignature(set.L3, "3L" + tag, "", -1, syst_tag);
  */
  return;
}

//-----------------------------------------------------------------------------

void getData_SigSignature(distrSigSignature& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {
  
  getData_SigRegion(set.PRE, "PRE_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR3b, "SR1b1_" + tag, "", -1, syst_tag);

  getData_SigRegion(set.SR3bmNJETS, "SR1b2_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR3bmNBJETS, "SRlow_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR3bmMET, "SRhigh_" + tag, "", -1, syst_tag);
  getData_SigRegion(set.SR3bmMeff, "SR3b1_" + tag, "", -1, syst_tag);

  /*getData_SigRegion(set.CR0b, "CR0b_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.CR1b, "CR1b_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.CR2b, "CR2b_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.CR3b, "CR3b_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR3L1, "SR3L1_" + tag, "", -1, syst_tag);  
	getData_SigRegion(set.SR3L2, "SR3L2_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR0b1, "SR0b1_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR0b2, "SR0b2_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR0b5, "SR0b5_" + tag, "", -1, syst_tag)j;
	getData_SigRegion(set.SR1b1, "SR1b1_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR1b2, "SR1b2_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR2b1, "SR2b1_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR2b2, "SR2b2_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR3b1, "SR3b1_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR3b2, "SR3b2_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SRCMS, "SRCMS_" + tag, "", -1, syst_tag);
	getData_SigRegion(set.SR3L;, "SR3L;_" + tag, "", -1, syst_tag);*/

  return;
}

//-----------------------------------------------------------------------------

void getData_SigRegion(distrSigRegion& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag) {

  //  getData_SigSet(set.fs_elel, "ee_" + tag, "", -1, syst_tag);
  //  getData_SigSet(set.fs_elmu, "em_" + tag, "", -1, syst_tag);
  //  getData_SigSet(set.fs_mumu, "mm_" + tag, "", -1, syst_tag);
  getData_SigSet(set.fs_comb, "comb_" + tag, "", -1, syst_tag);

  return;
}

//-----------------------------------------------------------------------------

void getData_SigSet(distrSigSet& set, string tag, const char* signal_name, Int_t ind, const char* syst_tag){
  
  set.int_lumi = 1.;//lumi;	
  set.syst_tag = syst_tag;
  char temp_file[512];
  char temp_tag[256];
  TFile *f_data;
  
  set.tagname[0] = tag;

  //  const string files[N_SIG] = {"ttn1_1200_5000_845","ttn1_1200_5000_855","ttn1_1200_5000_900"}; //{ "ttn1_1200_5000_1", "ttn1_1200_5000_600", "ttn1_1200_5000_855"}; 
  
  for (int i = 0; i < N_SIG; i++){
	std::sprintf(temp_file, "%s/%s/%s.root", path, folder,files[i].c_str());
	set.file_name[i] = temp_file;
	set.color[i] = 0;
	set.lineColor[i] = 1;
  }
  
  set.lineColor[0] = kRed; //
  set.lineColor[1] = kMagenta; //
  set.lineColor[2] = 3; //
  
  for (int i = 0; i < N_SIG; i++) {
	f_data = new TFile(set.file_name[i].data(), "READ");


 // N-1 plots first
	if(strstr(tag.data(),"METoMeff") != NULL ){
		// NJETS
	std::sprintf(temp_tag, "Meff_%s_mc_%s", files[i].c_str(),tag.data());
	std::printf("Meff_%s_mc_%s\n", files[i].c_str(),tag.data());
	set.NJETS[i] =(TH1D*) f_data->Get(temp_tag);
	std::sprintf(temp_tag, "METoMeff_%s", tag.data());
	set.NJETS[i]->SetName(temp_tag);
	set.NJETS[i]->SetDirectory(gROOT);
	set.NJETS[i]->SetLineColor(set.lineColor[i]);
	set.NJETS[i]->SetFillColor(set.color[i]);
	set.NJETS[i]->SetLineWidth(1);
  }
	else if(strstr(tag.data(),"Meff") != NULL ){
		  // Meff
	  std::sprintf(temp_tag, "Meff_%s_mc_%s", files[i].c_str(),tag.data());
	std::printf("Meff_%s_mc_%s\n", files[i].c_str(),tag.data());
	  set.Meff[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Meff_%s", tag.data());
	  set.Meff[i]->SetName(temp_tag);
	  set.Meff[i]->SetDirectory(gROOT);
	  set.Meff[i]->SetLineColor(set.lineColor[i]);
	  set.Meff[i]->SetFillColor(set.color[i]);
	  set.Meff[i]->SetLineWidth(1);

  }
	else if(strstr(tag.data(),"NBJETS") != NULL ){
		// NBJETS
	std::sprintf(temp_tag, "NBJETS_%s_mc_%s", files[i].c_str(),tag.data());
	std::printf("NBJETS_%s_mc_%s\n", files[i].c_str(),tag.data());
	set.NBJETS[i] =(TH1D*) f_data->Get(temp_tag);
	std::sprintf(temp_tag, "NBJETS_%s", tag.data());
	set.NBJETS[i]->SetName(temp_tag);
	set.NBJETS[i]->SetDirectory(gROOT);
	set.NBJETS[i]->SetLineColor(set.lineColor[i]);
	set.NBJETS[i]->SetFillColor(set.color[i]);
	set.NBJETS[i]->SetLineWidth(1);
  }
	else if(strstr(tag.data(),"MET") != NULL ){
		  // MET
	  std::sprintf(temp_tag, "MET_%s_mc_%s", files[i].c_str(),tag.data());
	std::printf("MET_%s_mc_%s\n", files[i].c_str(),tag.data());
	  set.MET[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "MET_%s", tag.data());
	  set.MET[i]->SetName(temp_tag);
	  set.MET[i]->SetDirectory(gROOT);
	  set.MET[i]->SetLineColor(set.lineColor[i]);
	  set.MET[i]->SetFillColor(set.color[i]);
	  set.MET[i]->SetLineWidth(1);

  }
  else{

	// NJETS
	std::sprintf(temp_tag, "NJETS_%s_mc_%s", files[i].c_str(),tag.data());
	std::printf("NJETS_%s_mc_%s\n", files[i].c_str(),tag.data());
	set.NJETS[i] =(TH1D*) f_data->Get(temp_tag);
	std::sprintf(temp_tag, "NJETS_%s", tag.data());
	set.NJETS[i]->SetName(temp_tag);
	set.NJETS[i]->SetDirectory(gROOT);
	set.NJETS[i]->SetLineColor(set.lineColor[i]);
	set.NJETS[i]->SetFillColor(set.color[i]);
	set.NJETS[i]->SetLineWidth(1);
	if(!test_me){
	  // pt_jet1
	  std::sprintf(temp_tag, "pt_jet1_%s_mc_%s", files[i].c_str(),tag.data());
	std::printf("pt_jet1_%s_mc_%s\n", files[i].c_str(),tag.data());
	  set.pt_jet1[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_jet1_%s", tag.data());
	  set.pt_jet1[i]->SetName(temp_tag);
	  set.pt_jet1[i]->SetDirectory(gROOT);
	  set.pt_jet1[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet1[i]->SetFillColor(set.color[i]);
	  set.pt_jet1[i]->SetLineWidth(1);

	  // pt_jet2
	  std::sprintf(temp_tag, "pt_jet2_%s_mc_%s", files[i].c_str(),tag.data());
	  set.pt_jet2[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_jet2_%s", tag.data());
	  set.pt_jet2[i]->SetName(temp_tag);
	  set.pt_jet2[i]->SetDirectory(gROOT);
	  set.pt_jet2[i]->SetLineColor(set.lineColor[i]);
	  set.pt_jet2[i]->SetFillColor(set.color[i]);
	  set.pt_jet2[i]->SetLineWidth(1);

	  // NBJETS
	  std::sprintf(temp_tag, "NBJETS_%s_mc_%s", files[i].c_str(),tag.data());
	  set.NBJETS[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "NBJETS_%s", tag.data());
	  set.NBJETS[i]->SetName(temp_tag);
	  set.NBJETS[i]->SetDirectory(gROOT);
	  set.NBJETS[i]->SetLineColor(set.lineColor[i]);
	  set.NBJETS[i]->SetFillColor(set.color[i]);
	  set.NBJETS[i]->SetLineWidth(1);

	  // pt_bjet1
	  std::sprintf(temp_tag, "pt_bjet1_%s_mc_%s", files[i].c_str(),tag.data());
	  set.pt_bjet1[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_bjet1_%s", tag.data());
	  set.pt_bjet1[i]->SetName(temp_tag);
	  set.pt_bjet1[i]->SetDirectory(gROOT);
	  set.pt_bjet1[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet1[i]->SetFillColor(set.color[i]);
	  set.pt_bjet1[i]->SetLineWidth(1);

	  // pt_bjet2
	  std::sprintf(temp_tag, "pt_bjet2_%s_mc_%s", files[i].c_str(),tag.data());
	  set.pt_bjet2[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "pt_bjet2_%s", tag.data());
	  set.pt_bjet2[i]->SetName(temp_tag);
	  set.pt_bjet2[i]->SetDirectory(gROOT);
	  set.pt_bjet2[i]->SetLineColor(set.lineColor[i]);
	  set.pt_bjet2[i]->SetFillColor(set.color[i]);
	  set.pt_bjet2[i]->SetLineWidth(1);

	  // Nmu
	  //	  std::sprintf(temp_tag, "Nmu_%s_mc_%s", files[i].c_str(),tag.data());
	  std::sprintf(temp_tag, "mu1_pt_%s_mc_%s", files[i].c_str(),tag.data());
	  set.Nmu[i] =(TH1D*) f_data->Get(temp_tag);
	  //	  std::sprintf(temp_tag, "Nmu_%s", tag.data());
	  std::sprintf(temp_tag, "mu1_pt_%s", tag.data());
	  set.Nmu[i]->SetName(temp_tag);
	  set.Nmu[i]->SetDirectory(gROOT);
	  set.Nmu[i]->SetLineColor(set.lineColor[i]);
	  set.Nmu[i]->SetFillColor(set.color[i]);
	  set.Nmu[i]->SetLineWidth(1);

	  // mu1_pt
	  std::sprintf(temp_tag, "mu1_pt_%s_mc_%s", files[i].c_str(),tag.data());
	  set.mu1_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu1_pt_%s", tag.data());
	  set.mu1_pt[i]->SetName(temp_tag);
	  set.mu1_pt[i]->SetDirectory(gROOT);
	  set.mu1_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu1_pt[i]->SetFillColor(set.color[i]);
	  set.mu1_pt[i]->SetLineWidth(1);

	  // mu2_pt
	  std::sprintf(temp_tag, "mu2_pt_%s_mc_%s", files[i].c_str(),tag.data());
	  set.mu2_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu2_pt_%s", tag.data());
	  set.mu2_pt[i]->SetName(temp_tag);
	  set.mu2_pt[i]->SetDirectory(gROOT);
	  set.mu2_pt[i]->SetLineColor(set.lineColor[i]);
	  set.mu2_pt[i]->SetFillColor(set.color[i]);
	  set.mu2_pt[i]->SetLineWidth(1);

	  // mu_eta
	  std::sprintf(temp_tag, "mu_eta_%s_mc_%s", files[i].c_str(),tag.data());
	  set.mu_eta[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mu_eta_%s", tag.data());
	  set.mu_eta[i]->SetName(temp_tag);
	  set.mu_eta[i]->SetDirectory(gROOT);
	  set.mu_eta[i]->SetLineColor(set.lineColor[i]);
	  set.mu_eta[i]->SetFillColor(set.color[i]);
	  set.mu_eta[i]->SetLineWidth(1);

	  // Nel
	  //	  std::sprintf(temp_tag, "Nel_%s_mc_%s", files[i].c_str(),tag.data());
	  std::sprintf(temp_tag, "el1_pt_%s_mc_%s", files[i].c_str(),tag.data());
	  set.Nel[i] =(TH1D*) f_data->Get(temp_tag);
	  //	  std::sprintf(temp_tag, "Nel_%s", tag.data());
	  std::sprintf(temp_tag, "el1__pt_%s", tag.data());
	  set.Nel[i]->SetName(temp_tag);
	  set.Nel[i]->SetDirectory(gROOT);
	  set.Nel[i]->SetLineColor(set.lineColor[i]);
	  set.Nel[i]->SetFillColor(set.color[i]);
	  set.Nel[i]->SetLineWidth(1);

	  // el1_pt
	  std::sprintf(temp_tag, "el1_pt_%s_mc_%s", files[i].c_str(),tag.data());
	  set.el1_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el1_pt_%s", tag.data());
	  set.el1_pt[i]->SetName(temp_tag);
	  set.el1_pt[i]->SetDirectory(gROOT);
	  set.el1_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el1_pt[i]->SetFillColor(set.color[i]);
	  set.el1_pt[i]->SetLineWidth(1);

	  // el2_pt
	  std::sprintf(temp_tag, "el2_pt_%s_mc_%s", files[i].c_str(),tag.data());
	  set.el2_pt[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el2_pt_%s", tag.data());
	  set.el2_pt[i]->SetName(temp_tag);
	  set.el2_pt[i]->SetDirectory(gROOT);
	  set.el2_pt[i]->SetLineColor(set.lineColor[i]);
	  set.el2_pt[i]->SetFillColor(set.color[i]);
	  set.el2_pt[i]->SetLineWidth(1);

	  // el_eta
	  std::sprintf(temp_tag, "el_eta_%s_mc_%s", files[i].c_str(),tag.data());
	  set.el_eta[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "el_eta_%s", tag.data());
	  set.el_eta[i]->SetName(temp_tag);
	  set.el_eta[i]->SetDirectory(gROOT);
	  set.el_eta[i]->SetLineColor(set.lineColor[i]);
	  set.el_eta[i]->SetFillColor(set.color[i]);
	  set.el_eta[i]->SetLineWidth(1);

	  // MET
	  std::sprintf(temp_tag, "MET_%s_mc_%s", files[i].c_str(),tag.data());
	  set.MET[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "MET_%s", tag.data());
	  set.MET[i]->SetName(temp_tag);
	  set.MET[i]->SetDirectory(gROOT);
	  set.MET[i]->SetLineColor(set.lineColor[i]);
	  set.MET[i]->SetFillColor(set.color[i]);
	  set.MET[i]->SetLineWidth(1);

	  // Meff
	  std::sprintf(temp_tag, "Meff_%s_mc_%s", files[i].c_str(),tag.data());
	  set.Meff[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Meff_%s", tag.data());
	  set.Meff[i]->SetName(temp_tag);
	  set.Meff[i]->SetDirectory(gROOT);
	  set.Meff[i]->SetLineColor(set.lineColor[i]);
	  set.Meff[i]->SetFillColor(set.color[i]);
	  set.Meff[i]->SetLineWidth(1);

	  // METoMeff
	  //	  std::sprintf(temp_tag, "METoMeff_%s_mc_%s", files[i].c_str(),tag.data());
	  std::sprintf(temp_tag, "MET_%s_mc_%s", files[i].c_str(),tag.data());
	  set.METoMeff[i] =(TH1D*) f_data->Get(temp_tag);
	  //	  std::sprintf(temp_tag, "METoMeff_%s", tag.data());
	  std::sprintf(temp_tag, "MET_%s", tag.data());
	  set.METoMeff[i]->SetName(temp_tag);
	  set.METoMeff[i]->SetDirectory(gROOT);
	  set.METoMeff[i]->SetLineColor(set.lineColor[i]);
	  set.METoMeff[i]->SetFillColor(set.color[i]);
	  set.METoMeff[i]->SetLineWidth(1);

	  // mT_min
	  std::sprintf(temp_tag, "mT_min_%s_mc_%s", files[i].c_str(),tag.data());
	  set.mT_min[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "mT_min_%s", tag.data());
	  set.mT_min[i]->SetName(temp_tag);
	  set.mT_min[i]->SetDirectory(gROOT);
	  set.mT_min[i]->SetLineColor(set.lineColor[i]);
	  set.mT_min[i]->SetFillColor(set.color[i]);
	  set.mT_min[i]->SetLineWidth(1);

	  // Mee
	  std::sprintf(temp_tag, "Mee_%s_mc_%s", files[i].c_str(),tag.data());
	  set.Mee[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Mee_%s", tag.data());
	  set.Mee[i]->SetName(temp_tag);
	  set.Mee[i]->SetDirectory(gROOT);
	  set.Mee[i]->SetLineColor(set.lineColor[i]);
	  set.Mee[i]->SetFillColor(set.color[i]);
	  set.Mee[i]->SetLineWidth(1);

	  // Mmumu
	  std::sprintf(temp_tag, "Mmumu_%s_mc_%s", files[i].c_str(),tag.data());
	  set.Mmumu[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "Mmumu_%s", tag.data());
	  set.Mmumu[i]->SetName(temp_tag);
	  set.Mmumu[i]->SetDirectory(gROOT);
	  set.Mmumu[i]->SetLineColor(set.lineColor[i]);
	  set.Mmumu[i]->SetFillColor(set.color[i]);
	  set.Mmumu[i]->SetLineWidth(1);

	  // Nlep
	  //	  std::sprintf(temp_tag, "Nlep_%s_mc_%s", files[i].c_str(),tag.data());
	  std::sprintf(temp_tag, "Mmumu_%s_mc_%s", files[i].c_str(),tag.data());
	  set.Nlep[i] =(TH1D*) f_data->Get(temp_tag);
	  //	  std::sprintf(temp_tag, "Nlep_%s", tag.data());
	  std::sprintf(temp_tag, "Mmumu_%s", tag.data());
	  set.Nlep[i]->SetName(temp_tag);
	  set.Nlep[i]->SetDirectory(gROOT);
	  set.Nlep[i]->SetLineColor(set.lineColor[i]);
	  set.Nlep[i]->SetFillColor(set.color[i]);
	  set.Nlep[i]->SetLineWidth(1);

	  // LEPChargeSum
	  std::sprintf(temp_tag, "LEPChargeSum_%s_mc_%s", files[i].c_str(),tag.data());
	  set.LEPChargeSum[i] =(TH1D*) f_data->Get(temp_tag);
	  std::sprintf(temp_tag, "LEPChargeSum_%s", tag.data());
	  set.LEPChargeSum[i]->SetName(temp_tag);
	  set.LEPChargeSum[i]->SetDirectory(gROOT);
	  set.LEPChargeSum[i]->SetLineColor(set.lineColor[i]);
	  set.LEPChargeSum[i]->SetFillColor(set.color[i]);
	  set.LEPChargeSum[i]->SetLineWidth(1);

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
  /*  scaleLumi_Signature(set.SS, sf);
	  scaleLumi_Signature(set.L3, sf);*/

  return;
}

//-----------------------------------------------------------------------------

void scaleLumi_Signature(distrSignature& set, Double_t sf) {

  scaleLumi_Region(set.PRE, sf);
  scaleLumi_Region(set.SR3b, sf);
  scaleLumi_Region(set.SR3bmNJETS, sf);
  scaleLumi_Region(set.SR3bmNBJETS, sf);
  scaleLumi_Region(set.SR3bmMET, sf);
  scaleLumi_Region(set.SR3bmMeff, sf);

  /*scaleLumi_Region(set.CR0b, sf);
	scaleLumi_Region(set.CR1b, sf);
	scaleLumi_Region(set.CR2b, sf);
	scaleLumi_Region(set.CR3b, sf);
	scaleLumi_Region(set.SR3L1, sf);
	scaleLumi_Region(set.SR3L2, sf);
	scaleLumi_Region(set.SR0b1, sf);
	scaleLumi_Region(set.SR0b2, sf);
	scaleLumi_Region(set.SR0b5, sf);
	scaleLumi_Region(set.SR1b1, sf);
	scaleLumi_Region(set.SR1b2, sf);
	scaleLumi_Region(set.SR2b1, sf);
	scaleLumi_Region(set.SR2b2, sf);
	scaleLumi_Region(set.SR3b1, sf);
	scaleLumi_Region(set.SR3b2, sf);
	scaleLumi_Region(set.SRCMS, sf);
	scaleLumi_Region(set.SR3L, sf);*/


  return;
}

//-----------------------------------------------------------------------------

void scaleLumi_Region(distrRegion& set, Double_t sf) {
  
  //  scaleLumi_Set(set.fs_elel, sf);
  //  scaleLumi_Set(set.fs_elmu, sf);
  //  scaleLumi_Set(set.fs_mumu, sf);
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
  /*  scaleXSect_Signature(set.SS, ind, sf);
	  scaleXSect_Signature(set.L3, ind, sf);*/

  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_Signature(distrSignature& set, Int_t ind, Double_t sf) {

  scaleXSect_Region(set.PRE,  ind,  sf);
  scaleXSect_Region(set.SR3b,  ind,  sf);

  scaleXSect_Region(set.SR3bmNJETS,  ind,  sf);
  scaleXSect_Region(set.SR3bmNBJETS,  ind,  sf);
  scaleXSect_Region(set.SR3bmMET,  ind,  sf);
  scaleXSect_Region(set.SR3bmMeff,  ind,  sf);



  /*scaleXSect_Region(set.CR0b,  ind,  sf);
	scaleXSect_Region(set.CR1b,  ind,  sf);
	scaleXSect_Region(set.CR2b,  ind,  sf);
	scaleXSect_Region(set.CR3b,  ind,  sf);
    scaleXSect_Region(set.SR3L1, ind,  sf);
	scaleXSect_Region(set.SR3L2, ind,  sf);
	scaleXSect_Region(set.SR0b1, ind,  sf);
	scaleXSect_Region(set.SR0b2, ind,  sf);
	scaleXSect_Region(set.SR0b5, ind,  sf);
	scaleXSect_Region(set.SR1b1, ind,  sf);
	scaleXSect_Region(set.SR1b2, ind,  sf);
	scaleXSect_Region(set.SR2b1, ind,  sf);
	scaleXSect_Region(set.SR2b2, ind,  sf);
	scaleXSect_Region(set.SR3b1, ind,  sf);
	scaleXSect_Region(set.SR3b2, ind,  sf);
	scaleXSect_Region(set.SRCMS, ind,  sf);
	scaleXSect_Region(set.SR3L,  ind,  sf);*/

  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_Region(distrRegion& set, Int_t ind, Double_t sf) {
  
  //  scaleXSect_Set(set.fs_elel, ind, sf);
  //  scaleXSect_Set(set.fs_elmu, ind, sf);
  //  scaleXSect_Set(set.fs_mumu, ind, sf);
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
  /*  scaleXSect_SigSignature(set.SS, ind, sf);
	  scaleXSect_SigSignature(set.L3, ind, sf);*/

  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_SigSignature(distrSigSignature& set, Int_t ind, Double_t sf) {

  scaleXSect_SigRegion(set.PRE, ind, sf);
  scaleXSect_SigRegion(set.SR3b, ind, sf);
  scaleXSect_SigRegion(set.SR3bmNJETS, ind, sf);
  scaleXSect_SigRegion(set.SR3bmNBJETS, ind, sf);
  scaleXSect_SigRegion(set.SR3bmMET, ind, sf);
  scaleXSect_SigRegion(set.SR3bmMeff, ind, sf);


  /*scaleXSect_SigRegion(set.CR0b,  ind,  sf);
	scaleXSect_SigRegion(set.CR1b,  ind,  sf);
	scaleXSect_SigRegion(set.CR2b,  ind,  sf);
	scaleXSect_SigRegion(set.CR3b,  ind,  sf);
    scaleXSect_SigRegion(set.SR3L1, ind,  sf);
	scaleXSect_SigRegion(set.SR3L2, ind,  sf);
	scaleXSect_SigRegion(set.SR0b1, ind,  sf);
	scaleXSect_SigRegion(set.SR0b2, ind,  sf);
	scaleXSect_SigRegion(set.SR0b5, ind,  sf);
	scaleXSect_SigRegion(set.SR1b1, ind,  sf);
	scaleXSect_SigRegion(set.SR1b2, ind,  sf);
	scaleXSect_SigRegion(set.SR2b1, ind,  sf);
	scaleXSect_SigRegion(set.SR2b2, ind,  sf);
	scaleXSect_SigRegion(set.SR3b1, ind,  sf);
	scaleXSect_SigRegion(set.SR3b2, ind,  sf);
	scaleXSect_SigRegion(set.SRCMS, ind,  sf);
	scaleXSect_SigRegion(set.SR3L,  ind,  sf);*/

  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_SigRegion(distrSigRegion& set, Int_t ind, Double_t sf) {
  
  //  scaleXSect_SigSet(set.fs_elel, ind, sf);
  //  scaleXSect_SigSet(set.fs_elmu, ind, sf);
  //  scaleXSect_SigSet(set.fs_mumu, ind, sf);
  scaleXSect_SigSet(set.fs_comb, ind, sf);
    
  return;
}

//-----------------------------------------------------------------------------

void scaleXSect_SigSet(distrSigSet& set, Int_t ind, Double_t sf) {

  set.xsect[ind] *= sf;
  
  return;
}

//-----------------------------------------------------------------------------
// Weight histograms
//-----------------------------------------------------------------------------

void weightData_All(distrAll& set) {

  weightData_Signature(set.SS3L);
  /*  weightData_Signature(set.SS);
	  weightData_Signature(set.L3);*/

  return;
}

//-----------------------------------------------------------------------------

void weightData_Signature(distrSignature& set) {

  weightData_Region(set.PRE);
  std::cout << "finished regions pre" << std::endl;
  weightData_Region(set.SR3b);
  std::cout << "finished regions sr1" << std::endl;
  weightData_Region(set.SR3bmNBJETS);
  std::cout << "finished regions sr1 nbjet" << std::endl;
  weightData_Region(set.SR3bmMET);
  std::cout << "finished regions sr1 met" << std::endl;
  weightData_Region(set.SR3bmMeff);
  std::cout << "finished regions sr1 meff" << std::endl;
  weightData_Region(set.SR3bmNJETS);
  std::cout << "finished regions sr1 metomeff" << std::endl;

  /*weightData_Region(set.CR0b);
	weightData_Region(set.CR1b);
	weightData_Region(set.CR2b);
	weightData_Region(set.CR3b);
    weightData_Region(set.SR3L1);
	weightData_Region(set.SR3L2);
	weightData_Region(set.SR0b1);
	weightData_Region(set.SR0b2);
	weightData_Region(set.SR0b5);
	weightData_Region(set.SR1b1);
	weightData_Region(set.SR1b2);
	weightData_Region(set.SR2b1);
	weightData_Region(set.SR2b2);
	weightData_Region(set.SR3b1);
	weightData_Region(set.SR3b2);
	weightData_Region(set.SRCMS);
	weightData_Region(set.SR3L);*/

  return;
}

//-----------------------------------------------------------------------------

void weightData_Region(distrRegion& set) {
  
  //  weightData_Set(set.fs_elel);
  //  weightData_Set(set.fs_elmu);
  //  weightData_Set(set.fs_mumu);
  weightData_Set(set.fs_comb);
    
  //  buildStack(set.fs_elel);
  //  buildStack(set.fs_elmu);
  //  buildStack(set.fs_mumu);  
  buildStack(set.fs_comb);

  return;
}

//-----------------------------------------------------------------------------

void weightData_Set(distrSet& set) {

  Double_t weight[N_MC];
  for (int i = 0; i < N_MC; i++) { // TO DO: start from 1 if 0 is data OR just create a new class for DATA or MC

	weight[i] = set.int_lumi * set.xsect[i] ;

	double sf = 1.;

 // N-1 plots first

	std::cout << set.file_name[0].data() << std::endl;
	if(strstr(set.file_name[0].data(),"SR1mMEToMeff") != NULL ){
	  set.NJETS[i]->Scale(weight[i]*sf);
  }
	else if(strstr(set.file_name[0].data(),"SR1mMeff") != NULL ){
	  set.Meff[i]->Scale(weight[i]*sf);
  }
	else if(strstr(set.file_name[0].data(),"SR1mNBJETS") != NULL ){
	  set.NBJETS[i]->Scale(weight[i]*sf);
  }
	else if(strstr(set.file_name[0].data(),"SR1mMET") != NULL ){
	  set.MET[i]->Scale(weight[i]*sf);
  }
  else{
	set.NJETS[i]->Scale(weight[i]*sf);
	if(!test_me){
	  set.pt_jet1[i]->Scale(weight[i]*sf);
	  set.pt_jet2[i]->Scale(weight[i]*sf);
	  set.NBJETS[i]->Scale(weight[i]*sf);
	  set.pt_bjet1[i]->Scale(weight[i]*sf);
	  set.pt_bjet2[i]->Scale(weight[i]*sf);
	  set.Nmu[i]->Scale(weight[i]*sf);
	  set.mu1_pt[i]->Scale(weight[i]*sf);
	  set.mu2_pt[i]->Scale(weight[i]*sf);
	  set.mu_eta[i]->Scale(weight[i]*sf);
	  set.Nel[i]->Scale(weight[i]*sf);
	  set.el1_pt[i]->Scale(weight[i]*sf);
	  set.el2_pt[i]->Scale(weight[i]*sf);
	  set.el_eta[i]->Scale(weight[i]*sf);
	  set.MET[i]->Scale(weight[i]*sf);
	  set.Meff[i]->Scale(weight[i]*sf);
	  set.METoMeff[i]->Scale(weight[i]*sf);
	  set.mT_min[i]->Scale(weight[i]*sf);
	  set.Mee[i]->Scale(weight[i]*sf);
	  set.Mmumu[i]->Scale(weight[i]*sf);
	  set.Nlep[i]->Scale(weight[i]*sf);
	  set.LEPChargeSum[i]->Scale(weight[i]*sf);
	}
  }
  }
  std::cout << "done" << std::endl;

  return;
  }

//-----------------------------------------------------------------------------

void weightData_SigAll(distrSigAll& set) {

  weightData_SigSignature(set.SS3L);
  /*  weightData_SigSignature(set.SS);
	  weightData_SigSignature(set.L3);*/

  return;
}

//-----------------------------------------------------------------------------

void weightData_SigSignature(distrSigSignature& set) {

  weightData_SigRegion(set.PRE);
  weightData_SigRegion(set.SR3b);
  weightData_SigRegion(set.SR3bmNJETS);
  weightData_SigRegion(set.SR3bmNBJETS);
  weightData_SigRegion(set.SR3bmMET);
  weightData_SigRegion(set.SR3bmMeff);
  /*weightData_SigRegion(set.CR0b);
	weightData_SigRegion(set.CR1b);
	weightData_SigRegion(set.CR2b);
	weightData_SigRegion(set.CR3b);
    weightData_SigRegion(set.SR3L1);
	weightData_SigRegion(set.SR3L2);
	weightData_SigRegion(set.SR0b1);
	weightData_SigRegion(set.SR0b2);
	weightData_SigRegion(set.SR0b5);
	weightData_SigRegion(set.SR1b1);
	weightData_SigRegion(set.SR1b2);
	weightData_SigRegion(set.SR2b1);
	weightData_SigRegion(set.SR2b2);
	weightData_SigRegion(set.SR3b1);
	weightData_SigRegion(set.SR3b2);
	weightData_SigRegion(set.SRCMS);
	weightData_SigRegion(set.SR3L);*/

  return;
}

//-----------------------------------------------------------------------------

void weightData_SigRegion(distrSigRegion& set) {

  //  weightData_SigSet(set.fs_elel);
  //  weightData_SigSet(set.fs_elmu);
  //  weightData_SigSet(set.fs_mumu);
  weightData_SigSet(set.fs_comb);

  return;
}

//-----------------------------------------------------------------------------

void weightData_SigSet(distrSigSet& set) {

  Double_t weight[N_SIG];
  for (int i = 0; i < N_SIG; i++){ 

	weight[i] = set.int_lumi * set.xsect[i] ; // normalize to Lumi
  
	double sf = 1.;
 // N-1 plots first

	if(strstr(set.tagname[0].data(),"NJETS") != NULL ){
	  set.NJETS[i]->Scale(weight[i]*sf);
  }
	else if(strstr(set.tagname[0].data(),"Meff") != NULL ){
	  set.Meff[i]->Scale(weight[i]*sf);
  }
	else if(strstr(set.tagname[0].data(),"NBJETS") != NULL ){
	  set.NBJETS[i]->Scale(weight[i]*sf);
  }
	else if(strstr(set.tagname[0].data(),"MET") != NULL ){
	  set.MET[i]->Scale(weight[i]*sf);
  }
  else{
	set.NJETS[i]->Scale(weight[i]*sf);
	if(!test_me){
	  set.pt_jet1[i]->Scale(weight[i]*sf);
	  set.pt_jet2[i]->Scale(weight[i]*sf);
	  set.NBJETS[i]->Scale(weight[i]*sf);
	  set.pt_bjet1[i]->Scale(weight[i]*sf);
	  set.pt_bjet2[i]->Scale(weight[i]*sf);
	  set.Nmu[i]->Scale(weight[i]*sf);
	  set.mu1_pt[i]->Scale(weight[i]*sf);
	  set.mu2_pt[i]->Scale(weight[i]*sf);
	  set.mu_eta[i]->Scale(weight[i]*sf);
	  set.Nel[i]->Scale(weight[i]*sf);
	  set.el1_pt[i]->Scale(weight[i]*sf);
	  set.el2_pt[i]->Scale(weight[i]*sf);
	  set.el_eta[i]->Scale(weight[i]*sf);
	  set.MET[i]->Scale(weight[i]*sf);
	  set.Meff[i]->Scale(weight[i]*sf);
	  set.METoMeff[i]->Scale(weight[i]*sf);
	  set.mT_min[i]->Scale(weight[i]*sf);
	  set.Mee[i]->Scale(weight[i]*sf);
	  set.Mmumu[i]->Scale(weight[i]*sf);
	  set.Nlep[i]->Scale(weight[i]*sf);
	  set.LEPChargeSum[i]->Scale(weight[i]*sf);
  }
  }
  }
  return;
}

//-----------------------------------------------------------------------------

void buildStack(distrSet& set) {

 // N-1 plots first
  if(strstr(set.file_name[0].data(),"NJETS") != NULL ){
  buildAStack(set.ST_NJETS, set.NJETS, &set.syst_tag);
  }
	else if(strstr(set.file_name[0].data(),"Meff") != NULL ){
	buildAStack(set.ST_Meff, set.Meff, &set.syst_tag);
  }
	else if(strstr(set.file_name[0].data(),"NBJETS") != NULL ){
	buildAStack(set.ST_NBJETS, set.NBJETS, &set.syst_tag);
  }
	else if(strstr(set.file_name[0].data(),"MET") != NULL ){
buildAStack(set.ST_MET, set.MET, &set.syst_tag);
  }
  else{
  buildAStack(set.ST_NJETS, set.NJETS, &set.syst_tag);
  if(!test_me){
	buildAStack(set.ST_pt_jet1, set.pt_jet1, &set.syst_tag);
	buildAStack(set.ST_pt_jet2, set.pt_jet2, &set.syst_tag);
	buildAStack(set.ST_NBJETS, set.NBJETS, &set.syst_tag);
	buildAStack(set.ST_pt_bjet1, set.pt_bjet1, &set.syst_tag);
	buildAStack(set.ST_pt_bjet2, set.pt_bjet2, &set.syst_tag);
	buildAStack(set.ST_Nmu, set.Nmu, &set.syst_tag);
	buildAStack(set.ST_mu1_pt, set.mu1_pt, &set.syst_tag);
	buildAStack(set.ST_mu2_pt, set.mu2_pt, &set.syst_tag);
	buildAStack(set.ST_mu_eta, set.mu_eta, &set.syst_tag);
	buildAStack(set.ST_Nel, set.Nel, &set.syst_tag);
	buildAStack(set.ST_el1_pt, set.el1_pt, &set.syst_tag);
	buildAStack(set.ST_el2_pt, set.el2_pt, &set.syst_tag);
	buildAStack(set.ST_el_eta, set.el_eta, &set.syst_tag);
	buildAStack(set.ST_MET, set.MET, &set.syst_tag);
	buildAStack(set.ST_Meff, set.Meff, &set.syst_tag);
	buildAStack(set.ST_METoMeff, set.METoMeff, &set.syst_tag);
	buildAStack(set.ST_mT_min, set.mT_min, &set.syst_tag);
	buildAStack(set.ST_Mee, set.Mee, &set.syst_tag);
	buildAStack(set.ST_Mmumu, set.Mmumu, &set.syst_tag);
	buildAStack(set.ST_Nlep, set.Nlep, &set.syst_tag);
	buildAStack(set.ST_LEPChargeSum, set.LEPChargeSum, &set.syst_tag);
  }
  }
  return;
}

//-----------------------------------------------------------------------------

void buildAStack(THStack* &st, TH1D* hist[N_MC], string *syst_tag) {

  //We build Stacked plots here
  char my_name[256];
  sprintf(my_name, "HSTACK_%s%s", hist[0]->GetName(), syst_tag->data());
  st = new THStack(my_name, "Hstack");
  
  // Sort histograms before building the stack
  std::list <TH1D*> mc_hists;
  for (int i = 0; i < N_MC; i++) {
	mc_hists.push_back(hist[i]);
  }
  mc_hists.sort(hasLessEvents);
  std::list<TH1D*>::const_iterator iterator;
  for(  iterator = mc_hists.begin(); iterator != mc_hists.end(); ++iterator)
	st->Add(*iterator);
  
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
  /*  distrSignature* paired_SS[N_unc_paired];
	  distrSignature* unpaired_SS[N_unc_unpaired];
	  distrSignature* paired_L3[N_unc_paired];
	  distrSignature* unpaired_L3[N_unc_unpaired];*/

  for (int j = 0; j < N_unc_paired; j++) {
    distrAll* temp_set = paired[j];
	paired_SS3L[j] = (&(temp_set->SS3L));
	/*	paired_SS[j] = (&(temp_set->SS));
		paired_L3[j] = (&(temp_set->L3));*/
  }

  for (int j = 0; j < N_unc_unpaired; j++) {
    distrAll* temp_set = unpaired[j];
	unpaired_SS3L[j] = (&(temp_set->SS3L));
	/*	unpaired_SS[j] = (&(temp_set->SS));
		unpaired_L3[j] = (&(temp_set->L3));*/
  }

  draw_Signature(set.SS3L, sig.SS3L, paired_SS3L, unpaired_SS3L, fit);
  /*  draw_Signature(set.SS, sig.SS, paired_SS, unpaired_SS, fit);
	  draw_Signature(set.L3, sig.L3, paired_L3, unpaired_L3, fit);*/

  return;
}

//-----------------------------------------------------------------------------

void draw_Signature(distrSignature &set, distrSigSignature &sig, distrSignature* paired[N_unc_paired], distrSignature* unpaired[N_unc_unpaired], const char* fit){

  distrRegion* paired_PRE[N_unc_paired];
  distrRegion* paired_SR3b[N_unc_paired];
  distrRegion* paired_SR3bmNJETS[N_unc_paired];
  distrRegion* paired_SR3bmNBJETS[N_unc_paired];
  distrRegion* paired_SR3bmMET[N_unc_paired];
  distrRegion* paired_SR3bmMeff[N_unc_paired];
  distrRegion* unpaired_PRE[N_unc_unpaired];
  distrRegion* unpaired_SR3b[N_unc_unpaired];
  distrRegion* unpaired_SR3bmNJETS[N_unc_unpaired];
  distrRegion* unpaired_SR3bmNBJETS[N_unc_unpaired];
  distrRegion* unpaired_SR3bmMET[N_unc_unpaired];
  distrRegion* unpaired_SR3bmMeff[N_unc_unpaired];

  /*distrRegion* paired_CR0b[N_unc_paired];
	distrRegion* unpaired_CR0b[N_unc_unpaired];
	distrRegion* paired_CR1b[N_unc_paired];
	distrRegion* unpaired_CR1b[N_unc_unpaired];
	distrRegion* paired_CR2b[N_unc_paired];
	distrRegion* unpaired_CR2b[N_unc_unpaired];
	distrRegion* paired_CR3b[N_unc_paired];
	distrRegion* unpaired_CR3b[N_unc_unpaired];
    distrRegion* paired_SR3L1[N_unc_paired];
	distrRegion* unpaired_SR3L1[N_unc_unpaired];
	distrRegion* paired_SR3L2[N_unc_paired];
	distrRegion* unpaired_SR3L2[N_unc_unpaired];
	distrRegion* paired_SR0b1[N_unc_paired];
	distrRegion* unpaired_SR0b1[N_unc_unpaired];
	distrRegion* paired_SR0b2[N_unc_paired];
	distrRegion* unpaired_SR0b2[N_unc_unpaired];
	distrRegion* paired_SR0b5[N_unc_paired];
	distrRegion* unpaired_SR0b5[N_unc_unpaired];
	distrRegion* paired_SR1b1[N_unc_paired];
	distrRegion* unpaired_SR1b1[N_unc_unpaired];
	distrRegion* paired_SR1b2[N_unc_paired];
	distrRegion* unpaired_SR1b2[N_unc_unpaired];
	distrRegion* paired_SR2b1[N_unc_paired];
	distrRegion* unpaired_SR2b1[N_unc_unpaired];
	distrRegion* paired_SR2b2[N_unc_paired];
	distrRegion* unpaired_SR2b2[N_unc_unpaired];
	distrRegion* paired_SR3b1[N_unc_paired];
	distrRegion* unpaired_SR3b1[N_unc_unpaired];
	distrRegion* paired_SR3b2[N_unc_paired];
	distrRegion* unpaired_SR3b2[N_unc_unpaired];
	distrRegion* paired_SRCMS[N_unc_paired];
	distrRegion* unpaired_SRCMS[N_unc_unpaired];
	distrRegion* paired_SR3L[N_unc_paired];
	distrRegion* unpaired_SR3L[N_unc_unpaired];*/

  for (int j = 0; j < N_unc_paired; j++) {
    distrSignature* temp_set = paired[j];
	paired_PRE[j] = (&(temp_set->PRE));
	paired_SR3b[j] = (&(temp_set->SR3b));
	paired_SR3bmNJETS[j] = (&(temp_set->SR3bmNJETS));
	paired_SR3bmNBJETS[j] = (&(temp_set->SR3bmNBJETS));
	paired_SR3bmMET[j] = (&(temp_set->SR3bmMET));
	paired_SR3bmMeff[j] = (&(temp_set->SR3bmMeff));


	/*paired_CR0b[j] = (&(temp_set->CR0b));
	  paired_CR1b[j] = (&(temp_set->CR1b));
	  paired_CR2b[j] = (&(temp_set->CR2b));
	  paired_CR3b[j] = (&(temp_set->CR3b));
	  paired_SR3L1[j] = (&(temp_set->SR3L1));
	  paired_SR3L2[j] = (&(temp_set->SR3L2));
	  paired_SR0b1[j] = (&(temp_set->SR0b1));
	  paired_SR0b2[j] = (&(temp_set->SR0b2));
	  paired_SR0b5[j] = (&(temp_set->SR0b5));
	  paired_SR1b1[j] = (&(temp_set->SR1b1));
	  paired_SR1b2[j] = (&(temp_set->SR1b2));
	  paired_SR2b1[j] = (&(temp_set->SR2b1));
	  paired_SR2b2[j] = (&(temp_set->SR2b2));
	  paired_SR3b1[j] = (&(temp_set->SR3b1));
	  paired_SR3b2[j] = (&(temp_set->SR3b2));
	  paired_SRCMS[j] = (&(temp_set->SRCMS));
	  paired_SR3L[j] = (&(temp_set->SR3L));*/
  }

  for (int j = 0; j < N_unc_unpaired; j++) {
    distrSignature* temp_set = unpaired[j];
	unpaired_PRE[j] = (&(temp_set->PRE));
	unpaired_SR3b[j] = (&(temp_set->SR3b));
	unpaired_SR3bmNJETS[j] = (&(temp_set->SR3bmNJETS));
	unpaired_SR3bmNBJETS[j] = (&(temp_set->SR3bmNBJETS));
	unpaired_SR3bmMET[j] = (&(temp_set->SR3bmMET));
	unpaired_SR3bmMeff[j] = (&(temp_set->SR3bmMeff));


	/*unpaired_CR0b[j] = (&(temp_set->CR0b));
	  unpaired_CR1b[j] = (&(temp_set->CR1b));
	  unpaired_CR2b[j] = (&(temp_set->CR2b));
	  unpaired_CR3b[j] = (&(temp_set->CR3b));
	  unpaired_SR3L1[j] = (&(temp_set->SR3L1));
	  unpaired_SR3L2[j] = (&(temp_set->SR3L2));
	  unpaired_SR0b1[j] = (&(temp_set->SR0b1));
	  unpaired_SR0b2[j] = (&(temp_set->SR0b2));
	  unpaired_SR0b5[j] = (&(temp_set->SR0b5));
	  unpaired_SR1b1[j] = (&(temp_set->SR1b1));
	  unpaired_SR1b2[j] = (&(temp_set->SR1b2));
	  unpaired_SR2b1[j] = (&(temp_set->SR2b1));
	  unpaired_SR2b2[j] = (&(temp_set->SR2b2));
	  unpaired_SR3b1[j] = (&(temp_set->SR3b1));
	  unpaired_SR3b2[j] = (&(temp_set->SR3b2));
	  unpaired_SRCMS[j] = (&(temp_set->SRCMS));
	  unpaired_SR3L[j] = (&(temp_set->SR3L));*/
  }

  draw_Region(set.PRE, sig.PRE, paired_PRE, unpaired_PRE, fit);
  draw_Region(set.SR3b, sig.SR3b, paired_SR3b, unpaired_SR3b, fit);
  draw_Region(set.SR3bmNJETS, sig.SR3bmNJETS, paired_SR3bmNJETS, unpaired_SR3bmNJETS, fit);
  draw_Region(set.SR3bmNBJETS, sig.SR3bmNBJETS, paired_SR3bmNBJETS, unpaired_SR3bmNBJETS, fit);
  draw_Region(set.SR3bmMET, sig.SR3bmMET, paired_SR3bmMET, unpaired_SR3bmMET, fit);
  draw_Region(set.SR3bmMeff, sig.SR3bmMeff, paired_SR3bmMeff, unpaired_SR3bmMeff, fit);

  /*draw_Region(set.CR0b, sig.CR0b, paired_CR0b, unpaired_CR0b, fit);
	draw_Region(set.CR1b, sig.CR1b, paired_CR1b, unpaired_CR1b, fit);
	draw_Region(set.CR2b, sig.CR2b, paired_CR2b, unpaired_CR2b, fit);
	draw_Region(set.CR3b, sig.CR3b, paired_CR3b, unpaired_CR3b, fit);
    draw_Region(set.SR3L1, sig.SR3L1, paired_SR3L1, unpaired_SR3L1, fit);
	draw_Region(set.SR3L2, sig.SR3L2, paired_SR3L2, unpaired_SR3L2, fit);
	draw_Region(set.SR0b1, sig.SR0b1, paired_SR0b1, unpaired_SR0b1, fit);
	draw_Region(set.SR0b2, sig.SR0b2, paired_SR0b2, unpaired_SR0b2, fit);
	draw_Region(set.SR0b5, sig.SR0b5, paired_SR0b5, unpaired_SR0b5, fit);
	draw_Region(set.SR1b1, sig.SR1b1, paired_SR1b1, unpaired_SR1b1, fit);
	draw_Region(set.SR1b2, sig.SR1b2, paired_SR1b2, unpaired_SR1b2, fit);
	draw_Region(set.SR2b1, sig.SR2b1, paired_SR2b1, unpaired_SR2b1, fit);
	draw_Region(set.SR2b2, sig.SR2b2, paired_SR2b2, unpaired_SR2b2, fit);
	draw_Region(set.SR3b1, sig.SR3b1, paired_SR3b1, unpaired_SR3b1, fit);
	draw_Region(set.SR3b2, sig.SR3b2, paired_SR3b2, unpaired_SR3b2, fit);
	draw_Region(set.SRCMS, sig.SRCMS, paired_SRCMS, unpaired_SRCMS, fit);
	draw_Region(set.SR3L, sig.SR3L, paired_SR3L, unpaired_SR3L, fit);*/

  return;
}

//-----------------------------------------------------------------------------

void draw_Region(distrRegion &set, distrSigRegion &sig,distrRegion* paired[N_unc_paired], distrRegion* unpaired[N_unc_unpaired], const char* fit){

  distrSet *paired_elel[N_unc_paired];
  distrSet *paired_elmu[N_unc_paired];
  distrSet *paired_mumu[N_unc_paired];
  distrSet *paired_comb[N_unc_paired];

  distrSet *unpaired_elel[N_unc_unpaired];
  distrSet *unpaired_elmu[N_unc_unpaired];
  distrSet *unpaired_mumu[N_unc_unpaired];
  distrSet *unpaired_comb[N_unc_unpaired];

  for (int j = 0; j < N_unc_paired; j++) {
    distrRegion* temp_set = (distrRegion*) paired[j];
	//    paired_elel[j] = &(temp_set->fs_elel);
	//    paired_elmu[j] = &(temp_set->fs_elmu);
	//    paired_mumu[j] = &(temp_set->fs_mumu);
    paired_comb[j] = &(temp_set->fs_comb);
  }

  for (int j = 0; j < N_unc_unpaired; j++) {
    distrRegion* temp_set = (distrRegion*) unpaired[j];
	//    unpaired_elel[j] = &(temp_set->fs_elel);
	//    unpaired_elmu[j] = &(temp_set->fs_elmu);
	//    unpaired_mumu[j] = &(temp_set->fs_mumu);
    unpaired_comb[j] = &(temp_set->fs_comb);
  }

  //  draw_Set(set.fs_elel, sig.fs_elel, paired_elel, unpaired_elel, fit);
  //  draw_Set(set.fs_elmu, sig.fs_elmu, paired_elmu, unpaired_elmu, fit);
  //  draw_Set(set.fs_mumu, sig.fs_mumu, paired_mumu, unpaired_mumu, fit);
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
  TObjArray *paired_NBJETS = new TObjArray(N_unc_paired);
  TObjArray *unpaired_NBJETS = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_bjet1 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_bjet1 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_pt_bjet2 = new TObjArray(N_unc_paired);
  TObjArray *unpaired_pt_bjet2 = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Nmu = new TObjArray(N_unc_paired);
  TObjArray *unpaired_Nmu = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mu1_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mu1_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mu2_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mu2_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mu_eta = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mu_eta = new TObjArray(N_unc_unpaired);
  TObjArray *unpaired_Nel = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Nel = new TObjArray(N_unc_paired);
  TObjArray *paired_el1_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_el1_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_el2_pt = new TObjArray(N_unc_paired);
  TObjArray *unpaired_el2_pt = new TObjArray(N_unc_unpaired);
  TObjArray *paired_el_eta = new TObjArray(N_unc_paired);
  TObjArray *unpaired_el_eta = new TObjArray(N_unc_unpaired);
  TObjArray *paired_MET = new TObjArray(N_unc_paired);
  TObjArray *unpaired_MET = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Meff = new TObjArray(N_unc_paired);
  TObjArray *unpaired_Meff = new TObjArray(N_unc_unpaired);
  TObjArray *paired_METoMeff = new TObjArray(N_unc_paired);
  TObjArray *unpaired_METoMeff = new TObjArray(N_unc_unpaired);
  TObjArray *paired_mT_min = new TObjArray(N_unc_paired);
  TObjArray *unpaired_mT_min = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Mee = new TObjArray(N_unc_paired);
  TObjArray *unpaired_Mee = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Mmumu = new TObjArray(N_unc_paired);
  TObjArray *unpaired_Mmumu = new TObjArray(N_unc_unpaired);
  TObjArray *paired_Nlep = new TObjArray(N_unc_paired);
  TObjArray *unpaired_Nlep = new TObjArray(N_unc_unpaired);
  TObjArray *paired_LEPChargeSum = new TObjArray(N_unc_paired);
  TObjArray *unpaired_LEPChargeSum = new TObjArray(N_unc_unpaired);
  
  for (int j = 0; j < N_unc_paired; j++) {
	distrSet* temp_set = paired[j];

 // N-1 plots first
	if(strstr(set.file_name[0].data(),"NJETS") != NULL ){
	paired_NJETS->Add(temp_set->ST_NJETS);
  }
	else if(strstr(set.file_name[0].data(),"Meff") != NULL ){
  paired_Meff->Add(temp_set->ST_Meff);
  }
	else if(strstr(set.file_name[0].data(),"NBJETS") != NULL ){
 paired_NBJETS->Add(temp_set->ST_NBJETS);
  }
	else if(strstr(set.file_name[0].data(),"MET") != NULL ){
 paired_MET->Add(temp_set->ST_MET);
  }
  else{
	paired_NJETS->Add(temp_set->ST_NJETS);
	if(!test_me){
	  paired_pt_jet1->Add(temp_set->ST_pt_jet1);
	  paired_pt_jet2->Add(temp_set->ST_pt_jet2);
	  paired_NBJETS->Add(temp_set->ST_NBJETS);
	  paired_pt_bjet1->Add(temp_set->ST_pt_bjet1);
	  paired_pt_bjet2->Add(temp_set->ST_pt_bjet2);
	  paired_Nmu->Add(temp_set->ST_Nmu);
	  paired_mu1_pt->Add(temp_set->ST_mu1_pt);
	  paired_mu2_pt->Add(temp_set->ST_mu2_pt);
	  paired_mu_eta->Add(temp_set->ST_mu_eta);
	  paired_Nel->Add(temp_set->ST_Nel);
	  paired_el1_pt->Add(temp_set->ST_el1_pt);
	  paired_el2_pt->Add(temp_set->ST_el2_pt);
	  paired_el_eta->Add(temp_set->ST_el_eta);
	  paired_MET->Add(temp_set->ST_MET);
	  paired_Meff->Add(temp_set->ST_Meff);
	  paired_METoMeff->Add(temp_set->ST_METoMeff);
	  paired_mT_min->Add(temp_set->ST_mT_min);
	  paired_Mee->Add(temp_set->ST_Mee);
	  paired_Mmumu->Add(temp_set->ST_Mmumu);
	  paired_Nlep->Add(temp_set->ST_Nlep);
	  paired_LEPChargeSum->Add(temp_set->ST_LEPChargeSum);
  }
  }
  }

  for (int j = 0; j < N_unc_unpaired; j++) {
	distrSet* temp_set = unpaired[j];

 // N-1 plots first
	if(strstr(set.file_name[0].data(),"NJETS") != NULL ){
	unpaired_NJETS->Add(temp_set->ST_NJETS);
  }
	else if(strstr(set.file_name[0].data(),"Meff") != NULL ){
  unpaired_Meff->Add(temp_set->ST_Meff);
  }
	else if(strstr(set.file_name[0].data(),"NBJETS") != NULL ){
 unpaired_NBJETS->Add(temp_set->ST_NBJETS);
  }
	else if(strstr(set.file_name[0].data(),"MET") != NULL ){
 unpaired_MET->Add(temp_set->ST_MET);
  }
  else{
	unpaired_NJETS->Add(temp_set->ST_NJETS);
	if(!test_me){
	  unpaired_pt_jet1->Add(temp_set->ST_pt_jet1);
	  unpaired_pt_jet2->Add(temp_set->ST_pt_jet2);
	  unpaired_NBJETS->Add(temp_set->ST_NBJETS);
	  unpaired_pt_bjet1->Add(temp_set->ST_pt_bjet1);
	  unpaired_pt_bjet2->Add(temp_set->ST_pt_bjet2);
	  unpaired_Nmu->Add(temp_set->ST_Nmu);
	  unpaired_mu1_pt->Add(temp_set->ST_mu1_pt);
	  unpaired_mu2_pt->Add(temp_set->ST_mu2_pt);
	  unpaired_mu_eta->Add(temp_set->ST_mu_eta);
	  unpaired_Nel->Add(temp_set->ST_Nel);
	  unpaired_el1_pt->Add(temp_set->ST_el1_pt);
	  unpaired_el2_pt->Add(temp_set->ST_el2_pt);
	  unpaired_el_eta->Add(temp_set->ST_el_eta);
	  unpaired_MET->Add(temp_set->ST_MET);
	  unpaired_Meff->Add(temp_set->ST_Meff);	  
	  unpaired_METoMeff->Add(temp_set->ST_METoMeff);
	  unpaired_mT_min->Add(temp_set->ST_mT_min);
	  unpaired_Mee->Add(temp_set->ST_Mee);
	  unpaired_Mmumu->Add(temp_set->ST_Mmumu);
	  unpaired_Nlep->Add(temp_set->ST_Nlep);
	  unpaired_LEPChargeSum->Add(temp_set->ST_LEPChargeSum);
  }
  }
  }
  //  drawAVariable_test(set.ST_NJETS, set.NJETS, sig.NJETS, paired_NJETS, unpaired_NJETS, fit);
  //  drawAVariable_all(set.ST_NJETS, set.NJETS, sig.NJETS, paired_NJETS, unpaired_NJETS, fit);

  //  drawAVariable_normalized(set.ST_NJETS, set.NJETS, sig.NJETS, paired_NJETS, unpaired_NJETS, fit);
 // N-1 plots first
	if(strstr(set.file_name[0].data(),"NJETS") != NULL ){
  drawAVariable_merged(set.ST_NJETS, set.NJETS, sig.NJETS, paired_NJETS, unpaired_NJETS, fit);
  }
	else if(strstr(set.file_name[0].data(),"Meff") != NULL ){
drawAVariable_merged(set.ST_Meff, set.Meff, sig.Meff, paired_Meff, unpaired_Meff, fit);
  }
	else if(strstr(set.file_name[0].data(),"NBJETS") != NULL ){
drawAVariable_merged(set.ST_NBJETS, set.NBJETS, sig.NBJETS, paired_NBJETS, unpaired_NBJETS, fit);
  }
	else if(strstr(set.file_name[0].data(),"MET") != NULL ){
	drawAVariable_merged(set.ST_MET, set.MET, sig.MET, paired_MET, unpaired_MET, fit);
  }
  else{
  drawAVariable_merged(set.ST_NJETS, set.NJETS, sig.NJETS, paired_NJETS, unpaired_NJETS, fit);
  if(!test_me){
	drawAVariable_merged(set.ST_pt_jet1, set.pt_jet1, sig.pt_jet1, paired_pt_jet1, unpaired_pt_jet1, fit);
	drawAVariable_merged(set.ST_pt_jet2, set.pt_jet2, sig.pt_jet2, paired_pt_jet2, unpaired_pt_jet2, fit);
	drawAVariable_merged(set.ST_NBJETS, set.NBJETS, sig.NBJETS, paired_NBJETS, unpaired_NBJETS, fit);
	drawAVariable_merged(set.ST_pt_bjet1, set.pt_bjet1, sig.pt_bjet1, paired_pt_bjet1, unpaired_pt_bjet1, fit);
	drawAVariable_merged(set.ST_pt_bjet2, set.pt_bjet2, sig.pt_bjet2, paired_pt_bjet2, unpaired_pt_bjet2, fit);
	drawAVariable_merged(set.ST_Nmu, set.Nmu, sig.Nmu, paired_Nmu, unpaired_Nmu, fit);
	drawAVariable_merged(set.ST_mu1_pt, set.mu1_pt, sig.mu1_pt, paired_mu1_pt, unpaired_mu1_pt, fit);
	drawAVariable_merged(set.ST_mu2_pt, set.mu2_pt, sig.mu2_pt, paired_mu2_pt, unpaired_mu2_pt, fit);
	drawAVariable_merged(set.ST_mu_eta, set.mu_eta, sig.mu_eta, paired_mu_eta, unpaired_mu_eta, fit);
	drawAVariable_merged(set.ST_Nel, set.Nel, sig.Nel, paired_Nel, unpaired_Nel, fit);
	drawAVariable_merged(set.ST_el1_pt, set.el1_pt, sig.el1_pt, paired_el1_pt, unpaired_el1_pt, fit);
	drawAVariable_merged(set.ST_el2_pt, set.el2_pt, sig.el2_pt, paired_el2_pt, unpaired_el2_pt, fit);
	drawAVariable_merged(set.ST_el_eta, set.el_eta, sig.el_eta, paired_el_eta, unpaired_el_eta, fit);
	drawAVariable_merged(set.ST_MET, set.MET, sig.MET, paired_MET, unpaired_MET, fit);
	drawAVariable_merged(set.ST_Meff, set.Meff, sig.Meff, paired_Meff, unpaired_Meff, fit);
	drawAVariable_merged(set.ST_METoMeff, set.METoMeff, sig.METoMeff, paired_METoMeff, unpaired_METoMeff, fit);
	drawAVariable_merged(set.ST_mT_min, set.mT_min, sig.mT_min, paired_mT_min, unpaired_mT_min, fit);
	drawAVariable_merged(set.ST_Mee, set.Mee, sig.Mee, paired_Mee, unpaired_Mee, fit);
	drawAVariable_merged(set.ST_Mmumu, set.Mmumu, sig.Mmumu, paired_Mmumu, unpaired_Mmumu, fit);
	drawAVariable_merged(set.ST_Nlep, set.Nlep, sig.Nlep, paired_Nlep, unpaired_Nlep, fit);
	drawAVariable_merged(set.ST_LEPChargeSum, set.LEPChargeSum, sig.LEPChargeSum, paired_LEPChargeSum, unpaired_LEPChargeSum, fit);

  }
  }
  //calculate and output to a file

  delete paired_NJETS;
  delete unpaired_NJETS;
  delete paired_pt_jet1;
  delete unpaired_pt_jet1;
  delete paired_pt_jet2;
  delete unpaired_pt_jet2;
  delete paired_NBJETS;
  delete unpaired_NBJETS;
  delete paired_pt_bjet1;
  delete unpaired_pt_bjet1;
  delete paired_pt_bjet2;
  delete unpaired_pt_bjet2;
  delete paired_Nmu;
  delete unpaired_Nmu;
  delete paired_mu1_pt;
  delete unpaired_mu1_pt;
  delete paired_mu2_pt;
  delete unpaired_mu2_pt;
  delete paired_mu_eta;
  delete unpaired_mu_eta;
  delete paired_Nel;
  delete unpaired_Nel;
  delete paired_el1_pt;
  delete unpaired_el1_pt;
  delete paired_el2_pt;
  delete unpaired_el2_pt;
  delete paired_el_eta;
  delete unpaired_el_eta;
  delete paired_MET;
  delete unpaired_MET;
  delete paired_Meff;
  delete unpaired_Meff;
  delete paired_METoMeff;
  delete unpaired_METoMeff;
  delete paired_mT_min;
  delete unpaired_mT_min;
  delete paired_Mee;
  delete unpaired_Mee;
  delete paired_Mmumu;
  delete unpaired_Mmumu;
  delete paired_Nlep;
  delete unpaired_Nlep;
  delete paired_LEPChargeSum;
  delete unpaired_LEPChargeSum;

  return;
}

// draw simple for tests
//-----------------------------------------------------------------------------
void drawAVariable_test(THStack* &st, TH1D* hist[N_MC], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit){
  
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
  for (int i = 0; i < N_MC; i++) 
	desc.push_back(std::make_pair(description_mc[i],hist[i]));	
  std::sort(desc.begin(), desc.end(), hasLessEventspair);
  std::vector<std::pair<string,TH1D*>>::reverse_iterator desc_it = desc.rbegin();
  for (; desc_it != desc.rend(); ++desc_it){
	std::sprintf(temp, "%s (%.1e)", (*desc_it).first.data(), (*desc_it).second->Integral());
	leg->AddEntry((*desc_it).second, temp , "f");
  }

  for (int i = 0; i < N_SIG; i++){
		std::sprintf(temp, "%s (%.1e)", description_SIG[i].data(), sig[i]->Integral());
	//	std::sprintf(temp, "%s (%.1e)", files[i].data(), sig[i]->Integral());
	leg->AddEntry(sig[i], temp, "l");
  }

  leg->Draw("same");
  myPad->RedrawAxis();
  myPlots->Update();

  char my_extension[256] = "";
  sprintf(my_extension, "/tmp/plot-tests/%s.pdf", hist[0]->GetName());
  myPlots->Print(my_extension);

  delete myPlots;

  return;
}

// draw simple for tests
//-----------------------------------------------------------------------------
void drawAVariable_normalized(THStack* &st, TH1D* hist[N_MC], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit){
  
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

	if (strstr(hist[0]->GetName(), "_SR3b_") != NULL)
	  legendHeader += ", SR3b, ";

	if (strstr(hist[0]->GetName(), "_SR3bmMEToMeff_") != NULL)
	  legendHeader += ", SR3b - NJETS, ";

	if (strstr(hist[0]->GetName(), "_SR3bmNBJETS_") != NULL)
	  legendHeader += ", SR3b - NBJETS, ";

	if (strstr(hist[0]->GetName(), "_SR3bmMET_") != NULL)
	  legendHeader += ", SR3b - MET, ";

	if (strstr(hist[0]->GetName(), "_SR3bmMeff_") != NULL)
	  legendHeader += ", SR3b - Meff, ";

	if (strstr(hist[0]->GetName(), "_CR0b_") != NULL)
	  legendHeader += ", CR0b, ";

	if (strstr(hist[0]->GetName(), "_CR1b_") != NULL)
	  legendHeader += ", CR1b, ";

	if (strstr(hist[0]->GetName(), "_CR2b_") != NULL)
	  legendHeader += ", CR2b, ";

	if (strstr(hist[0]->GetName(), "_CR3b_") != NULL)
	  legendHeader += ", CR3b, ";

	// channels
	if (strstr(hist[0]->GetName(), "_comb_") != NULL)
	  legendHeader += "ee+e#mu+#mu#mu";

	if (strstr(hist[0]->GetName(), "_ee_") != NULL)
	  legendHeader += "ee";
	
	if (strstr(hist[0]->GetName(), "_em_") != NULL)
	  legendHeader += "e#mu";
	
	if (strstr(hist[0]->GetName(), "_mm_") != NULL)
	  legendHeader += "#mu#mu";

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
	sprintf(fpath, "/tmp/plot-tests/%s", folder);
	int res = mkdir(fpath, 0700);
	sprintf(fpath, "/tmp/plot-tests/%s/normalized", folder);
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
void drawAVariable_all(THStack* &st, TH1D* hist[N_MC], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit){  

  for (int ilog=0; ilog<2; ilog++){
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

	if ((st->GetMaximum() == 0) && (hist[0]->GetEntries() == 0) && (sig_max == 0)) {
	  return;
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
	double new_maximum = sig_max;
	if (new_maximum < background_maximum)
	  new_maximum = background_maximum;

	TH1D *err_brs = errorBars(st, paired, unpaired);
	//error-bars are included into the calculations of maximum
	double err_brs_maximum = GetMyMaximum(err_brs, x_low, x_high, is_log);
	if (err_brs_maximum > new_maximum)
	  new_maximum = err_brs_maximum;

	//----------------------------
	if (x_low > 0 && x_high > 0) {
	  st->GetXaxis()->SetRange(x_low, x_high);
	  err_brs->GetXaxis()->SetRange(x_low, x_high);
	  background->GetXaxis()->SetRange(x_low, x_high);
	}

	if (is_log) {
	  st->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  err_brs->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  background->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	} else {
	  st->SetMaximum(1.28 * new_maximum);
	  err_brs->SetMaximum(1.28 * new_maximum);
	  background->SetMaximum(1.28 * new_maximum);
	}
  
	if (is_log) {
	  st->SetMinimum(0.2);
	  err_brs->SetMinimum(0.2);
	  background->SetMinimum(0.2);
	} else {
	  st->SetMinimum(0);
	  err_brs->SetMinimum(0);
	  background->SetMinimum(0);
	}

	//  st->GetXaxis()->SetNdivisions(2 + x_high - x_low);
	st->GetYaxis()->SetTitleOffset(1.6);
	st->Draw("9 hist");
	err_brs->Draw("9 same  E2");
	if (sig_max > 0) {
	  for (int i = 0; i < N_SIG; i++)
		sig[i]->Draw("9 hist same");
	}

	// total MC
	background->SetLineColor(kBlue);
	background->SetFillColor(kWhite);
	background->SetLineWidth(2);
	background->Draw("9 HIST same");
	
	TLegend* leg;
	leg = new TLegend(0.65, 0.55, 0.87, 0.92);
	leg->SetTextAlign(12);
	leg->SetFillColor(0);
	//  leg->SetTextSize(0.032);
	leg->SetBorderSize(0);
	std::string legendHeader = "Detailed MC ";
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
	if (strstr(hist[0]->GetName(), "_PRE_") != NULL)
	  legendHeader += ", Inclusive, ";

	if (strstr(hist[0]->GetName(), "_SR3b_") != NULL)
	  legendHeader += ", SR3b, ";

	if (strstr(hist[0]->GetName(), "_SR3bmMEToMeff_") != NULL)
	  legendHeader += ", SR3b - NJETS, ";

	if (strstr(hist[0]->GetName(), "_SR3bmNBJETS_") != NULL)
	  legendHeader += ", SR3b - NBJETS, ";

	if (strstr(hist[0]->GetName(), "_SR3bmMET_") != NULL)
	  legendHeader += ", SR3b - MET, ";

	if (strstr(hist[0]->GetName(), "_SR3bmMeff_") != NULL)
	  legendHeader += ", SR3b - Meff, ";

	if (strstr(hist[0]->GetName(), "_CR0b_") != NULL)
	  legendHeader += ", CR0b, ";

	if (strstr(hist[0]->GetName(), "_CR1b_") != NULL)
	  legendHeader += ", CR1b, ";

	if (strstr(hist[0]->GetName(), "_CR2b_") != NULL)
	  legendHeader += ", CR2b, ";

	if (strstr(hist[0]->GetName(), "_CR3b_") != NULL)
	  legendHeader += ", CR3b, ";

	// channels
	if (strstr(hist[0]->GetName(), "_comb_") != NULL)
	  legendHeader += "ee+e#mu+#mu#mu";

	if (strstr(hist[0]->GetName(), "_ee_") != NULL)
	  legendHeader += "ee";
	
	if (strstr(hist[0]->GetName(), "_em_") != NULL)
	  legendHeader += "e#mu";
	
	if (strstr(hist[0]->GetName(), "_mm_") != NULL)
	  legendHeader += "#mu#mu";

	leg->SetHeader(legendHeader.data());
	char temp[128];
	std::sprintf(temp, "Total MC (%.1e)", background->Integral());
	leg->AddEntry(background, temp , "fl");  
	std::vector<std::pair<string,TH1D*>> desc;
	for (int i = 0; i < N_MC; i++) 
	  desc.push_back(std::make_pair(description_mc[i],hist[i]));	
	std::sort(desc.begin(), desc.end(), hasLessEventspair);
	std::vector<std::pair<string,TH1D*>>::reverse_iterator desc_it = desc.rbegin();
	for (; desc_it != desc.rend(); ++desc_it){
	  std::sprintf(temp, "%s (%.1e)", (*desc_it).first.data(), (*desc_it).second->Integral());
	  leg->AddEntry((*desc_it).second, temp , "f");
	}
	if (sig_max > 0) 
	  for (int i = 0; i < N_SIG; i++){
		std::sprintf(temp, "%s (%.1e)", description_SIG[i].data(), sig[i]->Integral());
		leg->AddEntry(sig[i], temp, "l");
	  }

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
	sprintf(fpath, "/tmp/plot-tests/%s", folder);
	int res = mkdir(fpath, 0700);
	sprintf(fpath, "/tmp/plot-tests/%s/all", folder);
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

// draw merged stacked plots, "drawAVariable_long" draws all of them
//-----------------------------------------------------------------------------
void drawAVariable_merged(THStack* &st, TH1D* hist[N_MC], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired, const char* fit){
  
  int color[N_MC];
  //Specify the colors

  int ind=0;
  color[ind++] =  TColor::GetColor("#cc99ff"); //kTeal; // ttW, ttZ
  color[ind++] = 0;
  color[ind++] = TColor::GetColor("#3399ff"); // WW, WZ, ZZ
  color[ind++] = 0;
  color[ind++] = 0;
    color[ind++] = kOrange-2; // tth, Wh, Zh
    color[ind++] = 0;
  color[ind++] =  TColor::GetColor("#339900"); //kAzure +7; // tt+WW/t/tt, tZ, VVV
  color[ind++] = 0;
  color[ind++] = 0;
  color[ind++] = 0;
  color[ind++] = 0;
  color[ind++] = 0;
  color[ind++] = TColor::GetColor("#ffcc99"); //kOrange - 6; // ttbar, single top
  color[ind++] = TColor::GetColor("#993300"); //kTeal + 4; // Z+jets
  color[ind++] = kGray; // W+jets
  color[ind++] = kRed+2 ; // W+jets

  for (int ilog=0; ilog<2; ilog++){
	
	// setup the merging machinery
	TH1D *my_hist[N_MC];
	char my_name[256];
	for (int i = 0; i < N_MC; i++)
	  if (map_mc_merged[i] == -1) {
		sprintf(my_name, "Merged_%s", hist[i]->GetName());
		my_hist[i] = (TH1D*) hist[i]->Clone(my_name);
		my_hist[i]->SetFillColor(color[i]);
		my_hist[i]->SetLineWidth(1);
		my_hist[i]->SetLineColor(1);
		my_hist[i]->SetLineStyle(1);
		my_hist[i]->SetFillStyle(1001);
		my_hist[i]->SetMarkerStyle(20);
		my_hist[i]->SetMarkerSize(1.2);
		my_hist[i]->GetXaxis()->SetLabelFont(42);
		my_hist[i]->GetXaxis()->SetLabelSize(0.05);
		my_hist[i]->GetXaxis()->SetTitleSize(0.05);
		my_hist[i]->GetXaxis()->SetTitleOffset(1.4);
		my_hist[i]->GetXaxis()->SetTitleFont(42);
		my_hist[i]->GetYaxis()->SetLabelFont(42);
		my_hist[i]->GetYaxis()->SetLabelSize(0.05);
		my_hist[i]->GetYaxis()->SetTitleSize(0.05);
		my_hist[i]->GetYaxis()->SetTitleOffset(1.4);
		my_hist[i]->GetYaxis()->SetTitleFont(42);
	  }

	for (int i = 0; i < N_MC; i++)
	  if (map_mc_merged[i] > -1) {
		my_hist[map_mc_merged[i]]->Add(hist[i]);
	  }

	//We build Stacked plots here

	sprintf(my_name, "Merged_HSTACK_%s", hist[0]->GetName());
	THStack* my_st = new THStack(my_name, "Hstack");
	
	std::vector<std::pair<string,TH1D*>> desc;
	for (int i = 0; i < N_MC; i++)
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

	TH1D *err_brs = errorBars(my_st, paired, unpaired);
	//error-bars are included into the calculations of maximum
	double err_brs_maximum = GetMyMaximum(err_brs, x_low, x_high, is_log);
	if (err_brs_maximum > new_maximum)
	  new_maximum = err_brs_maximum;

	//----------------------------
	if (x_low > 0 && x_high > 0) {
	  my_st->GetXaxis()->SetRange(x_low, x_high);
	  err_brs->GetXaxis()->SetRange(x_low, x_high);
	  background->GetXaxis()->SetRange(x_low, x_high);
	}

	if (is_log) {
	  my_st->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  err_brs->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	  background->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	} else {
	  my_st->SetMaximum(1.28 * new_maximum);
	  err_brs->SetMaximum(1.28 * new_maximum);
	  background->SetMaximum(1.28 * new_maximum);
	}
  
	if (is_log) {
	  my_st->SetMinimum(0.2);
	  err_brs->SetMinimum(0.2);
	  background->SetMinimum(0.2);
	} else {
	  my_st->SetMinimum(0);
	  err_brs->SetMinimum(0);
	  background->SetMinimum(0);
	}

	//  my_st->GetXaxis()->SetNdivisions(2 + x_high - x_low);
	my_st->Draw("hist");
	my_st->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
	my_st->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());	
	my_st->GetYaxis()->SetTitleOffset(1.6);

	my_st->Draw("9 hist same");
	err_brs->Draw("9 same  E2");

	// total MC
	background->SetLineColor(kBlue);
	background->SetFillColor(kWhite);
	background->SetLineWidth(2);
	background->Draw("9 HIST same");
	if (sig_max > 0) {
	  for (int i = 0; i < N_SIG; i++)
		sig[i]->Draw("9 hist same");
	}


	/*	TLegend* leg2;
	leg2 = new TLegend(0.65, 0.845, 0.87, 0.885);
	leg2->SetTextAlign(12);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->SetTextSize(0.02);
	leg2->SetTextFont(42);
	leg2->SetBorderSize(0);
	err_brs->SetTitle("");
	leg2->AddEntry(err_brs, "", "f");
	*/
	TLegend* leg;
	leg = new TLegend(0.65, 0.55, 0.87, 0.92);
	leg->SetTextAlign(12);
	leg->SetFillColor(0);
	leg->SetTextSize(0.02);
	leg->SetTextFont(42);
	leg->SetBorderSize(0);
	std::string legendHeader = "MC ";
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

	if (strstr(hist[0]->GetName(), "_SR3b_") != NULL)
	  legendHeader += ", SR3b, ";

	if (strstr(hist[0]->GetName(), "_SR3bmMEToMeff_") != NULL)
	  legendHeader += ", SR3b - NJETS, ";

	if (strstr(hist[0]->GetName(), "_SR3bmNBJETS_") != NULL)
	  legendHeader += ", SR3b - NBJETS, ";

	if (strstr(hist[0]->GetName(), "_SR3bmMET_") != NULL)
	  legendHeader += ", SR3b - MET, ";

	if (strstr(hist[0]->GetName(), "_SR3bmMeff_") != NULL)
	  legendHeader += ", SR3b - Meff, ";


	if (strstr(hist[0]->GetName(), "_CR0b_") != NULL)
	  legendHeader += ", CR0b, ";

	if (strstr(hist[0]->GetName(), "_CR1b_") != NULL)
	  legendHeader += ", CR1b, ";

	if (strstr(hist[0]->GetName(), "_CR2b_") != NULL)
	  legendHeader += ", CR2b, ";

	if (strstr(hist[0]->GetName(), "_CR3b_") != NULL)
	  legendHeader += ", CR3b, ";

	// channels
	if (strstr(hist[0]->GetName(), "_comb_") != NULL)
	  legendHeader += "ee+e#mu+#mu#mu";

	if (strstr(hist[0]->GetName(), "_ee_") != NULL)
	  legendHeader += "ee";
	
	if (strstr(hist[0]->GetName(), "_em_") != NULL)
	  legendHeader += "e#mu";
	
	if (strstr(hist[0]->GetName(), "_mm_") != NULL)
	  legendHeader += "#mu#mu";
	
	leg->SetHeader(legendHeader.data());
	char temp[128];
	std::sprintf(temp, "Total MC (%.1e)", background->Integral());
	leg->AddEntry(background, temp , "fl");  
	
	std::vector<std::pair<string,TH1D*>>::reverse_iterator desc_it = desc.rbegin();
	for (; desc_it != desc.rend(); ++desc_it){
	  std::sprintf(temp, "%s (%.1e)", (*desc_it).first.data(), (*desc_it).second->Integral());
	  leg->AddEntry((*desc_it).second, temp , "f");
	}
	
	if (sig_max > 0) 
	  for (int i = 0; i < N_SIG; i++){
		double zExp = RooStats::NumberCountingUtils::BinomialExpZ(sig[i]->Integral(),  background->Integral(), .3);
		//		std::sprintf(temp, "%s (%.1e, %.1f)", description_SIG[i].data(), sig[i]->Integral(), zExp);
		std::sprintf(temp, "%s (%.1e, %.1f)", files[i].data(), sig[i]->Integral(), zExp);
		leg->AddEntry(sig[i], temp, "l");
	  }
	
	leg->Draw("same");
	//	leg2->Draw("same");

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
	sprintf(fpath, "/tmp/plot-tests/%s", folder);
	int res = mkdir(fpath, 0700);
	sprintf(fpath, "/tmp/plot-tests/%s/merged", folder);
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

  // Luminosity
  distrAll det_lvl_pLUMI;
  distrAll det_lvl_mLUMI;
  
  // cross sections
  distrAll det_lvl_pTTbar;
  distrAll det_lvl_mTTbar;

  // Unpaired systematics
  
  // Generator
  distrAll det_lvl_pGen;
  
  //------------------------------------------
  // Get data
  std::cout << "\nStart reading files...\n";

  std::cout << "\n// Nominal\n";
  getData_All(det_lvl, tag, "");
  getData_SigAll(signal, tag, ""); // comment out if you don't want to plot signal
  
  /*  std::cout << "// Systematics for luminosity\n";
	  std::cout << "==> up\n";
	  getData_All(det_lvl_pLUMI, tag, "_pLUMI");
	  std::cout << "==> down\n";
	  getData_All(det_lvl_mLUMI, tag, "_mLUMI");

	  std::cout << "Systematics for ttbar cross section\n\n";
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
  Float_t c_lumi_up = 1. + 0.35; //0.05;
  Float_t c_lumi_dn = 1. - 0.35; //0.05;
  //  scaleLumi_All(det_lvl_pLUMI, c_lumi_up);
  //  scaleLumi_All(det_lvl_mLUMI, c_lumi_dn);

  //scale ttbar x-section
  //  scaleXSect_All(det_lvl_pTTbar, ttbar_ind, (1. + 0.0));
  //  scaleXSect_All(det_lvl_mTTbar, ttbar_ind, (1. - 0.0));

  // scale signal xsection up to see it
  scaleXSect_SigAll(signal, 0, 1);
  scaleXSect_SigAll(signal, 1, 1);
  scaleXSect_SigAll(signal, 2, 1);

  std::cout << "\n...done scaling\n";
  //------------------------------------------
  // Weight with new scales 
  std::cout << "\nStart re-weighting...\n";
  std::cout << "\nRe-weighting background and data\n";
  weightData_All(det_lvl);
  std::cout << "\nRe-weighting signal\n";
  weightData_SigAll(signal);

  //  std::cout << "\nRe-weighting luminosity\n";
  //  weightData_All(det_lvl_pLUMI);
  //  weightData_All(det_lvl_mLUMI);

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
  paired[ind_paired++] = &det_lvl;//_pLUMI;
  paired[ind_paired++] = &det_lvl;//_mLUMI;
  paired[ind_paired++] = &det_lvl;//_pTTbar;
  paired[ind_paired++] = &det_lvl;//_mTTbar;

  int ind_unpaired=0;
  unpaired[ind_unpaired++] = &det_lvl;//_pGen;

  //------------------------------------------
 
  //------------------------------------------
  // Draw observables
  draw_All(det_lvl, signal, paired, unpaired, "MC");
  //------------------------------------------
  
  gSystem->Exit(0);
  return 0;
}
