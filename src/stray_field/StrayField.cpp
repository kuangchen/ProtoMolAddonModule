#include <protomol/addon/stray_field/StrayField.h>
#include <protomol/addon/Constants.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

namespace pt = boost::property_tree;
namespace algorithm = boost::algorithm;

namespace ProtoMolAddon {
  namespace StrayField {
    
    StrayField::Spec::Spec(const std::string &fname) {
      pt::ptree tree;
      pt::read_xml(fname, tree);
      field = tree.get<Vector3D>("ConfigRoot.StrayField");
    }
    
    
    StrayField::StrayField(const StrayField::Spec &spec): spec(spec) {}

    
    Vector3D StrayField::GetForce(const Util::ConstSIAtomProxy &atom, double now) const {
      return spec.field * atom.GetCharge();
    }

    std::ostream& operator<< (std::ostream &os, const StrayField &f) {
      os << "Stray Electric Field = "
	 << f.spec.field
	 << "\n===========================\n";
	
      return os;
    }
  }
}




