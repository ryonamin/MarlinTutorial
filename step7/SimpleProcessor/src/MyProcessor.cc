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
  // /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/source/src/Processor.cc

  // See other examples for types /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lcio/v02-12-01/include/EVENT/LCIO.h
  registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE, // type of input collection
     "InputPFOCollection" , // define parameter name. You can change this parameter with this name in your steering file.
     "Name of the PFOs collection" ,
     _colname , // input value will be stored in this variable
     std::string("PandoraPFOs") // default value
  ) ;

  registerProcessorParameter( "TestStringParameterName", // define parameter name. You can change this parameter with this name in your steering file.
         "Explain this parameter here",
         _myparam1, // input value will be stored in this variable 
         std::string("This_is_default.") // default value
  );

  registerProcessorParameter( "TestFloatParameterName", // define parameter name. You can change this parameter with this name in your steering file.
         "Explain this parameter here",
         _myparam2, // input value will be stored in this variable  
         float(0.) // default value
  );
}



void MyProcessor::init() { 

  std::cout << "init() called." << std::endl;


}


void MyProcessor::processRunHeader( LCRunHeader* run) { 
   
  std::cout << "processRunHeader() called." << std::endl;
 
} 



void MyProcessor::processEvent( LCEvent * evt ) { 

  std::cout << "processEvent() called." << std::endl;

  // Note that now you can control the input collection name from your steering file.
  LCCollection* colpfo     = evt->getCollection(_colname) ;

  int nPFO = colpfo->getNumberOfElements()  ;
  std::cout << "nPFO = " << nPFO << std::endl;
  std::cout << "_myparam1 = " << _myparam1 << std::endl;
  std::cout << "_myparam2 = " << _myparam2 << std::endl;

}



void MyProcessor::check( LCEvent * evt ) { 

  std::cout << "check() called." << std::endl;

}


void MyProcessor::end(){ 

  std::cout << "end() called." << std::endl;

}
