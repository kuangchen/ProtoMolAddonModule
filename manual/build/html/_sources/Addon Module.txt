.. highlight:: xml


Addon Module
============

The ``addon`` module provides support for simulation of AMO systems, which consists of

- forces due to linear quadrupole trap, harmonic trap, laser cooling, fricition
- integrators which accounts for buffer gas collisions, and chemical reactions
- outputs which can save particles' position and velocities locally in a compact format



Forces
------

LQTForce
~~~~~~~~
``LQTForce`` simulates the force due to the trapping field in an linear quadrupole trap:

   .. math::
      V(x, y, z) = \frac{x^2-y^2}{r_0^2}v_{\mathrm{rf}}\cos(\Omega t) + \kappa\frac{z^2 - \frac{1}{2}(x^2+y^2)}{z_0^2 }v_{\mathrm{ec}}

By design, ``LQTForce`` applies to all charged particles in the simulation.

The ``LQTForce`` takes an xml file as a required string argument after the ``-lqt-spec`` directive::

      LQTForce
      -lqt-spec your_spec.xml

The xml file contains the following fields, ::

      <ConfigRoot>
          <LQTSpec>
	      <r0> 12e-3 </r0>
	      <z0> 21.5e-3 </z0>
	      <v_rf> 43.75 </v_rf>
	      <v_ec> 1 </v_ec>
	      <kappa> 0.1275 </kappa>
	      <omega> 300e3 </omega>
	  </LQTSpec>
      </ConfigRoot>

The meaning of these fields are given below:

+----------+---------------------------------+----------+
| Field    | Meaning                         | Unit     |
+----------+---------------------------------+----------+
| r_0      | Field Radius                    | m        |
+----------+---------------------------------+----------+
| z_0      | Distance from center to endcap  | m        |
+----------+---------------------------------+----------+
| v_rf     | Rf-voltage                      | V        |
+----------+---------------------------------+----------+
| v_ec     | End-cap voltage                 | V        |
+----------+---------------------------------+----------+
| omega    | angular trap frequency          | Hz       |
+----------+---------------------------------+----------+
| kappa    | geometrical factor              | NA       |
+----------+---------------------------------+----------+

HarmonicTrapForce
~~~~~~~~~~~~~~~~~
``HarmonicTrapForce`` simulates the force due to a harmonical potential,


.. math::

   V(x, y, z) = \frac{1}{2}m(\omega_x^2 x^2 + \omega_y^2 y^2 + \omega_z^2 z^2)

By design, ``HarmonicTrapForce`` applies to all particles in the simulation. 

The ``HarmonicTrapForce`` takes an xml file as a required string argument after the ``-ht-spec`` directive::

      HarmonicTrapForce
      -ht-spec your_spec.xml

The xml file contains the following fields,::

  <ConfigRoot>
    <HTSpec>
       <omega_x> 40e3 </omega_x>
       <omega_y> 40e3 </omega_y>
       <omega_x> 40e3 </omega_z>
    </HTSpec>
  </ConfigRoot>


The meaning of these fields are given below:

+---------------+---------------------------------------------+---------------+
| Field         | Meaning                                     | Unit          |
+---------------+---------------------------------------------+---------------+
| omega_x       | angular trapping frequency in x direction   | Hz            |
+---------------+---------------------------------------------+---------------+
| omega_y       | angular trapping frequency in y direction   | Hz            |
+---------------+---------------------------------------------+---------------+
| omega_z       | angular trapping frequency in z direction   | Hz            |
+---------------+---------------------------------------------+---------------+

LaserCoolingDampingForce
~~~~~~~~~~~~~~~~~~~~~~~~

``LaserCoolingDampingForce`` simulates the force due to the force due to the cooling laser. The force is model based on the optical pressure on a two level system:

  .. math::
     F = \sum_{\textrm{all lasers}}\frac{ \hbar \vec{k} \gamma}{2} \frac{s}{1+s+4\frac{(\delta-\vec{k}\vec{v})^2}{\Gamma^2}}

where :math:`s` is the saturation parameter, :math:`\vec{k}` is the wavevector, :math:`\gamma` is the spontanous emission rate of the excited state, :math:`\delta` is the detuning of the laser from the transition, :math:`\vec{v}` is velocity of laser-cooled atom. 

The ``LaserCoolingDampingForce`` takes an xml file as a required string argument after the ``-laser-cooling-damping-spec`` directive::

      LaserCoolingDampingForce
      -laser-cooling-damping-spec your_spec.xml

The xml file contains the following fields: ::

  <ConfigRoot>
    <LaserCoolingDampingSpec>
      <beam>
	<label> main beam </label>
	<ion_name> Yb174 </ion_name>
	<t_start> 0 </t_start>
	<t_end> 10 </t_end>
	<n> 0.04932527561 -0.04932527561 -0.99756405026 </n>
	<k> 27100 </k>
	<s> 10 </s>
	<delta> -40e6 </delta>
	<gamma> 20e6 </gamma>
      </beam>

      <beam>
	<label> retro beam </label>
	<ion_name> Yb174 </ion_name>
	<t_start> 0 </t_start>
	<t_end> 10 </t_end>
	<n> -0.04932527561 0.04932527561 0.99756405026 </n>
	<k> 27100 </k>
	<s> 10 </s>
	<delta> -40e6 </delta>
	<gamma> 20e6 </gamma>
      </beam>
    </LaserCoolingDampingSpec>
  </ConfigRoot>

The part between :code:`<beam>` and :code:`</beam>` contains simulation parameters that need to be changed. The meaning of each property node is given below:

+----------------+------------------------------------+-------------------------+
| Field          |  Meaning                           | Unit                    |
+----------------+------------------------------------+-------------------------+
| label          |  Dummy text to label the beam      | string                  |
+----------------+------------------------------------+-------------------------+
| target_atom    |  Name of laser-coolded atom        | string                  |
+----------------+------------------------------------+-------------------------+
| t_start        |  start time of laser-cooling       | sec                     |
+----------------+------------------------------------+-------------------------+
| t_end          |  end time of laser cooling         | sec                     |
+----------------+------------------------------------+-------------------------+
| n              |  direction of laser beam           | 3d unit vector          |
+----------------+------------------------------------+-------------------------+
| s              |  saturation parameter              | 1                       |
+----------------+------------------------------------+-------------------------+
| gamma          |  spontanous emission rate          | Hz                      |
+----------------+------------------------------------+-------------------------+
| delta          |  laser detuning                    | Hz                      |
+----------------+------------------------------------+-------------------------+
| k              |  wavenumber                        | cm^{-1}                 |
+----------------+------------------------------------+-------------------------+


SimpleDampingForce
~~~~~~~~~~~~~~~~~~

``SimpleDampingForce`` simulates the force due to a idealized friciton force that's propotional to the atom's velocity. 

  .. math::
     \vec{F} = -\alpha \vec{v}

where :math:`\alpha` is the proportionality factor. 

``SimpleDampingForce`` take one string argument ``-simple-damping-spec``, which contains the following field: :: 

    <ConfigRoot>
      <SimpleDampingSpec>
        <entry>
          <label> Dummy </label>
          <target_atom> Yb174 </target_atom>
          <t_start> 0 </t_start>
          <t_end> 10 </t_end>
          <alpha> 1e-23 </alpha>
        </entry> 
      </SimpleDampingSpec>
    </ConfigRoot>
    
The meaning of these fields are given below:

+-------------------------+-------------------------+-------------------------+
| Field                   |  Meaning                |  Unit                   |
+-------------------------+-------------------------+-------------------------+
| label                   |  label                  |  string                 |
+-------------------------+-------------------------+-------------------------+
| target                  |  target atom            |  string                 |
+-------------------------+-------------------------+-------------------------+
| t_start                 |  start time for damping |  second                 |
+-------------------------+-------------------------+-------------------------+
| t_end                   |  end time for damping   |  second                 |
+-------------------------+-------------------------+-------------------------+
| alpha                   |  proportionality factor |                         |
+-------------------------+-------------------------+-------------------------+




Integrators
-----------

LeapFrogBufferGasIsotropic
~~~~~~~~~~~~~~~~~~~~~~~~~~

``LeapfrogBufferGasIsotropic`` integrator is provided to simulate the elastic collision of ions with neutral atoms. This integrators assumes the neutral atom has a mass :math:`m`, a uniform density :math:`\rho`, a single temperature :math:`T`, and a polarizability :math:`\alpha`. Under such assumption, the average collision rate between an ion and the neutral atoms is given by 

  .. math::
     \Gamma = 2\pi\rho\sqrt{\alpha/2\mu}

where :math:`\mu` is the reduced mass of the ion and neutral atom system. In addition, each collision is assumed to scatter the relative velocity isotropically into :math:`4\pi` solid angle. 

``LeapfrogBufferGasIsotropic`` integrator take two arguments: ``timestep`` and ``filename``. ::

    level X LeapfrogBufferGasIsotropic {
       timestep N
       filename your_spec.xml
    
       # Definition of forces
    }

  

- ``timestep`` is the number of unit steps (each unit step is 1 femto seconds) the integrator propagates in each iteration. 
- ``filename`` points to an xml file that contains the following fields, ::

     <ConfigRoot>
         <BufferGas>
	     <m> 40 </m>
             <name> Ca </name>
             <alpha> 159.4 </alpha>
             <T> 5e-3 </T>
             <rho> 1e17 </rho>
             <target> Yb174 </target>
         </BufferGas>
     </ConfigRoot>

The meaning of these fields are given below:


+-------------------------+-------------------------+-------------------------+
| Field                   |  Meaning                |  Unit                   |
+-------------------------+-------------------------+-------------------------+
| name                    |  neutral name           |  string                 |
+-------------------------+-------------------------+-------------------------+
| m                       |  neutral mass           |  amu                    |
+-------------------------+-------------------------+-------------------------+
| alpha                   |  neutral polarizability |  a.u.                   |
+-------------------------+-------------------------+-------------------------+
| T                       |  neutral temperature    |  K                      |
+-------------------------+-------------------------+-------------------------+
| rho                     |  neutral density        |  m^{-3}                 |
+-------------------------+-------------------------+-------------------------+
| target                  |  target ion             |  string                 |
+-------------------------+-------------------------+-------------------------+



Outputs
-------

OutputSnapshotWithHDF5Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
``OutputSnapshotWithHDF5Storage`` provides the functionality to store snapshots of particle's position and velocities in a Hierarchical Data Format for the purpose of data efficiency and access speed. This output becomes convenient when the particle's positions and velocities over a period of time need to be saved and analyzed offline. 

For example, suppose we would like to monitor the reduction of trapped ion's secular energy :math:`T_{sec}`  when ions are sympathetically cooled by surrounding ultracold atoms. Given the cooling rate, we decide to calculate :math:`T_{sec}(t)` at several checkpoints, i.e. :math:`t = 0, 0.25, 0.5, 0.75\ \mathrm{and}\ 1 \mathrm{sec}`. This means ion's trajectories over a few micromotion cycles at these checkpoints should be stored. 

The data at each checkpoint is called a *snapshot*, and it is saved as a *single* HDF5 file. Each snapshot consists of several *frames*, where each frame contains all ion's positions and velocities, :math:`N_{\mathrm{ion}}\times 6` real numbers in total.





``OutputSnapshotWithHDf5Storage`` only take one string argument, which contains the following field::

    OutputSnapshotWithHDF5Storage your_spec.xml

``your_spec.xml`` points to an xml file which contains the following fields, ::


  <ConfigRoot>
    <OutputSnapshotWithHDF5Storage>
      <FileNamePattern>snapshot_%d.h5</FileNamePattern>
      <TimeQueue>
        <Entry>1000 0    1.000e-07</Entry>
        <Entry>1000 0.02 1.000e-07</Entry>
        <Entry>1000 0.04 1.000e-07</Entry>
        <Entry>1000 0.06 1.000e-07</Entry>
	<Entry>1000 0.08 1.000e-07</Entry>
	<Entry>1000 0.1	 1.000e-07</Entry>
      </TimeQueue>
    </OutputSnapshotWithHDF5Storage>
  </ConfigRoot>



The meaning of these fields are given below:

+----------------+------------------------------+------------------------------------------------------------------------+
| Field          | Meaning                      | Specification                                                          |
|                |                              |                                                                        |
+----------------+------------------------------+------------------------------------------------------------------------+
| FilenamePattern| pattern for shapshot files   | a string with '%d'. The %d part is replaced by 0,1, 2, ...             |
+----------------+------------------------------+------------------------------------------------------------------------+
| TimeQueue      | specification                | each entry consists of :math:`N_{i}`, :math:`t_{i}`, :math:`dt_ {i}`   |
+----------------+------------------------------+------------------------------------------------------------------------+
