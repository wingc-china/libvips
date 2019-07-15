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
)

  target_compile_options(
    ${PROJECT_NAME} PRIVATE 
    "/W3 /nologo /EHsc"
    "$<$<CONFIG:Debug>:/MTd /Od /Ob0 /Zi /RTC1 /DDEBUG /D_DEBUG>"
    "$<$<CONFIG:Release>:/MT /O2 /Ob2 /DNDEBUG>"
  )

# For the link warning LNK4098: defaultlib 'LIBCMTD' conflicts with use of other libs...
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt /NODEFAULTLIB:libcmtd")

find_package(EXPAT REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE EXPAT::EXPAT)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::glib::gio
  unofficial::glib::glib
  unofficial::glib::gmodule
  unofficial::glib::gobject)

#TODO: VIPS_LIBS="$ZLIB_LIBS $MAGICK_LIBS $IMAGEQUANT_LIBS $TIFF_LIBS $GTHREAD_LIBS $REQUIRED_LIBS $PANGOFT2_LIBS $GSF_LIBS $FFTW_LIBS $ORC_LIBS $LCMS_LIBS $GIFLIB_LIBS $RSVG_LIBS $NIFTI_LIBS $PDFIUM_LIBS $POPPLER_LIBS $OPENEXR_LIBS $OPENSLIDE_LIBS $CFITSIO_LIBS $MATIO_LIBS $EXIF_LIBS -lm"

#TODO swtich between JPEG, JPEG-turbo and JPEG-moz
if(NOT JPEG_TURBO OR JPEG_MOZ)
  find_package(JPEG REQUIRED)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${JPEG_LIBRARIES})
endif()

# ./vcpkg install libpng:x64-windows-static
find_package(PNG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PNG_LIBRARIES})

# ./vcpkg install libwebp[all]:x64-windows-static
find_package(WebP CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${WebP_LIBRARIES})

# ./vcpkg install libexif[all]:x64-windows-static
find_library(EXIF_LIB NAMES libexif)
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXIF_LIB})
