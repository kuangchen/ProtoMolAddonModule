Installation 
=============================

Installation consists of the following steps. 

1. Download the original ProtoMol source code for your operating system from sourceforge_ page. Extract the source code to a directory, ``protomol_orig`` for instance.

.. _sourceforge: http://sourceforge.net/projects/protomol/files/ProtoMol/Protomol%203.3/

2. Download the protomol-addon package from here. Extract the source code to a directory, ``protomol_addon`` for instance. 

3. Change the directory to ``protomol_addon``. Patch the original ProtoMol source code with the addon package by running

   .. code:: bash

      make install ../protomol_orig

   After the installation, an executable named ``ProtoMol`` will be created in the system directory. To see whether the add-on package has been successfully installed, run :code:`ProtoMol --modules`, and the output should list ``addon`` as an installed module.

   .. code:: bash
   
      Checkpoint                              Provides checkpointing support
      Addon                                   Addons for simulating AMO systems
      BondedForces
      CommandLine                             Adds standard command line options.
      Configuration                           Configuration system.
      HessianIntegrator
      IO
      IntegratorBase
      IntegratorOpenMM
      Leapfrog
      Main                                    System default keywords and setup.
      Modifier
      NonbondedCutoffForce
      NonbondedFullElectrostaticForce
      NonbondedFullForce
      NonbondedIntermittentFullForce
      NonbondedSimpleFullForce
      Output
      Topology
      NormalMode
