#ifndef __COLLISION_H_
#define __COLLISION_H_

#include <vector>

namespace ProtoMol {
  class ProtoMolApp;
}

namespace ProtoMolAddon {
  namespace Util {
    class SIAtomProxy;
  }

  namespace BufferGas {

    class Collision {

    protected:
      std::vector<Util::SIAtomProxy> atom_proxy;
      void virtual CollideEach(Util::SIAtomProxy &ap, double dt) = 0;

    public:
      Collision();
      
      void Initialize(ProtoMol::ProtoMolApp *app);
      void Collide(double dt);

    };
  }
}

#endif
