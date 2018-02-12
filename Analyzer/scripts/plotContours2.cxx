const int num_files = 1;
int lumi = 36500;
int TH2toTGraph2D(TH2F* histo, TGraph2D* g){
  
  int firstxbin = 1;
  int lastxbin = histo->GetXaxis()->GetNbins();
  int firstybin = 1;
  int lastybin = histo->GetYaxis()->GetNbins();
  int npoints = 0;
  for (Int_t j = firstybin; j <= lastybin; j++) {
    for (Int_t i = firstxbin; i <= lastxbin; i++) {
      if(histo->GetBinContent(i,j)>0 ){
		g->SetPoint(npoints,
					histo->GetXaxis()->GetBinCenter(i),
					histo->GetYaxis()->GetBinCenter(j),
					histo->GetBinContent(i,j));      
		npoints++;
      }
    }
  }
  
  return npoints;
  
}

void getTGraphs(TH2F* hFinalSig, TGraph *& gr168, TGraph *& gr3s){
  //TGraph* getTGraphs(TH2F* hFinalSig){
  TGraph2D* g = new TGraph2D();
  int ret = TH2toTGraph2D(hFinalSig,g);
  if(ret==0){
	cout << "no points left, exiting" << endl;
	//	  return gr168;
  }
	
  Double_t contours[2];
  contours[0] = 1.64;
  contours[1] = 3;

  TH2F* Ghisto=(TH2F*)g->GetHistogram();
  Ghisto->SetContour(2, contours);
  Ghisto->SetLineWidth(4);
  Ghisto->Draw("CONT LIST same");
  gPad->Update();
  TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
  TList* contLevel = NULL;
  TGraph* curv     = NULL;
  TGraph* gc       = NULL;

  Int_t nGraphs    = 0;
  Int_t TotalConts = 0;
	
  if (conts == NULL){
	printf("*** No Contours Were Extracted!\n");
	TotalConts = 0;
	//	  return NULL;
  } else {
	TotalConts = conts->GetSize();
  }
  printf("TotalConts = %d\n", TotalConts);

  for(i = 0; i < TotalConts; i++){
	contLevel = (TList*)conts->At(i);
	printf("Contour %d has %d Graphs\n", i, contLevel->GetSize());
	nGraphs += contLevel->GetSize();
  }
	
  for(int i = 0; i < TotalConts; i++){
	contLevel = (TList*)conts->At(i);
	curv = (TGraph*)contLevel->First();
	for(int j = 0; j < contLevel->GetSize(); j++){
	  gc = (TGraph*)curv->Clone();
	  gc->SetLineColor(kRed);
	  gc->Draw("C same");
	  //		cout << "File=" << ifile << ", TGraph=" << ntgr << endl;
	  if(i==0)		gr168=(TGraph*)curv->Clone();		
	  if(i==1)		gr3s=(TGraph*)curv->Clone(); 
	  curv = (TGraph*)contLevel->After(curv); // Get Next graph
	}
  }
  return;
}

void drawTGraphs(TH2F* hFinalSig, TGraph * gr[], int ntgr, TString filenames[], TString sigmaCont, int colors[]){

  gStyle->SetOptStat(0);
  gStyle->SetTitleW(0.99);
  gStyle->SetTitleH(0.08);
  gStyle->SetPaintTextFormat("3.2f");
  gStyle->SetStatX(50);

  TLegend* leg;
  leg = new TLegend(0.676218,0.678571,0.896848,0.888655);
  std::string legendHeader = (std::string)sigmaCont +" Contours";
  leg->SetHeader(legendHeader.data());
  leg->SetTextAlign(12);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);

  hFinalSig->Reset();
  hFinalSig->Draw();
  cout << "number of TGraphs: " << ntgr << endl;

  for(int i=0; i<ntgr; i++){
	//	gr3s[i]->SetLineColor(i+1);
	//	gr3s[i]->SetLineStyle(2);
	//	gr3s[i]->Draw("same");
	gr[i]->SetLineStyle(1);
	gr[i]->SetLineColor(colors[i]);
	gr[i]->Draw("same");
	std::cout << filenames[i] << std::endl;
	leg->AddEntry(gr[i], filenames[i] + "", "l");
	//	leg->AddEntry(gr3s[i], filenames[i] + "3 #sigma", "l");
  }

  leg->Draw("same");
  TLatex *l1 = new TLatex();
  l1->SetNDC();
  l1->SetTextFont(73);
  l1->SetTextSize(28);
  l1->SetTextColor(kBlack);
  l1->DrawLatex(0.138277, 0.842437 , "ATLAS ");
	
  TLatex *l2 = new TLatex();
  l2->SetNDC();
  l2->SetTextFont(43);
  l2->SetTextSize(28);
  l2->SetTextColor(kBlack);
  l2->DrawLatex(0.270774, 0.842437, "Internal");

  TLatex *l3 = new TLatex();
  l3->SetNDC();
  l3->SetTextFont(43);
  l3->SetTextSize(14);
  l3->SetTextColor(kBlack);
  char lumilabel[512];
  sprintf(lumilabel, "#sqrt{s}=13 TeV, #intLdt=%.2f fb^{-1}", lumi/1000.);
  l3->DrawLatex(0.157593, 0.787815 , lumilabel);


  // Draw m_gl - m_N1 = 2 (m_W+m_b)
  TLine *line = new TLine(600, 429.6 ,1800, 1629.6);
  line->SetLineColor(16);
  line->SetLineStyle(7);
  line->Draw("same");
  TLatex *th1 = new TLatex(1350,1238.39,"m_{#tilde{g}} - m_{#tilde{#chi}_{1}^{0}} = 2 #left(m_{W}+m_{b}#right)");
  th1->SetTextAngle(30) ;
  th1->SetTextColor(16);
  th1->SetTextSize(0.03);
  th1->Draw("same");
  
  // Draw m_gl - m_N1 = 2 m_t;
  TLine *line2 = new TLine(600, 255 ,2050, 1680);
  line2->SetLineColor(16);
  line2->SetLineStyle(7);
  line2->Draw("same");
  TLatex *th2 = new TLatex(1550,1240,"m_{#tilde{g}} - m_{#tilde{#chi}_{1}^{0}} = 2 m_{t}");
  th2->SetTextAngle(30) ;
  th2->SetTextColor(16);
  th2->SetTextSize(0.03);
	//    th2->Draw("same");

  if(gr[0]->Eval(1200)<500){
  TLine *line3 = new TLine(600, 25 ,2100, 25);
  line3->SetLineColor(16);
  line3->SetLineStyle(7);
  line3->Draw("same");
  TLatex *th3 = new TLatex(1600,40,"#Delta m = m_{#tilde{#chi}_{1}^{0}} - #left(m_{#tilde{g}} -2 m_{t} #right)");
  //        th3->SetTextAngle(32) ;
  th3->SetTextColor(16);
  th3->SetTextSize(0.03);
  th3->Draw("same");
  }
	}


void plotContours2(TString filename = "newOpt2",TString outname = "test1"){
  
  TH2F* hFinalSig = new TH2F("Significance","",50,600,2100,175,0,1700);
  hFinalSig->SetFillColor(1);
  hFinalSig->SetLineWidth(1);
  hFinalSig->SetLineColor(1);
  hFinalSig->SetLineStyle(1);
  hFinalSig->SetFillStyle(1001);
  hFinalSig->SetMarkerStyle(20);
  hFinalSig->SetMarkerSize(1.6);
  hFinalSig->GetXaxis()->SetTitleOffset(1.3);
  hFinalSig->GetYaxis()->SetTitleOffset(1.3);
  hFinalSig->GetXaxis()->SetTitle("m(#tilde{g}) [GeV]");
  hFinalSig->GetYaxis()->SetTitle("m(#tilde{#chi}^{0}_{1}) [GeV]");

  TH2F* hFinalSig_Dm = new TH2F("Significance_Dm","",40,600,2100,35,0,200);
  hFinalSig_Dm->SetFillColor(1);
  hFinalSig_Dm->SetLineWidth(1);
  hFinalSig_Dm->SetLineColor(1);
  hFinalSig_Dm->SetLineStyle(1);
  hFinalSig_Dm->SetFillStyle(1001);
  hFinalSig_Dm->SetMarkerStyle(20);
  hFinalSig_Dm->SetMarkerSize(1.6);
  hFinalSig_Dm->GetXaxis()->SetTitleOffset(1.3);
  hFinalSig_Dm->GetYaxis()->SetTitleOffset(1.3);
  hFinalSig_Dm->GetXaxis()->SetTitle("m(#tilde{g}) [GeV]");
  hFinalSig_Dm->GetYaxis()->SetTitle("#Delta m [GeV]");
  
  TString directory = "/afs/cern.ch/user/o/othrif/workarea/results/v48/Logs/"+filename+"/GG_ttn1/";

  TString filenames[num_files];// = {"GG_ttn1_SRbest", "GG_ttn1_SR3bXimo", "GG_ttn1_SR3bYang","GG_ttn1_SRlow", "GG_ttn1_SRmed", "GG_ttn1_SRhigh"};
  filenames[0] = "SRbestALL";
  filenames[1] = "SRbest";
  //  filenames[2] = "SRhigh";
  int offset = 2;
  for(int i=offset; i<num_files; i++){
	filenames[i] = Form("SR%d",i-offset);std::cout << filenames[i]<<std::endl;
	filenames[i] += "-"+outname;
  }
  std::cout << std::endl;
  TGraph* gr[20];
  TGraph* gr3s[20];
  TGraph* gr_Dm[20];
  TGraph* gr3s_Dm[20];
  int ntgr=0;

  for(int ifile=0; ifile<num_files; ifile++){
	std::cout << "filename = " << ifile << " => " << filenames[ifile] << std::endl;
	hFinalSig->Reset();
	hFinalSig_Dm->Reset();
	TString list = directory+"GG_ttn1_"+filenames[ifile]+".log";
	ifstream fList;
	fList.open(list);
	if (!fList){
	  cout << "!!! Can't open file " << list 
		   << endl;
	}
	char lineFromFile[400];
	float _bkg;
	while(fList.getline(lineFromFile, 450))
	  {
		//		cout << "Loading... '" << lineFromFile<< "..." << endl;

		//Find x,y:
		TString _temp(lineFromFile);
		float x;
		float y;
		float sig;

		TObjArray* my = (TObjArray*)_temp.Tokenize(" ");
		x = ((TObjString *)my->At(0))->GetString().Atoi();
		y = ((TObjString *)my->At(1))->GetString().Atoi();
		sig = ((TObjString *)my->At(2))->GetString().Atof();

		//	  cout << "x=" << x<< ", y=" << y << ", sig=" << sig << endl;
		hFinalSig->Fill(x,y,sig);
		if ((y-(x-2*172.5-25))>0){
		  hFinalSig_Dm->Fill(x,y-(x-2*172.5-25),sig);
		  std::cout << "x=" << x << ", y=" << y-(x-2*172.5-25) << ", sig=" << sig << std::endl;
		}
	  }
	
	// Protections and fixes:
	hFinalSig->Fill(600,400,3);
	hFinalSig->Fill(600,1,3);
	
	//	hFinalSig-> Draw("colz, text30");
	
	getTGraphs(hFinalSig, gr[ifile], gr3s[ifile]);
	getTGraphs(hFinalSig_Dm, gr_Dm[ifile], gr3s_Dm[ifile]);
	std::cout << std::endl;
	ntgr++;
  }

  int colors[] = {kRed, TColor::GetColor("#3399ff"), kOrange-2, TColor::GetColor("#339900"), TColor::GetColor("#cc99ff"), TColor::GetColor("#993300"), kViolet-10, kGray, TColor::GetColor("#99ccff"), 38, 14,  kRed-10, kRed-3};
  //  TString newnames[] = {"Best limit", "Rpc2L2bS", "Rpc2Lsoft2b", "Rpc2Lsoft1b","Rpc2L1bS","Rpc2L1bH"};//,"SRlow bound","SRhigh bound","SRlow no-bound","SRhigh no-bound"};
  TString newnames[] = {"Best limit", "Best limit with 2b","SR3b1", "SR2b1"};
  //  TString newnames[num_files];
  //  newnames[0] = "SRbest";
  //  newnames[1] = "SRlow";
  //  newnames[2] = "SRhigh";
  //  for(int i=offset; i<num_files; i++)
  //	newnames[i] = Form("SR%d",i-offset+1);

  TCanvas *c2 = new TCanvas("c2", "c2",2810,202,700,500);
  drawTGraphs(hFinalSig, gr, ntgr, newnames, "Gtt 1.64 #sigma", colors);
  c2->SaveAs("/afs/cern.ch/user/o/othrif/workarea/results/v48/Plots/"+filename+"/Lumi35/Compare164-"+outname+".pdf");
  //  TCanvas *c3 = new TCanvas("c3", "c3",2810,202,700,500);
  //  drawTGraphs(hFinalSig, gr3s, ntgr, newnames, "GG_ttn1 3 #sigma");
  //* TCanvas *c4 = new TCanvas("c4", "c4",2810,202,700,500);
  //*  drawTGraphs(hFinalSig_Dm, gr_Dm, ntgr, newnames, "GG_ttn1 1.64 #sigma", colors);
  //*  c4->SaveAs("/afs/cern.ch/user/o/othrif/workarea/results/v48/Plots/"+filename+"/Lumi35/Compare164_Dm-"+outname+".pdf");
  //  TCanvas *c5 = new TCanvas("c5", "c5",2810,202,700,500);
  //  drawTGraphs(hFinalSig_Dm, gr3s_Dm, ntgr, newnames, "GG_ttn1 3 #sigma");
  
  
}
