xsection_graph(){

double  m_gl[21]={550 ,
650 ,
700 ,
750 ,
750 ,
800 ,
800 ,
850 ,
850 ,
900 ,
900 ,
950 ,
950 ,
1000 ,
1000 ,
1050 ,
1050 ,
1100 ,
1100 ,
1150 ,
1250};

  TGraph *gr = new TGraph("xsection_gluino.log");
  gr->Draw("AC*");


  for (int i=0; i<21;i++){
    //    TString exp =  "if (filename->Index(\"G" +m_gl[i]+"\")>0) Xsection ="+gr->Eval(m_gl[i])+" ;";
    cout << "if (filename->Index(\"G"<<m_gl[i]<< "\")>0) Xsection =" << gr->Eval(m_gl[i]) << " ;" << endl;
  }
}
