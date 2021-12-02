add_library(Geom ${Geom_SRC_DIR}/GEOMUtils/GEOMUtils.cxx)
target_link_libraries(Geom Kernel TKBRep TKShHealing TKMesh TKGeomAlgo TKTopAlgo TKG2d TKG3d TKV3d TKGeomBase TKBO)
target_include_directories(Geom PUBLIC
  $<BUILD_INTERFACE:${Geom_SRC_DIR}/GEOMUtils>
  $<INSTALL_INTERFACE:include/smesh/Geom>
)

if(WIN32)
  set_target_properties(Geom PROPERTIES COMPILE_FLAGS
    "-DUTILS_EXPORTS \
     -DSMESH_ONLY \
     -DSALOME_LIGHT \
     -DSALOME_LIGHT_ONLY")
else()
  set_target_properties(Geom PROPERTIES COMPILE_FLAGS
    "-DSMESH_ONLY \
     -DSALOME_LIGHT \
     -DSALOME_LIGHT_ONLY")
endif()
set(CMAKE_VERBOSE_MAKEFILE ON)

install(FILES ${Geom_SRC_DIR}/GEOMUtils/GEOMUtils.hxx DESTINATION "include/smesh/Geom")

set(Geom_LIBRARIES Geom)
