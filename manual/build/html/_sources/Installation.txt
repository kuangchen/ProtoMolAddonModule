Installation 
=============================

Installation of ``ProtoMol`` addon module consists of the following steps. 

1. Install all the dependencies: ``git``, ``boost``, ``HD5``, ``cmake``.
   
   .. code-block:: bash
 
      sudo apt-get install git libboost1.55-all-dev libhdf5-dev cmake

2. Clone the ``ProtoMolAddon`` git repository to a local path:

   .. code-block:: bash
  
      git clone https://github.com/kuangchen/ProtoMolAddon.git

3. Compile the source code into binary:

   .. code-block:: bash

      # Change directory
      cd protomol
		   
      # Build CMake cache
      cmake .
 
      # Compile all cpp files
      make 

      # Link and install the executable into system directory
      sudo make install

4. After the installation, an executable named ``ProtoMol`` will be created in the system directory. To see whether the add-on package has been successfully installed, run :code:`ProtoMol --modules`, and the output should list ``addon`` as an installed module.

   .. code-block:: bash
      
      user@localhost:~$ ProtoMol --modules		   
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
