/*
 * myevt_n.hh
 *
 *  Created on: May 7, 2009
 *  Author: Alexander Paramonov
 *  paramon@hep.uchicago.edu
 */

//Blocks: myevt
#ifndef MYEVT_N_HH_
#define MYEVT_N_HH_

//_____________________________________________________________________________
const Int_t MAXJETS = 100;
const Int_t MAXLEPT = 25;
const Int_t MAXVTX = 60;
const Int_t MAXHEPG = 500;
const Int_t MAXPART = 200;
const Int_t MAXSTABLE = 1000;
const Int_t MAXCLUSTER = 2000;

//_____________________________________________________________________________
struct true_jet {
	Int_t n;

	//--------------------
	Float_t phi[MAXJETS]; //[n]
	Float_t eta[MAXJETS]; //[n]
	Float_t pt[MAXJETS]; //[n]
	Float_t px[MAXJETS]; //[n]
	Float_t py[MAXJETS]; //[n]
	Float_t pz[MAXJETS]; //[n]
	Float_t E[MAXJETS]; //[n]
	Float_t m[MAXJETS]; //[n]
	Float_t charge[MAXJETS]; //[n]

	Int_t flavor_truth_label[MAXJETS]; //[n]
	Float_t flavor_truth_dRminToB[MAXJETS]; //[n]
	Float_t flavor_truth_dRminToC[MAXJETS]; //[n]
	Float_t flavor_truth_dRminToT[MAXJETS]; //[n]
	Int_t flavor_truth_BHadronpdg[MAXJETS]; //[n]
	Float_t flavor_truth_vx_x[MAXJETS]; //[n]
	Float_t flavor_truth_vx_y[MAXJETS]; //[n]
	Float_t flavor_truth_vx_z[MAXJETS]; //[n]
//--------------------
};

typedef struct true_jet trueJet;

//_____________________________________________________________________________
struct calo_jet {
	Int_t n;

	//--------------------
	Float_t phi[MAXJETS]; //[n]
	Float_t eta[MAXJETS]; //[n]
	Float_t E[MAXJETS]; //[n]
	Float_t m[MAXJETS]; //[n]
	Float_t pt[MAXJETS]; //[n]
	Float_t px[MAXJETS]; //[n]
	Float_t py[MAXJETS]; //[n]
	Float_t pz[MAXJETS]; //[n]

	Float_t emscale_phi[MAXJETS]; //[n]
	Float_t emscale_eta[MAXJETS]; //[n]
	Float_t emscale_E[MAXJETS]; //[n]
	Float_t emscale_m[MAXJETS]; //[n]
	Float_t emscale_pt[MAXJETS]; //[n]
	Float_t emscale_px[MAXJETS]; //[n]
	Float_t emscale_py[MAXJETS]; //[n]
	Float_t emscale_pz[MAXJETS]; //[n]

	Float_t constscale_E[MAXJETS]; //[n]
	Float_t constscale_pt[MAXJETS]; //[n]
	Float_t constscale_m[MAXJETS]; //[n]
	Float_t constscale_eta[MAXJETS]; //[n]
	Float_t constscale_phi[MAXJETS]; //[n]

	Float_t ActiveAreaPx[MAXJETS]; //[n]
	Float_t ActiveAreaPy[MAXJETS]; //[n]
	Float_t ActiveAreaPz[MAXJETS]; //[n]
	Float_t ActiveAreaE[MAXJETS]; //[n]

	Float_t hecf[MAXJETS]; //[n]
	Float_t timing[MAXJETS]; //[n]
	Float_t quality[MAXJETS]; //[n]
	Float_t emfrac[MAXJETS]; //[n]
	Float_t n90[MAXJETS]; //[n]
	Float_t tgap3f[MAXJETS]; //[n]
	Float_t BCH_CORR_CELL[MAXJETS]; //[n]
	Float_t BCH_CORR_JET[MAXJETS]; //[n]
	Float_t BCH_CORR_DOTX[MAXJETS]; //[n]

	//JET ENERGY scale
	Float_t GCWJES[MAXJETS]; //[n]
	Float_t GCWJES_EtaCorr[MAXJETS]; //[n]
	Float_t EMJES[MAXJETS]; //[n]
	Float_t EMJES_EtaCorr[MAXJETS]; //[n]
	Float_t EMJESnooffset[MAXJETS]; //[n]
	Float_t Offset[MAXJETS]; //[n]

	// JVF
	Float_t jvtxf[MAXJETS]; //[n]
	Float_t jvtx_x[MAXJETS]; //[n]
	Float_t jvtx_y[MAXJETS]; //[n]
	Float_t jvtx_z[MAXJETS]; //[n]

	// Origin/vertex
	Float_t OriginIndex[MAXJETS]; //[n]
	Float_t nTrk[MAXJETS]; //[n]
	Float_t sumPtTrk[MAXJETS]; //[n]

	// Jet Quality
	Int_t isUgly[MAXJETS]; //[n]
	Int_t isBadLoose[MAXJETS]; //[n]
	Int_t isBadTight[MAXJETS]; //[n]

	Float_t fracSamplingMax[MAXJETS]; //[n]
	Float_t SamplingMax[MAXJETS]; //[n]

	Float_t LArQuality[MAXJETS]; //[n]
	Float_t HECQuality[MAXJETS]; //[n]
	Float_t NegativeE[MAXJETS]; //[n]
	Float_t AverageLArQF[MAXJETS]; //[n]

	Float_t EtaOrigin[MAXJETS]; //[n]
	Float_t PhiOrigin[MAXJETS]; //[n]
	Float_t MOrigin[MAXJETS]; //[n]
	Float_t EtaOriginEM[MAXJETS]; //[n]
	Float_t PhiOriginEM[MAXJETS]; //[n]
	Float_t MOriginEM[MAXJETS]; //[n]

	Int_t flavor_truth_label[MAXJETS]; //[n]
	Float_t flavor_weight_MV1[MAXJETS]; //[n]

	Float_t MET_Egamma10NoTau_STVF_wpx[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_STVF_wpy[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_STVF_wet[MAXJETS]; //[n]
	Int_t MET_Egamma10NoTau_STVF_statusWord[MAXJETS]; //[n]

	Float_t MET_Egamma10NoTau_STVF_wpx2[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_STVF_wpy2[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_STVF_wet2[MAXJETS]; //[n]
	Int_t MET_Egamma10NoTau_STVF_statusWord2[MAXJETS]; //[n]

	Float_t MET_Egamma10NoTau_STVF_wpx3[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_STVF_wpy3[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_STVF_wet3[MAXJETS]; //[n]
	Int_t MET_Egamma10NoTau_STVF_statusWord3[MAXJETS]; //[n]

	Float_t MET_Egamma10NoTau_wpx[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_wpy[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_wet[MAXJETS]; //[n]
	Int_t MET_Egamma10NoTau_statusWord[MAXJETS]; //[n]

	Float_t MET_Egamma10NoTau_wpx2[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_wpy2[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_wet2[MAXJETS]; //[n]
	Int_t MET_Egamma10NoTau_statusWord2[MAXJETS]; //[n]

	Float_t MET_Egamma10NoTau_wpx3[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_wpy3[MAXJETS]; //[n]
	Float_t MET_Egamma10NoTau_wet3[MAXJETS]; //[n]
	Int_t MET_Egamma10NoTau_statusWord3[MAXJETS]; //[n]

//--------------------
};

typedef struct calo_jet calJet;

//_____________________________________________________________________________
//This is the format used to store the reduced ntuple
struct my_event {

	//General Info
	Int_t runNumber;
	Int_t eventNumber;
	Int_t lumiBlock;
	Int_t bcid;
	Float_t weight;
	Bool_t isMC;
	Int_t larError;
	Int_t tileError;
	Int_t coreFlags;
	Int_t top_hfor_type;
	Int_t mc_channel_number;
	Float_t Eventshape_rhoKt4LC;

	//New Pileup re-weighting
	Float_t averageIntPerXing;
	Float_t actualIntPerXing;

	//MC generator info.
	Int_t mcevt_n;
	Int_t mcevt_signal_process_id[MAXVTX]; //[mcevt_n]
	Int_t mcevt_event_number[MAXVTX]; //[mcevt_n]
	Float_t mcevt_event_scale[MAXVTX]; //[mcevt_n]
	Int_t mcevt_pdf_id1[MAXVTX]; //[mcevt_n]
	Int_t mcevt_pdf_id2[MAXVTX]; //[mcevt_n]
	Float_t mcevt_pdf_x1[MAXVTX]; //[mcevt_n]
	Float_t mcevt_pdf_x2[MAXVTX]; //[mcevt_n]
	Float_t mcevt_weight[MAXVTX]; //[mcevt_n]

	//Primary Vertex info
	Int_t vxp_n;
	Float_t vxp_vertx[MAXVTX]; //[vxp_n]
	Float_t vxp_verty[MAXVTX]; //[vxp_n]
	Float_t vxp_vertz[MAXVTX]; //[vxp_n]
	Int_t vxp_vertNtrk[MAXVTX]; //[vxp_n]
	Float_t vxp_vertSumPt[MAXVTX]; //[vxp_n]

	//Egamma10NoTau_MetRefFinal
	Float_t MET_Egamma10NoTau_RefFinal_etx;
	Float_t MET_Egamma10NoTau_RefFinal_ety;
	Float_t MET_Egamma10NoTau_RefFinal_sumet;

	Float_t MET_Egamma10NoTau_RefGamma_etx;
	Float_t MET_Egamma10NoTau_RefGamma_ety;
	Float_t MET_Egamma10NoTau_RefGamma_sumet;

	Float_t MET_Egamma10NoTau_CellOut_etx;
	Float_t MET_Egamma10NoTau_CellOut_ety;
	Float_t MET_Egamma10NoTau_CellOut_sumet;

	Float_t MET_Egamma10NoTau_CellOut_Eflow_etx;
	Float_t MET_Egamma10NoTau_CellOut_Eflow_ety;
	Float_t MET_Egamma10NoTau_CellOut_Eflow_sumet;

	Float_t MET_Egamma10NoTau_CellOut_Eflow_STVF_etx;
	Float_t MET_Egamma10NoTau_CellOut_Eflow_STVF_ety;
	Float_t MET_Egamma10NoTau_CellOut_Eflow_STVF_sumet;

	//MET_Egamma10NoTau_STVF
	Float_t MET_Egamma10NoTau_STVF_RefFinal_etx;
	Float_t MET_Egamma10NoTau_STVF_RefFinal_ety;
	Float_t MET_Egamma10NoTau_STVF_RefFinal_sumet;

	Float_t MET_Egamma10NoTau_STVF_RefGamma_etx;
	Float_t MET_Egamma10NoTau_STVF_RefGamma_ety;
	Float_t MET_Egamma10NoTau_STVF_RefGamma_sumet;

	Float_t MET_Egamma10NoTau_STVF_CellOut_etx;
	Float_t MET_Egamma10NoTau_STVF_CellOut_ety;
	Float_t MET_Egamma10NoTau_STVF_CellOut_sumet;

	Float_t MET_Egamma10NoTau_STVF_CellOut_Track_etx;
	Float_t MET_Egamma10NoTau_STVF_CellOut_Track_ety;
	Float_t MET_Egamma10NoTau_STVF_CellOut_Track_sumet;

	Float_t MET_Egamma10NoTau_STVF_CellOut_TrackPV_etx;
	Float_t MET_Egamma10NoTau_STVF_CellOut_TrackPV_ety;
	Float_t MET_Egamma10NoTau_STVF_CellOut_TrackPV_sumet;

	Float_t MET_Egamma10NoTau_STVF_SoftJets_etx;
	Float_t MET_Egamma10NoTau_STVF_SoftJets_ety;
	Float_t MET_Egamma10NoTau_STVF_SoftJets_sumet;

	Float_t MET_LocHadTopo_etx;
	Float_t MET_LocHadTopo_ety;
	Float_t MET_LocHadTopo_sumet;

	//electrons
	Int_t el_n;
	Float_t el_E[MAXLEPT]; //[el_n]
	Float_t el_Et[MAXLEPT]; //[el_n]
	Float_t el_pt[MAXLEPT]; //[el_n]
	Float_t el_m[MAXLEPT]; //[el_n]
	Float_t el_eta[MAXLEPT]; //[el_n]
	Float_t el_phi[MAXLEPT]; //[el_n]
	Float_t el_px[MAXLEPT]; //[el_n]
	Float_t el_py[MAXLEPT]; //[el_n]
	Float_t el_pz[MAXLEPT]; //[el_n]
	Float_t el_charge[MAXLEPT]; //[el_n]
	Int_t el_author[MAXLEPT]; //[el_n]
	Int_t el_isEM[MAXLEPT]; //[el_n]
	Int_t el_convFlag[MAXLEPT]; //[el_n]
	Int_t el_isConv[MAXLEPT]; //[el_n]
	Int_t el_type[MAXLEPT]; //[el_n]
	Int_t el_origin[MAXLEPT]; //[el_n]
	Int_t el_typebkg[MAXLEPT]; //[el_n]
	Int_t el_originbkg[MAXLEPT]; //[el_n]
	Int_t el_OQ[MAXLEPT]; //[el_n]

	Int_t el_isfake[MAXLEPT]; //[el_n]
	Int_t el_ischmisid[MAXLEPT]; //[el_n]

	Int_t el_loosePP[MAXLEPT]; //[el_n]
	Int_t el_mediumPP[MAXLEPT]; //[el_n]
	Int_t el_tightPP[MAXLEPT]; //[el_n]

	Float_t el_weta2[MAXLEPT]; //[el_n]
	Float_t el_expectHitInBLayer[MAXLEPT]; //[el_n]
	Float_t el_reta[MAXLEPT]; //[el_n]
	Float_t el_rphi[MAXLEPT]; //[el_n]
	Float_t el_etap[MAXLEPT]; //[el_n]
	Float_t el_Etcone20[MAXLEPT]; //[el_n]
	Float_t el_Etcone30[MAXLEPT]; //[el_n]
	Float_t el_Etcone40[MAXLEPT]; //[el_n]
	Float_t el_Etcone45[MAXLEPT]; //[el_n]
	Float_t el_ptcone20[MAXLEPT]; //[el_n]
	Float_t el_ptcone30[MAXLEPT]; //[el_n]
	Float_t el_ptcone40[MAXLEPT]; //[el_n]
	Float_t el_nucone20[MAXLEPT]; //[el_n]
	Float_t el_nucone30[MAXLEPT]; //[el_n]
	Float_t el_nucone40[MAXLEPT]; //[el_n]
	Float_t el_Etcone40_corrected[MAXLEPT]; //[el_n]
	Float_t el_Etcone40_ED_corrected[MAXLEPT]; //[el_n]

	Float_t el_cl_E[MAXLEPT]; //[el_n]
	Float_t el_cl_pt[MAXLEPT]; //[el_n]
	Float_t el_cl_eta[MAXLEPT]; //[el_n]
	Float_t el_cl_phi[MAXLEPT]; //[el_n]
	Float_t el_trackd0[MAXLEPT]; //[el_n]
	Float_t el_trackz0[MAXLEPT]; //[el_n]
	Float_t el_tracktheta[MAXLEPT]; //[el_n]
	Float_t el_trackphi[MAXLEPT]; //[el_n]
	Float_t el_trackpt[MAXLEPT]; //[el_n]
	Float_t el_tracketa[MAXLEPT]; //[el_n]

	Float_t el_trackd0pv[MAXLEPT]; //[el_n]
	Float_t el_tracksigd0pv[MAXLEPT]; //[el_n]
	Float_t el_trackz0pv[MAXLEPT]; //[el_n]
	Float_t el_tracksigz0pv[MAXLEPT]; //[el_n]

	Int_t el_nBLHits[MAXLEPT]; //[el_n]
	Int_t el_nPixHits[MAXLEPT]; //[el_n]
	Int_t el_nSCTHits[MAXLEPT]; //[el_n]
	Int_t el_nTRTHits[MAXLEPT]; //[el_n]
	Int_t el_nTRTHighTHits[MAXLEPT]; //[el_n]
	Int_t el_nTRTOutliers[MAXLEPT]; //[el_n]
	Int_t el_nTRTHighTOutliers[MAXLEPT]; //[el_n]
	Int_t el_nPixHoles[MAXLEPT]; //[el_n]
	Int_t el_nSCTHoles[MAXLEPT]; //[el_n]
	Int_t el_hastrack[MAXLEPT]; //[el_n]
	Float_t el_trackd0beam[MAXLEPT]; //[el_n]

	//Electron ID variables
	Float_t el_etas2[MAXLEPT]; //[el_n]
	Float_t el_phis2[MAXLEPT]; //[el_n]
	Float_t el_Ethad[MAXLEPT]; //[el_n]
	Float_t el_f1[MAXLEPT]; //[el_n]
	Float_t el_f1core[MAXLEPT]; //[el_n]
	Float_t el_f3[MAXLEPT]; //[el_n]
	Float_t el_f3core[MAXLEPT]; //[el_n]
	Float_t el_E233[MAXLEPT]; //[el_n]
	Float_t el_E237[MAXLEPT]; //[el_n]
	Float_t el_E277[MAXLEPT]; //[el_n]
	Float_t el_Rconv[MAXLEPT]; //[el_n]
	Float_t el_zconv[MAXLEPT]; //[el_n]
	Float_t el_deltaEs[MAXLEPT]; //[el_n]
	Float_t el_wstot[MAXLEPT]; //[el_n]
	Float_t el_ws3[MAXLEPT]; //[el_n]
	Float_t el_fside[MAXLEPT]; //[el_n]
	Float_t el_Emax2[MAXLEPT]; //[el_n]
	Float_t el_MET_Egamma10NoTau_STVF_wpx[MAXLEPT]; //[el_n]
	Float_t el_MET_Egamma10NoTau_STVF_wpy[MAXLEPT]; //[el_n]
	Float_t el_MET_Egamma10NoTau_STVF_wet[MAXLEPT]; //[el_n]
	Int_t el_MET_Egamma10NoTau_STVF_statusWord[MAXLEPT]; //[el_n]

	Float_t el_MET_Egamma10NoTau_wpx[MAXLEPT]; //[el_n]
	Float_t el_MET_Egamma10NoTau_wpy[MAXLEPT]; //[el_n]
	Float_t el_MET_Egamma10NoTau_wet[MAXLEPT]; //[el_n]
	Int_t el_MET_Egamma10NoTau_statusWord[MAXLEPT]; //[el_n]

	Float_t el_Ethad1[MAXLEPT]; //[el_n]
	Float_t el_emaxs1[MAXLEPT]; //[el_n]
	Float_t el_deltaeta1[MAXLEPT]; //[el_n]
	Float_t el_trackd0_physics[MAXLEPT]; //[el_n]
	Float_t el_TRTHighTOutliersRatio[MAXLEPT]; //[el_n]
	Float_t el_nSiHits[MAXLEPT]; //[el_n]
	Float_t el_nSCTOutliers[MAXLEPT]; //[el_n]
	Float_t el_nPixelOutliers[MAXLEPT]; //[el_n]
	Float_t el_nBLayerOutliers[MAXLEPT]; //[el_n]
	Float_t el_trackqoverp[MAXLEPT]; //[el_n]
	Float_t el_deltaphi2[MAXLEPT]; //[el_n]

	Float_t el_Es0[MAXLEPT]; //[el_n]
	Float_t el_Es1[MAXLEPT]; //[el_n]
	Float_t el_Es2[MAXLEPT]; //[el_n]
	Float_t el_Es3[MAXLEPT]; //[el_n]

	Float_t el_topoEtcone20_corrected[MAXLEPT]; //[el_n]
	Float_t el_topoEtcone30_corrected[MAXLEPT]; //[el_n]
	Float_t el_topoEtcone40_corrected[MAXLEPT]; //[el_n]

	Float_t el_trackIPEstimate_d0_unbiasedpvunbiased[MAXLEPT]; //[el_n]
	Float_t el_trackIPEstimate_sigd0_unbiasedpvunbiased[MAXLEPT]; //[el_n]
	Float_t el_trackIPEstimate_z0_unbiasedpvunbiased[MAXLEPT]; //[el_n]
	Float_t el_trackIPEstimate_sigz0_unbiasedpvunbiased[MAXLEPT]; //[el_n]

	//STACO Muons
	Int_t mu_staco_n;
	Float_t mu_staco_E[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_pt[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_m[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_eta[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_phi[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_px[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_py[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_pz[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_charge[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_author[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_matchchi2[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_matchndof[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_etcone20[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_etcone30[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_etcone40[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_ptcone20[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_ptcone30[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_ptcone40[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_energyLossPar[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_energyLossErr[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_bestMatch[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_isStandAloneMuon[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_isCombinedMuon[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_isSegmentTaggedMuon[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_isLowPtReconstructedMuon[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_loose[MAXLEPT]; //[mu_staco_n]

	Int_t mu_staco_isfake[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_ischmisid[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_truth_barcode[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_d0_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_z0_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_phi_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_theta_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_qoverp_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_cov_qoverp_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_cov_d0_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_cov_z0_exPV[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_ms_d0[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_ms_z0[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_ms_phi[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_ms_theta[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_ms_qoverp[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_id_d0[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_z0[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_phi[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_theta[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_qoverp[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_id_d0_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_z0_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_phi_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_theta_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_qoverp_exPV[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_id_cov_d0_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_cov_z0_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_cov_phi_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_cov_theta_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_id_cov_qoverp_exPV[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_me_d0[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_me_z0[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_me_phi[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_me_theta[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_me_qoverp[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_me_d0_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_me_z0_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_me_phi_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_me_theta_exPV[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_me_qoverp_exPV[MAXLEPT]; //[mu_staco_n]

	Int_t mu_staco_nBLHits[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nPixHits[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nSctHits[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nTrtHits[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nBLSharedHits[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nPixSharedHits[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nPixHoles[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nSCTSharedHits[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nSCTHoles[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nTRTHighTHits[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nTRTOutliers[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nTRTHighTOutliers[MAXLEPT]; //[mu_staco_n]

	Int_t mu_staco_expectBLayerHit[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nPixelDeadSensors[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_nSCTDeadSensors[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_trackd0[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_trackz0[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_tracktheta[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_trackphi[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_hastrack[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_ptcone20_trkelstyle[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_ptcone30_trkelstyle[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_ptcone40_trkelstyle[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_trackIPEstimate_d0_unbiasedpvunbiased[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_trackIPEstimate_z0_unbiasedpvunbiased[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_trackIPEstimate_sigz0_unbiasedpvunbiased[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_MET_Egamma10NoTau_STVF_wpx1[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_MET_Egamma10NoTau_STVF_wpy1[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_MET_Egamma10NoTau_STVF_wet1[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_MET_Egamma10NoTau_STVF_statusWord1[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_MET_Egamma10NoTau_STVF_wpx2[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_MET_Egamma10NoTau_STVF_wpy2[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_MET_Egamma10NoTau_STVF_wet2[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_MET_Egamma10NoTau_STVF_statusWord2[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_MET_Egamma10NoTau_wpx1[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_MET_Egamma10NoTau_wpy1[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_MET_Egamma10NoTau_wet1[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_MET_Egamma10NoTau_statusWord1[MAXLEPT]; //[mu_staco_n]

	Float_t mu_staco_MET_Egamma10NoTau_wpx2[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_MET_Egamma10NoTau_wpy2[MAXLEPT]; //[mu_staco_n]
	Float_t mu_staco_MET_Egamma10NoTau_wet2[MAXLEPT]; //[mu_staco_n]
	Int_t mu_staco_MET_Egamma10NoTau_statusWord2[MAXLEPT]; //[mu_staco_n]

	Int_t muonTruth_n;
	Float_t muonTruth_pt[MAXLEPT]; //[muonTruth_n]
	Float_t muonTruth_m[MAXLEPT]; //[muonTruth_n]
	Float_t muonTruth_eta[MAXLEPT]; //[muonTruth_n]
	Float_t muonTruth_phi[MAXLEPT]; //[muonTruth_n]
	Float_t muonTruth_charge[MAXLEPT]; //[muonTruth_n]
	Int_t muonTruth_PDGID[MAXLEPT]; //[muonTruth_n]
	Int_t muonTruth_barcode[MAXLEPT]; //[muonTruth_n]
	Int_t muonTruth_type[MAXLEPT]; //[muonTruth_n]
	Int_t muonTruth_origin[MAXLEPT]; //[muonTruth_n]

	//stable particles
	Int_t mc_n;
	Float_t mc_pt[MAXSTABLE]; //[mc_n]
	Float_t mc_m[MAXSTABLE]; //[mc_n]
	Float_t mc_eta[MAXSTABLE]; //[mc_n]
	Float_t mc_phi[MAXSTABLE]; //[mc_n]
	Int_t mc_pdgId[MAXSTABLE]; //[mc_n]
	Float_t mc_charge[MAXSTABLE]; //[mc_n]
	Int_t mc_status[MAXSTABLE]; //[mc_n]
	Int_t mc_parent_index1[MAXSTABLE]; //[mc_n]
	Int_t mc_parent_index2[MAXSTABLE]; //[mc_n]
	Int_t mc_child_index1[MAXSTABLE]; //[mc_n]
	Int_t mc_child_index2[MAXSTABLE]; //[mc_n]
	Int_t mc_parents1[MAXSTABLE]; //[mc_n]
	Int_t mc_parents2[MAXSTABLE]; //[mc_n]
	Int_t mc_children1[MAXSTABLE]; //[mc_n]
	Int_t mc_children2[MAXSTABLE]; //[mc_n]
	Int_t mc_barcode[MAXSTABLE]; //[mc_n]
	Int_t mc_index[MAXSTABLE]; //[mc_n]

	//parton level
	Int_t parton_n;
	Float_t parton_pt[MAXPART]; //[parton_n]
	Float_t parton_m[MAXPART]; //[parton_n]
	Float_t parton_eta[MAXPART]; //[parton_n]
	Float_t parton_phi[MAXPART]; //[parton_n]
	Int_t parton_pdgId[MAXPART]; //[parton_n]
	Float_t parton_charge[MAXPART]; //[parton_n]
	Int_t parton_status[MAXSTABLE]; //[parton_n]
	Int_t parton_parent_index1[MAXSTABLE]; //[parton_n]
	Int_t parton_parent_index2[MAXSTABLE]; //[parton_n]
	Int_t parton_child_index1[MAXSTABLE]; //[parton_n]
	Int_t parton_child_index2[MAXSTABLE]; //[parton_n]
	Int_t parton_parents1[MAXSTABLE]; //[parton_n]
	Int_t parton_parents2[MAXSTABLE]; //[parton_n]
	Int_t parton_children1[MAXSTABLE]; //[parton_n]
	Int_t parton_children2[MAXSTABLE]; //[parton_n]
	Int_t parton_barcode[MAXSTABLE]; //[parton_n]
	Int_t parton_index[MAXSTABLE]; //[parton_n]

	//Single-lepton triggers
	Bool_t EF_e24vhi_medium1;
	Bool_t EF_e60_medium1;
	Bool_t EF_mu24i_tight;
	Bool_t EF_mu36_tight;

	//Lepton+MET
	Bool_t EF_mu24_j65_a4tchad_EFxe40_tclcw;
	Bool_t EF_e24vh_medium1_EFxe35_tclcw;

	//Dilepton triggers
	Bool_t EF_2e12Tvh_loose1;
	Bool_t EF_2mu13;
	Bool_t EF_mu18_tight_mu8_EFFS;
	Bool_t EF_e12Tvh_medium1_mu10;
	Bool_t EF_e24vhi_loose1_mu8;
	Bool_t EF_e24vh_medium1_e7_medium1;
	Bool_t EF_e12Tvh_medium1_mu8;
	Bool_t EF_mu18_tight_e7_medium1;

	//MET Triggers
	Bool_t EF_xe80T_tclcw_loose;
	Bool_t EF_xe80_tclcw_loose;

	//trigger matching
	Int_t trig_EF_el_n;
	Float_t trig_EF_el_eta[MAXLEPT]; //[trig_EF_el_n]
	Float_t trig_EF_el_phi[MAXLEPT]; //[trig_EF_el_n]
	Int_t trig_EF_el_EF_2e12Tvh_loose1[MAXLEPT]; //[trig_EF_el_n]
	Int_t trig_EF_el_EF_e60_medium1[MAXLEPT]; //[trig_EF_el_n]
	Int_t trig_EF_el_EF_e12Tvh_medium1_mu8[MAXLEPT]; //[trig_EF_el_n]

	Int_t trig_EF_trigmuonef_n;
	Float_t trig_EF_trigmuonef_track_CB_eta[MAXLEPT]; //[trig_EF_trigmuonef_n]
	Float_t trig_EF_trigmuonef_track_CB_phi[MAXLEPT]; //[trig_EF_trigmuonef_n]
	Int_t trig_EF_trigmuonef_track_CB_hasCB[MAXLEPT]; //[trig_EF_trigmuonef_n]
	Int_t trig_EF_trigmuonef_EF_mu36_tight[MAXLEPT]; //[trig_EF_trigmuonef_n]
	Int_t trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS[MAXLEPT]; //[trig_EF_trigmuonef_n]
	Int_t trig_EF_trigmuonef_EF_mu8[MAXLEPT]; //[trig_EF_trigmuonef_n]
	Int_t trig_EF_trigmuonef_EF_mu18_tight[MAXLEPT]; //[trig_EF_trigmuonef_n]

	calJet AntiKt4LCTopo;

	trueJet AntiKt4Truth;

};

typedef struct my_event myevt;

#endif /* MYEVT_N_HH_ */
