#include "MyProcessor.h"
#include <iostream>  

#include <EVENT/LCCollection.h>
#include <EVENT/ReconstructedParticle.h>
#include "UTIL/PIDHandler.h"

// ----- include for verbosity dependend logging ---------
//#include "marlin/VerbosityLevels.h"


using namespace lcio ;
using namespace marlin ;


MyProcessor aMyProcessor ;


MyProcessor::MyProcessor() : Processor("MyProcessor") {
  // Constructor
  // All Marlin processor must inherit Processor class which is defined. 
  // /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/include/marlin/Processor.h
  // /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/source/src/Processor.cc
}



void MyProcessor::init() { 

  std::cout << "init() called." << std::endl;


}


void MyProcessor::processRunHeader( LCRunHeader* run) { 
   
  std::cout << "processRunHeader() called." << std::endl;
 
} 



void MyProcessor::processEvent( LCEvent * evt ) { 

  std::cout << "processEvent() called." << std::endl;

  // Jet is defined as a reconstructed particles (EVENT::RECONSTRUCTEDPARTICLE)
  LCCollection* coljet     = evt->getCollection("RefinedJets") ;

  int njets = coljet->getNumberOfElements()  ;
  std::cout << "njets = " << njets << std::endl;

  // Get resutls of flavor tagging that has been done in LCFIPlus
  PIDHandler pidh ( coljet ) ;
  const IntVec& algolist = pidh.getAlgorithmIDs() ;
  int algo = -99999;
  if ( algolist.size() != 0 ) algo = pidh.getAlgorithmID( "lcfiplus" ) ;

  for(int ijet=0; ijet< njets ; ijet++){
      ReconstructedParticle* jet = dynamic_cast<ReconstructedParticle*>( coljet->getElementAt( ijet ) ) ;
      if ( algolist.size() != 0 ) {
        const ParticleID& jetID = pidh.getParticleID( jet , algo ) ;
        FloatVec params = jetID.getParameters() ;
        float btag  = params[pidh.getParameterIndex( algo , "BTag"  )]  ; // b-likeliness
        float ctag  = params[pidh.getParameterIndex( algo , "CTag"  )]  ; // c-liekliness

        std::cout << "Jet " << ijet << ": energy = " << jet->getEnergy() << ", btag = " << btag << ", ctag = " << ctag << std::endl;
     }
  }

}



void MyProcessor::check( LCEvent * evt ) { 

  std::cout << "check() called." << std::endl;

}


void MyProcessor::end(){ 

  std::cout << "end() called." << std::endl;

}
