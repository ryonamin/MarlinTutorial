#include "MyProcessor.h"
#include <iostream>  

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include "UTIL/LCRelationNavigator.h"

// ----- include for verbosity dependend logging ---------
//#include "marlin/VerbosityLevels.h"


using namespace lcio ;
using namespace marlin ;


MyProcessor aMyProcessor ;


MyProcessor::MyProcessor() : Processor("MyProcessor") {
  // Constructor
  // All Marlin processor must inherit Processor class which is defined. 
  // /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/include/marlin/Processor.h
  // ////cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/source/src/Processor.cc
}



void MyProcessor::init() { 

  std::cout << "init() called." << std::endl;
  // Set _nevent.

}


void MyProcessor::processRunHeader( LCRunHeader* run) { 
   
  std::cout << "processRunHeader() called." << std::endl;
 
} 



void MyProcessor::processEvent( LCEvent * evt ) { 

  std::cout << "processEvent() called." << std::endl;

  // Get reconstructed particles (Pandora is a name of algorithm to reconstruct particles)
  LCCollection* colpfo     = evt->getCollection("PandoraPFOs") ;
  // Get an auxiliary data collection to find MCParticle corresponding to a reconstructed particle.
  LCCollection* colnav     = evt->getCollection("RecoMCTruthLink") ;
  // Create an auxiliary object to handle the MC-Reco link data above.
  LCRelationNavigator* nav = new LCRelationNavigator(colnav);

  int nPFO = colpfo->getNumberOfElements()  ;
  for(int i=0; i< nPFO ; i++){
    // Get a reconstructed particle
    ReconstructedParticle* p = dynamic_cast<ReconstructedParticle*>( colpfo->getElementAt( i ) ) ;
    // Access its parameters
    int pid = p->getType();
    double e = p->getEnergy();
    std::cout << "Reconstructed Particle : PID = " << pid << ", Energy = " << e << std::endl;

    // Finding corresponding MCParticle to this reconstructed particle
    std::cout << "  Corresponding MCParticles :";
    int ncandidates = nav->getRelatedToObjects(p).size();
    for (int imc = 0; imc < ncandidates; imc++ ) {
       MCParticle *mcp = dynamic_cast<MCParticle*>(nav->getRelatedToObjects(p)[imc]);

       // Correct probability (weight) from tracker info. 
       // This can be used to choose best candidate if you have multiple candidates.
       double trkw = double((int(nav->getRelatedToWeights(p)[imc])%10000)/1000.);

       // Correct probability (weight) from calorimeter info
       // This can be used to choose best candidate if you have multiple candidates.
       double calw = double((int(nav->getRelatedToWeights(p)[imc])/10000)/1000.);

       std::cout << " Candidate " << imc << "( PID = " << mcp->getPDG() << ", Energy = " << mcp->getEnergy() 
                 << ", trkw = " << trkw << ", calw = " <<  calw;
    }
    std::cout << std::endl; 
  }

}



void MyProcessor::check( LCEvent * evt ) { 

  std::cout << "check() called." << std::endl;

}


void MyProcessor::end(){ 

  std::cout << "end() called." << std::endl;

}
