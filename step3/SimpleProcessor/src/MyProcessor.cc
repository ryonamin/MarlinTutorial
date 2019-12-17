#include "MyProcessor.h"
#include <iostream>  

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>

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

}


void MyProcessor::processRunHeader( LCRunHeader* run) { 
   
  std::cout << "processRunHeader() called." << std::endl;
 
} 



void MyProcessor::processEvent( LCEvent * evt ) { 

  std::cout << "processEvent() called." << std::endl;

  // Get data named "MCParticlesSkimmed" from LCEvent object.
  LCCollection* col = evt->getCollection("MCParticlesSkimmed") ;

  // Get number of elements (MCParticles in this case).
  int n = col->getNumberOfElements();

  for(int i=0; i< n ; i++){

    // Extract MCParticle objects from data (LCCollection).
    MCParticle* mcp = dynamic_cast<MCParticle*>( col->getElementAt( i ) ) ;

    // Get Particle ID for mcp.
    int pdg = mcp->getPDG();
    // Get Particle energy for mcp.
    double e = mcp->getEnergy();
    // Get Particle momentum for mcp.
    const double* p = mcp->getMomentum();

    std::cout << "i = " << i << ", pdg = " << pdg << ", energy = " << e << " [GeV], (px, py, pz) = (" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl; 
  } 
}



void MyProcessor::check( LCEvent * evt ) { 

  std::cout << "check() called." << std::endl;

}


void MyProcessor::end(){ 

  std::cout << "end() called." << std::endl;

}
