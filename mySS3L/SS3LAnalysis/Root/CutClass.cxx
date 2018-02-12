#define CutClass_cxx
#include "SS3LAnalysis/CutClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include <math.h>
//#include "ktclusdble.h"
#include "TLorentzVector.h"
#include <vector>
#include <algorithm>


const Double_t GeV= 1E+03;
const Double_t Pi = TMath::Pi();


void CutClass::Sort(vector<Particle> vPart){
  return;// sort (vPart.begin(), vPart.end(), SortPt); 
}

bool CutClass::ElectronCrackVeto(vector<Particle> vEle){

 // isEM &  0x3ff   =0, ET>10GeV and 1.37<|eta|<1.52

 bool el_veto=false;
 for (int iele=0; iele < (int)vEle.size(); iele++){
   if ( fabs(vEle[iele].FourVector.Pt()>10.*GeV) && 
	1.37 < fabs(vEle[iele].FourVector.Eta()) && fabs(vEle[iele].FourVector.Eta()) < 1.52){
     el_veto=true;
//      printf("--- event vetoed ---\n");
//      DumpParticle(vEle[iele]);
     break;
     
   }
 }
  
 return el_veto;
}

bool CutClass::OneLepton(vector<Particle> vLep){

  int Nlep=0;
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt()>20.*GeV){
      Nlep++;
      //      printf("  pT:%f  ID:%d   eta: %f   phi: %f\n",vLep[ilep].FourVector.Pt()/GeV,vLep[ilep].ID,vLep[ilep].FourVector.Eta(),vLep[ilep].FourVector.Phi());
    }
  }
  //  printf("Nlep(pT>20)=%d\n",Nlep);

  //  if(Nlep!=0)printf("------> NLeptons: %d \n",Nlep);
  if((Nlep)!=1) return true;  // go to next event

  // Count remaining leptons with pT>10
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt() >= 10.*GeV && vLep[ilep].FourVector.Pt() < 20.*GeV )
      return true;   // go to next event
  }

  return false;  // check next cuts
}

void CutClass::OneLepton(vector<Particle> vEle, vector<Particle> vMu, bool Cut[3][3]){
  
  float PtCutEle[3]={20,17,15};
  float PtCutMu[3]={20,17,15};

  for(int ele=0; ele<3; ele++){
    for(int mu=0; mu<3; mu++){

      Cut[ele][mu]=false; // Set it to false at the beginning
      
      int Nlep=0;
      for (int iele=0; iele < (int)vEle.size(); iele++){
	if(vEle[iele].FourVector.Pt()>PtCutEle[ele]*GeV){
	  Nlep++;
	}    
      }
      for (int imu=0; imu < (int)vMu.size(); imu++){
	if(vMu[imu].FourVector.Pt()>PtCutEle[mu]*GeV){
	  Nlep++;
	}    
      }

      if((Nlep)!=1) Cut[ele][mu]=true;  // go to next event
      
      // Count remaining leptons with pT>10
      for (int iele=0; iele < (int)vEle.size(); iele++){
	if(vEle[iele].FourVector.Pt() >= 10.*GeV && vEle[iele].FourVector.Pt() < PtCutEle[ele]*GeV ) 
	  Cut[ele][mu]=true;   // go to next event
      }
      for (int imu=0; imu < (int)vMu.size(); imu++){
	if(vMu[imu].FourVector.Pt() >= 10.*GeV && vMu[imu].FourVector.Pt() < PtCutMu[mu]*GeV ) 
	  Cut[ele][mu]=true;   // go to next event
      }


    }
  } 
  return;  // check next cuts
}

bool CutClass::TwoLeptonsOS(vector<Particle> vLep){
  
  int Nlep=0;
  int charge=1;
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt()>10.*GeV){
      Nlep++;
      charge=charge*vLep[ilep].ID;
      //  printf("  ----> ID=%d  %d\n",vLep[ilep].ID,charge);
    }
  }
  //  printf("Nlep(pT>20)=%d  charge=%d\n",Nlep,charge);
  
  if(Nlep!=2) return true;  // go to next event
  if(charge > 0 ) return true;  // go to next event
 
  //  printf("  <-------GOOD---\n");
  
  // Count remaining leptons with pT>10
  // for (int ilep=0; ilep < (int)vLep.size(); ilep++){
//     if(vLep[ilep].FourVector.Pt() >= 10.*GeV && vLep[ilep].FourVector.Pt() < 20.*GeV ) 
//       return true;   // go to next event
//   }
  
  return false;  // check next cuts
}


bool CutClass::mLLCutOS(vector<Particle> vLep,float  mllCut){
  
  CutClass::Particle theLep[2];
  int Nlep=0;
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt()>10.*GeV){
      theLep[Nlep]=vLep[ilep];
      Nlep++;
    }
  }
  
  float InvMass = sqrt(vLep[0].FourVector.M()*vLep[0].FourVector.M()+
		       vLep[1].FourVector.M()*vLep[1].FourVector.M()+
		       2.*((vLep[0].FourVector.E()*vLep[1].FourVector.E())-
			   (vLep[0].FourVector.Px()*vLep[1].FourVector.Px()+
			    vLep[0].FourVector.Py()*vLep[1].FourVector.Py()+
			    vLep[0].FourVector.Pz()*vLep[1].FourVector.Pz())));
  
  if(InvMass<mllCut*GeV)
    return true;  // go to next event
  else
    return false;  // check next cuts
}

bool CutClass::TwoLeptonsSS(vector<Particle> vLep){
  
  int Nlep=0;
  int charge=1;
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt()>20.*GeV){
      Nlep++;
      charge=charge*vLep[ilep].ID;
    }
  }
  //  printf("Nlep(pT>20)=%d\n",Nlep);
  
  if(Nlep!=2) return true;  // go to next event
  if(charge < 0 ) return true;  // go to next event
  
  //Count remaining leptons with pT>10
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt() >= 10.*GeV && vLep[ilep].FourVector.Pt() < 20.*GeV ) 
      return true;   // go to next event
  }
  
  return false;  // check next cuts
}

bool CutClass::mLLCutSS(vector<Particle> vLep, float mllCut){
  
  CutClass::Particle theLep[2];
  int Nlep=0;
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt()>20.*GeV){
      theLep[Nlep]=vLep[ilep];
      Nlep++;
    }
  }
  
  float InvMass = sqrt(vLep[0].FourVector.M()*vLep[0].FourVector.M()+
		       vLep[1].FourVector.M()*vLep[1].FourVector.M()+
		       2.*((vLep[0].FourVector.E()*vLep[1].FourVector.E())-
			   (vLep[0].FourVector.Px()*vLep[1].FourVector.Px()+
			    vLep[0].FourVector.Py()*vLep[1].FourVector.Py()+
			    vLep[0].FourVector.Pz()*vLep[1].FourVector.Pz())));
  
  if(InvMass<mllCut*GeV)
    return true;  // go to next event
  else
    return false;  // check next cuts
}

bool CutClass::ThreeLeptons(vector<Particle> vLep){
  
  int NlepL=0;
  int NlepT=0;
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt()>20.*GeV){
      NlepL++;
    }
    if(vLep[ilep].FourVector.Pt()>10.*GeV){
      NlepT++;
    }
  }
  //  printf("Nlep(pT>20)=%d\n",Nlep);
  
  if(NlepT!=3) return true;  // go to next event
  if(NlepL<2) return true;  // go to next event
  
//   //Count remaining leptons with pT>10
//   for (int ilep=0; ilep < (int)vLep.size(); ilep++){
//     if(vLep[ilep].FourVector.Pt() >= 10.*GeV && vLep[ilep].FourVector.Pt() < 20.*GeV ) 
//       return true;   // go to next event
//   }
  
  return false;  // check next cuts
}

bool CutClass::mLLCut3L(vector<Particle> vLep, float mllCut){
  
  CutClass::Particle theLep[2];
  int Nlep=0;
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt()>20.*GeV){
      if(Nlep<2)
	theLep[Nlep]=vLep[ilep];
      Nlep++;
    }
  }
  
  float InvMass = sqrt(vLep[0].FourVector.M()*vLep[0].FourVector.M()+
		       vLep[1].FourVector.M()*vLep[1].FourVector.M()+
		       2.*((vLep[0].FourVector.E()*vLep[1].FourVector.E())-
			   (vLep[0].FourVector.Px()*vLep[1].FourVector.Px()+
			    vLep[0].FourVector.Py()*vLep[1].FourVector.Py()+
			    vLep[0].FourVector.Pz()*vLep[1].FourVector.Pz())));
  
  if(InvMass<mllCut*GeV)
    return true;  // go to next event
  else
    return false;  // check next cuts
}

bool CutClass::ZeroLepton(vector<Particle> vLep){
  
  int Nlep=0;
  for (int ilep=0; ilep < (int)vLep.size(); ilep++){
    if(vLep[ilep].FourVector.Pt()>20.*GeV){
      Nlep++;
    }    
  }
  
  if((Nlep)!=0) return true;  // go to next event
 
  return false;  // check next cuts
}


float CutClass::MEff_RefFinal(vector<Particle> vJet, vector<Particle> vLep, float met, int nleptons, int Njets){
  
  double meff=0.;
  for(int ijet=0; ijet<(int)vJet.size(); ijet++){
    //    if(ijet==Njets) break; // Uncomment to be a la Freiburg!
    if(ijet==4) break; // A la Tapas
    //cout << "Jet "<< ijet << "  Pt="<<vJet[ijet].FourVector.Pt()/GeV<< endl;
    meff += vJet[ijet].FourVector.Pt();
  }
  //  cout << "MEFF-Jet="<<meff/GeV<< endl;

  meff += met;
  //  cout << "MEFF-MET="<<meff/GeV<< endl;

  if(nleptons>0){
    for (int ilep=0; ilep < (int)vLep.size(); ilep++){
      //      cout << "Lep "<< ilep << "  Pt="<<vLep[ilep].FourVector.Pt()/GeV<< endl;
      meff += vLep[ilep].FourVector.Pt();
    }
  }
  //  cout << "MEFF-Lep="<<meff/GeV<< endl;

  return (meff);
}



float CutClass::MT_RefFinal(vector<Particle> vLep, float met, float phimet){

  // Definition by Sep: mt=sqrt{2*pT*MET*(1-cos(phi))}

  double mt;

  double deltaphi=DiffPhi(vLep[0].FourVector.Phi()-phimet);
  mt=sqrt(2*vLep[0].FourVector.Pt()*met*(1-cos(deltaphi)));

  return (mt);
}

float CutClass::deltaR(TLorentzVector tlv1, TLorentzVector tlv2) {

  Float_t deltaEta = fabs(tlv1.Eta() - tlv2.Eta());
  Float_t deltaPhi = fabs(tlv1.Phi() - tlv2.Phi());
  if (deltaPhi > Pi){
    deltaPhi = 2*Pi - deltaPhi;
  }
  Float_t deltaR = sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
  return deltaR;
}


float CutClass::DiffPhi(float dPhi) {
  if (fabs(dPhi) > Pi) return fabs(2.*Pi-fabs(dPhi));
  return fabs(dPhi);
}

bool CutClass::DeltaPhiCut(vector<Particle> vP,float METphi, float ptLast){

  for(int i=0;i<(int)vP.size();i++){
    if ( i<3 && vP[i].FourVector.Pt()>ptLast) {
      if( DiffPhi(vP[i].FourVector.Phi()-METphi) < 0.2){
	//	printf("jet %d: %f   met:%f \n",i,vP[i].FourVector.Phi(),METphi);
	return true;  // kill the event
      }
    }
  }
  
  return false;   // if nothing found it is because is good

}

void CutClass::RemoveBadParticles(vector<Particle> vP){

  //remove all the bad objects
  vector<Particle>::iterator startPIterator;

  startPIterator = vP.begin();
  int size;
  int size0=(int)vP.size();
  for (int j=0;j<size0;j++){
    size=(int)vP.size();
    for (int i=0; i < size; i++){
      if (vP[i].good == 0){
	vP.erase(startPIterator + i);
	break;
      }
    }
  }

}

void CutClass::RemoveBadParticles(vector<Particle>* vP){

  //remove all the bad objects
  vector<Particle>::iterator startPIterator;

  startPIterator = vP->begin();
  int size;
  int size0=(int)(*vP).size();
  for (int j=0;j<size0;j++){
    size=(int)(*vP).size();
    for (int i=0; i < size; i++){
      if (((*vP)[i]).good == 0){
	(*vP).erase(startPIterator + i);
	break;
      }
    }
  }

  
//   vector<Particle>::iterator PIterator;
//   for( PIterator = (*vP).begin(); PIterator != (*vP).end(); PIterator++ ) {
//     if ( (*PIterator).good == 0){
//       (*vP).erase(PIterator);
//     }
//   }
  
  // int size0=(int)(*vP).size();
//   for (int j=0;j<size0;j++){
//     for (int i=0;i<(*vP).size();i++){
//       if (((*vP)[i]).good == 0){
// 	(*vP).erase((*vP).begin()+i);
// 	break;
//       }
//     }
//   }


}

bool CutClass::JetCuts(vector<Particle> vJet,int njets,float ptLeading,float ptLast){
     
  int NjLeading=0,NjLast=0;
  for (int ijet=0; ijet < (int)vJet.size(); ijet++){
    if ( vJet[ijet].FourVector.Pt()> ptLeading*GeV ) NjLeading++;
    if ( vJet[ijet].FourVector.Pt()> ptLast*GeV ) NjLast++;
  } 
  
  //  if(njets==4){
  if( NjLeading>0 && NjLast>=njets)  // 4 jet is inclusive
    return false;  // good event, go on cutting
  else
    return true;  // kill the event
//   }else{
//     if( NjLeading>0 && NjLast==njets)  // NjLast==njets because they're exclusive channels!!
//       return false;  // good event, go on cutting
//     else
//       return true;  // kill the event
//   }
}


void CutClass::DumpParticle(Particle p){
  printf("good: %d   ID: %d  Phi: %f  Eta: %f Pt: %f GeV \n",p.good,p.ID
	 ,p.FourVector.Phi(),p.FourVector.Eta(),p.FourVector.Pt()/GeV);
}


void CutClass::FillNEntriesXsect(float nentr,float xsect,int ilast){
  ANA_NENTRIES->Fill(nentr,1);
  ANA_XSECT0->Fill(0.,xsect);
  
  return;
}


void CutClass::FillAnalysisHistograms(int i,vector<Particle> vJet,vector<Particle> vLep,vector<Particle> vEle, vector<Particle> vMu, double w, float MET, float METphi,int nleptons,int njets){
  
  //Xsect and number of events
  ANA_XSECT[i]->Fill(0.,w);

  if(nleptons==1){  
    if((int)vEle.size()==1)
      ANA_XSECT_ELECT[i]->Fill(0.,w);
    
    if((int)vMu.size()==1)
      ANA_XSECT_MUON[i]->Fill(0.,w);
  }
  
  if(nleptons==2){  
    if((int)vEle.size()==1 && (int)vMu.size()==1)
      ANA_XSECT_MIXED[i]->Fill(0.,w);

    if((int)vEle.size()==2)
      ANA_XSECT_ELECT[i]->Fill(0.,w);

    if((int)vMu.size()==2)
      ANA_XSECT_MUON[i]->Fill(0.,w);
  }


  ANA_NB[i]->Fill(0.,w);

  // Distributions for MEFF, MET, MET.
  ANA_MEFF[i]->Fill(MEff_RefFinal(vJet, vLep,MET,nleptons,njets)/GeV,w);
  ANA_MET[i]->Fill(MET/GeV,w);
  ANA_MET_MEFF[i]->Fill(MET/MEff_RefFinal(vJet, vLep,MET,nleptons,njets),w);
  ANA_MT[i]->Fill(MT_RefFinal(vLep, MET, METphi)/GeV,w);
  
  if(MT_RefFinal(vLep, MET, METphi)<=100*GeV){
    ANA_MET_LowMT[i]->Fill(MET/GeV,w);
    ANA_MEFF_LowMT[i]->Fill(MEff_RefFinal(vJet, vLep,MET,nleptons,njets)/GeV,w);
  }else{
    ANA_MET_HighMT[i]->Fill(MET/GeV,w);
    ANA_MEFF_HighMT[i]->Fill(MEff_RefFinal(vJet, vLep,MET,nleptons,njets)/GeV,w);
  }
  // 2D histograms
  ANA_MEFF_MT[i]->Fill(MEff_RefFinal(vJet, vLep,MET,nleptons,njets)/GeV,MT_RefFinal(vLep, MET, METphi)/GeV,w);
  ANA_MET_MT[i]->Fill(MET/GeV,MT_RefFinal(vLep, MET, METphi)/GeV,w);
  
  // Lepton Multiplicity
  ANA_NEL[i]->Fill(vEle.size(),w);
  ANA_NMU[i]->Fill(vMu.size(),w);
  ANA_NLEP[i]->Fill((int)vLep.size(),w);

  if((int)vJet.size()>0)
    ANA_PTJET1[i]->Fill(vJet[0].FourVector.Pt()/GeV,w);
  if((int)vJet.size()>1)
    ANA_PTJET2[i]->Fill(vJet[1].FourVector.Pt()/GeV,w);
  if((int)vJet.size()>2)
    ANA_PTJET3[i]->Fill(vJet[2].FourVector.Pt()/GeV,w);
  if((int)vJet.size()>3)
    ANA_PTJET4[i]->Fill(vJet[3].FourVector.Pt()/GeV,w);

  if((int)vLep.size()>0)
    ANA_PTLEP1[i]->Fill(vLep[0].FourVector.Pt()/GeV,w);
  if((int)vLep.size()>1)
    ANA_PTLEP2[i]->Fill(vLep[1].FourVector.Pt()/GeV,w);


  // Matching variables
  for(int j=0;j<(int)vJet.size();j++)
    RMATCH_JET[i]->Fill(vJet[j].rMatchEle,w);

//   for(int j=0;j<(int)vEle.size();j++)
//     RMATCH_EL[i]->Fill(vEle[j].rMatch,w);

//   for(int j=0;j<(int)vMu.size();j++)
//     RMATCH_MU[i]->Fill(vMu[j].rMatch,w);

  return;
 
}

void CutClass::FillSummaryNtuple(int jentry,int EvNb,vector<Particle> vJet,vector<Particle> vLep,vector<Particle> vEle, vector<Particle> vMu, double w, float MET, float pxMiss, float pyMiss, float METphi,int nleptons){
  
 
  nJet=0;
  for (int ijet=0; ijet < (int)vJet.size(); ijet++){
    if(vJet[ijet].FourVector.Pt()>20*GeV){
      //      cout << "i="<< ijet << "  pT="<<vJet[ijet].FourVector.Pt()/GeV << endl;
      etaJet[nJet]= vJet[nJet].FourVector.Eta();
      ptJet[nJet]= vJet[nJet].FourVector.Pt();
      nJet++;
    }
  }
  
  meff = 0.;
  for (int ijet=0; ijet < (int)vJet.size(); ijet++)
    meff += vJet[ijet].FourVector.Pt();
  meff+=MET;
  for (int ilep=0; ilep < (int)vLep.size(); ilep++)
    meff += vLep[ilep].FourVector.Pt();
    
  mT = MT_RefFinal(vLep, MET, METphi);
  st = 0;//CalcSpher(vJet,vLep,nleptons);
  ptMiss = MET;
  
  HT = 0;
  for(Int_t k=0;k<vJet.size();k++) {
    if(fabs(vJet[k].FourVector.Eta()) < 2.5)
      HT += vJet[k].FourVector.Pt();
  }

  //  printf("%d -> MET:%4.1f  MEFF:%4.1f  MT:%4.1f  HT:%4.1f  ST:%4.1f \n",jentry,MET/GeV,meff/GeV,mT/GeV,HT/GeV,st);
  
//   for(int i=0;i<vJet.size();i++)
//     printf("JET %d   E: %3.2f   pT: %3.2f   px: %3.2f   py: %3.2f   pz: %3.2f  Eta: %3.2f   Phi: %3.2f \n",i,
// 	   vJet[i].FourVector.E()/GeV,vJet[i].FourVector.Pt()/GeV,
// 	   vJet[i].FourVector.Px()/GeV,vJet[i].FourVector.Py()/GeV,vJet[i].FourVector.Pz()/GeV,
// 	   vJet[i].FourVector.Eta(),vJet[i].FourVector.Phi());

//   for(int i=0;i<vLep.size();i++)
//     printf("Lep %d   E: %3.2f   pT: %3.2f   px: %3.2f   py: %3.2f   pz: %3.2f\n",i,vLep[i].FourVector.E()/GeV,vLep[i].FourVector.Pt()/GeV,
// 	   vLep[i].FourVector.Px()/GeV,vLep[i].FourVector.Py()/GeV,vLep[i].FourVector.Pz()/GeV);
  


  if(HT/GeV>150 && MET/GeV>20) {
    
    Double_t max_pt_vec_sum = 0;
    Int_t I1(-1), I2(-1), I3(-1);
    for(int i1=0; i1<vJet.size()-2; i1++) {
      for(int i2=i1+1; i2<vJet.size()-1; i2++) {
	for(int i3=i2+1; i3<vJet.size(); i3++) {
	  if(GetAveDR(vJet[i1],vJet[i2],vJet[i3])<1.2) {
	    Float_t PtSum = (vJet[i1].FourVector + vJet[i2].FourVector + vJet[i3].FourVector).Pt();
// 	    printf("Combination  Pt:%3.1f  Mass: %3.1f\n",
// 		   (vJet[i1].FourVector + vJet[i2].FourVector + vJet[i3].FourVector).Pt()/GeV,
// 		   (vJet[i1].FourVector + vJet[i2].FourVector + vJet[i3].FourVector).M()/GeV);
	    if(PtSum>max_pt_vec_sum) {
	      max_pt_vec_sum = PtSum;
	      I1 = i1;
	      I2 = i2;
	      I3 = i3;
// 	      printf("--> HadTop New max: %d %d %d -> %3.1f\n",(int)I1,(int)I2,(int)I3,max_pt_vec_sum/GeV);
	    }
	  }
	}
      }
    }
    // Same stuff without the DeltaR cut
    if(I1<0 || I2<0 || I3<0) {
      for(int i1=0; i1<vJet.size()-2; i1++) {
	for(int i2=i1+1; i2<vJet.size()-1; i2++) {
	  for(int i3=i2+1; i3<vJet.size(); i3++) {
	    Float_t PtSum = (vJet[i1].FourVector + vJet[i2].FourVector + vJet[i3].FourVector).Pt();
// 	    printf("CombinationNoDeltaR  Pt:%3.1f  Mass: %3.1f\n",
// 		   (vJet[i1].FourVector + vJet[i2].FourVector + vJet[i3].FourVector).Pt()/GeV,
// 		   (vJet[i1].FourVector + vJet[i2].FourVector + vJet[i3].FourVector).M()/GeV);
	    if(PtSum>max_pt_vec_sum) {
	      max_pt_vec_sum = PtSum;
	      I1 = i1;
	      I2 = i2;
	      I3 = i3;
// 	      printf("--> HadTopNoDeltaR New max: %d %d %d -> %3.1f\n",(int)I1,(int)I2,(int)I3,max_pt_vec_sum/GeV);
	    }
	  }
	}
      }
    }

    for(int i1=0; i1<vJet.size(); i1++) {
      if(vJet[i1].FourVector.M()/GeV>65.4 && vJet[i1].FourVector.M()/GeV<95.4) {
	for(int i2=0; i2<vJet.size(); i2++) {
	  if(i2==i1) continue;
	  if(GetAveDR(vJet[i1],vJet[i2])<1.2) {
	    TVector2 v1(vJet[i1].FourVector.Px(),vJet[i1].FourVector.Py());
	    TVector2 v2(vJet[i2].FourVector.Px(),vJet[i2].FourVector.Py());
	    TVector2 vt = v1+v2;
	    if(vt.Mod()>max_pt_vec_sum) {
	      max_pt_vec_sum = vt.Mod();
	      if(fabs(vJet[i1].FourVector.M()/GeV-80.4)<fabs(vJet[i1].FourVector.M()/GeV-80.4)) {
		I1 = i1;
		I2 = i1;
		I3 = i2;
	      }
	      else {
		I1 = i2;
		I2 = i2;
		I3 = i1;
	      }
	      //	      printf("W: New max: %d %d -> pt: %3.1f  \n",(int)I1,(int)I2,max_pt_vec_sum);
	    }
	  }
	}
      }
    }
  
    Double_t pzMiss;
    Double_t ptX = vLep[0].FourVector.Px()*pxMiss + vLep[0].FourVector.Py()*pyMiss;
    Double_t tmp = pow(80.4*GeV,2)+2*ptX;
    if(mT/GeV<80.4) {
      Double_t pzMiss1 = (vLep[0].FourVector.Pz()*tmp-vLep[0].FourVector.E()*sqrt(pow(tmp,2)-pow(2*vLep[0].FourVector.Pt()*MET,2)))/2/vLep[0].FourVector.Pt()/vLep[0].FourVector.Pt();
      Double_t pzMiss2 = (vLep[0].FourVector.Pz()*tmp+vLep[0].FourVector.E()*sqrt(pow(tmp,2)-pow(2*vLep[0].FourVector.Pt()*MET,2)))/2/vLep[0].FourVector.Pt()/vLep[0].FourVector.Pt();
      //      printf("    1: %f   2: %f \n",pzMiss1,pzMiss2);
      if(fabs(pzMiss1)<fabs(pzMiss2)) pzMiss = pzMiss1;
      else pzMiss = pzMiss2;
    }else 
      pzMiss = vLep[0].FourVector.Pz()*MET/vLep[0].FourVector.Pt();
    
    //    printf("      pzMiss: %3.1f   pxMiss: %3.1f   pyMiss: %3.1f   ptMiss: %3.1f %3.1f\n",pzMiss/GeV,pxMiss/GeV,pyMiss/GeV,MET/GeV,sqrt(pxMiss*pxMiss+pyMiss*pyMiss)/GeV);

    Double_t eMiss = sqrt(pow(ptMiss,2)+pow(pzMiss,2));
    Particle pMiss;
    pMiss.FourVector.SetPxPyPzE(pxMiss,pyMiss,pzMiss,eMiss);
//     printf("After pzMiss: %3.1f   pxMiss: %3.1f   pyMiss: %3.1f   ptMiss: %3.1f   %3.1f   Eta: %2.1f\n",
//  	   pMiss.FourVector.Pz()/GeV,pMiss.FourVector.Px()/GeV,
//  	   pMiss.FourVector.Py()/GeV,pMiss.FourVector.Pt()/GeV,pMiss.FourVector.M()/GeV,pMiss.FourVector.Eta());    

    max_pt_vec_sum = 0;
    Int_t I4(-1);
    for(int k=0; k<vJet.size(); k++) {   
      if(k==I1 || k==I2 || k==I3 ) continue;
      if(GetAveDR(pxMiss, pyMiss, pzMiss, vJet[k], vLep[0])<1.4) {
// 	printf("Lep Combination %d Pt:%3.1f  Mass: %3.1f\n",k,
// 	       (pMiss.FourVector + vJet[k].FourVector + vLep[0].FourVector).Pt()/GeV,
// 	       (pMiss.FourVector + vJet[k].FourVector + vLep[0].FourVector).M()/GeV);
	Float_t PtSum = (pMiss.FourVector + vJet[k].FourVector + vLep[0].FourVector).Pt();
	if(PtSum>max_pt_vec_sum) {
	  max_pt_vec_sum = PtSum;
	  I4 = k;
	}
      }
    }
    // Same stuff without DR
    if(I4<0) {
      for(int k=0; k<vJet.size(); k++) {
	if(k==I1 || k==I2 || k==I3 ) continue;
// 	printf("Lep Combination %d noDeltaR Pt:%3.1f  Mass: %3.1f\n",k,
// 	       (pMiss.FourVector + vJet[k].FourVector + vLep[0].FourVector).Pt()/GeV,
// 	       (pMiss.FourVector + vJet[k].FourVector + vLep[0].FourVector).M()/GeV);
	Float_t PtSum = (pMiss.FourVector + vJet[k].FourVector + vLep[0].FourVector).Pt();
	if(PtSum>max_pt_vec_sum) {
	  max_pt_vec_sum = PtSum;
	  I4 = k;
	}
      }
    }
   
    Int_t  ij1_W, ij2_W;
    Int_t  ib_had;
    Int_t  ib_lep;
   
   //  Float_t mTop_had;
//     Float_t mW_had;
//     Float_t mTop_lep;
    
    Float_t ptW_had;
    Float_t ptTop_had;
    Float_t ptTop_lep;
    Float_t ptW_lep;

    ptW_lep   = (vLep[0].FourVector + pMiss.FourVector).Pt();
    ptTop_lep = (vJet[I4].FourVector + vLep[0].FourVector + pMiss.FourVector).Pt();
    mTop_lep = (vJet[I4].FourVector + vLep[0].FourVector + pMiss.FourVector).M();
    // Xin: mTop_lep = GetMass(eLep,pxLep,pyLep,pzLep,eMiss,pxMiss,pyMiss,pzMiss,eJet[I4],pxJet[I4],pyJet[I4],pzJet[I4]);
    // printf("Emiss: %f  %f \n",eMiss/GeV,pMiss.FourVector.E()/GeV);
    //     mTop_lep = GetMass(vLep[0].FourVector.E(),vLep[0].FourVector.Px(),vLep[0].FourVector.Py(),vLep[0].FourVector.Pz(),
    // 		       eMiss,pxMiss,pyMiss,pzMiss,
    // 		       vJet[I4].FourVector.E(),vJet[I4].FourVector.Px(),vJet[I4].FourVector.Py(),vJet[I4].FourVector.Pz());

    //    mTop_lep = GetMass(eLep,pxLep,pyLep,pzLep,eMiss,pxMiss,pyMiss,pzMiss,eJet[I4],pxJet[I4],pyJet[I4],pzJet[I4]);

    ib_lep    = I4;
    
    if(I1!=I2) {
      ptTop_had = (vJet[I1].FourVector + vJet[I2].FourVector + vJet[I3].FourVector).Pt();
      mTop_had  = (vJet[I1].FourVector + vJet[I2].FourVector + vJet[I3].FourVector).M();   
      ij1_W  = I2;
      ij2_W  = I1;
      ib_had = I3;
      mW_had = (vJet[I1].FourVector + vJet[I2].FourVector).M(); 
      tmp = (vJet[I1].FourVector + vJet[I3].FourVector).M();
      if(fabs(tmp/GeV-80.4)<fabs(mW_had/GeV-80.4)) {
	mW_had = tmp;
	ij1_W  = I1;
	ij2_W  = I3;
	ib_had = I2;
      }
      tmp = (vJet[I2].FourVector + vJet[I3].FourVector).M();
      if(fabs(tmp/GeV-80.4)<fabs(mW_had/GeV-80.4)) {
	mW_had = tmp;
	ij1_W  = I3;
	ij2_W  = I2;
	ib_had = I1;
      }
      ptW_had = (vJet[ij1_W].FourVector + vJet[ij2_W].FourVector).Pt(); 
    }else {
      ptTop_had = (vJet[I1].FourVector + vJet[I3].FourVector).Pt();
      mTop_had  = (vJet[I1].FourVector + vJet[I3].FourVector).M(); 
      mW_had    = vJet[I1].FourVector.M();
      ptW_had   = vJet[I1].FourVector.Pt();
      ij1_W     = I1;
      ij2_W     = I2;
      ib_had    = I3;
    }
//     printf("===> New masses: %3.1f   %3.1f    %3.1f\n",mTop_had/GeV,mW_had/GeV,mTop_lep/GeV);

    mTop_lep = (vLep[0].FourVector + pMiss.FourVector + vJet[I4].FourVector).M();
    
    oblate = GetOblateness(vJet,I4,I1,I2,I3,vLep,pMiss);
//     printf("===> Oblateness: %3.3f\n",oblate);
    


 
  }

  entry = jentry;
  event = EvNb;
  
  weight = w;
  
  chargeLep = vLep[0].ID/fabs(vLep[0].ID);

  treeSummary->Fill();
  return;
  
}

void CutClass::BookSummaryNtuple(){
  treeSummary= new TTree("ntp","ntp");
  treeSummary->Branch("ptMiss",&ptMiss,"ptMiss/F");
  treeSummary->Branch("mT",&mT,"mT/F");
  treeSummary->Branch("st",&st,"st/F");
  treeSummary->Branch("meff",&meff,"meff/F");
  treeSummary->Branch("weight",&weight,"weight/F");
  treeSummary->Branch("entry",&entry,"entry/I");
  treeSummary->Branch("event",&event,"event/I");
  treeSummary->Branch("mTop_had",&mTop_had,"mTop_had/F");
  treeSummary->Branch("mW_had",&mW_had,"mW_had/F");
  treeSummary->Branch("mTop_lep",&mTop_lep,"mTop_lep/F");
  treeSummary->Branch("HT",&HT,"HT/F");
  treeSummary->Branch("oblate",&oblate,"oblate/F");
  treeSummary->Branch("nJet",&nJet,"nJet/I");
  treeSummary->Branch("chargeLep",&chargeLep,"chargeLep/F");
  treeSummary->Branch("etaJet",&etaJet,"etaJet[20]/F");
  treeSummary->Branch("ptJet",&ptJet,"ptJet[20]/F");

}

void CutClass::WriteSummaryNtuple(const char * outfname){

  if (!outfname) outfname="mysummary.root";
  TFile f2(outfname,"recreate");
  f2.cd();
  treeSummary->Write();

}

void CutClass::ScaleXSectHistogram(double xsect, double TotWeight){

  //Xsect and number of events
  double factor=xsect/TotWeight;
  
  for(int i=0;i<10;i++){
    ANA_XSECT[i]->Scale(factor);
    ANA_XSECT_ELECT[i]->Scale(factor);
    ANA_XSECT_MUON[i]->Scale(factor);
    ANA_XSECT_MIXED[i]->Scale(factor);
//     ANA_NLEP[i]->Scale(factor);
//     ANA_NEL[i]->Scale(factor);
//     ANA_NMU[i]->Scale(factor);
  }
 
//   ANA_MT_Ctrl->Sumw2();
//   ANA_MT_Sig1->Sumw2();
//   ANA_MET_Sig2->Sumw2();

//   ANA_MT_Ctrl->Scale(factor);
//   ANA_MT_Sig1->Scale(factor);
//   ANA_MET_Sig2->Scale(factor);
  
}



// ====================
// MATERIAL FROM XIN:
// ====================
Double_t CutClass::GetDR(Float_t eta1, Float_t phi1, Float_t eta2, Float_t phi2) {
  Float_t dphi = fabs(phi1-phi2);
  if(dphi>M_PI) dphi = 2*M_PI-dphi;
  Float_t deta = fabs(eta1-eta2);
  Float_t dr = sqrt(dphi*dphi+deta*deta);
  return dr;
}

Double_t CutClass::GetAveDR(Particle j1, Particle j2) {
  //  printf("In the only 2 partt mode!\n");
  Double_t eta = (j1.FourVector + j2.FourVector ).Eta();
  Double_t phi = (j1.FourVector + j2.FourVector ).Phi();
  
  Double_t dr1 = GetDR(j1.FourVector.Eta(),j1.FourVector.Phi(),eta,phi);
  //  printf("dr1: %2.1f   ",dr1);
  Double_t dr2 = GetDR(j2.FourVector.Eta(),j2.FourVector.Phi(),eta,phi);
  //printf("dr2: %2.1f   ",dr2);
  
  return (dr1+dr2)/2;

}

Double_t CutClass::GetAveDR(Particle j1, Particle j2, Particle j3) {
  
  Double_t eta = (j1.FourVector + j2.FourVector +j3.FourVector).Eta();
  Double_t phi = (j1.FourVector + j2.FourVector +j3.FourVector).Phi();
  
  Double_t dr1 = GetDR(j1.FourVector.Eta(),j1.FourVector.Phi(),eta,phi);
  //  printf("dr1: %2.1f   ",dr1);
  Double_t dr2 = GetDR(j2.FourVector.Eta(),j2.FourVector.Phi(),eta,phi);
  //printf("dr2: %2.1f   ",dr2);
  Double_t dr3 = GetDR(j3.FourVector.Eta(),j3.FourVector.Phi(),eta,phi);
  //printf("dr3: %2.1f\n",dr3);
  //printf("avg: %2.1f\n",(dr1+dr2+dr3)/3);
  
  return (dr1+dr2+dr3)/3;
}

Double_t CutClass::GetAveDR(Double_t pxMiss, Double_t pyMiss, Double_t pzMiss, Particle ib, Particle Lep) {
  Double_t px = pxMiss+Lep.FourVector.Px()+ib.FourVector.Px();
  Double_t py = pyMiss+Lep.FourVector.Py()+ib.FourVector.Px();
  Double_t pz = pzMiss+Lep.FourVector.Pz()+ib.FourVector.Px();

  Double_t pt = sqrt(px*px+py*py);
  Double_t p  = sqrt(pt*pt+pz*pz);

  Double_t eta = 0.5*log((p+pz)/(p-pz));
  Double_t phi = atan2(py,px);

  Double_t pMiss   = sqrt(ptMiss*ptMiss+pzMiss*pzMiss);
  Double_t etaMiss = 0.5*log((pMiss+pzMiss)/(pMiss-pzMiss));
  Double_t phiMiss = atan2(pyMiss,pxMiss);

  Double_t dr1 = GetDR(etaMiss,phiMiss,eta,phi);
  Double_t dr2 = GetDR(Lep.FourVector.Eta(),Lep.FourVector.Phi(),eta,phi);
  Double_t dr3 = GetDR(ib.FourVector.Eta(),ib.FourVector.Phi(),eta,phi);

  return (dr1+dr2+dr3)/3;
}

Double_t CutClass::GetPt(Double_t px1, Double_t py1, Double_t px2, Double_t py2) {
  Double_t px = px1+px2;
  Double_t py = py1+py2;
  return sqrt(pow(px,2)+pow(py,2));
}

Double_t CutClass::GetPt(Double_t px1, Double_t py1, Double_t px2, Double_t py2, Double_t px3, Double_t py3) {
  Double_t px = px1+px2+px3;
  Double_t py = py1+py2+py3;
  return sqrt(pow(px,2)+pow(py,2));
}

Double_t CutClass::GetMass(Double_t e1, Double_t px1, Double_t py1, Double_t pz1, Double_t e2, Double_t px2, Double_t py2, Double_t pz2) {
  Double_t e  = e1+e2;
  Double_t px = px1+px2;
  Double_t py = py1+py2;
  Double_t pz = pz1+pz2;
  return sqrt(pow(e,2)-pow(px,2)-pow(py,2)-pow(pz,2));
}

Double_t CutClass::GetMass(Double_t e1, Double_t px1, Double_t py1, Double_t pz1, Double_t e2, Double_t px2, Double_t py2, Double_t pz2, Double_t e3, Double_t px3, Double_t py3, Double_t pz3) {
  Double_t e  = e1+e2+e3;
  Double_t px = px1+px2+px3;
  Double_t py = py1+py2+py3;
  Double_t pz = pz1+pz2+pz3;
  return sqrt(pow(e,2)-pow(px,2)-pow(py,2)-pow(pz,2));
}

Double_t CutClass::GetOblateness(vector<Particle> vJet, Int_t I4, Int_t I1, Int_t I2, Int_t I3, vector<Particle> vLep, Particle pMiss) {
  Double_t pxTop1(0), pyTop1(0);
  if(I1!=I2) {
    pxTop1 = (vJet[I1].FourVector + vJet[I2].FourVector + vJet[I3].FourVector).Px();
    pyTop1 = (vJet[I1].FourVector + vJet[I2].FourVector + vJet[I3].FourVector).Py();
  }
  else {
    pxTop1 = (vJet[I1].FourVector + vJet[I3].FourVector).Px();
    pyTop1 = (vJet[I1].FourVector + vJet[I3].FourVector).Py();
  }
  Double_t ptTop1  = sqrt(pow(pxTop1,2)+pow(pyTop1,2));
  Double_t phiTop1 = atan2(pyTop1,pxTop1);

  Double_t pxTop2  = (vJet[I4].FourVector + vLep[0].FourVector + pMiss.FourVector).Px();
  Double_t pyTop2  = (vJet[I4].FourVector + vLep[0].FourVector + pMiss.FourVector).Py();
  Double_t ptTop2  = sqrt(pow(pxTop2,2)+pow(pyTop2,2));
  Double_t phiTop2 = atan2(pyTop2,pxTop2);

  Double_t pt[20], phi[20];
  Int_t n=0;
  for(Int_t i=0;i<vJet.size();i++) {
    if(i!=I4 && i!=I1 && i!=I2 && i!=I3) {
      pt[n]  = vJet[i].FourVector.Pt();
      phi[n] = vJet[i].FourVector.Phi();
      n++;
    }
  }
  pt[n]  = ptTop1;
  phi[n] = phiTop1;
  n++;
  pt[n]  = ptTop2;
  phi[n] = phiTop2;
  n++;

  return oblateness(pt,phi,n);
}


