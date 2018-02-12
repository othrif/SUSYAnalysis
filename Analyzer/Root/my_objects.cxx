/*****************************************************************************/
/*                                                                           */
/* File Name        : my_objects.cxx                                         */
/*                                                                           */
/* Author           : Othmane Rifki			                                 */
/* Email            : othmane.rifki@cern.ch			                         */
/*                                                                           */
/* Description      : Provides necessery functions to Plotter for SS/3L      */
/*                    has a header file my_objects.h                         */
/*                                                                           */
/*                                                                           */
/***** C 2016 ****************************************************************/

// These are standard C++ header files.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <strstream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>

// These are ROOT header files.
#include "TChain.h"
#include "TLeaf.h"            
#include "TFile.h"
#include "TProfile.h"
#include "TH2.h"
#include "TH1.h"
#include "TF1.h"
#include "TVirtualPS.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TVector3.h"
#include "TRandom.h"
#include "TRandom2.h"
#include "TLorentzVector.h"

//here are the project-specific files
#include "Analyzer/my_objects.h" 
#include "xAODRootAccess/tools/Message.h"

bool debug = false;
bool otilia = false;
bool detail = false;
bool reduce = true;

//------------------------------------------------------------------------
//				-= Histograms =-
//------------------------------------------------------------------------

void BookHistos_Channel(const char* ftag, const char* tag) {

  char new_tag[256];
 
  sprintf(new_tag, "%s", tag);
  BookHistos_SystSet(ftag, new_tag);


  return;	
}
void BookHistos_SystSet(const char* ftag, const char* tag) {

  char new_tag[256];

  sprintf(new_tag, "%s", tag); // nominal
  BookHistos_Regions(ftag, new_tag);
  /*
    sprintf(new_tag, "pPDF_%s", tag);
    BookHistos_Regions(ftag, new_tag);

    sprintf(new_tag, "mPDF_%s", tag);
    BookHistos_Regions(ftag, new_tag);

    sprintf(new_tag, "pPDF_CT10_%s", tag);
    BookHistos_Regions(ftag, new_tag);

    sprintf(new_tag, "mPDF_CT10_%s", tag);
    BookHistos_Regions(ftag, new_tag);

    sprintf(new_tag, "pPDF_NNPDF_130_%s", tag);
    BookHistos_Regions(ftag, new_tag);

    sprintf(new_tag, "mPDF_NNPDF_130_%s", tag);
    BookHistos_Regions(ftag, new_tag);
  */

  /*
  //  char new_tag[256];
  // Nominal
  BookHistos(tag);
  // Systematics
  sprintf(new_tag, "%s_pJES", tag);
  BookHistos(new_tag);
  sprintf(new_tag, "%s_mJES", tag);
  BookHistos(new_tag);*/

  return;	
}

void BookHistos_Regions(const char* ftag, const char* tag) {

  char hname[256];
  sprintf(hname, "Incl_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "PRE_%s", tag);
  BookHistos(ftag, hname);
  
  sprintf(hname, "CR0b_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "CR1b_%s", tag);
  BookHistos(ftag, hname);

  /*  sprintf(hname, "CR3b_%s", tag);
  BookHistos(ftag, hname);
  
  sprintf(hname, "SR3L0b1_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3L0b2_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3L1b1_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3L1b2_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR0b1_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR0b2_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b1_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b2_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3b1_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3b2_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SRlow_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SRhigh_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b_3LSS_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b_DD_low_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b_DD_high_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3b_DD_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b_GG_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SRRPV0b_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SRRPV3b_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "Rpc2L2bS_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "Rpc2L2bH_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "Rpv2L2bS_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "Rpv2L2bH_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3L0b1mMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3L0b2mMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3L1b1mMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3L1b2mMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR0b1mMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR0b2mMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b1mMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b2mMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3b1mMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3b2mMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SRlowmMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SRhighmMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b_DD_lowmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b_DD_highmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR3b_DDmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SR1b_GGmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SRRPV0bmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SRRPV3bmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "SRRPV2bmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "Rpc2L2bSmMET_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "Rpc2L2bHmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "Rpv2L2bSmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "Rpv2L2bHmMeff_%s", tag);
  BookHistos(ftag, hname);

  sprintf(hname, "VRWW_%s", tag);
  BookHistos(ftag, hname);
  sprintf(hname, "VRWZ4j_%s", tag);
  BookHistos(ftag, hname);
  sprintf(hname, "VRWZ5j_%s", tag);
  BookHistos(ftag, hname);
  sprintf(hname, "VRttW_%s", tag);
  BookHistos(ftag, hname);
  sprintf(hname, "VRttZ_%s", tag);
  BookHistos(ftag, hname);
  */

  return;	
}

void BookHistos(const char* ftag, const char* tag) {

  char hname[256];

  sprintf(hname, "comb_%s", tag);
  BookHistos_New(ftag, hname);
  
  sprintf(hname, "ee_%s", tag);
  BookHistos_New(ftag, hname);

  sprintf(hname, "em_%s", tag);
  BookHistos_New(ftag, hname);

  sprintf(hname, "mm_%s", tag);
  BookHistos_New(ftag, hname);
  /*
  sprintf(hname, "3l_%s", tag);
  BookHistos_New(ftag, hname);
  */
  return;
}

void BookHistos_New(const char* ftag, const char* tag) {

  char hname[256];

  sprintf(hname, "data_%s", tag);
  BookHistos_FS(hname);

  sprintf(hname, "%s_mc_%s", ftag, tag);
  BookHistos_FS(hname);
  //  BookHistos_pt(hname);
   
  sprintf(hname, "real_%s", tag);  // real
  BookHistos_FS(hname);
  //  BookHistos_pt(hname);
  
  sprintf(hname, "%s_prompt_%s", ftag, tag);  // real
  BookHistos_FS(hname);
  
  sprintf(hname, "chmisid_%s", tag);
  BookHistos_FS(hname);
  //  BookHistos_pt(hname);

  sprintf(hname, "fake_HF_e_%s", tag);
  BookHistos_FS(hname);
  //  BookHistos_pt(hname);

  sprintf(hname, "fake_HF_m_%s", tag);
  BookHistos_FS(hname);
  //  BookHistos_pt(hname);
  
  sprintf(hname, "fake_LF_e_%s", tag);
  BookHistos_FS(hname);
  //  BookHistos_pt(hname);  

  sprintf(hname, "fake_LF_m_%s", tag);
  BookHistos_FS(hname);
  //  BookHistos_pt(hname);

  /*  sprintf(hname, "%s_realb_%s", ftag, tag);
  BookHistos_FS(hname);

  sprintf(hname, "%s_fakeb_%s", ftag, tag);
  BookHistos_FS(hname);

  sprintf(hname, "%s_extraB_%s", ftag, tag);
  BookHistos_FS(hname);

  sprintf(hname, "%s_extraC_%s", ftag, tag);
  BookHistos_FS(hname);

  sprintf(hname, "%s_extraNone_%s", ftag, tag);
  BookHistos_FS(hname);
  */


  return;
}

void BookHistos_pt(const char* tag) {

  char hname[256];

  sprintf(hname, "pt10_%s", tag);
  BookHistos_Comp(hname);
  sprintf(hname, "pt15_%s", tag);
  BookHistos_Comp(hname);
  sprintf(hname, "pt20_%s", tag);
  BookHistos_Comp(hname);
  sprintf(hname, "pt30_%s", tag);
  BookHistos_Comp(hname);

  return;

}

void BookHistos_Comp(const char* tag) {

  char hname[256];

  sprintf(hname, "el_%s", tag);
  BookHistos_Comp_FS(hname);

  sprintf(hname, "mu_%s", tag);
  BookHistos_Comp_FS(hname);
  
  return;
}

void BookHistos_Comp_FS(const char* tag) {

  const char* name;
  char hname[256];
  TH1D* h1d;

  name = "composition";
  sprintf(hname, "%s_%s", name, tag);
  h1d = new TH1D(hname, "Background Composition;;Events", 7, 0, 7);
  h1d->Sumw2();

  /*  h1d->GetXaxis()->FindBin("iso top");
      h1d->GetXaxis()->FindBin("iso W");
      h1d->GetXaxis()->FindBin("iso Z");
      h1d->GetXaxis()->FindBin("iso Higgs");
      h1d->GetXaxis()->FindBin("iso SUSY");
      h1d->GetXaxis()->FindBin("Diboson");
      h1d->GetXaxis()->FindBin("Charge flip");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv sign");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv top");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv W");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv Z");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv H");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv SUSY");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv Diboson");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv Brem");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv FSR");
      h1d->GetXaxis()->FindBin("Bkg PhotonConv other");
      h1d->GetXaxis()->FindBin("NonIso Bottom");
      h1d->GetXaxis()->FindBin("NonIso Charm");
      h1d->GetXaxis()->FindBin("everything else");*/

  h1d->GetXaxis()->FindBin("Iso"); // top, W, Z, Higgs, SUSY, Diboson
  h1d->GetXaxis()->FindBin("Charge flip"); // Julien ChFlip
  h1d->GetXaxis()->FindBin("Bkg PhotonConv sign"); // 
  h1d->GetXaxis()->FindBin("Bkg PhotonConv Iso"); // mother: top, W, Z, H, SUSY, Diboson
  h1d->GetXaxis()->FindBin("Bkg PhotonConv Other"); // Brem, FSR, other
  h1d->GetXaxis()->FindBin("NonIso Bottom"); // Bottom
  h1d->GetXaxis()->FindBin("NonIso Charm");  // Charm

  return;
}

void BookHistos_FS(const char* tag) {

  const char* name;
  char hname[256];
  TH1D* h1d;
  TH2D* h2d;
  //TProfile* hp;

  // N-1 Plots

  // Do N-1 plots first
  if(strstr(tag,"NJETS") != NULL ){
	name = "NJETS";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "# of jets (N-1); N_{jets} (N-1);Events", 16, -0.5, 15.5);
	h1d->Sumw2();
  }
  else if(strstr(tag,"Meff") != NULL ){
	name = "Meff";
	sprintf(hname, "%s_%s", name, tag);

	if( strstr(tag,"Rpv2L2bS") != NULL )
	  h1d = new TH1D(hname, "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 200 GeV", 6, 200, 1200+200);
	else if( strstr(tag,"Rpv2L2bH") != NULL )
	  h1d = new TH1D(hname, "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 400 GeV", 5, 400, 2000+400);
	else if( strstr(tag,"Rpc2L2bH") != NULL )
	  h1d = new TH1D(hname, "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 400 GeV", 5, 200, 1800+400);
	else if( strstr(tag,"SRRPV3b") != NULL )
	  h1d = new TH1D(hname, "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 400 GeV", 5, 200, 1800+400);
	else if( strstr(tag,"SR1b_GG") != NULL )
	  h1d = new TH1D(hname, "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 400 GeV", 6, 200, 2200+400);
	else if( strstr(tag,"SRRPV0b") != NULL )
	  h1d = new TH1D(hname, "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 400 GeV", 5, 200, 1800+400);
	else if( strstr(tag,"SRRPV2b") != NULL )
	  h1d = new TH1D(hname, "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 200 GeV", 9, 200, 1800+200);
	else 
	  h1d = new TH1D(hname, "effective mass (N-1); m_{eff}  (N-1) [GeV] ;Events / 200 GeV", 6, 200, 1200+200);

	h1d->Sumw2();
  }
  else if(strstr(tag,"NBJETS") != NULL ){
	name = "NBJETS";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "# of b-jets (N-1); N_{b-jets} (N-1);Events", 11, -0.5, 10.5);
	h1d->Sumw2();
  }
  else if(strstr(tag,"MET") != NULL ){
	name = "MET";
	sprintf(hname, "%s_%s", name, tag);

	if( strstr(tag,"Rpc2L2bS") != NULL )
	  h1d = new TH1D(hname, "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 50 GeV", 4, 50, 200+50);
	//	else if( strstr(tag,"Rpc2L2bH") != NULL )
	//	  h1d = new TH1D(hname, "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 50 GeV", 4, 50, 200+50);
	else if( strstr(tag,"SR3b2") != NULL )
	  h1d = new TH1D(hname, "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 50 GeV", 5, 50, 250+50);
	else if( strstr(tag,"SRlow") != NULL )
	  h1d = new TH1D(hname, "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 25 GeV", 7, 50, 200+25);
	else if( strstr(tag,"SR1b2") != NULL )
	  h1d = new TH1D(hname, "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 50 GeV", 5, 50, 250+50);
	else if( strstr(tag,"SR3L0b1") != NULL )
	  h1d = new TH1D(hname, "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 25 GeV", 7, 50, 200+25);
	else if( strstr(tag,"SR3L1b1") != NULL )
	  h1d = new TH1D(hname, "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 25 GeV", 7, 50, 200+25);
	else if( strstr(tag,"SR0b2") != NULL )
	  h1d = new TH1D(hname, "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 50 GeV", 5, 50, 250+50);
	else
	  h1d = new TH1D(hname, "mEt (N-1);E_{T}^{miss}  (N-1) [GeV];Events / 25 GeV", 5, 50, 150+25);	

	h1d->Sumw2();

	//----------------------------------------------------------------------
  }
  else{
	const int n_bins_jet_pt = 14;
	const Double_t jet_pt_bins[n_bins_jet_pt + 1] = { 30., 40., 50., 70., 90., 120., 155., 195., 235., 280., 330., 385., 445., 510., 580.};

	//----------------------------------------------------------------------
	// Jets

	name = "NJETS";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Number of jets (p_{T} > 25 GeV); Number of jets (p_{T} > 25 GeV);Events", 5, 1.5, 6.5);
	h1d->Sumw2();
	/*  
	name = "pt_jet1";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(jet1);First Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();
  
	name = "pt_jet2";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(jet2);Second Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();
  
	name = "pt_jet3";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(jet3);Third Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();
	if(detail){
	  name = "pt_jet4";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "pT(jet4);Fourth Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	  h1d->Sumw2();
  
	  name = "pt_jet5";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "pT(jet5);Fifth Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	  h1d->Sumw2();
  
	  name = "JVT";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "JVT;Jet JVT;Entries", 10, -0.2, 1.2);
	  h1d->Sumw2();
	}
	//----------------------------------------------------------------------
	// b-Jets
	*/
	name = "NBJETS";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "# of b-jets; N_{b-jets};Events", 11, -0.5, 10.5);
	h1d->Sumw2();
	/*
	name = "pt_bjet1";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(b-jet1);First b-Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();
  
	name = "pt_bjet2";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(b-jet2);Second b-Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();
  
	name = "pt_bjet3";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(b-jet3);Third b-Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();
	if(detail){  
	  name = "pt_bjet4";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "pT(b-jet4);Fourth b-Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	  h1d->Sumw2();
	}
	//----------------------------------------------------------------------
	// muons

	name = "mu1_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 1st muon;p_{T}(#mu1) [GeV];entries", 60, 0, 600);
	h1d->Sumw2();
	*/
	name = "mu2_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 2nd muon;p_{T}(#mu2) [GeV];entries", 40, 0, 400);
	h1d->Sumw2();
	/*
	name = "mu3_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 3rd muon;p_{T}(#mu3) [GeV];entries", 40, 0, 400);
	h1d->Sumw2();
	if(detail){
	  name = "mu1_D0";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0 of the 1st muon;d_{0}(#mu1) [mm];entries", 50, -0.1, 0.1);
	  h1d->Sumw2();
  
	  name = "mu2_D0";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0 of the 2nd muon;d_{0}(#mu2) [mm];entries", 50, -0.1, 0.1);
	  h1d->Sumw2();
  
	  name = "mu3_D0";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0 of the 3rd muon;d_{0}(#mu3) [mm];entries", 50, -0.1, 0.1);
	  h1d->Sumw2();
  
	  name = "mu1_D0sig";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0/#sigma(d0) of the 1st muon;d_{0}/#sigma(d0);entries", 50, -5, 5);
	  h1d->Sumw2();
  
	  name = "mu2_D0sig";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0/#sigma(d0) of the 2nd muon;d_{0}/#sigma(d0);entries", 50, -5, 5);
	  h1d->Sumw2();
  
	  name = "mu3_D0sig";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0/#sigma(d0) of the 3rd muon;d_{0}/#sigma(d0);entries", 50, -5, 5);
	  h1d->Sumw2();
	}
	name = "mu_eta";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "#eta of muons;#eta(#mu);entries", 25, -2.5, 2.5);
	h1d->Sumw2();
	if(detail){
	  name = "mu_phi";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "#phi of muons;#phi(#mu) [rad];entries", 30, -3.1416, 3.1416);
	  h1d->Sumw2();

	  name = "mu1_ptvarcone30";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "ptvarcone30 of 1st muon; ptvarcone30(#mu1)/p_{T}(#mu1);entries", 20, 0, 0.1);
	  h1d->Sumw2();

	  name = "mu2_ptvarcone30";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "ptvarcone30 of 2nd muon; ptvarcone30(#mu2)/p_{T}(#mu2);entries",  20, 0, 0.1);
	  h1d->Sumw2();

	  name = "mu3_ptvarcone30";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "ptvarcone30 of 3rd muon; ptvarcone30(#mu3)/p_{T}(#mu3);entries",  20, 0, 0.1);
	  h1d->Sumw2();
	}
	//----------------------------------------------------------------------
	// electrons
  
	name = "el1_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 1st electron;p_{T}(e1) [GeV];entries", 60, 0, 600);
	h1d->Sumw2();
	*/
	name = "el2_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 2nd electron;p_{T}(e2) [GeV];entries", 40, 0, 400);
	h1d->Sumw2();
	/*
	name = "el3_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 3rd electron;p_{T}(e3) [GeV];entries", 40, 0, 400);
	h1d->Sumw2();
	if(detail){
	  name = "el1_D0";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0 of the 1st electron;d_{0}(e1) [mm];entries", 50, -0.1, 0.1);
	  h1d->Sumw2();
  
	  name = "el2_D0";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0 of the 2nd electron;d_{0}(e2) [mm];entries", 50, -0.1, 0.1);
	  h1d->Sumw2();
  
	  name = "el3_D0";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0 of the 3rd electron;d_{0}(e3) [mm];entries", 50, -0.1, 0.1);
	  h1d->Sumw2();
  
	  name = "el1_D0sig";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0/#sigma(d0) of the 1st electron;d_{0}/#sigma(d0);entries", 50, -5, 5);
	  h1d->Sumw2();
  
	  name = "el2_D0sig";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0/#sigma(d0) of the 2nd electron;d_{0}/#sigma(d0);entries", 50, -5, 5);
	  h1d->Sumw2();
  
	  name = "el3_D0sig";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "d0/#sigma(d0) of the 3rd electron;d_{0}/#sigma(d0);entries", 50, -5, 5);
	  h1d->Sumw2();
	}
	name = "el_eta";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "#eta of electrons;#eta(e);entries", 25, -2.5, 2.5);
	h1d->Sumw2();
	if(detail){
	  name = "el_phi";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "#phi of electrons;#phi(e) [rad];entries", 30, -3.1416, 3.1416);
	  h1d->Sumw2();

	  name = "el1_TightLH";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "TightLH of 1st electron;TightLH;entries", 2, -0.5, 1.5);
	  h1d->Sumw2();

	  name = "el2_TightLH";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "TightLH of 2nd electron;TightLH;entries", 2, -0.5, 1.5);
	  h1d->Sumw2();

	  name = "el3_TightLH";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "TightLH of 3rd electron;TightLH;entries", 2, -0.5, 1.5);
	  h1d->Sumw2();

	  name = "el1_MediumLH";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "MediumLH of 1st electron;MediumLH;entries", 2, -0.5, 1.5);
	  h1d->Sumw2();

	  name = "el2_MediumLH";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "MediumLH of 2nd electron;MediumLH;entries", 2, -0.5, 1.5);
	  h1d->Sumw2();

	  name = "el3_MediumLH";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "MediumLH of 3rd electron;MediumLH;entries", 2, -0.5, 1.5);
	  h1d->Sumw2();

	  name = "el1_ptvarcone20";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "ptvarcone20 of 1st electron; ptvarcone20(e1)/p_{T}(e1);entries",  20, 0, 0.1);
	  h1d->Sumw2();

	  name = "el2_ptvarcone20";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "ptvarcone20 of 2nd electron; ptvarcone20(e2)/p_{T}(e2);entries",  20, 0, 0.1);
	  h1d->Sumw2();

	  name = "el3_ptvarcone20";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "ptvarcone20 of 3rd electron; ptvarcone20(e3)/p_{T}(e3);entries",  20, 0, 0.1);
	  h1d->Sumw2();

	  name = "el1_topoetcone20";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "topoetcone20 of 1st electron; topoetcone20(e1)/p_{T}(e1);entries",  20, 0, 0.1);
	  h1d->Sumw2();

	  name = "el2_topoetcone20";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "topoetcone20 of 2nd electron; topoetcone20(e2)/p_{T}(e2);entries",  20, 0, 0.1);
	  h1d->Sumw2();

	  name = "el3_topoetcone20";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "topoetcone20 of 3rd electron; topoetcone20(e3)/p_{T}(e3);entries",  20, 0, 0.1);
	  h1d->Sumw2();
	}
	//----------------------------------------------------------------------
	*/
	name = "MET";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "mEt;E_{T}^{miss} [GeV];Events / 30 GeV", 20, 0, 600);
	h1d->Sumw2();
	/*
	//----------------------------------------------------------------------

	name = "HT";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "HT;H_{T} [GeV];Events / 100 GeV", 25, 0, 2500);
	h1d->Sumw2();
	*/
	//----------------------------------------------------------------------

	name = "Meff";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "effective mass; m_{eff} [GeV];Events / 100 GeV", 30, 0, 3000);
	h1d->Sumw2();
	/*
	//----------------------------------------------------------------------

	name = "mT";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Transverse mass (leading lepton);Transverse mass (lead lepton) [GeV];Events / 50 GeV", 20, 0, 1000);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	if(detail){
	  name = "mT2";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "Transverse mass (mT2);mT2 [GeV];Events / 30 GeV", 20, 0, 600);
	  h1d->Sumw2();
	}
	//----------------------------------------------------------------------

	name = "mT_min";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Transverse mass (min);Transverse mass (min) [GeV];Events / 30 GeV", 20, 0, 600);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	if(detail){
	  name = "MZ";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "M(ll);M(ll) [GeV]; Events / 20 GeV", 40, 0, 200);
	  h1d->Sumw2();

	  //----------------------------------------------------------------------

	  name = "Mlll";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "M(lll);M(lll) [GeV]; Entries / 20 GeV", 40, 0, 200);
	  h1d->Sumw2();

	  //----------------------------------------------------------------------

	  name = "Mleps";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "M(all leps);M(leps) [GeV]; Entries / 4 GeV", 75, 0, 300);
	  h1d->Sumw2();
	}

	//----------------------------------------------------------------------

	name = "Mll";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "M(ll);M(ll) [GeV]; Entries / 4 GeV", 75, 0, 300);  
	h1d->Sumw2();                                                              


	//----------------------------------------------------------------------

	name = "Mee";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "M(ee);M(ee) [GeV]; Entries / 5 GeV", 40, 0, 200);  
	h1d->Sumw2();                                                              

	//----------------------------------------------------------------------

	name = "Mmumu";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "M(mumu);M(mumu) [GeV]; Entries / 5 GeV", 40, 0, 200);
	h1d->Sumw2();

	//----------------------------------------------------------------------
  
	name = "LEPPt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the signal leptons;p_{T}(signal leptons) [GeV]; Entries / 20 GeV", 20, 0, 400);
	h1d->Sumw2();
	//----------------------------------------------------------------------
  
	name = "LEP1Pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 1st lepton;p_{T}(l1) [GeV]; Entries / 20 GeV", 20, 0, 400);
	h1d->Sumw2();
  

	//----------------------------------------------------------------------
  
	name = "LEP2Pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 2nd lepton;p_{T}(l2) [GeV]; Entries / 20 GeV", 20, 0, 400);
	h1d->Sumw2();
  
	//----------------------------------------------------------------------
  
	name = "LEP3Pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 3rd lepton;p_{T}(l3) [GeV]; Entries / 20 GeV", 20, 0, 400);
	h1d->Sumw2();
  
	//----------------------------------------------------------------------


	name = "LEPChargeSum";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Total charge of signal leptons;Total charge (signal leptons); Events ", 10, -5, 5);
	h1d->Sumw2();
  
	//----------------------------------------------------------------------
	if(detail){
	  name = "lep_softest_pt";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "Pt of the softest lepton;p_{T}(softest lepton) [GeV]; Entries / 20GeV", 20, 0, 400);
	  h1d->Sumw2();
  
	  //----------------------------------------------------------------------

	  name = "deltaR_lep1_jet";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "deltaR_lep1_jet;deltaR_lep1_jet;entries", 50, 0, 5);
	  h1d->Sumw2();

	  //----------------------------------------------------------------------

	  name = "deltaR_lep2_jet";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "deltaR_lep2_jet;deltaR_lep2_jet;entries", 50, 0, 5);
	  h1d->Sumw2();

	  //----------------------------------------------------------------------

	  name = "deltaR_lep3_jet";
	  sprintf(hname, "%s_%s", name, tag);
	  h1d = new TH1D(hname, "deltaR_lep3_jet;deltaR_lep3_jet;entries", 50, 0, 5);
	  h1d->Sumw2();

	  //----------------------------------------------------------------------

	  name = "NJETS_MET";
	  sprintf(hname, "%s_%s", name, tag);
	  h2d = new TH2D(hname, "NJETS_MET;N_{jets};E_{T}^{miss} [GeV]", 16, -0.5, 15.5, 20, 0, 600);
	  h2d->Sumw2();

	  //----------------------------------------------------------------------

	  name = "NJETS_NBJETS";
	  sprintf(hname, "%s_%s", name, tag);
	  h2d = new TH2D(hname, "NJETS_NBJETS;N_{jets};N_{b-jets}", 16, -0.5, 15.5, 11, -0.5, 10.5);
	  h2d->Sumw2();

	  //----------------------------------------------------------------------

	  name = "NJETS_Meff";
	  sprintf(hname, "%s_%s", name, tag);
	  h2d = new TH2D(hname, "NJETS_Meff;N_{jets};m_{eff} [GeV]", 16, -0.5, 15.5, 30, 0, 3000);
	  h2d->Sumw2();

	  //----------------------------------------------------------------------
  
	  name = "NBJETS_MET";
	  sprintf(hname, "%s_%s", name, tag);
	  h2d = new TH2D(hname, "NBJETS_MET;N_{b-jets};E_{T}^{miss} [GeV]", 11, -0.5, 10.5, 20, 0, 600);
	  h2d->Sumw2();

	  //----------------------------------------------------------------------
  
	  name = "NBJETS_Meff";
	  sprintf(hname, "%s_%s", name, tag);
	  h2d = new TH2D(hname, "NBJETS_Meff;N_{b-jets};m_{eff} [GeV]", 11, -0.5, 10.5, 30, 0, 3000);
	  h2d->Sumw2();

	  //----------------------------------------------------------------------
  
	  name = "MET_Meff";
	  sprintf(hname, "%s_%s", name, tag);
	  h2d = new TH2D(hname, "MET_Meff;E_{T}^{miss} [GeV];m_{eff} [GeV]", 20, 0, 600, 30, 0, 3000);
	  h2d->Sumw2();
	  }*/
  }

  return;
}

// Control/Signal Regions
//-----------------------------------------------------------------------
void FillHistos_Regions(const char* ftag, const char* tag, myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet) {

  if (lep->num_leptons < 2 || lep->pT[0] < LeptPt10 || lep->pT[1] < LeptPt10) {
    std::cerr << "ERROR FillHistos_Regions: incorrect usage of cuts!!!!";
    return;
  }

  char my_tag[256];
  char hist_name[256];

  if (strlen(tag) > 0)
    sprintf(my_tag, "_%s", tag);
  else
    sprintf(my_tag, "%s", tag);

  int num20GeVLept = 0;
  for (int lepi = 0; lepi < lep->num_leptons; lepi++)
    if(lep->pT[lepi] > LeptPt){
      num20GeVLept++;
    }

  int numLept = 0;
  for (int lepi = 0; lepi < lep->num_leptons; lepi++)
    {
      numLept++;
    }

  bool el_eta137=true;
  //  for (int lepi = 0; lepi < lep->num_leptons; lepi++)
  for (int lepi = 0; lepi < 2; lepi++)
    if(lep->is_electron[lepi])
      {
		el_eta137 &= fabs(lep->eta[lepi])<1.37;
      }
	
  int count_Ncharge = 0;
  for (int lepi = 0; lepi < lep->num_leptons; lepi++)
    if(lep->charge[lepi]<0)
      count_Ncharge++;

  // calculate deltaR lep, jet:
  double deltaR_lep_jet[2] = { 5., 5.};
  double  dR = 10.;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
    if(jet->pT[jeti]>25000)
	  if(lep->num_leptons >1)
		for (int lepj = 0; lepj < 2; lepj++) {
		  dR = DeltaR(jet->eta[jeti], jet->phi[jeti], lep->eta[lepj], lep->phi[lepj]);
		  if (dR < deltaR_lep_jet[lepj])
			deltaR_lep_jet[lepj] = dR;
		}

  // calculate deltaR lep, lep:
  double deltaR_lep_lep = 5.;
  double  dRl = 10.;
  for (int lepi = 0; lepi < lep->num_leptons; lepi++)
	for (int lepj = lepi+1; lepj < lep->num_leptons; lepj++) {
	  dRl = DeltaR(lep->eta[lepi], lep->phi[lepi], lep->eta[lepj], lep->phi[lepj]);
	  if (dRl < deltaR_lep_lep)
		deltaR_lep_lep = dRl;
	}

  //effective mass
  //-----------------------------------------------------------------------

  double meff = 0;
  double ht = 0;
  double sum_bjet_pt = 0;	
  double sum_jet_pt = 0;	
  double sum_lep_pt = 0;	

  // leptons pt
  for (int i = 0; i < lep->num_leptons; i++) {
    meff += lep->pT[i];
	sum_lep_pt += lep->pT[i];
  }

  // jets pt
  for (int i = 0; i < jet->num_jets; i++) {
    meff += jet->pT[i];
	sum_jet_pt += jet->pT[i];
  } 

  // b-jets pt
  for (int i = 0; i < bjet->num_jets; i++) {
	sum_bjet_pt += bjet->pT[i];
  }

  ht = meff;

  if (ht) {}

  //miss-Et variables
  float mis_Ex = evt->Etmiss_TST_Etx;
  float mis_Ey = evt->Etmiss_TST_Ety;
  float met = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);
  meff += met;

 
  //  int n_jets  = jet->num_jets;
  int n_bjets = bjet->num_jets;
  //  int n_leps  = lep->num_leptons;
  
  int n_jets_50 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
    if(jet->pT[jeti]>50000)
      n_jets_50++;

  int n_jets_25 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
    if(jet->pT[jeti]>25000)
      n_jets_25++;

  int n_jets_30 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
    if(jet->pT[jeti]>30000)
      n_jets_30++;

  int n_jets_35 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
    if(jet->pT[jeti]>35000)
      n_jets_35++;

  int n_jets_40 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
    if(jet->pT[jeti]>40000)
      n_jets_40++;
  
  bool incl = true;
  if(incl){
    sprintf(hist_name, "Incl%s", my_tag);
    FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  } 

  bool PRE = (n_jets_40 >= 2 && met > 50000 ); // Same as Julien
  if(PRE){
    sprintf(hist_name, "PRE%s", my_tag);
    FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  } 
  
  bool CR3b = (n_bjets >= 3 && n_jets_40 >= 2 && met > 50000 ); // Same as Julien
  if(CR3b){
    sprintf(hist_name, "CR3b%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  } 
  
  // signal regions
  
  bool is_SR = false;
  bool is_SR_veto = false;
  
  bool SR3L0b1 = (num20GeVLept >= 2 && lep->has_ss && numLept >= 3 && n_bjets == 0 && n_jets_40 >= 4 && met > 200000  && meff > 600000 );
  if(SR3L0b1){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR3L0b1%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR3L0b2 = (num20GeVLept >= 2 && lep->has_ss && numLept >= 3 && n_bjets == 0 && n_jets_40 >= 4 && met > 200000 && meff > 1600000);
  if(SR3L0b2){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR3L0b2%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR3L1b1 = (num20GeVLept >= 2 && lep->has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_40 >= 4 && met > 200000  && meff > 600000 );
  if(SR3L1b1){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR3L1b1%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR3L1b2 = (num20GeVLept >= 2 && lep->has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_40 >= 4 && met > 200000 && meff > 1600000);
  if(SR3L1b2){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR3L1b2%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR0b1 = (num20GeVLept >= 2 && lep->has_ss && n_bjets == 0 && n_jets_25 >= 6  && met > 150000 && met/meff > 0.25);
  if(SR0b1){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR0b1%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR0b2 = (num20GeVLept >= 2 && lep->has_ss && n_bjets == 0 && n_jets_40 >= 6  && met > 250000 && meff > 900000 );
  if(SR0b2){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR0b2%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR1b1 = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_25 >= 6  && met > 0 && meff > 600000 && met/meff > 0.25 );
  if(SR1b1){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR1b1%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR1b2 = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_25 >= 6  && met > 250000 && meff > 0 && met/meff > 0.2 );
  if(SR1b2){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR1b2%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR3b1 = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 3 && n_jets_25 >= 6 && met > 150000 && meff > 0 && met/meff > 0.2);
  if(SR3b1){
	//	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR3b1%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR3b2 = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 3 && n_jets_25 >= 6 && met > 250000 && meff > 1200000 && met/meff > 0);
  if(SR3b2){
	//	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR3b2%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SRlow = (lep->has_ss && 20000 < lep->pT[0] &&  lep->pT[0] < 100000 && 10000 < lep->pT[1]  &&   n_bjets >= 2 && n_jets_25 >= 6 && met > 200000 && meff > 600000 && met/meff > 0.25);
  if(SRlow){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SRlow%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SRhigh = (lep->has_ss && 20000 < lep->pT[0] &&  lep->pT[0] < 100000 && 10000 < lep->pT[1] &&  n_bjets >= 1 && n_jets_25 >= 6 && met > 100000 && meff > 0 && met/meff > 0.3);
  if(SRhigh){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SRhigh%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR1b_3LSS = (num20GeVLept >= 2 && lep->has_ss && lep->has_3lss && n_bjets >= 1 && !lep->has_Z_SS_ee);
  if(SR1b_3LSS){
	is_SR = true;  //is_SR_veto = true;
	sprintf(hist_name, "SR1b_3LSS%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  //  bool SR1b_DD_low = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_50 >= 4  && met > 0 && meff > 1200000 && count_Ncharge >= 2); 
  bool SR1b_DD_low = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_50 >= 4  && met > 0 && meff > 1200000 ); 
  if(SR1b_DD_low){
	is_SR_veto = true;
	if(count_Ncharge >= 2){
	  is_SR = true; 
	  sprintf(hist_name, "SR1b_DD_low%s", my_tag);
	  // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	}
  }

  //  bool SR1b_DD_high =  (lep->has_ss && n_bjets >= 1 && n_jets_50 >= 4  && met > 0 && meff > 1800000 && count_Ncharge >= 2);
  bool SR1b_DD_high = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_50 >= 4  && met > 0 && meff > 1800000 );
  if(SR1b_DD_high){
	is_SR_veto = true;
	if( count_Ncharge >= 2 ){
	  is_SR = true;
	  sprintf(hist_name, "SR1b_DD_high%s", my_tag);
	  // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	}
  }

  //  bool SR3b_DD = (lep->has_ss && n_bjets >= 3 && n_jets_50 >= 3  && met > 0 && meff > 1200000 && count_Ncharge >= 2); 
  bool SR3b_DD = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 3 && n_jets_50 >= 3  && met > 0 && meff > 1200000 ); 
  if(SR3b_DD){
	//	is_SR_veto = true;
	if(count_Ncharge >= 2){
	  //	  is_SR = true; 
	  sprintf(hist_name, "SR3b_DD%s", my_tag);
	  // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	}
  }

  bool SR1b_GG = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_50 >= 6  && met > 0 && meff > 2200000);
  if(SR1b_GG){
	is_SR = true; is_SR_veto = true;
	sprintf(hist_name, "SR1b_GG%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  //  bool SRRPV0b =  (lep->has_ss && numLept == 2 && n_bjets == 0 && n_jets_40 >= 6  && meff > 1500000 && !lep->has_Z_OS );
  bool SRRPV0b = (num20GeVLept >= 2 && lep->has_ss && numLept == 2 && n_bjets == 0 && n_jets_40 >= 6  && meff > 1800000 );
  if(SRRPV0b){
	is_SR_veto = true;
	if( !lep->has_Z_SS_ee ){
	  is_SR = true; 
	  sprintf(hist_name, "SRRPV0b%s", my_tag);
	  // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	}
  }

  //  bool SRRPV3b =  (lep->has_ss && n_bjets >= 3 && n_jets_40 >= 6  && meff > 1500000 && !lep->has_Z_OS );
  bool SRRPV3b = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 3 && n_jets_40 >= 6  && meff > 1800000);
  if(SRRPV3b){
	//	is_SR_veto = true;
	if(  !lep->has_Z_SS_ee ){ 
	  //	  is_SR = true; 
	  sprintf(hist_name, "SRRPV3b%s", my_tag);
	  // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	}
  }

  bool Rpc2L2bS = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 2 && n_jets_25 >= 6 && met > 200000 && meff > 600000 && met/meff > 0.25);
	  if(Rpc2L2bS){
	is_SR = true; is_SR_veto = true;
 sprintf(hist_name, "Rpc2L2bS%s", my_tag);
 // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	  }

	  bool Rpc2L2bH = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 2 && n_jets_25 >= 6 && met > 0 && meff > 1800000 && met/meff > 0.15);
	  if(Rpc2L2bH){
	is_SR = true; is_SR_veto = true;
 sprintf(hist_name, "Rpc2L2bH%s", my_tag);
 // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	  }

	  bool Rpv2L2bS = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 2 && n_jets_50 >= 3 && meff > 1200000);
	  if(Rpv2L2bS){
		is_SR_veto = true;
		if(count_Ncharge >= 2){
		   sprintf(hist_name, "Rpv2L2bS%s", my_tag);
		   // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
		}
	  }

	  bool Rpv2L2bH = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 2 && n_jets_40 >= 6 && meff > 2000000 );
	  if(Rpv2L2bH){
		is_SR_veto = true;
		if(  !lep->has_Z_SS_ee ){ 
		   sprintf(hist_name, "Rpv2L2bH%s", my_tag);
		   // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
		}
	  }

auto meff_corrected = [&](float met_threshold){ return meff+std::max(met_threshold-met,0.f); };
auto meff_ratioCorrected = [&](float mom_threshold,float met_threshold){ return mom_threshold*meff*(met>met_threshold?1.:met/met_threshold); };

  // N-1 

  bool SR3b1mMET = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 3 && n_jets_25 >= 6  && met > 50000 &&
					met > meff_ratioCorrected(0.2,150000.) && (SR3b1 || meff < 1200000)  );
  if(SR3b1mMET){
    sprintf(hist_name, "SR3b1mMET%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR3b2mMET = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 3 && n_jets_25 >= 6  && meff_corrected(250000) > 1200000 && met > 50000);
  if(SR3b2mMET){
    sprintf(hist_name, "SR3b2mMET%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SRlowmMET = (lep->has_ss && 20000 < lep->pT[0] &&  lep->pT[0] < 100000 && 10000 < lep->pT[1] && n_bjets >= 2 && n_jets_25 >= 6 && meff > 600000 && met > 50000 && met>meff_ratioCorrected(0.25,200000) && (SRlow || meff < 1000000.)  );
  if(SRlowmMET){
    sprintf(hist_name, "SRlowmMET%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR1b2mMET = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_25 >= 6   && met > 50000 && 
					met > meff_ratioCorrected(0.2,250000) && ( SR1b2 || meff < 1200000.) );
  if(SR1b2mMET){
    sprintf(hist_name, "SR1b2mMET%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR0b1mMET = (num20GeVLept >= 2 && lep->has_ss && n_bjets == 0 && n_jets_25 >= 6   && met > 50000 && 
					met > meff_ratioCorrected(0.25,150000) && (SR0b1 || meff < 900000));
  if(SR0b1mMET){
    sprintf(hist_name, "SR0b1mMET%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR0b2mMET = (num20GeVLept >= 2 && lep->has_ss && n_bjets == 0 && n_jets_40 >= 6   && meff_corrected(250000) > 900000 
					&& met > 50000);
  if(SR0b2mMET){
    sprintf(hist_name, "SR0b2mMET%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR3L0b1mMET = (num20GeVLept >= 2 && lep->has_ss && numLept >= 3 && n_bjets == 0 && n_jets_40 >= 4  
					  && meff_corrected(200000) > 600000 && met > 50000);
 if(SR3L0b1mMET){
   sprintf(hist_name, "SR3L0b1mMET%s", my_tag);
   // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
 }

 bool SR3L1b1mMET = (num20GeVLept >= 2 && lep->has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_40 >= 4  
					 && meff_corrected(200000) > 600000 && met > 50000);
  if(SR3L1b1mMET){
    sprintf(hist_name, "SR3L1b1mMET%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR1b_GGmMeff = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_50 >= 6 && meff > 200000);
  if(SR1b_GGmMeff){
    sprintf(hist_name, "SR1b_GGmMeff%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SRRPV0bmMeff = (num20GeVLept >= 2 && lep->has_ss && numLept == 2 && n_bjets == 0 && n_jets_40 >= 6  && meff > 200000 
					   &&  !lep->has_Z_SS_ee);
  if(SRRPV0bmMeff){
	sprintf(hist_name, "SRRPV0bmMeff%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SRRPV3bmMeff = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 3 && n_jets_40 >= 6 && meff > 200000 &&  !lep->has_Z_SS_ee );
  if(SRRPV3bmMeff){
    sprintf(hist_name, "SRRPV3bmMeff%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SRRPV2bmMeff = (num20GeVLept >= 2 && lep->has_ss && numLept == 2 && n_bjets >= 2 && n_jets_40 >= 6  && meff > 200000 
					   && !lep->has_Z_OS);
  if(SRRPV2bmMeff){
	sprintf(hist_name, "SRRPV2bmMeff%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR3b_DDmMeff = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 3 && n_jets_50 >= 3  && meff > 200000 && count_Ncharge >= 2); 
  if(SR3b_DDmMeff){
    sprintf(hist_name, "SR3b_DDmMeff%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR1b_DD_lowmMeff = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_50 >= 4  && meff > 200000  && count_Ncharge >= 2); 
  if(SR1b_DD_lowmMeff){
    sprintf(hist_name, "SR1b_DD_lowmMeff%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

 bool SR3L0b2mMET = (num20GeVLept >= 2 && lep->has_ss && numLept >= 3 && n_bjets == 0 && n_jets_40 >= 4  && meff > 1600000);
 if(SR3L0b2mMET){
   sprintf(hist_name, "SR3L0b2mMET%s", my_tag);
   // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
 }


  bool SR3L1b2mMET = (num20GeVLept >= 2 && lep->has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_40 >= 4  && meff > 1600000);
  if(SR3L1b2mMET){
    sprintf(hist_name, "SR3L1b2mMET%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool SR1b1mMeff =   (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 1 && n_jets_25 >= 6   && met/meff > 0.25 );
  if(SR1b1mMeff){
    sprintf(hist_name, "SR1b1mMeff%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }


  bool SRhighmMET = (lep->has_ss && 20000 < lep->pT[0] &&  lep->pT[0] < 100000 && 10000 < lep->pT[1] &&  n_bjets >= 1 && n_jets_25 >= 6 && meff > 0 && met/meff > 0.3);
  if(SRhighmMET){
    sprintf(hist_name, "SRhighmMET%s", my_tag);
    // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool Rpc2L2bSmMET = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 2 && n_jets_25 >= 6 && meff > 600000 && 
					   met > 50000 && met > meff_ratioCorrected(0.25,200000.)  );
  if(Rpc2L2bSmMET){
	sprintf(hist_name, "Rpc2L2bSmMET%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }
  
  bool Rpc2L2bHmMeff = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 2 && n_jets_25 >= 6 && meff > 700000 && met/meff > 0.15);
  if(Rpc2L2bHmMeff){
	sprintf(hist_name, "Rpc2L2bHmMeff%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool Rpv2L2bSmMeff = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 2 && n_jets_50 >= 3 );
  if(Rpv2L2bSmMeff){
	if(count_Ncharge >= 2){
	  sprintf(hist_name, "Rpv2L2bSmMeff%s", my_tag);
	  // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	}
  }
  
  bool Rpv2L2bHmMeff = (num20GeVLept >= 2 && lep->has_ss && n_bjets >= 2 && n_jets_40 >= 6 );
  if(Rpv2L2bHmMeff){
	if(  !lep->has_Z_SS_ee ){ 
	  sprintf(hist_name, "Rpv2L2bHmMeff%s", my_tag);
	  // * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	}
  }


  // Validation Regions
  bool is_VR = false;

  //  bool VRWW = (num20GeVLept >= 2 &&  lep->has_ss && numLept == 2 && lep->num_leptons_baseline == 2 && n_bjets == 0  && n_jets_25 >= 2 && met > 50000 && meff > 500000 && dijet_mass(jet) > 500000 && jet->pT[1] > 40000 && lep->pT[1] > 25000 && transverse_mass(evt, lep) > 40000 && (!lep->has_Z || lep->has_em || lep->has_mm) && el_eta137 && !is_SR );
  bool VRWW = (num20GeVLept >= 2 &&  lep->has_ss && numLept == 2 && lep->num_leptons_baseline ==2 && n_bjets == 0  && n_jets_50 >= 2 && met > 55000 && meff > 650000 && lep->pT[1] > 30000 
			   && (!lep->has_Z || lep->has_em || lep->has_mm) && deltaR_lep_lep > 1.3 && deltaR_lep_jet[0] > 0.7 && deltaR_lep_jet[1] > 0.7 && !is_SR_veto );
  if(VRWW){
	is_VR = true;
	sprintf(hist_name, "VRWW%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }
	
  //  bool VRWZ = ( lep->has_ss && numLept == 3 && lep->num_leptons_baseline == 3 && n_bjets == 0 && n_jets_25 >= 4 && met > 20000 && meff > 300000 && trilepton_mass_lead(evt, lep) > 100000 && !is_SR );
  bool VRWZ4j = ( num20GeVLept >= 2 && lep->has_ss && numLept == 3  && lep->num_leptons_baseline == 3 && n_bjets == 0 && n_jets_25 >= 4 && meff > 450000 && met/sum_lep_pt < 0.7 && !is_SR_veto );
  if(VRWZ4j){
	is_VR = true;
	sprintf(hist_name, "VRWZ4j%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  bool VRWZ5j = ( num20GeVLept >= 2 && lep->has_ss && numLept == 3  && lep->num_leptons_baseline == 3 && n_bjets == 0 && n_jets_25 >= 5 && meff > 450000 && met/sum_lep_pt < 0.7 && !is_SR_veto );
  if(VRWZ5j){
	is_VR = true;
	sprintf(hist_name, "VRWZ5j%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  //  bool VRttW = (lep->has_ss && numLept == 2 && n_bjets >= 1 && ((n_jets_25 >= 4 && lep->has_em) || (n_jets_25 >= 3 && lep->has_mm)) && met > 50000 && meff > 550000 && lep->pT[1] > 30000 && !lep->has_ee && el_eta137  && !is_SR );
  bool VRttW = (num20GeVLept >= 2 && lep->has_ss && numLept == 2  && lep->num_leptons_baseline ==2 && n_bjets >= 1 && ((n_jets_40 >= 4 && (lep->has_ee || lep->has_em)) || (n_jets_25 >= 3 && lep->has_mm)) && met > 45000 && meff > 550000 && lep->pT[1] > 40000 && sum_bjet_pt / sum_jet_pt > 0.25  && !is_SR_veto );
  if(VRttW){
	is_VR = true;
	sprintf(hist_name, "VRttW%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }
	
  //  bool VRttZ = (lep->has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_25 >= 3 && met > 20000 && meff > 0 && lep->pT[1] > 25000 && lep->has_Z_OS && !is_SR );
  bool VRttZ = (num20GeVLept >= 2 && lep->has_ss && numLept >= 3 && n_bjets >= 1 && n_jets_35 >= 3 && meff > 450000 &&  lep->has_Z_OS && !is_SR_veto );
  if(VRttZ){
	is_VR = true;
	sprintf(hist_name, "VRttZ%s", my_tag);
	// * FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
  }

  if(is_VR){}

  // Control Regions
  //  if(/*!is_SR  &&*/ met > 40000. && n_jets_25 >= 2){
  
  if(lep->has_ss && !is_SR_veto  && n_jets_40 >= 2 && met > 50000){
	if(n_bjets == 0){
	  sprintf(hist_name, "CR0b%s", my_tag);
	  FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	}
	else if(n_bjets >= 1){
	  sprintf(hist_name, "CR1b%s", my_tag);
	  FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);
	}
  }
  
  return;
}
  
// Channel separation into ee,em,mm
//-----------------------------------------------------------------------
void FillHistos_Channels(const char* ftag, const char* tag, myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet) {

  if (lep->num_leptons < 2 || lep->pT[0] < LeptPt10 || lep->pT[1] < LeptPt10) {
	std::cerr << "ERROR FillHistos_Channels: incorrect usage of cuts!!!!";
	return;
  }

  char hist_name[256];
  
  sprintf(hist_name, "comb_%s", tag);
  FillHistos_Composition(ftag, hist_name, evt, lep, jet, bjet);
  
  if(lep->has_ss){
	if(lep->has_ee){
	  sprintf(hist_name, "ee_%s", tag);
	  FillHistos_Composition(ftag, hist_name, evt, lep, jet, bjet);
	}
	else if (lep->has_em) {
	  sprintf(hist_name, "em_%s", tag);
	  FillHistos_Composition(ftag, hist_name, evt, lep, jet, bjet);
	}
	else if (lep->has_mm){
	  sprintf(hist_name, "mm_%s", tag);
	  FillHistos_Composition(ftag, hist_name, evt, lep, jet, bjet);
	}
	else 
	  cout << "ERROR: Undertermined channel" << endl;
  }/*
  else if ( lep->has_os_ee ){
	sprintf(hist_name, "ee_%s", tag);
	FillHistos_Composition(ftag, hist_name, evt, lep, jet, bjet);
  }
  else if ( lep->has_os_em ){
	sprintf(hist_name, "em_%s", tag);
	FillHistos_Composition(ftag, hist_name, evt, lep, jet, bjet);
  }
  else if ( lep->has_os_mm ){
	sprintf(hist_name, "mm_%s", tag);
	FillHistos_Composition(ftag, hist_name, evt, lep, jet, bjet);
  }
  else 
	cout << "ERROR: Undertermined channel" << endl;




  if(lep->num_leptons >= 3){
	sprintf(hist_name, "3l_%s", tag);
	FillHistos_Composition(ftag, hist_name, evt, lep, jet, bjet);
  }
  */
  return;
}

// Composition of the background: fakes, charge flip, and real
//-----------------------------------------------------------------------
void FillHistos_Composition(const char* ftag, const char* tag, myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet) {

  //  cout <<"fill composition" << endl;
  if (lep->num_leptons < 2 || lep->pT[0] < LeptPt10 || lep->pT[1] < LeptPt10) {
	std::cerr << "ERROR FillHistos_Composition: incorrect usage of cuts!!!!";
	return;
  }

  char hist_name[256];

  if(evt->isMC){
	sprintf(hist_name, "%s_mc_%s", ftag, tag);
	FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	//	FillHistos_Comp_Variables(hist_name, evt, lep);

	if (evt->extraB>=1) {
	  sprintf(hist_name, "%s_extraB_%s", ftag, tag);
	  //	  FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	}
	else if (evt->extraC>=1) {
	  sprintf(hist_name, "%s_extraC_%s", ftag, tag);
	  //	  FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	}
	else { 
	  sprintf(hist_name, "%s_extraNone_%s", ftag, tag);
	  //	  FillHistos_Variables(hist_name, evt, lep, jet, bjet);

	}	  

	  
	int index_realb = -1;
	int index_fakeb = -1;	  

	for (int jeti = 0; jeti < bjet->num_jets; jeti++)
	  if(!bjet->is_btype_jet[jeti] )
		{
		  index_fakeb = jeti;
		  break;
		}

	if (index_fakeb >= 0) {
	  sprintf(hist_name, "%s_fakeb_%s", ftag, tag);
	  //	  FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	}
	else {
	  sprintf(hist_name, "%s_realb_%s", ftag, tag);
	  //	  FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	}

	//			if(detail) {	
	int index_fake_HF = -1;
	int index_fake_LF = -1;
	int index_chmisid = -1;
	
	int num_lept = 0;
	for (int i = 0; i < lep->num_leptons /*&& num_lept < 3*/; i++) {
	  num_lept++;
	  if (lep->is_fake_HF[i]) {
		index_fake_HF = i;
		break;
	  }
	  else if (lep->is_fake_LF[i]){
		index_fake_LF = i;
		break;
	  }
	}

	num_lept = 0;
	for (int i = 0; i < lep->num_leptons /*&& num_lept < 3*/; i++) {
	  num_lept++;
	  if (lep->is_chmisid[i]) {
		index_chmisid = i;
		break;
	  }
	}

	/*
	if(evt->EventNumber == 35152){
	for (int i = 0; i < lep->num_leptons ; i++) {
	  std::cout << "is_fake_HF=" << lep->is_fake_HF[i] << ", is_fake_LF=" << lep->is_fake_LF[i] << ", is_chmisid=" << lep->is_chmisid[i] << std::endl;
	}
	for (int i = 0; i < lep->num_leptons ; i++) {
	  if(lep->is_electron[i])
		std::cout << "el in event " << evt->EventNumber << " -> pT=" << lep->pT[i] << ", El_truthType: " <<  evt->El_truthType[lep->index[i]] << ", El_truthOrigin: " << evt->El_truthOrigin[lep->index[i]] << ", index_fake_HF= " <<  index_fake_HF << ", index_fake_LF= " << index_fake_LF << ", index_chmisid= " << index_chmisid << std::endl;	
	  
	  if(!lep->is_electron[i])
		std::cout << "mu in event " << evt->EventNumber << " -> pT=" << lep->pT[i] << ", Mu_type: " <<  evt->Mu_type[lep->index[i]] << ", Mu_origin: " << evt->Mu_origin[lep->index[i]] << ", index_fake_HF= " <<  index_fake_HF << ", index_fake_LF= " << index_fake_LF << ", index_chmisid= " << index_chmisid << std::endl;	
	}
	}*/

	// Only classify Fake/Charge flip processes that do not give you SS/3L
	bool choosePrompt = (evt->ChannelNumber == 410155 || evt->ChannelNumber == 410218 || evt->ChannelNumber == 410219 || evt->ChannelNumber == 410220 || evt->ChannelNumber == 361069 || evt->ChannelNumber == 361070 || evt->ChannelNumber == 363490 || evt->ChannelNumber == 361072 || evt->ChannelNumber == 361073 || evt->ChannelNumber == 363491 || evt->ChannelNumber == 361071 || evt->ChannelNumber == 343365 || evt->ChannelNumber == 343366 || evt->ChannelNumber == 343367 || evt->ChannelNumber == 342284 || evt->ChannelNumber == 342285 || evt->ChannelNumber == 410080 || evt->ChannelNumber == 304014 || evt->ChannelNumber == 410050 || evt->ChannelNumber == 410081 || evt->ChannelNumber == 361620 || evt->ChannelNumber == 361621 || evt->ChannelNumber == 361622 || evt->ChannelNumber == 361623 || evt->ChannelNumber == 361624 || evt->ChannelNumber == 361625 || evt->ChannelNumber == 361626 || evt->ChannelNumber == 361627 || evt->ChannelNumber == 410215 || evt->ChannelNumber == 407321);
	bool choosePrompt_3LSS = ( evt->ChannelNumber == 343365 || evt->ChannelNumber == 343366 || evt->ChannelNumber == 343367  || evt->ChannelNumber == 361623 || evt->ChannelNumber == 361624 || evt->ChannelNumber == 361625 || evt->ChannelNumber == 361626 || evt->ChannelNumber == 361627 || evt->ChannelNumber == 410081 || evt->ChannelNumber == 407321);
	bool is_3LSS = ( strstr(tag, "SR1b_3LSS") != NULL );

	if(choosePrompt && !is_3LSS){
	  sprintf(hist_name, "real_%s", tag); // real
	  FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	  //	  FillHistos_Comp_Variables(hist_name, evt, lep);
	  
	  sprintf(hist_name, "%s_prompt_%s", ftag, tag); // real
	  FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	} else 
	  {
	if (index_fake_HF >= 0) {
	  if (lep->is_electron[index_fake_HF]) {
		sprintf(hist_name, "fake_HF_e_%s", tag);
		FillHistos_Variables(hist_name, evt, lep, jet, bjet);
		//		FillHistos_Comp_Variables(hist_name, evt, lep);
	  }
	  else {
		sprintf(hist_name, "fake_HF_m_%s", tag);
		FillHistos_Variables(hist_name, evt, lep, jet, bjet);
		//		FillHistos_Comp_Variables(hist_name, evt, lep);
	  }
	}
	else if (index_fake_LF >= 0){
	  if (lep->is_electron[index_fake_LF]) {
		sprintf(hist_name, "fake_LF_e_%s", tag);
		FillHistos_Variables(hist_name, evt, lep, jet, bjet);
		//		FillHistos_Comp_Variables(hist_name, evt, lep);
	  }
	  else {
		sprintf(hist_name, "fake_LF_m_%s", tag);
		FillHistos_Variables(hist_name, evt, lep, jet, bjet); 
		//		FillHistos_Comp_Variables(hist_name, evt, lep);
	  }
	}
	else if(index_chmisid >= 0){
	  sprintf(hist_name, "chmisid_%s", tag);
	  FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	  //	  FillHistos_Comp_Variables(hist_name, evt, lep);
	}	
	else {
	  bool iso = true;
	  for (int i = 0; i < lep->num_leptons /*&& num_lept < 3*/; i++) {

		if(lep->is_electron[i])
		  iso &= ( evt->El_truthType[lep->index[i]] == 2 || (evt->El_truthOrigin[lep->index[i]] == 5 && fabs(evt->El_firstEgMotherPdgId[lep->index[i]]) == 11 ));
		else
		  iso &= ( evt->Mu_type[lep->index[i]] == 6 );

		if(!iso ){
		  std::cout << "Major screw up in event " << evt->EventNumber << std::endl;
		  if(lep->is_electron[i])
			std::cout << "el in event " << evt->EventNumber << " -> pT=" << lep->pT[i] << ", El_truthType: " <<  evt->El_truthType[lep->index[i]] << ", El_truthOrigin: " << evt->El_truthOrigin[lep->index[i]] << ", index_fake_HF= " <<  index_fake_HF << ", index_fake_LF= " << index_fake_LF << ", index_chmisid= " << index_chmisid << std::endl;	

		  if(!lep->is_electron[i])
			std::cout << "mu in event " << evt->EventNumber << " -> pT=" << lep->pT[i] << ", Mu_type: " <<  evt->Mu_type[lep->index[i]] << ", Mu_origin: " << evt->Mu_origin[lep->index[i]] << ", index_fake_HF= " <<  index_fake_HF << ", index_fake_LF= " << index_fake_LF << ", index_chmisid= " << index_chmisid << std::endl;	
		}
	  }

	  /*	  if( strstr(tag, "SR1b_3LSS") != NULL )
		{
		  std::cout << "\nEventNumber=" << evt->EventNumber << std::endl;
		  for (int i = 0; i < lep->num_leptons; i++) {
			if(lep->is_electron[i])
			  std::cout <<  "el" << i << " T/O/PdgId/Charge=" << evt->El_truthType[lep->index[i]] << "/" << evt->El_truthOrigin[lep->index[i]] << "/" << evt->El_firstEgMotherPdgId[lep->index[i]]  << "/" << lep->charge[i] << std::endl;
			else 
			  std::cout <<  "mu" << i << " T/O/Charge=" << evt->Mu_type[lep->index[i]] << "/" << evt->Mu_origin[lep->index[i]] << "/" << lep->charge[i] << std::endl;
			std::cout <<  "lep" << i << " HF/LF/MisId=" << lep->is_fake_HF[i] << "/" << lep->is_fake_LF[i] << "/" << lep->is_chmisid[i] << std::endl;
		  }
		  }*/

	  if((!choosePrompt && !is_3LSS) || (choosePrompt_3LSS && is_3LSS) ){
		sprintf(hist_name, "real_%s", tag); // real
		FillHistos_Variables(hist_name, evt, lep, jet, bjet);
		//		FillHistos_Comp_Variables(hist_name, evt, lep);
	  
		sprintf(hist_name, "%s_prompt_%s", ftag, tag); // real
		FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	  }
	}
	  }
	//			}
  } else {
	//	if(detail){
	sprintf(hist_name, "data_%s", tag);
	FillHistos_Variables(hist_name, evt, lep, jet, bjet);
	//	}
	
  }
  
  return;
}

// Fill the kinematic variables
//-----------------------------------------------------------------------
void FillHistos_Comp_Variables(const char* tag, myevt *evt, my_leptons *lep) {

  if (lep->num_leptons < 2 || lep->pT[0] < LeptPt10 || lep->pT[1] < LeptPt10) {
	std::cerr << "ERROR FillHistos_Comp_Variables: incorrect usage of cuts!!!!";
	return;
  }

  double count=0.1;	 
  char hist_name[256];
  int pt_thresh[4] = {10, 15, 20, 30};

  for(int pti = 0; pti < 4; pti++){
	for (int lepi = 0; lepi < lep->num_leptons; lepi++)
	  if(lep->pT[lepi] > pt_thresh[pti]*1000)
		{

		  if(lep->is_electron[lepi]){
			sprintf(hist_name, "composition_el_pt%d", pt_thresh[pti]);
	
			count=0.1;	 
			/*
			  if( evt->El_truthType[lep->index[lepi]]==2 &&  evt->El_truthOrigin[lep->index[lepi]]==10)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==2 &&  evt->El_truthOrigin[lep->index[lepi]]==12)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==2 &&  evt->El_truthOrigin[lep->index[lepi]]==13)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==2 && evt->El_truthOrigin[lep->index[lepi]]==14)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==2 &&  evt->El_truthOrigin[lep->index[lepi]]==22)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==2 &&  evt->El_truthOrigin[lep->index[lepi]]==43)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && ( evt->El_chFlip[lep->index[lepi]]==2 ||  evt->El_chFlip[lep->index[lepi]]==4 ||  evt->El_chFlip[lep->index[lepi]]==7 ))
			  fillHist(hist_name, tag, count, evt->EventWeight); 	  
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && fabs(evt->El_bkgMotherPdgId[lep->index[lepi]])==11 && evt->El_bkgMotherPdgId[lep->index[lepi]]*lep->charge[lepi]<0)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && evt->El_bkgTruthOrigin[lep->index[lepi]]==10)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && evt->El_bkgTruthOrigin[lep->index[lepi]]==12)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && evt->El_bkgTruthOrigin[lep->index[lepi]]==13)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && evt->El_bkgTruthOrigin[lep->index[lepi]]==14)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && evt->El_bkgTruthOrigin[lep->index[lepi]]==22)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && evt->El_bkgTruthOrigin[lep->index[lepi]]==43)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && evt->El_bkgTruthOrigin[lep->index[lepi]]==36)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && evt->El_bkgTruthOrigin[lep->index[lepi]]==40)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 ) //&& evt->El_bkgMotherPdgId[lep->index[lepi]]==22
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==3 &&  (evt->El_truthOrigin[lep->index[lepi]]==26 || evt->El_truthOrigin[lep->index[lepi]]==33)   )
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count && evt->El_truthType[lep->index[lepi]]==3 &&  (evt->El_truthOrigin[lep->index[lepi]]==25 || evt->El_truthOrigin[lep->index[lepi]]==32)   )
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			  else if(++count)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			*/

			//  h1d->GetXaxis()->FindBin("Iso"); // top, W, Z, Higgs, SUSY, Diboson
			if( evt->El_truthType[lep->index[lepi]]==2 &&  ( evt->El_truthOrigin[lep->index[lepi]]==10 || evt->El_truthOrigin[lep->index[lepi]]==12 || evt->El_truthOrigin[lep->index[lepi]]==13 || evt->El_truthOrigin[lep->index[lepi]]==14
															 || evt->El_truthOrigin[lep->index[lepi]]==22 || evt->El_truthOrigin[lep->index[lepi]]==43 ) )
			  fillHist(hist_name, tag, count, evt->EventWeight); 

			//  h1d->GetXaxis()->FindBin("Charge flip"); // Julien ChFlip
			if(++count && ( evt->El_chFlip[lep->index[lepi]]==2 ||  evt->El_chFlip[lep->index[lepi]]==4 ||  evt->El_chFlip[lep->index[lepi]]==7 ))
			  fillHist(hist_name, tag, count, evt->EventWeight); 	  
	
			//  h1d->GetXaxis()->FindBin("Bkg PhotonConv sign"); // 
			if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && fabs(evt->El_bkgMotherPdgId[lep->index[lepi]])==11 && evt->El_bkgMotherPdgId[lep->index[lepi]]*lep->charge[lepi]<0)
			  fillHist(hist_name, tag, count, evt->EventWeight); 
  
			//  h1d->GetXaxis()->FindBin("Bkg PhotonConv Iso"); // mother: top, W, Z, H, SUSY, Diboson
			if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 && ( evt->El_bkgTruthOrigin[lep->index[lepi]]==10 || evt->El_bkgTruthOrigin[lep->index[lepi]]==12 || evt->El_bkgTruthOrigin[lep->index[lepi]]==13 || evt->El_bkgTruthOrigin[lep->index[lepi]]==14 || evt->El_bkgTruthOrigin[lep->index[lepi]]==22 || evt->El_bkgTruthOrigin[lep->index[lepi]]==43 ))
			  fillHist(hist_name, tag, count, evt->EventWeight); 
			//  h1d->GetXaxis()->FindBin("Bkg PhotonConv Other"); // Brem, FSR, other
			else if(++count && evt->El_truthType[lep->index[lepi]]==4 &&  evt->El_truthOrigin[lep->index[lepi]]==5 )
			  fillHist(hist_name, tag, count, evt->EventWeight); 
  
			//  h1d->GetXaxis()->FindBin("NonIso Bottom"); // Bottom
			if(++count && evt->El_truthType[lep->index[lepi]]==3 &&  (evt->El_truthOrigin[lep->index[lepi]]==26 || evt->El_truthOrigin[lep->index[lepi]]==33)   )
			  fillHist(hist_name, tag, count, evt->EventWeight); 
  
			//  h1d->GetXaxis()->FindBin("NonIso Charm");  // Charm
			if(++count && evt->El_truthType[lep->index[lepi]]==3 &&  (evt->El_truthOrigin[lep->index[lepi]]==25 || evt->El_truthOrigin[lep->index[lepi]]==32)   )
			  fillHist(hist_name, tag, count, evt->EventWeight); 
		
		  } else {

			sprintf(hist_name, "composition_mu_pt%d", pt_thresh[pti]);
			count=0.1;	 
		
			//  h1d->GetXaxis()->FindBin("Iso"); // top, W, Z, Higgs, SUSY, Diboson
			if( evt->Mu_type[lep->index[lepi]]==6 &&  ( evt->Mu_origin[lep->index[lepi]]==10 || evt->Mu_origin[lep->index[lepi]]==12 || evt->Mu_origin[lep->index[lepi]]==13 || evt->Mu_origin[lep->index[lepi]]==14
														|| evt->Mu_origin[lep->index[lepi]]==22 || evt->Mu_origin[lep->index[lepi]]==43 ) )
			  fillHist(hist_name, tag, count, evt->EventWeight); 
  
			//  h1d->GetXaxis()->FindBin("Charge flip"); // Julien ChFlip
			if(++count)
			  fillHist(hist_name, tag, 0, 0); 	  
	
			//  h1d->GetXaxis()->FindBin("Bkg PhotonConv sign"); // 
			if(++count )
			  fillHist(hist_name, tag, 0, 0); 
  
			//  h1d->GetXaxis()->FindBin("Bkg PhotonConv Iso"); // mother: top, W, Z, H, SUSY, Diboson
			if(++count )
			  fillHist(hist_name, tag, 0, 0); 

			//  h1d->GetXaxis()->FindBin("Bkg PhotonConv Other"); // Brem, FSR, other			
			if(++count && evt->Mu_type[lep->index[lepi]]==7 &&  evt->Mu_origin[lep->index[lepi]]==5 )
			  fillHist(hist_name, tag, count, evt->EventWeight); 
  
			//  h1d->GetXaxis()->FindBin("NonIso Bottom"); // Bottom
			if(++count && evt->Mu_type[lep->index[lepi]]==7 &&  (evt->Mu_origin[lep->index[lepi]]==26 || evt->Mu_origin[lep->index[lepi]]==33)   )
			  fillHist(hist_name, tag, count, evt->EventWeight); 
  
			//  h1d->GetXaxis()->FindBin("NonIso Charm");  // Charm
			if(++count && evt->Mu_type[lep->index[lepi]]==7 &&  (evt->Mu_origin[lep->index[lepi]]==25 || evt->Mu_origin[lep->index[lepi]]==32)   )
			  fillHist(hist_name, tag, count, evt->EventWeight); 
		
		  }
		}
  }

  return;
}

void FillHistos_Variables(const char* tag, myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet) {

  if (lep->num_leptons < 2 || lep->pT[0] < LeptPt10 || lep->pT[1] < LeptPt10) {
	std::cerr << "ERROR FillHistos_Variables: incorrect usage of cuts!!!!";
	return;
  }

  char hist_name[256];

  double meff = 0;
  double ht = 0;
  
  // leptons pt
  for (int i = 0; i < lep->num_leptons; i++) {
	meff += lep->pT[i];
  }

  // jets pt
  for (int i = 0; i < jet->num_jets; i++) {
	meff += jet->pT[i];
  }

  ht = meff;
  
  //miss-Et variables
  float mis_Ex = evt->Etmiss_TST_Etx;
  float mis_Ey = evt->Etmiss_TST_Ety;
  float met = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);
  meff += met;
 
  // calculate deltaR lep, jet:
  double deltaR_lep_jet[3] = { 5., 5., 5. };
  double  dR = 10.;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>25000) // TO DO: revist the jet pt cut
	  for (int lepj = 0; lepj < lep->num_leptons; lepj++) {
		dR = DeltaR(jet->eta[jeti], jet->phi[jeti], lep->eta[lepj], lep->phi[lepj]);
		if (dR < deltaR_lep_jet[lepj])
		  deltaR_lep_jet[lepj] = dR;
	  }


  int n_jets_50 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>50000)
	  n_jets_50++;

  int n_jets_25 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>25000)
	  n_jets_25++;

  int n_jets_40 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>40000)
	  n_jets_40++;


  int n_jets = jet->num_jets;
  int n_bjets = bjet->num_jets;
  //  int n_leps = lep->num_leptons;
  
  // N-1 plots first
  if(strstr(tag,"NJETS") != NULL ){
	fillHist("NJETS", tag, n_jets, evt->EventWeight);
  }
  else if(strstr(tag,"Meff") != NULL ){
	fillHist("Meff", tag, meff / 1000., evt->EventWeight);
  }
  else if(strstr(tag,"NBJETS") != NULL ){
	fillHist("NBJETS", tag, n_bjets, evt->EventWeight);
  }
  else if(strstr(tag,"MET") != NULL ){
	fillHist("MET", tag, met / 1000., evt->EventWeight);
  }
  else{
	//-----------------------------------------------------------------------------------------
	// Jets
	fillHist("NJETS", tag, n_jets_25, evt->EventWeight);
	/*	if (n_jets >= 1) 
	  fillHist("pt_jet1", tag, jet->pT[0] / 1000., evt->EventWeight);
	if (n_jets >= 2) 
	  fillHist("pt_jet2", tag, jet->pT[1] / 1000., evt->EventWeight);
	if (n_jets >= 3) 
	  fillHist("pt_jet3", tag, jet->pT[2] / 1000., evt->EventWeight);
	if(detail){
	  if (n_jets >= 4) 
		fillHist("pt_jet4", tag, jet->pT[3] / 1000., evt->EventWeight);
	  if (n_jets >= 5) 
		fillHist("pt_jet5", tag, jet->pT[4] / 1000., evt->EventWeight);
	  for (int jeti = 0; jeti < jet->num_jets; jeti++)
		fillHist("JVT", tag, evt->Jet_JVT[jet->index[jeti]], evt->EventWeight);
		}*/
	//-----------------------------------------------------------------------------------------
	// b-Jets
	fillHist("NBJETS", tag, n_bjets, evt->EventWeight);
	/*
	if (n_bjets >= 1) 
	  fillHist("pt_bjet1", tag, bjet->pT[0] / 1000., evt->EventWeight);
	if (n_bjets >= 2) 
	  fillHist("pt_bjet2", tag, bjet->pT[1] / 1000., evt->EventWeight);
	if (n_bjets >= 3) 
	  fillHist("pt_bjet3", tag, bjet->pT[2] / 1000., evt->EventWeight);
	if(detail){
	  if (n_bjets >= 4) 
		fillHist("pt_bjet4", tag, bjet->pT[3] / 1000., evt->EventWeight);
	}
	//-----------------------------------------------------------------------------------------

	int mu_count = 1;
	int el_count = 1;
	int num_lept = 0;

	for (int j = 0; j < lep->num_leptons && num_lept < 3; j++){
	  num_lept++;

	  // Muons
	  //-----------------------------------------------------------------------------------------
	  if (!lep->is_electron[j]) {	  
		if (mu_count < 4) {
		  sprintf(hist_name, "mu%d_pt", mu_count);
		  fillHist(hist_name, tag, lep->pT[j] / 1000., evt->EventWeight);		
		  if(detail){	
			sprintf(hist_name, "mu%d_D0", mu_count);
			fillHist(hist_name, tag, evt->Mu_d0pvtx[lep->index[j]], evt->EventWeight);
		
			sprintf(hist_name, "mu%d_D0sig", mu_count);
			fillHist(hist_name, tag, evt->Mu_sigd0[lep->index[j]], evt->EventWeight);		

			sprintf(hist_name, "mu%d_ptvarcone30", mu_count);
			fillHist(hist_name, tag, evt->Mu_ptvarcone30[lep->index[j]]/evt->Mu_pT[lep->index[j]], evt->EventWeight);		
		  }
		}

		fillHist("mu_eta", tag, lep->eta[j], evt->EventWeight);
		if(detail){	
		  fillHist("mu_phi", tag, lep->phi[j], evt->EventWeight);
		}
		mu_count++;
	  } else {
		// Electrons
		//-----------------------------------------------------------------------------------------
	 
		if (el_count < 4) {
		  sprintf(hist_name, "el%d_pt", el_count);
		  fillHist(hist_name, tag, lep->pT[j] / 1000., evt->EventWeight);
		  if(detail){		
			sprintf(hist_name, "el%d_D0", el_count);
			fillHist(hist_name, tag, evt->El_d0pvtx[lep->index[j]], evt->EventWeight);

			sprintf(hist_name, "el%d_D0sig", el_count);
			fillHist(hist_name, tag, evt->El_sigd0[lep->index[j]], evt->EventWeight);

			sprintf(hist_name, "el%d_TightLH", el_count);
			fillHist(hist_name, tag, evt->El_isTightLH[lep->index[j]], evt->EventWeight);		

			sprintf(hist_name, "el%d_MediumLH", el_count);
			fillHist(hist_name, tag, evt->El_isMediumLH[lep->index[j]], evt->EventWeight);		

			sprintf(hist_name, "el%d_ptvarcone20", el_count);
			fillHist(hist_name, tag, evt->El_ptvarcone20[lep->index[j]]/evt->El_pT[lep->index[j]], evt->EventWeight);		
		  
			sprintf(hist_name, "el%d_topoetcone20", el_count);
			fillHist(hist_name, tag, evt->El_topoetcone20[lep->index[j]]/evt->El_pT[lep->index[j]], evt->EventWeight);		
		  }
		}

		fillHist("el_eta", tag, lep->eta[j], evt->EventWeight);
		if(detail){	
		  fillHist("el_phi", tag, lep->phi[j], evt->EventWeight);
		}		
		el_count++;
	  }
	}
	*/
	//-----------------------------------------------------------------------------------------
	// Other variables

	fillHist("MET", tag, met / 1000., evt->EventWeight);
	//	fillHist("HT", tag, ht / 1000., evt->EventWeight);
	fillHist("Meff", tag, meff / 1000., evt->EventWeight);
	/*
	fillHist("mT", tag, transverse_mass(evt, lep) / 1000., evt->EventWeight);
	if(detail){	
	  fillHist("mT2", tag, transverse_mass(evt, lep) / 1000., evt->EventWeight);
	  fillHist("mT_min", tag, transverse_mass_min(evt, lep) / 1000., evt->EventWeight);
	  if (lep->has_Z)
		fillHist("MZ", tag, lep->MZ / 1000., evt->EventWeight);
	  if(lep->num_leptons>2){
		fillHist("Mlll", tag,  trilepton_mass_lead(evt, lep) / 1000., evt->EventWeight);
		fillHist("Mleps", tag,  multilepton_mass(evt, lep) / 1000., evt->EventWeight);
	  }
	}

	// Compute Mee and Mmumu  // TO DO: create function
	//-----------------------------------------------------------------------------------------
	fillHist("Mll", tag, dilepton_mass_lead(evt, lep) / 1000., evt->EventWeight);
	TLorentzVector lep_tlv[3], lep_sum;
	float M;
	for (int lepi = 0; lepi < lep->num_leptons; lepi++) 
	  for (int lepj = lepi+1; lepj < lep->num_leptons; lepj++) { 
		if (lep->is_electron[lepi] == lep->is_electron[lepj] && lep->charge[lepi]*lep->charge[lepj] > 0 ){ 

		  if (!lep->is_electron[lepi]) {//muons 
			lep_tlv[0].SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]],muon_mass);
			lep_tlv[1].SetPtEtaPhiM(evt->Mu_pT[lep->index[lepj]],evt->Mu_eta[lep->index[lepj]],evt->Mu_phi[lep->index[lepj]],muon_mass);
			lep_sum = lep_tlv[0] + lep_tlv[1];
			M = (lep_sum).M();
			fillHist("Mmumu", tag, M / 1000., evt->EventWeight);
		  } else { //electrons 
			lep_tlv[0].SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
			lep_tlv[1].SetPtEtaPhiE(evt->El_pT[lep->index[lepj]],evt->El_eta[lep->index[lepj]],evt->El_phi[lep->index[lepj]],evt->El_E[lep->index[lepj]]);
			lep_sum = lep_tlv[0] + lep_tlv[1];
			M = (lep_sum).M();
			fillHist("Mee", tag, M / 1000., evt->EventWeight);

		  }
		}
	  }

	//-----------------------------------------------------------------------------------------
	// LEPPt
	int lep_count = 1;
	int lep_tot_charge = 0;
	for (int j = 0; j < lep->num_leptons; j++)
	  {
		sprintf(hist_name, "LEPPt");
		fillHist(hist_name, tag, lep->pT[j] / 1000., evt->EventWeight);
	  
		// ordered in pT
		if (lep_count < 4) {
		  sprintf(hist_name, "LEP%dPt", lep_count);
		  fillHist(hist_name, tag, lep->pT[j] / 1000., evt->EventWeight);
		}
		lep_count++;
		lep_tot_charge += lep->charge[j];
	  }
	if(detail){	
	  fillHist("LEPChargeSum", tag, lep_tot_charge, evt->EventWeight);
	  fillHist("lep_softest_pt", tag, lep->pT[lep_count] / 1000., evt->EventWeight);
	  //-----------------------------------------------------------------------------------------
	  if (deltaR_lep_jet[0] < 5.)
		fillHist("deltaR_lep1_jet", tag, deltaR_lep_jet[0], evt->EventWeight);
	  if (deltaR_lep_jet[1] < 5.)
		fillHist("deltaR_lep2_jet", tag, deltaR_lep_jet[1], evt->EventWeight);
	  if (deltaR_lep_jet[2] < 5.)
		fillHist("deltaR_lep3_jet", tag, deltaR_lep_jet[2], evt->EventWeight);

	  //-----------------------------------------------------------------------------------------
	  // 2D histograms
	  fill2DHist("NJETS_MET", tag, n_jets, met / 1000., evt->EventWeight);
	  fill2DHist("NJETS_NBJETS", tag, n_jets, n_bjets, evt->EventWeight);
	  fill2DHist("NJETS_Meff", tag, n_jets, meff/1000., evt->EventWeight);
	  fill2DHist("NBJETS_MET", tag, n_bjets, met / 1000., evt->EventWeight);
	  fill2DHist("NBJETS_Meff", tag, n_bjets, meff / 1000., evt->EventWeight);
	  fill2DHist("MET_Meff", tag, met / 1000., meff/1000., evt->EventWeight);
	}
	*/
	//-----------------------------------------------------------------------------------------
  }
  return;
}

// Fill a single histogram
//-----------------------------------------------------------------------
void fillHist(const char* hname, const char* tag, float val, double weight) {
  TH1F* hist;
  char my_hname[256];

  sprintf(my_hname, "%s_%s", hname, tag);
  //  cout << my_hname << endl;
  hist = (TH1F*) gDirectory->Get(my_hname);
  if (hist) {

	//Now we need to determine the range of the x-axis
	double min = hist->GetXaxis()->GetBinLowEdge(1);
	double max = hist->GetXaxis()->GetBinUpEdge(hist->GetNbinsX());

	if (min <= val && val < max) {
	  hist->Fill(val, weight);
	} else {
	  if (min > val)
		hist->Fill(hist->GetXaxis()->GetBinCenter(1), weight);

	  if (val >= max)
		hist->Fill(hist->GetXaxis()->GetBinCenter(hist->GetNbinsX()), weight);
	}

  } else {
	std::cerr << "Warning: incorrect histogram name: " << my_hname << "\n";
	gDirectory->pwd();
  }

  return;
}
//---------------------------------------------------------------------------
void fill2DHist(const char* hname, float x, float y, double weight) {

  TH2F* hist;
  hist = (TH2F*) gDirectory->Get(hname);
  if (hist)
	hist->Fill(x, y, weight);
  else
	std::cerr << "Warning: incorrect histogram name: " << hname << "\n";

  return;
}

//---------------------------------------------------------------------------
void fill2DHist(const char* hname, const char* tag, float x, float y, double weight) {

  TH2F* hist;
  char my_hname[256];
  sprintf(my_hname, "%s_%s", hname, tag);
  hist = (TH2F*) gDirectory->Get(my_hname);
  if (hist)
	hist->Fill(x, y, weight);
  else
	std::cerr << "Warning: incorrect histogram name: " << my_hname << "\n";

  return;
}

//---------------------------------------------------------------------------
void fillTProfile(const char* hname, const char* tag, float x, float y, double weight) {

  TProfile* hist;
  char my_hname[256];
  sprintf(my_hname, "%s_%s", hname, tag);

  hist = (TProfile*) gDirectory->Get(my_hname);
  if (hist)
	hist->Fill(x, y, weight);
  else
	std::cerr << "Warning: incorrect histogram name: " << my_hname << "\n";

  return;
}

//------------------------------------------------------------------------
//				-= General Functions =-
//------------------------------------------------------------------------

//Compare jet pt's
//----------------------------------------------------------------------------
int jet_pt_comparator(const void * a, const void * b) {
  Float_t pt1 = ((srtJt*) a)->pt;
  Float_t pt2 = ((srtJt*) b)->pt;
  if (pt1 < pt2)
	return 1;
  else if (pt1 == pt2)
	return 0;
  else
	return -1;
}

//Here we sort the leptons in Pt                                                               
//----------------------------------------------------------------------------
void sortLeptons(my_leptons *lep) {
  srtJt jet_srt[2 * MAXLEPT];
  my_leptons temp_lep;
  /*
	for(int i=0; i<lep->num_leptons; i++)
	std::cout << lep->is_electron[i] << " " << fabs(lep->eta[i]) << std::endl;
  */
  for (int i = 0; i < lep->num_leptons; i++) {
	jet_srt[i].ind = i;
	jet_srt[i].pt = lep->pT[i];
	//	std::cout << i  << " " <<lep->index[i] << " " <<  jet_srt[i].ind << " " << lep->index[jet_srt[i].ind]  << std::endl;
  }

  qsort(jet_srt, lep->num_leptons, sizeof(srtJt), jet_pt_comparator);

  //  for (int i = 0; i < lep->num_leptons; i++) 
  //	std::cout << i  << " " <<lep->index[i] << " " <<  jet_srt[i].ind << " " << lep->index[jet_srt[i].ind]  << std::endl;


  
  for (int i = 0; i < lep->num_leptons; i++) {
	temp_lep.index[i] = lep->index[jet_srt[i].ind];
	temp_lep.m[i] = lep->m[jet_srt[i].ind];
	if(temp_lep.is_electron[jet_srt[i].ind])
	  temp_lep.E[i] = lep->E[jet_srt[i].ind];
	temp_lep.pT[i] = lep->pT[jet_srt[i].ind];
	temp_lep.phi[i] = lep->phi[jet_srt[i].ind];
	temp_lep.eta[i] = lep->eta[jet_srt[i].ind];
	temp_lep.is_electron[i] = lep->is_electron[jet_srt[i].ind];
	temp_lep.charge[i] = lep->charge[jet_srt[i].ind];
  }

  for (int i = 0; i < lep->num_leptons; i++) {
	lep->index[i] = temp_lep.index[i];
	lep->m[i] = temp_lep.m[i];
	if(lep->is_electron[i])
	  lep->E[i] = temp_lep.E[i];
	lep->pT[i] = temp_lep.pT[i];
	lep->phi[i] = temp_lep.phi[i];
	lep->eta[i] = temp_lep.eta[i];
	lep->is_electron[i] = temp_lep.is_electron[i];
	lep->charge[i] = temp_lep.charge[i];
  }

  /*
	for (int i = 0; i < lep->num_leptons; i++) {
	std::cout << i  << " " <<lep->index[i] << " " <<  jet_srt[i].ind << " " << lep->index[jet_srt[i].ind]  << std::endl;
	lep->index[i] = lep->index[jet_srt[i].ind];
	lep->m[i] = lep->m[jet_srt[i].ind];
	if(lep->is_electron[jet_srt[i].ind])
	lep->E[i] = lep->E[jet_srt[i].ind];
	lep->pT[i] = lep->pT[jet_srt[i].ind];
	lep->phi[i] = lep->phi[jet_srt[i].ind];
	lep->eta[i] = lep->eta[jet_srt[i].ind];
	lep->is_electron[i] = lep->is_electron[jet_srt[i].ind];
	lep->charge[i] = lep->charge[jet_srt[i].ind];
	}*/

  //	for(int i=0; i<lep->num_leptons; i++)
  //		std::cout << lep->is_electron[i] << " " << fabs(lep->eta[i]) << std::endl;


  return;
}

//Here we sort the jets in Pt                                                               
//----------------------------------------------------------------------------
void sortJets(my_jets *jet) {
  srtJt jet_srt[2 * MAXLEPT];
  my_jets temp_jet;
  for (int i = 0; i < jet->num_jets; i++) {
	jet_srt[i].ind = i;
	jet_srt[i].pt = jet->pT[i];
  }
  qsort(jet_srt, jet->num_jets, sizeof(srtJt), jet_pt_comparator);
  for (int i = 0; i < jet->num_jets; i++) {
	temp_jet.index[i] = jet->index[jet_srt[i].ind];
	temp_jet.pT[i] = jet->pT[jet_srt[i].ind];
	temp_jet.phi[i] = jet->phi[jet_srt[i].ind];
	temp_jet.eta[i] = jet->eta[jet_srt[i].ind];
	temp_jet.E[i] = jet->E[jet_srt[i].ind];
	temp_jet.MV2c20[i] = jet->MV2c20[jet_srt[i].ind];
  }
  for (int i = 0; i < jet->num_jets; i++) {
	jet->index[i] = temp_jet.index[i];
	jet->pT[i] = temp_jet.pT[i];
	jet->phi[i] = temp_jet.phi[i];
	jet->eta[i] = temp_jet.eta[i];
	jet->E[i] = temp_jet.E[i];
	jet->MV2c20[i] = temp_jet.MV2c20[i];
  }
  return;
}

// Calculate DeltaR
//----------------------------------------------------------------------------
double DeltaR(float eta1, float phi1, float eta2, float phi2) {
  const double PI = TMath::Pi();
  double deltaR12 = fabs((double) phi1 - (double) phi2);
  if (deltaR12 > PI)
	deltaR12 = 2.0 * PI - deltaR12;
  deltaR12 = sqrt(deltaR12 * deltaR12 + ((double) eta1 - (double) eta2) * ((double) eta1 - (double) eta2));
  return deltaR12;
}

// Calculate Delta Phi
//------------------------------------------------------------------------
double DeltaPhi(float phi1, float phi2) {

  double deltaR12 = (double) phi1 - (double) phi2;
  if (deltaR12 >= TMath::Pi())
	deltaR12 -= 2. * TMath::Pi();
  if (deltaR12 <= -TMath::Pi())
	deltaR12 += 2. * TMath::Pi();

  return deltaR12;
}

// Classify jets
//------------------------------------------------------------------------
void classify_jets(myevt *evt, my_jets  *jet){

  bool is_btype = false;
  bool is_ctype = false;
  bool is_ltype = false;

  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	{
	  jet->is_btype_jet[jeti] = false;
	  jet->is_ctype_jet[jeti] = false;
	  jet->is_ltype_jet[jeti] = false;
	}

  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	{
		
	  //	  if(fabs(evt->Jet_ConeTruthLabel[jet->index[jeti]]) == 5)
	  if(fabs(evt->Jet_HadronConeExclTruthLabel[jet->index[jeti]]) == 5)
		{
		  jet->is_btype_jet[jeti] = true;
		  jet->is_ctype_jet[jeti] = false;
		  jet->is_ltype_jet[jeti] = false;
		}
	  //	  else if(fabs(evt->Jet_ConeTruthLabel[jet->index[jeti]]) == 4)
	  else if(fabs(evt->Jet_HadronConeExclTruthLabel[jet->index[jeti]]) == 4)
		{
		  jet->is_btype_jet[jeti] = false;
		  jet->is_ctype_jet[jeti] = true;
		  jet->is_ltype_jet[jeti] = false;
		}
	  else 
		{
		  jet->is_btype_jet[jeti] = false;
		  jet->is_ctype_jet[jeti] = false;
		  jet->is_ltype_jet[jeti] = true;
		}
	}
}

// Classify leptons
//------------------------------------------------------------------------
/*
  http://acode-browser2.usatlas.bnl.gov/lxr-rel17/source/atlas/PhysicsAnalysis/MCTruthClassifier/MCTruthClassifier/MCTruthClassifierDefs.h
  http://acode-browser2.usatlas.bnl.gov/lxr-rel17/source/atlas/PhysicsAnalysis/MCTruthClassifier/src/MCTruthClassifier.cxx

  type:
  IsoElectron     =  2
  NonIsoElectron  =  3
  BkgElectron     =  4
  UnknownMuon     =  5
  IsoMuon         =  6
  NonIsoMuon      =  7

  origin:
  PhotonConv    = 5
  top           = 10
  WBoson        = 12
  ZBoson        = 13
  SUSY          = 22
  FSRPhot       = 40
  BottomMeson   = 26
  BBbarMeson    = 29  
  BottomBaryon  = 33


  *************************************
  if (EleOrig == WBoson     || EleOrig == ZBoson     || EleOrig == top       ||
  EleOrig == SingleElec || EleOrig == Higgs      || EleOrig == HiggsMSSM || 
  EleOrig == WZMSSM     || EleOrig == WBosonLRSM || EleOrig == NuREle    || 
  EleOrig == NuRMu      || EleOrig == NuRTau     || EleOrig == LQ        || 
  EleOrig == SUSY       || m_isPrompt )  
  return IsoElectron;
  if (EleOrig == JPsi          || EleOrig == BottomMeson  || 
  EleOrig == CharmedMeson  || EleOrig == BottomBaryon || 
  EleOrig == CharmedBaryon || EleOrig == TauLep       ||
  EleOrig == Mu            || EleOrig == QuarkWeakDec)
  return  NonIsoElectron; 
  return BkgElectron;
  *************************************
  if (MuOrig == WBoson     || MuOrig == ZBoson     || MuOrig == top       ||
  MuOrig == SingleMuon || MuOrig == Higgs      || MuOrig == HiggsMSSM || 
  MuOrig == WZMSSM     || MuOrig == WBosonLRSM || MuOrig == NuREle    ||  
  MuOrig == NuRMu      || MuOrig == NuRTau     || MuOrig == LQ        || 
  MuOrig == SUSY       || m_isPrompt)  
  return IsoMuon;
  if (MuOrig == JPsi          || MuOrig == BottomMeson  || 
  MuOrig == CharmedMeson  || MuOrig == BottomBaryon || 
  MuOrig == CharmedBaryon ||  MuOrig == TauLep      ||
  MuOrig == QuarkWeakDec)
  return  NonIsoMuon;
  return BkgMuon;
  *************************************
  if ( (m_MotherPDG == 22 && m_NumOfDaug == 2 &&  NumOfEl == 1 && NumOfPos == 1)||
  (m_MotherPDG == 22 && m_NumOfDaug == 1 && (NumOfEl == 1 || NumOfPos == 1)))
  return PhotonConv;  
  *************************************
  El_chFlip variable:
  CHARGE_UNKNOWN = 0,
  CHARGE_CORRECT = 1,
  CHARGE_FLIPPED = 2,
  CHARGE_MAYBE_CORRECT = 3,
  CHARGE_MAYBE_FLIPPED = 4,
  CHARGE_AMBIGUOUS = 5,
  CHARGE_MCTRUTHCLASSIFIER_CORRECT = 6,
  CHARGE_MCTRUTHCLASSIFIER_FLIPPED = 7
  *************************************
  */

//------------------------------------------------------------------------
void classify_leptons(myevt *evt, my_leptons *lep){

  if (lep->num_leptons < 2 || lep->pT[0] < LeptPt10 || lep->pT[1] < LeptPt10) {
	std::cerr << "ERROR classify_leptons: incorrect usage of cuts!!!!";
	return;
  }
  
  //  char hist_name[256];

  bool iso = false;
  bool iso_e = false;
  bool iso_m = false;
  bool HF_e = false;
  bool HF_m = false;
  bool chmisId = false;

  if (iso_e || iso_m){}

  int num_lept = 0;
  for (int i = 0; i < lep->num_leptons/* && num_lept < 3*/; i++) {
	lep->is_fake_HF[i] = false;
	lep->is_fake_LF[i] = false;
	lep->is_chmisid[i] = false;
	num_lept++;
  }
  
  /*  if(lep->has_ss){
  std::cout << "\nEventNumber=" << evt->EventNumber << std::endl;
  for (int i = 0; i < lep->num_leptons && num_lept < 3; i++) {
	if(lep->is_electron[i])
      std::cout <<  "el" << i << " T/O/PdgId/Charge=" << evt->El_truthType[lep->index[i]] << "/" << evt->El_truthOrigin[lep->index[i]] << "/" << evt->El_firstEgMotherPdgId[lep->index[i]]  << "/" << lep->charge[i] << std::endl;
	else 
	  std::cout <<  "mu" << i << " T/O/Charge=" << evt->Mu_type[lep->index[i]] << "/" << evt->Mu_origin[lep->index[i]] << "/" << lep->charge[i] << std::endl;
  }
  }*/

  num_lept = 0;
  for (int i = 0; i < lep->num_leptons /*&& num_lept < 3*/; i++) {
	num_lept++;
	if(lep->is_electron[i]){
	
	  // real electron with correct charge
	  iso = ( (evt->El_truthType[lep->index[i]]==2 || (evt->El_truthOrigin[lep->index[i]] == 5 && fabs(evt->El_firstEgMotherPdgId[lep->index[i]])==11)) && (lep->charge[i]*evt->El_firstEgMotherPdgId[lep->index[i]] < 0));
	
	  // real electron with charge flip
	  chmisId =  ( lep->num_leptons == 2 || lep->has_3lss ) && ( (evt->El_truthType[lep->index[i]]==2 || (evt->El_truthOrigin[lep->index[i]] == 5 && fabs(evt->El_firstEgMotherPdgId[lep->index[i]])==11)) && (lep->charge[i]*evt->El_firstEgMotherPdgId[lep->index[i]] > 0));

	  // case 1: HF is from b-mesons
	  HF_e = ( evt->El_truthOrigin[lep->index[i]]==26 || evt->El_truthOrigin[lep->index[i]]==33  );
	
	  // case 2: HF is from b or c-mesons
	  //HF_e = (evt->El_truthType[lep->index[i]]==3 && ( evt->El_truthOrigin[lep->index[i]]==26 || evt->El_truthOrigin[lep->index[i]]==33 ||  evt->El_truthOrigin[lep->index[i]]==25 || evt->El_truthOrigin[lep->index[i]]==32 ));

	} else {

	  iso = ( evt->Mu_type[lep->index[i]]==6 ); 

	  // case 1: HF is from b-mesons
	  HF_m =  (  evt->Mu_origin[lep->index[i]]==26 || evt->Mu_origin[lep->index[i]]==33 );

	  // case 2: HF is from b or c-mesons
	  //HF_m = (evt->Mu_type[lep->index[i]]==7 && (  evt->Mu_origin[lep->index[i]]==26 || evt->Mu_origin[lep->index[i]]==33 || evt->Mu_origin[lep->index[i]]==25 || evt->Mu_origin[lep->index[i]]==32 ));
	}

	if( iso ){ 	// real lepton
	  lep->is_fake_HF[i] = false;
	  lep->is_fake_LF[i] = false;
	  lep->is_chmisid[i] = false;
	} 
	else if( chmisId){    // charge flipped electrons: Note we classify them based on background not on lepton truth charge - ToDo
	  lep->is_fake_HF[i] = false;
	  lep->is_fake_LF[i] = false;
	  lep->is_chmisid[i] = true;
	} else if (HF_e || HF_m){// non prompt leptons from heavy decays - see definition above
	  lep->is_fake_HF[i] = true;
	  lep->is_fake_LF[i] = false;
	  lep->is_chmisid[i] = false;
	}
	else { // everything else is LF
	  lep->is_fake_HF[i] = false;
	  lep->is_fake_LF[i] = true;
	  lep->is_chmisid[i] = false;
	}
  }

  return;
}

// Trigger Matching

bool checkTriggerMatching(myevt *evt, my_leptons *lep){
  
  bool accept = true; 

  if(evt->trigRND < 290000) { // for 2015

	if(debug){
	  std::cout<<"Debug " << evt->EventNumber << ", 2015 config; met="<<evt->Etmiss_TST_Et<<", xe70="<<(bool)evt->HLT_xe70<<std::endl;
	}

	if(evt->Etmiss_TST_Et>250000. && evt->HLT_xe70)
	  return true;
	int ne12=0, ne17=0, nmu14=0, nmu18_mu8=0; 

	for (int lepi = 0; lepi < lep->num_leptons; lepi++)
	  {
		if(lep->is_electron[lepi]){ // electron
		  if(lep->pT[lepi]>20000){
			if(evt->El_trigMatch_2e12_lhloose_L12EM10VH[lep->index[lepi]]) ++ne12;
			if(evt->El_trigMatch_e17_lhloose_mu14[lep->index[lepi]]) ++ne17;             
		  }
		} else // muon
		  {
			if(lep->pT[lepi]>20000){
			  if(evt->Mu_trigMatch_e17_lhloose_mu14[lep->index[lepi]]) ++nmu14;

			  for (int lepj = 0; lepj < lep->num_leptons; lepj++)
				if(!lep->is_electron[lepj] && lep->pT[lepj]>10000){
				  if(evt->Mu_trigMatchPair_mu18_mu8noL1[evt->NMu*lep->index[lepi]+lep->index[lepj]]) ++nmu18_mu8;
				}
			}
		  }
	  }

	accept = (evt->HLT_2e12_lhloose_L12EM10VH && ne12>=2) || (evt->HLT_e17_lhloose_mu14 && ne17>=1 && nmu14>=1) || (evt->HLT_mu18_mu8noL1 && nmu18_mu8>=1);

	if(debug){
	  std::cout<<(bool)evt->HLT_2e12_lhloose_L12EM10VH<<" ("<<ne12<<"), "<<(bool)evt->HLT_e17_lhloose_mu14<<" ("<<ne17<<","<<nmu14<<"), "<<(bool)evt->HLT_mu18_mu8noL1<<" ("<<nmu18_mu8<<")"<<std::endl;
	}

  } else { // for 2016

	if(debug){
	  std::cout<<"Debug " << evt->EventNumber << ", 2016 config; met="<<evt->Etmiss_TST_Et<<", xe100="<<(bool)evt->HLT_xe100_mht_L1XE50<<", xe110="<<(bool)evt->HLT_xe110_mht_L1XE50<<std::endl;
	}

	if(evt->Etmiss_TST_Et>250000. && (evt->HLT_xe100_mht_L1XE50 || evt->HLT_xe110_mht_L1XE50) )
	  return true;
	int ne17_ee=0, nmu14=0, nmu22_mu8=0, ne17_em=0; 
	double pt1=0,pt2=0;
	for (int lepi = 0; lepi < lep->num_leptons; lepi++)
	  {

		if(lep->is_electron[lepi]){ // electron
		  if(lep->pT[lepi]>20000){
			if(evt->El_trigMatch_2e17_lhvloose_nod0[lep->index[lepi]]) ++ne17_ee;
			if(evt->El_trigMatch_e17_lhloose_nod0_mu14[lep->index[lepi]]) ++ne17_em;
		  }
		}
		else // muon
		  {
			if(lep->pT[lepi]>20000)
			  if(evt->Mu_trigMatch_e17_lhloose_nod0_mu14[lep->index[lepi]]) ++nmu14;
			
			if(lep->pT[lepi]>23000){
			  for (int lepj = 0; lepj < lep->num_leptons; lepj++)
				if(!lep->is_electron[lepj] && lep->pT[lepj]>10000 && lepj != lepi){
				  if(evt->Mu_trigMatchPair_mu22_mu8noL1[evt->NMu*lep->index[lepi]+lep->index[lepj]]) {++nmu22_mu8;pt1=lep->pT[lepi];pt2=lep->pT[lepj];}
				}
			}
		  }
	  }
	
	accept = (evt->HLT_2e17_lhvloose_nod0 && ne17_ee>=2) || (evt->HLT_e17_lhloose_nod0_mu14 && ne17_em>=1 && nmu14>=1) || (evt->HLT_mu22_mu8noL1 && nmu22_mu8>=1);
	
	if(debug){
	  std::cout<<(bool)evt->HLT_2e17_lhvloose_nod0<<" ("<<ne17_ee<<"), "<<(bool)evt->HLT_e17_lhloose_nod0_mu14<<" ("<<ne17_em<<","<<nmu14<<"), "<<(bool)evt->HLT_mu22_mu8noL1<<" ("<<nmu22_mu8<<")->pt("<<pt1<<","<<pt2<<")"<<std::endl;
	} 
  }

  return  accept; // true;

}

  
//------------------------------------------------------------------------
//				-= Overlap Removal Functions  =-
//------------------------------------------------------------------------

// in a jet loop
bool jet_overlaps_electron(myevt *evt, int jeti) {

  bool dR_overlap = false;
  float dR;
  TLorentzVector veci, vecj;
  veci.SetPtEtaPhiE(evt->Jet_pT[jeti],evt->Jet_eta[jeti],evt->Jet_phi[jeti],evt->Jet_E[jeti]);
  float yi = veci.Rapidity();
  for (int elj = 0; elj < evt->NEl && !dR_overlap; elj++) 
	if(is_baseline_electron(evt, elj)){
	  vecj.SetPtEtaPhiE(evt->El_pT[elj],evt->El_eta[elj],evt->El_phi[elj],evt->El_E[elj]);
	  //vecj.SetPtEtaPhiM(evt->El_pT[elj],evt->El_eta[elj],evt->El_phi[elj],electron_mass);
	  float yj     = vecj.Rapidity();
	  //dR = DeltaR(evt->El_eta[elj], evt->El_phi[elj], evt->Jet_eta[jeti], evt->Jet_phi[jeti]);
	  dR = DeltaR(yi, evt->Jet_phi[jeti], yj, evt->El_phi[elj]);
	  dR_overlap |= (dR <= 0.2);
	}
  //check if it is not a bjet
  /* dR_overlap &= (evt->Jet_MV2c20[jeti] < -.5911  || fabs(evt->Jet_eta[jeti])>2.5 || fabs(evt->Jet_pT[jeti]) < 20000 || (evt->Jet_pT[jeti] < 60000. && fabs(evt->Jet_eta[jeti]) < 2.4 && evt->Jet_JVT[jeti]<0.59));*/
  dR_overlap &= (evt->Jet_MV2c20[jeti] < 0.0206  || fabs(evt->Jet_eta[jeti])>2.5 || fabs(evt->Jet_pT[jeti]) < 20000 || (evt->Jet_pT[jeti] < 60000. && fabs(evt->Jet_eta[jeti]) < 2.4 && evt->Jet_JVT[jeti]<0.59));
  return dR_overlap;
}

// in an electron loop
bool electron_overlaps_jet(myevt *evt, int eli, my_jets *jet_4Overlap) {
  bool dR_overlap = false;
  float dR;
  TLorentzVector veci, vecj;
  veci.SetPtEtaPhiE(evt->El_pT[eli],evt->El_eta[eli],evt->El_phi[eli],evt->El_E[eli]);
  //veci.SetPtEtaPhiM(evt->El_pT[eli],evt->El_eta[eli],evt->El_phi[eli],electron_mass);
  float yi     = veci.Rapidity();
  for (int jetk = 0; jetk < jet_4Overlap->num_jets && !dR_overlap ; jetk++)
	{
	  //	if( fabs(jet_4Overlap->eta[jetk]) < 2.8){	
	  vecj.SetPtEtaPhiE(jet_4Overlap->pT[jetk], jet_4Overlap->eta[jetk], jet_4Overlap->phi[jetk], jet_4Overlap->E[jetk]);
	  float yj     = vecj.Rapidity();
	  dR = DeltaR(yi, evt->El_phi[eli], yj, jet_4Overlap->phi[jetk]);
	  dR_overlap |= (dR < 0.4);
	}
  return dR_overlap;
}

bool electron_overlapsdR_jet(myevt *evt, int eli, my_jets *jet) {
  bool dR_overlap = false;
  float dR;
  TLorentzVector veci, vecj;
  veci.SetPtEtaPhiE(evt->El_pT[eli],evt->El_eta[eli],evt->El_phi[eli],evt->El_E[eli]);
  //veci.SetPtEtaPhiM(evt->El_pT[eli],evt->El_eta[eli],evt->El_phi[eli],electron_mass);
  float yi     = veci.Rapidity();
  for (int jetk = 0; jetk < jet->num_jets && !dR_overlap ; jetk++)
	{
	  //	if( fabs(jet->eta[jetk]) < 2.8){	
	  vecj.SetPtEtaPhiE(jet->pT[jetk], jet->eta[jetk], jet->phi[jetk], jet->E[jetk]);
	  float yj     = vecj.Rapidity();
	  dR = DeltaR(yi, evt->El_phi[eli], yj, jet->phi[jetk]);
	  dR_overlap |= (dR < std::min(0.4, 0.1 + (9600./evt->El_pT[eli])));
	}
  return dR_overlap;
}

//in a muon loop
bool muon_overlaps_jet(myevt *evt, int mui, my_jets *jet_4Overlap) {
  bool dR_overlap = false;
  float dR;
  TLorentzVector veci, vecj;
  veci.SetPtEtaPhiM(evt->Mu_pT[mui],evt->Mu_eta[mui],evt->Mu_phi[mui], muon_mass);
  float yi     = veci.Rapidity();
  for (int jetk = 0; jetk < jet_4Overlap->num_jets && !dR_overlap  ; jetk++)
	//	if( fabs(jet_4Overlap->eta[jetk]) < 2.8){
	{
	  vecj.SetPtEtaPhiE(jet_4Overlap->pT[jetk], jet_4Overlap->eta[jetk], jet_4Overlap->phi[jetk], jet_4Overlap->E[jetk]);
	  float yj     = vecj.Rapidity();
	  dR = DeltaR(yi, evt->Mu_phi[mui], yj, jet_4Overlap->phi[jetk]);
	  //	  dR_overlap |= (dR < 0.2 && evt->Jet_nTrk[jet_4Overlap->index[jetk]]>=3);
	  dR_overlap |= (dR <= 0.4 && evt->Jet_nTrk[jet_4Overlap->index[jetk]]>=3); // New recommendation  Sep21
	}
  return dR_overlap;
}

bool muon_overlapsdR_jet(myevt *evt, int mui, my_jets *jet) {
  bool dR_overlap = false;
  float dR;
  TLorentzVector veci, vecj;
  veci.SetPtEtaPhiM(evt->Mu_pT[mui],evt->Mu_eta[mui],evt->Mu_phi[mui], muon_mass);
  float yi     = veci.Rapidity();
  for (int jetk = 0; jetk < jet->num_jets && !dR_overlap  ; jetk++)
	//	if( fabs(jet->eta[jetk]) < 2.8){
	{
	  vecj.SetPtEtaPhiE(jet->pT[jetk], jet->eta[jetk], jet->phi[jetk], jet->E[jetk]);
	  float yj     = vecj.Rapidity();
	  dR = DeltaR(yi, evt->Mu_phi[mui], yj, jet->phi[jetk]);
	  //	  dR_overlap |= (dR < 0.2 && evt->Jet_nTrk[jet->index[jetk]]>=3);
	  //		dR_overlap |= (dR <= 0.4 && evt->Jet_nTrk[jet->index[jetk]]>=3); // New recommendation  Sep21
	  dR_overlap |= (dR < std::min(0.4, 0.1 + (9600./evt->Mu_pT[mui])));
	}
  return dR_overlap;
}

// in a jet loop
bool jet_overlaps_muon(myevt *evt, int jeti) {
  bool dR_overlap = false;
  float dR;
  TLorentzVector veci, vecj;
  veci.SetPtEtaPhiE(evt->Jet_pT[jeti],evt->Jet_eta[jeti],evt->Jet_phi[jeti],evt->Jet_E[jeti]);
  float yi     = veci.Rapidity();
  for (int muj = 0; muj < evt->NMu && !dR_overlap; muj++) 
	{
	  vecj.SetPtEtaPhiM(evt->Mu_pT[muj],  evt->Mu_eta[muj], evt->Mu_phi[muj], muon_mass);
	  float yj     = vecj.Rapidity();
	  dR = DeltaR(yi, evt->Jet_phi[jeti], yj, evt->Mu_phi[muj]);
	  //	  dR_overlap |= (dR < 0.2 && evt->Jet_nTrk[jeti]<3);
	  dR_overlap |= (dR < 0.4 && evt->Jet_nTrk[jeti]<3); // New recommendation Sep21
	}
  return dR_overlap;
}


// in an electron loop
bool electron_overlaps_electron(myevt *evt, int eli, my_leptons *elec_4Overlap) {
  if(evt){}; // suppress warning
  bool dR_overlap = false;
  float dR;
  TLorentzVector veci, vecj;
  veci.SetPtEtaPhiE(elec_4Overlap->pT[eli],elec_4Overlap->eta[eli],elec_4Overlap->phi[eli],elec_4Overlap->E[eli]);
  //veci.SetPtEtaPhiM(elec_4Overlap->pT[eli],elec_4Overlap->eta[eli],elec_4Overlap->phi[eli],electron_mass);
  float yi     = veci.Rapidity();
  if(elec_4Overlap->num_leptons>1)
	for (int elj = 0; elj < elec_4Overlap->num_leptons && !dR_overlap ; elj++)
	  if( elj != eli){	
		//		vecj.SetPtEtaPhiE(elec_4Overlap->pT[elj],elec_4Overlap->eta[elj],elec_4Overlap->phi[elj],elec_4Overlap->E[elj]);
		vecj.SetPtEtaPhiE(elec_4Overlap->pT[elj],elec_4Overlap->eta[elj],elec_4Overlap->phi[elj], elec_4Overlap->E[elj]);
		float yj     = vecj.Rapidity();
		dR = DeltaR(yi, elec_4Overlap->phi[eli], yj, elec_4Overlap->phi[elj]);

		dR_overlap |= (dR < 0.05 && (elec_4Overlap->pT[eli] < elec_4Overlap->pT[elj]));
	  }
  
  return dR_overlap;
}



// in an electron loop
bool electron_overlaps_muon(myevt *evt, int eli, my_leptons *muon_4Overlap) {
  bool dR_overlap = false;
  float dR;
  TLorentzVector veci, vecj;
  veci.SetPtEtaPhiE(evt->El_pT[eli],evt->El_eta[eli],evt->El_phi[eli],evt->El_E[eli]);
  //veci.SetPtEtaPhiM(evt->El_pT[eli],evt->El_eta[eli],evt->El_phi[eli],electron_mass);
  float yi     = veci.Rapidity();
  for (int muj = 0; muj < muon_4Overlap->num_leptons && !dR_overlap; muj++){
	vecj.SetPtEtaPhiM(muon_4Overlap->pT[muj],  muon_4Overlap->eta[muj], muon_4Overlap->phi[muj], muon_mass);
	float yj     = vecj.Rapidity();
	dR = DeltaR(yi, evt->El_phi[eli], yj, muon_4Overlap->phi[muj]);
	dR_overlap |= (dR < 0.01);
  }



  return dR_overlap;
}

// in a muon loop
bool muon_overlaps_electron(myevt *evt, int mui, my_leptons *elec_4Overlap) {
  bool dR_overlap = false;
  float dR;
  TLorentzVector veci, vecj;
  veci.SetPtEtaPhiM(evt->Mu_pT[mui],evt->Mu_eta[mui],evt->Mu_phi[mui], muon_mass);
  float yi     = veci.Rapidity();
  for (int elj = 0; elj < elec_4Overlap->num_leptons && !dR_overlap; elj++){

	vecj.SetPtEtaPhiE(elec_4Overlap->pT[elj],elec_4Overlap->eta[elj],elec_4Overlap->phi[elj],elec_4Overlap->E[elj]);
	//vecj.SetPtEtaPhiM(elec_4Overlap->pT[elj],elec_4Overlap->eta[elj],elec_4Overlap->phi[elj],electron_mass);
	float yj     = vecj.Rapidity();
	dR = DeltaR(yi, evt->Mu_phi[mui], yj, elec_4Overlap->phi[elj]);
	dR_overlap |= (dR < 0.01);
  }
  return dR_overlap;
}


//------------------------------------------------------------------------
//				-= Baseline Definitions  =-
//------------------------------------------------------------------------

// electrons
//----------------------------------------------------------------------------
bool is_baseline_electron(myevt *evt, int eli) {
  bool good_electron = evt->El_isLooseAndBLayerLH[eli];
  good_electron &= (evt->El_pT[eli] > 10000.); 
  //  good_electron &= (fabs(evt->El_eta[eli]) < 2.47 && (fabs(evt->El_eta[eli]) >= 1.52 || fabs(evt->El_eta[eli]) <= 1.37));
  good_electron &= (fabs(evt->El_etaclus[eli]) < 2.47 && (fabs(evt->El_etaclus[eli]) >= 1.52 || fabs(evt->El_etaclus[eli]) <= 1.37));
  //   good_electron &= (fabs(evt->El_etaclus[eli]) < 2.);
  good_electron &= ( fabs(evt->El_sigd0[eli]) < 5 );
  return good_electron;
}

// muons
//----------------------------------------------------------------------------
bool is_baseline_muon(myevt *evt, int mui) {
  bool good_muon = (evt->Mu_pT[mui] > 10000. && fabs(evt->Mu_eta[mui]) < 2.5); 
  return good_muon;
}

// jets
//----------------------------------------------------------------------------
// baseline: 
bool is_baseline_jet(myevt *evt, int jetk) {
  bool good_jet = evt->Jet_pT[jetk] > 20000.; 
  good_jet &= !(evt->Jet_pT[jetk] < 60000. && fabs(evt->Jet_eta[jetk]) < 2.4 && evt->Jet_JVT[jetk]<0.59);
  //   good_jet &= fabs(evt->Jet_eta[jetk]) <  2.8;
  //  good_jet &= evt->Jet_isSig[jetk];
  return good_jet;
}

//------------------------------------------------------------------------
//				-= Signal Definitions  =-
//------------------------------------------------------------------------

// electrons
//----------------------------------------------------------------------------
bool is_signal_electron(myevt *evt, int eli) {
  bool good_electron =  true;

  //  if(evt->El_pT[eli] >= 300000)
  //	good_electron &= evt->El_isMediumLH[eli];
  //  else if(evt->El_pT[eli] < 300000)

  //	good_electron &= evt->El_isTightLH[eli];
  good_electron &= evt->El_isMediumLH[eli];

  //  good_electron &= evt->El_passIsoGradLoose[eli];
  good_electron &= ( evt->El_ptvarcone20[eli]/evt->El_pT[eli] < 0.06  && evt->El_topoetcone20[eli]/evt->El_pT[eli] < 0.06  )   ;
  good_electron &= ( fabs(evt->El_eta[eli]) <= 2. ); // must use this eta (track eta)

  good_electron &= ( fabs(evt->El_z0sinTheta[eli]) < 0.5 );
  good_electron &= (evt->El_passChargeFlipTaggerBDTmedium[eli] > -0.28087);

  //  good_electron &= ( fabs(evt->El_etaclus[eli]) <= 2. ); // for comparison with fabio
  //  TLorentzVector vec;
  //  vec.SetPtEtaPhiE(evt->El_pT[eli],evt->El_eta[eli],evt->El_phi[eli],evt->El_E[eli]);
  //  float theta  = vec.Theta();
  //  good_electron &= ( fabs(evt->El_z0pvtx[eli] * sin(theta)) < 0.5 );
  //   good_electron &= ( evt->El_pT[eli] > LeptPt );
  return good_electron;
}

// muons
//----------------------------------------------------------------------------
bool is_signal_muon(myevt *evt, int mui) {
  //  bool good_muon =  evt->Mu_passIsoGradLoose[mui];
  bool good_muon =   ( evt->Mu_ptvarcone30[mui]/evt->Mu_pT[mui] < 0.06 ) ;

	
  //  TLorentzVector vec;
  //  vec.SetPtEtaPhiM(evt->Mu_pT[mui],evt->Mu_eta[mui],evt->Mu_phi[mui],muon_mass);
  //  float theta  = vec.Theta();
  good_muon &= ( fabs(evt->Mu_sigd0[mui]) < 3 );
  //  good_muon &= ( fabs(evt->Mu_z0pvtx[mui] * sin(theta)) < 0.5 );
  good_muon &= ( fabs(evt->Mu_z0sinTheta[mui]) < 0.5 );

  //  good_muon &= ( evt->Mu_pT[mui] > LeptPt ) ;
  return good_muon;
}

// jets
//----------------------------------------------------------------------------
bool is_signal_jet(myevt *evt, int jeti) {
  bool good_jet = is_baseline_jet(evt, jeti);
  good_jet &= (fabs(evt->Jet_eta[jeti]) < 2.8);
  good_jet &= !(evt->Jet_pT[jeti] < 60000. && fabs(evt->Jet_eta[jeti]) < 2.4 && evt->Jet_JVT[jeti]<0.59);
  return good_jet;
}

// bjets
bool is_signal_bjet(myevt *evt, int jeti) {
  /*  bool good_jet = is_baseline_jet(evt, jeti);
	  good_jet &= (fabs(evt->Jet_eta[jeti]) < 2.5);
	  //  good_jet &= (evt->Jet_MV2c20[jeti] > 0.7110);
	  good_jet &= (evt->Jet_MV2c10[jeti] > 0.8244);
	  good_jet &= !(evt->Jet_pT[jeti] < 60000. && fabs(evt->Jet_eta[jeti]) < 2.4 && evt->Jet_JVT[jeti]<0.59);*/
  return is_signal_bjet(evt,jeti,3); // 0.8244273 -> 70% eff 
}

bool is_signal_bjet(myevt *evt, int jeti, int cut) {
  if (cut<0 || cut >5)
	return false;

  // https://twiki.cern.ch/twiki/bin/view/AtlasProtected/BTaggingBenchmarks#MV2c10_tagger_added_on_11th_May
  // Working points [30, 50, 60, 70, 77, 85] 
  const float cuts[]={0.9977155, 0.9769329, 0.934906, 0.8244273, 0.645925, 0.1758475};
 
  bool good_jet = is_baseline_jet(evt, jeti);
  good_jet &= (fabs(evt->Jet_eta[jeti]) < 2.5);
  good_jet &= (evt->Jet_MV2c10[jeti] > cuts[cut]);
  good_jet &= !(evt->Jet_pT[jeti] < 60000. && fabs(evt->Jet_eta[jeti]) < 2.4 && evt->Jet_JVT[jeti]<0.59);
  return good_jet;
}

//----------------------------------------------------------------------------
//				-= Channel Separation Function  =-
//----------------------------------------------------------------------------
void SetChannelSeparation(my_leptons *lep) {
  SetChannelSeparation(lep, 10, LargeNum, 10, LargeNum);
}

void SetChannelSeparation(my_leptons *lep, float minpt1, float maxpt1,float minpt2, float maxpt2) {
  lep->has_ss = false;
  lep->has_ee = false;
  lep->has_em = false;
  lep->has_mm = false;
  lep->has_os = false;
  lep->has_os_ee = false;
  lep->has_os_em = false;
  lep->has_os_mm = false;
  lep->has_3lss = false;

  lep->has_3lss_index0 = -1;
  lep->has_3lss_index1 = -1;
  lep->has_3lss_index2 = -1;
  
  int ind_ss[50] = {-1};
  int index = 0;
  
  if(lep->num_leptons > 1)
	if(lepton_pt_good(lep, minpt1, maxpt1, minpt2, maxpt2))
	  for (int i = 0; i < lep->num_leptons; i++) {
		for (int j = i+1; j < lep->num_leptons; j++) {
		  if((lep->charge[i]*lep->charge[j])>0){
			lep->has_ss = true;
			ind_ss[index] = i;
			index++;
			ind_ss[index] = j;
			index++; 
		  }
		}
	  }
  
  if(lep->num_leptons > 2)
	if(lepton_pt_good(lep, minpt1, maxpt1, minpt2, maxpt2))
	  for (int i = 0; i < lep->num_leptons; i++) 
		for (int j = i+1; j < lep->num_leptons; j++) 
		  for (int k = j+1; k < lep->num_leptons; k++) 
			if((lep->charge[i]*lep->charge[j])>0 && (lep->charge[i]*lep->charge[k])>0){
			  lep->has_3lss = true;
			  lep->has_3lss_index0 = i; // lepton index NOT Ntp index
			  lep->has_3lss_index1 = j;
			  lep->has_3lss_index2 = k;
			}


  if(lep->has_ss )
	{
	  lep->has_2lss_index0 = ind_ss[0];
	  lep->has_2lss_index1 = ind_ss[1];

	  if(lep->is_electron[ind_ss[0]] && lep->is_electron[ind_ss[1]])
		lep->has_ee = true;
	  else if( (lep->is_electron[ind_ss[0]] && !lep->is_electron[ind_ss[1]]) || (!lep->is_electron[ind_ss[0]] && lep->is_electron[ind_ss[1]]) )
		lep->has_em = true;
	  else 	  if(!lep->is_electron[ind_ss[0]] && !lep->is_electron[ind_ss[1]])
		lep->has_mm = true;
	}
  else if ( lep->num_leptons == 2 ) // TO BE REVISED??
	{
	  lep->has_2lss_index0 = 0;
	  lep->has_2lss_index1 = 1;

	  if(lep->is_electron[0] && lep->is_electron[1]){
		lep->has_ee = true;
	  }
	  else 	  if( (lep->is_electron[0] && !lep->is_electron[1]) || (!lep->is_electron[0] && lep->is_electron[1]) )
		lep->has_em = true;
	  else 	  if(!lep->is_electron[0] && !lep->is_electron[1])
		lep->has_mm = true;
	}

  // 
  
  if (lep->num_leptons == 2 && lep->charge[0]*lep->charge[1]<0)
	lep->has_os = true;
  
  if(lep->has_os){
	if(lep->is_electron[0] && lep->is_electron[1])
	  lep->has_os_ee = true;
	else if ( (lep->is_electron[0] && !lep->is_electron[1]) || (!lep->is_electron[0] && lep->is_electron[1]) ) 
	  lep->has_os_em = true;
	else if (!lep->is_electron[0] && !lep->is_electron[1])
	  lep->has_os_mm = true;
  }


}

//------------------------------------------------------------------------
//				-= Other functions  =-
//------------------------------------------------------------------------

// to reject cosmic muons
//----------------------------------------------------------------------------
bool NoCosmicMuon(myevt *evt, my_leptons * lep) {

  bool nocosmicmuon = true;

  for (int lepi = 0; lepi < lep->num_leptons && nocosmicmuon; lepi++)
	if (!(lep->is_electron[lepi]))
	  {
		nocosmicmuon &= !(evt->Mu_isCosmic[lep->index[lepi]]);
	  }  
  return nocosmicmuon;
}

// calculate minimum mass between 2 leptons in an event
// -------------------------------------------------------------------------
double dilepton_mass(myevt *evt, my_leptons *lep) {
  if (lep->num_leptons < 2)
	return -9999.;
  lep->ind1_Mll = -1;
  lep->ind2_Mll = -1;
  float M;
  float min_M = 9999999999.;
  int num_lept = 0;
  TLorentzVector lep_tlv[4];
  for (int lepi = 0; lepi < lep->num_leptons && num_lept < 4; lepi++) {
	if (!lep->is_electron[lepi]) {//muons 
	  lep_tlv[num_lept].SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]],muon_mass);
	} else { //electrons 
	  lep_tlv[num_lept].SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
	}
	num_lept++;
  }
  if (num_lept >= 2) {
	for (int i = 0; i < num_lept; i++) {
	  for (int j = i + 1; j < num_lept; j++){
		TLorentzVector lep_sum = lep_tlv[i] + lep_tlv[j];
		M = (lep_sum).M();
		if (min_M > M){
		  min_M = M;
		  lep->ind1_Mll = i;
		  lep->ind2_Mll = j;

		}
	  }
	}
  }
  return min_M;
}

// calculate invariant mass between dilepton pairs
// ---------------------------------------------------------
void dilepton_mass_comb(myevt *evt, my_leptons *lep) {
  if (lep->num_leptons < 2)
	return;
  float M;
  //  float min_M = 9999999999.;
  int num_lept = 0;
  TLorentzVector lep_tlv[4];
  for (int lepi = 0; lepi < lep->num_leptons && num_lept < 4; lepi++) {
	if (!lep->is_electron[lepi]) {//muons 
	  lep_tlv[num_lept].SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]],muon_mass);
	} else { //electrons 
	  lep_tlv[num_lept].SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
	}
	num_lept++;
  }

  // m_ll[] count: 3 lep case = 0->12, 1->13, 2->23, ...
  int mll_count=0;
  if (num_lept >= 2) {
	for (int i = 0; i < num_lept; i++) {
	  for (int j = i + 1; j < num_lept; j++){
		TLorentzVector lep_sum = lep_tlv[i] + lep_tlv[j];
		M = (lep_sum).M();
		lep->m_ll[mll_count] = M;
		mll_count++;
	  }
	}
  }
  return;
}


double dilepton_mass_ss(myevt *evt, my_leptons *lep) {
  if (lep->num_leptons < 2)
	return -9999;
  float M;
  float min_M = 9999999999.;
  int num_lept = 0;
  TLorentzVector lep_tlv[4];
  for (int lepi = 0; lepi < lep->num_leptons && num_lept < 4; lepi++) {
	if (!lep->is_electron[lepi]) {//muons 
	  lep_tlv[num_lept].SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]],muon_mass);
	} else { //electrons 
	  lep_tlv[num_lept].SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
	}
	num_lept++;
  }

  if (num_lept >= 2) 
	for (int i = 0; i < num_lept; i++) 
	  for (int j = i + 1; j < num_lept; j++)
		if(lep->is_electron[i] == lep->is_electron[j] && lep->charge[i]*lep->charge[j]>0 ){
		  TLorentzVector lep_sum = lep_tlv[i] + lep_tlv[j];
		  M = (lep_sum).M();
		  if (min_M > M)
			min_M = M;
		}
	
  
  return min_M;
}

// calculate mass between 2 leading leptons in an event
// -------------------------------------------------------------------------
double dilepton_mass_lead(myevt *evt, my_leptons *lep) {
  if (lep->num_leptons < 2)
	return -9999.;
  float M=999;
  //  float min_M = 9999.;
  int num_lept = 0;
  TLorentzVector lep_tlv[4];
  for (int lepi = 0; lepi < lep->num_leptons && num_lept < 4; lepi++) {
	if (!lep->is_electron[lepi]) {//muons 
	  lep_tlv[num_lept].SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]],muon_mass);
	} else { //electrons 
	  lep_tlv[num_lept].SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
	}
	num_lept++;
  }
  if (num_lept >= 2) {
	//	for (int i = 0; i < num_lept; i++) {
	//	  for (int j = i + 1; j < num_lept; j++){
	TLorentzVector lep_sum = lep_tlv[0] + lep_tlv[1];
	M = (lep_sum).M();
	//		if (min_M > M)
	//		  min_M = M;
	//	  }
	//	}
  }
  return M;
}

// calculate mass between 3 leading leptons in an event
// -------------------------------------------------------------------------
double trilepton_mass_lead(myevt *evt, my_leptons *lep) {
  if (lep->num_leptons < 3)
	return -9999.;
  float M=999;
  //  float min_M = 9999.;
  int num_lept = 0;
  TLorentzVector lep_tlv[4];
  for (int lepi = 0; lepi < lep->num_leptons && num_lept < 4; lepi++) {
	if (!lep->is_electron[lepi]) {//muons 
	  lep_tlv[num_lept].SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]],muon_mass);
	} else { //electrons 
	  lep_tlv[num_lept].SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
	}
	num_lept++;
  }

  if (num_lept >= 3) {
	TLorentzVector lep_sum = lep_tlv[0] + lep_tlv[1] + lep_tlv[2];
	M = (lep_sum).M();
  }
  return M;
}

// calculate invariant mass of all leptons in the event
// -------------------------------------------------------------------------
double multilepton_mass(myevt *evt, my_leptons *lep) {
  if (lep->num_leptons < 2)
	return -9999.;
  float M;
  int num_lept = 0;
  TLorentzVector lep_tlv[10];
  for (int lepi = 0; lepi < lep->num_leptons && num_lept < 10; lepi++) {
	if (!lep->is_electron[lepi]) {//muons 
	  lep_tlv[num_lept].SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]],muon_mass);
	} else { //electrons 
	  lep_tlv[num_lept].SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
	}
	num_lept++;
  }

  TLorentzVector lep_sum;
  for (int i = 0; i < num_lept; i++) {
	lep_sum += lep_tlv[i];
  }
  M = (lep_sum).M();
	  
  
  return M;
}


// calculate minimum mass between 2 jets in an event
// -------------------------------------------------------------------------
double dijet_mass(my_jets *jet) {
  if (jet->num_jets < 2)
	return -9999.;
  float M = -9999.;
  //  float min_M = 9999.;
  int num_jet = 0;
  TLorentzVector jet_tlv[50];
  for (int jeti = 0; jeti < jet->num_jets; jeti++) {
	//	std::cout << jet->pT[jeti] << " ";
	//	  jet_tlv[num_jet].SetPtEtaPhiE(evt->Jet_pT[jet->index[jeti]],evt->Jet_eta[jet->index[jeti]],evt->Jet_phi[jet->index[jeti]],evt->Jet_E[jet->index[jeti]]);
	jet_tlv[num_jet].SetPtEtaPhiE(jet->pT[jeti],jet->eta[jeti],jet->phi[jeti],jet->E[jeti]);
	num_jet++;
  }
  //  std::cout << std::endl;

  if (num_jet >= 2) {
	/*	
		for (int i = 0; i < num_jet; i++) {
		for (int j = i + 1; j < num_jet; j++){
		TLorentzVector jet_sum = jet_tlv[i] + jet_tlv[j];
		M = (jet_sum).M();
		if (min_M > M)
		min_M = M;
		}
		}
	*/

	//	  std::cout << "first two jets: " << jet->pT[0]  << " " <<  jet->pT[1] ;
	TLorentzVector jet_sum = jet_tlv[0] + jet_tlv[1];
	M = (jet_sum).M();
	//	  std::cout << " " << M << std::endl;
  }
  //  return min_M;
  return M;
}

// calculate dilepton mass of leading leptons
// -------------------------------------------------------------------------
double leading_dilepton_mass(myevt *evt, my_leptons *lep) {
  if (lep->num_leptons < 2)
	return -9999.;
  float M;
  int num_lept = 0;
  TLorentzVector lep_tlv[3];
  for (int lepi = 0; lepi < 2; lepi++) {
	if (!lep->is_electron[lepi]) {//muons 
	  lep_tlv[num_lept].SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]],muon_mass);
	} else { //electrons 
	  lep_tlv[num_lept].SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
	}
	num_lept++;
  }

  TLorentzVector lep_sum = lep_tlv[0] + lep_tlv[1];
  M = (lep_sum).M();

  return M;
}



// Can be used to select different pt cuts for signal leptons
// -------------------------------------------------------------------------
bool lepton_pt_good(my_leptons *lep, float minpt1, float maxpt1,float minpt2, float maxpt2) {

  bool good_pt = false;
  minpt1*=1000;
  maxpt1*=1000;
  minpt2*=1000;
  maxpt2*=1000;

  bool check = (minpt1>=maxpt1 || minpt2>=maxpt2 || minpt2>=maxpt1);
  //  std::cout << "\n-> " << minpt1<< " " << maxpt1 << " " <<  minpt2<< " " << maxpt2 << " " << minpt2<< " " << maxpt1 << "<- " << check << std::endl;

  //  if(minpt1>=maxpt1 || minpt2>=maxpt2 || minpt2>=maxpt1)
  if(check)
	return good_pt; // false

  //  std::cout << "\n-> " <<  minpt1 << " < " << lep->pT[0] << " < " << maxpt1 << " // " << minpt2 << "<" << lep->pT[1] << "<" << maxpt2 << std::endl;
  // after baseline selection, should be sorted in pT
  if(lep->num_leptons>1)
	good_pt = (( minpt1 < lep->pT[0] && lep->pT[0] < maxpt1) && ( minpt2 < lep->pT[1] && lep->pT[1] < maxpt2));
  /*  if(lep->num_leptons>2)
	  good_pt = (lep->pT[0] > LeptPt && lep->pT[1] > LeptPt && lep->pT[2] > LeptPt);*/
  return good_pt;
}

// Transverse mass calculated from leading lepton and MET
// -------------------------------------------------------------------------
double transverse_mass(myevt *evt, my_leptons *lep) {

  TLorentzVector P_lep1;

  int i = -1; //Only the first lepton is taken into account

  for (int j = 0; j < lep->num_leptons && i == -1; j++) { 
	if (lep->pT[j] > LeptPt)
	  i = j;
  }

  if (i == -1)
	return -9999.;

  if (!lep->is_electron[i]) {//muons
	P_lep1.SetPtEtaPhiM(evt->Mu_pT[lep->index[i]],evt->Mu_eta[lep->index[i]],evt->Mu_phi[lep->index[i]],muon_mass);
  } else { //electrons 
	P_lep1.SetPtEtaPhiE(evt->El_pT[lep->index[i]],evt->El_eta[lep->index[i]],evt->El_phi[lep->index[i]],evt->El_E[lep->index[i]]);
  }

  //miss-Et variables
  float mis_Ex = evt->Etmiss_TST_Etx;
  float mis_Ey = evt->Etmiss_TST_Ety;
  float met = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);

  TLorentzVector P_M(mis_Ex, mis_Ey, 0, met);

  float DeltaPhi_lep1_M = (P_lep1).DeltaPhi(P_M);
  float Mt_lep1_M = sqrt(2 * lep->pT[i] * met * (1 - cos(DeltaPhi_lep1_M)));

  return Mt_lep1_M;

}

// Minimum Transverse mass calculated from any of the leptons and MET
// -------------------------------------------------------------------------
double transverse_mass_min(myevt *evt, my_leptons *lep) {

  TLorentzVector P_lep1;
  TLorentzVector P_lep2;
  double lowest_mT = -1;

  //  int i = -1; //Only the first lepton is taken into account
  /*
	for (int j = 0; j < lep->num_leptons && i == -1; j++) { 
	if (lep->pT[j] > LeptPt)
	i = j;
	}

	if (i == -1)
	return -9999.;
  */
  if (lep->num_leptons < 2)
	return -9999.;

  if (!lep->is_electron[0]) {//muons
	P_lep1.SetPtEtaPhiM(evt->Mu_pT[lep->index[0]],evt->Mu_eta[lep->index[0]],evt->Mu_phi[lep->index[0]],muon_mass);
  } else { //electrons 
	P_lep1.SetPtEtaPhiE(evt->El_pT[lep->index[0]],evt->El_eta[lep->index[0]],evt->El_phi[lep->index[0]],evt->El_E[lep->index[0]]);
  }

  if (!lep->is_electron[1]) {//muons
	P_lep2.SetPtEtaPhiM(evt->Mu_pT[lep->index[1]],evt->Mu_eta[lep->index[1]],evt->Mu_phi[lep->index[1]],muon_mass);
  } else { //electrons 
	P_lep2.SetPtEtaPhiE(evt->El_pT[lep->index[1]],evt->El_eta[lep->index[1]],evt->El_phi[lep->index[1]],evt->El_E[lep->index[1]]);
  }

  //miss-Et variables
  float mis_Ex = evt->Etmiss_TST_Etx;
  float mis_Ey = evt->Etmiss_TST_Ety;
  float met = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);

  TLorentzVector P_M(mis_Ex, mis_Ey, 0, met);

  float DeltaPhi_lep1_M = (P_lep1).DeltaPhi(P_M);
  float Mt_lep1_M = sqrt(2 * lep->pT[0] * met * (1 - cos(DeltaPhi_lep1_M)));

  float DeltaPhi_lep2_M = (P_lep2).DeltaPhi(P_M);
  float Mt_lep2_M = sqrt(2 * lep->pT[1] * met * (1 - cos(DeltaPhi_lep2_M)));
  
  if (Mt_lep1_M < Mt_lep2_M) {
	lowest_mT = Mt_lep1_M;
  }
  else 
	lowest_mT = Mt_lep2_M;
	
  
  return lowest_mT;
  //  return Mt_lep1_M;

}

//Here we check if an event contains a Z-candidate
//----------------------------------------------------------------------------
void containsZ(myevt *evt, my_leptons *lep) {

  TLorentzVector P_lep0;
  TLorentzVector P_lep1;
  TLorentzVector P_lep2;

  lep->has_Z = false;
  lep->has_Z_SS = false;
  lep->has_Z_SS_ee = false;
  lep->has_Z_OS = false;
  lep->has_Z_OS_SR3L3b = false;
  lep->has_Z_lll = false;
  lep->ind1 = -1;
  lep->ind2 = -1;
  lep->MZ = -1;
  lep->lowest_M = -1;

  if (lep->num_leptons < 2)
	return;

  double best_M = -1;
  double M;

  int lept_count = 0;
  for (int i = 0; i < lep->num_leptons && lept_count < 5; i++) 
	lept_count++;
	

  for (int i = 0; i < lept_count ; i++) //Only the first five leptons are taken into account
	for (int j = i + 1; j < lept_count ; j++) //Only the first five leptons are taken into account
	  {

		if (lep->is_electron[i] == lep->is_electron[j] /*&& lep->charge[i] * lep->charge[j] < 0*/ ){ 
		  if (!lep->is_electron[i]) { //muons -----------------------------------------------------------
			P_lep1.SetPtEtaPhiM(evt->Mu_pT[lep->index[i]],evt->Mu_eta[lep->index[i]],evt->Mu_phi[lep->index[i]],muon_mass);
			P_lep2.SetPtEtaPhiM(evt->Mu_pT[lep->index[j]],evt->Mu_eta[lep->index[j]],evt->Mu_phi[lep->index[j]],muon_mass);
		  } else { //electrons -------------------------------------------------------------------------
			P_lep1.SetPtEtaPhiE(evt->El_pT[lep->index[i]],evt->El_eta[lep->index[i]],evt->El_phi[lep->index[i]],evt->El_E[lep->index[i]]);
			P_lep2.SetPtEtaPhiE(evt->El_pT[lep->index[j]],evt->El_eta[lep->index[j]],evt->El_phi[lep->index[j]],evt->El_E[lep->index[j]]);
		  }
		
		  TLorentzVector lep_sum = P_lep1 + P_lep2;
		  M = (lep_sum).M();


		  if (lep->lowest_M < 0) {
			lep->lowest_M = M;
		  }
			
		  if (M < lep->lowest_M) {
			lep->lowest_M = M;
		  }
			
		  if (best_M < 0) {
			best_M = M;
			lep->MZ = M;
			lep->ind1 = i;
			lep->ind2 = j;
		  }
		
		  // pick the pair closest to the Z mass if more than one Z	
		  if (fabs(M - 91000.) < fabs(best_M - 91000.)) {
			best_M = M;
			lep->MZ = M;
			lep->ind1 = i;
			lep->ind2 = j;
		  }

		  //		if (fabs(M - 91000.) < 7000.)
		  //		  if (M  < 101200. && M > 81200.){
		  if (M  < 101000. && M > 81000.){
			lep->has_Z = true;
			lep->MZ = M;
			//			lep->ind1 = i;
			//			lep->ind2 = j;

		  }
		  if (M  < 101200. && M > 81200. &&  lep->charge[i] * lep->charge[j] < 0){
			lep->MZ = M;
			lep->has_Z_OS_SR3L3b = true;
			//			lep->ind1 = i;
			//			lep->ind2 = j;

		  }
		  //		  if (M  < 101200. && M > 81200. &&  lep->charge[i] * lep->charge[j] < 0){
		  if (M  < 101000. && M > 81000. &&  lep->charge[i] * lep->charge[j] < 0){
			lep->MZ = M;
			lep->has_Z_OS = true;
			//			lep->ind1 = i;
			//			lep->ind2 = j;

		  }

		  //		  if (M  < 101200. && M > 81200. &&  lep->charge[i] * lep->charge[j] > 0){
		  if (M  < 101000. && M > 81000. &&  lep->charge[i] * lep->charge[j] > 0){
			lep->MZ = M;
			lep->has_Z_SS = true;
			if(lep->is_electron[i] && lep->is_electron[j])
			  lep->has_Z_SS_ee = true;
			//	  lep->ind1 = i;
			//		  lep->ind2 = j;

		  }
		}
	  }

  // Invariant mass of 3 leading leptons 
  if(lept_count > 2){  
	
	if(!lep->is_electron[0])
	  P_lep0.SetPtEtaPhiM(evt->Mu_pT[lep->index[0]],evt->Mu_eta[lep->index[0]],evt->Mu_phi[lep->index[0]],muon_mass);
	else
	  P_lep0.SetPtEtaPhiE(evt->El_pT[lep->index[0]],evt->El_eta[lep->index[0]],evt->El_phi[lep->index[0]],evt->El_E[lep->index[0]]);
	
	if(!lep->is_electron[1])
	  P_lep1.SetPtEtaPhiM(evt->Mu_pT[lep->index[1]],evt->Mu_eta[lep->index[1]],evt->Mu_phi[lep->index[1]],muon_mass);
	else
	  P_lep1.SetPtEtaPhiE(evt->El_pT[lep->index[1]],evt->El_eta[lep->index[1]],evt->El_phi[lep->index[1]],evt->El_E[lep->index[1]]);

	if(!lep->is_electron[2])
	  P_lep2.SetPtEtaPhiM(evt->Mu_pT[lep->index[2]],evt->Mu_eta[lep->index[2]],evt->Mu_phi[lep->index[2]],muon_mass);
	else
	  P_lep2.SetPtEtaPhiE(evt->El_pT[lep->index[2]],evt->El_eta[lep->index[2]],evt->El_phi[lep->index[2]],evt->El_E[lep->index[2]]);
	

	TLorentzVector lep_sum = P_lep0 + P_lep1 + P_lep2;
	M = (lep_sum).M();
	
	if (M  < 101200. && M > 81200.)
	  lep->has_Z_lll = true;
  }
  
}

//------------------------------------------------------------------------
//				-= Debugging Functions =-
//------------------------------------------------------------------------

void debug_printall(myevt *evt){

  cout << "------------------------------------------" << endl;
  cout << "debug::EventNumber: " << evt->EventNumber << endl;
  cout << evt->NJet << " jets" << endl;
  cout <<  setw(15) << left << "pt" <<  setw(15) << left << "eta" <<  setw(15) << left << "y" << setw(15) << left << "phi" << setw(15) << left << "E" << setw(15)  << "quality" << setw(15)  << "btag" << setw(15)  << "ntrk" << setw(15)  << left <<  "jvt" << setw(15)  << left << "passOR" << endl;
  for (int jeti = 0; jeti < evt->NJet ; jeti++)
	{
	  TLorentzVector vec;
	  vec.SetPtEtaPhiE(evt->Jet_pT[jeti],evt->Jet_eta[jeti],evt->Jet_phi[jeti],evt->Jet_E[jeti]);
	  float y = vec.Rapidity();
	  cout  << setw(15) << left << evt->Jet_pT[jeti]/1000. << setw(15) << left << evt->Jet_eta[jeti]  << setw(15) << left << y << setw(15) << left << evt->Jet_phi[jeti]  << setw(15)  <<  evt->Jet_E[jeti]/1000. << setw(15)<< evt->Jet_quality[jeti]   << setw(15) << left <<
		evt->Jet_MV2c20[jeti] << setw(15) << left << evt->Jet_nTrk[jeti] << setw(15) << left <<    evt->Jet_JVT[jeti]  << setw(15) << left << evt->Jet_passOR[jeti] << endl;
	}

  cout << evt->NEl << " electrons" << endl;
  cout <<  setw(15) << left <<"pt" << setw(15) << left << "eta" << setw(15) << left << "y"<< setw(15) << left << "phi" << setw(15) << left << "E" << setw(15) << left << "z0sinTheta"  << setw(15) << left << "sigd0" << setw(15) << left  << "d0" << setw(15) << left << "LooseLH" << setw(15) << left << "TightLH" <<  setw(15) << left << "charge" << setw(15)  << left << "passOR" << endl;
  for (int eli = 0; eli < evt->NEl; eli++)
	{
	  TLorentzVector vec2;
	  vec2.SetPtEtaPhiM(evt->El_pT[eli],evt->El_eta[eli],evt->El_phi[eli],electron_mass);
	  float theta  = vec2.Theta(); if(theta) {} // suppress warning 
	  float y2 = vec2.Rapidity();
	  cout  << setw(15) << left << evt->El_pT[eli]/1000. << setw(15) << left << evt->El_eta[eli] << setw(15) << left << y2 << setw(15) << left  << evt->El_phi[eli] << setw(15) << left << evt->El_E[eli]/1000. << setw(15) << left << evt->El_z0sinTheta[eli] << setw(15) << left << evt->El_sigd0[eli] << setw(15) << left <<  evt->El_d0pvtx[eli] << setw(15) << left << evt->El_isLooseAndBLayerLH[eli] << setw(15) << left << evt->El_isTightLH[eli] << setw(15) << left << evt->El_charge[eli] << setw(15) << left << evt->El_passOR[eli] << endl;
	}

  cout << evt->NMu << " muons" << endl;
  cout <<  setw(15) << left <<"pt" <<  setw(15) << left << "eta" <<  setw(15) << left << "phi" << setw(15) << left << "z0sinTheta" << setw(15) << left << "sigd0"<< setw(15) << left << "d0" << setw(15) << left << "isBad" << setw(15) << left << "isCosmic" << setw(15) << left << "IsoGrad" <<  setw(15) << left << "charge" << setw(15)  << left << "passOR" << endl;
  for (int mui = 0; mui < evt->NMu; mui++)
	{ 
	  TLorentzVector vec;
	  vec.SetPtEtaPhiM(evt->Mu_pT[mui],evt->Mu_eta[mui],evt->Mu_phi[mui],muon_mass);
	  float theta  = vec.Theta(); if(theta) {} // suppress warning
	  cout <<  setw(15) << left << evt->Mu_pT[mui]/1000. << setw(15) << left << evt->Mu_eta[mui] << setw(15) << left << evt->Mu_phi[mui] << setw(15) << left << evt->Mu_z0sinTheta[mui] << setw(15) << left << evt->Mu_sigd0[mui] << setw(15) << left << evt->Mu_d0pvtx[mui] << setw(15) << left << evt->Mu_isBad[mui] << setw(15) << left << evt->Mu_isCosmic[mui] << setw(15) << left <<  evt->Mu_passIsoGrad[mui] << setw(5) << left << evt->Mu_charge[mui]  << setw(15) << left << evt->Mu_passOR[mui] << endl;
	}

}

// print outs in the SR and VRs
void debug_objects(myevt *evt, my_leptons *lep, my_jets *jet, FILE* fp, bool record){
  int n_jets_50 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>50000)
	  n_jets_50++;

  int n_jets_25 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>25000)
	  n_jets_25++;

  int n_jets_40 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>40000)
	  n_jets_40++;
	
  bool el_eta137=true;
  for (int lepi = 0; lepi < 2; lepi++)
	if(lep->is_electron[lepi])
	  el_eta137 &= fabs(lep->eta[lepi])<1.37;

  //miss-Et variables
  float mis_Ex = evt->Etmiss_TST_Etx;
  float mis_Ey = evt->Etmiss_TST_Ety;
  float met = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);
  
  //effective mass and HT
  //-----------------------------------------------------------------------
  double meff = 0;
  double ht = 0;
  
  // leptons pt
  for (int i = 0; i < lep->num_leptons; i++) {
	meff += lep->pT[i];
  }

  // jets pt
  for (int i = 0; i < jet->num_jets; i++) {
	meff += jet->pT[i];
  }

  ht = meff;
  meff += met;

  if(record)
	fprintf(fp,"Debug Event %llu\n", evt->EventNumber);
  else
	printf("Debug Event %llu\n", evt->EventNumber);

  if(record)
	fprintf(fp,"nLep = %d, ", lep->num_leptons);
  else
	printf("nLep = %d, ", lep->num_leptons);

  for(int i =0; i<lep->num_leptons;i++){
	if(lep->is_electron[i]){
	  if(lep->charge[i]>=0){
		if(record)			
		  fprintf(fp,"el+ ");
		else
		  printf("el+ ");
	  } else{ 
		if(record)
		  fprintf(fp,"el- ");
		else
		  printf("el- ");
	  }
	}
	else {
	  if(lep->charge[i]>=0){
		if(record)
		  fprintf(fp,"mu+ ");
		else
		  printf("mu+ ");
	  }
	  else{ 
		if(record)
		  fprintf(fp,"mu- ");
		else
		  printf("mu- ");
	  }
	}
	if(record)
	  fprintf(fp,"pT = %.2f, ", lep->pT[i]/1000.);
	else
	  printf("pT = %.2f, ", lep->pT[i]/1000.);
  }
	 
  if(record)
	fprintf(fp,"MET = %.2f, meff = %.2f, HT = %.2f, nJet50 = %d, nJet40 = %d, nJet25 = %d, mjj = %.2f, mT = %.2f, !Mee = %d, pT(jet1) = %.2f, pT(jet2) = %.2f, el_eta = %d", met/1000., meff/1000., ht/1000., n_jets_50, n_jets_40, n_jets_25, dijet_mass(jet)/1000., transverse_mass(evt,lep)/1000., !lep->has_Z, jet->pT[0]/1000., jet->pT[1]/1000., el_eta137);			
  else
	printf("MET = %.2f, meff = %.2f, HT = %.2f, nJet50 = %d, nJet40 = %d, nJet25 = %d, mjj = %.2f, mT = %.2f, !Mee = %d, pT(jet1) = %.2f, pT(jet2) = %.2f, el_eta = %d", met/1000., meff/1000., ht/1000., n_jets_50, n_jets_40, n_jets_25, dijet_mass(jet)/1000., transverse_mass(evt,lep)/1000., !lep->has_Z, jet->pT[0]/1000., jet->pT[1]/1000., el_eta137);			

  if(record)
	fprintf(fp,", m12 = %.2f", lep->m_ll[0]/1000.);
  else
	printf(", m12 = %.2f", lep->m_ll[0]/1000.);

  if(lep->num_leptons==3){
	if(record){
	  fprintf(fp,", m13 = %.2f", lep->m_ll[1]/1000.);
	  fprintf(fp,", m23 = %.2f", lep->m_ll[2]/1000.);
	  fprintf(fp,", m123 = %.2f", trilepton_mass_lead(evt, lep)/1000.);
	}
	else {
	  printf(", m13 = %.2f", lep->m_ll[1]/1000.);
	  printf(", m23 = %.2f", lep->m_ll[2]/1000.);
	  printf(", m123 = %.2f", trilepton_mass_lead(evt, lep)/1000.);
	}

  }
  else if (lep->num_leptons==4){
	if(record){
	  fprintf(fp,", m13 = %.2f", lep->m_ll[1]/1000.);
	  fprintf(fp,", m14 = %.2f", lep->m_ll[2]/1000.);
	  fprintf(fp,", m23 = %.2f", lep->m_ll[3]/1000.);
	  fprintf(fp,", m24 = %.2f", lep->m_ll[4]/1000.);
	  fprintf(fp,", m34 = %.2f", lep->m_ll[5]/1000.);
	  fprintf(fp,", mALL = %.2f", multilepton_mass(evt, lep)/1000.);
	}
	else {
	  fprintf(fp,", m13 = %.2f", lep->m_ll[1]/1000.);
	  fprintf(fp,", m14 = %.2f", lep->m_ll[2]/1000.);
	  fprintf(fp,", m23 = %.2f", lep->m_ll[3]/1000.);
	  fprintf(fp,", m24 = %.2f", lep->m_ll[4]/1000.);
	  fprintf(fp,", m34 = %.2f", lep->m_ll[5]/1000.);
	  fprintf(fp,", mALL = %.2f", multilepton_mass(evt, lep)/1000.);
	}
  }
  if(record)
	fprintf(fp,"\n");
  else
	printf("\n");
}

// print outs in the SR and VRs
void debug_SR_VR(myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet, FILE* fp, bool record){
  int n_jets_50 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>50000)
	  n_jets_50++;

  int n_jets_25 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>25000)
	  n_jets_25++;

  int n_jets_35 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>35000)
	  n_jets_35++;

  int n_jets_40 = 0;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	if(jet->pT[jeti]>40000)
	  n_jets_40++;
	
  bool el_eta137=true;
  for (int lepi = 0; lepi < 2; lepi++)
	if(lep->is_electron[lepi])
	  el_eta137 &= fabs(lep->eta[lepi])<1.37;

  int n_bjets = bjet->num_jets;
	
  //miss-Et variables
  float mis_Ex = evt->Etmiss_TST_Etx;
  float mis_Ey = evt->Etmiss_TST_Ety;
  float met = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);
  
  //effective mass and HT
  //-----------------------------------------------------------------------
  double meff = 0;
  double ht = 0;
  
  // leptons pt
  for (int i = 0; i < lep->num_leptons; i++) {
	meff += lep->pT[i];
  }

  // jets pt
  for (int i = 0; i < jet->num_jets; i++) {
	meff += jet->pT[i];
  }

  ht = meff;
  meff += met;

  if(record)
	fprintf(fp,"runNr = %d, EventNumber->%llu, nSigLep = %d, nBaseLep = %d, ", evt->RunNb, evt->EventNumber, lep->num_leptons, lep->num_leptons_baseline);
  else
	printf("runNr = %d, EventNumber->%llu, nSigLep = %d, nBaseLep = %d, ", evt->RunNb, evt->EventNumber, lep->num_leptons, lep->num_leptons_baseline);

  for(int i =0; i<lep->num_leptons;i++){
	if(lep->is_electron[i]){
	  if(lep->charge[i]>=0){
		if(record)			
		  fprintf(fp,"el+ ");
		else
		  printf("el+ ");
	  } else{ 
		if(record)
		  fprintf(fp,"el- ");
		else
		  printf("el- ");
	  }
	}
	else {
	  if(lep->charge[i]>=0){
		if(record)
		  fprintf(fp,"mu+ ");
		else
		  printf("mu+ ");
	  }
	  else{ 
		if(record)
		  fprintf(fp,"mu- ");
		else
		  printf("mu- ");
	  }
	}
	if(record)
	  fprintf(fp,"pT = %.2f, ", lep->pT[i]/1000.);
	else
	  printf("pT = %.2f, ", lep->pT[i]/1000.);
  }
	 
  if(record)
	fprintf(fp,"MET = %.2f, meff = %.2f, HT = %.2f, nJet50 = %d, nJet40 = %d, nJet35 = %d, nJet25 = %d, nBJet20 = %d, mjj = %.2f, mT = %.2f, !Mee = %d, pT(jet1) = %.2f, pT(jet2) = %.2f, el_eta = %d", met/1000., meff/1000., ht/1000., n_jets_50, n_jets_40, n_jets_35, n_jets_25, n_bjets, dijet_mass(jet)/1000., transverse_mass(evt,lep)/1000., !lep->has_Z, jet->pT[0]/1000., jet->pT[1]/1000., el_eta137);			
  else
	printf("MET = %.2f, meff = %.2f, HT = %.2f, nJet50 = %d, nJet40 = %d, nJet35 = %d, nJet25 = %d, nBJet20 = %d, mjj = %.2f, mT = %.2f, !Mee = %d, pT(jet1) = %.2f, pT(jet2) = %.2f, el_eta = %d", met/1000., meff/1000., ht/1000., n_jets_50, n_jets_40, n_jets_35, n_jets_25, n_bjets, dijet_mass(jet)/1000., transverse_mass(evt,lep)/1000., !lep->has_Z, jet->pT[0]/1000., jet->pT[1]/1000., el_eta137);			

  if(record)
	fprintf(fp,", m12 = %.2f", lep->m_ll[0]/1000.);
  else
	printf(", m12 = %.2f", lep->m_ll[0]/1000.);

  if(lep->num_leptons==3){
	if(record){
	  fprintf(fp,", m13 = %.2f", lep->m_ll[1]/1000.);
	  fprintf(fp,", m23 = %.2f", lep->m_ll[2]/1000.);
	  fprintf(fp,", m123 = %.2f", trilepton_mass_lead(evt, lep)/1000.);
	}
	else {
	  printf(", m13 = %.2f", lep->m_ll[1]/1000.);
	  printf(", m23 = %.2f", lep->m_ll[2]/1000.);
	  printf(", m123 = %.2f", trilepton_mass_lead(evt, lep)/1000.);
	}

  }
  else if (lep->num_leptons==4){
	if(record){
	  fprintf(fp,", m13 = %.2f", lep->m_ll[1]/1000.);
	  fprintf(fp,", m14 = %.2f", lep->m_ll[2]/1000.);
	  fprintf(fp,", m23 = %.2f", lep->m_ll[3]/1000.);
	  fprintf(fp,", m24 = %.2f", lep->m_ll[4]/1000.);
	  fprintf(fp,", m34 = %.2f", lep->m_ll[5]/1000.);
	  fprintf(fp,", mALL = %.2f", multilepton_mass(evt, lep)/1000.);
	}
	else {
	  fprintf(fp,", m13 = %.2f", lep->m_ll[1]/1000.);
	  fprintf(fp,", m14 = %.2f", lep->m_ll[2]/1000.);
	  fprintf(fp,", m23 = %.2f", lep->m_ll[3]/1000.);
	  fprintf(fp,", m24 = %.2f", lep->m_ll[4]/1000.);
	  fprintf(fp,", m34 = %.2f", lep->m_ll[5]/1000.);
	  fprintf(fp,", mALL = %.2f", multilepton_mass(evt, lep)/1000.);
	}
  }
  if(record)
	fprintf(fp,"\n");
  else
	printf("\n");
}

// pass in a jet collection to show its information
void debug_jet(myevt *evt, my_jets *jet){
  cout << "------------------------------------------" << endl;
  cout << "debug evt=" << evt->EventNumber<< " with jets=" << jet->num_jets << endl;

  cout <<  setw(15) << left << "pt" <<  setw(15) << left << "eta" <<  setw(15) << left << "y" << setw(15) << left << "phi" << setw(15) << left << "E" << setw(15)  << "quality" << setw(15)  << "btag" << setw(15)  << "ntrk" << setw(15)  << left <<  "jvt" << setw(15)  << left << "passOR" << endl;
  for (int jeti = 0; jeti < jet->num_jets; jeti++)
	{
	  TLorentzVector vec;
	  vec.SetPtEtaPhiE(evt->Jet_pT[jet->index[jeti]],evt->Jet_eta[jet->index[jeti]],evt->Jet_phi[jet->index[jeti]],evt->Jet_E[jet->index[jeti]]);
	  float y = vec.Rapidity();
	  cout  << setw(15) << left << evt->Jet_pT[jet->index[jeti]]/1000. << setw(15) << left << evt->Jet_eta[jet->index[jeti]]  << setw(15) << left << y << setw(15) << left << evt->Jet_phi[jet->index[jeti]]  << setw(15)  <<  evt->Jet_E[jet->index[jeti]]/1000. << setw(15)<< evt->Jet_quality[jet->index[jeti]]   << setw(15) << left <<
		evt->Jet_MV2c20[jet->index[jeti]] << setw(15) << left << evt->Jet_nTrk[jet->index[jeti]] << setw(15) << left <<    evt->Jet_JVT[jet->index[jeti]]  << setw(15) << left << evt->Jet_passOR[jet->index[jeti]] << endl;
	}


}

// pass in a lepton collection to show its information
void debug_lept(myevt *evt, my_leptons *lep){
  cout << "------------------------------------------" << endl;
  cout << "debug evt=" << evt->EventNumber<< " with leptons=" << lep->num_leptons << endl;
  for (int lepi = 0; lepi < lep->num_leptons; lepi++){
	if(lep->is_electron[lepi]){
	  TLorentzVector vec;
	  vec.SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
	  float theta  = vec.Theta(); if(theta) {} // suppress warning
	  float yi = vec.Rapidity(); 
	  cout  << "el pt=" << setw(15) << left << evt->El_pT[lep->index[lepi]]/1000. << "eta=" << setw(15) << left << evt->El_eta[lep->index[lepi]] << "y=" << setw(15) << left << yi << "phi=" << setw(15) << left << evt->El_phi[lep->index[lepi]] << "E=" << setw(15) << left << evt->El_E[lep->index[lepi]]/1000. << "isTightLH=" << setw(15) << left << evt->El_isTightLH[lep->index[lepi]] << "ptvarcone20/pt" << setw(15) << left << evt->El_ptvarcone20[lep->index[lepi]]/evt->El_pT[lep->index[lepi]]  << "topoetcone20/pt=" << setw(15) << left << evt->El_topoetcone20[lep->index[lepi]]/evt->El_pT[lep->index[lepi]] << "z0SinTheta=" << setw(15) << left << evt->El_z0sinTheta[lep->index[lepi]] <<  "charge=" << setw(15) << left << evt->El_charge[lep->index[lepi]] 
			<<"passOR=" << setw(15) << left << evt->El_passOR[lep->index[lepi]]
			<< endl;}
	if(!lep->is_electron[lepi]){ 
	  TLorentzVector vec;
	  vec.SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]], muon_mass);
	  float yi = vec.Rapidity(); 
	  cout << "mu pt=" << setw(15) << left << evt->Mu_pT[lep->index[lepi]]/1000. << "eta=" << setw(15) << left << evt->Mu_eta[lep->index[lepi]] << "y=" <<  setw(15) << left << yi << "phi=" << setw(15) << left << evt->Mu_phi[lep->index[lepi]] << "ptvarcone30/pt=" << setw(15) << left << evt->Mu_ptvarcone30[lep->index[lepi]]/evt->Mu_pT[lep->index[lepi]] << "d0=" << setw(15) << left << evt->Mu_d0pvtx[lep->index[lepi]] << "z0sintheta=" << setw(15) << left << evt->Mu_z0sinTheta[lep->index[lepi]] << "isBad=" << setw(15) << left << evt->Mu_isBad[lep->index[lepi]]<< "isCosmic=" << setw(15) << left << evt->Mu_isCosmic[lep->index[lepi]] <<"charge=" << setw(15) << left << evt->Mu_charge[lep->index[lepi]] 
		   <<"passOR=" << setw(15) << left << evt->Mu_passOR[lep->index[lepi]]
		   << endl;
	}
  }
  cout << "------------------------------------------" << endl;
}

// pass in a lepton collection to show its information
void debug_truth_lept(myevt *evt, my_leptons *lep){
  cout << "------------------------------------------" << endl;
  cout << "debug evt=" << evt->EventNumber<< " with leptons=" << lep->num_leptons << endl;
  for (int lepi = 0; lepi < lep->num_leptons; lepi++){
	if(lep->is_electron[lepi]){
	  TLorentzVector vec;
	  vec.SetPtEtaPhiE(evt->El_pT[lep->index[lepi]],evt->El_eta[lep->index[lepi]],evt->El_phi[lep->index[lepi]],evt->El_E[lep->index[lepi]]);
	  float theta  = vec.Theta(); if(theta) {} // suppress warning
	  //      float yi = vec.Rapidity(); 
	  cout  << "el pt=" << setw(15) << left << evt->El_pT[lep->index[lepi]]/1000. << "eta=" << setw(15) << left << evt->El_eta[lep->index[lepi]] <<  "charge=" << setw(15) << left << evt->El_charge[lep->index[lepi]] << "tT=" << setw(15) << left << evt->El_truthType[lep->index[lepi]] << "tO=" << setw(15) << left << evt->El_truthOrigin[lep->index[lepi]] << "bkgtT=" << setw(15) << left << evt->El_bkgTruthType[lep->index[lepi]] << "bkgtO=" << setw(15) << left << evt->El_bkgTruthOrigin[lep->index[lepi]] << "1EgtT=" << setw(15) << left << evt->El_firstEgMotherTruthType[lep->index[lepi]] << "1EgtO=" << setw(15) << left << evt->El_firstEgMotherTruthOrigin[lep->index[lepi]] << "1EgPdgId=" << setw(15) << left << evt->El_firstEgMotherPdgId[lep->index[lepi]] << endl;}
	if(!lep->is_electron[lepi]){ 
	  TLorentzVector vec;
	  vec.SetPtEtaPhiM(evt->Mu_pT[lep->index[lepi]],evt->Mu_eta[lep->index[lepi]],evt->Mu_phi[lep->index[lepi]], muon_mass);
	  //      float yi = vec.Rapidity(); 
	  cout << "mu pt=" << setw(15) << left << evt->Mu_pT[lep->index[lepi]]/1000. << "eta=" << setw(15) << left << evt->Mu_eta[lep->index[lepi]] <<"charge=" << setw(15) << left << evt->Mu_charge[lep->index[lepi]] << "tT=" << setw(15) << left << evt->Mu_type[lep->index[lepi]] << "tO=" << setw(15) << left << evt->Mu_origin[lep->index[lepi]] << endl;}
  }
  cout << "------------------------------------------" << endl;
}


// For cutflow
// For Analyzer
const char* cut_name[28] = {
  "All events",
  "GRL",
  "Primary Vertex",
  "Trigger",
  "Global flags ",
  "Bad muon",
  ">=1 jet pass jet OR ",
  "Bad jet",
  ">=1 signal jet",
  "Cosmic veto",
  ">= 2 baseline leptons (10 GeV)",
  ">= 2 signal leptons (20 GeV)",
  "Same sign",
  // El-El channel                                                                                                     
  "Channel separation, same-sign [20, 20]",
  "Trigger Matching",
  ">= 1 bjet > 20 GeV",
  ">= 4 jets > 50 GeV",
  "MET > 125 GeV",

  // El-Mu channel                                                                                                                        
  "Channel separation, same-sign [20, 20]",
  "Trigger Matching",
  ">= 1 bjet > 20 GeV",
  ">= 4 jets > 50 GeV",
  "MET > 125 GeV",

  // Mu-Mu channel                                                          
  "Channel separation, same-sign [20, 20]",
  "Trigger Matching",
  ">= 1 bjet > 20 GeV",
  ">= 4 jets > 50 GeV",
  "MET > 125 GeV",
};

bool is_CF_source(myevt *evt){
  bool is_CF = false;
  if (evt->ChannelNumber ==361068 || evt->ChannelNumber ==361077 || evt->ChannelNumber ==410000 || evt->ChannelNumber ==410003 || evt->ChannelNumber ==410004 || evt->ChannelNumber ==410006 || evt->ChannelNumber ==410001 || evt->ChannelNumber ==410002 || evt->ChannelNumber ==410021 || evt->ChannelNumber ==410022 || evt->ChannelNumber ==410023 || evt->ChannelNumber ==410011 || evt->ChannelNumber ==410012 || evt->ChannelNumber ==410013 || evt->ChannelNumber ==410014 || evt->ChannelNumber ==410015 || evt->ChannelNumber ==410016 || evt->ChannelNumber ==361100 || evt->ChannelNumber ==361101 || evt->ChannelNumber ==361102 || evt->ChannelNumber ==361103 || evt->ChannelNumber ==361104 || evt->ChannelNumber ==361105 || evt->ChannelNumber ==361300 || evt->ChannelNumber ==361301 || evt->ChannelNumber ==361302 || evt->ChannelNumber ==361303 || evt->ChannelNumber ==361304 || evt->ChannelNumber ==361305 || evt->ChannelNumber ==361306 || evt->ChannelNumber ==361307 || evt->ChannelNumber ==361308 || evt->ChannelNumber ==361309 || evt->ChannelNumber ==361310 || evt->ChannelNumber ==361311 || evt->ChannelNumber ==361312 || evt->ChannelNumber ==361313 || evt->ChannelNumber ==361314 || evt->ChannelNumber ==361315 || evt->ChannelNumber ==361316 || evt->ChannelNumber ==361317 || evt->ChannelNumber ==361318 || evt->ChannelNumber ==361319 || evt->ChannelNumber ==361320 || evt->ChannelNumber ==361321 || evt->ChannelNumber ==361322 || evt->ChannelNumber ==361323 || evt->ChannelNumber ==361324 || evt->ChannelNumber ==361325 || evt->ChannelNumber ==361326 || evt->ChannelNumber ==361327 || evt->ChannelNumber ==361328 || evt->ChannelNumber ==361329 || evt->ChannelNumber ==361330 || evt->ChannelNumber ==361331 || evt->ChannelNumber ==361332 || evt->ChannelNumber ==361333 || evt->ChannelNumber ==361334 || evt->ChannelNumber ==361335 || evt->ChannelNumber ==361336 || evt->ChannelNumber ==361337 || evt->ChannelNumber ==361338 || evt->ChannelNumber ==361339 || evt->ChannelNumber ==361340 || evt->ChannelNumber ==361341 || evt->ChannelNumber ==361342 || evt->ChannelNumber ==361343 || evt->ChannelNumber ==361344 || evt->ChannelNumber ==361345 || evt->ChannelNumber ==361346 || evt->ChannelNumber ==361347 || evt->ChannelNumber ==361348 || evt->ChannelNumber ==361349 || evt->ChannelNumber ==361350 || evt->ChannelNumber ==361351 || evt->ChannelNumber ==361352 || evt->ChannelNumber ==361353 || evt->ChannelNumber ==361354 || evt->ChannelNumber ==361355 || evt->ChannelNumber ==361356 || evt->ChannelNumber ==361357 || evt->ChannelNumber ==361358 || evt->ChannelNumber ==361359 || evt->ChannelNumber ==361360 || evt->ChannelNumber ==361361 || evt->ChannelNumber ==361362 || evt->ChannelNumber ==361363 || evt->ChannelNumber ==361364 || evt->ChannelNumber ==361365 || evt->ChannelNumber ==361366 || evt->ChannelNumber ==361367 || evt->ChannelNumber ==361368 || evt->ChannelNumber ==361369 || evt->ChannelNumber ==361370 || evt->ChannelNumber ==361371 || evt->ChannelNumber ==361106 || evt->ChannelNumber ==361107 || evt->ChannelNumber ==361108 || evt->ChannelNumber ==361372 || evt->ChannelNumber ==361373 || evt->ChannelNumber ==361374 || evt->ChannelNumber ==361375 || evt->ChannelNumber ==361376 || evt->ChannelNumber ==361377 || evt->ChannelNumber ==361378 || evt->ChannelNumber ==361379 || evt->ChannelNumber ==361380 || evt->ChannelNumber ==361381 || evt->ChannelNumber ==361382 || evt->ChannelNumber ==361383 || evt->ChannelNumber ==361384 || evt->ChannelNumber ==361385 || evt->ChannelNumber ==361386 || evt->ChannelNumber ==361387 || evt->ChannelNumber ==361388 || evt->ChannelNumber ==361389 || evt->ChannelNumber ==361390 || evt->ChannelNumber ==361391 || evt->ChannelNumber ==361392 || evt->ChannelNumber ==361393 || evt->ChannelNumber ==361394 || evt->ChannelNumber ==361395 || evt->ChannelNumber ==361396 || evt->ChannelNumber ==361397 || evt->ChannelNumber ==361398 || evt->ChannelNumber ==361399 || evt->ChannelNumber ==361400 || evt->ChannelNumber ==361401 || evt->ChannelNumber ==361402 || evt->ChannelNumber ==361403 || evt->ChannelNumber ==361404 || evt->ChannelNumber ==361405 || evt->ChannelNumber ==361406 || evt->ChannelNumber ==361407 || evt->ChannelNumber ==361408 || evt->ChannelNumber ==361409 || evt->ChannelNumber ==361410 || evt->ChannelNumber ==361411 || evt->ChannelNumber ==361412 || evt->ChannelNumber ==361413 || evt->ChannelNumber ==361414 || evt->ChannelNumber ==361415 || evt->ChannelNumber ==361416 || evt->ChannelNumber ==361417 || evt->ChannelNumber ==361418 || evt->ChannelNumber ==361419 || evt->ChannelNumber ==361420 || evt->ChannelNumber ==361421 || evt->ChannelNumber ==361422 || evt->ChannelNumber ==361423 || evt->ChannelNumber ==361424 || evt->ChannelNumber ==361425 || evt->ChannelNumber ==361426 || evt->ChannelNumber ==361427 || evt->ChannelNumber ==361428 || evt->ChannelNumber ==361429 || evt->ChannelNumber ==361430 || evt->ChannelNumber ==361431 || evt->ChannelNumber ==361432 || evt->ChannelNumber ==361433 || evt->ChannelNumber ==361434 || evt->ChannelNumber ==361435 || evt->ChannelNumber ==361436 || evt->ChannelNumber ==361437 || evt->ChannelNumber ==361438 || evt->ChannelNumber ==361439 || evt->ChannelNumber ==361440 || evt->ChannelNumber ==361441 || evt->ChannelNumber ==361442 || evt->ChannelNumber ==361443 || evt->ChannelNumber ==361444 || evt->ChannelNumber ==361445 || evt->ChannelNumber ==361446 || evt->ChannelNumber ==361447 || evt->ChannelNumber ==361448 || evt->ChannelNumber ==361449 || evt->ChannelNumber ==361450 || evt->ChannelNumber ==361451 || evt->ChannelNumber ==361452 || evt->ChannelNumber ==361453 || evt->ChannelNumber ==361454 || evt->ChannelNumber ==361455 || evt->ChannelNumber ==361456 || evt->ChannelNumber ==361457 || evt->ChannelNumber ==361458 || evt->ChannelNumber ==361459 || evt->ChannelNumber ==361460 || evt->ChannelNumber ==361461 || evt->ChannelNumber ==361462 || evt->ChannelNumber ==361463 || evt->ChannelNumber ==361464 || evt->ChannelNumber ==361465 || evt->ChannelNumber ==361466 || evt->ChannelNumber ==361467 || evt->ChannelNumber ==361468 || evt->ChannelNumber ==361469 || evt->ChannelNumber ==361470 || evt->ChannelNumber ==361471 || evt->ChannelNumber ==361472 || evt->ChannelNumber ==361473 || evt->ChannelNumber ==361474 || evt->ChannelNumber ==361475 || evt->ChannelNumber ==361476 || evt->ChannelNumber ==361477 || evt->ChannelNumber ==361478 || evt->ChannelNumber ==361479 || evt->ChannelNumber ==361480 || evt->ChannelNumber ==361481 || evt->ChannelNumber ==361482 || evt->ChannelNumber ==361483 || evt->ChannelNumber ==361484 || evt->ChannelNumber ==361485 || evt->ChannelNumber ==361486 || evt->ChannelNumber ==361487 || evt->ChannelNumber ==361488 || evt->ChannelNumber ==361489 || evt->ChannelNumber ==361490 || evt->ChannelNumber ==361491 || evt->ChannelNumber ==301535 || evt->ChannelNumber ==301536 || evt->ChannelNumber ==301890 || evt->ChannelNumber ==301891 || evt->ChannelNumber ==301892 || evt->ChannelNumber ==301893 || evt->ChannelNumber ==301894 || evt->ChannelNumber ==301895 || evt->ChannelNumber ==301896 || evt->ChannelNumber ==301897 || evt->ChannelNumber ==301898 || evt->ChannelNumber ==301899 || evt->ChannelNumber ==301900 || evt->ChannelNumber ==301901 || evt->ChannelNumber ==301902 || evt->ChannelNumber ==301903 || evt->ChannelNumber ==301904 || evt->ChannelNumber ==301905 || evt->ChannelNumber ==301906 || evt->ChannelNumber ==301907 || evt->ChannelNumber ==301908 || evt->ChannelNumber ==301909 || evt->ChannelNumber ==301910 || evt->ChannelNumber ==361500 || evt->ChannelNumber ==361501 || evt->ChannelNumber ==361502 || evt->ChannelNumber ==361503 || evt->ChannelNumber ==361504 || evt->ChannelNumber ==361505 || evt->ChannelNumber ==361506 || evt->ChannelNumber ==361507 || evt->ChannelNumber ==361508 || evt->ChannelNumber ==361509 || evt->ChannelNumber ==361510 || evt->ChannelNumber ==361511 || evt->ChannelNumber ==361512 || evt->ChannelNumber ==361513 || evt->ChannelNumber ==361514 || evt->ChannelNumber ==361628 || evt->ChannelNumber ==361629 || evt->ChannelNumber ==361630 || evt->ChannelNumber ==361631 || evt->ChannelNumber ==361632 || evt->ChannelNumber ==361633 || evt->ChannelNumber ==361634 || evt->ChannelNumber ==361635 || evt->ChannelNumber ==361636 || evt->ChannelNumber ==361637 || evt->ChannelNumber ==361638 || evt->ChannelNumber ==361639 || evt->ChannelNumber ==361640 || evt->ChannelNumber ==361641 || evt->ChannelNumber ==361642 || evt->ChannelNumber ==407009 || evt->ChannelNumber ==407010 || evt->ChannelNumber ==407011 || evt->ChannelNumber ==407012 || evt->ChannelNumber ==301528 || evt->ChannelNumber ==301529 || evt->ChannelNumber ==301530 || evt->ChannelNumber ==301531 || evt->ChannelNumber ==301532 || evt->ChannelNumber ==363388 || evt->ChannelNumber ==363389 || evt->ChannelNumber ==363390 || evt->ChannelNumber ==363391 || evt->ChannelNumber ==363392 || evt->ChannelNumber ==363393 || evt->ChannelNumber ==363394 || evt->ChannelNumber ==363395 || evt->ChannelNumber ==363396 || evt->ChannelNumber ==363397 || evt->ChannelNumber ==363398 || evt->ChannelNumber ==363399 || evt->ChannelNumber ==363400 || evt->ChannelNumber ==363401 || evt->ChannelNumber ==363402 || evt->ChannelNumber ==363403 || evt->ChannelNumber ==363404 || evt->ChannelNumber ==363405 || evt->ChannelNumber ==363406 || evt->ChannelNumber ==363407 || evt->ChannelNumber ==363408 || evt->ChannelNumber ==363409 || evt->ChannelNumber ==363410 || evt->ChannelNumber ==363411 || evt->ChannelNumber ==363364 || evt->ChannelNumber ==363365 || evt->ChannelNumber ==363366 || evt->ChannelNumber ==363367 || evt->ChannelNumber ==363368 || evt->ChannelNumber ==363369 || evt->ChannelNumber ==363370 || evt->ChannelNumber ==363371 || evt->ChannelNumber ==363372 || evt->ChannelNumber ==363373 || evt->ChannelNumber ==363374 || evt->ChannelNumber ==363375 || evt->ChannelNumber ==363376 || evt->ChannelNumber ==363377 || evt->ChannelNumber ==363378 || evt->ChannelNumber ==363379 || evt->ChannelNumber ==363380 || evt->ChannelNumber ==363381 || evt->ChannelNumber ==363382 || evt->ChannelNumber ==363383 || evt->ChannelNumber ==363384 || evt->ChannelNumber ==363385 || evt->ChannelNumber ==363386 || evt->ChannelNumber ==363387 || evt->ChannelNumber ==363123 || evt->ChannelNumber ==363124 || evt->ChannelNumber ==363125 || evt->ChannelNumber ==363126 || evt->ChannelNumber ==363127 || evt->ChannelNumber ==363128 || evt->ChannelNumber ==363129 || evt->ChannelNumber ==363130 || evt->ChannelNumber ==363131 || evt->ChannelNumber ==363132 || evt->ChannelNumber ==363133 || evt->ChannelNumber ==363134 || evt->ChannelNumber ==363135 || evt->ChannelNumber ==363136 || evt->ChannelNumber ==363137 || evt->ChannelNumber ==363138 || evt->ChannelNumber ==363139 || evt->ChannelNumber ==363140 || evt->ChannelNumber ==363141 || evt->ChannelNumber ==363142 || evt->ChannelNumber ==363143 || evt->ChannelNumber ==363144 || evt->ChannelNumber ==363145 || evt->ChannelNumber ==363146 || evt->ChannelNumber ==363725 || evt->ChannelNumber ==363726 || evt->ChannelNumber ==363727 || evt->ChannelNumber ==363728 || evt->ChannelNumber ==363729 || evt->ChannelNumber ==363730 || evt->ChannelNumber ==363731 || evt->ChannelNumber ==363732 || evt->ChannelNumber ==363733 || evt->ChannelNumber ==363734 || evt->ChannelNumber ==363735 || evt->ChannelNumber ==363736 || evt->ChannelNumber ==363737 || evt->ChannelNumber ==363738 || evt->ChannelNumber ==363739 || evt->ChannelNumber ==363740 || evt->ChannelNumber ==363741 || evt->ChannelNumber ==363742 || evt->ChannelNumber ==363743 || evt->ChannelNumber ==363744 || evt->ChannelNumber ==363745 || evt->ChannelNumber ==363746 || evt->ChannelNumber ==363747 || evt->ChannelNumber ==363748 || evt->ChannelNumber ==363147 || evt->ChannelNumber ==363148 || evt->ChannelNumber ==363149 || evt->ChannelNumber ==363150 || evt->ChannelNumber ==363151 || evt->ChannelNumber ==363152 || evt->ChannelNumber ==363153 || evt->ChannelNumber ==363154 || evt->ChannelNumber ==363155 || evt->ChannelNumber ==363156 || evt->ChannelNumber ==363157 || evt->ChannelNumber ==363158 || evt->ChannelNumber ==363159 || evt->ChannelNumber ==363160 || evt->ChannelNumber ==363161 || evt->ChannelNumber ==363162 || evt->ChannelNumber ==363163 || evt->ChannelNumber ==363164 || evt->ChannelNumber ==363165 || evt->ChannelNumber ==363166 || evt->ChannelNumber ==363167 || evt->ChannelNumber ==363168 || evt->ChannelNumber ==363169 || evt->ChannelNumber ==363170 || evt->ChannelNumber ==361500 || evt->ChannelNumber ==361501 || evt->ChannelNumber ==361502 || evt->ChannelNumber ==361503 || evt->ChannelNumber ==361504 || evt->ChannelNumber ==361505 || evt->ChannelNumber ==361506 || evt->ChannelNumber ==361507 || evt->ChannelNumber ==361508 || evt->ChannelNumber ==361509 || evt->ChannelNumber ==361510 || evt->ChannelNumber ==361511 || evt->ChannelNumber ==361512 || evt->ChannelNumber ==361513 || evt->ChannelNumber ==361514)
	is_CF = true;
  return is_CF;
}

bool is_FullSim(myevt *evt){
  bool IsFullSim = true;

  if (evt->ChannelNumber == 304014 || evt->ChannelNumber == 370188 || evt->ChannelNumber == 370194 || evt->ChannelNumber == 371200 || evt->ChannelNumber == 371201 || evt->ChannelNumber == 371202 || evt->ChannelNumber == 371203 || evt->ChannelNumber == 371204 || evt->ChannelNumber == 371205 || evt->ChannelNumber == 371206 || evt->ChannelNumber == 371207 || evt->ChannelNumber == 371209 || evt->ChannelNumber == 371210 || evt->ChannelNumber == 371211 || evt->ChannelNumber == 371212 || evt->ChannelNumber == 371213 || evt->ChannelNumber == 371214 || evt->ChannelNumber == 371215 || evt->ChannelNumber == 371216 || evt->ChannelNumber == 371217 || evt->ChannelNumber == 371218 || evt->ChannelNumber == 371219 || evt->ChannelNumber == 371220 || evt->ChannelNumber == 371221 || evt->ChannelNumber == 371222 || evt->ChannelNumber == 371223 || evt->ChannelNumber == 371224 || evt->ChannelNumber == 371225 || evt->ChannelNumber == 371227 || evt->ChannelNumber == 371228 || evt->ChannelNumber == 371229 || evt->ChannelNumber == 371230 || evt->ChannelNumber == 371231 || evt->ChannelNumber == 371232 || evt->ChannelNumber == 371233 || evt->ChannelNumber == 371234 || evt->ChannelNumber == 371235 || evt->ChannelNumber == 371236 || evt->ChannelNumber == 371237 || evt->ChannelNumber == 371238 || evt->ChannelNumber == 371239 || evt->ChannelNumber == 371240 || evt->ChannelNumber == 371241 || evt->ChannelNumber == 371243 || evt->ChannelNumber == 371244 || evt->ChannelNumber == 371245 || evt->ChannelNumber == 371246 || evt->ChannelNumber == 371247 || evt->ChannelNumber == 371248 || evt->ChannelNumber == 371250 || evt->ChannelNumber == 371251 || evt->ChannelNumber == 371252 || evt->ChannelNumber == 371253 || evt->ChannelNumber == 371254 || evt->ChannelNumber == 371256 || evt->ChannelNumber == 371257 || evt->ChannelNumber == 371258 || evt->ChannelNumber == 371259 || evt->ChannelNumber == 371260 || evt->ChannelNumber == 371261 || evt->ChannelNumber == 371262 || evt->ChannelNumber == 371263 || evt->ChannelNumber == 371264 || evt->ChannelNumber == 371265 || evt->ChannelNumber == 371266 || evt->ChannelNumber == 371267 || evt->ChannelNumber == 371268 || evt->ChannelNumber == 371269 || evt->ChannelNumber == 371270 || evt->ChannelNumber == 371271 || evt->ChannelNumber == 371272 || evt->ChannelNumber == 371273 || evt->ChannelNumber == 371274 || evt->ChannelNumber == 371275 || evt->ChannelNumber == 371276 || evt->ChannelNumber == 371277 || evt->ChannelNumber == 371278 || evt->ChannelNumber == 371279 || evt->ChannelNumber == 371280 || evt->ChannelNumber == 371281 || evt->ChannelNumber == 371282 || evt->ChannelNumber == 371283 || evt->ChannelNumber == 371284 || evt->ChannelNumber == 371285 || evt->ChannelNumber == 371286 || evt->ChannelNumber == 371287 || evt->ChannelNumber == 371288 || evt->ChannelNumber == 371289 || evt->ChannelNumber == 371290 || evt->ChannelNumber == 371291 || evt->ChannelNumber == 371292 || evt->ChannelNumber == 371293 || evt->ChannelNumber == 371294 || evt->ChannelNumber == 371295 || evt->ChannelNumber == 371296 || evt->ChannelNumber == 371297 || evt->ChannelNumber == 371298 || evt->ChannelNumber == 371299 || evt->ChannelNumber == 371300 || evt->ChannelNumber == 371301 || evt->ChannelNumber == 371302 || evt->ChannelNumber == 371303 || evt->ChannelNumber == 371304 || evt->ChannelNumber == 371305 || evt->ChannelNumber == 371306 || evt->ChannelNumber == 371307 || evt->ChannelNumber == 371308 || evt->ChannelNumber == 372300 || evt->ChannelNumber == 372301 || evt->ChannelNumber == 372302 || evt->ChannelNumber == 372303 || evt->ChannelNumber == 372304 || evt->ChannelNumber == 372305 || evt->ChannelNumber == 372306 || evt->ChannelNumber == 372307 || evt->ChannelNumber == 372308 || evt->ChannelNumber == 372309 || evt->ChannelNumber == 372310 || evt->ChannelNumber == 372311 || evt->ChannelNumber == 372312 || evt->ChannelNumber == 372313 || evt->ChannelNumber == 372314 || evt->ChannelNumber == 372315 || evt->ChannelNumber == 372316 || evt->ChannelNumber == 372317 || evt->ChannelNumber == 372318 || evt->ChannelNumber == 372319 || evt->ChannelNumber == 372320 || evt->ChannelNumber == 372321 || evt->ChannelNumber == 372322 || evt->ChannelNumber == 372323 || evt->ChannelNumber == 372324 || evt->ChannelNumber == 372325 || evt->ChannelNumber == 372326 || evt->ChannelNumber == 372327 || evt->ChannelNumber == 372328 || evt->ChannelNumber == 372329 || evt->ChannelNumber == 372330 || evt->ChannelNumber == 372331 || evt->ChannelNumber == 372332 || evt->ChannelNumber == 372333 || evt->ChannelNumber == 372334 || evt->ChannelNumber == 372335 || evt->ChannelNumber == 372336 || evt->ChannelNumber == 372337 || evt->ChannelNumber == 372338 || evt->ChannelNumber == 372339 || evt->ChannelNumber == 372340 || evt->ChannelNumber == 372341 || evt->ChannelNumber == 372342 || evt->ChannelNumber == 372343 || evt->ChannelNumber == 372344 || evt->ChannelNumber == 372345 || evt->ChannelNumber == 372346 || evt->ChannelNumber == 372347 || evt->ChannelNumber == 372348 || evt->ChannelNumber == 372349 || evt->ChannelNumber == 372350 || evt->ChannelNumber == 372351 || evt->ChannelNumber == 372352 || evt->ChannelNumber == 372353 || evt->ChannelNumber == 372354 || evt->ChannelNumber == 372355 || evt->ChannelNumber == 372356 || evt->ChannelNumber == 372357 || evt->ChannelNumber == 372358 || evt->ChannelNumber == 372359 || evt->ChannelNumber == 372360 || evt->ChannelNumber == 372361 || evt->ChannelNumber == 372362 || evt->ChannelNumber == 372363 || evt->ChannelNumber == 372364 || evt->ChannelNumber == 372365 || evt->ChannelNumber == 372367 || evt->ChannelNumber == 372368 || evt->ChannelNumber == 372450 || evt->ChannelNumber == 372451 || evt->ChannelNumber == 372452 || evt->ChannelNumber == 372453 || evt->ChannelNumber == 372454 || evt->ChannelNumber == 372455 || evt->ChannelNumber == 372456 || evt->ChannelNumber == 372457 || evt->ChannelNumber == 372458 || evt->ChannelNumber == 372459 || evt->ChannelNumber == 372460 || evt->ChannelNumber == 372461 || evt->ChannelNumber == 372462 || evt->ChannelNumber == 372463 || evt->ChannelNumber == 372465 || evt->ChannelNumber == 372466 || evt->ChannelNumber == 372467 || evt->ChannelNumber == 372468 || evt->ChannelNumber == 372469 || evt->ChannelNumber == 372470 || evt->ChannelNumber == 372471 || evt->ChannelNumber == 372472 || evt->ChannelNumber == 372473 || evt->ChannelNumber == 372474 || evt->ChannelNumber == 372475 || evt->ChannelNumber == 372476 || evt->ChannelNumber == 372477 || evt->ChannelNumber == 372478 || evt->ChannelNumber == 372479 || evt->ChannelNumber == 372480 || evt->ChannelNumber == 372481 || evt->ChannelNumber == 372482 || evt->ChannelNumber == 372483 || evt->ChannelNumber == 372484 || evt->ChannelNumber == 372485 || evt->ChannelNumber == 372486 || evt->ChannelNumber == 372487 || evt->ChannelNumber == 372488 || evt->ChannelNumber == 372489 || evt->ChannelNumber == 372490 || evt->ChannelNumber == 372491 || evt->ChannelNumber == 372492 || evt->ChannelNumber == 372493 || evt->ChannelNumber == 372494 || evt->ChannelNumber == 372495 || evt->ChannelNumber == 372496 || evt->ChannelNumber == 372497 || evt->ChannelNumber == 372498 || evt->ChannelNumber == 372499 || evt->ChannelNumber == 372500 || evt->ChannelNumber == 372501 || evt->ChannelNumber == 372502 || evt->ChannelNumber == 372503 || evt->ChannelNumber == 372504 || evt->ChannelNumber == 372505 || evt->ChannelNumber == 372506 || evt->ChannelNumber == 372507 || evt->ChannelNumber == 372508 || evt->ChannelNumber == 372510 || evt->ChannelNumber == 372511 || evt->ChannelNumber == 372512 || evt->ChannelNumber == 372513 || evt->ChannelNumber == 372514 || evt->ChannelNumber == 372515 || evt->ChannelNumber == 372516 || evt->ChannelNumber == 372517 || evt->ChannelNumber == 372518 || evt->ChannelNumber == 372519 || evt->ChannelNumber == 372520 || evt->ChannelNumber == 372521 || evt->ChannelNumber == 372522 || evt->ChannelNumber == 372523 || evt->ChannelNumber == 372524 || evt->ChannelNumber == 403380 || evt->ChannelNumber == 403381 || evt->ChannelNumber == 403382 || evt->ChannelNumber == 403383 || evt->ChannelNumber == 403384 || evt->ChannelNumber == 403385 || evt->ChannelNumber == 403386 || evt->ChannelNumber == 403387 || evt->ChannelNumber == 403388 || evt->ChannelNumber == 403389 || evt->ChannelNumber == 403391 || evt->ChannelNumber == 403392 || evt->ChannelNumber == 403393 || evt->ChannelNumber == 403394 || evt->ChannelNumber == 403395 || evt->ChannelNumber == 403396 || evt->ChannelNumber == 403397 || evt->ChannelNumber == 403398 || evt->ChannelNumber == 403399 || evt->ChannelNumber == 403400 || evt->ChannelNumber == 403401 || evt->ChannelNumber == 403402 || evt->ChannelNumber == 403403 || evt->ChannelNumber == 403405 || evt->ChannelNumber == 403406 || evt->ChannelNumber == 403407 || evt->ChannelNumber == 403408 || evt->ChannelNumber == 403409 || evt->ChannelNumber == 403410 || evt->ChannelNumber == 403411 || evt->ChannelNumber == 403412 || evt->ChannelNumber == 403413 || evt->ChannelNumber == 403414 || evt->ChannelNumber == 403415 || evt->ChannelNumber == 403416 || evt->ChannelNumber == 403417 || evt->ChannelNumber == 403418 || evt->ChannelNumber == 403419 || evt->ChannelNumber == 403420 || evt->ChannelNumber == 403421 || evt->ChannelNumber == 403422 || evt->ChannelNumber == 403423 || evt->ChannelNumber == 403424 || evt->ChannelNumber == 403425 || evt->ChannelNumber == 403426 || evt->ChannelNumber == 403427 || evt->ChannelNumber == 403428 || evt->ChannelNumber == 403429 || evt->ChannelNumber == 403430 || evt->ChannelNumber == 403431 || evt->ChannelNumber == 403432 || evt->ChannelNumber == 403433 || evt->ChannelNumber == 403434 || evt->ChannelNumber == 403435 || evt->ChannelNumber == 403436 || evt->ChannelNumber == 403437 || evt->ChannelNumber == 403438 || evt->ChannelNumber == 403439 || evt->ChannelNumber == 403440 || evt->ChannelNumber == 403441 || evt->ChannelNumber == 403442 || evt->ChannelNumber == 403443 || evt->ChannelNumber == 403444 || evt->ChannelNumber == 403445 || evt->ChannelNumber == 403446 || evt->ChannelNumber == 403447 || evt->ChannelNumber == 403448 || evt->ChannelNumber == 403449 || evt->ChannelNumber == 403450 || evt->ChannelNumber == 403452 || evt->ChannelNumber == 403453 || evt->ChannelNumber == 403454 || evt->ChannelNumber == 403455 || evt->ChannelNumber == 403456 || evt->ChannelNumber == 403457 || evt->ChannelNumber == 403458 || evt->ChannelNumber == 403459 || evt->ChannelNumber == 403460 || evt->ChannelNumber == 403461 || evt->ChannelNumber == 403462 || evt->ChannelNumber == 403463 || evt->ChannelNumber == 403464 || evt->ChannelNumber == 403465 || evt->ChannelNumber == 403466 || evt->ChannelNumber == 403467 || evt->ChannelNumber == 403468 || evt->ChannelNumber == 403469 || evt->ChannelNumber == 403470 || evt->ChannelNumber == 403471 || evt->ChannelNumber == 403472 || evt->ChannelNumber == 403473 || evt->ChannelNumber == 403474 || evt->ChannelNumber == 403475 || evt->ChannelNumber == 403476 || evt->ChannelNumber == 403477 || evt->ChannelNumber == 403478 || evt->ChannelNumber == 403479 || evt->ChannelNumber == 403480 || evt->ChannelNumber == 403481 || evt->ChannelNumber == 410011 || evt->ChannelNumber == 410012 || evt->ChannelNumber == 410013 || evt->ChannelNumber == 410014 || evt->ChannelNumber == 410022 || evt->ChannelNumber == 410023 || evt->ChannelNumber == 410142 || evt->ChannelNumber == 410144 || evt->ChannelNumber == 341177 || evt->ChannelNumber == 341270 || evt->ChannelNumber == 341271)
	IsFullSim = false;
  // if re.search("_a\d{3,4}_", dataset): isAtlfast = True  
  // ami list datasets mc15_13TeV.370122.MGPy8EG_A14N_GG_ttn1_1200_5000_855.merge.DAOD_SUSY2.e4049_s2608_r7772_r7676_p2879 --type DAOD_SUSY2 --fields events,version 
  return IsFullSim;
}
