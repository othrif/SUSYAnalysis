#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <strstream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>

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

#include "my_objects.h" //Calls METUtility.h, AnalysisMuonEfficiencyScaleFactors.h, SmearingClass.h, EnergyRescalerUpgrade.h
#include "myevt.h"

//extern float xbins_p[30];
//extern int n_p_bins;

//---------------------------------------------------------------------------
// Booking Jet histograms
//---------------------------------------------------------------------------
void BookHistos_SystSet(const char* tag) {

	char new_tag[256];

	BookHistos(tag); // pre-selected events; 1 chargeated muon in event

	sprintf(new_tag, "%s_pJES", tag);
	BookHistos(new_tag);
	sprintf(new_tag, "%s_mJES", tag);
	BookHistos(new_tag);

	sprintf(new_tag, "%s_pJER", tag);
	BookHistos(new_tag); // Jet Energy (Momentum) Resolution

	sprintf(new_tag, "%s_pMUR", tag);
	BookHistos(new_tag); // Muon Momentum Resolution
	sprintf(new_tag, "%s_mMUR", tag);
	BookHistos(new_tag); // Muon Momentum Resolution

	sprintf(new_tag, "%s_pMUS", tag);
	BookHistos(new_tag); // momentum scale of the muon
	sprintf(new_tag, "%s_mMUS", tag);
	BookHistos(new_tag);

	sprintf(new_tag, "%s_pELR", tag);
	BookHistos(new_tag); // Electron Momentum Resolution
	sprintf(new_tag, "%s_mELR", tag);
	BookHistos(new_tag); // Electron Momentum Resolution

	sprintf(new_tag, "%s_pELS", tag);
	BookHistos(new_tag); // momentum scale of the Electron
	sprintf(new_tag, "%s_mELS", tag);
	BookHistos(new_tag);

	//muon reconstruction efficiency
	sprintf(new_tag, "%s_pBA", tag);
	BookHistos(new_tag);
	sprintf(new_tag, "%s_mBA", tag);
	BookHistos(new_tag);

	//electron reconstruction efficiency
	sprintf(new_tag, "%s_pEF", tag);
	BookHistos(new_tag);
	sprintf(new_tag, "%s_mEF", tag);
	BookHistos(new_tag);

	//btag efficiency
	sprintf(new_tag, "%s_pBT", tag);
	BookHistos(new_tag);
	sprintf(new_tag, "%s_mBT", tag);
	BookHistos(new_tag);

	//sprintf(new_tag, "%s_pJVF", tag);
	//BookHistos(new_tag); // Jet vertex fraction cut is released in data

	//electron reconstruction efficiency
	sprintf(new_tag, "%s_pPLUP", tag);
	BookHistos(new_tag);
	sprintf(new_tag, "%s_mPLUP", tag);
	BookHistos(new_tag);

	//Cell Out (soft term) scale
	sprintf(new_tag, "%s_pStSc", tag);
	BookHistos(new_tag);
	sprintf(new_tag, "%s_mStSc", tag);
	BookHistos(new_tag);

	//Cell Out (soft term) resolution
	sprintf(new_tag, "%s_pStRs", tag);
	BookHistos(new_tag);
	sprintf(new_tag, "%s_mStRs", tag);
	BookHistos(new_tag);

	return;
}

void BookHistos(const char* tag) {

	char hname[256];

	sprintf(hname, "ee_%s", tag);
	BookHistos_New(hname);

	sprintf(hname, "em_%s", tag);
	BookHistos_New(hname);

	sprintf(hname, "mm_%s", tag);
	BookHistos_New(hname);

	return;
}

void BookHistos_New(const char* tag) {

	char hname[256];

	sprintf(hname, "real_%s", tag);
	BookHistos_FS(hname);

	sprintf(hname, "chmisid_%s", tag);
	BookHistos_FS(hname);

	sprintf(hname, "fake_e_%s", tag);
	BookHistos_FS(hname);

	sprintf(hname, "fake_m_%s", tag);
	BookHistos_FS(hname);

	return;
}

void BookHistos_FS(const char* tag) {

	const char* name;
	char hname[256];
	TH1D* h1d;
	//TH2D* h2d;
	//TProfile* hp;

	const int n_bins_jet_pt = 10;
	const Double_t jet_pt_bins[n_bins_jet_pt + 1] = { 30., 40., 50., 70., 90., 120., 155., 195., 235., 280., 330. };

	name = "mu1_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 1st muon;p_{T}(#mu1) [GeV];entries", 20, 0, 100);
	h1d->Sumw2();

	name = "mu2_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 2nd muon;p_{T}(#mu2) [GeV];entries", 20, 0, 100);
	h1d->Sumw2();

	name = "mu3_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 3rd muon;p_{T}(#mu3) [GeV];entries", 20, 0, 100);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "el1_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 1st electron;p_{T}(e1) [GeV];entries", 20, 0, 100);
	h1d->Sumw2();

	name = "el2_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 2nd electron;p_{T}(e2) [GeV];entries", 20, 0, 100);
	h1d->Sumw2();

	name = "el3_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 3rd electron;p_{T}(e3) [GeV];entries", 20, 0, 100);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "lep_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the signal leptons;p_{T}(signal leptons) [GeV];entries", 15, 0, 150);
	h1d->Sumw2();

	name = "lep_softest_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the softest lepton;p_{T}(softest lepton) [GeV];entries", 15, 0, 150);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "lep1_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 1st lepton;p_{T}(l1) [GeV];entries", 15, 0, 150);
	h1d->Sumw2();

	name = "lep2_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 2nd lepton;p_{T}(l2) [GeV];entries", 15, 0, 150);
	h1d->Sumw2();

	name = "lep3_pt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "Pt of the 3rd lepton;p_{T}(l3) [GeV];entries", 15, 0, 150);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "mu_eta";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "#eta of muons;#eta(#mu);entries", 25, -2.5, 2.5);
	h1d->Sumw2();

	name = "el_eta";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "#eta of electrons;#eta(e);entries", 25, -2.5, 2.5);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "mu_phi";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "#phi of muons;#phi(#mu) [rad];entries", 30, -3.1416, 3.1416);
	h1d->Sumw2();

	name = "el_phi";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "#phi of electrons;#phi(e) [rad];entries", 30, -3.1416, 3.1416);
	h1d->Sumw2();

	//----------------------------------------------------------------------

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

	//----------------------------------------------------------------------

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

	name = "el1_isTight";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "isTightPP of the 1st electron;tight++;entries", 2, -.5, 1.5);
	h1d->Sumw2();

	name = "el2_isTight";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "isTightPP of the 2nd electron;tight++;entries", 2, -.5, 1.5);
	h1d->Sumw2();

	name = "el3_isTight";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "isTightPP of the 3rd electron;tight++;entries", 2, -.5, 1.5);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	name = "mu1_ptcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone02 of the 1st muon;ptcone02/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "mu2_ptcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone02 of the 2nd muon;ptcone02/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "mu3_ptcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone02 of the 3rd muon;ptcone02/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "el1_ptcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone02 of the 1st electron;ptcone02/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "el2_ptcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone02 of the 2nd electron;ptcone02/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "el3_ptcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone02 of the 3rd electron;ptcone02/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "lep1_ptcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone02 of the 1st lepton;ptcone02/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "lep2_ptcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone02 of the 2nd lepton;ptcone02/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "lep3_ptcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone02 of the 3rd lepton;ptcone02/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	name = "mu1_etcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone02 of the 1st muon;etcone02/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "mu2_etcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone02 of the 2nd muon;etcone02/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "mu3_etcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone02 of the 3rd muon;etcone02/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "el1_etcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone02 of the 1st electron;etcone02/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "el2_etcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone02 of the 2nd electron;etcone02/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "el3_etcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone02 of the 3rd electron;etcone02/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "lep1_etcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone02 of the 1st lepton;etcone02/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "lep2_etcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone02 of the 2nd lepton;etcone02/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "lep3_etcone02";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone02 of the 3rd lepton;etcone02/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	name = "mu1_ptcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone03 of the 1st muon;ptcone03/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "mu2_ptcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone03 of the 2nd muon;ptcone03/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "mu3_ptcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone03 of the 3rd muon;ptcone03/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "el1_ptcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone03 of the 1st electron;ptcone03/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "el2_ptcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone03 of the 2nd electron;ptcone03/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "el3_ptcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone03 of the 3rd electron;ptcone03/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "lep1_ptcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone03 of the 1st lepton;ptcone03/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "lep2_ptcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone03 of the 2nd lepton;ptcone03/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	name = "lep3_ptcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "ptcone03 of the 3rd lepton;ptcone03/pt;entries", 20, 0, 0.1);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	name = "mu1_etcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone03 of the 1st muon;etcone03/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "mu2_etcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone03 of the 2nd muon;etcone03/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "mu3_etcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone03 of the 3rd muon;etcone03/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "el1_etcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone03 of the 1st electron;etcone03/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "el2_etcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone03 of the 2nd electron;etcone03/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "el3_etcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone03 of the 3rd electron;etcone03/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "lep1_etcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone03 of the 1st lepton;etcone03/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "lep2_etcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone03 of the 2nd lepton;etcone03/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	name = "lep3_etcone03";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "etcone03 of the 3rd lepton;etcone03/pt;entries", 40, -0.05, 0.2);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	name = "N_jets";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "# of jets;# of jets;Events", 15, 0, 15);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	name = "N_bjets";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "# of bjets;# of bjets;Events", 10, 0, 10);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "meff";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "effective mass;effective mass [GeV];Events / 100 GeV", 10, 0, 1000);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "mt";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "transverse mass (leading lepton);transverse mass (leading lepton) [GeV];Events / 20 GeV", 15, 0, 300);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "met";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "mEt;E_{T}^{miss} [GeV];Events / 5 GeV", 20, 0, 100);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "metL";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "mEt;E_{T}^{miss} [GeV];Events / 25 GeV", 12, 0, 300);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "MZ";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "M(ll);M(ll) [GeV];entries", 40, 0, 200);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "Mee";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "M(ee);M(ee) [GeV];entries", 40, 0, 200);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "Mmumu";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "M(mumu);M(mumu) [GeV];entries", 40, 0, 200);
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

	name = "pt_jet1";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(jet1);First Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "pt_jet2";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(jet2);Second Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "pt_jet3";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(jet3);Third Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();

	//----------------------------------------------------------------------

	name = "pt_jet4";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "pT(jet4);Fourth Jet p_{T}^{} [GeV];Entries / GeV", n_bins_jet_pt, jet_pt_bins);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	name = "el1_origin";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "el_origin of the 1st electron;el_origin;entries", 40, 0, 40);
	h1d->Sumw2();

	name = "el2_origin";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "el_origin of the 2nd electron;el_origin;entries", 40, 0, 40);
	h1d->Sumw2();

	name = "el3_origin";
	sprintf(hname, "%s_%s", name, tag);
	h1d = new TH1D(hname, "el_origin of the 3rd electron;el_origin;entries", 40, 0, 40);
	h1d->Sumw2();

	//----------------------------------------------------------------------
	return;
}

//---------------------------------------------------------------------------
void FillJetHistos(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap, DileptonTriggerTool* _dileptonTriggerTool) {

	FillJetHistos(tag, evt, jet, jet, NULL, lep, NULL, elec_4jetOverlap, SystErr::NONE, NULL, _dileptonTriggerTool);
	return;
}

//---------------------------------------------------------------------------
void FillJetHistos(const char* tag, myevt *evt, calJet *jet, calJet *syst_jet, calJet *jet_D3PD, my_leptons *lep, my_leptons *lep_met, my_leptons *elec_4jetOverlap,
		SystErr::Syste whichsyste, METUtility* _metUtility, DileptonTriggerTool* _dileptonTriggerTool) {

	//Wrapper
	double old_MRF_Px = evt->MET_Egamma10NoTau_RefFinal_etx;
	double old_MRF_Py = evt->MET_Egamma10NoTau_RefFinal_ety;

	//We have to calculate a correction for the mis-Et here.
	if (evt->isMC && jet != syst_jet && syst_jet != NULL && jet_D3PD != NULL && (strstr(tag, "JES") != NULL || strstr(tag, "pJER") != NULL)) {

		TVector2 newMet = getMET(evt, syst_jet, jet_D3PD, lep_met, SystErr::NONE, _metUtility);
		evt->MET_Egamma10NoTau_RefFinal_etx = newMet.X();
		evt->MET_Egamma10NoTau_RefFinal_ety = newMet.Y();
	}

	if (evt->isMC && jet == syst_jet && jet_D3PD != NULL && (strstr(tag, "StSc") != NULL || strstr(tag, "StRs") != NULL)) {

		TVector2 newMet = getMET(evt, jet, jet_D3PD, lep_met, whichsyste, _metUtility);
		evt->MET_Egamma10NoTau_RefFinal_etx = newMet.X();
		evt->MET_Egamma10NoTau_RefFinal_ety = newMet.Y();
	}

	/*
	 double cl_sign = 0;
	 if (evt->isMC) {
	 if (strstr(tag, "pJES") != NULL) {
	 cl_sign = 1;
	 }

	 if (strstr(tag, "mJES") != NULL) {
	 cl_sign = -1;
	 }
	 }

	 for (int i = 0; i < jet->n && evt->isMC && jet != syst_jet; i++)
	 if ((jet->pt[i] > 20000. || cl_sign == 0) && jet->E[i] > 0) {
	 double delta_pt = syst_jet->pt[i] - jet->pt[i]; // in MeV

	 mis_Ex -= delta_pt * cos(jet->phi[i]);
	 mis_Ey -= delta_pt * sin(jet->phi[i]);
	 }
	 */

	//evt->MET_Egamma10NoTau_RefFinal_etx += lep->delta_met_x;
	//evt->MET_Egamma10NoTau_RefFinal_ety += lep->delta_met_y;
	FillJetHistos_Kenematics(tag, evt, syst_jet, lep, elec_4jetOverlap, _dileptonTriggerTool);

	evt->MET_Egamma10NoTau_RefFinal_etx = old_MRF_Px;
	evt->MET_Egamma10NoTau_RefFinal_ety = old_MRF_Py;

	return;
}

//---------------------------------------------------------------------------
void FillJetHistos_Kenematics(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap, DileptonTriggerTool* _dileptonTriggerTool) {

	int n_prim_vtx = 0;
	for (int i = 0; i < evt->vxp_n; i++) {
		if (evt->vxp_vertNtrk[i] >= 5) {
			n_prim_vtx++; //this is a good vertex

		}
	}

	char my_tag[256];
	char hist_name[256];

	if (strlen(tag) > 0)
		sprintf(my_tag, "_%s", tag);
	else
		sprintf(my_tag, "%s", tag);

	//effective mass
	double meff = 0;
	for (int i = 0; i < lep->num_leptons; i++) {
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			meff += lep->pt[i];
		}
	}

	//miss-Et variables
	double my_MET_px = lep->delta_met_x + evt->MET_Egamma10NoTau_RefFinal_etx;
	double my_MET_py = lep->delta_met_y + evt->MET_Egamma10NoTau_RefFinal_ety;
	double my_MET_pT = sqrt(my_MET_px * my_MET_px + my_MET_py * my_MET_py);

	meff += my_MET_pT;

	//Now we can count jets
	int n_jets = 0;

	for (int i = 0; i < jet->n; i++)
		if (jet->pt[i] > 40000. && fabs(jet->eta[i]) < 2.8) {

			bool dR_excl = false;
			double dR;

			//We exclude all electrons from the jet collection
			for (int k = 0; k < elec_4jetOverlap->num_leptons && !dR_excl; k++) {

				if ((evt->el_nSCTHits[elec_4jetOverlap->index[k]] + evt->el_nPixHits[elec_4jetOverlap->index[k]]) < 4) {
					dR = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[k]], evt->el_cl_phi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				} else {
					dR = DeltaR(evt->el_tracketa[elec_4jetOverlap->index[k]], evt->el_trackphi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				}

				dR_excl |= (dR <= 0.2);
			}

			if (!dR_excl) {
				n_jets++;
				meff += jet->pt[i]; //TODO: What should be included in m_eff
			}
		}

	//Now we can count bjets
	int n_bjets = 0;

	for (int i = 0; i < jet->n; i++)
		if (jet->pt[i] > 20000. && fabs(jet->eta[i]) < 2.5 && jet->flavor_weight_MV1[i] > 0.7892) {

			bool dR_excl = false;
			double dR;

			//We exclude all electrons from the jet collection
			for (int k = 0; k < elec_4jetOverlap->num_leptons && !dR_excl; k++) {

				if ((evt->el_nSCTHits[elec_4jetOverlap->index[k]] + evt->el_nPixHits[elec_4jetOverlap->index[k]]) < 4) {
					dR = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[k]], evt->el_cl_phi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				} else {
					dR = DeltaR(evt->el_tracketa[elec_4jetOverlap->index[k]], evt->el_trackphi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				}

				dR_excl |= (dR <= 0.2);
			}

			if (!dR_excl) {
				n_bjets++;
			}
		}

	bool is_full = false;

	if (n_jets >= 5 && n_bjets >= 3) {
		is_full = true;
		if (meff > 350000.) {
			sprintf(hist_name, "full_3b%s", my_tag);
			FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
		}
	} else {
		if (lep->num_20GeV_leptons_noverlap == 2 && fabs(lep->total_charge) > 1. && n_jets >= 3 && n_bjets == 0 && my_MET_pT > 150000. && transverse_mass(lep, evt) > 100000.) {
			is_full = true;
			if (meff > 400000.) {
				sprintf(hist_name, "full_2l0b%s", my_tag);
				FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
			}
		}

		if (lep->num_20GeV_leptons_noverlap == 2 && fabs(lep->total_charge) > 1. && n_jets >= 3 && n_bjets > 0 && my_MET_pT > 150000. && transverse_mass(lep, evt) > 100000.) {
			is_full = true;
			if (meff > 700000.) {
				sprintf(hist_name, "full_2l1b%s", my_tag);
				FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
			}
		}

		if (lep->num_20GeV_leptons_noverlap >= 3 && n_jets >= 4 && my_MET_pT > 50000. && my_MET_pT < 150000. && !lep->has_Z) {
			is_full = true;
			if (meff > 400000.) {
				sprintf(hist_name, "full_3llm%s", my_tag);
				FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
			}
		}

		if (lep->num_20GeV_leptons_noverlap >= 3 && n_jets >= 4 && my_MET_pT > 150000.) {
			is_full = true;
			if (meff > 400000.) {
				sprintf(hist_name, "full_3lhm%s", my_tag);
				FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
			}
		}
	}

	if (!is_full) {

		if (n_jets >= 0 && n_bjets == 0 && my_MET_pT > 25000.) {
			sprintf(hist_name, "zero_0b%s", my_tag);
			FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
		}

		if (n_jets >= 1 && n_bjets == 0 && my_MET_pT > 25000.) {
			sprintf(hist_name, "one_0b%s", my_tag);
			FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
		}

		if (n_jets >= 2 && n_bjets == 0 && my_MET_pT > 25000.) {
			sprintf(hist_name, "two_0b%s", my_tag);
			FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
		}

		if (n_jets >= 3 && n_bjets == 0 && my_MET_pT > 25000.) {
			sprintf(hist_name, "three_0b%s", my_tag);
			FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
		}

		if (n_jets >= 0 && n_bjets > 0 && my_MET_pT > 25000.) {
			sprintf(hist_name, "zero_1b%s", my_tag);
			FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
		}

		if (n_jets >= 1 && n_bjets > 0 && my_MET_pT > 25000.) {
			sprintf(hist_name, "one_1b%s", my_tag);
			FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
		}

		if (n_jets >= 2 && n_bjets > 0 && my_MET_pT > 25000.) {
			sprintf(hist_name, "two_1b%s", my_tag);
			FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
		}

		if (n_jets >= 3 && n_bjets > 0 && my_MET_pT > 25000.) {
			sprintf(hist_name, "three_1b%s", my_tag);
			FillJetHistos_SetOfFinalStates(hist_name, evt, jet, lep, elec_4jetOverlap, _dileptonTriggerTool);
		}
	}

	return;
}

//---------------------------------------------------------------------------
void FillJetHistos_SetOfFinalStates(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap, DileptonTriggerTool* _dileptonTriggerTool) {

	char hist_name[256];

	double triggerWeight_ee;
	if (is_ee(lep, evt) && trigger_ee(lep, evt, _dileptonTriggerTool, triggerWeight_ee)) {
		if (evt->isMC)
			evt->weight *= triggerWeight_ee;
		sprintf(hist_name, "ee_%s", tag);
		FillJetHistos_New(hist_name, evt, jet, lep, elec_4jetOverlap);
		if (evt->isMC)
			evt->weight *= 1. / triggerWeight_ee;
	}

	double triggerWeight_mm;
	if (is_mm(lep, evt) && trigger_mm(lep, evt, _dileptonTriggerTool, triggerWeight_mm)) {
		if (evt->isMC)
			evt->weight *= triggerWeight_mm;
		sprintf(hist_name, "mm_%s", tag);
		FillJetHistos_New(hist_name, evt, jet, lep, elec_4jetOverlap);
		if (evt->isMC)
			evt->weight *= 1. / triggerWeight_mm;
	}

	double triggerWeight_em;
	if (is_em(lep, evt) && trigger_em(lep, evt, _dileptonTriggerTool, triggerWeight_em)) {
		if (evt->isMC)
			evt->weight *= triggerWeight_em;
		sprintf(hist_name, "em_%s", tag);
		FillJetHistos_New(hist_name, evt, jet, lep, elec_4jetOverlap);
		if (evt->isMC)
			evt->weight *= 1. / triggerWeight_em;
	}

	return;
}

//---------------------------------------------------------------------------
void FillJetHistos_New(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap) {

	char hist_name[256];

	int index_fake = -1;
	int index_chmisid = -1;

	int num_lept = 0;
	for (int i = 0; i < lep->num_leptons && num_lept < 3; i++) {
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			num_lept++;
			if (lep->is_fake[i]) {
				index_fake = i;
				break;
			}
		}
	}

	num_lept = 0;
	for (int i = 0; i < lep->num_leptons && num_lept < 3; i++) {
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			num_lept++;
			if (lep->is_chmisid[i]) {
				index_chmisid = i;
				break;
			}
		}
	}

	if (index_fake >= 0) {
		if (lep->is_electron[index_fake]) {
			sprintf(hist_name, "fake_e_%s", tag);
			FillJetHistos_FinalState(hist_name, evt, jet, lep, elec_4jetOverlap);
		}

		else {
			sprintf(hist_name, "fake_m_%s", tag);
			FillJetHistos_FinalState(hist_name, evt, jet, lep, elec_4jetOverlap);
		}
	}

	else {
		if (index_chmisid >= 0) {
			sprintf(hist_name, "chmisid_%s", tag);
			FillJetHistos_FinalState(hist_name, evt, jet, lep, elec_4jetOverlap);
		}

		else {
			sprintf(hist_name, "real_%s", tag);
			FillJetHistos_FinalState(hist_name, evt, jet, lep, elec_4jetOverlap);
		}
	}

	return;
}

//---------------------------------------------------------------------------
void FillJetHistos_FinalState(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap) {

	if (lep->num_20GeV_leptons_noverlap < 2) {
		std::cerr << "ERROR: incorrect usage of cuts!!!!";
		return;
	}

	char hist_name[256];

	//Jet Multiplicities
	int n_jets = 0;
	int jet_ind[MAXJETS];
	srtJt jet_srt[MAXJETS];

	//effective mass
	double meff = 0;
	for (int i = 0; i < lep->num_leptons; i++) {
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			meff += lep->pt[i];
		}
	}

	//deltaR_lep_jet
	double deltaR_lep_jet[3] = { 5., 5., 5. };

	//miss-Et variables
	double my_MET_px = lep->delta_met_x + evt->MET_Egamma10NoTau_RefFinal_etx;
	double my_MET_py = lep->delta_met_y + evt->MET_Egamma10NoTau_RefFinal_ety;
	double my_MET_pT = sqrt(my_MET_px * my_MET_px + my_MET_py * my_MET_py);

	meff += my_MET_pT;

	//Now we can count jets
	for (int i = 0; i < jet->n; i++)
		if (jet->pt[i] / 1000. > 40. && fabs(jet->eta[i]) < 2.8) {

			bool dR_excl = false;
			double dR;

			//We exclude all electrons from the jet collection
			for (int k = 0; k < elec_4jetOverlap->num_leptons; k++) {

				if ((evt->el_nSCTHits[elec_4jetOverlap->index[k]] + evt->el_nPixHits[elec_4jetOverlap->index[k]]) < 4) {
					dR = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[k]], evt->el_cl_phi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				} else {
					dR = DeltaR(evt->el_tracketa[elec_4jetOverlap->index[k]], evt->el_trackphi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				}

				dR_excl |= (dR <= 0.2);
			}

			if (!dR_excl) {
				if (n_jets < MAXJETS) {
					jet_srt[n_jets].ind = i;
					jet_srt[n_jets].pt = jet->pt[i];
				}

				n_jets++;
				meff += jet->pt[i];

				int num_lept = 0;
				dR = 10.;
				for (int j = 0; j < lep->num_leptons && num_lept < 3; j++) {
					if (lep->pt[j] > LeptPt && !lep->lept_overlap[j]) {
						if (lep->is_electron[j]) {

							if ((evt->el_nSCTHits[lep->index[j]] + evt->el_nPixHits[lep->index[j]]) < 4) {
								dR = DeltaR(evt->el_cl_eta[lep->index[j]], evt->el_cl_phi[lep->index[j]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
							} else {
								dR = DeltaR(evt->el_tracketa[lep->index[j]], evt->el_trackphi[lep->index[j]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
							}

						} else
							dR = DeltaR(evt->mu_staco_eta[lep->index[j]], evt->mu_staco_phi[lep->index[j]], jet->eta[i], jet->phi[i]);

						if (dR < deltaR_lep_jet[num_lept])
							deltaR_lep_jet[num_lept] = dR;

						num_lept++;
					}
				}
			}
		}

	//Now we can count bjets
	int n_bjets = 0;

	for (int i = 0; i < jet->n; i++)
		if (jet->pt[i] > 20000. && fabs(jet->eta[i]) < 2.5 && jet->flavor_weight_MV1[i] > 0.7892) {

			bool dR_excl = false;
			double dR;

			//We exclude all electrons from the jet collection
			for (int k = 0; k < elec_4jetOverlap->num_leptons; k++) {

				if ((evt->el_nSCTHits[elec_4jetOverlap->index[k]] + evt->el_nPixHits[elec_4jetOverlap->index[k]]) < 4) {
					dR = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[k]], evt->el_cl_phi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				} else {
					dR = DeltaR(evt->el_tracketa[elec_4jetOverlap->index[k]], evt->el_trackphi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				}

				dR_excl |= (dR <= 0.2);
			}

			if (!dR_excl) {
				n_bjets++;
			}
		}

	//-Here we re-sort jets--------------------------------------------------------------------
	qsort(jet_srt, n_jets, sizeof(srtJt), jet_pt_comparator);

	for (int i = 0; i < n_jets; i++)
		jet_ind[i] = jet_srt[i].ind;

	//-----------------------------------------------------------------------------------------

	int mu_count = 1;
	int el_count = 1;

	int num_lept = 0;
	for (int j = 0; j < lep->num_leptons && num_lept < 3; j++)
		if (lep->pt[j] > LeptPt && !lep->lept_overlap[j]) {
			num_lept++;

			if (!lep->is_electron[j]) {

				if (mu_count < 4) {
					//double d0_corr = evt->mu_staco_trackd0[mu_ind] + evt->vxp_vertx[prim_vtx_ind] * sin(evt->mu_staco_phi[mu_ind])	- evt->vxp_verty[prim_vtx_ind] * cos(evt->mu_staco_phi[mu_ind]);
					double d0_corr = evt->mu_staco_id_d0_exPV[lep->index[j]];
					double d0_sig = d0_corr / sqrt(evt->mu_staco_id_cov_d0_exPV[lep->index[j]]);

					sprintf(hist_name, "mu%d_pt", mu_count);
					fillHist(hist_name, tag, lep->pt[j] / 1000., evt->weight);

					sprintf(hist_name, "mu%d_D0", mu_count);
					fillHist(hist_name, tag, d0_corr, evt->weight);

					sprintf(hist_name, "mu%d_D0sig", mu_count);
					fillHist(hist_name, tag, d0_sig, evt->weight);

					sprintf(hist_name, "mu%d_ptcone02", mu_count);
					fillHist(hist_name, tag, evt->mu_staco_ptcone20[lep->index[j]] / evt->mu_staco_pt[lep->index[j]], evt->weight);

					sprintf(hist_name, "mu%d_ptcone03", mu_count);
					fillHist(hist_name, tag, evt->mu_staco_ptcone30[lep->index[j]] / evt->mu_staco_pt[lep->index[j]], evt->weight);

					sprintf(hist_name, "mu%d_etcone02", mu_count);
					fillHist(hist_name, tag, evt->mu_staco_etcone20[lep->index[j]] / evt->mu_staco_pt[lep->index[j]], evt->weight);

					sprintf(hist_name, "mu%d_etcone03", mu_count);
					fillHist(hist_name, tag, evt->mu_staco_etcone30[lep->index[j]] / evt->mu_staco_pt[lep->index[j]], evt->weight);

					fillHist("mu_eta", tag, evt->mu_staco_eta[lep->index[j]], evt->weight);
					fillHist("mu_phi", tag, evt->mu_staco_phi[lep->index[j]], evt->weight);
				}
				mu_count++;

			} else {

				if (el_count < 4) {

					//double d0_corr = evt->el_trackd0[lep->index[j]] + evt->vxp_vertx[0] * sin(evt->el_trackphi[lep->index[j]]) - evt->vxp_verty[0] * cos(evt->el_trackphi[lep->index[j]]);
					//double d0_sig = d0_corr; // / sqrt(evt->mu_staco_id_cov_d0_exPV[lep->index[j]]);

					sprintf(hist_name, "el%d_pt", el_count);
					fillHist(hist_name, tag, lep->pt[j] / 1000., evt->weight);

					sprintf(hist_name, "el%d_D0", el_count);
					fillHist(hist_name, tag, evt->el_trackIPEstimate_d0_unbiasedpvunbiased[lep->index[j]], evt->weight);

					sprintf(hist_name, "el%d_isTight", el_count);
					fillHist(hist_name, tag, evt->el_tightPP[lep->index[j]], evt->weight);

					double el_pt;
					if ((evt->el_nSCTHits[lep->index[j]] + evt->el_nPixHits[lep->index[j]]) < 4) {
						el_pt = evt->el_cl_E[lep->index[j]] / cosh(evt->el_cl_eta[lep->index[j]]);
					} else {
						el_pt = evt->el_cl_E[lep->index[j]] / cosh(evt->el_tracketa[lep->index[j]]);
					}

					//TODO: Correct isolation for electrons
					sprintf(hist_name, "el%d_ptcone02", el_count);
					fillHist(hist_name, tag, evt->el_ptcone20[lep->index[j]] / el_pt, evt->weight);

					sprintf(hist_name, "el%d_ptcone03", el_count);
					fillHist(hist_name, tag, evt->el_ptcone30[lep->index[j]] / el_pt, evt->weight);

					sprintf(hist_name, "el%d_etcone02", el_count);
					fillHist(hist_name, tag, evt->el_Etcone20[lep->index[j]] / el_pt, evt->weight);

					sprintf(hist_name, "el%d_etcone03", el_count);
					fillHist(hist_name, tag, evt->el_Etcone30[lep->index[j]] / el_pt, evt->weight);

					fillHist("el_eta", tag, evt->el_cl_eta[lep->index[j]], evt->weight);
					fillHist("el_phi", tag, evt->el_cl_phi[lep->index[j]], evt->weight);

					if (evt->isMC) {
						sprintf(hist_name, "el%d_origin", el_count);
						fillHist(hist_name, tag, evt->el_origin[lep->index[j]], evt->weight);
					}

				}
				el_count++;

			}
		}

//-----------------------------------------------------------------------------------------

	int lep_count = 1;

	for (int j = 0; j < lep->num_leptons; j++)
		if (lep->pt[j] > LeptPt && !lep->lept_overlap[j]) {

			if (!lep->is_electron[j]) {

				if (lep_count < 4) {
					sprintf(hist_name, "lep%d_pt", lep_count);
					fillHist(hist_name, tag, lep->pt[j] / 1000., evt->weight);

					sprintf(hist_name, "lep%d_ptcone02", lep_count);
					fillHist(hist_name, tag, evt->mu_staco_ptcone20[lep->index[j]] / evt->mu_staco_pt[lep->index[j]], evt->weight);

					sprintf(hist_name, "lep%d_ptcone03", lep_count);
					fillHist(hist_name, tag, evt->mu_staco_ptcone30[lep->index[j]] / evt->mu_staco_pt[lep->index[j]], evt->weight);

					sprintf(hist_name, "lep%d_etcone02", lep_count);
					fillHist(hist_name, tag, evt->mu_staco_etcone20[lep->index[j]] / evt->mu_staco_pt[lep->index[j]], evt->weight);

					sprintf(hist_name, "lep%d_etcone03", lep_count);
					fillHist(hist_name, tag, evt->mu_staco_etcone30[lep->index[j]] / evt->mu_staco_pt[lep->index[j]], evt->weight);

				}
				lep_count++;

			} else {

				if (lep_count < 4) {

					sprintf(hist_name, "lep%d_pt", lep_count);
					fillHist(hist_name, tag, lep->pt[j] / 1000., evt->weight);

					double el_pt;
					if ((evt->el_nSCTHits[lep->index[j]] + evt->el_nPixHits[lep->index[j]]) < 4) {
						el_pt = evt->el_cl_E[lep->index[j]] / cosh(evt->el_cl_eta[lep->index[j]]);
					} else {
						el_pt = evt->el_cl_E[lep->index[j]] / cosh(evt->el_tracketa[lep->index[j]]);
					}

					//TODO: Correct isolation for electrons
					sprintf(hist_name, "lep%d_ptcone02", lep_count);
					fillHist(hist_name, tag, evt->el_ptcone20[lep->index[j]] / el_pt, evt->weight);

					sprintf(hist_name, "lep%d_ptcone03", lep_count);
					fillHist(hist_name, tag, evt->el_ptcone30[lep->index[j]] / el_pt, evt->weight);

					sprintf(hist_name, "lep%d_etcone02", lep_count);
					fillHist(hist_name, tag, evt->el_Etcone20[lep->index[j]] / el_pt, evt->weight);

					sprintf(hist_name, "lep%d_etcone03", lep_count);
					fillHist(hist_name, tag, evt->el_Etcone30[lep->index[j]] / el_pt, evt->weight);

				}
				lep_count++;

			}
		}

//----------------------------------------------------------------------
	fillHist("meff", tag, meff / 1000., evt->weight);
	fillHist("mt", tag, transverse_mass(lep, evt) / 1000., evt->weight);
	fillHist("met", tag, my_MET_pT / 1000., evt->weight);
	fillHist("metL", tag, my_MET_pT / 1000., evt->weight);
	fillHist("N_jets", tag, n_jets, evt->weight);
	fillHist("N_bjets", tag, n_bjets, evt->weight);
	if (lep->MZ >= 0)
		fillHist("MZ", tag, lep->MZ / 1000., evt->weight);

	if (deltaR_lep_jet[0] < 5.)
		fillHist("deltaR_lep1_jet", tag, deltaR_lep_jet[0], evt->weight);
	if (deltaR_lep_jet[1] < 5.)
		fillHist("deltaR_lep2_jet", tag, deltaR_lep_jet[1], evt->weight);
	if (deltaR_lep_jet[2] < 5.)
		fillHist("deltaR_lep3_jet", tag, deltaR_lep_jet[2], evt->weight);

	for (int j = 0; j < lep->num_leptons; j++)
		if (lep->pt[j] > LeptPt && !lep->lept_overlap[j]) {
			fillHist("lep_pt", tag, lep->pt[j] / 1000., evt->weight);
		}

	int softest_index = -1;
	num_lept = 0;
	for (int j = 0; j < lep->num_leptons && num_lept < 3; j++)
		if (lep->pt[j] > LeptPt && !lep->lept_overlap[j]) {
			softest_index = j;
			num_lept++;
		}
	fillHist("lep_softest_pt", tag, lep->pt[softest_index] / 1000., evt->weight);

	//----------------------------------------------------------------------
	if (n_jets >= 1) {
		fillHistDiff("pt_jet1", tag, jet->pt[jet_ind[0]] / 1000., evt->weight);
		//fillHist("mu_eta_jet1", tag, rapidity(jet->E[jet_ind[0]], jet->pz[jet_ind[0]]), evt->weight);
	}

	//----------------------------------------------------------------------
	if (n_jets >= 2) {
		fillHistDiff("pt_jet2", tag, jet->pt[jet_ind[1]] / 1000., evt->weight);
		//fillHistDiff("mu_eta_jet2", tag, rapidity(jet->E[jet_ind[1]], jet->pz[jet_ind[1]]), evt->weight);
	}

	//----------------------------------------------------------------------
	if (n_jets >= 3) {
		fillHistDiff("pt_jet3", tag, jet->pt[jet_ind[2]] / 1000., evt->weight);
		//fillHistDiff("mu_eta_jet3", tag, rapidity(jet->E[jet_ind[2]], jet->pz[jet_ind[2]]), evt->weight);
	}

	//----------------------------------------------------------------------
	if (n_jets >= 4) {
		fillHistDiff("pt_jet4", tag, jet->pt[jet_ind[3]] / 1000., evt->weight);
		//fillHistDiff("mu_eta_jet4", tag, rapidity(jet->E[jet_ind[3]], jet->pz[jet_ind[3]]), evt->weight);
	}

	//----------------------------------------------------------------------
	num_lept = 0;
	int max_lept_ind = 0;
	for (int j = 0; j < lep->num_leptons && num_lept < 3; j++)
		if (lep->pt[j] > LeptPt && !lep->lept_overlap[j]) {
			num_lept++;
			max_lept_ind = j;
		}

	for (int i = 0; i <= max_lept_ind; i++)
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i])
			for (int j = i + 1; j <= max_lept_ind; j++)
				if (lep->pt[j] > LeptPt && !lep->lept_overlap[j])
					if (lep->is_electron[i] == lep->is_electron[j]) {

						if (!lep->is_electron[i]) { //muons -----------------------------------------------------------

							double sf1 = lep->pt[i] / evt->mu_staco_pt[lep->index[i]];
							double sf2 = lep->pt[j] / evt->mu_staco_pt[lep->index[j]];

							double M;

							M = pow(sf1 * evt->mu_staco_E[lep->index[i]] + sf2 * evt->mu_staco_E[lep->index[j]], 2);
							M += -pow(sf1 * evt->mu_staco_px[lep->index[i]] + sf2 * evt->mu_staco_px[lep->index[j]], 2);
							M += -pow(sf1 * evt->mu_staco_py[lep->index[i]] + sf2 * evt->mu_staco_py[lep->index[j]], 2);
							M += -pow(sf1 * evt->mu_staco_pz[lep->index[i]] + sf2 * evt->mu_staco_pz[lep->index[j]], 2);

							M = sqrt(M);

							fillHist("Mmumu", tag, M / 1000., evt->weight);

						} else { //electrons -------------------------------------------------------------------------

							double pt1, px1, py1, pz1, E1;
							int ind1 = lep->index[i];
							E1 = evt->el_cl_E[ind1];

							if ((evt->el_nSCTHits[ind1] + evt->el_nPixHits[ind1]) < 4) {
								pt1 = E1 / cosh(evt->el_cl_eta[ind1]);
								px1 = pt1 * cos(evt->el_cl_phi[ind1]);
								py1 = pt1 * sin(evt->el_cl_phi[ind1]);
								pz1 = pt1 * sinh(evt->el_cl_eta[ind1]);
							} else {
								pt1 = E1 / cosh(evt->el_tracketa[ind1]);
								px1 = pt1 * cos(evt->el_trackphi[ind1]);
								py1 = pt1 * sin(evt->el_trackphi[ind1]);
								pz1 = pt1 * sinh(evt->el_tracketa[ind1]);
							}

							double pt2, px2, py2, pz2, E2;
							int ind2 = lep->index[j];
							E2 = evt->el_cl_E[ind2];

							if ((evt->el_nSCTHits[ind2] + evt->el_nPixHits[ind2]) < 4) {
								pt2 = E2 / cosh(evt->el_cl_eta[ind2]);
								px2 = pt2 * cos(evt->el_cl_phi[ind2]);
								py2 = pt2 * sin(evt->el_cl_phi[ind2]);
								pz2 = pt2 * sinh(evt->el_cl_eta[ind2]);
							} else {
								pt2 = E2 / cosh(evt->el_tracketa[ind2]);
								px2 = pt2 * cos(evt->el_trackphi[ind2]);
								py2 = pt2 * sin(evt->el_trackphi[ind2]);
								pz2 = pt2 * sinh(evt->el_tracketa[ind2]);
							}

							double sf1 = lep->pt[i] / pt1;
							double sf2 = lep->pt[j] / pt2;

							double M;

							M = pow(E1 * sf1 + E2 * sf2, 2) - pow(px1 * sf1 + px2 * sf2, 2) - pow(py1 * sf1 + py2 * sf2, 2) - pow(pz1 * sf1 + pz2 * sf2, 2);
							M = sqrt(M);

							fillHist("Mee", tag, M / 1000., evt->weight);

						}

					}

	return;
}

//---------------------------------------------------------------------------
void fillHist(const char* hname, const char* tag, float val, double weight) {

	TH1F* hist;
	char my_hname[256];

	sprintf(my_hname, "%s_%s", hname, tag);
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
void fillHist(const char* hname, float val, double weight) {

	TH1F* hist;
	hist = (TH1F*) gDirectory->Get(hname);
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
	} else
		std::cerr << "Warning: incorrect histogram name: " << hname << "\n";

	return;
}

//---------------------------------------------------------------------------
void fillHistDiff(const char* hname, const char* tag, float val, double weight) {

	TH1F* hist;
	char my_hname[256];
	sprintf(my_hname, "%s_%s", hname, tag);
	hist = (TH1F*) gDirectory->Get(my_hname);

	if (hist) {
		TAxis *a = hist->GetXaxis();
		if ((val >= a->GetXmin()) && (val < a->GetXmax())) {
			hist->Fill(val, weight / (a->GetBinWidth(a->FindBin(val))));
		} else {
			hist->Fill(val, weight);
		}
	} else
		std::cout << "Warning: bad histogram name: " << my_hname << "\n";

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
//hname = Form("%s_%s", hname, tag);
	char my_hname[256];
	sprintf(my_hname, "%s_%s", hname, tag);

	hist = (TProfile*) gDirectory->Get(my_hname);
	if (hist)
		hist->Fill(x, y, weight);
	else
		std::cerr << "Warning: incorrect histogram name: " << hname << "\n";

	return;
}

//_____________________________________________________________________________
double DeltaR(float eta1, float phi1, float eta2, float phi2) {

	const double PI = TMath::Pi();
	double deltaR12 = fabs((double) phi1 - (double) phi2);
	if (deltaR12 > PI)
		deltaR12 = 2.0 * PI - deltaR12;
//if (deltaR12 <= -TMath::Pi())
//	deltaR12 += 2. * TMath::Pi();

	deltaR12 = sqrt(deltaR12 * deltaR12 + ((double) eta1 - (double) eta2) * ((double) eta1 - (double) eta2));

	return deltaR12;
}

//_____________________________________________________________________________
double DeltaPhi(float phi1, float phi2) {

	double deltaR12 = (double) phi1 - (double) phi2;
	if (deltaR12 >= TMath::Pi())
		deltaR12 -= 2. * TMath::Pi();
	if (deltaR12 <= -TMath::Pi())
		deltaR12 += 2. * TMath::Pi();

	return deltaR12;
}

//----------------------------------------------------------------------------
// MET cleaning cuts
// We remove loose "bad" and "ugly" jets
// https://twiki.cern.ch/twiki/bin/view/AtlasProtected/HowToCleanJets
// + Veto events with significant energy losses on the LAr hole
//----------------------------------------------------------------------------
bool isCleanMet(calJet *jet, myevt *evt, my_leptons *elec_4jetOverlap) {

	bool is_jet_bad = false;

	is_jet_bad |= evt->larError == 2;
	is_jet_bad |= evt->tileError == 2;
	is_jet_bad |= (evt->coreFlags & 0x40000) != 0;

	//Hot tile calorimeter in B1 and B2 2012
	//https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/HowToCleanJets2012
	//First check if run is affected

	bool isbadTileRun = false;
	if (!evt->isMC) { //only check if data
		const int NbadTileRuns = 9;
		const int badTileRuns[NbadTileRuns] = { 202660, 202668, 202712, 202740, 202965, 202987, 202991, 203027, 203169 };

		for (int TileRunIndex = 0; TileRunIndex < NbadTileRuns; TileRunIndex++) {
			isbadTileRun |= (evt->runNumber == badTileRuns[TileRunIndex]);
		}
	}

	// Cleaning Should be applied  to Data and MC
	// "Looser" definition
	bool dR_excl_for_jet;
	float dR_for_jet;
	double Chf;
	for (int i = 0; i < jet->n && !is_jet_bad; i++) {
		/*
		 if (evt->eventNumber == 302520) {
		 std::cout << "\nIndex " << i;
		 std::cout << "\npT " << jet->pt[i];
		 std::cout << "\njet_AntiKt4LCTopo_constscale_eta " << jet->constscale_eta[i];
		 std::cout << "\njet_AntiKt4LCTopo_emfrac " << jet->emfrac[i];
		 std::cout << "\njet_AntiKt4LCTopo_hecf " << jet->hecf[i];
		 std::cout << "\njet_AntiKt4LCTopo_LArQuality " << jet->LArQuality[i];
		 std::cout << "\njet_AntiKt4LCTopo_AverageLArQF " << jet->AverageLArQF[i];
		 std::cout << "\njet_AntiKt4LCTopo_Timing " << jet->timing[i];
		 std::cout << "\njet_AntiKt4LCTopo_sumPtTrk " << jet->sumPtTrk[i];
		 std::cout << "\njet_AntiKt4LCTopo_fracSamplingMax " << jet->fracSamplingMax[i];
		 std::cout << "\njet_AntiKt4LCTopo_SamplingMax " << jet->SamplingMax[i];
		 std::cout << "\njet_AntiKt4LCTopo_NegativeE " << jet->NegativeE[i];

		 }
		 */
		if (jet->pt[i] > 20000.) { // && fabs(jet->constscale_eta[i]) < 10.

			//Exclude the overlap with leptons
			dR_excl_for_jet = false;

			for (int l = 0; l < elec_4jetOverlap->num_leptons && !dR_excl_for_jet; l++) {

				if ((evt->el_nSCTHits[elec_4jetOverlap->index[l]] + evt->el_nPixHits[elec_4jetOverlap->index[l]]) < 4) {
					dR_for_jet = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[l]], evt->el_cl_phi[elec_4jetOverlap->index[l]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				} else {
					dR_for_jet = DeltaR(evt->el_tracketa[elec_4jetOverlap->index[l]], evt->el_trackphi[elec_4jetOverlap->index[l]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
				}

				//dR_for_jet = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[l]], evt->el_cl_phi[elec_4jetOverlap->index[l]], jet->eta[i], jet->phi[i]);
				dR_excl_for_jet |= (dR_for_jet <= 0.2);
			}

			if (dR_excl_for_jet)
				continue;

			//EM Coherent Noise
			is_jet_bad |= fabs(jet->LArQuality[i]) > 0.8 && jet->emfrac[i] > 0.95 && fabs(jet->constscale_eta[i]) < 2.8 && ((double) jet->AverageLArQF[i] / 65535.) >= 0.8;

			//HEC Spike
			is_jet_bad |= fabs(jet->NegativeE[i]) > 60000.; // > 60 GeV
			is_jet_bad |= (fabs(jet->HECQuality[i]) > 0.5 && jet->hecf[i] > 0.5 && ((double) jet->AverageLArQF[i] / 65535.) >= 0.8);

			//Cosmics - Beam Backgrounds
			Chf = (double) jet->sumPtTrk[i] / (double) jet->pt[i];

			//is_jet_bad |= fabs(jet->timing[i]) > 25.;
			is_jet_bad |= jet->emfrac[i] < 0.05 && fabs(jet->constscale_eta[i]) < 2.0 && Chf < 0.05;
			is_jet_bad |= jet->emfrac[i] < 0.05 && fabs(jet->constscale_eta[i]) >= 2.0;
			is_jet_bad |= fabs(jet->constscale_eta[i]) < 2. && jet->fracSamplingMax[i] > 0.99;

			//Hot tile calorimeter in B1 and B2 2012
			//https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/HowToCleanJets2012
			if (isbadTileRun)
				is_jet_bad |= (jet->eta[i] > -0.2 && jet->eta[i] < -0.1 && jet->phi[i] > 2.65 && jet->phi[i] < 2.75 && jet->fracSamplingMax[i] > 0.6 && jet->SamplingMax[i] == 13);

		}
	}

	/* LAr hole veto No longer needed
	 //Now we can veto events with significant looses in the LAr hole
	 //if ((evt->isMC && evt->runNumber == 183003) || (!evt->isMC && evt->runNumber >= 180614 && evt->runNumber < 185352))
	 //TMP
	 {
	 double Ep = 0;

	 for (int i = 0; i < jet->n && !is_jet_bad; i++) {
	 if (jet->pt[i] > 20000. && jet->E[i] > 0
	 && IsLArHole(jet->eta[i], jet->phi[i])) {

	 Ep = jet->pt[i]
	 * (1. - (jet->BCH_CORR_CELL[i] + jet->BCH_CORR_DOTX[i]))
	 * jet->BCH_CORR_JET[i]
	 * cos(DeltaPhi(evt->MRF_Phi, jet->phi[i]))
	 / (1. - jet->BCH_CORR_JET[i]);

	 //10 GeV threshold
	 is_jet_bad |= (Ep > 10000. || Ep > 0.1 * evt->MRF_Pt);

	 }
	 }

	 }
	 */

	//Bad FCAL response in C1-C8 periods
	//https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/HowToCleanJets2012
	/*
	 bool applyVeto = false;

	 double intLuminosity = 20.7;

	 if (!evt->isMC){
	 // Data, apply veto only for runs in the interval below

	 if (evt->runNumber >= 206248 && evt->runNumber <=207332){
	 applyVeto = true;
	 }
	 }
	 else {
	 // MC, apply veto randomly to a fraction lumi_frac of the events

	 if (jet->n > 0){
	 int seed = int(fabs(jet->phi[0]*1.e+5));
	 if(!seed) ++seed;
	 TRandom2* m_random = new TRandom2();
	 m_random->SetSeed(seed);

	 if (m_random->Rndm() < (1.18034/intLuminosity)){
	 applyVeto = true;
	 }

	 delete m_random;
	 }
	 }

	 if (applyVeto){
	 for (int i = 0; i < jet->n; ++i){
	 is_jet_bad |= (fabs(jet->eta[i]) > 3.2 && jet->pt[i] > 20000 && jet->phi[i] > 1.6 && jet->phi[i] < 3.1);
	 }
	 }
	 */

	//HEC Veto
	is_jet_bad |= !HEC_Veto(jet, evt);

	return !is_jet_bad;
}

// -----------------------------------------------------------------------------------
bool HEC_Veto(calJet *jet, myevt *evt) {

	bool is_jet_bad = false;
	double DeltaPhi_jet_M;
	TVector2 P_jet;
	TVector2 P_M(evt->MET_Egamma10NoTau_RefFinal_etx, evt->MET_Egamma10NoTau_RefFinal_ety);

	for (int i = 0; i < jet->n && !is_jet_bad; i++) {
		if (jet->pt[i] > 40000. && jet->BCH_CORR_JET[i] > 0.05) {

			P_jet.SetMagPhi(jet->pt[i], jet->phi[i]);
			DeltaPhi_jet_M = (P_jet).DeltaPhi(P_M);
			is_jet_bad |= fabs(DeltaPhi_jet_M) < 0.3;

		}
	}

	return !is_jet_bad;
}

/* LAr hole veto No longer needed
 bool IsLArHole(float eta, float phi) {
 if (eta < -0.1 || eta > 1.5)
 return false;
 if (phi < -0.9 || phi > -0.5)
 return false;
 return true;
 }
 */

//----------------------------------------------------------------------------
// The function returns 1 for data or lumi-weighted trigger period
// OLD 2011 period dependent triggers
//----------------------------------------------------------------------------
/*
 int muonTrigger(myevt *evt, double rndm) {

 int prd = 0;

 if (!evt->isMC) { //DATA
 //---------------------------------------------------------------------------------------------------
 if ((evt->runNumber <= 186493 && evt->runNumber >= 178044))
 prd = 1; // B-I
 if ((evt->runNumber >= 186516 && evt->runNumber <= 186755))
 prd = 2; // J
 if ((evt->runNumber >= 186873 && evt->runNumber <= 187815))
 prd = 3; // K
 if ((evt->runNumber >= 188902))
 prd = 4; // L,M

 if (prd == 0)
 std::cout << "\nWarning: the data is not associated with any data-taking period! " << evt->runNumber
 << ".\n";

 if (prd == 1) {
 if (evt->EF_mu18 || evt->EF_mu18_MG || evt->EF_e20_medium)
 ; // B-I
 else
 prd = 0;
 }

 if (prd == 2) {
 if (evt->EF_mu18_medium || evt->EF_mu18_MG_medium || evt->EF_e20_medium)
 ; // J
 else
 prd = 0;
 }

 if (prd == 3) {
 if (evt->EF_mu18_medium || evt->EF_mu18_MG_medium || evt->EF_e22_medium)
 ; // K
 else
 prd = 0;
 }

 if (prd == 4) {
 if (evt->EF_mu18_medium || evt->EF_mu18_MG_medium || evt->EF_e22vh_medium1 || evt->EF_e45_medium1)
 ; // L,M
 else
 prd = 0;
 }

 } else { //MC

 //---------------------------------------------------------------------------------------------------
 //MC11b menu
 if (evt->runNumber == 180164 || evt->runNumber == 183003)
 prd = 1; // B-D || E-H

 if (evt->runNumber == 186169 || evt->runNumber == 189751)
 prd = 2; // I,J,K || L,M;

 //---------------------------------------------------------------------------------------------------
 //MC10b menu
 if (prd == 0) {
 prd = 1; //mc10b simulations
 std::cout << "\nWARNING: This is MC10b or triggers are applied incorrectly\n";
 }

 if (prd > 0) {
 if (evt->EF_mu18 || evt->EF_mu18_MG || evt->EF_mu18_medium || evt->EF_mu18_MG_medium || evt->EF_e20_medium
 || evt->EF_e22_medium || evt->EF_e22vh_medium1 || evt->EF_e45_medium1) {
 prd = 1; // B-D || E-H
 } else
 prd = 0;
 }

 *//*
 const double lumi[4] = { 0, 3.10118, 15.819, 17.9683 }; // should correspond to the luminosity in each period
 const double tot_lumi = lumi[0] + lumi[1] + lumi[2] + lumi[3];
 double sum = 0;

 for (int i = 0; i < 4; i++) {
 sum += lumi[i];
 if (sum > tot_lumi * rndm) {
 prd = i + 1;
 break;
 }
 }
 //MC trigger is done separately
 *//*

 }

 return prd;
 }
 */

//----------------------------------------------------------------------------
// Here we calculate rapidity for jets
//----------------------------------------------------------------------------
double rapidity(double E, double pz) {

	double y = 0.5 * log((E + pz) / (E - pz));

	return y;
}

//----------------------------------------------------------------------------
// Muon hit requirement
// "i" stands for muon index
// 2012 update: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/WZElectroweakCommonTopics2012#Muon_Selection
//----------------------------------------------------------------------------
bool Muon_IdHitReq(myevt *evt, int i) {

	bool hit_req = evt->mu_staco_nBLHits[i] > 0 || evt->mu_staco_expectBLayerHit[i] == 0;
	hit_req &= (evt->mu_staco_nPixHits[i] + evt->mu_staco_nPixelDeadSensors[i]) > 0;
	hit_req &= (evt->mu_staco_nSctHits[i] + evt->mu_staco_nSCTDeadSensors[i]) > 4;
	hit_req &= (evt->mu_staco_nSCTHoles[i] + evt->mu_staco_nPixHoles[i]) < 3;

	float trackEta = -log(tan(evt->mu_staco_id_theta[i] / 2.));
	if (fabs(trackEta) < 1.9 && fabs(trackEta) > 0.1) {
		hit_req &= (evt->mu_staco_nTrtHits[i] + evt->mu_staco_nTRTOutliers[i]) >= 6;
		hit_req &= (float) evt->mu_staco_nTRTOutliers[i] / (float) (evt->mu_staco_nTrtHits[i] + evt->mu_staco_nTRTOutliers[i]) < 0.9;
	} else {
		if ((evt->mu_staco_nTrtHits[i] + evt->mu_staco_nTRTOutliers[i]) >= 6)
			hit_req &= (float) evt->mu_staco_nTRTOutliers[i] / (float) (evt->mu_staco_nTrtHits[i] + evt->mu_staco_nTRTOutliers[i]) < 0.9;
	}

	return hit_req;
}

//----------------------------------------------------------------------------
// Transverse impact parameter, d0
// "i" stands for muon index
//----------------------------------------------------------------------------
double calc_d0(myevt *evt, int i) {

	double d0_corr = 10.;
	if (evt->mu_staco_hastrack[i]) {
		//d0_corr = evt->mu_staco_trackd0[i] + evt->vxp_vertx[prim_vtx_ind] * sin(evt->mu_staco_phi[i])	- evt->vxp_verty[prim_vtx_ind] * cos(evt->mu_staco_phi[i]);

		d0_corr = evt->mu_staco_id_d0_exPV[i] / sqrt(evt->mu_staco_id_cov_d0_exPV[i]);
	}
//d0_corr = evt->mu_staco_id_d0_exPV[i];

	return d0_corr;
}

//_____________________________________________________________________________
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

//----------------------------------------------------------------------------
// Select a good muon
//----------------------------------------------------------------------------
bool is_preselection_muon_noIso(myevt *evt, int i, float pt) {

	bool good_muon = ((evt->mu_staco_isCombinedMuon[i] == 1 || evt->mu_staco_isSegmentTaggedMuon[i] == 1) && pt > 10000.);
	good_muon &= evt->mu_staco_loose[i] == 1;
	good_muon &= (fabs(evt->mu_staco_eta[i]) < 2.5);
//good_muon &= (evt->mu_staco_author[i] == 6);
	good_muon &= Muon_IdHitReq(evt, i);

	return good_muon;
}

//------------------------------------------------------------------------
bool is_preselection_muon(myevt *evt, int i, float pt, my_leptons *elec_4jetOverlap) {

	bool good_muon = is_preselection_muon_noIso(evt, i, pt);

	bool dR_excl_for_jet;
	double dR;

	for (int k = 0; k < evt->AntiKt4LCTopo.n && good_muon; k++)
		if (evt->AntiKt4LCTopo.pt[k] > 20000. && fabs(evt->AntiKt4LCTopo.eta[k]) < 2.8) {
		  
			// Here we check if a jet overlap with an electron
			dR_excl_for_jet = false;
			for (int l = 0; l < elec_4jetOverlap->num_leptons && !dR_excl_for_jet; l++) {

			  if ((evt->el_nSCTHits[elec_4jetOverlap->index[l]] + evt->el_nPixHits[elec_4jetOverlap->index[l]]) < 4) {
					dR = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[l]], evt->el_cl_phi[elec_4jetOverlap->index[l]], evt->AntiKt4LCTopo.eta[k], evt->AntiKt4LCTopo.phi[k]);
				} else {
					dR = DeltaR(evt->el_tracketa[elec_4jetOverlap->index[l]], evt->el_trackphi[elec_4jetOverlap->index[l]], evt->AntiKt4LCTopo.eta[k], evt->AntiKt4LCTopo.phi[k]);
				}

				//dR = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[l]], evt->el_cl_phi[elec_4jetOverlap->index[l]], evt->AntiKt4LCTopo.eta[k], evt->AntiKt4LCTopo.phi[k]);
				dR_excl_for_jet |= (dR <= 0.2);
			}

			//We check if a muon is isolated from the jet if the jet does not overlap with an electron
			if (!dR_excl_for_jet) {
				dR = DeltaR(evt->mu_staco_eta[i], evt->mu_staco_phi[i], evt->AntiKt4LCTopo.eta[k], evt->AntiKt4LCTopo.phi[k]);
				good_muon &= (dR > 0.4);
			}

		}

	return good_muon;
}

//------------------------------------------------------------------------
bool is_tight_muon(myevt *evt, int i, float pt, my_leptons *elec_4jetOverlap, int Nvtx5Trk) {

	bool good_muon = is_preselection_muon(evt, i, pt, elec_4jetOverlap);

	//good_muon &= (evt->mu_staco_ptcone30_trkelstyle[i] / min((double) pt, 60000.)) < 0.12;
	good_muon &= (evt->mu_staco_ptcone30_trkelstyle[i] / pt) < 0.12;

	/// Compute pileup corrected etcone
	float calo_iso_corr;
	if (!evt->isMC)
		//calo_iso_corr = -64.8 * (float) Nvtx5Trk - 0.98 * (float) (Nvtx5Trk * Nvtx5Trk);
		calo_iso_corr = -10.98 * (float) Nvtx5Trk;
	else
		//calo_iso_corr = -69.2 * (float) Nvtx5Trk - 0.76 * (float) (Nvtx5Trk * Nvtx5Trk);
		calo_iso_corr = -6.27 * (float) Nvtx5Trk;

	//good_muon &= ((evt->mu_staco_etcone30[i] + calo_iso_corr) / pt) < 0.12; //((evt->mu_staco_etcone30[i] + calo_iso_corr) / min((double) pt, 60000.)) < 0.12;

	float mu_staco_theta = 2. * atan(exp(-evt->mu_staco_eta[i]));
	good_muon &= fabs(evt->mu_staco_trackIPEstimate_z0_unbiasedpvunbiased[i] * sin(mu_staco_theta)) <= 1.0; //0.4;

	if (evt->mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased[i] != 0)
		good_muon &= fabs(evt->mu_staco_trackIPEstimate_d0_unbiasedpvunbiased[i] / evt->mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased[i]) <= 3.0;

	return good_muon;
}

//----------------------------------------------------------------------------
// Select a good electron
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
bool is_good_electron(myevt *evt, int i, double pt_cut) {

	bool good_ele = true;

//kinematic cuts
	if ((evt->el_nSCTHits[i] + evt->el_nPixHits[i]) < 4) {
		good_ele &= (evt->el_cl_E[i] / cosh(evt->el_cl_eta[i])) > pt_cut;
	} else {
		good_ele &= (evt->el_cl_E[i] / cosh(evt->el_tracketa[i])) > pt_cut;
	}

	good_ele &= fabs(evt->el_cl_eta[i]) < 2.47;
	good_ele &= (evt->el_author[i] == 1 || evt->el_author[i] == 3);
	good_ele &= (evt->el_mediumPP[i] == 1);
	good_ele &= ((evt->el_OQ[i] & 1446) == 0);

//double d0_corr = evt->el_trackd0[i] + evt->vxp_vertx[prim_vtx_ind] * sin(evt->el_trackphi[i]) - evt->vxp_verty[prim_vtx_ind] * cos(evt->el_trackphi[i]);

//double z0_corr = 1. / tan(evt->el_tracktheta[i]);
//z0_corr *= (evt->vxp_vertx[prim_vtx_ind] * cos(evt->el_trackphi[i]) + evt->vxp_verty[prim_vtx_ind] * sin(evt->el_trackphi[i]));
//double delta_z = evt->el_trackz0[i] - evt->vxp_vertz[prim_vtx_ind] + z0_corr;

	good_ele &= fabs(evt->el_trackz0pv[i]) < 1.; // in mm //Electron longitudinal impact parameter

	good_ele &= fabs(evt->el_trackd0pv[i] / evt->el_tracksigd0pv[i]) < 5.; //"el_trackd0_sig5" Electron track sigma

	/*
	 if (good_ele && evt->el_ptcone20[i] / evt->el_pt[i] < 0.1)
	 std::cout << "\nNum pixel hits: " << evt->el_nPixHits[i] << " \tSCT: " << evt->el_nSCTHits[i] << " \td0: "
	 << d0_corr << " \tdeltaZ: " << delta_z;
	 */

	return good_ele;
}

//----------------------------------------------------------------------------
bool is_preselection_electron_4met(myevt *evt, int i, float el_pt) {

  return (el_pt > 10000. && evt->el_MET_Egamma10NoTau_wet != 0); // ?

}

//----------------------------------------------------------------------------
bool is_preselection_electron_nonIso(myevt *evt, int i, float el_pt) {

	bool good_ele = el_pt > 10000.;
	good_ele &= fabs(evt->el_cl_eta[i]) < 2.47;
	good_ele &= (evt->el_author[i] == 1 || evt->el_author[i] == 3); // ?
	good_ele &= (evt->el_mediumPP[i] == 1);
	good_ele &= ((evt->el_OQ[i] & 1446) == 0); // ?

	if (evt->el_trackIPEstimate_sigd0_unbiasedpvunbiased[i] != 0)
	  good_ele &= fabs(evt->el_trackIPEstimate_d0_unbiasedpvunbiased[i] / evt->el_trackIPEstimate_sigd0_unbiasedpvunbiased[i]) < 5.0; // ?

	return good_ele;
}

//----------------------------------------------------------------------------
bool is_preselection_electron(myevt *evt, int i, float el_pt, my_leptons *elec_4jetOverlap) {

	bool good_ele = is_preselection_electron_nonIso(evt, i, el_pt);

	double dR;
	bool dR_excl_for_jet;
	for (int k = 0; k < evt->AntiKt4LCTopo.n && good_ele; k++) //loop over jet?
	  if (evt->AntiKt4LCTopo.pt[k] > 20000. && fabs(evt->AntiKt4LCTopo.eta[k]) < 2.8) {// jet cut?

			dR_excl_for_jet = false;
			for (int l = 0; l < elec_4jetOverlap->num_leptons && !dR_excl_for_jet; l++) { // loop over ele

				if ((evt->el_nSCTHits[elec_4jetOverlap->index[l]] + evt->el_nPixHits[elec_4jetOverlap->index[l]]) < 4) {
					dR = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[l]], evt->el_cl_phi[elec_4jetOverlap->index[l]], evt->AntiKt4LCTopo.eta[k], evt->AntiKt4LCTopo.phi[k]);
					// dR between el and jet
				} else {
					dR = DeltaR(evt->el_tracketa[elec_4jetOverlap->index[l]], evt->el_trackphi[elec_4jetOverlap->index[l]], evt->AntiKt4LCTopo.eta[k], evt->AntiKt4LCTopo.phi[k]);
				}

				dR_excl_for_jet |= (dR <= 0.2);
			}

			if (!dR_excl_for_jet) { //The jet is not another electron

				if ((evt->el_nSCTHits[i] + evt->el_nPixHits[i]) < 4) {
					dR = DeltaR(evt->el_cl_eta[i], evt->el_cl_phi[i], evt->AntiKt4LCTopo.eta[k], evt->AntiKt4LCTopo.phi[k]);
				} else {
					dR = DeltaR(evt->el_tracketa[i], evt->el_trackphi[i], evt->AntiKt4LCTopo.eta[k], evt->AntiKt4LCTopo.phi[k]);
				}

				good_ele &= (dR > 0.4);
			}

	  }

	return good_ele;
}

//----------------------------------------------------------------------------
bool is_tight_electron(myevt *evt, int i, float el_pt, my_leptons *elec_4jetOverlap, int Nvtx5Trk) {

	bool good_ele = is_preselection_electron(evt, i, el_pt, elec_4jetOverlap);

	good_ele &= (evt->el_tightPP[i] == 1);

	good_ele &= (evt->el_ptcone30[i] / el_pt) < 0.16; //(evt->el_ptcone20[i] / min((double) el_pt, 60000.)) < 0.06;

	float calo_iso_corr;
	if (!evt->isMC) //Data
		//calo_iso_corr = -20.15 * (4. / 9.) * (float) Nvtx5Trk;
	  calo_iso_corr = -20.15 * (float) Nvtx5Trk;  //?
	else
		//calo_iso_corr = -17.94 * (4. / 9.) * (float) Nvtx5Trk;
		calo_iso_corr = -17.94 * (float) Nvtx5Trk;

	//good_ele &= ((evt->el_topoEtcone20_corrected[i] + calo_iso_corr) / min((double) el_pt, 60000.)) < 0.06;
	good_ele &= ((evt->el_topoEtcone30_corrected[i] + calo_iso_corr) / el_pt) < 0.18;

	if ((evt->el_nSCTHits[i] + evt->el_nPixHits[i]) < 4) {
		double el_cl_theta = 2. * atan(exp(-evt->el_cl_eta[i]));
		good_ele &= fabs(evt->el_trackIPEstimate_z0_unbiasedpvunbiased[i] * sin(el_cl_theta)) <= 0.4;
	} else {
		good_ele &= fabs(evt->el_trackIPEstimate_z0_unbiasedpvunbiased[i] * sin(evt->el_tracktheta[i])) <= 0.4;
	}

	if (evt->el_trackIPEstimate_sigd0_unbiasedpvunbiased[i] != 0)
		//good_ele &= fabs(evt->el_trackIPEstimate_d0_unbiasedpvunbiased[i] / evt->el_trackIPEstimate_sigd0_unbiasedpvunbiased[i]) <= 3.0;
		good_ele &= fabs(evt->el_trackIPEstimate_d0_unbiasedpvunbiased[i] / evt->el_trackIPEstimate_sigd0_unbiasedpvunbiased[i]) <= 5.0;

	return good_ele;
}

//----------------------------------------------------------------------------
// Here we calculate the number of 20 GeV leptons
//----------------------------------------------------------------------------
void calcNum20GeVleptons(my_leptons *lep, myevt *evt, my_leptons *lep_baseline, my_leptons * elec_4jetOverlap) {

	lep->num_20GeV_leptons_noverlap = 0;
	lep->num_10GeV_leptons_noverlap = 0;
	bool overlapping_lept;

	for (int i = 0; i < lep->num_leptons; i++) { // loop over tight ele

		if (evt->isMC) {
			//lep->is_fake[i] = Is_Fake(lep, i, evt);
			//lep->is_chmisid[i] = Is_ChMisID(lep, i, evt);

			if (!lep->is_electron[i]) { //muons -----------------------------------------------------------
				lep->is_fake[i] = evt->mu_staco_isfake[lep->index[i]];
				lep->is_chmisid[i] = evt->mu_staco_ischmisid[lep->index[i]];
			} else { //electrons -------------------------------------------------------------------------
				lep->is_fake[i] = evt->el_isfake[lep->index[i]];
				lep->is_chmisid[i] = evt->el_ischmisid[lep->index[i]];
			}

		} else {
			lep->is_fake[i] = false;
			lep->is_chmisid[i] = false;
		}

		//The lepton-lepton overlap removal needs to be applied to pre-selected (baseline) leptons after the jet-lepton isolation requirement

		overlapping_lept = false;
		lep->lept_overlap[i] = overlapping_lept;

		double eta_i, phi_i;
		double eta_j, phi_j;

		if (lep->is_electron[i]) {
			if ((evt->el_nSCTHits[lep->index[i]] + evt->el_nPixHits[lep->index[i]]) < 4) {
				eta_i = evt->el_cl_eta[lep->index[i]];
				phi_i = evt->el_cl_phi[lep->index[i]];
			} else {
				eta_i = evt->el_tracketa[lep->index[i]];
				phi_i = evt->el_trackphi[lep->index[i]];
			}
		} else {
			eta_i = evt->mu_staco_eta[lep->index[i]];
			phi_i = evt->mu_staco_phi[lep->index[i]];

		}

		for (int j = 0; j < lep_baseline->num_leptons && !overlapping_lept; j++)  // loop over preseleciton ele
			//Check that the baseline lepton and the primary leptons are different objects
		  if (lep->index[i] != lep_baseline->index[j] || lep->is_electron[i] != lep_baseline->is_electron[j]) {  

				//if (lep_baseline->pt[j] > LeptPt) {

				if (lep_baseline->is_electron[j]) {
					if (!is_preselection_electron(evt, lep_baseline->index[j], lep_baseline->pt[j], elec_4jetOverlap))
						continue;
				} else {
					if (!is_preselection_muon(evt, lep_baseline->index[j], lep_baseline->pt[j], elec_4jetOverlap))
						continue;
				}

				if (lep_baseline->is_electron[j]) {

					if ((evt->el_nSCTHits[lep_baseline->index[j]] + evt->el_nPixHits[lep_baseline->index[j]]) < 4) {
						eta_j = evt->el_cl_eta[lep_baseline->index[j]];
						phi_j = evt->el_cl_phi[lep_baseline->index[j]];
					} else {
						eta_j = evt->el_tracketa[lep_baseline->index[j]];
						phi_j = evt->el_trackphi[lep_baseline->index[j]];
					}

				} else {
					eta_j = evt->mu_staco_eta[lep_baseline->index[j]];
					phi_j = evt->mu_staco_phi[lep_baseline->index[j]];
				}

				double deltaR = DeltaR(eta_i, phi_i, eta_j, phi_j);

				if (deltaR < 0.1) { //0.01 changed?
					if ((lep->is_electron[i] && !lep_baseline->is_electron[j]) || (!lep->is_electron[i] && lep_baseline->is_electron[j]))
						overlapping_lept = true;
				}

				/*	if (deltaR < 0.05) { // mu mu ?
					if (!lep->is_electron[i] && !lep_baseline->is_electron[j])
						overlapping_lept = true;

					if (lep->is_electron[i] && lep_baseline->is_electron[j] && lep->pt[i] < lep_baseline->pt[j]) // ?
						overlapping_lept = true;

						}*/

				//}
			}

		lep->lept_overlap[i] = overlapping_lept;

		///---------------------------------------
		if (lep->pt[i] > LeptPt && !overlapping_lept)
			lep->num_20GeV_leptons_noverlap++;

		if (lep->pt[i] > 10000. && !overlapping_lept)
		  lep->num_10GeV_leptons_noverlap++;

	}

	return;
}

//----------------------------------------------------------------------------
//Here we calculate charge of the first three leptons.
//----------------------------------------------------------------------------
void calcChargeLeptons(my_leptons *lep, myevt *evt) {

	lep->total_charge = 0;
	lep->softest_ss = -1;
	lep->is_tight_3rd_lep = true;

	int num_lept = 0;
	for (int i = 0; i < lep->num_leptons && num_lept < 3; i++) {
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			lep->total_charge += lep->charge[i];
			num_lept++;
		}
	}

	return;
}

//----------------------------------------------------------------------------
// calculates invariant mass of a lepton and a jet
// j --> lepton index
// i --> jet index
//----------------------------------------------------------------------------
float calcM_lept_jet(myevt *evt, my_leptons *lep, int j, int i) {

	float m = -1;
	float pt, px, py, pz, E, sf;

	if (!lep->is_electron[j]) { //muons -----------------------------------------------------------

		pt = evt->mu_staco_pt[lep->index[j]];
		px = evt->mu_staco_px[lep->index[j]];
		py = evt->mu_staco_py[lep->index[j]];
		pz = evt->mu_staco_pz[lep->index[j]];
		E = evt->mu_staco_E[lep->index[j]];
		sf = lep->pt[j] / pt;

	} else { //electrons -------------------------------------------------------------------------

		E = evt->el_cl_E[lep->index[j]];

		if ((evt->el_nSCTHits[lep->index[j]] + evt->el_nPixHits[lep->index[j]]) < 4) {
			pt = E / cosh(evt->el_cl_eta[lep->index[j]]);
			px = pt * cos(evt->el_cl_phi[lep->index[j]]);
			py = pt * sin(evt->el_cl_phi[lep->index[j]]);
			pz = pt * sinh(evt->el_cl_eta[lep->index[j]]);
		} else {
			pt = E / cosh(evt->el_tracketa[lep->index[j]]);
			px = pt * cos(evt->el_trackphi[lep->index[j]]);
			py = pt * sin(evt->el_trackphi[lep->index[j]]);
			pz = pt * sinh(evt->el_tracketa[lep->index[j]]);
		}

		sf = lep->pt[j] / pt;

	}

	m = pow(sf * E + evt->AntiKt4LCTopo.E[i], 2);
	m += -pow(sf * px + evt->AntiKt4LCTopo.px[i], 2);
	m += -pow(sf * py + evt->AntiKt4LCTopo.py[i], 2);
	m += -pow(sf * pz + evt->AntiKt4LCTopo.pz[i], 2);

	m = sqrt(m);

	return m;
}

//----------------------------------------------------------------------------
// here we check if a jet (index i) overlaps with an electron
//----------------------------------------------------------------------------
bool jet_overlaps_electron(myevt *evt, my_leptons *elec_4jetOverlap, int i) {

	bool dR_excl = false;

	float dR;
	//We exclude all electrons and muons from the jet collection
	for (int k = 0; k < elec_4jetOverlap->num_leptons && !dR_excl; k++) {

		if ((evt->el_nSCTHits[elec_4jetOverlap->index[k]] + evt->el_nPixHits[elec_4jetOverlap->index[k]]) < 4) {
			dR = DeltaR(evt->el_cl_eta[elec_4jetOverlap->index[k]], evt->el_cl_phi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
		} else {
			dR = DeltaR(evt->el_tracketa[elec_4jetOverlap->index[k]], evt->el_trackphi[elec_4jetOverlap->index[k]], evt->AntiKt4LCTopo.eta[i], evt->AntiKt4LCTopo.phi[i]);
		}

		dR_excl |= (dR <= 0.2);
	}

	return dR_excl;
}

//----------------------------------------------------------------------------
//Here we sort the leptons in Pt
//----------------------------------------------------------------------------
void sortLeptons(my_leptons *lep) {

	srtJt jet_srt[2 * MAXLEPT];
	my_leptons temp_lep;

	for (int i = 0; i < lep->num_leptons; i++) {
		jet_srt[i].ind = i;
		jet_srt[i].pt = lep->pt[i];
	}

	qsort(jet_srt, lep->num_leptons, sizeof(srtJt), jet_pt_comparator);

	for (int i = 0; i < lep->num_leptons; i++) {
		temp_lep.index[i] = lep->index[jet_srt[i].ind];
		temp_lep.pt[i] = lep->pt[jet_srt[i].ind];
		temp_lep.is_electron[i] = lep->is_electron[jet_srt[i].ind];
		temp_lep.charge[i] = lep->charge[jet_srt[i].ind];
		temp_lep.is_fake[i] = lep->is_fake[jet_srt[i].ind];
		temp_lep.is_chmisid[i] = lep->is_chmisid[jet_srt[i].ind];
		temp_lep.lept_overlap[i] = lep->lept_overlap[jet_srt[i].ind];

	}

	for (int i = 0; i < lep->num_leptons; i++) {
		lep->index[i] = temp_lep.index[i];
		lep->pt[i] = temp_lep.pt[i];
		lep->is_electron[i] = temp_lep.is_electron[i];
		lep->charge[i] = temp_lep.charge[i];
		lep->is_fake[i] = temp_lep.is_fake[i];
		lep->is_chmisid[i] = temp_lep.is_chmisid[i];
		lep->lept_overlap[i] = temp_lep.lept_overlap[i];
	}

	return;
}

//----------------------------------------------------------------------------
//Here we check if an event contains a Z-candidate
//----------------------------------------------------------------------------
void containsZ(my_leptons *lep, myevt *evt) {

	lep->has_Z = false;
	lep->ind1 = -1;
	lep->ind2 = -1;
	lep->MZ = -1;
	lep->lowest_M = -1;

	if (lep->num_leptons < 2)
		return;

	double best_M = -1;
	double M;

	int max_lept_count = -1;
	int lept_count = 0;
	for (int i = 0; i < lep->num_leptons && lept_count < 3; i++) {
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			lept_count++;
			max_lept_count = i;
		}
	}

	for (int i = 0; i <= max_lept_count; i++) //Only the first three leptons are taken into account
		for (int j = i + 1; j <= max_lept_count; j++) //Only the first three leptons are taken into account
			if (lep->pt[i] > LeptPt && lep->pt[j] > LeptPt && lep->is_electron[i] == lep->is_electron[j] && lep->charge[i] * lep->charge[j] < 0 && !lep->lept_overlap[i]
			    && !lep->lept_overlap[j]) { 

				if (!lep->is_electron[i]) { //muons -----------------------------------------------------------

				  double sf1 = lep->pt[i] / evt->mu_staco_pt[lep->index[i]]; // correction from pt that is already corrected to px and py and pz
					double sf2 = lep->pt[j] / evt->mu_staco_pt[lep->index[j]];

					M = pow(sf1 * evt->mu_staco_E[lep->index[i]] + sf2 * evt->mu_staco_E[lep->index[j]], 2);
					M += -pow(sf1 * evt->mu_staco_px[lep->index[i]] + sf2 * evt->mu_staco_px[lep->index[j]], 2);
					M += -pow(sf1 * evt->mu_staco_py[lep->index[i]] + sf2 * evt->mu_staco_py[lep->index[j]], 2);
					M += -pow(sf1 * evt->mu_staco_pz[lep->index[i]] + sf2 * evt->mu_staco_pz[lep->index[j]], 2);

					M = sqrt(M);

				} else { //electrons -------------------------------------------------------------------------

					double pt1, px1, py1, pz1, E1;
					int ind1 = lep->index[i];
					E1 = evt->el_cl_E[ind1];

					if ((evt->el_nSCTHits[ind1] + evt->el_nPixHits[ind1]) < 4) {
						pt1 = E1 / cosh(evt->el_cl_eta[ind1]);
						px1 = pt1 * cos(evt->el_cl_phi[ind1]);
						py1 = pt1 * sin(evt->el_cl_phi[ind1]);
						pz1 = pt1 * sinh(evt->el_cl_eta[ind1]);
					} else {
						pt1 = E1 / cosh(evt->el_tracketa[ind1]);
						px1 = pt1 * cos(evt->el_trackphi[ind1]);
						py1 = pt1 * sin(evt->el_trackphi[ind1]);
						pz1 = pt1 * sinh(evt->el_tracketa[ind1]);
					}

					double pt2, px2, py2, pz2, E2;
					int ind2 = lep->index[j];
					E2 = evt->el_cl_E[ind2];

					if ((evt->el_nSCTHits[ind2] + evt->el_nPixHits[ind2]) < 4) {
						pt2 = E2 / cosh(evt->el_cl_eta[ind2]);
						px2 = pt2 * cos(evt->el_cl_phi[ind2]);
						py2 = pt2 * sin(evt->el_cl_phi[ind2]);
						pz2 = pt2 * sinh(evt->el_cl_eta[ind2]);
					} else {
						pt2 = E2 / cosh(evt->el_tracketa[ind2]);
						px2 = pt2 * cos(evt->el_trackphi[ind2]);
						py2 = pt2 * sin(evt->el_trackphi[ind2]);
						pz2 = pt2 * sinh(evt->el_tracketa[ind2]);
					}

					double sf1 = lep->pt[i] / pt1;
					double sf2 = lep->pt[j] / pt2;

					M = pow(E1 * sf1 + E2 * sf2, 2) - pow(px1 * sf1 + px2 * sf2, 2) - pow(py1 * sf1 + py2 * sf2, 2) - pow(pz1 * sf1 + pz2 * sf2, 2);
					M = sqrt(M);

				}

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

				if (fabs(M - 91000.) < fabs(best_M - 91000.)) {
					best_M = M;
					lep->MZ = M;
					lep->ind1 = i;
					lep->ind2 = j;
				}

				if (fabs(M - 91000.) < 7000.) // within 7 gev
					lep->has_Z = true;

			}

	return;
}

//----------------------------------------------------------------------------
//Here we calculate the invariant mass of two simulated particles
//----------------------------------------------------------------------------
double CalcMass(myevt *evt, int ind0, int ind1) {

	TLorentzVector l1;
	l1.SetPtEtaPhiM(evt->parton_pt[ind0], evt->parton_eta[ind0], evt->parton_phi[ind0], evt->parton_m[ind0]);

	TLorentzVector l2;
	l2.SetPtEtaPhiM(evt->parton_pt[ind1], evt->parton_eta[ind1], evt->parton_phi[ind1], evt->parton_m[ind1]);

	l1 += l2;

	return l1.M();
}

//----------------------------------------------------------------------------
//Here we calculate the missing transverse momentum
//----------------------------------------------------------------------------
TVector2 getMET(myevt *evt, calJet *jet, calJet *jet_D3PD, my_leptons *lep, SystErr::Syste whichsyste, METUtility* _metUtility) {

	vector<float> jetpt(jet->n);
	vector<float> jeteta(jet->n);
	vector<float> jetphi(jet->n);
	vector<float> jete(jet->n);

	std::vector < vector<float> > new_jetwet;
	std::vector < vector<float> > new_jetwpx;
	std::vector < vector<float> > new_jetwpy;

	std::vector < vector<unsigned int> > jetstatus;

	for (int j = 0; j < jet->n; ++j) {
		jetpt[j] = jet->pt[j];
		//jeteta[j] = jet->eta[j];
		//jetphi[j] = jet->phi[j];
		jeteta[j] = jet_D3PD->eta[j];
		jetphi[j] = jet_D3PD->phi[j];
		jete[j] = jet->E[j];

		vector<float> j_wpx;
		vector<float> j_wpy;
		vector<float> j_wet;
		vector<unsigned int> j_sts;

		// Temporary fix for too large (or too low) jet weights
		// Not nice, waiting for a final fix on the etmiss side
		if (jet->MET_Egamma10NoTau_wpx[j] < 0.5 * jet->MET_Egamma10NoTau_wet[j] || jet->MET_Egamma10NoTau_wpx[j] > 2. * jet->MET_Egamma10NoTau_wet[j])
			jet->MET_Egamma10NoTau_wpx[j] = jet->MET_Egamma10NoTau_wet[j];

		if (jet->MET_Egamma10NoTau_wpy[j] < 0.5 * jet->MET_Egamma10NoTau_wet[j] || jet->MET_Egamma10NoTau_wpy[j] > 2. * jet->MET_Egamma10NoTau_wet[j])
			jet->MET_Egamma10NoTau_wpy[j] = jet->MET_Egamma10NoTau_wet[j];

		j_wpx.push_back(jet->MET_Egamma10NoTau_wpx[j]); //MET_Egamma10NoTau_wpx
		j_wpy.push_back(jet->MET_Egamma10NoTau_wpy[j]);
		j_wet.push_back(jet->MET_Egamma10NoTau_wet[j]);
		j_sts.push_back(jet->MET_Egamma10NoTau_statusWord[j]);

		if (jet->MET_Egamma10NoTau_wet2[j] > -999.) {

			if (jet->MET_Egamma10NoTau_wpx2[j] < 0.5 * jet->MET_Egamma10NoTau_wet2[j] || jet->MET_Egamma10NoTau_wpx2[j] > 2. * jet->MET_Egamma10NoTau_wet2[j])
				jet->MET_Egamma10NoTau_wpx2[j] = jet->MET_Egamma10NoTau_wet2[j];

			if (jet->MET_Egamma10NoTau_wpy2[j] < 0.5 * jet->MET_Egamma10NoTau_wet2[j] || jet->MET_Egamma10NoTau_wpy2[j] > 2. * jet->MET_Egamma10NoTau_wet2[j])
				jet->MET_Egamma10NoTau_wpy2[j] = jet->MET_Egamma10NoTau_wet2[j];

			j_wpx.push_back(jet->MET_Egamma10NoTau_wpx2[j]); //MET_Egamma10NoTau_wpx
			j_wpy.push_back(jet->MET_Egamma10NoTau_wpy2[j]);
			j_wet.push_back(jet->MET_Egamma10NoTau_wet2[j]);
			j_sts.push_back(jet->MET_Egamma10NoTau_statusWord2[j]);

		}

		if (jet->MET_Egamma10NoTau_wet3[j] > -999.) {

			if (jet->MET_Egamma10NoTau_wpx3[j] < 0.5 * jet->MET_Egamma10NoTau_wet3[j] || jet->MET_Egamma10NoTau_wpx3[j] > 2. * jet->MET_Egamma10NoTau_wet3[j])
				jet->MET_Egamma10NoTau_wpx3[j] = jet->MET_Egamma10NoTau_wet3[j];

			if (jet->MET_Egamma10NoTau_wpy3[j] < 0.5 * jet->MET_Egamma10NoTau_wet3[j] || jet->MET_Egamma10NoTau_wpy3[j] > 2. * jet->MET_Egamma10NoTau_wet3[j])
				jet->MET_Egamma10NoTau_wpy3[j] = jet->MET_Egamma10NoTau_wet3[j];

			j_wpx.push_back(jet->MET_Egamma10NoTau_wpx3[j]); //MET_Egamma10NoTau_wpx
			j_wpy.push_back(jet->MET_Egamma10NoTau_wpy3[j]);
			j_wet.push_back(jet->MET_Egamma10NoTau_wet3[j]);
			j_sts.push_back(jet->MET_Egamma10NoTau_statusWord3[j]);

		}

		new_jetwet.push_back(j_wet);
		new_jetwpx.push_back(j_wpx);
		new_jetwpy.push_back(j_wpy);
		jetstatus.push_back(j_sts);

	}

	_metUtility->reset();
//_metUtility->configEgammaJetFix(true, false, false, 0.3); // OFF by default
	_metUtility->configMissingET(true, false); //_metUtility->configMissingET(true, true);
	_metUtility->setJetPUcode(MissingETTags::DEFAULT); //_metUtility->setJetPUcode(MissingETTags::JPU_JET_JVFCUT);

	_metUtility->setMETTerm(METUtil::SoftTerms, evt->MET_Egamma10NoTau_CellOut_etx, evt->MET_Egamma10NoTau_CellOut_ety, evt->MET_Egamma10NoTau_CellOut_sumet);
	_metUtility->setAverageIntPerXing(evt->averageIntPerXing);
	_metUtility->setJetParameters(&jetpt, &jeteta, &jetphi, &jete, &new_jetwet, &new_jetwpx, &new_jetwpy, &jetstatus);

// -----------------------------------

	vector<float> elpt;
	vector<float> eleta;
	vector<float> elphi;

	std::vector < vector<unsigned int> > new_elstatus;

	std::vector < vector<float> > new_elwet;
	std::vector < vector<float> > new_elwpx;
	std::vector < vector<float> > new_elwpy;

	for (int j = 0; j < lep->num_leptons; j++)
		if (lep->is_electron[j]) {
			int iEl = lep->index[j];

			elpt.push_back(lep->pt[j]);
			if ((evt->el_nSCTHits[iEl] + evt->el_nPixHits[iEl]) < 4) {
				eleta.push_back(evt->el_cl_eta[iEl]);
				elphi.push_back(evt->el_cl_phi[iEl]);
			} else {
				eleta.push_back(evt->el_tracketa[iEl]);
				elphi.push_back(evt->el_trackphi[iEl]);
			}

			vector<unsigned int> l_sts;
			l_sts.push_back(evt->el_MET_Egamma10NoTau_statusWord[iEl]);
			new_elstatus.push_back(l_sts);

			// Temporary fix for too large (or too low) el weights
			// Not nice, waiting for a final fix on the etmiss side
			if (evt->el_MET_Egamma10NoTau_wpx[iEl] < 0.5 * evt->el_MET_Egamma10NoTau_wet[iEl] || evt->el_MET_Egamma10NoTau_wpx[iEl] > 2. * evt->el_MET_Egamma10NoTau_wet[iEl]) {
				evt->el_MET_Egamma10NoTau_wpx[iEl] = evt->el_MET_Egamma10NoTau_wet[iEl];
			}

			if (evt->el_MET_Egamma10NoTau_wpy[iEl] < 0.5 * evt->el_MET_Egamma10NoTau_wet[iEl] || evt->el_MET_Egamma10NoTau_wpy[iEl] > 2. * evt->el_MET_Egamma10NoTau_wet[iEl]) {
				evt->el_MET_Egamma10NoTau_wpy[iEl] = evt->el_MET_Egamma10NoTau_wet[iEl];
			}

			vector<float> l_wpx;
			vector<float> l_wpy;
			vector<float> l_wet;

			l_wpx.push_back(evt->el_MET_Egamma10NoTau_wpx[iEl]);
			l_wpy.push_back(evt->el_MET_Egamma10NoTau_wpy[iEl]);
			l_wet.push_back(evt->el_MET_Egamma10NoTau_wet[iEl]);

			new_elwet.push_back(l_wet);
			new_elwpx.push_back(l_wpx);
			new_elwpy.push_back(l_wpy);
		}

	_metUtility->setElectronParameters(&elpt, &eleta, &elphi, &new_elwet, &new_elwpx, &new_elwpy, &new_elstatus);
	_metUtility->setMETTerm(METUtil::RefGamma, evt->MET_Egamma10NoTau_RefGamma_etx, evt->MET_Egamma10NoTau_RefGamma_ety, evt->MET_Egamma10NoTau_RefGamma_sumet);

//	_metUtility->setMETTerm(METUtil::SoftJets, evt->MET_Egamma10NoTau_STVF_SoftJets_etx, evt->MET_Egamma10NoTau_STVF_SoftJets_ety,
//			evt->MET_Egamma10NoTau_STVF_SoftJets_sumet);

//	_metUtility->setMETTerm(METUtil::CellOut, evt->MET_Egamma10NoTau_STVF_CellOut_etx, evt->MET_Egamma10NoTau_STVF_CellOut_ety,
//			evt->MET_Egamma10NoTau_STVF_CellOut_sumet);

	/*
	 double stvf_weight = evt->MET_Egamma10NoTau_STVF_CellOut_TrackPV_sumet / evt->MET_Egamma10NoTau_STVF_CellOut_Track_sumet;
	 double MET_CellOutNew_STVF_etx = evt->MET_Egamma10NoTau_STVF_CellOut_etx * stvf_weight;
	 double MET_CellOutNew_STVF_ety = evt->MET_Egamma10NoTau_STVF_CellOut_ety * stvf_weight;
	 double MET_CellOutNew_STVF_sumet = evt->MET_Egamma10NoTau_STVF_CellOut_sumet * stvf_weight;

	 _metUtility->setMETTerm(METUtil::CellOutEflow,MET_CellOutNew_STVF_etx, MET_CellOutNew_STVF_ety, MET_CellOutNew_STVF_sumet);
	 */

// -----------------------------------
	vector<float> mupt;
	vector<float> mueta;
	vector<float> muphi;

	std::vector < vector<unsigned int> > new_statusWord;

	std::vector < vector<float> > new_wet;
	std::vector < vector<float> > new_wpx;
	std::vector < vector<float> > new_wpy;

	vector<float> mu_ms_qoverp;
	vector<float> mu_ms_theta;
	vector<float> mu_ms_phi;
	vector<float> mu_charge;

	for (int j = 0; j < lep->num_leptons; j++)
		if (!lep->is_electron[j]) {
			int iMuIdx = lep->index[j];

			mupt.push_back(lep->pt[j]);
			mueta.push_back(evt->mu_staco_eta[iMuIdx]);
			muphi.push_back(evt->mu_staco_phi[iMuIdx]);

			mu_ms_qoverp.push_back(evt->mu_staco_ms_qoverp[iMuIdx]);
			mu_ms_theta.push_back(evt->mu_staco_ms_theta[iMuIdx]);
			mu_ms_phi.push_back(evt->mu_staco_ms_phi[iMuIdx]);
			mu_charge.push_back(evt->mu_staco_charge[iMuIdx]);

			vector<float> univec;
			univec.push_back(1.);
			new_wet.push_back(univec);
			new_wpx.push_back(univec);
			new_wpy.push_back(univec);

			vector<unsigned int> defvec;
			defvec.push_back(MissingETTags::DEFAULT);
			new_statusWord.push_back(defvec);

		}

	_metUtility->setMuonParameters(&mupt, &mueta, &muphi, &new_wet, &new_wpx, &new_wpy, &new_statusWord);
	_metUtility->setExtraMuonParameters(&mu_ms_qoverp, &mu_ms_theta, &mu_ms_phi, &mu_charge);

// -----------------------------------

	METUtility::METObject finalMet;

	switch (whichsyste) {
// Soft Terms scale
	case SystErr::SCALESTUP:
		finalMet = _metUtility->getMissingET(METUtil::RefFinal, METUtil::ScaleSoftTermsUp);
		break;
	case SystErr::SCALESTDOWN:
		finalMet = _metUtility->getMissingET(METUtil::RefFinal, METUtil::ScaleSoftTermsDown);
		break;
		// Soft Terms resolution
	case SystErr::RESOSTUP:
		finalMet = _metUtility->getMissingET(METUtil::RefFinal, METUtil::ResoSoftTermsUp);
		break;
	case SystErr::RESOSTDOWN:
		finalMet = _metUtility->getMissingET(METUtil::RefFinal, METUtil::ResoSoftTermsDown);
		break;
	case SystErr::NONE:
	default:
		finalMet = _metUtility->getMissingET(METUtil::RefFinal);
		break;
	}

	TVector2 met(finalMet.etx(), finalMet.ety());
	return (met);
}

//----------------------------------------------------------------------------
// Smear pt of muons (in simulations)
//----------------------------------------------------------------------------
void smearMuonPt(myevt *evt, my_leptons *lep, MuonSmear::SmearingClass *mcp_smear) {

	if (!evt->isMC)
		return;

	int mu_ind;
	float charge;
	float eta;
	float ptcb;
	float ptms;
	float ptid;
	int seed;

	for (int i = 0; i < lep->num_leptons; i++)
		if (!lep->is_electron[i]) {
			mu_ind = lep->index[i];

			//Retrieve Eta, PtCB, PtMS and PtID from containers/ntuples
			// in MeV
			charge = evt->mu_staco_charge[mu_ind];
			eta = evt->mu_staco_eta[mu_ind];
			ptcb = evt->mu_staco_pt[mu_ind];
			ptms = (evt->mu_staco_me_qoverp_exPV[mu_ind] != 0.) ? fabs(sin(evt->mu_staco_me_theta_exPV[mu_ind]) / evt->mu_staco_me_qoverp_exPV[mu_ind]) : 0.;
			ptid = (evt->mu_staco_id_qoverp_exPV[mu_ind] != 0.) ? fabs(sin(evt->mu_staco_id_theta_exPV[mu_ind]) / evt->mu_staco_id_qoverp_exPV[mu_ind]) : 0.;

			seed = int(fabs(evt->mu_staco_phi[mu_ind] * 1.e+5));
			if (!seed)
				++seed;

			mcp_smear->SetSeed(seed);

			if (evt->mu_staco_isCombinedMuon[mu_ind]) {
				mcp_smear->Event(ptms, ptid, ptcb, eta, charge);
				lep->pt[i] = mcp_smear->pTCB();
			} else {
				if (evt->mu_staco_isSegmentTaggedMuon[mu_ind]) {
					mcp_smear->Event(ptid, eta, "ID", charge);
					lep->pt[i] = mcp_smear->pTID();
				} else {
					mcp_smear->Event(ptms, eta, "MS", charge);
					lep->pt[i] = mcp_smear->pTMS();
				}
			}

			if (lep->pt[i] <= 0)
				std::cerr << "\nERROR: Muon smearing is applied incorrectly\n";

		}

	return;
}

//----------------------------------------------------------------------------
// Smear pt of muons (in simulations)
//----------------------------------------------------------------------------
float smear_A_MuonPt(myevt *evt, int mu_ind, MuonSmear::SmearingClass *mcp_smear) {

	float pt = evt->mu_staco_pt[mu_ind];

	if (!evt->isMC)
		return pt;

	float charge;
	float eta;
	float ptcb;
	float ptms;
	float ptid;
	int seed;

//Retrieve Eta, PtCB, PtMS and PtID from containers/ntuples
// in MeV
	charge = evt->mu_staco_charge[mu_ind];
	eta = evt->mu_staco_eta[mu_ind];
	ptcb = evt->mu_staco_pt[mu_ind];
	ptms = (evt->mu_staco_me_qoverp_exPV[mu_ind] != 0.) ? fabs(sin(evt->mu_staco_me_theta_exPV[mu_ind]) / evt->mu_staco_me_qoverp_exPV[mu_ind]) : 0.;
	ptid = (evt->mu_staco_id_qoverp_exPV[mu_ind] != 0.) ? fabs(sin(evt->mu_staco_id_theta_exPV[mu_ind]) / evt->mu_staco_id_qoverp_exPV[mu_ind]) : 0.;

	seed = int(fabs(evt->mu_staco_phi[mu_ind] * 1.e+5));
	if (!seed)
		++seed;
	mcp_smear->SetSeed(seed);

	if (evt->mu_staco_isCombinedMuon[mu_ind]) {
		mcp_smear->Event(ptms, ptid, ptcb, eta, charge);
		pt = mcp_smear->pTCB();
	} else {
		if (evt->mu_staco_isSegmentTaggedMuon[mu_ind]) {
			mcp_smear->Event(ptid, eta, "ID", charge);
			pt = mcp_smear->pTID();
		} else {
			mcp_smear->Event(ptms, eta, "MS", charge);
			pt = mcp_smear->pTMS();
		}
	}

	if (pt <= 0)
		std::cerr << "\nERROR: Muon smearing is applied incorrectly\n";

	return pt;
}

//----------------------------------------------------------------------------
// Smear pt of electrons (in simulations)
//----------------------------------------------------------------------------
void smearElectronPt(myevt *evt, my_leptons *lep, egRescaler::EnergyRescalerUpgrade* eRescale) {

	if (!evt->isMC)
		return;
	int el_ind;
	float energy;
	float smearcorr;
	float cl_eta;
//bool mcWithConstantTerm = false; //false by default in funtions, as it should be for mc12

	for (int i = 0; i < lep->num_leptons; i++)
		if (lep->is_electron[i]) {
			el_ind = lep->index[i];
			energy = evt->el_cl_E[el_ind];
			cl_eta = evt->el_cl_eta[el_ind];
			///Set random seed, probably to something like eventNumber+offset
			//int evtNumber = 65537 + evt.eventNumber;
			//eRescale.SetRandomSeed(evtNumber);

			int seed = int(1.e+5 * fabs(evt->el_cl_phi[el_ind]));
			if (!seed)
				++seed;
			eRescale->SetRandomSeed(seed);

			smearcorr = eRescale->getSmearingCorrection(cl_eta, energy, egRescaler::EnergyRescalerUpgrade::Nominal); //in MeV
			//cout << "Energy : " << energy << "  Smeared energy : " << smearcorr * energy << endl;

			lep->pt[i] *= smearcorr;
		}

	return;
}

//----------------------------------------------------------------------------
// Smear pt of an electron (in simulations)
//----------------------------------------------------------------------------
float smear_An_ElectronPt(myevt *evt, int el_ind, egRescaler::EnergyRescalerUpgrade* eRescale) {

	if (!evt->isMC)
		return 1.;

///Set random seed
	int seed = int(1.e+5 * fabs(evt->el_cl_phi[el_ind]));
	if (!seed)
		++seed;
	eRescale->SetRandomSeed(seed);

	return eRescale->getSmearingCorrection(evt->el_cl_eta[el_ind], evt->el_cl_E[el_ind], egRescaler::EnergyRescalerUpgrade::Nominal); //in MeV
//cout << "Energy : " << energy << "  Smeared energy : " << smearcorr * energy << endl;

}

//----------------------------------------------------------------------------
// Scale  pt of electrons (in simulations)
//----------------------------------------------------------------------------
void scaleElectronPt(myevt *evt, my_leptons *lep, egRescaler::EnergyRescalerUpgrade* eRescale, bool isATLFAST) {

	float unCorrE;
	float cl_eta;
	//float cl_phi;
//double et;
	float corrE;
	int el_ind;

//DATA -----------------------------------------------------------------
	for (int i = 0; i < lep->num_leptons && !evt->isMC; i++)
		if (lep->is_electron[i]) {
			el_ind = lep->index[i];
			unCorrE = evt->el_cl_E[el_ind]; // uncorrected calorimetric energy
			cl_eta = evt->el_cl_eta[el_ind]; // cluster eta
			//cl_phi = evt->el_cl_phi[el_ind]; // cluster phi
			//et = lep->pt[i] / 1000.; // et = cl_e/cosh(trk_eta) if (nSCT + nPix) >= 4) otherwise  et = cl_et

			//corrE = eRescale.applyEnergyCorrectionGeV(cl_eta, cl_phi, unCorrE, et, 0, part_type); //OLD
			corrE = eRescale->applyEnergyCorrection(cl_eta, unCorrE, egRescaler::EnergyRescalerUpgrade::Electron, egRescaler::EnergyRescalerUpgrade::Nominal);
			lep->pt[i] *= corrE / unCorrE;
			//std::cout << "\n corrE " << corrE;

			//correction for the crack electrons
			//lep->pt[i] *= eRescale.applyMCCalibrationGeV(cl_eta, et, "ELECTRON"); //OLD
			//lep->pt[i] *= eRescale->applyMCCalibration(cl_eta, 1000. * et, egRescaler::EnergyRescalerUpgrade::Electron);
		}

//MC -----------------------------------------------------------------
	for (int i = 0; i < lep->num_leptons && evt->isMC; i++)
		if (lep->is_electron[i]) {
			el_ind = lep->index[i];
			cl_eta = evt->el_cl_eta[el_ind]; // cluster eta
			//et = lep->pt[i] / 1000.; // et = cl_e/cosh(trk_eta) if (nSCT + nPix) >= 4) otherwise  et = cl_et

			//correction for the crack electrons
			//lep->pt[i] *= eRescale.applyMCCalibrationMeV(cl_eta, et, "ELECTRON"); //OLD
			//lep->pt[i] *= eRescale->applyMCCalibration(cl_eta, 1000. * et, egRescaler::EnergyRescalerUpgrade::Electron);

			if (isATLFAST)
				lep->pt[i] *= eRescale->applyAFtoG4(cl_eta);
		}

	return;
}

//----------------------------------------------------------------------------
// Scale  pt of an electron
//----------------------------------------------------------------------------
float scale_An_ElectronPt(myevt *evt, int el_ind, egRescaler::EnergyRescalerUpgrade* eRescale, bool isATLFAST) {

	if (!evt->isMC) { //DATA -----------------------------------------------------------------

		return eRescale->applyEnergyCorrection(evt->el_cl_eta[el_ind], evt->el_cl_E[el_ind], egRescaler::EnergyRescalerUpgrade::Electron, egRescaler::EnergyRescalerUpgrade::Nominal)
				/ evt->el_cl_E[el_ind];

	} else { //MC -----------------------------------------------------------------

		if (isATLFAST)
			return eRescale->applyAFtoG4(evt->el_cl_eta[el_ind]);
	}

	return 1.0;
}

//----------------------------------------------------------------------------
// Systematics -- Smear pt of muons (in simulations)
//----------------------------------------------------------------------------
void smearMuonPt_syst(myevt *evt, my_leptons *lep, MuonSmear::SmearingClass *mcp_smear, const char* type) {

	if (!evt->isMC)
		return;

	int mu_ind;
	float charge;
	float eta;
	float ptcb;
	float ptms;
	float ptid;

	for (int i = 0; i < lep->num_leptons; i++)
		if (!lep->is_electron[i]) {
			mu_ind = lep->index[i];

			//Retrieve Eta, PtCB, PtMS and PtID from containers/ntuples
			// in MeV
			charge = evt->mu_staco_charge[mu_ind];
			eta = evt->mu_staco_eta[mu_ind];
			ptcb = evt->mu_staco_pt[mu_ind];
			ptms = (evt->mu_staco_me_qoverp_exPV[mu_ind] != 0.) ? fabs(sin(evt->mu_staco_me_theta_exPV[mu_ind]) / evt->mu_staco_me_qoverp_exPV[mu_ind]) : 0.;
			ptid = (evt->mu_staco_id_qoverp_exPV[mu_ind] != 0.) ? fabs(sin(evt->mu_staco_id_theta_exPV[mu_ind]) / evt->mu_staco_id_qoverp_exPV[mu_ind]) : 0.;

			mcp_smear->SetSeed(evt->eventNumber, i);
			if (evt->mu_staco_isCombinedMuon[mu_ind])
				mcp_smear->Event(ptms, ptid, ptcb, eta, charge);
			else if (evt->mu_staco_isSegmentTaggedMuon[mu_ind])
				mcp_smear->Event(ptid, eta, "ID", charge);
			else
				mcp_smear->Event(ptms, eta, "MS", charge);

			//systematic uncertainties ------------------------------------------------------
			//Get Smeared Pts
			double pTCB_smeared = evt->mu_staco_pt[mu_ind]; // = mcp_smear.pTCB();
			double pTMS_smeared = evt->mu_staco_pt[mu_ind]; // = mcp_smear.pTMS();
			double pTID_smeared = evt->mu_staco_pt[mu_ind]; // = mcp_smear.pTID();

			mcp_smear->PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, type);
			if (evt->mu_staco_isCombinedMuon[mu_ind])
				lep->pt[i] = pTCB_smeared;
			else if (evt->mu_staco_isSegmentTaggedMuon[mu_ind])
				lep->pt[i] = pTID_smeared;
			else
				lep->pt[i] = pTMS_smeared;
			if (lep->pt[i] <= 0)
				std::cerr << "\nERROR: Muon smearing is applied incorrectly\n";

			lep->delta_met_x += -(lep->pt[i] - evt->mu_staco_pt[mu_ind]) * cos(evt->mu_staco_phi[mu_ind]);
			lep->delta_met_y += -(lep->pt[i] - evt->mu_staco_pt[mu_ind]) * sin(evt->mu_staco_phi[mu_ind]);

			/*
			 * //MSUP
			 mcp_smear.PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, "MSUP");
			 lep_msup.pt[i] = pTCB_smeared;
			 if (lep_msup.pt[i] <= 0)
			 std::cerr << "\nERROR: Muon smearing is applied incorrectly\n";

			 lep_msup.delta_met_x += -(lep_msup.pt[i] - evt.mu_staco_pt[mu_ind]) * cos(evt.mu_staco_phi[mu_ind]);
			 lep_msup.delta_met_y += -(lep_msup.pt[i] - evt.mu_staco_pt[mu_ind]) * sin(evt.mu_staco_phi[mu_ind]);

			 //MSLOW
			 mcp_smear.PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, "MSLOW");
			 lep_msdn.pt[i] = pTCB_smeared;
			 if (lep_msdn.pt[i] <= 0)
			 std::cerr << "\nERROR: Muon smearing is applied incorrectly\n";

			 lep_msdn.delta_met_x += -(lep_msdn.pt[i] - evt.mu_staco_pt[mu_ind]) * cos(evt.mu_staco_phi[mu_ind]);
			 lep_msdn.delta_met_y += -(lep_msdn.pt[i] - evt.mu_staco_pt[mu_ind]) * sin(evt.mu_staco_phi[mu_ind]);

			 //IDUP
			 mcp_smear.PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, "IDUP");
			 lep_mrup.pt[i] = pTCB_smeared;
			 if (lep_mrup.pt[i] <= 0)
			 std::cerr << "\nERROR: Muon smearing is applied incorrectly\n";

			 lep_mrup.delta_met_x += -(lep_mrup.pt[i] - evt.mu_staco_pt[mu_ind]) * cos(evt.mu_staco_phi[mu_ind]);
			 lep_mrup.delta_met_y += -(lep_mrup.pt[i] - evt.mu_staco_pt[mu_ind]) * sin(evt.mu_staco_phi[mu_ind]);

			 //IDLOW
			 mcp_smear.PTVar(pTMS_smeared, pTID_smeared, pTCB_smeared, "IDLOW");
			 lep_mrdn.pt[i] = pTCB_smeared;
			 if (lep_mrdn.pt[i] <= 0)
			 std::cerr << "\nERROR: Muon smearing is applied incorrectly\n";

			 lep_mrdn.delta_met_x += -(lep_mrdn.pt[i] - evt.mu_staco_pt[mu_ind]) * cos(evt.mu_staco_phi[mu_ind]);
			 lep_mrdn.delta_met_y += -(lep_mrdn.pt[i] - evt.mu_staco_pt[mu_ind]) * sin(evt.mu_staco_phi[mu_ind]);
			 */

		} //end of muon smearing loop

	return;
}

//----------------------------------------------------------------------------
bool NoBadMuon(myevt *evt, my_leptons * lep_met, my_leptons * elec_4jetOverlap) {

	bool nobadmuon = true;

	for (int i = 0; i < lep_met->num_leptons; i++)
		if (!lep_met->is_electron[i])
			//We do not remove use the muons before the muon-jet overlap (isolaiton).
			if (is_preselection_muon_noIso(evt, lep_met->index[i], lep_met->pt[i])) {
				if (evt->mu_staco_qoverp_exPV[lep_met->index[i]] != 0 && evt->mu_staco_qoverp_exPV[lep_met->index[i]] > -99999.)
					nobadmuon &= (sqrt(evt->mu_staco_cov_qoverp_exPV[lep_met->index[i]]) / fabs(evt->mu_staco_qoverp_exPV[lep_met->index[i]])) < 0.2;
			}

	return nobadmuon;
}

//----------------------------------------------------------------------------
bool NoCosmicMuon(myevt *evt, my_leptons * lep_met, my_leptons * elec_4jetOverlap) {

	bool nocosmicmuon = true;

	for (int i = 0; i < lep_met->num_leptons; i++)
		if (!lep_met->is_electron[i])
			if (is_preselection_muon(evt, lep_met->index[i], lep_met->pt[i], elec_4jetOverlap)) {
				nocosmicmuon &= fabs(evt->mu_staco_z0_exPV[lep_met->index[i]]) < 1.0;
				nocosmicmuon &= fabs(evt->mu_staco_d0_exPV[lep_met->index[i]]) < 0.2;
			}

	return nocosmicmuon;
}

//----------------------------------------------------------------------------
// Sasha: I fixed a couple of bugs in the mass calculation.
// Othmane: Dilepton mass regardless if SS or OS SF
double dilepton_mass(my_leptons *lep, myevt *evt) {

	if (lep->num_leptons < 2)
		return -9999.;

	float pt[3], px[3], py[3], pz[3], E[3], q[3];
	bool is_el[3];
	float sf[3];
	float M;
	float min_M = 9999999999.;
	int num_lept = 0;

	for (int i = 0; i < lep->num_leptons && num_lept < 3; i++) { //Only the first two leptons are taken into account
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {

			if (!lep->is_electron[i]) { //muons -----------------------------------------------------------

				pt[num_lept] = evt->mu_staco_pt[lep->index[i]];
				px[num_lept] = evt->mu_staco_px[lep->index[i]];
				py[num_lept] = evt->mu_staco_py[lep->index[i]];
				pz[num_lept] = evt->mu_staco_pz[lep->index[i]];
				E[num_lept] = evt->mu_staco_E[lep->index[i]];

				sf[num_lept] = lep->pt[i] / pt[num_lept];
				is_el[num_lept] = false;
				q[num_lept] = evt->mu_staco_charge[lep->index[i]];

			} else { //electrons -------------------------------------------------------------------------

				E[num_lept] = evt->el_cl_E[lep->index[i]];

				if ((evt->el_nSCTHits[lep->index[i]] + evt->el_nPixHits[lep->index[i]]) < 4) {
					pt[num_lept] = E[num_lept] / cosh(evt->el_cl_eta[lep->index[i]]);
					px[num_lept] = pt[num_lept] * cos(evt->el_cl_phi[lep->index[i]]);
					py[num_lept] = pt[num_lept] * sin(evt->el_cl_phi[lep->index[i]]);
					pz[num_lept] = pt[num_lept] * sinh(evt->el_cl_eta[lep->index[i]]);
				} else {
					pt[num_lept] = E[num_lept] / cosh(evt->el_tracketa[lep->index[i]]);
					px[num_lept] = pt[num_lept] * cos(evt->el_trackphi[lep->index[i]]);
					py[num_lept] = pt[num_lept] * sin(evt->el_trackphi[lep->index[i]]);
					pz[num_lept] = pt[num_lept] * sinh(evt->el_tracketa[lep->index[i]]);
				}

				sf[num_lept] = lep->pt[i] / pt[num_lept];
				is_el[num_lept] = true;
				q[num_lept] = evt->el_charge[lep->index[i]];

			}

			num_lept++;
		}
	}

	if (num_lept >= 2) {
		for (int i = 0; i < num_lept; i++) {
		  for (int j = i + 1; j < num_lept; j++){

		    //		    if(num_lept == 2 && q[i] * q[j]>0) // If 2SS than skip computing invariant mass
		    //		      return -9999;
		    /*
		    // OS SF
		    if (is_el[i] == is_el[j] && q[i] * q[j] < 0) {

					M = pow(E[i] * sf[i] + E[j] * sf[j], 2) - pow(px[i] * sf[i] + px[j] * sf[j], 2) - pow(py[i] * sf[i] + py[j] * sf[j], 2) - pow(pz[i] * sf[i] + pz[j] * sf[j], 2);
					M = sqrt(M);

					if (min_M > M)
						min_M = M;
				}
		    */

		    M = pow(E[i] * sf[i] + E[j] * sf[j], 2) - pow(px[i] * sf[i] + px[j] * sf[j], 2) - pow(py[i] * sf[i] + py[j] * sf[j], 2) - pow(pz[i] * sf[i] + pz[j] * sf[j], 2);
		    M = sqrt(M);

		    if (min_M > M)
		      min_M = M;
		  }
		}
	}
	return min_M;

}

//----------------------------------------------------------------------------
// Sasha: I fixed a couple of bugs in the mass calculation.
double trilepton_mass(my_leptons *lep, myevt *evt) {

	if (lep->num_leptons < 2)
		return -9999.;

	float pt[3], px[3], py[3], pz[3], E[3], q[3];
	bool is_el[3];
	float sf[3];
	float M = -999.;
	int num_lept = 0;

	for (int i = 0; i < lep->num_leptons && num_lept < 3; i++) { //Only the first two leptons are taken into account
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {

			if (!lep->is_electron[i]) { //muons -----------------------------------------------------------

				pt[num_lept] = evt->mu_staco_pt[lep->index[i]];
				px[num_lept] = evt->mu_staco_px[lep->index[i]];
				py[num_lept] = evt->mu_staco_py[lep->index[i]];
				pz[num_lept] = evt->mu_staco_pz[lep->index[i]];
				E[num_lept] = evt->mu_staco_E[lep->index[i]];

				sf[num_lept] = lep->pt[i] / pt[num_lept];
				is_el[num_lept] = false;
				q[num_lept] = evt->mu_staco_charge[lep->index[i]];

			} else { //electrons -------------------------------------------------------------------------

				E[num_lept] = evt->el_cl_E[lep->index[i]];

				if ((evt->el_nSCTHits[lep->index[i]] + evt->el_nPixHits[lep->index[i]]) < 4) {
					pt[num_lept] = E[num_lept] / cosh(evt->el_cl_eta[lep->index[i]]);
					px[num_lept] = pt[num_lept] * cos(evt->el_cl_phi[lep->index[i]]);
					py[num_lept] = pt[num_lept] * sin(evt->el_cl_phi[lep->index[i]]);
					pz[num_lept] = pt[num_lept] * sinh(evt->el_cl_eta[lep->index[i]]);
				} else {
					pt[num_lept] = E[num_lept] / cosh(evt->el_tracketa[lep->index[i]]);
					px[num_lept] = pt[num_lept] * cos(evt->el_trackphi[lep->index[i]]);
					py[num_lept] = pt[num_lept] * sin(evt->el_trackphi[lep->index[i]]);
					pz[num_lept] = pt[num_lept] * sinh(evt->el_tracketa[lep->index[i]]);
				}

				sf[num_lept] = lep->pt[i] / pt[num_lept];
				is_el[num_lept] = true;
				q[num_lept] = evt->el_charge[lep->index[i]];

			}

			num_lept++;
		}
	}

	if (num_lept == 3) {
		M = pow(E[0] * sf[0] + E[1] * sf[1] + E[2] * sf[2], 2) - pow(px[0] * sf[0] + px[1] * sf[1] + px[2] * sf[2], 2) - pow(py[0] * sf[0] + py[1] * sf[1] + py[2] * sf[2], 2)
				- pow(pz[0] * sf[0] + pz[1] * sf[1] + pz[2] * sf[2], 2);
		M = sqrt(M);
	}

	return M;

}

//----------------------------------------------------------------------------
double transverse_mass(my_leptons *lep, myevt *evt) {

	float pt, px, py, pz, E;
	float sf;

	int i = -1; //Only the first leptons are taken into account

	for (int j = 0; j < lep->num_leptons && i == -1; j++) { //Only the first two leptons are taken into account
		if (lep->pt[j] > LeptPt && !lep->lept_overlap[j])
			i = j;
	}

	if (i == -1)
		return -9999.;

	if (!lep->is_electron[i]) { //muons -----------------------------------------------------------

		pt = evt->mu_staco_pt[lep->index[i]];
		px = evt->mu_staco_px[lep->index[i]];
		py = evt->mu_staco_py[lep->index[i]];
		pz = evt->mu_staco_pz[lep->index[i]];
		E = evt->mu_staco_E[lep->index[i]];

		sf = lep->pt[i] / pt;

	} else { //electrons -------------------------------------------------------------------------

		E = evt->el_cl_E[lep->index[i]];

		if ((evt->el_nSCTHits[lep->index[i]] + evt->el_nPixHits[lep->index[i]]) < 4) {
			pt = E / cosh(evt->el_cl_eta[lep->index[i]]);
			px = pt * cos(evt->el_cl_phi[lep->index[i]]);
			py = pt * sin(evt->el_cl_phi[lep->index[i]]);
			pz = pt * sinh(evt->el_cl_eta[lep->index[i]]);
		} else {
			pt = E / cosh(evt->el_tracketa[lep->index[i]]);
			px = pt * cos(evt->el_trackphi[lep->index[i]]);
			py = pt * sin(evt->el_trackphi[lep->index[i]]);
			pz = pt * sinh(evt->el_tracketa[lep->index[i]]);
		}

		sf = lep->pt[i] / pt;

	}

	TLorentzVector P_lep1(px * sf, py * sf, pz * sf, E * sf);

//miss-Et variables
	float mis_Ex = lep->delta_met_x + evt->MET_Egamma10NoTau_RefFinal_etx;
	float mis_Ey = lep->delta_met_y + evt->MET_Egamma10NoTau_RefFinal_ety;
	float my_MET_pT = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);

	TLorentzVector P_M(mis_Ex, mis_Ey, 0, my_MET_pT);

	float DeltaPhi_lep1_M = (P_lep1).DeltaPhi(P_M);
	float Mt_lep1_M = sqrt(2 * lep->pt[i] * my_MET_pT * (1 - cos(DeltaPhi_lep1_M)));

	return Mt_lep1_M;

}

// -------------------------------------------------------------------------
//Check that the leading (non-overlapping lepton) has pt>20 GeV
// -------------------------------------------------------------------------
bool SetChannelAlternate(my_leptons* lep, myevt *evt) {

	//The leptons should be already sorted in PT
	int lept_index = -1;
	int num_lept = 0;
	for (int i = 0; i < lep->num_leptons; i++) {
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			num_lept++;

			if (lept_index == -1)
				lept_index = i;
		}
	}

	if (lept_index != -1 && num_lept > 1)
		return (lep->pt[lept_index] > 20000.);
	else
		return false;

}

// -------------------------------------------------------------------------
/*bool is_ee(my_leptons* lep, myevt *evt) { // exactly 3 leptons

	bool is_ee = false;

	//int lept_index[2];
	int num_lept = 0;
	for (int i = 0; i < lep->num_leptons && num_lept < 4; i++) { //num_lept < 2
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			//lept_index[num_lept] = i;
			num_lept++;
		}
	}

	return (num_lept == 3);

}
*/
// othmane
bool is_ee(my_leptons* lep, myevt *evt) { // exactly 3 leptons

	bool is_ee = false;

	//int lept_index[2];
	int num_lept = 0;
	for (int i = 0; i < lep->num_leptons && num_lept < 4; i++) { //num_lept < 2
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			//lept_index[num_lept] = i;
			num_lept++;
		}
	}

	return (num_lept == 3);

}

// -------------------------------------------------------------------------
bool is_em(my_leptons* lep, myevt *evt) { // exactly same sign 2 leptons

	bool is_em = false;

	int lept_index[30];
	int num_lept = 0;
	for (int i = 0; i < lep->num_leptons; i++) { //&& num_lept < 2
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			lept_index[num_lept] = i;
			num_lept++;
		}
	}

	if (num_lept == 2) {
		//TEMP
		//	if ((lep->is_electron[lept_index[0]] && !lep->is_electron[lept_index[1]]) || (!lep->is_electron[lept_index[0]] && lep->is_electron[lept_index[1]]))
		if (lep->charge[lept_index[0]] == lep->charge[lept_index[1]])
			is_em = true;
	}
	return is_em;

}

// -------------------------------------------------------------------------
bool is_mm(my_leptons* lep, myevt *evt) { // exactly 2 muons

	bool is_mm = false;

	int lept_index[2];
	int num_lept = 0;
	for (int i = 0; i < lep->num_leptons && num_lept < 2; i++) {
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			lept_index[num_lept] = i;
			num_lept++;
		}
	}

	if (num_lept == 2)
		if (!lep->is_electron[lept_index[0]] && !lep->is_electron[lept_index[1]])
			is_mm = true;
	return is_mm;

}

//electrons -------------------------------------------------------------------------
bool trigger_ee(my_leptons* lep, myevt *evt, DileptonTriggerTool* _dileptonTriggerTool, double& triggerWeight) {

	//TODO: Does the trigger lepton definition account for the overlap?

	bool trigger = false;
	int num_lept = 0;
	triggerWeight = 1.;
	TLorentzVector lepvec[3];
	DileptonTriggerTool::leptontype lep3type = DileptonTriggerTool::none;

	//Only the first two leptons are taken into account?
	//TODO: Revise the requirements
	for (int i = 0; i < lep->num_leptons && num_lept < 3; i++)
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			if (!lep->is_electron[i]) { //muons -----------------------------------------------------------

				lepvec[num_lept].SetPtEtaPhiM(lep->pt[i], evt->mu_staco_eta[lep->index[i]], evt->mu_staco_phi[lep->index[i]], 0.);
			} else { //electrons -------------------------------------------------------------------------

				if ((evt->el_nSCTHits[lep->index[i]] + evt->el_nPixHits[lep->index[i]]) < 4) {

					lepvec[num_lept].SetPtEtaPhiM(lep->pt[i], evt->el_cl_eta[lep->index[i]], evt->el_cl_phi[lep->index[i]], 0.);
				} else {

					lepvec[num_lept].SetPtEtaPhiM(lep->pt[i], evt->el_tracketa[lep->index[i]], evt->el_trackphi[lep->index[i]], 0.);
				}
			}

			if (num_lept == 2) {
				if (lep->is_electron[i]) {
					lep3type = DileptonTriggerTool::electron;
				} else {
					lep3type = DileptonTriggerTool::muon;
				}
			}

			num_lept++;
		}

	//miss-Et variables
	float mis_Ex = evt->MET_LocHadTopo_etx;
	float mis_Ey = evt->MET_LocHadTopo_ety;
	float my_MET_pT = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);

	DileptonTriggerTool::selection seli = DileptonTriggerTool::ee;
	DileptonTriggerTool::stream _myStream = DileptonTriggerTool::MC;

	if (num_lept > 1)
		trigger = _dileptonTriggerTool->isTriggered(&lepvec[0], &lepvec[1], &lepvec[2], lep3type, my_MET_pT, 65000., 36000., 125000., triggerWeight, seli, _myStream, evt->runNumber,
				evt->EF_xe80T_tclcw_loose, evt->EF_xe80_tclcw_loose, evt->EF_e60_medium1, evt->EF_mu36_tight, evt->EF_2e12Tvh_loose1, evt->EF_mu18_tight_mu8_EFFS,
				evt->EF_e12Tvh_medium1_mu8, evt->trig_EF_el_EF_e60_medium1, evt->trig_EF_el_EF_2e12Tvh_loose1, evt->trig_EF_el_EF_e12Tvh_medium1_mu8, evt->trig_EF_el_n,
				evt->trig_EF_el_eta, evt->trig_EF_el_phi, evt->trig_EF_trigmuonef_EF_mu36_tight, evt->trig_EF_trigmuonef_EF_mu18_tight, evt->trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS,
				evt->trig_EF_trigmuonef_EF_mu8, evt->trig_EF_trigmuonef_n, evt->trig_EF_trigmuonef_track_CB_eta, evt->trig_EF_trigmuonef_track_CB_phi,
				evt->trig_EF_trigmuonef_track_CB_hasCB, 0, 0, 0, 0);

	return trigger || true;

}

//----------------------------------------------------------------------------
bool trigger_em(my_leptons* lep, myevt *evt, DileptonTriggerTool* _dileptonTriggerTool, double& triggerWeight) {

	bool trigger = false;
	int num_lept = 0;
	triggerWeight = 1.;
	int first_lept_ind = -1;
	TLorentzVector lepvec[3];
	DileptonTriggerTool::leptontype lep3type = DileptonTriggerTool::none;

//Only the first two leptons are taken into account
	for (int i = 0; i < lep->num_leptons && num_lept < 3; i++)
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {

			if (first_lept_ind == -1)
				first_lept_ind = i;

			if (!lep->is_electron[i]) { //muons -----------------------------------------------------------

				lepvec[num_lept].SetPtEtaPhiM(lep->pt[i], evt->mu_staco_eta[lep->index[i]], evt->mu_staco_phi[lep->index[i]], 0.);

			} else { //electrons -------------------------------------------------------------------------

				if ((evt->el_nSCTHits[lep->index[i]] + evt->el_nPixHits[lep->index[i]]) < 4) {

					lepvec[num_lept].SetPtEtaPhiM(lep->pt[i], evt->el_cl_eta[lep->index[i]], evt->el_cl_phi[lep->index[i]], 0.);
				} else {

					lepvec[num_lept].SetPtEtaPhiM(lep->pt[i], evt->el_tracketa[lep->index[i]], evt->el_trackphi[lep->index[i]], 0.);
				}

			}

			if (num_lept == 2) {
				if (lep->is_electron[i]) {
					lep3type = DileptonTriggerTool::electron;
				} else {
					lep3type = DileptonTriggerTool::muon;
				}
			}

			num_lept++;
		}

//miss-Et variables
	float mis_Ex = evt->MET_LocHadTopo_etx;
	float mis_Ey = evt->MET_LocHadTopo_ety;
	float my_MET_pT = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);

	DileptonTriggerTool::selection seli = DileptonTriggerTool::em;
	DileptonTriggerTool::stream _myStream = DileptonTriggerTool::MC;

	if (num_lept > 1) {
		if (lep->is_electron[first_lept_ind]) {
			trigger = _dileptonTriggerTool->isTriggered(&lepvec[0], &lepvec[1], &lepvec[2], lep3type, my_MET_pT, 65000., 36000., 125000., triggerWeight, seli, _myStream, evt->runNumber,
					evt->EF_xe80T_tclcw_loose, evt->EF_xe80_tclcw_loose, evt->EF_e60_medium1, evt->EF_mu36_tight, evt->EF_2e12Tvh_loose1, evt->EF_mu18_tight_mu8_EFFS,
					evt->EF_e12Tvh_medium1_mu8, evt->trig_EF_el_EF_e60_medium1, evt->trig_EF_el_EF_2e12Tvh_loose1, evt->trig_EF_el_EF_e12Tvh_medium1_mu8, evt->trig_EF_el_n,
					evt->trig_EF_el_eta, evt->trig_EF_el_phi, evt->trig_EF_trigmuonef_EF_mu36_tight, evt->trig_EF_trigmuonef_EF_mu18_tight, evt->trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS,
					evt->trig_EF_trigmuonef_EF_mu8, evt->trig_EF_trigmuonef_n, evt->trig_EF_trigmuonef_track_CB_eta, evt->trig_EF_trigmuonef_track_CB_phi,
					evt->trig_EF_trigmuonef_track_CB_hasCB, 0, 0, 0, 0);
		} else {
			trigger = _dileptonTriggerTool->isTriggered(&lepvec[1], &lepvec[0], &lepvec[2], lep3type, my_MET_pT, 65000., 36000., 125000., triggerWeight, seli, _myStream, evt->runNumber,
					evt->EF_xe80T_tclcw_loose, evt->EF_xe80_tclcw_loose, evt->EF_e60_medium1, evt->EF_mu36_tight, evt->EF_2e12Tvh_loose1, evt->EF_mu18_tight_mu8_EFFS,
					evt->EF_e12Tvh_medium1_mu8, evt->trig_EF_el_EF_e60_medium1, evt->trig_EF_el_EF_2e12Tvh_loose1, evt->trig_EF_el_EF_e12Tvh_medium1_mu8, evt->trig_EF_el_n,
					evt->trig_EF_el_eta, evt->trig_EF_el_phi, evt->trig_EF_trigmuonef_EF_mu36_tight, evt->trig_EF_trigmuonef_EF_mu18_tight, evt->trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS,
					evt->trig_EF_trigmuonef_EF_mu8, evt->trig_EF_trigmuonef_n, evt->trig_EF_trigmuonef_track_CB_eta, evt->trig_EF_trigmuonef_track_CB_phi,
					evt->trig_EF_trigmuonef_track_CB_hasCB, 0, 0, 0, 0);
		}
	} else
		std::cout << "\nWARNING: The trigger tool is called for an event with less than two leptons.\n";

	return trigger;

}

//----------------------------------------------------------------------------
bool trigger_mm(my_leptons* lep, myevt *evt, DileptonTriggerTool* _dileptonTriggerTool, double& triggerWeight) {

	bool trigger = false;

	int num_lept = 0;
	triggerWeight = 1.;
	TLorentzVector lepvec[3];
	DileptonTriggerTool::leptontype lep3type = DileptonTriggerTool::none;

	for (int i = 0; i < lep->num_leptons && num_lept < 3; i++)
		if (lep->pt[i] > LeptPt && !lep->lept_overlap[i]) {
			if (!lep->is_electron[i]) { //muons -----------------------------------------------------------

				lepvec[num_lept].SetPtEtaPhiM(lep->pt[i], evt->mu_staco_eta[lep->index[i]], evt->mu_staco_phi[lep->index[i]], 0.);

			} else { //electrons -------------------------------------------------------------------------

				//std::cout << "\nWARNING: Selecting an electron the di-muon trigger!\n";

				if ((evt->el_nSCTHits[lep->index[i]] + evt->el_nPixHits[lep->index[i]]) < 4) {

					lepvec[num_lept].SetPtEtaPhiM(lep->pt[i], evt->el_cl_eta[lep->index[i]], evt->el_cl_phi[lep->index[i]], 0.);
				} else {

					lepvec[num_lept].SetPtEtaPhiM(lep->pt[i], evt->el_tracketa[lep->index[i]], evt->el_trackphi[lep->index[i]], 0.);
				}

			}

			if (num_lept == 2) {
				if (lep->is_electron[i]) {
					lep3type = DileptonTriggerTool::electron;
				} else {
					lep3type = DileptonTriggerTool::muon;
				}
			}

			num_lept++;
		}

	//miss-Et variables
	float mis_Ex = evt->MET_LocHadTopo_etx;
	float mis_Ey = evt->MET_LocHadTopo_ety;
	float my_MET_pT = sqrt(mis_Ex * mis_Ex + mis_Ey * mis_Ey);

	DileptonTriggerTool::selection seli = DileptonTriggerTool::mm;
	DileptonTriggerTool::stream _myStream = DileptonTriggerTool::MC;

	if (num_lept > 1) { //TEMP: evt->EF_mu24i_tight
		trigger = _dileptonTriggerTool->isTriggered(&lepvec[0], &lepvec[1], &lepvec[2], lep3type, my_MET_pT, 65000., 36000., 125000., triggerWeight, seli, _myStream, evt->runNumber,
				evt->EF_mu24i_tight, evt->EF_xe80_tclcw_loose, evt->EF_e60_medium1, evt->EF_mu36_tight, evt->EF_2e12Tvh_loose1, evt->EF_mu18_tight_mu8_EFFS, evt->EF_e12Tvh_medium1_mu8,
				evt->trig_EF_el_EF_e60_medium1, evt->trig_EF_el_EF_2e12Tvh_loose1, evt->trig_EF_el_EF_e12Tvh_medium1_mu8, evt->trig_EF_el_n, evt->trig_EF_el_eta, evt->trig_EF_el_phi,
				evt->trig_EF_trigmuonef_EF_mu36_tight, evt->trig_EF_trigmuonef_EF_mu18_tight, evt->trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS, evt->trig_EF_trigmuonef_EF_mu8,
				evt->trig_EF_trigmuonef_n, evt->trig_EF_trigmuonef_track_CB_eta, evt->trig_EF_trigmuonef_track_CB_phi, evt->trig_EF_trigmuonef_track_CB_hasCB, 0, 0, 0, 0); //EF_xe80T_tclcw_loose

	}

	return trigger;

}





// in nb
float Get_CrossSection(TString* filename) {
  float Xsection = 1.;
if (filename->Index("204150")>0) Xsection = 1.2099E-03;
if (filename->Index("204151")>0) Xsection = 3.5657E-04;
if (filename->Index("204153")>0) Xsection = 2.0110E-04;
if (filename->Index("204154")>0) Xsection = 1.1657E-04;
if (filename->Index("204155")>0) Xsection = 1.1767E-04;
if (filename->Index("204156")>0) Xsection = 6.8990E-05;
if (filename->Index("204157")>0) Xsection = 6.9458E-05;
if (filename->Index("204158")>0) Xsection = 4.1822E-05;
if (filename->Index("204159")>0) Xsection = 4.2086E-05;
if (filename->Index("204160")>0) Xsection = 2.5549E-05;
if (filename->Index("204161")>0) Xsection = 2.5727E-05;
if (filename->Index("204162")>0) Xsection = 1.5929E-05;
if (filename->Index("204163")>0) Xsection = 1.5996E-05;
if (filename->Index("204164")>0) Xsection = 9.9704E-06;
if (filename->Index("204165")>0) Xsection = 1.0014E-05;
if (filename->Index("204166")>0) Xsection = 6.3245E-06;
if (filename->Index("204167")>0) Xsection = 6.3498E-06;
if (filename->Index("204168")>0) Xsection = 4.0353E-06;
if (filename->Index("204169")>0) Xsection = 4.0433E-06;
if (filename->Index("204170")>0) Xsection = 2.6057E-06;
if (filename->Index("204171")>0) Xsection = 1.0911E-06;


	return Xsection;
	}

// in pb
float Get_CrossSection_13(TString* filename) {
  float Xsection = 1.;
if (filename->Index("G550")>0) Xsection =15.5705 ;
if (filename->Index("G650")>0) Xsection =5.60048 ;
if (filename->Index("G700")>0) Xsection =3.5251 ;
if (filename->Index("G750")>0) Xsection =2.26585 ;
if (filename->Index("G750")>0) Xsection =2.26585 ;
if (filename->Index("G800")>0) Xsection =1.4891 ;
if (filename->Index("G800")>0) Xsection =1.4891 ;
if (filename->Index("G850")>0) Xsection =0.996137 ;
if (filename->Index("G850")>0) Xsection =0.996137 ;
if (filename->Index("G900")>0) Xsection =0.677478 ;
if (filename->Index("G900")>0) Xsection =0.677478 ;
if (filename->Index("G950")>0) Xsection =0.466352 ;
if (filename->Index("G950")>0) Xsection =0.466352 ;
if (filename->Index("G1000")>0) Xsection =0.325388 ;
if (filename->Index("G1000")>0) Xsection =0.325388 ;
if (filename->Index("G1050")>0) Xsection =0.229367 ;
if (filename->Index("G1050")>0) Xsection =0.229367 ;
if (filename->Index("G1100")>0) Xsection =0.163491 ;
if (filename->Index("G1100")>0) Xsection =0.163491 ;
if (filename->Index("G1150")>0) Xsection =0.117687 ;
if (filename->Index("G1250")>0) Xsection =0.0627027 ;

	return Xsection;
	}

