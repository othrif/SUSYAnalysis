void plotth2(){

  TH2D* h2d = new TH2D("h2d", "btag_weight vs. #mu;averageIntPerXing;btag_weight MV2c20;entries", 40, 0, 40, 30, -1.5, 1.5);

  TFile *f1 = new TFile("/afs/cern.ch/user/o/othrif/workarea/results/v47/RunNov30_noJetSF/ttW.root");
  TH1F  *h1 = (TH1F*)f1->Get("averageIntPerXing_PRW");
  TH1F  *h2 = (TH1F*)f1->Get("btag_weight_PRW");

  int nbins1 = h1->GetNbinsX();
  int nbins2 = h2->GetNbinsX();
  double x1,x2;
  for (int i = 1; i <= nbins1; i++)
	for (int j = 1; j <= nbins2; j++)
	  {
		x1 = h1->GetBinContent(i);
		cout << "bin=" << i << ", content=" << x1 <<endl;
		x2 = h2->GetBinContent(j);
		h2d->SetBinContent(i, j, x1+x2);
	  }
  TCanvas *c1 = new TCanvas( "c1" , "c1" );
  h1->Draw("HIST");
  TCanvas *c2 = new TCanvas( "c2" , "c2" );
  h2->Draw("HIST");
  TCanvas *c3 = new TCanvas( "c3" , "c3" );
  h2d->Draw("COL");
}
