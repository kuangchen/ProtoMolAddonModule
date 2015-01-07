Write Your Own Component
=======================
Writing your own forces/integrators/outputs is described in detail in the ``ProtoMol`` how-to guide. Interested readers are highly suggested to read the guide.

However, the instructions provided by the guide is quite tedious: similar code need be written each time a new force/integrator/output is created. The situation is only made worse by the fact ``ProtoMol`` uses a different system from SI. 

To alleviate the problem, a ``C++`` template has been introduced, which enables the user the focus more on the physical and mathematical part of the simulation problem, instead of spending time interfacing with ``ProtoMol``.

This chapter explains how to use the template class through three examples.

Implement a new force
---------------------
Suppose we would like to implement the new force :math:`\vec{F}` due to a stray electric field :math:`\vec{E}`, 

.. math::

   \vec{F}(x, y, z) = e\vec{E}(x, y, z)

where :math:`e` is the charge of the particle.

To be compatible with the generic force template, the force would have the following syntax in ``ProtoMol``, 

.. code-block:: bash
      
   StrayFieldForce
   -stray-field-spec your_spec.xml

where :code:`StrayFieldForce` is the *force name*, :code:`-stray-field-spec` is force's *parameter name*. The single string argument after the parameter name, ``your_spec.xml``, contains the information about :math:`E`. In the current implementation, the external file is in self-explainatory xml format. Nevertheless, you are free to choose the format you want (plain text, csv, *etc*).

Below is the header file:

.. code-block:: cpp

   // addon/stray_field.h
   #ifndef _STRAY_FIELD_H
   #define _STRAY_FIELD_H
   
   #include <protomol/addon/util/ConstSIAtomProxy.h>
   #include <protomol/type/Vector3D.h>
   #include <iosfwd>
   
   namespace ProtoMolAddon {
     namespace Util {
       class ConstSIAtomProxy;
     }
   
     namespace StrayField {
   
       using namespace ProtoMol;
   
       class StrayField {
       public:
         struct Spec {
           Vector3D field;
   
           Spec() {}
           Spec(const std::string &fname);
         };
   
       private:
         Spec spec;
   
       public:
         StrayField() {}
         StrayField(const Spec &spec);
   
         static std::string GetName() { return "StrayFieldForce"; }
	 
         static std::string GetParameterName() { return "-stray-field-spec"; }
   
         Vector3D GetForce(const Util::ConstSIAtomProxy &atom, double now) const;
       };
     }
   }
   
   #endif


and below is the cpp file.

.. code-block:: cpp

   #include <protomol/addon/stray_field/StrayField.h>
   #include <protomol/addon/Constants.h>
   #include <boost/property_tree/ptree.hpp>
   #include <boost/property_tree/xml_parser.hpp>
   #include <boost/algorithm/string.hpp>
   #include <iostream>
   
   namespace ProtoMolAddon {
     namespace StrayField {
   
       namespace pt = boost::property_tree;
       namespace algorithm = boost::algorithm;
   
       StrayField::Spec::Spec(const std::string &fname) {
         pt::ptree tree;
         pt::read_xml(fname, tree);
         field = tree.get<Vector3D>("ConfigRoot.StrayField");
       }
       
       StrayField::StrayField(const StrayField::Spec &spec): spec(spec) {}
   
       Vector3D StrayField::GetForce(const Util::ConstSIAtomProxy &atom, double now) const {
         return spec.field * atom.GetCharge();
       }
       
     }
   }
   

Here are the steps involved.  

   
1. Create a new ``C++`` class (in this case, ``StrayField``), and add necessary private variables.

2. Create a class constructor that takes a single string argument. Also provide a default constructor that takes no argument.  

3. Create a static :code:`GetName()` method with the signature:

   .. code-block:: cpp

      static std::string GetName();

   which returns the keyword for the force in :code:`ProtoMol`. 

4. Create a static :code:`GetParameterName()` method with the signature:

   .. code-block:: cpp
  
      static std::string GetParameterName();
   
   which return the parameter name specific to this force, whose value is always a string. 


5. Create a :code:`GetForce()` method with the signature:

   .. code-block:: cpp

     Vector3D GetForce(const Util::ConstSIAtomProxy &atom, double now) const;

   This method computes the force on each atom. Note that this method operates on a constant atom proxy, thus does not modify atom's position/velocity/label. ``now`` is the current simulation time in second. The returned value is the force on that atom also in SI unit. 

6. Register the new force in the ``AddonModule.cpp``, by including the header file

  .. code-block:: cpp

     #include <addon/stray_field/StrayField.h> 

  and add these two lines 

  .. code-block:: cpp

     if (equalNocase(boundConds, PeriodicBoundaryConditions::keyword)) {
       // ...
       f.registerExemplar(new Template::GenericForce<PeriodicBoundaryConditions, StrayField::FieldForce>());
     }
   
  and 

  .. code-block:: cpp

     if (equalNocase(boundConds, PeriodicBoundaryConditions::keyword)) {
       // ...
       f.registerExemplar(new Template::GenericForce<VacuumBoundaryConditions, StrayField::StrayField>()); # Step 7
     }
   

8. Re-compile the source code

   .. code-block:: bash

      cmake .
      make 
      sudo make install

   and then check if the force has been successfully added to the system.

   .. code-block:: bash
		   
      ~$:ProtoMol --forces

      =+=+=+=+=+=+=+=+=+=+= Forces periodic boundary conditions =+=+=+=+=+=+=+=+=+=+=+
      ...
      StrayFieldForce
      -stray-field-spec      <string=>                     
      ...

      =+=+=+=+=+=+=+=+=+=+=+ Forces vacuum boundary conditions +=+=+=+=+=+=+=+=+=+=+=+

      StrayFieldForce
      -stray-field-spec         <string=>                     



Implement a new integrator
--------------------------
Suppose we would like to simulate evaporation of trapped ions, i.e. an ion which escapes the trapping region (a cylindrial volume defined by radius :math:`r_0` and :math:`z_0`) is considered forever lost and does not exert Coulomb force on the still trapped ions.

To be compatible with the generic integrator template, the integrator would have the following syntax in ``ProtoMol``,

.. code:: bash

   Evaporation
   -evaporation-spec your_spec.xml

where ``Evaporation`` is the integrator *name*, ``-evaporation-spec`` is the integrator's *parameter* name. The single string argument after the parameter name, ``your_spec.xml``, contains the information about :math:`r_0` and :math:`x_0`. In the current implementation, the external file is in self-explainatory xml format. Nevertheless, you are free to choose the format you want (plain text, csv, *etc*).


Here is the header file:

.. code-block:: cpp

   #ifndef _EVAPORATION_H
   #define _EVAPORATION_H
   
   #include <string>
   #include <memory>
   #include <protomol/ProtoMolApp.h>
   #include <protomol/addon/util/SIAtomProxyArray.h>
   
   namespace ProtoMolAddon {
     namespace Util {
       class SIAtomProxyArray;
     }
     
     namespace Reaction {
   
       using namespace ProtoMol;
       
       class Evaporation {
       private:
         struct Spec {
   	double r0;
   	double z0;
   	Spec() : r0(0), z0(0) {}
   	Spec(const std::string &fname);
         };
   
         Spec spec;
         std::unique_ptr<Util::SIAtomProxyArray> ap_array_ptr;
         
       public:
         Evaporation() {}
         Evaporation(const Spec &spec) : spec(spec) {}
   
       public:
         void Initialize(ProtoMolApp *app);
         void Update(double now, double dt);
         
         static const std::string GetName() { return "Evaporation"; }
         static const std::string GetParameterName() { return "-evaporation-spec"; }
       };
     }
   }
   
   #endif
   

Here is the cpp file:

.. code-block:: cpp

   #include <protomol/addon/reaction/Evaporation.h>
   #include <boost/property_tree/xml_parser.hpp>
   
   namespace ProtoMolAddon {
     namespace Reaction {
   
       namespace pt = boost::property_tree;
   
       Evaporation::Spec::Spec(const std::string &fname) {
         pt::ptree tree;
         pt::read_xml(fname, tree);
   
         r0 = tree.get<double>("ConfigRoot.Evaporation.r0");
         z0 = tree.get<double>("ConfigRoot.Evaporation.z0");
       }
       
       void Evaporation::Initialize(ProtoMolApp *app) {
         ap_array_ptr.reset(new Util::SIAtomProxyArray(app));
       }
   
       void Evaporation::Update(double now, double dt) {
         for (auto &ap: *ap_array_ptr) {
   	   const Vector3D &pos = ap.GetPosition();
   
   	   if ( (ap.GetIntegerCharge()!=0) &&
   	        ((pos[0]*pos[0] + pos[1]*pos[1]) > spec.r0 * spec.r0 ||
   	         (fabs(pos[2]) > spec.z0)) )
   	     ap.SetIntegerCharge(0);
         }
       }
     }
   }
    
Here are the steps involved:

1. Create a new ``C++`` class (in this case, ``CEM``), and add necessary private variables.

2. Create a class constructor that takes a single string argument. Also provide a default constructor that takes no argument.  

3. Create a static :code:`GetName()` method with the signature:

   .. code-block:: cpp

      static std::string GetName();

   which returns the keyword for the integrator in :code:`ProtoMol`. 

4. Create a static :code:`GetParameterName()` method with the signature:

   .. code-block:: cpp
  
      static std::string GetParameterName();
   
   which return the parameter name specific to this integrator, whose value is always a string. 


5. Create a :code:`Initialize()` method with the signature:

   .. code-block:: cpp

     void Initialize(const ProtoMolApp *app);

   This function is called before the numerical integration starts. So it is handy to do initialization work here. In this case, the ``app`` pointer is used to initialize an array of atom proxy.

6. Create an :code:`Update()` method with the signature:

   .. code-block:: cpp

      void Update(double now);

   This function is called at every integration step. In this case, ion's position is checked, and if the ion escape the trapping region, ion's charge is set to zero (a trick which makes ion not subject to trapping force and Coulomb force). ``now`` is the current simulation time in second.

7. Register the new integrator in ``AddonModule.cpp``. First include the header file:

   .. code-block:: cpp

      #include <addon/reaction/Evaporation.h>

   and add the following line in 

   .. code-block:: cpp

      void AddonModule::init(ProtoMol::ProtoMolApp *app) {
        IntegratorFactory &i = app->integratorFactory;
	// Add new integrator below
	i.registerExemplar(new Template::GenericIntegrator<Reaction::Evaporation>());
	// ...
	// ...
      }

8. Re-compile the source code

   .. code-block:: bash

      cmake .
      make
      sudo make install

   and then check if the output has been successfully added to the system:

   .. code-block:: bash

      ~$: ProtoMol --integrators
      =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+= Integrators =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
      ... 
      ... 
      Evaporation
      timestep                  <real,positive>               
      -evaporation-spec         <string,non-empty>            
      ... 
      ... 



Implement a new output
----------------------
Suppose we would like to simulate the time-of-flight and ions' position/velocity when ions hit a channel electron multiplier (CEM). The multipler is approximated as a circular area with radius :math:`r_{cem}` and position :math:`x_{cem}` along the ejection direction.

To be compatible with the generic output template, the output would have the following syntax in ``ProtoMol``,

.. code:: bash

   CEM
   -cem-spec your_spec.xml

where ``CEM`` is the output *name*, ``-cem-spec`` is the output's *parameter* name. The single string argument after the parameter name, ``your_spec.xml``, contains the information about :math:`r_{cem}` and :math:`x_{cem}`. In the current implementation, the external file is in self-explainatory xml format. Nevertheless, you are free to choose the format you want (plain text, csv, *etc*).

Here is the header file:

.. code-block:: cpp

   #ifndef _CEM_H
   #define _CEM_H
   
   #include <protomol/type/Vector3DBlock.h>
   #include <protomol/addon/util/ConstSIAtomProxyArray.h>
   #include <memory>
   #include <map>
   #include <vector>
   #include <string>
   #include <iosfwd>
   
   namespace ProtoMolAddon {
   
     namespace Util {
       class ConstSIAtomProxy;
       class ConstSIAtomProxyArray;
     }
     
     namespace ToF {
       
       using namespace ProtoMol;
   
       class CEM {
       public:
         typedef enum ion_status { flying = 0, hit = 1 } ion_status;
         
         struct Spec {
   	   double x_cem;
   	   double r_cem;
   	   std::string fname;
   
   	   Spec() {}
   	   Spec(const std::string &fname);
         };
   
         struct HitEntry {
   	   double t;
   	   Vector3D pos;
   	   Vector3D vel;

	   HitEntry(double t, Vector3D pos, Vector3D vel) :
   	     t(t), pos(pos), vel(vel) {}
   
   	   HitEntry() {}
         };
         
       private:
         Spec spec;
         std::map<Util::ConstSIAtomProxy, HitEntry> hit_entry_map;
         std::unique_ptr<Util::ConstSIAtomProxyArray> ap_array_ptr;
         
       public:
         CEM() {}
         CEM(const Spec &spec);
         
         void Initialize(const ProtoMolApp *app);
         void Update(double now);
         void Finalize();
   
         static std::string GetName() { return "CEM"; }
         static std::string GetParameterName() { return "-cem-spec"; }
       };
   
     }
   }
   
   
   #endif
   
and here is the cpp file:

.. code-block:: cpp

   #include <protomol/addon/tof/CEM.h>
   #include <iostream>
   #include <boost/property_tree/ptree.hpp>
   #include <boost/property_tree/xml_parser.hpp>
   #include <boost/algorithm/string.hpp>
   
   namespace ProtoMolAddon {
     namespace ToF {
   
       namespace pt = boost::property_tree;
       namespace algorithm = boost::algorithm;
       
       CEM::Spec::Spec(const std::string &conf_fname) {
         pt::ptree tree;
         pt::read_xml(conf_fname, tree);
   
         x_cem = tree.get<double>("ConfigRoot.CEM.x_cem");
         r_cem = tree.get<double>("ConfigRoot.CEM.r_cem");
         fname = tree.get<std::string>("ConfigRoot.CEM.fname");
         algorithm::trim(fname);
       }
   
       CEM::CEM(const CEM::Spec &spec) :
         spec(spec) {
       }
   
       void CEM::Initialize(const ProtoMolApp *app) {
         ap_array_ptr.reset(new Util::ConstSIAtomProxyArray(app));
       }
   
       void CEM::Update(double now) {
         for (auto ap: *ap_array_ptr) {
   	   if (hit_entry_map.count(ap) == 0) {
   	     const Vector3D &pos = ap.GetPosition();
   	     if (pos[0] > spec.x_cem &&
   	        ((pos[1]*pos[1] + pos[2]*pos[2]) < spec.r_cem * spec.r_cem))
               hit_entry_map[ap] = HitEntry(now, pos, ap.GetVelocity());
   	   }
         }
       }
   
       void CEM::Finalize() {
         std::ofstream os(spec.fname);
         
         for (auto &kv: hit_entry_map) {
           os << kv.first.GetName() << "\t"
   	      << kv.second.t << "\t"
              << kv.second.pos << "\t"
   	      << kv.second.vel << std::endl;
         }
       }
     }
   }
   
Here are the steps involved:

1. Create a new ``C++`` class (in this case, ``CEM``), and add necessary private variables.

2. Create a class constructor that takes a single string argument. Also provide a default constructor that takes no argument.  

3. Create a static :code:`GetName()` method with the signature:

   .. code-block:: cpp

      static std::string GetName();

   which returns the keyword for the output in :code:`ProtoMol`. 

4. Create a static :code:`GetParameterName()` method with the signature:

   .. code-block:: cpp
  
      static std::string GetParameterName();
   
   which return the parameter name specific to this output, whose value is always a string. 


5. Create a :code:`Initialize()` method with the signature:

   .. code-block:: cpp

     void Initialize(const ProtoMolApp *app);

   This function is called before the numerical integration starts. So it is handy to do initialization work here. In this case, the ``app`` pointer is used to initialize an array of constant atom proxy.

6. Create an :code:`Update()` method with the signature:

   .. code-block:: cpp

      void Update(double now);

   This function is called everytime an output event (specified by ``outputfreq`` keyword in the configuration file) occurs. In this case, atom's position is checked and get saved if the atom hit the detector screen for the first time. ``now`` is the current simulation time in second.

7. Create a :code:`Finalize()` method with the signature:

   .. code-block:: cpp

      void Finalize()

   This function is called after the numerical integration is finished. In this case, atom's information saved in the ``Update()`` step is written to a pre-specified external file. 

8. Register the new output in ``AddonModule.cpp``. First include the header file:

   .. code-block:: cpp

      #include <addon/tof/CEM.h>

   and add the following line in 

   .. code-block:: cpp

      void AddonModule::init(ProtoMol::ProtoMolApp *app) {
        OutputFactory &f = app->outputFactory;
	// Add new output below
	f.registerExemplar(new Template::GenericOutput<ToF::CEM>());
	// ...
	// ...
      }

9. Re-compile the source code

   .. code-block:: bash

      cmake .
      make
      sudo make install

   and then check if the output has been successfully added to the system:

   .. code-block:: bash

      ~$: ProtoMol --outputs

      =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+= Outputs =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
      ... 
      ... 
      CEM
      -cem-spec                 <string,non-empty>            
      ... 
      ... 

