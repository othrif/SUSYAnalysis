#include "SS3LAnalysis/ClassifyAndCalculateHF.h"
#include "TVector3.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>

#include "xAODCore/ShallowCopy.h"

#define HADPTCUT 5000
#define JETPTCUT 10000
#define JETETACUT 2.5
#define DRCONE   0.4

bool debugme = false;

//-----------------------------------------------//

ClassifyAndCalculateHF::ClassifyAndCalculateHF(xAOD::TEvent*& event, std::string truthcollName,std::string jetcollName):m_event(event),m_truthcollName(truthcollName),m_jetcollName(jetcollName),m_ext_code(-9999),m_jet_trueflav(0),m_jet_count(0),m_jet_id(0),m_jet_pt(0),m_jet_eta(0),m_jet_phi(0),m_jet_m(0),m_jet_index(0)
{

}

ClassifyAndCalculateHF::~ClassifyAndCalculateHF(){

}

//--------//


void ClassifyAndCalculateHF::apply(int &code, int &ext_code, int &prompt_code, std::map<int,int>& mapJetClassHF){ 

  //  std::cout << "ClassifyEvent non-prompt" << std::endl;
  int HF_Classification=ClassifyEvent(false);
  //  std::cout << "ClassifyEvent prompt" << std::endl;
  int HF_Classification_Prompt=ClassifyEvent(true);

  //std::cout<<"HF CLASSIFICATION after Classify"<<HF_Classification<<std::endl;
  ext_code = HF_Classification;
  prompt_code = HF_Classification_Prompt;

  if(fabs(ext_code)>=100){
    code = 1;
  }
  else if(fabs(ext_code)==0){
    code = 0;
  }
  else{
    code =-1;
  }

  // Classify: extraB=1, extraC=2
 int iB =-1, iC=-1;   
 for(uint j=0; j< m_jet_pt.size(); j++){
   m_JetClassHF[m_jet_index.at(j)] = 0 ;
   if(m_jet_pt.at(j) < JETPTCUT || fabs(m_jet_eta.at(j)) > 2.5) 
	 continue;     
   if(ext_code >= 100 && m_jet_trueflav.at(j)==5 && m_jet_id.at(j)<3 && iB==-1) 
	 m_JetClassHF[m_jet_index.at(j)] = 1; // extraB
   else if (ext_code < 100 && m_jet_trueflav.at(j)==4 && (m_jet_id.at(j) ==0 || m_jet_id.at(j) ==-1 || m_jet_id.at(j) ==-2 ))
	 m_JetClassHF[m_jet_index.at(j)] = 2; // extraC
   //   std::cout << "Classify: jet " << j << " with index " << m_jet_index.at(j) << " classified as " << m_JetClassHF[m_jet_index.at(j)] << std::endl;
 }

 mapJetClassHF = m_JetClassHF;

}

int ClassifyAndCalculateHF::ClassifyEvent(bool doPrompt){
  //  std::cout << "Initial event" << std::endl;
  initEvent();

  //  std::cout << "flag jets" << std::endl;
  flagJets();
  //  std::cout << "count jets" << std::endl;
  m_ext_code=countJets(doPrompt);

  return m_ext_code;
}

void ClassifyAndCalculateHF::initEvent(){

  //Checks TruthJet container exists
  const xAOD::JetContainer* truthJets(nullptr);
  if(!m_event->retrieve(truthJets,m_jetcollName).isSuccess()){
    Warning( "ClassifyAndCalculateHF::InitEvent()", "Cannot retrieve TruthJets containers !" );
    return;
  }

  int jet_n=truthJets->size();
  //  std::cout << "number of truth jets: " << jet_n << std::endl;
  /*
   std::pair<xAOD::JetContainer*, xAOD::ShallowAuxContainer*> shallowcopy = xAOD::shallowCopyContainer( *truthJets ); 
   for(auto jptr : *shallowcopy.first){  
     //     m_jet_pt.push_back(jptr->pt());  
     jptr->auxdata< int >("XPtest") = -1; 
   }   
   m_event->record( shallowcopy.first, "ShallowCopiedJets" ); 
   m_event->record( shallowcopy.second, "ShallowCopiedJetsAux." );
  */

  ///initialization of data members///

  m_jet_trueflav.clear();
  m_jet_count.clear();
  m_jet_id.clear();
  m_jet_pt.clear();
  m_jet_eta.clear();
  m_jet_phi.clear();
  m_jet_m.clear();
  m_jet_trueflav.resize(jet_n,0);
  m_jet_count.resize(jet_n,0);
  m_jet_id.resize(jet_n,0);

  int counter=0;
  for(auto jptr : *truthJets){
	if(debugme)
	  std::cout << m_jetcollName << " -> jet " << counter << "/" << jet_n << ", pT=" << jptr->pt() << ", eta=" << jptr->eta() << ", phi=" << jptr->phi() << ", m=" << jptr->m()<< std::endl;
    m_jet_pt.push_back(jptr->pt());
    m_jet_eta.push_back(jptr->eta());
    m_jet_phi.push_back(jptr->phi());
    m_jet_m.push_back(jptr->m());
    m_jet_index.push_back(counter);
	counter++;
  }

}


void ClassifyAndCalculateHF::flagJets(){


  //Checks TruthParticle container exists
  const xAOD::TruthParticleContainer* truth_particles(0);
  if(!m_event->retrieve(truth_particles,m_truthcollName).isSuccess()){
    Warning( "ClassifyAndCalculateHF::flagJets()", "Cannot retrieve TruthParticles containers !" );
    return;
  }

 ///matches hadrons with jets///

  m_FinalHadrons.clear();
  m_HadronJets.clear();


  int flav;

  int counter = 0;
  for(const xAOD::TruthParticle* part: *truth_particles) {//loop truth
    int OriginFlag = part->isAvailable<int>("TopHadronOriginFlag")?part->auxdata< int >("TopHadronOriginFlag"):-1;
	//	std::cout << OriginFlag << std::endl;
	/*
	  typedef enum {extrajet=0,
	  c_MPI     =-1, b_MPI      =1,
	  c_FSR     =-2, b_FSR      =2,
	  c_from_W  =-3, b_from_W   =3,
	  c_from_top=-4, b_from_top =4,
	  c_from_H  =-5, b_from_H   =5} HF_id;
	*/

	if( OriginFlag==6 ) continue; //only hadrons flagged with origin at derivation level

	if( part->pt() < 1 ) continue; // protection against pt = 0

    m_FinalHadrons[ part->index() ]=OriginFlag; 


    flav = hadronType( part->pdgId() ); // c=4, b=5, l=0
	if(debugme){
	std::cout << m_truthcollName << " -> par " << counter << ", index=" << part->index() << ", PdgId=" << part->pdgId() << ", OriginFlag=" << OriginFlag << ", flav=" << flav << ", pT=" << part->pt() << ", eta=" << part->eta() << ", phi=" << part->phi() << ", m=" << part->m()<< std::endl;
	}
	counter++;


    TVector3 hadron, jet;
	//	std::cout << part << " pt=" << part->pt() << std::endl;
	  hadron.SetPtEtaPhi(part->pt(),part->eta(),part->phi());

    float mindr=99;
    int bestjet=-1;
    //match closest jet in DR


    for(uint jcount=0;jcount<m_jet_pt.size();jcount++){

	  if( m_jet_pt.at(jcount) < 1 ) continue;  // protection against pt = 0
	  jet.SetPtEtaPhi(m_jet_pt.at(jcount),m_jet_eta.at(jcount),m_jet_phi.at(jcount));

      if(jet.DeltaR(hadron) < DRCONE && jet.DeltaR(hadron) < mindr ){
	mindr = jet.DeltaR(hadron);
	bestjet = jcount;
      }

    }//loop over jets



    if(bestjet!=-1){
	  
      m_HadronJets[ part->index() ]=bestjet;

      if((m_jet_id.at(bestjet)==0 || (OriginFlag>0 && OriginFlag>m_jet_id.at(bestjet)) || (OriginFlag<0 && m_jet_id.at(bestjet)<0 && OriginFlag<m_jet_id.at(bestjet)) ) ){

	m_jet_id.at(bestjet) = OriginFlag;
	
      }

      if(flav > m_jet_trueflav.at(bestjet) && part->pt() >= HADPTCUT){

	m_jet_trueflav.at(bestjet) = flav;
	m_jet_count.at(bestjet) = 1;

      }
      else if(flav == m_jet_trueflav.at(bestjet)){

	m_jet_count.at(bestjet) += 1;
      }

    }//jet chosen
  }//loop over hadrons

}




int ClassifyAndCalculateHF::countJets(bool doPrompt){

  ///count how many hadrons are in a jet///

  int b=0, B=0, c=0, C=0;
  int b_prompt=0, B_prompt=0, c_prompt=0, C_prompt=0;
  for(unsigned int i=0;i<m_jet_id.size();i++){
    if(m_jet_pt.at(i) < JETPTCUT || fabs(m_jet_eta.at(i)) > JETETACUT) continue;
    ///count just additional HF for btype <3 while for c-type <1 and >-3///
    if(m_jet_trueflav.at(i)==5 && m_jet_id.at(i) < 3){
      if(m_jet_count.at(i) > 1){
	B++;
      }
      else{
	b++;
      }
    }
    if(m_jet_trueflav.at(i)==4 && (m_jet_id.at(i)==0 || m_jet_id.at(i)==-1 || m_jet_id.at(i)==-2)){
      if(m_jet_count.at(i) > 1){
	C++;
      }
      else{
	c++;
      }
    }

    if(m_jet_trueflav.at(i)==5 && m_jet_id.at(i)==0){

      if(m_jet_count.at(i) > 1){
	B_prompt++;
      }
      else{
	b_prompt++;
      }
    }
    if(m_jet_trueflav.at(i)==4 && m_jet_id.at(i)==0){
      if(m_jet_count.at(i) > 1){
	C_prompt++;
      }
      else{
	c_prompt++;
      }
    }


  }

  int ext_code = 1000*b+100*B+10*c+1*C;

  int prompt_code=1000*b_prompt+100*B_prompt+10*c_prompt+1*C_prompt;

  ///MPI and FSR categories///
  /*
  if(prompt_code==0 && ext_code!=0){
    ext_code=0;
    for(uint ii=0; ii< m_jet_id.size(); ii++){
      if(m_jet_pt.at(ii) < JETPTCUT || fabs(m_jet_eta.at(ii)) > JETETACUT) continue;
      if(m_jet_id.at(ii)==1 && m_jet_trueflav.at(ii)==5){ //b MPI
	ext_code -= 1000;
      } else if(m_jet_id.at(ii)==2 && m_jet_trueflav.at(ii)==5){ //b FSR
	ext_code -= 100;
      } else if(m_jet_id.at(ii)==-1 && m_jet_trueflav.at(ii)==4){ //c MPI
	ext_code -= 10;
      } else if(m_jet_id.at(ii)==-2 && m_jet_trueflav.at(ii)==4) { //c FSR
	ext_code -= 1;
      }
    }
	}*/

  if(doPrompt==false) return ext_code;
  if(doPrompt==true) return prompt_code;

  return 0;
}






int ClassifyAndCalculateHF::hadronType(int pdgid){

  ///method to transform hadron pdg id to parton flavor///

  int rest1(abs(pdgid%1000));
  int rest2(abs(pdgid%10000));

  if ( rest2 >= 5000 && rest2 < 6000 ) return 5;
  if( rest1 >= 500 && rest1 < 600 ) return 5;

  if ( rest2 >= 4000 && rest2 < 5000 ) return 4;
  if( rest1 >= 400 && rest1 < 500 ) return 4;

  return 0;

}


