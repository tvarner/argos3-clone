#
# Robot headers
#  
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_PROTOTYPE_UTILITY
    utility/urdf/urdf_parser.h
    utility/urdf/joint.h
    utility/urdf/link.h
    utility/urdf/model.h)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_PROTOTYPE_SIMULATOR_ENTITIES
    simulator/entities/prototype_entity.h)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Robot sources
#
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_PROTOTYPE
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PROTOTYPE_UTILITY}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PROTOTYPE_SIMULATOR_ENTITIES}
    utility/urdf/urdf_parser.cpp
    utility/urdf/joint.cpp
    utility/urdf/link.cpp
    utility/urdf/model.cpp
    simulator/entities/prototype_entity.cpp)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Create the prototype plugin
#
add_library(argos3plugin_${ARGOS_BUILD_FOR}_prototype SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_PROTOTYPE})
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_prototype)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PROTOTYPE_SIMULATOR_ENTITIES}       DESTINATION include/argos3/plugins/robots/prototype/simulator/entities)
endif(ARGOS_BUILD_FOR_SIMULATOR)

install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_prototype
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)