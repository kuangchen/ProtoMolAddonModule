#ifndef __CEM_DETECTOR_H
#define __CEM_DETECTOR_H

#include <protomol/addon/tof/AtomRecord.h>
#include <iostream>

namespace ProtoMolAddon {
  
  namespace ToF {

    class CEMDetector {
    public:
      typedef double init_type;
  
    private:
      double pos;

    public:

      CEMDetector(const init_type &init);
      void Process(AtomRecord *r, double now) const;
       
      friend ostream& operator << (ostream &os, const CEMDetector &detector);
    };

  }

}

#endif
