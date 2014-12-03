Write Your Own Component
=======================
This chapter discusses how to write your own forces, integrators and outputs.


Implement a new force
---------------------

In the ``ProtoMol`` how-to guide, there is a chapter with detailed instructions on implementing a new force. The procedure is tedious, and has to repeated each time a new force needs to be implemented. To simplify this process a generic force C++ template is introduced, which enables user to focus more on mathematical part and less on interfacing with :code:`ProtoMol`, with little loss of the flexibility how the force is specified in :code:`ProtoMol`. 

Suppose we would like to implement the new force due to a stray electric field, 

  .. math::
     \vec{F}(x, y, z) = e\vec{E}(x, y, z)

where :math:`\vec{E}(x, y, z)` is the stray electric field, and :math:`e` is the charge of the particle. To be compatible with the generic force template, the information about :math:`E` is moved into a single external file, whose name is the argument after the parameter keyword :code:`-stray-field-spec`. In :code:`ProtoMol`, the force would have the following syntax,

   .. code-block:: xml
      
      StrayFieldForce
      -stray-field-spec your_spec.xml

where :code:`StrayFieldForce` is the *force name*, :code:`-stray-field-spec` is force's *parameter name*. 
In the current implementation, the external file is in self-explainatory xml format. Nevertheless, you are free to choose the format you want (plain text, csv, *etc*).

Here are the steps involved:

   .. code-block:: cpp

      #ifndef _STRAY_FIELD_H
      #define _STRAY_FIELD_H
      
      #include <protomol/addon/util/SIAtomProxy.h>
      #include <protomol/type/Vector3D.h>
      
      namespace ProtoMolAddon {
        namespace Util {
          class ConstSIAtomProxy; // Forward declaration of the proxy class
        }
      
        using namespace ProtoMol;
      
        class StrayField {  // Step #1
	private:
	  Vector3D field;   // Step #1
      
        public:
          StrayField() {}   // Step #2, default constructor
          StrayField(const std::string &fname);  // Step #2, constructor with a string
      
          static std::string GetName() { return "StrayFieldForce"; } // Step 3, set force name

          static std::string GetParameterName() { return "-stray-field-spec"; } // Step 4, set force parameter name
          Vector3D GetForce(const Util::ConstSIAtomProxy &atom, double now) const;  // Step 5, compute the force
        };
      }
    
          
      #endif

1. Create a new ``C++`` class (e.g. ``MyStrayField``), preferably in the :code:`ProtoMolAddon` namespace. Add any private variables in a header file.

2. Create a class constructor that takes a single string argument. Also provide a default constructor that takes no argument.  

3. Create a :code:`GetName()` method with the signature:

   .. code-block:: cpp

      static std::string GetName();

   which returns the keyword for the force in :code:`ProtoMol`. 

4. Create a :code:`GetParameterName()` method with the signature:

   .. code-block:: cpp
  
      static std::string GetParameterName();
   
   which return the parameter name specific to this force, whose value is always a string. 


5. Create a :code:`GetForce()` method with the signature:

   .. code-block:: cpp

     Vector3D GetForce(const Util::ConstSIAtomProxy &atom, double now) const;

   This method computes the force on each atom. 

6. Implement the details of class constructor and method :code:`GetForce()` in a cpp file.

   .. code-block:: cpp
		   
      #include <protomol/addon/MyStrayField.h>
		   
      MyStrayField::MyStrayField(const std::string &fname)
		   : field()
      {
        // Open the file and read the content into field
        std::ifstream is(fname);		   
	is >> field;
      }

      Vector3D MyStrayField::GetForce(const Util::ConstSIAtomProxy &atom, double now) const {
        return field * atom.GetCharge();
      }

   Note that :code:`atom` is an proxy class which facilitates unit conversion between SI and :code:`ProtoMol`. The returned force is in SI unit.

7. Register the new force in the :code:`AddonModule.cpp`:

- include the header file 

  .. code-block:: cpp

     #include <addon/MyStrayFieldForce.h> # Step 7, change to the path on your system

- add these two lines

  .. code-block:: cpp

     if (equalNocase(boundConds, PeriodicBoundaryConditions::keyword)) {
       // ...
       f.registerExemplar(new Template::GenericForce<PeriodicBoundaryConditions, MyStrayFieldForce>()); # Step 7
     }
   
  and 

  .. code-block:: cpp

     if (equalNocase(boundConds, PeriodicBoundaryConditions::keyword)) {
       // ...
       f.registerExemplar(new Template::GenericForce<VacuumBoundaryConditions, MyStrayFieldForce>()); # Step 7
     }
   

8. Re-compile the source code

   .. code-block:: bash

      cmake .
      make 
      sudo make install

   and then check if the force has been successfully added to the system.

   .. code-block:: bash
		   
      ~$:ProtoMol --forces
      
      ...
      MyStrayFieldForce
      -my-stray-field-spec      <string=>                     
      ...
      


Implement a new integrator
--------------------------

