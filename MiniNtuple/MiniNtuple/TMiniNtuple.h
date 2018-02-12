//////////////////////////////////////////////////////////
// Author:      Othmane Rifki
// Contact:     othmane.rifki@cern.ch
// Description: MiniNtuple from Ximo AnaNtup
// Date 2016-07-11 07:29:16
//////////////////////////////////////////////////////////

#include "TTree.h"
#ifndef MININTUPLE_HH_
#define MININTUPLE_HH_

#include "GaudiKernel/ToolHandle.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/Property.h"
#include "CLHEP/Units/SystemOfUnits.h"


#include <string>
#include <vector>
#include <stdlib.h>

#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"

#include <MiniNtuple/myevt.h>
#include <MiniNtuple/OldNtpBranches.h>
#include "MiniNtuple/JetQuarkLabelD3PD.h"
#include "MiniNtuple/RecoTruthMatch.h"

//_____________________________________________________________

//memory management constants
const int basket_size = 256 * 1024; // basket size

//---------------------------------------------------------------------------------------
class TMiniNtuple: public Algorithm {

protected:

	// The struct stores the reduced event information
	myevt* evt;
	TFile* outputRootFile;
	TBranch	*b;
	TTree* t_MiniNtuple; //output Tree
	bool is_truth;
	std::vector<std::string> inpName;


	//D3PD
	TChain* t_inpNtuple;
	OldNtpBranches *oldTree; //stores D3PD variables
	std::string ntpName;


	bool debug;
	bool m_applyLeptonSkim;
	double m_minLeptonPt; 
	TH1D * m_h_events_raw;
	TH1D * m_h_events;
	TH1D * m_h_events_sq;

public:

	TMiniNtuple(const std::string &name, ISvcLocator *pSvcLocator);
	~TMiniNtuple();

	StatusCode initialize();
	StatusCode execute();
	StatusCode finalize();

	// ****** other methods
	void InitNtpVar(myevt *ev); // initialize all the ntp variables
	void SetNewNtpBranches();
	void SetOldNtpBranches();

	// Service functions
	// These are executed for each event to fill the reduced ntuple
	// Each method assumes that the corresponding STNtuple block exists

	//we recalculate the number of tracks in a jet using track quality cuts

	float deltaR(float eta1, float phi1, float eta2, float phi2);


};

#endif /* MININTUPLE_HH_ */
