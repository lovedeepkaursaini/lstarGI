#include "TLorentzVector.h"
#include "TGenPhaseSpace.h"

#include "TFile.h"
#include "TH1.h"

#include "Pythia8/Pythia.h"


using namespace Pythia8; 

int main() {

  // Generator. 
  Pythia8::Pythia pythia;
  pythia.readString("Beams:eCM = 8000.");
  pythia.readString("ExcitedFermion:qqbar2muStarmu = on");
  pythia.readString("ExcitedFermion:Lambda= 10000");
  pythia.readString("4000013:m0 = 2000");
  pythia.readString("4000013:onMode = off");
  pythia.readString("4000013:onIfMatch = 13 23");
  pythia.readString("23:onMode = off");
  pythia.readString("23:onIfAny = 1 2 3 4 5");
  pythia.readString("Next:numberShowInfo = 0");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 0");

  // Create an LHAup object that can access relevant information in pythia.
  LHAupFromPYTHIA8 myLHA(&pythia.process, &pythia.info);

  // Open a file on which LHEF events should be stored, and write header.
  myLHA.openLHEF("GI.lhe");



  pythia.init();


  // Store initialization info in the LHAup object.
  myLHA.setInit();

  // Write out this initialization info on the file.
  myLHA.initLHEF();

        TGenPhaseSpace phasespace;
	TFile* histoFile = new TFile("GIhistoFile.root","recreate");
	TH1F* hdR = new TH1F("hdR",";#DeltaR qq; Events",100,0.,6.);
	TH1F* hMass = new TH1F("hMass",";Mass (GeV); Events",200,0.,2500.);

  // Extract settings to be used in the main program.
  int    nEvent    = 10000;//pythia.mode("Main:numberOfEvents");
  int nList = 10;//pythia.mode("Next:numberShowProcess");
 

  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
   // Generate event. 
    if (!pythia.next()) continue;

	// retrieve the q qbar from l* decay

   int nsize = pythia.process.size() ;
   int i1 = -1;		// indices of the l and gamma from l* decay
   int i2 = -1;
   int ilep = -1;
    for (int i = 0; i < pythia.process.size(); i++) {
        int JMOHEP1 = pythia.process[i].mother1() ;
        int id_mother = pythia.process[JMOHEP1].id();
	if ( abs(id_mother) != 23 && abs(id_mother) != 4000011 && abs(id_mother) != 4000013) continue;
	int id = pythia.process[i].id() ;
	if ( abs(id) > 10 ) ilep =i;   // that's the lepton
   	else {
	   if (i1 < 0) i1 = i;
	   else i2 = i;
	}
	//	cout<< JMOHEP1<<'\t'<<id_mother<<'\t'<<id<<'\t'<<ilep<<'\t'<<i1<<'\t'<<i2<<endl;
    }


      if ( i1 < 0 || i2 < 0) {
	cout << " ... unexpected ... " << endl;
	continue;
      }

        TLorentzVector plep( pythia.process[ilep].px(), pythia.process[ilep].py(),
                              pythia.process[ilep].pz(), pythia.process[ilep].e()  );
	TLorentzVector pq( pythia.process[i1].px(), pythia.process[i1].py(),
			      pythia.process[i1].pz(), pythia.process[i1].e()  );
        TLorentzVector pqbar( pythia.process[i2].px(), pythia.process[i2].py(),
                              pythia.process[i2].pz(), pythia.process[i2].e()  );

		// basic kinematic checks:
        TLorentzVector plqq = pq + pqbar + plep;
	hMass -> Fill( plqq.M() );
	float deltar = pq.DeltaR( pqbar );
	hdR -> Fill( deltar );

    // Store event info in the LHAup object.
    myLHA.setEvent();

    // Write out this event info on the file.
    // With optional argument (verbose =) false the file is smaller.
    myLHA.eventLHEF();
    if (iEvent < nList) {
      cout << " Before the hack : " << endl;
      //  pythia.info.list();
      pythia.process.list();
      // pythia.event.list();
    }

  }
  pythia.stat();

  // Update the cross section info based on Monte Carlo integration during run.
  myLHA.updateSigma();

  // Write endtag. Overwrite initialization info with new cross sections.
  myLHA.closeLHEF(true);

  hdR -> Write();
  hMass -> Write();

  histoFile -> Close();
  
 
 
  // Done.
  return 0;
}
