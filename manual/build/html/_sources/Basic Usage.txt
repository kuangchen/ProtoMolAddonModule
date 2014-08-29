Basic Usage of ProtoMol
=======================
To run a ProtoMol simulation, a user needs to provide a configuration file that defines simulation initial conditions, integrator, outputs, and other simulation parameters. 

  .. code:: bash

     ProtoMol your_file.conf


Overview of configuration file
---------------------------------------
These entries are organized in the format of self-explanatory *keyword - value* pairs. A minimal example of configuration file is presented below, with the meaning of each entry explained in the comment line. 

  .. hgithlight:: bash
  .. code:: bash

     # Number of steps in simulation
     numsteps 100000000

     # The number assigned to the first step
     firststep 0

     # Random Number seed
     seed 11

     # Initial temperature of particles
     temperature 1e4

     # Simulation cell size
     cellsize 5000000

     # Boundary Conditions
     boundaryConditions vacuum

     # Cell Manager
     cellManager Cubic
     exclude none

     # Initial position and velocitiy definition
     posfile ion_neutral_cooling_ini_pos_32.xyz
     psffile ion_neutral_cooling_32.psf

     # Par file definition
     parfile ion_neutral_cooling.par

     # Output Setting
     outputfreq 10000

     # Add IonSnapshot as the output
     IonSnapshot ss.lua
     
     # Integrator Setting
     integrator {
	    # 0th level integrator
	    level 0 LeapfrogBufferGas {
	    timestep 1e8
	    filename buffer_gas.lua	
     
	    # Add Coulomb force between ions
	    force Coulomb 
	    -algorithm NonbondedSimpleFull

	    # Add ion trap force
	    force LQT 
	    -lqt_filename trap.lua
	    }
     }

To see the full list of supported keywords, refer to `ProtoMol Quick Reference`_.

.. _`ProtoMol Quick Reference` : http://protomol.sourceforge.net/quickref.pdf

The most important components are:

- Definition of position and velocities for each particle in ``xyz`` format
- Definition of particle parameters (mass, charge, *etc*), in ``psf`` and ``par`` format
- Definition of addon components in ``xml`` format.
