Addon Module
============

An overview of addon module
---------------------------
The ``addon`` module provides support for simulation of AMO systems, which include

- ``ion_trap`` : support for ion trap simulation, also including harmonics trap
- ``buffergas``: support for sympathetic cooling by ultracode buffer gas
- ``damping``  : support for damping mechanism (laser-cooling or fictious damping)
- ``reaction`` : support for chemical reactions (replacement ... )

LQTForce
--------
The trapping force from the linear quadrupole trap and harmonic traps are provided with the keywords ``LQTForce`` and ``HarmonicTrapForce``. 

The ``LQTForce`` takes ``your_spec.xml`` as a required string argument after the ``-lqt-spec`` directive:

   .. code::

      LQTForce
      -lqt-spec your_spec.xml

where ``your_spec.xml`` is a xml file which should contain the following fields:
   .. code:: xml

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
| omega    | trap frequency                  | Hz       |
+----------+---------------------------------+----------+
| kappa    | geometrical factor              | NA       |
+----------+---------------------------------+----------+

HarmonicTrapForce
-----------------
HarmonicTrapForce simulates the force due to a haromical potential:

    .. math::

    n_{\mathrm{offset}} = \sum_{k=0}^{N-1} s_k n_k


The ``HarmonicTrapForce`` takes ``your_spec.xml`` as a required string argument after the ``-ht-spec`` directive:

   .. code::

      HarmonicTrapForce
      -ht-spec your_spec.xml


where ``your_spec.xml`` is a xml file which should contain the following fields:
   .. code:: xml

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
