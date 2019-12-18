#include "MyProcessor.h"
#include <iostream>  

#include <EVENT/LCCollection.h>
#include <EVENT/ReconstructedParticle.h>

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

  // TFile creation
  _file = new TFile("output.root","RECREATE");
  // TTree creation
  _tree = new TTree("evt","");
  // Register variables to TTree 
  _tree->Branch( "npfos" , &_npfos , "npfos/I"        ); // I : integer, O : boolean, F : float, D : double
  _tree->Branch( "pfo_e" , _pfo_e  , "pfo_e[npfos]/D" ); // This is an example to set an Array

}


void MyProcessor::processRunHeader( LCRunHeader* run) { 
   
  std::cout << "processRunHeader() called." << std::endl;
 
} 



void MyProcessor::processEvent( LCEvent * evt ) { 

  std::cout << "processEvent() called." << std::endl;

  // Get reconstructed particles (Pandora is a name of algorithm to reconstruct particles)
  LCCollection* colpfo     = evt->getCollection("PandoraPFOs") ;

  int nPFO = colpfo->getNumberOfElements()  ;

  // set number of PFOs to the variable registered to TTree.
  _npfos = nPFO;

  for(int i=0; i< nPFO ; i++){
    // Get a reconstructed particle
    ReconstructedParticle* p = dynamic_cast<ReconstructedParticle*>( colpfo->getElementAt( i ) ) ;
    // Access its parameters
    double e = p->getEnergy();

    // set energy of this PFO to the variable registered to TTree.
    _pfo_e[i] = e;
  }

  // Don't forget to call fill whenever you want.
  // At this point, the variables you set above will be actually saved.
  _tree->Fill();

}



void MyProcessor::check( LCEvent * evt ) { 

  std::cout << "check() called." << std::endl;

}


void MyProcessor::end(){ 

  std::cout << "end() called." << std::endl;

  // Write TTree data to output file
  _file->Write();

}
