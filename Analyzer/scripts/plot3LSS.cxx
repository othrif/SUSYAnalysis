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
#include "TPad.h"
#include "TObjArray.h"
#include "TMinuit.h"
#include "RooStats/NumberCountingUtils.h"
#include "TPaveText.h"

double GetMyMaximum(TH1D* h, int x_low, int x_high, bool is_log); 
void plot3LSS(){ 

  TString path = "/afs/cern.ch/work/o/othrif/workarea/results/v47/run3LSS";
  TString files[] = {"ttV"};
  TH1D * hist;
  TString tempname;

  TFile *f = new TFile(path+"/"+files[0]+".root");

  int j = 0;
  int i = 0;
  tempname = Form("Canvas%d",j);
  TCanvas *myPlots = new TCanvas(tempname, "myPlots",200,235,1000,600);
  gStyle->SetOptStat(0);
  //myPlots->Range(-1.195973,9.295054,10.8604,165.4531);
  myPlots->SetFillColor(0);
  myPlots->SetBorderMode(0);
  myPlots->SetBorderSize(2);
  myPlots->SetRightMargin(0.1543086);
  myPlots->SetBottomMargin(0.1336806);
  myPlots->SetFrameBorderMode(0);
  myPlots->SetFrameBorderMode(0);

  THStack *hs = new THStack("hs",tempname);
  TLegend *leg = new TLegend(0.6953908,0.7291667,0.8456914,0.8802083,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);

  TPaveText *pt = new TPaveText(0.16,0.86,0.5,.96,"brNDC");



  tempname = "composition_3lss";
  std::cout << tempname << std::endl;
  hist = (TH1D*) gDirectory->Get(tempname);

  double background_maximum = GetMyMaximum(hist, 0, 10, 0);
  hist->GetXaxis()->SetLabelFont(42);
  hist->GetXaxis()->SetLabelSize(0.05);
  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetTitleOffset(2);
  hist->GetXaxis()->SetTitleFont(42);
  hist->GetYaxis()->SetLabelFont(42);
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetTitleOffset(1);
  hist->GetYaxis()->SetTitleFont(42);
  hist->GetYaxis()->SetTitle("Truth Composition (%)");
  hist->SetDirectory(0); 
  hist->SetFillColor(i+2);
  hist->SetMarkerStyle(21);
  hist->SetMarkerColor(i+2);
  hist->Scale(100./hist->GetBinContent(1));
  hist->SetMaximum(140); //1.000 * background_maximum);


  TString legendHeader = "";
  hist->SetTitle("Truth Composition for ttV " + legendHeader);
  //	  leg->AddEntry(hist, ranges_pt[i], "f");
  hist->Draw("same");

  leg->Draw("same");
  myPlots->Update();
  TLine *line = new TLine(myPlots->GetUxmin(),100,myPlots->GetUxmax(),100);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->SetLineColor(kBlack);
  line->Draw("same");

}

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

