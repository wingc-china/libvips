include_directories("include")

add_subdirectory(resample)
add_subdirectory(arithmetic)
add_subdirectory(colour)
add_subdirectory(conversion)
add_subdirectory(convolution)
add_subdirectory(foreign)
add_subdirectory(freqfilt)
add_subdirectory(histogram)
add_subdirectory(draw)
add_subdirectory(iofuncs)
add_subdirectory(morphology)
add_subdirectory(mosaicing)
add_subdirectory(create)

if(NOT NO_DEPRECATED)
  add_subdirectory(deprecated)
  set(OPTIONAL_LIB $<TARGET_OBJECTS:libdeprecated>)
else()
  set(OPTIONAL_LIB "")
endif()

add_library(${PROJECT_NAME} SHARED
  $<TARGET_OBJECTS:libresample>
  $<TARGET_OBJECTS:libarithmetic>
  $<TARGET_OBJECTS:libcolour>
  $<TARGET_OBJECTS:libconversion>
  $<TARGET_OBJECTS:libconvolution>
	${OPTIONAL_LIB}
  $<TARGET_OBJECTS:libforeign>
  $<TARGET_OBJECTS:libfreqfilt>
  $<TARGET_OBJECTS:libhistogram>
  $<TARGET_OBJECTS:libdraw>
  $<TARGET_OBJECTS:libiofuncs>
  $<TARGET_OBJECTS:libmorphology>
  $<TARGET_OBJECTS:libmosaicing>
  $<TARGET_OBJECTS:libcreate>
  # TODO ${VIPS_LIBS}
)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:\"libcmt\" /NODEFAULTLIB:\"libcmtd\"")

find_package(EXPAT REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE EXPAT::EXPAT)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::glib::gio
  unofficial::glib::glib
  unofficial::glib::gmodule
  unofficial::glib::gobject)