# Because JPEG, PNG and WebP are must have...
add_compile_definitions(HAVE_JPEG 
  HAVE_PNG
  HAVE_LIBWEBP)

add_library(libforeign OBJECT
  analyze2vips.c
  analyzeload.c
  cairo.c
  csv.c
  csvload.c
  csvsave.c
  dzsave.c
  exif.c
  fits.c
  fitsload.c
  fitssave.c
  foreign.c
  gifload.c
  heifload.c
  heifsave.c
  jpeg2vips.c
  jpegload.c
  jpegsave.c
  magick.c
  magick2vips.c
  magick7load.c
  magickload.c
  magicksave.c
  matlab.c
  matload.c
  matrixload.c
  matrixsave.c
  niftiload.c
  niftisave.c
  openexr2vips.c
  openexrload.c
  openslide2vips.c
  openslideload.c
  pdfiumload.c
  pdfload.c
  pngload.c
  pngsave.c
  ppm.c
  ppmload.c
  ppmsave.c
  quantise.c
  radiance.c
  radload.c
  radsave.c
  rawload.c
  rawsave.c
  svgload.c
  tiff.c
  tiff2vips.c
  tiffload.c
  tiffsave.c
  vips2jpeg.c
  vips2tiff.c
  vips2webp.c
  vipsload.c
  vipspng.c
  vipssave.c
  webp2vips.c
  webpload.c
  webpsave.c
)

find_package(unofficial-glib CONFIG REQUIRED)
target_link_libraries(libforeign PRIVATE unofficial::glib::gio unofficial::glib::glib unofficial::glib::gmodule unofficial::glib::gobject)

#TODO swtich between JPEG, JPEG-turbo and JPEG-moz
if(NOT JPEG_TURBO OR JPEG_MOZ)
  find_package(JPEG REQUIRED)
  target_include_directories(libforeign PRIVATE ${JPEG_INCLUDE_DIR})
endif()

# ./vcpkg install libpng:x64-windows-static
find_package(PNG REQUIRED)
target_include_directories(libforeign PRIVATE ${PNG_INCLUDE_DIR})

# ./vcpkg install libwebp[all]:x64-windows-static
find_package(WebP REQUIRED)
target_include_directories(libforeign PRIVATE ${WebP_INCLUDE_DIR})

