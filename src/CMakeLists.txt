project( ProtoMol )
cmake_minimum_required( VERSION 2.6 )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
SET(CMAKE_CXX_FLAGS "-std=c++0x -O2")
add_definitions (-fpermissive -Wall -s -O2 -g -DARCHLINUX)

find_package(Boost REQUIRED COMPONENTS program_options property_tree)

set (HDF5_FIND_COMPONENTS CXX)
find_package(HDF5 REQUIRED ${HDF5_FIND_COMPONENTS})  
if (HDF5_FOUND)
  include_directories( ${HDF5_INCLUDE_DIRS} )
  LIST( APPEND LIBS ${HDF5_LIBRARIES} )
endif (HDF5_FOUND)



# Library Addon Headers
file( GLOB ADDON_SNAPSHOT_HEADERS "src/protomol/addon/snapshot/*.h")
source_group( "include\\Addon" FILES ${ADDON_SNAPSHOT_HEADERS} )

file( GLOB ADDON_STRAYFIELD_HEADERS "src/protomol/addon/stray_field/*.h")
source_group( "include\\Addon\\StrayField" FILES ${ADDON_STRAYFIELD_HEADERS} )

file( GLOB ADDON_SEGMENTED_TRAP_HEADERS "src/protomol/addon/segmented_trap/*.h")
source_group( "include\\Addon\\SegmentedTrap" FILES ${ADDON_SEGMENTED_TRAP_HEADERS} )

file( GLOB ADDON_UTIL_HEADERS "src/protomol/addon/util/*.h")
source_group( "include\\Addon\\Util" FILES ${ADDON_UTIL_HEADERS} )

#file( GLOB ADDON_SYMPATHETIC_COOLING_HEADERS "src/protomol/addon/sympathetic_cooling/*.h" )
#source_group( "src\\Addons\\SympatheticCooling" FILES ${ADDON_SYMPATHETIC_COOING_HEADERS} )

file( GLOB ADDON_TEMPLATE_HEADERS "src/protomol/addon/template/*.h" )
source_group( "src\\Addons\\Template" FILES ${ADDON_TEMPLATE_HEADERS} )

file( GLOB ADDON_IONIZATION_HEADERS "src/protomol/addon/ionization/*.h" )
source_group( "src\\Addons\\Ionization" FILES ${ADDON_IONIZATION_HEADERS} )

file( GLOB ADDON_REACTION_HEADERS "src/protomol/addon/reaction/*.h" )
source_group( "src\\Addons\\Reaction" FILES ${ADDON_REACTION_HEADERS} )

file( GLOB ADDON_BUFFERGAS_HEADERS "src/protomol/addon/buffergas/*.h" )
source_group( "src\\Addons\\BufferGas" FILES ${ADDON_BUFFERGAS_HEADERS} )


set ( LIBRARY_ADDON_HEADERS ${ADDON_SNAPSHOT_HEADERS} ${ADDON_STRAYFIELD_HEADERS} ${ADDON_SEGMENTED_TRAP_HEADERS} ${ADDON_UTIL_HEADERS} ${ADDON_TEMPLATE_HEADERS} ${ADDON_IONZATION_HEADERS} ${ADDON_REACTION_HEADERS} ${ADDON_BUFFERGAS_HEADERS})

# Combined Headers
set( LIBRARY_HEADERS ${LIBRARY_BASE_HEADERS} ${LIBRARY_FOURCE_HEADERS} ${LIBRARY_INTEGRATOR_HEADERS} ${LIBRARY_IO_HEADERS} ${LIBRARY_ADDON_HEADERS} )

# Library sources
file( GLOB SOURCES "src/protomol/*.cpp" )
source_group( "src" FILES ${SOURCES} )
file( GLOB BASE_SOURCES "src/protomol/base/*.cpp" )
source_group( "src\\Base" FILES ${BASE_SOURCES} )
file( GLOB CONFIG_SOURCES "src/protomol/config/*.cpp" )
source_group( "src\\Config" FILES ${CONFIG_SOURCES} )
file( GLOB FACTORY_SOURCES "src/protomol/factory/*.cpp" )
source_group( "src\\Factory" FILES ${FACTORY_SOURCES} )
file( GLOB MODIFIER_SOURCES "src/protomol/modifier/*.cpp" )
source_group( "src\\Modifier" FILES ${MODIFIER_SOURCES} )
file( GLOB MODULE_SOURCES "src/protomol/module/*.cpp" )
source_group( "src\\Module" FILES ${MODULE_SOURCES} )
file( GLOB OS_SOURCES "src/protomol/os/*.cpp" )
source_group( "src\\OS" FILES ${OS_SOURCES} )
file( GLOB OUTPUT_SOURCES "src/protomol/output/*.cpp" )
source_group( "src\\Output" FILES ${OUTPUT_SOURCES} )
file( GLOB PARALLEL_SOURCES "src/protomol/parallel/*.cpp" )
source_group( "src\\Parallel" FILES ${PARALLEL_SOURCES} )
file( GLOB SWITCH_SOURCES "src/protomol/switch/*.cpp" )
source_group( "src\\Switch" FILES ${SWITCH_SOURCES} )
file( GLOB TOPOLOGY_SOURCES "src/protomol/topology/*.cpp" )
source_group( "src\\Topology" FILES ${TOPOLOGY_SOURCES} )
file( GLOB TYPE_SOURCES "src/protomol/type/*.cpp" )
source_group( "src\\Type" FILES ${TYPE_SOURCES} )

# Remove Application Sources
list( REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/protomol/main.cpp" )
list( REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/protomol/modules.cpp" )

set( LIBRARY_BASE_SOURCES ${SOURCES} ${BASE_SOURCES} ${CONFIG_SOURCES}
	${FACTORY_SOURCES} ${MODIFIER_SOURCES} ${MODULE_SOURCES} ${OS_SOURCES}
	${OUTPUT_SOURCES} ${PARALLEL_SOURCES} ${SWITCH_SOURCES} ${TOPOLOGY_SOURCES}
	${TYPE_SOURCES} )

if( NOT MSVC )
	file( GLOB DEBUG_SOURCES "src/protomol/debug/*.cpp" )
	source_group( "src\\Debug" FILES ${DEBUG_SOURCES} )

	set( LIBRARY_BASE_SOURCES ${LIBRARY_BASE_SOURCES} ${DEBUG_SOURCES} )
endif( NOT MSVC )

# Library Force sources
file( GLOB FORCE_SOURCES "src/protomol/force/*.cpp" )
source_group( "src\\Force" FILES ${FORCE_SOURCES} )
file( GLOB BONDED_FORCE_SOURCES "src/protomol/force/bonded/*.cpp" )
source_group( "src\\Force\\Bonded" FILES ${BONDED_FORCE_SOURCES} )
file( GLOB BORN_FORCE_SOURCES "src/protomol/force/born/*.cpp" )
source_group( "src\\Force\\Born" FILES ${BORN_FORCE_SOURCES} )
file( GLOB COULOMB_FORCE_SOURCES "src/protomol/force/coulomb/*.cpp" )
source_group( "src\\Force\\Coulomb" FILES ${COULOMB_FORCE_SOURCES} )
file( GLOB EXTENDED_FORCE_SOURCES "src/protomol/force/extended/*.cpp" )
source_group( "src\\Force\\Extended" FILES ${EXTENDED_FORCE_SOURCES} )
file( GLOB GB_FORCE_SOURCES "src/protomol/force/GB/*.cpp" )
source_group( "src\\Force\\GB" FILES ${GB_FORCE_SOURCES} )
file( GLOB HESSIAN_FORCE_SOURCES "src/protomol/force/hessian/*.cpp" )
source_group( "src\\Force\\Hessian" FILES ${HESSIAN_FORCE_SOURCES} )
file( GLOB NONBONDED_FORCE_SOURCES "src/protomol/force/nonbonded/*.cpp" )
source_group( "src\\Force\\NonBonded" FILES ${NONBONDED_FORCE_SOURCES} )
file( GLOB SYSTEM_FORCE_SOURCES "src/protomol/force/system/*.cpp" )
source_group( "src\\Force\\System" FILES ${SYSTEM_FORCE_SOURCES} )
file( GLOB TABLE_FORCE_SOURCES "src/protomol/force/table/*.cpp" )
source_group( "src\\Force\\Table" FILES ${TABLE_FORCE_SOURCES} )

set( LIBRARY_FOURCE_SOURCES ${FORCE_SOURCES} ${BONDED_FORCE_SOURCES}
	${BORN_FORCE_SOURCES} ${COULOMB_FORCE_SOURCES} ${EXTENDED_FORCE_SOURCES}
	${GB_FORCE_SOURCES} ${HESSIAN_FORCE_SOURCES} ${NONBONDED_FORCE_SOURCES}
	${SYSTEM_FORCE_SOURCES} ${TABLE_FORCE_SOURCES} )

# Library Integrator sources
file( GLOB INTEGRATOR_SOURCES "src/protomol/integrator/*.cpp" )
source_group( "src\\Integrator" FILES ${INTEGRATOR_SOURCES} )
file( GLOB BASE_INTEGRATOR_SOURCES "src/protomol/integrator/base/*.cpp" )
source_group( "src\\Integrator\\Base" FILES ${BASE_INTEGRATOR_SOURCES} )
file( GLOB HESSIAN_INTEGRATOR_SOURCES "src/protomol/integrator/hessian/*.cpp" )
source_group( "src\\Integrator\\Hessian" FILES ${HESSIAN_INTEGRATOR_SOURCES} )
file( GLOB LEAPFROG_INTEGRATOR_SOURCES "src/protomol/integrator/leapfrog/*.cpp" )
source_group( "src\\Integrator\\Leapfrog" FILES ${LEAPFROG_INTEGRATOR_SOURCES} )
file( GLOB NORMAL_INTEGRATOR_SOURCES "src/protomol/integrator/normal/*.cpp" )
source_group( "src\\Integrator\\Normal" FILES ${NORMAL_INTEGRATOR_SOURCES} )

if( BUILD_OPENMM )
    set( OPENMM_INTEGRATOR_SOURCES "src/protomol/integrator/openMM/OpenMMIntegrator.cpp" )
    if( BUILD_OPENMM_LTMD )
         set( OPENMM_INTEGRATOR_SOURCES ${OPENMM_INTEGRATOR_SOURCES} src/protomol/integrator/openMM/NormalModeOpenMM.cpp )
    endif( BUILD_OPENMM_LTMD )
    
    source_group( "src\\Integrator\\OpenMM" FILES ${OPENMM_INTEGRATOR_SOURCES} )
endif( BUILD_OPENMM )

set( LIBRARY_INTEGRATOR_SOURCES ${INTEGRATOR_SOURCES} ${BASE_INTEGRATOR_SOURCES}
	${HESSIAN_INTEGRATOR_SOURCES} ${LEAPFROG_INTEGRATOR_SOURCES}
	${NORMAL_INTEGRATOR_SOURCES} )

if( BUILD_OPENMM )
	set( LIBRARY_INTEGRATOR_SOURCES ${LIBRARY_INTEGRATOR_SOURCES} ${OPENMM_INTEGRATOR_SOURCES} )
endif( BUILD_OPENMM )

# Library IO sources
file( GLOB IO_SOURCES "src/protomol/io/*.cpp" )
source_group( "src\\IO" FILES ${IO_SOURCES} )
file( GLOB GROMACS_IO_SOURCES "src/protomol/io/gromacs/*.cpp" )
source_group( "src\\IO\\Gromacs" FILES ${GROMACS_IO_SOURCES} )

set( LIBRARY_IO_SOURCES ${IO_SOURCES} ${GROMACS_IO_SOURCES} )

# My add ons
file( GLOB ADDON_SOURCES "src/protomol/addon/*.cpp" )
source_group( "src\\Addons" FILES ${ADDON_SOURCES} )

file( GLOB ADDON_DAMPING_SOURCES "src/protomol/addon/damping/*.cpp" )
source_group( "src\\Addons\\Damping" FILES ${ADDON_DAMPING_SOURCES} )

file( GLOB ADDON_TOF_SOURCES "src/protomol/addon/tof/*.cpp" )
source_group( "src\\Addons\\ToF" FILES ${ADDON_TOF_SOURCES} )

file( GLOB ADDON_IONTRAP_SOURCES "src/protomol/addon/ion_trap/*.cpp" )
source_group( "src\\Addons\\ion_trap" FILES ${ADDON_IONTRAP_SOURCES} )

file( GLOB ADDON_UTIL_SOURCES "src/protomol/addon/util/*.cpp" )
source_group( "src\\Addons\\Util" FILES ${ADDON_UTIL_SOURCES} )

file( GLOB ADDON_SNAPSHOT_SOURCES "src/protomol/addon/snapshot/*.cpp" )
source_group( "src\\Addons\\Snapshot" FILES ${ADDON_SNAPSHOT_SOURCES} )

file( GLOB ADDON_STRAYFIELD_SOURCES "src/protomol/addon/stray_field/*.cpp" )
source_group( "src\\Addons\\StrayField" FILES ${ADDON_STRAYFIELD_SOURCES} )

file( GLOB ADDON_SEGMENTED_TRAP_SOURCES "src/protomol/addon/segmented_trap/*.cpp" )
source_group( "src\\Addons\\SegmentedTrap" FILES ${ADDON_SEGMENTED_TRAP_SOURCES} )

#file( GLOB ADDON_SYMPATHETIC_COOLING_SOURCES "src/protomol/addon/sympathetic_cooling/*.cpp" )
#source_group( "src\\Addons\\SympatheticCooling" FILES ${ADDON_SYMPATHETIC_COOING_SOURCES} )

file( GLOB ADDON_IONIZATION_SOURCES "src/protomol/addon/ionization/*.cpp" )
source_group( "src\\Addons\\Ionization" FILES ${ADDON_IONIZATION_SOURCES} )

file( GLOB ADDON_REACTION_SOURCES "src/protomol/addon/reaction/*.cpp" )
source_group( "src\\Addons\\Reaction" FILES ${ADDON_REACTION_SOURCES} )

file( GLOB ADDON_BUFFERGAS_SOURCES "src/protomol/addon/buffergas/*.cpp" )
source_group( "src\\Addons\\BufferGas" FILES ${ADDON_BUFFERGAS_SOURCES} )

# Combined sources
set( LIBRARY_SOURCES ${LIBRARY_BASE_SOURCES} ${LIBRARY_FOURCE_SOURCES} ${LIBRARY_INTEGRATOR_SOURCES} ${LIBRARY_IO_SOURCES} ${ADDON_SOURCES} ${ADDON_TOF_SOURCES} ${ADDON_DAMPING_SOURCES} ${ADDON_IONTRAP_SOURCES} ${ADDON_SNAPSHOT_SOURCES} ${ADDON_STRAYFIELD_SOURCES} ${ADDON_SEGMENTED_TRAP_SOURCES} ${ADDON_UTIL_SOURCES} ${ADDON_IONIZATION_SOURCES} ${ADDON_REACTION_SOURCES} ${ADDON_BUFFERGAS_SOURCES})

# Library Compilation
add_library( Library STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS} )
target_link_libraries( Library ${LIBS} )
target_link_libraries( Library ${Boost_LIBRARIES})

set_target_properties( Library PROPERTIES OUTPUT_NAME ProtoMol )

# Application Compilation
add_executable( Executable src/protomol/main.cpp src/protomol/modules.cpp )
target_link_libraries( Executable Library )

set_target_properties( Executable PROPERTIES OUTPUT_NAME ProtoMol )

install( TARGETS Executable RUNTIME DESTINATION bin )
