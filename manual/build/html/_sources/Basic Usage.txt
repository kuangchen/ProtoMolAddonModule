Basic Usage of ProtoMol
=======================
To run a ProtoMol simulation, a user needs to provide a configuration file that defines simulation initial conditions, integrator, outputs, and other simulation parameters. 

  .. code:: bash

     ProtoMol your_file.conf


Overview of configuration file
---------------------------------------
A minimal example of configuration file is presented below, with the meaning of each entry explained in the comment line. 

  .. code-block:: bash

     # Number of steps in simulation
     numsteps 100000000

     # The number assigned to the first step
     firststep 0

     # Random Number seed
     seed 11

     # Simulation cell size
     cellsize 5000000

     # Boundary Conditions
     boundaryConditions vacuum

     # Cell Manager
     cellManager Cubic
     exclude none

     # Initial position and velocitiy definition
     posfile sim_pos.xyz
     psffile sim_vel.psf

     # Par file definition
     parfile sim.par

     # Output Setting
     outputfreq 10000

     # Integrator Setting
     integrator {
	    # 0th level integrator
	    level 0 Leapfrog {

	        # Time step in units of femto seconds
	        timestep 1e8
     
                # Add Coulomb force between ions
		# additional options for force are specified
	        force Coulomb 
                -algorithm NonbondedSimpleFull
	    }
     }

The configurations are organized in the format of self-explanatory *keyword - value* pairs. The most important components are:

- Definition of position (example file) and velocities (example file) for each particle in ``xyz`` format. 
- Definition of particle parameters (mass, charge, *etc*), in ``psf`` (example file) and ``par`` (example file) format.
- Definition of integrator, with the following syntax:

  .. code-block:: bash

     integrator {
       level 0 integrator0 {
         timestep N
         force1
	 force2
	 ...
       
         level 1 integrator1 {
         ...
         }
       }
     }
  The details are explained in the Quick Reference.

- Definition of forces. The details are explained in the Quick Reference and :ref:`Addon_Forces`.
  


