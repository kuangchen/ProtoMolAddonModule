Unit system in ``ProtoMol``
===========================

Shown below, ``ProtoMol`` uses its own unit system (e.g. for position and velocity input), which is natural for bio-chemistry simulations. 

.. image:: units.gif

However, this becomes quickly inconvenient for AMO simulations, especially if new forces/integrator/outputs need to be implemented.


``SIAtomProxy`` and ``ConstSIAtomProxy``
----------------------------------------
Two ``C++`` classes, ``ProtoMolAddon::SIAtomProxy`` and ``ProtoMolAddon::ConstSIAtomProxy`` have been introduced to faciliate conversion between and ``ProtoMol`` unit and SI unit.

``ProtoMolAddon::SIAtomProxy`` supports reading and writing of atom's position/velocity/label, which is useful and should only be used when new integrators are implemented. In comparison, the constant version ``ProtoMolAddon::ConstSIAtomProxy`` *only* supports reading of atom's information, thus should be used for new forces or outputs.

The interfaces that ``SIAtomProxy`` and ``ConstSIAtomProxy`` can be easily found from ``/addon/util/SIAtomProxy.h`` and ``/addon/util/ConstSIAtomProxy.h``.

Additionally, two array classes, ``SIAtomProxyArray`` and ``ConstSIAtomProxyArray``, are also created, which interface all atoms being simulated. 

