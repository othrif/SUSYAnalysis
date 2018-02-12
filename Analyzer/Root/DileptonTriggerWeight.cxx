/*
	description: tool to compute the global trigger scale factor for the SUSY SS/3L+jets analysis
	contact: jmaurer@cern.ch
	version: 18/07/2016, evening
*/

#include "Analyzer/DileptonTriggerWeight.h"

#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;

namespace
{
	double efficiency_mc_2eX_anyelectron(double pt_in_gev, double eta, double& unc, int runnumber, bool fullsim);
	double scalefactor_2eX_anyelectron(double pt_in_gev, double eta, double& unc, int runnumber, bool fullsim);
	double efficiency_mc_eXmuY_electron(double pt_in_gev, double eta, double& unc, int runnumber, bool fullsim);
	double scalefactor_eXmuY_electron(double pt_in_gev, double eta, double& unc, int runnumber, bool fullsim);
	double efficiency_data_eXmuY_muon(double pt_in_gev, double eta, double& unc, int runnumber, bool fullsim);
	double efficiency_mc_eXmuY_muon(double eta, double phi, double& unc,int runnumber);
	double efficiency_data_muXmuY_leadmuon(double eta, double phi, double& unc,int runnumber);
	double efficiency_mc_muXmuY_leadmuon(double eta, double phi, double& unc,int runnumber);
	double efficiency_data_muXmuY_subleadmuon(double eta, double phi, double& unc,int runnumber);
	double efficiency_mc_muXmuY_subleadmuon(double eta, double phi, double& unc,int runnumber);
}
#include "DileptonTriggerWeightTables.hxx"

namespace
{
	double eff_mm(double z1, double w1, double z2, double w2);
	double eff_mmm(double z1, double w1, double z2, double w2, double z3, double w3);
	double eff_mmmm(double z1, double w1, double z2, double w2, double z3, double w3, double z4, double w4);
	double eff_em(double y1, double y2);
	double eff_emm(double y1, double y2, double z2, double w2, double y3, double z3, double w3);
	double eff_emmm(double y1, double y2, double z2, double w2, double y3, double z3, double w3, double y4, double z4, double w4);
	double eff_ee(double x1, double x2);
	double eff_eem(double x1, double y1, double x2, double y2, double y3);
	double eff_eemm(double x1, double y1, double x2, double y2, double y3, double z3, double w3, double y4, double z4, double w4);
	double eff_eee(double x1, double x2, double x3);
	double eff_eeem(double x1, double y1, double x2, double y2, double x3, double y3, double y4);
	double eff_eeee(double x1, double x2, double x3, double x4);
	
	template<class EffFunc, class...Effs>
	inline double scale_factor(double& unc, EffFunc& f, Effs... effs);
	
	enum
	{
		EFF_MC = 0,
		EFF_DATA,
		UNC_EFF_DATA_EL,
		UNC_EFF_DATA_MU,
		UNC_EFF_MC_EL,
		UNC_EFF_MC_MU
	};
	
	const int MAX_STORED = 4;
}

DileptonTriggerWeight::DileptonTriggerWeight()
{
	Reset();
}

//double DileptonTriggerWeight::GetScaleFactor()
void DileptonTriggerWeight::GetScaleFactor()
{
	double dummy;
	GetScaleFactor(dummy);
}

double DileptonTriggerWeight::GetScaleFactor(double& unc)
{
	if(m_reset)
	{
		cout<<"FATAL [DileptonTriggerWeight]: you must provide information about signal leptons first\n";
		throw;
	}
	int c;
	if(m_elN<2 && (m_mu20N<1 || m_elN<1) && (m_mu2XN<1 || m_muN<2))
	{
		cout<<"WARNING [DileptonTriggerWeight]: this event doesn't satisfy trigger requirements, returning SF=1\n";
		c = -1;
	}
	else c = 1000*m_elN+m_muN;
	Reset();
	switch(c)
	{
		case 2: // µµ
			return ::scale_factor(unc, ::eff_mm, m_mu18[0], m_mu8noL1[0], m_mu18[1], m_mu8noL1[1]);
		case 3: // µµµ
			return ::scale_factor(unc, ::eff_mmm, m_mu18[0], m_mu8noL1[0], m_mu18[1], m_mu8noL1[1], m_mu18[2], m_mu8noL1[2]);
		case 4: // µµµµ
			return ::scale_factor(unc, ::eff_mmmm, m_mu18[0], m_mu8noL1[0], m_mu18[1], m_mu8noL1[1], m_mu18[2], m_mu8noL1[2], m_mu18[3], m_mu8noL1[3]);
		case 1001: // eµ
			return ::scale_factor(unc, ::eff_em, m_e17[0], m_mu14[0]);
		case 1002: // eµµ
			return ::scale_factor(unc, ::eff_emm, m_e17[0], m_mu14[0], m_mu18[0], m_mu8noL1[0], m_mu14[1], m_mu18[1], m_mu8noL1[1]);
		case 1003: // eµµµ
			return ::scale_factor(unc, ::eff_emmm, m_e17[0], m_mu14[0], m_mu18[0], m_mu8noL1[0], m_mu14[1], m_mu18[1], m_mu8noL1[1], m_mu14[2], m_mu18[2], m_mu8noL1[2]);
		case 2000: // ee
			return ::scale_factor(unc, ::eff_ee, m_e12[0], m_e12[1]);
		case 2001: // eeµ
			return ::scale_factor(unc, ::eff_eem, m_e12[0], m_e17[0], m_e12[1], m_e17[1], m_mu14[0]);
		case 2002: // eeµµ
			return ::scale_factor(unc, ::eff_eemm, m_e12[0], m_e17[0], m_e12[1], m_e17[1], m_mu14[0], m_mu18[0], m_mu8noL1[0], m_mu14[1], m_mu18[1], m_mu8noL1[1]);
		case 3000: // eee
			return ::scale_factor(unc, ::eff_eee, m_e12[0], m_e12[1], m_e12[2]);
		case 3001: // eeeµ
			return ::scale_factor(unc, ::eff_eeem, m_e12[0], m_e17[0], m_e12[1], m_e17[1], m_e12[2], m_e17[2], m_mu14[0]);
		case 4000: // eeee
			return ::scale_factor(unc, ::eff_eeee, m_e12[0], m_e12[1], m_e12[2], m_e12[3]);
		default:; // many leptons... or problem encountered
	}
	unc = 0.;
	return 1.;
}

void DileptonTriggerWeight::AddElectron(double pt_in_mev, double eta, int runnumber, bool fullsim)
{
	if(pt_in_mev>=20000)
	{
		if(m_elN<::MAX_STORED)
		{
			double unc;
			m_e12[m_elN][::EFF_MC] = ::efficiency_mc_2eX_anyelectron(0.001*pt_in_mev,eta,unc,runnumber,fullsim);
			m_e12[m_elN][::UNC_EFF_MC_EL] = unc;
			m_e12[m_elN][::EFF_DATA] = ::scalefactor_2eX_anyelectron(0.001*pt_in_mev,eta,unc,runnumber,fullsim) * m_e12[m_elN][::EFF_MC];
			m_e12[m_elN][::UNC_EFF_DATA_EL] = unc * m_e12[m_elN][::EFF_MC];
			m_e12[m_elN][::UNC_EFF_MC_MU] = 0.;
			m_e12[m_elN][::UNC_EFF_DATA_MU] = 0.;
			m_e17[m_elN][::EFF_MC] = ::efficiency_mc_eXmuY_electron(0.001*pt_in_mev,eta,unc,runnumber,fullsim);
			m_e17[m_elN][::UNC_EFF_DATA_EL] = unc;
			m_e17[m_elN][::EFF_DATA] = ::scalefactor_eXmuY_electron(0.001*pt_in_mev,eta,unc,runnumber,fullsim) * m_e17[m_elN][::EFF_MC];
			m_e17[m_elN][::UNC_EFF_DATA_EL] = unc * m_e17[m_elN][::EFF_MC];
			m_e17[m_elN][::UNC_EFF_MC_MU] = 0.;
			m_e17[m_elN][::UNC_EFF_DATA_MU] = 0.;
			//cout<<"Added electron("<<pt_in_mev<<","<<eta<<"): "<<m_e12[m_elN][::EFF_MC]<<" "<<m_e12[m_elN][::EFF_DATA]<<" "<<m_e17[m_elN][::EFF_MC]<<" "<<m_e17[m_elN][::EFF_DATA]<<endl;
		}
		++m_elN;
	}
	m_reset = false;
}
	
void DileptonTriggerWeight::AddMuon(double pt_in_mev, double eta, double phi, int runnumber)
{
	if(pt_in_mev>=10000)
	{
		if(m_muN<::MAX_STORED)
		{
			if(pt_in_mev>=20000)
			{
				double unc;
				m_mu14[m_muN][::EFF_MC] = ::efficiency_mc_eXmuY_muon(eta,phi,unc,runnumber);
				m_mu14[m_muN][::UNC_EFF_MC_MU] = unc;
				m_mu14[m_muN][::EFF_DATA] = ::efficiency_data_eXmuY_muon(eta,phi,unc,runnumber);
				m_mu14[m_muN][::UNC_EFF_DATA_MU] = unc;
				m_mu14[m_muN][::UNC_EFF_MC_EL] = 0.;
				m_mu14[m_muN][::UNC_EFF_DATA_EL] = 0.;
				if(runnumber<290000 || pt_in_mev>21000.)
				{
					m_mu18[m_muN][::EFF_MC] = ::efficiency_mc_muXmuY_leadmuon(eta,phi,unc,runnumber);
					m_mu18[m_muN][::UNC_EFF_MC_MU] = unc;
					m_mu18[m_muN][::EFF_DATA] = ::efficiency_data_muXmuY_leadmuon(eta,phi,unc,runnumber);
					m_mu18[m_muN][::UNC_EFF_DATA_MU] = unc;
					m_mu18[m_muN][::UNC_EFF_MC_EL] = 0.;
					m_mu18[m_muN][::UNC_EFF_DATA_EL] = 0.;
				}
				else std::fill_n(m_mu18[m_muN],6,0.);
			}
			else
			{
				std::fill_n(m_mu14[m_muN],6,0.);
				std::fill_n(m_mu18[m_muN],6,0.);	
			}
			double unc;
			m_mu8noL1[m_muN][::EFF_MC] = ::efficiency_mc_muXmuY_subleadmuon(eta,phi,unc,runnumber);
			m_mu8noL1[m_muN][::UNC_EFF_MC_MU] = unc;
			m_mu8noL1[m_muN][::EFF_DATA] = ::efficiency_data_muXmuY_subleadmuon(eta,phi,unc,runnumber);
			m_mu8noL1[m_muN][::UNC_EFF_DATA_MU] = unc;
			m_mu8noL1[m_muN][::UNC_EFF_MC_EL] = 0.;
			m_mu8noL1[m_muN][::UNC_EFF_DATA_EL] = 0.;
			//cout<<"Added muon ("<<pt_in_mev<<","<<eta<<','<<phi<<"): "<<m_mu14[m_muN][::EFF_MC]<<" "<<m_mu14[m_muN][::EFF_DATA]<<" "<<m_mu18[m_muN][::EFF_MC]<<" "<<m_mu18[m_muN][::EFF_DATA]<<" "<<m_mu8noL1[m_muN][::EFF_MC]<<" "<<m_mu8noL1[m_muN][::EFF_DATA]<<endl;
		}
		if(pt_in_mev>=20000)
		{
			++m_mu20N;
			if(runnumber<290000 || pt_in_mev>21000.) ++m_mu2XN;
		}
		++m_muN;
	}
	m_reset = false;
}

void DileptonTriggerWeight::Reset()
{
	m_elN=0;
	m_muN = 0;
	m_mu20N = 0;
	m_mu2XN = 0;
	m_reset = true; 
}

namespace
{
	template<class EffFunc, class...Effs>
	inline double scale_factor(double& unc, EffFunc& f, Effs... effs)
	{
		double mc = f(effs[::EFF_MC]...);
		double sf = f(effs[::EFF_DATA]...) / mc;
		double err_data_el_up = f((effs[::EFF_DATA]+effs[::UNC_EFF_DATA_EL])...) / mc - sf;
		double err_data_mu_up = f((effs[::EFF_DATA]+effs[::UNC_EFF_DATA_MU])...) / mc - sf;
		double err_mc_el_up = f((effs[::EFF_DATA]+effs[::UNC_EFF_MC_EL])...) / mc - sf;
		double err_mc_mu_up = f((effs[::EFF_DATA]+effs[::UNC_EFF_MC_MU])...) / mc - sf;
		unc = sqrt(err_data_el_up*err_data_el_up + err_data_mu_up*err_data_mu_up
			+err_mc_el_up*err_mc_el_up + err_mc_mu_up*err_mc_mu_up);
		return sf;
	}
	
	double eff_mm(double z1, double w1, double z2, double w2)
	{
		//return z1 + (1- z1)*z2; // old, w/o mu8noL1
		return z1*w2 + w1*z2 - z1*z2;
	}

	double eff_mmm(double z1, double w1, double z2, double w2, double z3, double w3)
	{
		//return z1 + (1-z1)*(z2 + (1-z2)*z3); // old, w/o mu8noL1
		return z1*w2 + w1*z2 + z1*w3 + w1*z3 + z2*w3 + w2*z3 - z1*z2 - z1*w2*w3 - w1*z2*w3 - z1*z3 - w1*w2*z3 - z2*z3 + z1*z2*z3; 
	}
		
	double eff_mmmm(double z1, double w1, double z2, double w2, double z3, double w3, double z4, double w4)
	{
		//return z1 + (1-z1)*(z2 + (1-z2)*(z3 + (1-z3)*z4)); // old, w/o mu8noL1
		return z1*w2 + w1*z2 + z1*w3 + w1*z3 + z1*w4 + w1*z4 + z2*w3 + w2*z3 + z2*w4 + w2*z4 + z3*w4 + w3*z4 
			- z1*z2 - z1*w2*w3 - z1*w2*w4 - w1*z2*w3 - w1*z2*w4 - z1*z3 - z1*w3*w4 - w1*w2*z3 - w1*z3*w4 - z1*z4 
			- w1*w2*z4 - w1*w3*z4 - z2*z3 - z2*w3*w4 - w2*z3*w4 - z2*z4 - w2*w3*z4 - z3*z4 + z1*w2*w3*w4 + w1*z2*w3*w4 
			+ w1*w2*z3*w4 + w1*w2*w3*z4 + z1*z2*z3 + z1*z2*z4 + z1*z3*z4 + z2*z3*z4 - z1*z2*z3*z4;
	}

	double eff_em(double y1, double y2)
	{
		return y1*y2;
	}

	double eff_emm(double y1, double y2, double z2, double w2, double y3, double z3, double w3)
	{
		//return (1-y1)*(z2 + (1-z2)*z3) + y1*(y2 + (1-y2)*y3); // old, w/o mu8noL1
		return y1*y2 + y1*y3 + z2*w3 + w2*z3 - y1*y2*y3 - y1*z2*w3 - y1*w2*z3 - z2*z3 + y1*z2*z3;
	}

	double eff_emmm(double y1, double y2, double z2, double w2, double y3, double z3, double w3, double y4, double z4, double w4)
	{
		//return y1*(y2 + (1-y2)*(y3+(1-y3)*y4)) + (1-y1)*(z2 + (1-z2)*(z3+(1-z3)*z4)); // old, w/o mu8noL1
		return y1*y2 + y1*y3 + y1*y4 + z2*w3 + w2*z3 + z2*w4 + w2*z4 + z3*w4 + w3*z4 - y1*y2*y3 - y1*y2*y4 
			- y1*z2*w3 - y1*z2*w4 - y1*y3*y4 - y1*w2*z3 - y1*z3*w4 - y1*w2*z4 - y1*w3*z4 - z2*z3 - z2*w3*w4 
			- w2*z3*w4 - z2*z4 - w2*w3*z4 - z3*z4 + y1*y2*y3*y4 + y1*z2*w3*w4 + y1*z2*z3 + y1*w2*z3*w4 
			+ y1*z2*z4 + y1*w2*w3*z4 + y1*z3*z4 + z2*z3*z4 - y1*z2*z3*z4;
	}
		
	double eff_ee(double x1, double x2)
	{
		return x1*x2;
	}

	double eff_eem(double x1, double y1, double x2, double y2, double y3)
	{
		return x1*x2 + (1-x2)*y1*y3 + (1-x1)*y2*y3;
	}

	double eff_eemm(double x1, double y1, double x2, double y2, double y3, double z3, double w3, double y4, double z4, double w4)
	{
		//return x1*x2 + y1*y3 + y1*y4 + y2*y3 + y2*y4 + z3 + z4 - y1*x2*y3 - y1*x2*y4 - x1*y2*y3 - x1*y2*y4 	
		//- x1*x2*z3 - x1*x2*z4 - y1*y3*y4 - y1*z3 - y1*z4 - y2*y3*y4 - y2*z3 - y2*z4 - z3*z4 + y1*x2*y3*y4 
		//+ y1*x2*z3 + y1*x2*z4 + x1*y2*y3*y4 + x1*y2*z3 + x1*y2*z4 + x1*x2*z3*z4 + y1*z3*z4 + y2*z3*z4
		//- y1*x2*z3*z4 - x1*y2*z3*z4; // old, w/o mu8noL1
		return x1*x2 + y1*y3 + y1*y4 + y2*y3 + y2*y4 + z3*w4 + w3*z4 - y1*x2*y3 - y1*x2*y4 - x1*y2*y3 - x1*y2*y4 
			- x1*x2*z3*w4 - x1*x2*w3*z4 - y1*y3*y4 - y1*z3*w4 - y1*w3*z4 - y2*y3*y4 - y2*z3*w4 - y2*w3*z4 - z3*z4 
			+ y1*x2*y3*y4 + y1*x2*z3*w4 + y1*x2*w3*z4 + x1*y2*y3*y4 + x1*y2*z3*w4 + x1*y2*w3*z4 + x1*x2*z3*z4 
			+ y1*z3*z4 + y2*z3*z4 - y1*x2*z3*z4 - x1*y2*z3*z4;
	}

	double eff_eee(double x1, double x2, double x3)
	{
		return x1*x2 + (1-x1)*x2*x3 + (1-x2)*x3*x1;
	}

	double eff_eeem(double x1, double y1, double x2, double y2, double x3, double y3, double y4)
	{
		return x1*x2 + x1*x3 + x2*x3 + y1*y4 + y2*y4 + y3*y4 - x1*x2*x3 - y1*x2*y4 - x1*y2*y4 - x1*x2*x3
		- y1*x3*y4 - x1*y3*y4 - y2*x3*y4 - x2*y3*y4 + y1*x2*x3*y4 + x1*y2*x3*y4 + x1*x2*y3*y4;
	}

	double eff_eeee(double x1, double x2, double x3, double x4)
	{
		return x1*(x2 + (1-x2)*(x3 + (1-x3)*x4))+ (1-x1)*x2*(x3 + (1-x3)*x4) + (1-x1)*(1-x2)*x3*x4;
	}
}

/*

# 
# Python script to obtain formulas:
# 
	
import itertools

def generate(channel):
    ne = channel.count('e')
    nm = channel.count('m')
    triggers = []
    for i in range(ne):
        for j in range(i+1,ne):
            triggers.append('ee%d%d'%(i+1,j+1))
    for i in range(ne):
        for j in range(nm):
            triggers.append('em%d%d'%(i+1,j+1+ne))
    for i in range(nm):
        for j in range(i+1,nm):
            triggers.append('mm%d%d'%(i+1+ne,j+1+ne))
            triggers.append('mm%d%d'%(j+1+ne,i+1+ne)) # because mu18_mu8noL1 is asymmetric
    print 'Trigger combination : ',' | '.join(triggers)
    combinations = [itertools.combinations(triggers,n) for n in range(1,len(triggers)+1)]                
    lp = []
    for c in combinations:
        for x in c:
            e_ee = []
            e_em = []
            m_em = []
            m_mm1 = []
            m_mm2 = []
            for t in x:
                if t[:2]=='ee':
                    a,b = t[2:]
                    if a not in e_ee: e_ee.append(a)
                    if b not in e_ee: e_ee.append(b)
                elif t[:2]=='em':
                    a,b = t[2:]
                    if a not in e_em: e_em.append(a)
                    if b not in m_em: m_em.append(b)
                elif t[:2]=='mm':
                    a,b = t[2:]
                    if a not in m_mm1: m_mm1.append(a)
                    if b not in m_mm2: m_mm2.append(b)
            e_ee.sort()
            e_em.sort()
            m_em.sort()
            m_mm1.sort()
            m_mm2.sort()
            pp = ''
            tsb = ''
            for i in range(1,ne+1):
                if len(pp)>0: tsb = '*'
                if str(i) in e_em: pp += tsb+'y%d'%(i) # e17
                elif str(i) in e_ee:  pp += tsb+'x%d'%(i) # e12
            for i in range(ne+1,ne+nm+1):
                if len(pp)>0: tsb = '*'
                if str(i) in m_mm1: pp += tsb+'z%d'%(i) # mu18
                elif str(i) in m_em: pp += tsb+'y%d'%(i) # mu14
                elif str(i) in m_mm2: pp += tsb+'w%d'%(i) # mu8noL1
            if pp!='': lp.append((' + ' if len(x)%2==1 else ' - ')+pp)
    # cancel opposite terms
    nbs = len(lp)
    for i in range(len(lp)):
        if len(lp[i])==0: continue
        for j in range(i+1,len(lp)):
            if len(lp[j])==0: continue
            if lp[i][1]!=lp[j][1] and lp[i][3:]==lp[j][3:]:
                print 'cancelling %s and %s'%(lp[i],lp[j])
                lp[i] = ''
                lp[j] = ''
                break
    tmp_lp = []
    for x in lp:
        if len(x)>0: tmp_lp.append(x)
    lp = tmp_lp
    nas = len(lp)
    print 'Cancelled %d pairs of terms'%((nbs-nas)/2)
    print 'P =' + (''.join(lp))[2:]
generate('eemm')


*/
