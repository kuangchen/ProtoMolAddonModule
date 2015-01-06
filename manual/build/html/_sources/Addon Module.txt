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
The trapping force from the electric potential of a linear quadrupole trap is given by

   .. math::
      \vec{F}(x, y, z) = -e\vec{\nabla} \phi(x, y, z)

where

   .. math::
      \phi(x, y, z) = \frac{x^2-y^2}{r_0^2}v_{\mathrm{rf}}\cos(\Omega t) + \kappa\frac{z^2 - \frac{1}{2}(x^2+y^2)}{z_0^2 }v_{\mathrm{ec}}


In ``ProtoMol``, simulation of this force is provided by the keyword ``LQTForce``, with the following syntax:
      
      .. code-block:: bash

         LQTForce
         -lqt-spec your_spec.xml

where ``your-spec.xml`` is an xml file which contain the following fields:

     .. code-block:: xml

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
| r_0      | field radius                    | m        |
+----------+---------------------------------+----------+
| z_0      | distance from center to endcap  | m        |
+----------+---------------------------------+----------+
| v_rf     | rf-voltage                      | V        |
+----------+---------------------------------+----------+
| v_ec     | end-cap voltage                 | V        |
+----------+---------------------------------+----------+
| omega    | angular trap frequency          | Hz       |
+----------+---------------------------------+----------+
| kappa    | geometrical factor              | NA       |
+----------+---------------------------------+----------+

HarmonicTrapForce
~~~~~~~~~~~~~~~~~
The trapping force from a harmonic trapping potential is given by 

.. math::
   \vec{F}(x, y, z) = -\vec{\nabla} V(x, y, z)

where

.. math::
   V(x, y, z) = \frac{1}{2}m(\omega_x^2 x^2 + \omega_y^2 y^2 + \omega_z^2 z^2)


In ``ProtoMol``, simulation of this force is provided by the keyword ``HarmonicTrapForce``, with the following syntax:
      
      .. code-block:: bash

         HarmonicTrapForce
         -ht-spec your_spec.xml

where ``your-spec.xml`` is an xml file which contain the following fields:

      .. code-block:: xml

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
| omega_x       | angular trapping frequency in x direction   | Hz (no 2pi)   |
+---------------+---------------------------------------------+---------------+
| omega_y       | angular trapping frequency in y direction   | Hz (no 2pi)   | 
+---------------+---------------------------------------------+---------------+
| omega_z       | angular trapping frequency in z direction   | Hz (no 2pi)   | 
+---------------+---------------------------------------------+---------------+

An example ``ProtoMol`` project for ``HarmonicTrapForce`` is provided in the path ``example/HarmonicTrap``.


StrayFieldForce
~~~~~~~~~~~~~~~
The force from a stray dc electric field is given by

  .. math::
     \vec{F}(x, y, z) = e\vec{E}(x, y, z)

where :math:`\vec{E}(x, y, z)` is the stray electric field. The simulation of such force in ``ProtoMol`` is provided through the keyword ``StrayFieldFoce``, with the following syntax:

  .. code-block:: bash
     StrayFieldForce
     -stray-field-spec your_spec.xml

where ``your_spec.xml`` is an xml file which contains the following field:

  .. code-block:: xml
    
     <ConfigRoot>
       <StrayFieldSpec>
         <strength> 0 0 0.1 </strength>
       </StrayFieldSpec>
     </ConfigRoot>

The meaning of each field is given below:

+----------+----------------------------------+------+
| Field    | Meaning                          | Unit |
+----------+----------------------------------+------+
| strength | stray 3D electric field strength | V/m  |
+----------+----------------------------------+------+


LaserCoolingDampingForce
~~~~~~~~~~~~~~~~~~~~~~~~
The optical pressure force due to a laser is given by 

  .. math::
     \vec{F} = \frac{ \hbar \vec{k} \gamma}{2} \frac{s}{1+s+4\frac{(\delta-\vec{k}\cdot\vec{v})^2}{\Gamma^2}}

where :math:`s` is the saturation parameter, :math:`\vec{k}` is the wavevector, :math:`\gamma` is the spontanous emission rate of the excited state, :math:`\delta` is the detuning of the laser from the transition, :math:`\vec{v}` is velocity of laser-cooled atom. 

The simulation of such force in ``ProtoMol`` is provided through the keyword ``LaserCoolingDampingForce``, with the following syntax:

      .. code-block:: xml

         LaserCoolingDampingForce
         -laser-cooling-damping-spec your_spec.xml

where ``your_spec.xml`` is an xml file which contains the following fields: 

     .. code-block:: xml

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

+----------------+------------------------------------+---------------------+
| Field          |  Meaning                           | Unit                |
+----------------+------------------------------------+---------------------+
| label          |  Dummy text to label the beam      | string              |
+----------------+------------------------------------+---------------------+
| target_atom    |  Name of laser-coolded atom        | string              |
+----------------+------------------------------------+---------------------+
| t_start        |  start time of laser-cooling       | sec                 |
+----------------+------------------------------------+---------------------+
| t_end          |  end time of laser cooling         | sec                 |
+----------------+------------------------------------+---------------------+
| n              |  direction of laser beam           | 3d unit vector      |
+----------------+------------------------------------+---------------------+
| s              |  saturation parameter              | 1                   |
+----------------+------------------------------------+---------------------+
| gamma          |  spontanous emission rate          | Hz                  |
+----------------+------------------------------------+---------------------+
| delta          |  laser detuning                    | Hz                  |
+----------------+------------------------------------+---------------------+
| k              |  wavenumber                        | :math:`cm^{-1}`     |
+----------------+------------------------------------+---------------------+


Special note:

- The force is modeled as a continous force which is based on the optical Bloch equation. There is no random spontanous emission component. 
- The laser cooling force is on only if the simulation time is between t_start and t_end.
- The laser cooling can be applied to a specific atom species specified through the target_atom field. This features becomes useful for sympathetic cooling simulation, where only one species is actively cooled.
- Multiple laser beams (for instance, a strong main beam and a weaker retro-reflected beam) are specified by stacking more ``<beam>...</beam>`` blocks.
- When multiple `strong` beams are present, it is not correct to simply add up the force due to each beam based on their corresponding :math:`s` parameter. 

SimpleDampingForce
~~~~~~~~~~~~~~~~~~
The simple damping force is given by 

  .. math::
     \vec{F} = -\alpha \vec{v}

where :math:`\alpha` is the proportionality factor. The simulation of this force is provided by the keyword ``SimpleDampingForce``, with the following syntax:

  .. code-block:: bash
     
     SimpleDampingForce
     -simple-damping-spec your_spec.xml

where ``your_spec.xml`` is an xml file which contains the following field: 

  .. code-block:: xml

     <ConfigRoot>
       <SimpleDampingSpec>
         <entry>
           <label> DummyLabel </label>
           <target_atom> Yb174 </target_atom>
           <t_start> 0 </t_start>
           <t_end> 10 </t_end>
           <alpha> 1e-23 </alpha>
         </entry> 
       </SimpleDampingSpec>
     </ConfigRoot>
    
The meaning of these fields are given below:

+---------+------------------------+--------+
| Field   | Meaning                | Unit   |
+---------+------------------------+--------+
| label   | dummy label            |        |
+---------+------------------------+--------+
| target  | name of target atom    |        |
+---------+------------------------+--------+
| t_start | start time for damping | second |
+---------+------------------------+--------+
| t_end   | end time for damping   | second |
+---------+------------------------+--------+
| alpha   | proportionality factor | kg m /s|
+---------+------------------------+--------+

Special note:

- The damping force is on only if the simulation time is between t_start and t_end.
- The damping force can be applied to a specific atom species specified through the target_atom field. This features becomes useful for sympathetic cooling simulation, where only one species is actively cooled.
- Multiple damping forces (for instance, a strong damping on Yb174 and a weak damping on Yb 176) are specified by stacking more ``<entry>...</entry>`` blocks.


RadialQuenchingForce
~~~~~~~~~~~~~~~~~~~~



The patch potential on the electrodes of linear quadrupole trap results in a force given by

   .. math:: 
      
      \vec{F}(x, y, z) = -e \vec{\nabla}\phi(x, y, z)

where
   
   .. math::

      \phi(x, y, z) = \frac{x^2-y^2}{r_0^2} V_p

The simulation of such force in ``ProtoMol`` is provided through the keyword ``RadialQuenchingForce``, with the following syntax:

   .. code-block:: bash

      RadialQuenchingForce
      -raidal-quenching-spec your_spec.xml

where ``your_spec.xml`` is an xml file which contains the following fields:

   .. code-block:: xml
      
      <ConfigRoot>
        <RadialQuenchingSpec>
	  <r0> 12e-3 </r0>
          <v> 0.01 </v>
        </RadialQuenchingSpec>
      </ConfigRoot>

The meaning of these fields are given below:

+-------+---------------+------+
| Field | Meaning       | Unit |
+-------+---------------+------+
| r0    | field radius  | m    |
+-------+---------------+------+
| v     | patch voltage | V    |
+-------+---------------+------+


Integrators
-----------

LeapFrogBufferGasIsotropic
~~~~~~~~~~~~~~~~~~~~~~~~~~

Sympathetic cooling of ions through collisions with cold neutral atoms can be modeled (to a good approximation) as happening at a rate of

  .. math::
     \Gamma = 2\pi\rho\sqrt{\alpha/2\mu}

where :math:`\mu` is the reduced mass of the ion and neutral atom system. In addition, each collision is assumed to scatter the relative velocity isotropically into :math:`4\pi` solid angle. 

The simulation of such process is simulated through an integrator with keyword ``LeapfrogBufferGasIsotropic``, with the following syntax:

      .. code-block:: bash
   
         level X LeapfrogBufferGasIsotropic {
           timestep N
           filename your_spec.xml
    
           # Definition of forces
         ...
         }

where ``timestep`` is the length of integration time step in femtosecond, and ``your_spec.xml`` is an xml file which contains the following field:

     .. code-block:: xml
       
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

+------------+-------------------------+--------------+
| Field      |  Meaning                |  Unit        |
+------------+-------------------------+--------------+
| name       |  neutral name           |  string      |
+------------+-------------------------+--------------+
| m          |  neutral mass           |  amu         |
+------------+-------------------------+--------------+
| alpha      |  neutral polarizability |  a.u.        |
+------------+-------------------------+--------------+
| T          |  neutral temperature    |  K           |
+------------+-------------------------+--------------+
| rho        |  neutral density        |  m^{-3}      |
+------------+-------------------------+--------------+
| target     |  target ion             |  string      |
+------------+-------------------------+--------------+


Special note:

- The buffer gas is considered to be always on, although changing the code to be time-dependent is also easy.
- This version of code can only handle one species of neutral atom. The code need to be modified to accommondate the case of multiple species (for instance, Calcium MOT at 5mK and residual hydrogen background gas at 300K)



Outputs
-------


OutputSnapshotWithHDF5Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
``OutputSnapshotWithHDF5Storage`` provides the functionality to store snapshots of particle's position and velocities in a Hierarchical Data Format for the purpose of data efficiency and access speed. This output becomes convenient when the particle's positions and velocities over a period of time need to be saved and analyzed offline. 

For example, suppose we would like to monitor the reduction of trapped ion's secular energy :math:`T_{sec}`  when ions are sympathetically cooled by surrounding ultracold atoms. Given the cooling rate, we decide to calculate :math:`T_{sec}(t)` at several checkpoints, i.e. :math:`t = 0, 0.25, 0.5, 0.75\ \mathrm{and}\ 1 \mathrm{sec}`. This means ion's trajectories over a few micromotion cycles at these checkpoints should be stored. 

The data at each checkpoint is called a *snapshot*, and it is saved as a *single* HDF5 file. Each snapshot consists of several *frames*, where each frame contains all ion's positions and velocities, :math:`N_{\mathrm{ion}}\times 6` real numbers in total.





``OutputSnapshotWithHDf5Storage`` only take one string argument, which contains the following field

  .. code-block:: bash

    OutputSnapshotWithHDF5Storage your_spec.xml

``your_spec.xml`` points to an xml file which contains the following fields, 

  .. code-block:: xml

      <ConfigRoot>
        <OutputSnapshotWithHDF5Storage>
          <FileNamePattern>snapshot_%d.h5</FileNamePattern>
          <TimeQueue>
            <Entry>1000 0    1.000e-07</Entry>
            <Entry>1000 0.02 1.000e-07</Entry>
            <Entry>1000 0.04 1.000e-07</Entry>
            <Entry>1000 0.06 1.000e-07</Entry>
            <Entry>1000 0.08 1.000e-07</Entry>
            <Entry>1000 0.1  1.000e-07</Entry>
          </TimeQueue>
        </OutputSnapshotWithHDF5Storage>
      </ConfigRoot>


The meaning of these fields are given below:

+----------------+------------------------------+------------------------------------------------------------------------+
| Field          | Meaning                      | Specification                                                          |
+----------------+------------------------------+------------------------------------------------------------------------+
| FilenamePattern| pattern for shapshot files   | a string with '%d'. The %d part is replaced by 0,1, 2, ...             |
+----------------+------------------------------+------------------------------------------------------------------------+
| TimeQueue      | specification                | each entry consists of :math:`N_{i}`, :math:`t_{i}`, :math:`dt_ {i}`   |
+----------------+------------------------------+------------------------------------------------------------------------+


