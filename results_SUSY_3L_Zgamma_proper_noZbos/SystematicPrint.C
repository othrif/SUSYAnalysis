
void myPrint(TH1D* h){

  std::cout<<"\n"<<h->GetName();

  std::cout<<" & "<<(h->GetBinContent(1)-1.)*100.;
  std::cout<<" & "<<(h->GetBinContent(3)-1.)*100.;
  std::cout<<" & "<<(h->GetBinContent(2)-1.)*100.;
  std::cout<<" & "<<(h->GetBinContent(5)-1.)*100.;
  std::cout<<" & "<<(h->GetBinContent(4)-1.)*100.;
  std::cout<<" & "<<(h->GetBinContent(6)-1.)*100.;

  std::cout<<"\\\\\n";

  return;
}

void myAvgPrint(TH1D* h, TH1D* central){

  std::cout<<"\n"<<h->GetName();
  std::cout<<" & "<<(h->Integral()/central->Integral()-1.)*100.;
  std::cout<<"\\\\\n";

  return;
}



void SystematicPrint(){


 TH1D*     expected_backgrounds;
 TH1D*     expected_backgrounds_pJES;
 TH1D*     expected_backgrounds_mJES;
 TH1D*     expected_backgrounds_pLUMI;
 TH1D*     expected_backgrounds_mLUMI;
 TH1D*     expected_backgrounds_pTTbar;
 TH1D*     expected_backgrounds_mTTbar;
 TH1D*     expected_backgrounds_pTTbarV;
 TH1D*     expected_backgrounds_mTTbarV;
 TH1D*     expected_backgrounds_pWZ;
 TH1D*     expected_backgrounds_mWZ;
 TH1D*     expected_backgrounds_pZ;
 TH1D*     expected_backgrounds_mZ;
 TH1D*     expected_backgrounds_pZbb;
 TH1D*     expected_backgrounds_mZbb;
 TH1D*     expected_backgrounds_pJER;
 TH1D*     expected_backgrounds_pBA;
 TH1D*     expected_backgrounds_mBA;
 TH1D*     expected_backgrounds_pMUS;
 TH1D*     expected_backgrounds_mMUS;
 TH1D*     expected_backgrounds_pMUR;
 TH1D*     expected_backgrounds_mMUR;
 TH1D*     expected_backgrounds_pEF;
 TH1D*     expected_backgrounds_mEF;
 TH1D*     expected_backgrounds_pELS;
 TH1D*     expected_backgrounds_mELS;
 TH1D*     expected_backgrounds_pELR;
 TH1D*     expected_backgrounds_mELR;
 TH1D*     expected_backgrounds_mPLUP;
 TH1D*     expected_backgrounds_pFrE;
 TH1D*     expected_backgrounds_mFrE;
 TH1D*     expected_backgrounds_pFrMu;
 TH1D*     expected_backgrounds_mFrMu;

 TH1D*     expected_backgrounds_pStSc;
 TH1D*     expected_backgrounds_mStSc;
 TH1D*     expected_backgrounds_pStRs;
 TH1D*     expected_backgrounds_mStRs;


 {
    TFile f = TFile("output_histos.root", "READ");
    expected_backgrounds = (TH1D*) f.Get("expected_backgrounds");
    expected_backgrounds->SetDirectory(gROOT);

    expected_backgrounds_pJES = (TH1D*) f.Get("expected_backgrounds_pJES");
    expected_backgrounds_pJES->SetDirectory(gROOT);

    expected_backgrounds_mJES = (TH1D*) f.Get("expected_backgrounds_mJES");
    expected_backgrounds_mJES->SetDirectory(gROOT);

    expected_backgrounds_pLUMI = (TH1D*) f.Get("expected_backgrounds_pLUMI");
    expected_backgrounds_pLUMI->SetDirectory(gROOT);

    expected_backgrounds_mLUMI = (TH1D*) f.Get("expected_backgrounds_mLUMI");
    expected_backgrounds_mLUMI->SetDirectory(gROOT);

    expected_backgrounds_pTTbar = (TH1D*) f.Get("expected_backgrounds_pTTbar");
    expected_backgrounds_pTTbar->SetDirectory(gROOT);

    expected_backgrounds_mTTbar = (TH1D*) f.Get("expected_backgrounds_mTTbar");
    expected_backgrounds_mTTbar->SetDirectory(gROOT);

    expected_backgrounds_pTTbarV = (TH1D*) f.Get("expected_backgrounds_pTTbarV");
    expected_backgrounds_pTTbarV->SetDirectory(gROOT);

    expected_backgrounds_mTTbarV = (TH1D*) f.Get("expected_backgrounds_mTTbarV");
    expected_backgrounds_mTTbarV->SetDirectory(gROOT);

    expected_backgrounds_pWZ = (TH1D*) f.Get("expected_backgrounds_pWZ");
    expected_backgrounds_pWZ->SetDirectory(gROOT);

    expected_backgrounds_mWZ = (TH1D*) f.Get("expected_backgrounds_mWZ");
    expected_backgrounds_mWZ->SetDirectory(gROOT);

    expected_backgrounds_pZ = (TH1D*) f.Get("expected_backgrounds_pZ");
    expected_backgrounds_pZ->SetDirectory(gROOT);

    expected_backgrounds_mZ = (TH1D*) f.Get("expected_backgrounds_mZ");
    expected_backgrounds_mZ->SetDirectory(gROOT);

    expected_backgrounds_pZbb = (TH1D*) f.Get("expected_backgrounds_pZbb");
    expected_backgrounds_pZbb->SetDirectory(gROOT);

    expected_backgrounds_mZbb = (TH1D*) f.Get("expected_backgrounds_mZbb");
    expected_backgrounds_mZbb->SetDirectory(gROOT);

    expected_backgrounds_pJER = (TH1D*) f.Get("expected_backgrounds_pJER");
    expected_backgrounds_pJER->SetDirectory(gROOT);

    expected_backgrounds_pBA = (TH1D*) f.Get("expected_backgrounds_pBA");
    expected_backgrounds_pBA->SetDirectory(gROOT);

    expected_backgrounds_mBA = (TH1D*) f.Get("expected_backgrounds_mBA");
    expected_backgrounds_mBA->SetDirectory(gROOT);

    expected_backgrounds_pMUS = (TH1D*) f.Get("expected_backgrounds_pMUS");
    expected_backgrounds_pMUS->SetDirectory(gROOT);

    expected_backgrounds_mMUS = (TH1D*) f.Get("expected_backgrounds_mMUS");
    expected_backgrounds_mMUS->SetDirectory(gROOT);

    expected_backgrounds_pMUR = (TH1D*) f.Get("expected_backgrounds_pMUR");
    expected_backgrounds_pMUR->SetDirectory(gROOT);

    expected_backgrounds_mMUR = (TH1D*) f.Get("expected_backgrounds_mMUR");
    expected_backgrounds_mMUR->SetDirectory(gROOT);

    expected_backgrounds_pEF = (TH1D*) f.Get("expected_backgrounds_pEF");
    expected_backgrounds_pEF->SetDirectory(gROOT);

    expected_backgrounds_mEF = (TH1D*) f.Get("expected_backgrounds_mEF");
    expected_backgrounds_mEF->SetDirectory(gROOT);

    expected_backgrounds_pELS = (TH1D*) f.Get("expected_backgrounds_pELS");
    expected_backgrounds_pELS->SetDirectory(gROOT);

    expected_backgrounds_mELS = (TH1D*) f.Get("expected_backgrounds_mELS");
    expected_backgrounds_mELS->SetDirectory(gROOT);

    expected_backgrounds_pELR = (TH1D*) f.Get("expected_backgrounds_pELR");
    expected_backgrounds_pELR->SetDirectory(gROOT);

    expected_backgrounds_mELR = (TH1D*) f.Get("expected_backgrounds_mELR");
    expected_backgrounds_mELR->SetDirectory(gROOT);

    expected_backgrounds_mPLUP = (TH1D*) f.Get("expected_backgrounds_mPLUP");
    expected_backgrounds_mPLUP->SetDirectory(gROOT);

    expected_backgrounds_pFrE = (TH1D*) f.Get("expected_backgrounds_pFrE");
    expected_backgrounds_pFrE->SetDirectory(gROOT);

    expected_backgrounds_mFrE = (TH1D*) f.Get("expected_backgrounds_mFrE");
    expected_backgrounds_mFrE->SetDirectory(gROOT);

    expected_backgrounds_pFrMu = (TH1D*) f.Get("expected_backgrounds_pFrMu");
    expected_backgrounds_pFrMu->SetDirectory(gROOT);

    expected_backgrounds_mFrMu = (TH1D*) f.Get("expected_backgrounds_mFrMu");
    expected_backgrounds_mFrMu->SetDirectory(gROOT);


    expected_backgrounds_pStSc = (TH1D*) f.Get("expected_backgrounds_pStSc");
    expected_backgrounds_pStSc->SetDirectory(gROOT);

    expected_backgrounds_mStSc = (TH1D*) f.Get("expected_backgrounds_mStSc");
    expected_backgrounds_mStSc->SetDirectory(gROOT);

    expected_backgrounds_pStRs = (TH1D*) f.Get("expected_backgrounds_pStRs");
    expected_backgrounds_pStRs->SetDirectory(gROOT);

    expected_backgrounds_mStRs = (TH1D*) f.Get("expected_backgrounds_mStRs");
    expected_backgrounds_mStRs->SetDirectory(gROOT);

    f.Close();
 }

  //Normalization -----------------------------------------------------


  //print-out --------------------------------
  myAvgPrint(expected_backgrounds_pJES, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mJES, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pLUMI, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mLUMI, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pTTbar, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mTTbar, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pTTbarV, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mTTbarV, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pWZ, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mWZ, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pZ, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mZ, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pZbb, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mZbb, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pJER, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pBA, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mBA, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pMUS, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mMUS, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pMUR, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mMUR, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pEF, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mEF, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pELS, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mELS, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pELR, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mELR, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mPLUP, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pFrE, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mFrE, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pFrMu, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mFrMu, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pStSc, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mStSc, expected_backgrounds);
  myAvgPrint(expected_backgrounds_pStRs, expected_backgrounds);
  myAvgPrint(expected_backgrounds_mStRs, expected_backgrounds);



  expected_backgrounds_pJES->Divide(expected_backgrounds);
  expected_backgrounds_mJES->Divide(expected_backgrounds);
  expected_backgrounds_pLUMI->Divide(expected_backgrounds);
  expected_backgrounds_mLUMI->Divide(expected_backgrounds);
  expected_backgrounds_pTTbar->Divide(expected_backgrounds);
  expected_backgrounds_mTTbar->Divide(expected_backgrounds);
  expected_backgrounds_pTTbarV->Divide(expected_backgrounds);
  expected_backgrounds_mTTbarV->Divide(expected_backgrounds);
  expected_backgrounds_pWZ->Divide(expected_backgrounds);
  expected_backgrounds_mWZ->Divide(expected_backgrounds);
  expected_backgrounds_pZ->Divide(expected_backgrounds);
  expected_backgrounds_mZ->Divide(expected_backgrounds);
  expected_backgrounds_pZbb->Divide(expected_backgrounds);
  expected_backgrounds_mZbb->Divide(expected_backgrounds);
  expected_backgrounds_pJER->Divide(expected_backgrounds);
  expected_backgrounds_pBA->Divide(expected_backgrounds);
  expected_backgrounds_mBA->Divide(expected_backgrounds);
  expected_backgrounds_pMUS->Divide(expected_backgrounds);
  expected_backgrounds_mMUS->Divide(expected_backgrounds);
  expected_backgrounds_pMUR->Divide(expected_backgrounds);
  expected_backgrounds_mMUR->Divide(expected_backgrounds);
  expected_backgrounds_pEF->Divide(expected_backgrounds);
  expected_backgrounds_mEF->Divide(expected_backgrounds);
  expected_backgrounds_pELS->Divide(expected_backgrounds);
  expected_backgrounds_mELS->Divide(expected_backgrounds);
  expected_backgrounds_pELR->Divide(expected_backgrounds);
  expected_backgrounds_mELR->Divide(expected_backgrounds);
  expected_backgrounds_mPLUP->Divide(expected_backgrounds);
  expected_backgrounds_pFrE->Divide(expected_backgrounds);
  expected_backgrounds_mFrE->Divide(expected_backgrounds);
  expected_backgrounds_pFrMu->Divide(expected_backgrounds);
  expected_backgrounds_mFrMu->Divide(expected_backgrounds);

  expected_backgrounds_pStSc->Divide(expected_backgrounds);
  expected_backgrounds_mStSc->Divide(expected_backgrounds);
  expected_backgrounds_pStRs->Divide(expected_backgrounds);
  expected_backgrounds_mStRs->Divide(expected_backgrounds);

  //print-out --------------------------------
  myPrint(expected_backgrounds_pJES);
  myPrint(expected_backgrounds_mJES);
  myPrint(expected_backgrounds_pLUMI);
  myPrint(expected_backgrounds_mLUMI);
  myPrint(expected_backgrounds_pTTbar);
  myPrint(expected_backgrounds_mTTbar);
  myPrint(expected_backgrounds_pTTbarV);
  myPrint(expected_backgrounds_mTTbarV);
  myPrint(expected_backgrounds_pWZ);
  myPrint(expected_backgrounds_mWZ);
  myPrint(expected_backgrounds_pZ);
  myPrint(expected_backgrounds_mZ);
  myPrint(expected_backgrounds_pZbb);
  myPrint(expected_backgrounds_mZbb);
  myPrint(expected_backgrounds_pJER);
  myPrint(expected_backgrounds_pBA);
  myPrint(expected_backgrounds_mBA);
  myPrint(expected_backgrounds_pMUS);
  myPrint(expected_backgrounds_mMUS);
  myPrint(expected_backgrounds_pMUR);
  myPrint(expected_backgrounds_mMUR);
  myPrint(expected_backgrounds_pEF);
  myPrint(expected_backgrounds_mEF);
  myPrint(expected_backgrounds_pELS);
  myPrint(expected_backgrounds_mELS);
  myPrint(expected_backgrounds_pELR);
  myPrint(expected_backgrounds_mELR);
  myPrint(expected_backgrounds_mPLUP);
  myPrint(expected_backgrounds_pFrE);
  myPrint(expected_backgrounds_mFrE);
  myPrint(expected_backgrounds_pFrMu);
  myPrint(expected_backgrounds_mFrMu);
  myPrint(expected_backgrounds_pStSc);
  myPrint(expected_backgrounds_mStSc);
  myPrint(expected_backgrounds_pStRs);
  myPrint(expected_backgrounds_mStRs);

 return;
}

