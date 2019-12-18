#ifndef MyProcessor_h
#define MyProcessor_h 1

#include "marlin/Processor.h"
#include "lcio.h"

using namespace lcio ;
using namespace marlin ;

class MyProcessor : public Processor {
  
 public:
  
  virtual Processor*  newProcessor() { return new MyProcessor ; }
  
  
  MyProcessor() ;
  
  virtual void init() ;
  
  virtual void processRunHeader( LCRunHeader* run ) ;

  virtual void processEvent( LCEvent * evt ) ; 
  
  virtual void check( LCEvent * evt ) ; 
  
  virtual void end() ;

  std::string _colname ;
  std::string _myparam1 ;
  float       _myparam2 ;

} ;

#endif



