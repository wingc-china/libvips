cmake_minimum_required(VERSION 3.0.0)

project(libvips VERSION "8.7.4")

# NOTE: On Windows, this does nothing except when using MinGW or Cygwin.
# CMAKE_BUILD_TYPE has no meaning in Visual Studio, and it always defaults to
# Debug when using NMake.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE} (only if build using MinGW or Cygwin)")

#include("windows.cmake")

if(NOT INSTALL_DIR)
  set(INSTALL_DIR "C:\\libvips")
endif()

#TODO Should be true if building libvips as dll...
if(NOT CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
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

if (MSVC)
  # As we have our own config.h generated from the configure.in
  add_compile_definitions(HAVE_CONFIG_H)

  # OS_WIN32 has nothing to do with 32 or 64bit binary build, it just is a flag for Windows platform code to build
  add_compile_definitions(OS_WIN32)

  # Have to set this BINARY_OPEN else the JPEG and PNG files cannot be parsed correctly.
  add_compile_definitions(BINARY_OPEN)

  # To make sure GLib using code does not init with gthread_init(), which is deprecated.
  add_compile_definitions(HAVE_THREAD_NEW)

  # TODO: As now my Expat is installed by the vcpkg as static, to make build pass I have to have this XML_STATIC
  #       However it should be a flag by if the Expat is linked in statically or dynamically.
  add_compile_definitions(XML_STATIC)

  # TODO: moz-jpeg might need to turn HAVE_JPEG_EXT_PARAMS on
  #add_compile_definitions(HAVE_JPEG_EXT_PARAMS)
endif()

add_subdirectory(libvips)
#TODO add_subdirectory(cplusplus)
add_subdirectory(tools)
#add_subdirectory(po)
#add_subdirectory(man)
#add_subdirectory(doc)
#add_subdirectory(test)
