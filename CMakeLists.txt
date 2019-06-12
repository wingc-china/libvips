cmake_minimum_required(VERSION 3.0.0)

project(libvips VERSION "8.7.4")

# NOTE: On Windows, this does nothing except when using MinGW or Cygwin.
# CMAKE_BUILD_TYPE has no meaning in Visual Studio, and it always defaults to
# Debug when using NMake.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

if (NOT INSTALL_DIR)
  set(INSTALL_DIR "C:\\libvips")
endif()

# Detect CPU type and whether we're building 64-bit or 32-bit code
math(EXPR BITS "${CMAKE_SIZEOF_VOID_P} * 8")
string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} CMAKE_SYSTEM_PROCESSOR_LC)
if(CMAKE_SYSTEM_PROCESSOR_LC MATCHES "x86_64" OR
  CMAKE_SYSTEM_PROCESSOR_LC MATCHES "amd64" OR
  CMAKE_SYSTEM_PROCESSOR_LC MATCHES "i[0-9]86" OR
  CMAKE_SYSTEM_PROCESSOR_LC MATCHES "x86" OR
  CMAKE_SYSTEM_PROCESSOR_LC MATCHES "ia32")
  if(BITS EQUAL 64)
    set(CPU_TYPE x86_64)
  else()
    set(CPU_TYPE i386)
  endif()
  if(NOT CMAKE_SYSTEM_PROCESSOR STREQUAL ${CPU_TYPE})
    set(CMAKE_SYSTEM_PROCESSOR ${CPU_TYPE})
  endif()
elseif(CMAKE_SYSTEM_PROCESSOR_LC STREQUAL "aarch64" OR
  CMAKE_SYSTEM_PROCESSOR_LC MATCHES "arm*64*")
  set(CPU_TYPE arm64)
elseif(CMAKE_SYSTEM_PROCESSOR_LC MATCHES "arm*")
  set(CPU_TYPE arm)
elseif(CMAKE_SYSTEM_PROCESSOR_LC MATCHES "ppc*" OR
  CMAKE_SYSTEM_PROCESSOR_LC MATCHES "powerpc*")
  set(CPU_TYPE powerpc)
else()
  set(CPU_TYPE ${CMAKE_SYSTEM_PROCESSOR_LC})
endif()
message(STATUS "${BITS}-bit build (${CPU_TYPE})")

configure_file(
    ${PROJECT_SOURCE_DIR}/configure.in
    ${PROJECT_SOURCE_DIR}/libvips/include/config.h
)

if(MSVC)
  # As we have our own config.h generated from the configure.in
  add_compile_definitions(HAVE_CONFIG_H)
  # OS_WIN32 has nothing to do with 32 or 64bit binary build, it just is a flag for Windows platform code to build
  add_compile_definitions(OS_WIN32)
endif()

#TODO: VIPS_LIBS="$ZLIB_LIBS $MAGICK_LIBS $PNG_LIBS $IMAGEQUANT_LIBS $TIFF_LIBS $JPEG_LIBS $GTHREAD_LIBS $REQUIRED_LIBS $EXPAT_LIBS $PANGOFT2_LIBS $GSF_LIBS $FFTW_LIBS $ORC_LIBS $LCMS_LIBS $GIFLIB_LIBS $RSVG_LIBS $NIFTI_LIBS $PDFIUM_LIBS $POPPLER_LIBS $OPENEXR_LIBS $OPENSLIDE_LIBS $CFITSIO_LIBS $LIBWEBP_LIBS $LIBWEBPMUX_LIBS $MATIO_LIBS $EXIF_LIBS -lm"

add_subdirectory(libvips)
#TODO add_subdirectory(cplusplus)
add_subdirectory(tools)
#add_subdirectory(po)
#add_subdirectory(man)
#add_subdirectory(doc)
#add_subdirectory(test)
