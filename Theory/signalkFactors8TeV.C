#include "calc.cc"
#include <cmath>
#include <iomanip>

void signalkFactors8TeV(){

  double lambda = 0;
  double masspoint[13] = {200,400,600,800,1000,
 			  1200,1400,1600,1800,
			  2000,2200.,2400.,2600};
  //this is done just to match with "Production and Decay of Excited Electrons at LHC"
//  double masspoint[12] = {1000,3000,5000};
  
  double  Xsec_Sig_pythia6[12] = {2.128e-2,1.236e-2,7.233e-3,4.248e-3,2.506e-3,
				  1.455e-3,8.540e-4,5.031e-4,2.878e-4,
  				  1.648e-4,9.313e-5,5.199e-5 };
  
  double kfacs2tev[13] = {0.1296E+01,
			  0.1290E+01,
			  0.1282E+01,
			  0.1273E+01,
			  0.1268E+01,
			  0.1265E+01,
			  0.1267E+01,
			  0.1272E+01,
			  0.1282E+01,
			  0.1295E+01,
			  0.1311E+01,
			  0.1329E+01,
			  0.1348E+01
  };


  double fromShuHaoXsec[13] = {1.43398,9.548e-1,5.654e-1,3.359e-1,1.974e-1,1.163e-1,6.819e-2,3.961e-2,2.291e-2,1.308e-2,7.420e-3,4.153e-3,2.284e-3};//for 2600, xsec is 2.284e-3

  cout<<"give the value of lambda in GeV "<<endl;
  cin>>lambda;


  
  //cout<<" Xsec_Sig_pythia6_kfac[10] = {";
  for(int ii=0; ii<13; ii++)
    {

      //double kfac = kfacs2tev[ii]*pow(2000.0/lambda,4);
      //  double kfac = kfacs2tev[ii]; ///k -factor should not be scaled
      double xsec = Xsec_Sig_pythia6[ii]*pow(10000.0/lambda,4)*kfacs2tev[ii]*brCI(masspoint[ii],lambda)*1e3;
      //double xsec = Xsec_Sig_pythia6[ii]*pow(10000.0/lambda,4);
      //cout<<xsec<<", ";
      double xsecbr = xsec*brlz(masspoint[ii],lambda);
      // cout<<"Lambda = "<<lambda<<" , Mass = "<<masspoint[ii]<<" , kfactor = "<<kfacs2tev[ii]<<
      // 	" , prod. xsec of e*, i.e. pp->ee* = "<<Xsec_Sig_pythia6[ii]*pow(10000.0/lambda,4)*kfacs2tev[ii]<<
      // 	" , BR of e*->lZ = "<<brlz(masspoint[ii],lambda)<<" , xsec for pp->ee*->eeZ = "<<Xsec_Sig_pythia6[ii]*pow(10000.0/lambda,4)*kfacs2tev[ii]*brlz(masspoint[ii],lambda)
      // 	  <<" , , xsec for pp->ee*->eeZ->eeee = "<<Xsec_Sig_pythia6[ii]*pow(10000.0/lambda,4)*kfacs2tev[ii]*brlz(masspoint[ii],lambda)*0.03367*1e3<<endl;
      
      // if(lambda==masspoint[ii])
       //cout<<Xsec_Sig_pythia6[ii]*pow(10000.0/lambda,4)*kfacs2tev[ii]*brlz(masspoint[ii],lambda)*0.03367*1e3<<",";
//cout<<brlz(masspoint[ii],lambda)<<",";
      //    cout<<corrFacbrlz(masspoint[ii],lambda)<<", "<<brlz(masspoint[ii],lambda)<<", "<<brlzCI(masspoint[ii],lambda)<<endl;


      //from production:
      //  cout<<setprecision(3)<<masspoint[ii]<<" & "<<Xsec_Sig_pythia6[ii]*1e3<<" & "
      //	  <<Xsec_Sig_pythia6[ii]*1e3*brlz(masspoint[ii],lambda)*0.70<<" & "<<kfacs2tev[ii]
      //	  <<" & "<<kfacs2tev[ii]*Xsec_Sig_pythia6[ii]*1e3*brlz(masspoint[ii],lambda)*0.70<<" \\\\"<<endl;

      //from shu-hao (mainly used in AN)
      //  cout<<masspoint[ii]<<setprecision(6)<<" & "<<fromShuHaoXsec[ii]*pow(10000.0/lambda,4)<<" & "<<kfacs2tev[ii]
      //	  <<" & "<<corrFacbrlz(masspoint[ii],lambda)<<"  & "<<kfacs2tev[ii]*fromShuHaoXsec[ii]*pow(10000.0/lambda,4)*corrFacbrlz(masspoint[ii],lambda)<<" \\\\"<<endl;
      // cout<<kfacs2tev[ii]*fromShuHaoXsec[ii]*pow(10000.0/lambda,4)*corrFacbrlz(masspoint[ii],lambda)<<", ";
      //  cout<<fixed<<showpoint<<setprecision(3)<<corrFacbrlz(masspoint[ii],lambda)<<",";
      //Figure 1 of AN14-148: BR Vs Mass
      cout<<brlz(masspoint[ii],lambda)<<",  ";
      cout<<brnw(masspoint[ii],lambda)<<",  ";
      cout<<brpho(masspoint[ii],lambda)<<",  ";
      cout<<brCI(masspoint[ii],lambda)<<",  "<<endl;

       //get xsection for CI
      //  cout<<kfacs2tev[ii]*fromShuHaoXsec[ii]*pow(10000.0/lambda,4)*corrFacbrlz(masspoint[ii],lambda)*brCI(masspoint[ii],lambda)/brlz(masspoint[ii],lambda)<<", ";
                     


    }

  cout<<";"<<endl;

}
