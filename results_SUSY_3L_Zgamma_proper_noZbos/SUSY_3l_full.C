#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

#include "AtlasUtils.h"
#include "AtlasStyle.C"

#include "SUSY_3l_full.h"

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

// -----------------------------

distrAll* my_set;

//-----------------------------------------------------------------------------
void getData(distrAll& set, string tag, const char* syst_tag) {

	getData(set, tag, "", -1, -1, syst_tag);
	return;
}

//-----------------------------------------------------------------------------
// The "tag" is used to specified a systematic dataset
void getData(distrAll& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind, const char* syst_tag) {

	getData_Region(set.charge, "charge" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_Region(set.zbos, "zbos" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_Region(set.comb, "comb" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_Region(set.top, "top" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_Region(set.full, "full" + tag, signal_name, new_xsect, ind, syst_tag);

	string new_name = "expected_backgrounds" + tag + syst_tag;
	set.backgr_sum = new TH1D(new_name.data(), "expected backgrounds;final state;# of events", 6, 0, 6);
	set.backgr_sum->Sumw2();
	set.backgr_sum->GetXaxis()->FindBin("0e");
	set.backgr_sum->GetXaxis()->FindBin("1eOS");
	set.backgr_sum->GetXaxis()->FindBin("1eSS");
	set.backgr_sum->GetXaxis()->FindBin("2eOS");
	set.backgr_sum->GetXaxis()->FindBin("2eSS");
	set.backgr_sum->GetXaxis()->FindBin("3e");
	set.backgr_sum->ResetBit(TH1::kCanRebin);
	set.backgr_sum->SetMinimum(0.0);

	new_name = "observed_data" + tag + syst_tag;
	set.data_sum = new TH1D(new_name.data(), "observed data;final state;# of events", 6, 0, 6);
	//set.data_sum->Sumw2();
	set.data_sum->GetXaxis()->FindBin("0e");
	set.data_sum->GetXaxis()->FindBin("1eOS");
	set.data_sum->GetXaxis()->FindBin("1eSS");
	set.data_sum->GetXaxis()->FindBin("2eOS");
	set.data_sum->GetXaxis()->FindBin("2eSS");
	set.data_sum->GetXaxis()->FindBin("3e");
	set.data_sum->ResetBit(TH1::kCanRebin);
	set.data_sum->SetMinimum(0.0);

	return;
}

//-----------------------------------------------------------------------------
void getData_Region(distrRegion& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind,
		const char* syst_tag) {

	getData_FS(set.fs_3e, "3e_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_FS(set.fs_2eSS, "2eSS_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_FS(set.fs_2eOS, "2eOS_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_FS(set.fs_1eSS, "1eSS_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_FS(set.fs_1eOS, "1eOS_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_FS(set.fs_0e, "0e_" + tag, signal_name, new_xsect, ind, syst_tag);

	return;
}

//-----------------------------------------------------------------------------
void getData_FS(distrSet& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind,
		const char* syst_tag) {

	TH1D* num_of_evts_hist;

	memcpy(set.xsect, x_sect, N_SETS * sizeof(Double_t));

	if (ind > 0)
		set.xsect[ind] = new_xsect;

	set.int_lumi = lumi;

	set.syst_tag = syst_tag;

	const string files[N_SETS] = { "data_plots.root", "st_Wt_McAtNlo_Jimmy_plots.root", "alpgen_ttbar_plots.root",
			"AlpgenJimmyZmumu_plots.root", "AlpgenJimmyZee_plots.root", "AlpgenJimmyZmumubb_plots.root",
			"AlpgenJimmyZeebb_plots.root", "PythiaMadgraph_ttbarV_plots.root", "PythiaMadgraph_triboson_plots.root",
			"AlpgenJimmyWW_plots.root", "ZZ_Sherpa_plots.root", "WZ_Sherpa_plots.root" };

	for (int i = 0; i < N_SETS; i++) {
		set.file_name[i] = files[i];
		set.color[i] = 0;
		set.lineColor[i] = 1;
	}

	//specify the
	set.FR_lf_e = 1.;
	set.FR_hf_e = 1.;
	set.FR_lf_mu = 1.;
	set.FR_hf_mu = 1.;

	//Specify the colors
	set.color[1] = kGray + 2; //single top

	set.color[2] = TColor::GetColor("#00cc00"); //ttbar
	set.color[3] = kRed - 10; //Z->mumu
	set.color[4] = TColor::GetColor("#ff0000"); //Z->ee

	set.color[5] = TColor::GetColor("#ffff99"); //Z->mumu + bbbar
	set.color[6] = TColor::GetColor("#99ccff"); //Z->ee + bbbar

	set.color[7] = 38; //TColor::GetColor(38); //ttbar W
	set.color[8] = 29; //TColor::GetColor(29); //tbar Z

	//set.color[9] = TColor::GetColor(kGray + 2);
	//set.color[10] = TColor::GetColor(kGray + 3);
	//set.color[11] = TColor::GetColor(kGray + 4);

	set.color[10] = kOrange; //Z
	set.color[9] = kViolet; //WW
	set.color[11] = 0; //WZ

	if (strlen(signal_name) > 1 && ind > 0) {
		set.file_name[ind] = signal_name;
	}

	char temp_tag[256];
	TFile *f_data;

	for (int i = 0; i < N_SETS; i++) {

		f_data = new TFile(set.file_name[i].data(), "READ");

		num_of_evts_hist = (TH1D*) f_data->Get("num_of_evts");
		set.num_of_evts[i] = num_of_evts_hist->Integral();

		//muons
		std::sprintf(temp_tag, "mu1_pt_%s", tag.data());
		set.mu1_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu1_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu2_pt_%s", tag.data());
		set.mu2_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu2_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu3_pt_%s", tag.data());
		set.mu3_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu3_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu1_D0_%s", tag.data());
		set.mu1_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu1_D0[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu2_D0_%s", tag.data());
		set.mu2_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu2_D0[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu3_D0_%s", tag.data());
		set.mu3_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu3_D0[i]->SetDirectory(gROOT);

		/*
		 std::sprintf(temp_tag, "mu1_ptcone02_%s", tag.data());
		 set.mu1_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu1_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu2_ptcone02_%s", tag.data());
		 set.mu2_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu2_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu3_ptcone02_%s", tag.data());
		 set.mu3_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu3_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu1_ptcone03_%s", tag.data());
		 set.mu1_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu1_ptcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu2_ptcone03_%s", tag.data());
		 set.mu2_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu2_ptcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu3_ptcone03_%s", tag.data());
		 set.mu3_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu3_ptcone03[i]->SetDirectory(gROOT);
		 */

		std::sprintf(temp_tag, "mu1_etcone02_%s", tag.data());
		set.mu1_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu1_etcone02[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu2_etcone02_%s", tag.data());
		set.mu2_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu2_etcone02[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu3_etcone02_%s", tag.data());
		set.mu3_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu3_etcone02[i]->SetDirectory(gROOT);

		/*
		 std::sprintf(temp_tag, "mu1_etcone03_%s", tag.data());
		 set.mu1_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu1_etcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu2_etcone03_%s", tag.data());
		 set.mu2_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu2_etcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu3_etcone03_%s", tag.data());
		 set.mu3_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu3_etcone03[i]->SetDirectory(gROOT);
		 */

		std::sprintf(temp_tag, "mu1_D0sig_%s", tag.data());
		set.mu1_D0sig[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu1_D0sig[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu2_D0sig_%s", tag.data());
		set.mu2_D0sig[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu2_D0sig[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu3_D0sig_%s", tag.data());
		set.mu3_D0sig[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu3_D0sig[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu_eta_%s", tag.data());
		set.mu_eta[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu_eta[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu_phi_%s", tag.data());
		set.mu_phi[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu_phi[i]->SetDirectory(gROOT);

		//electrons
		std::sprintf(temp_tag, "el1_pt_%s", tag.data());
		set.el1_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.el1_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el2_pt_%s", tag.data());
		set.el2_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.el2_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el3_pt_%s", tag.data());
		set.el3_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.el3_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el1_D0_%s", tag.data());
		set.el1_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.el1_D0[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el2_D0_%s", tag.data());
		set.el2_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.el2_D0[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el3_D0_%s", tag.data());
		set.el3_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.el3_D0[i]->SetDirectory(gROOT);

		/*
		 std::sprintf(temp_tag, "el1_ptcone02_%s", tag.data());
		 set.el1_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el1_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el2_ptcone02_%s", tag.data());
		 set.el2_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el2_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el3_ptcone02_%s", tag.data());
		 set.el3_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el3_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el1_ptcone03_%s", tag.data());
		 set.el1_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el1_ptcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el2_ptcone03_%s", tag.data());
		 set.el2_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el2_ptcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el3_ptcone03_%s", tag.data());
		 set.el3_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el3_ptcone03[i]->SetDirectory(gROOT);
		 */

		std::sprintf(temp_tag, "el1_etcone02_%s", tag.data());
		set.el1_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.el1_etcone02[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el2_etcone02_%s", tag.data());
		set.el2_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.el2_etcone02[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el3_etcone02_%s", tag.data());
		set.el3_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.el3_etcone02[i]->SetDirectory(gROOT);

		/*
		 std::sprintf(temp_tag, "el1_etcone03_%s", tag.data());
		 set.el1_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el1_etcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el2_etcone03_%s", tag.data());
		 set.el2_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el2_etcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el3_etcone03_%s", tag.data());
		 set.el3_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el3_etcone03[i]->SetDirectory(gROOT);
		 */

		std::sprintf(temp_tag, "el1_isTight_%s", tag.data());
		set.el1_isTight[i] = (TH1D*) f_data->Get(temp_tag);
		set.el1_isTight[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el2_isTight_%s", tag.data());
		set.el2_isTight[i] = (TH1D*) f_data->Get(temp_tag);
		set.el2_isTight[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el3_isTight_%s", tag.data());
		set.el3_isTight[i] = (TH1D*) f_data->Get(temp_tag);
		set.el3_isTight[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el_eta_%s", tag.data());
		set.el_eta[i] = (TH1D*) f_data->Get(temp_tag);
		set.el_eta[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el_phi_%s", tag.data());
		set.el_phi[i] = (TH1D*) f_data->Get(temp_tag);
		set.el_phi[i]->SetDirectory(gROOT);

		//misc
		std::sprintf(temp_tag, "met_%s", tag.data());
		set.met[i] = (TH1D*) f_data->Get(temp_tag);
		set.met[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "metL_%s", tag.data());
		set.metL[i] = (TH1D*) f_data->Get(temp_tag);
		set.metL[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "MZ_%s", tag.data());
		set.MZ[i] = (TH1D*) f_data->Get(temp_tag);
		set.MZ[i]->SetDirectory(gROOT);

		//jets
		std::sprintf(temp_tag, "N_jets_%s", tag.data());
		set.N_jets[i] = (TH1D*) f_data->Get(temp_tag);
		set.N_jets[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "pt_jet1_%s", tag.data()); //This line gives an empty error-message.
		set.pt_jet1[i] = (TH1D*) f_data->Get(temp_tag);
		set.pt_jet1[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "pt_jet2_%s", tag.data());
		set.pt_jet2[i] = (TH1D*) f_data->Get(temp_tag);
		set.pt_jet2[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "pt_jet3_%s", tag.data());
		set.pt_jet3[i] = (TH1D*) f_data->Get(temp_tag);
		set.pt_jet3[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "pt_jet4_%s", tag.data());
		set.pt_jet4[i] = (TH1D*) f_data->Get(temp_tag);
		set.pt_jet4[i]->SetDirectory(gROOT);

		f_data->Close("R");

	}

	return;
}

//-----------------------------------------------------------------------------
void getData_SigRegion(distrSigRegion& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind,
		const char* syst_tag) {

	getData_SIG(set.fs_3e, "3e_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_SIG(set.fs_2eSS, "2eSS_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_SIG(set.fs_2eOS, "2eOS_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_SIG(set.fs_1eSS, "1eSS_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_SIG(set.fs_1eOS, "1eOS_" + tag, signal_name, new_xsect, ind, syst_tag);
	getData_SIG(set.fs_0e, "0e_" + tag, signal_name, new_xsect, ind, syst_tag);

	return;
}

//-----------------------------------------------------------------------------
void getData_SIG(distrSig& set, string tag, const char* signal_name, Double_t new_xsect, Int_t ind,
		const char* syst_tag) {

	TH1D* num_of_evts_hist;

	memcpy(set.xsect, x_sect_SIG, N_SIG * sizeof(Double_t));

	if (ind > 0)
		set.xsect[ind] = new_xsect;

	set.int_lumi = lumi;

	set.syst_tag = syst_tag;

	const string files[N_SIG] = { "sbottom_tchr_2lep_B500_C300_N150_plots.root",
			"simple_Gt_G900_T2500_L500_herwigpp_susy_plots.root" };

	for (int i = 0; i < N_SIG; i++) {
		set.file_name[i] = files[i];
		set.color[i] = 0;
		set.lineColor[i] = 1;
	}

	set.lineColor[0] = kMagenta; //kRed; //1 GeV LSP
	set.lineColor[1] = kBlue; //300 GeV LSP

	if (strlen(signal_name) > 1 && ind > 0) {
		set.file_name[ind] = signal_name;
	}

	char temp_tag[256];
	TFile *f_data;

	for (int i = 0; i < N_SIG; i++) {

		f_data = new TFile(set.file_name[i].data(), "READ");

		num_of_evts_hist = (TH1D*) f_data->Get("num_of_evts");
		set.num_of_evts[i] = num_of_evts_hist->Integral();

		//muons
		std::sprintf(temp_tag, "mu1_pt_%s", tag.data());
		set.mu1_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu1_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu2_pt_%s", tag.data());
		set.mu2_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu2_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu3_pt_%s", tag.data());
		set.mu3_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu3_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu1_D0_%s", tag.data());
		set.mu1_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu1_D0[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu2_D0_%s", tag.data());
		set.mu2_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu2_D0[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu3_D0_%s", tag.data());
		set.mu3_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu3_D0[i]->SetDirectory(gROOT);

		/*
		 std::sprintf(temp_tag, "mu1_ptcone02_%s", tag.data());
		 set.mu1_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu1_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu2_ptcone02_%s", tag.data());
		 set.mu2_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu2_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu3_ptcone02_%s", tag.data());
		 set.mu3_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu3_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu1_ptcone03_%s", tag.data());
		 set.mu1_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu1_ptcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu2_ptcone03_%s", tag.data());
		 set.mu2_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu2_ptcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu3_ptcone03_%s", tag.data());
		 set.mu3_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu3_ptcone03[i]->SetDirectory(gROOT);
		 */

		std::sprintf(temp_tag, "mu1_etcone02_%s", tag.data());
		set.mu1_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu1_etcone02[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu2_etcone02_%s", tag.data());
		set.mu2_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu2_etcone02[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu3_etcone02_%s", tag.data());
		set.mu3_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu3_etcone02[i]->SetDirectory(gROOT);

		/*
		 std::sprintf(temp_tag, "mu1_etcone03_%s", tag.data());
		 set.mu1_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu1_etcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu2_etcone03_%s", tag.data());
		 set.mu2_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu2_etcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "mu3_etcone03_%s", tag.data());
		 set.mu3_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.mu3_etcone03[i]->SetDirectory(gROOT);
		 */

		std::sprintf(temp_tag, "mu1_D0sig_%s", tag.data());
		set.mu1_D0sig[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu1_D0sig[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu2_D0sig_%s", tag.data());
		set.mu2_D0sig[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu2_D0sig[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu3_D0sig_%s", tag.data());
		set.mu3_D0sig[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu3_D0sig[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu_eta_%s", tag.data());
		set.mu_eta[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu_eta[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "mu_phi_%s", tag.data());
		set.mu_phi[i] = (TH1D*) f_data->Get(temp_tag);
		set.mu_phi[i]->SetDirectory(gROOT);

		//electrons
		std::sprintf(temp_tag, "el1_pt_%s", tag.data());
		set.el1_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.el1_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el2_pt_%s", tag.data());
		set.el2_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.el2_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el3_pt_%s", tag.data());
		set.el3_pt[i] = (TH1D*) f_data->Get(temp_tag);
		set.el3_pt[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el1_D0_%s", tag.data());
		set.el1_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.el1_D0[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el2_D0_%s", tag.data());
		set.el2_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.el2_D0[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el3_D0_%s", tag.data());
		set.el3_D0[i] = (TH1D*) f_data->Get(temp_tag);
		set.el3_D0[i]->SetDirectory(gROOT);

		/*
		 std::sprintf(temp_tag, "el1_ptcone02_%s", tag.data());
		 set.el1_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el1_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el2_ptcone02_%s", tag.data());
		 set.el2_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el2_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el3_ptcone02_%s", tag.data());
		 set.el3_ptcone02[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el3_ptcone02[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el1_ptcone03_%s", tag.data());
		 set.el1_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el1_ptcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el2_ptcone03_%s", tag.data());
		 set.el2_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el2_ptcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el3_ptcone03_%s", tag.data());
		 set.el3_ptcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el3_ptcone03[i]->SetDirectory(gROOT);
		 */

		std::sprintf(temp_tag, "el1_etcone02_%s", tag.data());
		set.el1_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.el1_etcone02[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el2_etcone02_%s", tag.data());
		set.el2_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.el2_etcone02[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el3_etcone02_%s", tag.data());
		set.el3_etcone02[i] = (TH1D*) f_data->Get(temp_tag);
		set.el3_etcone02[i]->SetDirectory(gROOT);

		/*
		 std::sprintf(temp_tag, "el1_etcone03_%s", tag.data());
		 set.el1_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el1_etcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el2_etcone03_%s", tag.data());
		 set.el2_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el2_etcone03[i]->SetDirectory(gROOT);

		 std::sprintf(temp_tag, "el3_etcone03_%s", tag.data());
		 set.el3_etcone03[i] = (TH1D*) f_data->Get(temp_tag);
		 set.el3_etcone03[i]->SetDirectory(gROOT);
		 */

		std::sprintf(temp_tag, "el1_isTight_%s", tag.data());
		set.el1_isTight[i] = (TH1D*) f_data->Get(temp_tag);
		set.el1_isTight[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el2_isTight_%s", tag.data());
		set.el2_isTight[i] = (TH1D*) f_data->Get(temp_tag);
		set.el2_isTight[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el3_isTight_%s", tag.data());
		set.el3_isTight[i] = (TH1D*) f_data->Get(temp_tag);
		set.el3_isTight[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el_eta_%s", tag.data());
		set.el_eta[i] = (TH1D*) f_data->Get(temp_tag);
		set.el_eta[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "el_phi_%s", tag.data());
		set.el_phi[i] = (TH1D*) f_data->Get(temp_tag);
		set.el_phi[i]->SetDirectory(gROOT);

		//misc
		std::sprintf(temp_tag, "met_%s", tag.data());
		set.met[i] = (TH1D*) f_data->Get(temp_tag);
		set.met[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "metL_%s", tag.data());
		set.metL[i] = (TH1D*) f_data->Get(temp_tag);
		set.metL[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "MZ_%s", tag.data());
		set.MZ[i] = (TH1D*) f_data->Get(temp_tag);
		set.MZ[i]->SetDirectory(gROOT);

		//jets
		std::sprintf(temp_tag, "N_jets_%s", tag.data());
		set.N_jets[i] = (TH1D*) f_data->Get(temp_tag);
		set.N_jets[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "pt_jet1_%s", tag.data()); //This line gives an empty error-message.
		set.pt_jet1[i] = (TH1D*) f_data->Get(temp_tag);
		set.pt_jet1[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "pt_jet2_%s", tag.data());
		set.pt_jet2[i] = (TH1D*) f_data->Get(temp_tag);
		set.pt_jet2[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "pt_jet3_%s", tag.data());
		set.pt_jet3[i] = (TH1D*) f_data->Get(temp_tag);
		set.pt_jet3[i]->SetDirectory(gROOT);

		std::sprintf(temp_tag, "pt_jet4_%s", tag.data());
		set.pt_jet4[i] = (TH1D*) f_data->Get(temp_tag);
		set.pt_jet4[i]->SetDirectory(gROOT);

		f_data->Close("R");

	}

	return;
}

//-----------------------------------------------------------------------------
void scaleXSect(distrAll& set, Int_t ind, Double_t sf) {

	scaleXSect_Region(set.charge, ind, sf);
	scaleXSect_Region(set.zbos, ind, sf);
	scaleXSect_Region(set.comb, ind, sf);
	scaleXSect_Region(set.top, ind, sf);
	scaleXSect_Region(set.full, ind, sf);

	return;
}

//-----------------------------------------------------------------------------
void scaleXSect_Region(distrRegion& set, Int_t ind, Double_t sf) {

	scaleXSect_FS(set.fs_3e, ind, sf);
	scaleXSect_FS(set.fs_2eSS, ind, sf);
	scaleXSect_FS(set.fs_2eOS, ind, sf);
	scaleXSect_FS(set.fs_1eSS, ind, sf);
	scaleXSect_FS(set.fs_1eOS, ind, sf);
	scaleXSect_FS(set.fs_0e, ind, sf);

	return;
}

//-----------------------------------------------------------------------------
void scaleXSect_FS(distrSet& set, Int_t ind, Double_t sf) {

	set.xsect[ind] *= sf;

	return;
}

//-----------------------------------------------------------------------------
void setFakeRates(distrAll& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4) {

	setFakeRates_Region(set.charge, sf1, sf2, sf3, sf4);
	setFakeRates_Region(set.zbos, sf1, sf2, sf3, sf4);
	setFakeRates_Region(set.comb, sf1, sf2, sf3, sf4);
	setFakeRates_Region(set.top, sf1, sf2, sf3, sf4);
	setFakeRates_Region(set.full, sf1, sf2, sf3, sf4);

	return;
}

//-----------------------------------------------------------------------------
void setFakeRates_Region(distrRegion& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4) {

	setFakeRates_FS(set.fs_3e, sf1, sf2, sf3, sf4);
	setFakeRates_FS(set.fs_2eSS, sf1, sf2, sf3, sf4);
	setFakeRates_FS(set.fs_2eOS, sf1, sf2, sf3, sf4);
	setFakeRates_FS(set.fs_1eSS, sf1, sf2, sf3, sf4);
	setFakeRates_FS(set.fs_1eOS, sf1, sf2, sf3, sf4);
	setFakeRates_FS(set.fs_0e, sf1, sf2, sf3, sf4);

	return;
}

//-----------------------------------------------------------------------------
void setFakeRates_FS(distrSet& set, Double_t sf1, Double_t sf2, Double_t sf3, Double_t sf4) {

	set.FR_lf_e = sf1;
	set.FR_lf_mu = sf2;
	set.FR_hf_e = sf3;
	set.FR_hf_mu = sf4;

	return;
}

//-----------------------------------------------------------------------------
void scaleLumi(distrAll& set, Double_t sf) {

	scaleLumi_Region(set.charge, sf);
	scaleLumi_Region(set.zbos, sf);
	scaleLumi_Region(set.comb, sf);
	scaleLumi_Region(set.top, sf);
	scaleLumi_Region(set.full, sf);

	return;
}

//-----------------------------------------------------------------------------
void scaleLumi_Region(distrRegion& set, Double_t sf) {

	scaleLumi_FS(set.fs_3e, sf);
	scaleLumi_FS(set.fs_2eSS, sf);
	scaleLumi_FS(set.fs_2eOS, sf);
	scaleLumi_FS(set.fs_1eSS, sf);
	scaleLumi_FS(set.fs_1eOS, sf);
	scaleLumi_FS(set.fs_0e, sf);

	return;
}

//-----------------------------------------------------------------------------
void scaleLumi_FS(distrSet& set, Double_t sf) {

	set.int_lumi *= sf;

	return;
}

//-----------------------------------------------------------------------------
void weightData(distrAll& set) {

	weightData_Region(set.charge);
	weightData_Region(set.zbos);
	weightData_Region(set.comb);
	weightData_Region(set.top);
	weightData_Region(set.full);

	//predictions
	int bin_0e = set.backgr_sum->GetXaxis()->FindBin("0e");
	int bin_1eOS = set.backgr_sum->GetXaxis()->FindBin("1eOS");
	int bin_1eSS = set.backgr_sum->GetXaxis()->FindBin("1eSS");
	int bin_2eOS = set.backgr_sum->GetXaxis()->FindBin("2eOS");
	int bin_2eSS = set.backgr_sum->GetXaxis()->FindBin("2eSS");
	int bin_3e = set.backgr_sum->GetXaxis()->FindBin("3e");

	set.backgr_sum->SetBinContent(bin_0e, getStackIntegral(set.full.fs_0e.ST_N_jets));
	set.backgr_sum->SetBinContent(bin_1eOS, getStackIntegral(set.full.fs_1eOS.ST_N_jets));
	set.backgr_sum->SetBinContent(bin_1eSS, getStackIntegral(set.full.fs_1eSS.ST_N_jets));
	set.backgr_sum->SetBinContent(bin_2eOS, getStackIntegral(set.full.fs_2eOS.ST_N_jets));
	set.backgr_sum->SetBinContent(bin_2eSS, getStackIntegral(set.full.fs_2eSS.ST_N_jets));
	set.backgr_sum->SetBinContent(bin_3e, getStackIntegral(set.full.fs_3e.ST_N_jets));

	set.backgr_sum->SetBinError(bin_0e, getStackError(set.full.fs_0e.ST_N_jets));
	set.backgr_sum->SetBinError(bin_1eOS, getStackError(set.full.fs_1eOS.ST_N_jets));
	set.backgr_sum->SetBinError(bin_1eSS, getStackError(set.full.fs_1eSS.ST_N_jets));
	set.backgr_sum->SetBinError(bin_2eOS, getStackError(set.full.fs_2eOS.ST_N_jets));
	set.backgr_sum->SetBinError(bin_2eSS, getStackError(set.full.fs_2eSS.ST_N_jets));
	set.backgr_sum->SetBinError(bin_3e, getStackError(set.full.fs_3e.ST_N_jets));

	//data
	bin_0e = set.data_sum->GetXaxis()->FindBin("0e");
	bin_1eOS = set.data_sum->GetXaxis()->FindBin("1eOS");
	bin_1eSS = set.data_sum->GetXaxis()->FindBin("1eSS");
	bin_2eOS = set.data_sum->GetXaxis()->FindBin("2eOS");
	bin_2eSS = set.data_sum->GetXaxis()->FindBin("2eSS");
	bin_3e = set.data_sum->GetXaxis()->FindBin("3e");

	set.data_sum->SetBinContent(bin_0e, getHistIntegral(set.full.fs_0e.N_jets[0]));
	set.data_sum->SetBinContent(bin_1eOS, getHistIntegral(set.full.fs_1eOS.N_jets[0]));
	set.data_sum->SetBinContent(bin_1eSS, getHistIntegral(set.full.fs_1eSS.N_jets[0]));
	set.data_sum->SetBinContent(bin_2eOS, getHistIntegral(set.full.fs_2eOS.N_jets[0]));
	set.data_sum->SetBinContent(bin_2eSS, getHistIntegral(set.full.fs_2eSS.N_jets[0]));
	set.data_sum->SetBinContent(bin_3e, getHistIntegral(set.full.fs_3e.N_jets[0]));

	return;
}

//-----------------------------------------------------------------------------
void weightData_Region(distrRegion& set) {

	weightData_FS(set.fs_3e);
	weightData_FS(set.fs_2eSS);
	weightData_FS(set.fs_2eOS);
	weightData_FS(set.fs_1eSS);
	weightData_FS(set.fs_1eOS);
	weightData_FS(set.fs_0e);

	TCanvas* plots1 = new TCanvas("c1", "c1", 50, 50, 200, 200);
	TPad* thePad = (TPad*) plots1->cd();
	thePad->SetLogy(0);

	buildStack(set.fs_3e);
	buildStack(set.fs_2eSS);
	buildStack(set.fs_2eOS);
	buildStack(set.fs_1eSS);
	buildStack(set.fs_1eOS);
	buildStack(set.fs_0e);

	//Now we can produce distributions for lepton-combined final states
	for (int i = 0; i < N_SETS; i++) {

		char new_name[256] = "";
		const char* old_name;
		int tmp_length;

		old_name = set.fs_3e.N_jets[i]->GetName();
		tmp_length = strlen(old_name) - strlen(strstr(old_name, "3e_"));
		memset(new_name, 0, 256 * sizeof(char));
		strncpy(new_name, old_name, tmp_length);
		strcat(new_name, (char*) (old_name + tmp_length + 3));

		set.N_jets[i] = (TH1D*) set.fs_3e.N_jets[i]->Clone(new_name);
		set.N_jets[i]->Add(set.fs_2eSS.N_jets[i]);
		set.N_jets[i]->Add(set.fs_2eOS.N_jets[i]);
		set.N_jets[i]->Add(set.fs_1eSS.N_jets[i]);
		set.N_jets[i]->Add(set.fs_1eOS.N_jets[i]);
		set.N_jets[i]->Add(set.fs_0e.N_jets[i]);

		// ----
		old_name = set.fs_3e.met[i]->GetName();
		tmp_length = strlen(old_name) - strlen(strstr(old_name, "3e_"));
		memset(new_name, 0, 256 * sizeof(char));
		strncpy(new_name, old_name, tmp_length);
		strcat(new_name, (char*) (old_name + tmp_length + 3));

		set.met[i] = (TH1D*) set.fs_3e.met[i]->Clone(new_name);
		set.met[i]->Add(set.fs_2eSS.met[i]);
		set.met[i]->Add(set.fs_2eOS.met[i]);
		set.met[i]->Add(set.fs_1eSS.met[i]);
		set.met[i]->Add(set.fs_1eOS.met[i]);
		set.met[i]->Add(set.fs_0e.met[i]);

		// ----
		old_name = set.fs_3e.metL[i]->GetName();
		tmp_length = strlen(old_name) - strlen(strstr(old_name, "3e_"));
		memset(new_name, 0, 256 * sizeof(char));
		strncpy(new_name, old_name, tmp_length);
		strcat(new_name, (char*) (old_name + tmp_length + 3));

		set.metL[i] = (TH1D*) set.fs_3e.metL[i]->Clone(new_name);
		set.metL[i]->Add(set.fs_2eSS.metL[i]);
		set.metL[i]->Add(set.fs_2eOS.metL[i]);
		set.metL[i]->Add(set.fs_1eSS.metL[i]);
		set.metL[i]->Add(set.fs_1eOS.metL[i]);
		set.metL[i]->Add(set.fs_0e.metL[i]);

	}

	buildAStack(set.ST_N_jets, set.N_jets, &set.fs_3e.syst_tag);
	buildAStack(set.ST_met, set.met, &set.fs_3e.syst_tag);
	buildAStack(set.ST_metL, set.metL, &set.fs_3e.syst_tag);

	delete plots1;

	return;
}

//-----------------------------------------------------------------------------
void weightData_FS(distrSet& set) {

	//we calculate weight for the datasets
	Double_t weight[N_SETS];
	for (int i = 1; i < N_SETS; i++) {
		weight[i] = set.int_lumi * set.xsect[i] / set.num_of_evts[i];
	}

	double sf = 1.;

	//We re-weight all events here
	for (int i = 1; i < N_SETS; i++) {

		//corrections to the lepton energies
		sf = 1.;
		if (i == zmm_ind || i == zee_ind || i == zmmbb_ind || i == zeebb_ind || i == ttbar_ind || i == st_Wt_ind) {

			if (i == zmm_ind) {
				if (strstr(set.mu1_pt[i]->GetName(), "1eSS") != NULL || strstr(set.mu1_pt[i]->GetName(), "1eOS") != NULL)
					sf = set.FR_lf_e;

				if (strstr(set.mu1_pt[i]->GetName(), "0e") != NULL)
					sf = set.FR_lf_mu;

			}

			if (i == zee_ind) {
				if (strstr(set.mu1_pt[i]->GetName(), "3e") != NULL)
					sf = set.FR_lf_e;

				if (strstr(set.mu1_pt[i]->GetName(), "2eSS") != NULL || strstr(set.mu1_pt[i]->GetName(), "2eOS") != NULL)
					sf = set.FR_lf_mu;
			}

			if (i == zmmbb_ind) {
				if (strstr(set.mu1_pt[i]->GetName(), "1eSS") != NULL || strstr(set.mu1_pt[i]->GetName(), "1eOS") != NULL)
					sf = set.FR_hf_e;

				if (strstr(set.mu1_pt[i]->GetName(), "0e") != NULL)
					sf = set.FR_hf_mu;

			}

			if (i == zeebb_ind) {
				if (strstr(set.mu1_pt[i]->GetName(), "3e") != NULL)
					sf = set.FR_hf_e;

				if (strstr(set.mu1_pt[i]->GetName(), "2eSS") != NULL || strstr(set.mu1_pt[i]->GetName(), "2eOS") != NULL)
					sf = set.FR_hf_mu;
			}

			if (i == ttbar_ind || i == st_Wt_ind) {

				if (strstr(set.mu1_pt[i]->GetName(), "3e") != NULL || strstr(set.mu1_pt[i]->GetName(), "2eSS") != NULL)
					sf = set.FR_hf_e;

				if (strstr(set.mu1_pt[i]->GetName(), "0e") != NULL || strstr(set.mu1_pt[i]->GetName(), "1eSS") != NULL)
					sf = set.FR_hf_mu;

				if (strstr(set.mu1_pt[i]->GetName(), "2eOS") != NULL)
					//sf = (set.FR_hf_mu + 2. * em_ee * set.FR_hf_e) / (1. + 2. * em_ee);
					sf = (set.FR_hf_mu + em_ee * set.FR_hf_e) / (1. + em_ee);

				if (strstr(set.mu1_pt[i]->GetName(), "1eOS") != NULL)
					//sf = (set.FR_hf_e * em_ee + 2. * set.FR_hf_mu) / (em_ee + 2.);
					sf = (set.FR_hf_e * em_ee + set.FR_hf_mu) / (em_ee + 1.);

			}

			if (i == ww_ind) {

				if (strstr(set.mu1_pt[i]->GetName(), "3e") != NULL || strstr(set.mu1_pt[i]->GetName(), "2eSS") != NULL)
					sf = set.FR_lf_e;

				if (strstr(set.mu1_pt[i]->GetName(), "0e") != NULL || strstr(set.mu1_pt[i]->GetName(), "1eSS") != NULL)
					sf = set.FR_lf_mu;

				if (strstr(set.mu1_pt[i]->GetName(), "2eOS") != NULL)
					//sf = (set.FR_lf_mu + 2. * em_ee * set.FR_lf_e) / (1. + 2. * em_ee);
					sf = (set.FR_lf_mu + em_ee * set.FR_lf_e) / (1. + em_ee);

				if (strstr(set.mu1_pt[i]->GetName(), "1eOS") != NULL)
					//sf = (set.FR_lf_e * em_ee + 2. * set.FR_lf_mu) / (em_ee + 2.);
					sf = (set.FR_lf_e * em_ee + set.FR_lf_mu) / (em_ee + 1.);

			}

		}

		//muons
		set.mu1_pt[i]->Scale(weight[i] * sf);
		set.mu1_pt[i]->SetLineColor(set.lineColor[i]);
		set.mu1_pt[i]->SetFillColor(set.color[i]);
		set.mu1_pt[i]->SetLineWidth(1);

		set.mu2_pt[i]->Scale(weight[i] * sf);
		set.mu2_pt[i]->SetLineColor(set.lineColor[i]);
		set.mu2_pt[i]->SetFillColor(set.color[i]);
		set.mu2_pt[i]->SetLineWidth(1);

		set.mu3_pt[i]->Scale(weight[i] * sf);
		set.mu3_pt[i]->SetLineColor(set.lineColor[i]);
		set.mu3_pt[i]->SetFillColor(set.color[i]);
		set.mu3_pt[i]->SetLineWidth(1);

		set.mu1_D0[i]->Scale(weight[i] * sf);
		set.mu1_D0[i]->SetLineColor(set.lineColor[i]);
		set.mu1_D0[i]->SetFillColor(set.color[i]);
		set.mu1_D0[i]->SetLineWidth(1);

		set.mu2_D0[i]->Scale(weight[i] * sf);
		set.mu2_D0[i]->SetLineColor(set.lineColor[i]);
		set.mu2_D0[i]->SetFillColor(set.color[i]);
		set.mu2_D0[i]->SetLineWidth(1);

		set.mu3_D0[i]->Scale(weight[i] * sf);
		set.mu3_D0[i]->SetLineColor(set.lineColor[i]);
		set.mu3_D0[i]->SetFillColor(set.color[i]);
		set.mu3_D0[i]->SetLineWidth(1);

		/*
		 set.mu1_ptcone02[i]->Scale(weight[i] * sf);
		 set.mu1_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.mu1_ptcone02[i]->SetFillColor(set.color[i]);
		 set.mu1_ptcone02[i]->SetLineWidth(1);

		 set.mu2_ptcone02[i]->Scale(weight[i] * sf);
		 set.mu2_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.mu2_ptcone02[i]->SetFillColor(set.color[i]);
		 set.mu2_ptcone02[i]->SetLineWidth(1);

		 set.mu3_ptcone02[i]->Scale(weight[i] * sf);
		 set.mu3_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.mu3_ptcone02[i]->SetFillColor(set.color[i]);
		 set.mu3_ptcone02[i]->SetLineWidth(1);

		 set.mu1_ptcone03[i]->Scale(weight[i] * sf);
		 set.mu1_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu1_ptcone03[i]->SetFillColor(set.color[i]);
		 set.mu1_ptcone03[i]->SetLineWidth(1);

		 set.mu2_ptcone03[i]->Scale(weight[i] * sf);
		 set.mu2_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu2_ptcone03[i]->SetFillColor(set.color[i]);
		 set.mu2_ptcone03[i]->SetLineWidth(1);

		 set.mu3_ptcone03[i]->Scale(weight[i] * sf);
		 set.mu3_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu3_ptcone03[i]->SetFillColor(set.color[i]);
		 set.mu3_ptcone03[i]->SetLineWidth(1);
		 */

		set.mu1_etcone02[i]->Scale(weight[i] * sf);
		set.mu1_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.mu1_etcone02[i]->SetFillColor(set.color[i]);
		set.mu1_etcone02[i]->SetLineWidth(1);

		set.mu2_etcone02[i]->Scale(weight[i] * sf);
		set.mu2_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.mu2_etcone02[i]->SetFillColor(set.color[i]);
		set.mu2_etcone02[i]->SetLineWidth(1);

		set.mu3_etcone02[i]->Scale(weight[i] * sf);
		set.mu3_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.mu3_etcone02[i]->SetFillColor(set.color[i]);
		set.mu3_etcone02[i]->SetLineWidth(1);

		/*
		 set.mu1_etcone03[i]->Scale(weight[i] * sf);
		 set.mu1_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu1_etcone03[i]->SetFillColor(set.color[i]);
		 set.mu1_etcone03[i]->SetLineWidth(1);

		 set.mu2_etcone03[i]->Scale(weight[i] * sf);
		 set.mu2_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu2_etcone03[i]->SetFillColor(set.color[i]);
		 set.mu2_etcone03[i]->SetLineWidth(1);

		 set.mu3_etcone03[i]->Scale(weight[i] * sf);
		 set.mu3_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu3_etcone03[i]->SetFillColor(set.color[i]);
		 set.mu3_etcone03[i]->SetLineWidth(1);
		 */

		set.mu1_D0sig[i]->Scale(weight[i] * sf);
		set.mu1_D0sig[i]->SetLineColor(set.lineColor[i]);
		set.mu1_D0sig[i]->SetFillColor(set.color[i]);
		set.mu1_D0sig[i]->SetLineWidth(1);

		set.mu2_D0sig[i]->Scale(weight[i] * sf);
		set.mu2_D0sig[i]->SetLineColor(set.lineColor[i]);
		set.mu2_D0sig[i]->SetFillColor(set.color[i]);
		set.mu2_D0sig[i]->SetLineWidth(1);

		set.mu3_D0sig[i]->Scale(weight[i] * sf);
		set.mu3_D0sig[i]->SetLineColor(set.lineColor[i]);
		set.mu3_D0sig[i]->SetFillColor(set.color[i]);
		set.mu3_D0sig[i]->SetLineWidth(1);

		set.mu_eta[i]->Scale(weight[i] * sf);
		set.mu_eta[i]->SetLineColor(set.lineColor[i]);
		set.mu_eta[i]->SetFillColor(set.color[i]);
		set.mu_eta[i]->SetLineWidth(1);

		set.mu_phi[i]->Scale(weight[i] * sf);
		set.mu_phi[i]->SetLineColor(set.lineColor[i]);
		set.mu_phi[i]->SetFillColor(set.color[i]);
		set.mu_phi[i]->SetLineWidth(1);

		//electrons
		set.el1_pt[i]->Scale(weight[i] * sf);
		set.el1_pt[i]->SetLineColor(set.lineColor[i]);
		set.el1_pt[i]->SetFillColor(set.color[i]);
		set.el1_pt[i]->SetLineWidth(1);

		set.el2_pt[i]->Scale(weight[i] * sf);
		set.el2_pt[i]->SetLineColor(set.lineColor[i]);
		set.el2_pt[i]->SetFillColor(set.color[i]);
		set.el2_pt[i]->SetLineWidth(1);

		set.el3_pt[i]->Scale(weight[i] * sf);
		set.el3_pt[i]->SetLineColor(set.lineColor[i]);
		set.el3_pt[i]->SetFillColor(set.color[i]);
		set.el3_pt[i]->SetLineWidth(1);

		set.el1_D0[i]->Scale(weight[i] * sf);
		set.el1_D0[i]->SetLineColor(set.lineColor[i]);
		set.el1_D0[i]->SetFillColor(set.color[i]);
		set.el1_D0[i]->SetLineWidth(1);

		set.el2_D0[i]->Scale(weight[i] * sf);
		set.el2_D0[i]->SetLineColor(set.lineColor[i]);
		set.el2_D0[i]->SetFillColor(set.color[i]);
		set.el2_D0[i]->SetLineWidth(1);

		set.el3_D0[i]->Scale(weight[i] * sf);
		set.el3_D0[i]->SetLineColor(set.lineColor[i]);
		set.el3_D0[i]->SetFillColor(set.color[i]);
		set.el3_D0[i]->SetLineWidth(1);

		/*
		 set.el1_ptcone02[i]->Scale(weight[i] * sf);
		 set.el1_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.el1_ptcone02[i]->SetFillColor(set.color[i]);
		 set.el1_ptcone02[i]->SetLineWidth(1);

		 set.el2_ptcone02[i]->Scale(weight[i] * sf);
		 set.el2_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.el2_ptcone02[i]->SetFillColor(set.color[i]);
		 set.el2_ptcone02[i]->SetLineWidth(1);

		 set.el3_ptcone02[i]->Scale(weight[i] * sf);
		 set.el3_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.el3_ptcone02[i]->SetFillColor(set.color[i]);
		 set.el3_ptcone02[i]->SetLineWidth(1);

		 set.el1_ptcone03[i]->Scale(weight[i] * sf);
		 set.el1_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el1_ptcone03[i]->SetFillColor(set.color[i]);
		 set.el1_ptcone03[i]->SetLineWidth(1);

		 set.el2_ptcone03[i]->Scale(weight[i] * sf);
		 set.el2_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el2_ptcone03[i]->SetFillColor(set.color[i]);
		 set.el2_ptcone03[i]->SetLineWidth(1);

		 set.el3_ptcone03[i]->Scale(weight[i] * sf);
		 set.el3_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el3_ptcone03[i]->SetFillColor(set.color[i]);
		 set.el3_ptcone03[i]->SetLineWidth(1);
		 */

		set.el1_etcone02[i]->Scale(weight[i] * sf);
		set.el1_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.el1_etcone02[i]->SetFillColor(set.color[i]);
		set.el1_etcone02[i]->SetLineWidth(1);

		set.el2_etcone02[i]->Scale(weight[i] * sf);
		set.el2_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.el2_etcone02[i]->SetFillColor(set.color[i]);
		set.el2_etcone02[i]->SetLineWidth(1);

		set.el3_etcone02[i]->Scale(weight[i] * sf);
		set.el3_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.el3_etcone02[i]->SetFillColor(set.color[i]);
		set.el3_etcone02[i]->SetLineWidth(1);

		/*
		 set.el1_etcone03[i]->Scale(weight[i] * sf);
		 set.el1_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el1_etcone03[i]->SetFillColor(set.color[i]);
		 set.el1_etcone03[i]->SetLineWidth(1);

		 set.el2_etcone03[i]->Scale(weight[i] * sf);
		 set.el2_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el2_etcone03[i]->SetFillColor(set.color[i]);
		 set.el2_etcone03[i]->SetLineWidth(1);

		 set.el3_etcone03[i]->Scale(weight[i] * sf);
		 set.el3_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el3_etcone03[i]->SetFillColor(set.color[i]);
		 set.el3_etcone03[i]->SetLineWidth(1);
		 */

		set.el1_isTight[i]->Scale(weight[i] * sf);
		set.el1_isTight[i]->SetLineColor(set.lineColor[i]);
		set.el1_isTight[i]->SetFillColor(set.color[i]);
		set.el1_isTight[i]->SetLineWidth(1);

		set.el2_isTight[i]->Scale(weight[i] * sf);
		set.el2_isTight[i]->SetLineColor(set.lineColor[i]);
		set.el2_isTight[i]->SetFillColor(set.color[i]);
		set.el2_isTight[i]->SetLineWidth(1);

		set.el3_isTight[i]->Scale(weight[i] * sf);
		set.el3_isTight[i]->SetLineColor(set.lineColor[i]);
		set.el3_isTight[i]->SetFillColor(set.color[i]);
		set.el3_isTight[i]->SetLineWidth(1);

		set.el_eta[i]->Scale(weight[i] * sf);
		set.el_eta[i]->SetLineColor(set.lineColor[i]);
		set.el_eta[i]->SetFillColor(set.color[i]);
		set.el_eta[i]->SetLineWidth(1);

		set.el_phi[i]->Scale(weight[i] * sf);
		set.el_phi[i]->SetLineColor(set.lineColor[i]);
		set.el_phi[i]->SetFillColor(set.color[i]);
		set.el_phi[i]->SetLineWidth(1);

		//misc
		set.met[i]->Scale(weight[i] * sf);
		set.met[i]->SetLineColor(set.lineColor[i]);
		set.met[i]->SetFillColor(set.color[i]);
		set.met[i]->SetLineWidth(1);

		//---
		set.metL[i]->Scale(weight[i] * sf);
		set.metL[i]->SetLineColor(set.lineColor[i]);
		set.metL[i]->SetFillColor(set.color[i]);
		set.metL[i]->SetLineWidth(1);

		set.MZ[i]->Scale(weight[i] * sf);
		set.MZ[i]->SetLineColor(set.lineColor[i]);
		set.MZ[i]->SetFillColor(set.color[i]);
		set.MZ[i]->SetLineWidth(1);

		//jets
		set.N_jets[i]->Scale(weight[i] * sf);
		set.N_jets[i]->SetLineColor(set.lineColor[i]);
		set.N_jets[i]->SetFillColor(set.color[i]);
		set.N_jets[i]->SetLineWidth(1);

		set.pt_jet1[i]->Scale(weight[i] * sf);
		set.pt_jet1[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet1[i]->SetFillColor(set.color[i]);
		set.pt_jet1[i]->SetLineWidth(1);

		set.pt_jet2[i]->Scale(weight[i] * sf);
		set.pt_jet2[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet2[i]->SetFillColor(set.color[i]);
		set.pt_jet2[i]->SetLineWidth(1);

		set.pt_jet3[i]->Scale(weight[i] * sf);
		set.pt_jet3[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet3[i]->SetFillColor(set.color[i]);
		set.pt_jet3[i]->SetLineWidth(1);

		set.pt_jet4[i]->Scale(weight[i] * sf);
		set.pt_jet4[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet4[i]->SetFillColor(set.color[i]);
		set.pt_jet4[i]->SetLineWidth(1);

	}

	return;
}

//-----------------------------------------------------------------------------
void weightData_SigRegion(distrSigRegion& set) {

	weightData_SIG(set.fs_3e);
	weightData_SIG(set.fs_2eSS);
	weightData_SIG(set.fs_2eOS);
	weightData_SIG(set.fs_1eSS);
	weightData_SIG(set.fs_1eOS);
	weightData_SIG(set.fs_0e);

	//Now we can produce distributions for lepton-combined final states
	for (int i = 0; i < N_SIG; i++) {

		char new_name[256] = "";
		const char* old_name;
		int tmp_length;

		old_name = set.fs_3e.N_jets[i]->GetName();
		tmp_length = strlen(old_name) - strlen(strstr(old_name, "3e_"));
		memset(new_name, 0, 256 * sizeof(char));
		strncpy(new_name, old_name, tmp_length);
		strcat(new_name, (char*) (old_name + tmp_length + 3));

		set.N_jets[i] = (TH1D*) set.fs_3e.N_jets[i]->Clone(new_name);
		set.N_jets[i]->Add(set.fs_2eSS.N_jets[i]);
		set.N_jets[i]->Add(set.fs_2eOS.N_jets[i]);
		set.N_jets[i]->Add(set.fs_1eSS.N_jets[i]);
		set.N_jets[i]->Add(set.fs_1eOS.N_jets[i]);
		set.N_jets[i]->Add(set.fs_0e.N_jets[i]);

		// ----
		old_name = set.fs_3e.met[i]->GetName();
		tmp_length = strlen(old_name) - strlen(strstr(old_name, "3e_"));
		memset(new_name, 0, 256 * sizeof(char));
		strncpy(new_name, old_name, tmp_length);
		strcat(new_name, (char*) (old_name + tmp_length + 3));

		set.met[i] = (TH1D*) set.fs_3e.met[i]->Clone(new_name);
		set.met[i]->Add(set.fs_2eSS.met[i]);
		set.met[i]->Add(set.fs_2eOS.met[i]);
		set.met[i]->Add(set.fs_1eSS.met[i]);
		set.met[i]->Add(set.fs_1eOS.met[i]);
		set.met[i]->Add(set.fs_0e.met[i]);

		// ----
		old_name = set.fs_3e.metL[i]->GetName();
		tmp_length = strlen(old_name) - strlen(strstr(old_name, "3e_"));
		memset(new_name, 0, 256 * sizeof(char));
		strncpy(new_name, old_name, tmp_length);
		strcat(new_name, (char*) (old_name + tmp_length + 3));

		set.metL[i] = (TH1D*) set.fs_3e.metL[i]->Clone(new_name);
		set.metL[i]->Add(set.fs_2eSS.metL[i]);
		set.metL[i]->Add(set.fs_2eOS.metL[i]);
		set.metL[i]->Add(set.fs_1eSS.metL[i]);
		set.metL[i]->Add(set.fs_1eOS.metL[i]);
		set.metL[i]->Add(set.fs_0e.metL[i]);
	}

	return;
}

//-----------------------------------------------------------------------------
void weightData_SIG(distrSig& set) {

	//we calculate weight for the dataSIG
	Double_t weight[N_SIG];
	for (int i = 0; i < N_SIG; i++) {
		weight[i] = set.int_lumi * set.xsect[i] / set.num_of_evts[i];
	}

	double sf = 1.;

	//We re-weight all events here
	for (int i = 0; i < N_SIG; i++) {

		//muons
		set.mu1_pt[i]->Scale(weight[i] * sf);
		set.mu1_pt[i]->SetLineColor(set.lineColor[i]);
		set.mu1_pt[i]->SetFillColor(set.color[i]);
		set.mu1_pt[i]->SetLineWidth(3);
		set.mu1_pt[i]->SetLineStyle(i + 1);

		set.mu2_pt[i]->Scale(weight[i] * sf);
		set.mu2_pt[i]->SetLineColor(set.lineColor[i]);
		set.mu2_pt[i]->SetFillColor(set.color[i]);
		set.mu2_pt[i]->SetLineWidth(3);
		set.mu2_pt[i]->SetLineStyle(i + 1);

		set.mu3_pt[i]->Scale(weight[i] * sf);
		set.mu3_pt[i]->SetLineColor(set.lineColor[i]);
		set.mu3_pt[i]->SetFillColor(set.color[i]);
		set.mu3_pt[i]->SetLineWidth(3);
		set.mu3_pt[i]->SetLineStyle(i + 1);

		set.mu1_D0[i]->Scale(weight[i] * sf);
		set.mu1_D0[i]->SetLineColor(set.lineColor[i]);
		set.mu1_D0[i]->SetFillColor(set.color[i]);
		set.mu1_D0[i]->SetLineWidth(3);
		set.mu1_D0[i]->SetLineStyle(i + 1);

		set.mu2_D0[i]->Scale(weight[i] * sf);
		set.mu2_D0[i]->SetLineColor(set.lineColor[i]);
		set.mu2_D0[i]->SetFillColor(set.color[i]);
		set.mu2_D0[i]->SetLineWidth(3);
		set.mu2_D0[i]->SetLineStyle(i + 1);

		set.mu3_D0[i]->Scale(weight[i] * sf);
		set.mu3_D0[i]->SetLineColor(set.lineColor[i]);
		set.mu3_D0[i]->SetFillColor(set.color[i]);
		set.mu3_D0[i]->SetLineWidth(3);
		set.mu3_D0[i]->SetLineStyle(i + 1);

		/*
		 set.mu1_ptcone02[i]->Scale(weight[i] * sf);
		 set.mu1_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.mu1_ptcone02[i]->SetFillColor(set.color[i]);
		 set.mu1_ptcone02[i]->SetLineWidth(1);

		 set.mu2_ptcone02[i]->Scale(weight[i] * sf);
		 set.mu2_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.mu2_ptcone02[i]->SetFillColor(set.color[i]);
		 set.mu2_ptcone02[i]->SetLineWidth(1);

		 set.mu3_ptcone02[i]->Scale(weight[i] * sf);
		 set.mu3_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.mu3_ptcone02[i]->SetFillColor(set.color[i]);
		 set.mu3_ptcone02[i]->SetLineWidth(1);

		 set.mu1_ptcone03[i]->Scale(weight[i] * sf);
		 set.mu1_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu1_ptcone03[i]->SetFillColor(set.color[i]);
		 set.mu1_ptcone03[i]->SetLineWidth(1);

		 set.mu2_ptcone03[i]->Scale(weight[i] * sf);
		 set.mu2_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu2_ptcone03[i]->SetFillColor(set.color[i]);
		 set.mu2_ptcone03[i]->SetLineWidth(1);

		 set.mu3_ptcone03[i]->Scale(weight[i] * sf);
		 set.mu3_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu3_ptcone03[i]->SetFillColor(set.color[i]);
		 set.mu3_ptcone03[i]->SetLineWidth(1);
		 */

		set.mu1_etcone02[i]->Scale(weight[i] * sf);
		set.mu1_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.mu1_etcone02[i]->SetFillColor(set.color[i]);
		set.mu1_etcone02[i]->SetLineWidth(3);
		set.mu1_etcone02[i]->SetLineStyle(i + 1);

		set.mu2_etcone02[i]->Scale(weight[i] * sf);
		set.mu2_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.mu2_etcone02[i]->SetFillColor(set.color[i]);
		set.mu2_etcone02[i]->SetLineWidth(3);
		set.mu2_etcone02[i]->SetLineStyle(i + 1);

		set.mu3_etcone02[i]->Scale(weight[i] * sf);
		set.mu3_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.mu3_etcone02[i]->SetFillColor(set.color[i]);
		set.mu3_etcone02[i]->SetLineWidth(3);
		set.mu3_etcone02[i]->SetLineStyle(i + 1);

		/*
		 set.mu1_etcone03[i]->Scale(weight[i] * sf);
		 set.mu1_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu1_etcone03[i]->SetFillColor(set.color[i]);
		 set.mu1_etcone03[i]->SetLineWidth(1);

		 set.mu2_etcone03[i]->Scale(weight[i] * sf);
		 set.mu2_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu2_etcone03[i]->SetFillColor(set.color[i]);
		 set.mu2_etcone03[i]->SetLineWidth(1);

		 set.mu3_etcone03[i]->Scale(weight[i] * sf);
		 set.mu3_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.mu3_etcone03[i]->SetFillColor(set.color[i]);
		 set.mu3_etcone03[i]->SetLineWidth(1);
		 */

		set.mu1_D0sig[i]->Scale(weight[i] * sf);
		set.mu1_D0sig[i]->SetLineColor(set.lineColor[i]);
		set.mu1_D0sig[i]->SetFillColor(set.color[i]);
		set.mu1_D0sig[i]->SetLineWidth(3);
		set.mu1_D0sig[i]->SetLineStyle(i + 1);

		set.mu2_D0sig[i]->Scale(weight[i] * sf);
		set.mu2_D0sig[i]->SetLineColor(set.lineColor[i]);
		set.mu2_D0sig[i]->SetFillColor(set.color[i]);
		set.mu2_D0sig[i]->SetLineWidth(3);
		set.mu2_D0sig[i]->SetLineStyle(i + 1);

		set.mu3_D0sig[i]->Scale(weight[i] * sf);
		set.mu3_D0sig[i]->SetLineColor(set.lineColor[i]);
		set.mu3_D0sig[i]->SetFillColor(set.color[i]);
		set.mu3_D0sig[i]->SetLineWidth(3);
		set.mu3_D0sig[i]->SetLineStyle(i + 1);

		set.mu_eta[i]->Scale(weight[i] * sf);
		set.mu_eta[i]->SetLineColor(set.lineColor[i]);
		set.mu_eta[i]->SetFillColor(set.color[i]);
		set.mu_eta[i]->SetLineWidth(3);
		set.mu_eta[i]->SetLineStyle(i + 1);

		set.mu_phi[i]->Scale(weight[i] * sf);
		set.mu_phi[i]->SetLineColor(set.lineColor[i]);
		set.mu_phi[i]->SetFillColor(set.color[i]);
		set.mu_phi[i]->SetLineWidth(3);
		set.mu_phi[i]->SetLineStyle(i + 1);

		//electrons
		set.el1_pt[i]->Scale(weight[i] * sf);
		set.el1_pt[i]->SetLineColor(set.lineColor[i]);
		set.el1_pt[i]->SetFillColor(set.color[i]);
		set.el1_pt[i]->SetLineWidth(3);
		set.el1_pt[i]->SetLineStyle(i + 1);

		set.el2_pt[i]->Scale(weight[i] * sf);
		set.el2_pt[i]->SetLineColor(set.lineColor[i]);
		set.el2_pt[i]->SetFillColor(set.color[i]);
		set.el2_pt[i]->SetLineWidth(3);
		set.el2_pt[i]->SetLineStyle(i + 1);

		set.el3_pt[i]->Scale(weight[i] * sf);
		set.el3_pt[i]->SetLineColor(set.lineColor[i]);
		set.el3_pt[i]->SetFillColor(set.color[i]);
		set.el3_pt[i]->SetLineWidth(3);
		set.el3_pt[i]->SetLineStyle(i + 1);

		set.el1_D0[i]->Scale(weight[i] * sf);
		set.el1_D0[i]->SetLineColor(set.lineColor[i]);
		set.el1_D0[i]->SetFillColor(set.color[i]);
		set.el1_D0[i]->SetLineWidth(3);
		set.el1_D0[i]->SetLineStyle(i + 1);

		set.el2_D0[i]->Scale(weight[i] * sf);
		set.el2_D0[i]->SetLineColor(set.lineColor[i]);
		set.el2_D0[i]->SetFillColor(set.color[i]);
		set.el2_D0[i]->SetLineWidth(3);
		set.el2_D0[i]->SetLineStyle(i + 1);

		set.el3_D0[i]->Scale(weight[i] * sf);
		set.el3_D0[i]->SetLineColor(set.lineColor[i]);
		set.el3_D0[i]->SetFillColor(set.color[i]);
		set.el3_D0[i]->SetLineWidth(3);
		set.el3_D0[i]->SetLineStyle(i + 1);

		/*
		 set.el1_ptcone02[i]->Scale(weight[i] * sf);
		 set.el1_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.el1_ptcone02[i]->SetFillColor(set.color[i]);
		 set.el1_ptcone02[i]->SetLineWidth(1);

		 set.el2_ptcone02[i]->Scale(weight[i] * sf);
		 set.el2_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.el2_ptcone02[i]->SetFillColor(set.color[i]);
		 set.el2_ptcone02[i]->SetLineWidth(1);

		 set.el3_ptcone02[i]->Scale(weight[i] * sf);
		 set.el3_ptcone02[i]->SetLineColor(set.lineColor[i]);
		 set.el3_ptcone02[i]->SetFillColor(set.color[i]);
		 set.el3_ptcone02[i]->SetLineWidth(1);

		 set.el1_ptcone03[i]->Scale(weight[i] * sf);
		 set.el1_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el1_ptcone03[i]->SetFillColor(set.color[i]);
		 set.el1_ptcone03[i]->SetLineWidth(1);

		 set.el2_ptcone03[i]->Scale(weight[i] * sf);
		 set.el2_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el2_ptcone03[i]->SetFillColor(set.color[i]);
		 set.el2_ptcone03[i]->SetLineWidth(1);

		 set.el3_ptcone03[i]->Scale(weight[i] * sf);
		 set.el3_ptcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el3_ptcone03[i]->SetFillColor(set.color[i]);
		 set.el3_ptcone03[i]->SetLineWidth(1);
		 */

		set.el1_etcone02[i]->Scale(weight[i] * sf);
		set.el1_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.el1_etcone02[i]->SetFillColor(set.color[i]);
		set.el1_etcone02[i]->SetLineWidth(3);
		set.el1_etcone02[i]->SetLineStyle(i + 1);

		set.el2_etcone02[i]->Scale(weight[i] * sf);
		set.el2_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.el2_etcone02[i]->SetFillColor(set.color[i]);
		set.el2_etcone02[i]->SetLineWidth(3);
		set.el2_etcone02[i]->SetLineStyle(i + 1);

		set.el3_etcone02[i]->Scale(weight[i] * sf);
		set.el3_etcone02[i]->SetLineColor(set.lineColor[i]);
		set.el3_etcone02[i]->SetFillColor(set.color[i]);
		set.el3_etcone02[i]->SetLineWidth(3);
		set.el3_etcone02[i]->SetLineStyle(i + 1);

		/*
		 set.el1_etcone03[i]->Scale(weight[i] * sf);
		 set.el1_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el1_etcone03[i]->SetFillColor(set.color[i]);
		 set.el1_etcone03[i]->SetLineWidth(1);

		 set.el2_etcone03[i]->Scale(weight[i] * sf);
		 set.el2_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el2_etcone03[i]->SetFillColor(set.color[i]);
		 set.el2_etcone03[i]->SetLineWidth(1);

		 set.el3_etcone03[i]->Scale(weight[i] * sf);
		 set.el3_etcone03[i]->SetLineColor(set.lineColor[i]);
		 set.el3_etcone03[i]->SetFillColor(set.color[i]);
		 set.el3_etcone03[i]->SetLineWidth(1);
		 */

		set.el1_isTight[i]->Scale(weight[i] * sf);
		set.el1_isTight[i]->SetLineColor(set.lineColor[i]);
		set.el1_isTight[i]->SetFillColor(set.color[i]);
		set.el1_isTight[i]->SetLineWidth(3);
		set.el1_isTight[i]->SetLineStyle(i + 1);

		set.el2_isTight[i]->Scale(weight[i] * sf);
		set.el2_isTight[i]->SetLineColor(set.lineColor[i]);
		set.el2_isTight[i]->SetFillColor(set.color[i]);
		set.el2_isTight[i]->SetLineWidth(3);
		set.el2_isTight[i]->SetLineStyle(i + 1);

		set.el3_isTight[i]->Scale(weight[i] * sf);
		set.el3_isTight[i]->SetLineColor(set.lineColor[i]);
		set.el3_isTight[i]->SetFillColor(set.color[i]);
		set.el3_isTight[i]->SetLineWidth(3);
		set.el3_isTight[i]->SetLineStyle(i + 1);

		set.el_eta[i]->Scale(weight[i] * sf);
		set.el_eta[i]->SetLineColor(set.lineColor[i]);
		set.el_eta[i]->SetFillColor(set.color[i]);
		set.el_eta[i]->SetLineWidth(3);
		set.el_eta[i]->SetLineStyle(i + 1);

		set.el_phi[i]->Scale(weight[i] * sf);
		set.el_phi[i]->SetLineColor(set.lineColor[i]);
		set.el_phi[i]->SetFillColor(set.color[i]);
		set.el_phi[i]->SetLineWidth(3);
		set.el_phi[i]->SetLineStyle(i + 1);

		//misc
		set.met[i]->Scale(weight[i] * sf);
		set.met[i]->SetLineColor(set.lineColor[i]);
		set.met[i]->SetFillColor(set.color[i]);
		set.met[i]->SetLineWidth(3);
		set.met[i]->SetLineStyle(i + 1);

		//---
		set.metL[i]->Scale(weight[i] * sf);
		set.metL[i]->SetLineColor(set.lineColor[i]);
		set.metL[i]->SetFillColor(set.color[i]);
		set.metL[i]->SetLineWidth(3);
		set.metL[i]->SetLineStyle(i + 1);

		set.MZ[i]->Scale(weight[i] * sf);
		set.MZ[i]->SetLineColor(set.lineColor[i]);
		set.MZ[i]->SetFillColor(set.color[i]);
		set.MZ[i]->SetLineWidth(3);
		set.MZ[i]->SetLineStyle(i + 1);

		//jets
		set.N_jets[i]->Scale(weight[i] * sf);
		set.N_jets[i]->SetLineColor(set.lineColor[i]);
		set.N_jets[i]->SetFillColor(set.color[i]);
		set.N_jets[i]->SetLineWidth(3);
		set.N_jets[i]->SetLineStyle(i + 1);

		set.pt_jet1[i]->Scale(weight[i] * sf);
		set.pt_jet1[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet1[i]->SetFillColor(set.color[i]);
		set.pt_jet1[i]->SetLineWidth(3);
		set.pt_jet1[i]->SetLineStyle(i + 1);

		set.pt_jet2[i]->Scale(weight[i] * sf);
		set.pt_jet2[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet2[i]->SetFillColor(set.color[i]);
		set.pt_jet2[i]->SetLineWidth(3);
		set.pt_jet2[i]->SetLineStyle(i + 1);

		set.pt_jet3[i]->Scale(weight[i] * sf);
		set.pt_jet3[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet3[i]->SetFillColor(set.color[i]);
		set.pt_jet3[i]->SetLineWidth(3);
		set.pt_jet3[i]->SetLineStyle(i + 1);

		set.pt_jet4[i]->Scale(weight[i] * sf);
		set.pt_jet4[i]->SetLineColor(set.lineColor[i]);
		set.pt_jet4[i]->SetFillColor(set.color[i]);
		set.pt_jet4[i]->SetLineWidth(3);
		set.pt_jet4[i]->SetLineStyle(i + 1);

	}

	return;
}

//-----------------------------------------------------------------------------
void buildStack(distrSet& set) {

	//muons
	buildAStack(set.ST_mu1_pt, set.mu1_pt, &set.syst_tag);
	buildAStack(set.ST_mu2_pt, set.mu2_pt, &set.syst_tag);
	buildAStack(set.ST_mu3_pt, set.mu3_pt, &set.syst_tag);

	buildAStack(set.ST_mu1_D0, set.mu1_D0, &set.syst_tag);
	buildAStack(set.ST_mu2_D0, set.mu2_D0, &set.syst_tag);
	buildAStack(set.ST_mu3_D0, set.mu3_D0, &set.syst_tag);

	/*
	 buildAStack(set.ST_mu1_ptcone02, set.mu1_ptcone02, &set.syst_tag);
	 buildAStack(set.ST_mu2_ptcone02, set.mu2_ptcone02, &set.syst_tag);
	 buildAStack(set.ST_mu3_ptcone02, set.mu3_ptcone02, &set.syst_tag);

	 buildAStack(set.ST_mu1_ptcone03, set.mu1_ptcone03, &set.syst_tag);
	 buildAStack(set.ST_mu2_ptcone03, set.mu2_ptcone03, &set.syst_tag);
	 buildAStack(set.ST_mu3_ptcone03, set.mu3_ptcone03, &set.syst_tag);
	 */

	buildAStack(set.ST_mu1_etcone02, set.mu1_etcone02, &set.syst_tag);
	buildAStack(set.ST_mu2_etcone02, set.mu2_etcone02, &set.syst_tag);
	buildAStack(set.ST_mu3_etcone02, set.mu3_etcone02, &set.syst_tag);

	/*
	 buildAStack(set.ST_mu1_etcone03, set.mu1_etcone03, &set.syst_tag);
	 buildAStack(set.ST_mu2_etcone03, set.mu2_etcone03, &set.syst_tag);
	 buildAStack(set.ST_mu3_etcone03, set.mu3_etcone03, &set.syst_tag);
	 */

	buildAStack(set.ST_mu1_D0sig, set.mu1_D0sig, &set.syst_tag);
	buildAStack(set.ST_mu2_D0sig, set.mu2_D0sig, &set.syst_tag);
	buildAStack(set.ST_mu3_D0sig, set.mu3_D0sig, &set.syst_tag);

	buildAStack(set.ST_mu_eta, set.mu_eta, &set.syst_tag);

	buildAStack(set.ST_mu_phi, set.mu_phi, &set.syst_tag);

	//electrons
	buildAStack(set.ST_el1_pt, set.el1_pt, &set.syst_tag);
	buildAStack(set.ST_el2_pt, set.el2_pt, &set.syst_tag);
	buildAStack(set.ST_el3_pt, set.el3_pt, &set.syst_tag);

	buildAStack(set.ST_el1_D0, set.el1_D0, &set.syst_tag);
	buildAStack(set.ST_el2_D0, set.el2_D0, &set.syst_tag);
	buildAStack(set.ST_el3_D0, set.el3_D0, &set.syst_tag);

	/*
	 buildAStack(set.ST_el1_ptcone02, set.el1_ptcone02, &set.syst_tag);
	 buildAStack(set.ST_el2_ptcone02, set.el2_ptcone02, &set.syst_tag);
	 buildAStack(set.ST_el3_ptcone02, set.el3_ptcone02, &set.syst_tag);

	 buildAStack(set.ST_el1_ptcone03, set.el1_ptcone03, &set.syst_tag);
	 buildAStack(set.ST_el2_ptcone03, set.el2_ptcone03, &set.syst_tag);
	 buildAStack(set.ST_el3_ptcone03, set.el3_ptcone03, &set.syst_tag);
	 */

	buildAStack(set.ST_el1_etcone02, set.el1_etcone02, &set.syst_tag);
	buildAStack(set.ST_el2_etcone02, set.el2_etcone02, &set.syst_tag);
	buildAStack(set.ST_el3_etcone02, set.el3_etcone02, &set.syst_tag);

	/*
	 buildAStack(set.ST_el1_etcone03, set.el1_etcone03, &set.syst_tag);
	 buildAStack(set.ST_el2_etcone03, set.el2_etcone03, &set.syst_tag);
	 buildAStack(set.ST_el3_etcone03, set.el3_etcone03, &set.syst_tag);
	 */

	buildAStack(set.ST_el1_isTight, set.el1_isTight, &set.syst_tag);
	buildAStack(set.ST_el2_isTight, set.el2_isTight, &set.syst_tag);
	buildAStack(set.ST_el3_isTight, set.el3_isTight, &set.syst_tag);

	buildAStack(set.ST_el_eta, set.el_eta, &set.syst_tag);
	buildAStack(set.ST_el_phi, set.el_phi, &set.syst_tag);

	//misc
	buildAStack(set.ST_met, set.met, &set.syst_tag);
	buildAStack(set.ST_metL, set.metL, &set.syst_tag);
	buildAStack(set.ST_MZ, set.MZ, &set.syst_tag);

	//jets
	buildAStack(set.ST_N_jets, set.N_jets, &set.syst_tag);

	buildAStack(set.ST_pt_jet1, set.pt_jet1, &set.syst_tag);
	buildAStack(set.ST_pt_jet2, set.pt_jet2, &set.syst_tag);
	buildAStack(set.ST_pt_jet3, set.pt_jet3, &set.syst_tag);
	buildAStack(set.ST_pt_jet4, set.pt_jet4, &set.syst_tag);

	return;
}

//-----------------------------------------------------------------------------
void buildAStack(THStack* &st, TH1D* hist[N_SETS], string *syst_tag) {

	//We build Stacked plots here
	char my_name[256];
	sprintf(my_name, "HSTACK_%s%s", hist[0]->GetName(), syst_tag->data());
	st = new THStack(my_name, "Hstack");

	for (int i = 1; i < N_SETS; i++) {
		st->Add(hist[i]);
	}

	st->Draw("hist");
	st->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
	st->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());

	return;
}

//-----------------------------------------------------------------------------
void drawObservables(distrAll &set, distrSigRegion *sig, distrAll* paired[N_unc_paired],
		distrAll* unpaired[N_unc_paired]) {

	distrRegion* paired_charge[N_unc_paired];
	distrRegion* paired_zbos[N_unc_paired];
	distrRegion* paired_comb[N_unc_paired];
	distrRegion* paired_top[N_unc_paired];
	distrRegion* paired_full[N_unc_paired];

	distrRegion* unpaired_charge[N_unc_unpaired];
	distrRegion* unpaired_zbos[N_unc_unpaired];
	distrRegion* unpaired_comb[N_unc_unpaired];
	distrRegion* unpaired_top[N_unc_unpaired];
	distrRegion* unpaired_full[N_unc_unpaired];

	for (int j = 0; j < N_unc_paired; j++) {

		distrAll* temp_set = paired[j];

		paired_charge[j] = (&(temp_set->charge));
		paired_zbos[j] = (&(temp_set->zbos));
		paired_comb[j] = (&(temp_set->comb));
		paired_top[j] = (&(temp_set->top));
		paired_full[j] = (&(temp_set->full));
	}

	for (int j = 0; j < N_unc_unpaired; j++) {

		distrAll* temp_set = unpaired[j];

		unpaired_charge[j] = &(temp_set->charge);
		unpaired_zbos[j] = &(temp_set->zbos);
		unpaired_comb[j] = &(temp_set->comb);
		unpaired_top[j] = &(temp_set->top);
		unpaired_full[j] = &(temp_set->full);
	}

	draw_Region(set.charge, sig, paired_charge, unpaired_charge);
	draw_Region(set.zbos, sig, paired_zbos, unpaired_zbos);
	draw_Region(set.comb, sig, paired_comb, unpaired_comb);
	draw_Region(set.top, sig, paired_top, unpaired_top);
	draw_Region(set.full, sig, paired_full, unpaired_full);

	return;
}

//-----------------------------------------------------------------------------
void draw_Region(distrRegion &set, distrSigRegion *sig, distrRegion* paired[N_unc_paired],
		distrRegion* unpaired[N_unc_unpaired]) {

	distrSet *paired_3e[N_unc_paired];
	distrSet *paired_2eSS[N_unc_paired];
	distrSet *paired_2eOS[N_unc_paired];
	distrSet *paired_1eSS[N_unc_paired];
	distrSet *paired_1eOS[N_unc_paired];
	distrSet *paired_0e[N_unc_paired];

	distrSet *unpaired_3e[N_unc_unpaired];
	distrSet *unpaired_2eSS[N_unc_unpaired];
	distrSet *unpaired_2eOS[N_unc_unpaired];
	distrSet *unpaired_1eSS[N_unc_unpaired];
	distrSet *unpaired_1eOS[N_unc_unpaired];
	distrSet *unpaired_0e[N_unc_unpaired];

	for (int j = 0; j < N_unc_paired; j++) {

		distrRegion* temp_set = (distrRegion*) paired[j];

		paired_3e[j] = &(temp_set->fs_3e);
		paired_2eSS[j] = &(temp_set->fs_2eSS);
		paired_2eOS[j] = &(temp_set->fs_2eOS);
		paired_1eSS[j] = &(temp_set->fs_1eSS);
		paired_1eOS[j] = &(temp_set->fs_1eOS);
		paired_0e[j] = &(temp_set->fs_0e);
	}

	for (int j = 0; j < N_unc_unpaired; j++) {

		distrRegion* temp_set = (distrRegion*) unpaired[j];

		unpaired_3e[j] = &(temp_set->fs_3e);
		unpaired_2eSS[j] = &(temp_set->fs_2eSS);
		unpaired_2eOS[j] = &(temp_set->fs_2eOS);
		unpaired_1eSS[j] = &(temp_set->fs_1eSS);
		unpaired_1eOS[j] = &(temp_set->fs_1eOS);
		unpaired_0e[j] = &(temp_set->fs_0e);
	}

	draw_FS(set.fs_3e, &(sig->fs_3e), paired_3e, unpaired_3e);
	draw_FS(set.fs_2eSS, &(sig->fs_2eSS), paired_2eSS, unpaired_2eSS);
	draw_FS(set.fs_2eOS, &(sig->fs_2eOS), paired_2eOS, unpaired_2eOS);
	draw_FS(set.fs_1eSS, &(sig->fs_1eSS), paired_1eSS, unpaired_1eSS);
	draw_FS(set.fs_1eOS, &(sig->fs_1eOS), paired_1eOS, unpaired_1eOS);
	draw_FS(set.fs_0e, &(sig->fs_0e), paired_0e, unpaired_0e);

	//Now we can draw the combined distributions for N_jets and met
	//-------------------------------------------------------------

	TObjArray *paired_N_jets_ALL = new TObjArray(N_unc_paired);
	TObjArray *paired_met_ALL = new TObjArray(N_unc_paired);
	TObjArray *paired_metL_ALL = new TObjArray(N_unc_paired);

	TObjArray *unpaired_N_jets_ALL = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_met_ALL = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_metL_ALL = new TObjArray(N_unc_unpaired);

	for (int j = 0; j < N_unc_paired; j++) {

		distrRegion* temp_set = (distrRegion*) paired[j];

		paired_N_jets_ALL->Add(temp_set->ST_N_jets);
		paired_met_ALL->Add(temp_set->ST_met);
		paired_metL_ALL->Add(temp_set->ST_metL);
	}

	for (int j = 0; j < N_unc_unpaired; j++) {

		distrRegion* temp_set = (distrRegion*) unpaired[j];

		unpaired_N_jets_ALL->Add(temp_set->ST_N_jets);
		unpaired_met_ALL->Add(temp_set->ST_met);
		unpaired_metL_ALL->Add(temp_set->ST_metL);
	}

	drawAVariable_short(set.ST_N_jets, set.N_jets, sig->N_jets, paired_N_jets_ALL, unpaired_N_jets_ALL);
	CalcBackgrounds(set.ST_N_jets, paired_N_jets_ALL, unpaired_N_jets_ALL, set);

	drawAVariable_short(set.ST_met, set.met, sig->met, paired_met_ALL, unpaired_met_ALL);
	drawAVariable_short(set.ST_metL, set.metL, sig->metL, paired_metL_ALL, unpaired_metL_ALL);

	delete paired_N_jets_ALL;
	delete paired_met_ALL;
	delete paired_metL_ALL;

	delete unpaired_N_jets_ALL;
	delete unpaired_met_ALL;
	delete unpaired_metL_ALL;

	return;
}

//-----------------------------------------------------------------------------
void draw_FS(distrSet &set, distrSig *sig, distrSet* paired[N_unc_paired], distrSet *unpaired[N_unc_unpaired]) {

	//muons
	TObjArray *paired_mu1_pt = new TObjArray(N_unc_paired);
	TObjArray *paired_mu2_pt = new TObjArray(N_unc_paired);
	TObjArray *paired_mu3_pt = new TObjArray(N_unc_paired);

	TObjArray *paired_mu1_D0 = new TObjArray(N_unc_paired);
	TObjArray *paired_mu2_D0 = new TObjArray(N_unc_paired);
	TObjArray *paired_mu3_D0 = new TObjArray(N_unc_paired);

	/*
	 TObjArray *paired_mu1_ptcone02 = new TObjArray(N_unc_paired);
	 TObjArray *paired_mu2_ptcone02 = new TObjArray(N_unc_paired);
	 TObjArray *paired_mu3_ptcone02 = new TObjArray(N_unc_paired);

	 TObjArray *paired_mu1_ptcone03 = new TObjArray(N_unc_paired);
	 TObjArray *paired_mu2_ptcone03 = new TObjArray(N_unc_paired);
	 TObjArray *paired_mu3_ptcone03 = new TObjArray(N_unc_paired);
	 */

	TObjArray *paired_mu1_etcone02 = new TObjArray(N_unc_paired);
	TObjArray *paired_mu2_etcone02 = new TObjArray(N_unc_paired);
	TObjArray *paired_mu3_etcone02 = new TObjArray(N_unc_paired);

	/*
	 TObjArray *paired_mu1_etcone03 = new TObjArray(N_unc_paired);
	 TObjArray *paired_mu2_etcone03 = new TObjArray(N_unc_paired);
	 TObjArray *paired_mu3_etcone03 = new TObjArray(N_unc_paired);
	 */

	TObjArray *paired_mu1_D0sig = new TObjArray(N_unc_paired);
	TObjArray *paired_mu2_D0sig = new TObjArray(N_unc_paired);
	TObjArray *paired_mu3_D0sig = new TObjArray(N_unc_paired);

	TObjArray *paired_mu_eta = new TObjArray(N_unc_paired);

	TObjArray *paired_mu_phi = new TObjArray(N_unc_paired);

	//electrons
	TObjArray *paired_el1_pt = new TObjArray(N_unc_paired);
	TObjArray *paired_el2_pt = new TObjArray(N_unc_paired);
	TObjArray *paired_el3_pt = new TObjArray(N_unc_paired);

	TObjArray *paired_el1_D0 = new TObjArray(N_unc_paired);
	TObjArray *paired_el2_D0 = new TObjArray(N_unc_paired);
	TObjArray *paired_el3_D0 = new TObjArray(N_unc_paired);

	/*
	 TObjArray *paired_el1_ptcone02 = new TObjArray(N_unc_paired);
	 TObjArray *paired_el2_ptcone02 = new TObjArray(N_unc_paired);
	 TObjArray *paired_el3_ptcone02 = new TObjArray(N_unc_paired);

	 TObjArray *paired_el1_ptcone03 = new TObjArray(N_unc_paired);
	 TObjArray *paired_el2_ptcone03 = new TObjArray(N_unc_paired);
	 TObjArray *paired_el3_ptcone03 = new TObjArray(N_unc_paired);
	 */

	TObjArray *paired_el1_etcone02 = new TObjArray(N_unc_paired);
	TObjArray *paired_el2_etcone02 = new TObjArray(N_unc_paired);
	TObjArray *paired_el3_etcone02 = new TObjArray(N_unc_paired);

	/*
	 TObjArray *paired_el1_etcone03 = new TObjArray(N_unc_paired);
	 TObjArray *paired_el2_etcone03 = new TObjArray(N_unc_paired);
	 TObjArray *paired_el3_etcone03 = new TObjArray(N_unc_paired);
	 */

	TObjArray *paired_el1_isTight = new TObjArray(N_unc_paired);
	TObjArray *paired_el2_isTight = new TObjArray(N_unc_paired);
	TObjArray *paired_el3_isTight = new TObjArray(N_unc_paired);

	TObjArray *paired_el_eta = new TObjArray(N_unc_paired);
	TObjArray *paired_el_phi = new TObjArray(N_unc_paired);

	//misc
	TObjArray *paired_met = new TObjArray(N_unc_paired);
	TObjArray *paired_metL = new TObjArray(N_unc_paired);
	TObjArray *paired_MZ = new TObjArray(N_unc_paired);

	//jets
	TObjArray *paired_N_jets = new TObjArray(N_unc_paired);

	TObjArray *paired_pt_jet1 = new TObjArray(N_unc_paired);
	TObjArray *paired_pt_jet2 = new TObjArray(N_unc_paired);
	TObjArray *paired_pt_jet3 = new TObjArray(N_unc_paired);
	TObjArray *paired_pt_jet4 = new TObjArray(N_unc_paired);

	//--------------------------------------------
	//muons
	TObjArray *unpaired_mu1_pt = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_mu2_pt = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_mu3_pt = new TObjArray(N_unc_unpaired);

	TObjArray *unpaired_mu1_D0 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_mu2_D0 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_mu3_D0 = new TObjArray(N_unc_unpaired);

	/*
	 TObjArray *unpaired_mu1_ptcone02 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_mu2_ptcone02 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_mu3_ptcone02 = new TObjArray(N_unc_unpaired);

	 TObjArray *unpaired_mu1_ptcone03 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_mu2_ptcone03 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_mu3_ptcone03 = new TObjArray(N_unc_unpaired);
	 */

	TObjArray *unpaired_mu1_etcone02 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_mu2_etcone02 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_mu3_etcone02 = new TObjArray(N_unc_unpaired);

	/*
	 TObjArray *unpaired_mu1_etcone03 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_mu2_etcone03 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_mu3_etcone03 = new TObjArray(N_unc_unpaired);
	 */

	TObjArray *unpaired_mu1_D0sig = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_mu2_D0sig = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_mu3_D0sig = new TObjArray(N_unc_unpaired);

	TObjArray *unpaired_mu_eta = new TObjArray(N_unc_unpaired);

	TObjArray *unpaired_mu_phi = new TObjArray(N_unc_unpaired);

	//electrons
	TObjArray *unpaired_el1_pt = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_el2_pt = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_el3_pt = new TObjArray(N_unc_unpaired);

	TObjArray *unpaired_el1_D0 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_el2_D0 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_el3_D0 = new TObjArray(N_unc_unpaired);

	/*
	 TObjArray *unpaired_el1_ptcone02 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_el2_ptcone02 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_el3_ptcone02 = new TObjArray(N_unc_unpaired);

	 TObjArray *unpaired_el1_ptcone03 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_el2_ptcone03 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_el3_ptcone03 = new TObjArray(N_unc_unpaired);
	 */

	TObjArray *unpaired_el1_etcone02 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_el2_etcone02 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_el3_etcone02 = new TObjArray(N_unc_unpaired);

	/*
	 TObjArray *unpaired_el1_etcone03 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_el2_etcone03 = new TObjArray(N_unc_unpaired);
	 TObjArray *unpaired_el3_etcone03 = new TObjArray(N_unc_unpaired);
	 */

	TObjArray *unpaired_el1_isTight = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_el2_isTight = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_el3_isTight = new TObjArray(N_unc_unpaired);

	TObjArray *unpaired_el_eta = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_el_phi = new TObjArray(N_unc_unpaired);

	//misc
	TObjArray *unpaired_met = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_metL = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_MZ = new TObjArray(N_unc_unpaired);

	//jets
	TObjArray *unpaired_N_jets = new TObjArray(N_unc_unpaired);

	TObjArray *unpaired_pt_jet1 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_pt_jet2 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_pt_jet3 = new TObjArray(N_unc_unpaired);
	TObjArray *unpaired_pt_jet4 = new TObjArray(N_unc_unpaired);

	for (int j = 0; j < N_unc_paired; j++) {

		distrSet* temp_set = paired[j];

		//muons
		paired_mu1_pt->Add(temp_set->ST_mu1_pt);
		paired_mu2_pt->Add(temp_set->ST_mu2_pt);
		paired_mu3_pt->Add(temp_set->ST_mu3_pt);

		paired_mu1_D0->Add(temp_set->ST_mu1_D0);
		paired_mu2_D0->Add(temp_set->ST_mu2_D0);
		paired_mu3_D0->Add(temp_set->ST_mu3_D0);

		/*
		 paired_mu1_ptcone02->Add(temp_set->ST_mu1_ptcone02);
		 paired_mu2_ptcone02->Add(temp_set->ST_mu2_ptcone02);
		 paired_mu3_ptcone02->Add(temp_set->ST_mu3_ptcone02);

		 paired_mu1_ptcone03->Add(temp_set->ST_mu1_ptcone03);
		 paired_mu2_ptcone03->Add(temp_set->ST_mu2_ptcone03);
		 paired_mu3_ptcone03->Add(temp_set->ST_mu3_ptcone03);
		 */

		paired_mu1_etcone02->Add(temp_set->ST_mu1_etcone02);
		paired_mu2_etcone02->Add(temp_set->ST_mu2_etcone02);
		paired_mu3_etcone02->Add(temp_set->ST_mu3_etcone02);

		/*
		 paired_mu1_etcone03->Add(temp_set->ST_mu1_etcone03);
		 paired_mu2_etcone03->Add(temp_set->ST_mu2_etcone03);
		 paired_mu3_etcone03->Add(temp_set->ST_mu3_etcone03);
		 */

		paired_mu1_D0sig->Add(temp_set->ST_mu1_D0sig);
		paired_mu2_D0sig->Add(temp_set->ST_mu2_D0sig);
		paired_mu3_D0sig->Add(temp_set->ST_mu3_D0sig);

		paired_mu_eta->Add(temp_set->ST_mu_eta);

		paired_mu_phi->Add(temp_set->ST_mu_phi);

		//electrons
		paired_el1_pt->Add(temp_set->ST_el1_pt);
		paired_el2_pt->Add(temp_set->ST_el2_pt);
		paired_el3_pt->Add(temp_set->ST_el3_pt);

		paired_el1_D0->Add(temp_set->ST_el1_D0);
		paired_el2_D0->Add(temp_set->ST_el2_D0);
		paired_el3_D0->Add(temp_set->ST_el3_D0);

		/*
		 paired_el1_ptcone02->Add(temp_set->ST_el1_ptcone02);
		 paired_el2_ptcone02->Add(temp_set->ST_el2_ptcone02);
		 paired_el3_ptcone02->Add(temp_set->ST_el3_ptcone02);

		 paired_el1_ptcone03->Add(temp_set->ST_el1_ptcone03);
		 paired_el2_ptcone03->Add(temp_set->ST_el2_ptcone03);
		 paired_el3_ptcone03->Add(temp_set->ST_el3_ptcone03);
		 */

		paired_el1_etcone02->Add(temp_set->ST_el1_etcone02);
		paired_el2_etcone02->Add(temp_set->ST_el2_etcone02);
		paired_el3_etcone02->Add(temp_set->ST_el3_etcone02);

		/*
		 paired_el1_etcone03->Add(temp_set->ST_el1_etcone03);
		 paired_el2_etcone03->Add(temp_set->ST_el2_etcone03);
		 paired_el3_etcone03->Add(temp_set->ST_el3_etcone03);
		 */

		paired_el1_isTight->Add(temp_set->ST_el1_isTight);
		paired_el2_isTight->Add(temp_set->ST_el2_isTight);
		paired_el3_isTight->Add(temp_set->ST_el3_isTight);

		paired_el_eta->Add(temp_set->ST_el_eta);
		paired_el_phi->Add(temp_set->ST_el_phi);

		//misc
		paired_met->Add(temp_set->ST_met);
		paired_metL->Add(temp_set->ST_metL);
		paired_MZ->Add(temp_set->ST_MZ);

		//jets
		paired_N_jets->Add(temp_set->ST_N_jets);

		paired_pt_jet1->Add(temp_set->ST_pt_jet1);
		paired_pt_jet2->Add(temp_set->ST_pt_jet2);
		paired_pt_jet3->Add(temp_set->ST_pt_jet3);
		paired_pt_jet4->Add(temp_set->ST_pt_jet4);
	}

	for (int j = 0; j < N_unc_unpaired; j++) {

		distrSet* temp_set = unpaired[j];

		//muons
		unpaired_mu1_pt->Add(temp_set->ST_mu1_pt);
		unpaired_mu2_pt->Add(temp_set->ST_mu2_pt);
		unpaired_mu3_pt->Add(temp_set->ST_mu3_pt);

		unpaired_mu1_D0->Add(temp_set->ST_mu1_D0);
		unpaired_mu2_D0->Add(temp_set->ST_mu2_D0);
		unpaired_mu3_D0->Add(temp_set->ST_mu3_D0);

		/*
		 unpaired_mu1_ptcone02->Add(temp_set->ST_mu1_ptcone02);
		 unpaired_mu2_ptcone02->Add(temp_set->ST_mu2_ptcone02);
		 unpaired_mu3_ptcone02->Add(temp_set->ST_mu3_ptcone02);

		 unpaired_mu1_ptcone03->Add(temp_set->ST_mu1_ptcone03);
		 unpaired_mu2_ptcone03->Add(temp_set->ST_mu2_ptcone03);
		 unpaired_mu3_ptcone03->Add(temp_set->ST_mu3_ptcone03);
		 */

		unpaired_mu1_etcone02->Add(temp_set->ST_mu1_etcone02);
		unpaired_mu2_etcone02->Add(temp_set->ST_mu2_etcone02);
		unpaired_mu3_etcone02->Add(temp_set->ST_mu3_etcone02);

		/*
		 unpaired_mu1_etcone03->Add(temp_set->ST_mu1_etcone03);
		 unpaired_mu2_etcone03->Add(temp_set->ST_mu2_etcone03);
		 unpaired_mu3_etcone03->Add(temp_set->ST_mu3_etcone03);
		 */

		unpaired_mu1_D0sig->Add(temp_set->ST_mu1_D0sig);
		unpaired_mu2_D0sig->Add(temp_set->ST_mu2_D0sig);
		unpaired_mu3_D0sig->Add(temp_set->ST_mu3_D0sig);

		unpaired_mu_eta->Add(temp_set->ST_mu_eta);

		unpaired_mu_phi->Add(temp_set->ST_mu_phi);

		//electrons
		unpaired_el1_pt->Add(temp_set->ST_el1_pt);
		unpaired_el2_pt->Add(temp_set->ST_el2_pt);
		unpaired_el3_pt->Add(temp_set->ST_el3_pt);

		unpaired_el1_D0->Add(temp_set->ST_el1_D0);
		unpaired_el2_D0->Add(temp_set->ST_el2_D0);
		unpaired_el3_D0->Add(temp_set->ST_el3_D0);

		/*
		 unpaired_el1_ptcone02->Add(temp_set->ST_el1_ptcone02);
		 unpaired_el2_ptcone02->Add(temp_set->ST_el2_ptcone02);
		 unpaired_el3_ptcone02->Add(temp_set->ST_el3_ptcone02);

		 unpaired_el1_ptcone03->Add(temp_set->ST_el1_ptcone03);
		 unpaired_el2_ptcone03->Add(temp_set->ST_el2_ptcone03);
		 unpaired_el3_ptcone03->Add(temp_set->ST_el3_ptcone03);
		 */

		unpaired_el1_etcone02->Add(temp_set->ST_el1_etcone02);
		unpaired_el2_etcone02->Add(temp_set->ST_el2_etcone02);
		unpaired_el3_etcone02->Add(temp_set->ST_el3_etcone02);

		/*
		 unpaired_el1_etcone03->Add(temp_set->ST_el1_etcone03);
		 unpaired_el2_etcone03->Add(temp_set->ST_el2_etcone03);
		 unpaired_el3_etcone03->Add(temp_set->ST_el3_etcone03);
		 */

		unpaired_el1_isTight->Add(temp_set->ST_el1_isTight);
		unpaired_el2_isTight->Add(temp_set->ST_el2_isTight);
		unpaired_el3_isTight->Add(temp_set->ST_el3_isTight);

		unpaired_el_eta->Add(temp_set->ST_el_eta);
		unpaired_el_phi->Add(temp_set->ST_el_phi);

		//misc
		unpaired_met->Add(temp_set->ST_met);
		unpaired_metL->Add(temp_set->ST_metL);
		unpaired_MZ->Add(temp_set->ST_MZ);

		//jets
		unpaired_N_jets->Add(temp_set->ST_N_jets);

		unpaired_pt_jet1->Add(temp_set->ST_pt_jet1);
		unpaired_pt_jet2->Add(temp_set->ST_pt_jet2);
		unpaired_pt_jet3->Add(temp_set->ST_pt_jet3);
		unpaired_pt_jet4->Add(temp_set->ST_pt_jet4);
	}

	//-----------------------------------------------------
	//muons
	drawAVariable(set.ST_mu1_pt, set.mu1_pt, sig->mu1_pt, paired_mu1_pt, unpaired_mu1_pt);
	drawAVariable(set.ST_mu2_pt, set.mu2_pt, sig->mu2_pt, paired_mu2_pt, unpaired_mu2_pt);
	drawAVariable(set.ST_mu3_pt, set.mu3_pt, sig->mu3_pt, paired_mu3_pt, unpaired_mu3_pt);

	drawAVariable(set.ST_mu1_D0, set.mu1_D0, sig->mu1_D0, paired_mu1_D0, unpaired_mu1_D0);
	drawAVariable(set.ST_mu2_D0, set.mu2_D0, sig->mu2_D0, paired_mu2_D0, unpaired_mu2_D0);
	drawAVariable(set.ST_mu3_D0, set.mu3_D0, sig->mu3_D0, paired_mu3_D0, unpaired_mu3_D0);

	/*
	 drawAVariable(set.ST_mu1_ptcone02, set.mu1_ptcone02, sig->mu1_ptcone02, paired_mu1_ptcone02, unpaired_mu1_ptcone02);
	 drawAVariable(set.ST_mu2_ptcone02, set.mu2_ptcone02, sig->mu2_ptcone02, paired_mu2_ptcone02, unpaired_mu2_ptcone02);
	 drawAVariable(set.ST_mu3_ptcone02, set.mu3_ptcone02, sig->mu3_ptcone02, paired_mu3_ptcone02, unpaired_mu3_ptcone02);

	 drawAVariable(set.ST_mu1_ptcone03, set.mu1_ptcone03, sig->mu1_ptcone03, paired_mu1_ptcone03, unpaired_mu1_ptcone03);
	 drawAVariable(set.ST_mu2_ptcone03, set.mu2_ptcone03, sig->mu2_ptcone03, paired_mu2_ptcone03, unpaired_mu2_ptcone03);
	 drawAVariable(set.ST_mu3_ptcone03, set.mu3_ptcone03, sig->mu3_ptcone03, paired_mu3_ptcone03, unpaired_mu3_ptcone03);
	 */

	drawAVariable(set.ST_mu1_etcone02, set.mu1_etcone02, sig->mu1_etcone02, paired_mu1_etcone02, unpaired_mu1_etcone02);
	drawAVariable(set.ST_mu2_etcone02, set.mu2_etcone02, sig->mu2_etcone02, paired_mu2_etcone02, unpaired_mu2_etcone02);
	drawAVariable(set.ST_mu3_etcone02, set.mu3_etcone02, sig->mu3_etcone02, paired_mu3_etcone02, unpaired_mu3_etcone02);

	/*
	 drawAVariable(set.ST_mu1_etcone03, set.mu1_etcone03, sig->mu1_etcone03, paired_mu1_etcone03, unpaired_mu1_etcone03);
	 drawAVariable(set.ST_mu2_etcone03, set.mu2_etcone03, sig->mu2_etcone03, paired_mu2_etcone03, unpaired_mu2_etcone03);
	 drawAVariable(set.ST_mu3_etcone03, set.mu3_etcone03, sig->mu3_etcone03, paired_mu3_etcone03, unpaired_mu3_etcone03);
	 */

	drawAVariable(set.ST_mu1_D0sig, set.mu1_D0sig, sig->mu1_D0sig, paired_mu1_D0sig, unpaired_mu1_D0sig);
	drawAVariable(set.ST_mu2_D0sig, set.mu2_D0sig, sig->mu2_D0sig, paired_mu2_D0sig, unpaired_mu2_D0sig);
	drawAVariable(set.ST_mu3_D0sig, set.mu3_D0sig, sig->mu3_D0sig, paired_mu3_D0sig, unpaired_mu3_D0sig);

	drawAVariable(set.ST_mu_eta, set.mu_eta, sig->mu_eta, paired_mu_eta, unpaired_mu_eta);

	drawAVariable(set.ST_mu_phi, set.mu_phi, sig->mu_phi, paired_mu_phi, unpaired_mu_phi);

	//electrons
	drawAVariable(set.ST_el1_pt, set.el1_pt, sig->el1_pt, paired_el1_pt, unpaired_el1_pt);
	drawAVariable(set.ST_el2_pt, set.el2_pt, sig->el2_pt, paired_el2_pt, unpaired_el2_pt);
	drawAVariable(set.ST_el3_pt, set.el3_pt, sig->el3_pt, paired_el3_pt, unpaired_el3_pt);

	drawAVariable(set.ST_el1_D0, set.el1_D0, sig->el1_D0, paired_el1_D0, unpaired_el1_D0);
	drawAVariable(set.ST_el2_D0, set.el2_D0, sig->el2_D0, paired_el2_D0, unpaired_el2_D0);
	drawAVariable(set.ST_el3_D0, set.el3_D0, sig->el3_D0, paired_el3_D0, unpaired_el3_D0);

	/*
	 drawAVariable(set.ST_el1_ptcone02, set.el1_ptcone02, sig->el1_ptcone02, paired_el1_ptcone02, unpaired_el1_ptcone02);
	 drawAVariable(set.ST_el2_ptcone02, set.el2_ptcone02, sig->el2_ptcone02, paired_el2_ptcone02, unpaired_el2_ptcone02);
	 drawAVariable(set.ST_el3_ptcone02, set.el3_ptcone02, sig->el3_ptcone02, paired_el3_ptcone02, unpaired_el3_ptcone02);

	 drawAVariable(set.ST_el1_ptcone03, set.el1_ptcone03, sig->el1_ptcone03, paired_el1_ptcone03, unpaired_el1_ptcone03);
	 drawAVariable(set.ST_el2_ptcone03, set.el2_ptcone03, sig->el2_ptcone03, paired_el2_ptcone03, unpaired_el2_ptcone03);
	 drawAVariable(set.ST_el3_ptcone03, set.el3_ptcone03, sig->el3_ptcone03, paired_el3_ptcone03, unpaired_el3_ptcone03);
	 */

	drawAVariable(set.ST_el1_etcone02, set.el1_etcone02, sig->el1_etcone02, paired_el1_etcone02, unpaired_el1_etcone02);
	drawAVariable(set.ST_el2_etcone02, set.el2_etcone02, sig->el2_etcone02, paired_el2_etcone02, unpaired_el2_etcone02);
	drawAVariable(set.ST_el3_etcone02, set.el3_etcone02, sig->el3_etcone02, paired_el3_etcone02, unpaired_el3_etcone02);

	/*
	 drawAVariable(set.ST_el1_etcone03, set.el1_etcone03, sig->el1_etcone03, paired_el1_etcone03, unpaired_el1_etcone03);
	 drawAVariable(set.ST_el2_etcone03, set.el2_etcone03, sig->el2_etcone03, paired_el2_etcone03, unpaired_el2_etcone03);
	 drawAVariable(set.ST_el3_etcone03, set.el3_etcone03, sig->el3_etcone03, paired_el3_etcone03, unpaired_el3_etcone03);
	 */

	//drawAVariable(set.ST_el1_isTight, set.el1_isTight, sig->el1_isTight, paired_el1_isTight, unpaired_el1_isTight);
	//drawAVariable(set.ST_el2_isTight, set.el2_isTight, sig->el2_isTight, paired_el2_isTight, unpaired_el2_isTight);
	//drawAVariable(set.ST_el3_isTight, set.el3_isTight, sig->el3_isTight, paired_el3_isTight, unpaired_el3_isTight);
	drawAVariable(set.ST_el_eta, set.el_eta, sig->el_eta, paired_el_eta, unpaired_el_eta);
	drawAVariable(set.ST_el_phi, set.el_phi, sig->el_phi, paired_el_phi, unpaired_el_phi);

	//misc
	drawAVariable(set.ST_met, set.met, sig->met, paired_met, unpaired_met);
	drawAVariable(set.ST_metL, set.metL, sig->metL, paired_metL, unpaired_metL);
	drawAVariable(set.ST_MZ, set.MZ, sig->MZ, paired_MZ, unpaired_MZ);

	//jets
	drawAVariable(set.ST_N_jets, set.N_jets, sig->N_jets, paired_N_jets, unpaired_N_jets);

	//if (strstr(set.N_jets[0]->GetName(), "full") != NULL) {
	//std::cout << "\n\n" << set.N_jets[0]->GetName() << "\n";
	//printBackgrounds(set.ST_N_jets, paired_N_jets, unpaired_N_jets);
	CalcBackgrounds(set.ST_N_jets, paired_N_jets, unpaired_N_jets, set);
	//}

	drawAVariable(set.ST_pt_jet1, set.pt_jet1, sig->pt_jet1, paired_pt_jet1, unpaired_pt_jet1);
	drawAVariable(set.ST_pt_jet2, set.pt_jet2, sig->pt_jet2, paired_pt_jet2, unpaired_pt_jet2);
	drawAVariable(set.ST_pt_jet3, set.pt_jet3, sig->pt_jet3, paired_pt_jet3, unpaired_pt_jet3);
	drawAVariable(set.ST_pt_jet4, set.pt_jet4, sig->pt_jet4, paired_pt_jet4, unpaired_pt_jet4);

	//-------------------------------------
	//muons
	delete paired_mu1_pt;
	delete paired_mu2_pt;
	delete paired_mu3_pt;

	delete paired_mu1_D0;
	delete paired_mu2_D0;
	delete paired_mu3_D0;

	/*
	 delete paired_mu1_ptcone02;
	 delete paired_mu2_ptcone02;
	 delete paired_mu3_ptcone02;

	 delete paired_mu1_ptcone03;
	 delete paired_mu2_ptcone03;
	 delete paired_mu3_ptcone03;
	 */

	delete paired_mu1_etcone02;
	delete paired_mu2_etcone02;
	delete paired_mu3_etcone02;

	/*
	 delete paired_mu1_etcone03;
	 delete paired_mu2_etcone03;
	 delete paired_mu3_etcone03;
	 */

	delete paired_mu1_D0sig;
	delete paired_mu2_D0sig;
	delete paired_mu3_D0sig;

	delete paired_mu_eta;
	delete paired_mu_phi;

	//electrons
	delete paired_el1_pt;
	delete paired_el2_pt;
	delete paired_el3_pt;

	delete paired_el1_D0;
	delete paired_el2_D0;
	delete paired_el3_D0;

	/*
	 delete paired_el1_ptcone02;
	 delete paired_el2_ptcone02;
	 delete paired_el3_ptcone02;

	 delete paired_el1_ptcone03;
	 delete paired_el2_ptcone03;
	 delete paired_el3_ptcone03;
	 */

	delete paired_el1_etcone02;
	delete paired_el2_etcone02;
	delete paired_el3_etcone02;

	/*
	 delete paired_el1_etcone03;
	 delete paired_el2_etcone03;
	 delete paired_el3_etcone03;
	 */

	delete paired_el1_isTight;
	delete paired_el2_isTight;
	delete paired_el3_isTight;

	delete paired_el_eta;
	delete paired_el_phi;

	//misc
	delete paired_met;
	delete paired_metL;
	delete paired_MZ;

	//jets
	delete paired_N_jets;

	delete paired_pt_jet1;
	delete paired_pt_jet2;
	delete paired_pt_jet3;
	delete paired_pt_jet4;

	//-------------------------------------
	//muons
	delete unpaired_mu1_pt;
	delete unpaired_mu2_pt;
	delete unpaired_mu3_pt;

	delete unpaired_mu1_D0;
	delete unpaired_mu2_D0;
	delete unpaired_mu3_D0;

	/*
	 delete unpaired_mu1_ptcone02;
	 delete unpaired_mu2_ptcone02;
	 delete unpaired_mu3_ptcone02;

	 delete unpaired_mu1_ptcone03;
	 delete unpaired_mu2_ptcone03;
	 delete unpaired_mu3_ptcone03;
	 */

	delete unpaired_mu1_etcone02;
	delete unpaired_mu2_etcone02;
	delete unpaired_mu3_etcone02;

	/*
	 delete unpaired_mu1_etcone03;
	 delete unpaired_mu2_etcone03;
	 delete unpaired_mu3_etcone03;
	 */

	delete unpaired_mu1_D0sig;
	delete unpaired_mu2_D0sig;
	delete unpaired_mu3_D0sig;

	delete unpaired_mu_eta;
	delete unpaired_mu_phi;

	//electrons
	delete unpaired_el1_pt;
	delete unpaired_el2_pt;
	delete unpaired_el3_pt;

	delete unpaired_el1_D0;
	delete unpaired_el2_D0;
	delete unpaired_el3_D0;

	/*
	 delete unpaired_el1_ptcone02;
	 delete unpaired_el2_ptcone02;
	 delete unpaired_el3_ptcone02;

	 delete unpaired_el1_ptcone03;
	 delete unpaired_el2_ptcone03;
	 delete unpaired_el3_ptcone03;
	 */

	delete unpaired_el1_etcone02;
	delete unpaired_el2_etcone02;
	delete unpaired_el3_etcone02;

	/*
	 delete unpaired_el1_etcone03;
	 delete unpaired_el2_etcone03;
	 delete unpaired_el3_etcone03;
	 */

	delete unpaired_el1_isTight;
	delete unpaired_el2_isTight;
	delete unpaired_el3_isTight;

	delete unpaired_el_eta;
	delete unpaired_el_phi;

	//misc
	delete unpaired_met;
	delete unpaired_metL;
	delete unpaired_MZ;

	//jets
	delete unpaired_N_jets;

	delete unpaired_pt_jet1;
	delete unpaired_pt_jet2;
	delete unpaired_pt_jet3;
	delete unpaired_pt_jet4;

	return;
}

//-----------------------------------------------------------------------------
void drawAVariable(THStack* &st, TH1D* hist[N_SETS], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired) {

	int x_low = -1; // range of the x-axis
	int x_high = -1; // range of they y-axis

	//----------------------------
	if (strstr(hist[0]->GetName(), "_zbos") != NULL && strstr(hist[0]->GetName(), "met_") != NULL) {
		x_low = 1;
		x_high = 14;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_zbos") != NULL && strstr(hist[0]->GetName(), "MZ_") != NULL) {
		x_low = 15;
		x_high = 24;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_zbos") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 1;
		x_high = 6;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_comb") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 1;
		x_high = 7;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_top") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 1;
		x_high = 4;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_full") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 5;
		x_high = 12;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_charge") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 1;
		x_high = 6;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_top") != NULL && strstr(hist[0]->GetName(), "met_") != NULL) {
		x_low = 10;
		x_high = 20;
	}

	//Check if we should use log scale
	bool is_log = false;
	if (strstr(hist[0]->GetName(), "N_jets_") != NULL
			&& (strstr(hist[0]->GetName(), "_comb") != NULL || strstr(hist[0]->GetName(), "_zbos") != NULL))
		is_log = true;

	double sig_max = 0;
	double max = 0;
	if (strstr(hist[0]->GetName(), "_full") != NULL) {
		for (int i = 0; i < N_SIG; i++)
			if (sig[i] != NULL) {
				max = GetMyMaximum(sig[i], x_low, x_high, is_log);
				if (sig_max < max) {
					sig_max = max;
				}
			}
	}

	if ((st->GetMaximum() == 0) && (hist[0]->GetEntries() == 0) && (sig_max == 0)) {
		return;
	}

	TCanvas* plots1 = new TCanvas("c2", "c2", 50, 50, 600, 600);
	TPad* thePad = (TPad*) plots1->cd();
	if (is_log)
		thePad->SetLogy(1);
	else
		thePad->SetLogy(0);

	//----------------------------
	double data_maximum = GetMyMaximum(hist[0], x_low, x_high, is_log);
	double new_maximum = sig_max;

	if (new_maximum < data_maximum)
		new_maximum = data_maximum;

	//st->Draw("9 hist");
	TH1D *err_brs = errorBars(st, paired, unpaired);

	//error-bars are included into the calculations of maximum
	double err_brs_maximum = GetMyMaximum(err_brs, x_low, x_high, is_log);
	if (err_brs_maximum > new_maximum)
		new_maximum = err_brs_maximum;

	//----------------------------
	if (x_low > 0 && x_high > 0) {
		hist[0]->GetXaxis()->SetRange(x_low, x_high);
		err_brs->GetXaxis()->SetRange(x_low, x_high);
		st->GetXaxis()->SetRange(x_low, x_high);
	}

	if (strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		hist[0]->GetXaxis()->SetNdivisions(2 + x_high - x_low);
		st->GetXaxis()->SetNdivisions(2 + x_high - x_low);
	}

	if (is_log) {
		st->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
		err_brs->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
		hist[0]->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.28));
	} else {
		st->SetMaximum(1.28 * new_maximum);
		err_brs->SetMaximum(1.28 * new_maximum);
		hist[0]->SetMaximum(1.28 * new_maximum);
	}

	if (is_log) {
		st->SetMinimum(0.2);
		err_brs->SetMinimum(0.2);
		hist[0]->SetMinimum(0.2);
	} else {
		st->SetMinimum(0);
		err_brs->SetMinimum(0);
		hist[0]->SetMinimum(0);
	}

	hist[0]->Draw("9");
	st->Draw("9 hist same");
	err_brs->Draw("9 same  E2");
	hist[0]->Draw("9 same");

	if (sig_max > 0) {
		for (int i = 0; i < N_SIG; i++)
			sig[i]->Draw("9 same hist");
	}

	//TODO: Store All "N_jet*full" histograms in an output file (DATA+MC+Uncertainties).

	TLegend* leg;
	if (strstr(hist[0]->GetName(), "full") == NULL)
		leg = new TLegend(0.65, 0.55, 0.87, 0.92);
	else
		leg = new TLegend(0.65, 0.45, 0.87, 0.92); //.49
	leg->SetTextAlign(12);
	leg->SetFillColor(0);
	leg->SetTextSize(0.032);
	leg->SetBorderSize(0);

	std::string legendHeader = "";

	if (strstr(hist[0]->GetName(), "_0e_") != NULL)
		legendHeader += "0e, ";
	if (strstr(hist[0]->GetName(), "_1eSS_") != NULL)
		legendHeader += "1eSS, ";
	if (strstr(hist[0]->GetName(), "_1eOS_") != NULL)
		legendHeader += "1eOS, ";
	if (strstr(hist[0]->GetName(), "_2eSS_") != NULL)
		legendHeader += "2eSS, ";
	if (strstr(hist[0]->GetName(), "_2eOS_") != NULL)
		legendHeader += "2eOS, ";
	if (strstr(hist[0]->GetName(), "_3e_") != NULL)
		legendHeader += "3e, ";

	if (strstr(hist[0]->GetName(), "_zbos") != NULL)
		legendHeader += "Z-boson CR";
	if (strstr(hist[0]->GetName(), "_top") != NULL)
		legendHeader += "t#bar{t} CR";
	if (strstr(hist[0]->GetName(), "_comb") != NULL)
		legendHeader += "low-E^{miss}_{T}^{} CR";
	if (strstr(hist[0]->GetName(), "_full") != NULL)
		legendHeader += "Signal Region";

	leg->SetHeader(legendHeader.data());
	//leg->SetHeader(hist[0]->GetName());
	leg->AddEntry(hist[0], "Data, #sqrt{s}=8 TeV", "lep");

	for (int i = 1; i < N_SETS; i++) {
		if (strcmp(description[N_SETS - i].data(), ""))
			leg->AddEntry(hist[N_SETS - i], description[N_SETS - i].data(), "f");
	}

	if (sig_max > 0) {
		for (int i = 0; i < N_SIG; i++)
			leg->AddEntry(sig[i], description_SIG[i].data(), "l");
	}

	leg->Draw("same");

	if (CONF_NOTE) {
		//ATLASLabel(0.23, 0.885, false);
		//myText(0.23 + 0.165, 0.885, 1, "Preliminary");
		//myText(0.25 + 0.165, 0.885, 1, "Internal");
		myText(0.34, 0.83, 1, "#intLdt=13.0 fb^{-1}_{}");
	}

	thePad->RedrawAxis();
	plots1->Update();

	char my_extension[256] = "";
	sprintf(my_extension, "%s.eps", hist[0]->GetName());
	plots1->Print(my_extension);

	delete plots1;

	return;
}

//--------------------------------------------------------------------------------------------------------------------
// A function to draw "merged" stacked plot
void drawAVariable_short(THStack* &st, TH1D* hist[N_SETS], TH1D* sig[N_SIG], TObjArray *paired, TObjArray *unpaired) {

	int x_low = -1; // range of the x-axis
	int x_high = -1; // range of they y-axis

	//Check if we should use log scale
	bool is_log = false;
	if (strstr(hist[0]->GetName(), "N_jets_") != NULL
			&& (strstr(hist[0]->GetName(), "_comb") != NULL || strstr(hist[0]->GetName(), "_zbos") != NULL))
		is_log = true;

	bool draw_ratio = false;
	if (strstr(hist[0]->GetName(), "_comb") != NULL || strstr(hist[0]->GetName(), "_zbos") != NULL
			|| strstr(hist[0]->GetName(), "_top") != NULL)
		draw_ratio = true;

	int color[N_SETS];
	//Specify the colors
	color[1] = kGray + 2; //single top
	color[2] = TColor::GetColor("#00cc00"); //ttbar
	color[3] = TColor::GetColor("#ff0000"); //kRed - 10; //Z->mumu
	color[4] = 0; //TColor::GetColor("#ff0000"); //Z->ee
	color[5] = 0; //TColor::GetColor("#ffff99"); //Z->mumu + bbbar
	color[6] = 0; //TColor::GetColor("#99ccff"); //Z->ee + bbbar
	color[7] = 38; //ttbar Z
	color[8] = 0; //29;
	color[9] = kCyan; //0; //WW, ZZ, WZ
	color[10] = 0;
	color[11] = 0;

//	const int merge_map[N_SETS] = { 0, 0, 0, 0, zmm_ind, zmm_ind, zmm_ind, 0, ttbarW_ind, 0, ww_ind, ww_ind };
//	const string description_short[N_SETS] = { "Data #sqrt{s}=8 TeV", "Wt", "t#bar{t}", "Z+jets", "", "", "",	"t#bar{t}W, t#bar{t}Z", "", "WW, ZZ, WZ", "", "" };

	TH1D *my_hist[N_SETS];
	char my_name[256];

	for (int i = 1; i < N_SETS; i++)
		if (merge_map[i] == 0) {
			sprintf(my_name, "Merged_%s", hist[i]->GetName());
			my_hist[i] = (TH1D*) hist[i]->Clone(my_name);
			my_hist[i]->SetFillColor(color[i]);
		}

	for (int i = 1; i < N_SETS; i++)
		if (merge_map[i] > 0) {
			my_hist[merge_map[i]]->Add(hist[i]);
		}

	//We build Stacked plots here

	sprintf(my_name, "Short_HSTACK_%s", hist[0]->GetName());
	THStack* my_st = new THStack(my_name, "Hstack");

	for (int i = 1; i < N_SETS; i++)
		if (merge_map[i] == 0) {
			my_st->Add(my_hist[i]);
		}

	TCanvas * plots1;
	TPad* thePad1;
	TPad* thePad2 = NULL;

	if (draw_ratio) {
		/////////////
		const double bt_fr2 = 0.35;
		const double vert_size2 = (int) (600. * 0.84 / (1 - bt_fr2));
		/////////////

		plots1 = new TCanvas("c2", "c2", 50, 50, 600, (int) vert_size2);
		plots1->Divide(1, 2);

		thePad1 = (TPad*) plots1->cd(1);
		thePad1->SetPad(0, bt_fr2, 1, 1);
		thePad1->SetBottomMargin(0.0);
		thePad1->SetTopMargin(0.05 * 600. / ((1. - bt_fr2) * vert_size2));

		thePad2 = (TPad*) plots1->cd(2);
		thePad2->SetPad(0, 0.0, 1, bt_fr2);
		thePad2->SetTopMargin(0.0);
		thePad2->SetBottomMargin(0.16 * 600. / (vert_size2 * bt_fr2));

		thePad1 = (TPad*) plots1->cd(1);

	} else {
		plots1 = new TCanvas("c2", "c2", 50, 50, 600, 600);
		thePad1 = (TPad*) plots1->cd();
	}

	thePad1->SetLogy(0);

	if (strstr(hist[0]->GetName(), "N_jets_") != NULL)
		hist[0]->GetXaxis()->SetTitle("Jet Multiplicity");

	my_st->Draw("hist");
	my_st->GetXaxis()->SetTitle(hist[0]->GetXaxis()->GetTitle());
	my_st->GetYaxis()->SetTitle(hist[0]->GetYaxis()->GetTitle());

	if (draw_ratio) {
		my_st->GetXaxis()->SetLabelFont(43);
		my_st->GetXaxis()->SetLabelSize(30);
		my_st->GetYaxis()->SetLabelFont(43);
		my_st->GetYaxis()->SetLabelSize(30);

		my_st->GetXaxis()->SetTitleFont(43);
		my_st->GetXaxis()->SetTitleSize(29);
		my_st->GetYaxis()->SetTitleFont(43);
		my_st->GetYaxis()->SetTitleSize(29);

		my_st->GetYaxis()->SetTitleOffset(2.0);
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_zbos") != NULL && strstr(hist[0]->GetName(), "met_") != NULL) {
		x_low = 1;
		x_high = 14;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_zbos") != NULL && strstr(hist[0]->GetName(), "MZ_") != NULL) {
		x_low = 15;
		x_high = 24;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_zbos") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 1;
		x_high = 6;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_comb") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 1;
		x_high = 6;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_comb") != NULL && strstr(hist[0]->GetName(), "met_") != NULL) {
		x_low = 1;
		x_high = 10;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_top") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 1;
		x_high = 4;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_full") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 5;
		x_high = 12;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_charge") != NULL && strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		x_low = 1;
		x_high = 6;
	}

	//----------------------------
	if (strstr(hist[0]->GetName(), "_top") != NULL && strstr(hist[0]->GetName(), "met_") != NULL) {
		x_low = 10;
		x_high = 20;
	}

	double sig_max = 0;
	double max = 0;
	if (strstr(hist[0]->GetName(), "_full") != NULL) {
		for (int i = 0; i < N_SIG; i++)
			if (sig[i] != NULL) {
				max = GetMyMaximum(sig[i], x_low, x_high, is_log);
				if (sig_max < max) {
					sig_max = max;
				}
			}
	}

	if ((st->GetMaximum() == 0) && (hist[0]->GetEntries() == 0) && (sig_max == 0)) {
		return;
	}

	if (is_log)
		thePad1->SetLogy(1);
	else
		thePad1->SetLogy(0);

	//----------------------------
	TGraphAsymmErrors* my_data = MakePoissonConfidenceLevelErrors(hist[0]);
	double data_maximum = 0;
	if (strstr(hist[0]->GetName(), "_full") != NULL && my_data != NULL)
		data_maximum = GetMyMaximum(my_data);
	else
		data_maximum = GetMyMaximum(hist[0], x_low, x_high, is_log);
	double new_maximum = sig_max;

	if (new_maximum < data_maximum)
		new_maximum = data_maximum;

	//st->Draw("9 hist");
	TH1D *err_brs = errorBars(st, paired, unpaired);

	//error-bars are included into the calculations of maximum
	double err_brs_maximum = GetMyMaximum(err_brs, x_low, x_high, is_log);
	if (err_brs_maximum > new_maximum)
		new_maximum = err_brs_maximum;

	//----------------------------
	if (x_low > 0 && x_high > 0) {
		hist[0]->GetXaxis()->SetRange(x_low, x_high);
		err_brs->GetXaxis()->SetRange(x_low, x_high);
		my_st->GetXaxis()->SetRange(x_low, x_high);
	}

	if (strstr(hist[0]->GetName(), "N_jets_") != NULL) {
		hist[0]->GetXaxis()->SetNdivisions(2 + x_high - x_low);
		my_st->GetXaxis()->SetNdivisions(2 + x_high - x_low);
		err_brs->GetXaxis()->SetNdivisions(2 + x_high - x_low);
		if (my_data != NULL)
			my_data->GetXaxis()->SetNdivisions(2 + x_high - x_low);

		hist[0]->GetXaxis()->CenterLabels();
		my_st->GetXaxis()->CenterLabels();
		err_brs->GetXaxis()->CenterLabels();
		if (my_data != NULL)
			my_data->GetXaxis()->CenterLabels();
	}

	if (is_log) {
		my_st->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.31));
		err_brs->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.31));
		hist[0]->SetMaximum(0.2 * pow(new_maximum / 0.2, 1.31));
	} else {
		my_st->SetMaximum(1.32 * new_maximum);
		err_brs->SetMaximum(1.32 * new_maximum);
		hist[0]->SetMaximum(1.32 * new_maximum);
	}

	if (is_log) {
		my_st->SetMinimum(0.2);
		err_brs->SetMinimum(0.2);
		hist[0]->SetMinimum(0.2);
	} else {

		if (draw_ratio) {
			my_st->SetMinimum(0.001);
			err_brs->SetMinimum(0.001);
			hist[0]->SetMinimum(0.001);
		} else {
			my_st->SetMinimum(0);
			err_brs->SetMinimum(0);
			hist[0]->SetMinimum(0);
		}
	}

	if (draw_ratio) {
		hist[0]->GetXaxis()->SetLabelFont(43);
		hist[0]->GetXaxis()->SetLabelSize(30);
		hist[0]->GetYaxis()->SetLabelFont(43);
		hist[0]->GetYaxis()->SetLabelSize(30);

		hist[0]->GetXaxis()->SetTitleFont(43);
		hist[0]->GetXaxis()->SetTitleSize(29);
		hist[0]->GetYaxis()->SetTitleFont(43);
		hist[0]->GetYaxis()->SetTitleSize(29);

		hist[0]->GetYaxis()->SetTitleOffset(2.0);

	}

	if (draw_ratio) {
		my_data->GetXaxis()->SetLabelFont(43);
		my_data->GetXaxis()->SetLabelSize(30);
		my_data->GetYaxis()->SetLabelFont(43);
		my_data->GetYaxis()->SetLabelSize(30);

		my_data->GetXaxis()->SetTitleFont(43);
		my_data->GetXaxis()->SetTitleSize(29);
		my_data->GetYaxis()->SetTitleFont(43);
		my_data->GetYaxis()->SetTitleSize(29);

		my_data->GetYaxis()->SetTitleOffset(2.0);

	}

	hist[0]->Draw("axis 9");
	my_st->Draw("9 hist same");
	err_brs->Draw("9 same  E2");
	if (my_data != NULL)
		my_data->Draw("9 same P E");
	else
		hist[0]->Draw("9 same");

	if (sig_max > 0) {
		for (int i = 0; i < N_SIG; i++) {

			if (draw_ratio) {
				sig[i]->GetXaxis()->SetLabelFont(43);
				sig[i]->GetXaxis()->SetLabelSize(30);
				sig[i]->GetYaxis()->SetLabelFont(43);
				sig[i]->GetYaxis()->SetLabelSize(30);

				sig[i]->GetXaxis()->SetTitleFont(43);
				sig[i]->GetXaxis()->SetTitleSize(29);
				sig[i]->GetYaxis()->SetTitleFont(43);
				sig[i]->GetYaxis()->SetTitleSize(29);

				sig[i]->GetYaxis()->SetTitleOffset(2.0);
			}

			sig[i]->Draw("9 same hist");
		}
	}

	//TODO: Store All "N_jet*full" histograms in an output file (DATA+MC+Uncertainties).

	TLegend* leg;
	if (strstr(hist[0]->GetName(), "full") == NULL)
		leg = new TLegend(0.58, 0.58, 0.8, 0.92); //65
	else
		leg = new TLegend(0.58, 0.47, 0.8, 0.92); //55 //.49
	leg->SetTextAlign(12);
	leg->SetFillColor(0);
	if (draw_ratio) {
		leg->SetTextFont(43);
		leg->SetTextSize(23);
	} else
		leg->SetTextSize(0.038); //0.032
	leg->SetBorderSize(0);

	std::string legendHeader = "";

	if (strstr(hist[0]->GetName(), "_0e_") != NULL)
		legendHeader += "0e, ";
	if (strstr(hist[0]->GetName(), "_1eSS_") != NULL)
		legendHeader += "1eSS, ";
	if (strstr(hist[0]->GetName(), "_1eOS_") != NULL)
		legendHeader += "1eOS, ";
	if (strstr(hist[0]->GetName(), "_2eSS_") != NULL)
		legendHeader += "2eSS, ";
	if (strstr(hist[0]->GetName(), "_2eOS_") != NULL)
		legendHeader += "2eOS, ";
	if (strstr(hist[0]->GetName(), "_3e_") != NULL)
		legendHeader += "3e, ";

	if (strstr(hist[0]->GetName(), "_zbos") != NULL)
		legendHeader += "Z-boson CR";
	if (strstr(hist[0]->GetName(), "_top") != NULL)
		legendHeader += "t#bar{t} CR";
	if (strstr(hist[0]->GetName(), "_comb") != NULL)
		legendHeader += "Low-E^{miss}_{T}^{} CR";
	if (strstr(hist[0]->GetName(), "_full") != NULL)
		legendHeader += "Signal Region";

	leg->SetHeader(legendHeader.data());
	//leg->SetHeader(hist[0]->GetName());
	leg->AddEntry(hist[0], "Data, #sqrt{s}=8 TeV", "lep");

	for (int i = 1; i < N_SETS; i++) {
		if (merge_map[N_SETS - i] == 0)
			leg->AddEntry(my_hist[N_SETS - i], description_short[N_SETS - i].data(), "f");
	}

	if (sig_max > 0) {
		for (int i = 0; i < N_SIG; i++)
			leg->AddEntry(sig[i], description_SIG[i].data(), "l");
	}

	leg->Draw("same");

	if (CONF_NOTE) {

		if (draw_ratio) {

			TLatex *l1 = new TLatex();
			l1->SetNDC();
			l1->SetTextFont(73);
			l1->SetTextSize(28);
			l1->SetTextColor(kBlack);
			l1->DrawLatex(0.19, 0.865, "ATLAS");

			TLatex *l2 = new TLatex();
			l2->SetNDC();
			l2->SetTextFont(43);
			l2->SetTextSize(28);
			l2->SetTextColor(kBlack);
			l2->DrawLatex(0.19 + 0.155, 0.865, "Preliminary");
			l2->DrawLatex(0.24, 0.765, "#intLdt=13.0 fb^{-1}_{}");

		} else {

			TLatex *l1 = new TLatex();
			l1->SetNDC();
			l1->SetTextFont(73);
			l1->SetTextSize(28);
			l1->SetTextColor(kBlack);
			l1->DrawLatex(0.19, 0.885, "ATLAS");

			TLatex *l2 = new TLatex();
			l2->SetNDC();
			l2->SetTextFont(43);
			l2->SetTextSize(28);
			l2->SetTextColor(kBlack);
			l2->DrawLatex(0.19 + 0.155, 0.885, "Preliminary");
			l2->DrawLatex(0.24, 0.795, "#intLdt=13.0 fb^{-1}_{}");

			//ATLASLabel(0.19, 0.885, false);
			//myText(0.19 + 0.165, 0.885, 1, "Preliminary");
			//myText(0.21 + 0.165, 0.885, 1, "Internal");
			//myText(0.24, 0.795, 1, "#intLdt=13.0 fb^{-1}_{}");
		}

	} else
		myText(0.24, 0.835, 1, "#intLdt=13.0 fb^{-1}_{}");

	thePad1->RedrawAxis();

	//--------------------------------------------------------------------------------
	if (draw_ratio) {
		plots1->cd(2);
		thePad2->SetLogy(0);

		TObjArray* fStack = my_st->GetStack();
		TH1D* h = (TH1D*) fStack->At(fStack->GetSize() - 1)->Clone();

		TH1D* unf_err_brs_njet = (TH1D*) err_brs->Clone("Ratio_unf_err_brs_njet");

		for (int k = 1; k <= unf_err_brs_njet->GetNbinsX(); k++)
			if (h->GetBinContent(k) != 0) {
				unf_err_brs_njet->SetBinContent(k, err_brs->GetBinContent(k) / h->GetBinContent(k));
				unf_err_brs_njet->SetBinError(k, err_brs->GetBinError(k) / h->GetBinContent(k));
			} else {
				unf_err_brs_njet->SetBinContent(k, 1);
				unf_err_brs_njet->SetBinError(k, 0);
			}

		unf_err_brs_njet->SetTitle("");
		unf_err_brs_njet->GetYaxis()->SetTitle("Data/Predictions");
		unf_err_brs_njet->GetYaxis()->SetNdivisions(502);
		if (strstr(hist[0]->GetName(), "N_jets_") != NULL)
			unf_err_brs_njet->GetXaxis()->SetTitle("Jet Multiplicity");

		unf_err_brs_njet->GetXaxis()->SetLabelFont(43);
		unf_err_brs_njet->GetXaxis()->SetLabelSize(30);
		unf_err_brs_njet->GetYaxis()->SetLabelFont(43);
		unf_err_brs_njet->GetYaxis()->SetLabelSize(30);

		unf_err_brs_njet->GetXaxis()->SetTitleFont(43);
		unf_err_brs_njet->GetXaxis()->SetTitleSize(29);
		unf_err_brs_njet->GetYaxis()->SetTitleFont(43);
		unf_err_brs_njet->GetYaxis()->SetTitleSize(29);
		unf_err_brs_njet->GetXaxis()->SetTitleOffset(4.);
		unf_err_brs_njet->GetYaxis()->SetTitleOffset(2.0);

		unf_err_brs_njet->SetMaximum(1.99);
		unf_err_brs_njet->SetMinimum(0.);

		unf_err_brs_njet->Draw("e2 9");

		// straight line
		TH1D* unf_Sherpa = (TH1D*) h->Clone("line");
		for (int k = 1; k <= unf_Sherpa->GetNbinsX(); k++) {
			unf_Sherpa->SetBinContent(k, 1);
			unf_Sherpa->SetBinError(k, 0);
		}
		unf_Sherpa->SetLineWidth(1);
		unf_Sherpa->SetMarkerSize(0);
		unf_Sherpa->SetLineColor(kBlack);
		unf_Sherpa->SetFillColor(0);
		unf_Sherpa->Draw("hist same 9");
		unf_err_brs_njet->Draw("e2  9 same");
		unf_err_brs_njet->Draw("axis same");

		TH1D* unf_BlackBand = (TH1D*) hist[0]->Clone("unf_BlackBand");
		//Need to avoid double counting of the stat uncertainties on data
		//unf_BlackBand->Divide(hResult[0]);
		for (int k = 1; k <= unf_BlackBand->GetNbinsX(); k++)
			if (h->GetBinContent(k) != 0) {
				unf_BlackBand->SetBinContent(k, unf_BlackBand->GetBinContent(k) / h->GetBinContent(k));
				unf_BlackBand->SetBinError(k, unf_BlackBand->GetBinError(k) / h->GetBinContent(k));
			} else {
				unf_BlackBand->SetBinContent(k, 0);
				unf_BlackBand->SetBinError(k, 0);
			}

		unf_BlackBand->Draw("e p9 same");

		thePad2->RedrawAxis();
	}

	thePad1->RedrawAxis();
	plots1->Update();

	char my_extension[256] = "";
	sprintf(my_extension, "%s.eps", hist[0]->GetName());
	plots1->Print(my_extension);

	delete plots1;
	delete my_st;
	//delete unf_Sherpa;
	//delete unf_BlackBand;
	//delete unf_err_brs_njet;
	delete err_brs;
	delete leg;

	//TODO: we have to free memory for my_hist

	return;
}

//-----------------------------------------------------------------------------
//Calculate lower confidence limit
//e.g. to calculate the 68% lower limit for 2 observed events:
//calcPoissonCLLower(2.)
//-----------------------------------------------------------------------------
double calcPoissonCLLower(double obs) {
	const double q = 0.68269;

	double LL = 0.;
	double a = 0;

	if (q == 0.68269 && obs > 1000) {
		LL = obs - sqrt(obs + 0.25) + 0.5;
		return LL;
	}

	if (obs >= 0) {
		a = (1. - q) / 2.; // = 0.025 for 95% confidence interval
		LL = TMath::ChisquareQuantile(a, 2. * obs) / 2.;
	}

	return LL;

}

//-----------------------------------------------------------------------------
//Calculate upper confidence limit
//e.g. to calculate the 68% upper limit for 2 observed events:
//calcPoissonCLUpper(2.)
//-----------------------------------------------------------------------------
double calcPoissonCLUpper(double obs) {
	const double q = 0.68269;

	double UL = 0., a;

	if (q == 0.68269 && obs > 1000) {
		UL = obs + sqrt(obs + 0.25) + 0.5;
		return UL;
	}

	if (obs >= 0.) {
		a = 1. - (1. - q) / 2.; // = 0.025 for 95% confidence interval
		UL = TMath::ChisquareQuantile(a, 2. * (obs + 1.)) / 2.;
	}

	return UL;

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
TGraphAsymmErrors* MakePoissonConfidenceLevelErrors(TH1D* hist) {
	double x_val[256];
	double y_val[256];
	double x_errU[256];
	double x_errL[256];
	double y_errU[256];
	double y_errL[256];

	int n_bins = hist->GetNbinsX();

	double binEntries;
	double binErrUp;
	double binErrLow;
	int n_points = 0;

	for (int b = 1; b <= n_bins; b++) {
		binEntries = hist->GetBinContent(b);
		if (binEntries > 0.) {
			binErrUp = calcPoissonCLUpper(binEntries) - binEntries;
			binErrLow = binEntries - calcPoissonCLLower(binEntries);

			x_val[n_points] = hist->GetXaxis()->GetBinCenter(b);
			y_val[n_points] = binEntries;
			y_errU[n_points] = binErrUp;
			y_errL[n_points] = binErrLow;
			x_errU[n_points] = hist->GetXaxis()->GetBinWidth(b) / 2.; //#hist.GetXaxis().GetBinWidth( b )/2.0  )
			x_errL[n_points] = hist->GetXaxis()->GetBinWidth(b) / 2.; //#hist.GetXaxis().GetBinWidth( b )/2.0  )

			n_points++;
		}
	}

//#print len(x_val), x_val, y_val, x_errL, x_errU, y_errL, y_errU
	if (n_points > 0) {
		TGraphAsymmErrors* dataGraph = new TGraphAsymmErrors(n_points, x_val, y_val, x_errL, x_errU, y_errL, y_errU);
		return dataGraph;
	} else
		return NULL;

}

//-----------------------------------------------------------------------------
void ATLASLabel(Double_t x, Double_t y, bool Preliminary) {
	TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
	l.SetNDC();
	l.SetTextFont(72);
	l.SetTextColor(kBlack);
	l.DrawLatex(x, y, "ATLAS");
	if (Preliminary) {
		TLatex p;
		p.SetNDC();
		p.SetTextFont(42);
		p.SetTextColor(kBlack);
		p.DrawLatex(x + 0.15, y, "Preliminary");
	}

	return;
}

//-----------------------------------------------------------------------------
void myText(Double_t x, Double_t y, Color_t color, const char* text) {
	//Double_t tsize=0.05;
	TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
	l.SetNDC();
	l.SetTextColor(color);
	l.DrawLatex(x, y, text);

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
// Calculates the maximum value and takes into account the legend
//-----------------------------------------------------------------------------

double GetMyMaximum(TGraphAsymmErrors* h) {

	double my_max = 0;
	double in_bin = 0;
	double x, y;

	for (int i = 0; i < h->GetN(); i++)
		if (h->GetPoint(i, x, y) != -1) {
			in_bin = y + h->GetErrorYhigh(i);
			if (in_bin > my_max)
				my_max = in_bin;
		}

	return my_max;
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
TH1D* calculateFractError(TH1D *altered, TH1D *control) {

	TH1D* h = (TH1D*) altered->Clone();

	h->Divide(control);
	h->GetYaxis()->SetTitle("Fractional Uncertainty");

	Int_t N_bins = h->GetNbinsX();

	for (Int_t j = 1; j <= N_bins; j++) {
		Double_t offset = (h->GetBinContent(j)) - 1.;
		if (strstr(altered->GetName(), "JES") == NULL)
			h->SetBinContent(j, offset);
		else {
			//std::cout << "\nFlipping sing for: " << altered->GetName() << "\n";
			h->SetBinContent(j, -offset);
		}
	}

	return h;
}

//-----------------------------------------------------------------------------
double getHistIntegral(TH1D* h) {

	return h->Integral(0, h->GetNbinsX() + 1, ""); // includes underflow and overflow bins
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
double getHistError(TH1D* h) {

	double error = 0;
	for (int i = 0; i <= h->GetNbinsX() + 1; i++) // includes underflow and overflow bins
		error += pow(h->GetBinError(i), 2);

	return sqrt(error);

}

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
// Here we print out the number of background events
//-----------------------------------------------------------------------------
void printBackgrounds(THStack* central, TObjArray *paired, TObjArray *unpaired) {

	TList* cList = central->GetHists();

	double syst_up = 0;
	double syst_dn = 0;
	double mean = 0;
	double value = 0;

	double total = 0;
	double total_stat = 0;
	double total_syst_up = 0;
	double total_syst_dn = 0;

	int n_bins;

	Int_t N_unc_paird = paired->GetSize();
	Int_t N_unc_unpaird = unpaired->GetSize();

	// TList* of TH1*
	for (int i = 0; i < (N_SETS - 1); i++) {

		syst_up = 0;
		syst_dn = 0;
		TH1D* hc = (TH1D*) cList->At(i);
		n_bins = hc->GetNbinsX();
		mean = hc->Integral(0, 1 + n_bins);
		total += mean;

		//paired systematics
		for (int j = 0; j < N_unc_paird; j++) {

			THStack* st = (THStack*) paired->At(j);
			TList* pList = st->GetHists();
			TH1D* hp = (TH1D*) pList->At(i);
			n_bins = hp->GetNbinsX();
			value = hp->Integral(0, n_bins + 1);

			//p or m JES
			if (value > mean)
				syst_up += pow(value - mean, 2);
			else
				syst_dn += pow(value - mean, 2);

			//uncertainty foe the sum of the contributions
			if (i == (N_SETS - 2)) { // now "total" includes all the contributions
				TObjArray* fStack = st->GetStack();
				TH1D* ht = (TH1D*) fStack->At(fStack->GetSize() - 1);
				n_bins = ht->GetNbinsX();
				double t_value = ht->Integral(0, n_bins + 1);

				if (t_value > total)
					total_syst_up += pow(total - t_value, 2);
				else
					total_syst_up += pow(total - t_value, 2);
			}

		}

		//unpaired systematics
		for (int j = 0; j < N_unc_unpaird; j++) {

			THStack* st = (THStack*) unpaired->At(j);
			TList* uList = st->GetHists();
			TH1D* hp = (TH1D*) uList->At(i);
			n_bins = hp->GetNbinsX();
			value = hp->Integral(0, n_bins + 1);

			syst_up += pow(value - mean, 2);
			syst_dn += pow(value - mean, 2);

			//uncertainty foe the sum of the contributions
			if (i == (N_SETS - 2)) { // now "total" includes all the contributions
				TObjArray* fStack = st->GetStack();
				TH1D* ht = (TH1D*) fStack->At(fStack->GetSize() - 1);
				n_bins = ht->GetNbinsX();
				double t_value = ht->Integral(0, n_bins + 1);
				total_syst_dn += pow(total - t_value, 2);
				total_syst_dn += pow(total - t_value, 2);
			}

		}

		syst_up = sqrt(syst_up);
		syst_dn = sqrt(syst_dn);

		std::cout << "\n " << description[i + 1] << " & " << mean << " $\\pm$ " << getHistError((TH1D*) cList->At(i))
				<< " $^{+" << syst_up << "}_{-" << syst_dn << "}$";

		total_stat += pow(getHistError((TH1D*) cList->At(i)), 2);
	}

	total_stat = sqrt(total_stat);
	total_syst_up = sqrt(total_syst_up);
	total_syst_dn = sqrt(total_syst_dn);

	std::cout << "\n Total & " << total << " $\\pm$ " << total_stat << " $^{+" << total_syst_up << "}_{-" << total_syst_dn
			<< "}$";

	return;

}

//-----------------------------------------------------------------------------
// Here we print out the number of background events
//-----------------------------------------------------------------------------
void CalcBackgrounds(THStack* central, TObjArray *paired, TObjArray *unpaired, distrSet &my_set) {

	TList* cList = central->GetHists();

	int n_bins;

	double syst_up = 0;
	double syst_dn = 0;
	double mean = 0;
	double value = 0;

	double total = 0;
	double total_stat = 0;
	double total_syst_up = 0;
	double total_syst_dn = 0;

	Int_t N_unc_paird = paired->GetSize();
	Int_t N_unc_unpaird = unpaired->GetSize();

	// TList* of TH1*
	for (int i = 0; i < (N_SETS - 1); i++) {

		syst_up = 0;
		syst_dn = 0;
		TH1D* hc = (TH1D*) cList->At(i);
		n_bins = hc->GetNbinsX();
		mean = hc->Integral(0, n_bins + 1);
		total += mean;

		//paired systematics
		for (int j = 0; j < N_unc_paird; j++) {

			THStack* st = (THStack*) paired->At(j);
			TList* pList = st->GetHists();
			TH1D* hp = (TH1D*) pList->At(i);
			n_bins = hp->GetNbinsX();
			value = hp->Integral(0, n_bins + 1);

			//p or m JES
			if (value > mean)
				syst_up += pow(value - mean, 2);
			else
				syst_dn += pow(value - mean, 2);

			//uncertainty for the sum of the contributions
			if (i == (N_SETS - 2)) { // now "total" includes all the contributions
				TObjArray* fStack = st->GetStack();
				TH1D* ht = (TH1D*) fStack->At(fStack->GetSize() - 1);
				n_bins = ht->GetNbinsX();
				double t_value = ht->Integral(0, n_bins + 1);

				//Check if "total" is calculated correctly
				{
					TObjArray* my_fStack = central->GetStack();
					TH1D* my_h = (TH1D*) my_fStack->At(my_fStack->GetSize() - 1);
					n_bins = my_h->GetNbinsX();
					double my_total = my_h->Integral(0, n_bins + 1);
					if (fabs((total - my_total) / (total + my_total)) > 1e-3)
						std::cout << "\n\n Total is calculated incorrectly: " << total << " vs " << my_total << "\n";
				}

				if (t_value > total)
					total_syst_up += pow(total - t_value, 2);
				else
					total_syst_dn += pow(total - t_value, 2);

			}

		}

		//unpaired systematics
		for (int j = 0; j < N_unc_unpaird; j++) {

			THStack* st = (THStack*) unpaired->At(j);
			TList* uList = st->GetHists();
			TH1D* hp = (TH1D*) uList->At(i);
			n_bins = hp->GetNbinsX();
			value = hp->Integral(0, n_bins + 1);

			syst_up += pow(value - mean, 2);
			syst_dn += pow(value - mean, 2);

			//uncertainty foe the sum of the contributions
			if (i == (N_SETS - 2)) { // now "total" includes all the contributions
				TObjArray* fStack = st->GetStack();
				TH1D* ht = (TH1D*) fStack->At(fStack->GetSize() - 1);
				n_bins = ht->GetNbinsX();
				double t_value = ht->Integral(0, n_bins + 1);
				total_syst_up += pow(total - t_value, 2);
				total_syst_dn += pow(total - t_value, 2);
			}

		}

		syst_up = sqrt(syst_up);
		syst_dn = sqrt(syst_dn);

		//std::cout << "\n " << description[i + 1] << " & " << mean << " $\\pm$ " << getHistError((TH1D*) cList->At(i))
		//		<< " $^{+" << syst_up << "}_{-" << syst_dn << "}$";

		my_set.backgr_mean[i + 1] = mean;
		my_set.backgr_stat[i + 1] = getHistError((TH1D*) cList->At(i));
		my_set.backgr_systup[i + 1] = syst_up;
		my_set.backgr_systdn[i + 1] = syst_dn;

		total_stat += pow(getHistError((TH1D*) cList->At(i)), 2);
	}

	total_stat = sqrt(total_stat);
	total_syst_up = sqrt(total_syst_up);
	total_syst_dn = sqrt(total_syst_dn);

	my_set.backgr_mean[N_SETS] = total;
	my_set.backgr_stat[N_SETS] = total_stat;
	my_set.backgr_systup[N_SETS] = total_syst_up;
	my_set.backgr_systdn[N_SETS] = total_syst_dn;

	//std::cout << "\n Total & " << total << " $\\pm$ " << total_stat << " $^{+" << total_syst_up << "}_{-" << total_syst_dn	<< "}$";

	return;

}

//-----------------------------------------------------------------------------
// Here we print out the number of background events
//-----------------------------------------------------------------------------
void CalcBackgrounds(THStack* central, TObjArray *paired, TObjArray *unpaired, distrRegion &my_set) {

	TList* cList = central->GetHists();

	double syst_up = 0;
	double syst_dn = 0;
	double mean = 0;
	double value = 0;

	int n_bins;

	double total = 0;
	double total_stat = 0;
	double total_syst_up = 0;
	double total_syst_dn = 0;

	Int_t N_unc_paird = paired->GetSize();
	Int_t N_unc_unpaird = unpaired->GetSize();

	// TList* of TH1*
	for (int i = 0; i < (N_SETS - 1); i++) {

		syst_up = 0;
		syst_dn = 0;
		TH1D* hc = (TH1D*) cList->At(i);
		n_bins = hc->GetNbinsX();
		mean = hc->Integral(0, n_bins + 1);
		total += mean;

		//paired systematics
		for (int j = 0; j < N_unc_paird; j++) {

			THStack* st = (THStack*) paired->At(j);
			TList* pList = st->GetHists();
			TH1D* hp = (TH1D*) pList->At(i);
			n_bins = hp->GetNbinsX();
			value = hp->Integral(0, n_bins + 1);

			//p or m JES
			if (value > mean)
				syst_up += pow(value - mean, 2);
			else
				syst_dn += pow(value - mean, 2);

			//uncertainty for the sum of the contributions
			if (i == (N_SETS - 2)) { // now "total" includes all the contributions
				TObjArray* fStack = st->GetStack();
				TH1D* ht = (TH1D*) fStack->At(fStack->GetSize() - 1);
				n_bins = ht->GetNbinsX();
				double t_value = ht->Integral(0, n_bins + 1);

				//Check if "total" is calculated correctly
				{
					TObjArray* my_fStack = central->GetStack();
					TH1D* my_h = (TH1D*) my_fStack->At(my_fStack->GetSize() - 1);
					n_bins = my_h->GetNbinsX();
					double my_total = my_h->Integral(0, n_bins + 1);
					if (fabs((total - my_total) / (total + my_total)) > 1e-3)
						std::cout << "\n\n Total is calculated incorrectly: " << total << " vs " << my_total << "\n";
				}

				if (t_value > total)
					total_syst_up += pow(total - t_value, 2);
				else
					total_syst_dn += pow(total - t_value, 2);

			}

		}

		//unpaired systematics
		for (int j = 0; j < N_unc_unpaird; j++) {

			THStack* st = (THStack*) unpaired->At(j);
			TList* uList = st->GetHists();
			TH1D* hp = (TH1D*) uList->At(i);
			n_bins = hp->GetNbinsX();
			value = hp->Integral(0, n_bins + 1);

			syst_up += pow(value - mean, 2);
			syst_dn += pow(value - mean, 2);

			//uncertainty foe the sum of the contributions
			if (i == (N_SETS - 2)) { // now "total" includes all the contributions
				TObjArray* fStack = st->GetStack();
				TH1D* ht = (TH1D*) fStack->At(fStack->GetSize() - 1);
				n_bins = ht->GetNbinsX();
				double t_value = ht->Integral(0, n_bins + 1);
				total_syst_up += pow(total - t_value, 2);
				total_syst_dn += pow(total - t_value, 2);
			}

		}

		syst_up = sqrt(syst_up);
		syst_dn = sqrt(syst_dn);

		//std::cout << "\n " << description[i + 1] << " & " << mean << " $\\pm$ " << getHistError((TH1D*) cList->At(i))
		//		<< " $^{+" << syst_up << "}_{-" << syst_dn << "}$";

		my_set.backgr_mean[i + 1] = mean;
		my_set.backgr_stat[i + 1] = getHistError((TH1D*) cList->At(i));
		my_set.backgr_systup[i + 1] = syst_up;
		my_set.backgr_systdn[i + 1] = syst_dn;

		total_stat += pow(getHistError((TH1D*) cList->At(i)), 2);
	}

	total_stat = sqrt(total_stat);
	total_syst_up = sqrt(total_syst_up);
	total_syst_dn = sqrt(total_syst_dn);

	my_set.backgr_mean[N_SETS] = total;
	my_set.backgr_stat[N_SETS] = total_stat;
	my_set.backgr_systup[N_SETS] = total_syst_up;
	my_set.backgr_systdn[N_SETS] = total_syst_dn;

	//std::cout << "\n Total & " << total << " $\\pm$ " << total_stat << " $^{+" << total_syst_up << "}_{-" << total_syst_dn	<< "}$";

	return;

}

//-----------------------------------------------------------------------------
// Here we print out the number of background events
//-----------------------------------------------------------------------------
void printBackgrounds(distrSet *my_set_0e, distrSet *my_set_1eSS, distrSet *my_set_1eOS, distrSet *my_set_2eSS,
		distrSet *my_set_2eOS, distrSet *my_set_3e) {

	// TList* of TH1*
	for (int i = 1; i < N_SETS; i++) {
		std::cout << "\n" << description[i] << " ";

		std::cout << "& " << my_set_0e->backgr_mean[i] << "$\\pm$" << my_set_0e->backgr_stat[i] << "$^{+"
				<< my_set_0e->backgr_systup[i] << "}_{-" << my_set_0e->backgr_systdn[i] << "}$ ";

		std::cout << "& " << my_set_1eSS->backgr_mean[i] << "$\\pm$" << my_set_1eSS->backgr_stat[i] << "$^{+"
				<< my_set_1eSS->backgr_systup[i] << "}_{-" << my_set_1eSS->backgr_systdn[i] << "}$ ";

		std::cout << "& " << my_set_1eOS->backgr_mean[i] << "$\\pm$" << my_set_1eOS->backgr_stat[i] << "$^{+"
				<< my_set_1eOS->backgr_systup[i] << "}_{-" << my_set_1eOS->backgr_systdn[i] << "}$ ";

		std::cout << "& " << my_set_2eSS->backgr_mean[i] << "$\\pm$" << my_set_2eSS->backgr_stat[i] << "$^{+"
				<< my_set_2eSS->backgr_systup[i] << "}_{-" << my_set_2eSS->backgr_systdn[i] << "}$ ";

		std::cout << "& " << my_set_2eOS->backgr_mean[i] << "$\\pm$" << my_set_2eOS->backgr_stat[i] << "$^{+"
				<< my_set_2eOS->backgr_systup[i] << "}_{-" << my_set_2eOS->backgr_systdn[i] << "}$ ";

		std::cout << "& " << my_set_3e->backgr_mean[i] << "$\\pm$" << my_set_3e->backgr_stat[i] << "$^{+"
				<< my_set_3e->backgr_systup[i] << "}_{-" << my_set_3e->backgr_systdn[i] << "}$";

		std::cout << " \\\\ \n";

	}

	std::cout << "\nTotal ";

	std::cout << "& " << my_set_0e->backgr_mean[N_SETS] << "$\\pm$" << my_set_0e->backgr_stat[N_SETS] << "$^{+"
			<< my_set_0e->backgr_systup[N_SETS] << "}_{-" << my_set_0e->backgr_systdn[N_SETS] << "}$ ";

	std::cout << "& " << my_set_1eSS->backgr_mean[N_SETS] << "$\\pm$" << my_set_1eSS->backgr_stat[N_SETS] << "$^{+"
			<< my_set_1eSS->backgr_systup[N_SETS] << "}_{-" << my_set_1eSS->backgr_systdn[N_SETS] << "}$ ";

	std::cout << "& " << my_set_1eOS->backgr_mean[N_SETS] << "$\\pm$" << my_set_1eOS->backgr_stat[N_SETS] << "$^{+"
			<< my_set_1eOS->backgr_systup[N_SETS] << "}_{-" << my_set_1eOS->backgr_systdn[N_SETS] << "}$ ";

	std::cout << "& " << my_set_2eSS->backgr_mean[N_SETS] << "$\\pm$" << my_set_2eSS->backgr_stat[N_SETS] << "$^{+"
			<< my_set_2eSS->backgr_systup[N_SETS] << "}_{-" << my_set_2eSS->backgr_systdn[N_SETS] << "}$ ";

	std::cout << "& " << my_set_2eOS->backgr_mean[N_SETS] << "$\\pm$" << my_set_2eOS->backgr_stat[N_SETS] << "$^{+"
			<< my_set_2eOS->backgr_systup[N_SETS] << "}_{-" << my_set_2eOS->backgr_systdn[N_SETS] << "}$ ";

	std::cout << "& " << my_set_3e->backgr_mean[N_SETS] << "$\\pm$" << my_set_3e->backgr_stat[N_SETS] << "$^{+"
			<< my_set_3e->backgr_systup[N_SETS] << "}_{-" << my_set_3e->backgr_systdn[N_SETS] << "}$";

	std::cout << " \\\\ \n";

	Int_t n_bins = (Int_t)(my_set_0e->N_jets[0]->GetNbinsX());

	std::cout << "\nData ";

	std::cout << "& " << my_set_0e->N_jets[0]->Integral(0, n_bins + 1);

	std::cout << "& " << my_set_1eSS->N_jets[0]->Integral(0, n_bins + 1);

	std::cout << "& " << my_set_1eOS->N_jets[0]->Integral(0, n_bins + 1);

	std::cout << "& " << my_set_2eSS->N_jets[0]->Integral(0, n_bins + 1);

	std::cout << "& " << my_set_2eOS->N_jets[0]->Integral(0, n_bins + 1);

	std::cout << "& " << my_set_3e->N_jets[0]->Integral(0, n_bins + 1);

	std::cout << " \\\\ \n";

	return;

}

//-----------------------------------------------------------------------------
// Here we print out the number of background events
//-----------------------------------------------------------------------------
void printBackgrounds(distrRegion *my_set) {

	// TList* of TH1*
	for (int i = 1; i < N_SETS; i++) {
		std::cout << "\n" << description[i] << " ";

		std::cout << "& " << my_set->backgr_mean[i] << "$\\pm$" << my_set->backgr_stat[i] << "$^{+"
				<< my_set->backgr_systup[i] << "}_{-" << my_set->backgr_systdn[i] << "}$ ";

		std::cout << " \\\\ \n";

	}

	std::cout << "\nTotal ";

	std::cout << "& " << my_set->backgr_mean[N_SETS] << "$\\pm$" << my_set->backgr_stat[N_SETS] << "$^{+"
			<< my_set->backgr_systup[N_SETS] << "}_{-" << my_set->backgr_systdn[N_SETS] << "}$ ";

	std::cout << " \\\\ \n";

	return;

}

/*
 //-----------------------------------------------------------------------------
 void printErrorBars(THStack* central, TObjArray *paired, TObjArray *unpaired, const string* descr) {

 printErrorBars(central, paired, unpaired, descr, -1);
 return;
 }
 //-----------------------------------------------------------------------------
 void printErrorBars(THStack* central, TObjArray *paired, TObjArray *unpaired, const string* descr, Int_t QCD_ind) {

 Int_t N_unc_paird = paired->GetSize();
 Int_t N_unc_unpaird = unpaired->GetSize();

 for (int i = 0; i < N_SETS - 1; i++) {

 TObjArray *paired_h1 = new TObjArray(N_unc_paird);
 TObjArray *unpaired_h1 = new TObjArray(N_unc_unpaird);

 TList* fListC = central->GetHists();
 TH1D* mean = (TH1D*) fListC->At(i);

 //We should use statistical uncertainties provided by the central value
 //paired systematics
 for (int j = 0; j < N_unc_paird; j++) {
 THStack *paired_st = (THStack*) paired->At(j);
 TList* fStackP = paired_st->GetHists();
 paired_h1->Add((TH1D*) fStackP->At(i));
 }

 //unpaired systematics
 for (int j = 0; j < N_unc_unpaird; j++) {
 THStack *unpaired_st = (THStack*) unpaired->At(j);
 TList* fStackU = unpaired_st->GetHists();
 unpaired_h1->Add((TH1D*) fStackU->At(i));
 }

 //here we print our errors for each process
 printErrorBars(mean, paired_h1, unpaired_h1, descr[i + 1].data(), QCD_ind);

 delete paired_h1;
 delete unpaired_h1;

 }

 }
 */

/*
 //-----------------------------------------------------------------------------
 TH1D* errorBars(TH1D* central, TObjArray *paired, TObjArray *unpaired) {

 return errorBars(central, paired, unpaired, true, -1);
 }

 //-----------------------------------------------------------------------------
 TH1D* errorBars(TH1D* central, TObjArray *paired, TObjArray *unpaired, bool incl_stat) {

 return errorBars(central, paired, unpaired, incl_stat, -1);

 }

 //-----------------------------------------------------------------------------
 TH1D* errorBars(TH1D* central, TObjArray *paired, TObjArray *unpaired, bool incl_stat, Int_t QCD_ind) {

 TH1D* h = (TH1D*) central->Clone();
 h->SetTitle(Form("errors_%s", h->GetName()));

 Int_t N_bins = h->GetNbinsX();

 Int_t N_unc_paird = 0;
 if (paired != NULL)
 N_unc_paird = paired->GetSize();
 Int_t N_unc_unpaird = 0;
 if (unpaired != NULL)
 N_unc_unpaird = unpaired->GetSize();

 double pos_err, neg_err, mean_value, value, stat_error;
 for (int i = 1; i <= N_bins; i++) {

 //We should use statistical uncertainties provided by the central value
 stat_error = h->GetBinError(i);

 if (incl_stat) {
 pos_err = pow(stat_error, 2);
 neg_err = pow(stat_error, 2);
 } else {
 pos_err = 0;
 neg_err = 0;
 }
 mean_value = h->GetBinContent(i);

 //paired systematics
 for (int j = 0; j < N_unc_paird; j++) {

 TH1D* hp = (TH1D*) paired->At(j);
 value = hp->GetBinContent(i);

 if (strstr(hp->GetName(), "JES") == NULL) {
 if (value > mean_value)
 pos_err += pow(value - mean_value, 2);
 else
 neg_err += pow(value - mean_value, 2);
 } else {
 //std::cout << "\nFlipping sing for: " << hp->GetName() << "\n";
 if (value > mean_value)
 neg_err += pow(value - mean_value, 2);
 else
 pos_err += pow(value - mean_value, 2);

 }

 }

 //unpaired systematics
 for (int j = 0; j < N_unc_unpaird; j++) {

 TH1D* hp = (TH1D*) unpaired->At(j);
 value = hp->GetBinContent(i);

 if (j != QCD_ind) {
 pos_err += pow(value - mean_value, 2);
 neg_err += pow(value - mean_value, 2);
 } else {
 if (value > mean_value)
 pos_err += pow(value - mean_value, 2);
 else
 neg_err += pow(value - mean_value, 2);
 }
 }

 pos_err = sqrt(pos_err);
 neg_err = sqrt(neg_err);

 h->SetBinContent(i, mean_value + (pos_err - neg_err) / 2.);
 h->SetBinError(i, (pos_err + neg_err) / 2.);
 }

 h->SetFillStyle(3554);
 //h->SetFillStyle(3344);
 h->SetFillColor(1);
 h->SetMarkerSize(0);

 return h;

 }


 */
/*
 //-----------------------------------------------------------------------------
 void printErrorBars(TH1D* central, TObjArray *paired, TObjArray *unpaired, const char* description) {

 printErrorBars(central, paired, unpaired, description, -1);

 return;
 }
 //-----------------------------------------------------------------------------
 // Printing out the errors on the background predictions.
 //-----------------------------------------------------------------------------
 void printErrorBars(TH1D* central, TObjArray *paired, TObjArray *unpaired, const char* description, Int_t QCD_ind) {

 Int_t N_bins = central->GetNbinsX();

 Int_t N_unc_paird = paired->GetSize();
 Int_t N_unc_unpaird = unpaired->GetSize();

 std::cout << description;

 bool separate_lumi = true;

 if (strcmp(description, "QCD") == 0)
 separate_lumi = false;

 double pos_err, neg_err, mean_value, value, stat_error;
 for (int i = 1; i <= N_bins && i <= 6; i++) { //up to 4-jet bin

 //We should use statistical uncertainties provided by the central value
 stat_error = central->GetBinError(i);
 //stat_error = 0; //TEMP
 pos_err = pow(stat_error, 2);
 neg_err = pow(stat_error, 2);
 mean_value = central->GetBinContent(i);

 //paired systematics
 for (int j = 0; j < N_unc_paird; j++) {

 TH1D* hp = (TH1D*) paired->At(j);
 value = hp->GetBinContent(i);

 if (strstr(hp->GetName(), "JES") == NULL) {
 if (value > mean_value)
 pos_err += pow(value - mean_value, 2);
 else
 neg_err += pow(value - mean_value, 2);
 } else {
 if (value > mean_value)
 neg_err += pow(value - mean_value, 2);
 else
 pos_err += pow(value - mean_value, 2);
 }

 }

 //unpaired systematics
 for (int j = 0; j < N_unc_unpaird; j++) {

 TH1D* hp = (TH1D*) unpaired->At(j);
 value = hp->GetBinContent(i);

 if (j != QCD_ind) {
 pos_err += pow(value - mean_value, 2);
 neg_err += pow(value - mean_value, 2);
 } else {
 if (value > mean_value)
 pos_err += pow(value - mean_value, 2);
 else
 neg_err += pow(value - mean_value, 2);
 }
 }

 pos_err = sqrt(pos_err);
 neg_err = sqrt(neg_err);

 if (separate_lumi) {
 pos_err = sqrt(pos_err * pos_err - mean_value * mean_value * 0.034 * 0.034);
 neg_err = sqrt(neg_err * neg_err - mean_value * mean_value * 0.034 * 0.034);
 std::cout << " &  $" << mean_value << "\\pm" << mean_value * 0.034 << "\\:^{+" << pos_err << "}_{-" << neg_err
 << "}$ ";
 } else {
 std::cout << " &  $" << mean_value << "\\:^{+" << pos_err << "}_{-" << neg_err << "}$ ";
 }

 }

 std::cout << " \\\\ \n";

 }

 //-----------------------------------------------------------------------------
 void printXsect(TH1D* jet_mult, TH1D* err_brs, TH1D* jet_mult_pLUMI, TH1D* jet_mult_mLUMI) {

 Int_t n_bins = jet_mult->GetNbinsX();

 for (int i = 1; i <= n_bins; i++) {

 Double_t mean = jet_mult->GetBinContent(i);

 Double_t lumi_up = (jet_mult_mLUMI->GetBinContent(i) - mean);
 Double_t lumi_dn = (-jet_mult_pLUMI->GetBinContent(i) + mean);

 Double_t syst_up = sqrt(pow(-mean + err_brs->GetBinContent(i) + err_brs->GetBinError(i), 2) - pow(
 jet_mult->GetBinError(i), 2) - pow(lumi_up, 2));

 Double_t syst_dn = sqrt(pow(-mean + err_brs->GetBinContent(i) - err_brs->GetBinError(i), 2) - pow(
 jet_mult->GetBinError(i), 2) - pow(lumi_dn, 2));

 std::cout << i << " $" << mean << "\\pm " << jet_mult->GetBinError(i) << "\\:^{+" << syst_up << "}_{-" << syst_dn
 << "}\\:^{+" << lumi_up << "}_{-" << lumi_dn << "}$\n";

 }

 return;
 }

 //-----------------------------------------------------------------------------
 void printXsectNoLumi(TH1D* jet_mult, TH1D* err_brs) {

 Int_t n_bins = jet_mult->GetNbinsX();

 for (int i = 1; i <= n_bins; i++) {

 Double_t mean = jet_mult->GetBinContent(i);

 Double_t syst_up = sqrt(pow(-mean + err_brs->GetBinContent(i) + err_brs->GetBinError(i), 2) - pow(
 jet_mult->GetBinError(i), 2));

 Double_t syst_dn = sqrt(pow(-mean + err_brs->GetBinContent(i) - err_brs->GetBinError(i), 2) - pow(
 jet_mult->GetBinError(i), 2));

 std::cout << i << " $" << mean << "\\pm " << jet_mult->GetBinError(i) << "\\:^{+" << syst_up << "}_{-" << syst_dn
 << "}$\n";

 }

 return;
 }

 */

//-----------------------------------------------------------------------------
void getFakeRateCorr(distrAll* set) {

	my_set = set;

	// Initializing the variables
	const int nfit = 4;
	TMinuit *minuit = new TMinuit(nfit);
	minuit->SetFCN(fcn);
	minuit->SetPrintLevel(1); //TODO: (-1);
	double arglist[10];
	int ierflg = 0;
	minuit->mnexcm("SET NOW", arglist, 0, ierflg); // no warnings

	////Setting up minuit parameters
	Double_t vstart[nfit] = { 1.0, 1.0, 1.0, 1.0 };
	Double_t step[nfit] = { 0.01, 0.01, 0.01, 0.01 };
	TString name[nfit] = { "FR_lf_e", "FR_lf_mu", "FR_hf_e", "FR_hf_mu" };

	//Things i want to keep after fit
	Double_t value[nfit];
	Double_t Error[nfit];

	for (int j = 0; j < nfit; j++) {
		minuit->mnparm(j, name[j], vstart[j], step[j], 0, 0, ierflg);
	}

	//Running the minimization
	//If you don't want to use errors comment out lines with a // --
	//after them.
	arglist[0] = 1; // --
	minuit->mnexcm("CAL", arglist, 1, ierflg); // --
	//Instructs Minuit to call subroutine FCN with the value of IFLAG=<iflag>
	minuit->mnexcm("SET NOG", arglist, 0, ierflg); // --
	//The inverse of SET GRAdient, instructs Minuit not to use the first derivatives calculated
	// by the user in FCN.
	minuit->mnexcm("MINIMIZE", arglist, 0, ierflg);
	//Causes minimization of the function by the method of Migrad, as does the MIGrad command,
	// but switches to the SIMplex method if Migrad fails to converge. Arguments are as for
	// MIGrad. Note that command requires four characters to be unambiguous with MINOs.
	minuit->mnexcm("MIGRAD", arglist, 0, ierflg); // --
	//Causes minimization of the function by the method of Migrad, the most efficient and
	// complete single method, recommended for general functions (see also MINImize). The
	// minimization produces as a by-product the error matrix of the parameters, which is usually
	// reliable unless warning messages are produced. The optional argument [maxcalls] specifies the
	//(approximate) maximum number of function calls after which the calculation will be stopped
	// even if it has not yet converged. The optional argument [tolerance] specifies required
	// tolerance on the function value at the minimum. The default tolerance is 0.1, and the
	// minimization will stop when the estimated vertical distance to the minimum (EDM) is less
	// than 0.001*[tolerance]*UP (see SET ERR).

	Double_t tchi2, edm, errdef;
	Int_t npari = 1, nparx = 7, minuit_status = -1;
	minuit->mnstat(tchi2, edm, errdef, npari, nparx, minuit_status);
	arglist[0] = 10000; // --
	arglist[1] = 5.; // --
	minuit->mnexcm("HESSE", arglist, 1, ierflg); // --
	//Instructs Minuit to calculate, by finite differences, the Hessian or error matrix.
	// That is, it calculates the full matrix of second derivatives of the function with
	// respect to the currently variable parameters, and inverts it, printing out the
	// resulting error matrix. The optional argument [maxcalls] specifies the (approximate)
	// maximum number of function calls after which the calculation will be stopped.
	//	minuit->mnexcm("MINOS", arglist, 2, ierflg); // --
	//Causes a Minos error analysis to be performed on the parameters whose numbers [parno]
	// are specified. If none are specified, Minos errors are calculated for all variable
	// parameters. Minos errors may be expensive to calculate, but are very reliable since
	// they take account of non-linearities in the problem as well as parameter correlations,
	// and are in general asymmetric. The optional argument [maxcalls] specifies the
	// (approximate) maximum number of function calls per parameter requested, after which
	// the calculation will be stopped for that parameter.
	arglist[0] = 1; // --
	minuit->mnexcm("CAL", arglist, 1, ierflg); // --

	//Grab the parameters for this fit
	for (int j = 0; j < nfit; j++) {
		minuit->GetParameter(j, value[j], Error[j]);
		std::cout << "\n " << name[j] << ", par[" << j << "]: " << value[j] << " Error: " << Error[j];
	}

	//Dummy vars that we don't use
	//	Double_t temp1, temp2;
	//Get asymm. error for top mass
	//	minuit->mnerrs(4, mtop_error_p[i], mtop_error_m[i], temp1, temp2);

	minuit->Clear();
	//Delete It
	minuit->Delete();

	return;
}

//////The Chi2 Function (poisson likelyhood)
void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag) {
	// par = the fake rate corrections

	double sf;

	distrAll* set;
	set = my_set;

	// Expected distributions
	//Z-boson CR
	TH1D* met_0e;
	TH1D* met_1eOS;
	TH1D* met_2eOS;
	TH1D* met_3e;

	//low-mEt CR
	TH1D* comb_met_0e;
	TH1D* comb_met_1eOS;
	TH1D* comb_Njet_1eSS;
	TH1D* comb_met_2eOS;
	TH1D* comb_Njet_2eSS;
	TH1D* comb_met_3e;

	//top CR
	TH1D* Njet_0e;
	TH1D* Njet_1eOS;
	TH1D* Njet_1eSS;
	TH1D* Njet_2eOS;
	TH1D* Njet_2eSS;
	TH1D* Njet_3e;

	//Preparing the histograms

	//Z-boson
	met_0e = (TH1D*) set->zbos.fs_0e.met[0]->Clone("test_met_0e");
	met_0e->Reset();
	met_1eOS = (TH1D*) set->zbos.fs_1eOS.met[0]->Clone("test_met_1eOS");
	met_1eOS->Reset();
	met_2eOS = (TH1D*) set->zbos.fs_2eOS.met[0]->Clone("test_met_2eOS");
	met_2eOS->Reset();
	met_3e = (TH1D*) set->zbos.fs_3e.met[0]->Clone("test_met_3e");
	met_3e->Reset();

	//low-mEt CR
	comb_met_0e = (TH1D*) set->comb.fs_0e.met[0]->Clone("test_comb_met_0e");
	comb_met_0e->Reset();
	comb_met_1eOS = (TH1D*) set->comb.fs_1eOS.met[0]->Clone("test_comb_met_1eOS");
	comb_met_1eOS->Reset();
	comb_Njet_1eSS = (TH1D*) set->comb.fs_1eSS.N_jets[0]->Clone("test_comb_Njet_1eSS");
	comb_Njet_1eSS->Reset();
	comb_met_2eOS = (TH1D*) set->comb.fs_2eOS.met[0]->Clone("test_comb_met_2eOS");
	comb_met_2eOS->Reset();
	comb_Njet_2eSS = (TH1D*) set->comb.fs_2eSS.N_jets[0]->Clone("test_comb_Njet_2eSS");
	comb_Njet_2eSS->Reset();
	comb_met_3e = (TH1D*) set->comb.fs_3e.met[0]->Clone("test_comb_met_3e");
	comb_met_3e->Reset();

	//top
	Njet_0e = (TH1D*) set->top.fs_0e.N_jets[0]->Clone("test_Njet_0e");
	Njet_0e->Reset();
	Njet_1eOS = (TH1D*) set->top.fs_1eOS.N_jets[0]->Clone("test_Njet_1eOS");
	Njet_1eOS->Reset();
	Njet_1eSS = (TH1D*) set->top.fs_1eSS.N_jets[0]->Clone("test_Njet_1eSS");
	Njet_1eSS->Reset();
	Njet_2eOS = (TH1D*) set->top.fs_2eOS.N_jets[0]->Clone("test_Njet_2eOS");
	Njet_2eOS->Reset();
	Njet_2eSS = (TH1D*) set->top.fs_2eSS.N_jets[0]->Clone("test_Njet_2eSS");
	Njet_2eSS->Reset();
	Njet_3e = (TH1D*) set->top.fs_3e.N_jets[0]->Clone("test_NBjet_3e");
	Njet_3e->Reset();

	//We re-weight all events here

	//met_0e ---------------------------------------------------------------------------------
	for (int i = 1; i < N_SETS; i++) {

		//corrections to the lepton energies
		sf = 1.;

		if (i == zmm_ind || i == ww_ind) {
			sf = fabs(par[1]); //set.FR_lf_mu;
		}

		if (i == zmmbb_ind || i == ttbar_ind || i == st_Wt_ind) {
			sf = fabs(par[3]); //set.FR_hf_mu;
		}

		met_0e->Add(set->zbos.fs_0e.met[i], sf);
		Njet_0e->Add(set->top.fs_0e.N_jets[i], sf);
		comb_met_0e->Add(set->comb.fs_0e.met[i], sf);

	}

	//1eSS -------------------------------------------------------------------------------------------------
	for (int i = 1; i < N_SETS; i++) {

		//corrections to the lepton energies
		sf = 1.;

		if (i == zmm_ind || i == ww_ind) {
			sf = fabs(par[0]); //set.FR_lf_e;
		}

		if (i == zmmbb_ind) {
			sf = fabs(par[2]); //set.FR_hf_e;
		}

		if (i == ttbar_ind || i == st_Wt_ind) {
			sf = fabs(par[3]); //set.FR_hf_mu;
		}

		Njet_1eSS->Add(set->top.fs_1eSS.N_jets[i], sf);
		comb_Njet_1eSS->Add(set->comb.fs_1eSS.N_jets[i], sf);

	}

	//1eOS -------------------------------------------------------------------------------------------------
	for (int i = 1; i < N_SETS; i++) {

		sf = 1.;

		if (i == zmm_ind) {
			sf = fabs(par[0]); //set.FR_lf_e;
		}

		if (i == zmmbb_ind) {
			sf = fabs(par[2]); //set.FR_hf_e;
		}

		if (i == ttbar_ind || i == st_Wt_ind) {
			//sf = (fabs(par[2]) * em_ee + 2. * fabs(par[3])) / (em_ee + 2.);
			sf = (fabs(par[2]) * em_ee + fabs(par[3])) / (em_ee + 1.);
		}

		if (i == ww_ind) {
			//sf = (fabs(par[0]) * em_ee + 2. * fabs(par[1])) / (em_ee + 2.);
			sf = (fabs(par[0]) * em_ee + fabs(par[1])) / (em_ee + 1.);
		}

		met_1eOS->Add(set->zbos.fs_1eOS.met[i], sf);
		Njet_1eOS->Add(set->top.fs_1eOS.N_jets[i], sf);
		comb_met_1eOS->Add(set->comb.fs_1eOS.met[i], sf);

	}

	//2eSS -------------------------------------------------------------------------------------------------
	for (int i = 1; i < N_SETS; i++) {

		sf = 1.;

		if (i == zee_ind || i == ww_ind) {
			sf = fabs(par[1]); //set.FR_lf_mu;
		}

		if (i == zeebb_ind) {
			sf = fabs(par[3]); //set.FR_hf_mu;
		}

		if (i == ttbar_ind || i == st_Wt_ind) {
			sf = fabs(par[2]); //set.FR_hf_e;
		}

		Njet_2eSS->Add(set->top.fs_2eSS.N_jets[i], sf);
		comb_Njet_2eSS->Add(set->comb.fs_2eSS.N_jets[i], sf);
	}

	//2eOS -------------------------------------------------------------------------------------------------
	for (int i = 1; i < N_SETS; i++) {

		sf = 1.;

		if (i == zee_ind) {
			sf = fabs(par[1]); //set.FR_lf_mu;
		}

		if (i == zeebb_ind) {
			sf = fabs(par[3]); //set.FR_hf_mu;
		}

		if (i == ttbar_ind || i == st_Wt_ind) {
			//sf = (fabs(par[3]) + 2. * em_ee * fabs(par[2])) / (1. + 2. * em_ee);
			sf = (fabs(par[3]) + em_ee * fabs(par[2])) / (1. + em_ee);
		}

		if (i == ww_ind) {
			//sf = (fabs(par[1]) + 2. * em_ee * fabs(par[0])) / (1. + 2. * em_ee);
			sf = (fabs(par[1]) + em_ee * fabs(par[0])) / (1. + em_ee);
		}

		met_2eOS->Add(set->zbos.fs_2eOS.met[i], sf);
		Njet_2eOS->Add(set->top.fs_2eOS.N_jets[i], sf);
		comb_met_2eOS->Add(set->comb.fs_2eOS.met[i], sf);
	}

	//3e -------------------------------------------------------------------------------------------------
	for (int i = 1; i < N_SETS; i++) {

		sf = 1.;

		if (i == zee_ind || i == ww_ind) {
			sf = fabs(par[0]); //set.FR_lf_e;
		}

		if (i == ttbar_ind || i == st_Wt_ind || i == zeebb_ind) {
			sf = fabs(par[2]); //set.FR_hf_e;
		}

		met_3e->Add(set->zbos.fs_3e.met[i], sf);
		Njet_3e->Add(set->top.fs_3e.N_jets[i], sf);
		comb_met_3e->Add(set->comb.fs_3e.met[i], sf);
	}

	// Now we calculate the probability
	f = 0; // chi2

	//zbos
	f += CalLikelihood(met_0e, set->zbos.fs_0e.met[0]);
//	f += CalLikelihood(met_1eOS, set->zbos.fs_1eOS.met[0]);
	f += CalLikelihood(met_2eOS, set->zbos.fs_2eOS.met[0]);
//	f += CalLikelihood(met_3e, set->zbos.fs_3e.met[0]);

	//comb (low-mEt)
	f += CalLikelihood(comb_met_0e, set->comb.fs_0e.met[0]);
	f += CalLikelihood(comb_met_1eOS, set->comb.fs_1eOS.met[0]);
	f += CalLikelihood(comb_Njet_1eSS, set->comb.fs_1eSS.N_jets[0]);
	f += CalLikelihood(comb_met_2eOS, set->comb.fs_2eOS.met[0]);
	f += CalLikelihood(comb_Njet_2eSS, set->comb.fs_2eSS.N_jets[0]);
	f += CalLikelihood(comb_met_3e, set->comb.fs_3e.met[0]);

	//top
	f += CalLikelihood(Njet_0e, set->top.fs_0e.N_jets[0]);
	f += CalLikelihood(Njet_1eOS, set->top.fs_1eOS.N_jets[0]);
	f += CalLikelihood(Njet_1eSS, set->top.fs_1eSS.N_jets[0]);
	f += CalLikelihood(Njet_2eOS, set->top.fs_2eOS.N_jets[0]);
	f += CalLikelihood(Njet_2eSS, set->top.fs_2eSS.N_jets[0]);
	f += CalLikelihood(Njet_3e, set->top.fs_3e.N_jets[0]);

	// clean memory
	delete met_0e;
	delete met_1eOS;
	delete met_2eOS;
	delete met_3e;

	delete comb_met_0e;
	delete comb_met_1eOS;
	delete comb_Njet_1eSS;
	delete comb_met_2eOS;
	delete comb_Njet_2eSS;
	delete comb_met_3e;

	delete Njet_0e;
	delete Njet_1eOS;
	delete Njet_1eSS;
	delete Njet_2eOS;
	delete Njet_2eSS;
	delete Njet_3e;

	return;
}

//-----------------------------------------------------------------------------
Double_t CalLikelihood(TH1D* MC, TH1D* data) {

	double f = 0;

	for (int i = 1; i <= MC->GetNbinsX(); i++) {
		if (MC->GetBinContent(i) > 0) {
			//Uncertainty on the predicted number of events
			double x;
			double loc_prob = 0;
			double gaus;
			double gaus_norm = 0;

			//This is integral is within 2 sigma.
			double max, min;
			max = MC->GetBinContent(i) + 2. * MC->GetBinError(i);
			min = MC->GetBinContent(i) - 2. * MC->GetBinError(i);
			if (min < 0)
				min = 0;

			//we do 30 iterrations for the integral
			for (int j = 0; j < 30; j++) {
				x = min + (max - min) * ((double) j + 0.5) / 30.;
				gaus = TMath::Gaus(x, MC->GetBinContent(i), MC->GetBinError(i), kFALSE);
				gaus_norm += gaus;
				loc_prob += TMath::Poisson(data->GetBinContent(i), x) * gaus;
			}

			loc_prob = loc_prob / gaus_norm;

			f += -log(loc_prob);
		}
	}

	return f;
}

//-----------------------------------------------------------------------------
void SUSY_3l_full() {

#ifdef __CINT__
	gROOT->LoadMacro("AtlasUtils.C");
#endif

	SetAtlasStyle();

	//------------------------------------------
	const string tag = "";
	const string tag_pJES = "_pJES";
	const string tag_mJES = "_mJES";

	const string tag_pJER = "_pJER";

	const string tag_pBA = "_pBA";
	const string tag_mBA = "_mBA";

	const string tag_pEF = "_pEF";
	const string tag_mEF = "_mEF";

	const string tag_pMUR = "_pMUR";
	const string tag_mMUR = "_mMUR";

	const string tag_pMUS = "_pMUS";
	const string tag_mMUS = "_mMUS";

	const string tag_pELR = "_pELR";
	const string tag_mELR = "_mELR";

	const string tag_pELS = "_pELS";
	const string tag_mELS = "_mELS";

	const string tag_pPLUP = "_pPLUP";
	const string tag_mPLUP = "_mPLUP";

	const string tag_pStSc = "_pStSc";
	const string tag_mStSc = "_mStSc";

	const string tag_pStRs = "_pStRs";
	const string tag_mStRs = "_mStRs";

	//const string tag_pJVF = "_pJVF";

	//------------------------------------------

	distrAll det_lvl;

	//JES
	distrAll det_lvl_pJES;
	distrAll det_lvl_mJES;

	//Luminosity
	distrAll det_lvl_pLUMI;
	distrAll det_lvl_mLUMI;

	// XXX
	//distrAll det_lvl_pREF;
	//distrAll det_lvl_mREF;

	//cross-section for ttbar
	distrAll det_lvl_pTTbar;
	distrAll det_lvl_mTTbar;

	//cross-section for ttbar+V
	distrAll det_lvl_pTTbarV;
	distrAll det_lvl_mTTbarV;

	//cross-section for WZ
	distrAll det_lvl_pWZ;
	distrAll det_lvl_mWZ;

	//cross-section for Z+jets
	distrAll det_lvl_pZ;
	distrAll det_lvl_mZ;

	//cross-section for Z+bb+jets
	distrAll det_lvl_pZbb;
	distrAll det_lvl_mZbb;

	//Jet Energy resolution
	distrAll det_lvl_pJER;

	//Muon Reconstruction efficiency
	distrAll det_lvl_pBA;
	distrAll det_lvl_mBA;

	//Electron Reconstruction efficiency
	distrAll det_lvl_pEF;
	distrAll det_lvl_mEF;

	//Muon pt scale
	distrAll det_lvl_pMUS;
	distrAll det_lvl_mMUS;

	//Muon pt resolution
	distrAll det_lvl_pMUR;
	distrAll det_lvl_mMUR;

	//electron pt scale
	distrAll det_lvl_pELS;
	distrAll det_lvl_mELS;

	//electron pt resolution
	distrAll det_lvl_pELR;
	distrAll det_lvl_mELR;

	//#pileup interaction is MC
	distrAll det_lvl_pPLUP;
	distrAll det_lvl_mPLUP;

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

	//Scale of Cell Out
	distrAll det_lvl_pStSc;
	distrAll det_lvl_mStSc;

	//Resolution of Cell Out
	distrAll det_lvl_pStRs;
	distrAll det_lvl_mStRs;

	//PowHeg Instead of Sherpa
	distrAll det_lvl_pGen;

	//distrAll det_lvl_pJVF; //unused

	//SUSY signal
	distrSigRegion signal;

	//------------------------------------------
	getData(det_lvl, tag, "");

	getData(det_lvl_pJES, tag_pJES, "");
	getData(det_lvl_mJES, tag_mJES, "");

	getData(det_lvl_pLUMI, tag, "_pLUMI");
	getData(det_lvl_mLUMI, tag, "_mLUMI");

	//getData(det_lvl_pREF, tag, "_pREF");
	//getData(det_lvl_mREF, tag, "_mREF");

	getData(det_lvl_pTTbar, tag, "_pTTbar");
	getData(det_lvl_mTTbar, tag, "_mTTbar");

	getData(det_lvl_pTTbarV, tag, "_pTTbarV");
	getData(det_lvl_mTTbarV, tag, "_mTTbarV");

	getData(det_lvl_pWZ, tag, "_pWZ");
	getData(det_lvl_mWZ, tag, "_mWZ");

	getData(det_lvl_pZ, tag, "_pZ");
	getData(det_lvl_mZ, tag, "_mZ");

	getData(det_lvl_pZbb, tag, "_pZbb");
	getData(det_lvl_mZbb, tag, "_mZbb");

	getData(det_lvl_pJER, tag_pJER, "");

	//muon reconstruction efficiency
	getData(det_lvl_pBA, tag_pBA, "");
	getData(det_lvl_mBA, tag_mBA, "");

	//electron reco efficiency
	getData(det_lvl_pEF, tag_pEF, "");
	getData(det_lvl_mEF, tag_mEF, "");

	//muon scale and resolution
	getData(det_lvl_pMUS, tag_pMUS, "");
	getData(det_lvl_mMUS, tag_mMUS, "");

	getData(det_lvl_pMUR, tag_pMUR, "");
	getData(det_lvl_mMUR, tag_mMUR, "");

	//electron scale and resolution
	getData(det_lvl_pELS, tag_pELS, "");
	getData(det_lvl_mELS, tag_mELS, "");

	getData(det_lvl_pELR, tag_pELR, "");
	getData(det_lvl_mELR, tag_mELR, "");

	// Pileup
	getData(det_lvl_pPLUP, tag_pPLUP, "");
	getData(det_lvl_mPLUP, tag_mPLUP, "");

	// Fr(HF-->e)
	getData(det_lvl_pFrE, tag, "_pFrE");
	getData(det_lvl_mFrE, tag, "_mFrE");

	// Fr(HF-->mu)
	getData(det_lvl_pFrMu, tag, "_pFrMu");
	getData(det_lvl_mFrMu, tag, "_mFrMu");

	// Fr(LF-->e)
	getData(det_lvl_pFlE, tag, "_pFlE");
	getData(det_lvl_mFlE, tag, "_mFlE");

	// Fr(LF-->mu)
	getData(det_lvl_pFlMu, tag, "_pFlMu");
	getData(det_lvl_mFlMu, tag, "_mFlMu");

	//Scale of Cell Out
	getData(det_lvl_pStSc, tag_pStSc, "");
	getData(det_lvl_mStSc, tag_mStSc, "");

	//Resolution of Cell Out
	getData(det_lvl_pStRs, tag_pStRs, "");
	getData(det_lvl_mStRs, tag_mStRs, "");

	//PowHeg Instead of Sherpa
	getData(det_lvl_pGen, tag, "PowhegPythia_ttbar_plots.root", 128.55e-3, ttbar_ind, "pGen");

	//getData(det_lvl_pJVF, tag_pJVF, "");

	getData_SigRegion(signal, "full", "", -1, -1, "");
	getData_SigRegion(signal, "full", "", -1, -1, "");

	std::cout << "\nDone Reading Files\n";
	//------------------------------------------

	Float_t c_lumi_up = 1. + 0.036;
	Float_t c_lumi_dn = 1. - 0.036;

	scaleLumi(det_lvl_pLUMI, c_lumi_up);
	scaleLumi(det_lvl_mLUMI, c_lumi_dn);

	//scale ttbar x-section
	scaleXSect(det_lvl_pTTbar, ttbar_ind, (1. + 0.10));
	scaleXSect(det_lvl_mTTbar, ttbar_ind, (1. - 0.11));

	scaleXSect(det_lvl_pTTbar, st_Wt_ind, (1. + 0.074));
	scaleXSect(det_lvl_mTTbar, st_Wt_ind, (1. - 0.077));

	//ttbar+V
	scaleXSect(det_lvl_pTTbarV, ttbarV_ind, (1. + 0.4));
	scaleXSect(det_lvl_mTTbarV, ttbarV_ind, (1. - 0.4));

	scaleXSect(det_lvl_pTTbarV, VVV_ind, (1. + 1.0));
	scaleXSect(det_lvl_mTTbarV, VVV_ind, (1. - 1.0));

	//dibosons
	scaleXSect(det_lvl_pWZ, wz_ind, (1. + 0.07));
	scaleXSect(det_lvl_mWZ, wz_ind, (1. - 0.07));

	scaleXSect(det_lvl_pWZ, zz_ind, (1. + 0.05));
	scaleXSect(det_lvl_mWZ, zz_ind, (1. - 0.05));

	scaleXSect(det_lvl_pWZ, ww_ind, (1. + 0.05));
	scaleXSect(det_lvl_mWZ, ww_ind, (1. - 0.05));

	//scale Z cross-sections by 5%
	scaleXSect(det_lvl_pZ, zmm_ind, (1. + 0.05));
	scaleXSect(det_lvl_mZ, zmm_ind, (1. - 0.05));

	scaleXSect(det_lvl_pZ, zee_ind, (1. + 0.05));
	scaleXSect(det_lvl_mZ, zee_ind, (1. - 0.05));

	//scale Zbb cross-sections by 55%
	scaleXSect(det_lvl_pZbb, zmmbb_ind, (1. + 0.55));
	scaleXSect(det_lvl_mZbb, zmmbb_ind, (1. - 0.55));

	scaleXSect(det_lvl_pZbb, zeebb_ind, (1. + 0.55));
	scaleXSect(det_lvl_mZbb, zeebb_ind, (1. - 0.55));

	//Here we set the fake rates --------------------------------------------------
	const double my_FR_lf_e = 0.843555;
	const double my_FR_lf_mu = 1.71937;
	const double my_FR_hf_e = 1.23899;
	const double my_FR_hf_mu = 1.89981;

	setFakeRates(det_lvl, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

//CENTRAL Value
// FR_lf_e, par[0]: 0.843555 Error: 0.0859575 SYST: +0.018754 +0.390565
// FR_lf_mu, par[1]: 1.71937 Error: 0.417123  SYST: +0.03919 +0.02198
// FR_hf_e, par[2]: 1.23899 Error: 0.45744    SYST: +0.71187 +0.22832
// FR_hf_mu, par[3]: 1.89981 Error: 0.414616  SYST: -0.12293 -0.07607

//Full Fit
// FR_lf_e, par[0]: 0.862309 Error: 0.089485
// FR_lf_mu, par[1]: 1.75856 Error: 0.414945
// FR_hf_e, par[2]: 1.95086 Error: 0.419126
// FR_hf_mu, par[3]: 1.77688 Error: 0.397044

//No comb CR
// FR_lf_e, par[0]: 1.23412 Error: 0.249375
// FR_lf_mu, par[1]: 1.74135 Error: 0.416445
// FR_hf_e, par[2]: 1.46731 Error: 0.476233
// FR_hf_mu, par[3]: 1.82374 Error: 0.404559

	setFakeRates(det_lvl_pJES, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mJES, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pLUMI, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mLUMI, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pTTbar, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mTTbar, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pTTbarV, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mTTbarV, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pWZ, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mWZ, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pZ, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mZ, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pZbb, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mZbb, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pJER, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pBA, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mBA, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pEF, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mEF, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pMUS, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mMUS, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pMUR, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mMUR, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pELS, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mELS, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pELR, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mELR, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pPLUP, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mPLUP, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	//heavy-flavor jets
	setFakeRates(det_lvl_pFrE, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e + 0.84617, my_FR_hf_mu);
	setFakeRates(det_lvl_mFrE, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e - 0.45744, my_FR_hf_mu);

	setFakeRates(det_lvl_pFrMu, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu + 0.414616);
	setFakeRates(det_lvl_mFrMu, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu - 0.432456);

	//light-flavor jets
	setFakeRates(det_lvl_pFlE, my_FR_lf_e + 0.39991212913, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mFlE, my_FR_lf_e - 0.0859575, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pFlMu, my_FR_lf_e, my_FR_lf_mu + 0.419, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mFlMu, my_FR_lf_e, my_FR_lf_mu - 0.417, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pStSc, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mStSc, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	setFakeRates(det_lvl_pStRs, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);
	setFakeRates(det_lvl_mStRs, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	//PowHeg
	setFakeRates(det_lvl_pGen, my_FR_lf_e, my_FR_lf_mu, my_FR_hf_e, my_FR_hf_mu);

	bool do_fit = false;
	//------------------------------------------
	weightData(det_lvl);
	//if (do_fit)
	getFakeRateCorr(&det_lvl);

	std::cout << "\nRe-weighting for the JES uncertainties\n";
	weightData(det_lvl_pJES);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pJES);
	std::cout << "\nmJES\n";
	weightData(det_lvl_mJES);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mJES);

	std::cout << "\nRe-weighting for the LUMI uncertainties\n";
	weightData(det_lvl_pLUMI);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pLUMI);
	std::cout << "\nmLUMI\n";
	weightData(det_lvl_mLUMI);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mLUMI);

	std::cout << "\nRe-weighting for the ttbar cross section uncertainties\n";
	weightData(det_lvl_pTTbar);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pTTbar);
	std::cout << "\nmTTbar\n";
	weightData(det_lvl_mTTbar);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mTTbar);

	std::cout << "\nRe-weighting for the ttbar+V cross section uncertainties\n";
	weightData(det_lvl_pTTbarV);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pTTbarV);
	std::cout << "\nmTTbarV\n";
	weightData(det_lvl_mTTbarV);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mTTbarV);

	std::cout << "\nRe-weighting for the VV cross section uncertainties\n";
	weightData(det_lvl_pWZ); //WZ, ZZ, and WW cross-sections
	if (do_fit)
		getFakeRateCorr(&det_lvl_pWZ);
	std::cout << "\nmJWZ\n";
	weightData(det_lvl_mWZ);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mWZ);

	std::cout << "\nRe-weighting for the Z cross section uncertainties\n";
	weightData(det_lvl_pZ); //Z cross-sections
	if (do_fit)
		getFakeRateCorr(&det_lvl_pZ);
	std::cout << "\nmZ\n";
	weightData(det_lvl_mZ);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mZ);

	std::cout << "\nRe-weighting for the Zbb cross section uncertainties\n";
	weightData(det_lvl_pZbb);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pZbb);
	std::cout << "\nmZbb\n";
	weightData(det_lvl_mZbb);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mZbb);

	std::cout << "\nRe-weighting for the JER uncertainties\n";
	weightData(det_lvl_pJER); // Jet energy resolution.
	if (do_fit)
		getFakeRateCorr(&det_lvl_pJER);

	std::cout << "\nRe-weighting for the muon reconstruction efficiency uncertainties\n";
	weightData(det_lvl_pBA);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pBA);
	std::cout << "\nmBA\n";
	weightData(det_lvl_mBA);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mBA);

	std::cout << "\nRe-weighting for the electrons reconstruction efficiency uncertainties\n";
	weightData(det_lvl_pEF);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pEF);
	std::cout << "\nmEF\n";
	weightData(det_lvl_mEF);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mEF);

	std::cout << "\nRe-weighting for the muon momentum scale uncertainties\n";
	weightData(det_lvl_pMUS);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pMUS);
	std::cout << "\nmMUS\n";
	weightData(det_lvl_mMUS);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mMUS);

	std::cout << "\nRe-weighting for the muon momentum resolution uncertainties\n";
	weightData(det_lvl_pMUR);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pMUR);
	std::cout << "\nmMUR\n";
	weightData(det_lvl_mMUR);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mMUR);

	std::cout << "\nRe-weighting for the electron momentum scale uncertainties\n";
	weightData(det_lvl_pELS);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pELS);
	std::cout << "\nmELS\n";
	weightData(det_lvl_mELS);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mELS);

	std::cout << "\nRe-weighting for the electron momentum resolution uncertainties\n";
	weightData(det_lvl_pELR);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pELR);
	std::cout << "\nmELR\n";
	weightData(det_lvl_mELR);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mELR);

	std::cout << "\nRe-weighting for the pileup simulations uncertainties\n";
	//weightData(det_lvl_pPLUP);
	//if (do_fit)
	//	getFakeRateCorr(&det_lvl_pPLUP);
	//std::cout << "\nmPLUP\n";
	weightData(det_lvl_mPLUP);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mPLUP);

	std::cout << "\nRe-weighting for the Fr(HF-->e) uncertainties\n";
	weightData(det_lvl_pFrE);
	std::cout << "\nmFrE\n";
	weightData(det_lvl_mFrE);

	std::cout << "\nRe-weighting for the Fr(HF-->mu) uncertainties\n";
	weightData(det_lvl_pFrMu);
	std::cout << "\nmFrMu\n";
	weightData(det_lvl_mFrMu);

	std::cout << "\nRe-weighting for the Fr(LF-->e) uncertainties\n";
	weightData(det_lvl_pFlE);
	std::cout << "\nmFlE\n";
	weightData(det_lvl_mFlE);

	std::cout << "\nRe-weighting for the Fr(LF-->mu) uncertainties\n";
	weightData(det_lvl_pFlMu);
	std::cout << "\nmFlMu\n";
	weightData(det_lvl_mFlMu);

	std::cout << "\nRe-weighting for the CellOut Scale uncertainties\n";
	weightData(det_lvl_pStSc);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pStSc);
	std::cout << "\nmStSc\n";
	weightData(det_lvl_mStSc);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mStSc);

	std::cout << "\nRe-weighting for the CellOut Resolution uncertainties\n";
	weightData(det_lvl_pStRs);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pStRs);
	std::cout << "\nmStRs\n";
	weightData(det_lvl_mStRs);
	if (do_fit)
		getFakeRateCorr(&det_lvl_mStRs);

	std::cout << "\nRe-weighting for the PowHeg\n";
	weightData(det_lvl_pGen);
	if (do_fit)
		getFakeRateCorr(&det_lvl_pGen);

	//std::cout << "\nRe-weighting for the JVF uncertainties\n";
	//weightData(det_lvl_pJVF);

	std::cout << "\nRe-weighting signal\n";
	weightData_SigRegion(signal);

	std::cout << "\nDone Re-weighting Histograms\n";
	//------------------------------------------
	//Error-bar machinery
	distrAll* paired[N_unc_paired];
	paired[0] = &det_lvl_pJES;
	paired[1] = &det_lvl_mJES;

	paired[2] = &det_lvl_pLUMI;
	paired[3] = &det_lvl_mLUMI;

	paired[4] = &det_lvl_pTTbar;
	paired[5] = &det_lvl_mTTbar;

	paired[6] = &det_lvl_pTTbarV;
	paired[7] = &det_lvl_mTTbarV;

	paired[8] = &det_lvl_pWZ;
	paired[9] = &det_lvl_mWZ;

	paired[10] = &det_lvl_pZ;
	paired[11] = &det_lvl_mZ;

	paired[12] = &det_lvl_pZbb;
	paired[13] = &det_lvl_mZbb;

	paired[14] = &det_lvl_pBA;
	paired[15] = &det_lvl_mBA;

	paired[16] = &det_lvl_pMUS;
	paired[17] = &det_lvl_mMUS;

	paired[18] = &det_lvl_pMUR;
	paired[19] = &det_lvl_mMUR;

	paired[20] = &det_lvl_pEF;
	paired[21] = &det_lvl_mEF;

	paired[22] = &det_lvl_pELS;
	paired[23] = &det_lvl_mELS;

	paired[24] = &det_lvl_pELR;
	paired[25] = &det_lvl_mELR;

	//paired[26] = &det_lvl_pPLUP;
	//paired[27] = &det_lvl_mPLUP;

	paired[26] = &det_lvl_pFrE;
	paired[27] = &det_lvl_mFrE;

	paired[28] = &det_lvl_pFrMu;
	paired[29] = &det_lvl_mFrMu;

	paired[30] = &det_lvl_pFlE;
	paired[31] = &det_lvl_mFlE;

	paired[32] = &det_lvl_pFlMu;
	paired[33] = &det_lvl_mFlMu;

	paired[34] = &det_lvl_pStSc;
	paired[35] = &det_lvl_mStSc;

	paired[36] = &det_lvl_pStRs;
	paired[37] = &det_lvl_mStRs;

	distrAll *unpaired[N_unc_unpaired];

	unpaired[0] = &det_lvl_pJER;
	unpaired[1] = &det_lvl_mPLUP;
	unpaired[2] = &det_lvl_pGen;

	drawObservables(det_lvl, &signal, paired, unpaired);

	//Here we write down the unfolded cross sections into a root file
	TFile f_unfolded_csects = TFile("output_histos.root", "RECREATE");

	det_lvl.backgr_sum->Write();
	det_lvl.data_sum->Write();

	det_lvl_pJES.backgr_sum->Write();
	det_lvl_mJES.backgr_sum->Write();

	det_lvl_pLUMI.backgr_sum->Write();
	det_lvl_mLUMI.backgr_sum->Write();

	det_lvl_pTTbar.backgr_sum->Write();
	det_lvl_mTTbar.backgr_sum->Write();

	det_lvl_pTTbarV.backgr_sum->Write();
	det_lvl_mTTbarV.backgr_sum->Write();

	det_lvl_pWZ.backgr_sum->Write();
	det_lvl_mWZ.backgr_sum->Write();

	det_lvl_pZ.backgr_sum->Write();
	det_lvl_mZ.backgr_sum->Write();

	det_lvl_pZbb.backgr_sum->Write();
	det_lvl_mZbb.backgr_sum->Write();

	det_lvl_pJER.backgr_sum->Write();

	//Muons
	det_lvl_pBA.backgr_sum->Write();
	det_lvl_mBA.backgr_sum->Write();

	det_lvl_pMUS.backgr_sum->Write();
	det_lvl_mMUS.backgr_sum->Write();

	det_lvl_pMUR.backgr_sum->Write();
	det_lvl_mMUR.backgr_sum->Write();

	//Electrons
	det_lvl_pEF.backgr_sum->Write();
	det_lvl_mEF.backgr_sum->Write();

	det_lvl_pELS.backgr_sum->Write();
	det_lvl_mELS.backgr_sum->Write();

	det_lvl_pELR.backgr_sum->Write();
	det_lvl_mELR.backgr_sum->Write();

	//det_lvl_pPLUP.backgr_sum->Write();
	det_lvl_mPLUP.backgr_sum->Write();

	det_lvl_pFrE.backgr_sum->Write();
	det_lvl_mFrE.backgr_sum->Write();

	det_lvl_pFrMu.backgr_sum->Write();
	det_lvl_mFrMu.backgr_sum->Write();

	det_lvl_pStSc.backgr_sum->Write();
	det_lvl_mStSc.backgr_sum->Write();

	det_lvl_pStRs.backgr_sum->Write();
	det_lvl_mStRs.backgr_sum->Write();

	det_lvl_pGen.backgr_sum->Write();

	f_unfolded_csects.Close();

	//----------------------------------------------------------------------

	std::cout << "\n\n ---------------------- ZBOS -------------------- \n\n";
	printBackgrounds(&(det_lvl.zbos.fs_0e), &(det_lvl.zbos.fs_1eSS), &(det_lvl.zbos.fs_1eOS), &(det_lvl.zbos.fs_2eSS),
			&(det_lvl.zbos.fs_2eOS), &(det_lvl.zbos.fs_3e));

	std::cout << "\n\n ---------------------- ZBOS 3l ----------------- \n\n";
	printBackgrounds(&(det_lvl.zbos));
	std::cout << "\n\n";

	std::cout << "\n\n ---------------------- low-MET -------------------- \n\n";
	printBackgrounds(&(det_lvl.comb.fs_0e), &(det_lvl.comb.fs_1eSS), &(det_lvl.comb.fs_1eOS), &(det_lvl.comb.fs_2eSS),
			&(det_lvl.comb.fs_2eOS), &(det_lvl.comb.fs_3e));

	std::cout << "\n\n ---------------------- low-MET 3l ----------------- \n\n";
	printBackgrounds(&(det_lvl.comb));
	std::cout << "\n\n";

	std::cout << "\n\n ---------------------- TOP -------------------- \n\n";
	printBackgrounds(&(det_lvl.top.fs_0e), &(det_lvl.top.fs_1eSS), &(det_lvl.top.fs_1eOS), &(det_lvl.top.fs_2eSS),
			&(det_lvl.top.fs_2eOS), &(det_lvl.top.fs_3e));

	std::cout << "\n\n ---------------------- TOP 3l ----------------- \n\n";
	printBackgrounds(&(det_lvl.top));
	std::cout << "\n\n";

	std::cout << "\n\n ---------------------- FULL -------------------- \n\n";
	printBackgrounds(&(det_lvl.full.fs_0e), &(det_lvl.full.fs_1eSS), &(det_lvl.full.fs_1eOS), &(det_lvl.full.fs_2eSS),
			&(det_lvl.full.fs_2eOS), &(det_lvl.full.fs_3e));
	std::cout << "\n\n";

	std::cout << "\n\n ---------------------- FULL 3l ----------------- \n\n";
	printBackgrounds(&(det_lvl.full));
	std::cout << "\n\n";

	gSystem->Exit(0);

	return;
}
