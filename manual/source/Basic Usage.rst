Basic Usage of ProtoMol
=======================
To run a ProtoMol simulation, a user needs to provide a configuration file that defines simulation initial conditions, integrator, outputs, and other simulation parameters. 

.. code:: conf

   ProtoMol your_file.conf


Overview of configuration file
---------------------------------------
A minimal example of configuration file is presented below, with the meaning of each entry explained in the comment line. 

.. code-block:: bash
   
   # Number of steps in simulation
   numsteps 1000000
         
   firststep 0

   # Simulation cell size
   cellsize 5000000

   boundaryConditions vacuum

   # Cell Manager
   cellManager Cubic
   exclude none

   # Initial position and velocitiy definition
   posfile single_ion.pos_xyz
   velfile single_ion.vel_xyz

   # par and psf file definition
   psffile single_ion.psf
   parfile single_ion.par

   # trajectory output file
   XYZPosFile single_ion_trajectory.xyz

   # output frequency
   outputfreq 2000

   # integrator definition
   Integrator {
     # use LeapFrog for 0th level integrator
     level 0 LeapFrog {
        # time step for this integrator
    	timestep 2e7

	# force specification
	force LQTForce 
	-lqt-spec single_ion.xml 
     } 
   }

The configurations are organized in the format of self-explanatory *keyword - value* pairs. The most important components are:

- Definition of position and velocities for each particle in ``xyz`` format. 
- Definition of particle parameters (mass, charge, *etc*), in ``psf`` and ``par`` format.
- Definition of forces/integrators/outputs, which we detail below.

Forces, Integrators and Outputs
-------------------------------
- ``ProtoMol`` forces are the actual forces in Newton's equation:

.. math::

   m \frac{d^2 \vec{r}_i}{dt^2} = \sum_{all\, forces\, on\,i^{th}\,particle}\vec{F}

- ``ProtoMol`` integrators specify how the equation of motion should be numerically integrated. For instance, it could be Rugga-Kutta method (:math:`O(4)`) or LeapFrog method (:math:`O(4)`, but more stable ), *etc*. Some mechansims which are difficult to be implemented as force, such as evaporation cooling or sympathetic cooling, can also be cast as an integrator.

- ``ProtoMol`` outputs write particle's information to screen or an external file.
