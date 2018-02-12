/*
	description: tool to compute the global trigger scale factor for the SUSY SS/3L+jets analysis
	contact: jmaurer@cern.ch
	version: 18/07/2016, evening
*/

#pragma once

/*
	Usage
	-----
	- only call the tool when MET trigger is not fired, otherwise you should set yourself the scale factor to 1
	- call AddElectron/AddMuon for each signal electron (resp. muon) with pT>20 GeV (resp. 10 GeV) REGARDLESS of their matching or not to any trigger
	- event-level scale factor then obtained by GetScaleFactor(), cannot be called more than once per event (if needed, then first refill again all lepton info with AddElectron()/AddMuon())
	- you need to provide the random run number and whether you're running on full-sim or fast-sim (electron scale factors are different)
	- example:
		if(in.IsMC() && (in.Etmiss_TST_Et<250000 || !in.HLT_xe70))
		{
			for(int iel : vars.electrons)
				dtwTool.AddElectron(in.El_pT[iel],in.El_eta[iel],in.RunNb,in.IsFullSim);
			for(int imu : vars.muons)
				dtwTool.AddMuon(in.Mu_pT[imu],in.Mu_eta[imu],in.Mu_phi[imu],In.RunNb);
			double uncertainty;
			out.triggerWgt = dtwTool.GetScaleFactor(uncertainty);
		}
		else out.triggerWgt = 1.;
	
	Efficiencies / scale factors
	------------------------------------
	- efficiencies and/or scale factors and their uncertainties have been dumped from the CP tools
	
	More info:
	----------
	- scale factor is only valid for the SS/3L non-trivial trigger strategy (https://cds.cern.ch/record/2151944)
		- events selected by a logical "OR" (2e12_lhloose || e17_lhloose_mu14 || mu18_mu8noL1) [2015 config] 
		  or (2e18_lhvloose || e17_lhloose_nod0_mu14 || mu20_mu8noL1) [2016 config] regardless of the channel classification of the event
		- trigger matching performed only with leptons with pT>20 GeV, except mu18_mu8noL1 (2015) or mu20_mu8noL1 (2016)
		  which requires respectively the matching of a pair (>20 GeV,>10 GeV) and (>21 GeV,>10 GeV)
	- scale factor computation assumes that an electron firing e17_lhloose always fires e12_lhloose, and same for other triggers
	- scale factor computation assumes uncorrelated branches in the dilepton triggers
	- for events with >=5 leptons a trigger efficiency of 100% (hence a scale factor of 1) is assumed for simplicity
	- uncertainties on the scale factors for e12 and e17 are treated as correlated (same for mu14 and mu18)
*/

class DileptonTriggerWeight
{
public:
	DileptonTriggerWeight();
	~DileptonTriggerWeight() {}
	void AddElectron(double pt_in_mev, double eta,int runnumber,bool fullsim); 
	void AddMuon(double pt_in_mev, double eta, double phi,int runnumber);
	void Reset();
	//	double GetScaleFactor();
	void GetScaleFactor();
	double GetScaleFactor(double& uncertainty);
	
protected:
	int m_elN;
	int m_muN;
	int m_mu20N;
	int m_mu2XN;
	double m_e12[4][6];
	double m_e17[4][6];
	double m_mu14[4][6];
	double m_mu18[4][6];
	double m_mu8noL1[4][6];
	bool m_reset;
};
