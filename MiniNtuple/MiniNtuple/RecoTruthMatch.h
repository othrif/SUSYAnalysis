#ifndef _RECOTRUTHMATCH_H_
#define _RECOTRUTHMATCH_H_

//std includes 
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <cmath>
#include <TString.h>
#include <TLorentzVector.h>

/** @brief A simple class for reco to truth matching
 @author Estel Perez
 @author TRIUMF
 @date First Written: 23 August 2012
 @date Revised: 21 September 2012

 Selects the truth leptons that come from Z/W decay.
 By default it selects the final state leptons.
 Given the TLorentzVector of the reconstructed lepton,
 returns the mc_ index of the matched truth lepton,
 or the type of fake, or whether is charge flipped.

 Usage:
 - For every event, do:

 RecoTruthMatch recotruthmatch(0.1, (&truthparticle)->channel_number(), (&truthparticle)->n(),
 (&truthparticle)->barcode(),(&truthparticle)->status(),(&truthparticle)->pdgId(),
 (&truthparticle)->parents(), (&truthparticle)->children(),
 (&truthparticle)->pt(), (&truthparticle)->eta(), (&truthparticle)->phi(),
 (&truthparticle)->m(), 0);

 - Then for every lepton:
 int mcidx = recotruthmatch.MatchedTruthLepton((&electrons)->pt()->at(iel), (&electrons)->eta()->at(iel), (&electrons)->phi()->at(iel), (&electrons)->m()->at(iel));
 // if a match is not found, returns -1


 */

class RecoTruthMatch {

public:

	/** @brief empty constructor, needed for ROOT

	 */
	RecoTruthMatch();

	/** @brief A constructor allowing for the setting the parameters
	 @param[in] dR for reco to truth matching
	 @param[in] MC Id number to identify Sherpa generator
	 @param[in] mc_* variables to navigate D3PD truth info
	 @param[in] verbose The amount of output. A value of 0 will
	 print nothing.
	 */
	RecoTruthMatch(float dR, int mcChannel, int mc_n,
			std::vector<int> *mc_barcode, std::vector<int> *mc_status, std::vector<int> *mc_pdgId,
			std::vector<std::vector<int> > *mc_parents, std::vector<std::vector<int> > *mc_children,
			std::vector<float> *mc_pt, std::vector<float> *mc_eta, std::vector<float> *mc_phi,
			std::vector<float> *mc_m, int verbose=0, bool StepUp = true, float dRTau=0.2 );

	/** @brief Do nothing destructor */
	~RecoTruthMatch() {};

	enum type {
		PROMPT,
		CONV,
		HF,
		LF,
		UK,
		ELEC,
		MUON
	};

	///** @brief Identifies Sherpa mcChannels. Not used at the moment. */
	bool IsSherpa(int mcChannel) {return ( (mcChannel>=126892 && mcChannel<=126895) ||
				(mcChannel>=147770 && mcChannel<=147772) ||
				(mcChannel>=147774 && mcChannel<=147776) ||
				(mcChannel>=126988 && mcChannel<=126989) ||
				(mcChannel>=146820 && mcChannel<=146822) ||
				(mcChannel>=128975 && mcChannel<=128977) ||
				(mcChannel>=117800 && mcChannel<=117802) ||
				(mcChannel>=157820 && mcChannel<=157829) );}

	///** @brief given a barcode, looks for the corresponding index in the mc_ container. */
	int GetMCIdxFromBarcode(int barcode);

	///** @brief returns a vector with the index in mc_ container for the selected truth leptons.  */
	std::vector<int> LepFromHS_McIdx() {return _LepFromHS_McIdx;}

	///** @brief returns a vector with the TLorentzVector for the selected truth leptons.  */
	std::vector<TLorentzVector> LepFromHS_TLV() {return _LepFromHS_TLV;}

	///** @brief Tells you if a reconstructed lepton is matched to one of the truth selected leptons. */
	bool Matched2TruthLepton(TLorentzVector recolep_tlv, bool isTau=false);

	///** @brief Returns the mc_ index of the truth lepton that matches the reco lepton. */
	int MatchedTruthLepton(TLorentzVector recolep_tlv, bool isTau=false);

	///** @brief Returns the mc_ index of the truth lepton that matches the reco lepton. */
	int MatchedTruthLepton(float reco_pt, float reco_eta, float reco_phi, float reco_m, bool isTau=false);

	///** @brief returns a vector with the index in mc_ container for the selected truth taus.  */
	std::vector<int> TauFromHS_McIdx() {return _TauFromHS_McIdx;}

	///** @brief returns a vector with the TLorentzVector for the selected truth taus.  */
	std::vector<TLorentzVector> TauFromHS_TLV() {return _TauFromHS_TLV;}

//  ///** @brief returns a vector with pairs of vectors containing the indices of taus charged and neutral decay products.  */ 
//  std::vector< std::pair<std::vector<int>, std::vector<int> > > TauFromHS_Prongs(){return _TauFromHS_Prongs ; }

///** @brief Tells you if a reconstructed tau is matched to one of the truth selected taus. */
	bool Matched2TruthTau(TLorentzVector recolep_tlv);

	///** @brief Returns the mc_ index of the truth tau that matches the reco tau. */
	int MatchedTruthTau(TLorentzVector recolep_tlv);

	///** @brief Returns the mc_ index of the truth tau that matches the reco tau. */
	int MatchedTruthTau(float reco_pt, float reco_eta, float reco_phi, float reco_m);

//  ///** @brief Returns a pair of vectors containing the indices of the truth tau's charged and neutral decay products. */
//  std::pair<std::vector<int>, std::vector<int> > MatchedTruthTauProducts(TLorentzVector recolep_tlv);

//  ///** @brief Returns the number of charged decay products. */
//  int MatchedTruthTauNProngs(TLorentzVector recolep_tlv);

//  ///** @brief Returns the number of neutral decay products. */
//  int MatchedTruthTauNNeutral(TLorentzVector recolep_tlv);

	void printSettings();

/// Functions to make it user friendly

	/*--------------------------------------------------------------------------------*/
	///** @brief Checks if reco and truth leptons have the same charge. */
	bool isChargeFlip(TLorentzVector recolep_tlv, int recolep_charge);

	/*--------------------------------------------------------------------------------*/
	///** @brief Checks if is a prompt lepton from W, Z, tau. */
	bool isRealLepton(TLorentzVector lep, int Origin, int Type, bool isTau = false)
	{
		int imc = -1; imc = MatchedTruthLepton(lep, isTau);
		/// if not match then for sure is false
		if (imc == -1) return false;
		/// for taus, ignore origin and type
		if(isTau) return true;
		/// when reco ele from conversion of photon radiated from a truth muon, conversions are conversions always, never prompt electrons
		//std::cout<<"in isRealLepton: pdgid = "<<fabs ( _mc_pdgId->at(imc))<<" Type="<<Type<<" Origin="<<Origin<<std::endl;
		if ( fabs ( _mc_pdgId->at(imc)) == 13 && Type==4 && Origin==5) return false;
		// avoid returning true if type is not electron or muon (ex: type 17 by chance close to prompt lep)
		return (Type==21||Type==1||Type==2||Type==3||Type==4||Type==5||Type==6||Type==7||Type==8);}

	///** @brief Checks if it is not prompt and has origin 5,6or7: Conversion, Dalitz decay or Electromagnetic process. */
	bool isConvLepton(TLorentzVector lep, int Origin, int Type, bool isTau = false)
	{	return isFakeLepton(lep, Origin, Type, isTau) && (Origin == 5||Origin == 6||Origin == 7);}

	///** @brief Checks if it is not prompt. */
	bool isFakeLepton(TLorentzVector lep, int Origin, int Type, bool isTau = false)
	{	return !isRealLepton(lep, Origin, Type, isTau);}

	///** @brief Checks if it is not prompt and has origin heavy flavour. */
	bool isHFLepton(TLorentzVector lep, int Origin, int Type, bool isTau = false)
	{	return isFakeLepton(lep, Origin, Type, isTau) && (Origin == 25 || Origin == 26 || Origin == 27 ||
				Origin == 28 || Origin == 29 || Origin == 32 || Origin == 33);}

	///** @brief Checks if it is not prompt and has not origin heavy flavour or conversion. */
	bool isLFLepton(TLorentzVector lep, int Origin, int Type, bool isTau = false)
	{	return isFakeLepton(lep, Origin, Type, isTau) && !isConvLepton(lep, Origin, Type, isTau) && !isHFLepton(lep, Origin, Type, isTau);}

	///** @brief Checks if it is not prompt and not conversion. */
	bool isJFLepton(TLorentzVector lep, int Origin, int Type, bool isTau = false)
	{	return isFakeLepton(lep, Origin, Type, isTau) && !isConvLepton(lep, Origin, Type, isTau);}

	///** @brief Checks if it is not prompt and has unknown type and origin. */
	bool isUKLepton(TLorentzVector lep, int Origin, int Type, bool isTau = false)
	{	return isFakeLepton(lep, Origin, Type, isTau) && Type == 0 && Origin == 0;}

	/*--------------------------------------------------------------------------------*/
	///** @brief Returns the type of fake: 0=prompt 1=conversion 2=HF 3=LF 4=unknown. */
	int fakeType(TLorentzVector lep, int Origin, int Type, bool isTau = false)
	{
		if(isTau) {
			if (isRealLepton(lep, Origin, Type, isTau) ) return PROMPT; // Prompt
			else return UK;// Unknown
		}

		if (isRealLepton(lep, Origin, Type, isTau) ) return PROMPT; // Prompt
		else if (Origin == 5 || Origin == 6 || Origin == 7) return CONV;// Conversions
		else if (Origin == 25 || Origin == 26 || Origin == 27 ||
				Origin == 28 || Origin == 29 || Origin == 32 || Origin == 33) return HF;// Heavy Flavour
		else if (!(Type == 0 && Origin == 0)) return LF;// Light Flavour
		else return UK;// Unknown
	}

protected:

	float _dR;
	float _dRTau;
	bool _IsSherpa;
	int _verbose;
	bool _StepUp;

	int _mc_n;
	std::vector<float> *_mc_pt;
	std::vector<float> *_mc_eta;
	std::vector<float> *_mc_phi;
	std::vector<float> *_mc_m;
	std::vector<int> *_mc_pdgId;
	std::vector<int> *_mc_status;
	std::vector<int> *_mc_barcode;
	std::vector<std::vector<int> > *_mc_parents;
	std::vector<std::vector<int> > *_mc_children;

	std::vector<int> _LepFromHS_McIdx;
	std::vector<TLorentzVector> _LepFromHS_TLV;
	std::vector<int> _TauFromHS_McIdx;
	std::vector<TLorentzVector> _TauFromHS_TLV;
//  std::vector<std::pair<std::vector<int>, std::vector<int> > > _TauFromHS_Prongs;

	void setDR(float dR) {_dR = dR;}
	void setDRTau(float dRTau) {_dRTau = dRTau;}
	float dR() {return _dR;}
	float dRTau() {return _dRTau;}

	void setIsSherpa(bool IsSherpa) {_IsSherpa = IsSherpa;}
	bool IsSherpa() {return _IsSherpa;}

	void setVerbose(int verbose) {_verbose = verbose;}
	int verbose() {return _verbose;}

	void setStepUp(bool stepUp) {_StepUp = stepUp;}

	void setmc_n (int mc_n) {_mc_n = mc_n;}
	void setmc_pt (std::vector<float> *mc_pt) {_mc_pt = mc_pt;}
	void setmc_eta (std::vector<float> *mc_eta) {_mc_eta = mc_eta;}
	void setmc_phi (std::vector<float> *mc_phi) {_mc_phi = mc_phi;}
	void setmc_m (std::vector<float> *mc_m) {_mc_m = mc_m;}
	void setmc_pdgId (std::vector<int> *mc_pdgId) {_mc_pdgId = mc_pdgId;}
	void setmc_status (std::vector<int> *mc_status) {_mc_status = mc_status;}
	void setmc_barcode (std::vector<int> *mc_barcode) {_mc_barcode = mc_barcode;}
	void setmc_parents (std::vector<std::vector<int> > *mc_parents) {_mc_parents = mc_parents;}
	void setmc_children (std::vector<std::vector<int> > *mc_children) {_mc_children = mc_children;}

	///** @brief Gets a vector with the mc_ index of all mothers. */
	std::vector<int> MothersIdxVector (int imc);

	///** @brief Gets a vector with the mc_ index of all children. */
	std::vector<int> ChildrenIdxVector (int imc);

	///** @brief Checks if is W, Z or gamma. */
	bool IsBoson(int imc);

	///** @brief Checks if is e, mu or tau. */
	bool IsLepton(int imc);

	///** @brief Checks if is e, mu or tau Neutrino. */
	bool IsNeutrino(int imc);

	///** @brief Checks if lepton index is already in the list */
	bool AlreadyInLepList(int imc);

	///** @brief Checks if has a child with the same id. */
	bool DecaysIntoItself(int imc);

	///** @brief Checks if ant child is a charged lepton. */
	bool DecaysLeptonically(int imc);

	///** @brief Subtracts the neutrino 4-mom from the tau. */
	TLorentzVector GetTauVisTLV(int imc);

//  ///** @brief Classifies tau products into neutral and charged, returns a pair of vectors with mc indices */
//  std::pair<std::vector<int>, std::vector<int> > GetTauProngIdx(int imc);

	///** @brief If it is a boson/lepton steps up (check for mothers) until it finds a status=3 particle (lepton or boson) or W/Z boson. For Sherpa. */
	bool IsFromHardScattering_StepUp(int imc, int step);

	///** @brief If decays into itself or into tau, step down. Otherwise store all electrons and muons. */
	bool IsFromHardScattering_StepDown(int imc, int step);

//  ///** @brief Collect all tau decay products classified into charged and neutral. */
//  bool Tau_StepDown(int imc, std::vector<int> * childs_neutral, std::vector<int> * childs_charged, int step);

	///** @brief Returns the internal index of the truth tau that matches the reco tau. */
	int MatchedTruthTauInternalIdx(TLorentzVector recolep_tlv);

	///** @brief If Sherpa, take final state leptons. Otherwise, initial state leptons. */
	void SetTruthLeptons();

	///** @brief prints out basic info of the mc particle. */
	void partInfo(int imc);

}; /*End class RecoTruthMatch */

#endif /* #ifndef _RECOTRUTHMATCH_H_ */
